---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: sps_fft.hpp
    title: sps_fft.hpp
  - icon: ':heavy_check_mark:'
    path: subset_conv.hpp
    title: subset_conv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/bitwise_and_convolution.0.test.cpp
    title: test/convolution/bitwise_and_convolution.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/convolution/bitwise_xor_convolution.0.test.cpp
    title: test/convolution/bitwise_xor_convolution.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"bitwise_conv.hpp\"\n\n#line 2 \"sps_fft.hpp\"\n\n#include\
    \ <cassert>\n#include <iterator>\n#include <vector>\n\n// set power series = R[x_1,...,x_n]/(x_1^2,...,x_n^2)\n\
    // FFT is computing F({1,-1}^n)\n\ntemplate<typename Iterator> inline void sps_fft_n(Iterator\
    \ a, int n) {\n    assert((n & (n - 1)) == 0);\n    for (int i = 2; i <= n; i\
    \ *= 2)\n        for (int j = 0; j < n; j += i)\n            for (int k = j; k\
    \ < j + i / 2; ++k) {\n                const auto u = a[k], v = a[k + i / 2];\n\
    \                a[k] = u + v, a[k + i / 2] = u - v;\n            }\n}\n\ntemplate<typename\
    \ Tp> inline void sps_fft(std::vector<Tp> &a) { sps_fft_n(a.begin(), a.size());\
    \ }\n\ntemplate<typename Iterator> inline void sps_inv_fft_n(Iterator a, int n)\
    \ {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n   \
    \ sps_fft_n(a, n);\n    const Tp iv = Tp::mod() - (Tp::mod() - 1) / n;\n    for\
    \ (int i = 0; i < n; ++i) a[i] *= iv;\n}\n\ntemplate<typename Tp> inline void\
    \ sps_inv_fft(std::vector<Tp> &a) {\n    sps_inv_fft_n(a.begin(), a.size());\n\
    }\n#line 2 \"subset_conv.hpp\"\n\n#line 5 \"subset_conv.hpp\"\n\ntemplate<typename\
    \ Tp> inline std::vector<std::vector<Tp>> to_ranked(const std::vector<Tp> &A)\
    \ {\n    const int N = A.size();\n    int LogN    = 0;\n    while ((1 << LogN)\
    \ != N) ++LogN;\n    std::vector res(LogN + 1, std::vector<Tp>(N));\n    for (int\
    \ i = 0; i < N; ++i) res[__builtin_popcount(i)][i] = A[i];\n    return res;\n\
    }\n\ntemplate<typename Tp> inline std::vector<Tp> from_ranked(const std::vector<std::vector<Tp>>\
    \ &A) {\n    const int N = A[0].size();\n    std::vector<Tp> res(N);\n    for\
    \ (int i = 0; i < N; ++i) res[i] = A[__builtin_popcount(i)][i];\n    return res;\n\
    }\n\ntemplate<typename Iterator> inline void subset_zeta_n(Iterator a, int n)\
    \ {\n    assert((n & (n - 1)) == 0);\n    for (int i = 2; i <= n; i *= 2)\n  \
    \      for (int j = 0; j < n; j += i)\n            for (int k = j; k < j + i /\
    \ 2; ++k) a[k + i / 2] += a[k];\n}\n\ntemplate<typename Tp> inline void subset_zeta(std::vector<Tp>\
    \ &a) {\n    subset_zeta_n(a.begin(), a.size());\n}\n\ntemplate<typename Iterator>\
    \ inline void subset_moebius_n(Iterator a, int n) {\n    assert((n & (n - 1))\
    \ == 0);\n    for (int i = 2; i <= n; i *= 2)\n        for (int j = 0; j < n;\
    \ j += i)\n            for (int k = j; k < j + i / 2; ++k) a[k + i / 2] -= a[k];\n\
    }\n\ntemplate<typename Tp> inline void subset_moebius(std::vector<Tp> &a) {\n\
    \    subset_moebius_n(a.begin(), a.size());\n}\n\ntemplate<typename Tp>\ninline\
    \ std::vector<Tp> subset_convolution(const std::vector<Tp> &A, const std::vector<Tp>\
    \ &B) {\n    assert(A.size() == B.size());\n    const int N = A.size();\n    int\
    \ LogN    = 0;\n    while ((1 << LogN) != N) ++LogN;\n    auto rankedA = to_ranked(A);\n\
    \    auto rankedB = to_ranked(B);\n\n    for (int i = 0; i <= LogN; ++i) {\n \
    \       subset_zeta(rankedA[i]);\n        subset_zeta(rankedB[i]);\n    }\n\n\
    \    // see: https://codeforces.com/blog/entry/126418\n    // see: https://oeis.org/A025480\n\
    \    std::vector<int> map(LogN + 1);\n    for (int i = 0; i <= LogN; ++i) map[i]\
    \ = (i & 1) ? map[i / 2] : i / 2;\n\n    std::vector rankedAB(LogN / 2 + 1, std::vector<Tp>(N));\n\
    \    for (int i = 0; i <= LogN; ++i)\n        for (int j = 0; i + j <= LogN; ++j)\n\
    \            for (int k = (1 << j) - 1; k < N; ++k)\n                rankedAB[map[i\
    \ + j]][k] += rankedA[i][k] * rankedB[j][k];\n\n    for (int i = 0; i <= LogN\
    \ / 2; ++i) subset_moebius(rankedAB[i]);\n\n    std::vector<Tp> res(N);\n    for\
    \ (int i = 0; i < N; ++i) res[i] = rankedAB[map[__builtin_popcount(i)]][i];\n\
    \    return res;\n}\n#line 5 \"bitwise_conv.hpp\"\n#include <algorithm>\n#line\
    \ 8 \"bitwise_conv.hpp\"\n\ntemplate<typename Tp>\ninline std::vector<Tp> bitwise_or_convolution(std::vector<Tp>\
    \ a, std::vector<Tp> b) {\n    assert(a.size() == b.size());\n    const int n\
    \ = a.size();\n    assert((n & (n - 1)) == 0);\n    assert(n > 0);\n    subset_zeta(a);\n\
    \    subset_zeta(b);\n    for (int i = 0; i < n; ++i) a[i] *= b[i];\n    subset_moebius(a);\n\
    \    return a;\n}\n\ntemplate<typename Tp>\ninline std::vector<Tp> bitwise_and_convolution(const\
    \ std::vector<Tp> &a, const std::vector<Tp> &b) {\n    auto ab = bitwise_or_convolution(std::vector(a.rbegin(),\
    \ a.rend()),\n                                     std::vector(b.rbegin(), b.rend()));\n\
    \    std::reverse(ab.begin(), ab.end());\n    return ab;\n}\n\ntemplate<typename\
    \ Tp>\ninline std::vector<Tp> bitwise_xor_convolution(std::vector<Tp> a, std::vector<Tp>\
    \ b) {\n    assert(a.size() == b.size());\n    const int n = a.size();\n    assert((n\
    \ & (n - 1)) == 0);\n    assert(n > 0);\n    sps_fft(a);\n    sps_fft(b);\n  \
    \  for (int i = 0; i < n; ++i) a[i] *= b[i];\n    sps_inv_fft(a);\n    return\
    \ a;\n}\n"
  code: "#pragma once\n\n#include \"sps_fft.hpp\"\n#include \"subset_conv.hpp\"\n\
    #include <algorithm>\n#include <cassert>\n#include <vector>\n\ntemplate<typename\
    \ Tp>\ninline std::vector<Tp> bitwise_or_convolution(std::vector<Tp> a, std::vector<Tp>\
    \ b) {\n    assert(a.size() == b.size());\n    const int n = a.size();\n    assert((n\
    \ & (n - 1)) == 0);\n    assert(n > 0);\n    subset_zeta(a);\n    subset_zeta(b);\n\
    \    for (int i = 0; i < n; ++i) a[i] *= b[i];\n    subset_moebius(a);\n    return\
    \ a;\n}\n\ntemplate<typename Tp>\ninline std::vector<Tp> bitwise_and_convolution(const\
    \ std::vector<Tp> &a, const std::vector<Tp> &b) {\n    auto ab = bitwise_or_convolution(std::vector(a.rbegin(),\
    \ a.rend()),\n                                     std::vector(b.rbegin(), b.rend()));\n\
    \    std::reverse(ab.begin(), ab.end());\n    return ab;\n}\n\ntemplate<typename\
    \ Tp>\ninline std::vector<Tp> bitwise_xor_convolution(std::vector<Tp> a, std::vector<Tp>\
    \ b) {\n    assert(a.size() == b.size());\n    const int n = a.size();\n    assert((n\
    \ & (n - 1)) == 0);\n    assert(n > 0);\n    sps_fft(a);\n    sps_fft(b);\n  \
    \  for (int i = 0; i < n; ++i) a[i] *= b[i];\n    sps_inv_fft(a);\n    return\
    \ a;\n}\n"
  dependsOn:
  - sps_fft.hpp
  - subset_conv.hpp
  isVerificationFile: false
  path: bitwise_conv.hpp
  requiredBy: []
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution/bitwise_xor_convolution.0.test.cpp
  - test/convolution/bitwise_and_convolution.0.test.cpp
documentation_of: bitwise_conv.hpp
layout: document
redirect_from:
- /library/bitwise_conv.hpp
- /library/bitwise_conv.hpp.html
title: bitwise_conv.hpp
---
