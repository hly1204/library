---
title: Formal Power Series Composition
documentation_of: ../fps_composition.hpp
---

## Composition of formal power series

We are given $f\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack,g\in x\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$, and we want to compute $f(g)\bmod{x^n}$.

It is possible to compute $f(g)$ if $f,g\in\mathbb{C}\left\lbrack x\right\rbrack$, since each coefficient of $f(g)$ is a sum of finitely many terms. But if $f,g\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$ then $g(0)=0$ is required.

### Kinoshita–Li's algorithm

Let $f(x):=\sum _ {j = 0}^{n - 1}f _ j x^j$, we have

$$
f(g)=\sum _ {j \geq 0}f _ j g(x)^j
$$

Consider the bivariate formal Laurent series in $x,y$

$$
\begin{aligned}
f(g) &= \left\lbrack y^0\right\rbrack\frac{f\left(y^{-1}\right)}{1 - y\cdot g(x)} \in \mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack\left(\left(y\right)\right) \\
&= \sum _ {j\geq 0}\left(\left(\cdots + f _ j y^{-j} + \cdots \right)y^j\cdot g(x)^j\right)
\end{aligned}
$$

since we only need to compute $f(g)\bmod{x^n}$, it's okay to treat $g(x)$ as a polynomial. Unlike Kinoshita and Li's paper, I don't want to manipulate in formal power series ring by multiplying $\frac{f\left(y^{-1}\right)}{1 - y\cdot g(x)}$ by $y^{n-1}$. If we did so, we may care about the parity of $n-1$.

Kinoshita–Li's algorithm is actually a bivariate variant of Bostan–Mori's algorithm, we have

$$
\begin{aligned}
\frac{P\left(y\right)}{Q\left(x,y\right)}\bmod{x^n}&=\left(\frac{P\left(y\right)}{Q\left(x,y\right)Q\left(-x,y\right)}\bmod{x^n}\right)Q\left(-x,y\right)\bmod{x^n} \\
&=\left(\frac{P(y)}{V\left(x^2,y\right)}\bmod{x^n}\right)Q\left(-x,y\right)\bmod{x^n} \\
&=\left.\left(\frac{P(y)}{V(z,y)}\bmod{z^{\left\lceil n/2\right\rceil}}\right)\right|_{z=x^2}Q\left(-x,y\right)\bmod{x^n}
\end{aligned}
$$

