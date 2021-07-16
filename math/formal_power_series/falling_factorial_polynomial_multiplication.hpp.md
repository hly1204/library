---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/NTT_binomial.hpp
    title: "NTT prime binomial / NTT \u7D20\u6570\u7528\u4E8C\u9879\u5F0F\u7CFB\u6570"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    _deprecated_at_docs: docs/math/formal_power_series/falling_factorial_polynomial_multiplication.md
    document_title: "falling factorial polynomial multiplication / \u4E0B\u964D\u5E42\
      \u591A\u9879\u5F0F\u4E58\u6CD5"
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/falling_factorial_polynomial_multiplication.hpp\"\
    \n\n\n\r\n/**\r\n * @brief falling factorial polynomial multiplication / \u4E0B\
    \u964D\u5E42\u591A\u9879\u5F0F\u4E58\u6CD5\r\n * @docs docs/math/formal_power_series/falling_factorial_polynomial_multiplication.md\r\
    \n */\r\n\r\n#include <vector>\r\n\r\n#line 1 \"math/formal_power_series/NTT_binomial.hpp\"\
    \n\n\n\r\n/**\r\n * @brief NTT prime binomial / NTT \u7D20\u6570\u7528\u4E8C\u9879\
    \u5F0F\u7CFB\u6570\r\n *\r\n */\r\n\r\n#line 10 \"math/formal_power_series/NTT_binomial.hpp\"\
    \n\r\nnamespace lib {\r\n\r\ntemplate <typename mod_t>\r\nclass NTTBinomial {\r\
    \npublic:\r\n  NTTBinomial(int lim = 0) {\r\n    if (fac_.empty()) {\r\n     \
    \ fac_.emplace_back(1);\r\n      ifac_.emplace_back(1);\r\n    }\r\n    init(lim);\r\
    \n  }\r\n  ~NTTBinomial() = default;\r\n\r\n  void init(int n) { // \u9884\u5904\
    \u7406 [0, n) \u7684\u9636\u4E58\u548C\u5176\u9006\u5143\uFF01\r\n    if (int(fac_.size())\
    \ < n) {\r\n      int old_size = fac_.size();\r\n      fac_.resize(n);\r\n   \
    \   ifac_.resize(n);\r\n      for (int i = old_size; i < n; ++i) fac_[i] = fac_[i\
    \ - 1] * mod_t(i);\r\n      mod_t iv     = mod_t(1) / fac_.back();\r\n      ifac_.back()\
    \ = iv;\r\n      for (int i = n - 2; i >= lim; --i) ifac_[i] = ifac_[i + 1] *\
    \ mod_t(i + 1);\r\n    }\r\n  }\r\n\r\n  mod_t fac_unsafe(int n) const { return\
    \ fac_[n]; }\r\n  mod_t ifac_unsafe(int n) const { return ifac_[n]; }\r\n  mod_t\
    \ inv_unsafe(int n) const { return ifac_[n] * fac_[n - 1]; }\r\n  mod_t choose_unsafe(int\
    \ n, int k) const {\r\n    // \u8FD4\u56DE binom{n}{k} \u6CE8\u610F\u4E0A\u6307\
    \u6807\u53EF\u4EE5\u4E3A\u8D1F\u6570\u4F46\u8FD9\u91CC\u5E76\u672A\u5B9E\u73B0\
    \uFF01\r\n    return n >= k ? fac_[n] * ifac_[k] * ifac_[n - k] : mod_t(0);\r\n\
    \  }\r\n\r\nprivate:\r\n  static inline std::vector<mod_t> fac_, ifac_;\r\n  static\
    \ inline int lim = 0;\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line 12 \"math/formal_power_series/falling_factorial_polynomial_multiplication.hpp\"\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u6837\u672C\u70B9\u8F6C\u6362\u4E3A\
    \u4E0B\u964D\u5E42\u591A\u9879\u5F0F\r\n *\r\n * @tparam PolyType \u591A\u9879\
    \u5F0F\u7C7B\r\n * @tparam PolyType::value_type NTT \u53CB\u597D\u7684\u6A21\u6570\
    \r\n * @param pts f(0), f(1), \u2026, f(n-1)\r\n * @return PolyType \u4E0B\u964D\
    \u5E42\u591A\u9879\u5F0F\r\n */\r\ntemplate <typename PolyType, typename mod_t\
    \ = typename PolyType::value_type>\r\nPolyType sample_points_to_FFP(const std::vector<mod_t>\
    \ &pts) {\r\n  int n = pts.size();\r\n  NTTBinomial<mod_t> bi(n);\r\n  PolyType\
    \ emx(n), pts_egf(n);\r\n  for (int i = 0; i < n; ++i) {\r\n    pts_egf[i] = pts[i]\
    \ * (emx[i] = bi.ifac_unsafe(i));\r\n    if (i & 1) emx[i] = -emx[i];\r\n  }\r\
    \n  return (emx * pts_egf).slice(n);\r\n}\r\n\r\n/**\r\n * @brief \u4E0B\u964D\
    \u5E42\u591A\u9879\u5F0F\u8F6C\u6362\u4E3A\u6837\u672C\u70B9\r\n *\r\n * @tparam\
    \ PolyType\r\n * @tparam PolyType::value_type\r\n * @param n\r\n * @param ffp\
    \ \u4E0B\u964D\u5E42\u591A\u9879\u5F0F\r\n * @return std::vector<mod_t> f(0),\
    \ f(1), \u2026, f(n-1)\r\n */\r\ntemplate <typename PolyType, typename mod_t =\
    \ typename PolyType::value_type>\r\nstd::vector<mod_t> FFP_to_sample_points(int\
    \ n, const PolyType &ffp) {\r\n  NTTBinomial<mod_t> bi(n);\r\n  PolyType ex(n);\r\
    \n  for (int i = 0; i < n; ++i) ex[i] = bi.ifac_unsafe(i);\r\n  ex *= ffp.slice(n);\r\
    \n  std::vector<mod_t> pts(n);\r\n  for (int i = 0; i < n; ++i) pts[i] = ex[i]\
    \ * bi.fac_unsafe(i);\r\n  return pts;\r\n}\r\n\r\n/**\r\n * @brief \u4E0B\u964D\
    \u5E42\u591A\u9879\u5F0F\u4E58\u6CD5\r\n */\r\ntemplate <typename PolyType, typename\
    \ mod_t = typename PolyType::value_type>\r\nPolyType mul_FFP(const PolyType &lhs,\
    \ const PolyType &rhs) {\r\n  int d = lhs.size() + rhs.size() - 1;\r\n  std::vector<mod_t>\
    \ lhs_pts(FFP_to_sample_points(d, lhs)), rhs_pts(FFP_to_sample_points(d, rhs));\r\
    \n  for (int i = 0; i < d; ++i) lhs_pts[i] *= rhs_pts[i];\r\n  return sample_points_to_FFP<PolyType>(lhs_pts);\r\
    \n}\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef FALLING_FACTORIAL_POLYNOMIAL_MULTIPLICATION_HEADER_HPP\r\n#define\
    \ FALLING_FACTORIAL_POLYNOMIAL_MULTIPLICATION_HEADER_HPP\r\n\r\n/**\r\n * @brief\
    \ falling factorial polynomial multiplication / \u4E0B\u964D\u5E42\u591A\u9879\
    \u5F0F\u4E58\u6CD5\r\n * @docs docs/math/formal_power_series/falling_factorial_polynomial_multiplication.md\r\
    \n */\r\n\r\n#include <vector>\r\n\r\n#include \"NTT_binomial.hpp\"\r\n\r\nnamespace\
    \ lib {\r\n\r\n/**\r\n * @brief \u6837\u672C\u70B9\u8F6C\u6362\u4E3A\u4E0B\u964D\
    \u5E42\u591A\u9879\u5F0F\r\n *\r\n * @tparam PolyType \u591A\u9879\u5F0F\u7C7B\
    \r\n * @tparam PolyType::value_type NTT \u53CB\u597D\u7684\u6A21\u6570\r\n * @param\
    \ pts f(0), f(1), \u2026, f(n-1)\r\n * @return PolyType \u4E0B\u964D\u5E42\u591A\
    \u9879\u5F0F\r\n */\r\ntemplate <typename PolyType, typename mod_t = typename\
    \ PolyType::value_type>\r\nPolyType sample_points_to_FFP(const std::vector<mod_t>\
    \ &pts) {\r\n  int n = pts.size();\r\n  NTTBinomial<mod_t> bi(n);\r\n  PolyType\
    \ emx(n), pts_egf(n);\r\n  for (int i = 0; i < n; ++i) {\r\n    pts_egf[i] = pts[i]\
    \ * (emx[i] = bi.ifac_unsafe(i));\r\n    if (i & 1) emx[i] = -emx[i];\r\n  }\r\
    \n  return (emx * pts_egf).slice(n);\r\n}\r\n\r\n/**\r\n * @brief \u4E0B\u964D\
    \u5E42\u591A\u9879\u5F0F\u8F6C\u6362\u4E3A\u6837\u672C\u70B9\r\n *\r\n * @tparam\
    \ PolyType\r\n * @tparam PolyType::value_type\r\n * @param n\r\n * @param ffp\
    \ \u4E0B\u964D\u5E42\u591A\u9879\u5F0F\r\n * @return std::vector<mod_t> f(0),\
    \ f(1), \u2026, f(n-1)\r\n */\r\ntemplate <typename PolyType, typename mod_t =\
    \ typename PolyType::value_type>\r\nstd::vector<mod_t> FFP_to_sample_points(int\
    \ n, const PolyType &ffp) {\r\n  NTTBinomial<mod_t> bi(n);\r\n  PolyType ex(n);\r\
    \n  for (int i = 0; i < n; ++i) ex[i] = bi.ifac_unsafe(i);\r\n  ex *= ffp.slice(n);\r\
    \n  std::vector<mod_t> pts(n);\r\n  for (int i = 0; i < n; ++i) pts[i] = ex[i]\
    \ * bi.fac_unsafe(i);\r\n  return pts;\r\n}\r\n\r\n/**\r\n * @brief \u4E0B\u964D\
    \u5E42\u591A\u9879\u5F0F\u4E58\u6CD5\r\n */\r\ntemplate <typename PolyType, typename\
    \ mod_t = typename PolyType::value_type>\r\nPolyType mul_FFP(const PolyType &lhs,\
    \ const PolyType &rhs) {\r\n  int d = lhs.size() + rhs.size() - 1;\r\n  std::vector<mod_t>\
    \ lhs_pts(FFP_to_sample_points(d, lhs)), rhs_pts(FFP_to_sample_points(d, rhs));\r\
    \n  for (int i = 0; i < d; ++i) lhs_pts[i] *= rhs_pts[i];\r\n  return sample_points_to_FFP<PolyType>(lhs_pts);\r\
    \n}\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn:
  - math/formal_power_series/NTT_binomial.hpp
  isVerificationFile: false
  path: math/formal_power_series/falling_factorial_polynomial_multiplication.hpp
  requiredBy: []
  timestamp: '2021-07-16 15:42:02+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/formal_power_series/falling_factorial_polynomial_multiplication.hpp
