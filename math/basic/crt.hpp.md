---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/basic/binary_mul.hpp
    title: "binary multiplication / \u5FEB\u901F\u4E58"
  - icon: ':question:'
    path: math/basic/exgcd.hpp
    title: "extended Euclidean algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\
      \u6CD5"
  - icon: ':question:'
    path: traits/base.hpp
    title: "type traits / \u7C7B\u578B\u8403\u53D6"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/modulo/binomial_coefficient_mod.hpp
    title: "binomial coefficient mod / \u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\u6A21"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
    title: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Chinese remainder theorem / \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406"
    links: []
  bundledCode: "#line 1 \"math/basic/crt.hpp\"\n\n\n\n/**\n * @brief Chinese remainder\
    \ theorem / \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406\n *\n */\n\n#include <cassert>\n\
    #include <cstdint>\n#include <vector>\n\n#line 1 \"math/basic/binary_mul.hpp\"\
    \n\n\n\n/**\n * @brief binary multiplication / \u5FEB\u901F\u4E58\n *\n */\n\n\
    #include <type_traits>\n\n#line 1 \"traits/base.hpp\"\n\n\n\n/**\n * @brief type\
    \ traits / \u7C7B\u578B\u8403\u53D6\n *\n */\n\n#line 11 \"traits/base.hpp\"\n\
    \nnamespace lib {\n\ntemplate <typename Type> struct promote_integral;\ntemplate\
    \ <> struct promote_integral<std::int32_t> { using type = std::int64_t; };\ntemplate\
    \ <> struct promote_integral<std::uint32_t> { using type = std::uint64_t; };\n\
    \n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename Type> using promote_integral_t\
    \ = typename promote_integral<Type>::type;\n\ntemplate <typename T, typename U,\n\
    \          bool = (sizeof(T) > sizeof(U) || (sizeof(T) == sizeof(U) && std::is_signed_v<T>))>\n\
    struct longer_integral;\ntemplate <typename T, typename U> struct longer_integral<T,\
    \ U, true> { using type = T; };\ntemplate <typename T, typename U> struct longer_integral<T,\
    \ U, false> { using type = U; };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename\
    \ T, typename U> using longer_integral_t = typename longer_integral<T, U>::type;\n\
    \n} // namespace lib\n\n\n#line 12 \"math/basic/binary_mul.hpp\"\n\nnamespace\
    \ lib {\n\nnamespace internal {\n\ntemplate <typename T> std::enable_if_t<std::is_integral_v<T>,\
    \ T> mul_mod(T x, T y, T mod) {\n  if ((x %= mod) < 0) x += mod;\n  if ((y %=\
    \ mod) < 0) y += mod;\n  if constexpr (sizeof(T) < 8) {\n    return static_cast<T>(static_cast<promote_integral_t<T>>(x)\
    \ * y % mod);\n  } else {\n    T res = 0;\n    for (; y != 0; y >>= 1) {\n   \
    \   if ((y & 1) && (res += x) >= mod) res -= mod;\n      if ((x <<= 1) >= mod)\
    \ x -= mod;\n    }\n    return res;\n  }\n}\n\n} // namespace internal\n\ntemplate\
    \ <typename T1, typename T2, typename T3,\n          typename T = longer_integral_t<longer_integral_t<T1,\
    \ T2>, T3>>\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>\
    \ && std::is_integral_v<T3>, T>\nmul_mod(T1 x, T2 y, T3 mod) {\n  if constexpr\
    \ (std::is_signed_v<T1> || std::is_signed_v<T2>) {\n    return internal::mul_mod<std::make_signed_t<T>>(x,\
    \ y, mod);\n  } else {\n    return internal::mul_mod<T>(x, y, mod);\n  }\n}\n\n\
    } // namespace lib\n\n\n#line 1 \"math/basic/exgcd.hpp\"\n\n\n\n/**\n * @brief\
    \ extended Euclidean algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\u6CD5\
    \n *\n */\n\n#line 10 \"math/basic/exgcd.hpp\"\n#include <tuple>\n#line 12 \"\
    math/basic/exgcd.hpp\"\n\n#line 14 \"math/basic/exgcd.hpp\"\n\nnamespace lib {\n\
    \nnamespace internal {\n\ntemplate <typename T> std::enable_if_t<std::is_integral_v<T>,\
    \ T> gcd(T a, T b) {\n  while (b != 0) std::tie(a, b) = std::make_tuple(b, a %\
    \ b);\n  return a;\n}\n\ntemplate <typename T, typename S = std::make_signed_t<T>>\n\
    std::enable_if_t<std::is_integral_v<T>, std::tuple<T, S, S>> exgcd(T a, T b) {\n\
    \  S a_p = a, b_p = b, x1 = 1, x2 = 0, x3 = 0, x4 = 1;\n  while (b_p != 0) {\n\
    \    S q = a_p / b_p;\n    std::tie(x1, x2, x3, x4, a_p, b_p) =\n        std::make_tuple(x3,\
    \ x4, x1 - x3 * q, x2 - x4 * q, b_p, a_p - b_p * q);\n  }\n  return std::make_tuple(static_cast<T>(a_p),\
    \ x1, x2);\n}\n\ntemplate <typename T> std::enable_if_t<std::is_integral_v<T>,\
    \ T> inv_mod(T x, T mod) {\n  using S = std::make_signed_t<T>;\n  S a = x, b =\
    \ mod, x1 = 1, x3 = 0;\n  assert(a < b);\n  while (b != 0) {\n    S q = a / b;\n\
    \    std::tie(x1, x3, a, b) = std::make_tuple(x3, x1 - x3 * q, b, a - b * q);\n\
    \  }\n  assert(a == 1 && \"inv_mod_error\");\n  return static_cast<T>(x1 < 0 ?\
    \ x1 + mod : x1);\n}\n\n} // namespace internal\n\ntemplate <typename T1, typename\
    \ T2, typename T = longer_integral_t<T1, T2>>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2>, T> gcd(T1 a, T2 b) {\n  return internal::gcd<T>(a,\
    \ b);\n}\n\ntemplate <typename T1, typename T2, typename T = longer_integral_t<T1,\
    \ T2>,\n          typename S = std::make_signed_t<T>>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2>, std::tuple<T, S, S>>\nexgcd(T1 a, T2 b) {\n  return\
    \ internal::exgcd<T, S>(a, b);\n}\n\ntemplate <typename T1, typename T2, typename\
    \ T = longer_integral_t<T1, T2>>\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>,\
    \ T> inv_mod(T1 x, T2 mod) {\n  return internal::inv_mod<T>(x, mod);\n}\n\n} //\
    \ namespace lib\n\n\n#line 15 \"math/basic/crt.hpp\"\n\nnamespace lib {\n\ntemplate\
    \ <typename T> class CoprimeCRT {\npublic:\n  using u64 = std::uint64_t;\n\n \
    \ CoprimeCRT() = default;\n\n  /**\n   * @note \u5047\u8BBE m \u6570\u7EC4\u4E2D\
    \u6240\u6709\u5143\u7D20\u7684\u4E58\u79EF\u5728 std::int64_t \u8868\u793A\u8303\
    \u56F4\u5185\n   */\n  CoprimeCRT(const std::vector<T> &m) : m_(m), C_(m.size())\
    \ {\n    int n = m_.size();\n    u64 prod = 1;\n    for (int i = 0; i < n; ++i)\
    \ {\n      C_[i] = inv_mod(prod % m_[i], m_[i]);\n      prod *= m_[i];\n    }\n\
    \  }\n\n  ~CoprimeCRT() = default;\n\n  void set_m(const std::vector<T> &m) {\n\
    \    m_ = m;\n    int n = m_.size();\n    C_.resize(n);\n    u64 prod = 1;\n \
    \   for (int i = 0; i < n; ++i) {\n      C_[i] = inv_mod(prod % m_[i], m_[i]);\n\
    \      prod *= m_[i];\n    }\n  }\n\n  u64 operator()(const std::vector<T> &v)\
    \ const {\n    int n = m_.size();\n    assert(v.size() == n);\n    u64 x = 0,\
    \ prod = 1;\n    for (int i = 0; i < n; ++i) {\n      x += mul_mod(v[i] + m_[i]\
    \ - x % m_[i], C_[i], m_[i]) * prod;\n      prod *= m_[i];\n    }\n    return\
    \ x;\n  }\n\nprivate:\n  std::vector<T> m_, C_;\n};\n\n// TODO\ntemplate <typename\
    \ T> class CRT;\n\n} // namespace lib\n\n\n"
  code: "#ifndef CHINESE_REMAINDER_THEOREM_HEADER_HPP\n#define CHINESE_REMAINDER_THEOREM_HEADER_HPP\n\
    \n/**\n * @brief Chinese remainder theorem / \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406\
    \n *\n */\n\n#include <cassert>\n#include <cstdint>\n#include <vector>\n\n#include\
    \ \"binary_mul.hpp\"\n#include \"exgcd.hpp\"\n\nnamespace lib {\n\ntemplate <typename\
    \ T> class CoprimeCRT {\npublic:\n  using u64 = std::uint64_t;\n\n  CoprimeCRT()\
    \ = default;\n\n  /**\n   * @note \u5047\u8BBE m \u6570\u7EC4\u4E2D\u6240\u6709\
    \u5143\u7D20\u7684\u4E58\u79EF\u5728 std::int64_t \u8868\u793A\u8303\u56F4\u5185\
    \n   */\n  CoprimeCRT(const std::vector<T> &m) : m_(m), C_(m.size()) {\n    int\
    \ n = m_.size();\n    u64 prod = 1;\n    for (int i = 0; i < n; ++i) {\n     \
    \ C_[i] = inv_mod(prod % m_[i], m_[i]);\n      prod *= m_[i];\n    }\n  }\n\n\
    \  ~CoprimeCRT() = default;\n\n  void set_m(const std::vector<T> &m) {\n    m_\
    \ = m;\n    int n = m_.size();\n    C_.resize(n);\n    u64 prod = 1;\n    for\
    \ (int i = 0; i < n; ++i) {\n      C_[i] = inv_mod(prod % m_[i], m_[i]);\n   \
    \   prod *= m_[i];\n    }\n  }\n\n  u64 operator()(const std::vector<T> &v) const\
    \ {\n    int n = m_.size();\n    assert(v.size() == n);\n    u64 x = 0, prod =\
    \ 1;\n    for (int i = 0; i < n; ++i) {\n      x += mul_mod(v[i] + m_[i] - x %\
    \ m_[i], C_[i], m_[i]) * prod;\n      prod *= m_[i];\n    }\n    return x;\n \
    \ }\n\nprivate:\n  std::vector<T> m_, C_;\n};\n\n// TODO\ntemplate <typename T>\
    \ class CRT;\n\n} // namespace lib\n\n#endif"
  dependsOn:
  - math/basic/binary_mul.hpp
  - traits/base.hpp
  - math/basic/exgcd.hpp
  isVerificationFile: false
  path: math/basic/crt.hpp
  requiredBy:
  - math/modulo/binomial_coefficient_mod.hpp
  timestamp: '2021-06-17 19:06:03+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
documentation_of: math/basic/crt.hpp
layout: document
redirect_from:
- /library/math/basic/crt.hpp
- /library/math/basic/crt.hpp.html
title: "Chinese remainder theorem / \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406"
---
