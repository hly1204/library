---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: modint/runtime_Montgomery_modint.hpp
    title: "runtime Montgomery modint / \u8FD0\u884C\u65F6 Montgomery \u53D6\u6A21\
      \u7C7B"
  - icon: ':question:'
    path: modint/runtime_long_Montgomery_modint.hpp
    title: "runtime long Montgomery modint / \u8FD0\u884C\u65F6\u957F\u6574\u578B\
      \ Montgomery \u53D6\u6A21\u7C7B"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: remote_test/yosupo/math/mod_sqrt.0.test.cpp
    title: remote_test/yosupo/math/mod_sqrt.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839"
    links: []
  bundledCode: "#line 1 \"math/modulo/sqrt_mod.hpp\"\n\n\n\n/**\n * @brief square\
    \ root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839\n *\n */\n\n#include <cassert>\n\
    #include <random>\n#include <tuple>\n#include <type_traits>\n#include <vector>\n\
    \n#line 1 \"modint/runtime_Montgomery_modint.hpp\"\n\n\n\n/**\n * @brief runtime\
    \ Montgomery modint / \u8FD0\u884C\u65F6 Montgomery \u53D6\u6A21\u7C7B\n *\n */\n\
    \n#include <cstdint>\n#include <iostream>\n#line 12 \"modint/runtime_Montgomery_modint.hpp\"\
    \n\nnamespace lib {\n\n/**\n * @brief \u8FD0\u884C\u65F6 Montgomery \u53D6\u6A21\
    \u7C7B\n * @ref https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\n\
    \ * @author Nyaan\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\n */\n\
    class RuntimeMontgomeryModInt {\npublic:\n  using i32 = std::int32_t;\n  using\
    \ u32 = std::uint32_t;\n  using u64 = std::uint64_t;\n  using m32 = RuntimeMontgomeryModInt;\n\
    \n  using value_type = u32;\n\n  static u32 get_mod() { return mod; }\n\n  static\
    \ bool set_mod(u32 m) {\n    if ((m & 1) == 0 || m == 1 || (m & (3U << 30)) !=\
    \ 0) return false;\n    mod = m, mod2 = mod << 1;\n    u32 two = 2, iv = mod *\
    \ (two - mod * mod);\n    iv *= two - mod * iv;\n    iv *= two - mod * iv;\n \
    \   r = iv * (mod * iv - two);\n    r2 = -u64(mod) % mod;\n    return true;\n\
    \  }\n\n  RuntimeMontgomeryModInt() = default;\n  ~RuntimeMontgomeryModInt() =\
    \ default;\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  RuntimeMontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) + i32(mod))\
    \ * r2)) {}\n\n  RuntimeMontgomeryModInt(const m32 &) = default;\n\n  u32 get()\
    \ const { return norm(reduce(v_)); }\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  explicit constexpr operator T() const {\n    return T(get());\n\
    \  }\n\n  m32 operator-() const {\n    m32 res;\n    res.v_ = (mod2 & -(v_ !=\
    \ 0)) - v_;\n    return res;\n  }\n\n  m32 inv() const {\n    i32 x1 = 1, x3 =\
    \ 0, a = get(), b = mod;\n    while (b != 0) {\n      i32 q = a / b, x1_old =\
    \ x1, a_old = a;\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b *\
    \ q;\n    }\n    return m32(x1);\n  }\n\n  m32 &operator+=(const m32 &rhs) {\n\
    \    v_ += rhs.v_ - mod2;\n    v_ += mod2 & -(v_ >> 31);\n    return *this;\n\
    \  }\n  m32 &operator-=(const m32 &rhs) {\n    v_ -= rhs.v_;\n    v_ += mod2 &\
    \ -(v_ >> 31);\n    return *this;\n  }\n  m32 &operator*=(const m32 &rhs) {\n\
    \    v_ = reduce(u64(v_) * rhs.v_);\n    return *this;\n  }\n  m32 &operator/=(const\
    \ m32 &rhs) { return operator*=(rhs.inv()); }\n  friend m32 operator+(const m32\
    \ &lhs, const m32 &rhs) { return m32(lhs) += rhs; }\n  friend m32 operator-(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) -= rhs; }\n  friend m32 operator*(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }\n  friend m32 operator/(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) /= rhs; }\n  friend bool operator==(const\
    \ m32 &lhs, const m32 &rhs) { return norm(lhs.v_) == norm(rhs.v_); }\n  friend\
    \ bool operator!=(const m32 &lhs, const m32 &rhs) { return norm(lhs.v_) != norm(rhs.v_);\
    \ }\n\n  friend std::istream &operator>>(std::istream &is, m32 &rhs) {\n    i32\
    \ x;\n    is >> x;\n    rhs = m32(x);\n    return is;\n  }\n  friend std::ostream\
    \ &operator<<(std::ostream &os, const m32 &rhs) { return os << rhs.get(); }\n\n\
    \  m32 pow(u64 y) const {\n    m32 res(1), x(*this);\n    for (; y != 0; y >>=\
    \ 1, x *= x)\n      if (y & 1) res *= x;\n    return res;\n  }\n\nprivate:\n \
    \ static u32 reduce(u64 x) { return (x + u64(u32(x) * r) * mod) >> 32; }\n  static\
    \ u32 norm(u32 x) { return x - (mod & -((mod - 1 - x) >> 31)); }\n\n  u32 v_;\n\
    \n  static u32 r, r2, mod, mod2;\n};\n\nRuntimeMontgomeryModInt::u32 RuntimeMontgomeryModInt::r;\n\
    RuntimeMontgomeryModInt::u32 RuntimeMontgomeryModInt::r2;\nRuntimeMontgomeryModInt::u32\
    \ RuntimeMontgomeryModInt::mod;\nRuntimeMontgomeryModInt::u32 RuntimeMontgomeryModInt::mod2;\n\
    \n// \u522B\u540D\nusing RuntimeMontModInt = RuntimeMontgomeryModInt;\n\n} //\
    \ namespace lib\n\n\n#line 1 \"modint/runtime_long_Montgomery_modint.hpp\"\n\n\
    \n\n/**\n * @brief runtime long Montgomery modint / \u8FD0\u884C\u65F6\u957F\u6574\
    \u578B Montgomery \u53D6\u6A21\u7C7B\n *\n */\n\n#line 14 \"modint/runtime_long_Montgomery_modint.hpp\"\
    \n\n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace lib {\n\n/**\n *\
    \ @brief \u8FD0\u884C\u65F6\u957F\u6574\u578B Montgomery \u53D6\u6A21\u7C7B\n\
    \ * @ref https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\n *\
    \ @author Nyaan\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\n */\n\
    class RuntimeLongMontgomeryModInt {\npublic:\n  using u32 = std::uint32_t;\n \
    \ using i64 = std::int64_t;\n  using u64 = std::uint64_t;\n  using m64 = RuntimeLongMontgomeryModInt;\n\
    \n  using value_type = u64;\n\n  static u64 get_mod() { return mod; }\n\n  static\
    \ bool set_mod(u64 m) {\n    if ((m & 1) == 0 || m == 1 || (m & (1ULL << 63))\
    \ != 0) return false;\n    mod = m;\n    r = get_r();\n    r2 = get_r2();\n  \
    \  return true;\n  }\n\n  RuntimeLongMontgomeryModInt() = default;\n  ~RuntimeLongMontgomeryModInt()\
    \ = default;\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  RuntimeLongMontgomeryModInt(T v) : v_(reduce(mul(norm(v % i64(mod)),\
    \ r2))) {}\n\n  RuntimeLongMontgomeryModInt(const m64 &) = default;\n\n  u64 get()\
    \ const { return reduce({0, v_}); }\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  explicit operator T() const {\n    return T(get());\n  }\n\n  m64\
    \ operator-() const {\n    m64 res;\n    res.v_ = (mod & -(v_ != 0)) - v_;\n \
    \   return res;\n  }\n\n  m64 inv() const {\n    i64 x1 = 1, x3 = 0, a = get(),\
    \ b = mod;\n    while (b != 0) {\n      i64 q = a / b, x1_old = x1, a_old = a;\n\
    \      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\n    }\n    return\
    \ m64(x1);\n  }\n\n  m64 &operator+=(const m64 &rhs) {\n    v_ += rhs.v_ - mod;\n\
    \    v_ += mod & -(v_ >> 63);\n    return *this;\n  }\n  m64 &operator-=(const\
    \ m64 &rhs) {\n    v_ -= rhs.v_;\n    v_ += mod & -(v_ >> 63);\n    return *this;\n\
    \  }\n  m64 &operator*=(const m64 &rhs) {\n    v_ = reduce(mul(v_, rhs.v_));\n\
    \    return *this;\n  }\n  m64 &operator/=(const m64 &rhs) { return operator*=(rhs.inv());\
    \ }\n  friend m64 operator+(const m64 &lhs, const m64 &rhs) { return m64(lhs)\
    \ += rhs; }\n  friend m64 operator-(const m64 &lhs, const m64 &rhs) { return m64(lhs)\
    \ -= rhs; }\n  friend m64 operator*(const m64 &lhs, const m64 &rhs) { return m64(lhs)\
    \ *= rhs; }\n  friend m64 operator/(const m64 &lhs, const m64 &rhs) { return m64(lhs)\
    \ /= rhs; }\n  friend bool operator==(const m64 &lhs, const m64 &rhs) { return\
    \ lhs.v_ == rhs.v_; }\n  friend bool operator!=(const m64 &lhs, const m64 &rhs)\
    \ { return lhs.v_ != rhs.v_; }\n\n  friend std::istream &operator>>(std::istream\
    \ &is, m64 &rhs) {\n    i64 x;\n    is >> x;\n    rhs = m64(x);\n    return is;\n\
    \  }\n  friend std::ostream &operator<<(std::ostream &os, const m64 &rhs) { return\
    \ os << rhs.get(); }\n\n  m64 pow(u64 y) const {\n    m64 res(1), x(*this);\n\
    \    for (; y != 0; y >>= 1, x *= x)\n      if (y & 1) res *= x;\n    return res;\n\
    \  }\n\nprivate:\n  static std::pair<u64, u64> mul(u64 x, u64 y) {\n#ifdef __GNUC__\n\
    \    unsigned __int128 res = (unsigned __int128)x * y;\n    return {u64(res >>\
    \ 64), u64(res)};\n#elif defined(_MSC_VER)\n    u64 h, l = _umul128(x, y, &h);\n\
    \    return {h, l};\n#else\n    u64 a = x >> 32, b = u32(x), c = y >> 32, d =\
    \ u32(y), ad = a * d, bc = b * c;\n    return {a * c + (ad >> 32) + (bc >> 32)\
    \ +\n                (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32))\
    \ >> 32),\n            x * y};\n#endif\n  }\n\n  static u64 mulh(u64 x, u64 y)\
    \ {\n#ifdef __GNUC__\n    return u64((unsigned __int128)x * y >> 64);\n#elif defined(_MSC_VER)\n\
    \    return __umulh(x, y);\n#else\n    u64 a = x >> 32, b = u32(x), c = y >> 32,\
    \ d = u32(y), ad = a * d, bc = b * c;\n    return a * c + (ad >> 32) + (bc >>\
    \ 32) +\n           (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32))\
    \ >> 32);\n#endif\n  }\n\n  static u64 get_r() {\n    u64 two = 2, iv = mod *\
    \ (two - mod * mod);\n    iv *= two - mod * iv;\n    iv *= two - mod * iv;\n \
    \   iv *= two - mod * iv;\n    return iv * (two - mod * iv);\n  }\n\n  static\
    \ u64 get_r2() {\n    u64 iv = -u64(mod) % mod;\n    for (int i = 0; i != 64;\
    \ ++i)\n      if ((iv <<= 1) >= mod) iv -= mod;\n    return iv;\n  }\n\n  static\
    \ u64 reduce(const std::pair<u64, u64> &x) {\n    u64 res = x.first - mulh(x.second\
    \ * r, mod);\n    return res + (mod & -(res >> 63));\n  }\n\n  static u64 norm(i64\
    \ x) { return x + (mod & -(x < 0)); }\n\n  u64 v_;\n\n  static u64 mod, r, r2;\n\
    };\n\nRuntimeLongMontgomeryModInt::u64 RuntimeLongMontgomeryModInt::mod;\nRuntimeLongMontgomeryModInt::u64\
    \ RuntimeLongMontgomeryModInt::r;\nRuntimeLongMontgomeryModInt::u64 RuntimeLongMontgomeryModInt::r2;\n\
    \nusing RuntimeLongMontModInt = RuntimeLongMontgomeryModInt;\n\n} // namespace\
    \ lib\n\n\n#line 17 \"math/modulo/sqrt_mod.hpp\"\n\nnamespace lib {\n\nnamespace\
    \ internal {\n\ntemplate <typename mod_t> std::vector<mod_t> sqrt_mod_prime(const\
    \ mod_t x) {\n  const auto p = mod_t::get_mod();\n  const mod_t ONE(1), MINUS_ONE(-ONE),\
    \ ZERO(0);\n  if (x == ZERO) return {ZERO};\n  if (x.pow(p >> 1) == MINUS_ONE)\
    \ return {};\n  if ((p & 3) == 3) {\n    mod_t res = x.pow(p + 1 >> 2);\n    return\
    \ {res, -res};\n  }\n\n  static std::random_device rd;\n  static std::mt19937\
    \ gen(rd());\n  static std::uniform_int_distribution<std::uint32_t> dis(2, p -\
    \ 1);\n\n  const mod_t four(mod_t(4) * x);\n  mod_t t, w2;\n  do {\n    t = mod_t(dis(gen)),\
    \ w2 = t * t - four;\n    if (w2 == ZERO) { // \u8DB3\u591F\u5E78\u8FD0\u65F6\n\
    \      t /= 2;\n      return {t, -t};\n    }\n  } while (w2.pow(p >> 1) != MINUS_ONE);\n\
    \n  mod_t a(ONE), b(ZERO), c(ZERO), d(ONE);\n\n  for (auto e = (p + 1) >> 1; e\
    \ != 0; e >>= 1) {\n    if (e & 1) {\n      mod_t bd = b * d;\n      std::tie(a,\
    \ b) = std::make_pair(a * c - bd * x, a * d + b * c + bd * t);\n    }\n    mod_t\
    \ dd = d * d, cd = c * d;\n    std::tie(c, d) = std::make_pair(c * c - dd * x,\
    \ cd + cd + dd * t);\n  }\n\n  return {a, -a};\n}\n\n} // namespace internal\n\
    \n/**\n * @brief \u6A21\u5E73\u65B9\u6839\n * @param x [0, p-1] \u4E2D\u7684\u4E00\
    \u4E2A\u503C\n * @param p \u7D20\u6570\n * @return std::vector<T>\n */\ntemplate\
    \ <typename T>\nstd::enable_if_t<std::is_integral_v<T>, std::vector<T>> sqrt_mod_prime(T\
    \ x, T p) {\n  if (p == 2) return {x};\n  if (p < (3U << 30)) {\n    RuntimeMontgomeryModInt::set_mod(p);\n\
    \    auto res = internal::sqrt_mod_prime(RuntimeMontgomeryModInt(x));\n    return\
    \ std::vector<T>(res.begin(), res.end());\n  }\n  RuntimeLongMontgomeryModInt::set_mod(p);\n\
    \  auto res = internal::sqrt_mod_prime(RuntimeLongMontgomeryModInt(x));\n  return\
    \ std::vector<T>(res.begin(), res.end());\n}\n\n} // namespace lib\n\n\n"
  code: "#ifndef SQRT_MOD_HEADER_HPP\n#define SQRT_MOD_HEADER_HPP\n\n/**\n * @brief\
    \ square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839\n *\n */\n\n#include\
    \ <cassert>\n#include <random>\n#include <tuple>\n#include <type_traits>\n#include\
    \ <vector>\n\n#include \"modint/runtime_Montgomery_modint.hpp\"\n#include \"modint/runtime_long_Montgomery_modint.hpp\"\
    \n\nnamespace lib {\n\nnamespace internal {\n\ntemplate <typename mod_t> std::vector<mod_t>\
    \ sqrt_mod_prime(const mod_t x) {\n  const auto p = mod_t::get_mod();\n  const\
    \ mod_t ONE(1), MINUS_ONE(-ONE), ZERO(0);\n  if (x == ZERO) return {ZERO};\n \
    \ if (x.pow(p >> 1) == MINUS_ONE) return {};\n  if ((p & 3) == 3) {\n    mod_t\
    \ res = x.pow(p + 1 >> 2);\n    return {res, -res};\n  }\n\n  static std::random_device\
    \ rd;\n  static std::mt19937 gen(rd());\n  static std::uniform_int_distribution<std::uint32_t>\
    \ dis(2, p - 1);\n\n  const mod_t four(mod_t(4) * x);\n  mod_t t, w2;\n  do {\n\
    \    t = mod_t(dis(gen)), w2 = t * t - four;\n    if (w2 == ZERO) { // \u8DB3\u591F\
    \u5E78\u8FD0\u65F6\n      t /= 2;\n      return {t, -t};\n    }\n  } while (w2.pow(p\
    \ >> 1) != MINUS_ONE);\n\n  mod_t a(ONE), b(ZERO), c(ZERO), d(ONE);\n\n  for (auto\
    \ e = (p + 1) >> 1; e != 0; e >>= 1) {\n    if (e & 1) {\n      mod_t bd = b *\
    \ d;\n      std::tie(a, b) = std::make_pair(a * c - bd * x, a * d + b * c + bd\
    \ * t);\n    }\n    mod_t dd = d * d, cd = c * d;\n    std::tie(c, d) = std::make_pair(c\
    \ * c - dd * x, cd + cd + dd * t);\n  }\n\n  return {a, -a};\n}\n\n} // namespace\
    \ internal\n\n/**\n * @brief \u6A21\u5E73\u65B9\u6839\n * @param x [0, p-1] \u4E2D\
    \u7684\u4E00\u4E2A\u503C\n * @param p \u7D20\u6570\n * @return std::vector<T>\n\
    \ */\ntemplate <typename T>\nstd::enable_if_t<std::is_integral_v<T>, std::vector<T>>\
    \ sqrt_mod_prime(T x, T p) {\n  if (p == 2) return {x};\n  if (p < (3U << 30))\
    \ {\n    RuntimeMontgomeryModInt::set_mod(p);\n    auto res = internal::sqrt_mod_prime(RuntimeMontgomeryModInt(x));\n\
    \    return std::vector<T>(res.begin(), res.end());\n  }\n  RuntimeLongMontgomeryModInt::set_mod(p);\n\
    \  auto res = internal::sqrt_mod_prime(RuntimeLongMontgomeryModInt(x));\n  return\
    \ std::vector<T>(res.begin(), res.end());\n}\n\n} // namespace lib\n\n#endif"
  dependsOn:
  - modint/runtime_Montgomery_modint.hpp
  - modint/runtime_long_Montgomery_modint.hpp
  isVerificationFile: false
  path: math/modulo/sqrt_mod.hpp
  requiredBy: []
  timestamp: '2021-06-21 03:16:05+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - remote_test/yosupo/math/mod_sqrt.0.test.cpp
documentation_of: math/modulo/sqrt_mod.hpp
layout: document
title: "square root mod / \u6A21\u610F\u4E49\u4E0B\u5E73\u65B9\u6839"
---

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

