---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: traits/base.hpp
    title: "type traits / \u7C7B\u578B\u8403\u53D6"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/basic/binary_pow.hpp
    title: "binary power / \u5FEB\u901F\u5E42"
  - icon: ':heavy_check_mark:'
    path: math/basic/crt.hpp
    title: "Chinese remainder theorem / \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406"
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
    document_title: "binary multiplication / \u5FEB\u901F\u4E58"
    links: []
  bundledCode: "#line 1 \"math/basic/binary_mul.hpp\"\n\n\n\n/**\n * @brief binary\
    \ multiplication / \u5FEB\u901F\u4E58\n *\n */\n\n#include <type_traits>\n\n#line\
    \ 1 \"traits/base.hpp\"\n\n\n\n/**\n * @brief type traits / \u7C7B\u578B\u8403\
    \u53D6\n *\n */\n\n#include <cstdint>\n#line 11 \"traits/base.hpp\"\n\nnamespace\
    \ lib {\n\ntemplate <typename Type>\nstruct promote_integral;\ntemplate <>\nstruct\
    \ promote_integral<std::int32_t> {\n  using type = std::int64_t;\n};\ntemplate\
    \ <>\nstruct promote_integral<std::uint32_t> {\n  using type = std::uint64_t;\n\
    };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename Type>\nusing promote_integral_t\
    \ = typename promote_integral<Type>::type;\n\ntemplate <typename T, typename U>\n\
    using longer_integral_t =\n    std::conditional_t<(sizeof(T) > sizeof(U) || (sizeof(T)\
    \ == sizeof(U) && std::is_signed_v<T>)),\n                       T, U>;\n\n} //\
    \ namespace lib\n\n\n#line 12 \"math/basic/binary_mul.hpp\"\n\nnamespace lib::internal\
    \ {\n\ntemplate <typename T>\nstd::enable_if_t<std::is_integral_v<T> && sizeof(T)\
    \ <= 4 && std::is_signed_v<T>, T>\nmul_mod(T x, T y, T mod) {\n  T res = static_cast<T>(static_cast<promote_integral_t<T>>(x)\
    \ * y % mod);\n  return res < 0 ? res + mod : res;\n}\n\ntemplate <typename T>\n\
    std::enable_if_t<std::is_integral_v<T> && sizeof(T) <= 4 && std::is_unsigned_v<T>,\
    \ T>\nmul_mod(T x, T y, T mod) {\n  return static_cast<T>(static_cast<promote_integral_t<T>>(x)\
    \ * y % mod);\n}\n\ntemplate <typename T>\nstd::enable_if_t<std::is_integral_v<T>\
    \ && (sizeof(T) > 4) && std::is_unsigned_v<T>, T>\nmul_mod(T x, T y, T mod) {\n\
    \  x %= mod, y %= mod;\n  T res = 0;\n  for (; y != 0; y >>= 1) {\n    if ((y\
    \ & 1) && (res += x) >= mod) res -= mod;\n    if ((x <<= 1) >= mod) x -= mod;\n\
    \  }\n  return res;\n}\n\ntemplate <typename T>\nstd::enable_if_t<std::is_integral_v<T>\
    \ && (sizeof(T) > 4) && std::is_signed_v<T>, T>\nmul_mod(T x, T y, T mod) {\n\
    \  if ((x %= mod) < 0) x += mod;\n  if ((y %= mod) < 0) y += mod;\n  T res = 0;\n\
    \  for (; y != 0; y >>= 1) {\n    if ((y & 1) && (res += x) >= mod) res -= mod;\n\
    \    if ((x <<= 1) >= mod) x -= mod;\n  }\n  return res;\n}\n\n} // namespace\
    \ lib::internal\n\nnamespace lib {\n\ntemplate <typename T1, typename T2, typename\
    \ T3,\n          typename T = longer_integral_t<longer_integral_t<T1, T2>, T3>>\n\
    std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2> && std::is_integral_v<T3>\
    \ &&\n                     (std::is_signed_v<T1> || std::is_signed_v<T2>),\n \
    \                T>\nmul_mod(T1 x, T2 y, T3 mod) {\n  return internal::mul_mod<std::make_signed_t<T>>(x,\
    \ y, mod);\n}\n\ntemplate <typename T1, typename T2, typename T3,\n          typename\
    \ T = longer_integral_t<longer_integral_t<T1, T2>, T3>>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2> && std::is_integral_v<T3> &&\n                   \
    \  std::is_unsigned_v<T1> && std::is_unsigned_v<T2>,\n                 T>\nmul_mod(T1\
    \ x, T2 y, T3 mod) {\n  return internal::mul_mod<T>(x, y, mod);\n}\n\n} // namespace\
    \ lib\n\n\n"
  code: "#ifndef BINARY_MUL_HEADER_HPP\n#define BINARY_MUL_HEADER_HPP\n\n/**\n * @brief\
    \ binary multiplication / \u5FEB\u901F\u4E58\n *\n */\n\n#include <type_traits>\n\
    \n#include \"../../traits/base.hpp\"\n\nnamespace lib::internal {\n\ntemplate\
    \ <typename T>\nstd::enable_if_t<std::is_integral_v<T> && sizeof(T) <= 4 && std::is_signed_v<T>,\
    \ T>\nmul_mod(T x, T y, T mod) {\n  T res = static_cast<T>(static_cast<promote_integral_t<T>>(x)\
    \ * y % mod);\n  return res < 0 ? res + mod : res;\n}\n\ntemplate <typename T>\n\
    std::enable_if_t<std::is_integral_v<T> && sizeof(T) <= 4 && std::is_unsigned_v<T>,\
    \ T>\nmul_mod(T x, T y, T mod) {\n  return static_cast<T>(static_cast<promote_integral_t<T>>(x)\
    \ * y % mod);\n}\n\ntemplate <typename T>\nstd::enable_if_t<std::is_integral_v<T>\
    \ && (sizeof(T) > 4) && std::is_unsigned_v<T>, T>\nmul_mod(T x, T y, T mod) {\n\
    \  x %= mod, y %= mod;\n  T res = 0;\n  for (; y != 0; y >>= 1) {\n    if ((y\
    \ & 1) && (res += x) >= mod) res -= mod;\n    if ((x <<= 1) >= mod) x -= mod;\n\
    \  }\n  return res;\n}\n\ntemplate <typename T>\nstd::enable_if_t<std::is_integral_v<T>\
    \ && (sizeof(T) > 4) && std::is_signed_v<T>, T>\nmul_mod(T x, T y, T mod) {\n\
    \  if ((x %= mod) < 0) x += mod;\n  if ((y %= mod) < 0) y += mod;\n  T res = 0;\n\
    \  for (; y != 0; y >>= 1) {\n    if ((y & 1) && (res += x) >= mod) res -= mod;\n\
    \    if ((x <<= 1) >= mod) x -= mod;\n  }\n  return res;\n}\n\n} // namespace\
    \ lib::internal\n\nnamespace lib {\n\ntemplate <typename T1, typename T2, typename\
    \ T3,\n          typename T = longer_integral_t<longer_integral_t<T1, T2>, T3>>\n\
    std::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2> && std::is_integral_v<T3>\
    \ &&\n                     (std::is_signed_v<T1> || std::is_signed_v<T2>),\n \
    \                T>\nmul_mod(T1 x, T2 y, T3 mod) {\n  return internal::mul_mod<std::make_signed_t<T>>(x,\
    \ y, mod);\n}\n\ntemplate <typename T1, typename T2, typename T3,\n          typename\
    \ T = longer_integral_t<longer_integral_t<T1, T2>, T3>>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2> && std::is_integral_v<T3> &&\n                   \
    \  std::is_unsigned_v<T1> && std::is_unsigned_v<T2>,\n                 T>\nmul_mod(T1\
    \ x, T2 y, T3 mod) {\n  return internal::mul_mod<T>(x, y, mod);\n}\n\n} // namespace\
    \ lib\n\n#endif"
  dependsOn:
  - traits/base.hpp
  isVerificationFile: false
  path: math/basic/binary_mul.hpp
  requiredBy:
  - math/basic/binary_pow.hpp
  - math/basic/crt.hpp
  - math/modulo/binomial_coefficient_mod.hpp
  timestamp: '2021-07-15 16:37:02+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
  - remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
documentation_of: math/basic/binary_mul.hpp
layout: document
redirect_from:
- /library/math/basic/binary_mul.hpp
- /library/math/basic/binary_mul.hpp.html
title: "binary multiplication / \u5FEB\u901F\u4E58"
---
