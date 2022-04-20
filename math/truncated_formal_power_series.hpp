#ifndef TRUNCATED_FORMAL_POWER_SERIES_HPP
#define TRUNCATED_FORMAL_POWER_SERIES_HPP

#include "../common.hpp"
#include "radix2_ntt.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

LIB_BEGIN

template <typename ModIntT>
class truncated_formal_power_series : public std::vector<ModIntT> {
  static_assert(std::is_same_v<typename std::vector<ModIntT>::value_type, ModIntT>);

public:
  using std::vector<ModIntT>::vector;

  enum : int { NEGATIVE_INFINITY = -1 };

  // leading coefficient
  ModIntT lc() const {
    int d = deg();
    return d == NEGATIVE_INFINITY ? ModIntT() : this->operator[](d);
  }
  // degree
  int deg() const {
    // treat formal power series like polynomials
    int n = static_cast<int>(this->size());
    while (n >= 0 && !this->operator[](n).is_zero()) --n;
    return n == -1 ? NEGATIVE_INFINITY : n;
  }
  // order
  int ord() const;
  bool is_zero() const { return deg() == NEGATIVE_INFINITY; }
  void shrink() { this->resize(deg() + 1); }
  truncated_formal_power_series operator-() {
    truncated_formal_power_series res(*this);
    for (auto &&i : res) i = -i;
    return res;
  }

  truncated_formal_power_series &operator+=(const truncated_formal_power_series &rhs) {
    if (this->size() < rhs.size()) this->resize(rhs.size());
    for (int i = 0, e = static_cast<int>(rhs.size()); i != e; ++i) this->operator[](i) += rhs[i];
    return *this;
  }
  truncated_formal_power_series &operator-=(const truncated_formal_power_series &rhs) {
    if (this->size() < rhs.size()) this->resize(rhs.size());
    for (int i = 0, e = static_cast<int>(rhs.size()); i != e; ++i) this->operator[](i) -= rhs[i];
    return *this;
  }
  truncated_formal_power_series &operator*=(const truncated_formal_power_series &rhs);
  truncated_formal_power_series inv(int n) const;
  truncated_formal_power_series log(int n) const;
  truncated_formal_power_series exp(int n) const;
  truncated_formal_power_series div(const truncated_formal_power_series &rhs, int n) const;

  friend truncated_formal_power_series operator+(const truncated_formal_power_series &lhs,
                                                 const truncated_formal_power_series &rhs) {
    return truncated_formal_power_series(lhs) += rhs;
  }
  friend truncated_formal_power_series operator-(const truncated_formal_power_series &lhs,
                                                 const truncated_formal_power_series &rhs) {
    return truncated_formal_power_series(lhs) -= rhs;
  }
  friend truncated_formal_power_series operator*(const truncated_formal_power_series &lhs,
                                                 const truncated_formal_power_series &rhs) {
    return truncated_formal_power_series(lhs) *= rhs;
  }

  friend std::istream &operator>>(std::istream &lhs, truncated_formal_power_series &rhs) {
    for (auto &&i : rhs) lhs >> i;
    return lhs;
  }
  friend std::ostream &operator<<(std::ostream &lhs, const truncated_formal_power_series &rhs) {
    int s = 0, e = static_cast<int>(rhs.size());
    lhs << '[';
    for (auto &&i : rhs) {
      lhs << i;
      if (s >= 1) lhs << 'x';
      if (s > 1) lhs << '^' << s;
      if (++s != e) lhs << " + ";
    }
    return lhs << ']';
  }
};

template <typename IterT>
truncated_formal_power_series(IterT, IterT)
    -> truncated_formal_power_series<typename std::iterator_traits<IterT>::value_type>;

template <typename ModIntT>
using tfps = truncated_formal_power_series<ModIntT>;

template <typename ModIntT>
tfps<ModIntT> &tfps<ModIntT>::operator*=(const tfps<ModIntT> &rhs) {
  // 6E
  int n = static_cast<int>(this->size()), m = static_cast<int>(rhs.size());
  if (n == 0 || m == 0) {
    this->clear();
    return *this;
  }
  if (std::min(n, m) <= 32) {
    tfps<ModIntT> res(n + m - 1);
    for (int i = 0; i != n; ++i)
      for (int j = 0; j != m; ++j) res[i + j] += this->operator[](i) * rhs[j];
    return this->operator=(res);
  }
  int len = ntt_len(n + m - 1);
  tfps<ModIntT> rhs_cpy(len);
  std::copy_n(rhs.cbegin(), m, rhs_cpy.begin());
  this->resize(len);
  dft_n(this->begin(), len), dft_n(rhs_cpy.begin(), len);
  for (int i = 0; i != len; ++i) this->operator[](i) *= rhs_cpy[i];
  idft_n(this->begin(), len);
  this->resize(n + m - 1);
  return *this;
}

template <typename ModIntT>
tfps<ModIntT> tfps<ModIntT>::inv(int n) const {
  // 10E
  assert(n > 0);
  assert(!this->front().is_zero());
  if (n == 1) return tfps<ModIntT>{this->front().inv()};
  int len = ntt_len(n);
  tfps<ModIntT> res(len), temp0(len), temp1(len), cpy(len);
  std::copy(this->cbegin(), this->cend(), cpy.begin());
  res.front() = this->front().inv();
  for (int i = 2; i <= len; i <<= 1) {
    std::copy_n(cpy.cbegin(), i, temp0.begin());
    dft_n(temp0.begin(), i); // 2E
    std::copy_n(res.cbegin(), i, temp1.begin());
    dft_n(temp1.begin(), i); // 2E
    for (int j = 0; j != i; ++j) temp0[j] *= temp1[j];
    idft_n(temp0.begin(), i); // 2E
    std::fill_n(temp0.begin(), i >> 1, ModIntT());
    dft_n(temp0.begin(), i); // 2E
    for (int j = 0; j != i; ++j) temp0[j] *= temp1[j];
    idft_n(temp0.begin(), i); // 2E
    for (int j = i >> 1; j != i; ++j) res[j] = -temp0[j];
  }
  res.resize(n);
  return res;
}

LIB_END

#endif