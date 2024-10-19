---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: conv_mod.hpp
    title: conv_mod.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/convolution_mod_1000000007.0.test.cpp
    title: test/convolution/convolution_mod_1000000007.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"modlong.hpp\"\n\n#include <iostream>\n#include <type_traits>\n\
    \ntemplate <unsigned long long Mod, bool Odd = (Mod & 1)>\nclass ModLong;\n\n\
    template <unsigned long long Mod>\nclass ModLong<Mod, true> {\n    using LL  =\
    \ long long;\n    using ULL = unsigned long long;\n\n    static_assert((Mod >>\
    \ 63) == 0, \"`Mod` must less than 2^(63)\");\n    static_assert((Mod & 1) ==\
    \ 1, \"`Mod` must be odd\");\n\n    template <typename Int>\n    static std::enable_if_t<std::is_integral_v<Int>,\
    \ ULL> safe_mod(Int v) {\n        using D = std::common_type_t<Int, LL>;\n   \
    \     return (v %= (LL)Mod) < 0 ? (D)(v + (LL)Mod) : (D)v;\n    }\n\n    static\
    \ ULL norm(LL x) { return x < 0 ? x + (LL)Mod : x; }\n    static ULL norm(ULL\
    \ x) { return x + (Mod & -(x >> 63)); }\n\n    struct PrivateConstructor {};\n\
    \    static inline PrivateConstructor private_constructor{};\n    ModLong(PrivateConstructor,\
    \ ULL v) : v_(v) {}\n\n    ULL v_;\n\n    static constexpr ULL r() {\n       \
    \ ULL t = 2, iv = Mod * (t - Mod * Mod);\n        iv *= t - Mod * iv, iv *= t\
    \ - Mod * iv, iv *= t - Mod * iv;\n        return iv * (t - Mod * iv);\n    }\n\
    \    static constexpr ULL r2() {\n        ULL iv = -Mod % Mod;\n        for (int\
    \ i = 0; i < 64; ++i)\n            if ((iv *= 2) >= Mod) iv -= Mod;\n        return\
    \ iv;\n    }\n\n    static ULL mul_high(ULL x, ULL y) {\n        ULL a = x >>\
    \ 32, b = x & -1U, c = y >> 32, d = y & -1U;\n        ULL ad = a * d, bc = b *\
    \ c;\n        return a * c + (ad >> 32) + (bc >> 32) + (((ad & -1U) + (bc & -1U)\
    \ + (b * d >> 32)) >> 32);\n    }\n    // Montgomery reduction\n    static ULL\
    \ redc_mul(ULL x, ULL y) { return norm(mul_high(x, y) - mul_high(x * y * R, Mod));\
    \ }\n\n    static constexpr ULL R  = r();\n    static constexpr ULL R2 = r2();\n\
    \npublic:\n    static unsigned long long mod() { return Mod; }\n    static ModLong\
    \ from_raw(unsigned long long v) {\n        return ModLong(private_constructor,\
    \ redc_mul(v, R2));\n    }\n    ModLong() : v_() {}\n    template <typename Int,\
    \ typename std::enable_if_t<std::is_signed_v<Int>, int> = 0>\n    ModLong(Int\
    \ v) : v_(redc_mul(safe_mod(v), R2)) {}\n    template <typename Int, typename\
    \ std::enable_if_t<std::is_unsigned_v<Int>, int> = 0>\n    ModLong(Int v) : v_(redc_mul(v\
    \ % Mod, R2)) {}\n    unsigned long long val() const { return norm(-mul_high(v_\
    \ * R, Mod)); }\n\n    ModLong operator-() const { return ModLong(private_constructor,\
    \ v_ == 0 ? v_ : Mod - v_); }\n    ModLong pow(long long e) const {\n        if\
    \ (e < 0) return inv().pow(-e);\n        for (ModLong x(*this), res(from_raw(1));;\
    \ x *= x) {\n            if (e & 1) res *= x;\n            if ((e >>= 1) == 0)\
    \ return res;\n        }\n    }\n    ModLong inv() const {\n        LL x1 = 1,\
    \ x3 = 0, a = val(), b = Mod;\n        while (b) {\n            LL q = a / b,\
    \ x1_old = x1, a_old = a;\n            x1 = x3, x3 = x1_old - x3 * q, a = b, b\
    \ = a_old - b * q;\n        }\n        return from_raw(norm(x1));\n    }\n   \
    \ ModLong div_by_2() const {\n        if (v_ & 1) return ModLong(private_constructor,\
    \ (v_ + Mod) >> 1);\n        return ModLong(private_constructor, v_ >> 1);\n \
    \   }\n\n    ModLong &operator+=(const ModLong &a) {\n        v_ = norm(v_ + a.v_\
    \ - Mod);\n        return *this;\n    }\n    ModLong &operator-=(const ModLong\
    \ &a) {\n        v_ = norm(v_ - a.v_);\n        return *this;\n    }\n    ModLong\
    \ &operator*=(const ModLong &a) {\n        v_ = redc_mul(v_, a.v_);\n        return\
    \ *this;\n    }\n    ModLong &operator/=(const ModLong &a) { return *this *= a.inv();\
    \ }\n\n    friend ModLong operator+(const ModLong &a, const ModLong &b) { return\
    \ ModLong(a) += b; }\n    friend ModLong operator-(const ModLong &a, const ModLong\
    \ &b) { return ModLong(a) -= b; }\n    friend ModLong operator*(const ModLong\
    \ &a, const ModLong &b) { return ModLong(a) *= b; }\n    friend ModLong operator/(const\
    \ ModLong &a, const ModLong &b) { return ModLong(a) /= b; }\n    friend bool operator==(const\
    \ ModLong &a, const ModLong &b) { return a.v_ == b.v_; }\n    friend bool operator!=(const\
    \ ModLong &a, const ModLong &b) { return a.v_ != b.v_; }\n    friend std::istream\
    \ &operator>>(std::istream &a, ModLong &b) {\n        LL v;\n        a >> v;\n\
    \        b.v_ = redc_mul(safe_mod(v), R2);\n        return a;\n    }\n    friend\
    \ std::ostream &operator<<(std::ostream &a, const ModLong &b) { return a << b.val();\
    \ }\n};\n"
  code: "#pragma once\n\n#include <iostream>\n#include <type_traits>\n\ntemplate <unsigned\
    \ long long Mod, bool Odd = (Mod & 1)>\nclass ModLong;\n\ntemplate <unsigned long\
    \ long Mod>\nclass ModLong<Mod, true> {\n    using LL  = long long;\n    using\
    \ ULL = unsigned long long;\n\n    static_assert((Mod >> 63) == 0, \"`Mod` must\
    \ less than 2^(63)\");\n    static_assert((Mod & 1) == 1, \"`Mod` must be odd\"\
    );\n\n    template <typename Int>\n    static std::enable_if_t<std::is_integral_v<Int>,\
    \ ULL> safe_mod(Int v) {\n        using D = std::common_type_t<Int, LL>;\n   \
    \     return (v %= (LL)Mod) < 0 ? (D)(v + (LL)Mod) : (D)v;\n    }\n\n    static\
    \ ULL norm(LL x) { return x < 0 ? x + (LL)Mod : x; }\n    static ULL norm(ULL\
    \ x) { return x + (Mod & -(x >> 63)); }\n\n    struct PrivateConstructor {};\n\
    \    static inline PrivateConstructor private_constructor{};\n    ModLong(PrivateConstructor,\
    \ ULL v) : v_(v) {}\n\n    ULL v_;\n\n    static constexpr ULL r() {\n       \
    \ ULL t = 2, iv = Mod * (t - Mod * Mod);\n        iv *= t - Mod * iv, iv *= t\
    \ - Mod * iv, iv *= t - Mod * iv;\n        return iv * (t - Mod * iv);\n    }\n\
    \    static constexpr ULL r2() {\n        ULL iv = -Mod % Mod;\n        for (int\
    \ i = 0; i < 64; ++i)\n            if ((iv *= 2) >= Mod) iv -= Mod;\n        return\
    \ iv;\n    }\n\n    static ULL mul_high(ULL x, ULL y) {\n        ULL a = x >>\
    \ 32, b = x & -1U, c = y >> 32, d = y & -1U;\n        ULL ad = a * d, bc = b *\
    \ c;\n        return a * c + (ad >> 32) + (bc >> 32) + (((ad & -1U) + (bc & -1U)\
    \ + (b * d >> 32)) >> 32);\n    }\n    // Montgomery reduction\n    static ULL\
    \ redc_mul(ULL x, ULL y) { return norm(mul_high(x, y) - mul_high(x * y * R, Mod));\
    \ }\n\n    static constexpr ULL R  = r();\n    static constexpr ULL R2 = r2();\n\
    \npublic:\n    static unsigned long long mod() { return Mod; }\n    static ModLong\
    \ from_raw(unsigned long long v) {\n        return ModLong(private_constructor,\
    \ redc_mul(v, R2));\n    }\n    ModLong() : v_() {}\n    template <typename Int,\
    \ typename std::enable_if_t<std::is_signed_v<Int>, int> = 0>\n    ModLong(Int\
    \ v) : v_(redc_mul(safe_mod(v), R2)) {}\n    template <typename Int, typename\
    \ std::enable_if_t<std::is_unsigned_v<Int>, int> = 0>\n    ModLong(Int v) : v_(redc_mul(v\
    \ % Mod, R2)) {}\n    unsigned long long val() const { return norm(-mul_high(v_\
    \ * R, Mod)); }\n\n    ModLong operator-() const { return ModLong(private_constructor,\
    \ v_ == 0 ? v_ : Mod - v_); }\n    ModLong pow(long long e) const {\n        if\
    \ (e < 0) return inv().pow(-e);\n        for (ModLong x(*this), res(from_raw(1));;\
    \ x *= x) {\n            if (e & 1) res *= x;\n            if ((e >>= 1) == 0)\
    \ return res;\n        }\n    }\n    ModLong inv() const {\n        LL x1 = 1,\
    \ x3 = 0, a = val(), b = Mod;\n        while (b) {\n            LL q = a / b,\
    \ x1_old = x1, a_old = a;\n            x1 = x3, x3 = x1_old - x3 * q, a = b, b\
    \ = a_old - b * q;\n        }\n        return from_raw(norm(x1));\n    }\n   \
    \ ModLong div_by_2() const {\n        if (v_ & 1) return ModLong(private_constructor,\
    \ (v_ + Mod) >> 1);\n        return ModLong(private_constructor, v_ >> 1);\n \
    \   }\n\n    ModLong &operator+=(const ModLong &a) {\n        v_ = norm(v_ + a.v_\
    \ - Mod);\n        return *this;\n    }\n    ModLong &operator-=(const ModLong\
    \ &a) {\n        v_ = norm(v_ - a.v_);\n        return *this;\n    }\n    ModLong\
    \ &operator*=(const ModLong &a) {\n        v_ = redc_mul(v_, a.v_);\n        return\
    \ *this;\n    }\n    ModLong &operator/=(const ModLong &a) { return *this *= a.inv();\
    \ }\n\n    friend ModLong operator+(const ModLong &a, const ModLong &b) { return\
    \ ModLong(a) += b; }\n    friend ModLong operator-(const ModLong &a, const ModLong\
    \ &b) { return ModLong(a) -= b; }\n    friend ModLong operator*(const ModLong\
    \ &a, const ModLong &b) { return ModLong(a) *= b; }\n    friend ModLong operator/(const\
    \ ModLong &a, const ModLong &b) { return ModLong(a) /= b; }\n    friend bool operator==(const\
    \ ModLong &a, const ModLong &b) { return a.v_ == b.v_; }\n    friend bool operator!=(const\
    \ ModLong &a, const ModLong &b) { return a.v_ != b.v_; }\n    friend std::istream\
    \ &operator>>(std::istream &a, ModLong &b) {\n        LL v;\n        a >> v;\n\
    \        b.v_ = redc_mul(safe_mod(v), R2);\n        return a;\n    }\n    friend\
    \ std::ostream &operator<<(std::ostream &a, const ModLong &b) { return a << b.val();\
    \ }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: modlong.hpp
  requiredBy:
  - conv_mod.hpp
  timestamp: '2024-05-15 00:00:04+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution/convolution_mod_1000000007.0.test.cpp
documentation_of: modlong.hpp
layout: document
redirect_from:
- /library/modlong.hpp
- /library/modlong.hpp.html
title: modlong.hpp
---
