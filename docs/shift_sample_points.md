---
title: Shift Sample Points
documentation_of: ../shift_sample_points.hpp
---

## Shift via Lagrange Interpolation

Given sample points $f(0), f(1), \dots ,f(n - 1)$ of polynomial $f \in \mathbb{C}\left\lbrack x\right\rbrack$ with $\deg f \lt n$, we want to compute $f(c), f(c + 1), \dots, f(c + m - 1)$ for $c \in \mathbb{Z}, m \in \mathbb{N}$.

Recall the Lagrange interpolation formula,

$$
\begin{aligned}
f(x) &= \sum _ {0 \leq i \lt n}\left(f(i) \prod _ {0 \leq j \lt n \atop j \neq i} \frac{x - j}{i - j}\right) \\
&= \sum _ {0 \leq i \lt n}\left(f(i)\frac{\prod _ {0 \leq j \lt n \atop j \neq i}\left(x - j\right)}{\prod _ {0 \leq j \lt n \atop j \neq i}\left(i - j\right)}\right) \\
&= \sum _ {0 \leq i \lt n}\left(f(i)\frac{x!}{(x - n)!(x - i)}\frac{(-1)^{n - 1 - i}}{i!(n - 1 - i)!}\right) \\
&= \frac{x!}{(x - n)!}\sum _ {0 \leq i \lt n}\left(f(i)\frac{1}{x - i}\frac{(-1)^{n - 1 - i}}{i!(n - 1 - i)!}\right)
\end{aligned}
$$

Let

$$
\begin{aligned}
F(x) &:= \sum _ {0 \leq i \lt n}\frac{f(i)(-1)^{n - 1 - i}}{i!(n - 1 - i)!}x^i, \\
G(x) &:= \sum _ {i \geq 0}\frac{1}{c - (n - 1) + i}x^i
\end{aligned}
$$

now we have

$$
\begin{aligned}
\left\lbrack x^{n - 1 + t}\right\rbrack\left(F(x)G(x)\right) &= \sum _ {i = 0}^{n - 1 + t}\left(\left(\left\lbrack x^i\right\rbrack F(x)\right)\left(\left\lbrack x^{n - 1 + t - i}\right\rbrack G(x)\right)\right) \\
&= \sum _ {i = 0}^{n - 1}\left(\frac{f(i)(-1)^{n - 1 - i}}{i!(n - 1 - i)!}\frac{1}{c + t - i}\right) \\
&= \frac{(c + t - n)!}{(c + t)!} f(c + t)
\end{aligned}
$$

for $t = 0, 1, \dots, m - 1$. We should handle the case that $c - (n - 1) + i = 0$ for a certain $i$.

## Shift via O.g.f.

Let

$$
F(x) := \sum _ {i \geq 0}f(i)x^i \in \mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack
$$

We have $F(x) = \frac{P(x)}{(1 - x)^n}$ where $P(x) \in \mathbb{C}\left\lbrack x\right\rbrack _ {\lt n}$.

And the negative binomial coefficients are

$$
\begin{aligned}
\frac{1}{(1 - x)^n} &= (1 - x)^{-n} \\
&= \sum _ {k \geq 0}\binom{-n}{k}x^k \\
&= \sum _ {k \geq 0}\frac{(-n)(-n - 1)\cdots (-n - (k - 1))}{k!}x^k \\
&= \sum _ {k \geq 0}(-1)^k\frac{(n + k - 1)!}{(n - 1)!k!}x^k \\
&= \sum _ {k \geq 0}(-1)^k\binom{n + k - 1}{k}x^k
\end{aligned}
$$

But we are not able to compute $(-n)(-n - 1)\cdots (-n - (k - 1))$ and $k!$ fast if $k$ is large.

## Shift via Falling Factorial Polynomial

Might in another documentation.
