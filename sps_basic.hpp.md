---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: subset_conv.hpp
    title: subset_conv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/set_power_series/exp_of_set_power_series.0.test.cpp
    title: test/set_power_series/exp_of_set_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/set_power_series/inv_of_set_power_series.0.test.cpp
    title: test/set_power_series/inv_of_set_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/set_power_series/log_of_set_power_series.0.test.cpp
    title: test/set_power_series/log_of_set_power_series.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"sps_basic.hpp\"\n\n#line 2 \"subset_conv.hpp\"\n\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate<typename Tp> inline std::vector<std::vector<Tp>>\
    \ to_ranked(const std::vector<Tp> &A) {\n    const int N = A.size();\n    int\
    \ LogN    = 0;\n    while ((1 << LogN) != N) ++LogN;\n    std::vector res(LogN\
    \ + 1, std::vector<Tp>(N));\n    for (int i = 0; i < N; ++i) res[__builtin_popcount(i)][i]\
    \ = A[i];\n    return res;\n}\n\ntemplate<typename Tp> inline std::vector<Tp>\
    \ from_ranked(const std::vector<std::vector<Tp>> &A) {\n    const int N = A[0].size();\n\
    \    std::vector<Tp> res(N);\n    for (int i = 0; i < N; ++i) res[i] = A[__builtin_popcount(i)][i];\n\
    \    return res;\n}\n\ntemplate<typename Iterator> inline void subset_zeta_n(Iterator\
    \ a, int n) {\n    assert((n & (n - 1)) == 0);\n    for (int i = 2; i <= n; i\
    \ *= 2)\n        for (int j = 0; j < n; j += i)\n            for (int k = j; k\
    \ < j + i / 2; ++k) a[k + i / 2] += a[k];\n}\n\ntemplate<typename Tp> inline void\
    \ subset_zeta(std::vector<Tp> &a) {\n    subset_zeta_n(a.begin(), a.size());\n\
    }\n\ntemplate<typename Iterator> inline void subset_moebius_n(Iterator a, int\
    \ n) {\n    assert((n & (n - 1)) == 0);\n    for (int i = 2; i <= n; i *= 2)\n\
    \        for (int j = 0; j < n; j += i)\n            for (int k = j; k < j + i\
    \ / 2; ++k) a[k + i / 2] -= a[k];\n}\n\ntemplate<typename Tp> inline void subset_moebius(std::vector<Tp>\
    \ &a) {\n    subset_moebius_n(a.begin(), a.size());\n}\n\ntemplate<typename Tp>\n\
    inline std::vector<Tp> subset_convolution(const std::vector<Tp> &A, const std::vector<Tp>\
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
    \    return res;\n}\n#line 6 \"sps_basic.hpp\"\n\nnamespace detail {\n\ntemplate<typename\
    \ Tp> void sps_hadamard_inplace(std::vector<std::vector<Tp>> &rankedA,\n     \
    \                                           const std::vector<std::vector<Tp>>\
    \ &rankedB,\n                                                int LogN) {\n   \
    \ const int N = (1 << LogN);\n    for (int i = LogN; i >= 0; --i) {\n        for\
    \ (int j = 0; j < N; ++j) rankedA[i][j] *= rankedB[0][j];\n        for (int j\
    \ = 1; j <= i; ++j)\n            for (int k = (1 << j) - 1; k < N; ++k)\n    \
    \            rankedA[i][k] += rankedA[i - j][k] * rankedB[j][k];\n    }\n}\n\n\
    } // namespace detail\n\ntemplate<typename Tp> inline std::vector<Tp> sps_inv(const\
    \ std::vector<Tp> &A) {\n    const int N = A.size();\n    assert(N > 0);\n   \
    \ assert((N & (N - 1)) == 0);\n    assert(A[0] != 0);\n    int LogN = 0;\n   \
    \ while ((1 << LogN) != N) ++LogN;\n    std::vector<Tp> res(N);\n    res[0] =\
    \ A[0].inv();\n    std::vector rankedInvA(LogN, std::vector<Tp>(N / 2));\n   \
    \ for (int i = 0; i < LogN; ++i) {\n        std::vector rankedA(i + 1, std::vector<Tp>(1\
    \ << i));\n        for (int j = 0; j < (1 << i); ++j) rankedA[__builtin_popcount(j)][j]\
    \ = A[j + (1 << i)];\n        for (int j = 0; j <= i; ++j) subset_zeta(rankedA[j]);\n\
    \n        for (int j = (1 << i) / 2; j < (1 << i); ++j) rankedInvA[__builtin_popcount(j)][j]\
    \ = res[j];\n        for (int j = 0; j <= i; ++j) {\n            subset_zeta_n(rankedInvA[j].begin()\
    \ + (1 << i) / 2, (1 << i) / 2);\n            for (int k = 0; k < (1 << i) / 2;\
    \ ++k)\n                rankedInvA[j][k + (1 << i) / 2] += rankedInvA[j][k];\n\
    \        }\n\n        detail::sps_hadamard_inplace(rankedA, rankedInvA, i);\n\
    \        detail::sps_hadamard_inplace(rankedA, rankedInvA, i);\n\n        for\
    \ (int j = 0; j <= i; ++j) subset_moebius(rankedA[j]);\n        for (int j = 0;\
    \ j < (1 << i); ++j) res[j + (1 << i)] = -rankedA[__builtin_popcount(j)][j];\n\
    \    }\n    return res;\n}\n\ntemplate<typename Tp> inline std::vector<Tp> sps_log(const\
    \ std::vector<Tp> &A) {\n    const int N = A.size();\n    assert(N > 0);\n   \
    \ assert((N & (N - 1)) == 0);\n    assert(A[0] == 1);\n    int LogN = 0;\n   \
    \ while ((1 << LogN) != N) ++LogN;\n    std::vector<Tp> res(N);\n    std::vector<Tp>\
    \ invA = {Tp(1)};\n    invA.resize(N / 2);\n    std::vector rankedInvA(LogN, std::vector<Tp>(N\
    \ / 2));\n    for (int i = 0; i < LogN; ++i) {\n        std::vector rankedA(i\
    \ + 1, std::vector<Tp>(1 << i));\n        for (int j = 0; j < (1 << i); ++j) rankedA[__builtin_popcount(j)][j]\
    \ = A[j + (1 << i)];\n        for (int j = 0; j <= i; ++j) subset_zeta(rankedA[j]);\n\
    \n        for (int j = (1 << i) / 2; j < (1 << i); ++j)\n            rankedInvA[__builtin_popcount(j)][j]\
    \ = invA[j];\n        for (int j = 0; j <= i; ++j) {\n            subset_zeta_n(rankedInvA[j].begin()\
    \ + (1 << i) / 2, (1 << i) / 2);\n            for (int k = 0; k < (1 << i) / 2;\
    \ ++k)\n                rankedInvA[j][k + (1 << i) / 2] += rankedInvA[j][k];\n\
    \        }\n\n        detail::sps_hadamard_inplace(rankedA, rankedInvA, i);\n\
    \        auto rankedLogA = rankedA;\n        for (int j = 0; j <= i; ++j) subset_moebius(rankedLogA[j]);\n\
    \        for (int j = 0; j < (1 << i); ++j) res[j + (1 << i)] = rankedLogA[__builtin_popcount(j)][j];\n\
    \        if (i == LogN - 1) break;\n        detail::sps_hadamard_inplace(rankedA,\
    \ rankedInvA, i);\n\n        for (int j = 0; j <= i; ++j) subset_moebius(rankedA[j]);\n\
    \        for (int j = 0; j < (1 << i); ++j) invA[j + (1 << i)] = -rankedA[__builtin_popcount(j)][j];\n\
    \    }\n    return res;\n}\n\n// returns exp(0 + tx_1 + ...) in R[x_1,...,x_n]/(x_1^2,...,x_n^2)\n\
    template<typename Tp> inline std::vector<Tp> sps_exp(const std::vector<Tp> &A)\
    \ {\n    const int N = A.size();\n    assert(N > 0);\n    assert((N & (N - 1))\
    \ == 0);\n    assert(A[0] == 0);\n    int LogN = 0;\n    while ((1 << LogN) !=\
    \ N) ++LogN;\n    std::vector<Tp> res(N);\n    res[0] = 1;\n    std::vector rankedExpA(LogN,\
    \ std::vector<Tp>(N / 2));\n    for (int i = 0; i < LogN; ++i) {\n        std::vector\
    \ rankedA(i + 1, std::vector<Tp>(1 << i));\n        for (int j = 0; j < (1 <<\
    \ i); ++j) rankedA[__builtin_popcount(j)][j] = A[j + (1 << i)];\n        for (int\
    \ j = 0; j <= i; ++j) subset_zeta(rankedA[j]);\n\n        for (int j = (1 << i)\
    \ / 2; j < (1 << i); ++j) rankedExpA[__builtin_popcount(j)][j] = res[j];\n   \
    \     for (int j = 0; j <= i; ++j) {\n            subset_zeta_n(rankedExpA[j].begin()\
    \ + (1 << i) / 2, (1 << i) / 2);\n            for (int k = 0; k < (1 << i) / 2;\
    \ ++k)\n                rankedExpA[j][k + (1 << i) / 2] += rankedExpA[j][k];\n\
    \        }\n\n        std::vector<int> map(i + 1);\n        for (int j = 0; j\
    \ <= i; ++j) map[j] = (j & 1) ? map[j / 2] : j / 2;\n\n        std::vector ExpAA(i\
    \ / 2 + 1, std::vector<Tp>(1 << i));\n        for (int j = 0; j <= i; ++j)\n \
    \           for (int k = 0; j + k <= i; ++k)\n                for (int l = (1\
    \ << k) - 1; l < (1 << i); ++l)\n                    ExpAA[map[j + k]][l] += rankedExpA[j][l]\
    \ * rankedA[k][l];\n        for (int j = 0; j <= i / 2; ++j) subset_moebius(ExpAA[j]);\n\
    \n        for (int j = 0; j < (1 << i); ++j) res[j + (1 << i)] = ExpAA[map[__builtin_popcount(j)]][j];\n\
    \    }\n    return res;\n}\n"
  code: "#pragma once\n\n#include \"subset_conv.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\nnamespace detail {\n\ntemplate<typename Tp> void sps_hadamard_inplace(std::vector<std::vector<Tp>>\
    \ &rankedA,\n                                                const std::vector<std::vector<Tp>>\
    \ &rankedB,\n                                                int LogN) {\n   \
    \ const int N = (1 << LogN);\n    for (int i = LogN; i >= 0; --i) {\n        for\
    \ (int j = 0; j < N; ++j) rankedA[i][j] *= rankedB[0][j];\n        for (int j\
    \ = 1; j <= i; ++j)\n            for (int k = (1 << j) - 1; k < N; ++k)\n    \
    \            rankedA[i][k] += rankedA[i - j][k] * rankedB[j][k];\n    }\n}\n\n\
    } // namespace detail\n\ntemplate<typename Tp> inline std::vector<Tp> sps_inv(const\
    \ std::vector<Tp> &A) {\n    const int N = A.size();\n    assert(N > 0);\n   \
    \ assert((N & (N - 1)) == 0);\n    assert(A[0] != 0);\n    int LogN = 0;\n   \
    \ while ((1 << LogN) != N) ++LogN;\n    std::vector<Tp> res(N);\n    res[0] =\
    \ A[0].inv();\n    std::vector rankedInvA(LogN, std::vector<Tp>(N / 2));\n   \
    \ for (int i = 0; i < LogN; ++i) {\n        std::vector rankedA(i + 1, std::vector<Tp>(1\
    \ << i));\n        for (int j = 0; j < (1 << i); ++j) rankedA[__builtin_popcount(j)][j]\
    \ = A[j + (1 << i)];\n        for (int j = 0; j <= i; ++j) subset_zeta(rankedA[j]);\n\
    \n        for (int j = (1 << i) / 2; j < (1 << i); ++j) rankedInvA[__builtin_popcount(j)][j]\
    \ = res[j];\n        for (int j = 0; j <= i; ++j) {\n            subset_zeta_n(rankedInvA[j].begin()\
    \ + (1 << i) / 2, (1 << i) / 2);\n            for (int k = 0; k < (1 << i) / 2;\
    \ ++k)\n                rankedInvA[j][k + (1 << i) / 2] += rankedInvA[j][k];\n\
    \        }\n\n        detail::sps_hadamard_inplace(rankedA, rankedInvA, i);\n\
    \        detail::sps_hadamard_inplace(rankedA, rankedInvA, i);\n\n        for\
    \ (int j = 0; j <= i; ++j) subset_moebius(rankedA[j]);\n        for (int j = 0;\
    \ j < (1 << i); ++j) res[j + (1 << i)] = -rankedA[__builtin_popcount(j)][j];\n\
    \    }\n    return res;\n}\n\ntemplate<typename Tp> inline std::vector<Tp> sps_log(const\
    \ std::vector<Tp> &A) {\n    const int N = A.size();\n    assert(N > 0);\n   \
    \ assert((N & (N - 1)) == 0);\n    assert(A[0] == 1);\n    int LogN = 0;\n   \
    \ while ((1 << LogN) != N) ++LogN;\n    std::vector<Tp> res(N);\n    std::vector<Tp>\
    \ invA = {Tp(1)};\n    invA.resize(N / 2);\n    std::vector rankedInvA(LogN, std::vector<Tp>(N\
    \ / 2));\n    for (int i = 0; i < LogN; ++i) {\n        std::vector rankedA(i\
    \ + 1, std::vector<Tp>(1 << i));\n        for (int j = 0; j < (1 << i); ++j) rankedA[__builtin_popcount(j)][j]\
    \ = A[j + (1 << i)];\n        for (int j = 0; j <= i; ++j) subset_zeta(rankedA[j]);\n\
    \n        for (int j = (1 << i) / 2; j < (1 << i); ++j)\n            rankedInvA[__builtin_popcount(j)][j]\
    \ = invA[j];\n        for (int j = 0; j <= i; ++j) {\n            subset_zeta_n(rankedInvA[j].begin()\
    \ + (1 << i) / 2, (1 << i) / 2);\n            for (int k = 0; k < (1 << i) / 2;\
    \ ++k)\n                rankedInvA[j][k + (1 << i) / 2] += rankedInvA[j][k];\n\
    \        }\n\n        detail::sps_hadamard_inplace(rankedA, rankedInvA, i);\n\
    \        auto rankedLogA = rankedA;\n        for (int j = 0; j <= i; ++j) subset_moebius(rankedLogA[j]);\n\
    \        for (int j = 0; j < (1 << i); ++j) res[j + (1 << i)] = rankedLogA[__builtin_popcount(j)][j];\n\
    \        if (i == LogN - 1) break;\n        detail::sps_hadamard_inplace(rankedA,\
    \ rankedInvA, i);\n\n        for (int j = 0; j <= i; ++j) subset_moebius(rankedA[j]);\n\
    \        for (int j = 0; j < (1 << i); ++j) invA[j + (1 << i)] = -rankedA[__builtin_popcount(j)][j];\n\
    \    }\n    return res;\n}\n\n// returns exp(0 + tx_1 + ...) in R[x_1,...,x_n]/(x_1^2,...,x_n^2)\n\
    template<typename Tp> inline std::vector<Tp> sps_exp(const std::vector<Tp> &A)\
    \ {\n    const int N = A.size();\n    assert(N > 0);\n    assert((N & (N - 1))\
    \ == 0);\n    assert(A[0] == 0);\n    int LogN = 0;\n    while ((1 << LogN) !=\
    \ N) ++LogN;\n    std::vector<Tp> res(N);\n    res[0] = 1;\n    std::vector rankedExpA(LogN,\
    \ std::vector<Tp>(N / 2));\n    for (int i = 0; i < LogN; ++i) {\n        std::vector\
    \ rankedA(i + 1, std::vector<Tp>(1 << i));\n        for (int j = 0; j < (1 <<\
    \ i); ++j) rankedA[__builtin_popcount(j)][j] = A[j + (1 << i)];\n        for (int\
    \ j = 0; j <= i; ++j) subset_zeta(rankedA[j]);\n\n        for (int j = (1 << i)\
    \ / 2; j < (1 << i); ++j) rankedExpA[__builtin_popcount(j)][j] = res[j];\n   \
    \     for (int j = 0; j <= i; ++j) {\n            subset_zeta_n(rankedExpA[j].begin()\
    \ + (1 << i) / 2, (1 << i) / 2);\n            for (int k = 0; k < (1 << i) / 2;\
    \ ++k)\n                rankedExpA[j][k + (1 << i) / 2] += rankedExpA[j][k];\n\
    \        }\n\n        std::vector<int> map(i + 1);\n        for (int j = 0; j\
    \ <= i; ++j) map[j] = (j & 1) ? map[j / 2] : j / 2;\n\n        std::vector ExpAA(i\
    \ / 2 + 1, std::vector<Tp>(1 << i));\n        for (int j = 0; j <= i; ++j)\n \
    \           for (int k = 0; j + k <= i; ++k)\n                for (int l = (1\
    \ << k) - 1; l < (1 << i); ++l)\n                    ExpAA[map[j + k]][l] += rankedExpA[j][l]\
    \ * rankedA[k][l];\n        for (int j = 0; j <= i / 2; ++j) subset_moebius(ExpAA[j]);\n\
    \n        for (int j = 0; j < (1 << i); ++j) res[j + (1 << i)] = ExpAA[map[__builtin_popcount(j)]][j];\n\
    \    }\n    return res;\n}\n"
  dependsOn:
  - subset_conv.hpp
  isVerificationFile: false
  path: sps_basic.hpp
  requiredBy: []
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/set_power_series/exp_of_set_power_series.0.test.cpp
  - test/set_power_series/log_of_set_power_series.0.test.cpp
  - test/set_power_series/inv_of_set_power_series.0.test.cpp
documentation_of: sps_basic.hpp
layout: document
redirect_from:
- /library/sps_basic.hpp
- /library/sps_basic.hpp.html
title: sps_basic.hpp
---
