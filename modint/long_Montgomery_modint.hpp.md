---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "long Montgomery modint / \u957F\u6574\u578B Montgomery \u53D6\
      \u6A21\u7C7B"
    links:
    - https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp
  bundledCode: "#line 1 \"modint/long_Montgomery_modint.hpp\"\n\n\n\n#include <cstdint>\n\
    #include <iostream>\n#include <tuple>\n#include <type_traits>\n\n#ifdef _MSC_VER\n\
    #include <intrin.h>\n#endif\n\nnamespace lib {\n\n// reference: https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\n\
    // author: Nyaan\ntemplate <std::uint64_t mod> class LongMontgomeryModInt {\n\
    public:\n  using u32 = std::uint32_t;\n  using i64 = std::int64_t;\n  using u64\
    \ = std::uint64_t;\n  using m64 = LongMontgomeryModInt;\n\n  using value_type\
    \ = u64;\n\n  static constexpr u64 get_mod() { return mod; }\n\n  static constexpr\
    \ u64 get_primitive_root_prime() {\n    u64 tmp[64] = {};\n    int cnt = 0;\n\
    \    const u64 phi = mod - 1;\n    u64 m = phi;\n    for (u64 i = 2; i * i <=\
    \ m; ++i) {\n      if (m % i == 0) {\n        tmp[cnt++] = i;\n        do {\n\
    \          m /= i;\n        } while (m % i == 0);\n      }\n    }\n    if (m !=\
    \ 1) tmp[cnt++] = m;\n    for (m64 res = 2;; res += 1) {\n      bool f = true;\n\
    \      for (int i = 0; i < cnt && f; ++i) f &= res.pow(phi / tmp[i]) != 1;\n \
    \     if (f) return u32(res);\n    }\n  }\n\n  constexpr LongMontgomeryModInt()\
    \ = default;\n  ~LongMontgomeryModInt() = default;\n\n  template <typename T,\
    \ std::enable_if_t<std::is_integral_v<T>, int> = 0>\n  constexpr LongMontgomeryModInt(T\
    \ v) : v_(reduce(mul(norm(v % i64(mod)), r2))) {}\n\n  constexpr LongMontgomeryModInt(const\
    \ m64 &) = default;\n\n  constexpr u64 get() const { return reduce({0, v_}); }\n\
    \n  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\n\
    \  explicit constexpr operator T() const {\n    return T(get());\n  }\n\n  constexpr\
    \ m64 operator-() const {\n    m64 res;\n    res.v_ = (mod & -(v_ != 0)) - v_;\n\
    \    return res;\n  }\n\n  constexpr m64 inv() const {\n    i64 x1 = 1, x3 = 0,\
    \ a = get(), b = mod;\n    while (b != 0) {\n      i64 q = a / b, x1_old = x1,\
    \ a_old = a;\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\n\
    \    }\n    return m64(x1);\n  }\n\n  constexpr m64 &operator+=(const m64 &rhs)\
    \ {\n    v_ += rhs.v_ - mod;\n    v_ += mod & -(v_ >> 63);\n    return *this;\n\
    \  }\n  constexpr m64 &operator-=(const m64 &rhs) {\n    v_ -= rhs.v_;\n    v_\
    \ += mod & -(v_ >> 63);\n    return *this;\n  }\n  constexpr m64 &operator*=(const\
    \ m64 &rhs) {\n    v_ = reduce(mul(v_, rhs.v_));\n    return *this;\n  }\n  constexpr\
    \ m64 &operator/=(const m64 &rhs) { return operator*=(rhs.inv()); }\n  friend\
    \ constexpr m64 operator+(const m64 &lhs, const m64 &rhs) { return m64(lhs) +=\
    \ rhs; }\n  friend constexpr m64 operator-(const m64 &lhs, const m64 &rhs) { return\
    \ m64(lhs) -= rhs; }\n  friend constexpr m64 operator*(const m64 &lhs, const m64\
    \ &rhs) { return m64(lhs) *= rhs; }\n  friend constexpr m64 operator/(const m64\
    \ &lhs, const m64 &rhs) { return m64(lhs) /= rhs; }\n  friend constexpr bool operator==(const\
    \ m64 &lhs, const m64 &rhs) { return lhs.v_ == rhs.v_; }\n  friend constexpr bool\
    \ operator!=(const m64 &lhs, const m64 &rhs) { return lhs.v_ != rhs.v_; }\n\n\
    \  friend std::istream &operator>>(std::istream &is, m64 &rhs) {\n    i64 x;\n\
    \    is >> x;\n    rhs = m64(x);\n    return is;\n  }\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const m64 &rhs) { return os << rhs.get(); }\n\n  constexpr m64 pow(u64\
    \ y) const {\n    m64 res(1), x(*this);\n    for (; y != 0; y >>= 1, x *= x)\n\
    \      if (y & 1) res *= x;\n    return res;\n  }\n\nprivate:\n  //---\n  static\
    \ constexpr std::pair<u64, u64> mul(u64 x, u64 y) {\n#ifdef _MSC_VER\n    u64\
    \ h, l = _umul128(x, y, &h);\n    return {h, l};\n#elif defined(__GNUC__)\n  \
    \  unsigned __int128 res = (unsigned __int128)x * y;\n    return {u64(res >> 64),\
    \ u64(res)};\n#else\n    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y),\
    \ ac = a * c, bd = b * d, ad = a * d,\n        bc = b * c;\n    // low = bd +\
    \ (ad + bc << 32); \u4F46\u662F\u6CA1\u5FC5\u8981\n    return {ac + (ad >> 32)\
    \ + (bc >> 32) +\n                (((ad & -UINT32_C(1)) + (bc & -UINT32_C(1))\
    \ + (bd >> 32)) >> 32),\n            x * y};\n#endif\n  }\n\n  static constexpr\
    \ u64 mulh(u64 x, u64 y) {\n#ifdef _MSC_VER\n    return __umulh(x, y);\n#elif\
    \ defined(__GNUC__)\n    return (unsigned __int128)x * y >> 64;\n#else\n    u64\
    \ a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ac = a * c, bd = b * d, ad\
    \ = a * d,\n        bc = b * c;\n    return ac + (ad >> 32) + (bc >> 32) +\n \
    \          (((ad & -UINT32_C(1)) + (bc & -UINT32_C(1)) + (bd >> 32)) >> 32);\n\
    #endif\n  }\n  //---\n\n  static constexpr u64 get_r() {\n    u64 two = 2, iv\
    \ = mod * (two - mod * mod);\n    iv *= two - mod * iv;\n    iv *= two - mod *\
    \ iv;\n    iv *= two - mod * iv;\n    return iv * (two - mod * iv);\n  }\n\n \
    \ static constexpr u64 get_r2() {\n    u64 iv = -u64(mod) % mod;\n    for (int\
    \ i = 0; i != 64; ++i)\n      if ((iv <<= 1) >= mod) iv -= mod;\n    return iv;\n\
    \  }\n\n  static constexpr u64 reduce(const std::pair<u64, u64> &x) {\n    u64\
    \ res = x.first - mulh(x.second * r, mod);\n    return res + (mod & -(res >> 63));\n\
    \  }\n\n  static constexpr u64 norm(i64 x) { return x + (mod & -(x < 0)); }\n\n\
    \  u64 v_;\n\n  static constexpr u64 r = get_r();\n  static constexpr u64 r2 =\
    \ get_r2();\n\n  static_assert((mod & 1) == 1, \"mod % 2 == 0\\n\");\n  static_assert(r\
    \ * mod == 1, \"???\\n\");\n  static_assert((mod & (1ULL << 63)) == 0, \"mod >=\
    \ (1ULL << 63)\\n\");\n  static_assert(mod != 1, \"mod == 1\\n\");\n};\n\ntemplate\
    \ <std::uint64_t mod> using LongMontModInt = LongMontgomeryModInt<mod>;\n\n} //\
    \ namespace lib\n\n/**\n * @brief long Montgomery modint / \u957F\u6574\u578B\
    \ Montgomery \u53D6\u6A21\u7C7B\n *\n */\n\n\n"
  code: "#ifndef LONG_MONTGOMERY_MODINT_HEADER_HPP\n#define LONG_MONTGOMERY_MODINT_HEADER_HPP\n\
    \n#include <cstdint>\n#include <iostream>\n#include <tuple>\n#include <type_traits>\n\
    \n#ifdef _MSC_VER\n#include <intrin.h>\n#endif\n\nnamespace lib {\n\n// reference:\
    \ https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\n// author:\
    \ Nyaan\ntemplate <std::uint64_t mod> class LongMontgomeryModInt {\npublic:\n\
    \  using u32 = std::uint32_t;\n  using i64 = std::int64_t;\n  using u64 = std::uint64_t;\n\
    \  using m64 = LongMontgomeryModInt;\n\n  using value_type = u64;\n\n  static\
    \ constexpr u64 get_mod() { return mod; }\n\n  static constexpr u64 get_primitive_root_prime()\
    \ {\n    u64 tmp[64] = {};\n    int cnt = 0;\n    const u64 phi = mod - 1;\n \
    \   u64 m = phi;\n    for (u64 i = 2; i * i <= m; ++i) {\n      if (m % i == 0)\
    \ {\n        tmp[cnt++] = i;\n        do {\n          m /= i;\n        } while\
    \ (m % i == 0);\n      }\n    }\n    if (m != 1) tmp[cnt++] = m;\n    for (m64\
    \ res = 2;; res += 1) {\n      bool f = true;\n      for (int i = 0; i < cnt &&\
    \ f; ++i) f &= res.pow(phi / tmp[i]) != 1;\n      if (f) return u32(res);\n  \
    \  }\n  }\n\n  constexpr LongMontgomeryModInt() = default;\n  ~LongMontgomeryModInt()\
    \ = default;\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  constexpr LongMontgomeryModInt(T v) : v_(reduce(mul(norm(v % i64(mod)),\
    \ r2))) {}\n\n  constexpr LongMontgomeryModInt(const m64 &) = default;\n\n  constexpr\
    \ u64 get() const { return reduce({0, v_}); }\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  explicit constexpr operator T() const {\n    return T(get());\n\
    \  }\n\n  constexpr m64 operator-() const {\n    m64 res;\n    res.v_ = (mod &\
    \ -(v_ != 0)) - v_;\n    return res;\n  }\n\n  constexpr m64 inv() const {\n \
    \   i64 x1 = 1, x3 = 0, a = get(), b = mod;\n    while (b != 0) {\n      i64 q\
    \ = a / b, x1_old = x1, a_old = a;\n      x1 = x3, x3 = x1_old - x3 * q, a = b,\
    \ b = a_old - b * q;\n    }\n    return m64(x1);\n  }\n\n  constexpr m64 &operator+=(const\
    \ m64 &rhs) {\n    v_ += rhs.v_ - mod;\n    v_ += mod & -(v_ >> 63);\n    return\
    \ *this;\n  }\n  constexpr m64 &operator-=(const m64 &rhs) {\n    v_ -= rhs.v_;\n\
    \    v_ += mod & -(v_ >> 63);\n    return *this;\n  }\n  constexpr m64 &operator*=(const\
    \ m64 &rhs) {\n    v_ = reduce(mul(v_, rhs.v_));\n    return *this;\n  }\n  constexpr\
    \ m64 &operator/=(const m64 &rhs) { return operator*=(rhs.inv()); }\n  friend\
    \ constexpr m64 operator+(const m64 &lhs, const m64 &rhs) { return m64(lhs) +=\
    \ rhs; }\n  friend constexpr m64 operator-(const m64 &lhs, const m64 &rhs) { return\
    \ m64(lhs) -= rhs; }\n  friend constexpr m64 operator*(const m64 &lhs, const m64\
    \ &rhs) { return m64(lhs) *= rhs; }\n  friend constexpr m64 operator/(const m64\
    \ &lhs, const m64 &rhs) { return m64(lhs) /= rhs; }\n  friend constexpr bool operator==(const\
    \ m64 &lhs, const m64 &rhs) { return lhs.v_ == rhs.v_; }\n  friend constexpr bool\
    \ operator!=(const m64 &lhs, const m64 &rhs) { return lhs.v_ != rhs.v_; }\n\n\
    \  friend std::istream &operator>>(std::istream &is, m64 &rhs) {\n    i64 x;\n\
    \    is >> x;\n    rhs = m64(x);\n    return is;\n  }\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const m64 &rhs) { return os << rhs.get(); }\n\n  constexpr m64 pow(u64\
    \ y) const {\n    m64 res(1), x(*this);\n    for (; y != 0; y >>= 1, x *= x)\n\
    \      if (y & 1) res *= x;\n    return res;\n  }\n\nprivate:\n  //---\n  static\
    \ constexpr std::pair<u64, u64> mul(u64 x, u64 y) {\n#ifdef _MSC_VER\n    u64\
    \ h, l = _umul128(x, y, &h);\n    return {h, l};\n#elif defined(__GNUC__)\n  \
    \  unsigned __int128 res = (unsigned __int128)x * y;\n    return {u64(res >> 64),\
    \ u64(res)};\n#else\n    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y),\
    \ ac = a * c, bd = b * d, ad = a * d,\n        bc = b * c;\n    // low = bd +\
    \ (ad + bc << 32); \u4F46\u662F\u6CA1\u5FC5\u8981\n    return {ac + (ad >> 32)\
    \ + (bc >> 32) +\n                (((ad & -UINT32_C(1)) + (bc & -UINT32_C(1))\
    \ + (bd >> 32)) >> 32),\n            x * y};\n#endif\n  }\n\n  static constexpr\
    \ u64 mulh(u64 x, u64 y) {\n#ifdef _MSC_VER\n    return __umulh(x, y);\n#elif\
    \ defined(__GNUC__)\n    return (unsigned __int128)x * y >> 64;\n#else\n    u64\
    \ a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ac = a * c, bd = b * d, ad\
    \ = a * d,\n        bc = b * c;\n    return ac + (ad >> 32) + (bc >> 32) +\n \
    \          (((ad & -UINT32_C(1)) + (bc & -UINT32_C(1)) + (bd >> 32)) >> 32);\n\
    #endif\n  }\n  //---\n\n  static constexpr u64 get_r() {\n    u64 two = 2, iv\
    \ = mod * (two - mod * mod);\n    iv *= two - mod * iv;\n    iv *= two - mod *\
    \ iv;\n    iv *= two - mod * iv;\n    return iv * (two - mod * iv);\n  }\n\n \
    \ static constexpr u64 get_r2() {\n    u64 iv = -u64(mod) % mod;\n    for (int\
    \ i = 0; i != 64; ++i)\n      if ((iv <<= 1) >= mod) iv -= mod;\n    return iv;\n\
    \  }\n\n  static constexpr u64 reduce(const std::pair<u64, u64> &x) {\n    u64\
    \ res = x.first - mulh(x.second * r, mod);\n    return res + (mod & -(res >> 63));\n\
    \  }\n\n  static constexpr u64 norm(i64 x) { return x + (mod & -(x < 0)); }\n\n\
    \  u64 v_;\n\n  static constexpr u64 r = get_r();\n  static constexpr u64 r2 =\
    \ get_r2();\n\n  static_assert((mod & 1) == 1, \"mod % 2 == 0\\n\");\n  static_assert(r\
    \ * mod == 1, \"???\\n\");\n  static_assert((mod & (1ULL << 63)) == 0, \"mod >=\
    \ (1ULL << 63)\\n\");\n  static_assert(mod != 1, \"mod == 1\\n\");\n};\n\ntemplate\
    \ <std::uint64_t mod> using LongMontModInt = LongMontgomeryModInt<mod>;\n\n} //\
    \ namespace lib\n\n/**\n * @brief long Montgomery modint / \u957F\u6574\u578B\
    \ Montgomery \u53D6\u6A21\u7C7B\n *\n */\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: modint/long_Montgomery_modint.hpp
  requiredBy: []
  timestamp: '2021-06-06 20:47:15+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: modint/long_Montgomery_modint.hpp
