---
title: Polynomial Euclidean Algorithm
documentation_of: ./poly_gcd.hpp
---

## 有限域多项式 GCD 算法

对于两个有限域多项式 $f,g\in\mathbb{F} _ p\lbrack x\rbrack$ 且 $\deg(f),\deg(g)\lt p$ 且 $p$ 为素数，可以使用辗转相除来计算 $\gcd(f,g)$ ，因为多项式环 $\mathbb{F} _ p\lbrack x\rbrack$ 是欧几里得整环。

在参考文献中的三篇论文都描述了该算法，但个人更偏爱第一篇 Yap 的论文。但是我们需要对 Yap 论文中的算法稍作修改。下文主要译自一篇没有署名的 PDF （是对 Yap 论文的简化）。对于欧几里得商数和欧几里得余数，后文可能简称商数或余数。

考虑两个多项式 $P_0,P_1\in\mathbb{F} _ p\lbrack x\rbrack$ 且 $\deg(P_0)\gt \deg(P_1)\geq 0$ 。那么欧几里得余数序列为 $P_0,P_1,\dots ,P_k$ 且 $k\geq 1$ ，且我们有递推式

$$
P _ {i+1}=P_{i-1}-Q_iP_i
$$

其中 $\deg(P _ {i+1})\lt \deg(P_i)$ 且 $P_k\mid P _ {k-1}$ 。然后就是我们非常熟悉的欧几里得算法 $P_k=\gcd(P_0,P_1)$ 的辗转相除

$$
\gcd(P _ {i-1},P_i)=\gcd(P_i,P _ {i+1})
$$

令 $Q_i=P _ {i-1}\operatorname{div}P_i$ 那么 $P _ {i+1}=P _ {i-1}\bmod P_i$ 和 $n_i=\deg(P_i)$ 注意到 $\deg(Q_i)=n_{i-1}-n_i$ 我们使用矩阵表示一次辗转相除为

$$
\begin{bmatrix}
P_i\\
P _ {i+1}
\end{bmatrix}=
\begin{bmatrix}
0&1\\
1&-Q_i
\end{bmatrix}
\begin{bmatrix}
P _ {i-1}\\
P_i
\end{bmatrix}
$$

为了简便我们使用记号 $\langle Q_i\rangle$ 表示上述 $2\times 2$ 的多项式矩阵。那么

$$
\begin{bmatrix}
P_i\\
P _ {i+1}
\end{bmatrix}=
\langle Q_i\rangle \cdots \langle Q_2\rangle \langle Q_1\rangle
\begin{bmatrix}
P_0\\
P_1
\end{bmatrix}
$$

如果我们考虑 $\langle Q_i\rangle \cdots \langle Q_2\rangle \langle Q_1\rangle$ 中元素的度数，就相当于考虑 $\sum _ {j=1}^i\deg(Q_j)$ 而

$$
\sum _ {i=1}^k\deg(Q_i)=\sum _ {i=1}^k(n _ {i-1}-n_i)=n_0-n_k\leq n_0
$$

那么使用朴素算法计算 $\gcd(P_0,P_1)$ 需要约 $O(n_0^2)$ ，因为 $\forall i$ 计算 $Q_i$ 所消耗总时间为 $O(n_0)$ （假设余数序列为 normal ），而对某个 $i$ 计算 $P _ {i+1}=P _ {i-1}-Q_iP_i$ 需要 $O(\deg(Q_i)n_i)$ 时间。

