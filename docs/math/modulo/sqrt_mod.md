## Euler 判别准则

> Euler 判别准则： 设 $p$ 为奇素数， $n$ 为正整数， $\gcd(a,p)=1$ ，则 $a$ 是一个 $n$ 次剩余当且仅当 $a^{(p-1)/\delta}\equiv 1\pmod{p}$ ，其中 $\delta =\gcd(p-1,n)$ 。

## 元素的阶

> 定义：在模正整数 $m$ 意义下，对于一个正整数 $x$ 与 $m$ 互素，我们说 $x$ 的阶为 $t$ ，记作 $\operatorname{ord}_{m}(x)=t$ ，其中 $t$ 为满足 $x^{t}\equiv 1\pmod{m}$ 的最小 **正** 整数。

当模数明确时，也简记为 $\operatorname{ord}(x)$ ，而当 $x$ 与 $m$ 不互素时，则为未定义。

下面在模正整数 $m$ 意义下，且 $\gcd(x,m)=1$ ，考虑 $\operatorname{ord}(x)=t$ ，有

$$
x^{t}\equiv 1\pmod{m}
$$

且对于某个正整数 $k$ 存在

$$
\left(x^{k}\right)^{\operatorname{ord}(x^{k})}\equiv 1\pmod{m}
$$

显然 $k\operatorname{ord}(x^{k})\geq t$ 且

$$
t\mid k\operatorname{ord}(x^{k})\implies \frac{t}{\gcd(t,k)}\mid \operatorname{ord}(x^{k})
$$

又因为

$$
\left(x^{k}\right)^{t/\gcd(t,k)}=\left(x^{t}\right)^{k/\gcd(t,k)}\equiv 1\pmod{m}
$$

我们有

$$
\left.
\begin{aligned}
\left(x^{t/\gcd(t,k)}\right)^{k}\equiv 1\pmod{m}\\
\left(x^{\operatorname{ord}(x^{k})}\right)^{k}\equiv 1\pmod{m}
\end{aligned}
\right\}
\implies \frac{t}{\gcd(t,k)}\geq \operatorname{ord}(x^{k}),\quad \operatorname{ord}(x^{k})\mid \frac{t}{\gcd(t,k)}
$$

综上，有 $\operatorname{ord}(x^{k})=\frac{\operatorname{ord}(x)}{\gcd(\operatorname{ord}(x),k)}$ 。

当模数 $m$ 为奇素数时，原根 $g$ 的阶为 $m-1$ 。

## Tonelli-Shanks 算法

设 $p$ 为奇素数，求关于 $x$ 的同余方程 $x^{2}\equiv a\pmod{p}$ 的解（不考虑 $a\equiv 0\pmod{p}$ 的情况）。

使用欧拉准则判断方程是否有解，若有解，则 $a^{\frac{p-1}{2}}\equiv 1\pmod{p}$ 否则 $a^{\frac{p-1}{2}}\equiv -1\pmod{p}$ 。

下面仅考虑有解的情况。

**特殊情况** ：若 $p\bmod{4}=3$ 那么有

$$
\left(a^{\frac{p+1}{4}}\right)^{2}\equiv a^{\frac{p+1}{2}}\equiv x^{p+1}\equiv x^{2}\cdot x^{p-1}\equiv x^{2}\pmod{p}
$$

那么 $a^{\frac{p+1}{4}}$ 为一个解。我们可以在参考文献中找到另一种特殊情况，但是个人认为没有必要。

找到 $r,s$ 满足 $2^{r}\cdot s=p-1$ 且 $s$ 为奇数，在 $\mathbb{F} _ p ^\times$ 中用随机方法寻找一个二次 **非** 剩余 $v$ ，存在原根 $g^{k}\equiv v\pmod{p}$ 且 $k$ 为奇数，那么对于 $\operatorname{ord}(v^{s})=\operatorname{ord}(g^{sk})=\frac{2^{r}\cdot s}{\gcd(2^{r}\cdot s,sk)}=2^{r}$ ，令 $x_{0}=a^{\frac{s+1}{2}}\bmod{p},w=v^{s}\bmod{p}$ ，显然 $v^{s}$ 的阶为 $2^{r}$ ，对于 $x_{0}$ ，有

$$
\left(\frac{x_{0}^{2}}{a}\right)^{2^{r-1}}\equiv \left(\frac{a^{s+1}}{a}\right)^{2^{r-1}}\equiv a^{2^{r-1}\cdot s}\equiv a^{\frac{p-1}{2}}\equiv 1\pmod{p}
$$

令 $\displaystyle 2^{t_{0}}=\operatorname{ord}\left(\frac{x_{0}^{2}}{a}\right)$ （可以发现 $x_{0}^{2}/a=a^{s}$ 的阶是二的幂次），且设

