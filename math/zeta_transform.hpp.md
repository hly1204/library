---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/set_power_series.hpp
    title: Set Power Series
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/subset_convolution.0.test.cpp
    title: remote_test/yosupo/math/subset_convolution.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/zeta_transform.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\
    \n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 5 \"math/zeta_transform.hpp\"\n\n#include\
    \ <cassert>\n#include <vector>\n\n#ifdef _MSC_VER\n  #include <intrin.h>\n#endif\n\
    \nLIB_BEGIN\n\nint popcount(unsigned int c) {\n#ifdef _MSC_VER\n  return __popcnt(c);\n\
    #else\n  return __builtin_popcount(c);\n#endif\n}\n\nint popcount(unsigned long\
    \ c) {\n#ifdef _MSC_VER\n  return sizeof(unsigned long) == 8 ? __popcnt64(c) :\
    \ __popcnt(c);\n#else\n  return __builtin_popcountl(c);\n#endif\n}\n\nint popcount(unsigned\
    \ long long c) {\n#ifdef _MSC_VER\n  return __popcnt64(c);\n#else\n  return __builtin_popcountll(c);\n\
    #endif\n}\n\n// Input:           f(x) = `a[0]` + `a[1]`x_1 + ... + `a[n - 1]`x_1...x_n.\n\
    // Output(inplace): [f mod (x_1,...,x_n), f mod (x_1-1,x_2,...,x_n), ..., f mod\
    \ (x_1-1,...,x_n-1)].\ntemplate <typename ModIntT>\nvoid zeta_transform(std::vector<ModIntT>\
    \ &x) {\n  const int n = static_cast<int>(x.size());\n  assert((n & (n - 1)) ==\
    \ 0);\n  // assume a + b = b + a\n  for (int i = 1; i < n; i <<= 1)\n    for (int\
    \ j = i; j < n; j = (j + 1) | i) x[j] += x[j ^ i];\n}\n\n// Input:           [f\
    \ mod (x_1,...,x_n), f mod (x_1-1,x_2,...,x_n), ..., f mod (x_1-1,...,x_n-1)].\n\
    // Output(inplace): f(x) = `a[0]` + `a[1]`x_1 + ... + `a[n - 1]`x_1...x_n.\ntemplate\
    \ <typename ModIntT>\nvoid moebius_transform(std::vector<ModIntT> &x) {\n  const\
    \ int n = static_cast<int>(x.size());\n  assert((n & (n - 1)) == 0);\n  // assume\
    \ a + b = b + a\n  for (int i = n >> 1; i != 0; i >>= 1)\n    for (int j = i;\
    \ j < n; j = (j + 1) | i) x[j] -= x[j ^ i];\n}\n\nLIB_END\n\n\n"
  code: "#ifndef ZETA_TRANSFORM_HPP\n#define ZETA_TRANSFORM_HPP\n\n#include \"../common.hpp\"\
    \n\n#include <cassert>\n#include <vector>\n\n#ifdef _MSC_VER\n  #include <intrin.h>\n\
    #endif\n\nLIB_BEGIN\n\nint popcount(unsigned int c) {\n#ifdef _MSC_VER\n  return\
    \ __popcnt(c);\n#else\n  return __builtin_popcount(c);\n#endif\n}\n\nint popcount(unsigned\
    \ long c) {\n#ifdef _MSC_VER\n  return sizeof(unsigned long) == 8 ? __popcnt64(c)\
    \ : __popcnt(c);\n#else\n  return __builtin_popcountl(c);\n#endif\n}\n\nint popcount(unsigned\
    \ long long c) {\n#ifdef _MSC_VER\n  return __popcnt64(c);\n#else\n  return __builtin_popcountll(c);\n\
    #endif\n}\n\n// Input:           f(x) = `a[0]` + `a[1]`x_1 + ... + `a[n - 1]`x_1...x_n.\n\
    // Output(inplace): [f mod (x_1,...,x_n), f mod (x_1-1,x_2,...,x_n), ..., f mod\
    \ (x_1-1,...,x_n-1)].\ntemplate <typename ModIntT>\nvoid zeta_transform(std::vector<ModIntT>\
    \ &x) {\n  const int n = static_cast<int>(x.size());\n  assert((n & (n - 1)) ==\
    \ 0);\n  // assume a + b = b + a\n  for (int i = 1; i < n; i <<= 1)\n    for (int\
    \ j = i; j < n; j = (j + 1) | i) x[j] += x[j ^ i];\n}\n\n// Input:           [f\
    \ mod (x_1,...,x_n), f mod (x_1-1,x_2,...,x_n), ..., f mod (x_1-1,...,x_n-1)].\n\
    // Output(inplace): f(x) = `a[0]` + `a[1]`x_1 + ... + `a[n - 1]`x_1...x_n.\ntemplate\
    \ <typename ModIntT>\nvoid moebius_transform(std::vector<ModIntT> &x) {\n  const\
    \ int n = static_cast<int>(x.size());\n  assert((n & (n - 1)) == 0);\n  // assume\
    \ a + b = b + a\n  for (int i = n >> 1; i != 0; i >>= 1)\n    for (int j = i;\
    \ j < n; j = (j + 1) | i) x[j] -= x[j ^ i];\n}\n\nLIB_END\n\n#endif\n"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: math/zeta_transform.hpp
  requiredBy:
  - math/set_power_series.hpp
  timestamp: '2024-02-28 21:27:40+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/subset_convolution.0.test.cpp
documentation_of: math/zeta_transform.hpp
layout: document
title: Zeta Transform
---
