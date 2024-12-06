---
title: C-recursive Sequence
documentation_of: ../c_recursive.hpp
---

## C-recursive Sequence

The sequence $\left(a _ n\right) _ {n\geq 0}$ is said to be C-recursive if it has form

$$
a _ n=\sum _ {j=1}^d c _ j a _ {n-j}, \qquad (n \geq d)
$$

here C-recursive means linear with **constant** coefficients. $d$ is said to be the **order** of the recurrent relation. We are given $c _ 1, \dots , c _ d$ and **initial terms** $a _ 0, \dots, a _ {d-1}$ in $\mathbb{C}$, the following algorithm could help us computing $a _ k$ for $k\gg d$.

We define $\Gamma(x):=x^d-\sum _ {j=0}^{d-1}c _ {d-j}x^j$ to be the **characteristic polynomial** of $\left(a _ n\right) _ {n\geq 0}$.

### Companion matrix

The companion matrix of monic polynomial $\Gamma (x)$ is

$$
C_\Gamma:=
\begin{bmatrix}
&&&c _ d \\
1&&&c _ {d-1} \\
&\ddots &&\vdots \\
&&1&c _ 1
\end{bmatrix}
$$

We define $b(x):=\sum _ {j=0}^{d-1}b _ jx^j$ and

$$
B _ b:=\begin{bmatrix}b _ 0 & b _ 1 & \cdots & b _ {d-1}\end{bmatrix}^{\intercal}
$$

One could simply check that

$$
\underbrace{\begin{bmatrix}
&&&c _ d \\
1&&&c _ {d-1} \\
&\ddots &&\vdots \\
&&1&c _ 1
\end{bmatrix}} _ {C _ \Gamma}
\underbrace{\begin{bmatrix}
b _ 0 \\
b _ 1 \\
\vdots \\
b _ {d-1}
\end{bmatrix}} _ {B _ b}=
\underbrace{\begin{bmatrix}
c _ d b _ {d-1} \\
b _ 0 + c _ {d-1} b _ {d-1} \\
\vdots \\
b _ {d-2} + c _ 1 b _ {d-1}
\end{bmatrix}} _ {B _ {xb\bmod{\Gamma}}}
$$

and

$$
\begin{aligned}
C _ \Gamma &= \begin{bmatrix}B _ {x\bmod{\Gamma}} & B _ {x^2\bmod{\Gamma}} & \cdots & B _ {x^d\bmod{\Gamma}}\end{bmatrix}, \\
\left(C _ \Gamma\right)^2 &= \begin{bmatrix}B _ {x^2\bmod{\Gamma}} & B _ {x^3\bmod{\Gamma}} & \cdots & B _ {x^{d+1}\bmod{\Gamma}}\end{bmatrix}, \\
\vdots \\
\left(C _ \Gamma\right)^k&=\begin{bmatrix}B _ {x^k\bmod{\Gamma}} & B _ {x^{k+1}\bmod{\Gamma}} & \cdots & B _ {x^{k+d}\bmod{\Gamma}}\end{bmatrix}
\end{aligned}
$$

### Reduce the order

Since the order $d$ maybe large, we can use matrix to reduce the order by

$$
\begin{bmatrix}
a _ {k} \\
a _ {k+1} \\
\vdots \\
a _ {k+d-1}
\end{bmatrix}=\underbrace{\begin{bmatrix}
&1&& \\
&&\ddots & \\
&&&1 \\
c _ d&c _ {d-1}&\cdots &c _ 1
\end{bmatrix}^k} _ {\left(\left(C _ \Gamma\right)^{\intercal}\right)^k=\left(\left(C _ \Gamma\right)^{k}\right)^{\intercal}}
\begin{bmatrix}
a _ 0 \\
a _ {1} \\
\vdots \\
a _ {d-1}
\end{bmatrix}
$$

