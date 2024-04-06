---
title: Formal Power Series Composition (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack \rbrack$ for FFT prime $p$)
documentation_of: ./fps_composition.hpp
---

## Pseudocode

I also have a blog at [Codeforces](https://codeforces.com/blog/entry/127674) without more details.

### Composition of Formal Power Series

For the composition problem, we have

$$
\frac{f(y^{-1})}{1-yg(x)}=\sum_{k\geq 0}(\cdots +f_ky^{-k}+\cdots)y^kg(x)^k
$$

Our goal is computing $\left\lbrack y^0\right\rbrack\dfrac{f(y^{-1})}{1-yg(x)}\bmod{x^n}$.

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{Composition-Subprocedure}(P,Q,n)\text{:} \\
&\textbf{Input}\text{: }P=\sum_{0\leq j\leq n}p_jy^{-j}\in\mathbb{C}((y)),Q\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack\left\lbrack y\right\rbrack\text{.} \\
&\textbf{Output}\text{: }\left\lbrack y^{\left\lbrack -\deg_y(Q)+1,0\right\rbrack}\right\rbrack\dfrac{P}{Q}\bmod{x^{n+1}}\text{.} \\
1&d\gets \deg_y(Q)\\
2&\textbf{if }n=0\textbf{ then return }\left(\left\lbrack y^{-d+1}\right\rbrack P/Q,\dots ,\left\lbrack y^0\right\rbrack P/Q\right) \\
3&V(x^2,y)\gets Q(x,y)Q(-x,y)\bmod{x^{n+1}} \\ 4&(t_{-2d+1},\dots ,t_0)\gets \operatorname{Composition-Subprocedure}\left(P,V(x,y),\left\lfloor n/2\right\rfloor\right) \\
5&T(x,y)\gets \sum_{j=-2d+1}^0t_jy^j \\
6&U(x,y)=\sum_{j=-2d+1}^d u_jy^j\gets T(x^2,y)Q(-x,y)\bmod{x^{n+1}} \\
7&\textbf{return }\left(u_{-d+1},\dots ,u_0\right)
\end{array}
$$

and 

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{Composition}(f,g,n)\text{:} \\
&\textbf{Input}\text{: }f,g\in\mathbb{C}\left\lbrack x\right\rbrack ,n\in\mathbb{Z}_{>0}\text{.} \\
&\textbf{Output}\text{: }f(g)\bmod{x^n}\text{.} \\
1&(u)\gets\operatorname{Composition-Subprocedure}\left(f\left(y^{-1}\right),1-yg(x),n-1\right) \\
2&\textbf{return }(u)
\end{array}
$$

### Compositional Inverse of Formal Power Series

For the compositional inverse problem, we have

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{Enum-}k\operatorname{th-Term-of-Power}(f,k,n)\text{:} \\
&\textbf{Input}\text{: } f\in \mathbb{C}\left\lbrack x\right\rbrack,k,n\in\mathbb{Z}_{\geq 0}\text{.} \\
&\textbf{Output}\text{: }\left(\left\lbrack x^k\right\rbrack f^0,\left\lbrack x^k\right\rbrack f,\left\lbrack x^k\right\rbrack f^2,\dots ,\left\lbrack x^k\right\rbrack f^{n-1}\right)\text{.} \\
1&P(x,y)\gets 1 \\
2&Q(x,y)\gets 1-yf \\
3&\textbf{while }k\neq 0\textbf{ do}\text{:} \\
4&\qquad U_0(x^2,y)+xU_1(x^2,y)\gets P(x,y)Q(-x,y) \\
5&\qquad V(x^2,y)\gets Q(x,y)Q(-x,y) \\
6&\qquad P\gets U_{k\bmod{2}}(x,y) \bmod{x^{\left\lfloor k/2\right\rfloor +1}} \\
7&\qquad Q\gets V(x,y) \bmod{x^{\left\lfloor k/2\right\rfloor +1}} \\
8&\qquad k\gets \left\lfloor k/2\right\rfloor \\
9&\textbf{end while} \\
10&A(y)=\sum_{j=0}^{n-1}a_jy^j\gets P/Q\bmod{y^n} \\
&P,Q \text{ are univariate polynomial with }Q(0)=1 \\
11&\textbf{return }(a_0,\dots ,a_{n-1})
\end{array}
$$

and

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{Compositional-Inverse}(f,n)\text{:} \\
&\textbf{Input}\text{: }f\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack, f'(0)\neq 0,n\in\mathbb{Z}_{\geq 2}\text{.} \\
&\textbf{Output}\text{: }g\pmod{x^n} \text{ such that }f(g)\equiv g(f)\equiv x\pmod{x^n}\text{.} \\
1&t\gets f'(0) \\
2&F(x)\gets f\left(t^{-1}x\right) \\
3&(a_0,\dots ,a_{n-1})\gets \operatorname{Enum-}k\operatorname{th-Term-of-Power}(F,n-1,n) \\
&\because \left\lbrack x^{n-1}\right\rbrack F^k=\frac{k}{n-1}\left\lbrack x^{n-1-k}\right\rbrack \left(F^{\langle -1\rangle}/x\right)^{-(n-1)} \\
&\therefore \frac{n-1}{k}a_{k}=\left\lbrack x^{n-1-k}\right\rbrack\left(F^{\langle -1\rangle}/x\right)^{-(n-1)},\space (k>0) \\
4&G(x)\gets \sum_{k=1}^{n-1}\frac{n-1}{k}a_{k}x^{n-1-k} \\
5&F^{\langle -1\rangle}/x\gets \left(G(x)^{1/(n-1)}\right)^{-1}\mod{x^{n-1}} \\
&\because (F^{\langle -1\rangle}/x)(0)=1 \\
&\therefore F^{\langle -1\rangle}/x=\exp\left(\frac{1}{1-n}\log G\right) \\
&\because F^{\langle -1\rangle}\circ f\circ \left(t^{-1}x\right)=x \\
&\therefore \left((t^{-1}x) \circ F^{\langle -1\rangle}\right)\circ f=\left((t^{-1}x) \circ F^{\langle -1\rangle}\right)\circ f \circ \left((t^{-1}x)\circ (tx)\right)=x \\
6&\textbf{return }\left((t^{-1}x) \circ F^{\langle -1\rangle}\right)
\end{array}
$$

From this algorithm, we can know that the sequence $\left(\left\lbrack x^k\right\rbrack gf^n\right)_{n\geq 0}$ is a linearly recurrent sequence (more precisely, the $C$-recursive sequence), what this algorithm is doing is finding such a rational function $P/Q$ generate the sequence.

At the very end of this algorithm,

$$
\begin{aligned}
\left\lbrack x^0\right\rbrack Q&=\left(1-y\left\lbrack x^0\right\rbrack f\right)^{\deg_y(Q)}\\
&=\sum_{j=0}^{\deg_y(Q)}\binom{\deg_y(Q)}{j}\left(-\left\lbrack x^0\right\rbrack f\right)^{j}y^j
\end{aligned}
$$

so

$$
\left\lbrack x^0\right\rbrack Q^{-1}=\sum_{j\geq 0}\binom{\deg_y(Q)+j-1}{j}\left(\left\lbrack x^0\right\rbrack f\right)^{j}y^j
$$

There is no need to compute the inversion of formal power series.

Thanks noshi91 for teaching me this at [X (Twitter)](https://twitter.com/noshi91/status/1776305463526826041)!

## Bibliography

1. noshi91. [FPS の合成と逆関数、冪乗の係数列挙 $\Theta(n(\log(n))^2)$](https://noshi91.hatenablog.com/entry/2024/03/16/224034).
2. Alin Bostan, Ryuhei Mori. [A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence](https://arxiv.org/abs/2008.08822).
