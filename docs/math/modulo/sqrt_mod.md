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

部分同余符号省略。

设 $p$ 为奇素数，令 $a_0,a_1,r,u\in \mathbb{F} _ p$ 且 $u$ 为二次剩余， $r^2-u$ 为二次非剩余且 $a_0+a_1x$ 为 $r-x$ 在环 $\mathbb{F} _ p[x]/(x^2-(r^2-u))$ 中的 $(p+1)/2$ 次幂。那么 $a_1=0$ 且 $a_0^2=u$。

证明：

$$
\begin{aligned}
x^p&=x(x^2)^{(p-1)/2}\\
&=x(r^2-u)^{(p-1)/2} \quad (\because x^2\equiv r^2-u\pmod{(x^2-(r^2-u))})\\
&=-x \quad (\because \text{Euler's criterion})
\end{aligned}
$$

所以 $(r-x)^p=r+x$ 。因此

$$
\begin{aligned}
a_0^2+a_1^2(r^2-u)+2a_0a_1x&=(a_0+a_1x)^2\\
&=(r-x)^{p+1}\\
&=(r+x)(r-x)\\
&=r^2-x^2\\
&=u
\end{aligned}
$$

若 $a_1\neq 0$ 则 $a_0=0$，所以 $r^2-u=u/a_1^2$ 所以 $r^2-u$ 为二次剩余，不符合定义。因此 $a_1=0$ 且 $a_0^2=u$。

该算法的时间是 $O(\log p)$ 的，快于上述 Tonelli-Shanks 算法（时间为 $O(\log^2 p)$ 若乘法为 $O(1)$ ）。

## Legendre 算法

部分同余符号省略。

设 $p$ 为奇素数，令 $a_0,a_1,r,u\in \mathbb{F} _ p$ 且 $u$ 为二次剩余，$r^2-u$ 为二次非剩余且 $a_0+a_1x$ 为 $r-x$ 在环 $\mathbb{F} _ p[x]/(x^2-u)$ 中的 $(p-1)/2$ 次幂。那么 $a_0=0$ 且 $a_1^{-2}=u$。

证明：考虑选择一个 $u$ 的平方根 $v$ 。那么 $(r-v)(r+v)=r^2-v^2=r^2-u$ 为二次非剩余，所以 $(r-v)^{(p-1)/2}(r+v)^{(p-1)/2}=-1$ 。

存在环态射（ morphism ） $\varphi :\mathbb{F} _ p[x]/(x^2-u)\to \mathbb{F} _ p\times \mathbb{F} _ p$ （我认为可以理解为 $\mathbb{F} _ p[x]/(x\pm u)$ ）将 $x$ 映射为 $(v,-v)$ 那么

$$
\begin{aligned}
(a_0+a_1v,a_0-a_1v)&=\varphi (a_0+a_1x)\\
&=\varphi (r-x)^{(p-1)/2}\\
&=((r-v)^{(p-1)/2},(r+v)^{(p-1)/2})\\
&=(\pm 1,\mp 1)
\end{aligned}
$$

所以 $2a_0=(\pm 1)+(\mp 1)=0$ 且 $2a_1v=(\pm 1)-(\mp 1)=\pm 2$ 。

## Pocklington 算法

沿用 Legendre 算法的定义和 $p\in 1+4\mathbb{Z}$ 且记 $b_0+b_1x$ 为 $r-x$ 在 $\mathbb{F} _ p[x]/(x^2-u)$ 中的 $(p-1)/4$ 次幂。那么 $(b_0/b_1)^2=-u$ 。

证明：

$$
\begin{aligned}
b_0^2+b_1^2u+2b_0b_1x&=(b_0+b_1x)^2\\
&=a_0+a_1x\\
&=a_1x
\end{aligned}
$$

根据二次互反律我们知道 $-1$ 在 $p\bmod{4}=1$ 时是模 $p$ 意义下的二次剩余。

这个算法有更通用的说法，详见参考文献。

## Hensel lifting 求模素数幂次平方根的逆元

也称为牛顿迭代法。构造 $ f(x)=\frac{1}{x^{2}}-a$ ，一次迭代可表示为 $x_{n+1}=x_{n}-\frac{1/x_{n}^{2}-a}{-2/x_{n}^{3}}=x_{n}+x_{n}\left(\frac{1-ax_{n}^{2}} {2}\right)$ 。令 $\Phi(x)=x+x\left(\frac{1-ax^{2}}{2}\right)$ 。假设我们已经得到 $a$ 在模 **奇** 素数 $p$ 意义下的平方根的逆元 $b$ 满足 $b^{2}\equiv a^{-1}\pmod{p}$ ，认为 $(\Phi(b))^{2}\equiv a^{-1}\pmod{p^{2}}$ 。因为存在某个整数 $k$ 满足 $ab^{2}\equiv 1+kp\pmod{p^{2}}$ ，记 $b^{2}\equiv a^{-1}(1+kp)\pmod{p^{2}}$ ，有

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

尽管 Cipolla 算法和 Tonelli-Shanks 算法都可以扩展到在模奇素数 $p$ 的幂次意义下求平方根，但我认为还是采用牛顿迭代法更好。

## 重新认识 Tonelli-Shanks 算法

尽管上文描述了 Tonelli-Shanks 算法，但其距离算法的本质太远，仅仅是算法流程，该算法本质是基于离散对数的算法，而 Adleman-Manders-Miller 算法是 Tonelli-Shanks 算法的一种扩张。

依然考虑奇素数 $p$ 和 $p-1=2^n\cdot m$ 其中 $m$ 为奇数。令 $g,r,u,v\in\mathbb{F} _ p$ 且 $g=r^m$ 且 $r$ 为二次非剩余， $u$ 非零和 $v=u^{(m-1)/2}$ 。那么存在整数 $e\in \lbrace 0,1,2,\dots ,2^n-1\rbrace$ 满足 $uv^2=g^e$ 。若 $u$ 为二次剩余，那么 $e$ 为偶数且 $(uvg^{-e/2})^2=u$ 。

证明：

$$
\begin{aligned}
g^{2^n}&=r^{2^n\cdot m}\\
&=r^{p-1}\\
&=1
\end{aligned}
$$

但是

$$
\begin{aligned}
g^{2^{n-1}}&=r^{2^{n-1}\cdot m}\\
&=r^{(p-1)/2}\\
&=-1
\end{aligned}
$$

所以 $g$ 的阶为 $2^n$ ；且 $uv^2=u^m$ 为 $1$ 的一个 $2^n$ 次根（因为 $u^{m\cdot 2^n}=u^{p-1}=1$ 显然），所以它是 $g$ 的幂次，记作 $g^e$ 。若 $u$ 为二次剩余则 $g^{2^{n-1}\cdot e}=u^{(p-1)/2}=1$ 所以 $e$ 为偶数且 $(uvg^{-e/2})^2=u^2v^2g^{-e}=u$ 。

我们要借助离散对数来计算 $e$ 。 Tonelli 和 Shanks 通过一个 bit 一个 bit 来计算 $e$ 。令 $e$ 在二进制下表示为 $e=e_0+2e_1+4e_2+\cdots$ 且 $e_k\in\lbrace 0,1\rbrace$ 。我们假设 $e_0=0$ （因为 $e$ 为偶数才能使得 $u$ 是二次剩余，这由 Legendre 符号给出）然后计算 $e_1$ 后 $e_2$ 等等。给出 $g^e$ 和 $e_0,\dots e _ {k-1}$ ， Tonelli 和 Shanks 使用下面的方法来计算 $e_k$

$$
\left(g^eg^{-(e\bmod 2^k)}\right)^{2^{n-1-k}}=g^{2^{n-1}\cdot e_k}=
\begin{cases}
1&\text{if }e_k=0\text{,}\\
-1&\text{if }e_k=1\text{.}
\end{cases}
$$

Tonelli 的算法还要更加复杂一些，上面的方法由 Shanks 提出。

聪明的您可能发现，和上面验证阶的算法本质是一样的！

通过一些预处理，我们可以一次算出 $e$ 的多个 bit ，详见参考文献。

另外 37zigen's HP 中对于该算法的介绍也非常漂亮，和上述解释是一致的，但是使用了 index 来替代阶，我们使用 $(\mathbb{F} _ p\setminus \lbrace 0\rbrace, \times)\cong (\mathbb{Z}/2^n\mathbb{Z}\times \mathbb{Z}/m\mathbb{Z}, +)$ 将乘法与 index 的加法一一对应，左边也常用记号 $\mathbb{F} _ p^{\times}=\mathbb{F} _ p\setminus \lbrace 0\rbrace$ 表示。

## 参考文献

- Jeremy Booher. [Square Roots in Finite Fields and Quadratic Nonresidues](https://www.math.arizona.edu/~jeremybooher/expos/sqr_qnr.pdf).
- A. Menezes, P. van Oorschot and S. Vanstone. [Handbook of Applied Cryptography](http://cacr.uwaterloo.ca/hac/), 1996.
- [Nyaan's Library](https://nyaannyaan.github.io/library/modulo/mod-kth-root.hpp)
- [Tonelli-Shanks algorithm（sugarknriさん、Min_25さん、37zigenの解法）](https://yukicoder.me/problems/no/981/editorial)
- [Tonelli-Shanks のアルゴリズム - 37zigenのHP](https://37zigen.com/tonelli-shanks-algorithm/)
- Adleman, L. M., K. Manders, and G. Miller: 1977, `On taking roots in finite fields'. In: 18th IEEE Symposium on Foundations of Computer Science. pp. 175-177
- Daniel. J. Bernstein. Faster Square Roots in Annoying Finite Fields.