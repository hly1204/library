---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: math/random.hpp
    title: Pseudo Random Number Generator
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/polynomial.hpp
    title: Polynomial (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  - icon: ':heavy_check_mark:'
    path: math/truncated_formal_power_series.hpp
    title: Truncated Formal Power Series (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack
      \rbrack$ for FFT prime $p$)
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.1.test.cpp
    title: remote_test/yosupo/math/convolution_mod.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
    title: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
    title: remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
    title: remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
    title: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
    title: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
    title: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/sqrt_mod.0.test.cpp
    title: remote_test/yosupo/math/sqrt_mod.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
    title: remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
    title: remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/sqrt_mod.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\n\n\
    #define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n#define\
    \ LIB ::lib::\n\n\n#line 1 \"math/random.hpp\"\n\n\n\n#line 5 \"math/random.hpp\"\
    \n\n#include <cstdint>\n#include <limits>\n\nLIB_BEGIN\n\n// see https://prng.di.unimi.it/xoshiro256starstar.c\n\
    // original license CC0 1.0\nclass xoshiro256starstar {\n  using u64 = std::uint64_t;\n\
    \n  static inline u64 rotl(const u64 x, int k) { return (x << k) | (x >> (64 -\
    \ k)); }\n\n  u64 s_[4];\n\n  u64 next() {\n    const u64 res = rotl(s_[1] * 5,\
    \ 7) * 9;\n    const u64 t   = s_[1] << 17;\n    s_[2] ^= s_[0], s_[3] ^= s_[1],\
    \ s_[1] ^= s_[2], s_[0] ^= s_[3], s_[2] ^= t,\n        s_[3] = rotl(s_[3], 45);\n\
    \    return res;\n  }\n\npublic:\n  // see https://prng.di.unimi.it/splitmix64.c\n\
    \  // original license CC0 1.0\n  explicit xoshiro256starstar(u64 seed) {\n  \
    \  for (int i = 0; i != 4; ++i) {\n      u64 z = (seed += 0x9e3779b97f4a7c15);\n\
    \      z     = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n      z     = (z ^ (z >>\
    \ 27)) * 0x94d049bb133111eb;\n      s_[i] = z ^ (z >> 31);\n    }\n  }\n  // see\
    \ https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator\n  using\
    \ result_type = u64;\n  static constexpr u64 min() { return std::numeric_limits<u64>::min();\
    \ }\n  static constexpr u64 max() { return std::numeric_limits<u64>::max(); }\n\
    \  u64 operator()() { return next(); }\n};\n\nLIB_END\n\n\n#line 6 \"math/sqrt_mod.hpp\"\
    \n\n#include <random>\n#include <type_traits>\n#include <vector>\n\nLIB_BEGIN\n\
    \ntemplate <typename ModIntT>\nstd::vector<ModIntT> sqrt_mod_prime(ModIntT a)\
    \ {\n  // Bostan--Mori's algorithm\n  const auto p = ModIntT::mod();\n  if (p\
    \ == 2 || a.is_zero()) return {a};\n  if (a.pow(p >> 1) == -1) return {};\n  if\
    \ ((p & 3) == 3) {\n    ModIntT b(a.pow((p + 1) >> 2));\n    return {b, -b};\n\
    \  }\n  xoshiro256starstar gen(std::random_device{}());\n  std::uniform_int_distribution<std::decay_t<decltype(p)>>\
    \ dis(2, p - 1);\n  ModIntT t;\n  do { t = dis(gen); } while ((t * t - 4 * a).pow(p\
    \ >> 1) != -1);\n  ModIntT k0(1), k1, k2(-t), k3(a);\n  for (auto e = (p + 1)\
    \ >> 1;;) {\n    // clang-format off\n    if (e & 1) k0 = k1 - k0 * k2, k1 *=\
    \ k3;\n    else k1 = k0 * k3 - k1 * k2;\n    // clang-format on\n    if ((e >>=\
    \ 1) == 0) return {k0, -k0};\n    k2 = k3 + k3 - k2 * k2, k3 *= k3;\n  }\n}\n\n\
    LIB_END\n\n\n"
  code: "#ifndef SQRT_MOD_HPP\n#define SQRT_MOD_HPP\n\n#include \"../common.hpp\"\n\
    #include \"random.hpp\"\n\n#include <random>\n#include <type_traits>\n#include\
    \ <vector>\n\nLIB_BEGIN\n\ntemplate <typename ModIntT>\nstd::vector<ModIntT> sqrt_mod_prime(ModIntT\
    \ a) {\n  // Bostan--Mori's algorithm\n  const auto p = ModIntT::mod();\n  if\
    \ (p == 2 || a.is_zero()) return {a};\n  if (a.pow(p >> 1) == -1) return {};\n\
    \  if ((p & 3) == 3) {\n    ModIntT b(a.pow((p + 1) >> 2));\n    return {b, -b};\n\
    \  }\n  xoshiro256starstar gen(std::random_device{}());\n  std::uniform_int_distribution<std::decay_t<decltype(p)>>\
    \ dis(2, p - 1);\n  ModIntT t;\n  do { t = dis(gen); } while ((t * t - 4 * a).pow(p\
    \ >> 1) != -1);\n  ModIntT k0(1), k1, k2(-t), k3(a);\n  for (auto e = (p + 1)\
    \ >> 1;;) {\n    // clang-format off\n    if (e & 1) k0 = k1 - k0 * k2, k1 *=\
    \ k3;\n    else k1 = k0 * k3 - k1 * k2;\n    // clang-format on\n    if ((e >>=\
    \ 1) == 0) return {k0, -k0};\n    k2 = k3 + k3 - k2 * k2, k3 *= k3;\n  }\n}\n\n\
    LIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  - math/random.hpp
  isVerificationFile: false
  path: math/sqrt_mod.hpp
  requiredBy:
  - math/polynomial.hpp
  - math/truncated_formal_power_series.hpp
  timestamp: '2022-06-22 23:05:33+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
  - remote_test/yosupo/math/sqrt_mod.0.test.cpp
  - remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/convolution_mod.1.test.cpp
  - remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
  - remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  - remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
documentation_of: math/sqrt_mod.hpp
layout: document
title: Square Roots (in $\mathbb{F} _ p$)
---

## A Simple and Fast Algorithm

I think this algorithm is identical to Bostan--Mori's algorithm. I omit the details here.

## Bibliography

1. A. Menezes, P. van Oorschot, and S. Vanstone. [Handbook of Applied Cryptography](http://cacr.uwaterloo.ca/hac/), 1996.
2. A. Bostan, and R. Mori. [A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence](https://arxiv.org/abs/2008.08822v1), 2020.
