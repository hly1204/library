---
title: Chirp Z Transform
documentation_of: ../czt.hpp
---

## Chirp Z transform

The Chirp Z transform is by definition

$$
\operatorname{\mathsf{CZT}} _ n:\left(f(x),q\right) \mapsto \begin{bmatrix}f(1)&f(q)&\cdots &f\left(q^{n-1}\right)\end{bmatrix}
$$

where $f(x):=\sum _ {i=0}^{m-1}f _ i x^i\in\mathbb{C}\left\lbrack x\right\rbrack$ and $q\in\mathbb{C}\setminus \left\lbrace 0\right\rbrace$. Since

$$
ij = \binom{i}{2} + \binom{-j}{2} - \binom{i - j}{2}
$$

where $i,j\in\mathbb{Z}$, we can construct

$$
\begin{aligned}
G(x)&:=\sum _ {i = -(m - 1)}^{n - 1}q^{-\binom{i}{2}}x^i, \\
F(x)&:=\sum _ {i = 0}^{m - 1}f _ i q^{\binom{-i}{2}}x^i
\end{aligned}
$$

note that $G(x)\in\mathbb{C}\left\lbrack x,x^{-1}\right\rbrack$, and for $i=0,\dots,n-1$ we have

$$
\begin{aligned}
\left\lbrack x^i\right\rbrack\left(G(x)F(x)\right) &= \sum _ {j = 0}^{m - 1}\left(\left(\left\lbrack x^{i-j}\right\rbrack G(x)\right)\left(\left\lbrack x^j\right\rbrack F(x)\right)\right) \\
&= \sum _ {j=0}^{m-1}f _ jq^{\binom{-j}{2} - \binom{i - j}{2}} \\
&= q^{-\binom{i}{2}}\cdot f\left(q^i\right)
\end{aligned}
$$

note that $q^{\binom{i+1}{2}}=q^{\binom{i}{2}}\cdot q^i$ and $\binom{-i}{2} = \binom{i+1}{2}$.

One can take advantage of the "middle product" algorithm. CZT could be done in time $O\left(\mathsf{M}(n+m)\right)$.

## Inverse Chirp Z transform

The inverse Chirp Z transform is by definition

$$
\operatorname{\mathsf{ICZT}} _ n:\left(\begin{bmatrix}f(1)&f(q)&\cdots &f\left(q^{n-1}\right)\end{bmatrix},q\right) \mapsto f(x)
$$

where $f(x)\in\mathbb{C}\left\lbrack x\right\rbrack _ {\lt n}$ and $q\in\mathbb{C}\setminus\left\lbrace 0\right\rbrace$, $q^{i}\neq q^{j}$ for all $i\neq j$.

### (Modified) Lagrange interpolation formula

Recall the Lagrange interpolation formula, we have

$$
f(x) = \sum _ {i=0}^{n-1}\left(f\left(x _ i\right)\prod _ {0\leq j\lt n\atop j\neq i} \frac{x - x _ j}{x _ i - x _ j}\right)
$$

for $x _ i \neq x _ j$ for all $i\neq j$.

> L'Hôpital's Rule：
> The derivative of $f = \sum _ {i} f _ i x^i$ is $f' = \sum _ {i} i f_i x^{i - 1}$, for $g\in\mathbb{C}\left\lbrack x\right\rbrack$ we have the product rule: $\left(fg\right)' = f'g + fg'$. Let $\alpha\in\mathbb{C}$ and $f(\alpha) = 0$ then $\left(fg\right)'(\alpha) = f'(\alpha)g(\alpha)$, if $f'(\alpha)\neq 0$ then $(fg/f)(\alpha) = g(\alpha) = (fg)'(\alpha)/f'(\alpha)$.

Let $M(x):=\prod _ {i=0}^{n-1}\left(x - x _ i\right)$, we have

$$
M'(x _ i)=\prod_{0\leq j\lt n\atop j\neq i}\left(x _ i - x _ j\right)
$$

The **modified Lagrange interpolation formula** is

