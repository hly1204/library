---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: subset_conv.hpp
    title: subset_conv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/set_power_series/polynomial_composite_set_power_series.0.test.cpp
    title: test/set_power_series/polynomial_composite_set_power_series.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"sps_in_poly.hpp\"\n\n#line 2 \"subset_conv.hpp\"\n\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate <typename Tp>\ninline std::vector<std::vector<Tp>>\
    \ to_ranked(const std::vector<Tp> &A) {\n    const int N = A.size();\n    int\
    \ LogN    = 0;\n    while ((1 << LogN) != N) ++LogN;\n    std::vector res(LogN\
    \ + 1, std::vector<Tp>(N));\n    for (int i = 0; i < N; ++i) res[__builtin_popcount(i)][i]\
    \ = A[i];\n    return res;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ from_ranked(const std::vector<std::vector<Tp>> &A) {\n    const int N = A[0].size();\n\
    \    std::vector<Tp> res(N);\n    for (int i = 0; i < N; ++i) res[i] = A[__builtin_popcount(i)][i];\n\
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
    \    auto rankedB = to_ranked(B);\n\n    for (int i = 0; i <= LogN; ++i) {\n \
    \       subset_zeta(rankedA[i]);\n        subset_zeta(rankedB[i]);\n    }\n\n\
    \    // see: https://codeforces.com/blog/entry/126418\n    // see: https://oeis.org/A025480\n\
    \    std::vector<int> map(LogN + 1);\n    for (int i = 0; i <= LogN; ++i) map[i]\
    \ = (i & 1) ? map[i / 2] : i / 2;\n\n    std::vector rankedAB(LogN / 2 + 1, std::vector<Tp>(N));\n\
    \    for (int i = 0; i <= LogN; ++i)\n        for (int j = 0; i + j <= LogN; ++j)\n\
    \            for (int k = 0; k < N; ++k) rankedAB[map[i + j]][k] += rankedA[i][k]\
    \ * rankedB[j][k];\n\n    for (int i = 0; i <= LogN / 2; ++i) subset_moebius(rankedAB[i]);\n\
    \n    std::vector<Tp> res(N);\n    for (int i = 0; i < N; ++i) res[i] = rankedAB[map[__builtin_popcount(i)]][i];\n\
    \    return res;\n}\n#line 4 \"sps_in_poly.hpp\"\n#include <algorithm>\n#line\
    \ 7 \"sps_in_poly.hpp\"\n\n// returns F(G)\n// requires deg(F)<=n, G(0)=0\ntemplate\
    \ <typename Tp>\ninline std::vector<Tp> sps_in_egf(const std::vector<Tp> &F, const\
    \ std::vector<Tp> &G) {\n    const int N = (int)F.size() - 1;\n    assert((int)G.size()\
    \ == (1 << N));\n    assert(G[0] == 0);\n\n    std::vector res = {F[N]};\n   \
    \ for (int i = 0; i < N; ++i) {\n        std::vector<Tp> R(1 << (i + 1));\n  \
    \      R[0] = F[N - (i + 1)];\n        for (int j = 0; j <= i; ++j) {\n      \
    \      const auto FG =\n                subset_convolution(std::vector(res.begin(),\
    \ res.begin() + (1 << j)),\n                                   std::vector(G.begin()\
    \ + (1 << j), G.begin() + (2 << j)));\n            std::copy(FG.begin(), FG.end(),\
    \ R.begin() + (1 << j));\n        }\n        R.swap(res);\n    }\n\n    return\
    \ res;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> sps_in_poly(std::vector<Tp>\
    \ F, std::vector<Tp> G) {\n    const int N = G.size();\n    int LogN    = 0;\n\
    \    while ((1 << LogN) != N) ++LogN;\n\n    if (G[0] != 0) {\n        std::vector<Tp>\
    \ bin(LogN + 1), pw(F.size() + 1), FF(LogN + 1);\n        pw[0] = 1;\n       \
    \ for (int i = 1; i < (int)pw.size(); ++i) pw[i] = pw[i - 1] * G[0];\n       \
    \ G[0]   = 0;\n        bin[0] = 1;\n        for (int i = 0; i < (int)F.size();\
    \ ++i) {\n            for (int j = 0; j <= std::min(LogN, i); ++j) FF[j] += F[i]\
    \ * bin[j] * pw[i - j];\n            for (int j = LogN; j > 0; --j) bin[j] +=\
    \ bin[j - 1];\n        }\n        FF.swap(F);\n    }\n\n    F.resize(LogN + 1);\n\
    \    Tp c = 1;                                       // factorial\n    for (int\
    \ i = 1; i <= LogN; ++i) F[i] *= c *= i; // to EGF\n    return sps_in_egf(F, G);\n\
    }\n"
  code: "#pragma once\n\n#include \"subset_conv.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\n// returns F(G)\n// requires deg(F)<=n, G(0)=0\n\
    template <typename Tp>\ninline std::vector<Tp> sps_in_egf(const std::vector<Tp>\
    \ &F, const std::vector<Tp> &G) {\n    const int N = (int)F.size() - 1;\n    assert((int)G.size()\
    \ == (1 << N));\n    assert(G[0] == 0);\n\n    std::vector res = {F[N]};\n   \
    \ for (int i = 0; i < N; ++i) {\n        std::vector<Tp> R(1 << (i + 1));\n  \
    \      R[0] = F[N - (i + 1)];\n        for (int j = 0; j <= i; ++j) {\n      \
    \      const auto FG =\n                subset_convolution(std::vector(res.begin(),\
    \ res.begin() + (1 << j)),\n                                   std::vector(G.begin()\
    \ + (1 << j), G.begin() + (2 << j)));\n            std::copy(FG.begin(), FG.end(),\
    \ R.begin() + (1 << j));\n        }\n        R.swap(res);\n    }\n\n    return\
    \ res;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> sps_in_poly(std::vector<Tp>\
    \ F, std::vector<Tp> G) {\n    const int N = G.size();\n    int LogN    = 0;\n\
    \    while ((1 << LogN) != N) ++LogN;\n\n    if (G[0] != 0) {\n        std::vector<Tp>\
    \ bin(LogN + 1), pw(F.size() + 1), FF(LogN + 1);\n        pw[0] = 1;\n       \
    \ for (int i = 1; i < (int)pw.size(); ++i) pw[i] = pw[i - 1] * G[0];\n       \
    \ G[0]   = 0;\n        bin[0] = 1;\n        for (int i = 0; i < (int)F.size();\
    \ ++i) {\n            for (int j = 0; j <= std::min(LogN, i); ++j) FF[j] += F[i]\
    \ * bin[j] * pw[i - j];\n            for (int j = LogN; j > 0; --j) bin[j] +=\
    \ bin[j - 1];\n        }\n        FF.swap(F);\n    }\n\n    F.resize(LogN + 1);\n\
    \    Tp c = 1;                                       // factorial\n    for (int\
    \ i = 1; i <= LogN; ++i) F[i] *= c *= i; // to EGF\n    return sps_in_egf(F, G);\n\
    }\n"
  dependsOn:
  - subset_conv.hpp
  isVerificationFile: false
  path: sps_in_poly.hpp
  requiredBy: []
  timestamp: '2024-10-22 23:05:35+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/set_power_series/polynomial_composite_set_power_series.0.test.cpp
documentation_of: sps_in_poly.hpp
layout: document
redirect_from:
- /library/sps_in_poly.hpp
- /library/sps_in_poly.hpp.html
title: sps_in_poly.hpp
---
