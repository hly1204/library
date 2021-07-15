---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    _deprecated_at_docs: docs/modint/long_Montgomery_modint.md
    document_title: "long Montgomery modint / \u957F\u6574\u578B Montgomery \u53D6\
      \u6A21\u7C7B"
    links:
    - https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp
  bundledCode: "#line 1 \"modint/long_Montgomery_modint.hpp\"\n\n\n\r\n/**\r\n * @brief\
    \ long Montgomery modint / \u957F\u6574\u578B Montgomery \u53D6\u6A21\u7C7B\r\n\
    \ * @docs docs/modint/long_Montgomery_modint.md\r\n */\r\n\r\n#include <cstdint>\r\
    \n#include <iostream>\r\n#include <tuple>\r\n#include <type_traits>\r\n\r\n#ifdef\
    \ _MSC_VER\r\n  #include <intrin.h>\r\n#endif\r\n\r\nnamespace lib {\r\n\r\n/**\r\
    \n * @brief \u957F\u6574\u578B Montgomery \u53D6\u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
    \n * @author Nyaan\r\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\r\n\
    \ */\r\ntemplate <std::uint64_t mod>\r\nclass LongMontgomeryModInt {\r\npublic:\r\
    \n  using u32 = std::uint32_t;\r\n  using i64 = std::int64_t;\r\n  using u64 =\
    \ std::uint64_t;\r\n  using m64 = LongMontgomeryModInt;\r\n\r\n  using value_type\
    \ = u64;\r\n\r\n  static constexpr u64 get_mod() { return mod; }\r\n\r\n  static\
    \ constexpr u64 get_primitive_root_prime() {\r\n    u64 tmp[64]   = {};\r\n  \
    \  int cnt       = 0;\r\n    const u64 phi = mod - 1;\r\n    u64 m         = phi;\r\
    \n    for (u64 i = 2; i * i <= m; ++i) {\r\n      if (m % i == 0) {\r\n      \
    \  tmp[cnt++] = i;\r\n        do { m /= i; } while (m % i == 0);\r\n      }\r\n\
    \    }\r\n    if (m != 1) tmp[cnt++] = m;\r\n    for (m64 res = 2;; res += 1)\
    \ {\r\n      bool f = true;\r\n      for (int i = 0; i < cnt && f; ++i) f &= res.pow(phi\
    \ / tmp[i]) != 1;\r\n      if (f) return u32(res);\r\n    }\r\n  }\r\n\r\n  constexpr\
    \ LongMontgomeryModInt() = default;\r\n  ~LongMontgomeryModInt()          = default;\r\
    \n\r\n  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\
    \n  constexpr LongMontgomeryModInt(T v) : v_(reduce(mul(norm(v % i64(mod)), r2)))\
    \ {}\r\n\r\n  constexpr LongMontgomeryModInt(const m64 &) = default;\r\n\r\n \
    \ constexpr u64 get() const { return reduce({0, v_}); }\r\n\r\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  explicit constexpr\
    \ operator T() const {\r\n    return T(get());\r\n  }\r\n\r\n  constexpr m64 operator-()\
    \ const {\r\n    m64 res;\r\n    res.v_ = (mod & -(v_ != 0)) - v_;\r\n    return\
    \ res;\r\n  }\r\n\r\n  constexpr m64 inv() const {\r\n    i64 x1 = 1, x3 = 0,\
    \ a = get(), b = mod;\r\n    while (b != 0) {\r\n      i64 q = a / b, x1_old =\
    \ x1, a_old = a;\r\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b\
    \ * q;\r\n    }\r\n    return m64(x1);\r\n  }\r\n\r\n  constexpr m64 &operator=(const\
    \ m64 &) = default;\r\n\r\n  constexpr m64 &operator+=(const m64 &rhs) {\r\n \
    \   v_ += rhs.v_ - mod;\r\n    v_ += mod & -(v_ >> 63);\r\n    return *this;\r\
    \n  }\r\n  constexpr m64 &operator-=(const m64 &rhs) {\r\n    v_ -= rhs.v_;\r\n\
    \    v_ += mod & -(v_ >> 63);\r\n    return *this;\r\n  }\r\n  constexpr m64 &operator*=(const\
    \ m64 &rhs) {\r\n    v_ = reduce(mul(v_, rhs.v_));\r\n    return *this;\r\n  }\r\
    \n  constexpr m64 &operator/=(const m64 &rhs) { return operator*=(rhs.inv());\
    \ }\r\n  friend constexpr m64 operator+(const m64 &lhs, const m64 &rhs) { return\
    \ m64(lhs) += rhs; }\r\n  friend constexpr m64 operator-(const m64 &lhs, const\
    \ m64 &rhs) { return m64(lhs) -= rhs; }\r\n  friend constexpr m64 operator*(const\
    \ m64 &lhs, const m64 &rhs) { return m64(lhs) *= rhs; }\r\n  friend constexpr\
    \ m64 operator/(const m64 &lhs, const m64 &rhs) { return m64(lhs) /= rhs; }\r\n\
    \  friend constexpr bool operator==(const m64 &lhs, const m64 &rhs) { return lhs.v_\
    \ == rhs.v_; }\r\n  friend constexpr bool operator!=(const m64 &lhs, const m64\
    \ &rhs) { return lhs.v_ != rhs.v_; }\r\n\r\n  friend std::istream &operator>>(std::istream\
    \ &is, m64 &rhs) {\r\n    i64 x;\r\n    is >> x;\r\n    rhs = m64(x);\r\n    return\
    \ is;\r\n  }\r\n  friend std::ostream &operator<<(std::ostream &os, const m64\
    \ &rhs) { return os << rhs.get(); }\r\n\r\n  constexpr m64 pow(u64 y) const {\r\
    \n    m64 res(1), x(*this);\r\n    for (; y != 0; y >>= 1, x *= x)\r\n      if\
    \ (y & 1) res *= x;\r\n    return res;\r\n  }\r\n\r\nprivate:\r\n  static constexpr\
    \ std::pair<u64, u64> mul(u64 x, u64 y) {\r\n#ifdef __GNUC__\r\n    unsigned __int128\
    \ res = (unsigned __int128)x * y;\r\n    return {u64(res >> 64), u64(res)};\r\n\
    #elif defined(_MSC_VER)\r\n    u64 h, l = _umul128(x, y, &h);\r\n    return {h,\
    \ l};\r\n#else\r\n    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad\
    \ = a * d, bc = b * c;\r\n    return {a * c + (ad >> 32) + (bc >> 32) +\r\n  \
    \              (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32)) >>\
    \ 32),\r\n            x * y};\r\n#endif\r\n  }\r\n\r\n  static constexpr u64 mulh(u64\
    \ x, u64 y) {\r\n#ifdef __GNUC__\r\n    return u64((unsigned __int128)x * y >>\
    \ 64);\r\n#elif defined(_MSC_VER)\r\n    return __umulh(x, y);\r\n#else\r\n  \
    \  u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad = a * d, bc = b *\
    \ c;\r\n    return a * c + (ad >> 32) + (bc >> 32) +\r\n           (((ad & ~UINT32_C(0))\
    \ + (bc & ~UINT32_C(0)) + (b * d >> 32)) >> 32);\r\n#endif\r\n  }\r\n\r\n  static\
    \ constexpr u64 get_r() {\r\n    u64 two = 2, iv = mod * (two - mod * mod);\r\n\
    \    iv *= two - mod * iv;\r\n    iv *= two - mod * iv;\r\n    iv *= two - mod\
    \ * iv;\r\n    return iv * (two - mod * iv);\r\n  }\r\n\r\n  static constexpr\
    \ u64 get_r2() {\r\n    u64 iv = -u64(mod) % mod;\r\n    for (int i = 0; i !=\
    \ 64; ++i)\r\n      if ((iv <<= 1) >= mod) iv -= mod;\r\n    return iv;\r\n  }\r\
    \n\r\n  static constexpr u64 reduce(const std::pair<u64, u64> &x) {\r\n    u64\
    \ res = x.first - mulh(x.second * r, mod);\r\n    return res + (mod & -(res >>\
    \ 63));\r\n  }\r\n\r\n  static constexpr u64 norm(i64 x) { return x + (mod & -(x\
    \ < 0)); }\r\n\r\n  u64 v_;\r\n\r\n  static constexpr u64 r  = get_r();\r\n  static\
    \ constexpr u64 r2 = get_r2();\r\n\r\n  static_assert((mod & 1) == 1, \"mod %\
    \ 2 == 0\\n\");\r\n  static_assert(r * mod == 1, \"???\\n\");\r\n  static_assert((mod\
    \ & (1ULL << 63)) == 0, \"mod >= (1ULL << 63)\\n\");\r\n  static_assert(mod !=\
    \ 1, \"mod == 1\\n\");\r\n};\r\n\r\ntemplate <std::uint64_t mod>\r\nusing LongMontModInt\
    \ = LongMontgomeryModInt<mod>;\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef LONG_MONTGOMERY_MODINT_HEADER_HPP\r\n#define LONG_MONTGOMERY_MODINT_HEADER_HPP\r\
    \n\r\n/**\r\n * @brief long Montgomery modint / \u957F\u6574\u578B Montgomery\
    \ \u53D6\u6A21\u7C7B\r\n * @docs docs/modint/long_Montgomery_modint.md\r\n */\r\
    \n\r\n#include <cstdint>\r\n#include <iostream>\r\n#include <tuple>\r\n#include\
    \ <type_traits>\r\n\r\n#ifdef _MSC_VER\r\n  #include <intrin.h>\r\n#endif\r\n\r\
    \nnamespace lib {\r\n\r\n/**\r\n * @brief \u957F\u6574\u578B Montgomery \u53D6\
    \u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
    \n * @author Nyaan\r\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\r\n\
    \ */\r\ntemplate <std::uint64_t mod>\r\nclass LongMontgomeryModInt {\r\npublic:\r\
    \n  using u32 = std::uint32_t;\r\n  using i64 = std::int64_t;\r\n  using u64 =\
    \ std::uint64_t;\r\n  using m64 = LongMontgomeryModInt;\r\n\r\n  using value_type\
    \ = u64;\r\n\r\n  static constexpr u64 get_mod() { return mod; }\r\n\r\n  static\
    \ constexpr u64 get_primitive_root_prime() {\r\n    u64 tmp[64]   = {};\r\n  \
    \  int cnt       = 0;\r\n    const u64 phi = mod - 1;\r\n    u64 m         = phi;\r\
    \n    for (u64 i = 2; i * i <= m; ++i) {\r\n      if (m % i == 0) {\r\n      \
    \  tmp[cnt++] = i;\r\n        do { m /= i; } while (m % i == 0);\r\n      }\r\n\
    \    }\r\n    if (m != 1) tmp[cnt++] = m;\r\n    for (m64 res = 2;; res += 1)\
    \ {\r\n      bool f = true;\r\n      for (int i = 0; i < cnt && f; ++i) f &= res.pow(phi\
    \ / tmp[i]) != 1;\r\n      if (f) return u32(res);\r\n    }\r\n  }\r\n\r\n  constexpr\
    \ LongMontgomeryModInt() = default;\r\n  ~LongMontgomeryModInt()          = default;\r\
    \n\r\n  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\
    \n  constexpr LongMontgomeryModInt(T v) : v_(reduce(mul(norm(v % i64(mod)), r2)))\
    \ {}\r\n\r\n  constexpr LongMontgomeryModInt(const m64 &) = default;\r\n\r\n \
    \ constexpr u64 get() const { return reduce({0, v_}); }\r\n\r\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  explicit constexpr\
    \ operator T() const {\r\n    return T(get());\r\n  }\r\n\r\n  constexpr m64 operator-()\
    \ const {\r\n    m64 res;\r\n    res.v_ = (mod & -(v_ != 0)) - v_;\r\n    return\
    \ res;\r\n  }\r\n\r\n  constexpr m64 inv() const {\r\n    i64 x1 = 1, x3 = 0,\
    \ a = get(), b = mod;\r\n    while (b != 0) {\r\n      i64 q = a / b, x1_old =\
    \ x1, a_old = a;\r\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b\
    \ * q;\r\n    }\r\n    return m64(x1);\r\n  }\r\n\r\n  constexpr m64 &operator=(const\
    \ m64 &) = default;\r\n\r\n  constexpr m64 &operator+=(const m64 &rhs) {\r\n \
    \   v_ += rhs.v_ - mod;\r\n    v_ += mod & -(v_ >> 63);\r\n    return *this;\r\
    \n  }\r\n  constexpr m64 &operator-=(const m64 &rhs) {\r\n    v_ -= rhs.v_;\r\n\
    \    v_ += mod & -(v_ >> 63);\r\n    return *this;\r\n  }\r\n  constexpr m64 &operator*=(const\
    \ m64 &rhs) {\r\n    v_ = reduce(mul(v_, rhs.v_));\r\n    return *this;\r\n  }\r\
    \n  constexpr m64 &operator/=(const m64 &rhs) { return operator*=(rhs.inv());\
    \ }\r\n  friend constexpr m64 operator+(const m64 &lhs, const m64 &rhs) { return\
    \ m64(lhs) += rhs; }\r\n  friend constexpr m64 operator-(const m64 &lhs, const\
    \ m64 &rhs) { return m64(lhs) -= rhs; }\r\n  friend constexpr m64 operator*(const\
    \ m64 &lhs, const m64 &rhs) { return m64(lhs) *= rhs; }\r\n  friend constexpr\
    \ m64 operator/(const m64 &lhs, const m64 &rhs) { return m64(lhs) /= rhs; }\r\n\
    \  friend constexpr bool operator==(const m64 &lhs, const m64 &rhs) { return lhs.v_\
    \ == rhs.v_; }\r\n  friend constexpr bool operator!=(const m64 &lhs, const m64\
    \ &rhs) { return lhs.v_ != rhs.v_; }\r\n\r\n  friend std::istream &operator>>(std::istream\
    \ &is, m64 &rhs) {\r\n    i64 x;\r\n    is >> x;\r\n    rhs = m64(x);\r\n    return\
    \ is;\r\n  }\r\n  friend std::ostream &operator<<(std::ostream &os, const m64\
    \ &rhs) { return os << rhs.get(); }\r\n\r\n  constexpr m64 pow(u64 y) const {\r\
    \n    m64 res(1), x(*this);\r\n    for (; y != 0; y >>= 1, x *= x)\r\n      if\
    \ (y & 1) res *= x;\r\n    return res;\r\n  }\r\n\r\nprivate:\r\n  static constexpr\
    \ std::pair<u64, u64> mul(u64 x, u64 y) {\r\n#ifdef __GNUC__\r\n    unsigned __int128\
    \ res = (unsigned __int128)x * y;\r\n    return {u64(res >> 64), u64(res)};\r\n\
    #elif defined(_MSC_VER)\r\n    u64 h, l = _umul128(x, y, &h);\r\n    return {h,\
    \ l};\r\n#else\r\n    u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad\
    \ = a * d, bc = b * c;\r\n    return {a * c + (ad >> 32) + (bc >> 32) +\r\n  \
    \              (((ad & ~UINT32_C(0)) + (bc & ~UINT32_C(0)) + (b * d >> 32)) >>\
    \ 32),\r\n            x * y};\r\n#endif\r\n  }\r\n\r\n  static constexpr u64 mulh(u64\
    \ x, u64 y) {\r\n#ifdef __GNUC__\r\n    return u64((unsigned __int128)x * y >>\
    \ 64);\r\n#elif defined(_MSC_VER)\r\n    return __umulh(x, y);\r\n#else\r\n  \
    \  u64 a = x >> 32, b = u32(x), c = y >> 32, d = u32(y), ad = a * d, bc = b *\
    \ c;\r\n    return a * c + (ad >> 32) + (bc >> 32) +\r\n           (((ad & ~UINT32_C(0))\
    \ + (bc & ~UINT32_C(0)) + (b * d >> 32)) >> 32);\r\n#endif\r\n  }\r\n\r\n  static\
    \ constexpr u64 get_r() {\r\n    u64 two = 2, iv = mod * (two - mod * mod);\r\n\
    \    iv *= two - mod * iv;\r\n    iv *= two - mod * iv;\r\n    iv *= two - mod\
    \ * iv;\r\n    return iv * (two - mod * iv);\r\n  }\r\n\r\n  static constexpr\
    \ u64 get_r2() {\r\n    u64 iv = -u64(mod) % mod;\r\n    for (int i = 0; i !=\
    \ 64; ++i)\r\n      if ((iv <<= 1) >= mod) iv -= mod;\r\n    return iv;\r\n  }\r\
    \n\r\n  static constexpr u64 reduce(const std::pair<u64, u64> &x) {\r\n    u64\
    \ res = x.first - mulh(x.second * r, mod);\r\n    return res + (mod & -(res >>\
    \ 63));\r\n  }\r\n\r\n  static constexpr u64 norm(i64 x) { return x + (mod & -(x\
    \ < 0)); }\r\n\r\n  u64 v_;\r\n\r\n  static constexpr u64 r  = get_r();\r\n  static\
    \ constexpr u64 r2 = get_r2();\r\n\r\n  static_assert((mod & 1) == 1, \"mod %\
    \ 2 == 0\\n\");\r\n  static_assert(r * mod == 1, \"???\\n\");\r\n  static_assert((mod\
    \ & (1ULL << 63)) == 0, \"mod >= (1ULL << 63)\\n\");\r\n  static_assert(mod !=\
    \ 1, \"mod == 1\\n\");\r\n};\r\n\r\ntemplate <std::uint64_t mod>\r\nusing LongMontModInt\
    \ = LongMontgomeryModInt<mod>;\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: modint/long_Montgomery_modint.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: modint/long_Montgomery_modint.hpp
layout: document
redirect_from:
- /library/modint/long_Montgomery_modint.hpp
- /library/modint/long_Montgomery_modint.hpp.html
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

