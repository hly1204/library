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

有 $x=k_1m_1+a_1=k_2m_2+a_2$ 其中 $k_1,k_2\in\mathbb{Z}$，我们假设 $\gcd(m_1,m_2)=1$ 那么

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

对比系数后可以得到 $k_1$ 和 $k_2$。

### Garner 算法

$$
\begin{array}{ll}
&\textbf{Algorithm Chinese Remaindering }\operatorname{cr}(\mathbf{v}, \mathbf{m})\text{:} \\
&\textbf{Input}\text{: }\mathbf{m}=(m_0,m_1,\dots ,m _ {n-1})^{\mathrm{T}}\text{, }m_i\in\mathbb{Z}^+\land\gcd(m_i,m_j)=1\text{ for all } i\neq j\text{,} \\
&\qquad \mathbf{v}=(v_0,\dots ,v _ {n-1})^{\mathrm{T}} \text{ where }v_i=x\bmod m_i\text{.} \\
&\textbf{Output}\text{: }x\bmod{\prod _ {i=0}^{n-1} m_i}\text{.} \\
1&\qquad \textbf{for }i\text{ from }1\text{ to }(n-1)\textbf{ do} \\
2&\qquad \qquad C_i\gets \left(\prod _ {j=0}^{i-1}m_j\right)^{-1}\bmod{m_i}\text{;} \\
3&\qquad x\gets v_0\text{;} \\
4&\qquad \textbf{for }i\text{ from }1\text{ to }(n-1)\textbf{ do} \\
5&\qquad \qquad u\gets (v_i-x)\cdot C_i\bmod{m_i}\text{;} \\
6&\qquad \qquad x\gets x+u\prod _ {j=0}^{i-1}m_j\text{;} \\
7&\qquad \textbf{return }(x)\text{;}
\end{array}
$$

我们发现对 Garner 算法进行简单的修改即可使其支持求出 $\left(x\bmod{\prod_i m_i}\right)\bmod{p}$。

$$
\begin{array}{ll}
&\textbf{Algorithm Chinese Remaindering }\operatorname{cr}(\mathbf{v}, \mathbf{m}, p)\text{:} \\
&\textbf{Input}\text{: }\mathbf{m}=(m_0,m_1,\dots ,m _ {n-1})^{\mathrm{T}}\text{, }m_i\in\mathbb{Z}^+\land\gcd(m_i,m_j)=1\text{ for all } i\neq j\text{,} \\
&\qquad \mathbf{v}=(v_0,\dots ,v _ {n-1})^{\mathrm{T}} \text{ where }v_i=x\bmod m_i\text{. }p\in\mathbb{Z}^+\text{.} \\
&\textbf{Output}\text{: }\left(x\bmod{\prod _ {i=0}^{n-1} m_i}\right)\bmod{p}\text{.} \\
1&\qquad \textbf{for }i\text{ from }1\text{ to }(n-1)\textbf{ do} \\
2&\qquad \qquad C_i\gets \left(\prod _ {j=0}^{i-1}m_j\right)^{-1}\bmod{m_i}\text{;} \\
3&\qquad x\gets v_0\bmod{p}\text{;} \\
4&\qquad \textbf{for }i\text{ from }1\text{ to }(n-1)\textbf{ do} \\
5&\qquad \qquad x_i\gets v_0\bmod{m_i}\text{;} \\
6&\qquad \textbf{for }i\text{ from }1\text{ to }(n-1)\textbf{ do} \\
7&\qquad \qquad u\gets (v_i-x_i)\cdot C_i\bmod{m_i}\text{;} \\
8&\qquad \qquad x\gets \left(x+u\prod _ {j=0}^{i-1}m_j\right)\bmod p\text{;} \\
9&\qquad \qquad \textbf{for }j\text{ from }(i+1)\text{ to }(n-1)\textbf{ do} \\
10&\qquad \qquad \qquad x_j\gets \left(x_j+u\prod _ {k=0}^im_k\right)\bmod{m_j}\text{;}\\
11&\qquad \textbf{return }(x)\text{;}
\end{array}
$$

但是对于模数不是两两互素时就比较复杂了。注意到这里表述的较为繁琐是为了防止写代码时 $\prod_im_i$ 太大的情况。

## 参考文献

- Alfred J. Menezes, Paul C. van Oorschot and Scott A. Vanstone. Handbook of Applied Cryptography.
- math314のブログ. [任意modでの畳み込み演算をO(n log(n))で](https://math314.hateblo.jp/entry/2015/05/07/014908).