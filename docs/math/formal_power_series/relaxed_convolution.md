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

TODO

## 参考文献

- van der Hoeven, J., 2003a. [New algorithms for relaxed multiplication](http://www.texmacs.org/joris/newrelax/newrelax.html). Tech. Rep. 2003–44, Universit´e Paris-Sud, Orsay, France.
- J. van der Hoeven. Relax, but don't be too lazy. JSC, 34:479–542, 2002.
- Elegia and Athekatelan. 信息学竞赛中的⽣成函数计算理论框架.
- Elegia 的讲课[视频](https://www.bilibili.com/video/BV1kA41187dQ). （约 50 分钟左右，半在线卷积的具体实现及常见幂级数算法表示为半在线卷积， $O\left(\frac{n\log ^2n}{\log \log n}\right)$ ）
- fjzzq2002. [一个更好的多项式模板](https://fjzzq2002.blog.uoj.ac/blog/7281).