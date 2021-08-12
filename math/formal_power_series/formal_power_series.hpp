#ifndef FORMAL_POWER_SERIES_HEADER_HPP
#define FORMAL_POWER_SERIES_HEADER_HPP

/**
 * @brief basic operations of formal power series / 形式幂级数的基本操作
 * @docs docs/math/formal_power_series/formal_power_series.md
 */

#include <algorithm>
#include <cassert>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

#include "../../traits/modint.hpp"
#include "prime_binomial.hpp"
#include "radix_2_NTT.hpp"

namespace lib {

/**
 * @note 必须使用 NTT 友好的模数！！！
 *       在使用模板类继承时，对于继承来的 public 成员函数，要么使用 using 来声明，要么使用域限定符
 *       要么使用 this 指针，这样在第一次扫描时不会处理，第二次才会分析基类中的函数，
 *       否则不能通过编译。MSVC 因为有扩展的原因可以通过编译，但标准规定是这样。
 *       若不是模板类继承则没有这样的问题。
 *
 */
template <typename mod_t>
class FormalPowerSeries : public std::vector<mod_t> {
private:
  using vec = std::vector<mod_t>;
  using fps = FormalPowerSeries<mod_t>;

public:
  using std::vector<mod_t>::vector;
  using value_type = mod_t;

  /**
   * @brief 获取度数
   * @note 特例为 deg(0)=-1
   * @return int
   */
  int deg() const {
    static constexpr mod_t Z = 0;
    int n                    = int(this->size()) - 1;
    while (n >= 0 && this->operator[](n) == Z) --n;
    return n;
  }

  /**
   * @brief 获取最高次项的系数
   * @return mod_t
   */
  mod_t leading_coeff() const {
    int d = deg();
    return d == -1 ? mod_t(0) : this->operator[](d);
  }

  /**
   * @brief 去除尾 0 ，但如果只有一个 0 则会保留
   */
  void shrink() { this->resize(std::max(deg() + 1, 1)); }
  fps slice() const { return fps(*this); }
  fps slice(int n) const {
    assert(n >= 0);
    int sz = this->size();
    if (sz >= n) return fps(this->begin(), this->begin() + n);
    fps res(*this);
    res.resize(n, mod_t(0));
    return res;
  }

  fps deriv() const {
    int n = this->size();
    if (n <= 1) return {0};
    fps res(n - 1);
    for (int i = 1; i != n; ++i) res[i - 1] = this->operator[](i) * mod_t(i);
    return res;
  }

  fps integr(const mod_t &c = mod_t(0)) const {
    int n = this->size() + 1;
    PrimeBinomial<mod_t> bi(n);
    fps res(n);
    res[0] = c;
    for (int i = 1; i != n; ++i) res[i] = this->operator[](i - 1) * bi.inv_unsafe(i);
    return res;
  }

  fps operator-() const {
    fps res(this->size());
    for (int i = 0, e = this->size(); i != e; ++i) res[i] = -this->operator[](i);
    return res;
  }

  fps &operator+=(const fps &rhs) {
    if (this->size() < rhs.size()) this->resize(rhs.size(), mod_t(0));
    for (int i = 0, e = rhs.size(); i != e; ++i) this->operator[](i) += rhs[i];
    return *this;
  }
  fps &operator-=(const fps &rhs) {
    if (this->size() < rhs.size()) this->resize(rhs.size(), mod_t(0));
    for (int i = 0, e = rhs.size(); i != e; ++i) this->operator[](i) -= rhs[i];
    return *this;
  }
  fps &operator*=(const fps &rhs) {
    int n = this->size(), m = rhs.size();
    if (std::min(n, m) <= 32) {
      fps res(n + m - 1, mod_t(0));
      for (int i = 0; i != n; ++i) {
        for (int j = 0; j != m; ++j) { res[i + j] += this->operator[](i) * rhs[j]; }
      }
      return this->operator=(res);
    }
    int len = get_ntt_len(n + m - 1);
    this->resize(len, mod_t(0));
    if (this == &rhs) {
      dft(len, this->data());
      for (int i = 0; i != len; ++i) this->operator[](i) *= this->operator[](i);
      idft(len, this->data());
      this->resize(n + m - 1);
      return *this;
    }
    auto b = rhs.slice(len);
    dft(len, this->data());
    dft(len, b.data());
    for (int i = 0; i != len; ++i) this->operator[](i) *= b[i];
    idft(len, this->data());
    this->resize(n + m - 1);
    return *this;
  }

