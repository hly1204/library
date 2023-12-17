---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/integer_factorization.hpp
    title: Integer Factorization (Pollard's rho algorithm) (in $\mathbb{Z}$)
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/factorize.0.test.cpp
    title: remote_test/yosupo/math/factorize.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/primality_test.0.test.cpp
    title: remote_test/yosupo/math/primality_test.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"modint/runtime_long_montgomery_modint.hpp\"\n\n\n\n#line\
    \ 1 \"common.hpp\"\n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib\
    \ {\n#define LIB_END }\n#define LIB ::lib::\n\n\n#line 5 \"modint/runtime_long_montgomery_modint.hpp\"\
    \n\n#ifdef LIB_DEBUG\n  #include <stdexcept>\n#endif\n#include <cstdint>\n#include\
    \ <iostream>\n#include <type_traits>\n\nLIB_BEGIN\n\ntemplate <int /* IdT */>\n\
    class runtime_montgomery_modint63 {\n  using u32 = std::uint32_t;\n  using i64\
    \ = std::int64_t;\n  using u64 = std::uint64_t;\n\n  u64 v_{};\n\n  static inline\
    \ u64 mul_high(u64 x, u64 y) {\n    u64 a = x >> 32, b = static_cast<u32>(x),\
    \ c = y >> 32, d = static_cast<u32>(y), ad = a * d,\n        bc = b * c;\n   \
    \ return a * c + (ad >> 32) + (bc >> 32) +\n           (((ad & 0xFFFFFFFF) + (bc\
    \ & 0xFFFFFFFF) + (b * d >> 32)) >> 32);\n  }\n  static inline u64 redc_mul(u64\
    \ x, u64 y) {\n    u64 res = mul_high(x, y) - mul_high(x * y * R, MOD);\n    return\
    \ res + (MOD & -(res >> 63));\n  }\n  static inline u64 norm(i64 x) { return x\
    \ + (MOD & -(x < 0)); }\n\n  static u64 MOD, R, R2;\n  static i64 SMOD;\n\npublic:\n\
    \  static inline bool set_mod(u64 m) {\n    if ((m & 1) == 0 || m == 1 || m >>\
    \ 63 != 0) return false;\n    MOD = m;\n    {\n      // compute R\n      u64 t\
    \ = 2, iv = MOD * (t - MOD * MOD);\n      iv *= t - MOD * iv, iv *= t - MOD *\
    \ iv, iv *= t - MOD * iv;\n      R = iv * (t - MOD * iv);\n    }\n    {\n    \
    \  // compute R2\n      R2 = -MOD % MOD;\n      for (int i = 0; i != 64; ++i)\n\
    \        if ((R2 <<= 1) >= MOD) R2 -= MOD;\n    }\n    SMOD = static_cast<i64>(MOD);\n\
    \    return true;\n  }\n  static inline u64 mod() { return MOD; }\n  static inline\
    \ i64 smod() { return SMOD; }\n  runtime_montgomery_modint63() {}\n  template\
    \ <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>\n  runtime_montgomery_modint63(IntT\
    \ v) : v_(redc_mul(norm(v % SMOD), R2)) {}\n  u64 val() const {\n    u64 res =\
    \ -mul_high(v_ * R, MOD);\n    return res + (MOD & -(res >> 63));\n  }\n  i64\
    \ sval() const { return val(); }\n  bool is_zero() const { return v_ == 0; }\n\
    \  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> =\
    \ 0>\n  explicit operator IntT() const {\n    return static_cast<IntT>(val());\n\
    \  }\n  runtime_montgomery_modint63 operator-() const {\n    runtime_montgomery_modint63\
    \ res;\n    res.v_ = (MOD & -(v_ != 0)) - v_;\n    return res;\n  }\n  runtime_montgomery_modint63\
    \ inv() const {\n    i64 x1 = 1, x3 = 0, a = sval(), b = SMOD;\n    while (b !=\
    \ 0) {\n      i64 q = a / b, x1_old = x1, a_old = a;\n      x1 = x3, x3 = x1_old\
    \ - x3 * q, a = b, b = a_old - b * q;\n    }\n#ifdef LIB_DEBUG\n    if (a != 1)\
    \ throw std::runtime_error(\"modular inverse error\");\n#endif\n    return runtime_montgomery_modint63(x1);\n\
    \  }\n  runtime_montgomery_modint63 &operator+=(const runtime_montgomery_modint63\
    \ &rhs) {\n    v_ += rhs.v_ - MOD, v_ += MOD & -(v_ >> 63);\n    return *this;\n\
    \  }\n  runtime_montgomery_modint63 &operator-=(const runtime_montgomery_modint63\
    \ &rhs) {\n    v_ -= rhs.v_, v_ += MOD & -(v_ >> 63);\n    return *this;\n  }\n\
    \  runtime_montgomery_modint63 &operator*=(const runtime_montgomery_modint63 &rhs)\
    \ {\n    v_ = redc_mul(v_, rhs.v_);\n    return *this;\n  }\n  runtime_montgomery_modint63\
    \ &operator/=(const runtime_montgomery_modint63 &rhs) {\n    return operator*=(rhs.inv());\n\
    \  }\n  runtime_montgomery_modint63 pow(u64 e) const {\n    for (runtime_montgomery_modint63\
    \ res(1), x(*this);; x *= x) {\n      if (e & 1) res *= x;\n      if ((e >>= 1)\
    \ == 0) return res;\n    }\n  }\n  void swap(runtime_montgomery_modint63 &rhs)\
    \ {\n    auto v = v_;\n    v_ = rhs.v_, rhs.v_ = v;\n  }\n  friend runtime_montgomery_modint63\
    \ operator+(const runtime_montgomery_modint63 &lhs,\n                        \
    \                       const runtime_montgomery_modint63 &rhs) {\n    return\
    \ runtime_montgomery_modint63(lhs) += rhs;\n  }\n  friend runtime_montgomery_modint63\
    \ operator-(const runtime_montgomery_modint63 &lhs,\n                        \
    \                       const runtime_montgomery_modint63 &rhs) {\n    return\
    \ runtime_montgomery_modint63(lhs) -= rhs;\n  }\n  friend runtime_montgomery_modint63\
    \ operator*(const runtime_montgomery_modint63 &lhs,\n                        \
    \                       const runtime_montgomery_modint63 &rhs) {\n    return\
    \ runtime_montgomery_modint63(lhs) *= rhs;\n  }\n  friend runtime_montgomery_modint63\
    \ operator/(const runtime_montgomery_modint63 &lhs,\n                        \
    \                       const runtime_montgomery_modint63 &rhs) {\n    return\
    \ runtime_montgomery_modint63(lhs) /= rhs;\n  }\n  friend bool operator==(const\
    \ runtime_montgomery_modint63 &lhs,\n                         const runtime_montgomery_modint63\
    \ &rhs) {\n    return lhs.v_ == rhs.v_;\n  }\n  friend bool operator!=(const runtime_montgomery_modint63\
    \ &lhs,\n                         const runtime_montgomery_modint63 &rhs) {\n\
    \    return lhs.v_ != rhs.v_;\n  }\n  friend std::istream &operator>>(std::istream\
    \ &is, runtime_montgomery_modint63 &rhs) {\n    i64 x;\n    is >> x;\n    rhs\
    \ = runtime_montgomery_modint63(x);\n    return is;\n  }\n  friend std::ostream\
    \ &operator<<(std::ostream &os, const runtime_montgomery_modint63 &rhs) {\n  \
    \  return os << rhs.val();\n  }\n};\n\ntemplate <int IdT>\ntypename runtime_montgomery_modint63<IdT>::u64\
    \ runtime_montgomery_modint63<IdT>::MOD;\ntemplate <int IdT>\ntypename runtime_montgomery_modint63<IdT>::u64\
    \ runtime_montgomery_modint63<IdT>::R;\ntemplate <int IdT>\ntypename runtime_montgomery_modint63<IdT>::u64\
    \ runtime_montgomery_modint63<IdT>::R2;\ntemplate <int IdT>\ntypename runtime_montgomery_modint63<IdT>::i64\
    \ runtime_montgomery_modint63<IdT>::SMOD;\n\ntemplate <int IdT>\nusing rmm63 =\
    \ runtime_montgomery_modint63<IdT>;\n\nLIB_END\n\n\n"
  code: "#ifndef RUNTIME_LONG_MONTGOMERY_MODINT_HPP\n#define RUNTIME_LONG_MONTGOMERY_MODINT_HPP\n\
    \n#include \"../common.hpp\"\n\n#ifdef LIB_DEBUG\n  #include <stdexcept>\n#endif\n\
    #include <cstdint>\n#include <iostream>\n#include <type_traits>\n\nLIB_BEGIN\n\
    \ntemplate <int /* IdT */>\nclass runtime_montgomery_modint63 {\n  using u32 =\
    \ std::uint32_t;\n  using i64 = std::int64_t;\n  using u64 = std::uint64_t;\n\n\
    \  u64 v_{};\n\n  static inline u64 mul_high(u64 x, u64 y) {\n    u64 a = x >>\
    \ 32, b = static_cast<u32>(x), c = y >> 32, d = static_cast<u32>(y), ad = a *\
    \ d,\n        bc = b * c;\n    return a * c + (ad >> 32) + (bc >> 32) +\n    \
    \       (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) + (b * d >> 32)) >> 32);\n  }\n\
    \  static inline u64 redc_mul(u64 x, u64 y) {\n    u64 res = mul_high(x, y) -\
    \ mul_high(x * y * R, MOD);\n    return res + (MOD & -(res >> 63));\n  }\n  static\
    \ inline u64 norm(i64 x) { return x + (MOD & -(x < 0)); }\n\n  static u64 MOD,\
    \ R, R2;\n  static i64 SMOD;\n\npublic:\n  static inline bool set_mod(u64 m) {\n\
    \    if ((m & 1) == 0 || m == 1 || m >> 63 != 0) return false;\n    MOD = m;\n\
    \    {\n      // compute R\n      u64 t = 2, iv = MOD * (t - MOD * MOD);\n   \
    \   iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv;\n      R = iv\
    \ * (t - MOD * iv);\n    }\n    {\n      // compute R2\n      R2 = -MOD % MOD;\n\
    \      for (int i = 0; i != 64; ++i)\n        if ((R2 <<= 1) >= MOD) R2 -= MOD;\n\
    \    }\n    SMOD = static_cast<i64>(MOD);\n    return true;\n  }\n  static inline\
    \ u64 mod() { return MOD; }\n  static inline i64 smod() { return SMOD; }\n  runtime_montgomery_modint63()\
    \ {}\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int>\
    \ = 0>\n  runtime_montgomery_modint63(IntT v) : v_(redc_mul(norm(v % SMOD), R2))\
    \ {}\n  u64 val() const {\n    u64 res = -mul_high(v_ * R, MOD);\n    return res\
    \ + (MOD & -(res >> 63));\n  }\n  i64 sval() const { return val(); }\n  bool is_zero()\
    \ const { return v_ == 0; }\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>,\
    \ int> = 0>\n  explicit operator IntT() const {\n    return static_cast<IntT>(val());\n\
    \  }\n  runtime_montgomery_modint63 operator-() const {\n    runtime_montgomery_modint63\
    \ res;\n    res.v_ = (MOD & -(v_ != 0)) - v_;\n    return res;\n  }\n  runtime_montgomery_modint63\
    \ inv() const {\n    i64 x1 = 1, x3 = 0, a = sval(), b = SMOD;\n    while (b !=\
    \ 0) {\n      i64 q = a / b, x1_old = x1, a_old = a;\n      x1 = x3, x3 = x1_old\
    \ - x3 * q, a = b, b = a_old - b * q;\n    }\n#ifdef LIB_DEBUG\n    if (a != 1)\
    \ throw std::runtime_error(\"modular inverse error\");\n#endif\n    return runtime_montgomery_modint63(x1);\n\
    \  }\n  runtime_montgomery_modint63 &operator+=(const runtime_montgomery_modint63\
    \ &rhs) {\n    v_ += rhs.v_ - MOD, v_ += MOD & -(v_ >> 63);\n    return *this;\n\
    \  }\n  runtime_montgomery_modint63 &operator-=(const runtime_montgomery_modint63\
    \ &rhs) {\n    v_ -= rhs.v_, v_ += MOD & -(v_ >> 63);\n    return *this;\n  }\n\
    \  runtime_montgomery_modint63 &operator*=(const runtime_montgomery_modint63 &rhs)\
    \ {\n    v_ = redc_mul(v_, rhs.v_);\n    return *this;\n  }\n  runtime_montgomery_modint63\
    \ &operator/=(const runtime_montgomery_modint63 &rhs) {\n    return operator*=(rhs.inv());\n\
    \  }\n  runtime_montgomery_modint63 pow(u64 e) const {\n    for (runtime_montgomery_modint63\
    \ res(1), x(*this);; x *= x) {\n      if (e & 1) res *= x;\n      if ((e >>= 1)\
    \ == 0) return res;\n    }\n  }\n  void swap(runtime_montgomery_modint63 &rhs)\
    \ {\n    auto v = v_;\n    v_ = rhs.v_, rhs.v_ = v;\n  }\n  friend runtime_montgomery_modint63\
    \ operator+(const runtime_montgomery_modint63 &lhs,\n                        \
    \                       const runtime_montgomery_modint63 &rhs) {\n    return\
    \ runtime_montgomery_modint63(lhs) += rhs;\n  }\n  friend runtime_montgomery_modint63\
    \ operator-(const runtime_montgomery_modint63 &lhs,\n                        \
    \                       const runtime_montgomery_modint63 &rhs) {\n    return\
    \ runtime_montgomery_modint63(lhs) -= rhs;\n  }\n  friend runtime_montgomery_modint63\
    \ operator*(const runtime_montgomery_modint63 &lhs,\n                        \
    \                       const runtime_montgomery_modint63 &rhs) {\n    return\
    \ runtime_montgomery_modint63(lhs) *= rhs;\n  }\n  friend runtime_montgomery_modint63\
    \ operator/(const runtime_montgomery_modint63 &lhs,\n                        \
    \                       const runtime_montgomery_modint63 &rhs) {\n    return\
    \ runtime_montgomery_modint63(lhs) /= rhs;\n  }\n  friend bool operator==(const\
    \ runtime_montgomery_modint63 &lhs,\n                         const runtime_montgomery_modint63\
    \ &rhs) {\n    return lhs.v_ == rhs.v_;\n  }\n  friend bool operator!=(const runtime_montgomery_modint63\
    \ &lhs,\n                         const runtime_montgomery_modint63 &rhs) {\n\
    \    return lhs.v_ != rhs.v_;\n  }\n  friend std::istream &operator>>(std::istream\
    \ &is, runtime_montgomery_modint63 &rhs) {\n    i64 x;\n    is >> x;\n    rhs\
    \ = runtime_montgomery_modint63(x);\n    return is;\n  }\n  friend std::ostream\
    \ &operator<<(std::ostream &os, const runtime_montgomery_modint63 &rhs) {\n  \
    \  return os << rhs.val();\n  }\n};\n\ntemplate <int IdT>\ntypename runtime_montgomery_modint63<IdT>::u64\
    \ runtime_montgomery_modint63<IdT>::MOD;\ntemplate <int IdT>\ntypename runtime_montgomery_modint63<IdT>::u64\
    \ runtime_montgomery_modint63<IdT>::R;\ntemplate <int IdT>\ntypename runtime_montgomery_modint63<IdT>::u64\
    \ runtime_montgomery_modint63<IdT>::R2;\ntemplate <int IdT>\ntypename runtime_montgomery_modint63<IdT>::i64\
    \ runtime_montgomery_modint63<IdT>::SMOD;\n\ntemplate <int IdT>\nusing rmm63 =\
    \ runtime_montgomery_modint63<IdT>;\n\nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: modint/runtime_long_montgomery_modint.hpp
  requiredBy:
  - math/integer_factorization.hpp
  timestamp: '2022-05-15 18:42:53+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/primality_test.0.test.cpp
  - remote_test/yosupo/math/factorize.0.test.cpp
documentation_of: modint/runtime_long_montgomery_modint.hpp
layout: document
title: Runtime Long Montgomery ModInt
---

## Bibliography

1. [Nyaan's Library](https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp).
