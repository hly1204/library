---
title: Factorial Modulo Prime
documentation_of: ./factorial_modulo_prime.hpp
---

## 阶乘模素数

此文译自参考文献！

令 $p$ 为素数模数，若省略同余符号，也认为在同余 $p$ 意义下运算。定义多项式 $f(x)=\prod _ {i=1}^n(x+i)$ 那么 $n!=f(0)$ ，令 $v=\left\lfloor \sqrt{n}\right\rfloor$ 和 $g(x)=\prod _ {i=1}^v(x+i)$ 那么

$$
n! =\left(\prod _ {i=0}^{v-1}g(vi)\right)\cdot \prod _ {i=v^2+1}^ni
$$

后者暴力计算时间为 $O(p^{1/2})$ 可以无视，我们只要能快速计算 $g(0),g(v),\dots ,g(v(v-1))$ 就好了。

### $O(p^{1/2}\log ^2p)$ 计算的方法

使用多点求值对 $g(x)$ 求出 $g(0),g(v),\dots ,g(v(v-1))$ 即可，但因为运算量较大有时甚至不能说比 $O(p)$ 的实现更快速。

### $O(p^{1/2}\log p)$ 计算的方法

$g(x)$ 的根为 $-1,-2,\dots ,-v$ 为等差数列，且我们希望对 $g(x)$ 求的点值 $0,v,\dots ,v(v-1)$ 也是等差数列。在这里使用拉格朗日插值公式可以使计算量下降 $\log p$ 。

对于 $d$ 次多项式 $g_d(x)=\prod _ {i=1}^d(x+i)$ 计算 $g_d(0),g_d(v),\dots ,g_d(dv)$ 。此时可以通过 $O(d\log d)$ 的计算量求出 $g_{2d}(0),g_{2d}(v),\dots ,g_{2d}(2dv)$ 。

首先有 $g_{2d}(x)=g_d(x)\cdot g_d(x+d)$ 我们令 $G_d(i)=(g_d(i),g_d(v+i),\dots ,g_d(dv+i))$ 如果我们能从 $G_d(0)$ 计算 $G_d(d),G_d(dv),G_d(dv+d)$ 三组询问的话就可以解决了，在这里使用拉格朗日插值公式。

### 模拟

考虑 $g_1(x)=x+1$ 我们用 $2$ 个点 $g_1(0)=1,g_1(v)=v+1$ 可以唯一确定这个多项式，现要求 $g_2(0),g_2(v),g_2(2v)$ 因为 $g_2(x)=g_1(x)\cdot g_1(x+1)$ 于是我们只需求出 $g_1(2v)$ 和 $g_1(1),g_1(v+1)$ 和 $g_1(2v+1)$ 之后易得。

我们令 $h(x)=g_1(vx)$ 那么有 $h(0)=g_1(0),h(1)=g_1(v)$ 通过样本点平移计算 $h(2)=g_1(2v)$ 是简单的。

同样，已知 $h(0),h(1),h(2)$ 求 $h\left(\frac{1}{v}\right)=g_1(1),h\left(\frac{1}{v}+1\right)=g_1(v+1),h\left(\frac{1}{v}+2\right)=g_1(2v+1)$ 即得。

那么 $g_2(0)=g_1(0)g_1(1),g_2(v)=g_1(v)g_1(v+1),g_2(2v)=g_1(2v)g_1(2v+1)$ 。

在这里我们采取一种更简单的方法即令 $v=2^{\lceil \log_2\sqrt{n}\rceil}$ ，这样我们只需要倍增即可，无需额外的调整，最差时 $v\approx 2\sqrt{n}$ ；若需要多次询问，那么我们令 $v=\lfloor \sqrt{p}\rfloor$ 。

