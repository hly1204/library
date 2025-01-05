---
title: FPS as Linear Operator
documentation_of: ../fps_as_operator.hpp
---

## FPS as Linear Operator

Let $F(t) := \sum _ {j \geq 0}\frac{f _ j}{j!}t^j$ where $t = \frac{\mathrm{d}}{\mathrm{d}x}$, we want to apply $F(t)$ to $p(x) = \sum _ {j = 0}^{n - 1} p _ j x^j$. We have

$$
\begin{aligned}
F(t)p(x) &= (F(t) \bmod{t^n})p(x) \\
&= \sum _ {j = 0}^{n - 1} \frac{f _ j}{j!} p^{(j)}(x) \\
&= \sum _ {j = 0}^{n - 1}\left(\frac{f _ j}{j!}\sum _ {k = j}^{n - 1}p _ k k!\frac{x^{k - j}}{(k - j)!}\right) \\
&= \sum _ {j = 0}^{n - 1}\left(\frac{f _ j}{j!}\sum _ {k = 0}^{n - 1 - j}p _ {k + j} (k + j)!\frac{x^{k}}{k!}\right)
\end{aligned}
$$

So

$$
\begin{aligned}
\left\lbrack x^i\right\rbrack F(t)p(x) &= \sum _ {j = 0}^{n - 1}\left(\frac{f _ j}{j!} \left\lbrack x^i\right\rbrack \left(\sum _ {k = 0}^{n - 1 - j}p _ {k + j} (k + j)!\frac{x^{k}}{k!}\right)\right) \\
&= \sum _ {j = 0}^{n - 1 - i}\frac{f _ j}{j!} p _ {i + j}(i + j)!\frac{1}{i!} \\
&= \sum _ {j = 0}^{n - 1 - i}\binom{i + j}{i} f _ j p _ {i + j}
\end{aligned}
$$

for $i = 0, 1, \dots, n - 1$. We could construct $\hat p(x) := \sum _ {j = 0}^{n - 1}p _ {n - 1 - j}(n - 1 - j)!x^j$, we have

$$
\begin{aligned}
\left\lbrack x^{n - 1 - i}\right\rbrack F(x)\hat p(x) &= \sum _ {j = 0}^{n - 1 - i}\left(\left\lbrack x^j\right\rbrack F(x)\right) \left(\left\lbrack x^{n - 1 - i - j}\right\rbrack \hat p(x)\right) \\
&= \sum _ {j = 0}^{n - 1 - i}\frac{f _ j}{j!}p _ {i + j}(i + j)! \\
&= i! \sum _ {j = 0}^{n - 1 - i}\binom{i + j}{i} f _ j p _ {i + j}
\end{aligned}
$$

as desired.

## Linear Operators

The operator $\mathrm{e}^{at}$ satisfies

$$
\mathrm{e}^{at}p(x) = p(x + a)
$$

is a **translation operator**.

The **forward difference operator** is the delta operator $\mathrm{e}^{at} - 1$, where

$$
(\mathrm{e}^{at} - 1) p(x) = p(x + a) - p(a)
$$

The classical **difference operator** $\Delta = \mathrm{e}^{t} - 1$.

The **Abel operator** is the delta operator $t\mathrm{e}^{at}$, where

$$
t\mathrm{e}^{at} p(x) = p'(x + a)
$$

One can check _Advanced Linear Algebra_ by Steven Roman for more details.

Additionally, we have

$$
\mathrm{e}^{x^2t}p(x) = p\left(\frac{x}{1 - x}\right)
$$

to see this, we need the definition

$$
\mathrm{e}^{x^2 t} x = x + x^2 tx + \frac{1}{2}x^2tx^2tx + \cdots
$$

where $x^2 tx = x^2 \frac{\mathrm{d}}{\mathrm{d}x}x = x^2$ and $x^2tx^2tx = x^2tx^2=2x^3$, so

$$
\mathrm{e}^{x^2 t} x = x + x^2 + x^3 + \cdots = \frac{x}{1 - x}
$$

## References

1. 李⽩天. 信息学竞赛中的生成函数计算理论框架. 2021 年信息学奥林匹克中国国家集训队论文. url: <https://github.com/OI-wiki/libs/tree/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87>
2. Steven Roman. Advanced Linear Algebra (Graduate Texts in Mathematics). url: <https://link.springer.com/book/10.1007/978-0-387-72831-5>
3. 飞雨烟雁. 论线性算法的关系：分式分解、基变换与偏序集. url: <https://www.luogu.com/article/ft2eejw9>
4. StackExchange. Formal Power Series as Linear Operators. url: <https://math.stackexchange.com/questions/1958491/formal-power-series-as-linear-operators>
