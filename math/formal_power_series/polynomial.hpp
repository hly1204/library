#ifndef POLYNOMIAL_HEADER_HPP
#define POLYNOMIAL_HEADER_HPP

/**
 * @brief polynomial / 多项式
 * @docs docs/math/formal_power_series/polynomial.md
 */

#include "NTT_binomial.hpp"
#include "formal_power_series.hpp"

namespace lib {

/**
 * @brief 多项式类
 * @note 基类 FormalPowerSeries 中函数都没有使用 virtual
 *       所以在该类中有定义相同的函数则会阻止调用基类的函数
 *       这被称为隐藏（ hide ）。
 *       而如果使用了 virtual 则被称为覆盖（ override ），而覆盖会导出多态。
 */
template <typename mod_t>
class Polynomial : public FormalPowerSeries<mod_t> {
private:
  using fps  = FormalPowerSeries<mod_t>;
  using poly = Polynomial<mod_t>;

public:
  using FormalPowerSeries<mod_t>::FormalPowerSeries;
  using value_type = mod_t;

  // 使得能够从 FormalPowerSeries 转换为 Polynomial 类型，但不清楚是否有什么问题
  Polynomial(const fps &rhs) : fps(rhs) {}
  Polynomial(fps &&rhs) : fps(std::move(rhs)) {}

  poly operator-() const {
    poly res = this->fps::operator-();
    res.shrink();
    return res;
  }
  poly &operator+=(const poly &rhs) {
    this->fps::operator+=(rhs);
    this->shrink();
    return *this;
  }
  poly &operator-=(const poly &rhs) {
    this->fps::operator-=(rhs);
    this->shrink();
    return *this;
  }
  poly &operator*=(const poly &rhs) {
    this->fps::operator*=(rhs);
    this->shrink();
    return *this;
  }
  poly &operator/=(const poly &rhs) {
    assert(rhs.deg() >= 0);
    this->shrink();
    int quo_size = this->deg() - rhs.deg() + 1;
    if (quo_size <= 0) {
      this->resize(1);
      this->operator[](0) = 0;
      return *this;
    }
    poly rhs_cpy(rhs);
    rhs_cpy.shrink();
    std::reverse(this->begin(), this->end());
    std::reverse(rhs_cpy.begin(), rhs_cpy.end());
    poly quo(this->div(quo_size, rhs_cpy));
    this->resize(quo_size);
    std::reverse_copy(quo.begin(), quo.end(), this->begin());
    return *this;
  }
  poly &operator%=(const poly &rhs) {
    // f/g => f=gq+r, deg(r)<deg(g) 在这里 f 就是 (*this) 而 g 就是 rhs
    // r=f-gq (mod ((x^deg(rhs)) - 1))
    // 所以我们做 NTT 的长度可以是 O(deg(rhs)) 级别的
    int rem_size = rhs.deg();
    assert(rem_size >= 0);
    if (rem_size == 0) {
      this->resize(1);
      this->operator[](0) = 0;
      return *this;
    }
    this->shrink();
    if (this->deg() < rem_size) return *this;
    poly quo((*this) / rhs), rhs_cpy(rhs);
    int len = get_ntt_len(rem_size);
    // 令 (*this) 和 quo 和 rhs_cpy 都在 mod ((x^len) - 1) 意义下
    int mask = len - 1;
    for (int i = len, e = this->size(); i < e; ++i)
      this->operator[](i &mask) += this->operator[](i);
    for (int i = len, e = quo.size(); i < e; ++i) quo[i & mask] += quo[i];
    for (int i = len, e = rhs_cpy.size(); i < e; ++i) rhs_cpy[i & mask] += rhs_cpy[i];
    this->resize(len, mod_t(0));
    quo.resize(len, mod_t(0));
    rhs_cpy.resize(len, mod_t(0));
    dft(len, rhs_cpy.data());
    dft(len, quo.data());
    for (int i = 0; i != len; ++i) rhs_cpy[i] *= quo[i];
    idft(len, rhs_cpy.data());
    this->resize(rem_size);
    for (int i = 0; i != rem_size; ++i) this->operator[](i) -= rhs_cpy[i];
    this->shrink();
    return *this;
  }
  std::pair<poly, poly> divmod(const poly &rhs) const {
    int rem_size = rhs.deg();
    assert(rem_size >= 0);
    if (rem_size == 0) return {(*this) * poly{rhs[0].inv()}, poly{0}};
    poly cpy(*this);
    cpy.shrink();
    if (cpy.deg() < rem_size) return {poly{0}, cpy};
    poly quo(cpy / rhs), quo_cpy(quo), rhs_cpy(rhs);
    int len = get_ntt_len(rem_size), mask = len - 1;
    for (int i = len, e = cpy.size(); i < e; ++i) cpy[i & mask] += cpy[i];
    for (int i = len, e = quo_cpy.size(); i < e; ++i) quo_cpy[i & mask] += quo_cpy[i];
    for (int i = len, e = rhs_cpy.size(); i < e; ++i) rhs_cpy[i & mask] += rhs_cpy[i];
    cpy.resize(len, mod_t(0));
    quo_cpy.resize(len, mod_t(0));
    rhs_cpy.resize(len, mod_t(0));
    dft(len, rhs_cpy.data());
    dft(len, quo_cpy.data());
    for (int i = 0; i != len; ++i) rhs_cpy[i] *= quo_cpy[i];
    idft(len, rhs_cpy.data());
    cpy.resize(rem_size);
    for (int i = 0; i != rem_size; ++i) cpy[i] -= rhs_cpy[i];
    cpy.shrink();
    return {quo, cpy};
  }

