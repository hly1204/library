---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: math/binomial.hpp
    title: Binomial Coefficient (in $\mathbb{F} _ p$)
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/stirling_numbers.hpp
    title: Stirling Numbers (in $\mathbb{F} _ p$ for FFT prime $p$)
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
    title: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
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
  bundledCode: "#line 1 \"math/taylor_shift.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\
    \n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n\
    #define LIB ::lib::\n\n\n#line 1 \"math/binomial.hpp\"\n\n\n\n#line 5 \"math/binomial.hpp\"\
    \n\n#include <vector>\n\nLIB_BEGIN\n\n// helper class for precomputation of factorials\
    \ and multiplicative inverse of them.\ntemplate <typename ModIntT>\nclass binomial\
    \ {\n  mutable std::vector<ModIntT> factorial_{ModIntT(1)}, invfactorial_{ModIntT(1)};\n\
    \npublic:\n  explicit binomial(int n) { preprocess(n); }\n  binomial() {}\n  void\
    \ preprocess(int n) const {\n    if (int nn = static_cast<int>(factorial_.size());\
    \ nn <= n) {\n      int k = nn;\n      while (k <= n) k <<= 1;\n      factorial_.resize(k);\n\
    \      invfactorial_.resize(k);\n      for (int i = nn; i != k; ++i) factorial_[i]\
    \ = factorial_[i - 1] * i;\n      invfactorial_.back() = factorial_.back().inv();\n\
    \      for (int i = k - 2; i >= nn; --i) invfactorial_[i] = invfactorial_[i +\
    \ 1] * (i + 1);\n    }\n  }\n  // binomial coefficient `n`C`m`\n  ModIntT binom(int\
    \ n, int m) const {\n    return n < m ? ModIntT()\n                 : (preprocess(n),\
    \ factorial_[n] * invfactorial_[m] * invfactorial_[n - m]);\n  }\n  ModIntT inv(int\
    \ n) const { return preprocess(n), factorial_[n - 1] * invfactorial_[n]; }\n \
    \ ModIntT factorial(int n) const { return preprocess(n), factorial_[n]; }\n  ModIntT\
    \ inv_factorial(int n) const { return preprocess(n), invfactorial_[n]; }\n};\n\
    \nLIB_END\n\n\n#line 6 \"math/taylor_shift.hpp\"\n\n#include <algorithm>\n\nLIB_BEGIN\n\
    \ntemplate <typename PolyT>\nPolyT taylor_shift(const PolyT &a, typename PolyT::value_type\
    \ c) {\n  using T     = typename PolyT::value_type;\n  const int n = static_cast<int>(a.size());\n\
    \  binomial<T> b(n);\n  PolyT rev_a_cpy(n), pc(n);\n  for (int i = 0; i != n;\
    \ ++i) rev_a_cpy[n - 1 - i] = a[i] * b.factorial(i);\n  T cc(1);\n  for (int i\
    \ = 0; i != n; ++i) pc[i] = cc * b.inv_factorial(i), cc *= c;\n  (rev_a_cpy *=\
    \ pc).resize(n);\n  std::reverse(rev_a_cpy.begin(), rev_a_cpy.end());\n  for (int\
    \ i = 0; i != n; ++i) rev_a_cpy[i] *= b.inv_factorial(i);\n  return rev_a_cpy;\n\
    }\n\nLIB_END\n\n\n"
  code: "#ifndef TAYLOR_SHIFT_HPP\n#define TAYLOR_SHIFT_HPP\n\n#include \"../common.hpp\"\
    \n#include \"binomial.hpp\"\n\n#include <algorithm>\n\nLIB_BEGIN\n\ntemplate <typename\
    \ PolyT>\nPolyT taylor_shift(const PolyT &a, typename PolyT::value_type c) {\n\
    \  using T     = typename PolyT::value_type;\n  const int n = static_cast<int>(a.size());\n\
    \  binomial<T> b(n);\n  PolyT rev_a_cpy(n), pc(n);\n  for (int i = 0; i != n;\
    \ ++i) rev_a_cpy[n - 1 - i] = a[i] * b.factorial(i);\n  T cc(1);\n  for (int i\
    \ = 0; i != n; ++i) pc[i] = cc * b.inv_factorial(i), cc *= c;\n  (rev_a_cpy *=\
    \ pc).resize(n);\n  std::reverse(rev_a_cpy.begin(), rev_a_cpy.end());\n  for (int\
    \ i = 0; i != n; ++i) rev_a_cpy[i] *= b.inv_factorial(i);\n  return rev_a_cpy;\n\
    }\n\nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  - math/binomial.hpp
  isVerificationFile: false
  path: math/taylor_shift.hpp
  requiredBy:
  - math/stirling_numbers.hpp
  timestamp: '2022-05-05 22:58:57+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  - remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
documentation_of: math/taylor_shift.hpp
layout: document
title: Polynomial Taylor Shift (in $\mathbb{F} _ p$ for FFT prime $p$)
---
