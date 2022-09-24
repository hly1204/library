---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/integer_factorization.hpp
    title: Integer Factorization (Pollard's rho algorithm) (in $\mathbb{Z}$)
  - icon: ':question:'
    path: math/polynomial.hpp
    title: Polynomial (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  - icon: ':question:'
    path: math/sqrt_mod.hpp
    title: Square Roots (in $\mathbb{F} _ p$)
  - icon: ':question:'
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
    path: remote_test/yosupo/math/factorize.0.test.cpp
    title: remote_test/yosupo/math/factorize.0.test.cpp
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
  - icon: ':x:'
    path: remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
    title: remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
    title: remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links:
    - https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator
    - https://prng.di.unimi.it/splitmix64.c
    - https://prng.di.unimi.it/xoshiro256starstar.c
  bundledCode: "#line 1 \"math/random.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\n\n\
    #define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n#define\
    \ LIB ::lib::\n\n\n#line 5 \"math/random.hpp\"\n\n#include <cstdint>\n#include\
    \ <limits>\n\nLIB_BEGIN\n\n// see https://prng.di.unimi.it/xoshiro256starstar.c\n\
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
    \  u64 operator()() { return next(); }\n};\n\nLIB_END\n\n\n"
  code: "#ifndef RADOM_HPP\n#define RADOM_HPP\n\n#include \"../common.hpp\"\n\n#include\
    \ <cstdint>\n#include <limits>\n\nLIB_BEGIN\n\n// see https://prng.di.unimi.it/xoshiro256starstar.c\n\
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
    \  u64 operator()() { return next(); }\n};\n\nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: math/random.hpp
  requiredBy:
  - math/integer_factorization.hpp
  - math/sqrt_mod.hpp
  - math/polynomial.hpp
  - math/truncated_formal_power_series.hpp
  timestamp: '2022-05-27 06:01:13+00:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - remote_test/yosupo/math/factorize.0.test.cpp
  - remote_test/yosupo/math/sqrt_mod.0.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
  - remote_test/yosupo/math/convolution_mod.1.test.cpp
  - remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  - remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
documentation_of: math/random.hpp
layout: document
title: Pseudo Random Number Generator
---
