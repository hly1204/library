## 第一类无符号斯特林数

第一类无符号斯特林数一般记作

$$
{n\brack k}
$$

是 $n$ 个元素排成 $k$ 个（非空）轮换的方案数，所谓一个轮换即 $\lbrack A,B,C,D\rbrack$ 理解为

$$
\lbrack A,B,C,D\rbrack =\lbrack B,C,D,A\rbrack =\lbrack C,D,A,B\rbrack =\lbrack D,A,B,C\rbrack
$$

也就是“环绕”的，首尾相连的。因此若我们想在原有的一个轮换中加入一个元素，那么方案数为原轮换中的元素数（将一个轮换想象成一个简单的首尾相连的环，方案数为其中边数）。

当 $k\lt 0$ 且 $n\geq 0$ 时，认为 ${n\brack k}=0$ 。

| $n$ | ${n\brack 0}$ | ${n\brack 1}$ | ${n\brack 2}$ | ${n\brack 3}$ | ${n\brack 4}$ | ${n\brack 5}$ | ${n\brack 6}$ | ${n\brack 7}$ | ${n\brack 8}$ | ${n\brack 9}$ |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0 | 1 |  |  |  |  |  |  |  |  |  |
| 1 | 0 | 1 |  |  |  |  |  |  |  |  |
| 2 | 0 | 1 | 1 |  |  |  |  |  |  |  |
| 3 | 0 | 2 | 3 | 1 |  |  |  |  |  |  |
| 4 | 0 | 6 | 11 | 6 | 1 |  |  |  |  |  |
| 5 | 0 | 24 | 50 | 35 | 10 | 1 |  |  |  |  |
| 6 | 0 | 120 | 274 | 225 | 85 | 15 | 1 |  |  |  |
| 7 | 0 | 720 | 1764 | 1624 | 735 | 175 | 21 | 1 |  |  |
| 8 | 0 | 5040 | 13068 | 13132 | 6769 | 1960 | 322 | 28 | 1 |  |
| 9 | 0 | 40320 | 109584 | 118124 | 67284 | 22449 | 4536 | 546 | 36 | 1 |

其递推公式为

$$
{n+1\brack k}=n{n\brack k}+{n\brack k-1},\quad n\geq 0\tag{1}
$$

将一个元素插入有 $n$ 个元素的 $k$ 个轮换中有 $n$ 种方案，或者原先有 $k-1$ 个轮换，新元素单独为一个轮换。

我们关注表格中的一行，有

$$
\begin{aligned}
x^{\overline{0}}&=1\\
x^{\overline{1}}&=0+x\\
x^{\overline{2}}&=x(x+1)=0+x+x^2\\
x^{\overline{3}}&=x(x+1)(x+2)=0+2x+3x^2+x^3\\
x^{\overline{4}}&=x(x+1)(x+2)(x+3)=0+6x+11x^2+6x^3+x^4\\
\vdots
\end{aligned}
$$

我们猜测有

$$
x^{\overline{n}}=\sum _ {i=0}^n{n\brack i}x^i,\quad n\geq 0
$$

使用数学归纳法，当 $n=0$ 时显然成立，假设对于 $n\gt 0$ 成立那么

$$
\begin{aligned}
x^{\overline{n+1}}&=x^{\overline{n}}\cdot (x+n)\\
&=(x+n)\sum _ {i=0}^n{n\brack i}x^i\\
&=n\sum _ {i=0}^{n+1}{n\brack i}x^i+\sum _ {i=0}^{n+1}{n\brack i-1}x^i,\quad \left(\because {n\brack -1}={n\brack n+1}=0\right)\\
&=\sum _ {i=0}^{n+1}{n+1\brack i}x^i
\end{aligned}
$$

得证。令 $f_n(x)=x^{\overline{n}}$ 那么 $f_{2n}(x)=x^{\overline{n}}\cdot (x+n)^{\overline{n}}=f_n(x)f_n(x+n)$ 使用多项式平移的方法即可。

无符号斯特林数是有符号斯特林数的绝对值

$$
{n\brack k}=\lvert s(n,k)\rvert =(-1)^{n-k}s(n,k)
$$

## 第二类斯特林数

第二类斯特林数记为

$$
{n\brace k}
$$

为将 $n$ 个元素划分为 $k$ 个非空子集的方案数。特别的

$$
{0\brace k}=\begin{cases}1,&k=0,\\0,&k\gt 0.\end{cases}
$$

