#ifndef POLYNOMIAL_HPP
#define POLYNOMIAL_HPP

#include "../common.hpp"
#include "truncated_formal_power_series.hpp"

#include <cassert>
#include <iostream>
#include <type_traits>
#include <utility>
#include <vector>

LIB_BEGIN

template <typename ModIntT>
class polynomial : public truncated_formal_power_series<ModIntT> {
  using MyBase = truncated_formal_power_series<ModIntT>;
  static_assert(std::is_same_v<typename MyBase::value_type, ModIntT>);

public:
  using truncated_formal_power_series<ModIntT>::truncated_formal_power_series;

  explicit polynomial(const MyBase &rhs) : MyBase(rhs) {}
  ModIntT operator()(ModIntT c) const {
    ModIntT res;
    for (int i = this->deg(); i >= 0; --i) res = res * c + this->operator[](i);
    return res;
  }
  polynomial operator-() { return MyBase::operator-(); }
  polynomial &operator+=(const polynomial &rhs) {
    MyBase::operator+=(rhs);
    this->shrink();
    return *this;
  }
  polynomial &operator-=(const polynomial &rhs) {
    MyBase::operator-=(rhs);
    this->shrink();
    return *this;
  }
  polynomial &operator*=(const polynomial &rhs) {
    MyBase::operator*=(rhs);
    this->shrink();
    return *this;
  }
  polynomial &operator/=(const polynomial &rhs) {
    const int n = this->deg(), m = rhs.deg();
    assert(m != MyBase::NEGATIVE_INFINITY);
    if (n < m) {
      this->clear();
      return *this;
    }
    auto irev_rhs = polynomial(rhs.crbegin() + (rhs.size() - m - 1), rhs.crend()).inv(n - m + 1);
    auto lhsirhs  = *this * polynomial(irev_rhs.crbegin(), irev_rhs.crend());
    this->resize(n - m + 1);
    std::copy(lhsirhs.cbegin() + n, lhsirhs.cend(), this->begin());
    return *this;
  }
  polynomial &operator%=(const polynomial &rhs) {
    return this->operator=(div_with_rem(rhs).second);
  }
  std::pair<polynomial, polynomial> div_with_rem(const polynomial &rhs) {
    const int n = this->deg(), m = rhs.deg();
    if (n < m) return std::make_pair(polynomial(), *this);
    auto q    = *this / rhs;
    auto qrhs = q * rhs;
    polynomial r(m);
    for (int i = 0; i != m; ++i) r[i] = this->operator[](i) - qrhs[i];
    r.shrink();
    return std::make_pair(q, r);
  }

  friend polynomial operator+(const polynomial &lhs, const polynomial &rhs) {
    return polynomial(lhs) += rhs;
  }
  friend polynomial operator-(const polynomial &lhs, const polynomial &rhs) {
    return polynomial(lhs) -= rhs;
  }
  friend polynomial operator*(const polynomial &lhs, const polynomial &rhs) {
    return polynomial(lhs) *= rhs;
  }
  friend polynomial operator/(const polynomial &lhs, const polynomial &rhs) {
    return polynomial(lhs) /= rhs;
  }
  friend polynomial operator%(const polynomial &lhs, const polynomial &rhs) {
    return polynomial(lhs) %= rhs;
  }
  friend std::istream &operator>>(std::istream &lhs, polynomial &rhs) {
    for (auto &&i : rhs) lhs >> i;
    return lhs;
  }
  friend std::ostream &operator<<(std::ostream &lhs, const polynomial &rhs) {
    return lhs << MyBase(rhs.begin(), rhs.end()); // debug only (SLOW)
  }
};

template <typename IterT>
polynomial(IterT, IterT) -> polynomial<typename std::iterator_traits<IterT>::value_type>;

LIB_END

#endif