  fps &operator/=(const fps &rhs) { // 13E
    int n = this->size();
    if (n == 0) return *this;
    assert(rhs[0] != 0);
    if (n == 1) {
      this->operator[](0) /= rhs[0];
      return *this;
    }
    int len = get_ntt_len(n), len2 = len >> 1;
    fps work_tmp1(rhs.inv(len2)), work_tmp2(slice(len2)), work_tmp3(rhs.slice(len));
    // rhs.inv(len2) 花费 5E
    work_tmp1.resize(len, mod_t(0));
    dft(len, work_tmp1.data()); // 1E
    work_tmp2.resize(len, mod_t(0));
    dft(len, work_tmp2.data()); // 1E
    for (int i = 0; i != len; ++i) work_tmp2[i] *= work_tmp1[i];
    idft(len, work_tmp2.data()); // 1E
    std::copy_n(work_tmp2.begin(), len2, this->begin());
    std::fill_n(work_tmp2.begin() + len2, len2, mod_t(0));
    dft(len, work_tmp2.data()); // 1E
    dft(len, work_tmp3.data()); // 1E
    for (int i = 0; i != len; ++i) work_tmp3[i] *= work_tmp2[i];
    idft(len, work_tmp3.data()); // 1E
    std::fill_n(work_tmp3.begin(), len2, mod_t(0));
    this->resize(len);
    for (int i = len2; i != len; ++i) work_tmp3[i] = this->operator[](i) - work_tmp3[i];
    dft(len, work_tmp3.data()); // 1E
    for (int i = 0; i != len; ++i) work_tmp3[i] *= work_tmp1[i];
    idft(len, work_tmp3.data()); // 1E
    std::copy_n(work_tmp3.begin() + len2, n - len2, this->begin() + len2);
    this->resize(n);
    return *this;
  }

  fps inv(int n) const { // 10E
    assert(n > 0);
    assert(this->operator[](0) != 0);
    if (n == 1) return {mod_t(1) / this->operator[](0)};
    int len = get_ntt_len(n);
    fps res(len, mod_t(0)), work_tmp1(len), work_tmp2(len), cpy(slice(len));
    res[0] = mod_t(1) / this->operator[](0);
    for (int i = 2; i <= len; i <<= 1) {
      std::copy_n(cpy.begin(), i, work_tmp1.begin());
      dft(i, work_tmp1.data()); // 2E
      std::copy_n(res.begin(), i, work_tmp2.begin());
      dft(i, work_tmp2.data()); // 2E
      for (int j = 0; j != i; ++j) work_tmp1[j] *= work_tmp2[j];
      idft(i, work_tmp1.data()); // 2E
      std::fill_n(work_tmp1.begin(), i >> 1, mod_t(0));
      dft(i, work_tmp1.data()); // 2E
      for (int j = 0; j != i; ++j) work_tmp1[j] *= work_tmp2[j];
      idft(i, work_tmp1.data()); // 2E
      for (int j = i >> 1; j != i; ++j) res[j] = -work_tmp1[j];
    }
    res.resize(n);
    return res;
  }

  fps div(int n, const fps &rhs) const { return slice(n) /= rhs; }

  mod_t div_at(const fps &rhs, unsigned long long k) const { // [x^k](*this)/rhs
    // 当 this->deg>rhs.deg() 时我们可以计算一次欧几里得除法得到商和余数 (q, r)
    // q + r/rhs 注意此时若 k<=q.deg() 则答案需要加上[x^k]q，否则的话我们转而计算 r/rhs
    // 但是此处没有使用这个方法
    assert(rhs.deg() >= 0);
    assert(rhs[0] != 0);
    int offset = std::max(deg(), rhs.deg()) + 1;
    if (k <= offset) return div(k + 1, rhs).back();
    fps cpy(*this), rhs_cpy(rhs);
    int len = get_ntt_len((offset << 1) - 1);
    cpy.resize(len, mod_t(0));
    rhs_cpy.resize(len, mod_t(0));
    dft(len, cpy.data());
    dft(len, rhs_cpy.data());
    for (;;) {
      for (int i = 0; i != len; ++i) cpy[i] *= rhs_cpy[i ^ 1];
      if (k & 1) NTT<mod_t>::odd_dft(len, cpy.data());
      else
        NTT<mod_t>::even_dft(len, cpy.data());
      for (int i = 0; i != len; i += 2) rhs_cpy[i] = rhs_cpy[i + 1] = rhs_cpy[i] * rhs_cpy[i + 1];
      NTT<mod_t>::even_dft(len, rhs_cpy.data());
      k >>= 1;
      if (k <= offset) break;
      NTT<mod_t>::dft_doubling(len >> 1, cpy.data());
      NTT<mod_t>::dft_doubling(len >> 1, rhs_cpy.data());
    }
    cpy.resize(len >> 1);
    rhs_cpy.resize(len >> 1);
    idft(len >> 1, cpy.data());
    idft(len >> 1, rhs_cpy.data());
    fps irhs_cpy(rhs_cpy.inv(k + 1));
    mod_t sum(0);
    for (int i = 0; i <= k; ++i) sum += irhs_cpy[i] * cpy[k - i];
    return sum;
  }

  fps log(int n) const {
    assert(n > 0);
    assert(!this->empty());
    assert(this->operator[](0) == 1);
    if (this->size() == 1) return fps(n, mod_t(0));
    return deriv().div(n - 1, *this).integr();
  }

