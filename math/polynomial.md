---
title: Polynomial (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
documentation_of: ./polynomial.hpp
---

## The Ring of Reversed Formal Laurent Series $R\left(\left( z^{-1} \right)\right)$

Bernstein showed that division in $R \lbrack z \rbrack$ is division in $R\left(\left( z^{-1} \right)\right)$.

**Problem**: Given polynomials $a, b \in R \lbrack z \rbrack$, find $q, r \in R \lbrack z \rbrack$ such that $a = qb + r$ and $\deg r \lt \deg b$.

Recall what we do for computing such $q, r$ if both $a, b$ are positive integers. We compute $ab^{-1}$ in $\mathbb{Q}$ (which means we do the computation of $b^{-1}$ in $\mathbb{Q}$) and apply the floor function to $ab^{-1}$ to make the result in $\mathbb{Z}$.

We could do this to polynomials similarly. I omit the details.

## Bibliography

1. V. Shoup. [A Computational Introduction to Number Theory and Algebra (Version 2)](https://www.shoup.net/ntb/).
2. D. J. Bernstein. [Scaled remainder trees](https://cr.yp.to/papers.html#scaledmod).
