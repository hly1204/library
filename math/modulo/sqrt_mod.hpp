#ifndef SQRT_MOD_HEADER_HPP
#define SQRT_MOD_HEADER_HPP

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
  std::uniform_int_distribution<decltype(p)> dis(2, p - 1);

  const mod_t four(mod_t(4) * x);
  mod_t t, w2;
  do {
    t = mod_t(dis(gen)), w2 = t * t - four;
    if (w2 == ZERO) {
      t /= 2;
      return {t, -t};
    }
  } while (w2.pow(p >> 1) != MINUS_ONE);

  mod_t k0(ONE), k1(ZERO), k2(-t), k3(x);

  for (auto e = (p + 1) >> 1;;) {
    if (e & 1) {
      k0 = k1 - k0 * k2, k1 *= k3;
    } else {
      k1 = k0 * k3 - k1 * k2;
    }
    if ((e >>= 1) == 0) return {k0, -k0};
    k2 = k3 + k3 - k2 * k2, k3 *= k3;
  }
}

} // namespace lib::internal

namespace lib {

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