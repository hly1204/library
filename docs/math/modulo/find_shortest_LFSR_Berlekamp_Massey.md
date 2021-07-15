## linear feedback shift register

简称 LFSR 。对于一个长度为 $L$ 的 LFSR 和 $L$ 个初值 $s_0,s_1,\dots ,s_{L-1}$ 有

$$
s_j=-\sum_{i=1}^Lc_is_{j-i},\quad j=L,L+1,L+2,\dots
$$

其中 $c_i$ 都在同一个域中，或是有限域 $\mathbb{F} _ p,p\text{ is prime}$ 或是无限域如 $\mathbb{R}$ 。

对于一个序列 $s_0,s_1,\dots ,s_{N-1}$ 当 $L\lt N$ 时，当且仅当

$$
s_j+\sum_{i=1}^Lc_is_{j-1}=0
$$

时 LFSR 才能生成这个序列。

需要注意的是 Sugiyama 等指出扩展 Euclid 算法和 Berlekamp-Massey 算法在该处应用是等价的。

### 定理 1

对于一个长为 $L$ 的 LFSR 能够生成序列 $s_0,s_1,\dots ,s _ {N-1}$ 但是不能够生成 $s_0,s_1,\dots ,s_N$ 那么能够生成后者的 LFSR 长度为 $L'$ 满足

$$
L'\geq N+1-L\tag{3}
$$

