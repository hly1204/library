---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/basic/binary_mul.hpp
    title: "binary multiplication / \u5FEB\u901F\u4E58"
  - icon: ':heavy_check_mark:'
    path: traits/base.hpp
    title: "type traits / \u7C7B\u578B\u8403\u53D6"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/modulo/binomial_coefficient_mod.hpp
    title: "binomial coefficient mod / \u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\u6A21"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
    title: remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
    title: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "binary power / \u5FEB\u901F\u5E42"
    links: []
  bundledCode: "#line 1 \"math/basic/binary_pow.hpp\"\n\n\n\r\n/**\r\n * @brief binary\
    \ power / \u5FEB\u901F\u5E42\r\n *\r\n */\r\n\r\n#include <cassert>\r\n#include\
    \ <type_traits>\r\n\r\n#line 1 \"traits/base.hpp\"\n\n\n\r\n/**\r\n * @brief type\
    \ traits / \u7C7B\u578B\u8403\u53D6\r\n *\r\n */\r\n\r\n#include <cstdint>\r\n\
    #line 11 \"traits/base.hpp\"\n\r\nnamespace lib {\r\n\r\ntemplate <typename Type>\r\
    \nstruct promote_integral;\r\ntemplate <>\r\nstruct promote_integral<std::int32_t>\
    \ {\r\n  using type = std::int64_t;\r\n};\r\ntemplate <>\r\nstruct promote_integral<std::uint32_t>\
    \ {\r\n  using type = std::uint64_t;\r\n};\r\n\r\n// \u8F85\u52A9\u6A21\u677F\r\
    \ntemplate <typename Type>\r\nusing promote_integral_t = typename promote_integral<Type>::type;\r\
    \n\r\ntemplate <typename T, typename U>\r\nusing longer_integral_t =\r\n    std::conditional_t<(sizeof(T)\
    \ > sizeof(U) || (sizeof(T) == sizeof(U) && std::is_signed_v<T>)),\r\n       \
    \                T, U>;\r\n\r\n} // namespace lib\r\n\r\n\n#line 1 \"math/basic/binary_mul.hpp\"\
    \n\n\n\r\n/**\r\n * @brief binary multiplication / \u5FEB\u901F\u4E58\r\n *\r\n\
    \ */\r\n\r\n#line 10 \"math/basic/binary_mul.hpp\"\n\r\n#line 12 \"math/basic/binary_mul.hpp\"\
    \n\r\nnamespace lib::internal {\r\n\r\ntemplate <typename T>\r\nstd::enable_if_t<std::is_integral_v<T>\
    \ && sizeof(T) <= 4 && std::is_signed_v<T>, T>\r\nmul_mod(T x, T y, T mod) {\r\
    \n  T res = static_cast<T>(static_cast<promote_integral_t<T>>(x) * y % mod);\r\
    \n  return res < 0 ? res + mod : res;\r\n}\r\n\r\ntemplate <typename T>\r\nstd::enable_if_t<std::is_integral_v<T>\
    \ && sizeof(T) <= 4 && std::is_unsigned_v<T>, T>\r\nmul_mod(T x, T y, T mod) {\r\
    \n  return static_cast<T>(static_cast<promote_integral_t<T>>(x) * y % mod);\r\n\
    }\r\n\r\ntemplate <typename T>\r\nstd::enable_if_t<std::is_integral_v<T> && (sizeof(T)\
    \ > 4) && std::is_unsigned_v<T>, T>\r\nmul_mod(T x, T y, T mod) {\r\n  x %= mod,\
    \ y %= mod;\r\n  T res = 0;\r\n  for (; y != 0; y >>= 1) {\r\n    if ((y & 1)\
    \ && (res += x) >= mod) res -= mod;\r\n    if ((x <<= 1) >= mod) x -= mod;\r\n\
    \  }\r\n  return res;\r\n}\r\n\r\ntemplate <typename T>\r\nstd::enable_if_t<std::is_integral_v<T>\
    \ && (sizeof(T) > 4) && std::is_signed_v<T>, T>\r\nmul_mod(T x, T y, T mod) {\r\
    \n  if ((x %= mod) < 0) x += mod;\r\n  if ((y %= mod) < 0) y += mod;\r\n  T res\
    \ = 0;\r\n  for (; y != 0; y >>= 1) {\r\n    if ((y & 1) && (res += x) >= mod)\
    \ res -= mod;\r\n    if ((x <<= 1) >= mod) x -= mod;\r\n  }\r\n  return res;\r\
    \n}\r\n\r\n} // namespace lib::internal\r\n\r\nnamespace lib {\r\n\r\ntemplate\
    \ <typename T1, typename T2, typename T3,\r\n          typename T = longer_integral_t<longer_integral_t<T1,\
    \ T2>, T3>>\r\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>\
    \ && std::is_integral_v<T3> &&\r\n                     (std::is_signed_v<T1> ||\
    \ std::is_signed_v<T2>),\r\n                 T>\r\nmul_mod(T1 x, T2 y, T3 mod)\
    \ {\r\n  return internal::mul_mod<std::make_signed_t<T>>(x, y, mod);\r\n}\r\n\r\
    \ntemplate <typename T1, typename T2, typename T3,\r\n          typename T = longer_integral_t<longer_integral_t<T1,\
    \ T2>, T3>>\r\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>\
    \ && std::is_integral_v<T3> &&\r\n                     std::is_unsigned_v<T1>\
    \ && std::is_unsigned_v<T2>,\r\n                 T>\r\nmul_mod(T1 x, T2 y, T3\
    \ mod) {\r\n  return internal::mul_mod<T>(x, y, mod);\r\n}\r\n\r\n} // namespace\
    \ lib\r\n\r\n\n#line 14 \"math/basic/binary_pow.hpp\"\n\r\nnamespace lib {\r\n\
    \r\ntemplate <typename T1, typename T2>\r\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2>, T1> pow(T1 x, T2 y) {\r\n  assert(y >= 0);\r\n  T1\
    \ res = 1;\r\n  for (; y != 0; y >>= 1, x *= x)\r\n    if (y & 1) res *= x;\r\n\
    \  return res;\r\n}\r\n\r\ntemplate <typename T1, typename T2, typename T3, typename\
    \ T = longer_integral_t<T1, T3>>\r\nstd::enable_if_t<std::is_integral_v<T1> &&\
    \ std::is_integral_v<T2> && std::is_integral_v<T3>, T>\r\npow_mod(T1 x, T2 y,\
    \ T3 mod) {\r\n  assert(y >= 0);\r\n  T res = (mod != 1), tx = x;\r\n  for (;\
    \ y != 0; y >>= 1, tx = mul_mod(tx, tx, mod))\r\n    if (y & 1) res = mul_mod(res,\
    \ tx, mod);\r\n  return res;\r\n}\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef BINARY_POW_HEADER_HPP\r\n#define BINARY_POW_HEADER_HPP\r\n\r\n/**\r\
    \n * @brief binary power / \u5FEB\u901F\u5E42\r\n *\r\n */\r\n\r\n#include <cassert>\r\
    \n#include <type_traits>\r\n\r\n#include \"../../traits/base.hpp\"\r\n#include\
    \ \"binary_mul.hpp\"\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename T1, typename\
    \ T2>\r\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>, T1>\
    \ pow(T1 x, T2 y) {\r\n  assert(y >= 0);\r\n  T1 res = 1;\r\n  for (; y != 0;\
    \ y >>= 1, x *= x)\r\n    if (y & 1) res *= x;\r\n  return res;\r\n}\r\n\r\ntemplate\
    \ <typename T1, typename T2, typename T3, typename T = longer_integral_t<T1, T3>>\r\
    \nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2> && std::is_integral_v<T3>,\
    \ T>\r\npow_mod(T1 x, T2 y, T3 mod) {\r\n  assert(y >= 0);\r\n  T res = (mod !=\
    \ 1), tx = x;\r\n  for (; y != 0; y >>= 1, tx = mul_mod(tx, tx, mod))\r\n    if\
    \ (y & 1) res = mul_mod(res, tx, mod);\r\n  return res;\r\n}\r\n\r\n} // namespace\
    \ lib\r\n\r\n#endif\r\n"
  dependsOn:
  - traits/base.hpp
  - math/basic/binary_mul.hpp
  isVerificationFile: false
  path: math/basic/binary_pow.hpp
  requiredBy:
  - math/modulo/binomial_coefficient_mod.hpp
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
  - remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
documentation_of: math/basic/binary_pow.hpp
layout: document
redirect_from:
- /library/math/basic/binary_pow.hpp
- /library/math/basic/binary_pow.hpp.html
title: "binary power / \u5FEB\u901F\u5E42"
---
