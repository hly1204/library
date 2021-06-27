## Montgomery modint

类 `MontgomeryModInt` 是一个自动取模的类型，且模数 $M\in(1,2^{30}), M\bmod 2=1$ 。重载有基本的四则运算符号和比较运算符（ `==` 和 `!=` ）。

- `MontgomeryModInt<M>::value_type` 为内部数据类型，即 `std::uint32_t` 。
- `MontgomeryModInt<M>::get_mod()` 返回模数 $M$ 且类型为 `std::uint32_t` 。
- `using MontModInt = MontgomeryModInt` 为一个辅助模板。

成员函数有

- `pow(k)` 接收非负整型。
- `inv()` 返回其逆元，注意这里并未处理不存在的情况。
- `get_primitive_root_prime()` 返回素数的最小原根，配合 NTT 算法。

代码使用惰性的“修正”，在 `reduce` 函数后答案在 $[0,2M)$ 。

## Montgomery reduction

> 定义：对于 $N\gt 1$ 选择一个基数 $R$ 与 $N$ 互素且 $R\gt N$ 。令 $R^{-1}$ 和 $N'$ 满足 $0\lt R^{-1}\lt N$ 且 $0\lt N'\lt R$ 且 $RR^{-1}-NN'=1$ 。对于 $T$ 满足 $0\leq T\lt RN$ ，我们将一种快速计算 $TR^{-1}\bmod{N}$ 的算法称为 Montgomery reduction 。

Bézout 等式 $RR^{-1}-NN'=1$ 告诉我们 $N'\equiv -N^{-1}\pmod{R}$ 。

$$
\begin{array}{ll}
\textbf{procedure }\operatorname{REDC}(T) \\
\qquad m\gets (T\bmod R)N'\bmod{R} \\
\qquad t\gets (T+mN)/R \\
\qquad \textbf{if }t\geq N\textbf{ then return }t-N \\
\qquad \textbf{else return } t
\end{array}
$$

证明：观察到 $TN'\bmod R=TN'+kR$ 对于某个整数 $k$ 成立，那么

$$
t=(T+(TN'+kR)N)/R=(T+TN'N+kRN)/R
$$

而又因为 $N'N=-1+lR$ 对于某个整数 $l$ 成立，所以

$$
t=(T+T(-1+lR)+kRN)/R=lT+kN
$$

显然为整数。且因为 $0\leq T\lt RN,0\leq m\lt R$ 所以 $0\leq (T+mN)/R\lt 2N$ 。 $\square$

而在实践中通常选取 $R=2^{32}$ ，那么可以写下如下 C++ 代码

```cpp
typedef std::uint32_t u32;
typedef std::uint64_t u64;
// 预处理 N_p 作为 N' ，类型为 u32 ，模数 N 为奇数
u32 REDC(u64 T) { return T + u64(u32(T) * N_p) * N >> 32; }
```

其中我们没有处理 $t\geq N$ 的情况，这是因为假设选取的 $N\lt 2^{30}$ 此时返回值在 $[0,2N)$ 中，如果我们将两个 $T_{1},T_{2}$ 相乘再进行 REDC ，那么注意 REDC 的输入参数只要求 $[0,RN)$ 中即可，这样可以惰性的进行伪代码最后一步的“修正”过程。

假设我们需要在模奇数 $N$ 意义下对 $0\leq x\lt N$ 和 $0\leq y\lt N$ 计算 $xy\bmod N$，那么通过 $\operatorname{REDC}(x(R^{2}\bmod N))$ 计算 $xR\bmod N$ 再计算 $\operatorname{REDC}(xRy)$ 即可。这提示我们预处理 $R^{2}\bmod N$ 和 $N'$ 即可。

而 $N'$ 可以通过 Hensel lifting （可被视为 $p$-adic variant of Newton's method ）计算，因为 $N$ 为奇数，那么 $N^{-1}\bmod 2=1$ ，使用以下迭代

$$
x_{n+1}=x_{n}+x_{n}(1-bx_{n})
$$

假设 $x_{n}\equiv b^{-1}\pmod p$ 对于某个 $p$ 成立，那么 $x_{n}b\equiv 1+kp\pmod{p^{2}}$ 对于某个整数 $k$ 成立，那么

$$
\begin{aligned}x_{n+1}&=x_{n}(2-bx_{n})\\
&\equiv x_{n}(2-(1+kp))\pmod{p^{2}}\\
&\equiv b^{-1}(1+kp)(1-kp)\pmod{p^{2}}\\
&\equiv b^{-1}(1-k^{2}p^{2})\pmod{p^{2}}\\
&\equiv b^{-1}\pmod{p^{2}}\end{aligned}
$$

在这里我们只需将 $p$ 替换为 $2$ 即可。 $\square$

令 $x_{0}=1$ ，第一次迭代为 $x_{1}=x_{0}(2-Nx_{0})$ 这使我们发现 $x_{1}=2-N$ 而不论 $N\equiv 1\pmod{4}$ 或者 $N\equiv 3\pmod{4}$ 都有 $2-N\equiv N\pmod{4}$ 。

## 参考文献

- Peter L. Montgomery. Modular Multiplication Without Trial Division, 1985.
- Richard P. Brent and Paul Zimmermann, Modern Computer Arithmetic, Cambridge Monographs on Computational and Applied Mathematics (No. 18), Cambridge University Press, November 2010, 236 pages
- Nyaan 的[博客](https://nyaannyaan.github.io/docs/modulo/montgomery/)

