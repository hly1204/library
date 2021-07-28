## 常用 NTT 友好的模数

我们知道 NTT 友好的模数 $p$ 是素数且 $-1\bmod{p}$ 一定是二次剩余。在 $\mathbb{C}$ 中的 FFT 依靠的就是幂次为 $1$ 的元素即单位根，而在 NTT 中我们可以知道也存在阶为 $2$ 的幂次的元素，于是可以做 radix-2 NTT ，但 FFT 显然更灵活。

根据 Legendre 符号我们知道当 $p$ 为奇素数时， $\left(\frac{-1}{p}\right)\equiv (-1)^{(p-1)/2}\pmod{p}$ 若 $\left(\frac{-1}{p}\right)\equiv 1\pmod{p}$ 则为二次剩余，那么意味着 $p\bmod 4=1$ 。

NTT 模数是容易得到的，假设我们需要处理 $2^{23}$ 长的 NTT ，意味着需要其有阶为 $2^{23}$ 的元素，而 $\varphi(p)=p-1=2^{23}\cdot t$ 其中 $t\bmod 2=1$ 此时其中一定有元素的阶整除 $2^{23}$ ，我们枚举 $t$ 并依次进行素性测试即可。

| 素数 $p$ | 周期 |
| :----: | :----: |
| $998244353$ | $2^{23}$ |
| $897581057$  | $2^{23}$ |
| $880803841$ | $2^{23}$ |
| $645922817$ | $2^{23}$ |
| $595591169$ | $2^{23}$ |
| $377487361$ | $2^{23}$ |

## radix-2 NTT 的简单描述

在参考文献中该算法被称为 original radix-2 NTT 或 classical radix-2 NTT ，最早由 Fiduccia 发现可以表示为

$$
\begin{aligned}
\mathbb{F} _ p\lbrack x\rbrack /(x^{2m}-b^2)&\to \mathbb{F} _ p\lbrack x\rbrack /(x^m-b)\\
&\times \mathbb{F} _ p\lbrack x\rbrack /(x^m+b)
\end{aligned}
$$

输入 $f\bmod (x^{2m}-b^2)$ 计算 $f_Y=f\bmod (x^m-b)$ 和 $f_Z=f\bmod (x^m+b)$ 。令 $f\bmod (x^{2m}-b^2)=f_B+f_A\cdot x^m$ 其中 $f_B=(f\bmod{(x^{2m}-b^2)})\bmod{x^m}$ 那么

$$
\begin{bmatrix}
f_Y\\f_Z
\end{bmatrix}=
\begin{bmatrix}
1&1\\-1&1
\end{bmatrix}
\begin{bmatrix}
b\cdot f_A\\f_B
\end{bmatrix}
$$

当 $2b$ 可逆时该算法可逆，所以一般应用于特征不为 $2$ 的域，而 radix-3 NTT 则适用于特征为 $2$ 的域（如 $\chi (\mathbb{F} _ {2^n})=2$ ）。

## 预处理单位根的手法

令 $\zeta_n\in\mathbb{F} _ p$ 表示 $\operatorname{ord}(\zeta_n)=n$ 的某个数，且 $\zeta _ {2n}^2=\zeta_n$ ，使用 $\mathrm{i}\in\mathbb{F} _ p$ 表示 $\mathrm{i}^2\equiv -1\pmod{p}$ 的某个数（一般存在两个，但这里一直指代某一个而不是任意一个）。

| 单位根 | 二进制 |
| :-: | :-: |
| $\zeta_8^0=1$ | 000 |
| $\zeta_8^1$ | 001 |
| $\zeta_8^2$ | 010 |
| $\zeta_8^3$ | 011 |
| $\zeta_8^4=-1$ | 100 |
| $\zeta_8^5$ | 101 |
| $\zeta_8^6$ | 110 |
| $\zeta_8^7$ | 111 |

位逆序置换后的顺序为我们使用时的顺序，在 Bernstein 论文中的“分治”树结构清晰的说明了这一点。

| 单位根 | 二进制 |
| :-: | :-: |
| $\zeta_8^0=1$ | 000 |
| $\zeta_8^4=-1$ | 100 |
| $\zeta_8^2=\mathrm{i}$ | 010 |
| $\zeta_8^6=-\mathrm{i}$ | 110 |
| $\zeta_8^1=\sqrt{\mathrm{i}}$ | 001 |
| $\zeta_8^5=-\sqrt{\mathrm{i}}$ | 101 |
| $\zeta_8^3=\sqrt{-\mathrm{i}}$ | 011 |
| $\zeta_8^7=-\sqrt{-\mathrm{i}}$ | 111 |

