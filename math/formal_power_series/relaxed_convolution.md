---
title: Relaxed Convolution
documentation_of: ./relaxed_convolution.hpp
---

## 在线卷积

对于幂级数 $f,g$ 在能使用 FFT/NTT 的环上，但我只考虑 $\mathbb{F} _ p\lbrack \lbrack z\rbrack \rbrack$ 上的运算。

考虑朴素的在线卷积 $O(n^2)$ 的算法，对于 $f_i$ 和 $g_j$ 给出后，其对于 $(fg) _ {i+j}$ 的贡献是要等到 $f _ {i+j}$ 和 $g _ {i+j}$ 给出后才计算的，我们说直到需要才计算那么这个算法就是惰性（ lazy ）的，而快速算法虽然也是惰性，但不完全是惰性，这也可能是 Hoeven 论文标题的由来？

Hoeven 的论文中提出对于 $i,j,p\in\mathbb{N}$ 定义

$$
\begin{aligned}
\Pi _ {i,j,p}&=(f _ {i2^p-1}z^{i2^p-1}+\cdots +f _ {(i+1)2^p-1}z^{(i+1)2^p-1})\\
&\times (g _ {j2^p-1}z^{j2^p-1}+\cdots +g _ {(j+1)2^p-1}z^{(j+1)2^p-1})
\end{aligned}
$$

快速算法基于以下观察，在第 $2^{p+1}-1$ 个 $f$ 和 $g$ 的系数给出后， $\Pi _ {1,1,p}$ 对于 $fg$ 的贡献可以由任何离线算法计算。可推广为在前 $n=k2^p-1$ 个 $f$ 和 $g$ 的系数给出后，对于奇数 $k\geq 3$ 和 $p\geq 1$ 我们可以计算贡献 $\Pi _ {1,k-1,p}$ 和 $\Pi _ {k-1,1,p}$ 。

| $\times$ | $f_0$ | $f_1$ | $f_2$ | $f_3$ | $f_4$ | $f_5$ | $f_6$ | $f_7$ |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| $g_0$ | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |
| $g_1$ | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |
| $g_2$ | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |
| $g_3$ | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 |
| $g_4$ | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
| $g_5$ | 5 | 6 | 7 | 8 | 9 | 10 | 11 | 12 |
| $g_6$ | 6 | 7 | 8 | 9 | 10 | 11 | 12 | 13 |
| $g_7$ | 7 | 8 | 9 | 10 | 11 | 12 | 13 | 14 |

上表中为朴素的在线算法对于 $f_ig_j$ 对于 $fg$ 的贡献在第 $i+j$ 个阶段才进行计算，但这有点太过于惰性了。而快速算法则是

| $\times$ | $f_0$ | $f_1$ | $f_2$ | $f_3$ | $f_4$ | $f_5$ | $f_6$ |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| $g_0$ | 0 | 1 | 2 | 3 | 4 | 5 | 6 |
| $g_1$ | 1 | 2 | 2 | 4 | 4 | 6 | 6 |
| $g_2$ | 2 | 2 | 2 | 4 | 4 | 6 | 6 |
| $g_3$ | 3 | 4 | 4 | 6 | 6 | 6 | 6 |
| $g_4$ | 4 | 4 | 4 | 6 | 6 | 6 | 6 |
| $g_5$ | 5 | 6 | 6 | 6 | 6 | 6 | 6 |
| $g_6$ | 6 | 6 | 6 | 6 | 6 | 6 | 6 |

我们注意如 $g_2f_2$ 的贡献，在得到 $g_2$ 和 $f_2$ 后就计算完毕了，而 $f_3g_1$ 的贡献则与朴素算法在同一阶段执行，如果观察原论文中的更直观的表格会发现我们将整个矩形分成了大大小小的正方形，每一个正方形代表一次卷积（乘法）。

另外注意，我们在传统的分治 FFT 算法中使用到了循环卷积，这也正是 middle product （第三篇）论文中相关的，在一些论文中认为使用 middle product 进行半在线卷积减少了常数，虽然我觉得好像差不太多，但是实现难度更高，我没有尝试。

## 参考文献

- van der Hoeven, J., 2003a. [New algorithms for relaxed multiplication](http://www.texmacs.org/joris/newrelax/newrelax.html). Tech. Rep. 2003–44, Universit´e Paris-Sud, Orsay, France.
- J. van der Hoeven. Relax, but don't be too lazy. JSC, 34:479–542, 2002.
- van der Hoeven, J., August 2003b. Relaxed multiplication using the middle product. In: Bronstein, M. (Ed.), Proc.
ISSAC’03. Philadelphia, USA, pp. 143–147.
- Elegia and Athekatelan. 信息学竞赛中的⽣成函数计算理论框架.
- Elegia 的讲课[视频](https://www.bilibili.com/video/BV1kA41187dQ). （约 50 分钟左右，半在线卷积的具体实现及常见幂级数算法表示为半在线卷积， $O\left(\frac{n\log ^2n}{\log \log n}\right)$ ）
- fjzzq2002. [一个更好的多项式模板](https://fjzzq2002.blog.uoj.ac/blog/7281).