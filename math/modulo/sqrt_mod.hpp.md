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
    path: math/basic/exgcd.hpp
    title: "extended Euclidean algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\
      \u6CD5"
  - icon: ':heavy_check_mark:'
    path: traits/base.hpp
    title: "type traits / \u7C7B\u578B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/mod_sqrt.0.test.cpp
    title: remote_test/yosupo/math/mod_sqrt.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839"
    links: []
  bundledCode: "#line 1 \"math/modulo/sqrt_mod.hpp\"\n\n\n\n#include <cassert>\n#include\
    \ <optional>\n#include <random>\n\n#line 1 \"math/basic/binary_pow.hpp\"\n\n\n\
    \n#line 5 \"math/basic/binary_pow.hpp\"\n#include <type_traits>\n\n#line 1 \"\
    traits/base.hpp\"\n\n\n\n#include <cstdint>\n\nnamespace lib {\n\ntemplate <typename\
    \ Type> struct promote_integral;\ntemplate <> struct promote_integral<std::int32_t>\
    \ { using type = std::int64_t; };\ntemplate <> struct promote_integral<std::uint32_t>\
    \ { using type = std::uint64_t; };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename\
    \ Type> using promote_integral_t = typename promote_integral<Type>::type;\n\n\
    template <typename T, typename U,\n          bool = (sizeof(T) > sizeof(U) ||\
    \ (sizeof(T) == sizeof(U) && std::is_signed_v<T>))>\nstruct longer_integral;\n\
    template <typename T, typename U> struct longer_integral<T, U, true> { using type\
    \ = T; };\ntemplate <typename T, typename U> struct longer_integral<T, U, false>\
    \ { using type = U; };\n\n// \u8F85\u52A9\u6A21\u677F\ntemplate <typename T, typename\
    \ U> using longer_integral_t = typename longer_integral<T, U>::type;\n\n} // namespace\
    \ lib\n\n/**\n * @brief type traits / \u7C7B\u578B\u8403\u53D6\n *\n */\n\n\n\
    #line 1 \"math/basic/binary_mul.hpp\"\n\n\n\n#line 5 \"math/basic/binary_mul.hpp\"\
    \n\n#line 7 \"math/basic/binary_mul.hpp\"\n\nnamespace lib {\n\nnamespace internal\
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
    } // namespace lib\n\n/**\n * @brief binary multiplication / \u5FEB\u901F\u4E58\
    \n *\n */\n\n\n#line 9 \"math/basic/binary_pow.hpp\"\n\nnamespace lib {\n\ntemplate\
    \ <typename T1, typename T2>\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>,\
    \ T1> pow(T1 x, T2 y) {\n  assert(y >= 0);\n  T1 res = 1;\n  for (; y != 0; y\
    \ >>= 1, x *= x)\n    if (y & 1) res *= x;\n  return res;\n}\n\ntemplate <typename\
    \ T1, typename T2, typename T3>\nstd::enable_if_t<std::is_integral_v<T1> && std::is_integral_v<T2>\
    \ && std::is_integral_v<T3>, T1>\npow_mod(T1 x, T2 y, T3 mod) {\n  assert(y >=\
    \ 0);\n  T1 res = (mod != 1);\n  if constexpr (sizeof(T1) < 8) {\n    using S\
    \ = promote_integral_t<T1>;\n    for (; y != 0; y >>= 1, x = static_cast<S>(x)\
    \ * x % mod)\n      if (y & 1) res = static_cast<S>(res) * x % mod;\n  } else\
    \ {\n    // \u4F7F\u5F97 T1 \u4E3A 64 \u4F4D\u6574\u578B\u65F6\u4E5F\u80FD\u5DE5\
    \u4F5C\n    for (; y != 0; y >>= 1, x = mul_mod(x, x, mod))\n      if (y & 1)\
    \ res = mul_mod(res, x, mod);\n  }\n  return res;\n}\n\n} // namespace lib\n\n\
    /**\n * @brief binary power / \u5FEB\u901F\u5E42\n *\n */\n\n\n#line 1 \"math/basic/exgcd.hpp\"\
    \n\n\n\n#line 5 \"math/basic/exgcd.hpp\"\n#include <tuple>\n#line 7 \"math/basic/exgcd.hpp\"\
    \n\n#line 9 \"math/basic/exgcd.hpp\"\n\nnamespace lib {\n\nnamespace internal\
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
    \ namespace lib\n\n/**\n * @brief extended Euclidean algorithm / \u6269\u5C55\u6B27\
    \u51E0\u91CC\u5F97\u7B97\u6CD5\n *\n */\n\n\n#line 10 \"math/modulo/sqrt_mod.hpp\"\
    \n\nnamespace lib {\n\n// \u8FD4\u56DE\u8F83\u5C0F\u7684\u4E00\u4E2A\uFF0C\u82E5\
    \ x=0 \u5219\u8FD4\u56DE 0\ntemplate <typename T> std::optional<T> sqrt_mod_prime(T\
    \ x, T p) {\n  if (p == 2 || x <= 1) return x;\n  if (pow_mod(x, p >> 1, p) !=\
    \ 1) return {}; // (p>>1)=(p-1)/2 \u6B27\u62C9\u51C6\u5219\n  if ((p & 3) == 3)\
    \ {\n    x = pow_mod(x, (p + 1) >> 2, p);\n    return {x < p - x ? x : p - x};\n\
    \  }\n\n  T s = p - 1;\n  int r = 0;\n  while ((s & 1) == 0) {\n    ++r;\n   \
    \ s >>= 1;\n  }\n\n  static std::random_device rd;\n  static std::mt19937_64 gen(rd());\n\
    \  std::uniform_int_distribution<T> dis(T(2), p - 1);\n\n  // \u82E5\u5E7F\u4E49\
    \u9ECE\u66FC\u5047\u8BBE\u6210\u7ACB\uFF0C\u53EF\u4EE5\u4ECE 2 \u5F00\u59CB\u679A\
    \u4E3E\uFF0C\u6700\u5C0F\u7684\u4E8C\u6B21\u975E\u5269\u4F59\u5927\u7EA6\u4E3A\
    \ O(\\log^2 p) \u7EA7\u522B\n  // \u9A8C\u8BC1\u4E00\u6B21\u9700\u8981\u6D88\u8017\
    \ O(\\log p) \u65F6\u95F4\uFF0C\u90A3\u4E48\u65F6\u95F4\u590D\u6742\u5EA6\u8F83\
    \u9AD8\uFF0C\u82E5\u7528\u968F\u673A\u65B9\u6CD5\u5219\u53EF\u8BC1\u660E\u671F\
    \u671B 2 \u6B21\u627E\u5230\n\n  T v; // \u968F\u673A\u4E00\u4E2A\u4E8C\u6B21\u975E\
    \u5269\u4F59\n  while (pow_mod(v = dis(gen), p >> 1, p) == 1) {\n  }\n\n  T w\
    \ = pow_mod(v, s, p); // w = v^s\n\n  int t = 0;\n  T ix = pow_mod(x, p - 2, p);\
    \            // ix = x^{-1}\n  x = pow_mod(x, (s + 1) >> 1, p);        // x =\
    \ x^{(s+1)/2}\n  T y = mul_mod(mul_mod(x, x, p), ix, p); // y = x^s\n  while (pow_mod(y,\
    \ 1 << t, p) != 1) ++t; // 2^t = ord(x^s) \uFF0C\u8BA1\u7B97 t0\n  while (t !=\
    \ 0) {\n    x = mul_mod(x, pow_mod(w, 1 << (r - t - 1), p), p);\n    y = mul_mod(mul_mod(x,\
    \ x, p), ix, p);\n    for (--t; t != 0 && pow_mod(y, 1 << (t - 1), p) == 1; --t)\
    \ {\n    }\n  }\n  return x < p - x ? x : p - x;\n}\n\n// \u5229\u7528 Hensel\
    \ lifting \u5373\u53EF\ntemplate <typename T> std::optional<T> sqrt_mod_prime_power(T\
    \ x, T p, int e) {\n  if (x % p == 0 || (p & 1) == 0) return {};\n  auto a = sqrt_mod_prime(x\
    \ % p, p);\n  if (!a) return {};\n  T pe = lib::pow(p, e);\n  T b = inv_mod(a.value(),\
    \ pe);\n  T it = inv_mod(2, pe);\n  for (int i = 1; i < e; i <<= 1) {\n    b +=\
    \ mul_mod(b, mul_mod(1 + pe - mul_mod(x, mul_mod(b, b, pe), pe), it, pe), pe);\n\
    \    if (b >= pe) b -= pe;\n  }\n  return inv_mod(b, pe);\n}\n\n} // namespace\
    \ lib\n\n/**\n * @brief square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\
    \u6839\n *\n */\n\n\n"
  code: "#ifndef SQRT_MOD_HEADER_HPP\n#define SQRT_MOD_HEADER_HPP\n\n#include <cassert>\n\
    #include <optional>\n#include <random>\n\n#include \"../basic/binary_pow.hpp\"\
    \n#include \"../basic/exgcd.hpp\"\n\nnamespace lib {\n\n// \u8FD4\u56DE\u8F83\u5C0F\
    \u7684\u4E00\u4E2A\uFF0C\u82E5 x=0 \u5219\u8FD4\u56DE 0\ntemplate <typename T>\
    \ std::optional<T> sqrt_mod_prime(T x, T p) {\n  if (p == 2 || x <= 1) return\
    \ x;\n  if (pow_mod(x, p >> 1, p) != 1) return {}; // (p>>1)=(p-1)/2 \u6B27\u62C9\
    \u51C6\u5219\n  if ((p & 3) == 3) {\n    x = pow_mod(x, (p + 1) >> 2, p);\n  \
    \  return {x < p - x ? x : p - x};\n  }\n\n  T s = p - 1;\n  int r = 0;\n  while\
    \ ((s & 1) == 0) {\n    ++r;\n    s >>= 1;\n  }\n\n  static std::random_device\
    \ rd;\n  static std::mt19937_64 gen(rd());\n  std::uniform_int_distribution<T>\
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
    \ x < p - x ? x : p - x;\n}\n\n// \u5229\u7528 Hensel lifting \u5373\u53EF\ntemplate\
    \ <typename T> std::optional<T> sqrt_mod_prime_power(T x, T p, int e) {\n  if\
    \ (x % p == 0 || (p & 1) == 0) return {};\n  auto a = sqrt_mod_prime(x % p, p);\n\
    \  if (!a) return {};\n  T pe = lib::pow(p, e);\n  T b = inv_mod(a.value(), pe);\n\
    \  T it = inv_mod(2, pe);\n  for (int i = 1; i < e; i <<= 1) {\n    b += mul_mod(b,\
    \ mul_mod(1 + pe - mul_mod(x, mul_mod(b, b, pe), pe), it, pe), pe);\n    if (b\
    \ >= pe) b -= pe;\n  }\n  return inv_mod(b, pe);\n}\n\n} // namespace lib\n\n\
    /**\n * @brief square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839\n\
    \ *\n */\n\n#endif"
  dependsOn:
  - math/basic/binary_pow.hpp
  - traits/base.hpp
  - math/basic/binary_mul.hpp
  - math/basic/exgcd.hpp
  isVerificationFile: false
  path: math/modulo/sqrt_mod.hpp
  requiredBy: []
  timestamp: '2021-06-06 20:47:15+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/mod_sqrt.0.test.cpp
