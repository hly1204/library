---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/binomial_convolution.hpp
    title: Binomial Convolution (in $\mathbb{Z} / m \mathbb{Z}$)
  - icon: ':heavy_check_mark:'
    path: math/cra.hpp
    title: Chinese Remainder Algorithm (in $\mathbb{Z} / m \mathbb{Z}$)
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series.hpp
    title: Formal Power Series (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack \rbrack$
      for FFT prime $p$)
  - icon: ':question:'
    path: math/polynomial.hpp
    title: Polynomial (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  - icon: ':question:'
    path: math/truncated_formal_power_series.hpp
    title: Truncated Formal Power Series (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack
      \rbrack$ for FFT prime $p$)
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/aizu/number_theory/extended_euclidean_algorithm.0.test.cpp
    title: remote_test/aizu/number_theory/extended_euclidean_algorithm.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.1.test.cpp
    title: remote_test/yosupo/math/convolution_mod.1.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
    title: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/exp_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/exp_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
    title: remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
    title: remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
    title: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/partition_function.0.test.cpp
    title: remote_test/yosupo/math/partition_function.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
    title: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
    title: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp
    title: remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/pow_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/pow_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/sharp_p_subset_sum.0.test.cpp
    title: remote_test/yosupo/math/sharp_p_subset_sum.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
    title: remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
    title: remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yuki/math/187.0.test.cpp
    title: remote_test/yuki/math/187.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/extended_gcd.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\
    \n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n\
    #define LIB ::lib::\n\n\n#line 5 \"math/extended_gcd.hpp\"\n\n#include <tuple>\n\
    #include <utility>\n#include <vector>\n\nLIB_BEGIN\n\n// Input:  integer `a` and\
    \ `b`.\n// Output: (x, y, z) such that `a`x + `b`y = z = gcd(`a`, `b`).\n[[deprecated]]\
    \ std::tuple<long long, long long, long long> ext_gcd(long long a, long long b)\
    \ {\n  long long x11 = 1, x12 = 0, x21 = 0, x22 = 1;\n  while (b != 0) {\n   \
    \ long long q = a / b, x11_cpy = x11, x12_cpy = x12, a_cpy = a;\n    x11 = x21,\
    \ x21 = x11_cpy - q * x21;\n    x12 = x22, x22 = x12_cpy - q * x22;\n    a = b,\
    \ b = a_cpy - q * b;\n  }\n  return std::make_tuple(x11, x12, a);\n}\n\n// Input:\
    \  integer `a` and `b`.\n// Output: (x, gcd(`a`, `b`)) such that `a`x \u2261 gcd(`a`,\
    \ `b`) (mod `b`).\nstd::pair<long long, long long> inv_gcd(long long a, long long\
    \ b) {\n  long long x11 = 1, x21 = 0;\n  while (b != 0) {\n    long long q = a\
    \ / b, x11_cpy = x11, a_cpy = a;\n    x11 = x21, x21 = x11_cpy - q * x21;\n  \
    \  a = b, b = a_cpy - q * b;\n  }\n  return std::make_pair(x11, a);\n}\n\nnamespace\
    \ detail {\n\ntemplate <typename ModIntT>\nclass modular_inverse {\n  std::vector<ModIntT>\
    \ ivs{ModIntT()};\n\n  enum : int { LIM = 1 << 20 };\n\npublic:\n  modular_inverse()\
    \ {}\n  ModIntT operator()(int k) {\n    // assume `ModIntT::mod()` is prime.\n\
    \    if (k > LIM) return ModIntT(k).inv();\n    // preprocess modular inverse\
    \ from 1 to `k`\n    if (int n = static_cast<int>(ivs.size()); n <= k) {\n   \
    \   int nn = n;\n      while (nn <= k) nn <<= 1;\n      ivs.resize(nn);\n    \
    \  ModIntT v(1);\n      for (int i = n; i != nn; ++i) ivs[i] = v, v *= ModIntT(i);\n\
    \      v = v.inv();\n      for (int i = nn - 1; i >= n; --i) ivs[i] *= v, v *=\
    \ ModIntT(i);\n    }\n    return ivs[k];\n  }\n};\n\n} // namespace detail\n\n\
    LIB_END\n\n\n"
  code: "#ifndef EXTENDED_GCD_HPP\n#define EXTENDED_GCD_HPP\n\n#include \"../common.hpp\"\
    \n\n#include <tuple>\n#include <utility>\n#include <vector>\n\nLIB_BEGIN\n\n//\
    \ Input:  integer `a` and `b`.\n// Output: (x, y, z) such that `a`x + `b`y = z\
    \ = gcd(`a`, `b`).\n[[deprecated]] std::tuple<long long, long long, long long>\
    \ ext_gcd(long long a, long long b) {\n  long long x11 = 1, x12 = 0, x21 = 0,\
    \ x22 = 1;\n  while (b != 0) {\n    long long q = a / b, x11_cpy = x11, x12_cpy\
    \ = x12, a_cpy = a;\n    x11 = x21, x21 = x11_cpy - q * x21;\n    x12 = x22, x22\
    \ = x12_cpy - q * x22;\n    a = b, b = a_cpy - q * b;\n  }\n  return std::make_tuple(x11,\
    \ x12, a);\n}\n\n// Input:  integer `a` and `b`.\n// Output: (x, gcd(`a`, `b`))\
    \ such that `a`x \u2261 gcd(`a`, `b`) (mod `b`).\nstd::pair<long long, long long>\
    \ inv_gcd(long long a, long long b) {\n  long long x11 = 1, x21 = 0;\n  while\
    \ (b != 0) {\n    long long q = a / b, x11_cpy = x11, a_cpy = a;\n    x11 = x21,\
    \ x21 = x11_cpy - q * x21;\n    a = b, b = a_cpy - q * b;\n  }\n  return std::make_pair(x11,\
    \ a);\n}\n\nnamespace detail {\n\ntemplate <typename ModIntT>\nclass modular_inverse\
    \ {\n  std::vector<ModIntT> ivs{ModIntT()};\n\n  enum : int { LIM = 1 << 20 };\n\
    \npublic:\n  modular_inverse() {}\n  ModIntT operator()(int k) {\n    // assume\
    \ `ModIntT::mod()` is prime.\n    if (k > LIM) return ModIntT(k).inv();\n    //\
    \ preprocess modular inverse from 1 to `k`\n    if (int n = static_cast<int>(ivs.size());\
    \ n <= k) {\n      int nn = n;\n      while (nn <= k) nn <<= 1;\n      ivs.resize(nn);\n\
    \      ModIntT v(1);\n      for (int i = n; i != nn; ++i) ivs[i] = v, v *= ModIntT(i);\n\
    \      v = v.inv();\n      for (int i = nn - 1; i >= n; --i) ivs[i] *= v, v *=\
    \ ModIntT(i);\n    }\n    return ivs[k];\n  }\n};\n\n} // namespace detail\n\n\
    LIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: math/extended_gcd.hpp
  requiredBy:
  - math/formal_power_series.hpp
  - math/binomial_convolution.hpp
  - math/cra.hpp
  - math/truncated_formal_power_series.hpp
  - math/polynomial.hpp
  timestamp: '2022-04-25 23:36:30+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - remote_test/yuki/math/187.0.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
  - remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  - remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
  - remote_test/yosupo/math/exp_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/pow_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/sharp_p_subset_sum.0.test.cpp
  - remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp
  - remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/convolution_mod.1.test.cpp
  - remote_test/yosupo/math/partition_function.0.test.cpp
  - remote_test/aizu/number_theory/extended_euclidean_algorithm.0.test.cpp
documentation_of: math/extended_gcd.hpp
layout: document
title: Extended Euclidean Algorithm (in $\mathbb{Z}$)
---
