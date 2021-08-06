<!-- ## 在线卷积

设存在 $f=\sum _ {i=0}^{n-1}f_iz^i$ 和 $g=\sum _ {i=0}^{n-1}g_iz^i$ 且 $f,g\in \mathbb{C}\lbrack z\rbrack$ ，我们知道 $\operatorname{FFT} _ n(f)\in \mathbb{C}^n$ 那么定义以下变换

$$
\operatorname{FFT} _ n(f)=(f(1), f(\zeta_n),\dots ,f(\zeta_n^{n-1}))
$$

且 $\operatorname{FFT} _ n^{-1}:\mathbb{C}^n\to \mathbb{C}\lbrack \lbrack z\rbrack \rbrack _ n$ 。

使用记号 $\mathbb{C}\lbrack \lbrack z\rbrack \rbrack _ n\subseteq \mathbb{C}\lbrack z\rbrack \subseteq \mathbb{C}\lbrack \lbrack z\rbrack \rbrack$ 表示 truncated 幂级数。

在这里令 $f _ {a\dots b}=f_a+f _ {a+1}z+\cdots +f _ {b-1}z^{b-a}\in \mathbb{C}\lbrack \lbrack z\rbrack \rbrack _ {b-a}$ 且有如下定义

> 定义 5 ：我们称
>
> $$
> P=f _ {0\dots n}g _ {0\dots n}\tag{2}
> $$
>
> 为 $f$ 和 $g$ 的 $n$ 阶的 full product 。

> 定义 6 ：我们称
>
> $$
> P=\sum _ {i+j\lt n}(f_ig_j)z^{i+j}\tag{3}
> $$
> 
> 为 $f$ 和 $g$ 的 $n$ 阶的 truncated product 。

> 定义 7 ：一个 full (or truncated) 离线的 $f$ 和 $g$ 的 $n$ 阶乘法为输入 $f_0,\dots ,f _ {n-1}$ 和 $g_0,\dots ,g _ {n-1}$ 并输出 $(2)$ （或 $(3)$ ）。

> 定义 8 ：一个 full (or truncated) 在线的 $f$ 和 $g$ 的 $n$ 阶乘法为连续输入 $(f_0,g_0),\dots ,(f _ {n-1},g _ {n-1})$ 并连续计算 $P_0, \dots ,P _ {2n-2}$ （或 $P_0, \dots ,P _ {n-1}$ ）。在这里 $P_i$ 须在 $(f_0,g_0),\dots ,(f_i,g_i)$ 已经得到后立即输出。

> 定义 9 ：一个 full (or truncated) 半在线的 $f$ 和 $g$ 的 $n$ 阶乘法为输入 $g_0, \dots ,g _ {n-1}$ 和连续输入 $f_0,\dots ,f _ {n-1}$ 并连续计算 $P_0, \dots ,P _ {2n-2}$ （或 $P_0, \dots ,P _ {n-1}$ ）。在这里 $P_i$ 须在 $f_0,\dots ,f_i$ 已经得到后立即输出。

在线算法的主旨是预料将来的计算。更准确的说，如果我们想在线计算 $f$ 和 $g$ 的 full product ，那么只要当 $f_0,\dots ,f_i$ 和 $g_0,\dots ,g_i$ 已知，对于 $0\leq j,k\leq i$ 计算 $f_jg_k$ 对 $P$ 的贡献是可能的，尽管对于 $j+k\gt i$ 而言 $f_jg_k$ 的贡献暂时还不需要。之后的想法是将这个问题划分为更多的子问题对 $P$ 的贡献，而子问题可以用离线算法解决。

不妨考虑在线的 $2n$ 阶的乘法

$$
P=f _ {0\dots 2n}g _ {0\dots 2n}
$$

我们可以写成

$$
P=P _ {0,0}+P _ {0,1}z^n+P _ {1,0}z^n + P _ {1,1}z^{2n}
$$

为四个 $n$ 阶的乘法

$$
\begin{aligned}
P _ {0,0}&=f _ {0\dots n}g _ {0\dots n}\\
P _ {0,1}&=f _ {0\dots n}g _ {n\dots 2n}\\
P _ {1,0}&=f _ {n\dots 2n}g _ {0\dots n}\\
P _ {1,1}&=f _ {n\dots 2n}g _ {n\dots 2n}
\end{aligned}
$$

现在 $P _ {0,0}$ 显然是一个 $n$ 阶的在线乘法，但是 $P _ {0,1}$ 是半在线的，因为在需要 $P _ {0,1}$ 时， $f_0,\dots ,f _ {n-1}$ 和 $g_0,\dots ,g _ {n-1}$ 都是已知的。类似的， $P _ {1,0}$ 也是半在线的，而 $P _ {1,1}$ 是离线的。

而半在线算法也是类似的。

## 参考文献

- van der Hoeven, J., 2003a. [New algorithms for relaxed multiplication](http://www.texmacs.org/joris/newrelax/newrelax.html). Tech. Rep. 2003–44, Universit´e Paris-Sud, Orsay, France.
- J. van der Hoeven. Relax, but don't be too lazy. JSC, 34:479–542, 2002.
 -->