documentation_of: math/modulo/sqrt_mod.hpp
layout: document
title: "square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839"
---

## 模平方根

- `sqrt_mod_prime(a, p)` 返回满足关于 $x$ 的同余方程 $x^2\equiv a\pmod{p}$ 的解，且类型为 `std::optional<decltype(a)>` ，若有解则仅返回较小的，否则返回 `std::nullopt` 。
- `sqrt_mod_prime_power(a, p, e)` 可由上一个函数加 Hensel lifting （ $p$-adic vairant of Newton's method ）得到。 **注意** ：要求 $a\nmid p$ 且 $p\neq 2$ （当 $p=2$ 或 $a\mid p$ 时是平凡的）。

## Euler 判别准则

> Euler 判别准则： 设 $p$ 为奇素数， $n$ 为正整数， $\gcd(a,p)=1$ ，则 $a$ 是一个 $n$ 次剩余当且仅当 $a^{(p-1)/\delta}\equiv 1\pmod{p}$ ，其中 $\delta =\gcd(p-1,n)$ 。

## 元素的阶

> 定义：在模正整数 $m$ 意义下，对于一个正整数 $x$ 与 $m$ 互素，我们说 $x$ 的阶为 $t$ ，记作 $\operatorname{ord}_{m}(x)=t$ ，其中 $t$ 为满足 $x^{t}\equiv 1\pmod{m}$ 的最小 **正** 整数。

