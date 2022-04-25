#ifndef TRUNCATED_FORMAL_POWER_SERIES_HPP
#define TRUNCATED_FORMAL_POWER_SERIES_HPP

#include "../common.hpp"
#include "extended_gcd.hpp"
#include "radix2_ntt.hpp"
#include "semi_relaxed_convolution.hpp"

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

  static typename detail::modular_inverse<ModIntT> invs;

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
    while (n >= 0 && this->operator[](n).is_zero()) --n;
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
  truncated_formal_power_series integr(ModIntT c = ModIntT()) const {
    const int n = static_cast<int>(this->size()) + 1;
    truncated_formal_power_series res(n);
    res.front() = c;
    for (int i = 1; i < n; ++i) res[i] = this->operator[](i - 1) * invs(i);
    return res;
  }
  truncated_formal_power_series deriv() const {
    const int n = static_cast<int>(this->size()) - 1;
    if (n <= 0) return truncated_formal_power_series{};
    truncated_formal_power_series res(n);
    for (int i = 1; i <= n; ++i) res[i - 1] = this->operator[](i) * i;
    return res;
  }
  truncated_formal_power_series inv(int n) const;
  truncated_formal_power_series log(int n) const { return deriv().div(*this, n - 1).integr(); }
  truncated_formal_power_series exp(int n) const;
  truncated_formal_power_series div(const truncated_formal_power_series &rhs, int n) const;
  truncated_formal_power_series pow(int n, long long e) const;

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
      // clang-format off
      if (s > 9) lhs << "^(" << s << ')';
      else if (s > 1) lhs << '^' << s;
      // clang-format on
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
typename detail::modular_inverse<ModIntT> tfps<ModIntT>::invs;

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
  if (n <= 0) return tfps<ModIntT>{};
  const std::vector a(this->cbegin(), this->cend());
  semi_relaxed_convolution src(a, [iv = a.front().inv()](int n, const std::vector<ModIntT> &c) {
    return n == 0 ? iv : -c[n] * iv;
  });
  auto &&multiplier = src.await(n).get_multiplier();
  return tfps<ModIntT>(multiplier.cbegin(), multiplier.cend());
}

template <typename ModIntT>
tfps<ModIntT> tfps<ModIntT>::exp(int n) const {
  if (n <= 0) return tfps<ModIntT>{};
  auto &&d = deriv();
  std::vector dv(d.cbegin(), d.cend());
  semi_relaxed_convolution src(dv, [this](int n, const std::vector<ModIntT> &c) {
    return n == 0 ? ModIntT(1) : c[n - 1] * invs(n);
  });
  auto &&multiplier = src.await(n).get_multiplier();
  return tfps<ModIntT>(multiplier.cbegin(), multiplier.cend());
}

template <typename ModIntT>
tfps<ModIntT> tfps<ModIntT>::div(const truncated_formal_power_series &rhs, int n) const {
  assert(!rhs.is_zero());
  if (n <= 0) return tfps<ModIntT>{};
  const std::vector a(rhs.cbegin(), rhs.cend());
  semi_relaxed_convolution src(
      a, [this, iv = a.front().inv()](int n, const std::vector<ModIntT> &c) {
        return ((n < static_cast<int>(this->size()) ? this->operator[](n) : ModIntT()) - c[n]) * iv;
      });
  auto &&multiplier = src.await(n).get_multiplier();
  return tfps<ModIntT>(multiplier.cbegin(), multiplier.cend());
}

LIB_END

#endif