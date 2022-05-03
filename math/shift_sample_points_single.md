---
title: Shift Sample Points (Single) (in $\mathbb{F} _ p \lbrack z \rbrack$)
documentation_of: ./shift_sample_points_single.hpp
---

## Lagrange Interpolation Formula

**Problem**: Given sample points $f(0), f(1), \dots ,f(n - 1)$ of polynomial $f$ with $\deg f \lt n$, find $f(c)$.

Recall the Lagrange interpolation formula,

$$
f(x) = \sum _ {0 \leq i \lt n} f(i) \prod _ {0 \leq j \lt n \atop j \neq i} \frac{x - j}{i - j}
$$

and define $k_i$ with

$$
k_i := \frac{f(i)}{i!} \prod _ {0 \leq j \lt i}(x - j)
$$

for some $i$, we have

$$
f(x) = \sum _ {0 \leq i \lt n} k_i \frac{(-1)^{n - 1 - i}}{(n - 1 - i)!} \prod _ {i \lt j \lt n}(x - j).
$$