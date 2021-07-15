---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/basic/exgcd.hpp
    title: "extended Euclidean algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\
      \u6CD5"
  - icon: ':heavy_check_mark:'
    path: traits/base.hpp
    title: "type traits / \u7C7B\u578B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_E
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_E
  bundledCode: "#line 1 \"remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp\"\
    \n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_E\"\
    \r\n\r\n#include <iostream>\r\n\r\n#line 1 \"math/basic/exgcd.hpp\"\n\n\n\r\n\
    /**\r\n * @brief extended Euclidean algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\
    \u5F97\u7B97\u6CD5\r\n *\r\n */\r\n\r\n#include <cassert>\r\n#include <tuple>\r\
    \n#include <type_traits>\r\n\r\n#line 1 \"traits/base.hpp\"\n\n\n\r\n/**\r\n *\
    \ @brief type traits / \u7C7B\u578B\u8403\u53D6\r\n *\r\n */\r\n\r\n#include <cstdint>\r\
    \n#line 11 \"traits/base.hpp\"\n\r\nnamespace lib {\r\n\r\ntemplate <typename\
    \ Type>\r\nstruct promote_integral;\r\ntemplate <>\r\nstruct promote_integral<std::int32_t>\
    \ {\r\n  using type = std::int64_t;\r\n};\r\ntemplate <>\r\nstruct promote_integral<std::uint32_t>\
    \ {\r\n  using type = std::uint64_t;\r\n};\r\n\r\n// \u8F85\u52A9\u6A21\u677F\r\
    \ntemplate <typename Type>\r\nusing promote_integral_t = typename promote_integral<Type>::type;\r\
    \n\r\ntemplate <typename T, typename U>\r\nusing longer_integral_t =\r\n    std::conditional_t<(sizeof(T)\
    \ > sizeof(U) || (sizeof(T) == sizeof(U) && std::is_signed_v<T>)),\r\n       \
    \                T, U>;\r\n\r\n} // namespace lib\r\n\r\n\n#line 14 \"math/basic/exgcd.hpp\"\
    \n\r\nnamespace lib::internal {\r\n\r\ntemplate <typename T>\r\nstd::enable_if_t<std::is_integral_v<T>,\
    \ T> gcd(T a, T b) {\r\n  while (b != 0) std::tie(a, b) = std::make_tuple(b, a\
    \ % b);\r\n  return a;\r\n}\r\n\r\ntemplate <typename T, typename S = std::make_signed_t<T>>\r\
    \nstd::enable_if_t<std::is_integral_v<T>, std::tuple<T, S, S>> exgcd(T a, T b)\
    \ {\r\n  S a_p = a, b_p = b, x1 = 1, x2 = 0, x3 = 0, x4 = 1;\r\n  while (b_p !=\
    \ 0) {\r\n    S q = a_p / b_p;\r\n    std::tie(x1, x2, x3, x4, a_p, b_p) =\r\n\
    \        std::make_tuple(x3, x4, x1 - x3 * q, x2 - x4 * q, b_p, a_p - b_p * q);\r\
    \n  }\r\n  return std::make_tuple(static_cast<T>(a_p), x1, x2);\r\n}\r\n\r\ntemplate\
    \ <typename T>\r\nstd::enable_if_t<std::is_integral_v<T>, T> inv_mod(T x, T mod)\
    \ {\r\n  using S = std::make_signed_t<T>;\r\n  S a = x, b = mod, x1 = 1, x3 =\
    \ 0;\r\n  assert(a < b);\r\n  while (b != 0) {\r\n    S q                    =\
    \ a / b;\r\n    std::tie(x1, x3, a, b) = std::make_tuple(x3, x1 - x3 * q, b, a\
    \ - b * q);\r\n  }\r\n  assert(a == 1 && \"inv_mod_error\");\r\n  return static_cast<T>(x1\
    \ < 0 ? x1 + mod : x1);\r\n}\r\n\r\n} // namespace lib::internal\r\n\r\nnamespace\
    \ lib {\r\n\r\ntemplate <typename T1, typename T2, typename T = longer_integral_t<T1,\
    \ T2>>\r\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>, T>\
    \ gcd(T1 a, T2 b) {\r\n  return internal::gcd<T>(a, b);\r\n}\r\n\r\ntemplate <typename\
    \ T1, typename T2, typename T = longer_integral_t<T1, T2>,\r\n          typename\
    \ S = std::make_signed_t<T>>\r\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>,\
    \ std::tuple<T, S, S>>\r\nexgcd(T1 a, T2 b) {\r\n  return internal::exgcd<T, S>(a,\
    \ b);\r\n}\r\n\r\ntemplate <typename T1, typename T2, typename T = longer_integral_t<T1,\
    \ T2>>\r\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>, T>\
    \ inv_mod(T1 x, T2 mod) {\r\n  return internal::inv_mod<T>(x, mod);\r\n}\r\n\r\
    \n} // namespace lib\r\n\r\n\n#line 6 \"remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp\"\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int a, b;\r\n  std::cin >> a >> b;\r\n  int c, d;\r\n  std::tie(std::ignore,\
    \ c, d) = lib::exgcd(a, b);\r\n  std::cout << c << ' ' << d << '\\n';\r\n  return\
    \ 0;\r\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_E\"\
    \r\n\r\n#include <iostream>\r\n\r\n#include \"math/basic/exgcd.hpp\"\r\n\r\nint\
    \ main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int a, b;\r\n  std::cin >> a >> b;\r\n  int c, d;\r\n  std::tie(std::ignore,\
    \ c, d) = lib::exgcd(a, b);\r\n  std::cout << c << ' ' << d << '\\n';\r\n  return\
    \ 0;\r\n}"
  dependsOn:
  - math/basic/exgcd.hpp
  - traits/base.hpp
  isVerificationFile: true
  path: remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
- /verify/remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp.html
title: remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
---
