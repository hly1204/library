---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: traits/base.hpp
    title: traits/base.hpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/basic/crt.hpp
    title: math/basic/crt.hpp
  - icon: ':heavy_check_mark:'
    path: math/modulo/binomial_coefficient_mod.hpp
    title: "\u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\u6A21"
  - icon: ':heavy_check_mark:'
    path: math/modulo/sqrt_mod.hpp
    title: "\u6A21\u5E73\u65B9\u6839"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
    title: remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
    title: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/mod_sqrt.0.test.cpp
    title: remote_test/yosupo/math/mod_sqrt.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/basic/exgcd.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <tuple>\n#include <type_traits>\n\n#line 1 \"traits/base.hpp\"\n\n\n\n#include\
    \ <cstdint>\n\nnamespace lib {\n\ntemplate <typename Type> struct promote_integral;\n\
    template <> struct promote_integral<std::int32_t> { using type = std::int64_t;\
    \ };\ntemplate <> struct promote_integral<std::uint32_t> { using type = std::uint64_t;\
    \ };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename Type> using promote_integral_t\
    \ = typename promote_integral<Type>::type;\n\ntemplate <typename T, typename U,\n\
    \          bool = (sizeof(T) > sizeof(U) || (sizeof(T) == sizeof(U) && std::is_signed_v<T>))>\n\
    struct longer_integral;\ntemplate <typename T, typename U> struct longer_integral<T,\
    \ U, true> { using type = T; };\ntemplate <typename T, typename U> struct longer_integral<T,\
    \ U, false> { using type = U; };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename\
    \ T, typename U> using longer_integral_t = typename longer_integral<T, U>::type;\n\
    \n} // namespace lib\n\n\n#line 9 \"math/basic/exgcd.hpp\"\n\nnamespace lib {\n\
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
    \ namespace lib\n\n\n"
  code: "#ifndef EXTENDED_EUCLIDEAN_HEADER_HPP\n#define EXTENDED_EUCLIDEAN_HEADER_HPP\n\
    \n#include <cassert>\n#include <tuple>\n#include <type_traits>\n\n#include \"\
    ../../traits/base.hpp\"\n\nnamespace lib {\n\nnamespace internal {\n\ntemplate\
    \ <typename T> std::enable_if_t<std::is_integral_v<T>, T> gcd(T a, T b) {\n  while\
    \ (b != 0) std::tie(a, b) = std::make_tuple(b, a % b);\n  return a;\n}\n\ntemplate\
    \ <typename T, typename S = std::make_signed_t<T>>\nstd::enable_if_t<std::is_integral_v<T>,\
    \ std::tuple<T, S, S>> exgcd(T a, T b) {\n  S a_p = a, b_p = b, x1 = 1, x2 = 0,\
    \ x3 = 0, x4 = 1;\n  while (b_p != 0) {\n    S q = a_p / b_p;\n    std::tie(x1,\
    \ x2, x3, x4, a_p, b_p) =\n        std::make_tuple(x3, x4, x1 - x3 * q, x2 - x4\
    \ * q, b_p, a_p - b_p * q);\n  }\n  return std::make_tuple(static_cast<T>(a_p),\
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
    \ namespace lib\n\n#endif\n"
  dependsOn:
  - traits/base.hpp
  isVerificationFile: false
  path: math/basic/exgcd.hpp
  requiredBy:
  - math/basic/crt.hpp
  - math/modulo/sqrt_mod.hpp
  - math/modulo/binomial_coefficient_mod.hpp
  timestamp: '2021-06-03 15:01:19+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  - remote_test/yosupo/math/mod_sqrt.0.test.cpp
  - remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
documentation_of: math/basic/exgcd.hpp
layout: document
redirect_from:
- /library/math/basic/exgcd.hpp
- /library/math/basic/exgcd.hpp.html
title: math/basic/exgcd.hpp
---
