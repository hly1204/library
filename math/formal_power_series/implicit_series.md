---
title: Implicit Series
documentation_of: ./implicit_series.hpp
---

## 隐式级数

在 [Philippe Flajolet](http://algo.inria.fr/flajolet/) 和 Robert Sedgewick 的 Analytic Combinatorics 一书中提到生成函数的隐式形式，我参考 Hoeven 的论文中的描述使用 C++ 中的 lambda 和在线卷积实现了部分相当简单的功能。

例如 Catalan 数的 OGF（Analytic Combinatorics 第 36 页）为

$$
T(z)=1+zT^2(z)\implies T(z)=\frac{1-\sqrt{1-4z}}{2z}
$$

右侧是闭形式可以使用形式幂级数简单的计算，左侧就是隐式的形式了。隐式级数一般容易找到，而找到闭形式有可能比较困难（或者不一定存在？）。

隐式级数的快速计算可以直接解决 [LOJ 6538. 烷基计数 加强版 加强版](https://loj.ac/p/6538) 等问题，尽管在时间复杂度上并无优势，见 [符号化方法](https://hly1204.github.io/library/symbolic_method.html)。

另外 Elegia 指出在线卷积也可以扩展到任意模数的二项卷积上，那么隐式级数的计算可能也可以扩展，但由于过于复杂我也不会！

## Pólya 算子

对于普通生成函数，下面要求 $f(0)=0$，此时四个算子为

$$
\begin{aligned}
Q\lbrack f\rbrack &=\frac{1}{1-f},&\operatorname{Log}\lbrack f\rbrack &=\sum _ {k\geq 1}\frac{\varphi(k)}{k}\log\frac{1}{1-f(z^k)},\\
\operatorname{Exp}\lbrack f\rbrack &=\exp\left(\sum _ {k\geq 1}\frac{f(z^k)}{k}\right),&\overline{\operatorname{Exp}}\lbrack f\rbrack &=\exp\left(\sum _ {k\geq 1}(-1)^{k-1}\frac{f(z^k)}{k}\right)
\end{aligned}
$$

对于 $\operatorname{Log}$ 因为我还不懂所以不打算实现。

### $Q\lbrack f\rbrack$

应用倒数即可。

### $\operatorname{Exp}\lbrack f\rbrack$ 和 $\overline{\operatorname{Exp}}\lbrack f\rbrack$

考虑维护 $\sum _ {k\geq 1}f(z^k)/k$。如果可以提前知道 $n$ 的大小，那么消耗时间大约为 $O(n\cdot H_n)$ 其中 $H_n=\sum _ {i=1}^{n}i^{-1}\approx \ln n+C$ 所以大概可以认为时间复杂度为 $O(n\log n)$，但是因为不知道所以我采用倍增的方法。

## 参考文献

- Elegia. [《生成函数的一点进展》重置版](https://www.bilibili.com/video/BV1U5411N7Uc).
- 同 [在线卷积](https://hly1204.github.io/library/math/formal_power_series/relaxed_convolution.hpp) 的参考文献.