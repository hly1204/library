# 符号化方法

《解析组合》中的第一部分（ part A ）符号化方法，试图教会我们将组合对象（集合）上的操作直接映射到生成函数上，我只学了一些皮毛都算不上的部分，在这里仅做记录。

和原书一样，使用 $\mathcal{A}$ 同一组的字符表示集合，而 $A(z)$ 表示对应生成函数， $A_n$ 或 $a_n$ 表示 $[z^n]A(z)$ ，对于集合我们使用记号 $\operatorname{card}(\mathcal{A})$ 表示大小，但是后文一般用不到，我们用 $\lvert \cdot \rvert$ 表示集合中对象的大小，即大小函数。对应集合中的元素为 $\alpha$ 等，大小为 $n$ 的元素的集合为 $\mathcal{A} _ n$ 。

对于一个组合结构，希望将其映射为生成函数需要的是有一个大小函数，可以将这个集合中的对象映射为一个非负整数（但不能是无限大），比如对于单词来说可以是其长度，对于树或图来说可以是其节点的数量，但这并不一定，比如在书中一部分对于二叉树的计数方式可以是对于其内部节点或外部节点，此时对于内部或者外部节点，其中一个的大小被映射为 $0$ ，而另一个为 $1$ ，这与通常我们认为的一个节点一定映射为 $1$ 是不同的，需要注意。

大小为 $0$ 的元素一般记为 $\epsilon$ ，而一个只包含这个元素的集合为 $\mathcal{E}$ 。如果两个组合结构在组合意义上是同构的记为 $\mathcal{A}=\mathcal{B}$ 或 $\mathcal{A}\cong\mathcal{B}$ 。

置换的意思是按顺序对所有进行排列？

## 无标号体系

对于普通生成函数可能简称为生成函数。

对于 $\mathcal{A}$ 的生成函数有

$$
A(z)=\sum _ {\alpha\in\mathcal{A}}z^{\lvert \alpha \rvert}=\sum _ {i\geq 0}a_iz^i
$$

下面的对于集合的操作被称为“构造”，对于构造可以施加限制。

### 集合的并

对于集合 $\mathcal{A},\mathcal{B}$ 我们定义其并为

$$
\mathcal{A}+\mathcal{B}=(\mathcal{E_0}\times \mathcal{A})+(\mathcal{E_1}\times \mathcal{B})
$$

（此处乘号为（笛卡尔）积）这样定义允许我们直接将生成函数的加法对应于集合的并，而不违背集合论中集合的定义，因为集合论中的集合不允许存在同一个元素的。

对应生成函数为

$$
A(z)+B(z)
$$

考虑

$$
A(z)+B(z)=\sum _ {\alpha\in\mathcal{A}}z^{\lvert \alpha\rvert} + \sum _ {\beta\in\mathcal{B}}z^{\lvert \beta\rvert}
$$

### 集合的（笛卡尔）积

$$
\mathcal{A}\times \mathcal{B}=\lbrace (\alpha, \beta)\mid \alpha \in \mathcal{A},\beta\in\mathcal{B}\rbrace
$$

那么其中一个元素的大小为两个元素大小之和。

对应生成函数为

$$
A(z)\cdot B(z)
$$

考虑

$$
A(z)\cdot B(z)=\left(\sum _ {\alpha\in\mathcal{A}}z^{\lvert \alpha\rvert}\right)\left(\sum _ {\beta\in\mathcal{B}}z^{\lvert \beta\rvert}\right)=\sum _ {(\alpha, \beta)\in(\mathcal{A}\times \mathcal{B})}z^{\lvert \alpha\rvert +\lvert \beta\rvert}
$$

### 集合的 Sequence

Sequence 生成了所有可能的组合