*证明*：对于 $L\geq N$ 显然正确，所以我们假设 $L\lt N$ 。令 $c_1,c_2,\dots ,c_L$ 和 $c_1',c_2',\dots ,c _ {L'}'$ 为这两个 LFSR 相关的系数，并且我们假设 $L'\leq N-L$ 通过这个假设有

$$
-\sum _ {i=1}^Lc_is _ {j-i}
\begin{cases}
=s_j,\quad j=L,L+1,\dots ,N-1\\
\neq s_N
\end{cases}
\tag{4}
$$

和

$$
-\sum _ {k=1}^{L'}c_k's _ {j-k}=s_j,\quad j=L',L'+1,\dots N
\tag{5}
$$

因此

$$
\begin{aligned}
-\sum _ {i=1}^Lc_is _ {N-i}&=
\sum _ {i=1}^Lc_i(-s_{N-i})\\
&=+\sum _ {i=1}^Lc_i\sum _ {k=1}^{L'}c_k's _ {N-i-k}
\end{aligned}
\tag{6}
$$

交换求和顺序有

$$
\begin{aligned}
-\sum _ {i=1}^Lc_is _ {N-i}&=
\sum _ {k=1}^{L'}c_k'\sum _ {i=1}^Lc_is _ {N-k-i}\\
&=-\sum _ {k=1}^{L'}c_k's _ {N-k}\\
&=s_N
\end{aligned}
\tag{7}
$$

注意 $(6)$ 仅当 $L'\leq N-L$ 时右式中的 $-s _ {N-i}$ 才能被替换为 $(5)$ 。因为

$$
\lbrace s _ {N-L},s _ {N-l+1},\dots ,s _ {N-1}\rbrace \subset\lbrace s _ {L'},s _ {L'+1},\dots ,s _{N-1}\rbrace
$$

我们发现如果 $L'\gt N-L$ 那么右式中的 $-s _ {N-L}$ 需要由 $s _ {N-L-L'}$ 到 $s _ {N-L-1}$ 来生成，而前者的下标为负数，这是我们所没有定义的，显然不能列出这样的等式！

而 $(7)$ 推翻了我们的假设 $(4)$ 说明了 $L'\leq N-L$ 是站不住脚的。我们断定 $L'\geq N+1-L$ 。

现在让我们令 $s$ 为一个无限序列 $s_0,s_1,\dots$ 且 $s_0,s_1,\dots ,s _ {N-1}$ 形成了 $s$ 的前 $N$ 位。我们定义 $L_N(s)$ 为所有生成 $s_0,s_1,\dots ,s _ {N-1}$ 的最短长度。根据上文有 $L_N(s)\leq N$ 且随着 $N$ 的增长 $L_N(s)$ 是单调不减的。我们约定一个全部为零的序列由 $L=0$ 长度的 LFSR 生成，因此 $L_N(s)=0$ 当且仅当 $s_0,s_1,\dots ,s _ {N-1}$ 都为零。

### 引理 1

设长度为 $L_N(s)$ 的 LFSR 生成 $s_0,s_1,\dots ,s _ {N-1}$ 且该 LFSR 的长度是最短的，但不能生成 $s_0,s_1,\dots ,s_N$ 那么

$$
L_{N+1}(s)\geq \max(L_N(s),N+1-L_N(s))
$$

*证明*：因为我们假设其为最短的，那么若 $L _ {N+1}(s)\lt L_N(s)$ 显然违背我们的假设（此处不难看出其单调不减的性质），结合定理 1 。 $\square$

## Berlekamp 算法

我们先定义一个 LFSR 的关系多项式为

$$
C(D)=1+c_1D+c_2D^2+\cdots +c_LD^L
\tag{8}
$$

度数最高为 $L$ 且对于长度 $L=0$ 的 LFSR 我们令 $C(D)=1$ 。

当 $s_0,s_1,\dots ,s _ {N-1}$ 都为零但 $s_N\neq 0$ 时 $L _ {N+1}(s)=N+1$ 。

对于一个给定的 $s$ ，我们令

$$
C^{(N)}(D)=1+c_1^{(N)}D+\cdots +c _ {L_N(s)}^{(N)}D^{L_N(s)}
\tag{9}
$$

为最短长度 $L_N(s)$ 的 LFSR 生成 $s_0,s_1,\dots ,s _ {N-1}$ 。

对于 $N=1,2,\cdots ,n$ 我们假设已经得到长为 $L_N(s)$ 的 $C^{(N)}(D)$ ，那么

$$
s_j+\sum _ {i=1}^{L_n(s)}c_i^{(n)}s _ {j-i}=
\begin{cases}
0&j=L_n(s),\dots ,n-1\\
d_n&j=n
\end{cases}
\tag{10}
$$

其中 $d_n$ 我们成为 next discrepancy 即 $s_n$ 和由当前最短 LFSR 生成的第 $(n+1)$ 个数之间的差异。

当 $d_n=0$ 时，该 LFSR 也能生成 $s_n$ ，所以 $L _ {n+1}(s)=L_n(s)$ ，所以我们可以取 $C^{n+1}(D)=C^{(n)}(D)$ 。

当 $d_n\neq 0$ 时则需要寻找一个新的 LFSR 来生成 $s$ 的前 $(n+1)$ 个数。我们令 $m$ 为在上一次长度变化之前的最短 LFSR 的长度即

$$
\begin{aligned}
L_m(s)&\lt L_n(s)\\
L _ {m+1}(s)&=L_n(s)
\end{aligned}
\tag{11}
$$

因为上一次长度变化了，所以 $C^{(m)}(D)$ 无法生成 $s_0,s_1,\dots ,s_m$ ，因此由 $(2)$ 我们有

$$
s_j+\sum _ {i=1}^{L_m(s)}c_i^{(m)}s _ {j-i}=
\begin{cases}
0&j=L_m(s),\dots ,m-1\\
d_m\neq 0&j=m
\end{cases}
\tag{12}
$$

而因为引理 1 所以

$$
L _ {m+1}(s)=L_n(s)=\max(L_m(s),m+1-L_m(s))
$$

而由于 $(11)$ 有

$$
L_n(s)=m+1-L_m(s)
\tag{13}
$$

我们现在确认了关系多项式

$$
C(D)=C^{(n)}(D)-d_nd_m^{-1}D^{n-m}C^{(m)}(D)
\tag{14}
$$

是 $C^{(n+1)}(D)$ 的一个合法选项。注意 $(14)$ 中 $C(D)$ 的度数最大为

$$
\max(L_n(s),n-m+L_m(s))=\max(L_n(s),n+1-L_n(s))
$$

因此 $C(D)$ 是一个长度为 $L$ 的 LFSR 的可接受的关系多项式其中

$$
L=\max(L_n(s),n+1-L_n(s))
\tag{15}
$$

而根据 $(14)$ 有

$$
\begin{aligned}
s_j+\sum _ {i=1}^Lc_is _ {j-i}&=
s_j+\sum _ {i=1}^{L_n(s)}c_i^{(n)}s _ {j-i}-d_nd_m^{-1}
\left(
s _ {j-n+m}+\sum _ {i=1}^{L_m(s)}c_i^{(m)}s _ {j-n+m-i}
\right)\\
&=
\begin{cases}
0&j=L,L+1,\dots ,n-1\\
d_n-d_nd_m^{-1}d_m=0&j=n
\end{cases}
\end{aligned}
$$

### 定理 2

如果某个长为 $L_N(s)$ 的 LFSR 生成了 $s_0,s_1,\dots ,s_{N-1}$ 也生成了 $s_0,s_1,\dots ,s_N$ 那么 $L_{N+1}(s)=L_N(s)$ 。

相反的，如果某个长为 $L_N(s)$ 的 LFSR 生成了 $s_0,s_1,\dots ,s_{N-1}$ 但不能生成 $s_0,s_1,\dots ,s_N$ 那么 $L_{N+1}(s)=\max(L_N(s),N+1-L_N(s))$ 。

下面给出了相关的算法及证明，但这里略去。

事实上该算法不仅可以找到一个最短 LFSR 也能找到所有最短 LFSR 。如果某个长为 $L_N(s)$ 的 LFSR 生成了 $s_0,s_1,\dots ,s_{N-1}$ 但不能生成 $s_0,s_1,\dots ,s_N$ 那么当且仅当 $2L_N(s)\leq N$ 时才会发生长度变化。这说明了最短 LFSR 是唯一的当且仅当 $2L_N(s)\leq N$ 。因此当算法在 $2L\gt n$ 时终止时结果的最短 LFSR 是不唯一的。定理 3 告诉我们这些多项式的集合为

$$
\lbrace
C(D)+Q(D)D^xB(D)\mid \deg(Q(D))\lt 2L-n
\rbrace
$$

其中一些记号可见原文的伪代码。

#### 关系多项式与最小多项式

我们可以发现关系多项式这样定义实际是为了方便，不需要在数组的开头进行插入操作，而其翻转实际上就是最小多项式了（零化这个序列）。

## 参考文献

- J.L. Massey, Shift register synthesis and BCH decoding, IEEE Trans. Inform. Theory, vol. IT-15,
122–127 (1969).
- J.L. Dornstetter, On the equivalence Between Berlekamp’s and Euclid’s Algorithm, IEEE Trans.
Inform. Theory, vol. IT-33, no 3,428–431 (1987).
- Y. Sugiyama, M. Kasahara, H. Hirasawa, and T. Namekawa, “A method for solving key equation for decoding Goppa codes,” Inform. Contr., vol. 27, pp. 87-99, 1975.