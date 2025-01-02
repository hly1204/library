---
title: Subproduct Tree
documentation_of: ../subproduct_tree.hpp
---

## Subproduct Tree

The name of "subproduct tree" comes from Bostan's papers, Bernstein called the structure "product tree". We will use the name "subproduct tree".

### Build the subproduct tree

Let $n := 2^k, k \in \mathbb{N}$, and the leaves of the subproduct tree are $x - a _ 0, x - a _ 1, \dots, x - a _ {n - 1}$ for $a _ j \in \mathbb{C}$, the non-leaf nodes are the product of their children. So the root of the tree is

$$
\prod _ {j = 0} ^ {n - 1}\left(x - a _ {j}\right)
$$

We can use divide and conquer combined with convolution algorithm to build the tree up from the leaves.

### Polynomial multipoint evaluation

Given polynomial $f\in\mathbb{C}\left\lbrack x\right\rbrack$. The traditional algorithm for computing $f(a _ 0), \dots, f(a _ {n - 1})$ is using the Euclidean division of polynomials. We first compute $g = f\bmod{\prod _ {j = 0} ^ {n - 1}\left(x - a _ j\right)}$, and

$$
\begin{aligned}
g _ 0 &= g\bmod{\prod _ {j = 0} ^ {n/2 - 1}\left(x - a _ j\right)} \\
g _ 1 &= g\bmod{\prod _ {j = n/2} ^ {n - 1}\left(x - a _ j\right)}
\end{aligned}
$$

all the way down to the leaves of the subproduct tree. An alternative idea showed by Bernstein is that we could compute

$$
\left\lbrack x^{\left\lbrack -n,0\right)}\right\rbrack\frac{f}{\prod _ {j = 0} ^ {n - 1}\left(x - a _ j\right)} \in \mathbb{C}\left(\left(x^{-1}\right)\right)
$$

and note that

$$
\left\lbrack x^{-1}\right\rbrack\frac{f}{x - a _ j} = f(a _ j) = f \bmod {\left(x - a _ j\right)}
$$

So we only need to compute one division and several multiplications but not several Euclidean divisions. It makes the algorithm faster.

### Polynomial interpolation

TODO

## References

1. Alin Bostan, Grégoire Lecerf, Éric Schost. Tellegen's principle into practice. ISSAC 2003: 37-44 url: <https://specfun.inria.fr/bostan/publications/BoLeSc03.pdf>
2. Daniel J. Bernstein. "Scaled remainder trees." url: <https://cr.yp.to/papers.html#scaledmod>
3. noshi91. 転置原理なしで Monomial 基底から Newton 基底への変換. url: <https://noshi91.hatenablog.com/entry/2023/05/01/022946>
