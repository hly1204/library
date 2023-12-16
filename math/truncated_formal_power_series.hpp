#ifndef TRUNCATED_FORMAL_POWER_SERIES_HPP
#define TRUNCATED_FORMAL_POWER_SERIES_HPP

#include "../common.hpp"
#include "extended_gcd.hpp"
#include "semi_relaxed_convolution.hpp"
#include "sqrt_mod.hpp"
#include "truncated_fourier_transform.hpp"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <optional>
#include <type_traits>
#include <utility>
#include <vector>

LIB_BEGIN

template <typename ModIntT>
class truncated_formal_power_series : public std::vector<ModIntT> {
  using MyBase = std::vector<ModIntT>;
  static_assert(std::is_same_v<typename MyBase::value_type, ModIntT>);
  static typename detail::modular_inverse<ModIntT> invs;

public:
  using std::vector<ModIntT>::vector;

  truncated_formal_power_series(const std::vector<ModIntT> &v) : std::vector<ModIntT>(v) {}
  truncated_formal_power_series(std::vector<ModIntT> &&v) : std::vector<ModIntT>(std::move(v)) {}

  enum : int { NEGATIVE_INFINITY = -1 };

  // leading coefficient
  ModIntT lc() const {
    int d = deg();
    return d == NEGATIVE_INFINITY ? ModIntT() : this->operator[](d);
  }
  // degree
  int deg() const {
    // treat formal power series like polynomials
    int n = static_cast<int>(this->size()) - 1;
    while (n >= 0 && this->operator[](n).is_zero()) --n;
    return n == -1 ? NEGATIVE_INFINITY : n;
  }
  // order
  int ord() const {
    int d = deg();
    if (d == NEGATIVE_INFINITY) return NEGATIVE_INFINITY;
    for (int i = 0;; ++i)
      if (!this->operator[](i).is_zero()) return i;
  }
  bool is_zero() const { return deg() == NEGATIVE_INFINITY; }
  void shrink() { this->resize(deg() + 1); }
  truncated_formal_power_series operator-() const {
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
  std::optional<truncated_formal_power_series> sqrt_hint(int n, ModIntT c) const;
  std::optional<truncated_formal_power_series> sqrt(int n) const;

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
typename detail::modular_inverse<ModIntT> truncated_formal_power_series<ModIntT>::invs;

template <typename ModIntT>
truncated_formal_power_series<ModIntT> &
truncated_formal_power_series<ModIntT>::operator*=(const truncated_formal_power_series &rhs) {
  // 6E
  int n = static_cast<int>(this->size()), m = static_cast<int>(rhs.size());
  if (n == 0 || m == 0) {
    this->clear();
    return *this;
  }
  if (std::min(n, m) <= 32) {
    truncated_formal_power_series res(n + m - 1);
    for (int i = 0; i != n; ++i)
      for (int j = 0; j != m; ++j) res[i + j] += this->operator[](i) * rhs[j];
    return this->operator=(res);
  }
  int len = n + m - 1;
  truncated_formal_power_series rhs_cpy(len);
  std::copy_n(rhs.cbegin(), m, rhs_cpy.begin());
  this->resize(len);
  tft(*this), tft(rhs_cpy);
  for (int i = 0; i != len; ++i) this->operator[](i) *= rhs_cpy[i];
  itft(*this);
  return *this;
}

template <typename ModIntT>
truncated_formal_power_series<ModIntT> truncated_formal_power_series<ModIntT>::inv(int n) const {
  return semi_relaxed_convolution(static_cast<const MyBase &>(*this),
                                  [iv = this->front().inv()](int n, const std::vector<ModIntT> &c) {
                                    return n == 0 ? iv : -c[n] * iv;
                                  })
      .await(n)
      .get_rhs();
}

template <typename ModIntT>
truncated_formal_power_series<ModIntT> truncated_formal_power_series<ModIntT>::exp(int n) const {
  return semi_relaxed_convolution(static_cast<MyBase>(deriv()),
                                  [](int n, const std::vector<ModIntT> &c) {
                                    return n == 0 ? ModIntT(1) : c[n - 1] * invs(n);
                                  })
      .await(n)
      .get_rhs();
}

template <typename ModIntT>
truncated_formal_power_series<ModIntT>
truncated_formal_power_series<ModIntT>::div(const truncated_formal_power_series &rhs, int n) const {
  assert(!rhs.is_zero());
  return semi_relaxed_convolution(static_cast<const MyBase &>(rhs),
                                  [this, sz = static_cast<int>(this->size()),
                                   iv = rhs.front().inv()](int n, const std::vector<ModIntT> &c) {
                                    return ((n < sz ? this->operator[](n) : ModIntT()) - c[n]) * iv;
                                  })
      .await(n)
      .get_rhs();
}

template <typename ModIntT>
truncated_formal_power_series<ModIntT>
truncated_formal_power_series<ModIntT>::pow(int n, long long e) const {
  if (e == 0) {
    truncated_formal_power_series res{1};
    res.resize(n);
    return res;
  }
  const int o = ord();
  if (o == NEGATIVE_INFINITY || (o > n / e || (o == n / e && n % e == 0)))
    return truncated_formal_power_series(n);
  const long long zs = static_cast<long long>(o) * e; // count zeros
  const int nn       = n - static_cast<int>(zs);
  const ModIntT c(this->operator[](o)), ic(c.inv()), ce(c.pow(e)), me(e);
  truncated_formal_power_series cpy(this->cbegin() + o, this->cend()); // optimize?
  for (auto &&i : cpy) i *= ic;
  cpy = cpy.log(nn);
  for (auto &&i : cpy) i *= me;
  cpy = cpy.exp(nn);
  for (auto &&i : cpy) i *= ce;
  cpy.insert(cpy.begin(), zs, ModIntT());
  return cpy;
}

template <typename ModIntT>
std::optional<truncated_formal_power_series<ModIntT>>
truncated_formal_power_series<ModIntT>::sqrt_hint(int n, ModIntT c) const {
  if (this->empty()) return {};
  const int o = ord();
  if (o == NEGATIVE_INFINITY) return truncated_formal_power_series(n);
  if ((o & 1) || c * c != this->operator[](o)) return {};
  truncated_formal_power_series cpy(this->cbegin() + o, this->cend());
  const ModIntT iv(cpy.front().inv());
  for (auto &&i : cpy) i *= iv;
  cpy = cpy.pow(n - (o >> 1), static_cast<long long>(ModIntT(2).inv()));
  for (auto &&i : cpy) i *= c;
  cpy.insert(cpy.begin(), o >> 1, ModIntT());
  return cpy;
}

template <typename ModIntT>
std::optional<truncated_formal_power_series<ModIntT>>
truncated_formal_power_series<ModIntT>::sqrt(int n) const {
  if (this->empty()) return {};
  const int o = ord();
  if (o == NEGATIVE_INFINITY) return truncated_formal_power_series(n);
  if (o & 1) return {};
  auto res = sqrt_mod_prime(this->operator[](o));
  if (res.empty()) return {};
  return sqrt_hint(n, res.front());
}

template <typename ModIntT>
using tfps = truncated_formal_power_series<ModIntT>;

LIB_END

#endif
