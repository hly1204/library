#ifndef EXTENDED_EUCLIDEAN_HEADER_HPP
#define EXTENDED_EUCLIDEAN_HEADER_HPP

#include <cassert>
#include <tuple>
#include <type_traits>

#include "../../traits/base.hpp"

namespace lib::internal {

template <typename T>
std::enable_if_t<std::is_integral_v<T>, T> gcd(T a, T b) {
  while (b != 0) std::tie(a, b) = std::make_tuple(b, a % b);
  return a;
}

template <typename T, typename S = std::make_signed_t<T>>
std::enable_if_t<std::is_integral_v<T>, std::tuple<T, S, S>> exgcd(T a, T b) {
  S a_p = a, b_p = b, x1 = 1, x2 = 0, x3 = 0, x4 = 1;
  while (b_p != 0) {
    S q = a_p / b_p;
    std::tie(x1, x2, x3, x4, a_p, b_p) =
        std::make_tuple(x3, x4, x1 - x3 * q, x2 - x4 * q, b_p, a_p - b_p * q);
  }
  return std::make_tuple(static_cast<T>(a_p), x1, x2);
}

template <typename T>
std::enable_if_t<std::is_integral_v<T>, T> inv_mod(T x, T mod) {
  using S = std::make_signed_t<T>;
  S a = x < mod ? x : x % mod, b = mod, x1 = 1, x3 = 0;
  while (b != 0) {
    S q                    = a / b;
    std::tie(x1, x3, a, b) = std::make_tuple(x3, x1 - x3 * q, b, a - b * q);
  }
  assert(a == 1 && "inv_mod_error");
  return static_cast<T>(x1 < 0 ? x1 + mod : x1);
}

} // namespace lib::internal

namespace lib {

template <typename T1, typename T2, typename T = longer_integral_t<T1, T2>>
std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>, T> gcd(T1 a, T2 b) {
  return internal::gcd<T>(a, b);
}

template <typename T1, typename T2, typename T = longer_integral_t<T1, T2>,
          typename S = std::make_signed_t<T>>
std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>, std::tuple<T, S, S>>
exgcd(T1 a, T2 b) {
  return internal::exgcd<T, S>(a, b);
}

template <typename T1, typename T2, typename T = longer_integral_t<T1, T2>>
std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>, T> inv_mod(T1 x, T2 mod) {
  return internal::inv_mod<T>(x, mod);
}

} // namespace lib

#endif