当模数明确时，也简记为 $\operatorname{ord}(x)$ ，而当 $x$ 与 $m$ 不互素时，则为未定义。

下面在模正整数 $m$ 意义下，且 $\gcd(x,m)=1$ ，考虑 $\operatorname{ord}(x)=t$ ，有

$$
x^{t}\equiv 1\pmod{m}
$$

且对于某个正整数 $k$ 存在

$$
\left(x^{k}\right)^{\operatorname{ord}(x^{k})}\equiv 1\pmod{m}
$$

显然 $k\operatorname{ord}(x^{k})\geq t$ 且

$$
t\mid k\operatorname{ord}(x^{k})\implies \frac{t}{\gcd(t,k)}\mid \operatorname{ord}(x^{k})
$$

又因为

$$
\left(x^{k}\right)^{t/\gcd(t,k)}=\left(x^{t}\right)^{k/\gcd(t,k)}\equiv 1\pmod{m}
$$

我们有

$$
\left.
\begin{aligned}
\left(x^{t/\gcd(t,k)}\right)^{k}\equiv 1\pmod{m}\\
\left(x^{\operatorname{ord}(x^{k})}\right)^{k}\equiv 1\pmod{m}
\end{aligned}
\right\}
\implies \frac{t}{\gcd(t,k)}\geq \operatorname{ord}(x^{k}),\quad \operatorname{ord}(x^{k})\mid \frac{t}{\gcd(t,k)}
$$

