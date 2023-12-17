---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/sqrt_mod.0.test.cpp
    title: remote_test/yosupo/math/sqrt_mod.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"modint/runtime_modint.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
    \n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 5 \"modint/runtime_modint.hpp\"\n\n#ifdef\
    \ LIB_DEBUG\n  #include <stdexcept>\n#endif\n#include <cstdint>\n#include <iostream>\n\
    #include <type_traits>\n\nLIB_BEGIN\n\ntemplate <int /* IdT */>\nclass runtime_modint31\
    \ {\n  using i32 = std::int32_t;\n  using u32 = std::uint32_t;\n  using u64 =\
    \ std::uint64_t;\n\n  u32 v_{};\n\n  static inline u32 norm(i32 x) { return x\
    \ + (-(x < 0) & MOD); }\n  static inline u32 redc(u64 x) {\n    u32 t = (x + static_cast<u64>(static_cast<u32>(x)\
    \ * R) * MOD_ODD) >> 32;\n    return t - (MOD_ODD & -((MOD_ODD - 1 - t) >> 31));\n\
    \  }\n  static inline u32 tsf(u32 x) {\n    return redc(static_cast<u64>(x % MOD_ODD)\
    \ * R2) << OFFSET | (x & MASK);\n  }\n\n  static u32 R, R2, MOD, MOD_ODD, OFFSET,\
    \ MASK;\n  static i32 SMOD;\n\npublic:\n  static inline bool set_mod(u32 m) {\n\
    \    if (m == 1 || m >> 31 != 0) return false;\n    for (MOD = MOD_ODD = m, OFFSET\
    \ = 0; (MOD_ODD & 1) == 0; ++OFFSET, MOD_ODD >>= 1) {}\n    MASK = (1 << OFFSET)\
    \ - 1, SMOD = static_cast<i32>(MOD);\n    {\n      // compute R\n      u32 t =\
    \ 2, iv = MOD_ODD * (t - MOD_ODD * MOD_ODD);\n      iv *= t - MOD_ODD * iv, iv\
    \ *= t - MOD_ODD * iv;\n      R = iv * (MOD_ODD * iv - t);\n    }\n    // compute\
    \ R2\n    R2 = -static_cast<u64>(MOD_ODD) % MOD_ODD;\n    return true;\n  }\n\
    \  static inline u32 mod() { return MOD; }\n  static inline i32 smod() { return\
    \ SMOD; }\n  runtime_modint31() {}\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>,\
    \ int> = 0>\n  runtime_modint31(IntT v) : v_(tsf(norm(v % SMOD))) {}\n  u32 val()\
    \ const {\n    u32 h = redc(v_ >> OFFSET);\n    return ((h - v_) * R & MASK) *\
    \ MOD_ODD + h;\n  }\n  i32 sval() const { return val(); }\n  bool is_zero() const\
    \ { return v_ == 0; }\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>,\
    \ int> = 0>\n  explicit operator IntT() const {\n    return static_cast<IntT>(val());\n\
    \  }\n  runtime_modint31 operator-() const {\n    runtime_modint31 res;\n    u32\
    \ h  = v_ >> OFFSET;\n    res.v_ = (((MOD_ODD & -(h != 0)) - h) << OFFSET) | (-v_\
    \ & MASK);\n    return res;\n  }\n  runtime_modint31 inv() const {\n    i32 x1\
    \ = 1, x3 = 0, a = sval(), b = SMOD;\n    while (b != 0) {\n      i32 q = a /\
    \ b, x1_old = x1, a_old = a;\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b =\
    \ a_old - b * q;\n    }\n#ifdef LIB_DEBUG\n    if (a != 1) throw std::runtime_error(\"\
    modular inverse error\");\n#endif\n    return runtime_modint31(x1);\n  }\n  runtime_modint31\
    \ &operator+=(const runtime_modint31 &rhs) {\n    u32 h = (v_ >> OFFSET) + (rhs.v_\
    \ >> OFFSET) - MOD_ODD;\n    v_    = ((h + (MOD_ODD & -(h >> 31))) << OFFSET)\
    \ | ((v_ + rhs.v_) & MASK);\n    return *this;\n  }\n  runtime_modint31 &operator-=(const\
    \ runtime_modint31 &rhs) {\n    u32 h = (v_ >> OFFSET) - (rhs.v_ >> OFFSET);\n\
    \    v_    = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ - rhs.v_) & MASK);\n\
    \    return *this;\n  }\n  runtime_modint31 &operator*=(const runtime_modint31\
    \ &rhs) {\n    v_ = (redc(static_cast<u64>(v_ >> OFFSET) * (rhs.v_ >> OFFSET))\
    \ << OFFSET) |\n         ((v_ * rhs.v_) & MASK);\n    return *this;\n  }\n  runtime_modint31\
    \ &operator/=(const runtime_modint31 &rhs) { return operator*=(rhs.inv()); }\n\
    \  runtime_modint31 pow(u64 e) const {\n    for (runtime_modint31 res(1), x(*this);;\
    \ x *= x) {\n      if (e & 1) res *= x;\n      if ((e >>= 1) == 0) return res;\n\
    \    }\n  }\n  void swap(runtime_modint31 &rhs) {\n    auto v = v_;\n    v_ =\
    \ rhs.v_, rhs.v_ = v;\n  }\n  friend runtime_modint31 operator+(const runtime_modint31\
    \ &lhs, const runtime_modint31 &rhs) {\n    return runtime_modint31(lhs) += rhs;\n\
    \  }\n  friend runtime_modint31 operator-(const runtime_modint31 &lhs, const runtime_modint31\
    \ &rhs) {\n    return runtime_modint31(lhs) -= rhs;\n  }\n  friend runtime_modint31\
    \ operator*(const runtime_modint31 &lhs, const runtime_modint31 &rhs) {\n    return\
    \ runtime_modint31(lhs) *= rhs;\n  }\n  friend runtime_modint31 operator/(const\
    \ runtime_modint31 &lhs, const runtime_modint31 &rhs) {\n    return runtime_modint31(lhs)\
    \ /= rhs;\n  }\n  friend bool operator==(const runtime_modint31 &lhs, const runtime_modint31\
    \ &rhs) {\n    return lhs.v_ == rhs.v_;\n  }\n  friend bool operator!=(const runtime_modint31\
    \ &lhs, const runtime_modint31 &rhs) {\n    return lhs.v_ != rhs.v_;\n  }\n  friend\
    \ std::istream &operator>>(std::istream &is, runtime_modint31 &rhs) {\n    i32\
    \ x;\n    is >> x;\n    rhs = runtime_modint31(x);\n    return is;\n  }\n  friend\
    \ std::ostream &operator<<(std::ostream &os, const runtime_modint31 &rhs) {\n\
    \    return os << rhs.val();\n  }\n};\n\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::R;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::R2;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::MOD;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::MOD_ODD;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::OFFSET;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::MASK;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::i32\
    \ runtime_modint31<IdT>::SMOD;\n\ntemplate <int IdT>\nusing rm31 = runtime_modint31<IdT>;\n\
    \nLIB_END\n\n\n"
  code: "#ifndef RUNTIME_MODINT_HPP\n#define RUNTIME_MODINT_HPP\n\n#include \"../common.hpp\"\
    \n\n#ifdef LIB_DEBUG\n  #include <stdexcept>\n#endif\n#include <cstdint>\n#include\
    \ <iostream>\n#include <type_traits>\n\nLIB_BEGIN\n\ntemplate <int /* IdT */>\n\
    class runtime_modint31 {\n  using i32 = std::int32_t;\n  using u32 = std::uint32_t;\n\
    \  using u64 = std::uint64_t;\n\n  u32 v_{};\n\n  static inline u32 norm(i32 x)\
    \ { return x + (-(x < 0) & MOD); }\n  static inline u32 redc(u64 x) {\n    u32\
    \ t = (x + static_cast<u64>(static_cast<u32>(x) * R) * MOD_ODD) >> 32;\n    return\
    \ t - (MOD_ODD & -((MOD_ODD - 1 - t) >> 31));\n  }\n  static inline u32 tsf(u32\
    \ x) {\n    return redc(static_cast<u64>(x % MOD_ODD) * R2) << OFFSET | (x & MASK);\n\
    \  }\n\n  static u32 R, R2, MOD, MOD_ODD, OFFSET, MASK;\n  static i32 SMOD;\n\n\
    public:\n  static inline bool set_mod(u32 m) {\n    if (m == 1 || m >> 31 != 0)\
    \ return false;\n    for (MOD = MOD_ODD = m, OFFSET = 0; (MOD_ODD & 1) == 0; ++OFFSET,\
    \ MOD_ODD >>= 1) {}\n    MASK = (1 << OFFSET) - 1, SMOD = static_cast<i32>(MOD);\n\
    \    {\n      // compute R\n      u32 t = 2, iv = MOD_ODD * (t - MOD_ODD * MOD_ODD);\n\
    \      iv *= t - MOD_ODD * iv, iv *= t - MOD_ODD * iv;\n      R = iv * (MOD_ODD\
    \ * iv - t);\n    }\n    // compute R2\n    R2 = -static_cast<u64>(MOD_ODD) %\
    \ MOD_ODD;\n    return true;\n  }\n  static inline u32 mod() { return MOD; }\n\
    \  static inline i32 smod() { return SMOD; }\n  runtime_modint31() {}\n  template\
    \ <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>\n  runtime_modint31(IntT\
    \ v) : v_(tsf(norm(v % SMOD))) {}\n  u32 val() const {\n    u32 h = redc(v_ >>\
    \ OFFSET);\n    return ((h - v_) * R & MASK) * MOD_ODD + h;\n  }\n  i32 sval()\
    \ const { return val(); }\n  bool is_zero() const { return v_ == 0; }\n  template\
    \ <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>\n  explicit\
    \ operator IntT() const {\n    return static_cast<IntT>(val());\n  }\n  runtime_modint31\
    \ operator-() const {\n    runtime_modint31 res;\n    u32 h  = v_ >> OFFSET;\n\
    \    res.v_ = (((MOD_ODD & -(h != 0)) - h) << OFFSET) | (-v_ & MASK);\n    return\
    \ res;\n  }\n  runtime_modint31 inv() const {\n    i32 x1 = 1, x3 = 0, a = sval(),\
    \ b = SMOD;\n    while (b != 0) {\n      i32 q = a / b, x1_old = x1, a_old = a;\n\
    \      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\n    }\n#ifdef\
    \ LIB_DEBUG\n    if (a != 1) throw std::runtime_error(\"modular inverse error\"\
    );\n#endif\n    return runtime_modint31(x1);\n  }\n  runtime_modint31 &operator+=(const\
    \ runtime_modint31 &rhs) {\n    u32 h = (v_ >> OFFSET) + (rhs.v_ >> OFFSET) -\
    \ MOD_ODD;\n    v_    = ((h + (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ + rhs.v_)\
    \ & MASK);\n    return *this;\n  }\n  runtime_modint31 &operator-=(const runtime_modint31\
    \ &rhs) {\n    u32 h = (v_ >> OFFSET) - (rhs.v_ >> OFFSET);\n    v_    = ((h +\
    \ (MOD_ODD & -(h >> 31))) << OFFSET) | ((v_ - rhs.v_) & MASK);\n    return *this;\n\
    \  }\n  runtime_modint31 &operator*=(const runtime_modint31 &rhs) {\n    v_ =\
    \ (redc(static_cast<u64>(v_ >> OFFSET) * (rhs.v_ >> OFFSET)) << OFFSET) |\n  \
    \       ((v_ * rhs.v_) & MASK);\n    return *this;\n  }\n  runtime_modint31 &operator/=(const\
    \ runtime_modint31 &rhs) { return operator*=(rhs.inv()); }\n  runtime_modint31\
    \ pow(u64 e) const {\n    for (runtime_modint31 res(1), x(*this);; x *= x) {\n\
    \      if (e & 1) res *= x;\n      if ((e >>= 1) == 0) return res;\n    }\n  }\n\
    \  void swap(runtime_modint31 &rhs) {\n    auto v = v_;\n    v_ = rhs.v_, rhs.v_\
    \ = v;\n  }\n  friend runtime_modint31 operator+(const runtime_modint31 &lhs,\
    \ const runtime_modint31 &rhs) {\n    return runtime_modint31(lhs) += rhs;\n \
    \ }\n  friend runtime_modint31 operator-(const runtime_modint31 &lhs, const runtime_modint31\
    \ &rhs) {\n    return runtime_modint31(lhs) -= rhs;\n  }\n  friend runtime_modint31\
    \ operator*(const runtime_modint31 &lhs, const runtime_modint31 &rhs) {\n    return\
    \ runtime_modint31(lhs) *= rhs;\n  }\n  friend runtime_modint31 operator/(const\
    \ runtime_modint31 &lhs, const runtime_modint31 &rhs) {\n    return runtime_modint31(lhs)\
    \ /= rhs;\n  }\n  friend bool operator==(const runtime_modint31 &lhs, const runtime_modint31\
    \ &rhs) {\n    return lhs.v_ == rhs.v_;\n  }\n  friend bool operator!=(const runtime_modint31\
    \ &lhs, const runtime_modint31 &rhs) {\n    return lhs.v_ != rhs.v_;\n  }\n  friend\
    \ std::istream &operator>>(std::istream &is, runtime_modint31 &rhs) {\n    i32\
    \ x;\n    is >> x;\n    rhs = runtime_modint31(x);\n    return is;\n  }\n  friend\
    \ std::ostream &operator<<(std::ostream &os, const runtime_modint31 &rhs) {\n\
    \    return os << rhs.val();\n  }\n};\n\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::R;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::R2;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::MOD;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::MOD_ODD;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::OFFSET;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::u32\
    \ runtime_modint31<IdT>::MASK;\ntemplate <int IdT>\ntypename runtime_modint31<IdT>::i32\
    \ runtime_modint31<IdT>::SMOD;\n\ntemplate <int IdT>\nusing rm31 = runtime_modint31<IdT>;\n\
    \nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: modint/runtime_modint.hpp
  requiredBy: []
  timestamp: '2022-05-15 18:42:53+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/sqrt_mod.0.test.cpp
documentation_of: modint/runtime_modint.hpp
layout: document
title: Runtime ModInt
---
