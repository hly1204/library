## chirp z 变换

也被称为 Bluestein 算法，我们使用标题的称呼。

对于 $A(x)=\sum _ {i=0}^na_ix^i\in\mathbb{F} _ p\lbrack x\rbrack$ 。我们希望得到 $A(1),A(c^2),A(c^4),\dots$ 其中 $c\in\mathbb{F} _ p^\times$ 那么可以通过将 $A_0(x)=\sum _ {i\geq 0}a_ic^{i^2}x^i$ （对于 $\forall j\gt n$ 令 $a_j=0$ ）与 $B_0(x)=\sum _ {i\geq 0}c^{-(i-n)^2}x^i$ 相乘得到，有

$$
\begin{aligned}
\lbrack x^{k}\rbrack (A_0(x)B_0(x))&=\sum _ {i=0}^{k}\left(\lbrack x^i\rbrack A_0(x)\right)\left(\lbrack x^{k-i}\rbrack B_0(x)\right)\\
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

而对于 $A(c),A(c^3),\dots $ 可构造 $A(cx)$ 后同理，因为我们从 $x^n$ 开始提取系数，所以可以使用循环卷积。

### 使用组合数作为指数

仍考虑上述问题，若将上面算法中的指数除以二，我们就能得到一个一次卷积即可计算 $A(1),A(c),A(c^2),\dots $ 的算法，但是会导致指数可能为小数。在数论变换中有时候没办法计算，此时考虑

$$
ki=\binom{i+k}{2}-\binom{i}{2}-\binom{k}{2}
$$

那么

$$
A(c^k)=c^{-\binom{k}{2}}\sum _ {i=0}^n\left(a_ic^{-\binom{i}{2}}\right)\left(c^{\binom{i+k}{2}}\right)
$$

是一个“减法卷积”，那么构造 $A_0(x)=\sum _ {i}a_{n-i}c^{-\binom{n-i}{2}}x^i$ （对于 $\forall j\gt n\lor j\lt 0$ 令 $a_j=0$ ）和 $B_0(x)=\sum _ {i\geq 0}c^{\binom{i}{2}}x^i$ 那么对于 $t\geq 0$ 有

$$
\begin{aligned}
\lbrack x^{n+t}\rbrack (A_0(x)B_0(x))&=\sum _ {i=0}^{n+t}\left(\lbrack x^{n+t-i}\rbrack A_0(x)\right)\left(\lbrack x^{i}\rbrack B_0(x)\right)\\
&=\sum _ {i=0}^{n+t}a_{i-t}c^{\binom{i}{2}-\binom{i-t}{2}}\\
&=\sum _ {i=-t}^na_ic^{\binom{i+t}{2}-\binom{i}{2}}\\
&=c^{\binom{t}{2}}\cdot A(c^t)
\end{aligned}
$$

可以用一次多项式乘法完成。另外 $\forall i\geq 2$ 有 $c^{\binom{i+1}{2}}=c^{\binom{i}{2}}\cdot c^i$ 。