另外，对于 $0\lt i\lt k$ 若 $P_i-P _ {i+1}=1$ 那么说这个欧几里得余数序列是 normal 的。在随机情况下这两个多项式的余数序列为 normal 的可能性很大，若需要构造 abnormal 的情况可考虑反向进行欧几里得算法去构造（ 该 [提交记录](https://loj.ac/s/1124308) 是一个简单的测试是否 normal 的代码）。

首先给出 co-GCD 算法的递归伪代码，其中调用的函数 HGCD 将在后文给出。

$$
\begin{array}{ll}
&\textbf{Algorithm Polynomial }\operatorname{co-gcd}(A,B)\text{:} \\
&\textbf{Input}\text{: }A,B\in\mathbb{F} _ p\lbrack x\rbrack \text{, }\deg(A)\gt \deg(B)\geq 0 \text{.} \\
&\textbf{Output}\text{: a regular matrix }\mathbf{M} \text{ such that }
\begin{bmatrix}
\gcd(A,B)\\
0
\end{bmatrix} =
\mathbf{M}
\begin{bmatrix}
A\\
B
\end{bmatrix}\text{.} \\
1&\mathbf{M} _ 1\gets \operatorname{hgcd}(A,B)\text{;} \\
2&
\begin{bmatrix}
C\\
D
\end{bmatrix}
\gets
\mathbf{M} _ 1
\begin{bmatrix}
A\\
B
\end{bmatrix} \text{;}\\
3&\textbf{if }D=0\textbf{ then return }(\mathbf{M} _ 1) \text{;}\\
4&
\begin{bmatrix}
Q\\
E
\end{bmatrix}
\gets
\begin{bmatrix}
C\operatorname{div}D\\
C\bmod D
\end{bmatrix}
\text{;} \\
5&\textbf{if }E=0\textbf{ then return } (\langle Q\rangle \mathbf{M} _ 1) \text{;}\\
6&\mathbf{M} _ 2\gets \operatorname{co-gcd}(D,E)\text{;} \\
7&\textbf{return }(\mathbf{M} _ 2\langle Q\rangle \mathbf{M} _ 1)\text{;}
\end{array}
$$

令 $G(n)$ 为 co-GCD 算法的复杂度， $\mathsf{M}(n)$ 为多项式乘法/欧几里得除法的复杂度，而 $H(n)$ 为 HGCD 算法的复杂度，那么有

$$
G(n)=H(n)+O(\mathsf{M}(n))+G(n/2)
$$

HGCD 算法给出的矩阵不一定能使得问题减少一半（查看 HGCD 算法的输出），但是加上一次辗转相除的步骤之后问题确实至少减少为原先的一半，所以该算法的瓶颈显然在于 $H(n)$ （如果推导过幂级数牛顿法的复杂度的话，这里是类似的？）。

我们准备好给出 HGCD 算法的伪代码

$$
\begin{array}{ll}
&\textbf{Algorithm Polynomial }\operatorname{hgcd}(A,B)\text{:}\\
&\textbf{Input}\text{: }A,B\in\mathbb{F} _ p\lbrack x\rbrack \text{, }\deg(A)\gt \deg(B)\geq 0 \text{.}\\
&\textbf{Output}\text{: a regular matrix }\mathbf{M} \text{ such that }
\deg(C)\geq \left\lceil\frac{\deg(A)}{2}\right\rceil \gt \deg(D) \text{ where }
\begin{bmatrix}
C\\
D
\end{bmatrix}=
\mathbf{M}
\begin{bmatrix}
A\\
B
\end{bmatrix}\text{.} \\
1&m\gets \left\lceil\frac{\deg(A)}{2}\right\rceil \text{;}\\
2& \textbf{if }\deg(B)\lt m\textbf{ then return}
\left(\begin{bmatrix}
1&0\\
0&1
\end{bmatrix}\right) \text{;}\\
3&\mathbf{R}\gets \operatorname{hgcd}(A\operatorname{div} x^m,B\operatorname{div} x^m) \text{;}\\
4&
\begin{bmatrix}
C\\
D
\end{bmatrix}
\gets
\mathbf{R}
\begin{bmatrix}
A\\
B
\end{bmatrix} \text{;}\\
5&\textbf{if }\deg(D)\lt m\textbf{ then return }\left(\mathbf{R}\right) \text{;}\\
6& 
\begin{bmatrix}
Q\\
E
\end{bmatrix}
\gets
\begin{bmatrix}
C\operatorname{div}D\\
C\bmod D
\end{bmatrix}
\text{;}\\
7&\textbf{if }\deg(E)\lt m\textbf{ then return }(\langle Q\rangle \mathbf{R})\text{;} \\
8&k\gets 2m-\deg(D) \text{;}\\
9&\mathbf{S}\gets \operatorname{hgcd}(D\operatorname{div}x^k, E\operatorname{div}x^k) \text{;}\\
10&\textbf{return }\left( \mathbf{S}\langle Q\rangle \mathbf{R}\right)\text{;}
\end{array}
$$

其中 regular 表示 $\det(\mathbf{M})\neq 0$ （当然的，此处 $\det(\langle Q\rangle)=-1$ 显然）。我们必须证明该算法会给出符合的输出。

令 $A,B$ 为满足 HGCD 算法输入的两个多项式且 $m\geq 1$ 。定义 $A_0=A\operatorname{div}x^m$ 和 $B_0=B\operatorname{div}x^m$ 这也决定了 $A_1$ 和 $B_1$ 如下

$$
\begin{aligned}
\begin{bmatrix}
A\\
B
\end{bmatrix}&=
\begin{bmatrix}
A_0x^m+A_1\\
B_0x^m+B_0
\end{bmatrix} \\
&=\begin{bmatrix}
A_0&A_1\\
B_0&B_1
\end{bmatrix}
\begin{bmatrix}
x^m\\
1
\end{bmatrix}
\end{aligned}
$$

现在我们令 $\mathbf{M}$ 为一个给定的矩阵，这决定了 $C_0,D_0,C_1,D_1$ 为

$$
\begin{bmatrix}
C_0&C_1\\
D_0&D_1
\end{bmatrix}=
\mathbf{M}
\begin{bmatrix}
A_0&A_1\\
B_0&B_1
\end{bmatrix}
$$

最后我们定义

$$
\begin{bmatrix}
C\\
D
\end{bmatrix}=
\begin{bmatrix}
C_0&C_1\\
D_0&D_1
\end{bmatrix}
\begin{bmatrix}
x^m\\
1
\end{bmatrix}
$$

因此

$$
\begin{bmatrix}
C\\
D
\end{bmatrix}=
\mathbf{M}
\begin{bmatrix}
A\\
B
\end{bmatrix},\quad
\begin{bmatrix}
C_0\\
D_0
\end{bmatrix}=
\mathbf{M}
\begin{bmatrix}
A_0\\
B_0
\end{bmatrix}
$$

这告诉我们使用 $m$ 去截断这个多项式，可将问题缩小，在 HGCD 算法的第 1 行，令 $Q=A\operatorname{div}B$ 那么 $\deg(Q)=\deg(A)-\deg(B)$ 而我们要保证 $(A\operatorname{div}x^m)\operatorname{div}(B\operatorname{div}x^m)=Q$ 。一个直觉告诉我们 $Q$ 仅由 $A$ 和 $B$ 的“高位”决定，因为 $\deg(A\bmod B)\lt \deg(B)$ 也就是 $A$ 和 $QB$ 的高位是相等的。

在这里我希望感性理解，但可能有误。回顾在多项式除法中我们“翻转”了两个多项式，使得商数的“翻转”可以在模 $x^{\deg(Q)+1}$ 意义下求出，这也提示在此处 $Q$ 仅与 $A$ 和 $B$ 的前 $\deg(Q)+1$ 项系数有有关（若 $\deg(B)\leq \deg(Q)$ 就不用那么多）。

在 HGCD 算法的第一步中的 $m$ 和第三步递归调用保证了返回的一个矩阵一定是正确的矩阵（不考虑后续过程的话），比如说 $\deg(A)=10$ 而 $\deg(B)=5$ 会产生一次递归调用，但是这次递归中会返回单位矩阵，我们注意 HGCD 算法中的返回值要求了矩阵 $\mathbf{M}$ 必须使得 $\deg(D)\lt 5$ 所以还需要一次辗转相除，这里 $m$ 的设置没有问题，注意这次递归的子问题大约为一半大小。

另外一个启发是如果我们对 $A$ 和 $B$ 不仅仅满足于取他们的高位 $\deg(Q)+1$ 个系数而是取更多，那么会使得截断后的多项式的余数的高位也与 $A\bmod B$ 的高位相等（具体多少取决于我们取了多少），这大约是该算法的主要思想，但是这个界需要非常小心的考虑！具体的，如果 $Q$ 作用于截断后的多项式上，那么其末尾的约 $\deg(Q)$ 个系数就不一定是正确的（原先我们计算 $A-QB$ ，现在我们计算 $(A\operatorname{div}x^m)-Q\cdot (B\operatorname{div}x^m)=(A-O(x^{m-1})+QB-Q\cdot O(x^{m-1}))\operatorname{div}x^m$ 所以 $((A\bmod B)\operatorname{div}x^m)-(A\operatorname{div}x^m)+Q\cdot (B\operatorname{div}x^m)=O\left(x^{\deg(Q)-1}\right)$ ），但是除去这些，其余高位的系数依然是正确的，所以可以递归应用该算法。

如果我们没有在第五步返回，通过后面的一次辗转相除，问题被缩小为原先的约 $3/4$ 而后 $2\deg(D)\lt 3m$ （这准确吗？）而 $\deg(D)-k=2\deg(D)-2m\lt m$ 所以后面的子问题大小还是至少约为原先的一半！此时

$$
H(n)=2H(n/2)+O(\mathsf{M}(n))
$$

但注意，这仅仅保证了复杂度，而没有进行任何正确性的分析！ Yap 指出第八步令 $k=\left\lceil m/2\right\rceil$ 是不正确的，但若余数序列为 normal 则正确，个人的理解是如果余数序列度数之间间隔比较大，可能导致这次递归的子问题规模错误，所以不能返回正确的矩阵。子问题的规模在这个问题中是相当重要的，因为 HGCD 算法是递归调用的！也导致该算法非常难脱离代码去考虑。

写的很粗糙，但是可能就止步于此了，希望以后有人能写一篇包含详细证明的介绍！

## 关于代码

我没有使用任何的优化，尽管有几处是很明显的，例如对于 $\langle Q\rangle \mathbf{M}$ 的乘法。

## 参考文献

- Chee Keng Yap. Fundamental Problems of Algorithmic Algebra.
- Klaus Thull and Chee Keng Yap. [A Unified Approach to HGCD Algorithms for polynomials and integers](http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.46.1941).
- Joachim von zur Gathen and Jürgen Gerhard. Modern Computer Algebra.
- Todd Mateer. [Fast Fourier Transform Algorithms with Applications](http://cr.yp.to/f2mult/mateer-thesis.pdf).