## radix-4 NTT 的简单描述

与 radix-2 NTT 类似的，我们使用

$$
\begin{aligned}
\mathbb{F} _ p\lbrack x\rbrack /(x^{4m}-b^4)&\to \mathbb{F} _ p\lbrack x\rbrack /(x^m-b)\\
&\times \mathbb{F} _ p\lbrack x\rbrack /(x^m+b)\\
&\times \mathbb{F} _ p\lbrack x\rbrack /(x^m-\mathrm{i}b)\\
&\times \mathbb{F} _ p\lbrack x\rbrack /(x^m+\mathrm{i}b)
\end{aligned}
$$

令 $f^{\circ}=f\bmod (x^{4m}-b^4)$ 计算 $f_W=f\bmod (x^m-b),f_X=f\bmod (x^m+b),f_Y=f\bmod (x-\mathrm{i}b),f_Z=f\bmod (x^m+\mathrm{i}b)$ 而将 $f^{\circ}$ 分为了四块多项式为 $f^{\circ}=f_A\cdot x^{3m}+f_B\cdot x^{2m}+f_C\cdot x^m+f_D$ 那么

$$
\begin{aligned}
f_W&=f_A\cdot b^3+f_B\cdot b^2+f_C\cdot b+f_D,\\
f_X&=-f_A\cdot b^3+f_B\cdot b^2-f_C\cdot b+f_D,\\
f_Y&=-\mathrm{i}\cdot f_A\cdot b^3-f_B\cdot b^2+\mathrm{i}\cdot f_C\cdot b+f_D\\
f_Z&=\mathrm{i}\cdot f_A\cdot b^3-f_B\cdot b^2-\mathrm{i}\cdot f_C\cdot b+f_D
\end{aligned}
$$

那么

$$
\begin{aligned}
\begin{bmatrix}
f_W\\
f_X\\
f_Y\\
f_Z
\end{bmatrix}&=
\begin{bmatrix}
1&1&1&1\\
-1&1&-1&1\\
-\mathrm{i}&-1&\mathrm{i}&1\\
\mathrm{i}&-1&-\mathrm{i}&1
\end{bmatrix}
\begin{bmatrix}
b^3\cdot f_A\\
b^2\cdot f_B\\
b\cdot f_C\\
f_D
\end{bmatrix}\\
&=
\begin{bmatrix}
b^3&b^2&b&1\\
-b^3&b^2&-b&1\\
-\mathrm{i}\cdot b^3&-b^2&\mathrm{i}\cdot b&1\\
\mathrm{i}\cdot b^3&-b^2&-\mathrm{i}\cdot b&1
\end{bmatrix}
\begin{bmatrix}
f_A\\
f_B\\
f_C\\
f_D
\end{bmatrix}
\end{aligned}
$$

其逆运算可表示为

$$
\begin{bmatrix}
f_A\\
f_B\\
f_C\\
f_D
\end{bmatrix}=
\frac{1}{4}
\begin{bmatrix}
b^{-3}&-b^{-3}&\mathrm{i}\cdot b^{-3}&-\mathrm{i}\cdot b^{-3}\\
b^{-2}&b^{-2}&-b^{-2}&-b^{-2}\\
b^{-1}&-b^{-1}&-\mathrm{i}\cdot b^{-1}&\mathrm{i}\cdot b^{-1}\\
1&1&1&1
\end{bmatrix}
\begin{bmatrix}
f_W\\
f_X\\
f_Y\\
f_Z
\end{bmatrix}
$$

逆矩阵为原矩阵转置后并对所有 entries 取逆元。

该算法为 classical radix-4 NTT 而 twisted radix-4 NTT 也是类似的，但是最内层循环中需要用到“更多的”单位根，故无法在实践中采用。

## 预处理单位根的手法

当我们要进行 radix-4 NTT 的多项式“长度”为二的幂次时只需进行一步 radix-2 NTT 即可，主要考虑为四的幂次时。

考虑使用到的 ROOT 数组为

| 单位根 | ROOT 数组下标 |
| :-: | :-: |
| $1$ | $0$ |
| $\zeta_8=(1\cdot \zeta_8)$ | $1$ |
| $\zeta _ {16}=(\zeta_8\cdot \zeta _ {16}^{15})$ | $2$ |
| $\zeta _ {16}^3=(\zeta _ {16}\cdot \zeta_8)$ | $3$ |
| $\zeta _ {32}=(\zeta _ {16}^3\cdot \zeta _ {32}^{27})$ | $4$ |
| $\zeta _ {32}^5=(\zeta _ {32}\cdot \zeta_8)$ | $5$ |

那么

$$
\mathrm{ROOT} _ i=
\begin{cases}
1,&i=0,\\
\mathrm{ROOT} _ {i-1}\cdot \mathrm{DW} _ {\operatorname{bsf}(i)},&i\gt 0.
\end{cases}
$$

所以 DW 数组为

| 单位根 | DW 数组下标 |
| :-: | :-: |
| $\zeta_8$ | $0$ |
| $\zeta _ {16}^{15}=\zeta_8\cdot \zeta_4^{-1}\cdot \zeta _ {16}$ | $1$ |
| $\zeta _ {32}^{27}=\zeta _ {16}^{15}\cdot \zeta_8^{-1}\cdot \zeta _ {32}$ | $2$ |
| $\vdots$ | $\vdots$ |
| $\mathrm{DW} _ {k-1}\cdot \zeta _ {2^{k+1}}^{-1}\cdot \zeta _ {2^{k+3}}$ | $k$ |

我很佩服能想到如此漂亮的手法的 Min\_25 ！

若我们使用 $998244353$ 计算 $2^{23}$ 长的 NTT 那么 DW 数组中 $k=20$ （同 radix-2 NTT 文末）。

## 参考文献

- Todd Mateer. [Fast Fourier Transform Algorithms with Applications](http://cr.yp.to/f2mult/mateer-thesis.pdf).
- Min\_25 的[提交记录](https://loj.ac/s/1016238)