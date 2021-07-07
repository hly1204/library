---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "runtime modint / \u8FD0\u884C\u65F6\u53D6\u6A21\u7C7B"
    links: []
  bundledCode: "#line 1 \"modint/runtime_modint.hpp\"\n\n\n\n/**\n * @brief runtime\
    \ modint / \u8FD0\u884C\u65F6\u53D6\u6A21\u7C7B\n *\n */\n\n#include <cstdint>\n\
    #include <iostream>\n#include <type_traits>\n\nnamespace lib {\n\ntemplate <int>\
    \ class RuntimeModInt {\npublic:\n  using i32 = std::int32_t;\n  using u32 = std::uint32_t;\n\
    \  using u64 = std::uint64_t;\n  using m32 = RuntimeModInt;\n\n  using value_type\
    \ = u32;\n\n  static u32 get_mod() { return mod; }\n\n  static bool set_mod(u32\
    \ m) {\n    if (m == 1 || (m & (1U << 31)) != 0) return false;\n    mod = mod_odd\
    \ = m, offset = 0;\n    while ((mod_odd & 1) == 0) ++offset, mod_odd >>= 1;\n\
    \    mask = (1 << offset) - 1;\n    u32 two = 2, iv = mod_odd * (two - mod_odd\
    \ * mod_odd);\n    iv *= two - mod_odd * iv;\n    iv *= two - mod_odd * iv;\n\
    \    r = iv * (mod_odd * iv - two);\n    r2 = -u64(mod_odd) % mod_odd;\n    return\
    \ true;\n  }\n\n  RuntimeModInt() = default;\n  ~RuntimeModInt() = default;\n\n\
    \  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\n \
    \ RuntimeModInt(T v) : v_(transform(v % i32(mod) + i32(mod))) {}\n\n  RuntimeModInt(const\
    \ m32 &) = default;\n\n  u32 get() const {\n    u32 h = reduce(v_ >> offset);\n\
    \    return ((h - v_) * r & mask) * mod_odd + h;\n  }\n\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\n  explicit operator T()\
    \ const {\n    return T(get());\n  }\n\n  m32 operator-() const {\n    m32 res;\n\
    \    u32 h = v_ >> offset;\n    res.v_ = (((mod_odd & -(h != 0)) - h) << offset)\
    \ | (-(v_ & mask) & mask);\n    return res;\n  }\n\n  m32 inv() const {\n    i32\
    \ x1 = 1, x3 = 0, a = get(), b = mod;\n    while (b != 0) {\n      i32 q = a /\
    \ b, x1_old = x1, a_old = a;\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b =\
    \ a_old - b * q;\n    }\n    return m32(x1);\n  }\n\n  m32 &operator=(const m32\
    \ &) = default;\n\n  m32 &operator+=(const m32 &rhs) {\n    u32 h = (v_ >> offset)\
    \ + (rhs.v_ >> offset) - mod_odd;\n    v_ = ((h + (mod_odd & -(h >> 31))) << offset)\
    \ | ((v_ + rhs.v_) & mask);\n    return *this;\n  }\n  m32 &operator-=(const m32\
    \ &rhs) {\n    u32 h = (v_ >> offset) - (rhs.v_ >> offset);\n    v_ = ((h + (mod_odd\
    \ & -(h >> 31))) << offset) | ((v_ - rhs.v_) & mask);\n    return *this;\n  }\n\
    \  m32 &operator*=(const m32 &rhs) {\n    v_ = (reduce(u64(v_ >> offset) * (rhs.v_\
    \ >> offset)) << offset) | ((v_ * rhs.v_) & mask);\n    return *this;\n  }\n \
    \ m32 &operator/=(const m32 &rhs) { return operator*=(rhs.inv()); }\n  friend\
    \ m32 operator+(const m32 &lhs, const m32 &rhs) { return m32(lhs) += rhs; }\n\
    \  friend m32 operator-(const m32 &lhs, const m32 &rhs) { return m32(lhs) -= rhs;\
    \ }\n  friend m32 operator*(const m32 &lhs, const m32 &rhs) { return m32(lhs)\
    \ *= rhs; }\n  friend m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs)\
    \ /= rhs; }\n  friend bool operator==(const m32 &lhs, const m32 &rhs) { return\
    \ lhs.v_ == rhs.v_; }\n  friend bool operator!=(const m32 &lhs, const m32 &rhs)\
    \ { return lhs.v_ != rhs.v_; }\n\n  friend std::istream &operator>>(std::istream\
    \ &is, m32 &rhs) {\n    i32 x;\n    is >> x;\n    rhs = m32(x);\n    return is;\n\
    \  }\n  friend std::ostream &operator<<(std::ostream &os, const m32 &rhs) { return\
    \ os << rhs.get(); }\n\n  m32 pow(u64 y) const {\n    m32 res(1), x(*this);\n\
    \    for (; y != 0; y >>= 1, x *= x)\n      if (y & 1) res *= x;\n    return res;\n\
    \  }\n\nprivate:\n  static u32 reduce(u64 x) {\n    u32 t = (x + u64(u32(x) *\
    \ r) * mod_odd) >> 32;\n    return t - (mod_odd & -((mod_odd - 1 - t) >> 31));\n\
    \  }\n  static u32 transform(u32 x) { return (reduce(u64(x) % mod_odd * r2) <<\
    \ offset) | (x & mask); }\n\n  u32 v_;\n  static inline u32 r, r2, mod, mod_odd,\
    \ offset, mask;\n};\n\n} // namespace lib\n\n\n"
  code: "#ifndef RUNTIME_MODINT_HEADER_HPP\n#define RUNTIME_MODINT_HEADER_HPP\n\n\
    /**\n * @brief runtime modint / \u8FD0\u884C\u65F6\u53D6\u6A21\u7C7B\n *\n */\n\
    \n#include <cstdint>\n#include <iostream>\n#include <type_traits>\n\nnamespace\
    \ lib {\n\ntemplate <int> class RuntimeModInt {\npublic:\n  using i32 = std::int32_t;\n\
    \  using u32 = std::uint32_t;\n  using u64 = std::uint64_t;\n  using m32 = RuntimeModInt;\n\
    \n  using value_type = u32;\n\n  static u32 get_mod() { return mod; }\n\n  static\
    \ bool set_mod(u32 m) {\n    if (m == 1 || (m & (1U << 31)) != 0) return false;\n\
    \    mod = mod_odd = m, offset = 0;\n    while ((mod_odd & 1) == 0) ++offset,\
    \ mod_odd >>= 1;\n    mask = (1 << offset) - 1;\n    u32 two = 2, iv = mod_odd\
    \ * (two - mod_odd * mod_odd);\n    iv *= two - mod_odd * iv;\n    iv *= two -\
    \ mod_odd * iv;\n    r = iv * (mod_odd * iv - two);\n    r2 = -u64(mod_odd) %\
    \ mod_odd;\n    return true;\n  }\n\n  RuntimeModInt() = default;\n  ~RuntimeModInt()\
    \ = default;\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  RuntimeModInt(T v) : v_(transform(v % i32(mod) + i32(mod))) {}\n\
    \n  RuntimeModInt(const m32 &) = default;\n\n  u32 get() const {\n    u32 h =\
    \ reduce(v_ >> offset);\n    return ((h - v_) * r & mask) * mod_odd + h;\n  }\n\
    \n  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\n\
    \  explicit operator T() const {\n    return T(get());\n  }\n\n  m32 operator-()\
    \ const {\n    m32 res;\n    u32 h = v_ >> offset;\n    res.v_ = (((mod_odd &\
    \ -(h != 0)) - h) << offset) | (-(v_ & mask) & mask);\n    return res;\n  }\n\n\
    \  m32 inv() const {\n    i32 x1 = 1, x3 = 0, a = get(), b = mod;\n    while (b\
    \ != 0) {\n      i32 q = a / b, x1_old = x1, a_old = a;\n      x1 = x3, x3 = x1_old\
    \ - x3 * q, a = b, b = a_old - b * q;\n    }\n    return m32(x1);\n  }\n\n  m32\
    \ &operator=(const m32 &) = default;\n\n  m32 &operator+=(const m32 &rhs) {\n\
    \    u32 h = (v_ >> offset) + (rhs.v_ >> offset) - mod_odd;\n    v_ = ((h + (mod_odd\
    \ & -(h >> 31))) << offset) | ((v_ + rhs.v_) & mask);\n    return *this;\n  }\n\
    \  m32 &operator-=(const m32 &rhs) {\n    u32 h = (v_ >> offset) - (rhs.v_ >>\
    \ offset);\n    v_ = ((h + (mod_odd & -(h >> 31))) << offset) | ((v_ - rhs.v_)\
    \ & mask);\n    return *this;\n  }\n  m32 &operator*=(const m32 &rhs) {\n    v_\
    \ = (reduce(u64(v_ >> offset) * (rhs.v_ >> offset)) << offset) | ((v_ * rhs.v_)\
    \ & mask);\n    return *this;\n  }\n  m32 &operator/=(const m32 &rhs) { return\
    \ operator*=(rhs.inv()); }\n  friend m32 operator+(const m32 &lhs, const m32 &rhs)\
    \ { return m32(lhs) += rhs; }\n  friend m32 operator-(const m32 &lhs, const m32\
    \ &rhs) { return m32(lhs) -= rhs; }\n  friend m32 operator*(const m32 &lhs, const\
    \ m32 &rhs) { return m32(lhs) *= rhs; }\n  friend m32 operator/(const m32 &lhs,\
    \ const m32 &rhs) { return m32(lhs) /= rhs; }\n  friend bool operator==(const\
    \ m32 &lhs, const m32 &rhs) { return lhs.v_ == rhs.v_; }\n  friend bool operator!=(const\
    \ m32 &lhs, const m32 &rhs) { return lhs.v_ != rhs.v_; }\n\n  friend std::istream\
    \ &operator>>(std::istream &is, m32 &rhs) {\n    i32 x;\n    is >> x;\n    rhs\
    \ = m32(x);\n    return is;\n  }\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const m32 &rhs) { return os << rhs.get(); }\n\n  m32 pow(u64 y) const {\n\
    \    m32 res(1), x(*this);\n    for (; y != 0; y >>= 1, x *= x)\n      if (y &\
    \ 1) res *= x;\n    return res;\n  }\n\nprivate:\n  static u32 reduce(u64 x) {\n\
    \    u32 t = (x + u64(u32(x) * r) * mod_odd) >> 32;\n    return t - (mod_odd &\
    \ -((mod_odd - 1 - t) >> 31));\n  }\n  static u32 transform(u32 x) { return (reduce(u64(x)\
    \ % mod_odd * r2) << offset) | (x & mask); }\n\n  u32 v_;\n  static inline u32\
    \ r, r2, mod, mod_odd, offset, mask;\n};\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: modint/runtime_modint.hpp
  requiredBy: []
  timestamp: '2021-07-08 03:55:34+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: modint/runtime_modint.hpp
layout: document
redirect_from:
- /library/modint/runtime_modint.hpp
- /library/modint/runtime_modint.hpp.html
title: "runtime modint / \u8FD0\u884C\u65F6\u53D6\u6A21\u7C7B"
---
