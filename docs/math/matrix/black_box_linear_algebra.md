## 黑盒线性代数

黑盒线性代数的意思是我们没办法直接接触到该矩阵，但我们可以获取矩阵与向量的乘积，借此来进行计算。

### 最小多项式

Wiedemann 提出，对于黑盒矩阵 $\mathbf{A}\in\mathbb{F}^{n\times n}$ 和一个随机的向量 $\mathbf{v}\in\mathbb{F}^n$ 其 Krylov 序列 $\lbrace \mathbf{A}^i\mathbf{v} \rbrace _ {i=0}^\infty$ 的最小多项式 $f^{\mathbf{A},\mathbf{v}}$ 很大可能等于 $\mathbf{A}$ 的最小多项式 $f^{\mathbf{A}}$ ，而对于第二个随机向量 $\mathbf{u}$ 其 bilinear projection 序列 $\lbrace \mathbf{u}^{\mathrm{T}}\mathbf{A}^i\mathbf{v} \rbrace _ {i=0}^\infty$ 的最小多项式 $f^{\mathbf{A},\mathbf{v}} _ \mathbf{u}$ 很大可能等于 $f^{\mathbf{A},\mathbf{v}}$ 。而 $f^{\mathbf{A},\mathbf{v}} _ \mathbf{u}$ 我们可以借助 Berlekamp-Massey 算法来计算（只需翻转即能得到首一多项式，这是因为 LFSR （序列的关系多项式）与最小多项式定义不同）。

### 行列式

根据上面提到的，假设 $\mathbf{A}$ 的特征多项式 $\chi (\mathbf{A})=\det(\lambda \mathbf{I}-\mathbf{A})$ 等于 $f^{\mathbf{A}}$ 那么有很大可能有这样的等式

$$
\det(\lambda \mathbf{I}-\mathbf{A})=f^{\mathbf{A}}=f^{\mathbf{A},\mathbf{v}}=f^{\mathbf{A},\mathbf{v}} _ \mathbf{u}
$$

Kaltofen 和 Pan 指出这个可能性至少为 $1-2\deg(f^{\mathbf{A}})/\lvert S\rvert$ 。因此

$$
\det(\mathbf{A})=(-1)^nf^{\mathbf{A},\mathbf{v}} _ \mathbf{u}(0)
$$

也就是其常数项，但是前提是 $f^{\mathbf{A}}=\chi(\mathbf{A})$ 。

在 2002 年 Chen 等提出了用一个对角矩阵

$$
\tilde{\mathbf{A}}=\mathbf{A}\cdot \operatorname{diag}(d_1,\cdots ,d_n)
$$

可以使得矩阵 $\tilde{\mathbf{A}}$ 满足这个条件，而 $\det(\operatorname{diag}(d_1,\cdots ,d_n))=\prod _ {i=1}^nd_i$ 。

我们求出 $\det(\tilde{\mathbf{A}})/\det(\operatorname{diag}(d_1,\cdots ,d_n))$ 即可。

## 参考文献

- Douglas H. Wiedemann (1986). Solving Sparse Linear Equations Over Finite Fields.