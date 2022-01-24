这篇文章经过一些修改和补充后发在 [洛谷](https://www.luogu.com.cn/blog/242973/solution-p5432) 。。。

## 大整数运算

为了方便我只实现了十进制表示的大整数运算，并且使用数论变换作为快速算法。

首先，我们将十进制整数 `114514` 使用多项式表为 $f(x)=4+x+5x^2+4x^3+x^4+x^5$ 的形式，那么整数乘法即为卷积后调整一下进位即可（即在十进制下为 $f(10)$ ），因为这里使用了 $\mathbb{F} _ {998244353}\lbrack x\rbrack$ 中的多项式，所以必须保证多项式乘法不能溢出，后文将关注除法运算。

## 使用 Newton 法计算倒数的误差分析

二阶的 Newton 法一般描述为

$$
x _ {i+1}=x_i-\frac{f(x_i)}{f'(x_i)}
$$

这里我们构造 $f(x)=x^{-1}-a$ 来计算 $a^{-1}$ 的近似值，那么 $f'(x)=-x^{-2}$

$$
\begin{aligned}
x _ {i+1}&=x_i-\frac{x_i^{-1}-a}{-x_i^{-2}}\\
&=x_i(2-ax_i)
\end{aligned}
$$

设误差 $\varepsilon_i=1-ax_i$ 那么

$$
\begin{aligned}
\varepsilon _ {i+1}&=1-ax_i(2-ax_i)\\
&=1-2ax_i+(ax_i)^2\\
&=(1-ax_i)^2\\
&=\varepsilon_i^2
\end{aligned}
$$

上面虽然分析了正确性而且可以应用于大整数的运算，但是效率太低，我虽然实现了但是有很多的 bug 并且需要用到浮点数的运算。

## 基于 Newton 法的方法

整数的折半 Euclid 算法告诉我们商基本只和两个整数的高位相关，但是有进位所以需要一些误差分析和舍入。下面基本参考参考文献中的算法。

倪泽堃指出，对于 $n$ 位的正整数 $A=a_0+a_1\cdot 10+\cdots +a _ {n-1}\cdot 10^{n-1}$ （其中整数 $0\leq a_i\lt 10$ ）和 $m$ 位的正整数 $B$ ，可以计算 $A'=\left\lfloor 10^{2n}/A\right\rfloor$ 后计算 $\lfloor A'B/10^{2n}\rfloor$ 后进行调整可以得到 $\left\lfloor B/A\right\rfloor$ 。

既然我们使用十进制表示，那么对于形如 $\lfloor A/10^t\rfloor$ 可以简单使用类似于位运算的移位，此时对于 Newton 法也改造为求 $A/10^{2n}$ 的倒数

$$
\begin{aligned}
&{}x _ {i+1}=x_i(2-x_iA/10^{2n})\\
\iff &x _ {i+1}\cdot 10^{2n}=x_i(2\cdot 10^{2n}-x_iA)
\end{aligned}
$$

文中表示，若 $m\leq 2n$ 最后调整时误差不超过 $10$ ，否则我们令 $A'=\left\lfloor 10^{m+n}/A\right\rfloor$ 后计算 $\lfloor A'B/10^{m+n}\rfloor$ 即可。

考虑

$$
\begin{aligned}
&{}\frac{10^{2n}}{A}-1\lt A'\leq \frac{10^{2n}}{A}\\
\iff &\frac{10^{2n}B}{A}-B\lt A'B\leq \frac{10^{2n}B}{A}\\
\iff &\frac{B}{A}-\frac{B}{10^{2n}}\lt \frac{A'B}{10^{2n}}\leq \frac{B}{A}\\
\iff &\frac{B}{A}-1\lt \frac{A'B}{10^{2n}}\leq \frac{B}{A}\quad \left(\because \frac{B}{10^{2n}}\lt 1\right)
\end{aligned}
$$

在这里向下取整可以发现误差最多为 $1$ ，并且此处用 $m+n$ 替换 $2n$ 结果也是一样的。

难点在于如何求解 $A'$ ，文中给出了一种递归算法为

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{compute}(A)\text{:} \\
&\textbf{Input}\text{: an integer }A\gt 0 \text{ with }n\text{ digits (radix-10).}\\
&\textbf{Output}\text{: an integer }B\text{ such that }0\leq \left\lfloor \dfrac{10^{2n}}{A}\right\rfloor -B\lt 10^2\text{.}\\
1&\textbf{if }n\leq 2\textbf{ then return }\left(\left\lfloor \dfrac{10^{2n}}{A}\right\rfloor \right)\text{;}\\
2&n'\gets \left\lfloor \dfrac{n}{2}\right\rfloor +1\text{;}\\
3&q\gets \operatorname{compute}\left(\left\lfloor \dfrac{A}{10^{n-n'}}\right\rfloor\right)\cdot 10^{n-n'}\text{;}\\
4&\textbf{return }\left(\left\lfloor \dfrac{q(2\cdot 10^{2n}-qA)}{10^{2n}}\right\rfloor \right)\text{;}
\end{array}
$$

在第三步时我们取 $A$ 的高 $n'$ 位为 $A_0$ 计算 $q\approx \left\lfloor \dfrac{10^{2n'}}{A_0}\right\rfloor \cdot 10^{n-n'}\approx \left\lfloor\dfrac{10^{2n}}{A}\right\rfloor$ 后面为一次 Newton 迭代，我不会分析误差，个人猜测最坏的情况即 $A_0=\underbrace{10\dots 0} _ {n'\text{ digits}}$ 而 $A=\underbrace{10\dots 0} _ {n'\text{ digits}}\underbrace{9\dots 9} _ {n-n'\text{ digits}}$ 此时 Newton 迭代时误差最大，那么结果的误差看起来似乎也是最大的。

```py
def count_digit(a):
    cnt = 0
    while a != 0:
        a //= 10
        cnt += 1
    return cnt

def compute(a):
    da = count_digit(a)
    print(da, a)
    if da <= 2:
        return (10 ** (da * 2)) // a
    da0 = da // 2 + 1
    r = compute(a // (10 ** (da - da0))) * 10 ** (da - da0)
    print(r)
    return r * (2 * 10 ** (da * 2) - r * a) // 10 ** (da * 2)

a = 1000000000000000999999999999999
da = count_digit(a)
print(10 ** (da * 2) // a - compute(a))
```

最后输出的误差为 `99` ，原文中为“不超过 `100` ”，这里不清楚我的猜测是否正确，但我仍然使用了自己的猜测。另外测试发现似乎不依赖于最后一层递归给出当前准确的解，也是可以存在误差的。

## 参考文献

- [倪泽堃. 理性愉悦——高精度数值计算（2012WC）](https://github.com/lzyrapx/Competitive-Programming-Docs/blob/master/WC%E8%AE%B2%E8%AF%BE%E8%B5%84%E6%96%99/%E7%90%86%E6%80%A7%E6%84%89%E6%82%A6%E2%80%94%E2%80%94%E9%AB%98%E7%B2%BE%E5%BA%A6%E6%95%B0%E5%80%BC%E8%AE%A1%E7%AE%97%EF%BC%882012WC%EF%BC%89.pdf)
- stackoverflow - [Newton-Raphson Division With Big Integers](https://stackoverflow.com/questions/27801397/newton-raphson-division-with-big-integers).