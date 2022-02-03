## 样本点平移

给出 $f(0),f(1),\dots f(n)$ 求出 $f(c),f(c+1),\dots f(c+n)$ ，其中 $f\in\mathbb{F} _ p\lbrack x\rbrack,c\in\mathbb{F} _ p\setminus \lbrace 0\rbrace ,\deg(f)\leq n$ 。发现可使用下降幂多项式的平移完成，我们考虑拉格朗日插值公式，有

$$
\begin{aligned}
f(x)&=\sum _ {0\leq i\leq n}f(i)\prod _ {0\leq j\leq n\land j\neq i}\frac{x-j}{i-j}\\
&=\sum _ {0\leq i\leq n}f(i)\frac{x!}{(x-n-1)!(x-i)}\frac{(-1)^{n-i}}{i!(n-i)!}\\
&=\frac{x!}{(x-n-1)!}\sum _ {0\leq i\leq n}\frac{f(i)}{(x-i)}\frac{(-1)^{n-i}}{i!(n-i)!}
\end{aligned}
$$

上式虽然是一个卷积形式但是 $x-i$ 在分母上可能为零，故该方法有局限性，我们假设 $\lbrace 0,1,\dots ,n\rbrace \cap\lbrace c,c+1,\dots c+n\rbrace =\emptyset$ 那么此时令

$$
A(x)=\sum _ {0\leq i\leq n}\frac{f(i)(-1)^{n-i}}{i!(n-i)!}x^i,\quad B(x)=\sum _ {i\geq 0}\frac{1}{c-n+i}x^i
$$

那么对于 $t\geq 0$ 有

$$
\begin{aligned}
\lbrack x^{n+t}\rbrack (A(x)B(x))&=\sum _ {i=0}^{n+t}\lbrack x^i\rbrack A(x)\lbrack x^{n+t-i}\rbrack B(x)\\
&=\sum _ {i=0}^{n}\frac{f(i)(-1)^{n-i}}{i!(n-i)!}\frac{1}{c+t-i}\\
&=\frac{(c+t-n-1)!}{(c+t)!}f(c+t)
\end{aligned}
$$

也就是说我们可以求出 $f(c),f(c+1),\dots $ 只要 $B(x)$ 足够“长”且不要导致分母为零的话上述算法是正确的。

另外注意到求单个点值的时间是 $O(n)$ 的，学习了叉姐的代码后，我们可以在第一次循环时维护

$$
k_i=\frac{f(i)}{i!}\prod _ {0\leq j\lt i}(x-j)
$$

此时循环为从 $0$ 到 $n$ ，第二次倒过来将上式中缺失的部分补全即可，也就是计算

$$
f(x)=\sum _ {0\leq i\leq n}k_i\cdot\frac{(-1)^{n-i}}{(n-i)!}\prod _ {i\lt j\leq n}(x-j)
$$

如果从 $n$ 到 $0$ 枚举，那么 $-1$ 的指数一定是从 $0$ 开始，那么维护一个变量每次乘以 $-1$ 。

## 等差数列

沿用上述问题，对于 $k\in\mathbb{F} _ p^{\times}$ 和 $d\in\mathbb{F} _ p$ 给出 $f(d),f(d+k),\dots ,f(d+nk)$ 求出 $f(c+d),f(c+d+k),\dots ,f(c+d+nk)$ 也是类似的，可视作平移 $g(x)=f(d+kx)$ 的点值 $g(0),g(1),\dots ,g(n)$ 为 $g\left(\frac{c}{k}\right),g\left(\frac{c}{k}+1\right),\dots ,g\left(\frac{c}{k}+n\right)$ 。