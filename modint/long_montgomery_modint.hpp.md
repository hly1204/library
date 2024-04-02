---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/binomial_convolution.hpp
    title: Binomial Convolution (in $\mathbb{Z} / m \mathbb{Z}$)
  - icon: ':heavy_check_mark:'
    path: math/convolution_mod.hpp
    title: Convolution (in $\mathbb{Z} / m \mathbb{Z} \lbrack z \rbrack$)
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
    title: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp
    title: remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"modint/long_montgomery_modint.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
    \n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 5 \"modint/long_montgomery_modint.hpp\"\n\n\
    #ifdef LIB_DEBUG\n  #include <stdexcept>\n#endif\n#include <cstdint>\n#include\
    \ <iostream>\n#include <type_traits>\n\nLIB_BEGIN\n\ntemplate <std::uint64_t ModT>\n\
    class montgomery_modint63 {\n  using u32 = std::uint32_t;\n  using i64 = std::int64_t;\n\
    \  using u64 = std::uint64_t;\n\n  u64 v_{};\n\n  static constexpr u64 get_r()\
    \ {\n    u64 t = 2, iv = MOD * (t - MOD * MOD);\n    iv *= t - MOD * iv, iv *=\
    \ t - MOD * iv, iv *= t - MOD * iv;\n    return iv * (t - MOD * iv);\n  }\n  static\
    \ constexpr u64 get_r2() {\n    u64 iv = -MOD % MOD;\n    for (int i = 0; i !=\
    \ 64; ++i)\n      if ((iv <<= 1) >= MOD) iv -= MOD;\n    return iv;\n  }\n  static\
    \ constexpr u64 mul_high(u64 x, u64 y) {\n    u64 a = x >> 32, b = static_cast<u32>(x),\
    \ c = y >> 32, d = static_cast<u32>(y), ad = a * d,\n        bc = b * c;\n   \
    \ return a * c + (ad >> 32) + (bc >> 32) +\n           (((ad & 0xFFFFFFFF) + (bc\
    \ & 0xFFFFFFFF) + (b * d >> 32)) >> 32);\n  }\n  static constexpr u64 redc_mul(u64\
    \ x, u64 y) {\n    u64 res = mul_high(x, y) - mul_high(x * y * R, MOD);\n    return\
    \ res + (MOD & -(res >> 63));\n  }\n  static constexpr u64 norm(i64 x) { return\
    \ x + (MOD & -(x < 0)); }\n\n  static constexpr u64 MOD  = ModT;\n  static constexpr\
    \ u64 R    = get_r();\n  static constexpr u64 R2   = get_r2();\n  static constexpr\
    \ i64 SMOD = static_cast<i64>(MOD);\n\n  static_assert(MOD & 1);\n  static_assert(R\
    \ * MOD == 1);\n  static_assert((MOD >> 63) == 0);\n  static_assert(MOD != 1);\n\
    \npublic:\n  static constexpr u64 mod() { return MOD; }\n  static constexpr i64\
    \ smod() { return SMOD; }\n  constexpr montgomery_modint63() {}\n  template <typename\
    \ IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>\n  constexpr montgomery_modint63(IntT\
    \ v) : v_(redc_mul(norm(v % SMOD), R2)) {}\n  constexpr u64 val() const {\n  \
    \  u64 res = -mul_high(v_ * R, MOD);\n    return res + (MOD & -(res >> 63));\n\
    \  }\n  constexpr i64 sval() const { return val(); }\n  constexpr bool is_zero()\
    \ const { return v_ == 0; }\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>,\
    \ int> = 0>\n  explicit constexpr operator IntT() const {\n    return static_cast<IntT>(val());\n\
    \  }\n  constexpr montgomery_modint63 operator-() const {\n    montgomery_modint63\
    \ res;\n    res.v_ = (MOD & -(v_ != 0)) - v_;\n    return res;\n  }\n  constexpr\
    \ montgomery_modint63 inv() const {\n    i64 x1 = 1, x3 = 0, a = sval(), b = SMOD;\n\
    \    while (b != 0) {\n      i64 q = a / b, x1_old = x1, a_old = a;\n      x1\
    \ = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\n    }\n#ifdef LIB_DEBUG\n\
    \    if (a != 1) throw std::runtime_error(\"modular inverse error\");\n#endif\n\
    \    return montgomery_modint63(x1);\n  }\n  constexpr montgomery_modint63 &operator+=(const\
    \ montgomery_modint63 &rhs) {\n    v_ += rhs.v_ - MOD, v_ += MOD & -(v_ >> 63);\n\
    \    return *this;\n  }\n  constexpr montgomery_modint63 &operator-=(const montgomery_modint63\
    \ &rhs) {\n    v_ -= rhs.v_, v_ += MOD & -(v_ >> 63);\n    return *this;\n  }\n\
    \  constexpr montgomery_modint63 &operator*=(const montgomery_modint63 &rhs) {\n\
    \    v_ = redc_mul(v_, rhs.v_);\n    return *this;\n  }\n  constexpr montgomery_modint63\
    \ &operator/=(const montgomery_modint63 &rhs) {\n    return operator*=(rhs.inv());\n\
    \  }\n  constexpr montgomery_modint63 pow(u64 e) const {\n    for (montgomery_modint63\
    \ res(1), x(*this);; x *= x) {\n      if (e & 1) res *= x;\n      if ((e >>= 1)\
    \ == 0) return res;\n    }\n  }\n  constexpr void swap(montgomery_modint63 &rhs)\
    \ {\n    auto v = v_;\n    v_ = rhs.v_, rhs.v_ = v;\n  }\n  friend constexpr montgomery_modint63\
    \ operator+(const montgomery_modint63 &lhs,\n                                \
    \                 const montgomery_modint63 &rhs) {\n    return montgomery_modint63(lhs)\
    \ += rhs;\n  }\n  friend constexpr montgomery_modint63 operator-(const montgomery_modint63\
    \ &lhs,\n                                                 const montgomery_modint63\
    \ &rhs) {\n    return montgomery_modint63(lhs) -= rhs;\n  }\n  friend constexpr\
    \ montgomery_modint63 operator*(const montgomery_modint63 &lhs,\n            \
    \                                     const montgomery_modint63 &rhs) {\n    return\
    \ montgomery_modint63(lhs) *= rhs;\n  }\n  friend constexpr montgomery_modint63\
    \ operator/(const montgomery_modint63 &lhs,\n                                \
    \                 const montgomery_modint63 &rhs) {\n    return montgomery_modint63(lhs)\
    \ /= rhs;\n  }\n  friend constexpr bool operator==(const montgomery_modint63 &lhs,\
    \ const montgomery_modint63 &rhs) {\n    return lhs.v_ == rhs.v_;\n  }\n  friend\
    \ constexpr bool operator!=(const montgomery_modint63 &lhs, const montgomery_modint63\
    \ &rhs) {\n    return lhs.v_ != rhs.v_;\n  }\n  friend std::istream &operator>>(std::istream\
    \ &is, montgomery_modint63 &rhs) {\n    i64 x;\n    is >> x;\n    rhs = montgomery_modint63(x);\n\
    \    return is;\n  }\n  friend std::ostream &operator<<(std::ostream &os, const\
    \ montgomery_modint63 &rhs) {\n    return os << rhs.val();\n  }\n};\n\ntemplate\
    \ <std::uint64_t ModT>\nusing mm63 = montgomery_modint63<ModT>;\n\nLIB_END\n\n\
    \n"
  code: "#ifndef LONG_MONTGOMERY_MODINT_HPP\n#define LONG_MONTGOMERY_MODINT_HPP\n\n\
    #include \"../common.hpp\"\n\n#ifdef LIB_DEBUG\n  #include <stdexcept>\n#endif\n\
    #include <cstdint>\n#include <iostream>\n#include <type_traits>\n\nLIB_BEGIN\n\
    \ntemplate <std::uint64_t ModT>\nclass montgomery_modint63 {\n  using u32 = std::uint32_t;\n\
    \  using i64 = std::int64_t;\n  using u64 = std::uint64_t;\n\n  u64 v_{};\n\n\
    \  static constexpr u64 get_r() {\n    u64 t = 2, iv = MOD * (t - MOD * MOD);\n\
    \    iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv;\n    return iv\
    \ * (t - MOD * iv);\n  }\n  static constexpr u64 get_r2() {\n    u64 iv = -MOD\
    \ % MOD;\n    for (int i = 0; i != 64; ++i)\n      if ((iv <<= 1) >= MOD) iv -=\
    \ MOD;\n    return iv;\n  }\n  static constexpr u64 mul_high(u64 x, u64 y) {\n\
    \    u64 a = x >> 32, b = static_cast<u32>(x), c = y >> 32, d = static_cast<u32>(y),\
    \ ad = a * d,\n        bc = b * c;\n    return a * c + (ad >> 32) + (bc >> 32)\
    \ +\n           (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);\n\
    \  }\n  static constexpr u64 redc_mul(u64 x, u64 y) {\n    u64 res = mul_high(x,\
    \ y) - mul_high(x * y * R, MOD);\n    return res + (MOD & -(res >> 63));\n  }\n\
    \  static constexpr u64 norm(i64 x) { return x + (MOD & -(x < 0)); }\n\n  static\
    \ constexpr u64 MOD  = ModT;\n  static constexpr u64 R    = get_r();\n  static\
    \ constexpr u64 R2   = get_r2();\n  static constexpr i64 SMOD = static_cast<i64>(MOD);\n\
    \n  static_assert(MOD & 1);\n  static_assert(R * MOD == 1);\n  static_assert((MOD\
    \ >> 63) == 0);\n  static_assert(MOD != 1);\n\npublic:\n  static constexpr u64\
    \ mod() { return MOD; }\n  static constexpr i64 smod() { return SMOD; }\n  constexpr\
    \ montgomery_modint63() {}\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>,\
    \ int> = 0>\n  constexpr montgomery_modint63(IntT v) : v_(redc_mul(norm(v % SMOD),\
    \ R2)) {}\n  constexpr u64 val() const {\n    u64 res = -mul_high(v_ * R, MOD);\n\
    \    return res + (MOD & -(res >> 63));\n  }\n  constexpr i64 sval() const { return\
    \ val(); }\n  constexpr bool is_zero() const { return v_ == 0; }\n  template <typename\
    \ IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>\n  explicit constexpr\
    \ operator IntT() const {\n    return static_cast<IntT>(val());\n  }\n  constexpr\
    \ montgomery_modint63 operator-() const {\n    montgomery_modint63 res;\n    res.v_\
    \ = (MOD & -(v_ != 0)) - v_;\n    return res;\n  }\n  constexpr montgomery_modint63\
    \ inv() const {\n    i64 x1 = 1, x3 = 0, a = sval(), b = SMOD;\n    while (b !=\
    \ 0) {\n      i64 q = a / b, x1_old = x1, a_old = a;\n      x1 = x3, x3 = x1_old\
    \ - x3 * q, a = b, b = a_old - b * q;\n    }\n#ifdef LIB_DEBUG\n    if (a != 1)\
    \ throw std::runtime_error(\"modular inverse error\");\n#endif\n    return montgomery_modint63(x1);\n\
    \  }\n  constexpr montgomery_modint63 &operator+=(const montgomery_modint63 &rhs)\
    \ {\n    v_ += rhs.v_ - MOD, v_ += MOD & -(v_ >> 63);\n    return *this;\n  }\n\
    \  constexpr montgomery_modint63 &operator-=(const montgomery_modint63 &rhs) {\n\
    \    v_ -= rhs.v_, v_ += MOD & -(v_ >> 63);\n    return *this;\n  }\n  constexpr\
    \ montgomery_modint63 &operator*=(const montgomery_modint63 &rhs) {\n    v_ =\
    \ redc_mul(v_, rhs.v_);\n    return *this;\n  }\n  constexpr montgomery_modint63\
    \ &operator/=(const montgomery_modint63 &rhs) {\n    return operator*=(rhs.inv());\n\
    \  }\n  constexpr montgomery_modint63 pow(u64 e) const {\n    for (montgomery_modint63\
    \ res(1), x(*this);; x *= x) {\n      if (e & 1) res *= x;\n      if ((e >>= 1)\
    \ == 0) return res;\n    }\n  }\n  constexpr void swap(montgomery_modint63 &rhs)\
    \ {\n    auto v = v_;\n    v_ = rhs.v_, rhs.v_ = v;\n  }\n  friend constexpr montgomery_modint63\
    \ operator+(const montgomery_modint63 &lhs,\n                                \
    \                 const montgomery_modint63 &rhs) {\n    return montgomery_modint63(lhs)\
    \ += rhs;\n  }\n  friend constexpr montgomery_modint63 operator-(const montgomery_modint63\
    \ &lhs,\n                                                 const montgomery_modint63\
    \ &rhs) {\n    return montgomery_modint63(lhs) -= rhs;\n  }\n  friend constexpr\
    \ montgomery_modint63 operator*(const montgomery_modint63 &lhs,\n            \
    \                                     const montgomery_modint63 &rhs) {\n    return\
    \ montgomery_modint63(lhs) *= rhs;\n  }\n  friend constexpr montgomery_modint63\
    \ operator/(const montgomery_modint63 &lhs,\n                                \
    \                 const montgomery_modint63 &rhs) {\n    return montgomery_modint63(lhs)\
    \ /= rhs;\n  }\n  friend constexpr bool operator==(const montgomery_modint63 &lhs,\
    \ const montgomery_modint63 &rhs) {\n    return lhs.v_ == rhs.v_;\n  }\n  friend\
    \ constexpr bool operator!=(const montgomery_modint63 &lhs, const montgomery_modint63\
    \ &rhs) {\n    return lhs.v_ != rhs.v_;\n  }\n  friend std::istream &operator>>(std::istream\
    \ &is, montgomery_modint63 &rhs) {\n    i64 x;\n    is >> x;\n    rhs = montgomery_modint63(x);\n\
    \    return is;\n  }\n  friend std::ostream &operator<<(std::ostream &os, const\
    \ montgomery_modint63 &rhs) {\n    return os << rhs.val();\n  }\n};\n\ntemplate\
    \ <std::uint64_t ModT>\nusing mm63 = montgomery_modint63<ModT>;\n\nLIB_END\n\n\
    #endif"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: modint/long_montgomery_modint.hpp
  requiredBy:
  - math/convolution_mod.hpp
  - math/binomial_convolution.hpp
  timestamp: '2022-04-26 20:45:46+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp
  - remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
documentation_of: modint/long_montgomery_modint.hpp
layout: document
title: Long Montgomery ModInt
---

## Bibliography

1. [Nyaan's Library](https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp).
