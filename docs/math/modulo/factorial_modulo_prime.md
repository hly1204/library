## 阶乘模素数

此文译自参考文献！

定义多项式 $f(x)=\prod _ {i=1}^n(x+i)$ 那么 $n!=f(0)$ ，令 $v=\left\lfloor \sqrt{n}\right\rfloor$ 和 $g(x)=\prod _ {i=1}^v(x+i)$ 那么

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

在这里我们采取一种更简单的方法即令 $v=2^{\lceil \log_2\sqrt{p}\rceil}\approx \sqrt{p}$ ，这样我们只需要倍增即可，无需额外的调整，但目前我的实现似乎有很大问题，能输出正确解但是速度非常慢。

若考虑从 $g_d(0),g_d(v),\dots ,g_d(dv)$ 推出 $g_{d+1}(0),g_{d+1}(v),\dots ,g_{d+1}(dv+v)$ 显然可在线性时间做到（额外的一项暴力计算即可），这样我们可以求出任意的 $d$ 对应的点值！在 [EntropyIncreaser 的提交记录](https://loj.ac/s/1110094) 中使用了不同的技术使得 DFT 的次数减少，我也不知道该怎么做到的，等有机会想请教 EntropyIncreaser ！

目前代码是错误的！因为可能在平移时遇到分母为零的情况。

## 参考文献

- [ZZQ 的博客](https://www.cnblogs.com/zzqsblog/p/8408691.html)
- [Min\_25 的博客（已被删除）](http://min-25.hatenablog.com/entry/2017/04/10/215046)