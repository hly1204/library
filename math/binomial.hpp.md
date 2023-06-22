---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/stirling_numbers.hpp
    title: Stirling Numbers (in $\mathbb{F} _ p$ for FFT prime $p$)
  - icon: ':question:'
    path: math/taylor_shift.hpp
    title: Polynomial Taylor Shift (in $\mathbb{F} _ p$ for FFT prime $p$)
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
    title: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
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
    links: []
  bundledCode: "#line 1 \"math/binomial.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\n\n\
    #define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n#define\
    \ LIB ::lib::\n\n\n#line 5 \"math/binomial.hpp\"\n\n#include <vector>\n\nLIB_BEGIN\n\
    \n// helper class for precomputation of factorials and multiplicative inverse\
    \ of them.\ntemplate <typename ModIntT>\nclass binomial {\n  mutable std::vector<ModIntT>\
    \ factorial_{ModIntT(1)}, invfactorial_{ModIntT(1)};\n\npublic:\n  explicit binomial(int\
    \ n) { preprocess(n); }\n  binomial() {}\n  void preprocess(int n) const {\n \
    \   if (int nn = static_cast<int>(factorial_.size()); nn <= n) {\n      int k\
    \ = nn;\n      while (k <= n) k <<= 1;\n      factorial_.resize(k);\n      invfactorial_.resize(k);\n\
    \      for (int i = nn; i != k; ++i) factorial_[i] = factorial_[i - 1] * i;\n\
    \      invfactorial_.back() = factorial_.back().inv();\n      for (int i = k -\
    \ 2; i >= nn; --i) invfactorial_[i] = invfactorial_[i + 1] * (i + 1);\n    }\n\
    \  }\n  // binomial coefficient `n`C`m`\n  ModIntT binom(int n, int m) const {\n\
    \    return n < m ? ModIntT()\n                 : (preprocess(n), factorial_[n]\
    \ * invfactorial_[m] * invfactorial_[n - m]);\n  }\n  ModIntT inv(int n) const\
    \ { return preprocess(n), factorial_[n - 1] * invfactorial_[n]; }\n  ModIntT factorial(int\
    \ n) const { return preprocess(n), factorial_[n]; }\n  ModIntT inv_factorial(int\
    \ n) const { return preprocess(n), invfactorial_[n]; }\n};\n\nLIB_END\n\n\n"
  code: "#ifndef BINOMIAL_HPP\n#define BINOMIAL_HPP\n\n#include \"../common.hpp\"\n\
    \n#include <vector>\n\nLIB_BEGIN\n\n// helper class for precomputation of factorials\
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
    \nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: math/binomial.hpp
  requiredBy:
  - math/stirling_numbers.hpp
  - math/taylor_shift.hpp
  timestamp: '2022-05-05 22:58:57+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  - remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
documentation_of: math/binomial.hpp
layout: document
title: Binomial Coefficient (in $\mathbb{F} _ p$)
---