观察到第一行和第二行、第三行和第四行等都互为相反数，也就是只要知道其中一个，截取表格中的一半并扩展有

| 单位根 | ROOT 数组下标 |
| :-: | :-: |
| $1$ | $0$ |
| $\zeta_4=(1\cdot \zeta_4)=\mathrm{i}$ | $1$ |
| $\zeta_8=(\zeta_4\cdot \zeta_8^7)=\sqrt{\mathrm{i}}$ | $2$ |
| $\zeta_8^3=(\zeta_8\cdot \zeta_4)=\sqrt{-\mathrm{i}}$ | $3$ |
| $\zeta _ {16}=(\zeta_8^3\cdot \zeta _ {16}^{11})$ | $4$ |
| $\zeta _ {16}^5=(\zeta _ {16}\cdot \zeta_4)$ | $5$ |
| $\zeta _ {16}^3=\zeta _ {16}\cdot\zeta_8=(\zeta _ {16}^5\cdot \zeta_8^7)$ | $6$ |
| $\zeta _ {16}^7=\zeta _ {16}\cdot\zeta_8^3=(\zeta _ {16}^3\cdot \zeta_4)$ | $7$ |
| $\zeta _ {32}=(\zeta _ {16}^7\cdot \zeta _ {32}^{19})$ | $8$ |
| $\zeta _ {32}^9=(\zeta _ {32}\cdot \zeta_4)$ | $9$ |
| $\zeta _ {32}^5=\zeta _ {32}\cdot \zeta_8=(\zeta _ {32}^9\cdot \zeta_8^7)$ | $10$ |
| $\zeta _ {32}^{13}=\zeta _ {32}\cdot \zeta_8^3=(\zeta _ {32}^{11}\cdot \zeta_4)$ | $11$ |

考虑

$$
\mathrm{ROOT} _ i=
\begin{cases}
1,&i=0,\\
\zeta _ {4i},&i\text{ is power of }2,\\
\zeta _ {4 \lfloor i/4\rfloor}\cdot \mathrm{ROOT} _ {i-4\lfloor i/4\rfloor},&\text{otherwise}.
\end{cases}
$$

我们可以做到在线性时空预处理，但仍不够满意，令 $\operatorname{bsr}(i)$ 表示 bit scan reverse ，即二进制表示中末尾零的数量，考虑

$$
\mathrm{ROOT} _ i=
\begin{cases}
1,&i=0,\\
\mathrm{ROOT} _ {i-1}\cdot \mathrm{DW} _ {\operatorname{bsr}(i)},&i\gt 0.
\end{cases}
$$

其中

| 单位根 | DW 数组下标 |
| :-: | :-: |
| $\zeta_4$ | $0$ |
| $\zeta_8^7=\zeta_8\cdot \zeta_4^{-1}$ | $1$ |
| $\zeta _ {16}^{11}=\zeta _ {16}\cdot \zeta_4^{-1}\cdot \zeta_8^{-1}$ | $2$ |
| $\zeta _ {32}^{19}=\zeta _ {32}\cdot \zeta_4^{-1}\cdot \zeta_8^{-1}\cdot \zeta _ {16}^{-1}$ | $3$ |
| $\vdots$ | $\vdots$ |
| $\zeta _ {2^{n+2}}\cdot \zeta_4^{-1}\cdot \zeta_8^{-1}\cdots \zeta _ {2^{n+1}}^{-1}$ | $n$ |

该方案使得单位根可在 $O(\log n)$ 空间预处理且在运算时进行计算，且由于 classical radix-2 NTT 算法在最内层循环中所用单位根为同一个，计算量较小，在使用 Montgomery 乘法时优于处理所有单位根并一一索引的方法。

## 参考文献

- Daniel J. Bernstein. [Multidigit Multiplication For Mathematicians](https://www.researchgate.net/publication/2370542_Multidigit_Multiplication_For_Mathematicians).
- Todd Mateer. [Fast Fourier Transform Algorithms with Applications](http://cr.yp.to/f2mult/mateer-thesis.pdf).