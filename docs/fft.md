---
title: FFT
documentation_of: ../fft.hpp
---

## Classical Radix-2 FFT

I have learned that classical/original FFT was first used by Gauss in 1805 from Bernstein's paper. The classical FFT is very simple and elegant. Consider the following two functions:

$$
\begin{aligned}
\phi&:\mathbb{C}\left\lbrack x\right\rbrack /(x^{2n}-c^2)\to \mathbb{C}\left\lbrack x\right\rbrack /(x^{n}-c) \\ \varphi&:\mathbb{C}\left\lbrack x\right\rbrack /(x^{2n}-c^2)\to \mathbb{C}\left\lbrack x\right\rbrack /(x^{n}+c)
\end{aligned}
$$

Let $f(x):=\sum _ {j=0}^{2n-1}f _ jx^j$, then

$$
\begin{aligned}
\phi&:f(x)\mapsto f(x)\bmod{\left(x^n-c\right)} \\
\varphi&:f(x)\mapsto f(x)\bmod{\left(x^n+c\right)}
\end{aligned}
$$

If we set $f _ 0(x):=\sum _ {j=0}^{n-1}f_jx^j$ and $f _ 1(x):=\sum _ {j=0}^{n-1}f _ {j+n}x^j$, we will find out that we are actually computing

$$
\begin{bmatrix}
F _ 0(x) \\
F _ 1(x)
\end{bmatrix}=
\begin{bmatrix}
1&c \\
1&-c
\end{bmatrix}
\begin{bmatrix}
f _ 0(x) \\
f _ 1(x)
\end{bmatrix}
$$

and we simply know that this step is invertible if $\begin{bmatrix}1&c \\\\ 1&-c \end{bmatrix}$ is invertible.

We use the notation $\zeta _ n=\exp\left(\frac{2\pi\mathrm{i}}{2}\right)$. For the number theory transformation (a.k.a. NTT), we mostly use prime numbers called FFT primes $p$ and computing in field $\mathbb{F} _ p$, which has element of order $2^k$ with sufficient large $k$, so we could compute DFT for polynomials over $\mathbb{F} _ p\left\lbrack x\right\rbrack$ of length $2^k$.

Use the step iteratively, we could get $f(x)\bmod{\left(x-d\right)}=f(d)$ for several $d$s. The whole algorithm is called radix-2 FFT, which could compute the size-$n$ DFT where $n$ is a power of $2$.

$$
\begin{aligned}
\operatorname{\mathsf{DFT}} _ n &: A(x)\bmod{\left(x^n-1\right)} \mapsto\left\lbrack A(1),A\left(\zeta _ {n}\right),\dots,A\left(\zeta _ n^{n-1}\right)\right\rbrack \\
\operatorname{\mathsf{IDFT}} _ n &: \left\lbrack A(1),A\left(\zeta _ {n}\right),\dots,A\left(\zeta _ n^{n-1}\right)\right\rbrack \mapsto A(x)\bmod{\left(x^n-1\right)}
\end{aligned}
$$

We don't need to explain how to compute IDFT which is the inverse function of DFT, just note that $\begin{bmatrix}1&c \\\\ 1&-c \end{bmatrix}^{-1}=\dfrac{1}{2}\begin{bmatrix}1&c^{-1} \\\\ 1&-c^{-1} \end{bmatrix}^{\intercal}$. But there is a little difference between Gauss's classical FFT algorithm and the definition of DFT, we will finally have the result in a [bit-reversed permutation](https://en.wikipedia.org/wiki/Bit-reversal_permutation) of $\left\lbrack A(1),A\left(\zeta _ {n}\right),\dots,A\left(\zeta _ n^{n-1}\right)\right\rbrack$.

By the way, if we don't take the inversion of entries of $\begin{bmatrix}1&c^{-1} \\\\ 1&-c^{-1} \end{bmatrix}^{\intercal}$, we will get the transposed algorithm of IDFT which is

$$
\operatorname{\mathsf{IDFT}} _ n^{\intercal}\left(A(x)\right)=\frac{1}{n}\operatorname{\mathsf{DFT}} _ n\left(x^nA\left(x^{-1}\right)\right)
$$

and the transposed algorithm of DFT is just the inverse function of the transposed algorithm of IDFT.

Before introducing the FFT algorithm formally, I would like to introduce the root array first, which is important and useful in FFT.

### The root array

Firstly, we know that we should have $\zeta _ n^k$ computed for $k=0,\dots,n-1$, and they are used in bit-reversed order. But it is not a good idea that we just compute all of them, there is a better way to compute and store them. We define the function $R:\mathbb{N}\to\mathbb{C}$ by

$$
R(k)=\begin{cases}
1,&\text{if }k=0, \\
\zeta _ {4k},&\text{if }k\text{ is a power of }2, \\
R\left(k-2^{\lfloor\log _ 2 k\rfloor}\right)R\left(2^{\lfloor\log _ 2 k\rfloor}\right),&\text{otherwise.}
\end{cases}
$$

and first $6$ of them are

$$
\begin{aligned}
R(0)&=1, \\
R(1)&=\zeta _ 4=\mathrm{i}, \\
R(2)&=\zeta _ 8, \\
R(3)&=\zeta _ 8\zeta _ 4=\zeta _ 8^3, \\
R(4)&=\zeta _ {16}, \\
R(5)&=\zeta _ {16}\zeta _ 4=\zeta _ {16}^5
\end{aligned}
$$

which could generate $\zeta _ n^k$ for $k=0,\dots,n-1$, and only need half of the storage.

### Implementation

It's not hard for anyone I think, so I just give the pseudocode.

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{FFT}}\text{:} \\
&\textbf{Input}\text{: }A(x)=\sum _ {j=0}^{n-1}a _ jx^j,n\in 2^{\mathbb{N}}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack A(1),A(-1),\dots,A\left(\zeta _ {n}^{n-1}\right)\right\rbrack\text{.} \\
1&i\gets n \\
2&\textbf{while }i\geq 2\textbf{ do} \\
3&\qquad j\gets 0 \\
4&\qquad \textbf{while }j\lt n\textbf{ do} \\
5&\qquad \qquad \textbf{for }k=0,\dots,i/2-1\textbf{ do} \\
6&\qquad \qquad \qquad \begin{bmatrix}a _ {j+k} \\ a _ {j+k+i/2}\end{bmatrix}\gets \begin{bmatrix}1&R(j/i) \\ 1&-R(j/i)\end{bmatrix}\begin{bmatrix}a _ {j+k} \\ a _ {j+k+i/2}\end{bmatrix} \\
7&\qquad \qquad \textbf{end for} \\
8&\qquad \qquad j\gets j+i \\
9&\qquad \textbf{end while} \\
10&\qquad i\gets i/2 \\
11&\textbf{end while} \\
12&\textbf{return }\left\lbrack a _ 0,a _ 1,\dots,a _ {n-1}\right\rbrack
\end{array}
$$

