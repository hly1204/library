---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/basic/binary_mul.hpp
    title: "binary multiplication / \u5FEB\u901F\u4E58"
  - icon: ':heavy_check_mark:'
    path: math/basic/binary_pow.hpp
    title: "binary power / \u5FEB\u901F\u5E42"
  - icon: ':heavy_check_mark:'
    path: math/basic/crt.hpp
    title: "Chinese remainder theorem / \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406"
  - icon: ':heavy_check_mark:'
    path: math/basic/exgcd.hpp
    title: "extended Euclidean algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\
      \u6CD5"
  - icon: ':heavy_check_mark:'
    path: math/modulo/binomial_coefficient_mod.hpp
    title: "binomial coefficient mod / \u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\u6A21"
  - icon: ':heavy_check_mark:'
    path: math/modulo/sqrt_mod_Tonelli_Shanks.hpp
    title: "square root mod Tonelli-Shanks / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839\
      \ Tonelli-Shanks \u7B97\u6CD5"
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
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/mod_sqrt.0.test.cpp
    title: remote_test/yosupo/math/mod_sqrt.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "type traits / \u7C7B\u578B\u8403\u53D6"
    links: []
  bundledCode: "#line 1 \"traits/base.hpp\"\n\n\n\n/**\n * @brief type traits / \u7C7B\
    \u578B\u8403\u53D6\n *\n */\n\n#include <cstdint>\n#include <type_traits>\n\n\
    namespace lib {\n\ntemplate <typename Type> struct promote_integral;\ntemplate\
    \ <> struct promote_integral<std::int32_t> { using type = std::int64_t; };\ntemplate\
    \ <> struct promote_integral<std::uint32_t> { using type = std::uint64_t; };\n\
    \n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename Type> using promote_integral_t\
    \ = typename promote_integral<Type>::type;\n\ntemplate <typename T, typename U,\n\
    \          bool = (sizeof(T) > sizeof(U) || (sizeof(T) == sizeof(U) && std::is_signed_v<T>))>\n\
    struct longer_integral;\ntemplate <typename T, typename U> struct longer_integral<T,\
    \ U, true> { using type = T; };\ntemplate <typename T, typename U> struct longer_integral<T,\
    \ U, false> { using type = U; };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename\
    \ T, typename U> using longer_integral_t = typename longer_integral<T, U>::type;\n\
    \n} // namespace lib\n\n\n"
  code: "#ifndef TYPE_TRAITS_HEADER_HPP\n#define TYPE_TRAITS_HEADER_HPP\n\n/**\n *\
    \ @brief type traits / \u7C7B\u578B\u8403\u53D6\n *\n */\n\n#include <cstdint>\n\
    #include <type_traits>\n\nnamespace lib {\n\ntemplate <typename Type> struct promote_integral;\n\
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
  - math/basic/exgcd.hpp
  - math/basic/crt.hpp
  - math/basic/binary_pow.hpp
  - math/basic/binary_mul.hpp
  - math/modulo/sqrt_mod_Tonelli_Shanks.hpp
  - math/modulo/binomial_coefficient_mod.hpp
  timestamp: '2021-06-11 23:09:55+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
  - remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
  - remote_test/yosupo/math/mod_sqrt.0.test.cpp
  - remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
documentation_of: traits/base.hpp
layout: document
redirect_from:
- /library/traits/base.hpp
- /library/traits/base.hpp.html
title: "type traits / \u7C7B\u578B\u8403\u53D6"
---