  poly pow_mod(unsigned long long e, const poly &mod) const {
    int rem_size = mod.deg();
    assert(rem_size >= 0);
    if (rem_size == 0) return poly{0};
    poly res{1}, cpy(*this % mod), mod_cpy(mod), rev_mod(mod);
    mod_cpy.shrink();
    rev_mod.shrink();
    std::reverse(rev_mod.begin(), rev_mod.end());        // x^{deg(mod)}mod(-x)
    int len          = get_ntt_len((rem_size << 1) - 1); // 两个 rem_size 长的多项式相乘
    int len2         = get_ntt_len(rem_size);
    int mask         = len2 - 1;
    int max_quo_size = rem_size;
#define MODIFY_POLY(t)                                                  \
  {                                                                     \
    for (int i = len2, ie = t.size(); i < ie; ++i) t[i & mask] += t[i]; \
    t.resize(len2);                                                     \
  }
    MODIFY_POLY(mod_cpy);
    dft(len2, mod_cpy.data());
    poly rev_mod_inv(rev_mod.inv(max_quo_size));
    rev_mod_inv.resize(len, mod_t(0));
    dft(len, rev_mod_inv.data());
    for (; e; e >>= 1) {
      if (e & 1) {
        // res=res*cpy%mod,cpy=cpy*cpy%mod
        // 先进行两次卷积，后翻转，取前 quo_size 项与 rev_mod 的逆卷积求出 rev_quo
        // 翻转求出 quo 后与 mod 卷积，这一步的 dft 可以在 O(deg(mod)) 级别
        // 后作一次减法即可
        res.resize(len, mod_t(0));
        cpy.resize(len, mod_t(0));
        dft(len, res.data());
        dft(len, cpy.data());
        for (int i = 0; i != len; ++i) res[i] *= cpy[i], cpy[i] *= cpy[i];
        idft(len, res.data());
        idft(len, cpy.data());
        int quo_size_res = res.deg() - rem_size + 1;
        if (quo_size_res > 0) {
          poly rev_res(res);
          rev_res.shrink();
          std::reverse(rev_res.begin(), rev_res.end());
          rev_res.resize(len);
          std::fill(rev_res.begin() + quo_size_res, rev_res.end(), mod_t(0));
          dft(len, rev_res.data());
          for (int i = 0; i != len; ++i) rev_res[i] *= rev_mod_inv[i];
          idft(len, rev_res.data());
          rev_res.resize(quo_size_res);
          std::reverse(rev_res.begin(), rev_res.end());
          MODIFY_POLY(res);
          MODIFY_POLY(rev_res);
          dft(len2, rev_res.data());
          for (int i = 0; i != len2; ++i) rev_res[i] *= mod_cpy[i];
          idft(len2, rev_res.data());
          for (int i = 0; i != len2; ++i) res[i] -= rev_res[i];
        }
      } else {
        cpy *= cpy;
      }
      int quo_size_cpy = cpy.deg() - rem_size + 1;
      if (quo_size_cpy > 0) {
        poly rev_cpy(cpy);
        rev_cpy.shrink();
        std::reverse(rev_cpy.begin(), rev_cpy.end());
        rev_cpy.resize(len);
        std::fill(rev_cpy.begin() + quo_size_cpy, rev_cpy.end(), mod_t(0));
        dft(len, rev_cpy.data());
        for (int i = 0; i != len; ++i) rev_cpy[i] *= rev_mod_inv[i];
        idft(len, rev_cpy.data());
        rev_cpy.resize(quo_size_cpy);
        std::reverse(rev_cpy.begin(), rev_cpy.end());
        MODIFY_POLY(cpy);
        MODIFY_POLY(rev_cpy);
        dft(len2, rev_cpy.data());
        for (int i = 0; i != len2; ++i) rev_cpy[i] *= mod_cpy[i];
        idft(len2, rev_cpy.data());
        for (int i = 0; i != len2; ++i) cpy[i] -= rev_cpy[i];
      }
    }
#undef MODIFY_POLY
    res.shrink();
    return res;
  }

  poly shift(mod_t c) const {
    int n = this->deg();
    if (n < 1) return poly(*this);
    NTTBinomial<mod_t> bi(n + 1);
    poly A(*this), B(n + 1);
    mod_t c_i(1);
    for (int i = 0; i <= n; ++i) A[i] *= bi.fac_unsafe(i), B[i] = c_i * bi.ifac_unsafe(i), c_i *= c;
    std::reverse(A.begin(), A.end());
    A *= B;
    A.resize(n + 1);
    std::reverse(A.begin(), A.end());
    for (int i = 0; i <= n; ++i) A[i] *= bi.ifac_unsafe(i);
    return A;
  }

  friend poly operator+(const poly &lhs, const poly &rhs) { return poly(lhs) += rhs; }
  friend poly operator-(const poly &lhs, const poly &rhs) { return poly(lhs) -= rhs; }
  friend poly operator*(const poly &lhs, const poly &rhs) { return poly(lhs) *= rhs; }
  friend poly operator/(const poly &lhs, const poly &rhs) { return poly(lhs) /= rhs; }
  friend poly operator%(const poly &lhs, const poly &rhs) { return poly(lhs) %= rhs; }
};

template <typename mod_t>
using Poly = Polynomial<mod_t>;

} // namespace lib

#endif