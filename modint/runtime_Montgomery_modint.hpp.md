---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/modulo/sqrt_mod.hpp
    title: "square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839"
  _extendedVerifiedWith:
  - icon: ':x:'
    path: remote_test/yosupo/math/mod_sqrt.0.test.cpp
    title: remote_test/yosupo/math/mod_sqrt.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "runtime Montgomery modint / \u8FD0\u884C\u65F6 Montgomery \u53D6\
      \u6A21\u7C7B"
    links:
    - https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp
  bundledCode: "#line 1 \"modint/runtime_Montgomery_modint.hpp\"\n\n\n\r\n/**\r\n\
    \ * @brief runtime Montgomery modint / \u8FD0\u884C\u65F6 Montgomery \u53D6\u6A21\
    \u7C7B\r\n *\r\n */\r\n\r\n#include <cstdint>\r\n#include <iostream>\r\n#include\
    \ <type_traits>\r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u8FD0\u884C\u65F6\
    \ Montgomery \u53D6\u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
    \n * @author Nyaan\r\n * @note \u7EA6\u5B9A\u4E0D\u4F7F\u7528\u6A21\u677F\u4E2D\
    \ int \u4E3A\u8D1F\u6570\u7684\u5BF9\u8C61\r\n */\r\ntemplate <int>\r\nclass RuntimeMontgomeryModInt\
    \ {\r\npublic:\r\n  using i32 = std::int32_t;\r\n  using u32 = std::uint32_t;\r\
    \n  using u64 = std::uint64_t;\r\n  using m32 = RuntimeMontgomeryModInt;\r\n\r\
    \n  using value_type = u32;\r\n\r\n  static u32 get_mod() { return mod; }\r\n\r\
    \n  static bool set_mod(u32 m) {\r\n    if ((m & 1) == 0 || m == 1 || (m & (3U\
    \ << 30)) != 0) return false;\r\n    mod = m, mod2 = mod << 1;\r\n    u32 two\
    \ = 2, iv = mod * (two - mod * mod);\r\n    iv *= two - mod * iv;\r\n    iv *=\
    \ two - mod * iv;\r\n    r  = iv * (mod * iv - two);\r\n    r2 = -u64(mod) % mod;\r\
    \n    return true;\r\n  }\r\n\r\n  RuntimeMontgomeryModInt()  = default;\r\n \
    \ ~RuntimeMontgomeryModInt() = default;\r\n\r\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\r\n  RuntimeMontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) + i32(mod))\
    \ * r2)) {}\r\n\r\n  RuntimeMontgomeryModInt(const m32 &) = default;\r\n\r\n \
    \ u32 get() const { return norm(reduce(v_)); }\r\n\r\n  template <typename T,\
    \ std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  explicit operator T()\
    \ const {\r\n    return T(get());\r\n  }\r\n\r\n  m32 operator-() const {\r\n\
    \    m32 res;\r\n    res.v_ = (mod2 & -(v_ != 0)) - v_;\r\n    return res;\r\n\
    \  }\r\n\r\n  m32 inv() const {\r\n    i32 x1 = 1, x3 = 0, a = get(), b = mod;\r\
    \n    while (b != 0) {\r\n      i32 q = a / b, x1_old = x1, a_old = a;\r\n   \
    \   x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\r\n    }\r\n    return\
    \ m32(x1);\r\n  }\r\n\r\n  m32 &operator=(const m32 &) = default;\r\n\r\n  m32\
    \ &operator+=(const m32 &rhs) {\r\n    v_ += rhs.v_ - mod2;\r\n    v_ += mod2\
    \ & -(v_ >> 31);\r\n    return *this;\r\n  }\r\n  m32 &operator-=(const m32 &rhs)\
    \ {\r\n    v_ -= rhs.v_;\r\n    v_ += mod2 & -(v_ >> 31);\r\n    return *this;\r\
    \n  }\r\n  m32 &operator*=(const m32 &rhs) {\r\n    v_ = reduce(u64(v_) * rhs.v_);\r\
    \n    return *this;\r\n  }\r\n  m32 &operator/=(const m32 &rhs) { return operator*=(rhs.inv());\
    \ }\r\n  friend m32 operator+(const m32 &lhs, const m32 &rhs) { return m32(lhs)\
    \ += rhs; }\r\n  friend m32 operator-(const m32 &lhs, const m32 &rhs) { return\
    \ m32(lhs) -= rhs; }\r\n  friend m32 operator*(const m32 &lhs, const m32 &rhs)\
    \ { return m32(lhs) *= rhs; }\r\n  friend m32 operator/(const m32 &lhs, const\
    \ m32 &rhs) { return m32(lhs) /= rhs; }\r\n  friend bool operator==(const m32\
    \ &lhs, const m32 &rhs) { return norm(lhs.v_) == norm(rhs.v_); }\r\n  friend bool\
    \ operator!=(const m32 &lhs, const m32 &rhs) { return norm(lhs.v_) != norm(rhs.v_);\
    \ }\r\n\r\n  friend std::istream &operator>>(std::istream &is, m32 &rhs) {\r\n\
    \    i32 x;\r\n    is >> x;\r\n    rhs = m32(x);\r\n    return is;\r\n  }\r\n\
    \  friend std::ostream &operator<<(std::ostream &os, const m32 &rhs) { return\
    \ os << rhs.get(); }\r\n\r\n  m32 pow(u64 y) const {\r\n    m32 res(1), x(*this);\r\
    \n    for (; y != 0; y >>= 1, x *= x)\r\n      if (y & 1) res *= x;\r\n    return\
    \ res;\r\n  }\r\n\r\nprivate:\r\n  static u32 reduce(u64 x) { return (x + u64(u32(x)\
    \ * r) * mod) >> 32; }\r\n  static u32 norm(u32 x) { return x - (mod & -((mod\
    \ - 1 - x) >> 31)); }\r\n\r\n  u32 v_;\r\n\r\n  static inline u32 r, r2, mod,\
    \ mod2;\r\n};\r\n\r\n// \u522B\u540D\r\ntemplate <int id>\r\nusing RuntimeMontModInt\
    \ = RuntimeMontgomeryModInt<id>;\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef RUNTIME_MONTGOMERY_MODINT_HEADER_HPP\r\n#define RUNTIME_MONTGOMERY_MODINT_HEADER_HPP\r\
    \n\r\n/**\r\n * @brief runtime Montgomery modint / \u8FD0\u884C\u65F6 Montgomery\
    \ \u53D6\u6A21\u7C7B\r\n *\r\n */\r\n\r\n#include <cstdint>\r\n#include <iostream>\r\
    \n#include <type_traits>\r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u8FD0\
    \u884C\u65F6 Montgomery \u53D6\u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
    \n * @author Nyaan\r\n * @note \u7EA6\u5B9A\u4E0D\u4F7F\u7528\u6A21\u677F\u4E2D\
    \ int \u4E3A\u8D1F\u6570\u7684\u5BF9\u8C61\r\n */\r\ntemplate <int>\r\nclass RuntimeMontgomeryModInt\
    \ {\r\npublic:\r\n  using i32 = std::int32_t;\r\n  using u32 = std::uint32_t;\r\
    \n  using u64 = std::uint64_t;\r\n  using m32 = RuntimeMontgomeryModInt;\r\n\r\
    \n  using value_type = u32;\r\n\r\n  static u32 get_mod() { return mod; }\r\n\r\
    \n  static bool set_mod(u32 m) {\r\n    if ((m & 1) == 0 || m == 1 || (m & (3U\
    \ << 30)) != 0) return false;\r\n    mod = m, mod2 = mod << 1;\r\n    u32 two\
    \ = 2, iv = mod * (two - mod * mod);\r\n    iv *= two - mod * iv;\r\n    iv *=\
    \ two - mod * iv;\r\n    r  = iv * (mod * iv - two);\r\n    r2 = -u64(mod) % mod;\r\
    \n    return true;\r\n  }\r\n\r\n  RuntimeMontgomeryModInt()  = default;\r\n \
    \ ~RuntimeMontgomeryModInt() = default;\r\n\r\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\r\n  RuntimeMontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) + i32(mod))\
    \ * r2)) {}\r\n\r\n  RuntimeMontgomeryModInt(const m32 &) = default;\r\n\r\n \
    \ u32 get() const { return norm(reduce(v_)); }\r\n\r\n  template <typename T,\
    \ std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  explicit operator T()\
    \ const {\r\n    return T(get());\r\n  }\r\n\r\n  m32 operator-() const {\r\n\
    \    m32 res;\r\n    res.v_ = (mod2 & -(v_ != 0)) - v_;\r\n    return res;\r\n\
    \  }\r\n\r\n  m32 inv() const {\r\n    i32 x1 = 1, x3 = 0, a = get(), b = mod;\r\
    \n    while (b != 0) {\r\n      i32 q = a / b, x1_old = x1, a_old = a;\r\n   \
    \   x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\r\n    }\r\n    return\
    \ m32(x1);\r\n  }\r\n\r\n  m32 &operator=(const m32 &) = default;\r\n\r\n  m32\
    \ &operator+=(const m32 &rhs) {\r\n    v_ += rhs.v_ - mod2;\r\n    v_ += mod2\
    \ & -(v_ >> 31);\r\n    return *this;\r\n  }\r\n  m32 &operator-=(const m32 &rhs)\
    \ {\r\n    v_ -= rhs.v_;\r\n    v_ += mod2 & -(v_ >> 31);\r\n    return *this;\r\
    \n  }\r\n  m32 &operator*=(const m32 &rhs) {\r\n    v_ = reduce(u64(v_) * rhs.v_);\r\
    \n    return *this;\r\n  }\r\n  m32 &operator/=(const m32 &rhs) { return operator*=(rhs.inv());\
    \ }\r\n  friend m32 operator+(const m32 &lhs, const m32 &rhs) { return m32(lhs)\
    \ += rhs; }\r\n  friend m32 operator-(const m32 &lhs, const m32 &rhs) { return\
    \ m32(lhs) -= rhs; }\r\n  friend m32 operator*(const m32 &lhs, const m32 &rhs)\
    \ { return m32(lhs) *= rhs; }\r\n  friend m32 operator/(const m32 &lhs, const\
    \ m32 &rhs) { return m32(lhs) /= rhs; }\r\n  friend bool operator==(const m32\
    \ &lhs, const m32 &rhs) { return norm(lhs.v_) == norm(rhs.v_); }\r\n  friend bool\
    \ operator!=(const m32 &lhs, const m32 &rhs) { return norm(lhs.v_) != norm(rhs.v_);\
    \ }\r\n\r\n  friend std::istream &operator>>(std::istream &is, m32 &rhs) {\r\n\
    \    i32 x;\r\n    is >> x;\r\n    rhs = m32(x);\r\n    return is;\r\n  }\r\n\
    \  friend std::ostream &operator<<(std::ostream &os, const m32 &rhs) { return\
    \ os << rhs.get(); }\r\n\r\n  m32 pow(u64 y) const {\r\n    m32 res(1), x(*this);\r\
    \n    for (; y != 0; y >>= 1, x *= x)\r\n      if (y & 1) res *= x;\r\n    return\
    \ res;\r\n  }\r\n\r\nprivate:\r\n  static u32 reduce(u64 x) { return (x + u64(u32(x)\
    \ * r) * mod) >> 32; }\r\n  static u32 norm(u32 x) { return x - (mod & -((mod\
    \ - 1 - x) >> 31)); }\r\n\r\n  u32 v_;\r\n\r\n  static inline u32 r, r2, mod,\
    \ mod2;\r\n};\r\n\r\n// \u522B\u540D\r\ntemplate <int id>\r\nusing RuntimeMontModInt\
    \ = RuntimeMontgomeryModInt<id>;\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: modint/runtime_Montgomery_modint.hpp
  requiredBy:
  - math/modulo/sqrt_mod.hpp
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - remote_test/yosupo/math/mod_sqrt.0.test.cpp
documentation_of: modint/runtime_Montgomery_modint.hpp
layout: document
redirect_from:
- /library/modint/runtime_Montgomery_modint.hpp
- /library/modint/runtime_Montgomery_modint.hpp.html
title: "runtime Montgomery modint / \u8FD0\u884C\u65F6 Montgomery \u53D6\u6A21\u7C7B"
---
