---
title: Exponential Generating Function
documentation_of: ./egf.hpp
---

## 指数生成函数

考虑数列 $\langle a_0,a_1,\dots \rangle$ 的指数生成函数为

$$
A(x)=\sum _ {i\geq 0}\frac{a_i}{i!}x^i
$$

易发现 $\mathrm{e}^x$ 为数列 $\langle 1,1,\dots \rangle$ 的 EGF 。

## 二项卷积

令 $B(x)=\sum _ {i\geq 0}b_ix^i/(i!)$ 为数列 $\langle b\rangle$ 的 EGF 那么 $A(x)B(x)$ 的 EGF 为

$$
\begin{aligned}
C(x)&=\sum _ {i\geq 0}\frac{c_i}{i!}x^i=\sum _ {i\geq 0}\left(\sum _ {j=0}^i\frac{a_j}{j!}\cdot \frac{b _ {i-j}}{(i-j)!}\right)x^i \\
c_i&=\sum _ {j=0}^i\frac{i!}{j!\cdot (i-j)!}a_jb _ {i-j}=\sum _ {j\geq 0}\binom{i}{j}a_jb _ {i-j}
\end{aligned}
$$

一般我们在 $\mathbb{F} _ p\lbrack x\rbrack$ 其中 $p$ 为素数时做二项卷积可以简单的将 OGF 转换为 EGF 做卷积最后再将每一个乘以阶乘就能得到结果，但是如果在 $(\mathbb{Z}/m\mathbb{Z})\lbrack x\rbrack$ 其中 $m$ 为合数时逆元可能不存在。

因为可以使用中国剩余定理合并，我们只需考虑在模素数幂次 $p^q$ 情况下的二项卷积即可。

Elegia 在论文和博客中指出，令 $\nu_p(n!)$ 表示 $n!$ 中含有的 $p$ 的次数和 $\hat{a} _ k=a_k\cdot (k!/p^{\nu_p(k!)})^{-1}\pmod{p^q}$ 那么

$$
\begin{aligned}
\frac{c_k}{k!}&\equiv \sum _ {i=0}^k \hat{a} _ ip^{-\nu_p(i!)}\hat{b} _ {k-i}p^{-\nu_p((k-i)!)}\pmod{p^q}\\
\hat{c} _ k&\equiv \sum _ {i=0}^kp^{\nu_p(k!)-\nu_p((k-i)!)-\nu_p(i!)}\hat{a} _ i\hat{b} _ {k-i}\pmod{p^q}
\end{aligned}
$$

我们知道 $k!/p^{\nu_p(k!)}$ 在模 $p^q$ 意义下一定存在逆元，而在模 NTT 模数 $N$ 意义下 $p^{-\nu_p(i!)}$ 存在，不妨假设 $N$ 足够大，那么在计算出 $c_k/k!$ 后乘以 $p^{\nu_p(k!)}$ 后右边 $p$ 的次数一定大于等于零可以抵消之前乘的逆元，得到了 $\hat{c} _ k$ 再在模 $p^q$ 意义下乘以 $k!/p^{\nu_p(k!)}$ 即得。换句话说，我们需要使得 $\hat{c} _ k$ 在不取模的意义下是正确的，这就是前面假设 $N$ 足够大的原因。 Kummer 定理告诉我们 $\binom{k}{i}$ 中含有的 $p$ 的次数为 $i$ 和 $k-i$ 在 $p$ 进制下相加所需要的进位次数。那么 $\nu_p(k!)-\nu_p((k-i)!)-\nu_p(i!)\leq \log_pk$ 那么 $p^{\nu_p(k!)-\nu_p((k-i)!)-\nu_p(i!)}\leq k$ 那么 $\hat{c} _ k\leq k\cdot k(p^q)^2$ ， Elegia 提出使用四模数的 NTT 可以使得 $\hat{c} _ k$ 的精度足够。可以解决 [LOJ 174. 二项卷积](https://loj.ac/p/174) 。

## 二项卷积的应用

Elegia 在论文中指出，考虑 $f(x)$ 和 EGF 形式的 $g(x)$ 和 $\mathrm{D}=\dfrac{\mathrm{d}}{\mathrm{d}x}$ 那么

$$
g(\mathrm{D})f(x)
$$

可以用二项卷积的转置求出。

考虑

$$
\begin{aligned}
g(\mathrm{D})f(x)&=\sum _ {i\geq 0}\frac{g_i}{i!}f^{(i)}(x) \\
&=\sum _ {i\geq 0}\frac{g_i}{i!}\sum _ {j\geq i}f_jj!\frac{x^{j-i}}{(j-i)!} \\
&=\sum _ {i\geq 0}\frac{x^i}{i!}\sum _ {j\geq i}f_jj!\frac{g_{j-i}}{(j-i)!} \\
&=\sum _ {i\geq 0}x^i\sum _ {j\geq i}\binom{j}{i}f_jg_{j-i}
\end{aligned}
$$

即得。

论文中指出，考虑 $f(x)\mapsto f(x+c)$ 就是计算 $\mathrm{e}^{c\mathrm{D}}\cdot f(x)$ 。

具体的，令

$$
\begin{aligned}
A(x)&=\sum _ {i=0}^na _ {n-i}(n-i)!x^i,\\
B(x)&=\sum _ {i=0}^n\frac{b_i}{i!}x^i
\end{aligned}
$$

那么

$$
\begin{aligned}
\lbrack x^{n-i}\rbrack \left(A(x)B(x)\right)&=\sum _ {j=0}^{n-i}\lbrack x^{n-i-j}\rbrack A(x) \lbrack x^{j}\rbrack B(x)\\
&=\sum _ {j=0}^{n-i}\frac{(i+j)!}{j!}a _ {i+j}b _ {j}\\
&=i!\sum _ {j=0}^{n-i}\binom{i+j}{i}a _ {i+j}b_j
\end{aligned}
$$

Elegia 还指出可以使用二项卷积完成连续点值的平移，这部分暂未理解和阅读。

## 参考文献

- 李⽩天（Elegia）. ⽣成函数的⼀⼂进展. 2021 年 2 月.
- 李⽩天. 信息学竞赛中的生成函数计算理论框架. [2021 年信息学奥林匹克中国国家集训队论文](https://github.com/OI-wiki/libs/tree/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87).
- 高德纳等. 具体数学.