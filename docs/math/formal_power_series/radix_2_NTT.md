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