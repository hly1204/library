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
\operatorname{\mathsf{DFT}} _ n &: A(x)\bmod{\left(x^n-1\right)} \mapsto \begin{bmatrix} A(1) & A\left(\zeta _ {n}\right) & \cdots & A\left(\zeta _ n^{n-1}\right)\end{bmatrix} \\
\operatorname{\mathsf{IDFT}} _ n &: \begin{bmatrix} A(1) & A\left(\zeta _ {n}\right) & \cdots & A\left(\zeta _ n^{n-1}\right)\end{bmatrix} \mapsto A(x)\bmod{\left(x^n-1\right)}
\end{aligned}
$$

We don't need to explain how to compute IDFT which is the inverse function of DFT, just note that $\begin{bmatrix}1&c \\\\ 1&-c \end{bmatrix}^{-1}=\dfrac{1}{2}\begin{bmatrix}1&c^{-1} \\\\ 1&-c^{-1} \end{bmatrix}^{\intercal}$. But there is a little difference between Gauss's classical FFT algorithm and the definition of DFT, we will finally have the result in a [bit-reversed permutation](https://en.wikipedia.org/wiki/Bit-reversal_permutation) of $\begin{bmatrix} A(1) & A\left(\zeta _ {n}\right) & \cdots & A\left(\zeta _ n^{n-1}\right)\end{bmatrix}$.

By the way, if we don't take the inversion of entries of $\frac{1}{2}\begin{bmatrix}1&c^{-1} \\\\ 1&-c^{-1} \end{bmatrix}^{\intercal}$, we will get the transposed algorithm of IDFT which is

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
&\textbf{Output}\text{: }\begin{bmatrix} A(1) & A(-1) & \cdots & A\left(\zeta _ {n}^{n-1}\right)\end{bmatrix}\text{.} \\
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
12&\textbf{return }\begin{bmatrix} a _ 0 & a _ 1 & \cdots & a _ {n-1} \end{bmatrix}
\end{array}
$$

Note that $\begin{bmatrix} A(1) & A(-1) & \cdots & A\left(\zeta _ {n}^{n-1}\right)\end{bmatrix} =\begin{bmatrix} A\left(R(0)\right) & A\left(-R(0)\right) & \cdots & A\left(-R(\left\lfloor n/2\right\rfloor)\right)\end{bmatrix}$, that's why the root array is useful and can be reused even for different $n$.

$\begin{bmatrix} A(1) & A\left(\zeta _ {n}\right) & \cdots & A\left(\zeta _ n^{n-1}\right)\end{bmatrix}$ is bit-reversed permutation of $\begin{bmatrix} A(1) & A(-1) & \cdots & A\left(\zeta _ {n}^{n-1}\right)\end{bmatrix}$.

I suggest to use the following C++ code to make the bit-reversed permutation.

```c++
#include <cassert>
#include <utility>
template <typename Iterator>
void revbin(Iterator a, int n) {
    assert((n & (n - 1)) == 0);
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
&\textbf{Input}\text{: }\begin{bmatrix} A(1) & A(-1) & \cdots & A\left(\zeta _ {n}^{n-1}\right)\end{bmatrix} ,n\text{ is a power of }2\text{.} \\
&\textbf{Output}\text{: }A(x)=\sum _ {j=0}^{n-1}a _ jx^j\text{.} \\
1&\begin{bmatrix} a _ 0 & a _ 1 & \cdots & a _ {n-1}\end{bmatrix} \gets \begin{bmatrix} A(1) & A(-1) & \cdots & A\left(\zeta _ {n}^{n-1}\right)\end{bmatrix} \\
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

### Basic tricks

#### Extract the odd/even part of FFT

These tricks could be used in various algorithms, and they are very simple. If one use the Gauss's original FFT algorithm, $A(-c)$ is next to $A(c)$.

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{FFTEven}}\text{:} \\
&\textbf{Input}\text{: }\begin{bmatrix} A(1) & A(-1) & \cdots & A\left(\zeta _ {2n}^{2n-1}\right) \end{bmatrix},n\text{ is a power of }2,\deg A\lt 2n\text{.} \\
&\textbf{Output}\text{: }\begin{bmatrix} B(1) & B(-1) & \cdots & B\left(\zeta _ {n}^{n-1}\right)\end{bmatrix}\text{ where }B(x^2)=\frac{1}{2}\left(A(x)+A(-x)\right)\text{.} \\
1&\textbf{return }\frac{1}{2}\begin{bmatrix} A(1)+A(-1) & A(\mathrm{i})+A(-\mathrm{i}) & \cdots & A\left(\zeta _ {2n}^{n-1}\right)+A\left(-\zeta _ {2n}^{n-1}\right)\end{bmatrix}
\end{array}
$$

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{FFTOdd}}\text{:} \\
&\textbf{Input}\text{: }\begin{bmatrix} A(1) & A(-1) & \cdots & A\left(\zeta _ {2n}^{2n-1}\right) \end{bmatrix},n\text{ is a power of }2,\deg A\lt 2n\text{.} \\
&\textbf{Output}\text{: }\begin{bmatrix} B(1) & B(-1) & \cdots & B\left(\zeta _ {n}^{n-1}\right)\end{bmatrix}\text{ where }B(x^2)=\frac{1}{2x}\left(A(x)-A(-x)\right)\text{.} \\
1&\textbf{return }\frac{1}{2}\begin{bmatrix} \left(A(1)-A(-1)\right)/1 & \left(A(\mathrm{i})-A(-\mathrm{i})\right)/\mathrm{i} & \cdots & \left(A\left(\zeta _ {2n}^{n-1}\right)-A\left(-\zeta _ {2n}^{n-1}\right)\right)/\zeta _ {2n}^{n-1}\end{bmatrix}
\end{array}
$$

#### Extract the low/high part of FFT

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{FFTLow}}\text{:} \\
&\textbf{Input}\text{: }\begin{bmatrix} A(1) & A(-1) & \cdots & A\left(\zeta _ {2n}^{2n-1}\right) \end{bmatrix},n\text{ is a power of }2,\deg A\lt 2n\text{.} \\
&\textbf{Output}\text{: }\begin{bmatrix} B(1) & B(-1) & \cdots & B\left(\zeta _ {n}^{n-1}\right)\end{bmatrix}\text{ where }B(x)=A(x)\bmod{x^n}\text{.} \\
1&C(\zeta _ {2n}x) \gets \operatorname{\mathsf{IFFT}} _ n\left(\begin{bmatrix} A\left(\zeta _ {2n}\right) & A\left(-\zeta _ {2n}\right) & \cdots & A\left(\zeta _ {2n}^{2n-1}\right)\end{bmatrix}\right) \\
2&\begin{bmatrix} C(1) & C(-1) & \cdots & C\left(\zeta _ {n}^{n-1}\right)\end{bmatrix} \gets \operatorname{\mathsf{FFT}} _ n\left(C(x)\right) \\
3&\textbf{return }\frac{1}{2}\begin{bmatrix} A(1)+C(1) & A(-1)+C(-1) & \cdots & A\left(\zeta _ {n}^{n-1}\right)+C\left(\zeta _ {n}^{n-1}\right)\end{bmatrix}
\end{array}
$$

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{FFTHigh}}\text{:} \\
&\textbf{Input}\text{: }\begin{bmatrix} A(1) & A(-1) & \cdots & A\left(\zeta _ {2n}^{2n-1}\right) \end{bmatrix},n\text{ is a power of }2,\deg A\lt 2n\text{.} \\
&\textbf{Output}\text{: }\begin{bmatrix} B(1) & B(-1) & \cdots & B\left(\zeta _ {n}^{n-1}\right)\end{bmatrix}\text{ where }B(x)=\left(A(x)-\left(A(x)\bmod{x^n}\right)\right)/x^n\text{.} \\
1&C(\zeta _ {2n}x) \gets \operatorname{\mathsf{IFFT}} _ n\left(\begin{bmatrix} A\left(\zeta _ {2n}\right) & A\left(-\zeta _ {2n}\right) & \cdots & A\left(\zeta _ {2n}^{2n-1}\right)\end{bmatrix}\right) \\
2&\begin{bmatrix} C(1) & C(-1) & \cdots & C\left(\zeta _ {n}^{n-1}\right)\end{bmatrix} \gets \operatorname{\mathsf{FFT}} _ n\left(C(x)\right) \\
3&\textbf{return }\frac{1}{2}\begin{bmatrix} A(1)-C(1) & A(-1)-C(-1) & \cdots & A\left(\zeta _ {n}^{n-1}\right)-C\left(\zeta _ {n}^{n-1}\right)\end{bmatrix}
\end{array}
$$

#### FFT Doubling

FFT doubling is described in another document.

#### Extract/Modify single coefficient of FFT (NOT USEFUL)

Consider the simple case first: Given $\operatorname{\mathsf{FFT}} _ n\left(A(x)\right)$ and define $A(x):=\sum _ {j=0}^{n-1}a _ j x^j$, but we don't know the coefficients of $A(x)$ and we want to know $A(0)$, this could be done in $O(n)$. Consider $A(x)+A(-x)=2\sum _ {j=0}^{n/2-1}a _ {2j}x^{2j}=B\left(x^2\right)$ and $B(1)+B(-1)=A(1)+A(-1)+A(\mathrm{i})+A(-\mathrm{i})$, finally we will have $\sum _ {j=0}^{n-1}A\left(\zeta _ {n}^j\right)=nA(0)$. Since we can compute $\operatorname{\mathsf{FFT}} _ n\left(x^kA(x)\bmod{\left(x^n - 1\right)}\right)$ in $O(n)$, we are able to extract or modify single coefficient of FFT.

```c++
#include "fft.hpp" // this file
#include <cassert>
#include <iterator>
#include <utility>
#include <vector>

template<typename Iterator> void revbin(Iterator a, int n) {
    assert((n & (n - 1)) == 0);
    if (n == 0) return;
    for (int i = 0, j = 0;;) {
        if (i < j) std::swap(a[i], a[j]);
        if (++i == n) break;
        for (int k = n >> 1; ((j ^= k) & k) == 0; k >>= 1) {}
    }
}

template<typename Iterator>
typename std::iterator_traits<Iterator>::value_type extract_coeff_from_fft(Iterator a, int n,
                                                                           int k) {
    using Tp = typename std::iterator_traits<Iterator>::value_type;
    assert(k < n);
    if (n == 0) return 0;
    assert((n & (n - 1)) == 0);
    std::vector<Tp> revbin_pow_table(n);
    {
        Tp v         = 1;
        const auto t = FftInfo<Tp>::get().inv_root(n / 2).at(n / 4);
        std::vector<Tp> pow_table(n);
        for (int i = 0; i < n; ++i) pow_table[i] = v, v *= t;
        for (int i = 0; i < n; ++i) revbin_pow_table[i] = pow_table[((long long)k * i) & (n - 1)];
        revbin(revbin_pow_table.begin(), n);
    }
    Tp res;
    for (int i = 0; i < n; ++i) res += a[i] * revbin_pow_table[i];
    return res / n;
}
```

#### Compute the transposed IFFT from FFT (NOT USEFUL)

We are given $\operatorname{\mathsf{FFT}} _ n\left(A(x)\right)$, and we want to compute $\operatorname{\mathsf{FFT}} _ n\left(x^nA\left(x^{-1}\right)\right)$. It could be done in $O(n)$.

```c++
#include <algorithm>
#include <cassert>
#include <utility>

template<typename Iterator> void revbin(Iterator a, int n) {
    assert((n & (n - 1)) == 0);
    if (n == 0) return;
    for (int i = 0, j = 0;;) {
        if (i < j) std::swap(a[i], a[j]);
        if (++i == n) break;
        for (int k = n >> 1; ((j ^= k) & k) == 0; k >>= 1) {}
    }
}

template<typename Iterator> void transform(Iterator a, int n) {
    assert((n & (n - 1)) == 0);
    if (n == 0) return;
    revbin(a, n);
    std::reverse(a + 1, a + n);
    revbin(a, n);
}
```

## Classical Radix-4 (I)FFT

The transformation can be viewed as

$$
\begin{aligned}
\mathbb{C}\left\lbrack x\right\rbrack/\left(x^{4m} - b^4\right) &\to \mathbb{C}\left\lbrack x\right\rbrack/\left(x^{m} - b\right) \\
&\times \mathbb{C}\left\lbrack x\right\rbrack/\left(x^{m} + b\right) \\
&\times \mathbb{C}\left\lbrack x\right\rbrack/\left(x^{m} - \mathrm{i} b\right) \\
&\times \mathbb{C}\left\lbrack x\right\rbrack/\left(x^{m} + \mathrm{i} b\right) \\
\end{aligned}
$$

showed by Bernstein. If one use the matrix to represent one step, it's very easy to implement. We omit the details which are verbose but simple.

## References

1. Daniel J. Bernstein. "The tangent FFT." Pages 291–300 in Applied Algebra, Algebraic Algorithms and Error-Correcting Codes, 17th International Symposium, AAECC-17, Bangalore, India, December 16–20, 2007, Proceedings, edited by Serdar Boztas, Hsiao-feng Lu, Lecture Notes in Computer Science 4851, Springer, 2007, ISBN 978-3-540-77223-1. url: <https://cr.yp.to/papers.html#tangentfft>
2. Daniel J. Bernstein. "Fast multiplication and its applications." Pages 325–384 in Algorithmic number theory: lattices, number fields, curves and cryptography, edited by Joe Buhler, Peter Stevenhagen, Cambridge University Press, 2008, ISBN 978-0521808545. url: <https://cr.yp.to/papers.html#multapps>
3. Alin Bostan, Ryuhei Mori. A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence. SOSA 2021: 118-132 url: <https://arxiv.org/abs/2008.08822>
4. noshi91. FFT の回数を削減するテクニック集. url: <https://noshi91.hatenablog.com/entry/2023/12/10/163348>
