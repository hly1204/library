---
title: Chinese Remainder Theorem
documentation_of: ./crt.hpp
---

## 中国剩余定理

考虑合并两个同余方程如

$$
\begin{cases}
x\equiv a_1\pmod{m_1}\\
x\equiv a_2\pmod{m_2}
\end{cases}
$$

有 $x=k_1m_1+a_1=k_2m_2+a_2$ 其中 $k_1,k_2\in\mathbb{Z}$ ，我们假设 $\gcd(m_1,m_2)=1$ 那么

$$
k_1\equiv (a_2-a_1)\cdot m_1^{-1}\pmod{m_2}
$$

若 $\gcd(m_1,m_2)=d$ 那么

$$
k_1m_1-k_2m_2=a_2-a_1
$$

且 $a_2-a_1\mid d$ 否则无解，而我们可以通过扩展欧几里得算法求出一组解满足

$$
sm_1+tm_2=d
$$

对比系数后可以得到 $k_1$ 和 $k_2$ 。