  fps exp(int n) const { // 17E
    assert(n > 0);
    assert(this->operator[](0) == 0);
    const mod_t ZERO(0), ONE(1);
    if (n == 1) return {mod_t(1)};
    int len = get_ntt_len(n);
    fps res(len);
    res[0] = mod_t(1), res[1] = this->operator[](1);
    if (n == 2) return res;
    PrimeBinomial<mod_t> bi(len);
    fps work_tmp1(len, ZERO), work_tmp2(len, ZERO), work_tmp3(deriv()), cpy(slice(len)),
        work_tmp4(len), work_tmp6(len), work_tmp7(len);
    work_tmp3.resize(len, ZERO);
    work_tmp1[0] = mod_t(1), work_tmp1[1] = -res[1];
    std::copy_n(res.begin(), 2, work_tmp2.begin());
    dft(4, work_tmp2.data());
    for (int i = 4; i <= len; i <<= 1) {
      mod_t tmp_j(i >> 2);
      for (int j = i >> 2; j != i >> 1; ++j, tmp_j += ONE) work_tmp7[j - 1] = res[j] * tmp_j;
      std::copy_n(work_tmp3.begin(), (i >> 1) - 1, work_tmp4.begin());
      std::fill(work_tmp4.begin() + (i >> 1) - 1, work_tmp4.begin() + i, ZERO);
      dft(i >> 1, work_tmp4.data()); // 1E
      for (int j = 0; j != i >> 1; ++j) work_tmp4[j] *= work_tmp2[j];
      idft(i >> 1, work_tmp4.data()); // 1E
      for (int j = 0; j != (i >> 1) - 2; ++j) work_tmp4[j + (i >> 1)] = work_tmp7[j] - work_tmp4[j];
      work_tmp4[(i >> 1) - 1] = -work_tmp4[(i >> 1) - 1];
      std::fill_n(work_tmp4.begin(), (i >> 1) - 1, ZERO);
      fps work_tmp5(work_tmp1.slice(i));
      dft(i, work_tmp5.data()), dft(i, work_tmp4.data()); // 4E
      for (int j = 0; j != i; ++j) work_tmp4[j] *= work_tmp5[j];
      idft(i, work_tmp4.data()); // 2E
      for (int j = i >> 1; j != i; ++j) work_tmp6[j] = work_tmp4[j - 1] * bi.inv_unsafe(j) - cpy[j];
      std::fill_n(work_tmp6.begin(), i >> 1, ZERO);
      dft(i, work_tmp6.data()); // 2E
      for (int j = 0; j != i; ++j) work_tmp2[j] *= work_tmp6[j];
      idft(i, work_tmp2.data()); // 2E
      for (int j = i >> 1; j != i; ++j) res[j] = -work_tmp2[j];
      if (i != len) { // 10E 最后一次迭代节省 5E
        std::copy_n(res.begin(), i, work_tmp2.begin());
        dft(i << 1, work_tmp2.data()); // 4E
        for (int j = 0; j != i; ++j) work_tmp4[j] = work_tmp2[j] * work_tmp5[j];
        idft(i, work_tmp4.data()); // 2E
        std::fill_n(work_tmp4.begin(), i >> 1, ZERO);
        dft(i, work_tmp4.data()); // 2E
        for (int j = 0; j != i; ++j) work_tmp4[j] *= work_tmp5[j];
        idft(i, work_tmp4.data()); // 2E
        for (int j = i >> 1; j != i; ++j) work_tmp1[j] = -work_tmp4[j];
      }
    }
    res.resize(n);
    return res;
  }

  fps pow(int n, long long e) const {
    const mod_t ZERO(0), ME(e);
    fps cpy(slice(n));
    int ord = 0;
    while (ord < n && cpy[ord] == ZERO) ++ord;
    long long offset = ord * e;
    if (offset >= n) return fps(n, ZERO);
    fps res(n, ZERO);
    mod_t k(cpy[ord]), ik(mod_t(1) / k);
    for (int i = ord; i != n; ++i) cpy[i] *= ik;
    fps t(fps(cpy.begin() + ord, cpy.end()).log(n - offset));
    for (int i = 0; i != n - offset; ++i) t[i] *= ME;
    fps pt(t.exp(n - offset));
    k = k.pow(e);
    for (int i = offset; i != n; ++i) res[i] = pt[i - offset] * k;
    return res;
  }

  // TODO
  fps sqrt(int n, mod_t c) const;

  friend fps operator+(const fps &lhs, const fps &rhs) { return fps(lhs) += rhs; }
  friend fps operator-(const fps &lhs, const fps &rhs) { return fps(lhs) -= rhs; }
  friend fps operator*(const fps &lhs, const fps &rhs) { return fps(lhs) *= rhs; }
  friend fps operator/(const fps &lhs, const fps &rhs) { return fps(lhs) /= rhs; }
};

template <typename mod_t>
using FPS = FormalPowerSeries<mod_t>;

} // namespace lib

#endif