| $n$ | ${n\brace 0}$ | ${n\brace 1}$ | ${n\brace 2}$ | ${n\brace 3}$ | ${n\brace 4}$ | ${n\brace 5}$ | ${n\brace 6}$ | ${n\brace 7}$ | ${n\brace 8}$ | ${n\brace 9}$ |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| 0 | 1 |  |  |  |  |  |  |  |  |  |
| 1 | 0 | 1 |  |  |  |  |  |  |  |  |
| 2 | 0 | 1 | 1 |  |  |  |  |  |  |  |
| 3 | 0 | 1 | 3 | 1 |  |  |  |  |  |  |
| 4 | 0 | 1 | 7 | 6 | 1 |  |  |  |  |  |
| 5 | 0 | 1 | 15 | 25 | 10 | 1 |  |  |  |  |
| 6 | 0 | 1 | 31 | 90 | 65 | 15 | 1 |  |  |  |
| 7 | 0 | 1 | 63 | 301 | 350 | 140 | 21 | 1 |  |  |
| 8 | 0 | 1 | 127 | 966 | 1701 | 1050 | 266 | 28 | 1 |  |
| 9 | 0 | 1 | 255 | 3025 | 7770 | 6951 | 2646 | 462 | 36 | 1 |

例如将四个元素分为三个非空集合有

$$
\lbrace 1\rbrace \cup\lbrace 2\rbrace \cup\lbrace 3,4\rbrace ,\lbrace 1\rbrace \cup\lbrace 2,4\rbrace \cup\lbrace 3\rbrace ,\lbrace 1,4\rbrace \cup\lbrace 2\rbrace \cup\lbrace 3\rbrace ,\\
\lbrace 1,3\rbrace \cup\lbrace 2\rbrace \cup\lbrace 4\rbrace ,
\lbrace 1\rbrace \cup\lbrace 2,3\rbrace \cup\lbrace 4\rbrace ,\lbrace 1,2\rbrace \cup\lbrace 3\rbrace \cup\lbrace 4\rbrace 
$$

故 ${4\brace 3}=6$ 。其递推式为

$$
{n+1\brace k}=k{n\brace k}+{n\brace k-1},\quad n\geq 0\tag{2}
$$

将一个新元素加入 $k$ 个子集有 $k$ 种可能，或者自己单独为一个集合。

通过比较第一类无符号斯特林数和第二类斯特林数的递推式我们发现

$$
{n\brack k}\geq {n\brace k},\quad n\geq 0
$$

因为 $k\leq n$ 根据 $(1),(2)$ 显然。且

$$
\begin{aligned}
{n\brace k}&=\frac{1}{k!}\sum _ {i=0}^k(-1)^i\binom{k}{i}(k-i)^n\\
&=\sum _ {i=0}^k\frac{(-1)^i (k-i)^n}{i!(k-i)!}
\end{aligned}
$$

为卷积形式。另外注意对于 $i=0,\dots ,k$ 求出 $i^n$ 有

$$
i^n=d^n\cdot (i/d)^n
$$

此时只需计算 $i$ 为素数的情况。关注表格中的每一行和

$$
\begin{aligned}
x^0&=1\\
x^1&=0+x^{\underline{1}}\\
x^2&=0+x^{\underline{1}}+x^{\underline{2}}\\
x^3&=0+x^{\underline{1}}+3x^{\underline{2}}+x^{\underline{3}}\\
x^4&=0+x^{\underline{1}}+7x^{\underline{2}}+6x^{\underline{3}}+x^{\underline{4}}\\
\vdots
\end{aligned}
$$

我们猜测有

$$
x^n=\sum _ {i=0}^n{n\brace i}x^{\underline{i}},\quad n\geq 0
$$

当 $n=0$ 时显然，假设在 $n\gt 0$ 时成立，那么

$$
\begin{aligned}
x^{n+1}&=x^n\cdot x\\
&=x\sum _ {i=0}^n{n\brace i}x^{\underline{i}}\\
&=\sum _ {i=0}^n{n\brace i}x^{\underline{i+1}}+\sum _ {i=0}^n{n\brace i}i\cdot x^{\underline{i}},\quad \left(\because x\cdot x^{\underline{i}}=x^{\underline{i+1}}+i\cdot x^{\underline{i}}\right)\\
&=\sum _ {i=0}^{n+1}{n\brace i-1}x^{\underline{i}}+\sum _ {i=0}^{n+1}{n\brace i}i\cdot x^{\underline{i}},\quad \left(\because {n\brace -1}={n\brace n+1}=0\right)\\
&=\sum _ {i=0}^{n+1}{n+1\brace i}x^{\underline{i}}
\end{aligned}
$$

得证。将 $x^{n}$ 转换为下降幂多项式容易联想到其点值的指数生成函数，使用下降幂多项式乘法中提到的方法发现本质和上述卷积相同。

## 参考文献

- Min\_25 的[博客](https://min-25.hatenablog.com/entry/2015/04/07/160154)
- WolframMathWorld. [Stirling Number of the First Kind](https://mathworld.wolfram.com/StirlingNumberoftheFirstKind.html)
- WolframMathWorld. [Stirling Number of the Second Kind](https://mathworld.wolfram.com/StirlingNumberoftheSecondKind.html)
- 高德纳等. 具体数学.