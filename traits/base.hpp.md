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
  bundledCode: "#line 1 \"traits/base.hpp\"\n\n\n\n/**\n * @brief type traits / \u7C7B\
    \u578B\u8403\u53D6\n *\n */\n\n#include <cstdint>\n#include <type_traits>\n\n\
    namespace lib {\n\ntemplate <typename Type>\nstruct promote_integral;\ntemplate\
    \ <>\nstruct promote_integral<std::int32_t> {\n  using type = std::int64_t;\n\
    };\ntemplate <>\nstruct promote_integral<std::uint32_t> {\n  using type = std::uint64_t;\n\
    };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename Type>\nusing promote_integral_t\
    \ = typename promote_integral<Type>::type;\n\ntemplate <typename T, typename U>\n\
    using longer_integral_t =\n    std::conditional_t<(sizeof(T) > sizeof(U) || (sizeof(T)\
    \ == sizeof(U) && std::is_signed_v<T>)),\n                       T, U>;\n\n} //\
    \ namespace lib\n\n\n"
  code: "#ifndef TYPE_TRAITS_HEADER_HPP\n#define TYPE_TRAITS_HEADER_HPP\n\n/**\n *\
    \ @brief type traits / \u7C7B\u578B\u8403\u53D6\n *\n */\n\n#include <cstdint>\n\
    #include <type_traits>\n\nnamespace lib {\n\ntemplate <typename Type>\nstruct\
    \ promote_integral;\ntemplate <>\nstruct promote_integral<std::int32_t> {\n  using\
    \ type = std::int64_t;\n};\ntemplate <>\nstruct promote_integral<std::uint32_t>\
    \ {\n  using type = std::uint64_t;\n};\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate\
    \ <typename Type>\nusing promote_integral_t = typename promote_integral<Type>::type;\n\
    \ntemplate <typename T, typename U>\nusing longer_integral_t =\n    std::conditional_t<(sizeof(T)\
    \ > sizeof(U) || (sizeof(T) == sizeof(U) && std::is_signed_v<T>)),\n         \
    \              T, U>;\n\n} // namespace lib\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: traits/base.hpp
  requiredBy:
  - math/basic/binary_mul.hpp
  - math/basic/exgcd.hpp
  - math/basic/binary_pow.hpp
  - math/basic/crt.hpp
  - math/modulo/binomial_coefficient_mod.hpp
  timestamp: '2021-07-15 14:25:20+08:00'
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
