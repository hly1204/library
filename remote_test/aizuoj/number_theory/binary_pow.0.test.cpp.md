---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/basic/binary_mul.hpp
    title: "binary multiplication / \u5FEB\u901F\u4E58"
  - icon: ':heavy_check_mark:'
    path: math/basic/binary_pow.hpp
    title: "binary power / \u5FEB\u901F\u5E42"
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B
  bundledCode: "#line 1 \"remote_test/aizuoj/number_theory/binary_pow.0.test.cpp\"\
    \n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B\"\
    \n\n#include <iostream>\n\n#line 1 \"math/basic/binary_pow.hpp\"\n\n\n\n/**\n\
    \ * @brief binary power / \u5FEB\u901F\u5E42\n *\n */\n\n#include <cassert>\n\
    #include <type_traits>\n\n#line 1 \"traits/base.hpp\"\n\n\n\n/**\n * @brief type\
    \ traits / \u7C7B\u578B\u8403\u53D6\n *\n */\n\n#include <cstdint>\n#line 11 \"\
    traits/base.hpp\"\n\nnamespace lib {\n\ntemplate <typename Type>\nstruct promote_integral;\n\
    template <>\nstruct promote_integral<std::int32_t> {\n  using type = std::int64_t;\n\
    };\ntemplate <>\nstruct promote_integral<std::uint32_t> {\n  using type = std::uint64_t;\n\
    };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename Type>\nusing promote_integral_t\
    \ = typename promote_integral<Type>::type;\n\ntemplate <typename T, typename U>\n\
    using longer_integral_t =\n    std::conditional_t<(sizeof(T) > sizeof(U) || (sizeof(T)\
    \ == sizeof(U) && std::is_signed_v<T>)),\n                       T, U>;\n\n} //\
    \ namespace lib\n\n\n#line 1 \"math/basic/binary_mul.hpp\"\n\n\n\n/**\n * @brief\
    \ binary multiplication / \u5FEB\u901F\u4E58\n *\n */\n\n#line 10 \"math/basic/binary_mul.hpp\"\
    \n\n#line 12 \"math/basic/binary_mul.hpp\"\n\nnamespace lib {\n\nnamespace internal\
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
    \ internal\n\ntemplate <typename T1, typename T2, typename T3,\n          typename\
    \ T = longer_integral_t<longer_integral_t<T1, T2>, T3>>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2> && std::is_integral_v<T3> &&\n                   \
    \  (std::is_signed_v<T1> || std::is_signed_v<T2>),\n                 T>\nmul_mod(T1\
    \ x, T2 y, T3 mod) {\n  return internal::mul_mod<std::make_signed_t<T>>(x, y,\
    \ mod);\n}\n\ntemplate <typename T1, typename T2, typename T3,\n          typename\
    \ T = longer_integral_t<longer_integral_t<T1, T2>, T3>>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2> && std::is_integral_v<T3> &&\n                   \
    \  std::is_unsigned_v<T1> && std::is_unsigned_v<T2>,\n                 T>\nmul_mod(T1\
    \ x, T2 y, T3 mod) {\n  return internal::mul_mod<T>(x, y, mod);\n}\n\n} // namespace\
    \ lib\n\n\n#line 14 \"math/basic/binary_pow.hpp\"\n\nnamespace lib {\n\ntemplate\
    \ <typename T1, typename T2>\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>,\
    \ T1> pow(T1 x, T2 y) {\n  assert(y >= 0);\n  T1 res = 1;\n  for (; y != 0; y\
    \ >>= 1, x *= x)\n    if (y & 1) res *= x;\n  return res;\n}\n\ntemplate <typename\
    \ T1, typename T2, typename T3, typename T = longer_integral_t<T1, T3>>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2> && std::is_integral_v<T3>, T>\npow_mod(T1 x, T2 y,\
    \ T3 mod) {\n  assert(y >= 0);\n  T res = (mod != 1), tx = x;\n  for (; y != 0;\
    \ y >>= 1, tx = mul_mod(tx, tx, mod))\n    if (y & 1) res = mul_mod(res, tx, mod);\n\
    \  return res;\n}\n\n} // namespace lib\n\n\n#line 6 \"remote_test/aizuoj/number_theory/binary_pow.0.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, m;\n  std::cin >> n >> m;\n  std::cout << lib::pow_mod(n, m, 1000000007)\
    \ << '\\n';\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B\"\
    \n\n#include <iostream>\n\n#include \"math/basic/binary_pow.hpp\"\n\nint main()\
    \ {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\"\
    , \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, m;\n  std::cin >> n >> m;\n  std::cout << lib::pow_mod(n, m, 1000000007)\
    \ << '\\n';\n  return 0;\n}"
  dependsOn:
  - math/basic/binary_pow.hpp
  - traits/base.hpp
  - math/basic/binary_mul.hpp
  isVerificationFile: true
  path: remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 14:25:20+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
- /verify/remote_test/aizuoj/number_theory/binary_pow.0.test.cpp.html
title: remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
---
