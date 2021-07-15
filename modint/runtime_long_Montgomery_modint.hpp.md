---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/basic/integer_factorization_Pollard_rho.hpp
    title: "integer factorization Pollard's rho / \u6574\u6570\u5206\u89E3 Pollard\
      \ \u7684 rho \u7B97\u6CD5"
  - icon: ':x:'
    path: math/modulo/sqrt_mod.hpp
    title: "square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/factorize.0.test.cpp
    title: remote_test/yosupo/math/factorize.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/mod_sqrt.0.test.cpp
    title: remote_test/yosupo/math/mod_sqrt.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: "runtime long Montgomery modint / \u8FD0\u884C\u65F6\u957F\u6574\
      \u578B Montgomery \u53D6\u6A21\u7C7B"
    links:
    - https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp
  bundledCode: "#line 1 \"modint/runtime_long_Montgomery_modint.hpp\"\n\n\n\r\n/**\r\
    \n * @brief runtime long Montgomery modint / \u8FD0\u884C\u65F6\u957F\u6574\u578B\
    \ Montgomery \u53D6\u6A21\u7C7B\r\n *\r\n */\r\n\r\n#include <cassert>\r\n#include\
    \ <cstdint>\r\n#include <iostream>\r\n#include <tuple>\r\n#include <type_traits>\r\
    \n\r\n#ifdef _MSC_VER\r\n  #include <intrin.h>\r\n#endif\r\n\r\nnamespace lib\
    \ {\r\n\r\n/**\r\n * @brief \u8FD0\u884C\u65F6\u957F\u6574\u578B Montgomery \u53D6\
    \u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
    \n * @author Nyaan\r\n * @note \u7EA6\u5B9A\u4E0D\u4F7F\u7528\u6A21\u677F\u4E2D\
    \ int \u4E3A\u8D1F\u6570\u7684\u5BF9\u8C61\r\n */\r\ntemplate <int>\r\nclass RuntimeLongMontgomeryModInt\
    \ {\r\npublic:\r\n  using u32 = std::uint32_t;\r\n  using i64 = std::int64_t;\r\
    \n  using u64 = std::uint64_t;\r\n  using m64 = RuntimeLongMontgomeryModInt;\r\
    \n\r\n  using value_type = u64;\r\n\r\n  static u64 get_mod() { return mod; }\r\
    \n\r\n  static bool set_mod(u64 m) {\r\n    if ((m & 1) == 0 || m == 1 || (m &\
    \ (1ULL << 63)) != 0) return false;\r\n    mod = m;\r\n    r   = get_r();\r\n\
    \    r2  = get_r2();\r\n    return true;\r\n  }\r\n\r\n  RuntimeLongMontgomeryModInt()\
    \  = default;\r\n  ~RuntimeLongMontgomeryModInt() = default;\r\n\r\n  template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  RuntimeLongMontgomeryModInt(T\
    \ v) : v_(reduce(mul(norm(v % i64(mod)), r2))) {}\r\n\r\n  RuntimeLongMontgomeryModInt(const\
    \ m64 &) = default;\r\n\r\n  u64 get() const { return reduce({0, v_}); }\r\n\r\
    \n  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n\
    \  explicit operator T() const {\r\n    return T(get());\r\n  }\r\n\r\n  m64 operator-()\
    \ const {\r\n    m64 res;\r\n    res.v_ = (mod & -(v_ != 0)) - v_;\r\n    return\
    \ res;\r\n  }\r\n\r\n  m64 inv() const {\r\n    i64 x1 = 1, x3 = 0, a = get(),\
    \ b = mod;\r\n    while (b != 0) {\r\n      i64 q = a / b, x1_old = x1, a_old\
    \ = a;\r\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\r\n \
    \   }\r\n    return m64(x1);\r\n  }\r\n\r\n  m64 &operator=(const m64 &) = default;\r\
    \n\r\n  m64 &operator+=(const m64 &rhs) {\r\n    v_ += rhs.v_ - mod;\r\n    v_\
    \ += mod & -(v_ >> 63);\r\n    return *this;\r\n  }\r\n  m64 &operator-=(const\
    \ m64 &rhs) {\r\n    v_ -= rhs.v_;\r\n    v_ += mod & -(v_ >> 63);\r\n    return\
    \ *this;\r\n  }\r\n  m64 &operator*=(const m64 &rhs) {\r\n    v_ = reduce(mul(v_,\
    \ rhs.v_));\r\n    return *this;\r\n  }\r\n  m64 &operator/=(const m64 &rhs) {\
    \ return operator*=(rhs.inv()); }\r\n  friend m64 operator+(const m64 &lhs, const\
    \ m64 &rhs) { return m64(lhs) += rhs; }\r\n  friend m64 operator-(const m64 &lhs,\
    \ const m64 &rhs) { return m64(lhs) -= rhs; }\r\n  friend m64 operator*(const\
    \ m64 &lhs, const m64 &rhs) { return m64(lhs) *= rhs; }\r\n  friend m64 operator/(const\
    \ m64 &lhs, const m64 &rhs) { return m64(lhs) /= rhs; }\r\n  friend bool operator==(const\
    \ m64 &lhs, const m64 &rhs) { return lhs.v_ == rhs.v_; }\r\n  friend bool operator!=(const\
    \ m64 &lhs, const m64 &rhs) { return lhs.v_ != rhs.v_; }\r\n\r\n  friend std::istream\
    \ &operator>>(std::istream &is, m64 &rhs) {\r\n    i64 x;\r\n    is >> x;\r\n\
    \    rhs = m64(x);\r\n    return is;\r\n  }\r\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const m64 &rhs) { return os << rhs.get(); }\r\n\r\n  m64 pow(u64 y) const\
    \ {\r\n    m64 res(1), x(*this);\r\n    for (; y != 0; y >>= 1, x *= x)\r\n  \
    \    if (y & 1) res *= x;\r\n    return res;\r\n  }\r\n\r\nprivate:\r\n  static\
    \ std::pair<u64, u64> mul(u64 x, u64 y) {\r\n#ifdef __GNUC__\r\n    unsigned __int128\
    \ res = (unsigned __int128)x * y;\r\n    return {u64(res >> 64), u64(res)};\r\n\
    #elif defined(_MSC_VER)\r\n    u64 h, l = _umul128(x, y, &h);\r\n    return {h,\
    \ l};\r\n#else\r\n    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad\
    \ = a * d, bc = b * c;\r\n    return {a * c + (ad >> 32) + (bc >> 32) +\r\n  \
    \              (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32)) >>\
    \ 32),\r\n            x * y};\r\n#endif\r\n  }\r\n\r\n  static u64 mulh(u64 x,\
    \ u64 y) {\r\n#ifdef __GNUC__\r\n    return u64((unsigned __int128)x * y >> 64);\r\
    \n#elif defined(_MSC_VER)\r\n    return __umulh(x, y);\r\n#else\r\n    u64 a =\
    \ x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad = a * d, bc = b * c;\r\n  \
    \  return a * c + (ad >> 32) + (bc >> 32) +\r\n           (((ad & ~UINT32_C(0))\
    \ + (bc & ~UINT32_C(0)) + (b * d >> 32)) >> 32);\r\n#endif\r\n  }\r\n\r\n  static\
    \ u64 get_r() {\r\n    u64 two = 2, iv = mod * (two - mod * mod);\r\n    iv *=\
    \ two - mod * iv;\r\n    iv *= two - mod * iv;\r\n    iv *= two - mod * iv;\r\n\
    \    return iv * (two - mod * iv);\r\n  }\r\n\r\n  static u64 get_r2() {\r\n \
    \   u64 iv = -u64(mod) % mod;\r\n    for (int i = 0; i != 64; ++i)\r\n      if\
    \ ((iv <<= 1) >= mod) iv -= mod;\r\n    return iv;\r\n  }\r\n\r\n  static u64\
    \ reduce(const std::pair<u64, u64> &x) {\r\n    u64 res = x.first - mulh(x.second\
    \ * r, mod);\r\n    return res + (mod & -(res >> 63));\r\n  }\r\n\r\n  static\
    \ u64 norm(i64 x) { return x + (mod & -(x < 0)); }\r\n\r\n  u64 v_;\r\n\r\n  static\
    \ inline u64 mod, r, r2;\r\n};\r\n\r\ntemplate <int id>\r\nusing RuntimeLongMontModInt\
    \ = RuntimeLongMontgomeryModInt<id>;\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef RUNTIME_LONG_MONTGOMERY_MODINT_HEADER_HPP\r\n#define RUNTIME_LONG_MONTGOMERY_MODINT_HEADER_HPP\r\
    \n\r\n/**\r\n * @brief runtime long Montgomery modint / \u8FD0\u884C\u65F6\u957F\
    \u6574\u578B Montgomery \u53D6\u6A21\u7C7B\r\n *\r\n */\r\n\r\n#include <cassert>\r\
    \n#include <cstdint>\r\n#include <iostream>\r\n#include <tuple>\r\n#include <type_traits>\r\
    \n\r\n#ifdef _MSC_VER\r\n  #include <intrin.h>\r\n#endif\r\n\r\nnamespace lib\
    \ {\r\n\r\n/**\r\n * @brief \u8FD0\u884C\u65F6\u957F\u6574\u578B Montgomery \u53D6\
    \u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
    \n * @author Nyaan\r\n * @note \u7EA6\u5B9A\u4E0D\u4F7F\u7528\u6A21\u677F\u4E2D\
    \ int \u4E3A\u8D1F\u6570\u7684\u5BF9\u8C61\r\n */\r\ntemplate <int>\r\nclass RuntimeLongMontgomeryModInt\
    \ {\r\npublic:\r\n  using u32 = std::uint32_t;\r\n  using i64 = std::int64_t;\r\
    \n  using u64 = std::uint64_t;\r\n  using m64 = RuntimeLongMontgomeryModInt;\r\
    \n\r\n  using value_type = u64;\r\n\r\n  static u64 get_mod() { return mod; }\r\
    \n\r\n  static bool set_mod(u64 m) {\r\n    if ((m & 1) == 0 || m == 1 || (m &\
    \ (1ULL << 63)) != 0) return false;\r\n    mod = m;\r\n    r   = get_r();\r\n\
    \    r2  = get_r2();\r\n    return true;\r\n  }\r\n\r\n  RuntimeLongMontgomeryModInt()\
    \  = default;\r\n  ~RuntimeLongMontgomeryModInt() = default;\r\n\r\n  template\
    \ <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  RuntimeLongMontgomeryModInt(T\
    \ v) : v_(reduce(mul(norm(v % i64(mod)), r2))) {}\r\n\r\n  RuntimeLongMontgomeryModInt(const\
    \ m64 &) = default;\r\n\r\n  u64 get() const { return reduce({0, v_}); }\r\n\r\
    \n  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n\
    \  explicit operator T() const {\r\n    return T(get());\r\n  }\r\n\r\n  m64 operator-()\
    \ const {\r\n    m64 res;\r\n    res.v_ = (mod & -(v_ != 0)) - v_;\r\n    return\
    \ res;\r\n  }\r\n\r\n  m64 inv() const {\r\n    i64 x1 = 1, x3 = 0, a = get(),\
    \ b = mod;\r\n    while (b != 0) {\r\n      i64 q = a / b, x1_old = x1, a_old\
    \ = a;\r\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\r\n \
    \   }\r\n    return m64(x1);\r\n  }\r\n\r\n  m64 &operator=(const m64 &) = default;\r\
    \n\r\n  m64 &operator+=(const m64 &rhs) {\r\n    v_ += rhs.v_ - mod;\r\n    v_\
    \ += mod & -(v_ >> 63);\r\n    return *this;\r\n  }\r\n  m64 &operator-=(const\
    \ m64 &rhs) {\r\n    v_ -= rhs.v_;\r\n    v_ += mod & -(v_ >> 63);\r\n    return\
    \ *this;\r\n  }\r\n  m64 &operator*=(const m64 &rhs) {\r\n    v_ = reduce(mul(v_,\
    \ rhs.v_));\r\n    return *this;\r\n  }\r\n  m64 &operator/=(const m64 &rhs) {\
    \ return operator*=(rhs.inv()); }\r\n  friend m64 operator+(const m64 &lhs, const\
    \ m64 &rhs) { return m64(lhs) += rhs; }\r\n  friend m64 operator-(const m64 &lhs,\
    \ const m64 &rhs) { return m64(lhs) -= rhs; }\r\n  friend m64 operator*(const\
    \ m64 &lhs, const m64 &rhs) { return m64(lhs) *= rhs; }\r\n  friend m64 operator/(const\
    \ m64 &lhs, const m64 &rhs) { return m64(lhs) /= rhs; }\r\n  friend bool operator==(const\
    \ m64 &lhs, const m64 &rhs) { return lhs.v_ == rhs.v_; }\r\n  friend bool operator!=(const\
    \ m64 &lhs, const m64 &rhs) { return lhs.v_ != rhs.v_; }\r\n\r\n  friend std::istream\
    \ &operator>>(std::istream &is, m64 &rhs) {\r\n    i64 x;\r\n    is >> x;\r\n\
    \    rhs = m64(x);\r\n    return is;\r\n  }\r\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const m64 &rhs) { return os << rhs.get(); }\r\n\r\n  m64 pow(u64 y) const\
    \ {\r\n    m64 res(1), x(*this);\r\n    for (; y != 0; y >>= 1, x *= x)\r\n  \
    \    if (y & 1) res *= x;\r\n    return res;\r\n  }\r\n\r\nprivate:\r\n  static\
    \ std::pair<u64, u64> mul(u64 x, u64 y) {\r\n#ifdef __GNUC__\r\n    unsigned __int128\
    \ res = (unsigned __int128)x * y;\r\n    return {u64(res >> 64), u64(res)};\r\n\
    #elif defined(_MSC_VER)\r\n    u64 h, l = _umul128(x, y, &h);\r\n    return {h,\
    \ l};\r\n#else\r\n    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad\
    \ = a * d, bc = b * c;\r\n    return {a * c + (ad >> 32) + (bc >> 32) +\r\n  \
    \              (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32)) >>\
    \ 32),\r\n            x * y};\r\n#endif\r\n  }\r\n\r\n  static u64 mulh(u64 x,\
    \ u64 y) {\r\n#ifdef __GNUC__\r\n    return u64((unsigned __int128)x * y >> 64);\r\
    \n#elif defined(_MSC_VER)\r\n    return __umulh(x, y);\r\n#else\r\n    u64 a =\
    \ x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad = a * d, bc = b * c;\r\n  \
    \  return a * c + (ad >> 32) + (bc >> 32) +\r\n           (((ad & ~UINT32_C(0))\
    \ + (bc & ~UINT32_C(0)) + (b * d >> 32)) >> 32);\r\n#endif\r\n  }\r\n\r\n  static\
    \ u64 get_r() {\r\n    u64 two = 2, iv = mod * (two - mod * mod);\r\n    iv *=\
    \ two - mod * iv;\r\n    iv *= two - mod * iv;\r\n    iv *= two - mod * iv;\r\n\
    \    return iv * (two - mod * iv);\r\n  }\r\n\r\n  static u64 get_r2() {\r\n \
    \   u64 iv = -u64(mod) % mod;\r\n    for (int i = 0; i != 64; ++i)\r\n      if\
    \ ((iv <<= 1) >= mod) iv -= mod;\r\n    return iv;\r\n  }\r\n\r\n  static u64\
    \ reduce(const std::pair<u64, u64> &x) {\r\n    u64 res = x.first - mulh(x.second\
    \ * r, mod);\r\n    return res + (mod & -(res >> 63));\r\n  }\r\n\r\n  static\
    \ u64 norm(i64 x) { return x + (mod & -(x < 0)); }\r\n\r\n  u64 v_;\r\n\r\n  static\
    \ inline u64 mod, r, r2;\r\n};\r\n\r\ntemplate <int id>\r\nusing RuntimeLongMontModInt\
    \ = RuntimeLongMontgomeryModInt<id>;\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: modint/runtime_long_Montgomery_modint.hpp
  requiredBy:
  - math/basic/integer_factorization_Pollard_rho.hpp
  - math/modulo/sqrt_mod.hpp
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - remote_test/yosupo/math/mod_sqrt.0.test.cpp
  - remote_test/yosupo/math/factorize.0.test.cpp
documentation_of: modint/runtime_long_Montgomery_modint.hpp
layout: document
redirect_from:
- /library/modint/runtime_long_Montgomery_modint.hpp
- /library/modint/runtime_long_Montgomery_modint.hpp.html
title: "runtime long Montgomery modint / \u8FD0\u884C\u65F6\u957F\u6574\u578B Montgomery\
  \ \u53D6\u6A21\u7C7B"
---
