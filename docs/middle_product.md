---
title: Middle Product
documentation_of: ../middle_product.hpp
---

## Middle Product

Given $f(x) := \sum _ {j = 0}^{m - 1} f _ j x^j$ and $g(x) := \sum _ {j = 0}^{n - 1} g_j x^j$, provided $m \geq n$. We want to compute

$$
\left\lbrack x^{n - 1}\right\rbrack (fg), \dots, \left\lbrack x^{m - 1}\right\rbrack (fg)
$$

which is called the **middle product** of $f$ and $g$. We could compute the full product of $fg$ but it is not necessary.

### Compute via Cyclic Convolution

Just compute $h = fg \bmod{\left(x^{m} - 1\right)}$ and extract the coefficients of $h$.

### Compute via Transposed Convolution

Use the trick that described in FFT.

## References

1. Guillaume Hanrot, Michel Quercia, Paul Zimmermann. The Middle Product Algorithm I. Appl. Algebra Eng. Commun. Comput. 14(6): 415-438 (2004) url: <https://inria.hal.science/inria-00071921/document>
2. Alin Bostan, Grégoire Lecerf, Éric Schost. Tellegen's principle into practice. ISSAC 2003: 37-44 url: <https://specfun.inria.fr/bostan/publications/BoLeSc03.pdf>
3. Daniel J. Bernstein. The transposition principle. url: <https://cr.yp.to/transposition.html>