layout: document
title: "long Montgomery modint / \u957F\u6574\u578B Montgomery \u53D6\u6A21\u7C7B"
---

## long Montgomery modint

类 `LongMontgomeryModInt` 是一个自动取模的类型，且模数 $M\in(1,2^{63}), M\bmod 2=1$ 。重载有基本的四则运算符号和比较运算符（ `==` 和 `!=` ）。

- `LongMontgomeryModInt<M>::value_type` 为内部数据类型，即 `std::uint64_t` 。
- `LongMontgomeryModInt<M>::get_mod()` 返回模数 $M$ 且类型为 `std::uint64_t` 。
- `using LongMontModInt = LongMontgomeryModInt` 为一个辅助模板。

成员函数有

- `pow(k)` 接收非负整型。
- `inv()` 返回其逆元，注意这里并未处理不存在的情况。
- `get_primitive_root_prime()` 返回素数的最小原根，配合 NTT 算法。

代码不使用惰性的“修正”，在每次 `reduce` 函数的末尾都会调整答案在 $[0,M)$ 。

在测试时发现，使用 `if` 语句与使用更多的运算符实现差别不大，虽然在 <https://godbolt.org/> 上开启 `-O2` 选项后 `if` 语句的汇编更短。不开启优化时会产生“分支预测”，这不是我想要的。

