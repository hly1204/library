---
title: Radix-2 Walsh Transform
documentation_of: ./radix_2_Walsh_transform.hpp
---

## Walsh 变换

Walsh 变换一般用于解决一类卷积问题如：给出序列 $a$ 和 $b$ 求出 $c$ 满足

$$
c_i=\sum _ {j\oplus k =i}a_jb_k
$$

其中 $\oplus $ 表示二元的异或运算，在 cpp 中可能是 `j ^ k`。

简单来说我们将 FFT 中的乘法舍去就得到了 Walsh 变换。考虑 radix-2 NTT 算法中第一步是无需乘法的，我们所进行的无非就是不停对于每次分成的两部分应用原先应该用于第一步的 radix-2 NTT 的步骤，所以该算法在某种意义上可以认为是高维的变换？

现在我们考虑其正确性，因为每一步都是一样的，只需考虑第一步即可。

令 $A(x)=\sum _ {i=0}^{2n-1}a_ix^i$ 和 $B(x)=\sum _ {i=0}^{2n-1}b_ix^i$ 后 $A(x)=A_0(x)+x^n\cdot A_1(x)$ 和 $B(x)=B_0(x)+x^n\cdot B_1(x)$ 且 $\deg(B_1),\deg(A_1)\lt n$ 和 $n\in\lbrace 1,2,4,\dots ,2^t,\dots \rbrace$ 那么应用一次变换后得到

$$
\begin{bmatrix}
1&1\\
1&-1
\end{bmatrix}
\begin{bmatrix}
A_0\\
A_1
\end{bmatrix}=
\begin{bmatrix}
A_0+A_1\\
A_0-A_1
\end{bmatrix}
$$

令 $\oplus$ 对两个多项式表示上述卷积，且假设我们求出了 $C_0=(A_0+A_1)\oplus (B_0+B_1)$ 和 $C_1=(A_0-A_1)\oplus (B_0-B_1)$ 对于 $i=0,1,\dots ,n-1$ 和 $j,k\lt n$ 有

$$
\begin{aligned}
\lbrack x^i\rbrack C_0&=\sum _ {j\oplus k=i}(a_j+a _ {j+n})(b_k+b _ {k+n})\\
&=\sum _ {j\oplus k=i}(a_jb_k+a _ {j+n}b_k+a_jb _ {k+n}+a _ {j+n}b _ {k+n})
\end{aligned}
$$

和

$$
\begin{aligned}
\lbrack x^i\rbrack C_1&=\sum _ {j\oplus k=i}(a_j-a _ {j+n})(b_k-b _ {k+n})\\
&=\sum _ {j\oplus k=i}(a_jb_k-a _ {j+n}b_k-a_jb _ {k+n}+a _ {j+n}b _ {k+n})
\end{aligned}
$$

而应用一次逆变换为

$$
\frac{1}{2}
\begin{bmatrix}
1&1\\
1&-1
\end{bmatrix}
\begin{bmatrix}
C_0\\
C_1
\end{bmatrix}
$$

那么有

$$
2^{-1}\lbrack x^i\rbrack (C_0+C_1)=\sum _ {j\oplus k=i}a_jb_k+\sum _ {j\oplus k=i}a _ {j+n}b_{k+n}
$$

由 $\oplus$ 的性质可知若 $j$ 和 $k$ 中有一个大于 $n$ 另一个小于 $n$ 的话 $j\oplus k\gt n$，所以下标确实取遍了所有可能的值，$C_0-C_1$ 同理。

当然，我们要将 radix-2 修改为 radix-4 也是轻而易举的。

但是注意这种写法显然并不是最优的，并且理解起来也有点繁琐，可能需要重新检视。

## 参考文献

- fxtbook.