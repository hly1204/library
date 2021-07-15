## 多项式多点求值

多点求值即 $\operatorname{eval}:\mathbb{F} _ p\lbrack x\rbrack\to \mathbb{F} _ p^n,f\mapsto (f(x_0),f(x_1),\dots ,f(x_{n-1}))$ 我们假设多项式 $f\in\mathbb{F} _ p\lbrack x\rbrack$ 有 $O(\deg (f))=O(n)$ 。我们可以通过分治取模的来计算。建立一棵 subproduct 树，树的叶子为 $x-x_i$ 而其余节点为叶子的乘积，而 FFT 的思想显然与此相同，为了简便可以使用线段树的递归建树方式。其中 $f(x_i)=f\bmod(x-x_i)$ 显然。

## 拉格朗日插值

插值即解同余方程组

$$
\begin{cases}
f\bmod (x-x_0)=y_0\\
f\bmod (x-x_1)=y_1\\
\vdots \\
f\bmod (x-x _ {n-1})=y _ {n-1}
\end{cases}
$$

其中对于 $\forall i\neq j$ 有 $x_i\neq x_j$ 。

令

$$
M=\prod _ {0\leq i\lt n}(x-x_i)\\
M_i=\frac{M}{x-x_i}\\
N_i=M_i^{-1}\bmod(x-x_i)=\prod _ {j\neq i}\frac{1}{x_i-x_j}
$$

那么

$$
f\equiv \sum _ {0\leq i\lt n}y_iM_iN_i\pmod{M}
$$

因为任取 $0\leq k\lt n$ 都满足

$$
f=y_k+\sum _ {i\neq k}y_iM_iN_i\pmod{(x-x_k)}
$$

后式中 $M_i$ 显然是 $x-x_k$ 的倍式所以同余零，得证。

稍加整理即

$$
f\equiv \sum _ {0\leq i\lt n}f(x_i)\prod  _ {j\neq i}\frac{x-x_j}{x_i-x_j}\pmod{M}
$$

观察到

$$
M'=\sum _ {0\leq i\lt n}\frac{M}{x-x_i}\\
M'(x_i)=\lim _ {x\to x_i}\frac{M(x)-M(x_i)}{x-x_i}=\lim _ {x\to x_i}\frac{M(x)}{x-x_i}=N_i^{-1}
$$

令

$$
M_a=\prod _ {0\leq i\lt \left\lfloor n/2\right\rfloor}(x-x_i)\\
M_b=\prod _ {\left\lfloor n/2\right\rfloor\leq i\lt n}(x-x_i)\\
f_a=\sum _ {0\leq i\lt \left\lfloor n/2\right\rfloor}y_iN_i\frac{M_a}{x-x_i}\\
f_b=\sum _ {\left\lfloor n/2\right\rfloor\leq i\lt n}y_iN_i\frac{M_b}{x-x_i}
$$

那么

$$
f\equiv f_aM_b+f_bM_a\pmod{M}
$$

可分治计算。

## 高速化

该算法有必要高速化吗？好像没有，因为有更快的转置算法，但是依然在这里指出我们只需在维护 subproduct 树的同时维护树中多项式对应的 DFT 发现如果要做乘法，那么上一次的 DFT 的一半是可用的，意味着只需要额外做另一半长度的 DFT ，而在插值时我们将多项式描述为一个线性组合，注意这里 `a*b+c*d` 中的加法也可以在 DFT 下运算，不维护其系数直接维护 DFT 即可。