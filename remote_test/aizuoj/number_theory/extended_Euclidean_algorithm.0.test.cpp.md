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
    \n\n#include <iostream>\n\n#line 1 \"math/basic/exgcd.hpp\"\n\n\n\n/**\n * @brief\
    \ extended Euclidean algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\u6CD5\
    \n *\n */\n\n#include <cassert>\n#include <tuple>\n#include <type_traits>\n\n\
    #line 1 \"traits/base.hpp\"\n\n\n\n/**\n * @brief type traits / \u7C7B\u578B\u8403\
    \u53D6\n *\n */\n\n#include <cstdint>\n#line 11 \"traits/base.hpp\"\n\nnamespace\
    \ lib {\n\ntemplate <typename Type> struct promote_integral;\ntemplate <> struct\
    \ promote_integral<std::int32_t> { using type = std::int64_t; };\ntemplate <>\
    \ struct promote_integral<std::uint32_t> { using type = std::uint64_t; };\n\n\
    // \u8F85\u52A9\u6A21\u677F\ntemplate <typename Type> using promote_integral_t\
    \ = typename promote_integral<Type>::type;\n\ntemplate <typename T, typename U>\n\
    using longer_integral_t =\n    std::conditional_t<(sizeof(T) > sizeof(U) || (sizeof(T)\
    \ == sizeof(U) && std::is_signed_v<T>)),\n                       T, U>;\n\n} //\
    \ namespace lib\n\n\n#line 14 \"math/basic/exgcd.hpp\"\n\nnamespace lib {\n\n\
    namespace internal {\n\ntemplate <typename T> std::enable_if_t<std::is_integral_v<T>,\
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
    \ namespace lib\n\n\n#line 6 \"remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int a, b;\n  std::cin >> a >> b;\n  int c, d;\n  std::tie(std::ignore, c, d)\
    \ = lib::exgcd(a, b);\n  std::cout << c << ' ' << d << '\\n';\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_E\"\
    \n\n#include <iostream>\n\n#include \"math/basic/exgcd.hpp\"\n\nint main() {\n\
    #ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\", \"w\"\
    , stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int a, b;\n  std::cin >> a >> b;\n  int c, d;\n  std::tie(std::ignore, c, d)\
    \ = lib::exgcd(a, b);\n  std::cout << c << ' ' << d << '\\n';\n  return 0;\n}"
  dependsOn:
  - math/basic/exgcd.hpp
  - traits/base.hpp
  isVerificationFile: true
  path: remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-05 14:57:46+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
- /verify/remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp.html
title: remote_test/aizuoj/number_theory/extended_Euclidean_algorithm.0.test.cpp
---