若考虑从 $g_d(0),g_d(v),\dots ,g_d(dv)$ 推出 $g_{d+1}(0),g_{d+1}(v),\dots ,g_{d+1}(dv+v)$ 显然可在线性时间做到（额外的一项暴力计算即可），这样我们可以求出任意的 $d$ 对应的点值，而不用在二的幂次处。在 [EntropyIncreaser 的提交记录](https://loj.ac/s/1110094) 中使用了不同的技术使得 DFT 的次数减少，具体的我们在刚开始维护 $g_1(0),g_1(1)$ 后计算 $g_1(2),g_1(3),g_1(4),g_1(5)$ 后得到 $g_2(0),g_2(2),g_2(4)$ 以此类推。

考虑 Wilson 定理 $(p-1)!\equiv -1\pmod{p}$ 可仅预处理前一半的阶乘。

## 某种线性递推序列

对于某种线性递推序列 $\lbrace a_i\rbrace _ {i=0}^\infty$ 我们认为其初值为一个向量 $\mathbf{v} _ 0$ 后有某个其中元素为度数至多为一的多项式的矩阵 $\mathbf{M}$ 满足 $\mathbf{v} _ {i+1}=\mathbf{M}\mathbf{v} _ {i}$ 。在这里我们可以将计算阶乘考虑为矩阵

$$
\begin{bmatrix}
n!
\end{bmatrix}
=\left(
\prod _ {i=0}^{n-1}
\begin{bmatrix}i+1\end{bmatrix}
\right)
\begin{bmatrix}
1
\end{bmatrix}
$$

类似的有

$$
\begin{bmatrix}
!n\\!(n+1)
\end{bmatrix}
=\left(
\prod _ {i=0}^{n-1}
\begin{bmatrix}
0&1\\i+1&i+1
\end{bmatrix}
\right)
\begin{bmatrix}
1\\0
\end{bmatrix}
$$

注意矩阵乘积是

$$
\begin{bmatrix}
0&1\\n&n
\end{bmatrix}
\cdots
\begin{bmatrix}
0&1\\2&2
\end{bmatrix}
\begin{bmatrix}
0&1\\1&1
\end{bmatrix}
$$

其中 $!n=n!\sum _ {k=0}^n\frac{(-1)^k}{k!}$ 是错位排列 $n$ 个物品的方案数（即 $\forall i$ 满足第 $i$ 个物品不在第 $i$ 个位置）。

$$
\begin{bmatrix}
!n\\(-1)^{n+1}
\end{bmatrix}
=\left(
\prod _ {i=0}^{n-1}
\begin{bmatrix}
i+1&1\\0&-1
\end{bmatrix}
\right)
\begin{bmatrix}
1\\-1
\end{bmatrix}
$$

$$
\begin{bmatrix}
(n+1)!\\\sum _ {i=0}^ni!
\end{bmatrix}
=\left(
\prod _ {i=0}^{n}
\begin{bmatrix}
i+1&0\\1&1
\end{bmatrix}
\right)
\begin{bmatrix}
1\\0
\end{bmatrix}
$$

$$
\begin{aligned}
\begin{bmatrix}
\binom{n}{m+1}\\
\sum _ {i=0}^m\binom{n}{i}
\end{bmatrix}
&=\left(
\prod _ {i=0}^{m}
\begin{bmatrix}
(n-i)/(i+1)&0\\1&1
\end{bmatrix}
\right)
\begin{bmatrix}
1\\0
\end{bmatrix}\\
&=
\frac{1}{(m+1)!}
\left(
\prod _ {i=0}^{m}
\begin{bmatrix}
n-i&0\\i+1&i+1
\end{bmatrix}
\right)
\begin{bmatrix}
1\\0
\end{bmatrix}
\end{aligned}
$$

全部摘自 Min\_25 的博客！

我对求调和数比较感兴趣，记 $H_n=\sum _ {k=1}^n\frac{1}{k}$ ，阅读了这篇 [文章](https://www.luogu.com.cn/blog/NaCly-Fish-blog/ji-yu-bei-zeng-wei-hu-duo-xiang-shi-dian-zhi-di-ji-suan) 但是其中的表记不是矩阵形式，而我们也可以将其改写为矩阵的形式如

$$
\begin{bmatrix}
(n+1)!\\(n+1)!H _ {n+1}
\end{bmatrix}=
\begin{bmatrix}
n+1&0\\1&n+1
\end{bmatrix}
\begin{bmatrix}
n!\\n!H_n
\end{bmatrix}
,\quad n\gt 0
$$

那么

$$
\begin{bmatrix}
{n+1\brack 1}\\{n+1\brack 2}
\end{bmatrix}=
\begin{bmatrix}
n!\\n!H_n
\end{bmatrix}=
\left(
\prod _ {i=0}^{n-1}
\begin{bmatrix}
i+1&0\\1&i+1
\end{bmatrix}
\right)
\begin{bmatrix}
1\\0
\end{bmatrix}
$$

我们取 $v=\left\lfloor \sqrt{n}\right\rfloor$ 并维护

$$
\begin{aligned}
\mathbf{M} _ d(x)&=
\prod _ {i=1}^{d}
\begin{bmatrix}
x+i&0\\1&x+i
\end{bmatrix}\\
&=
\begin{bmatrix}
g_d(x)&0\\h_d(x)&g_d(x)
\end{bmatrix}
\end{aligned}
$$

的点值 $\mathbf{M} _ d(0),\mathbf{M} _ d(v),\dots $ 即 $g_d(x),h_d(x)$ 的点值，而

$$
\begin{aligned}
\mathbf{M} _ {2d}(x)&=
\mathbf{M} _ d(x+d)\mathbf{M} _ d(x)\\
&=
\begin{bmatrix}
g_d(x+d)&0\\h_d(x+d)&g_d(x+d)
\end{bmatrix}
\begin{bmatrix}
g_d(x)&0\\h_d(x)&g_d(x)
\end{bmatrix}\\
&=
\begin{bmatrix}
g_d(x)g_d(x+d)&0\\h_d(x+d)g_d(x)+g_d(x+d)h_d(x)&g_d(x)g_d(x+d)
\end{bmatrix}
\end{aligned}
$$

易维护，上述其余矩阵同理。

## 例题

[LOJ 6386 组合数前缀和](https://loj.ac/p/6386) 求 $\sum _ {i=0}^m\binom{n}{i}\bmod 998244353$ ，考虑维护矩阵

$$
\begin{aligned}
\mathbf{M} _ d(x)&=
\prod _ {i=1}^d
\begin{bmatrix}
-x+n+1-i&0\\
x+i&x+i
\end{bmatrix}\\
&=
\begin{bmatrix}
f_d(x)&0\\
g_d(x)&h_d(x)
\end{bmatrix}
\end{aligned}
$$

的点值 $\mathbf{M} _ d(0),\mathbf{M} _ d(v),\dots $ 而

$$
\begin{aligned}
\mathbf{M} _ {2d}(x)&=
\prod _ {i=1}^{2d}
\begin{bmatrix}
-x+n+1-i&0\\
x+i&x+i
\end{bmatrix}\\
&=
\left(
\prod _ {i=1}^d
\begin{bmatrix}
-x-d+n+1-i&0\\
x+d+i&x+d+i
\end{bmatrix}
\right)
\left(
\prod _ {i=1}^d
\begin{bmatrix}
-x+n+1-i&0\\
x+i&x+i
\end{bmatrix}
\right) \\
&=
\begin{bmatrix}
f_d(x+d)&0\\
g_d(x+d)&h_d(x+d)
\end{bmatrix}
\begin{bmatrix}
f_d(x)&0\\
g_d(x)&h_d(x)
\end{bmatrix} \\
&=
\begin{bmatrix}
f_d(x+d)f_d(x)&0\\
g_d(x+d)f_d(x)+h_d(x+d)g_d(x)&h_d(x+d)h_d(x)
\end{bmatrix}
\end{aligned}
$$

$\mathbf{M} _ {2d}(x)$ 右下角为阶乘中维护的点值。我们计算

$$
\begin{aligned}
\prod _ {i=0}^{m}
\begin{bmatrix}
n-i&0\\i+1&i+1
\end{bmatrix}=
\left(
\prod _ {i=(k+1)v}^m
\begin{bmatrix}
n-i&0\\
i+1&i+1
\end{bmatrix}
\right)
\begin{bmatrix}
f_v(kv)&0\\
g_v(kv)&h_v(kv)
\end{bmatrix}
\cdots
\begin{bmatrix}
f_v(v)&0\\
g_v(v)&h_v(v)
\end{bmatrix}
\begin{bmatrix}
f_v(0)&0\\
g_v(0)&h_v(0)
\end{bmatrix}
\end{aligned}
$$

即可。

```cpp
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

#include "math/formal_power_series/convolution.hpp"
#include "math/formal_power_series/sample_points_shift.hpp"
#include "modint/Montgomery_modint.hpp"

using mint = lib::MontModInt<998244353>;

/**
 * @brief 计算二项式系数前缀和
 * @param n
 * @param m m <= n
 * @return mint C(n, 0) + C(n, 1) + … + C(n, m)
 */
mint binomial_coeff_prefix_sum(mint n, mint m) {
  using u32 = std::uint32_t;
  u32 v     = 1;
  assert(static_cast<u32>(m) <= static_cast<u32>(n));
  while (v * v < static_cast<u32>(m)) v <<= 1;
  const mint ONE(1), mv(v), iv(mv.inv());
  std::vector<mint> f{n, n - mv}, g{ONE, mv + ONE}, h{ONE, mv + ONE};
  auto conv = lib::convolve_cyclic<mint>;
  for (u32 d = 1; d != v; d <<= 1) {
    auto f0 = lib::shift_sample_points(d, f, mint(d) + 1, conv);
    auto f1 = lib::shift_sample_points(d << 1 | 1, f, mint(d) * iv, conv);
    auto g0 = lib::shift_sample_points(d, g, mint(d) + 1, conv);
    auto g1 = lib::shift_sample_points(d << 1 | 1, g, mint(d) * iv, conv);
    auto h0 = lib::shift_sample_points(d, h, mint(d) + 1, conv);
    auto h1 = lib::shift_sample_points(d << 1 | 1, h, mint(d) * iv, conv);
    std::copy_n(f0.begin(), d, std::back_inserter(f));
    std::copy_n(g0.begin(), d, std::back_inserter(g));
    std::copy_n(h0.begin(), d, std::back_inserter(h));
    for (u32 i = 0; i != (d << 1 | 1); ++i)
      std::tie(f[i], g[i], h[i]) =
          std::make_tuple(f[i] * f1[i], f[i] * g1[i] + h1[i] * g[i], h1[i] * h[i]);
  }
  mint A(1), B(0), C(1);
  u32 pass = 0;
  for (int i = 0; pass + v <= static_cast<u32>(m); pass += v, ++i)
    std::tie(A, B, C) = std::make_tuple(A * f[i], A * g[i] + B * h[i], C * h[i]);
  for (; pass <= static_cast<u32>(m); ++pass)
    std::tie(A, B, C) = std::make_tuple(A * (n - pass), (A + B) * (pass + 1), C * (pass + 1));
  return B / C;
}

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int T;
  std::cin >> T;
  for (mint n, m; T != 0; --T) {
    std::cin >> n >> m;
    std::cout << binomial_coeff_prefix_sum(n, m) << '\n';
  }
  return 0;
}
```

## P-recursive 序列

上面的说法可能不太正确， Bostan 等的论文解决的是多项式为系数的线性递推

$$
u _ {n+d}=c _ {d-1}(n)u _ {n+d-1}+\cdots +c_0(n)u_n
$$

其中 $c_0(x),\dots ,c _ {d-1}(x)$ 都是在环 $R(x)$ 上的有理函数（当然，我们依然是只考虑有限域 $\mathbb{F} _ {p}(x)$ 且 $p$ 为足够大的素数），这样的线性递推序列被称为 holonomic （或 P-recursive ）序列，而 Bostan-Mori 算法解决的为 C-recursive 的线性递推序列。我们思考如何解决上式，首先模仿在 [常系数其次线性递推](https://oi-wiki.org/math/linear-recurrence/) 中对矩阵的构造，记 $c_i(x)=P_i(x)/Q_i(x)$ 我们有

$$
\underbrace{
\begin{bmatrix}
u _ {n+1}\\
u _ {n+2}\\
\vdots\\
u _ {n+d}
\end{bmatrix}} _ {v _ {n+1}}
=\underbrace{\begin{bmatrix}
&1&&\\
&&\ddots&\\
&&&1\\
\dfrac{P_0(n)}{Q_0(n)}&\dfrac{P_1(n)}{Q_1(n)}&\cdots &\dfrac{P _ {d-1}(n)}{Q _ {d-1}(n)}
\end{bmatrix}} _ {\mathbf{M} _ n}
\underbrace{
\begin{bmatrix}
u_n\\
u _ {n+1}\\
\vdots\\
u _ {n+d-1}
\end{bmatrix}} _ {v_n}
$$

## 微分方程

EI 指出一些简单的微分有限的生成函数（包含复合某些代数函数）可以表为微分方程，也可以表为 P-recursive 序列，使用上述算法，但证明和过程过于复杂我还没理解！

## 参考文献

- ZZQ 的[博客](https://www.cnblogs.com/zzqsblog/p/8408691.html)
- Min\_25 的[博客](http://min-25.hatenablog.com/entry/2017/04/10/215046)（已被删除）
- Alin Bostan, Pierrick Gaudry, and Eric Schost. Linear recurrences with polynomial coefficients and application to integer factorization and Cartier-Manin operator.
- Entropy Increaser. [关于整式递推机械化的尝试](https://blog.csdn.net/EI_Captain/article/details/108930959).