#ifndef SQRT_MOD_HPP
#define SQRT_MOD_HPP

#include "../common.hpp"

#include <random>
#include <type_traits>
#include <vector>

LIB_BEGIN

template <typename ModIntT>
std::vector<ModIntT> sqrt_mod_prime(ModIntT a) {
  // Bostan-Mori's algorithm
  if (a.is_zero()) return {a};
  const auto p = ModIntT::mod();
  if (a.pow(p >> 1) == -1) return {};
  if ((p & 3) == 3) {
    ModIntT b(a.pow((p + 1) >> 2));
    return {b, -b};
  }
  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<std::remove_cv_t<decltype(p)>> dis(2, p - 1);
  ModIntT t;
  do { t = dis(gen); } while ((t * t - 4 * a).pow(p >> 1) != -1);
  ModIntT k0(1), k1, k2(-t), k3(a);
  for (auto e = (p + 1) >> 1;;) {
    // clang-format off
    if (e & 1) k0 = k1 - k0 * k2, k1 *= k3;
    else k1 = k0 * k3 - k1 * k2;
    // clang-format on
    if ((e >>= 1) == 0) return {k0, -k0};
    k2 = k3 + k3 - k2 * k2, k3 *= k3;
  }
}

LIB_END

#endif