Using the [exponentiation by squaring](https://en.wikipedia.org/wiki/Exponentiation_by_squaring) trick, we could simply have an algorithm with time $O\left(\mathsf{MM}(d)\log k\right)$.

### Fiduccia's algorithm

Fiduccia showed that

$$
a _ k=\left\langle x^k\bmod{\Gamma(x)},\begin{bmatrix} a _ 0 & \cdots & a _ {d-1}\end{bmatrix}\right\rangle
$$

so we could reduce the matrix exponentiation to modular exponentiation in $\mathbb{C}\left\lbrack x\right\rbrack /\left(\Gamma\right)$, which is apparent.

### Bostan–Mori's algorithm

Bostan and Mori have introduced a new algorithm to compute $x^k\bmod{Q(x)}$ faster. It is called the MSB-first algorithm in their paper, but I would like to show this in a slightly different way which is still equivalent to the original Bostan–Mori's algorithm.

#### Graeffe iteration

Before introducing Bostan–Mori's algorithm, let's introduce the Graeffe iteration first, which could be used to compute truncated (multiplicative) inverse of a formal power series.

Given $Q(x)\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$ and $Q(0)\neq 0$. We want to compute $Q(x)^{-1}\bmod{x^{2n}}$, Graeffe iteration is that

$$
\begin{aligned}
\frac{1}{Q(x)}\bmod{x^{2n}}&=\left(\frac{1}{Q(x)Q(-x)}\bmod{x^{2n}}\right)\cdot Q(-x)\bmod{x^{2n}} \\
&=\left.\left(\frac{1}{V(z)}\bmod{z^{n}}\right)\right| _ {z=x^2}\cdot Q(-x)\bmod{x^{2n}}
\end{aligned}
$$

where $Q(x)Q(-x)$ is an even function written $V\left(x^2\right)$.

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{FPSInv}}\text{:} \\
&\textbf{Input}\text{: }A(x)\bmod{x^n},n\gt 0,A(0)\neq 0\text{.} \\
&\textbf{Output}\text{: }A(x)^{-1}\bmod{x^n}\text{.} \\
1&\textbf{if }n=1\textbf{ then return }A(0)^{-1}\\
2&B\left(x^2\right)\gets A(x)A(-x)\bmod{x^n} \\
3&C(x)\gets\operatorname{\mathsf{FPSInv}}\left(B(x),\left\lceil n/2\right\rceil\right) \\
4&\textbf{return }C\left(x^2\right)A(-x)\bmod{x^n}
\end{array}
$$

If we are using FFT, we can do better.

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{FPSInv}}\text{:} \\
&\textbf{Input}\text{: }A(x)\bmod{x^n},n\gt 0,A(0)\neq 0\text{.} \\
&\textbf{Output}\text{: }A(x)^{-1}\bmod{x^n}\text{.} \\
1&\textbf{if }n=1\textbf{ then return }A(0)^{-1}\\
2&\ell \gets 2^{\left\lceil\log _ 2 \left(2n-1\right)\right\rceil} \\
3&\left\lbrack b _ 0,\dots,b _ {\ell - 1}\right\rbrack \gets \operatorname{\mathsf{FFT}} _ {\ell}\left(A(x)\right) \\
4&V(x) \gets \operatorname{\mathsf{IFFT}} _ {\ell /2}\left(\begin{bmatrix} b _ 0 b _ 1 & b _ 2 b _ 3 & \cdots & b _ {\ell -2} b _ {\ell - 1}\end{bmatrix}\right) \bmod{x^{\left\lceil n/2\right\rceil}} \\
5&T(x) \gets \operatorname{\mathsf{FPSInv}}\left(V(x) \bmod{x^{\left\lfloor n/2\right\rfloor}},\left\lfloor n/2\right\rfloor\right) \\
6&\textbf{if }n \bmod{2} = 1 \textbf{ then} \\
7&\qquad T(x) \gets T(x)-\left(\left\lbrack x^{\left\lfloor n/2\right\rfloor}\right\rbrack V(x)T(x)\right)V(0)^{-1}x^{\left\lfloor n/2\right\rfloor} \\
8&\textbf{end if} \\
9&\left\lbrack c _ 0,\dots,c  _{\ell/2 - 1}\right\rbrack \gets \operatorname{\mathsf{FFT}}  _{\ell/2}\left(T(x)\right) \\
10&U(x) \gets \operatorname{\mathsf{IFFT}} _ {\ell}\left(\begin{bmatrix} b _ 0 c _ 0 & b _ 1 c _ 0 &  \cdots & b _ {\ell - 1} c _ {\ell/2 - 1}\end{bmatrix}\right) \bmod{x^n} \\
11&\textbf{return }U(x)
\end{array}
$$

