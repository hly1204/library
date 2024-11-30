---
title: FFT Doubling
documentation_of: ../fft_doubling.hpp
---

## FFT Doubling

Given $\operatorname{\mathsf{FFT}} _ n(A(x))$ and $A(x)$, we want to compute $\operatorname{\mathsf{FFT}} _ {2n}(A(x))$. With the definition of FFT, we know that the left half of $\operatorname{\mathsf{FFT}} _ {2n}(A(x))$ equals $\operatorname{\mathsf{FFT}} _ n(A(x))$. And the right half is just $\operatorname{\mathsf{FFT}} _ n(A(\zeta _ {2n}x))$. If we don't know $A(x)$, we should ensure that $\deg A\lt n$ since we can only restore $A(x)\bmod{\left(x^{n}-1\right)}$.

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{FFT\text{-}DOUBLING}}\text{:} \\
&\textbf{Input}\text{: }\left\lbrack A(1),A(-1),\dots,A\left(\zeta_n^{n-1}\right) \right\rbrack,n\text{ is a power of }2,\deg A\lt n\text{.} \\
&\textbf{Output}\text{: }\left\lbrack A(1),A(-1),\dots,A\left(\zeta_{2n}^{2n-1}\right)\right\rbrack\text{.} \\
1&A(x)\gets \operatorname{\mathsf{IFFT}}_n\left(\left\lbrack A(1),A(-1),\dots,A\left(\zeta_n^{n-1}\right) \right\rbrack\right) \\
2&\left\lbrack A\left(\zeta_{2n}\right),A\left(-\zeta_{2n}\right),\dots,A\left(\zeta_{2n}^{2n-1}\right)\right\rbrack \gets \operatorname{\mathsf{FFT}}_n\left(A\left(\zeta_{2n}x\right)\right) \\
3&\textbf{return } \left\lbrack A(1),A(-1),\dots,A\left(\zeta_{n}^{n-1}\right),A\left(\zeta_{2n}\right),A\left(-\zeta_{2n}\right),\dots,A\left(\zeta_{2n}^{2n-1}\right)\right\rbrack
\end{array}
$$

**Example**: If we are given $A(1),A(-1)$ and $\deg A\lt 2$, and we want to compute $A(\mathrm{i}),A(\mathrm{-i})$ since $\zeta _ 2=-1,\zeta _ 4=\mathrm{i}$ apparently.

## References

1. Alin Bostan, Ryuhei Mori. A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence. SOSA 2021: 118-132 url: <https://arxiv.org/abs/2008.08822>

2. Daniel J. Bernstein. "The tangent FFT." Pages 291–300 in Applied Algebra, Algebraic Algorithms and Error-Correcting Codes, 17th International Symposium, AAECC-17, Bangalore, India, December 16–20, 2007, Proceedings, edited by Serdar Boztas, Hsiao-feng Lu, Lecture Notes in Computer Science 4851, Springer, 2007, ISBN 978-3-540-77223-1. url: <https://cr.yp.to/papers.html#tangentfft>

3. noshi91. FFT の回数を削減するテクニック集. url: <https://noshi91.hatenablog.com/entry/2023/12/10/163348>
