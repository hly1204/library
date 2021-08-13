#ifndef SQRT_MOD_HEADER_HPP
#define SQRT_MOD_HEADER_HPP

/**
 * @brief square root mod
 * @docs docs/math/modulo/sqrt_mod.md
 */

#include <cassert>
#include <random>
#include <tuple>
#include <type_traits>
#include <vector>

#include "../../modint/runtime_Montgomery_modint.hpp"
#include "../../modint/runtime_long_Montgomery_modint.hpp"

namespace lib::internal {

template <typename mod_t>
std::vector<mod_t> sqrt_mod_prime(const mod_t x) {
  const auto p = mod_t::get_mod();
  const mod_t ONE(1), MINUS_ONE(-ONE), ZERO(0);
  if (x == ZERO) return {ZERO};
  if (x.pow(p >> 1) == MINUS_ONE) return {};
  if ((p & 3) == 3) {
    mod_t res = x.pow((p + 1) >> 2);
    return {res, -res};
  }

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<std::uint32_t> dis(2, p - 1);

  const mod_t four(mod_t(4) * x);
  mod_t t, w2;
  do {
    t = mod_t(dis(gen)), w2 = t * t - four;
    if (w2 == ZERO) { // 足够幸运时
      t /= 2;
      return {t, -t};
    }
  } while (w2.pow(p >> 1) != MINUS_ONE);

  mod_t a(ONE), b(ZERO), c(ZERO), d(ONE);

  for (auto e = (p + 1) >> 1; e != 0; e >>= 1) {
    if (e & 1) {
      mod_t bd       = b * d;
      std::tie(a, b) = std::make_pair(a * c - bd * x, a * d + b * c + bd * t);
    }
    mod_t dd = d * d, cd = c * d;
    std::tie(c, d) = std::make_pair(c * c - dd * x, cd + cd + dd * t);
  }

  return {a, -a};
}

} // namespace lib::internal

namespace lib {

/**
 * @brief 模平方根
 * @param x [0, p-1] 中的一个值
 * @param p 素数
 * @return std::vector<T>
 */
template <typename T>
std::enable_if_t<std::is_integral_v<T>, std::vector<T>> sqrt_mod_prime(T x, T p) {
  using m32 = RuntimeMontModInt<-1>;
  using m64 = RuntimeLongMontModInt<-1>;
  if (p == 2 || x == 0) return {x};
  if (p < (3U << 30)) {
    bool okay = m32::set_mod(p);
    assert(okay);
    auto res = internal::sqrt_mod_prime(m32(x));
    return std::vector<T>(res.begin(), res.end());
  }
  bool okay = m64::set_mod(p);
  assert(okay);
  auto res = internal::sqrt_mod_prime(m64(x));
  return std::vector<T>(res.begin(), res.end());
}

} // namespace lib

#endif