which runs in time $12\mathsf{E}(n)+O(n)$.

#### Formal Laurent series

If finitely many terms of form $x^{\lt 0}$ are allowed, we define the formal Laurent series ring:

$$
\mathbb{C}\left(\left(x\right)\right) := \left\lbrace \sum _ {j\geq N}a _ j x^j : N\in\mathbb{Z},a _ j \in\mathbb{C}\right\rbrace
$$

and actually $\mathbb{C}\left(\left(x\right)\right)$ is a field since $\mathbb{C}$ is a field. To compute the truncated inverse of a given formal Laurent series, we could use the algorithm which we used in the formal power series cases.

#### Reversed Laurent series

I will not give the definition of reversed Laurent series, since it is quite nature if one replace $x$ with $x^{-1}$ for the formal Laurent series. We will use the notation $\mathbb{C}\left(\left(x^{-1}\right)\right)$.

Since we want to compute $x^k\bmod{Q(x)}$, we could find that

$$
\begin{aligned}
\frac{1}{Q(x)}&=\cdots +a _ {0}x^{-\deg Q} \in \mathbb{C}\left(\left(x^{-1}\right)\right) \\
\frac{x^k}{Q(x)}&=\cdots +a _ kx^{-\deg Q}+\cdots +a _ 0x^{k-\deg Q} \in \mathbb{C}\left(\left(x^{-1}\right)\right) \\
\left\lbrack x^{\left(-\infty,0\right)}\right\rbrack \frac{x^k}{Q(x)}&=\left\lbrack x^{\left(-\infty,0\right)}\right\rbrack \frac{x^k\bmod{Q(x)}}{Q(x)}
\end{aligned}
$$

If we know $\left\lbrack x^{\left\lbrack -\deg Q,0\right)}\right\rbrack\frac{x^k}{Q(x)}$, then we could compute $x^k\bmod{Q(x)}$ by a simple convolution, Bostan–Mori's algorithm showed that

$$
\frac{x^k}{Q(x)}=\frac{x^k}{Q(x)Q(-x)}\cdot Q(-x)
$$

whether $k=2n$ or $k=2n+1$, we only need to compute

$$
\left\lbrack x^{\left\lbrack -2\deg Q,0\right)}\right\rbrack \frac{x^{2n}}{Q(x)Q(-x)}
$$

since $\left\lbrack x^{-2\deg Q-1}\right\rbrack \frac{x^{2n}}{Q(x)Q(-x)}=0$, if we set $V\left(x^2\right)=Q(x)Q(-x)$, then our goal is to compute

$$
\left\lbrack x^{\left\lbrack -\deg Q,0\right)}\right\rbrack \frac{x^{n}}{V(x)}
$$

The algorithm halts when $k=0$.

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{RLSBostanMori}}\text{:} \\
&\textbf{Input}\text{: }Q(x),k\in\mathbb{N}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack x^{\left\lbrack -\deg Q,0\right)}\right\rbrack \dfrac{x^k}{Q(x)},\text{where }Q(x)^{-1}\in\mathbb{C}\left(\left( x^{-1}\right)\right)\text{.} \\
1&\textbf{if }k=0 \textbf{ then return }\begin{bmatrix} \left(\left\lbrack x^{\deg Q}\right\rbrack Q(x)\right)^{-1} & 0 & \cdots & 0 \end{bmatrix} \\
2&V\left(x^2\right)\gets Q(x)Q(-x) \\
3&\begin{bmatrix} c _ {-\deg Q} & \cdots & c _ {-1}\end{bmatrix} \gets \operatorname{\mathsf{RLSBostanMori}}\left(V(x),\left\lfloor k/2\right\rfloor\right) \\
4&T(x)\gets \sum _ {j=0}^{-1+\deg Q}c _ {j-\deg Q}x^j \\
5&\sum _ {j=0}^{-1+3\deg Q} u _ jx^j\gets T\left(x^2\right)x^{k\bmod{2}}Q(-x) \\
6&\textbf{return }\begin{bmatrix} u _ {\deg Q} & \cdots & u _ {-1+2\deg Q}\end{bmatrix}
\end{array}
$$