$$
\begin{aligned}
\operatorname{SEQ}(\lbrace a\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace (a,a)\rbrace +\lbrace (a,a,a)\rbrace +\cdots\\
\operatorname{SEQ}(\lbrace a,b\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a,b\rbrace +\lbrace (a,b)\rbrace + \lbrace(b,a)\rbrace +\lbrace (a,a)\rbrace +\lbrace (b,b)\rbrace\\
&+\lbrace (a,b,a)\rbrace +\lbrace (a,b,b)\rbrace +\lbrace (a,a,b)\rbrace +\lbrace (b,b,a)\rbrace +\lbrace (b,a,b)\rbrace +\lbrace (b,b,b)\rbrace +\lbrace (a,a,a)\rbrace +\lbrace (b,a,a)\rbrace\\
&+\cdots
\end{aligned}
$$

所以

$$
\operatorname{SEQ}(\mathcal{A})=\mathcal{E}+\mathcal{A}+(\mathcal{A}\times \mathcal{A})+(\mathcal{A}\times \mathcal{A}\times \mathcal{A})+\cdots
$$

必须保证 $\mathcal{A} _ 0=\emptyset$ 也就是集合 $\mathcal{A}$ 中没有大小为 $0$ 的元素。

对应生成函数为

$$
Q(A(z))=\frac{1}{1-A(z)}
$$

其中 $Q$ 为 Pólya 算子。

限制构造为

$$
\operatorname{SEQ} _ k(\mathcal{A})=\overbrace{\mathcal{A}\times \cdots \times \mathcal{A}}^{k \text{ times}}
$$

对应生成函数为

$$
A^k(z)
$$

限制构造为

$$
\operatorname{SEQ} _ {\geq k}(\mathcal{A})=\sum _ {j\geq k}\mathcal{A}^j\cong \mathcal{A}^k\times \operatorname{SEQ}(\mathcal{A})
$$

限制构造为

$$
\operatorname{SEQ} _ {\Omega}(\mathcal{A})
$$

其中 $\Omega$ 为一个非负整数集合（如 $\Omega =\lbrace 0,1,2\rbrace$ ），那么

$$
\operatorname{SEQ} _ {\Omega}(\mathcal{A})=\sum _ {\omega \in\Omega}\operatorname{SEQ} _ {\omega}(\mathcal{A})
$$

简单举例，如一般平面树（即 ordered rooted tree ，平面意为将其嵌入在平面上时孩子的顺序是有意义的，所以一般这样称呼） $\mathcal{G}$ 而言，可以定义为根节点和 $\mathcal{G}$ 的 sequence 那么

$$
\mathcal{G}=\mathcal{Z}\times\operatorname{SEQ}(\mathcal{G})\implies G(z)=\frac{z}{1-G(z)}
$$

### 集合的 Powerset

Powerset 生成了所有的子集

$$
\begin{aligned}
\operatorname{PSET}(\lbrace a\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace \\
\operatorname{PSET}(\lbrace a,b\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace b\rbrace +\lbrace (a,b)\rbrace \\
\operatorname{PSET}(\lbrace a,b,c\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace b\rbrace +\lbrace (a,b)\rbrace +\lbrace c\rbrace +\lbrace (a,c)\rbrace +\lbrace (b,c)\rbrace +\lbrace (a,b,c)\rbrace\\
\end{aligned}
$$

那么递推式为

$$
\operatorname{PSET}(\lbrace a_0,a_1,\dots, a_n\rbrace)=\operatorname{PSET}(\lbrace a_0,a_1,\dots, a _ {n-1}\rbrace)\times (\lbrace \epsilon\rbrace +\lbrace a_n\rbrace)
$$

所以

$$
\operatorname{PSET}(\mathcal{A})\cong \prod _ {\alpha\in\mathcal{A}}\left(\lbrace \epsilon \rbrace +\lbrace \alpha\rbrace\right)
$$

仍限制 $\mathcal{A} _ 0=\emptyset$ 。

生成函数为

$$
\overline{\operatorname{Exp}}(A(z))=\prod _ {\alpha\in\mathcal{A}}\left(1+z^{\lvert \alpha \rvert}\right)=\prod _ {i\geq 1}\left(1+z^i\right)^{a_i}\\
$$

其中 $\overline{\operatorname{Exp}}$ 为 Pólya 指数·改。

我们知道

$$
\log(1+u)=\frac{u}{1}-\frac{u^2}{2}+\frac{u^3}{3}-\cdots
$$

而 $A(z)=\exp(\log(A(z)))$ 所以

$$
\begin{aligned}
\overline{\operatorname{Exp}}(A(z))&=\exp\left(\sum _ {i\geq 1}a_i\cdot \log\left(1+z^i\right)\right)\\
&=\exp\left(\sum _ {i\geq 1}a_i\cdot \sum _ {j\geq 1}\frac{(-1)^{j+1}z^{ij}}{j}\right)\\
&=\exp\left(\frac{A(z)}{1}-\frac{A(z^2)}{2}+\frac{A(z^3)}{3}-\cdots \right)
\end{aligned}
$$

限制构造为

$$
\mathcal{B}=\operatorname{PSET} _ k(\mathcal{A})
$$

这是一个关于 $A(z),\dots ,A(z^k)$ 的表达式，有

$$
B(z)=\lbrack u^k\rbrack \exp\left(\frac{u}{1}A(z)-\frac{u^2}{2}A(z^2)+\frac{u^3}{3}A(z^3)-\cdots\right)
$$

注意限制构造并没有要求 $\mathcal{A} _ 0=\emptyset$ 。

### 集合的 Multiset

Multiset 生成了所有子集且允许重复

$$
\begin{aligned}
\operatorname{MSET}(\lbrace a\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace (a,a)\rbrace +\lbrace (a,a,a)\rbrace +\cdots\\
\operatorname{MSET}(\lbrace a,b\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace (a,a)\rbrace +\lbrace (a,a,a)\rbrace +\cdots\\
&+\lbrace b\rbrace +\lbrace (a,b)\rbrace +\lbrace (a,a,b)\rbrace +\cdots \\
&+\lbrace (b,b)\rbrace + \lbrace (a,b,b)\rbrace +\lbrace (a,a,b,b)\rbrace + \cdots
\end{aligned}
$$

我们注意到 $\lbrace (b,a)\rbrace,\lbrace (a,b,a)\rbrace$ 在 $\operatorname{SEQ}(\lbrace a,b\rbrace)$ 中出现但是在 $\operatorname{MSET}(\lbrace a,b\rbrace)$ 中没有出现，在 Multiset 中对于仅顺序不同的对象是不存在的。

那么递推式为

$$
\operatorname{MSET}(\lbrace a_0,a_1,\dots, a_n\rbrace)=\operatorname{MSET}(\lbrace a_0,a_1,\dots, a _ {n-1}\rbrace)\times \operatorname{SEQ}(\lbrace a_n\rbrace)
$$

所以

$$
\operatorname{MSET}(\mathcal{A})=\prod _ {\alpha\in\mathcal{A}}\operatorname{SEQ}(\lbrace \alpha\rbrace)
$$

仍限制 $\mathcal{A} _ 0=\emptyset$ 。

考虑

$$
\begin{aligned}
\operatorname{Exp}(A(z))&=\prod _ {\alpha \in\mathcal{A}}\left(1-z^{\lvert \alpha \rvert}\right)^{-1}=\prod _ {i\geq 1}\left(1-z^i\right)^{-a_i}\\
&=\exp\left(\sum _ {i\geq 1}-a_i\cdot \log\left(1-z^i\right)\right)\\
&=\exp\left(\sum _ {i\geq 1}-a_i\cdot \sum _ {j\geq 1}\frac{-z^{ij}}{j}\right)\\
&=\exp\left(\frac{A(z)}{1}+\frac{A(z^2)}{2}+\frac{A(z^3)}{3}+\cdots \right)
\end{aligned}
$$

其中 $\operatorname{Exp}$ 为 Pólya 指数，也被称为 Euler 变换。

可以观察到 $\operatorname{PSET}(\mathcal{A})\subset \operatorname{MSET}(\mathcal{A})$ 因为 powerset 构造不允许重复。

若令 $\mathcal{M}=\operatorname{MSET}(\mathcal{C})$ 和 $\mathcal{P}=\operatorname{PSET}(\mathcal{C})$ 那么

$$
M(z)=P(z)M(z^2)
$$

通过上述推导和 $\exp(a)\exp(b)=\exp(a+b)$ 易得。

限制构造为

$$
\mathcal{B}=\operatorname{MSET} _ k(\mathcal{A})
$$

这是一个关于 $A(z),\dots ,A(z^k)$ 的表达式，有

$$
B(z)=\lbrack u^k\rbrack \exp\left(\frac{u}{1}A(z)+\frac{u^2}{2}A(z^2)+\frac{u^3}{3}A(z^3)+\cdots\right)
$$

注意限制构造并没有要求 $\mathcal{A} _ 0=\emptyset$ 。

这一限制很常见，例如 [烷基计数](https://loj.ac/p/6538) （根节点度数不超过 $3$ 其余节点度数不超过 $4$ 的有根非平面树）一题即

$$
\mathcal{G}=\lbrace \epsilon\rbrace +\mathcal{Z}\times \operatorname{MSET} _ {3}(\mathcal{G})
$$

注意这里 $\lbrace \epsilon\rbrace$ 的作用，如果没有空集，那么 $\widehat{\mathcal{G}}=\mathcal{G}\setminus \lbrace \epsilon\rbrace$ 有

$$
\widehat{\mathcal{G}}=\mathcal{Z}\times \operatorname{MSET} _ {0,1,2,3}(\widehat{\mathcal{G}})
$$

另外我们注意 [分拆数](https://loj.ac/p/6268) 实际上就是完全背包问题，而这里 Multiset 的构造也正是解决了这一问题，分拆数的组合类为

$$
\operatorname{MSET}(\operatorname{SEQ} _ {\geq 1}(\mathcal{Z}))
$$

[P4389 付公主的背包](https://www.luogu.com.cn/problem/P4389) 也是可以一样理解。

[P5900 无标号无根树计数](https://www.luogu.com.cn/problem/P5900) 首先对于非平面（即不关心孩子的顺序）有根树 $\mathcal{T}$ 有

$$
\mathcal{T}=\mathcal{Z}\times \operatorname{MSET}(\mathcal{T})
$$

而根据 Richard Otter 的论文 [The Number of Trees](https://users.math.msu.edu/users/magyarp/Math482/Otter-Trees.pdf) 中的描述，对应无根树的生成函数为

$$
T(z)-\frac{1}{2}T^2(z)+\frac{1}{2}T(z^2)
$$

### 集合的 Cycle

这里我没看懂，仅摘抄公式

$\operatorname{CYC}(\mathcal{A})$ 对应的生成函数为

$$
\operatorname{Log}(A(z))=\sum _ {i\geq 1}\frac{\varphi(i)}{i}\log\frac{1}{1-A(z^k)}
$$

要求 $\mathcal{A} _ 0=\emptyset$ ，其中 $\operatorname{Log}$ 为 Pólya 对数。

我理解应该是轮换构造在 Cycle 中认为是等价的，与 Multiset 中不同，比如 Multiset 中认为 $\lbrace (a,b,c,d)\rbrace$ 的任意 $4!$ 种置换都是等价的，但是 Cycle 中只认为 $\lbrace (a,b,c,d)\rbrace$ 与 $\lbrace (b,c,d,a)\rbrace ,\lbrace (c,d,a,b)\rbrace ,\lbrace (d,a,b,c)\rbrace$ 是等价的，其他也是类似的，在 x义x 的博客中使用了 Burnside 引理来证明，而《解析组合》中使用了二元的生成函数来解释，包括三个限制构造的证明。

限制构造为

$$
\mathcal{B}=\operatorname{CYC} _ k(\mathcal{A})
$$

这是一个关于 $A(z),\dots ,A(z^k)$ 的表达式，有

$$
B(z)=\lbrack u^k\rbrack \sum _ {i\geq 1}\frac{\varphi(i)}{i}\log\frac{1}{1-u^iA(z^i)}
$$

注意限制构造并没有要求 $\mathcal{A} _ 0=\emptyset$ 。

可以简单的注意到 $\operatorname{MSET} _ 2(\mathcal{A})\cong\operatorname{CYC} _ 2(\mathcal{A})$ 。

### 集合的 Pointing

$$
\Theta\mathcal{A}=\sum _ {i\geq 0}\mathcal{A} _ i\times \lbrace \epsilon_1, \dots,\epsilon_i\rbrace
$$

对应生成函数为

$$
z\partial_z A(z),\quad \partial_z=\frac{\mathrm{d}}{\mathrm{d}z}
$$

### 集合的 Substitution

$$
\mathcal{A}\circ\mathcal{B}=\sum _ {i\geq 0}\mathcal{A} _ i\times \operatorname{SEQ} _ i(\mathcal{B})
$$

对应生成函数为

$$
\sum _ {i\geq 0}A_k\cdot B^k(z)=A(B(z))
$$

### 限制构造的举例和说明

$$
\begin{aligned}
\operatorname{PSET} _ {2}(\mathcal{A})&:\quad \frac{A^2(z)}{2}-\frac{A(z^2)}{2}\\
\operatorname{MSET} _ {2}(\mathcal{A})&:\quad \frac{A^2(z)}{2}+\frac{A(z^2)}{2}\\
\operatorname{CYC} _ {2}(\mathcal{A})&:\quad \frac{A^2(z)}{2}+\frac{A(z^2)}{2}
\end{aligned}
$$

$$
\begin{aligned}
\operatorname{PSET} _ {3}(\mathcal{A})&:\quad \frac{A^3(z)}{6}-\frac{A(z)A(z^2)}{2}+\frac{A(z^3)}{3}\\
\operatorname{MSET} _ {3}(\mathcal{A})&:\quad \frac{A^3(z)}{6}+\frac{A(z)A(z^2)}{2}+\frac{A(z^3)}{3}\\
\operatorname{CYC} _ {3}(\mathcal{A})&:\quad \frac{A^3(z)}{3}+\frac{2A(z^3)}{3}\\
\end{aligned}
$$

$$
\begin{aligned}
\operatorname{PSET} _ {4}(\mathcal{A})&:\quad \frac{A^4(z)}{24}-\frac{A^2(z)A(z^2)}{4}+\frac{A(z)A(z^3)}{3}+\frac{A^2(z^2)}{8}-\frac{A(z^4)}{4}\\
\operatorname{MSET} _ {4}(\mathcal{A})&:\quad \frac{A^4(z)}{24}+\frac{A^2(z)A(z^2)}{4}+\frac{A(z)A(z^3)}{3}+\frac{A^2(z^2)}{8}+\frac{A(z^4)}{4}\\
\operatorname{CYC} _ {4}(\mathcal{A})&:\quad \frac{A^4(z)}{4}+\frac{A^2(z^2)}{4}+\frac{A(z^4)}{2}\\
\end{aligned}
$$

对于 $\operatorname{SEQ} _ k(\mathcal{A})$ 的理解是平凡的，即 $\lbrace (\alpha_1,\alpha_2,\dots ,\alpha_k)\mid \alpha_j\in\mathcal{A}\rbrace$ 。

对于 $\operatorname{PSET} _ k(\mathcal{A})$ 可以理解为 $\lbrace (\alpha_1,\alpha_2,\dots ,\alpha_k)\mid \alpha_j\in\mathcal{A},\forall i\neq j:\alpha_i\neq \alpha_j\rbrace /\mathbf{R}$ ，其中 $\mathbf{R}$ 代表 $\alpha_1,\dots ,\alpha_k$ 的任意排列。

对于 $\operatorname{MSET} _ k(\mathcal{A})$ 可以理解为 $\lbrace (\alpha_1,\alpha_2,\dots ,\alpha_k)\mid \alpha_j\in\mathcal{A}\rbrace /\mathbf{R}$ 。

并且显然可以发现 $\operatorname{MSET} _ \Omega(\mathcal{A})=\sum _ {\omega\in\Omega}\operatorname{MSET} _ \omega(\mathcal{A})$ 和 $\operatorname{PSET} _ \Omega(\mathcal{A})=\sum _ {\omega\in\Omega}\operatorname{PSET} _ \omega(\mathcal{A})$ 。

command_block 的博客中使用了 Burnside 引理来解释 $\operatorname{MSET}$ 的构造，而书中则推荐使用二元生成函数，额外使用一个变量来跟踪“组成部分的个数”。

令 $\mathfrak{K}$ 为 $\operatorname{SEQ},\operatorname{CYC},\operatorname{MSET},\operatorname{PSET}$ 之一和 $\mathcal{A}=\mathfrak{K}(\mathcal{B})$ 并令 $\chi(\alpha)$ 对于 $\alpha\in\mathcal{A}$ 表示 $\alpha$ 由 $\mathcal{B}$ 中的多少部分组成，例如 $\alpha=(\beta_1,\beta_2)$ 那么显然 $\lvert \alpha\rvert =\lvert \beta_1\rvert+\lvert \beta_2\rvert$ 而 $\chi(\beta)=1$ 对于 $\beta\in\mathcal{B}$ 成立，所以 $\chi(\alpha)=2$ 。

$$
\begin{aligned}
A _ {n,k}&=\operatorname{card}\left\lbrace \alpha\in\mathcal{A}\mid \lvert \alpha\rvert =n,\chi(\alpha)=k\right\rbrace\\
A(z,u)&=\sum _ {n,k}A _ {n,k}u^kz^n=\sum _ {\alpha\in\mathcal{A}}z^{\lvert \alpha\rvert}u^{\chi(\alpha)}
\end{aligned}
$$

然后我们只要提取出 $u^k$ 的系数即可得到相关的表达式。

比如对于 $\operatorname{SEQ} _ k(\mathcal{B})$ 可以直接导出

$$
A(z,u)=\sum _ {k\geq 0}u^kB^k(z)=\frac{1}{1-uB(z)}
$$

而对于 $\operatorname{MSET} _ k(\mathcal{B})$ 和 $\operatorname{PSET} _ k(\mathcal{B})$ 先前已经有

$$
A(z,u)=\prod_n\left(1-uz^n\right)^{-b_n},\quad A(z,u)=\prod_n\left(1+uz^n\right)^{b_n}
$$

我们不妨用给出的方法来模拟计算一下 $\operatorname{MSET} _ 3(\mathcal{A})$

$$
\begin{aligned}
\lbrack u^3\rbrack &= \frac{1}{0!}\left(\lbrack u^3\rbrack 1\right)+\frac{1}{1!}\left(\lbrack u^3\rbrack \left(\frac{u}{1}A(z)+\frac{u^2}{2}A(z^2)+\frac{u^3}{3}A(z^3)+\cdots \right)\right)\\
&+\frac{1}{2!}\left(\lbrack u^3\rbrack \left(\frac{u}{1}A(z)+\frac{u^2}{2}A(z^2)+\cdots \right)^2\right)\\
&+\frac{1}{3!}\left(\lbrack u^3\rbrack \left(\frac{u}{1}A(z)+\cdots \right)^3\right)\\
&=\frac{A(z^3)}{3}+\frac{A(z)A(z^2)}{2}+\frac{A^3(z)}{6}
\end{aligned}
$$

而 $\operatorname{MSET} _ 4(\mathcal{A})$

$$
\begin{aligned}
\lbrack u^4\rbrack &= \frac{1}{0!}\left(\lbrack u^4\rbrack 1\right)+\frac{1}{1!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}A(z)+\frac{u^2}{2}A(z^2)+\frac{u^3}{3}A(z^3)+\frac{u^4}{4}A(z^4)+\cdots \right)\right)\\
&+\frac{1}{2!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}A(z)+\frac{u^2}{2}A(z^2)+\frac{u^3}{3}A(z^3)+\cdots \right)^2\right)\\
&+\frac{1}{3!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}A(z)+\frac{u^2}{2}A(z^2)+\cdots \right)^3\right)\\
&+\frac{1}{4!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}A(z)+\cdots \right)^4\right)\\
&=\frac{A(z^4)}{4}+\frac{1}{2!}\left(\frac{A^2(z^2)}{4}+\frac{2A(z)A(z^3)}{3}\right)+\frac{1}{3!}\left(\frac{3A^2(z)A(z^2)}{2}\right)+\frac{A^4(z)}{4!}
\end{aligned}
$$

与刚刚给出的表格是一致的。

存在更通用的计算方法，即 Pólya 计数法（ Pólya enumeration theorem ）也就是 command\_block 博客中使用的方法，形式化的，令 $A$ 为一个置换群阶为 $m$ 且度数为 $d$ （有 $m$ 个元素且一个置换都包含于整数集合 $\lbrack d\rbrack = \lbrace 1,2,\dots, d\rbrace$ ，不过一般来说我们考虑的基本都只是 $m=d$ 的情况？）。

对于每个 $\alpha\in A$ 都可以分解成不相交的环，令 $j_1(\alpha)$ 表示长度为 $1$ 的环，以此类推，然后引入一些变量 $\lbrace a_k\rbrace _ {k=1}^d$ ，一个置换就可以用这样一个变量的序列表示，令 $a_k$ 的指数表示 $\alpha$ 中长度为 $k$ 的环的数量，那么循环多项式（ cycle polynomial ） $Z(A)$ 为

$$
Z(A)=\frac{1}{\lvert A\rvert}\sum _ {\alpha\in A}\prod _ {k=1}^da_k^{j_k(\alpha)}
$$

比如循环群 $C_3=\lbrace (1,2,3),(2,3,1),(3,1,2)\rbrace$ ，考虑将 $(1,2,3)$ 分别映射到 $C_3$ 中的每个元素，那么 $(1,2,3)$ 到 $(1,2,3)$ 显然只能 $1$ 映射到 $1$ ， $2$ 映射到 $2$ ， $3$ 映射到 $3$ 故有 $3$ 个长度为 $1$ 的环，而 $(1,2,3)$ 映射到 $(2,3,1)$ 则是将 $1$ 映射到 $2$ ，将 $2$ 映射到 $3$ 再将 $3$ 映射到 $1$ 是一个长度为 $3$ 的环，最后那种映射也是长度为 $3$ 的环，故

$$
Z(C_3)=\frac{1}{3}(a_1^3+2a_3)
$$

这实际上就是 $\operatorname{CYC} _ 3$ ，于是简单的机械化的计算方法就是我们生成这些所有的群然后建图后计算环的大小和数量。

对于组合类 $\mathcal{C}$ 和一个度数为 $d$ 的置换群 $A$ ，我们希望计算 $\mathcal{C}$ 中的对象放到 $d$ 个桶中的方案数，两种方案是等价的当且仅当可以根据某个 $\alpha\in\mathcal{A}$ 然后将桶进行置换得到。

令 $D(z)$ 为等价类的普通生成函数，那么 $\lbrack z^n\rbrack D(z)$ 也就是大小为 $n$ 的等价类的数量。我们有

$$
D(z)=\left.Z(A)\right| _ {a_1=C(z),a_2=C(z^2),\dots ,a_d=C(z^d)}
$$

## 有标号体系

在有标号体系中会使用指数生成函数，即对于 $\mathcal{A}$ 的指数生成函数为

$$
A(z)=\sum _ {\alpha\in\mathcal{A}}\frac{z^{\lvert\alpha\rvert}}{\lvert\alpha\rvert !}=\sum _ {i\geq 0}\frac{a_i}{i!}z^i
$$

所以

$$
a_i=i!\lbrack z^i\rbrack A(z)
$$

而指数生成函数的乘法对应二项卷积。对于 $\mathcal{E}$ 和 $\mathcal{Z}$ 发现其与无标号体系中的是一致的，沿用定义。

### 集合的并

$$
\begin{aligned}
\mathcal{A}+\mathcal{B}\implies A(z)+B(z)&=\left(\sum _ {\alpha\in\mathcal{A}}\frac{z^{\lvert\alpha\rvert}}{\lvert\alpha\rvert !}\right)+\left(\sum _ {\beta\in\mathcal{B}}\frac{z^{\lvert\beta\rvert}}{\lvert\beta\rvert !}\right)\\
&=\sum _ {i\geq 0}\frac{a_i+b_i}{i!}z^i
\end{aligned}
$$

### 集合的有标号积

有标号积（ labelled product ）又称为星积（ star product ），我们需要明确其对于集合而言具体的作用。

例如集合 $\lbrace (1,2)\rbrace$ 满足 $\lvert \lbrace (1,2)\rbrace\rvert =2$ 和集合 $\lbrace (1,2,3)\rbrace$ 满足 $\lvert\lbrace (1,2,3)\rbrace\rvert =3$ 有

$$
\begin{aligned}
\lbrace (1,2)\rbrace \star\lbrace (1,2,3)\rbrace &=\lbrace ((1,2),(3,4,5))\rbrace +\lbrace ((1,3),(2,4,5))\rbrace +\lbrace ((1,4),(2,3,5))\rbrace \\
&+\lbrace ((1,5),(2,3,4))\rbrace +\lbrace ((2,3),(1,4,5))\rbrace +\lbrace ((2,4)(1,3,5))\rbrace\\
&+\lbrace ((2,5),(1,3,4))\rbrace +\lbrace ((3,4),(1,2,5))\rbrace +\lbrace ((3,5),(1,2,4))\rbrace\\
&+\lbrace ((4,5),(1,2,3))\rbrace
\end{aligned}
$$

共 $\binom{5}{2}=10$ 个，其对应的指数生成函数运算为

$$
\left( \frac{1}{2!}z^2\right)\left(\frac{1}{3!}z^3\right)=\frac{10}{5!}z^5
$$

我们注意有标号积虽然会对生成的集合中的对象重新标号并且限制标号的区间为 $1$ 到对象大小的闭区间范围内，但其相对顺序依然是与之前的相对顺序一致的。

由此我们定义集合上的有标号积的运算对应指数生成函数 $A(z)$ 和 $B(z)$ 的（二项）卷积

$$
\begin{aligned}
\mathcal{A}\star\mathcal{B}\implies A(z)B(z)&=\left(\sum _ {\alpha\in\mathcal{A}}\frac{z^{\lvert\alpha\rvert}}{\lvert\alpha\rvert !}\right)\left(\sum _ {\beta\in\mathcal{B}}\frac{z^{\lvert\beta\rvert}}{\lvert\beta\rvert !}\right)\\
&=\sum _ {\alpha\in\mathcal{A}}\sum _ {\beta\in\mathcal{B}}\binom{\lvert \alpha\rvert +\lvert\beta\rvert}{\lvert \alpha\rvert ,\lvert\beta\rvert}\frac{z^{\lvert \alpha\rvert +\lvert\beta\rvert}}{(\lvert \alpha\rvert +\lvert\beta\rvert)!}\\
&=\sum _ {i\geq 0}\sum _ {j\geq 0}\binom{i+j}{i}a_ib_jz^{i+j}
\end{aligned}
$$

其中

$$
\binom{a}{b_1,b_2,\dots ,b_n}=\frac{a!}{b_1! b_2! \cdots b_n!}\implies \binom{i+j}{i}=\binom{i+j}{j}
$$

也有 $\mathcal{A}\star(\mathcal{B}\star\mathcal{C})\cong (\mathcal{A}\star\mathcal{B})\star\mathcal{C}$ 。

来观察指数生成函数 $A^k(z)$ 的意义

$$
\begin{aligned}
A^k(z)&=\sum _ {N\geq 0}\lbrace \text{\# }k\text{-sequences of size }N\rbrace \frac{z^N}{N!}\\
&=k\sum _ {N\geq 0}\lbrace \text{\# }k\text{-cycles of size }N\rbrace \frac{z^N}{N!}\\
&=k!\sum _ {N\geq 0}\lbrace \text{\# }k\text{-sets of size }N\rbrace \frac{z^N}{N!}
\end{aligned}
$$

这些都是对应的限制构造，组合意义上是显然的。下面我们考察对于 $\mathcal{A} _ 0=\emptyset$ 的构造。

### 集合的 Sequence

$$
\operatorname{SEQ}(\mathcal{A})=\mathcal{E}+\mathcal{A}+(\mathcal{A}\star\mathcal{A})+(\mathcal{A}\star\mathcal{A}\star\mathcal{A})+\cdots \implies \frac{1}{1-A(z)}
$$

其中 $A(z)$ 为指数生成函数。

一个置换是 $\operatorname{SEQ}(\mathcal{Z})$ ，有 $n!\lbrack z^n\rbrack \frac{1}{1-z}=n!$ 符合我们对 $n$ 个元素置换的认知。

### 集合的 Cycle

$$
\operatorname{CYC}(\mathcal{A})=\mathcal{A}+\operatorname{CYC} _ 2(\mathcal{A})+\cdots\implies \log\frac{1}{1-A(z)}
$$

其中 $A(z)$ 为指数生成函数。

### 集合的 Set

$$
\operatorname{SET}(\mathcal{A})=\mathcal{E}+\mathcal{A}+\operatorname{SET} _ 2(\mathcal{A})+\cdots\implies \exp(A(z))
$$

其中 $A(z)$ 为指数生成函数。

有标号生成函数的部分有些仓促，先将概念写完，例子以后再补充吧。

## Lagrange 反演公式

我还没有什么清晰的认识，先放着吧。。。不过好像可以用来对许多树的生成函数提取系数。

## 参考文献

- <https://ac.cs.princeton.edu/home/>
- 叉义叉的博客 - [组合结构符号化学习笔记](https://www.luogu.com.cn/blog/zyxxs/zu-ge-jie-gou-fu-hao-hua-xue-xi-bi-ji)
- command\_block 的博客 - [多项式计数杂谈](https://www.luogu.com.cn/blog/command-block/sheng-cheng-han-shuo-za-tan)
- 一只 alpha1022 的小窝 - [浅谈多项式复合和拉格朗日反演](https://www.luogu.com.cn/blog/your-alpha1022/qian-tan-duo-xiang-shi-fu-ge-hu-la-ge-lang-ri-fan-yan)