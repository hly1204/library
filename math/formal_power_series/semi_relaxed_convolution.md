---
title: Semi-relaxed Convolution
documentation_of: ./semi_relaxed_convolution.hpp
---

## 半在线卷积

我们使用 $R(n)$ 和 $Q(n)$ 分别表示 $n$ 长在线和半在线卷积的时间，且只考虑在 $\mathbb{F} _ p\lbrack x\rbrack$ 中的多项式。在 Hoeven 论文中提到我们只需倍增的进行半在线卷积即可得到在线卷积，有

$$
R(n)=R(n/2)+2Q(n)+M(n)
$$

其中 $M(n)$ 表示离线的 $n$ 长卷积的时间，一般可以 NTT/FFT 时 $M(n)=\Theta(n\log n)$ 与牛顿法的时间计算方法类似，我们有

$$
R(n)=O(Q(n))
$$

也就是只需要考虑快速的半在线算法即可得到一个同样时间的在线算法，这并不复杂。

在 EI 的讲课视频中提到，如果我们使用 $B$ 叉分治，那么有

$$
T(n)=B\cdot T(n/B)+B\cdot M(n/B)+B\cdot n
$$

第二项为计算 $B$ 块 $n/B$ 大小的 FFT/NTT 的时间，注意逆变换也同样需要这么多次，那么常数我们忽略。而第三项为朴素计算 FFT/NTT block 之间乘法的时间，有 $B$ 块所以需要 $B^2$ 次块与块之间的乘法（Hadamard 积），那么 $B^2\cdot \frac{n}{B}=n\cdot B$。如果我们取 $B=\log n$ 那么

$$
\begin{aligned}
T(n)&=T\left(\frac{n}{\log n}\right)\cdot \log n+n\log n\\
&\leq 2T(n/2)+n\log n
\end{aligned}
$$

显然是比分治 FFT 的 $\Theta(n\log ^2n)$ 快的，但我不会算（或许是考虑递归树的树高？如果只考虑这一点的话，我们可以令 $T(n)=T(n/\log n)+1$ 如同 [stackoverflow](https://stackoverflow.com/questions/30826040/calculating-the-recurrence-relation-tn-tn-log-n-%CE%981/) 提到的一样，这个解为 $T(n)=\Theta(\log n/\log \log n)$ 但是证明需要用另一个上界来等价替换），参考文献三和四给出了这个时间。在 Hoeven 的论文中给出了另外的时间和证明。

但是我们在实现时一般也不取 $B=\log n$ 而是近似的 $B\in\lbrace 4,8,16,32\rbrace$。

**补充**：对于二叉分治半在线卷积有

$$
\begin{aligned}
T(n)&=2\cdot T\left(\frac{n}{2}\right)+n\log n \\
&=\sum _ {i=0}^{\log n}n\log \frac{n}{2^i} \\
&=n\log \left(\prod _ {i=0}^{\log n}\frac{n}{2^i}\right),\quad \left(\because \log_aA+\log_aB=\log_{a}(AB)\right) \\
&=n\log \left(\frac{n^{\log n}}{2^{((1+\log n)\log n)/2}}\right) \\
&=n\log n\cdot \log\left(\frac{n}{2^{(1+\log n)/2}}\right),\quad \left(\because \log_aA^b=b\log_aA\right) \\
&=n\log n\cdot \log\left(\frac{n}{\sqrt{2}\cdot \sqrt{n}}\right) \\
&=\Theta(n\log ^2n),\quad \left(\because \log\left(\frac{n}{\sqrt{2}\sqrt{n}}\right)=\frac{1}{2}\log\left(\frac{n}{2}\right)=\frac{1}{2}(\log n-\log 2)=\Theta(\log n)\right)
\end{aligned}
$$

另外注意对于半在线卷积，一般也都是计算截断前 $n$ 项的，也就是只需计算下三角形的贡献，但是在线卷积就需要计算完整的正方形的贡献。

**笔记**：注意参考文献的最后一篇论文，我们在使用二叉分治半在线卷积时可以利用 middle product 的技巧减少常数，在这里多叉分治也可以应用，具体的我们对于每一次的递归只处理下三角形的贡献，然后使用 middle product 补充缺失的部分，最后仍计算了下三角形的贡献，这种方法易修改为迭代的。若不使用 middle product 亦不会显著增加处理 DFT 的时间，但会消耗更多加法与乘法的时间和更精细的实现。

## 半在线卷积完成幂级数的基本操作

### 指数

求 $\exp(f)$ 考虑

$$
\mathfrak{D}(\exp(f))=\exp(f)\cdot \mathfrak{D}(f)
$$

即得。

### 倒数

求 $f^{-1}$ 考虑

$$
f\cdot f^{-1}=1
$$

那么令 $g=f^{-1}=\sum _ {i\geq 0}g_ix^i$ 和 $f=\sum _ {i\geq 0}f_ix^i$ 有

$$
g_i=
\begin{cases}
f_0^{-1},&i=0,\\
-f_0^{-1}\cdot \sum _ {j=1}^if_ig _ {i-j},&i\neq 0.
\end{cases}
$$

即得。

### 商数或对数

求 $fg^{-1}$ 考虑

$$
(fg^{-1})g=f
$$

即得。

#### 求 $f^k$

参考 fjzzq2002 的文章，考虑链式求导法则，有 $\mathfrak{D}(f^k)=\mathfrak{D}(f)\cdot k\cdot f^{k-1}$ 那么

$$
\begin{aligned}
f^k&=\smallint \left(\mathfrak{D}(f)\cdot k\cdot f^k\cdot f^{-1}\right) \\
&=\smallint \left(\mathfrak{D}(\log(f))\cdot k\cdot f^k\right)
\end{aligned}
$$

即得。这与先求一次对数再求一次指数是一样的。

## 参考文献

- van der Hoeven, J., 2003a. [New algorithms for relaxed multiplication](http://www.texmacs.org/joris/newrelax/newrelax.html). Tech. Rep. 2003–44, Universit´e Paris-Sud, Orsay, France.
- J. van der Hoeven. Relax, but don't be too lazy. JSC, 34:479–542, 2002.
- Elegia and Athekatelan. 信息学竞赛中的⽣成函数计算理论框架.
- Elegia 的讲课[视频](https://www.bilibili.com/video/BV1kA41187dQ).（约 50 分钟左右，半在线卷积的具体实现及常见幂级数算法表示为半在线卷积，$O\left(\frac{n\log ^2n}{\log \log n}\right)$）
- fjzzq2002. [一个更好的多项式模板](https://fjzzq2002.blog.uoj.ac/blog/7281).
- van der Hoeven, J., August 2003b. Relaxed multiplication using the middle product. In: Bronstein, M. (Ed.), Proc. ISSAC’03. Philadelphia, USA, pp. 143–147.