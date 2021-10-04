#ifndef BINARY_POW_HEADER_HPP
#define BINARY_POW_HEADER_HPP

/**
 * @brief binary exponentiation
 *
 */

#include <cassert>
#include <type_traits>

#include "../../traits/base.hpp"
#include "binary_mul.hpp"

namespace lib {

template <typename T1, typename T2>
std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>, T1> pow(T1 x, T2 y) {
  assert(y >= 0);
  for (T1 res = 1;; x *= x) {
    if (y & 1) res *= x;
    if ((y >>= 1) == 0) return res;
  }
}

template <typename T1, typename T2, typename T3, typename T = longer_integral_t<T1, T3>>
std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2> && std::is_integral_v<T3>, T>
pow_mod(T1 x, T2 y, T3 mod) {
  assert(y >= 0);
  for (T res = (mod != 1), tx = x;; tx = tx = mul_mod(tx, tx, mod)) {
    if (y & 1) res = mul_mod(res, tx, mod);
    if ((y >>= 1) == 0) return res;
  }
}

} // namespace lib

#endif
