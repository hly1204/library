---
title: Z Algorithm
documentation_of: ./z_algorithm.hpp
---

## Z 算法

为了简化描述，令索引都从 $1$ 开始。

用 $\lvert S\rvert$ 表示字符串 $S$ 的长度，用 $S\lbrack a..b\rbrack$ 表示字符串 $S$ 的第 $a$ 到 $b$ 位的子串，例：$S=\texttt{abcdefg}$，那么 $S\lbrack 2..5\rbrack=\texttt{bcde}$，显然也有 $S\lbrack 1..\lvert S\rvert\rbrack=S$。

定义 1：对于一个字符串 $S$ 和一个位置 $i\gt 1$，令 $Z_i(S)$ 为 $S\lbrack i..\lvert S\rvert\rbrack$ 与 $S$ 的最长公共前缀的长度。

当 $S$ 明确时简记为 $Z_i$，例如对于 $S=\texttt{aabcaabxaaz}$ 有

$$
\begin{aligned}
Z_5&=3\\
Z_6&=1\\
Z_7&=Z_8=0\\
Z_9&=2
\end{aligned}
$$

定义 2：对于任何位置 $i\gt 1$ 且 $Z_i\gt 0$，在 $i$ 的 Z-box 被定义为一个区间 $\lbrack i,i+Z_i-1\rbrack$。

定义 3：对于任何 $i\gt 1$，$r_i$ 为从 $i$ 或之前开始的 Z-box 的最右末端点。换言之，$r_i$ 为 $j+Z_j-1$ 的最大值，其中 $1\lt j\leq i$ 且 $Z_j\gt 0$。

这里引入 Z-box 的概念可以使更易理解。

对于字符串 $S$，令 $k\gt 2$，当计算到 $Z_k$ 时，$Z_2,\dots ,Z _ {k-1}$ 都已经计算完毕（$Z_1=\lvert S\rvert$），考虑维护两个变量 $l,r$ 为某个 Z-box 的两端，根据 **定义 3**，在所有 $1\lt i\lt k$ 的 Z-box 中，我们维护的 Z-box 的 $r$ 是最大的，且显然有 $S\lbrack l..r\rbrack=S\lbrack 1..r-l+1\rbrack$，可以发现有以下几种情况：

1. 当 $k\gt r$ 时，即当前位置（索引）不在 Z-box 中，那么直接比较，如果 $Z_k\gt 0$ 则更新 $l,r$；

2. 当 $k\leq r$ 时：
   1. 当 $Z _ {k-l}\lt r-k+1$ 时，$Z_k=Z _ {k-l}$；
   2. 否则 $Z_k$ 至少为 $r-k+1$，并直接比较，更新 $l,r$。
   
有一个较具体的例子，如果 $k=121$，那么 $Z_2$ 到 $Z _ {120}$ 都已经计算完毕，且 $l _ {120}=100,r _ {120}=130$ 这意味着 $S\lbrack 100..130\rbrack =S\lbrack 1..31\rbrack$ 那么 $S\lbrack 121..130\rbrack =S\lbrack 22..31\rbrack$，这样 $Z _ {22}$ 对于计算 $Z _ {121}$ 就非常有帮助，如果 $Z _ {22}=3$，那么 $Z _ {121}=3$（这是情况 2.1）。

注意到直接比较本身是 $O(\lvert S\rvert)$ 的，而且需要执行 $O(\lvert S\rvert)$ 次，但是因为每个字符的成功匹配都会令 $r$ 增加 $1$，而 $r$ 最大可能为 $\lvert S\rvert$，可以说总时间为线性。

## KMP 算法

## border

定义 1：对于模式串 $P$ 的每个位置 $i$，定义 $\pi_i(P)$ 为 $P\lbrack 1..i\rbrack$ 的最长的与 $P$ 的前缀相等的真后缀的长度。

同样的，当 $P$ 显然时我们省略。

例如 $P=\texttt{abcabc}$，那么 $\pi_1=\pi_2=\pi_3=0,\pi_4=1,\pi_5=2$ 等。注意根据定义 $\pi_1=0$ 对任意字符串恒成立。

上述 $\pi$ 也被称为 border。对于 KMP 算法的优化，将会使用 $\pi'(P)$。

定义 2：对于模式串 $P$ 的每个位置 $i$，定义 $\pi_i'(P)$ 为 $P\lbrack 1..i\rbrack$ 的最长的与 $P$ 的前缀相等的真后缀的长度且 $P(i+1)\neq P(\pi_i'+1)$。

显然，$\pi_i'(P)\leq \pi_i(P)$ 恒成立。Gusfield 给出了一个例子 $P=\texttt{bbccaebbcabd}$，其中 $\pi_8=2$ 因为 $\texttt{bb}$ 是 $P\lbrack 1..8\rbrack$ 的真后缀，也是 $P\lbrack 1..8\rbrack$ 的前缀，然而 $P(3)=P(0)=\texttt{c}$ 所以 $\pi_8'\lt 2$。实际上 $\pi_8'=1$ 因为 $\texttt{b}$ 同样满足真后缀和前缀的条件，且后面一个字母不同。

TODO

## 参考文献

- Dan Gusfield. [Algorithms on Strings, Trees, and Sequences: Computer Science and Computational Biology](https://www.amazon.com/Algorithms-Strings-Trees-Sequences-Computational/dp/0521585198).