$$
x_{i+1}=x_{i}\cdot w^{2^{r-t_{i}-1}},\quad 2^{t_{i+1}}=\operatorname{ord}\left(\frac{x_{i+1}^{2}}{a}\right)
$$

注意到 $\displaystyle \operatorname{ord}\left(\frac{x_{i}^{2}}{a}\right)=2^{t_{i}}\implies\left(\frac{x_{i}^{2}}{a}\right)^{2^{t_{i}-1}}\equiv -1\pmod{p}$ ，同样的 $\operatorname{ord}(w)=2^{r}\implies w^{2^{r-1}}\equiv -1\pmod{p}$ （两个阶为二的幂次的元素的乘积的阶也为二的幂次），那么

$$
\begin{aligned}
\left(\frac{x_{i+1}^{2}}{a}\right)^{2^{t_{i}-1}}&\equiv\left(\frac{\left(x_{i}\cdot w^{2^{r-t_{i}-1}}\right)^{2}}{a}\right)^{2^{t_{i}-1}}\\
&\equiv \left(\frac{x_{i}^{2}}{a}\right)^{2^{t_{i}-1}}\left(w^{2\cdot 2^{r-t_{i}-1}}\right)^{2^{t_{i}-1}}\\
&\equiv -1\cdot -1\\
&\equiv 1\pmod{p}
\end{aligned}
$$

可以发现 $t_{i+1}\lt t_{i}$ ，而 $t_{0}\lt r\lt \log_{2}(p)$ ，那么 $t_{0}$ 可枚举计算，而 $t_{i}$ 每一次至少减少 $1$ 最多减少 $\log_{2}(p)$ 次，当 $t_{n}=0$ 时有 $x_{n}^{2}\equiv a\pmod{p}$ 得到了一个解。


## Cipolla 算法

与上述问题相同，我们寻找一个多项式 $f(x)=x^2-tx+a\in\mathbb{F}_p[x]$ 且 $f(x)$ 在 $\mathbb{F}_p[x]$ 上不可约（即 $t^2-4a$ 为二次非剩余，使用随机方法寻找 $t$ 期望需要两次，但是这里的证明不是“显然”的），此时 $\mathbb{F}_p[x]/f(x)$ 是一个有 $p^2$ 个元素的域。我们计算 $x^{(p+1)/2}\bmod{f(x)}$ 为一个解。

该算法的时间是 $O(\log p)$ 的，快于上述 Tonelli-Shanks 算法（时间为 $O(\log^2 p)$ 若乘法为 $O(1)$ ）。

## Hensel lifting 求模素数幂次平方根的逆元

与牛顿迭代法一样，构造 $ f(x)=\frac{1}{x^{2}}-a$ ，一次迭代可表示为 $x_{n+1}=x_{n}-\frac{1/x_{n}^{2}-a}{-2/x_{n}^{3}}=x_{n}+x_{n}\left(\frac{1-ax_{n}^{2}} {2}\right)$ 。令 $\Phi(x)=x+x\left(\frac{1-ax^{2}}{2}\right)$ 。假设我们已经得到 $a$ 在模 **奇** 素数 $p$ 意义下的平方根的逆元 $b$ 满足 $b^{2}\equiv a^{-1}\pmod{p}$ ，认为 $(\Phi(b))^{2}\equiv a^{-1}\pmod{p^{2}}$ 。因为存在某个整数 $k$ 满足 $ab^{2}\equiv 1+kp\pmod{p^{2}}$ ，记 $b^{2}\equiv a^{-1}(1+kp)\pmod{p^{2}}$ ，有

$$
\begin{aligned}
(\Phi(b))^{2}&=\left(b+b\left(\frac{1-ab^{2}}{2}\right)\right)^{2}\\
&=\frac{9b^{2}-6ab^{4}+a^{2}b^{6}}{4}\\
&\equiv \frac{9(a^{-1}(1+kp))-6(a^{-1}(1+kp)^{2})+a^{-1}(1+kp)^{3}}{4}\pmod{p^{2}}\\
&\equiv \frac{a^{-1}}{4}(9(1+kp)-6(1+kp)^{2}+(1+kp)^{3})\pmod{p^{2}}\\
&\equiv \frac{a^{-1}}{4}(4-3k^{2}p^{2}+k^{3}p^{3})\pmod{p^{2}}\\
&\equiv a^{-1}\pmod{p^{2}}
\end{aligned}
$$

$\square$

不直接求其平方根而求其平方根的逆元是因为求平方根过程中也要维护逆元。

## 参考文献

- Jeremy Booher. [Square Roots in Finite Fields and Quadratic Nonresidues](https://www.math.arizona.edu/~jeremybooher/expos/sqr_qnr.pdf).
- A. Menezes, P. van Oorschot and S. Vanstone. [Handbook of Applied Cryptography](http://cacr.uwaterloo.ca/hac/), 1996.