layout: document
redirect_from:
- /library/math/formal_power_series/falling_factorial_polynomial_multiplication.hpp
- /library/math/formal_power_series/falling_factorial_polynomial_multiplication.hpp.html
title: "falling factorial polynomial multiplication / \u4E0B\u964D\u5E42\u591A\u9879\
  \u5F0F\u4E58\u6CD5"
---
## 下降幂多项式

下降幂多项式 $f\in\mathbb{F} _ p\lbrack x\rbrack$ 是形如

$$
f=\sum _ {i=0}^nf_ix^{\underline{i}},\quad x^{\underline{k}}=x(x-1)\cdots (x-k+1)=\frac{x!}{(x-k)!}
$$

的多项式，且对于 $\forall j\gt n$ 令 $f_j=0$ ，其中 $x^{\underline{0}}=1$ 。

我们知道

$$
\begin{aligned}
\mathrm{e}^x&=0!+\frac{x}{1!}+\frac{x^2}{2!}+\cdots =\sum _ {i\geq 0}\frac{x^i}{i!}\\
\mathrm{e}^{-x}&=0!+(-1)\frac{x}{1!}+(-1)^2\frac{x^2}{2!}+\cdots =\sum _ {i\geq 0}(-1)^i\frac{x^i}{i!}\\
\left(\mathrm{e}^x\right)^\prime &=0+\frac{x^0}{1!}+\frac{2x}{2!}+\cdots =\sum _ {i\geq 0}\frac{x^i}{i!}=\mathrm{e}^x
\end{aligned}
$$

