---
title: Karatsuba Multiplication
documentation_of: ../karatsuba.hpp
---

## Karatsuba Multiplication

Karatsuba multiplication algorithm is very easy and well explained in Bernstein's paper.

If we want to compute the product of $A(y) = a_0 + a_1y$ and $B(y) = b_0 + b_1y$, Karatsuba suggests that we could compute $A(y)B(y) \bmod {\left(y^2 - y\right)}$, and use $\left(AB\right)(\infty) = a_1b_1$ to restore the result of $A(y)B(y)$.

For computing $A(y)B(y) \bmod {\left(y^2 - y\right)}$, a FFT-styled algorithm is used. We evaluate for $A(0), A(1), B(0), B(1)$ then we will get $A(y)B(y) \bmod {\left(y^2 - y\right)}$ without division. We could restore $A(y)B(y)$ with $a_1b_1$. An alternative is that we could compute $A(y)B(y) \bmod {\left(y^2 + y\right)}$ by evaluating $A(0), A(-1), B(0), B(-1)$ which works similarly.

I think the most important thing we could learn is that, this could be modified and used in computing bitwise convolution such as "bitwise and/or/xor convolution".

## References

1. Daniel J. Bernstein. "Multidigit multiplication for mathematicians." Accepted to Advances in Applied Mathematics, but withdrawn by author to prevent irreparable mangling by Academic Press. url: <https://cr.yp.to/papers.html#m3>