Note that $\left\lbrack A(1),A(-1),\dots,A\left(\zeta _ {n}^{n-1}\right)\right\rbrack =\left\lbrack A\left(R(0)\right),A\left(-R(0)\right),\dots,A\left(-R(\left\lfloor n/2\right\rfloor)\right)\right\rbrack$, that's why the root array is useful and can be reused even for different $n$.

$\left\lbrack A(1),A\left(\zeta _ {n}\right),\dots,A\left(\zeta _ n^{n-1}\right)\right\rbrack$ is bit-reversed permutation of $\left\lbrack A(1),A(-1),\dots,A\left(\zeta _ {n}^{n-1}\right)\right\rbrack$.

I suggest to use the following C++ code to make the bit-reversed permutation.

```c++
#include <utility>
template <typename Tp>
void revbin(Tp a[], int n) {
    if (n == 0) return;
    for (int i = 0, j = 0;;) {
        if (i < j) std::swap(a[i], a[j]);
        if (++i == n) break;
        for (int k = n >> 1; ((j ^= k) & k) == 0; k >>= 1) {}
    }
}
```

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{IFFT}}\text{:} \\
&\textbf{Input}\text{: }\left\lbrack A(1),A(-1),\dots,A\left(\zeta _ {n}^{n-1}\right)\right\rbrack ,n\text{ is a power of }2\text{.} \\
&\textbf{Output}\text{: }A(x)=\sum _ {j=0}^{n-1}a _ jx^j\text{.} \\
1&\left\lbrack a _ 0,a _ 1,\dots,a _ {n-1}\right\rbrack \gets \left\lbrack A(1),A(-1),\dots,A\left(\zeta _ {n}^{n-1}\right)\right\rbrack \\
2&i\gets 2 \\
3&\textbf{while }i\leq n\textbf{ do} \\
4&\qquad j\gets 0 \\
5&\qquad \textbf{while }j\lt n\textbf{ do} \\
6&\qquad \qquad \textbf{for }k=0,\dots,i/2-1\textbf{ do} \\
7&\qquad \qquad \qquad \begin{bmatrix}a _ {j+k} \\ a _ {j+k+i/2}\end{bmatrix}\gets \begin{bmatrix}1&R(j/i) \\ 1&-R(j/i)\end{bmatrix}^{-1}\begin{bmatrix}a _ {j+k} \\ a _ {j+k+i/2}\end{bmatrix} \\
8&\qquad \qquad \textbf{end for} \\
9&\qquad \qquad j\gets j+i \\
10&\qquad \textbf{end while} \\
11&\qquad i\gets 2i \\
12&\textbf{end while} \\
13&\textbf{return }\sum _ {j=0}^{n-1}a _ jx^j
\end{array}
$$

Note that the input is in bit-reversal order, so we are able to avoid explicit bit-reverse step by using the above pseudocode.

## References

1. Daniel J. Bernstein. "The tangent FFT." Pages 291–300 in Applied Algebra, Algebraic Algorithms and Error-Correcting Codes, 17th International Symposium, AAECC-17, Bangalore, India, December 16–20, 2007, Proceedings, edited by Serdar Boztas, Hsiao-feng Lu, Lecture Notes in Computer Science 4851, Springer, 2007, ISBN 978-3-540-77223-1. url: <https://cr.yp.to/papers.html#tangentfft>

1. Daniel J. Bernstein. "Fast multiplication and its applications." Pages 325–384 in Algorithmic number theory: lattices, number fields, curves and cryptography, edited by Joe Buhler, Peter Stevenhagen, Cambridge University Press, 2008, ISBN 978-0521808545. url: <https://cr.yp.to/papers.html#multapps>
