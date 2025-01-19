---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fft.hpp
    title: FFT
  - icon: ':heavy_check_mark:'
    path: modlong.hpp
    title: modlong.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/convolution_mod_1000000007.0.test.cpp
    title: test/convolution/convolution_mod_1000000007.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"conv_mod.hpp\"\n\n#line 2 \"fft.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iterator>\n#include <memory>\n#include <vector>\n\
    \ntemplate<typename Tp> class FftInfo {\n    static Tp least_quadratic_nonresidue()\
    \ {\n        for (int i = 2;; ++i)\n            if (Tp(i).pow((Tp::mod() - 1)\
    \ / 2) == -1) return Tp(i);\n    }\n\n    const int ordlog2_;\n    const Tp zeta_;\n\
    \    const Tp invzeta_;\n    const Tp imag_;\n    const Tp invimag_;\n\n    mutable\
    \ std::vector<Tp> root_;\n    mutable std::vector<Tp> invroot_;\n\n    FftInfo()\n\
    \        : ordlog2_(__builtin_ctzll(Tp::mod() - 1)),\n          zeta_(least_quadratic_nonresidue().pow((Tp::mod()\
    \ - 1) >> ordlog2_)),\n          invzeta_(zeta_.inv()), imag_(zeta_.pow(1LL <<\
    \ (ordlog2_ - 2))), invimag_(-imag_),\n          root_{Tp(1), imag_}, invroot_{Tp(1),\
    \ invimag_} {}\n\npublic:\n    static const FftInfo &get() {\n        static FftInfo\
    \ info;\n        return info;\n    }\n\n    Tp imag() const { return imag_; }\n\
    \    Tp inv_imag() const { return invimag_; }\n    Tp zeta() const { return zeta_;\
    \ }\n    Tp inv_zeta() const { return invzeta_; }\n    const std::vector<Tp> &root(int\
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
    \  return (n | n >> 16) + 1;\n}\n\nnamespace detail {\n\ntemplate<typename Iterator>\
    \ inline void\nbutterfly_n(Iterator a, int n,\n            const std::vector<typename\
    \ std::iterator_traits<Iterator>::value_type> &root) {\n    assert(n > 0);\n \
    \   assert((n & (n - 1)) == 0);\n    const int bn = __builtin_ctz(n);\n    if\
    \ (bn & 1) {\n        for (int i = 0; i < n / 2; ++i) {\n            const auto\
    \ a0 = a[i], a1 = a[i + n / 2];\n            a[i] = a0 + a1, a[i + n / 2] = a0\
    \ - a1;\n        }\n    }\n    for (int i = n >> (bn & 1); i >= 4; i /= 4) {\n\
    \        const int i4 = i / 4;\n        for (int k = 0; k < i4; ++k) {\n     \
    \       const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];\n            const\
    \ auto a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];\n            const auto a02p =\
    \ a0 + a2, a02m = a0 - a2;\n            const auto a13p = a1 + a3, a13m = (a1\
    \ - a3) * root[1];\n            a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p\
    \ - a13p;\n            a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;\n\
    \        }\n        for (int j = i, m = 2; j < n; j += i, m += 2) {\n        \
    \    const auto r = root[m], r2 = r * r, r3 = r2 * r;\n            for (int k\
    \ = j; k < j + i4; ++k) {\n                const auto a0 = a[k + i4 * 0], a1 =\
    \ a[k + i4 * 1] * r;\n                const auto a2 = a[k + i4 * 2] * r2, a3 =\
    \ a[k + i4 * 3] * r3;\n                const auto a02p = a0 + a2, a02m = a0 -\
    \ a2;\n                const auto a13p = a1 + a3, a13m = (a1 - a3) * root[1];\n\
    \                a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p - a13p;\n \
    \               a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;\n  \
    \          }\n        }\n    }\n}\n\ntemplate<typename Iterator> inline void\n\
    inv_butterfly_n(Iterator a, int n,\n                const std::vector<typename\
    \ std::iterator_traits<Iterator>::value_type> &root) {\n    assert(n > 0);\n \
    \   assert((n & (n - 1)) == 0);\n    const int bn = __builtin_ctz(n);\n    for\
    \ (int i = 4; i <= (n >> (bn & 1)); i *= 4) {\n        const int i4 = i / 4;\n\
    \        for (int k = 0; k < i4; ++k) {\n            const auto a0 = a[k + i4\
    \ * 0], a1 = a[k + i4 * 1];\n            const auto a2 = a[k + i4 * 2], a3 = a[k\
    \ + i4 * 3];\n            const auto a01p = a0 + a1, a01m = a0 - a1;\n       \
    \     const auto a23p = a2 + a3, a23m = (a2 - a3) * root[1];\n            a[k\
    \ + i4 * 0] = a01p + a23p, a[k + i4 * 1] = a01m + a23m;\n            a[k + i4\
    \ * 2] = a01p - a23p, a[k + i4 * 3] = a01m - a23m;\n        }\n        for (int\
    \ j = i, m = 2; j < n; j += i, m += 2) {\n            const auto r = root[m],\
    \ r2 = r * r, r3 = r2 * r;\n            for (int k = j; k < j + i4; ++k) {\n \
    \               const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];\n         \
    \       const auto a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];\n                const\
    \ auto a01p = a0 + a1, a01m = a0 - a1;\n                const auto a23p = a2 +\
    \ a3, a23m = (a2 - a3) * root[1];\n                a[k + i4 * 0] = a01p + a23p,\
    \ a[k + i4 * 1] = (a01m + a23m) * r;\n                a[k + i4 * 2] = (a01p -\
    \ a23p) * r2, a[k + i4 * 3] = (a01m - a23m) * r3;\n            }\n        }\n\
    \    }\n    if (bn & 1) {\n        for (int i = 0; i < n / 2; ++i) {\n       \
    \     const auto a0 = a[i], a1 = a[i + n / 2];\n            a[i] = a0 + a1, a[i\
    \ + n / 2] = a0 - a1;\n        }\n    }\n}\n\n} // namespace detail\n\n// FFT_n:\
    \ A(x) |-> bit-reversed order of [A(1), A(zeta_n), ..., A(zeta_n^(n-1))]\ntemplate<typename\
    \ Iterator> inline void fft_n(Iterator a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    detail::butterfly_n(a, n, FftInfo<Tp>::get().root(n / 2));\n}\n\ntemplate<typename\
    \ Tp> inline void fft(std::vector<Tp> &a) { fft_n(a.begin(), a.size()); }\n\n\
    // IFFT_n: bit-reversed order of [A(1), A(zeta_n), ..., A(zeta_n^(n-1))] |-> A(x)\n\
    template<typename Iterator> inline void inv_fft_n(Iterator a, int n) {\n    using\
    \ Tp = typename std::iterator_traits<Iterator>::value_type;\n    detail::inv_butterfly_n(a,\
    \ n, FftInfo<Tp>::get().inv_root(n / 2));\n    const Tp iv = Tp::mod() - (Tp::mod()\
    \ - 1) / n;\n    for (int i = 0; i < n; ++i) a[i] *= iv;\n}\n\ntemplate<typename\
    \ Tp> inline void inv_fft(std::vector<Tp> &a) { inv_fft_n(a.begin(), a.size());\
    \ }\n\n// IFFT_n^T: A(x) |-> 1/n FFT_n((x^n A(x^(-1))) mod (x^n - 1))\ntemplate<typename\
    \ Iterator> inline void transposed_inv_fft_n(Iterator a, int n) {\n    using Tp\
    \    = typename std::iterator_traits<Iterator>::value_type;\n    const Tp iv =\
    \ Tp::mod() - (Tp::mod() - 1) / n;\n    for (int i = 0; i < n; ++i) a[i] *= iv;\n\
    \    detail::butterfly_n(a, n, FftInfo<Tp>::get().inv_root(n / 2));\n}\n\ntemplate<typename\
    \ Tp> inline void transposed_inv_fft(std::vector<Tp> &a) {\n    transposed_inv_fft_n(a.begin(),\
    \ a.size());\n}\n\n// FFT_n^T : FFT_n((x^n A(x^(-1))) mod (x^n - 1)) |-> n A(x)\n\
    template<typename Iterator> inline void transposed_fft_n(Iterator a, int n) {\n\
    \    using Tp = typename std::iterator_traits<Iterator>::value_type;\n    detail::inv_butterfly_n(a,\
    \ n, FftInfo<Tp>::get().root(n / 2));\n}\n\ntemplate<typename Tp> inline void\
    \ transposed_fft(std::vector<Tp> &a) {\n    transposed_fft_n(a.begin(), a.size());\n\
    }\n\ntemplate<typename Tp> inline std::vector<Tp> convolution_fft(std::vector<Tp>\
    \ a, std::vector<Tp> b) {\n    if (a.empty() || b.empty()) return {};\n    const\
    \ int n   = a.size();\n    const int m   = b.size();\n    const int len = fft_len(n\
    \ + m - 1);\n    a.resize(len);\n    b.resize(len);\n    fft(a);\n    fft(b);\n\
    \    for (int i = 0; i < len; ++i) a[i] *= b[i];\n    inv_fft(a);\n    a.resize(n\
    \ + m - 1);\n    return a;\n}\n\ntemplate<typename Tp> inline std::vector<Tp>\
    \ square_fft(std::vector<Tp> a) {\n    if (a.empty()) return {};\n    const int\
    \ n   = a.size();\n    const int len = fft_len(n * 2 - 1);\n    a.resize(len);\n\
    \    fft(a);\n    for (int i = 0; i < len; ++i) a[i] *= a[i];\n    inv_fft(a);\n\
    \    a.resize(n * 2 - 1);\n    return a;\n}\n\ntemplate<typename Tp>\ninline std::vector<Tp>\
    \ convolution_naive(const std::vector<Tp> &a, const std::vector<Tp> &b) {\n  \
    \  if (a.empty() || b.empty()) return {};\n    const int n = a.size();\n    const\
    \ int m = b.size();\n    std::vector<Tp> res(n + m - 1);\n    for (int i = 0;\
    \ i < n; ++i)\n        for (int j = 0; j < m; ++j) res[i + j] += a[i] * b[j];\n\
    \    return res;\n}\n\ntemplate<typename Tp>\ninline std::vector<Tp> convolution(const\
    \ std::vector<Tp> &a, const std::vector<Tp> &b) {\n    if (std::min(a.size(),\
    \ b.size()) < 60) return convolution_naive(a, b);\n    if (std::addressof(a) ==\
    \ std::addressof(b)) return square_fft(a);\n    return convolution_fft(a, b);\n\
    }\n#line 2 \"modlong.hpp\"\n\n#include <iostream>\n#include <type_traits>\n\n\
    template<unsigned long long Mod, bool Odd = (Mod & 1)> class ModLong;\n\n// clang-format\
    \ off\ntemplate<unsigned long long Mod> class ModLong<Mod, true> {\n    using\
    \ LL  = long long;\n    using ULL = unsigned long long;\n\n    static_assert((Mod\
    \ >> 63) == 0, \"`Mod` must less than 2^(63)\");\n    static_assert((Mod & 1)\
    \ == 1, \"`Mod` must be odd\");\n\n    template<typename Int> static std::enable_if_t<std::is_integral_v<Int>,\
    \ ULL> safe_mod(Int v) { using D = std::common_type_t<Int, LL>; return (v %= (LL)Mod)\
    \ < 0 ? (D)(v + (LL)Mod) : (D)v; }\n    static ULL norm(LL x) { return x < 0 ?\
    \ x + (LL)Mod : x; }\n    static ULL norm(ULL x) { return x + (Mod & -(x >> 63));\
    \ }\n    struct PrivateConstructor {} static inline private_constructor;\n   \
    \ ModLong(PrivateConstructor, ULL v) : v_(v) {}\n    ULL v_;\n    static constexpr\
    \ ULL r() { ULL t = 2, iv = Mod * (t - Mod * Mod); iv *= t - Mod * iv, iv *= t\
    \ - Mod * iv, iv *= t - Mod * iv; return iv * (t - Mod * iv); }\n    static constexpr\
    \ ULL r2() { ULL iv = -Mod % Mod; for (int i = 0; i < 64; ++i) if ((iv *= 2) >=\
    \ Mod) iv -= Mod; return iv; }\n    static ULL mul_high(ULL x, ULL y) { const\
    \ ULL a = x >> 32, b = x & -1U, c = y >> 32, d = y & -1U, ad = a * d, bc = b *\
    \ c; return a * c + (ad >> 32) + (bc >> 32) + (((ad & -1U) + (bc & -1U) + (b *\
    \ d >> 32)) >> 32); }\n    // Montgomery reduction\n    static ULL redc_mul(ULL\
    \ x, ULL y) { return norm(mul_high(x, y) - mul_high(x * y * R, Mod)); }\n    static\
    \ constexpr ULL R  = r();\n    static constexpr ULL R2 = r2();\n\npublic:\n  \
    \  static unsigned long long mod() { return Mod; }\n    static ModLong from_raw(unsigned\
    \ long long v) { return ModLong(private_constructor, redc_mul(v, R2)); }\n   \
    \ static ModLong zero() { return ModLong(private_constructor, 0); }\n    static\
    \ ModLong one() { return from_raw(1); }\n    bool is_zero() const { return *this\
    \ == zero(); }\n    bool is_one() const { return *this == one(); }\n    ModLong()\
    \ : v_() {}\n    template<typename Int, typename std::enable_if_t<std::is_signed_v<Int>,\
    \ int> = 0> ModLong(Int v) : v_(redc_mul(safe_mod(v), R2)) {}\n    template<typename\
    \ Int, typename std::enable_if_t<std::is_unsigned_v<Int>, int> = 0> ModLong(Int\
    \ v) : v_(redc_mul(v % Mod, R2)) {}\n    unsigned long long val() const { return\
    \ norm(-mul_high(v_ * R, Mod)); }\n    ModLong operator-() const { return ModLong(private_constructor,\
    \ v_ == 0 ? v_ : Mod - v_); }\n    ModLong pow(long long e) const { if (e < 0)\
    \ return inv().pow(-e); for (ModLong x(*this), res(from_raw(1));; x *= x) { if\
    \ (e & 1) res *= x; if ((e >>= 1) == 0) return res; }}\n    ModLong inv() const\
    \ { LL x1 = 1, x3 = 0, a = val(), b = Mod; while (b) { const LL q = a / b, x1_old\
    \ = x1, a_old = a; x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q; }\
    \ return from_raw(norm(x1)); }\n    ModLong div_by_2() const { if (v_ & 1) return\
    \ ModLong(private_constructor, (v_ + Mod) >> 1); return ModLong(private_constructor,\
    \ v_ >> 1); }\n    ModLong &operator+=(const ModLong &a) { v_ = norm(v_ + a.v_\
    \ - Mod); return *this; }\n    ModLong &operator-=(const ModLong &a) { v_ = norm(v_\
    \ - a.v_); return *this; }\n    ModLong &operator*=(const ModLong &a) { v_ = redc_mul(v_,\
    \ a.v_); return *this; }\n    ModLong &operator/=(const ModLong &a) { return *this\
    \ *= a.inv(); }\n    ModLong &operator++() { return *this += one(); }\n    ModLong\
    \ operator++(int) { ModLong o(*this); *this += one(); return o; }\n    ModLong\
    \ &operator--() { return *this -= one(); }\n    ModLong operator--(int) { ModLong\
    \ o(*this); *this -= one(); return o; }\n    friend ModLong operator+(const ModLong\
    \ &a, const ModLong &b) { return ModLong(a) += b; }\n    friend ModLong operator-(const\
    \ ModLong &a, const ModLong &b) { return ModLong(a) -= b; }\n    friend ModLong\
    \ operator*(const ModLong &a, const ModLong &b) { return ModLong(a) *= b; }\n\
    \    friend ModLong operator/(const ModLong &a, const ModLong &b) { return ModLong(a)\
    \ /= b; }\n    friend bool operator==(const ModLong &a, const ModLong &b) { return\
    \ a.v_ == b.v_; }\n    friend bool operator!=(const ModLong &a, const ModLong\
    \ &b) { return a.v_ != b.v_; }\n    friend std::istream &operator>>(std::istream\
    \ &a, ModLong &b) { LL v; a >> v; b.v_ = redc_mul(safe_mod(v), R2); return a;\
    \ }\n    friend std::ostream &operator<<(std::ostream &a, const ModLong &b) {\
    \ return a << b.val(); }\n};\n// clang-format on\n#line 6 \"conv_mod.hpp\"\n\n\
    inline std::vector<int> convolution_mod(const std::vector<int> &a, const std::vector<int>\
    \ &b,\n                                        int modular) {\n    using mint0\
    \ = ModLong<0x3F9A000000000001>;\n    using mint1 = ModLong<0x3FC6000000000001>;\n\
    \    const auto res0 =\n        convolution(std::vector<mint0>(a.begin(), a.end()),\
    \ std::vector<mint0>(b.begin(), b.end()));\n    const auto res1 =\n        convolution(std::vector<mint1>(a.begin(),\
    \ a.end()), std::vector<mint1>(b.begin(), b.end()));\n    const int n = res0.size();\n\
    \    std::vector<int> res(n);\n    const mint0 im1 = mint0(mint1::mod()).inv();\n\
    \    const int m1    = mint1::mod() % modular;\n    for (int i = 0; i < n; ++i)\
    \ {\n        const mint0 k1 = (res0[i] - res1[i].val()) * im1;\n        res[i]\
    \         = (k1.val() % modular * m1 + res1[i].val()) % modular;\n    }\n    return\
    \ res;\n}\n"
  code: "#pragma once\n\n#include \"fft.hpp\"\n#include \"modlong.hpp\"\n#include\
    \ <vector>\n\ninline std::vector<int> convolution_mod(const std::vector<int> &a,\
    \ const std::vector<int> &b,\n                                        int modular)\
    \ {\n    using mint0 = ModLong<0x3F9A000000000001>;\n    using mint1 = ModLong<0x3FC6000000000001>;\n\
    \    const auto res0 =\n        convolution(std::vector<mint0>(a.begin(), a.end()),\
    \ std::vector<mint0>(b.begin(), b.end()));\n    const auto res1 =\n        convolution(std::vector<mint1>(a.begin(),\
    \ a.end()), std::vector<mint1>(b.begin(), b.end()));\n    const int n = res0.size();\n\
    \    std::vector<int> res(n);\n    const mint0 im1 = mint0(mint1::mod()).inv();\n\
    \    const int m1    = mint1::mod() % modular;\n    for (int i = 0; i < n; ++i)\
    \ {\n        const mint0 k1 = (res0[i] - res1[i].val()) * im1;\n        res[i]\
    \         = (k1.val() % modular * m1 + res1[i].val()) % modular;\n    }\n    return\
    \ res;\n}\n"
  dependsOn:
  - fft.hpp
  - modlong.hpp
  isVerificationFile: false
  path: conv_mod.hpp
  requiredBy: []
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution/convolution_mod_1000000007.0.test.cpp
documentation_of: conv_mod.hpp
layout: document
redirect_from:
- /library/conv_mod.hpp
- /library/conv_mod.hpp.html
title: conv_mod.hpp
---
