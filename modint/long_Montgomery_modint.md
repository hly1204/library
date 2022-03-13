---
title: Long Montgomery Modint
documentation_of: ./long_Montgomery_modint.hpp
---

## long Montgomery modint

类 `LongMontgomeryModInt` 是一个自动取模的类型，且模数 $M\in(1,2^{63}), M\bmod 2=1$ 。重载有基本的四则运算符号和比较运算符（ `==` 和 `!=` ）。

- `LongMontgomeryModInt<M>::value_type` 为内部数据类型，即 `std::uint64_t` 。
- `LongMontgomeryModInt<M>::get_mod()` 返回模数 $M$ 且类型为 `std::uint64_t` 。
- `using LongMontModInt = LongMontgomeryModInt` 为一个辅助模板。

成员函数有

- `pow(k)` 接收非负整型。
- `inv()` 返回其逆元，注意这里并未处理不存在的情况。
- `get_primitive_root_prime()` 返回素数的最小原根，配合 NTT 算法。

代码不使用惰性的“修正”，在每次 `reduce` 函数的末尾都会调整答案在 $[0,M)$ 。

在测试时发现，使用 `if` 语句与使用更多的运算符实现差别不大，虽然在 <https://godbolt.org/> 上开启 `-O2` 选项后 `if` 语句的汇编更短。不开启优化时会产生“分支预测”，这不是我想要的。

## MSVC 和 GNUC 的分别实现

在 GNUC 中， `__int128` 和 `int` 类型是相似的，都可以用 `unsigned` 前缀来表示他的无符号版本，其余特性也是类似的。

在 MSVC 中则没有定义，我们可以在 <https://docs.microsoft.com/en-us/cpp/intrinsics/umulh?view=msvc-160> 找到 `__umulh(x, y)` 函数，返回两个 `__int64` 相乘的高位，在 <https://docs.microsoft.com/en-us/cpp/intrinsics/umul128?view=msvc-160> 找到 `_umul128(x, y, high)` 返回值为低位而 `high` 为一个指针，存入高位的结果。

我没有尝试更精细的实现。需要注意的是 MSVC 中这两个函数非 `constexpr` 函数所以暂时不使用。

## Montgomery reduction

依然沿用 Montgomery modint 文档中的定义，仅修改令 $RR^{-1}+NN'=1$ ，即仅 $NN'\equiv 1\pmod{R}$ 与上述不同，显然存在整数 $k,l$ 满足 $m=TN'\bmod{R}=TN'+kR$ 且 $NN'=1+lR$ ，那么

$$
\begin{aligned}
(T-mN)/R&=(T-(TN'+kR)N)/R\\
&=(T-(TNN'+kRN))/R\\
&=(T-T(1+lR)-kRN)/R\\
&=-lT-kN
\end{aligned}
$$

显然为整数，且 $-N\lt (T-mN)/R\lt N$ 。

显然 $a\bmod{b}=a-\lfloor a/b\rfloor \cdot b \implies \lfloor a/b \rfloor =(a-(a\bmod{b}))/b$ ，那么

$$
\begin{aligned}
\lfloor T/R\rfloor -\lfloor mN/R\rfloor &=(T-(T\bmod{R}))/R-(mN-(mN\bmod{R}))/R\\
&=(T-mN-((T\bmod{R})-(TNN'\bmod{R})))/R\\
&=(T-mN-((T\bmod{R})-(T\bmod{R})))/R\\
&=(T-mN)/R
\end{aligned}
$$

该方法用于一些情况更快，因为无需计算“进位”。

## 参考文献

- Peter L. Montgomery. Modular Multiplication Without Trial Division, 1985.
- Richard P. Brent and Paul Zimmermann, Modern Computer Arithmetic, Cambridge Monographs on Computational and Applied Mathematics (No. 18), Cambridge University Press, November 2010, 236 pages
- Nyaan 的[博客](https://nyaannyaan.github.io/docs/modulo/montgomery/)

