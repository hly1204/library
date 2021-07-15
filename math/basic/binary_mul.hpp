#ifndef BINARY_MUL_HEADER_HPP
#define BINARY_MUL_HEADER_HPP

/**
 * @brief binary multiplication / 快速乘
 *
 */

#include <type_traits>

#include "../../traits/base.hpp"

namespace lib::internal {

template <typename T>
std::enable_if_t<std::is_integral_v<T> && sizeof(T) <= 4 && std::is_signed_v<T>, T>
mul_mod(T x, T y, T mod) {
  T res = static_cast<T>(static_cast<promote_integral_t<T>>(x) * y % mod);
  return res < 0 ? res + mod : res;
}

template <typename T>
std::enable_if_t<std::is_integral_v<T> && sizeof(T) <= 4 && std::is_unsigned_v<T>, T>
mul_mod(T x, T y, T mod) {
  return static_cast<T>(static_cast<promote_integral_t<T>>(x) * y % mod);
}

template <typename T>
std::enable_if_t<std::is_integral_v<T> && (sizeof(T) > 4) && std::is_unsigned_v<T>, T>
mul_mod(T x, T y, T mod) {
  x %= mod, y %= mod;
  T res = 0;
  for (; y != 0; y >>= 1) {
    if ((y & 1) && (res += x) >= mod) res -= mod;
    if ((x <<= 1) >= mod) x -= mod;
  }
  return res;
}

template <typename T>
std::enable_if_t<std::is_integral_v<T> && (sizeof(T) > 4) && std::is_signed_v<T>, T>
mul_mod(T x, T y, T mod) {
  if ((x %= mod) < 0) x += mod;
  if ((y %= mod) < 0) y += mod;
  T res = 0;
  for (; y != 0; y >>= 1) {
    if ((y & 1) && (res += x) >= mod) res -= mod;
    if ((x <<= 1) >= mod) x -= mod;
  }
  return res;
}

} // namespace lib::internal

namespace lib {

template <typename T1, typename T2, typename T3,
          typename T = longer_integral_t<longer_integral_t<T1, T2>, T3>>
std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2> && std::is_integral_v<T3> &&
                     (std::is_signed_v<T1> || std::is_signed_v<T2>),
                 T>
mul_mod(T1 x, T2 y, T3 mod) {
  return internal::mul_mod<std::make_signed_t<T>>(x, y, mod);
}

template <typename T1, typename T2, typename T3,
          typename T = longer_integral_t<longer_integral_t<T1, T2>, T3>>
std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2> && std::is_integral_v<T3> &&
                     std::is_unsigned_v<T1> && std::is_unsigned_v<T2>,
                 T>
mul_mod(T1 x, T2 y, T3 mod) {
  return internal::mul_mod<T>(x, y, mod);
}

} // namespace lib

#endif