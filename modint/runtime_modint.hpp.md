---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: remote_test/yosupo/matrix/matrix_det.2.test.cpp
    title: remote_test/yosupo/matrix/matrix_det.2.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "runtime modint / \u8FD0\u884C\u65F6\u53D6\u6A21\u7C7B"
    links: []
  bundledCode: "#line 1 \"modint/runtime_modint.hpp\"\n\n\n\r\n/**\r\n * @brief runtime\
    \ modint / \u8FD0\u884C\u65F6\u53D6\u6A21\u7C7B\r\n *\r\n */\r\n\r\n#include <cstdint>\r\
    \n#include <iostream>\r\n#include <type_traits>\r\n\r\nnamespace lib {\r\n\r\n\
    template <int>\r\nclass RuntimeModInt {\r\npublic:\r\n  using i32 = std::int32_t;\r\
    \n  using u32 = std::uint32_t;\r\n  using u64 = std::uint64_t;\r\n  using m32\
    \ = RuntimeModInt;\r\n\r\n  using value_type = u32;\r\n\r\n  static u32 get_mod()\
    \ { return mod; }\r\n\r\n  static bool set_mod(u32 m) {\r\n    if (m == 1 || (m\
    \ & (1U << 31)) != 0) return false;\r\n    mod = mod_odd = m, offset = 0;\r\n\
    \    while ((mod_odd & 1) == 0) ++offset, mod_odd >>= 1;\r\n    mask    = (1 <<\
    \ offset) - 1;\r\n    u32 two = 2, iv = mod_odd * (two - mod_odd * mod_odd);\r\
    \n    iv *= two - mod_odd * iv;\r\n    iv *= two - mod_odd * iv;\r\n    r  = iv\
    \ * (mod_odd * iv - two);\r\n    r2 = -u64(mod_odd) % mod_odd;\r\n    return true;\r\
    \n  }\r\n\r\n  RuntimeModInt()  = default;\r\n  ~RuntimeModInt() = default;\r\n\
    \r\n  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\
    \n  RuntimeModInt(T v) : v_(transform(v % i32(mod) + i32(mod))) {}\r\n\r\n  RuntimeModInt(const\
    \ m32 &) = default;\r\n\r\n  u32 get() const {\r\n    u32 h = reduce(v_ >> offset);\r\
    \n    return ((h - v_) * r & mask) * mod_odd + h;\r\n  }\r\n\r\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  explicit operator\
    \ T() const {\r\n    return T(get());\r\n  }\r\n\r\n  m32 operator-() const {\r\
    \n    m32 res;\r\n    u32 h  = v_ >> offset;\r\n    res.v_ = (((mod_odd & -(h\
    \ != 0)) - h) << offset) | (-(v_ & mask) & mask);\r\n    return res;\r\n  }\r\n\
    \r\n  m32 inv() const {\r\n    i32 x1 = 1, x3 = 0, a = get(), b = mod;\r\n   \
    \ while (b != 0) {\r\n      i32 q = a / b, x1_old = x1, a_old = a;\r\n      x1\
    \ = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\r\n    }\r\n    return\
    \ m32(x1);\r\n  }\r\n\r\n  m32 &operator=(const m32 &) = default;\r\n\r\n  m32\
    \ &operator+=(const m32 &rhs) {\r\n    u32 h = (v_ >> offset) + (rhs.v_ >> offset)\
    \ - mod_odd;\r\n    v_    = ((h + (mod_odd & -(h >> 31))) << offset) | ((v_ +\
    \ rhs.v_) & mask);\r\n    return *this;\r\n  }\r\n  m32 &operator-=(const m32\
    \ &rhs) {\r\n    u32 h = (v_ >> offset) - (rhs.v_ >> offset);\r\n    v_    = ((h\
    \ + (mod_odd & -(h >> 31))) << offset) | ((v_ - rhs.v_) & mask);\r\n    return\
    \ *this;\r\n  }\r\n  m32 &operator*=(const m32 &rhs) {\r\n    v_ = (reduce(u64(v_\
    \ >> offset) * (rhs.v_ >> offset)) << offset) | ((v_ * rhs.v_) & mask);\r\n  \
    \  return *this;\r\n  }\r\n  m32 &operator/=(const m32 &rhs) { return operator*=(rhs.inv());\
    \ }\r\n  friend m32 operator+(const m32 &lhs, const m32 &rhs) { return m32(lhs)\
    \ += rhs; }\r\n  friend m32 operator-(const m32 &lhs, const m32 &rhs) { return\
    \ m32(lhs) -= rhs; }\r\n  friend m32 operator*(const m32 &lhs, const m32 &rhs)\
    \ { return m32(lhs) *= rhs; }\r\n  friend m32 operator/(const m32 &lhs, const\
    \ m32 &rhs) { return m32(lhs) /= rhs; }\r\n  friend bool operator==(const m32\
    \ &lhs, const m32 &rhs) { return lhs.v_ == rhs.v_; }\r\n  friend bool operator!=(const\
    \ m32 &lhs, const m32 &rhs) { return lhs.v_ != rhs.v_; }\r\n\r\n  friend std::istream\
    \ &operator>>(std::istream &is, m32 &rhs) {\r\n    i32 x;\r\n    is >> x;\r\n\
    \    rhs = m32(x);\r\n    return is;\r\n  }\r\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const m32 &rhs) { return os << rhs.get(); }\r\n\r\n  m32 pow(u64 y) const\
    \ {\r\n    m32 res(1), x(*this);\r\n    for (; y != 0; y >>= 1, x *= x)\r\n  \
    \    if (y & 1) res *= x;\r\n    return res;\r\n  }\r\n\r\nprivate:\r\n  static\
    \ u32 reduce(u64 x) {\r\n    u32 t = (x + u64(u32(x) * r) * mod_odd) >> 32;\r\n\
    \    return t - (mod_odd & -((mod_odd - 1 - t) >> 31));\r\n  }\r\n  static u32\
    \ transform(u32 x) { return (reduce(u64(x) % mod_odd * r2) << offset) | (x & mask);\
    \ }\r\n\r\n  u32 v_;\r\n  static inline u32 r, r2, mod, mod_odd, offset, mask;\r\
    \n};\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef RUNTIME_MODINT_HEADER_HPP\r\n#define RUNTIME_MODINT_HEADER_HPP\r\n\
    \r\n/**\r\n * @brief runtime modint / \u8FD0\u884C\u65F6\u53D6\u6A21\u7C7B\r\n\
    \ *\r\n */\r\n\r\n#include <cstdint>\r\n#include <iostream>\r\n#include <type_traits>\r\
    \n\r\nnamespace lib {\r\n\r\ntemplate <int>\r\nclass RuntimeModInt {\r\npublic:\r\
    \n  using i32 = std::int32_t;\r\n  using u32 = std::uint32_t;\r\n  using u64 =\
    \ std::uint64_t;\r\n  using m32 = RuntimeModInt;\r\n\r\n  using value_type = u32;\r\
    \n\r\n  static u32 get_mod() { return mod; }\r\n\r\n  static bool set_mod(u32\
    \ m) {\r\n    if (m == 1 || (m & (1U << 31)) != 0) return false;\r\n    mod =\
    \ mod_odd = m, offset = 0;\r\n    while ((mod_odd & 1) == 0) ++offset, mod_odd\
    \ >>= 1;\r\n    mask    = (1 << offset) - 1;\r\n    u32 two = 2, iv = mod_odd\
    \ * (two - mod_odd * mod_odd);\r\n    iv *= two - mod_odd * iv;\r\n    iv *= two\
    \ - mod_odd * iv;\r\n    r  = iv * (mod_odd * iv - two);\r\n    r2 = -u64(mod_odd)\
    \ % mod_odd;\r\n    return true;\r\n  }\r\n\r\n  RuntimeModInt()  = default;\r\
    \n  ~RuntimeModInt() = default;\r\n\r\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\r\n  RuntimeModInt(T v) : v_(transform(v % i32(mod) + i32(mod))) {}\r\
    \n\r\n  RuntimeModInt(const m32 &) = default;\r\n\r\n  u32 get() const {\r\n \
    \   u32 h = reduce(v_ >> offset);\r\n    return ((h - v_) * r & mask) * mod_odd\
    \ + h;\r\n  }\r\n\r\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\r\n  explicit operator T() const {\r\n    return T(get());\r\n  }\r\
    \n\r\n  m32 operator-() const {\r\n    m32 res;\r\n    u32 h  = v_ >> offset;\r\
    \n    res.v_ = (((mod_odd & -(h != 0)) - h) << offset) | (-(v_ & mask) & mask);\r\
    \n    return res;\r\n  }\r\n\r\n  m32 inv() const {\r\n    i32 x1 = 1, x3 = 0,\
    \ a = get(), b = mod;\r\n    while (b != 0) {\r\n      i32 q = a / b, x1_old =\
    \ x1, a_old = a;\r\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b\
    \ * q;\r\n    }\r\n    return m32(x1);\r\n  }\r\n\r\n  m32 &operator=(const m32\
    \ &) = default;\r\n\r\n  m32 &operator+=(const m32 &rhs) {\r\n    u32 h = (v_\
    \ >> offset) + (rhs.v_ >> offset) - mod_odd;\r\n    v_    = ((h + (mod_odd & -(h\
    \ >> 31))) << offset) | ((v_ + rhs.v_) & mask);\r\n    return *this;\r\n  }\r\n\
    \  m32 &operator-=(const m32 &rhs) {\r\n    u32 h = (v_ >> offset) - (rhs.v_ >>\
    \ offset);\r\n    v_    = ((h + (mod_odd & -(h >> 31))) << offset) | ((v_ - rhs.v_)\
    \ & mask);\r\n    return *this;\r\n  }\r\n  m32 &operator*=(const m32 &rhs) {\r\
    \n    v_ = (reduce(u64(v_ >> offset) * (rhs.v_ >> offset)) << offset) | ((v_ *\
    \ rhs.v_) & mask);\r\n    return *this;\r\n  }\r\n  m32 &operator/=(const m32\
    \ &rhs) { return operator*=(rhs.inv()); }\r\n  friend m32 operator+(const m32\
    \ &lhs, const m32 &rhs) { return m32(lhs) += rhs; }\r\n  friend m32 operator-(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) -= rhs; }\r\n  friend m32 operator*(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }\r\n  friend m32 operator/(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) /= rhs; }\r\n  friend bool operator==(const\
    \ m32 &lhs, const m32 &rhs) { return lhs.v_ == rhs.v_; }\r\n  friend bool operator!=(const\
    \ m32 &lhs, const m32 &rhs) { return lhs.v_ != rhs.v_; }\r\n\r\n  friend std::istream\
    \ &operator>>(std::istream &is, m32 &rhs) {\r\n    i32 x;\r\n    is >> x;\r\n\
    \    rhs = m32(x);\r\n    return is;\r\n  }\r\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const m32 &rhs) { return os << rhs.get(); }\r\n\r\n  m32 pow(u64 y) const\
    \ {\r\n    m32 res(1), x(*this);\r\n    for (; y != 0; y >>= 1, x *= x)\r\n  \
    \    if (y & 1) res *= x;\r\n    return res;\r\n  }\r\n\r\nprivate:\r\n  static\
    \ u32 reduce(u64 x) {\r\n    u32 t = (x + u64(u32(x) * r) * mod_odd) >> 32;\r\n\
    \    return t - (mod_odd & -((mod_odd - 1 - t) >> 31));\r\n  }\r\n  static u32\
    \ transform(u32 x) { return (reduce(u64(x) % mod_odd * r2) << offset) | (x & mask);\
    \ }\r\n\r\n  u32 v_;\r\n  static inline u32 r, r2, mod, mod_odd, offset, mask;\r\
    \n};\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: modint/runtime_modint.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - remote_test/yosupo/matrix/matrix_det.2.test.cpp
documentation_of: modint/runtime_modint.hpp
layout: document
redirect_from:
- /library/modint/runtime_modint.hpp
- /library/modint/runtime_modint.hpp.html
title: "runtime modint / \u8FD0\u884C\u65F6\u53D6\u6A21\u7C7B"
---