If we want make the algorithm faster, make the input and output in FFT. We omit the details.

An alternative way is that we could consider as formal Laurent series, this also works. I have implemented such an algorithm used in computing $x^k\bmod{Q(x)}$. The implementation maybe a little weird.

#### Connection between $\mathbb{C}\left(\left(x\right)\right)$ and $\mathbb{C}\left(\left(x^{-1}\right)\right)$

Let $Q\in\mathbb{C}\left\lbrack x\right\rbrack$, we have

$$
\begin{aligned}
\left\lbrack x^{\left\lbrack L,L+\deg Q\right)}\right\rbrack \frac{1}{Q(x)}&=\left\lbrack x^{\left\lbrack 0,\deg Q\right)}\right\rbrack \frac{x^{-L}}{Q(x)} \in\mathbb{C}\left(\left(x\right)\right) \\
&=\left\lbrack x^{\left\lbrack -\deg Q+1,1\right)}\right\rbrack \frac{x^L}{Q\left(x^{-1}\right)} \in\mathbb{C}\left(\left(x^{-1}\right)\right) \\
&=\left\lbrack x^{\left\lbrack -\deg Q,0\right)}\right\rbrack \frac{x^{-1+\deg Q}x^L}{x^{\deg Q}Q\left(x^{-1}\right)} \in\mathbb{C}\left(\left(x^{-1}\right)\right)
\end{aligned}
$$

If we want to compute $\left\lbrack x^{\lbrack L,R)}\right\rbrack \frac{P(x)}{Q(x)}\in \mathbb{C}\left(\left(x\right)\right)$ where $P,Q\in\mathbb{C}\left\lbrack x\right\rbrack$, we have

$$
\begin{aligned}
\frac{P\left(x^{-1}\right)}{Q\left(x^{-1}\right)}&=\sum _ {j\geq 0}a _ j x^{-j}\in\mathbb{C}\left(\left(x^{-1}\right)\right) \\
\frac{x^{n-1}P\left(x^{-1}\right)}{x^nQ\left(x^{-1}\right)}&=\sum _ {j\geq 0}a _ j x^{-j-1}\in\mathbb{C}\left(\left(x^{-1}\right)\right)
\end{aligned}
$$

Let $\tilde{P}(x):=x^{n-1}P\left(x^{-1}\right),\tilde{Q}(x):=x^nQ\left(x^{-1}\right)$ for sufficient large $n$ such that $\tilde{P},\tilde{Q}\in\mathbb{C}\left\lbrack x\right\rbrack$, we have

$$
\begin{aligned}
\left\lbrack x^{\left\lbrack -R,-L\right)}\right\rbrack \frac{\tilde{P}(x)}{\tilde{Q}(x)}&=\left\lbrack x^{\left\lbrack -R+L,0\right)}\right\rbrack \frac{x^L\cdot \tilde{P}(x)}{\tilde{Q}(x)} \\
&=\left\lbrack x^{\left\lbrack -R+L,0\right)}\right\rbrack \frac{\left(x^L\cdot \tilde{P}(x)\right)\bmod{\tilde{Q}(x)}}{\tilde{Q}(x)}
\end{aligned}
$$

## References

1. Alin Bostan, Ryuhei Mori. A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence. SOSA 2021: 118-132 url: <https://arxiv.org/abs/2008.08822>

2. Arne Storjohann. Algorithms for Matrix Canonical Forms. ETH Zürich. Diss., Technische Wissenschaften ETH Zürich, Nr. 13922, 2001. url: <https://www.research-collection.ethz.ch/handle/20.500.11850/145127>
