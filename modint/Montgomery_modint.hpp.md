---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/arbitrary_modulo_convolution.hpp
    title: "arbitrary modulo convolution / \u4EFB\u610F\u6A21\u6570\u5377\u79EF"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.0.test.cpp
    title: remote_test/yosupo/math/convolution_mod.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.1.test.cpp
    title: remote_test/yosupo/math/convolution_mod.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
    title: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
    title: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/find_linear_recurrence.0.test.cpp
    title: remote_test/yosupo/math/find_linear_recurrence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
    title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
    title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
    title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
    title: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
    title: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
    title: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
    title: remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
    title: remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/matrix/inverse_matrix.0.test.cpp
    title: remote_test/yosupo/matrix/inverse_matrix.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/matrix/matrix_det.0.test.cpp
    title: remote_test/yosupo/matrix/matrix_det.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/matrix/matrix_det.1.test.cpp
    title: remote_test/yosupo/matrix/matrix_det.1.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/matrix/matrix_product.0.test.cpp
    title: remote_test/yosupo/matrix/matrix_product.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
    title: remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    _deprecated_at_docs: docs/modint/Montgomery_modint.md
    document_title: "Montgomery modint / Montgomery \u53D6\u6A21\u7C7B"
    links:
    - https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp
  bundledCode: "#line 1 \"modint/Montgomery_modint.hpp\"\n\n\n\r\n/**\r\n * @brief\
    \ Montgomery modint / Montgomery \u53D6\u6A21\u7C7B\r\n * @docs docs/modint/Montgomery_modint.md\r\
    \n */\r\n\r\n#include <cstdint>\r\n#include <iostream>\r\n#include <type_traits>\r\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief Montgomery \u53D6\u6A21\u7C7B\r\n\
    \ * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\n\
    \ * @author Nyaan\r\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\r\n\
    \ */\r\ntemplate <std::uint32_t mod>\r\nclass MontgomeryModInt {\r\npublic:\r\n\
    \  using i32 = std::int32_t;\r\n  using u32 = std::uint32_t;\r\n  using u64 =\
    \ std::uint64_t;\r\n  using m32 = MontgomeryModInt;\r\n\r\n  using value_type\
    \ = u32;\r\n\r\n  static constexpr u32 get_mod() { return mod; }\r\n\r\n  static\
    \ constexpr u32 get_primitive_root_prime() {\r\n    u32 tmp[32]   = {};\r\n  \
    \  int cnt       = 0;\r\n    const u32 phi = mod - 1;\r\n    u32 m         = phi;\r\
    \n    for (u32 i = 2; i * i <= m; ++i) {\r\n      if (m % i == 0) {\r\n      \
    \  tmp[cnt++] = i;\r\n        do { m /= i; } while (m % i == 0);\r\n      }\r\n\
    \    }\r\n    if (m != 1) tmp[cnt++] = m;\r\n    for (m32 res = 2;; res += 1)\
    \ {\r\n      bool f = true;\r\n      for (int i = 0; i < cnt && f; ++i) f &= res.pow(phi\
    \ / tmp[i]) != 1;\r\n      if (f) return u32(res);\r\n    }\r\n  }\r\n\r\n  constexpr\
    \ MontgomeryModInt() = default;\r\n  ~MontgomeryModInt()          = default;\r\
    \n\r\n  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\
    \n  constexpr MontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) + i32(mod)) *\
    \ r2)) {}\r\n\r\n  constexpr MontgomeryModInt(const m32 &) = default;\r\n\r\n\
    \  constexpr u32 get() const { return norm(reduce(v_)); }\r\n\r\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  explicit constexpr\
    \ operator T() const {\r\n    return T(get());\r\n  }\r\n\r\n  constexpr m32 operator-()\
    \ const {\r\n    m32 res;\r\n    res.v_ = (mod2 & -(v_ != 0)) - v_;\r\n    return\
    \ res;\r\n  }\r\n\r\n  constexpr m32 inv() const {\r\n    i32 x1 = 1, x3 = 0,\
    \ a = get(), b = mod;\r\n    while (b != 0) {\r\n      i32 q = a / b, x1_old =\
    \ x1, a_old = a;\r\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b\
    \ * q;\r\n    }\r\n    return m32(x1);\r\n  }\r\n\r\n  constexpr m32 &operator=(const\
    \ m32 &) = default;\r\n\r\n  constexpr m32 &operator+=(const m32 &rhs) {\r\n \
    \   v_ += rhs.v_ - mod2;\r\n    v_ += mod2 & -(v_ >> 31);\r\n    return *this;\r\
    \n  }\r\n  constexpr m32 &operator-=(const m32 &rhs) {\r\n    v_ -= rhs.v_;\r\n\
    \    v_ += mod2 & -(v_ >> 31);\r\n    return *this;\r\n  }\r\n  constexpr m32\
    \ &operator*=(const m32 &rhs) {\r\n    v_ = reduce(u64(v_) * rhs.v_);\r\n    return\
    \ *this;\r\n  }\r\n  constexpr m32 &operator/=(const m32 &rhs) { return operator*=(rhs.inv());\
    \ }\r\n  friend constexpr m32 operator+(const m32 &lhs, const m32 &rhs) { return\
    \ m32(lhs) += rhs; }\r\n  friend constexpr m32 operator-(const m32 &lhs, const\
    \ m32 &rhs) { return m32(lhs) -= rhs; }\r\n  friend constexpr m32 operator*(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }\r\n  friend constexpr\
    \ m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs) /= rhs; }\r\n\
    \  friend constexpr bool operator==(const m32 &lhs, const m32 &rhs) {\r\n    return\
    \ norm(lhs.v_) == norm(rhs.v_);\r\n  }\r\n  friend constexpr bool operator!=(const\
    \ m32 &lhs, const m32 &rhs) {\r\n    return norm(lhs.v_) != norm(rhs.v_);\r\n\
    \  }\r\n\r\n  friend std::istream &operator>>(std::istream &is, m32 &rhs) {\r\n\
    \    i32 x;\r\n    is >> x;\r\n    rhs = m32(x);\r\n    return is;\r\n  }\r\n\
    \  friend std::ostream &operator<<(std::ostream &os, const m32 &rhs) { return\
    \ os << rhs.get(); }\r\n\r\n  constexpr m32 pow(u64 y) const {\r\n    m32 res(1),\
    \ x(*this);\r\n    for (; y != 0; y >>= 1, x *= x)\r\n      if (y & 1) res *=\
    \ x;\r\n    return res;\r\n  }\r\n\r\nprivate:\r\n  static constexpr u32 get_r()\
    \ {\r\n    u32 two = 2, iv = mod * (two - mod * mod);\r\n    iv *= two - mod *\
    \ iv;\r\n    iv *= two - mod * iv;\r\n    return iv * (mod * iv - two);\r\n  }\r\
    \n\r\n  static constexpr u32 reduce(u64 x) { return (x + u64(u32(x) * r) * mod)\
    \ >> 32; }\r\n  static constexpr u32 norm(u32 x) { return x - (mod & -((mod -\
    \ 1 - x) >> 31)); }\r\n\r\n  u32 v_;\r\n\r\n  static constexpr u32 r    = get_r();\r\
    \n  static constexpr u32 r2   = -u64(mod) % mod;\r\n  static constexpr u32 mod2\
    \ = mod << 1;\r\n\r\n  static_assert((mod & 1) == 1, \"mod % 2 == 0\\n\");\r\n\
    \  static_assert(-r * mod == 1, \"???\\n\");\r\n  static_assert((mod & (3U <<\
    \ 30)) == 0, \"mod >= (1 << 30)\\n\");\r\n  static_assert(mod != 1, \"mod == 1\\\
    n\");\r\n};\r\n\r\n// \u522B\u540D\r\ntemplate <std::uint32_t mod>\r\nusing MontModInt\
    \ = MontgomeryModInt<mod>;\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef MONTGOMERY_MODINT_HEADER_HPP\r\n#define MONTGOMERY_MODINT_HEADER_HPP\r\
    \n\r\n/**\r\n * @brief Montgomery modint / Montgomery \u53D6\u6A21\u7C7B\r\n *\
    \ @docs docs/modint/Montgomery_modint.md\r\n */\r\n\r\n#include <cstdint>\r\n\
    #include <iostream>\r\n#include <type_traits>\r\n\r\nnamespace lib {\r\n\r\n/**\r\
    \n * @brief Montgomery \u53D6\u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
    \n * @author Nyaan\r\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\r\n\
    \ */\r\ntemplate <std::uint32_t mod>\r\nclass MontgomeryModInt {\r\npublic:\r\n\
    \  using i32 = std::int32_t;\r\n  using u32 = std::uint32_t;\r\n  using u64 =\
    \ std::uint64_t;\r\n  using m32 = MontgomeryModInt;\r\n\r\n  using value_type\
    \ = u32;\r\n\r\n  static constexpr u32 get_mod() { return mod; }\r\n\r\n  static\
    \ constexpr u32 get_primitive_root_prime() {\r\n    u32 tmp[32]   = {};\r\n  \
    \  int cnt       = 0;\r\n    const u32 phi = mod - 1;\r\n    u32 m         = phi;\r\
    \n    for (u32 i = 2; i * i <= m; ++i) {\r\n      if (m % i == 0) {\r\n      \
    \  tmp[cnt++] = i;\r\n        do { m /= i; } while (m % i == 0);\r\n      }\r\n\
    \    }\r\n    if (m != 1) tmp[cnt++] = m;\r\n    for (m32 res = 2;; res += 1)\
    \ {\r\n      bool f = true;\r\n      for (int i = 0; i < cnt && f; ++i) f &= res.pow(phi\
    \ / tmp[i]) != 1;\r\n      if (f) return u32(res);\r\n    }\r\n  }\r\n\r\n  constexpr\
    \ MontgomeryModInt() = default;\r\n  ~MontgomeryModInt()          = default;\r\
    \n\r\n  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\
    \n  constexpr MontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) + i32(mod)) *\
    \ r2)) {}\r\n\r\n  constexpr MontgomeryModInt(const m32 &) = default;\r\n\r\n\
    \  constexpr u32 get() const { return norm(reduce(v_)); }\r\n\r\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  explicit constexpr\
    \ operator T() const {\r\n    return T(get());\r\n  }\r\n\r\n  constexpr m32 operator-()\
    \ const {\r\n    m32 res;\r\n    res.v_ = (mod2 & -(v_ != 0)) - v_;\r\n    return\
    \ res;\r\n  }\r\n\r\n  constexpr m32 inv() const {\r\n    i32 x1 = 1, x3 = 0,\
    \ a = get(), b = mod;\r\n    while (b != 0) {\r\n      i32 q = a / b, x1_old =\
    \ x1, a_old = a;\r\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b\
    \ * q;\r\n    }\r\n    return m32(x1);\r\n  }\r\n\r\n  constexpr m32 &operator=(const\
    \ m32 &) = default;\r\n\r\n  constexpr m32 &operator+=(const m32 &rhs) {\r\n \
    \   v_ += rhs.v_ - mod2;\r\n    v_ += mod2 & -(v_ >> 31);\r\n    return *this;\r\
    \n  }\r\n  constexpr m32 &operator-=(const m32 &rhs) {\r\n    v_ -= rhs.v_;\r\n\
    \    v_ += mod2 & -(v_ >> 31);\r\n    return *this;\r\n  }\r\n  constexpr m32\
    \ &operator*=(const m32 &rhs) {\r\n    v_ = reduce(u64(v_) * rhs.v_);\r\n    return\
    \ *this;\r\n  }\r\n  constexpr m32 &operator/=(const m32 &rhs) { return operator*=(rhs.inv());\
    \ }\r\n  friend constexpr m32 operator+(const m32 &lhs, const m32 &rhs) { return\
    \ m32(lhs) += rhs; }\r\n  friend constexpr m32 operator-(const m32 &lhs, const\
    \ m32 &rhs) { return m32(lhs) -= rhs; }\r\n  friend constexpr m32 operator*(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }\r\n  friend constexpr\
    \ m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs) /= rhs; }\r\n\
    \  friend constexpr bool operator==(const m32 &lhs, const m32 &rhs) {\r\n    return\
    \ norm(lhs.v_) == norm(rhs.v_);\r\n  }\r\n  friend constexpr bool operator!=(const\
    \ m32 &lhs, const m32 &rhs) {\r\n    return norm(lhs.v_) != norm(rhs.v_);\r\n\
    \  }\r\n\r\n  friend std::istream &operator>>(std::istream &is, m32 &rhs) {\r\n\
    \    i32 x;\r\n    is >> x;\r\n    rhs = m32(x);\r\n    return is;\r\n  }\r\n\
    \  friend std::ostream &operator<<(std::ostream &os, const m32 &rhs) { return\
    \ os << rhs.get(); }\r\n\r\n  constexpr m32 pow(u64 y) const {\r\n    m32 res(1),\
    \ x(*this);\r\n    for (; y != 0; y >>= 1, x *= x)\r\n      if (y & 1) res *=\
    \ x;\r\n    return res;\r\n  }\r\n\r\nprivate:\r\n  static constexpr u32 get_r()\
    \ {\r\n    u32 two = 2, iv = mod * (two - mod * mod);\r\n    iv *= two - mod *\
    \ iv;\r\n    iv *= two - mod * iv;\r\n    return iv * (mod * iv - two);\r\n  }\r\
    \n\r\n  static constexpr u32 reduce(u64 x) { return (x + u64(u32(x) * r) * mod)\
    \ >> 32; }\r\n  static constexpr u32 norm(u32 x) { return x - (mod & -((mod -\
    \ 1 - x) >> 31)); }\r\n\r\n  u32 v_;\r\n\r\n  static constexpr u32 r    = get_r();\r\
    \n  static constexpr u32 r2   = -u64(mod) % mod;\r\n  static constexpr u32 mod2\
    \ = mod << 1;\r\n\r\n  static_assert((mod & 1) == 1, \"mod % 2 == 0\\n\");\r\n\
    \  static_assert(-r * mod == 1, \"???\\n\");\r\n  static_assert((mod & (3U <<\
    \ 30)) == 0, \"mod >= (1 << 30)\\n\");\r\n  static_assert(mod != 1, \"mod == 1\\\
    n\");\r\n};\r\n\r\n// \u522B\u540D\r\ntemplate <std::uint32_t mod>\r\nusing MontModInt\
    \ = MontgomeryModInt<mod>;\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: modint/Montgomery_modint.hpp
  requiredBy:
  - math/formal_power_series/arbitrary_modulo_convolution.hpp
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - remote_test/yosupo/matrix/matrix_det.0.test.cpp
  - remote_test/yosupo/matrix/characteristic_polynomial.1.test.cpp
  - remote_test/yosupo/matrix/matrix_det.1.test.cpp
  - remote_test/yosupo/matrix/characteristic_polynomial.0.test.cpp
  - remote_test/yosupo/matrix/matrix_product.0.test.cpp
  - remote_test/yosupo/matrix/inverse_matrix.0.test.cpp
  - remote_test/yosupo/matrix/sparse_matrix_det.0.test.cpp
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - remote_test/yosupo/math/find_linear_recurrence.0.test.cpp
  - remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
  - remote_test/yosupo/math/convolution_mod.0.test.cpp
  - remote_test/yosupo/math/convolution_mod.1.test.cpp
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
  - remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
documentation_of: modint/Montgomery_modint.hpp
layout: document
redirect_from:
- /library/modint/Montgomery_modint.hpp
- /library/modint/Montgomery_modint.hpp.html
title: "Montgomery modint / Montgomery \u53D6\u6A21\u7C7B"
---
## Montgomery modint

类 `MontgomeryModInt` 是一个自动取模的类型，且模数 $M\in(1,2^{30}), M\bmod 2=1$ 。重载有基本的四则运算符号和比较运算符（ `==` 和 `!=` ）。

- `MontgomeryModInt<M>::value_type` 为内部数据类型，即 `std::uint32_t` 。
- `MontgomeryModInt<M>::get_mod()` 返回模数 $M$ 且类型为 `std::uint32_t` 。
- `using MontModInt = MontgomeryModInt` 为一个辅助模板。

成员函数有

- `pow(k)` 接收非负整型。
- `inv()` 返回其逆元，注意这里并未处理不存在的情况。
- `get_primitive_root_prime()` 返回素数的最小原根，配合 NTT 算法。

代码使用惰性的“修正”，在 `reduce` 函数后答案在 $[0,2M)$ 。

## Montgomery reduction

> 定义：对于 $N\gt 1$ 选择一个基数 $R$ 与 $N$ 互素且 $R\gt N$ 。令 $R^{-1}$ 和 $N'$ 满足 $0\lt R^{-1}\lt N$ 且 $0\lt N'\lt R$ 且 $RR^{-1}-NN'=1$ 。对于 $T$ 满足 $0\leq T\lt RN$ ，我们将一种快速计算 $TR^{-1}\bmod{N}$ 的算法称为 Montgomery reduction 。

Bézout 等式 $RR^{-1}-NN'=1$ 告诉我们 $N'\equiv -N^{-1}\pmod{R}$ 。

$$
\begin{array}{ll}
\textbf{procedure }\operatorname{REDC}(T) \\
\qquad m\gets (T\bmod R)N'\bmod{R} \\
\qquad t\gets (T+mN)/R \\
\qquad \textbf{if }t\geq N\textbf{ then return }t-N \\
\qquad \textbf{else return } t
\end{array}
$$

证明：观察到 $TN'\bmod R=TN'+kR$ 对于某个整数 $k$ 成立，那么

$$
t=(T+(TN'+kR)N)/R=(T+TN'N+kRN)/R
$$

而又因为 $N'N=-1+lR$ 对于某个整数 $l$ 成立，所以

$$
t=(T+T(-1+lR)+kRN)/R=lT+kN
$$

显然为整数。且因为 $0\leq T\lt RN,0\leq m\lt R$ 所以 $0\leq (T+mN)/R\lt 2N$ 。 $\square$

而在实践中通常选取 $R=2^{32}$ ，那么可以写下如下 C++ 代码

```cpp
typedef std::uint32_t u32;
typedef std::uint64_t u64;
// 预处理 N_p 作为 N' ，类型为 u32 ，模数 N 为奇数
u32 REDC(u64 T) { return T + u64(u32(T) * N_p) * N >> 32; }
```

其中我们没有处理 $t\geq N$ 的情况，这是因为假设选取的 $N\lt 2^{30}$ 此时返回值在 $[0,2N)$ 中，如果我们将两个 $T_{1},T_{2}$ 相乘再进行 REDC ，那么注意 REDC 的输入参数只要求 $[0,RN)$ 中即可，这样可以惰性的进行伪代码最后一步的“修正”过程。

假设我们需要在模奇数 $N$ 意义下对 $0\leq x\lt N$ 和 $0\leq y\lt N$ 计算 $xy\bmod N$，那么通过 $\operatorname{REDC}(x(R^{2}\bmod N))$ 计算 $xR\bmod N$ 再计算 $\operatorname{REDC}(xRy)$ 即可。这提示我们预处理 $R^{2}\bmod N$ 和 $N'$ 即可。

而 $N'$ 可以通过 Hensel lifting （可被视为 $p$-adic variant of Newton's method ）计算，因为 $N$ 为奇数，那么 $N^{-1}\bmod 2=1$ ，使用以下迭代

$$
x_{n+1}=x_{n}+x_{n}(1-bx_{n})
$$

假设 $x_{n}\equiv b^{-1}\pmod p$ 对于某个 $p$ 成立，那么 $x_{n}b\equiv 1+kp\pmod{p^{2}}$ 对于某个整数 $k$ 成立，那么

$$
\begin{aligned}x_{n+1}&=x_{n}(2-bx_{n})\\
&\equiv x_{n}(2-(1+kp))\pmod{p^{2}}\\
&\equiv b^{-1}(1+kp)(1-kp)\pmod{p^{2}}\\
&\equiv b^{-1}(1-k^{2}p^{2})\pmod{p^{2}}\\
&\equiv b^{-1}\pmod{p^{2}}\end{aligned}
$$

在这里我们只需将 $p$ 替换为 $2$ 即可。 $\square$

令 $x_{0}=1$ ，第一次迭代为 $x_{1}=x_{0}(2-Nx_{0})$ 这使我们发现 $x_{1}=2-N$ 而不论 $N\equiv 1\pmod{4}$ 或者 $N\equiv 3\pmod{4}$ 都有 $2-N\equiv N\pmod{4}$ 。

## 参考文献

- Peter L. Montgomery. Modular Multiplication Without Trial Division, 1985.
- Richard P. Brent and Paul Zimmermann, Modern Computer Arithmetic, Cambridge Monographs on Computational and Applied Mathematics (No. 18), Cambridge University Press, November 2010, 236 pages
- Nyaan 的[博客](https://nyaannyaan.github.io/docs/modulo/montgomery/)

