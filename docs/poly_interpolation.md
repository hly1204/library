---
title: Polynomial Interpolation (Lagrange Interpolation)
documentation_of: ../poly_interpolation.hpp
---

## Lagrange Interpolation

Given sample points $f(0), f(1), \dots ,f(n - 1)$ of polynomial $f \in \mathbb{C}\left\lbrack x\right\rbrack$ with $\deg f \lt n$, we want to compute $f(c)$ for $c \in \mathbb{Z}$.

Recall the Lagrange interpolation formula,

$$
f(x) = \sum _ {0 \leq i \lt n} f(i) \prod _ {0 \leq j \lt n \atop j \neq i} \frac{x - j}{i - j}
$$

and let $k_i := \frac{f(i)}{i!} \prod _ {0 \leq j \lt i}(x - j)$ for some $i$, we have

$$
f(x) = \sum _ {0 \leq i \lt n} k_i \frac{(-1)^{n - 1 - i}}{(n - 1 - i)!} \prod _ {i \lt j \lt n}(x - j).
$$

### C-recursive sequence

The O.g.f. of $\left(f(j)\right) _ {j \geq 0}$ is

$$
F(x) = \sum _ {j \geq 0} f(j) x^j
$$

Let's introduce the difference operator $\Delta : f(x) \mapsto f(x+1) - f(x)$, notice that $\deg \left(\Delta f(x)\right) \lt n-1$, so $\Delta^n f(x)=0$. Now we have

$$
\begin{aligned}
(1-x)F(x)-f(0) &= x\sum _ {j\geq 0}\left(\Delta f(j)\right)x^j \\
(1-x)\left((1-x)F(x)-f(0)\right)-x\Delta f(0) &= x^2 \sum _ {j\geq 0}\left(\Delta^2 f(j)\right)x^j
\end{aligned}
$$

since $\Delta^n f(x)=0$, we know $\deg\left(\left(1-x\right)^n F(x)\right) \lt n$, which is saying that

$$
F(x)=\frac{P(x)}{(1-x)^n},\qquad P\in\mathbb{C}\left\lbrack x\right\rbrack _ {\lt n}.
$$
