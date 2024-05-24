---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: conv_mod.hpp
    title: conv_mod.hpp
  - icon: ':heavy_check_mark:'
    path: fft.hpp
    title: fft.hpp
  - icon: ':heavy_check_mark:'
    path: modlong.hpp
    title: modlong.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod_1000000007
    links:
    - https://judge.yosupo.jp/problem/convolution_mod_1000000007
  bundledCode: "#line 1 \"test/convolution_mod_1000000007.0.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/convolution_mod_1000000007\"\n\n#line 2 \"\
    conv_mod.hpp\"\n\n#line 2 \"fft.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <iterator>\n#include <memory>\n#include <vector>\n\ntemplate <typename\
    \ Tp>\nclass FftInfo {\n    static Tp least_quadratic_nonresidue() {\n       \
    \ for (int i = 2;; ++i)\n            if (Tp(i).pow((Tp::mod() - 1) / 2) == -1)\
    \ return Tp(i);\n    }\n\n    const int ordlog2_;\n    const Tp zeta_;\n    const\
    \ Tp invzeta_;\n    const Tp imag_;\n    const Tp invimag_;\n\n    mutable std::vector<Tp>\
    \ root_;\n    mutable std::vector<Tp> invroot_;\n\n    FftInfo()\n        : ordlog2_(__builtin_ctzll(Tp::mod()\
    \ - 1)),\n          zeta_(least_quadratic_nonresidue().pow((Tp::mod() - 1) >>\
    \ ordlog2_)),\n          invzeta_(zeta_.inv()), imag_(zeta_.pow(1LL << (ordlog2_\
    \ - 2))), invimag_(-imag_),\n          root_{Tp(1), imag_}, invroot_{Tp(1), invimag_}\
    \ {}\n\npublic:\n    static const FftInfo &get() {\n        static FftInfo info;\n\
    \        return info;\n    }\n\n    Tp imag() const { return imag_; }\n    Tp\
    \ inv_imag() const { return invimag_; }\n    Tp zeta() const { return zeta_; }\n\
    \    Tp inv_zeta() const { return invzeta_; }\n    const std::vector<Tp> &root(int\
    \ n) const {\n        // [0, n)\n        assert((n & (n - 1)) == 0);\n       \
    \ if (const int s = root_.size(); s < n) {\n            root_.resize(n);\n   \
    \         for (int i = __builtin_ctz(s); (1 << i) < n; ++i) {\n              \
    \  const int j = 1 << i;\n                root_[j]    = zeta_.pow(1LL << (ordlog2_\
    \ - i - 2));\n                for (int k = j + 1; k < j * 2; ++k) root_[k] = root_[k\
    \ - j] * root_[j];\n            }\n        }\n        return root_;\n    }\n \
    \   const std::vector<Tp> &inv_root(int n) const {\n        // [0, n)\n      \
    \  assert((n & (n - 1)) == 0);\n        if (const int s = invroot_.size(); s <\
    \ n) {\n            invroot_.resize(n);\n            for (int i = __builtin_ctz(s);\
    \ (1 << i) < n; ++i) {\n                const int j = 1 << i;\n              \
    \  invroot_[j] = invzeta_.pow(1LL << (ordlog2_ - i - 2));\n                for\
    \ (int k = j + 1; k < j * 2; ++k) invroot_[k] = invroot_[k - j] * invroot_[j];\n\
    \            }\n        }\n        return invroot_;\n    }\n};\n\ninline int fft_len(int\
    \ n) {\n    --n;\n    n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8;\n  \
    \  return (n | n >> 16) + 1;\n}\n\ntemplate <typename Iterator>\ninline void fft_n(Iterator\
    \ a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    assert((n & (n - 1)) == 0);\n    for (int j = 0; j < n / 2; ++j) {\n    \
    \    auto u = a[j], v = a[j + n / 2];\n        a[j] = u + v, a[j + n / 2] = u\
    \ - v;\n    }\n    auto &&root = FftInfo<Tp>::get().root(n / 2);\n    for (int\
    \ i = n / 2; i >= 2; i /= 2) {\n        for (int j = 0; j < i / 2; ++j) {\n  \
    \          auto u = a[j], v = a[j + i / 2];\n            a[j] = u + v, a[j + i\
    \ / 2] = u - v;\n        }\n        for (int j = i, m = 1; j < n; j += i, ++m)\n\
    \            for (int k = j; k < j + i / 2; ++k) {\n                auto u = a[k],\
    \ v = a[k + i / 2] * root[m];\n                a[k] = u + v, a[k + i / 2] = u\
    \ - v;\n            }\n    }\n}\n\ntemplate <typename Tp>\ninline void fft(std::vector<Tp>\
    \ &a) {\n    fft_n(a.begin(), a.size());\n}\n\ntemplate <typename Iterator>\n\
    inline void inv_fft_n(Iterator a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    assert((n & (n - 1)) == 0);\n    auto &&root = FftInfo<Tp>::get().inv_root(n\
    \ / 2);\n    for (int i = 2; i < n; i *= 2) {\n        for (int j = 0; j < i /\
    \ 2; ++j) {\n            auto u = a[j], v = a[j + i / 2];\n            a[j] =\
    \ u + v, a[j + i / 2] = u - v;\n        }\n        for (int j = i, m = 1; j <\
    \ n; j += i, ++m)\n            for (int k = j; k < j + i / 2; ++k) {\n       \
    \         auto u = a[k], v = a[k + i / 2];\n                a[k] = u + v, a[k\
    \ + i / 2] = (u - v) * root[m];\n            }\n    }\n    const Tp iv = Tp::mod()\
    \ - Tp::mod() / n;\n    for (int j = 0; j < n / 2; ++j) {\n        auto u = a[j]\
    \ * iv, v = a[j + n / 2] * iv;\n        a[j] = u + v, a[j + n / 2] = u - v;\n\
    \    }\n}\n\ntemplate <typename Tp>\ninline void inv_fft(std::vector<Tp> &a) {\n\
    \    inv_fft_n(a.begin(), a.size());\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ convolution_fft(std::vector<Tp> a, std::vector<Tp> b) {\n    if (a.empty() ||\
    \ b.empty()) return {};\n    const int n   = a.size();\n    const int m   = b.size();\n\
    \    const int len = fft_len(n + m - 1);\n    a.resize(len);\n    b.resize(len);\n\
    \    fft(a);\n    fft(b);\n    for (int i = 0; i < len; ++i) a[i] *= b[i];\n \
    \   inv_fft(a);\n    a.resize(n + m - 1);\n    return a;\n}\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> square_fft(std::vector<Tp> a) {\n    if (a.empty())\
    \ return {};\n    const int n   = a.size();\n    const int len = fft_len(n * 2\
    \ - 1);\n    a.resize(len);\n    fft(a);\n    for (int i = 0; i < len; ++i) a[i]\
    \ *= a[i];\n    inv_fft(a);\n    a.resize(n * 2 - 1);\n    return a;\n}\n\ntemplate\
    \ <typename Tp>\ninline std::vector<Tp> convolution_naive(const std::vector<Tp>\
    \ &a, const std::vector<Tp> &b) {\n    if (a.empty() || b.empty()) return {};\n\
    \    const int n = a.size();\n    const int m = b.size();\n    std::vector<Tp>\
    \ res(n + m - 1);\n    for (int i = 0; i < n; ++i)\n        for (int j = 0; j\
    \ < m; ++j) res[i + j] += a[i] * b[j];\n    return res;\n}\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> convolution(const std::vector<Tp> &a, const std::vector<Tp>\
    \ &b) {\n    if (std::min(a.size(), b.size()) < 60) return convolution_naive(a,\
    \ b);\n    if (std::addressof(a) == std::addressof(b)) return square_fft(a);\n\
    \    return convolution_fft(a, b);\n}\n#line 2 \"modlong.hpp\"\n\n#include <iostream>\n\
    #include <type_traits>\n\ntemplate <unsigned long long Mod, bool Odd = (Mod &\
    \ 1)>\nclass ModLong;\n\ntemplate <unsigned long long Mod>\nclass ModLong<Mod,\
    \ true> {\n    using LL  = long long;\n    using ULL = unsigned long long;\n\n\
    \    static_assert((Mod >> 63) == 0, \"`Mod` must less than 2^(63)\");\n    static_assert((Mod\
    \ & 1) == 1, \"`Mod` must be odd\");\n\n    template <typename Int>\n    static\
    \ std::enable_if_t<std::is_integral_v<Int>, ULL> safe_mod(Int v) {\n        using\
    \ D = std::common_type_t<Int, LL>;\n        return (v %= (LL)Mod) < 0 ? (D)(v\
    \ + (LL)Mod) : (D)v;\n    }\n\n    static ULL norm(LL x) { return x < 0 ? x +\
    \ (LL)Mod : x; }\n    static ULL norm(ULL x) { return x + (Mod & -(x >> 63));\
    \ }\n\n    struct PrivateConstructor {};\n    static inline PrivateConstructor\
    \ private_constructor{};\n    ModLong(PrivateConstructor, ULL v) : v_(v) {}\n\n\
    \    ULL v_;\n\n    static constexpr ULL r() {\n        ULL t = 2, iv = Mod *\
    \ (t - Mod * Mod);\n        iv *= t - Mod * iv, iv *= t - Mod * iv, iv *= t -\
    \ Mod * iv;\n        return iv * (t - Mod * iv);\n    }\n    static constexpr\
    \ ULL r2() {\n        ULL iv = -Mod % Mod;\n        for (int i = 0; i < 64; ++i)\n\
    \            if ((iv *= 2) >= Mod) iv -= Mod;\n        return iv;\n    }\n\n \
    \   static ULL mul_high(ULL x, ULL y) {\n        ULL a = x >> 32, b = x & -1U,\
    \ c = y >> 32, d = y & -1U;\n        ULL ad = a * d, bc = b * c;\n        return\
    \ a * c + (ad >> 32) + (bc >> 32) + (((ad & -1U) + (bc & -1U) + (b * d >> 32))\
    \ >> 32);\n    }\n    // Montgomery reduction\n    static ULL redc_mul(ULL x,\
    \ ULL y) { return norm(mul_high(x, y) - mul_high(x * y * R, Mod)); }\n\n    static\
    \ constexpr ULL R  = r();\n    static constexpr ULL R2 = r2();\n\npublic:\n  \
    \  static unsigned long long mod() { return Mod; }\n    static ModLong from_raw(unsigned\
    \ long long v) {\n        return ModLong(private_constructor, redc_mul(v, R2));\n\
    \    }\n    ModLong() : v_() {}\n    template <typename Int, typename std::enable_if_t<std::is_signed_v<Int>,\
    \ int> = 0>\n    ModLong(Int v) : v_(redc_mul(safe_mod(v), R2)) {}\n    template\
    \ <typename Int, typename std::enable_if_t<std::is_unsigned_v<Int>, int> = 0>\n\
    \    ModLong(Int v) : v_(redc_mul(v % Mod, R2)) {}\n    unsigned long long val()\
    \ const { return norm(-mul_high(v_ * R, Mod)); }\n\n    ModLong operator-() const\
    \ { return ModLong(private_constructor, v_ == 0 ? v_ : Mod - v_); }\n    ModLong\
    \ pow(long long e) const {\n        if (e < 0) return inv().pow(-e);\n       \
    \ for (ModLong x(*this), res(from_raw(1));; x *= x) {\n            if (e & 1)\
    \ res *= x;\n            if ((e >>= 1) == 0) return res;\n        }\n    }\n \
    \   ModLong inv() const {\n        LL x1 = 1, x3 = 0, a = val(), b = Mod;\n  \
    \      while (b) {\n            LL q = a / b, x1_old = x1, a_old = a;\n      \
    \      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\n        }\n \
    \       return from_raw(norm(x1));\n    }\n    ModLong div_by_2() const {\n  \
    \      if (v_ & 1) return ModLong(private_constructor, (v_ + Mod) >> 1);\n   \
    \     return ModLong(private_constructor, v_ >> 1);\n    }\n\n    ModLong &operator+=(const\
    \ ModLong &a) {\n        v_ = norm(v_ + a.v_ - Mod);\n        return *this;\n\
    \    }\n    ModLong &operator-=(const ModLong &a) {\n        v_ = norm(v_ - a.v_);\n\
    \        return *this;\n    }\n    ModLong &operator*=(const ModLong &a) {\n \
    \       v_ = redc_mul(v_, a.v_);\n        return *this;\n    }\n    ModLong &operator/=(const\
    \ ModLong &a) { return *this *= a.inv(); }\n\n    friend ModLong operator+(const\
    \ ModLong &a, const ModLong &b) { return ModLong(a) += b; }\n    friend ModLong\
    \ operator-(const ModLong &a, const ModLong &b) { return ModLong(a) -= b; }\n\
    \    friend ModLong operator*(const ModLong &a, const ModLong &b) { return ModLong(a)\
    \ *= b; }\n    friend ModLong operator/(const ModLong &a, const ModLong &b) {\
    \ return ModLong(a) /= b; }\n    friend bool operator==(const ModLong &a, const\
    \ ModLong &b) { return a.v_ == b.v_; }\n    friend bool operator!=(const ModLong\
    \ &a, const ModLong &b) { return a.v_ != b.v_; }\n    friend std::istream &operator>>(std::istream\
    \ &a, ModLong &b) {\n        LL v;\n        a >> v;\n        b.v_ = redc_mul(safe_mod(v),\
    \ R2);\n        return a;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &a, const ModLong &b) { return a << b.val(); }\n};\n#line 6 \"conv_mod.hpp\"\
    \n\ninline std::vector<int> convolution_mod(const std::vector<int> &a, const std::vector<int>\
    \ &b,\n                                        int modular) {\n    using mint0\
    \ = ModLong<0x3F9A000000000001>;\n    using mint1 = ModLong<0x3FC6000000000001>;\n\
    \    const auto res0 =\n        convolution(std::vector<mint0>(a.begin(), a.end()),\
    \ std::vector<mint0>(b.begin(), b.end()));\n    const auto res1 =\n        convolution(std::vector<mint1>(a.begin(),\
    \ a.end()), std::vector<mint1>(b.begin(), b.end()));\n    const int n = res0.size();\n\
    \    std::vector<int> res(n);\n    const mint0 im1 = mint0(mint1::mod()).inv();\n\
    \    const int m1    = mint1::mod() % modular;\n    for (int i = 0; i < n; ++i)\
    \ {\n        const mint0 k1 = (res0[i] - res1[i].val()) * im1;\n        res[i]\
    \         = (k1.val() % modular * m1 + res1[i].val()) % modular;\n    }\n    return\
    \ res;\n}\n#line 6 \"test/convolution_mod_1000000007.0.test.cpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n, m;\n    std::cin >> n >> m;\n    std::vector<int> f(n), g(m);\n    for (int\
    \ i = 0; i < n; ++i) std::cin >> f[i];\n    for (int i = 0; i < m; ++i) std::cin\
    \ >> g[i];\n    const auto fg = convolution_mod(f, g, 1000000007);\n    for (int\
    \ i = 0; i < (int)fg.size(); ++i) std::cout << fg[i] << ' ';\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod_1000000007\"\
    \n\n#include \"conv_mod.hpp\"\n#include <iostream>\n#include <vector>\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n, m;\n    std::cin >> n >> m;\n    std::vector<int> f(n), g(m);\n    for (int\
    \ i = 0; i < n; ++i) std::cin >> f[i];\n    for (int i = 0; i < m; ++i) std::cin\
    \ >> g[i];\n    const auto fg = convolution_mod(f, g, 1000000007);\n    for (int\
    \ i = 0; i < (int)fg.size(); ++i) std::cout << fg[i] << ' ';\n    return 0;\n\
    }\n"
  dependsOn:
  - conv_mod.hpp
  - fft.hpp
  - modlong.hpp
  isVerificationFile: true
  path: test/convolution_mod_1000000007.0.test.cpp
  requiredBy: []
  timestamp: '2024-05-17 19:15:49+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/convolution_mod_1000000007.0.test.cpp
layout: document
redirect_from:
- /verify/test/convolution_mod_1000000007.0.test.cpp
- /verify/test/convolution_mod_1000000007.0.test.cpp.html
title: test/convolution_mod_1000000007.0.test.cpp
---