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
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "type traits / \u7C7B\u578B\u8403\u53D6"
    links: []
  bundledCode: "#line 1 \"traits/base.hpp\"\n\n\n\r\n/**\r\n * @brief type traits\
    \ / \u7C7B\u578B\u8403\u53D6\r\n *\r\n */\r\n\r\n#include <cstdint>\r\n#include\
    \ <type_traits>\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename Type>\r\nstruct\
    \ promote_integral;\r\ntemplate <>\r\nstruct promote_integral<std::int32_t> {\r\
    \n  using type = std::int64_t;\r\n};\r\ntemplate <>\r\nstruct promote_integral<std::uint32_t>\
    \ {\r\n  using type = std::uint64_t;\r\n};\r\n\r\n// \u8F85\u52A9\u6A21\u677F\r\
    \ntemplate <typename Type>\r\nusing promote_integral_t = typename promote_integral<Type>::type;\r\
    \n\r\ntemplate <typename T, typename U>\r\nusing longer_integral_t =\r\n    std::conditional_t<(sizeof(T)\
    \ > sizeof(U) || (sizeof(T) == sizeof(U) && std::is_signed_v<T>)),\r\n       \
    \                T, U>;\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef TYPE_TRAITS_HEADER_HPP\r\n#define TYPE_TRAITS_HEADER_HPP\r\n\r\n\
    /**\r\n * @brief type traits / \u7C7B\u578B\u8403\u53D6\r\n *\r\n */\r\n\r\n#include\
    \ <cstdint>\r\n#include <type_traits>\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename\
    \ Type>\r\nstruct promote_integral;\r\ntemplate <>\r\nstruct promote_integral<std::int32_t>\
    \ {\r\n  using type = std::int64_t;\r\n};\r\ntemplate <>\r\nstruct promote_integral<std::uint32_t>\
    \ {\r\n  using type = std::uint64_t;\r\n};\r\n\r\n// \u8F85\u52A9\u6A21\u677F\r\
    \ntemplate <typename Type>\r\nusing promote_integral_t = typename promote_integral<Type>::type;\r\
    \n\r\ntemplate <typename T, typename U>\r\nusing longer_integral_t =\r\n    std::conditional_t<(sizeof(T)\
    \ > sizeof(U) || (sizeof(T) == sizeof(U) && std::is_signed_v<T>)),\r\n       \
    \                T, U>;\r\n\r\n} // namespace lib\r\n\r\n#endif\r\n"
  dependsOn: []
  isVerificationFile: false
  path: traits/base.hpp
  requiredBy:
  - math/basic/binary_mul.hpp
  - math/basic/exgcd.hpp
  - math/basic/binary_pow.hpp
  - math/basic/crt.hpp
  - math/modulo/binomial_coefficient_mod.hpp
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
  - remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
  - remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
documentation_of: traits/base.hpp
layout: document
redirect_from:
- /library/traits/base.hpp
- /library/traits/base.hpp.html
title: "type traits / \u7C7B\u578B\u8403\u53D6"
---
