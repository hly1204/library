---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: math/binomial.hpp
    title: Binomial Coefficient (in $\mathbb{F} _ p$)
  - icon: ':heavy_check_mark:'
    path: math/linear_sieve.hpp
    title: Linear Sieve
  - icon: ':heavy_check_mark:'
    path: math/taylor_shift.hpp
    title: Polynomial Taylor Shift (in $\mathbb{F} _ p$ for FFT prime $p$)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
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
  bundledCode: "#line 1 \"math/stirling_numbers.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
    \n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 1 \"math/binomial.hpp\"\n\n\n\n#line 5 \"\
    math/binomial.hpp\"\n\n#include <vector>\n\nLIB_BEGIN\n\n// helper class for precomputation\
    \ of factorials and multiplicative inverse of them.\ntemplate <typename ModIntT>\n\
    class binomial {\n  mutable std::vector<ModIntT> factorial_{ModIntT(1)}, invfactorial_{ModIntT(1)};\n\
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
    \nLIB_END\n\n\n#line 1 \"math/linear_sieve.hpp\"\n\n\n\n#line 5 \"math/linear_sieve.hpp\"\
    \n\n#line 7 \"math/linear_sieve.hpp\"\n\nLIB_BEGIN\n\n// Output: primes in [0,\
    \ `n`) (sorted).\nstd::vector<int> prime_table(int n) {\n  std::vector<bool> is_comp(n,\
    \ false);\n  std::vector<int> res;\n  for (int i = 2; i < n; ++i) {\n    if (!is_comp[i])\
    \ res.push_back(i);\n    for (int j = 0, je = res.size(); j < je && i * res[j]\
    \ < n; ++j) {\n      is_comp[i * res[j]] = true;\n      if (i % res[j] == 0) break;\n\
    \    }\n  }\n  return res;\n}\n\ntemplate <typename ModIntT>\nstd::vector<ModIntT>\
    \ pow_table(int e, int n) {\n  std::vector<bool> is_comp(n, false);\n  std::vector<int>\
    \ p;\n  std::vector<ModIntT> res(n);\n  if (n >= 1) {\n    res.front() = (e ==\
    \ 0 ? ModIntT(1) : ModIntT()); // 0^0 = 1\n    if (n >= 2) res[1] = ModIntT(1);\n\
    \  }\n  for (int i = 2; i < n; ++i) {\n    if (!is_comp[i]) {\n      p.push_back(i);\n\
    \      res[i] = ModIntT(i).pow(e);\n    }\n    for (int j = 0, je = static_cast<int>(p.size());\
    \ j < je && i * p[j] < n; ++j) {\n      is_comp[i * p[j]] = true;\n      res[i\
    \ * p[j]]     = res[i] * res[p[j]];\n      if (i % p[j] == 0) break;\n    }\n\
    \  }\n  return res;\n}\n\nLIB_END\n\n\n#line 1 \"math/taylor_shift.hpp\"\n\n\n\
    \n#line 6 \"math/taylor_shift.hpp\"\n\n#include <algorithm>\n\nLIB_BEGIN\n\ntemplate\
    \ <typename PolyT>\nPolyT taylor_shift(const PolyT &a, typename PolyT::value_type\
    \ c) {\n  using T     = typename PolyT::value_type;\n  const int n = static_cast<int>(a.size());\n\
    \  binomial<T> b(n);\n  PolyT rev_a_cpy(n), pc(n);\n  for (int i = 0; i != n;\
    \ ++i) rev_a_cpy[n - 1 - i] = a[i] * b.factorial(i);\n  T cc(1);\n  for (int i\
    \ = 0; i != n; ++i) pc[i] = cc * b.inv_factorial(i), cc *= c;\n  (rev_a_cpy *=\
    \ pc).resize(n);\n  std::reverse(rev_a_cpy.begin(), rev_a_cpy.end());\n  for (int\
    \ i = 0; i != n; ++i) rev_a_cpy[i] *= b.inv_factorial(i);\n  return rev_a_cpy;\n\
    }\n\nLIB_END\n\n\n#line 8 \"math/stirling_numbers.hpp\"\n\nLIB_BEGIN\n\n// unsigned\
    \ Stirling numbers of the first kind.\ntemplate <typename PolyT>\nPolyT stirling1st_row(int\
    \ n) {\n  using T = typename PolyT::value_type;\n  if (n == 0) return {T(1)};\n\
    \  int mask = 1 << 30;\n  while ((mask & n) == 0) mask >>= 1;\n  PolyT res{T(0),\
    \ T(1)};\n  for (int d = 1; d != n;) {\n    res *= taylor_shift(res, T(d)), d\
    \ <<= 1;\n    if ((mask >>= 1) & n) res *= PolyT{T(d), 1}, ++d;\n  }\n  return\
    \ res;\n}\n\ntemplate <typename PolyT>\nPolyT stirling2nd_row(int n) {\n  using\
    \ T = typename PolyT::value_type;\n  if (n == 0) return {T(1)};\n  PolyT res(n\
    \ + 1), rhs(n + 1);\n  binomial<T> bi(n);\n  const auto pt = pow_table<T>(n, n\
    \ + 1);\n  for (int i = 0; i <= n; ++i) {\n    rhs[i] = pt[i] * (res[i] = bi.inv_factorial(i));\n\
    \    if (i & 1) res[i] = -res[i];\n  }\n  (res *= rhs).resize(n + 1);\n  return\
    \ res;\n}\n\nLIB_END\n\n\n"
  code: "#ifndef STIRLING_NUMBERS_HPP\n#define STIRLING_NUMBERS_HPP\n\n#include \"\
    ../common.hpp\"\n#include \"binomial.hpp\"\n#include \"linear_sieve.hpp\"\n#include\
    \ \"taylor_shift.hpp\"\n\nLIB_BEGIN\n\n// unsigned Stirling numbers of the first\
    \ kind.\ntemplate <typename PolyT>\nPolyT stirling1st_row(int n) {\n  using T\
    \ = typename PolyT::value_type;\n  if (n == 0) return {T(1)};\n  int mask = 1\
    \ << 30;\n  while ((mask & n) == 0) mask >>= 1;\n  PolyT res{T(0), T(1)};\n  for\
    \ (int d = 1; d != n;) {\n    res *= taylor_shift(res, T(d)), d <<= 1;\n    if\
    \ ((mask >>= 1) & n) res *= PolyT{T(d), 1}, ++d;\n  }\n  return res;\n}\n\ntemplate\
    \ <typename PolyT>\nPolyT stirling2nd_row(int n) {\n  using T = typename PolyT::value_type;\n\
    \  if (n == 0) return {T(1)};\n  PolyT res(n + 1), rhs(n + 1);\n  binomial<T>\
    \ bi(n);\n  const auto pt = pow_table<T>(n, n + 1);\n  for (int i = 0; i <= n;\
    \ ++i) {\n    rhs[i] = pt[i] * (res[i] = bi.inv_factorial(i));\n    if (i & 1)\
    \ res[i] = -res[i];\n  }\n  (res *= rhs).resize(n + 1);\n  return res;\n}\n\n\
    LIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  - math/binomial.hpp
  - math/linear_sieve.hpp
  - math/taylor_shift.hpp
  isVerificationFile: false
  path: math/stirling_numbers.hpp
  requiredBy: []
  timestamp: '2022-06-03 11:52:48+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  - remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
documentation_of: math/stirling_numbers.hpp
layout: document
title: Stirling Numbers (in $\mathbb{F} _ p$ for FFT prime $p$)
---
