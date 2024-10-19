---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: bitwise_conv.hpp
    title: bitwise_conv.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/bitwise_and_convolution.0.test.cpp
    title: test/convolution/bitwise_and_convolution.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/convolution/bitwise_xor_convolution.0.test.cpp
    title: test/convolution/bitwise_xor_convolution.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/set_power_series/subset_convolution.0.test.cpp
    title: test/set_power_series/subset_convolution.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"subset_conv.hpp\"\n\n#include <cassert>\n#include <vector>\n\
    \ntemplate <typename Tp>\ninline std::vector<std::vector<Tp>> to_ranked(const\
    \ std::vector<Tp> &A) {\n    const int N = A.size();\n    int LogN    = 0;\n \
    \   while ((1 << LogN) != N) ++LogN;\n    std::vector res(LogN + 1, std::vector<Tp>(N));\n\
    \    for (int i = 0; i < N; ++i) res[__builtin_popcount(i)][i] = A[i];\n    return\
    \ res;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> from_ranked(const\
    \ std::vector<std::vector<Tp>> &A) {\n    const int N = A[0].size();\n    std::vector<Tp>\
    \ res(N);\n    for (int i = 0; i < N; ++i) res[i] = A[__builtin_popcount(i)][i];\n\
    \    return res;\n}\n\ntemplate <typename Iterator>\ninline void subset_zeta_n(Iterator\
    \ a, int n) {\n    assert((n & (n - 1)) == 0);\n    for (int i = 2; i <= n; i\
    \ *= 2)\n        for (int j = 0; j < n; j += i)\n            for (int k = j; k\
    \ < j + i / 2; ++k) a[k + i / 2] += a[k];\n}\n\ntemplate <typename Tp>\ninline\
    \ void subset_zeta(std::vector<Tp> &a) {\n    subset_zeta_n(a.begin(), a.size());\n\
    }\n\ntemplate <typename Iterator>\ninline void subset_moebius_n(Iterator a, int\
    \ n) {\n    assert((n & (n - 1)) == 0);\n    for (int i = 2; i <= n; i *= 2)\n\
    \        for (int j = 0; j < n; j += i)\n            for (int k = j; k < j + i\
    \ / 2; ++k) a[k + i / 2] -= a[k];\n}\n\ntemplate <typename Tp>\ninline void subset_moebius(std::vector<Tp>\
    \ &a) {\n    subset_moebius_n(a.begin(), a.size());\n}\n\ntemplate <typename Tp>\n\
    inline std::vector<Tp> subset_convolution(const std::vector<Tp> &A, const std::vector<Tp>\
    \ &B) {\n    assert(A.size() == B.size());\n    const int N = A.size();\n    int\
    \ LogN    = 0;\n    while ((1 << LogN) != N) ++LogN;\n    auto rankedA = to_ranked(A);\n\
    \    auto rankedB = to_ranked(B);\n\n    // One can replace subset_zeta here to\
    \ sps_fft\n    for (int i = 0; i <= LogN; ++i) {\n        subset_zeta(rankedA[i]);\n\
    \        subset_zeta(rankedB[i]);\n    }\n\n    std::vector rankedAB(LogN + 1,\
    \ std::vector<Tp>(N));\n    for (int i = 0; i <= LogN; ++i)\n        for (int\
    \ j = 0; i + j <= LogN; ++j)\n            for (int k = 0; k < N; ++k) rankedAB[i\
    \ + j][k] += rankedA[i][k] * rankedB[j][k];\n\n    // One can replace subset_moebius\
    \ here to sps_inv_fft\n    for (int i = 0; i <= LogN; ++i) subset_moebius(rankedAB[i]);\n\
    \n    return from_ranked(rankedAB);\n}\n"
  code: "#pragma once\n\n#include <cassert>\n#include <vector>\n\ntemplate <typename\
    \ Tp>\ninline std::vector<std::vector<Tp>> to_ranked(const std::vector<Tp> &A)\
    \ {\n    const int N = A.size();\n    int LogN    = 0;\n    while ((1 << LogN)\
    \ != N) ++LogN;\n    std::vector res(LogN + 1, std::vector<Tp>(N));\n    for (int\
    \ i = 0; i < N; ++i) res[__builtin_popcount(i)][i] = A[i];\n    return res;\n\
    }\n\ntemplate <typename Tp>\ninline std::vector<Tp> from_ranked(const std::vector<std::vector<Tp>>\
    \ &A) {\n    const int N = A[0].size();\n    std::vector<Tp> res(N);\n    for\
    \ (int i = 0; i < N; ++i) res[i] = A[__builtin_popcount(i)][i];\n    return res;\n\
    }\n\ntemplate <typename Iterator>\ninline void subset_zeta_n(Iterator a, int n)\
    \ {\n    assert((n & (n - 1)) == 0);\n    for (int i = 2; i <= n; i *= 2)\n  \
    \      for (int j = 0; j < n; j += i)\n            for (int k = j; k < j + i /\
    \ 2; ++k) a[k + i / 2] += a[k];\n}\n\ntemplate <typename Tp>\ninline void subset_zeta(std::vector<Tp>\
    \ &a) {\n    subset_zeta_n(a.begin(), a.size());\n}\n\ntemplate <typename Iterator>\n\
    inline void subset_moebius_n(Iterator a, int n) {\n    assert((n & (n - 1)) ==\
    \ 0);\n    for (int i = 2; i <= n; i *= 2)\n        for (int j = 0; j < n; j +=\
    \ i)\n            for (int k = j; k < j + i / 2; ++k) a[k + i / 2] -= a[k];\n\
    }\n\ntemplate <typename Tp>\ninline void subset_moebius(std::vector<Tp> &a) {\n\
    \    subset_moebius_n(a.begin(), a.size());\n}\n\ntemplate <typename Tp>\ninline\
    \ std::vector<Tp> subset_convolution(const std::vector<Tp> &A, const std::vector<Tp>\
    \ &B) {\n    assert(A.size() == B.size());\n    const int N = A.size();\n    int\
    \ LogN    = 0;\n    while ((1 << LogN) != N) ++LogN;\n    auto rankedA = to_ranked(A);\n\
    \    auto rankedB = to_ranked(B);\n\n    // One can replace subset_zeta here to\
    \ sps_fft\n    for (int i = 0; i <= LogN; ++i) {\n        subset_zeta(rankedA[i]);\n\
    \        subset_zeta(rankedB[i]);\n    }\n\n    std::vector rankedAB(LogN + 1,\
    \ std::vector<Tp>(N));\n    for (int i = 0; i <= LogN; ++i)\n        for (int\
    \ j = 0; i + j <= LogN; ++j)\n            for (int k = 0; k < N; ++k) rankedAB[i\
    \ + j][k] += rankedA[i][k] * rankedB[j][k];\n\n    // One can replace subset_moebius\
    \ here to sps_inv_fft\n    for (int i = 0; i <= LogN; ++i) subset_moebius(rankedAB[i]);\n\
    \n    return from_ranked(rankedAB);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: subset_conv.hpp
  requiredBy:
  - bitwise_conv.hpp
  timestamp: '2024-10-19 12:59:03+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution/bitwise_xor_convolution.0.test.cpp
  - test/convolution/bitwise_and_convolution.0.test.cpp
  - test/set_power_series/subset_convolution.0.test.cpp
documentation_of: subset_conv.hpp
layout: document
redirect_from:
- /library/subset_conv.hpp
- /library/subset_conv.hpp.html
title: subset_conv.hpp
---
