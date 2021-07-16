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

种取法（第一次有 $n+m$ 种取法，第二次有 $n+m-1$ 种，以此类推）。而另一种计算方式是假设第一次取了 $0$ 个黑球，第二次取了 $1$ 个黑球，以此类推，那么

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