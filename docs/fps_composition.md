---
title: Formal Power Series Composition
documentation_of: ../fps_composition.hpp
---

## Composition of formal power series

We are given $f\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack,g\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$, and we want to compute $f(g)\bmod{x^n}$.

It is possible to compute $f(g)$ if $f,g\in\mathbb{C}\left\lbrack x\right\rbrack$, since each coefficient of $f(g)$ is a sum of finitely many terms. But if $f,g\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$ then $g(0)=0$ is required.

### Kinoshita–Li's algorithm

Let $f(x):=\sum _ {j = 0}^{n - 1}f _ j x^j$, we have

$$
f(g)=\sum _ {j \geq 0}f _ j g(x)^j
$$

Consider the bivariate formal Laurent series in $x,y$ over $\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack\left(\left(y\right)\right)$

$$
f(g)=\left\lbrack y^0\right\rbrack\frac{f\left(y^{-1}\right)}{1 - y\cdot g(x)} = \sum _ {j\geq 0}\left(\left(\cdots + f _ j y^{-j} + \cdots \right)y^j\cdot g(x)^j\right)
$$

since we only need to compute $f(g)\bmod{x^n}$, it's okay to treat $g(x)$ as a polynomial. Unlike Kinoshita and Li's paper, I don't want to manipulate in formal power series ring by multiplying $\frac{f\left(y^{-1}\right)}{1 - y\cdot g(x)}$ by $y^{n-1}$. If we did so, we may care about the parity of $n-1$.

Kinoshita–Li's algorithm is actually a bivariate variant of Bostan–Mori's algorithm, we have

$$
\begin{aligned}
\frac{P\left(y\right)}{Q\left(x,y\right)}\bmod{x^n}&=\left(\frac{P\left(y\right)}{Q\left(x,y\right)Q\left(-x,y\right)}\bmod{x^n}\right)Q\left(-x,y\right)\bmod{x^n} \\
&=\left(\frac{P(y)}{V\left(x^2,y\right)}\bmod{x^n}\right)Q\left(-x,y\right)\bmod{x^n} \\
&=\left.\left(\frac{P(y)}{V(z,y)}\bmod{z^{\left\lceil n/2\right\rceil}}\right)\right|_{z=x^2}Q\left(-x,y\right)\bmod{x^n}
\end{aligned}
$$

where $V\left(x^2,y\right)=Q(x,y)Q(-x,y)$. We can solve the problem when $n=1$, since now we only need to compute $\frac{P(y)}{Q(x,y)}\bmod{x}=\frac{P(y)}{Q(0,y)}\in\mathbb{C}\left(\left( y\right)\right)$. Actually we do not need to compute $\frac{1}{Q(0,y)}$, since it's just $\left(1-g(0)y\right)^{-k}\in\mathbb{C}\left\lbrack\left\lbrack y\right\rbrack\right\rbrack$ for a certain $k\in\mathbb{N}$, the coefficients of which are known as the binomial coefficients multiplied by some powers of $g(0)$. (noshi91 told me on twitter, I did't noticed that.)

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{KinoshitaLi}}\left(P(y),Q(x,y),n,m\right)\text{:} \\
&\textbf{Input}\text{: }P=\sum_{0\leq j< n}p_jy^{-j}\in\mathbb{C}((y)),Q\in\mathbb{C}\left\lbrack x,y\right\rbrack ,n,m\in\mathbb{N}_{>0}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack y^{\left(-m,0\right\rbrack}\right\rbrack\dfrac{P(y)}{Q(x,y)}\bmod{x^n}\text{.} \\
&\textbf{Require}\text{: }\left\lbrack x^0y^0\right\rbrack Q=1\text{.} \\
1&\textbf{if }n=1\textbf{ then return }\begin{bmatrix}\left\lbrack y^{-m+1}\right\rbrack\frac{P(y)}{Q(0,y)} & \cdots & \left\lbrack y^0\right\rbrack\frac{P(y)}{Q(0,y)}\end{bmatrix} \\
2&V(x^2,y)\gets Q(x,y)Q(-x,y)\bmod{x^n} \\
3&d\gets\deg_y Q\left(-x,y\right)\\
4&\begin{bmatrix} t_{-(m+d)+1} & \cdots & t_0\end{bmatrix}\gets \operatorname{\mathsf{KinoshitaLi}}\left(P(y),V(x,y),\left\lceil n/2\right\rceil,m+d\right) \\
5&T(x,y)\gets \sum_{j=-(m+d)+1}^0t_jy^j \\
6&U(x,y)=\sum_{j=-(m+d)+1}^d u_jy^j\gets T(x^2,y)Q(-x,y)\bmod{x^n} \\
7&\textbf{return }\begin{bmatrix}u_{-m+1} & \cdots & u_0\end{bmatrix}
\end{array}
$$

Kinoshita–Li's algorithm is simple and elegant.

TODO: optimization of this algorithm.

## References

1. Yasunori Kinoshita, Baitian Li. Power Series Composition in Near-Linear Time. FOCS 2024. url: <https://arxiv.org/abs/2404.05177>

2. Alin Bostan, Ryuhei Mori. A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence. SOSA 2021: 118-132 url: <https://arxiv.org/abs/2008.08822>

3. R. P. Brent and H. T. Kung. 1978. Fast Algorithms for Manipulating Formal Power Series. J. ACM 25, 4 (Oct. 1978), 581–595. url: <https://doi.org/10.1145/322092.322099>

4. Faster polynomial multiplication via multipoint Kronecker substitution. J. Symb. Comput. 44(10): 1502-1510 (2009) url: <https://doi.org/10.1016/j.jsc.2009.05.004>

5. Alin Bostan, Bruno Salvy, Éric Schost. Power series composition and change of basis. ISSAC 2008: 269-276 url: <https://arxiv.org/abs/0804.2337>
