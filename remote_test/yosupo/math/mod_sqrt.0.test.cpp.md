---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/basic/binary_mul.hpp
    title: "binary multiplication / \u5FEB\u901F\u4E58"
  - icon: ':question:'
    path: math/basic/binary_pow.hpp
    title: "binary power / \u5FEB\u901F\u5E42"
  - icon: ':question:'
    path: math/basic/exgcd.hpp
    title: "extended Euclidean algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\
      \u6CD5"
  - icon: ':x:'
    path: math/modulo/sqrt_mod.hpp
    title: "square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839"
  - icon: ':question:'
    path: traits/base.hpp
    title: "type traits / \u7C7B\u578B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sqrt_mod
    links:
    - https://judge.yosupo.jp/problem/sqrt_mod
  bundledCode: "#line 1 \"remote_test/yosupo/math/mod_sqrt.0.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#include <iostream>\n\n#line\
    \ 1 \"math/modulo/sqrt_mod.hpp\"\n\n\n\n/**\n * @brief square root mod / \u6A21\
    \u610F\u4E49\u4E0B\u5E73\u65B9\u6839\n *\n */\n\n#include <cassert>\n#include\
    \ <optional>\n#include <random>\n\n#line 1 \"math/basic/binary_pow.hpp\"\n\n\n\
    \n/**\n * @brief binary power / \u5FEB\u901F\u5E42\n *\n */\n\n#line 10 \"math/basic/binary_pow.hpp\"\
    \n#include <type_traits>\n\n#line 1 \"traits/base.hpp\"\n\n\n\n/**\n * @brief\
    \ type traits / \u7C7B\u578B\u8403\u53D6\n *\n */\n\n#include <cstdint>\n#line\
    \ 11 \"traits/base.hpp\"\n\nnamespace lib {\n\ntemplate <typename Type> struct\
    \ promote_integral;\ntemplate <> struct promote_integral<std::int32_t> { using\
    \ type = std::int64_t; };\ntemplate <> struct promote_integral<std::uint32_t>\
    \ { using type = std::uint64_t; };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename\
    \ Type> using promote_integral_t = typename promote_integral<Type>::type;\n\n\
    template <typename T, typename U,\n          bool = (sizeof(T) > sizeof(U) ||\
    \ (sizeof(T) == sizeof(U) && std::is_signed_v<T>))>\nstruct longer_integral;\n\
    template <typename T, typename U> struct longer_integral<T, U, true> { using type\
    \ = T; };\ntemplate <typename T, typename U> struct longer_integral<T, U, false>\
    \ { using type = U; };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename T, typename\
    \ U> using longer_integral_t = typename longer_integral<T, U>::type;\n\n} // namespace\
    \ lib\n\n\n#line 1 \"math/basic/binary_mul.hpp\"\n\n\n\n/**\n * @brief binary\
    \ multiplication / \u5FEB\u901F\u4E58\n *\n */\n\n#line 10 \"math/basic/binary_mul.hpp\"\
    \n\n#line 12 \"math/basic/binary_mul.hpp\"\n\nnamespace lib {\n\nnamespace internal\
    \ {\n\ntemplate <typename T> std::enable_if_t<std::is_integral_v<T>, T> mul_mod(T\
    \ x, T y, T mod) {\n  if ((x %= mod) < 0) x += mod;\n  if ((y %= mod) < 0) y +=\
    \ mod;\n  if constexpr (sizeof(T) < 8) {\n    return static_cast<T>(static_cast<promote_integral_t<T>>(x)\
    \ * y % mod);\n  } else {\n    T res = 0;\n    for (; y != 0; y >>= 1) {\n   \
    \   if ((y & 1) && (res += x) >= mod) res -= mod;\n      if ((x <<= 1) >= mod)\
    \ x -= mod;\n    }\n    return res;\n  }\n}\n\n} // namespace internal\n\ntemplate\
    \ <typename T1, typename T2, typename T3,\n          typename T = longer_integral_t<longer_integral_t<T1,\
    \ T2>, T3>>\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>\
    \ && std::is_integral_v<T3>, T>\nmul_mod(T1 x, T2 y, T3 mod) {\n  if constexpr\
    \ (std::is_signed_v<T1> || std::is_signed_v<T2>) {\n    return internal::mul_mod<std::make_signed_t<T>>(x,\
    \ y, mod);\n  } else {\n    return internal::mul_mod<T>(x, y, mod);\n  }\n}\n\n\
    } // namespace lib\n\n\n#line 14 \"math/basic/binary_pow.hpp\"\n\nnamespace lib\
    \ {\n\ntemplate <typename T1, typename T2>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2>, T1> pow(T1 x, T2 y) {\n  assert(y >= 0);\n  T1 res\
    \ = 1;\n  for (; y != 0; y >>= 1, x *= x)\n    if (y & 1) res *= x;\n  return\
    \ res;\n}\n\ntemplate <typename T1, typename T2, typename T3>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2> && std::is_integral_v<T3>, T1>\npow_mod(T1 x, T2 y,\
    \ T3 mod) {\n  assert(y >= 0);\n  T1 res = (mod != 1);\n  if constexpr (sizeof(T1)\
    \ < 8) {\n    using S = promote_integral_t<T1>;\n    for (; y != 0; y >>= 1, x\
    \ = static_cast<S>(x) * x % mod)\n      if (y & 1) res = static_cast<S>(res) *\
    \ x % mod;\n  } else {\n    // \u4F7F\u5F97 T1 \u4E3A 64 \u4F4D\u6574\u578B\u65F6\
    \u4E5F\u80FD\u5DE5\u4F5C\n    for (; y != 0; y >>= 1, x = mul_mod(x, x, mod))\n\
    \      if (y & 1) res = mul_mod(res, x, mod);\n  }\n  return res;\n}\n\n} // namespace\
    \ lib\n\n\n#line 1 \"math/basic/exgcd.hpp\"\n\n\n\n/**\n * @brief extended Euclidean\
    \ algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\u6CD5\n *\n */\n\n#line\
    \ 10 \"math/basic/exgcd.hpp\"\n#include <tuple>\n#line 12 \"math/basic/exgcd.hpp\"\
    \n\n#line 14 \"math/basic/exgcd.hpp\"\n\nnamespace lib {\n\nnamespace internal\
    \ {\n\ntemplate <typename T> std::enable_if_t<std::is_integral_v<T>, T> gcd(T\
    \ a, T b) {\n  while (b != 0) std::tie(a, b) = std::make_tuple(b, a % b);\n  return\
    \ a;\n}\n\ntemplate <typename T, typename S = std::make_signed_t<T>>\nstd::enable_if_t<std::is_integral_v<T>,\
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
    \ namespace lib\n\n\n#line 15 \"math/modulo/sqrt_mod.hpp\"\n\nnamespace lib {\n\
    \n/**\n * @brief \u6A21\u5E73\u65B9\u6839\uFF0C\u8FD4\u56DE\u8F83\u5C0F\u7684\u4E00\
    \u4E2A\uFF0C\u82E5 x=0 \u5219\u8FD4\u56DE 0 \uFF0C\u65E0\u89E3\u5219\u8FD4\u56DE\
    \u7A7A\n *\n * @tparam T\n * @param x\n * @param p\n * @return std::optional<T>\n\
    \ */\ntemplate <typename T> std::optional<T> sqrt_mod_prime(T x, T p) {\n  if\
    \ (p == 2 || x <= 1) return x;\n  if (pow_mod(x, p >> 1, p) != 1) return {}; //\
    \ (p>>1)=(p-1)/2 \u6B27\u62C9\u51C6\u5219\n  if ((p & 3) == 3) {\n    x = pow_mod(x,\
    \ (p + 1) >> 2, p);\n    return {x < p - x ? x : p - x};\n  }\n\n  T s = p - 1;\n\
    \  int r = 0;\n  while ((s & 1) == 0) {\n    ++r;\n    s >>= 1;\n  }\n\n  static\
    \ std::random_device rd;\n  static std::mt19937_64 gen(rd());\n  std::uniform_int_distribution<T>\
    \ dis(T(2), p - 1);\n\n  // \u82E5\u5E7F\u4E49\u9ECE\u66FC\u5047\u8BBE\u6210\u7ACB\
    \uFF0C\u53EF\u4EE5\u4ECE 2 \u5F00\u59CB\u679A\u4E3E\uFF0C\u6700\u5C0F\u7684\u4E8C\
    \u6B21\u975E\u5269\u4F59\u5927\u7EA6\u4E3A O(\\log^2 p) \u7EA7\u522B\n  // \u9A8C\
    \u8BC1\u4E00\u6B21\u9700\u8981\u6D88\u8017 O(\\log p) \u65F6\u95F4\uFF0C\u90A3\
    \u4E48\u65F6\u95F4\u590D\u6742\u5EA6\u8F83\u9AD8\uFF0C\u82E5\u7528\u968F\u673A\
    \u65B9\u6CD5\u5219\u53EF\u8BC1\u660E\u671F\u671B 2 \u6B21\u627E\u5230\n\n  T v;\
    \ // \u968F\u673A\u4E00\u4E2A\u4E8C\u6B21\u975E\u5269\u4F59\n  while (pow_mod(v\
    \ = dis(gen), p >> 1, p) == 1) {\n  }\n\n  T w = pow_mod(v, s, p); // w = v^s\n\
    \n  int t = 0;\n  T ix = pow_mod(x, p - 2, p);            // ix = x^{-1}\n  x\
    \ = pow_mod(x, (s + 1) >> 1, p);        // x = x^{(s+1)/2}\n  T y = mul_mod(mul_mod(x,\
    \ x, p), ix, p); // y = x^s\n  while (pow_mod(y, 1 << t, p) != 1) ++t; // 2^t\
    \ = ord(x^s) \uFF0C\u8BA1\u7B97 t0\n  while (t != 0) {\n    x = mul_mod(x, pow_mod(w,\
    \ 1 << (r - t - 1), p), p);\n    y = mul_mod(mul_mod(x, x, p), ix, p);\n    for\
    \ (--t; t != 0 && pow_mod(y, 1 << (t - 1), p) == 1; --t) {\n    }\n  }\n  return\
    \ x < p - x ? x : p - x;\n}\n\n/**\n * @brief Hensel lifting \u6C42\u6A21\u7D20\
    \u6570\u5E42\u6B21\u7684\u5E73\u65B9\u6839\uFF0C p \u4E0D\u80FD\u4E3A 2 \u4E14\
    \ x \u4E0D\u80FD\u6574\u9664 p\n *\n * @tparam T\n * @param x\n * @param p\n *\
    \ @param e\n * @return std::optional<T>\n */\ntemplate <typename T> std::optional<T>\
    \ sqrt_mod_prime_power(T x, T p, int e) {\n  if (x % p == 0 || (p & 1) == 0) return\
    \ {};\n  auto a = sqrt_mod_prime(x % p, p);\n  if (!a) return {};\n  T pe = lib::pow(p,\
    \ e);\n  T b = inv_mod(a.value(), pe);\n  T it = inv_mod(2, pe);\n  for (int i\
    \ = 1; i < e; i <<= 1) {\n    b += mul_mod(b, mul_mod(1 + pe - mul_mod(x, mul_mod(b,\
    \ b, pe), pe), it, pe), pe);\n    if (b >= pe) b -= pe;\n  }\n  return inv_mod(b,\
    \ pe);\n}\n\n} // namespace lib\n\n\n#line 6 \"remote_test/yosupo/math/mod_sqrt.0.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int t;\n  std::cin >> t;\n  while (t--) {\n    int k, p;\n    std::cin >> k\
    \ >> p;\n    std::cout << lib::sqrt_mod_prime(k, p).value_or(-1) << '\\n';\n \
    \ }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\n\n#include\
    \ <iostream>\n\n#include \"math/modulo/sqrt_mod.hpp\"\n\nint main() {\n#ifdef\
    \ LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n\
    #endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n  int t;\n  std::cin\
    \ >> t;\n  while (t--) {\n    int k, p;\n    std::cin >> k >> p;\n    std::cout\
    \ << lib::sqrt_mod_prime(k, p).value_or(-1) << '\\n';\n  }\n  return 0;\n}"
  dependsOn:
  - math/modulo/sqrt_mod.hpp
  - math/basic/binary_pow.hpp
  - traits/base.hpp
  - math/basic/binary_mul.hpp
  - math/basic/exgcd.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/mod_sqrt.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-11 23:09:55+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: remote_test/yosupo/math/mod_sqrt.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/mod_sqrt.0.test.cpp
- /verify/remote_test/yosupo/math/mod_sqrt.0.test.cpp.html
title: remote_test/yosupo/math/mod_sqrt.0.test.cpp
---