where $V\left(x^2,y\right)=Q(x,y)Q(-x,y)$. We can solve the problem when $n=1$, since now we only need to compute $\frac{P(y)}{Q(x,y)}\bmod{x}=\frac{P(y)}{Q(0,y)}\in\mathbb{C}\left(\left( y\right)\right)$. Actually we do not need to compute $\frac{1}{Q(0,y)}$, since it's just $\left(1-g(0)y\right)^{-k}\in\mathbb{C}\left\lbrack\left\lbrack y\right\rbrack\right\rbrack$ for a certain $k\in\mathbb{N}$, the coefficients of which are known as the binomial coefficients multiplied by some powers of $g(0)$. (noshi91 told me on twitter, I did't notice that.)

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{KinoshitaLi}}\text{:} \\
&\textbf{Input}\text{: }P\in\mathbb{C}\left\lbrack y\right\rbrack,Q\in\mathbb{C}\left\lbrack x,y\right\rbrack ,n,m\in\mathbb{N}_{>0}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack y^{\left(-m,0\right\rbrack}\right\rbrack\dfrac{P\left(y^{-1}\right)}{Q(x,y)}\bmod{x^n}\text{.} \\
&\textbf{Require}\text{: }\left\lbrack x^0y^0\right\rbrack Q=1\text{.} \\
1&\textbf{if }n=1\textbf{ then return }\begin{bmatrix}\left\lbrack y^{-m+1}\right\rbrack\frac{P\left(y^{-1}\right)}{Q(0,y)} & \cdots & \left\lbrack y^0\right\rbrack\frac{P\left(y^{-1}\right)}{Q(0,y)}\end{bmatrix} \\
2&V(x^2,y)\gets Q(x,y)Q(-x,y)\bmod{x^n}\bmod{y^{1 + \deg _ y P}} \\
3&d \gets \deg _ y Q\left(-x,y\right) \\
4&m' \gets \min \left\lbrace m+d, 1 + \deg _ y P\right\rbrace \\
5&\begin{bmatrix} t _ {- m' + 1} & \cdots & t _ 0\end{bmatrix}\gets \operatorname{\mathsf{KinoshitaLi}}\left(P(y),V(x,y),\left\lceil n/2\right\rceil,m'\right) \\
6&T(x,y) \gets \sum_{j=- m' + 1}^0 t _ jy^j \\
7&U(x,y) \gets T(x^2,y)Q(-x,y)\bmod{x^n} \\
8&\textbf{return }\begin{bmatrix}\left\lbrack y^{-m+1}\right\rbrack U(x,y) & \cdots & \left\lbrack y^0\right\rbrack U(x,y)\end{bmatrix}
\end{array}
$$

Kinoshita–Li's algorithm is simple and elegant.

TODO: optimization of this algorithm.

### Sample Code

I have written a simplified version of Kinoshita–Li's algorithm which could be found at [形式幂级数复合丨复合逆 - OI Wiki](https://oi-wiki.org/math/poly/comp-rev/).

```c++
#include <algorithm>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

using uint         = unsigned;
using ull          = unsigned long long;
constexpr uint MOD = 998244353;

constexpr uint PowMod(uint a, ull e) {
    for (uint res = 1;; a = (ull)a * a % MOD) {
        if (e & 1) res = (ull)res * a % MOD;
        if ((e /= 2) == 0) return res;
    }
}

constexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }

constexpr uint QUAD_NONRESIDUE = 3;
constexpr int LOG2_ORD         = __builtin_ctz(MOD - 1);
constexpr uint ZETA            = PowMod(QUAD_NONRESIDUE, (MOD - 1) >> LOG2_ORD);
constexpr uint INV_ZETA        = InvMod(ZETA);

std::pair<std::vector<uint>, std::vector<uint>> GetFFTRoot(int n) {
    assert((n & (n - 1)) == 0);
    if (n / 2 == 0) return {};
    std::vector<uint> root(n / 2), inv_root(n / 2);
    root[0] = inv_root[0] = 1;
    for (int i = 0; (1 << i) < n / 2; ++i)
        root[1 << i]               = PowMod(ZETA, 1LL << (LOG2_ORD - i - 2)),
                  inv_root[1 << i] = PowMod(INV_ZETA, 1LL << (LOG2_ORD - i - 2));
    for (int i = 1; i < n / 2; ++i)
        root[i]     = (ull)root[i - (i & (i - 1))] * root[i & (i - 1)] % MOD,
        inv_root[i] = (ull)inv_root[i - (i & (i - 1))] * inv_root[i & (i - 1)] % MOD;
    return {root, inv_root};
}

void Butterfly(int n, uint a[], const uint root[]) {
    assert((n & (n - 1)) == 0);
    for (int i = n; i >= 2; i /= 2)
        for (int j = 0; j < n; j += i)
            for (int k = j; k < j + i / 2; ++k) {
                const uint u = a[k];
                a[k + i / 2] = (ull)a[k + i / 2] * root[j / i] % MOD;
                if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;
                if ((a[k + i / 2] = u + MOD - a[k + i / 2]) >= MOD) a[k + i / 2] -= MOD;
            }
}

void InvButterfly(int n, uint a[], const uint root[]) {
    assert((n & (n - 1)) == 0);
    for (int i = 2; i <= n; i *= 2)
        for (int j = 0; j < n; j += i)
            for (int k = j; k < j + i / 2; ++k) {
                const uint u = a[k];
                if ((a[k] += a[k + i / 2]) >= MOD) a[k] -= MOD;
                a[k + i / 2] = (ull)(u + MOD - a[k + i / 2]) * root[j / i] % MOD;
            }
}

void FFT(int n, uint a[], const uint root[]) { Butterfly(n, a, root); }

void InvFFT(int n, uint a[], const uint root[]) {
    InvButterfly(n, a, root);
    const uint invn = InvMod(n);
    for (int i = 0; i < n; ++i) a[i] = (ull)a[i] * invn % MOD;
}

std::vector<uint> FPSComp(std::vector<uint> f, std::vector<uint> g, int n) {
    assert(g.empty() || g[0] == 0);
    int len = 1;
    while (len < n) len *= 2;
    std::vector<uint> root, inv_root;
    std::tie(root, inv_root) = GetFFTRoot(len * 4);
    // [y^(-1)] (f(y) / (-g(x) + y)) mod x^n in R[x]((y^(-1)))
    auto KinoshitaLi = [&](auto &&KinoshitaLi, const std::vector<uint> &P,
                           const std::vector<uint> &Q, int d, int n) {
        assert((int)P.size() == d * n);
        assert((int)Q.size() == d * n);
        if (n == 1) return P;
        std::vector<uint> dftQ(d * n * 4);
        for (int i = 0; i < d; ++i)
            for (int j = 0; j < n; ++j) dftQ[i * n * 2 + j] = Q[i * n + j];
        dftQ[d * n * 2] = 1;
        FFT(d * n * 4, dftQ.data(), root.data());
        std::vector<uint> V(d * n * 2);
        for (int i = 0; i < d * n * 4; i += 2) V[i / 2] = (ull)dftQ[i] * dftQ[i + 1] % MOD;
        InvFFT(d * n * 2, V.data(), inv_root.data());
        if ((V[0] += MOD - 1) >= MOD) V[0] -= MOD;
        for (int i = 1; i < d * 2; ++i)
            for (int j = 0; j < n / 2; ++j) V[i * (n / 2) + j] = V[i * n + j];
        V.resize(d * n);
        const auto T = KinoshitaLi(KinoshitaLi, P, V, d * 2, n / 2);
        std::vector<uint> dftT(d * n * 2);
        for (int i = 0; i < d * 2; ++i)
            for (int j = 0; j < n / 2; ++j) dftT[i * n + j] = T[i * (n / 2) + j];
        FFT(d * n * 2, dftT.data(), root.data());
        for (int i = 0; i < d * n * 4; i += 2) {
            const uint u = dftQ[i];
            dftQ[i]      = (ull)dftT[i / 2] * dftQ[i + 1] % MOD;
            dftQ[i + 1]  = (ull)dftT[i / 2] * u % MOD;
        }
        InvFFT(d * n * 4, dftQ.data(), inv_root.data());
        for (int i = 0; i < d; ++i)
            for (int j = 0; j < n; ++j) dftQ[i * n + j] = dftQ[(i + d) * (n * 2) + j];
        dftQ.resize(d * n);
        return dftQ;
    };
    f.resize(len);
    g.resize(len);
    for (int i = 0; i < len; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);
    auto res = KinoshitaLi(KinoshitaLi, f, g, 1, len);
    res.resize(n);
    return res;
}

// Power Projection: [x^(n-1)] (fg^i) for i=0,..,n-1
std::vector<uint> PowProj(std::vector<uint> f, std::vector<uint> g, int n) {
    assert(g.empty() || g[0] == 0);
    int len = 1;
    while (len < n) len *= 2;
    std::vector<uint> root, inv_root;
    std::tie(root, inv_root) = GetFFTRoot(len * 4);
    // [x^(n-1)] (f(x) / (-g(x) + y)) in R[x]((y^(-1)))
    auto KinoshitaLi = [&](auto &&KinoshitaLi, std::vector<uint> P, std::vector<uint> Q, int d,
                           int n) -> std::vector<uint> {
        assert((int)P.size() == d * n);
        assert((int)Q.size() == d * n);
        if (n == 1) return P;
        std::vector<uint> dftQ(d * n * 4), dftP(d * n * 4);
        for (int i = 0; i < d; ++i)
            for (int j = 0; j < n; ++j)
                dftP[i * n * 2 + j] = P[i * n + j], dftQ[i * n * 2 + j] = Q[i * n + j];
        dftQ[d * n * 2] = 1;
        FFT(d * n * 4, dftP.data(), root.data());
        FFT(d * n * 4, dftQ.data(), root.data());
        P.resize(d * n * 2);
        Q.resize(d * n * 2);
        for (int i = 0; i < d * n * 4; i += 2) {
            const uint u = (ull)dftP[i] * dftQ[i + 1] % MOD;
            const uint v = (ull)dftP[i + 1] * dftQ[i] % MOD;
            P[i / 2]     = (ull)(u + MOD - v) * inv_root[i / 2] % MOD;
            if (P[i / 2] & 1) P[i / 2] += MOD;
            P[i / 2] /= 2;
            Q[i / 2] = (ull)dftQ[i] * dftQ[i + 1] % MOD;
        }
        InvFFT(d * n * 2, P.data(), inv_root.data());
        InvFFT(d * n * 2, Q.data(), inv_root.data());
        if ((Q[0] += MOD - 1) >= MOD) Q[0] -= MOD;
        for (int i = 1; i < d * 2; ++i)
            for (int j = 0; j < n / 2; ++j)
                P[i * (n / 2) + j] = P[i * n + j], Q[i * (n / 2) + j] = Q[i * n + j];
        P.resize(d * n);
        Q.resize(d * n);
        return KinoshitaLi(KinoshitaLi, P, Q, d * 2, n / 2);
    };
    f.insert(f.begin(), len - n, 0);
    f.resize(len);
    g.resize(len);
    for (int i = 0; i < len; ++i) g[i] = (g[i] != 0 ? MOD - g[i] : 0);
    auto res = KinoshitaLi(KinoshitaLi, f, g, 1, len);
    std::reverse(res.begin(), res.end());
    res.resize(n);
    return res;
}

std::vector<uint> FPSPow1(std::vector<uint> g, uint e, int n) {
    assert(!g.empty() && g[0] == 1);
    if (n == 1) return std::vector<uint>{1u};
    std::vector<uint> inv(n), f(n);
    inv[1] = f[0] = 1;
    for (int i = 2; i < n; ++i) inv[i] = (ull)(MOD - MOD / i) * inv[MOD % i] % MOD;
    for (int i = 1; i < n; ++i) f[i] = (ull)f[i - 1] * (e + MOD + 1 - i) % MOD * inv[i] % MOD;
    g[0] = 0;
    return FPSComp(f, g, n);
}

std::vector<uint> FPSRev(std::vector<uint> f, int n) {
    assert(f.size() >= 2 && f[0] == 0 && f[1] != 0);
    if (n == 1) return std::vector<uint>{0u};
    f.resize(n);
    const uint invf1 = InvMod(f[1]);
    uint invf1p      = 1;
    for (int i = 0; i < n; ++i) f[i] = (ull)f[i] * invf1p % MOD, invf1p = (ull)invf1p * invf1 % MOD;
    std::vector<uint> inv(n);
    inv[1] = 1;
    for (int i = 2; i < n; ++i) inv[i] = (ull)(MOD - MOD / i) * inv[MOD % i] % MOD;
    auto proj = PowProj(std::vector<uint>{1u}, f, n);
    for (int i = 1; i < n; ++i) proj[i] = (ull)proj[i] * (n - 1) % MOD * inv[i] % MOD;
    std::reverse(proj.begin(), proj.end());
    auto res = FPSPow1(proj, InvMod(MOD + 1 - n), n - 1);
    for (int i = 0; i < n - 1; ++i) res[i] = (ull)res[i] * invf1 % MOD;
    res.insert(res.begin(), 0);
    return res;
}
```

## References

1. Yasunori Kinoshita, Baitian Li. Power Series Composition in Near-Linear Time. FOCS 2024: 2180-2185 url: <https://arxiv.org/abs/2404.05177>
2. Alin Bostan, Ryuhei Mori. A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence. SOSA 2021: 118-132 url: <https://arxiv.org/abs/2008.08822>
3. R. P. Brent and H. T. Kung. 1978. Fast Algorithms for Manipulating Formal Power Series. J. ACM 25, 4 (Oct. 1978), 581–595. url: <https://doi.org/10.1145/322092.322099>
4. David Harvey. Faster polynomial multiplication via multipoint Kronecker substitution. J. Symb. Comput. 44(10): 1502-1510 (2009) url: <https://doi.org/10.1016/j.jsc.2009.05.004>
5. Alin Bostan, Bruno Salvy, Éric Schost. Power series composition and change of basis. ISSAC 2008: 269-276 url: <https://arxiv.org/abs/0804.2337>
