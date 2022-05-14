---
title: Chinese Remainder Algorithm (in $\mathbb{Z} / m \mathbb{Z}$)
documentation_of: ./cra.hpp
---

## Garner's Algorithm

**Problem**: Solve the following system of linear congruence equation.

$$
\begin{cases}
x \equiv a_0 \pmod{m_0} \\
x \equiv a_1 \pmod{m_1} \\
\vdots \\
x \equiv a _ {n - 1} \pmod{m _ {n - 1}}
\end{cases}\tag{1}
$$

Consider the simplest problem which is

$$
\begin{cases}
x \equiv a_0 \pmod{m_0} \\
x \equiv a_1 \pmod{m_1}
\end{cases}\tag{2}
$$

We have $x = a_0 + k_0m_0 = a_1 + k_1m_1$, which implies $k_0m_0 - k_1m_1 = (a_1 - a_0)$. Let $d := \gcd(m_0, m_1)$. We know that $(2)$ has solution if and only if $d \mid (a_1 - a_0)$, and we could use extended Euclidean algorithm to compute $s,t$ such that

$$
sm_0 + tm_1 = d,
$$

so

$$
k_0 = s\cdot \frac{a_1 - a_0}{d}.
$$

and

$$
x \equiv a_0 + k_0m_0 \pmod{\operatorname{lcm}(m_0, m_1)}.
$$

Another view is that

$$
\begin{aligned}
&{} k_0 \cdot \frac{m_0}{d} - k_1 \cdot \frac{m_1}{d} = \frac{a_1 - a_0}{d} \\
\implies &{} k_0 \equiv (a_1 - a_0) m_0^{-1}\pmod{(m_1 / d)}.
\end{aligned}
$$

## Reference

1. math314のブログ. [任意modでの畳み込み演算をO(n log(n))で](https://math314.hateblo.jp/entry/2015/05/07/014908).