$$
f(x)=M(x)\cdot \sum _ {i=0}^{n-1}\frac{f\left(x _ i\right)/M'(x _ i)}{x - x _ i}
$$

Now we have

$$
f(x)=M(x)\cdot\sum _ {i=0}^{n-1}\frac{f\left(q^i\right)/M'\left(q^i\right)}{x-q^i}
$$

where $M(x)=\prod _ {j=0}^{n-1}\left(x - q^j\right)$. If we set $n-1=2k$ and $H(x):=\prod_{j=0}^{k-1}\left(x - q^j\right)$ then

$$
M(x)=H(x)\cdot q^{k^2}\cdot H\left(\frac{x}{q^k}\right)
$$

So we could compute $M(x)$ in time $O\left(\mathsf{M}(n)\right)$. We could use CZT to compute $M'(1),\dots ,M'(q^{n-1})$. Let $c _ i := f\left(q^i\right)/M'\left(q^i\right)$, we have

$$
f(x) = M(x)\cdot\sum _ {i=0}^{n-1}\frac{c _ i}{x-q^i}
$$

since $\deg f(x) \lt n$, we only need to compute $\sum _ {i=0}^{n-1}\frac{c _ i}{x - q^i}\bmod{x^n}$, which is

$$
\begin{aligned}
\sum _ {i=0}^{n-1}\frac{c _ i}{x - q^i}\bmod x^n&=-\sum _ {i=0}^{n-1}\left(\sum _ {j=0}^{n-1}c _ i q^{-i(j+1)}x^j\right) \\
&=-\sum _ {j=0}^{n-1}C\left(q^{-j-1}\right)x^j
\end{aligned}
$$

where $C(x)=\sum _ {i=0}^{n-1}c _ i x^i$. We can use another CZT to compute $C\left(q^{-1}\right),\dots ,C\left(q^{-n}\right)$.

```c++
// An alternative implementation of this file.
template <typename Tp>
inline std::vector<Tp> inv_czt(const std::vector<Tp> &f, const Tp q) {
    if (f.empty()) return {};
    const int n = f.size();
    // prod_(i=0..(n-1))(x-q^i)
    auto rec = [q, iq = q.inv()](auto &&rec, int n) -> std::vector<Tp> {
        if (n == 0) return std::vector<Tp>{Tp(1)};
        if (n == 1) return std::vector<Tp>{Tp(-1), Tp(1)};
        const auto H   = rec(rec, n / 2);
        auto HH        = H;
        const auto qn  = q.pow(n / 2);
        const auto iqn = qn.inv();
        Tp qq          = q.pow((long long)(n / 2) * (n / 2));
        for (int i = 0; i <= n / 2; ++i) HH[i] *= qq, qq *= iqn;
        const auto res = convolution(H, HH);
        return (n & 1) ? convolution(res, std::vector<Tp>{-q.pow(n - 1), Tp(1)}) : res;
    };

    const auto M = rec(rec, n);
    auto C       = czt(deriv(M), q, n);
    for (int i = 0; i < n; ++i) C[i] = f[i] / C[i];
    C = czt(C, q.inv(), n, q.inv());
    for (int i = 0; i < n; ++i) C[i] = -C[i];
    auto res = convolution(M, C);
    res.resize(n);
    return res;
}
```

noshi91 showed that we could compute $M(x)$ and $M'(1),\dots ,M'(q^{n-1})$ faster. Let $s _ i:=\prod _ {j=1}^i\left(1-q^j\right)$ and $s _ 0 := 0$ followed by noshi91's definition. We have

$$
\begin{aligned}
\prod _ {0\leq j\lt n\atop j\neq i}\left(q^i-q^j\right)&=\left(\prod _ {j=0}^{i-1}\left(q^i-q^j\right)\right)\left(\prod _ {j=i+1}^{n-1}\left(q^i-q^j\right)\right) \\
&=\left(\prod _ {j=0}^{i-1}q^j\left(q^{i-j}-1\right)\right)\left(\prod _ {j=i+1}^{n-1}q^i\left(1-q^{j-i}\right)\right) \\
&=(-1)^iq^{\sum _ {j=0}^{i-1}j}\left(\prod _ {j=0}^{i-1}\left(1-q^{i-j}\right)\right)\cdot q^{i(n-i-1)}\left(\prod _ {j=i+1}^{n-1}\left(1-q^{j-i}\right)\right) \\
&=(-1)^iq^{\binom{i}{2}}\left(\prod _ {k=1}^{i}\left(1-q^k\right)\right)\cdot q^{i(n-i-1)}\left(\prod _ {k=1}^{n-i-1}\left(1-q^k\right)\right) \\
&=(-1)^iq^{\binom{i}{2}}s _ i\cdot q^{i(n-i-1)}s _ {n-i-1}
\end{aligned}
$$

note that $q^{\binom{i+1}{2}}\cdot q^{(i+1)(n-(i+1)-1)}=\left(q^{\binom{i}{2}}\cdot q^{i}\right)\left(q^{i(n-i-1)}\cdot q^{n-2i-2}\right)$. Now we only need to compute $M(x)$.

### $q$-analog

Let $n\in\mathbb{N}$, the $q$-analog of $n$ is defined by

$$
\left\lbrack n\right\rbrack _ q :=
\begin{cases}
0,&\text{if }n=0, \\
1+q+\cdots +q^{n-1},&\text{otherwise}.
\end{cases}
$$

note that $\left\lbrack n\right\rbrack _ q = n$ when $q = 1$. And $q\left\lbrack n\right\rbrack _ q =q+q^2+\cdots +q^n$, so

$$
\left\lbrack n\right\rbrack _ q=
\begin{cases}
n,&\text{if }q=1, \\
\frac{1-q^n}{1-q},&\text{otherwise}.
\end{cases}
$$

We could also findout that

$$
\begin{aligned}
\left\lbrack -n\right\rbrack _ q &=
\frac{1-q^{-n}}{1-q} \\
&= q^{-n}\frac{q^n-1}{1-q} \\
&= -q^{-n}\left\lbrack n\right\rbrack _ q
\end{aligned}
$$

Now we define the $q$-factorial

$$
n! _ q :=
\begin{cases}
1,&\text{if }n=0, \\
\left\lbrack 1\right\rbrack_q\left\lbrack 2\right\rbrack _ q\cdots \left\lbrack n\right\rbrack _ q,&\text{otherwise}.
\end{cases}
$$

Finally we could define the $q$-binomial coefficients

$$
\binom{n}{k} _ q :=
\begin{cases}
\frac{n! _ q}{k! _ q(n-k)! _ q},&\text{if }0\leq k\leq n, \\
0,&\text{otherwise}.
\end{cases}
$$

Before introducing the $q$-binomial theorem, let's show some common identities. If $q \neq 1$, we have

$$
\begin{aligned}
\left\lbrack n\right\rbrack _ q&=\frac{1-q^n}{1-q} \\
&=\frac{1-q^k+q^k-q^n}{1-q} \\
&=\frac{1-q^k}{1-q}+q^k\frac{1-q^{n-k}}{1-q} \\
&=\left\lbrack k\right\rbrack _ q +q^k\left\lbrack n-k\right\rbrack _ q
\end{aligned}
$$

which still works when $q = 1$ since $n = k + (n - k)$. We have

$$
\begin{aligned}
\binom{n+1}{k} _ q&=\frac{(n+1)! _ q}{k! _ q(n+1-k)! _ q} \\
&=\frac{n! _ q}{k! _ q(n+1-k)! _ q}\cdot \left(\left\lbrack k\right\rbrack _ q +q^k\left\lbrack n+1-k\right\rbrack _ q\right) \\
&=\frac{n! _ q}{(k-1)! _ q(n+1-k)! _ q}\cdot \left\lbrack k\right\rbrack _ q^{-1}\cdot \left(\left\lbrack k\right\rbrack _ q +q^k\left\lbrack n+1-k\right\rbrack _ q\right) \\
&=\frac{n! _ q}{(k-1)! _ q(n+1-k)! _ q}+q^k\frac{n! _ q\left\lbrack n+1-k\right\rbrack _ q}{k! _ q(n+1-k)! _ q} \\
&=\binom{n}{k-1} _ q+q^k\binom{n}{k} _ q
\end{aligned}
$$

Since $\binom{n}{k} _ q=\binom{n}{n-k} _ q$, we could replace $k$ by $n-k$ which gives

$$
\begin{aligned}
\binom{n+1}{k} _ q&=\binom{n+1}{n+1-k} _ q \\
&=\binom{n}{n-k} _ q+q^{n+1-k}\binom{n}{n+1-k} _ q \\
&=\binom{n}{k} _ q+q^{n-k+1}\binom{n}{k-1} _ q
\end{aligned}
$$

These are called the $q$-Pascal relation.

#### Rothe's $q$-binomial Theorem

For variable $q,a,x$, we have

$$
\prod _ {i=0}^{n-1}\left(a+q^ix\right) = \sum _ {k=0}^n\binom{n}{k} _ q q^{\binom{k}{2}}a^{n-k}x^k
$$

and LHS is defined to be $1$ when $n = 0$.

*Proof*: Let RHS equals $r_n(x,a)$, apply $q$-Pascal relation here, we have

$$
\begin{aligned}
r _ {n+1}(x,a)&=\sum _ {k=0}^{n+1}\binom{n+1}{k} _ q q^{\binom{k}{2}}x^ka^{n+1-k} \\
&=\sum _ {k=0}^{n+1}\left(\binom{n}{k-1} _ q+q^k\binom{n}{k} _ q\right)q^{\binom{k}{2}}x^ka^{n+1-k} \\
&=\left(\sum _ {k=1}^{n+1}\binom{n}{k-1} _ q q^{\binom{k}{2}}x^ka^{n+1-k}\right)+\left(\sum _ {k=0}^{n}\binom{n}{k} _ q q^{\binom{k}{2}}\left(qx\right)^ka^{n+1-k}\right) \\
&=\left(\sum _ {j=0}^{n}\binom{n}{j} _ qq^{\binom{j+1}{2}}x^{j+1}a^{n-j}\right)+\left(\sum _ {j=0}^{n}\binom{n}{j} _ q q^{\binom{j}{2}}\left(qx\right)^ja^{n+1-j}\right)
\end{aligned}
$$

Since $\binom{n}{-1} _ q = \binom{n}{n+1} _ q = 0$ and $\binom{j+1}{2}=\binom{j}{2}+j$ for $j\in\mathbb{N}$, we have

$$
\begin{aligned}
r _ {n+1}(x,a)&=\left(\sum _ {j=0}^{n}\binom{n}{j} _ q q^{\binom{j}{2}}q^jx^{j+1}a^{n-j}\right)+\left(\sum _ {j=0}^{n}\binom{n}{j} _ q q^{\binom{j}{2}}\left(qx\right)^ja^{n+1-j}\right) \\
&=\left(\sum _ {j=0}^{n}\binom{n}{j} _ q q^{\binom{j}{2}}\left(qx\right)^ja^{n-j}x\right)+\left(\sum _ {j=0}^{n}\binom{n}{j} _ q q^{\binom{j}{2}}\left(qx\right)^ja^{n+1-j}\right) \\
&=\sum _ {j=0}^{n}\binom{n}{j} _ q q^{\binom{j}{2}}\left(qx\right)^ja^{n-j}(x+a) \\
&=(a+x)r _ n(qx,a)
\end{aligned}
$$

By induction, we have

$$
\begin{aligned}
r _ {n+1}(x,a)&=(a+x)r _ n(qx,a) \\
&=(a+x)(a+qx)r_{n-1}\left(q^2x,a\right) \\
&=\cdots \\
&=(a+x)(a+qx)\cdots \left(a+q^nx\right)r _ 0\left(q^{n+1}x,a\right)
\end{aligned}
$$

and $r_0(u,v) = 1$ agrees with our definition.

Now back to our problem: Computing $M(x)$ mentioned above.

$$
\begin{aligned}
M(x)&=\prod _ {j=0}^{n-1}\left(x-q^j\right) \\
&=\sum _ {k=0}^n\binom{n}{k} _ q q^{\binom{k}{2}}(-1)^kx^{n-k}
\end{aligned}
$$

where

$$
\binom{n}{k} _ q=\frac{\left(1-q\right)\cdots \left(1-q^n\right)}{\left(1-q\right)\cdots \left(1-q^k\right)\cdot \left(1-q\right)\cdots \left(1-q^{n-k}\right)}=\frac{s _ n}{s _ k s _ {n-k}}
$$

Since $q^n \neq 1$ is not guaranteed, $M(0)$ should be computed separately.

## References

1. 37zigen. 多項式補間：アルゴリズム url: <https://37zigen.com/lagrange-interpolation/>
2. noshi91. 標本点が等比数列を成す場合に補間多項式を計算するアルゴリズム. url: <https://noshi91.github.io/algorithm-encyclopedia/polynomial-interpolation-geometric>
3. Bostan, A. (2010). Fast algorithms for polynomials and matrices. JNCF 2010. Algorithms Project, INRIA. url: <https://specfun.inria.fr/bostan/publications/exposeJNCF.pdf>
4. Warren P. Johnson. An Introduction to $q$-analysis. American Mathematical Soc., 2020.