综上，有 $\operatorname{ord}(x^{k})=\frac{\operatorname{ord}(x)}{\gcd(\operatorname{ord}(x),k)}$ 。

当模数 $m$ 为奇素数时，原根 $g$ 的阶为 $m-1$ 。

## Tonelli-Shanks 算法

设 $p$ 为奇素数，求关于 $x$ 的同余方程 $x^{2}\equiv a\pmod{p}$ 的解（不考虑 $a\equiv 0\pmod{p}$ 的情况）。

使用欧拉准则判断方程是否有解，若有解，则 $a^{\frac{p-1}{2}}\equiv 1\pmod{p}$ 否则 $a^{\frac{p-1}{2}}\equiv -1\pmod{p}$ 。

下面仅考虑有解的情况。

**特殊情况** ：若 $p\bmod{4}=3$ 那么有

$$
\left(a^{\frac{p+1}{4}}\right)^{2}\equiv a^{\frac{p+1}{2}}\equiv x^{p+1}\equiv x^{2}\cdot x^{p-1}\equiv x^{2}\pmod{p}
$$

那么 $a^{\frac{p+1}{4}}$ 为一个解。我们可以在参考文献中找到另一种特殊情况，但是个人认为没有必要。

找到 $r,s$ 满足 $2^{r}\cdot s=p-1$ 且 $s$ 为奇数，在 $\mathbb{F} _ p ^\times$ 中用随机方法寻找一个二次 **非** 剩余 $v$ ，存在原根 $g^{k}\equiv v\pmod{p}$ 且 $k$ 为奇数，那么对于 $\operatorname{ord}(v^{s})=\operatorname{ord}(g^{sk})=\frac{2^{r}\cdot s}{\gcd(2^{r}\cdot s,sk)}=2^{r}$ ，令 $x_{0}=a^{\frac{s+1}{2}}\bmod{p},w=v^{s}\bmod{p}$ ，显然 $v^{s}$ 的阶为 $2^{r}$ ，对于 $x_{0}$ ，有

$$
\left(\frac{x_{0}^{2}}{a}\right)^{2^{r-1}}\equiv \left(\frac{a^{s+1}}{a}\right)^{2^{r-1}}\equiv a^{2^{r-1}\cdot s}\equiv a^{\frac{p-1}{2}}\equiv 1\pmod{p}
$$

令 $\displaystyle 2^{t_{0}}=\operatorname{ord}\left(\frac{x_{0}^{2}}{a}\right)$ （可以发现 $x_{0}^{2}/a=a^{s}$ 的阶是二的幂次），且设

$$
x_{i+1}=x_{i}\cdot w^{2^{r-t_{i}-1}},\quad 2^{t_{i+1}}=\operatorname{ord}\left(\frac{x_{i+1}^{2}}{a}\right)
$$

注意到 $\displaystyle \operatorname{ord}\left(\frac{x_{i}^{2}}{a}\right)=2^{t_{i}}\implies\left(\frac{x_{i}^{2}}{a}\right)^{2^{t_{i}-1}}\equiv -1\pmod{p}$ ，同样的 $\operatorname{ord}(w)=2^{r}\implies w^{2^{r-1}}\equiv -1\pmod{p}$ （两个阶为二的幂次的元素的乘积的阶也为二的幂次），那么

