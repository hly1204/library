## 样本点平移

给出 $f(0),f(1),\dots f(n-1)$ 求出 $f(c),f(c+1),\dots f(c+n-1)$ ，其中 $f\in\mathbb{F} _ p\lbrack x\rbrack,c\in\mathbb{F} _ p\setminus \lbrace 0\rbrace$ 。发现可使用下降幂多项式的平移完成，我们考虑拉格朗日插值公式，有

$$
\begin{aligned}
f&=\sum _ {0\leq i\lt n}f(i)\prod _ {0\leq j\lt n\land j\neq i}\frac{x-j}{i-j}\\
&=\sum _ {0\leq i\lt n}f(i)\frac{x!}{(x-n)!(x-i)}\frac{(-1)^{i-n+1}}{i!(i-n+1)!}\\
&=\frac{x!}{(x-n)!}\sum _ {0\leq i\lt n}\frac{f(i)}{x-i}\frac{(-1)^{n-1-i}}{i!(n-1-i)!}
\end{aligned}
$$