## MSVC 和 GNUC 的分别实现

在 GNUC 中， `__int128` 和 `int` 类型是相似的，都可以用 `unsigned` 前缀来表示他的无符号版本，其余特性也是类似的。

在 MSVC 中则没有定义，我们可以在 <https://docs.microsoft.com/en-us/cpp/intrinsics/umulh?view=msvc-160> 找到 `__umulh(x, y)` 函数，返回两个 `__int64` 相乘的高位，在 <https://docs.microsoft.com/en-us/cpp/intrinsics/umul128?view=msvc-160> 找到 `_umul128(x, y, high)` 返回值为低位而 `high` 为一个指针，存入高位的结果。

我没有尝试更精细的实现。

## Montgomery reduction

依然沿用 Montgomery modint 文档中的定义，仅修改令 $RR^{-1}+NN'=1$ ，即仅 $NN'\equiv 1\pmod{R}$ 与上述不同，显然存在整数 $k,l$ 满足 $m=TN'\bmod{R}=TN'+kR$ 且 $NN'=1+lR$ ，那么

$$
\begin{aligned}
(T-mN)/R&=(T-(TN'+kR)N)/R\\
&=(T-(TNN'+kRN))/R\\
&=(T-T(1+lR)-kRN)/R\\
&=-lT-kN
\end{aligned}
$$

显然为整数，且 $-N\lt (T-mN)/R\lt N$ 。

显然 $a\bmod{b}=a-\lfloor a/b\rfloor \cdot b \implies \lfloor a/b \rfloor =(a-(a\bmod{b}))/b$ ，那么

$$
\begin{aligned}
\lfloor T/R\rfloor -\lfloor mN/R\rfloor &=(T-(T\bmod{R}))/R-(mN-(mN\bmod{R}))/R\\
&=(T-mN-((T\bmod{R})-(TNN'\bmod{R})))/R\\
&=(T-mN-((T\bmod{R})-(T\bmod{R})))/R\\
&=(T-mN)/R
\end{aligned}
$$

该方法用于一些情况更快，因为无需计算“进位”。

## 参考文献

- Peter L. Montgomery. Modular Multiplication Without Trial Division, 1985.
- Richard P. Brent and Paul Zimmermann, Modern Computer Arithmetic, Cambridge Monographs on Computational and Applied Mathematics (No. 18), Cambridge University Press, November 2010, 236 pages
- Nyaan 的[博客](https://nyaannyaan.github.io/docs/modulo/montgomery/)

