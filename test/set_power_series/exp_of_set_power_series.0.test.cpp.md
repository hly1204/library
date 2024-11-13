---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: sps_basic.hpp
    title: sps_basic.hpp
  - icon: ':heavy_check_mark:'
    path: subset_conv.hpp
    title: subset_conv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/exp_of_set_power_series
    links:
    - https://judge.yosupo.jp/problem/exp_of_set_power_series
  bundledCode: "#line 1 \"test/set_power_series/exp_of_set_power_series.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/exp_of_set_power_series\"\n\
    \n#line 2 \"modint.hpp\"\n\n#include <iostream>\n#include <type_traits>\n\ntemplate\
    \ <unsigned Mod>\nclass ModInt {\n    static_assert((Mod >> 31) == 0, \"`Mod`\
    \ must less than 2^(31)\");\n    template <typename Int>\n    static std::enable_if_t<std::is_integral_v<Int>,\
    \ unsigned> safe_mod(Int v) {\n        using D = std::common_type_t<Int, unsigned>;\n\
    \        return (v %= (int)Mod) < 0 ? (D)(v + (int)Mod) : (D)v;\n    }\n\n   \
    \ struct PrivateConstructor {};\n    static inline PrivateConstructor private_constructor{};\n\
    \    ModInt(PrivateConstructor, unsigned v) : v_(v) {}\n\n    unsigned v_;\n\n\
    public:\n    static unsigned mod() { return Mod; }\n    static ModInt from_raw(unsigned\
    \ v) { return ModInt(private_constructor, v); }\n    ModInt() : v_() {}\n    template\
    \ <typename Int, typename std::enable_if_t<std::is_signed_v<Int>, int> = 0>\n\
    \    ModInt(Int v) : v_(safe_mod(v)) {}\n    template <typename Int, typename\
    \ std::enable_if_t<std::is_unsigned_v<Int>, int> = 0>\n    ModInt(Int v) : v_(v\
    \ % Mod) {}\n    unsigned val() const { return v_; }\n\n    ModInt operator-()\
    \ const { return from_raw(v_ == 0 ? v_ : Mod - v_); }\n    ModInt pow(long long\
    \ e) const {\n        if (e < 0) return inv().pow(-e);\n        for (ModInt x(*this),\
    \ res(from_raw(1));; x *= x) {\n            if (e & 1) res *= x;\n           \
    \ if ((e >>= 1) == 0) return res;\n        }\n    }\n    ModInt inv() const {\n\
    \        int x1 = 1, x3 = 0, a = val(), b = Mod;\n        while (b) {\n      \
    \      int q = a / b, x1_old = x1, a_old = a;\n            x1 = x3, x3 = x1_old\
    \ - x3 * q, a = b, b = a_old - b * q;\n        }\n        return from_raw(x1 <\
    \ 0 ? x1 + (int)Mod : x1);\n    }\n    template <bool Odd = (Mod & 1)>\n    std::enable_if_t<Odd,\
    \ ModInt> div_by_2() const {\n        if (v_ & 1) return from_raw((v_ + Mod) >>\
    \ 1);\n        return from_raw(v_ >> 1);\n    }\n\n    ModInt &operator+=(const\
    \ ModInt &a) {\n        if ((v_ += a.v_) >= Mod) v_ -= Mod;\n        return *this;\n\
    \    }\n    ModInt &operator-=(const ModInt &a) {\n        if ((v_ += Mod - a.v_)\
    \ >= Mod) v_ -= Mod;\n        return *this;\n    }\n    ModInt &operator*=(const\
    \ ModInt &a) {\n        v_ = (unsigned long long)v_ * a.v_ % Mod;\n        return\
    \ *this;\n    }\n    ModInt &operator/=(const ModInt &a) { return *this *= a.inv();\
    \ }\n\n    friend ModInt operator+(const ModInt &a, const ModInt &b) { return\
    \ ModInt(a) += b; }\n    friend ModInt operator-(const ModInt &a, const ModInt\
    \ &b) { return ModInt(a) -= b; }\n    friend ModInt operator*(const ModInt &a,\
    \ const ModInt &b) { return ModInt(a) *= b; }\n    friend ModInt operator/(const\
    \ ModInt &a, const ModInt &b) { return ModInt(a) /= b; }\n    friend bool operator==(const\
    \ ModInt &a, const ModInt &b) { return a.v_ == b.v_; }\n    friend bool operator!=(const\
    \ ModInt &a, const ModInt &b) { return a.v_ != b.v_; }\n    friend std::istream\
    \ &operator>>(std::istream &a, ModInt &b) {\n        int v;\n        a >> v;\n\
    \        b.v_ = safe_mod(v);\n        return a;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &a, const ModInt &b) { return a << b.val(); }\n};\n\
    #line 2 \"sps_basic.hpp\"\n\n#line 2 \"subset_conv.hpp\"\n\n#include <cassert>\n\
    #include <vector>\n\ntemplate <typename Tp>\ninline std::vector<std::vector<Tp>>\
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
    \            for (int k = (1 << j) - 1; k < N; ++k)\n                rankedAB[map[i\
    \ + j]][k] += rankedA[i][k] * rankedB[j][k];\n\n    for (int i = 0; i <= LogN\
    \ / 2; ++i) subset_moebius(rankedAB[i]);\n\n    std::vector<Tp> res(N);\n    for\
    \ (int i = 0; i < N; ++i) res[i] = rankedAB[map[__builtin_popcount(i)]][i];\n\
    \    return res;\n}\n#line 6 \"sps_basic.hpp\"\n\ntemplate <typename Tp>\nvoid\
    \ convolution_ranked_inplace(std::vector<std::vector<Tp>> &rankedA,\n        \
    \                        const std::vector<std::vector<Tp>> &rankedB, int LogN)\
    \ {\n    const int N = (1 << LogN);\n    for (int i = LogN; i >= 0; --i) {\n \
    \       for (int j = 0; j < N; ++j) rankedA[i][j] *= rankedB[0][j];\n        for\
    \ (int j = 1; j <= i; ++j)\n            for (int k = (1 << j) - 1; k < N; ++k)\n\
    \                rankedA[i][k] += rankedA[i - j][k] * rankedB[j][k];\n    }\n\
    }\n\ntemplate <typename Tp>\ninline std::vector<Tp> sps_inv(const std::vector<Tp>\
    \ &A) {\n    const int N = A.size();\n    assert(N > 0);\n    assert((N & (N -\
    \ 1)) == 0);\n    assert(A[0] != 0);\n    int LogN = 0;\n    while ((1 << LogN)\
    \ != N) ++LogN;\n    std::vector<Tp> res(N);\n    res[0] = A[0].inv();\n    std::vector\
    \ rankedInvA(LogN, std::vector<Tp>(N / 2));\n    for (int i = 0; i < LogN; ++i)\
    \ {\n        std::vector rankedA(i + 1, std::vector<Tp>(1 << i));\n        for\
    \ (int j = 0; j < (1 << i); ++j) rankedA[__builtin_popcount(j)][j] = A[j + (1\
    \ << i)];\n        for (int j = 0; j <= i; ++j) subset_zeta(rankedA[j]);\n\n \
    \       for (int j = (1 << i) / 2; j < (1 << i); ++j) rankedInvA[__builtin_popcount(j)][j]\
    \ = res[j];\n        for (int j = 0; j <= i; ++j) {\n            subset_zeta_n(rankedInvA[j].begin()\
    \ + (1 << i) / 2, (1 << i) / 2);\n            for (int k = 0; k < (1 << i) / 2;\
    \ ++k)\n                rankedInvA[j][k + (1 << i) / 2] += rankedInvA[j][k];\n\
    \        }\n\n        convolution_ranked_inplace(rankedA, rankedInvA, i);\n  \
    \      convolution_ranked_inplace(rankedA, rankedInvA, i);\n\n        for (int\
    \ j = 0; j <= i; ++j) subset_moebius(rankedA[j]);\n        for (int j = 0; j <\
    \ (1 << i); ++j) res[j + (1 << i)] = -rankedA[__builtin_popcount(j)][j];\n   \
    \ }\n    return res;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> sps_log(const\
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
    \        }\n\n        convolution_ranked_inplace(rankedA, rankedInvA, i);\n  \
    \      auto rankedLogA = rankedA;\n        for (int j = 0; j <= i; ++j) subset_moebius(rankedLogA[j]);\n\
    \        for (int j = 0; j < (1 << i); ++j) res[j + (1 << i)] = rankedLogA[__builtin_popcount(j)][j];\n\
    \        if (i == LogN - 1) break;\n        convolution_ranked_inplace(rankedA,\
    \ rankedInvA, i);\n\n        for (int j = 0; j <= i; ++j) subset_moebius(rankedA[j]);\n\
    \        for (int j = 0; j < (1 << i); ++j) invA[j + (1 << i)] = -rankedA[__builtin_popcount(j)][j];\n\
    \    }\n    return res;\n}\n\n// returns exp(0 + tx_1 + ...) in R[x_1,...,x_n]/(x_1^2,...,x_n^2)\n\
    template <typename Tp>\ninline std::vector<Tp> sps_exp(const std::vector<Tp> &A)\
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
    \    }\n    return res;\n}\n#line 7 \"test/set_power_series/exp_of_set_power_series.0.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = ModInt<998244353>;\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ a(1 << n);\n    for (int i = 0; i < (1 << n); ++i) std::cin >> a[i];\n    const\
    \ auto expa = sps_exp(a);\n    for (int i = 0; i < (1 << n); ++i) std::cout <<\
    \ expa[i] << ' ';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/exp_of_set_power_series\"\
    \n\n#include \"modint.hpp\"\n#include \"sps_basic.hpp\"\n#include <iostream>\n\
    #include <vector>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n   \
    \ std::cin.tie(nullptr);\n    using mint = ModInt<998244353>;\n    int n;\n  \
    \  std::cin >> n;\n    std::vector<mint> a(1 << n);\n    for (int i = 0; i < (1\
    \ << n); ++i) std::cin >> a[i];\n    const auto expa = sps_exp(a);\n    for (int\
    \ i = 0; i < (1 << n); ++i) std::cout << expa[i] << ' ';\n    return 0;\n}\n"
  dependsOn:
  - modint.hpp
  - sps_basic.hpp
  - subset_conv.hpp
  isVerificationFile: true
  path: test/set_power_series/exp_of_set_power_series.0.test.cpp
  requiredBy: []
  timestamp: '2024-10-25 19:24:31+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/set_power_series/exp_of_set_power_series.0.test.cpp
layout: document
redirect_from:
- /verify/test/set_power_series/exp_of_set_power_series.0.test.cpp
- /verify/test/set_power_series/exp_of_set_power_series.0.test.cpp.html
title: test/set_power_series/exp_of_set_power_series.0.test.cpp
---