对某个非负整数 $m$ 我们令 $T=x^{\underline{m}}$ 的点值 $T(0),T(1),\dots $ 的指数生成函数

$$
\begin{aligned}
\sum _ {i\geq 0}\frac{T(i)}{i!}x^i&=\sum _ {i\geq 0}\frac{i!}{(i-m)!}\frac{x^i}{i!}\\
&=\sum _ {i\geq 0}\frac{1}{(i-m)!}x^i\\
&=\mathrm{e}^xx^m
\end{aligned}
$$

那么 $f$ 的点值 $f(0),f(1),\dots $ 的指数生成函数

$$
\sum _ {i\geq 0}\frac{f(i)}{i!}x^i=\mathrm{e}^x\left(\sum _ {i\geq 0}f_ix^i\right)
$$

注意这里的 $\sum _ {i\geq 0}f_ix^i$ 是下降幂多项式 $f$ 其下降幂系数 $\lbrack x^{\underline i}\rbrack$ 的生成函数。我们可以通过一次多项式乘法在下降幂系数和点值间转换。

## 下降幂多项式平移

考虑下降幂的二项式定理 $(n+m)^{\underline{k}}=\sum _ {i=0}^k\binom{k}{i}n^{\underline{i}}m^{\underline{k-i}}$ ，参考 [stackexchange](https://math.stackexchange.com/questions/1271688/combinatorial-proof-of-falling-factorial-and-binomial-theorem) 不妨考虑其组合意义，从 $n$ 个不同的黑球和 $m$ 个不同的白球中取出 $k$ 个球有

$$
(n+m)^{\underline{k}}
$$

种取法（第一次有 $(n+m)$ 种取法，第二次有 $n+m-1$ 种，以此类推）。而另一种计算方式是假设第一次取了 $0$ 个黑球，第二次取了 $1$ 个黑球，以此类推，那么

$$
\begin{aligned}
(n+m)^{\underline{k}}&=\sum _ {i=0}^kk!\frac{n^{\underline{i}}}{i!}\frac{m^{\underline{k-i}}}{(k-i)!}\\
&=\sum _ {i=0}^k\binom{k}{i}n^{\underline{i}}m^{\underline{k-i}}
\end{aligned}
$$

我们忽略黑球之间的顺序再忽略白球之间的顺序，再考虑 $k$ 个球之间的顺序即可。有

$$
\begin{aligned}
f(x+c)&=\sum _ {i=0}^nf_i(x+c)^{\underline{i}}\\
&=\sum _ {i=0}^nf_i\left(\sum _ {j=0}^i\binom{i}{j}x^{\underline{j}}c^{\underline{i-j}}\right)\\
&=\sum _ {i=0}^nf_ii!\left(\sum _ {j=0}^i\frac{x^{\underline{j}}}{j!}\frac{c^{\underline{i-j}}}{(i-j)!}\right)\\
&=\sum _ {i=0}^n\frac{x^{\underline{i}}}{i!}\left(\sum _ {j=i}^{n}f_jj!\frac{c^{\underline{j-i}}}{(j-i)!}\right)
\end{aligned}
$$

与多项式平移相似。