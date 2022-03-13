---
title: Polynomial
documentation_of: ./polynomial.hpp
---

## 欧几里得商数和欧几里得余数

或称为带余除法。对于多项式 $f$ 与 $g$ 且 $\deg(f)\geq\deg(g)$ 我们假设其属于欧几里得整环上，那么存在 $f=gq+r$ 其中 $\deg(r)\lt \deg(g)$ 且 $\deg(q)=\deg(f)-\deg(g)$ ，那么说 $r$ 是欧几里得余数和 $q$ 是欧几里得商数（存在且唯一，证略）。我们可以考虑使用幂级数的逆元来得到这两者。我们发现 $gq$ 与 $f$ 的高位是相等的，那么

$$
x^{\deg(f)}f\left(x^{-1}\right)=g\left(x^{-1}\right)q\left(x^{-1}\right)x^{\deg(f)}+r\left(x^{-1}\right)x^{\deg(f)}
$$

发现 $r\left(x^{-1}\right)x^{\deg(f)}$ 影响的是高位，有

$$
x^{\deg(f)}f\left(x^{-1}\right)=\left(x^{\deg(g)}g\left(x^{-1}\right)\right)\left(x^{\deg(q)}q\left(x^{-1}\right)\right)+\left(x^{\deg(r)}r\left(x^{-1}\right)x^{\deg(f)-\deg(r)}\right)
$$

而 $\deg(r)\lt\deg(g)\implies \deg(f)-\deg(r)\geq\deg(f)-\deg(g)+1\gt\deg(q)$ 那么

$$
x^{\deg(q)}q\left(x^{-1}\right)\equiv x^{\deg(f)}f\left(x^{-1}\right)\left(x^{\deg(g)}g\left(x^{-1}\right)\right)^{-1}\pmod{x^{\deg(f)-\deg(g)+1}}
$$

且我们保留了 $q$ 的所有信息，所需要的无非是将多项式“系数翻转”。

求出 $q$ 后代入可求得 $r$ ，而我们知道 $f$ 和 $gq$ 高位是相等的，可以求 $r\equiv f-qg\pmod{(x^{\deg(g)}-1)}$ 。当 $\deg(f)-\deg(g)$ 较小时，我们不使用 NTT 计算会更快。 [EntropyIncreaser](https://loj.ac/u/EntropyIncreaser) 很早在 <https://loj.ac/s/943026> 已经使用了这个方法（不愧是 EI ！），当时我也并未理解。

注意在环 $\mathbb{F} _ p\lbrack x\rbrack$ 上的欧几里得除法实际上就是在环 $\mathbb{F} _ p((x^{-1}))$ 上的欧几里得除法，因为我们可以令这两个环的范数相同，借由这一点可以理解快速的多点求值算法。

## 多项式平移

给出多项式 $A(x)=\sum _ {i=0}^na _ {i}x^{i}$ 且 $\deg(A(x))=n\gt 0$ ，要求 $A(x+c)$ 的系数。

考虑分治法，令 $A(x)=A_0(x)+x^{\lfloor n/2\rfloor}A_1(x)$ 那么 $A(x+c)=A_0(x+c)+(x+c)^{\lfloor n/2\rfloor}A_1(x+c)$ 问题分解为了两部分，其中 $(x+c)^{\lfloor n/2\rfloor}$ 的系数为二项式系数易计算，只需一次卷积。对于任意模数， EI 指出这里可以使用（任意模数）二项卷积做到更好的时间，将来我可能会补充一下实现。

另一种方法考虑 $A(x)$ 在 $c$ 处应用泰勒公式，有

$$
A(x)=A(c)+\frac{A'(c)}{1!}(x-c)+\frac{A''(c)}{2!}(x-c)^{2}+\cdots +\frac{A^{(n)}(c)}{n!}(x-c)^{n}
$$

那么 $A(x+c)$ 是

$$
A(x+c)=A(c)+\frac{A'(c)}{1!}x+\frac{A''(c)}{2!}x^{2}+\cdots +\frac{A^{(n)}(c)}{n!}x^{n}
$$

观察发现

$$
\begin{aligned}
t!\lbrack x^t\rbrack A(x+c)&=A^{(t)}(c)\\
&=\sum _ {i=t}^{n}a _ {i}i!\frac{c^{i-t}}{(i-t)!}\\
&=\sum _ {i=0}^{n-t}a _ {i+t}(i+t)!\frac{c^i}{i!}
\end{aligned}
$$

我们令 $A_0(x)=\sum _ {i=0}^na _ {n-i}(n-i)!x^i$ 和 $B_0(x)=\sum _ {i=0}^n\frac{c^i}{i!}x^i$ 那么

$$
\begin{aligned}
\lbrack x^{n-t}\rbrack (A_0(x)B_0(x))&=\sum _ {i=0}^{n-t}(\lbrack x^{n-t-i}\rbrack A_0(x))(\lbrack x^i\rbrack B_0(x))\\
&=\sum _ {i=0}^{n-t}a _ {i+t}(i+t)!\frac{c^i}{i!}\\
&=t!\lbrack x^t\rbrack A(x+c)
\end{aligned}
$$

<!-- 注意这里的 Markdown 中 `[]()` 这种不能挨着写，否则会识别错误！ -->

可以通过一次多项式乘法得到。一般来说我们假设 $A(x)\in\mathbb{F} _ p\lbrack x\rbrack$ 其中 $p$ 比较大使得 $\deg(A(x))\lt p$ 。

另一种方法是考虑二项式定理 $(x+c)^y=\sum _ {i=0}^y\binom{y}{i}x^ic^{y-i}$ 即

$$
\begin{aligned}
A(x+c)&=\sum _ {i=0}^na_i(x+c)^i\\
&=\sum _ {i=0}^na_i\left(\sum _ {j=0}^i\binom{i}{j}x^jc^{i-j}\right)\\
&=\sum _ {i=0}^na_ii!\left(\sum _ {j=0}^i\frac{x^j}{j!}\frac{c^{i-j}}{(i-j)!}\right)\\
&=\sum _ {i=0}^n\frac{x^i}{i!}\left(\sum _ {j=i}^{n}a_jj!\frac{c^{j-i}}{(j-i)!}\right)
\end{aligned}
$$

括号内显然是卷积形式。

## 多项式快速幂

我经常写的快速幂是

```cpp
int pow(int x, int e) {
  int res = 1;
  for (; e; e >>= 1, x *= x)
    if (e & 1) res *= x;
  return res;
}
```

注意最后一次的 `x *= x` 是冗余的，在乘法代价大的时候要避免

```cpp
int pow(int x, int e) {
  for (int res = 1;; x *= x) {
    if (e & 1) res *= x;
    if ((e >>= 1) == 0) return res;
  }
}
```

这部分需要完善，目前在 `if (e & 1) {}` 的语句中仍有可能的冗余计算。可以阅读参考文献中的内容，使用加法链减少乘法次数。

## 参考文献

- Daniel J. Bernstein. ["Pippenger's exponentiation algorithm."](http://cr.yp.to/papers.html#pippenger) To be incorporated into author's High-speed cryptography book.