$$
\begin{aligned}
\left(\frac{x_{i+1}^{2}}{a}\right)^{2^{t_{i}-1}}&\equiv\left(\frac{\left(x_{i}\cdot w^{2^{r-t_{i}-1}}\right)^{2}}{a}\right)^{2^{t_{i}-1}}\\
&\equiv \left(\frac{x_{i}^{2}}{a}\right)^{2^{t_{i}-1}}\left(w^{2\cdot 2^{r-t_{i}-1}}\right)^{2^{t_{i}-1}}\\
&\equiv -1\cdot -1\\
&\equiv 1\pmod{p}
\end{aligned}
$$

可以发现 $t_{i+1}\lt t_{i}$ ，而 $t_{0}\lt r\lt \log_{2}(p)$ ，那么 $t_{0}$ 可枚举计算，而 $t_{i}$ 每一次至少减少 $1$ 最多减少 $\log_{2}(p)$ 次，当 $t_{n}=0$ 时有 $x_{n}^{2}\equiv a\pmod{p}$ 得到了一个解。


## Cipolla 算法

与上述问题相同，我们寻找一个多项式 $f(x)=x^2-tx+a\in\mathbb{F}_p[x]$ 且 $f(x)$ 在 $\mathbb{F}_p[x]$ 上不可约（即 $t^2-4a$ 为二次非剩余，使用随机方法寻找 $t$ 期望需要两次，但是这里的证明不是“显然”的），此时 $\mathbb{F}_p[x]/f(x)$ 是一个有 $p^2$ 个元素的域。我们计算 $x^{(p+1)/2}\bmod{f(x)}$ 为一个解。

该算法的时间是 $O(\log p)$ 的，快于上述 Tonelli-Shanks 算法（时间为 $O(\log^2 p)$ 若乘法为 $O(1)$ ）。

## Hensel lifting 求模素数幂次平方根的逆元

与牛顿迭代法一样，构造 $ f(x)=\frac{1}{x^{2}}-a$ ，一次迭代可表示为 $x_{n+1}=x_{n}-\frac{1/x_{n}^{2}-a}{-2/x_{n}^{3}}=x_{n}+x_{n}\left(\frac{1-ax_{n}^{2}} {2}\right)$ 。令 $\Phi(x)=x+x\left(\frac{1-ax^{2}}{2}\right)$ 。假设我们已经得到 $a$ 在模 **奇** 素数 $p$ 意义下的平方根的逆元 $b$ 满足 $b^{2}\equiv a^{-1}\pmod{p}$ ，认为 $(\Phi(b))^{2}\equiv a^{-1}\pmod{p^{2}}$ 。因为存在某个整数 $k$ 满足 $ab^{2}\equiv 1+kp\pmod{p^{2}}$ ，记 $b^{2}\equiv a^{-1}(1+kp)\pmod{p^{2}}$ ，有

$$
\begin{aligned}
(\Phi(b))^{2}&=\left(b+b\left(\frac{1-ab^{2}}{2}\right)\right)^{2}\\
&=\frac{9b^{2}-6ab^{4}+a^{2}b^{6}}{4}\\
&\equiv \frac{9(a^{-1}(1+kp))-6(a^{-1}(1+kp)^{2})+a^{-1}(1+kp)^{3}}{4}\pmod{p^{2}}\\
&\equiv \frac{a^{-1}}{4}(9(1+kp)-6(1+kp)^{2}+(1+kp)^{3})\pmod{p^{2}}\\
&\equiv \frac{a^{-1}}{4}(4-3k^{2}p^{2}+k^{3}p^{3})\pmod{p^{2}}\\
&\equiv a^{-1}\pmod{p^{2}}
\end{aligned}
$$

$\square$

不直接求其平方根而求其平方根的逆元是因为求平方根过程中也要维护逆元。

## 参考文献

- Jeremy Booher. [Square Roots in Finite Fields and Quadratic Nonresidues](https://www.math.arizona.edu/~jeremybooher/expos/sqr_qnr.pdf).
- A. Menezes, P. van Oorschot and S. Vanstone. [Handbook of Applied Cryptography](http://cacr.uwaterloo.ca/hac/), 1996.

