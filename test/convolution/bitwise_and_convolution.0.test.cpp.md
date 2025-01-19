---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: bitwise_conv.hpp
    title: bitwise_conv.hpp
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: sps_fft.hpp
    title: sps_fft.hpp
  - icon: ':question:'
    path: subset_conv.hpp
    title: subset_conv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bitwise_and_convolution
    links:
    - https://judge.yosupo.jp/problem/bitwise_and_convolution
  bundledCode: "#line 1 \"test/convolution/bitwise_and_convolution.0.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\n\n\
    #line 2 \"bitwise_conv.hpp\"\n\n#line 2 \"sps_fft.hpp\"\n\n#include <cassert>\n\
    #include <iterator>\n#include <vector>\n\n// set power series = R[x_1,...,x_n]/(x_1^2,...,x_n^2)\n\
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
    \ a;\n}\n#line 2 \"modint.hpp\"\n\n#include <iostream>\n#include <type_traits>\n\
    \n// clang-format off\ntemplate<unsigned Mod> class ModInt {\n    static_assert((Mod\
    \ >> 31) == 0, \"`Mod` must less than 2^(31)\");\n    template<typename Int>\n\
    \    static std::enable_if_t<std::is_integral_v<Int>, unsigned> safe_mod(Int v)\
    \ { using D = std::common_type_t<Int, unsigned>; return (v %= (int)Mod) < 0 ?\
    \ (D)(v + (int)Mod) : (D)v; }\n    struct PrivateConstructor {} static inline\
    \ private_constructor{};\n    ModInt(PrivateConstructor, unsigned v) : v_(v) {}\n\
    \    unsigned v_;\n\npublic:\n    static unsigned mod() { return Mod; }\n    static\
    \ ModInt from_raw(unsigned v) { return ModInt(private_constructor, v); }\n   \
    \ static ModInt zero() { return from_raw(0); }\n    static ModInt one() { return\
    \ from_raw(1); }\n    bool is_zero() const { return v_ == 0; }\n    bool is_one()\
    \ const { return v_ == 1; }\n    ModInt() : v_() {}\n    template<typename Int,\
    \ typename std::enable_if_t<std::is_signed_v<Int>, int> = 0> ModInt(Int v) : v_(safe_mod(v))\
    \ {}\n    template<typename Int, typename std::enable_if_t<std::is_unsigned_v<Int>,\
    \ int> = 0> ModInt(Int v) : v_(v % Mod) {}\n    unsigned val() const { return\
    \ v_; }\n    ModInt operator-() const { return from_raw(v_ == 0 ? v_ : Mod - v_);\
    \ }\n    ModInt pow(long long e) const { if (e < 0) return inv().pow(-e); for\
    \ (ModInt x(*this), res(from_raw(1));; x *= x) { if (e & 1) res *= x; if ((e >>=\
    \ 1) == 0) return res; }}\n    ModInt inv() const { int x1 = 1, x3 = 0, a = val(),\
    \ b = Mod; while (b) { const int q = a / b, x1_old = x1, a_old = a; x1 = x3, x3\
    \ = x1_old - x3 * q, a = b, b = a_old - b * q; } return from_raw(x1 < 0 ? x1 +\
    \ (int)Mod : x1); }\n    template<bool Odd = (Mod & 1)> std::enable_if_t<Odd,\
    \ ModInt> div_by_2() const { if (v_ & 1) return from_raw((v_ + Mod) >> 1); return\
    \ from_raw(v_ >> 1); }\n    ModInt &operator+=(const ModInt &a) { if ((v_ += a.v_)\
    \ >= Mod) v_ -= Mod; return *this; }\n    ModInt &operator-=(const ModInt &a)\
    \ { if ((v_ += Mod - a.v_) >= Mod) v_ -= Mod; return *this; }\n    ModInt &operator*=(const\
    \ ModInt &a) { v_ = (unsigned long long)v_ * a.v_ % Mod; return *this; }\n   \
    \ ModInt &operator/=(const ModInt &a) { return *this *= a.inv(); }\n    ModInt\
    \ &operator++() { return *this += one(); }\n    ModInt operator++(int) { ModInt\
    \ o(*this); *this += one(); return o; }\n    ModInt &operator--() { return *this\
    \ -= one(); }\n    ModInt operator--(int) { ModInt o(*this); *this -= one(); return\
    \ o; }\n    friend ModInt operator+(const ModInt &a, const ModInt &b) { return\
    \ ModInt(a) += b; }\n    friend ModInt operator-(const ModInt &a, const ModInt\
    \ &b) { return ModInt(a) -= b; }\n    friend ModInt operator*(const ModInt &a,\
    \ const ModInt &b) { return ModInt(a) *= b; }\n    friend ModInt operator/(const\
    \ ModInt &a, const ModInt &b) { return ModInt(a) /= b; }\n    friend bool operator==(const\
    \ ModInt &a, const ModInt &b) { return a.v_ == b.v_; }\n    friend bool operator!=(const\
    \ ModInt &a, const ModInt &b) { return a.v_ != b.v_; }\n    friend std::istream\
    \ &operator>>(std::istream &a, ModInt &b) { int v; a >> v; b.v_ = safe_mod(v);\
    \ return a; }\n    friend std::ostream &operator<<(std::ostream &a, const ModInt\
    \ &b) { return a << b.val(); }\n};\n// clang-format on\n#line 7 \"test/convolution/bitwise_and_convolution.0.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = ModInt<998244353>;\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ a(1 << n), b(1 << n);\n    for (int i = 0; i < (1 << n); ++i) std::cin >> a[i];\n\
    \    for (int i = 0; i < (1 << n); ++i) std::cin >> b[i];\n    const auto ab =\
    \ bitwise_and_convolution(a, b);\n    for (int i = 0; i < (1 << n); ++i) std::cout\
    \ << ab[i] << ' ';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bitwise_and_convolution\"\
    \n\n#include \"bitwise_conv.hpp\"\n#include \"modint.hpp\"\n#include <iostream>\n\
    #include <vector>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n   \
    \ std::cin.tie(nullptr);\n    using mint = ModInt<998244353>;\n    int n;\n  \
    \  std::cin >> n;\n    std::vector<mint> a(1 << n), b(1 << n);\n    for (int i\
    \ = 0; i < (1 << n); ++i) std::cin >> a[i];\n    for (int i = 0; i < (1 << n);\
    \ ++i) std::cin >> b[i];\n    const auto ab = bitwise_and_convolution(a, b);\n\
    \    for (int i = 0; i < (1 << n); ++i) std::cout << ab[i] << ' ';\n    return\
    \ 0;\n}\n"
  dependsOn:
  - bitwise_conv.hpp
  - sps_fft.hpp
  - subset_conv.hpp
  - modint.hpp
  isVerificationFile: true
  path: test/convolution/bitwise_and_convolution.0.test.cpp
  requiredBy: []
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/convolution/bitwise_and_convolution.0.test.cpp
layout: document
redirect_from:
- /verify/test/convolution/bitwise_and_convolution.0.test.cpp
- /verify/test/convolution/bitwise_and_convolution.0.test.cpp.html
title: test/convolution/bitwise_and_convolution.0.test.cpp
---
