---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/modulo/sqrt_mod.hpp
    title: "square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/mod_sqrt.0.test.cpp
    title: remote_test/yosupo/math/mod_sqrt.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "runtime Montgomery modint / \u8FD0\u884C\u65F6 Montgomery \u53D6\
      \u6A21\u7C7B"
    links:
    - https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp
  bundledCode: "#line 1 \"modint/runtime_Montgomery_modint.hpp\"\n\n\n\n/**\n * @brief\
    \ runtime Montgomery modint / \u8FD0\u884C\u65F6 Montgomery \u53D6\u6A21\u7C7B\
    \n *\n */\n\n#include <cstdint>\n#include <iostream>\n#include <type_traits>\n\
    \nnamespace lib {\n\n/**\n * @brief \u8FD0\u884C\u65F6 Montgomery \u53D6\u6A21\
    \u7C7B\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\n\
    \ * @author Nyaan\n * @note \u7EA6\u5B9A\u4E0D\u4F7F\u7528\u6A21\u677F\u4E2D int\
    \ \u4E3A\u8D1F\u6570\u7684\u5BF9\u8C61\n */\ntemplate <int> class RuntimeMontgomeryModInt\
    \ {\npublic:\n  using i32 = std::int32_t;\n  using u32 = std::uint32_t;\n  using\
    \ u64 = std::uint64_t;\n  using m32 = RuntimeMontgomeryModInt;\n\n  using value_type\
    \ = u32;\n\n  static u32 get_mod() { return mod; }\n\n  static bool set_mod(u32\
    \ m) {\n    if ((m & 1) == 0 || m == 1 || (m & (3U << 30)) != 0) return false;\n\
    \    mod = m, mod2 = mod << 1;\n    u32 two = 2, iv = mod * (two - mod * mod);\n\
    \    iv *= two - mod * iv;\n    iv *= two - mod * iv;\n    r = iv * (mod * iv\
    \ - two);\n    r2 = -u64(mod) % mod;\n    return true;\n  }\n\n  RuntimeMontgomeryModInt()\
    \ = default;\n  ~RuntimeMontgomeryModInt() = default;\n\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\n  RuntimeMontgomeryModInt(T\
    \ v) : v_(reduce(u64(v % i32(mod) + i32(mod)) * r2)) {}\n\n  RuntimeMontgomeryModInt(const\
    \ m32 &) = default;\n\n  u32 get() const { return norm(reduce(v_)); }\n\n  template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\n  explicit constexpr\
    \ operator T() const {\n    return T(get());\n  }\n\n  m32 operator-() const {\n\
    \    m32 res;\n    res.v_ = (mod2 & -(v_ != 0)) - v_;\n    return res;\n  }\n\n\
    \  m32 inv() const {\n    i32 x1 = 1, x3 = 0, a = get(), b = mod;\n    while (b\
    \ != 0) {\n      i32 q = a / b, x1_old = x1, a_old = a;\n      x1 = x3, x3 = x1_old\
    \ - x3 * q, a = b, b = a_old - b * q;\n    }\n    return m32(x1);\n  }\n\n  m32\
    \ &operator+=(const m32 &rhs) {\n    v_ += rhs.v_ - mod2;\n    v_ += mod2 & -(v_\
    \ >> 31);\n    return *this;\n  }\n  m32 &operator-=(const m32 &rhs) {\n    v_\
    \ -= rhs.v_;\n    v_ += mod2 & -(v_ >> 31);\n    return *this;\n  }\n  m32 &operator*=(const\
    \ m32 &rhs) {\n    v_ = reduce(u64(v_) * rhs.v_);\n    return *this;\n  }\n  m32\
    \ &operator/=(const m32 &rhs) { return operator*=(rhs.inv()); }\n  friend m32\
    \ operator+(const m32 &lhs, const m32 &rhs) { return m32(lhs) += rhs; }\n  friend\
    \ m32 operator-(const m32 &lhs, const m32 &rhs) { return m32(lhs) -= rhs; }\n\
    \  friend m32 operator*(const m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs;\
    \ }\n  friend m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs)\
    \ /= rhs; }\n  friend bool operator==(const m32 &lhs, const m32 &rhs) { return\
    \ norm(lhs.v_) == norm(rhs.v_); }\n  friend bool operator!=(const m32 &lhs, const\
    \ m32 &rhs) { return norm(lhs.v_) != norm(rhs.v_); }\n\n  friend std::istream\
    \ &operator>>(std::istream &is, m32 &rhs) {\n    i32 x;\n    is >> x;\n    rhs\
    \ = m32(x);\n    return is;\n  }\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const m32 &rhs) { return os << rhs.get(); }\n\n  m32 pow(u64 y) const {\n\
    \    m32 res(1), x(*this);\n    for (; y != 0; y >>= 1, x *= x)\n      if (y &\
    \ 1) res *= x;\n    return res;\n  }\n\nprivate:\n  static u32 reduce(u64 x) {\
    \ return (x + u64(u32(x) * r) * mod) >> 32; }\n  static u32 norm(u32 x) { return\
    \ x - (mod & -((mod - 1 - x) >> 31)); }\n\n  u32 v_;\n\n  static inline u32 r,\
    \ r2, mod, mod2;\n};\n\n// \u522B\u540D\ntemplate <int id> using RuntimeMontModInt\
    \ = RuntimeMontgomeryModInt<id>;\n\n} // namespace lib\n\n\n"
  code: "#ifndef RUNTIME_MONTGOMERY_MODINT_HEADER_HPP\n#define RUNTIME_MONTGOMERY_MODINT_HEADER_HPP\n\
    \n/**\n * @brief runtime Montgomery modint / \u8FD0\u884C\u65F6 Montgomery \u53D6\
    \u6A21\u7C7B\n *\n */\n\n#include <cstdint>\n#include <iostream>\n#include <type_traits>\n\
    \nnamespace lib {\n\n/**\n * @brief \u8FD0\u884C\u65F6 Montgomery \u53D6\u6A21\
    \u7C7B\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\n\
    \ * @author Nyaan\n * @note \u7EA6\u5B9A\u4E0D\u4F7F\u7528\u6A21\u677F\u4E2D int\
    \ \u4E3A\u8D1F\u6570\u7684\u5BF9\u8C61\n */\ntemplate <int> class RuntimeMontgomeryModInt\
    \ {\npublic:\n  using i32 = std::int32_t;\n  using u32 = std::uint32_t;\n  using\
    \ u64 = std::uint64_t;\n  using m32 = RuntimeMontgomeryModInt;\n\n  using value_type\
    \ = u32;\n\n  static u32 get_mod() { return mod; }\n\n  static bool set_mod(u32\
    \ m) {\n    if ((m & 1) == 0 || m == 1 || (m & (3U << 30)) != 0) return false;\n\
    \    mod = m, mod2 = mod << 1;\n    u32 two = 2, iv = mod * (two - mod * mod);\n\
    \    iv *= two - mod * iv;\n    iv *= two - mod * iv;\n    r = iv * (mod * iv\
    \ - two);\n    r2 = -u64(mod) % mod;\n    return true;\n  }\n\n  RuntimeMontgomeryModInt()\
    \ = default;\n  ~RuntimeMontgomeryModInt() = default;\n\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\n  RuntimeMontgomeryModInt(T\
    \ v) : v_(reduce(u64(v % i32(mod) + i32(mod)) * r2)) {}\n\n  RuntimeMontgomeryModInt(const\
    \ m32 &) = default;\n\n  u32 get() const { return norm(reduce(v_)); }\n\n  template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\n  explicit constexpr\
    \ operator T() const {\n    return T(get());\n  }\n\n  m32 operator-() const {\n\
    \    m32 res;\n    res.v_ = (mod2 & -(v_ != 0)) - v_;\n    return res;\n  }\n\n\
    \  m32 inv() const {\n    i32 x1 = 1, x3 = 0, a = get(), b = mod;\n    while (b\
    \ != 0) {\n      i32 q = a / b, x1_old = x1, a_old = a;\n      x1 = x3, x3 = x1_old\
    \ - x3 * q, a = b, b = a_old - b * q;\n    }\n    return m32(x1);\n  }\n\n  m32\
    \ &operator+=(const m32 &rhs) {\n    v_ += rhs.v_ - mod2;\n    v_ += mod2 & -(v_\
    \ >> 31);\n    return *this;\n  }\n  m32 &operator-=(const m32 &rhs) {\n    v_\
    \ -= rhs.v_;\n    v_ += mod2 & -(v_ >> 31);\n    return *this;\n  }\n  m32 &operator*=(const\
    \ m32 &rhs) {\n    v_ = reduce(u64(v_) * rhs.v_);\n    return *this;\n  }\n  m32\
    \ &operator/=(const m32 &rhs) { return operator*=(rhs.inv()); }\n  friend m32\
    \ operator+(const m32 &lhs, const m32 &rhs) { return m32(lhs) += rhs; }\n  friend\
    \ m32 operator-(const m32 &lhs, const m32 &rhs) { return m32(lhs) -= rhs; }\n\
    \  friend m32 operator*(const m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs;\
    \ }\n  friend m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs)\
    \ /= rhs; }\n  friend bool operator==(const m32 &lhs, const m32 &rhs) { return\
    \ norm(lhs.v_) == norm(rhs.v_); }\n  friend bool operator!=(const m32 &lhs, const\
    \ m32 &rhs) { return norm(lhs.v_) != norm(rhs.v_); }\n\n  friend std::istream\
    \ &operator>>(std::istream &is, m32 &rhs) {\n    i32 x;\n    is >> x;\n    rhs\
    \ = m32(x);\n    return is;\n  }\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const m32 &rhs) { return os << rhs.get(); }\n\n  m32 pow(u64 y) const {\n\
    \    m32 res(1), x(*this);\n    for (; y != 0; y >>= 1, x *= x)\n      if (y &\
    \ 1) res *= x;\n    return res;\n  }\n\nprivate:\n  static u32 reduce(u64 x) {\
    \ return (x + u64(u32(x) * r) * mod) >> 32; }\n  static u32 norm(u32 x) { return\
    \ x - (mod & -((mod - 1 - x) >> 31)); }\n\n  u32 v_;\n\n  static inline u32 r,\
    \ r2, mod, mod2;\n};\n\n// \u522B\u540D\ntemplate <int id> using RuntimeMontModInt\
    \ = RuntimeMontgomeryModInt<id>;\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: modint/runtime_Montgomery_modint.hpp
  requiredBy:
  - math/modulo/sqrt_mod.hpp
  timestamp: '2021-07-01 12:57:32+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/mod_sqrt.0.test.cpp
documentation_of: modint/runtime_Montgomery_modint.hpp
layout: document
redirect_from:
- /library/modint/runtime_Montgomery_modint.hpp
- /library/modint/runtime_Montgomery_modint.hpp.html
title: "runtime Montgomery modint / \u8FD0\u884C\u65F6 Montgomery \u53D6\u6A21\u7C7B"
---
