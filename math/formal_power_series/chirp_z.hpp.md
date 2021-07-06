---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    _deprecated_at_docs: docs/math/formal_power_series/chirp_z.md
    document_title: "chirp z transform / chirp z \u53D8\u6362"
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/chirp_z.hpp\"\n\n\n\n/**\n * @brief\
    \ chirp z transform / chirp z \u53D8\u6362\n * @docs docs/math/formal_power_series/chirp_z.md\n\
    \ */\n\nnamespace lib {\n\ntemplate <typename mod_t> void chirp_z() {}\n\n} //\
    \ namespace lib\n\n\n"
  code: "#ifndef CHIRP_Z_HEADER_HPP\n#define CHIRP_Z_HEADER_HPP\n\n/**\n * @brief\
    \ chirp z transform / chirp z \u53D8\u6362\n * @docs docs/math/formal_power_series/chirp_z.md\n\
    \ */\n\nnamespace lib {\n\ntemplate <typename mod_t> void chirp_z() {}\n\n} //\
    \ namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/formal_power_series/chirp_z.hpp
  requiredBy: []
  timestamp: '2021-07-06 15:14:37+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/formal_power_series/chirp_z.hpp
layout: document
redirect_from:
- /library/math/formal_power_series/chirp_z.hpp
- /library/math/formal_power_series/chirp_z.hpp.html
title: "chirp z transform / chirp z \u53D8\u6362"
---
## chirp z 变换

也被称为 Bluestein 算法，我们使用标题的称呼。

对于 $A(x)=\sum _ {i=0}^na_ix^i\in\mathbb{F} _ p\lbrack x\rbrack$ 。我们希望得到 $A(1),A(c^2),A(c^4),\dots ,A(c^{2n})$ 其中 $c\in\mathbb{F} _ p^\times$ 那么可以通过将 $A_0(x)=\sum _ {i=0}^na_ic^{i^2}x^i$ 与 $B_0(x)=\sum _ {i=-n}^nc^{-i^2}x^i$ 相乘得到（为了方便，对于 $\forall j\gt n$ 令 $a_j=0$ ），但因为 $B_0(x)$ 是 Laurent 级数，我们使用 $C_0(x)=\sum _ {i=0}^{2n}c^{-(i-n)^2}x^i=x^n\cdot B_0(x)$ 那么

$$
\begin{aligned}
\lbrack x^{k}\rbrack (A_0(x)C_0(x))&=\sum _ {i=0}^{k}(\lbrack x^i\rbrack A_0(x))(\lbrack x^{k-i}\rbrack C_0(x))\\
&=\sum _ {i=0}^ka_ic^{i^2-(k-n-i)^2}
\end{aligned}
$$

令 $k=n+t$ 其中 $t\geq 0$ 那么

$$
\begin{aligned}
\sum _ {i=0}^ka_ic^{i^2-(k-n-i)^2}&=\sum _ {i=0}^{n+t}a_ic^{i^2-(i-t)^2}\\
&=c^{-t^2}\sum _ {i=0}^{n+t}a_ic^{2it}\\
&=c^{-t^2}A(c^{2t})
\end{aligned}
$$

而对于 $A(c),A(c^3)$ 等可以通过构造多项式 $B(x)=A(cx)$ 后同理。

### 使用组合数作为指数

<!-- TODO -->