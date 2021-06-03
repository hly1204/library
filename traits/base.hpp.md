---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: math/basic/binary_mul.hpp
    title: math/basic/binary_mul.hpp
  - icon: ':question:'
    path: math/basic/binary_pow.hpp
    title: math/basic/binary_pow.hpp
  - icon: ':heavy_check_mark:'
    path: math/basic/crt.hpp
    title: math/basic/crt.hpp
  - icon: ':question:'
    path: math/basic/exgcd.hpp
    title: math/basic/exgcd.hpp
  - icon: ':heavy_check_mark:'
    path: math/modulo/binomial_coefficient_mod.hpp
    title: "\u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\u6A21"
  - icon: ':x:'
    path: math/modulo/sqrt_mod.hpp
    title: "\u6A21\u5E73\u65B9\u6839"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
    title: remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
    title: remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
    title: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/mod_sqrt.0.test.cpp
    title: remote_test/yosupo/math/mod_sqrt.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"traits/base.hpp\"\n\n\n\n#include <cstdint>\n\nnamespace\
    \ lib {\n\ntemplate <typename Type> struct promote_integral;\ntemplate <> struct\
    \ promote_integral<std::int32_t> { using type = std::int64_t; };\ntemplate <>\
    \ struct promote_integral<std::uint32_t> { using type = std::uint64_t; };\n\n\
    // \u8F85\u52A9\u6A21\u677F\ntemplate <typename Type> using promote_integral_t\
    \ = typename promote_integral<Type>::type;\n\ntemplate <typename T, typename U,\n\
    \          bool = (sizeof(T) > sizeof(U) || (sizeof(T) == sizeof(U) && std::is_signed_v<T>))>\n\
    struct longer_integral;\ntemplate <typename T, typename U> struct longer_integral<T,\
    \ U, true> { using type = T; };\ntemplate <typename T, typename U> struct longer_integral<T,\
    \ U, false> { using type = U; };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename\
    \ T, typename U> using longer_integral_t = typename longer_integral<T, U>::type;\n\
    \n} // namespace lib\n\n\n"
  code: "#ifndef TYPE_TRAITS_HEADER_HPP\n#define TYPE_TRAITS_HEADER_HPP\n\n#include\
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
    \n} // namespace lib\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: traits/base.hpp
  requiredBy:
  - math/basic/binary_mul.hpp
  - math/basic/binary_pow.hpp
  - math/basic/crt.hpp
  - math/basic/exgcd.hpp
  - math/modulo/sqrt_mod.hpp
  - math/modulo/binomial_coefficient_mod.hpp
  timestamp: '2021-06-03 15:01:19+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  - remote_test/yosupo/math/mod_sqrt.0.test.cpp
  - remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
  - remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
documentation_of: traits/base.hpp
layout: document
redirect_from:
- /library/traits/base.hpp
- /library/traits/base.hpp.html
title: traits/base.hpp
---
