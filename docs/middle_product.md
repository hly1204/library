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

Note: If we are given $f(x) = \sum _ {j = 0}^{m - 1} f_j x^{-j - 1}$ and $g(x) = \sum _ {j = 0}^{n - 1} g_j x^j$, we want to compute something like $\left\lbrack x^{\lt 0}\right\rbrack fg$, the **Transposed Convolution** just give us the correct result.

```c++
template<typename Tp>
inline std::vector<Tp> transposed_convolution(std::vector<Tp> f, std::vector<Tp> g) {
    const int m = f.size();
    const int n = g.size();
    assert(m >= n);
    const int len = fft_len(m);
    f.resize(len);
    g.resize(len);
    transposed_inv_fft(f);
    fft(g);
    for (int i = 0; i < len; ++i) f[i] *= g[i];
    transposed_fft(f);
    f.resize(m - n + 1);
    return f;
}
```

## References

1. Guillaume Hanrot, Michel Quercia, Paul Zimmermann. The Middle Product Algorithm I. Appl. Algebra Eng. Commun. Comput. 14(6): 415-438 (2004) url: <https://inria.hal.science/inria-00071921/document>
2. Alin Bostan, Grégoire Lecerf, Éric Schost. Tellegen's principle into practice. ISSAC 2003: 37-44 url: <https://specfun.inria.fr/bostan/publications/BoLeSc03.pdf>
3. Daniel J. Bernstein. The transposition principle. url: <https://cr.yp.to/transposition.html>
