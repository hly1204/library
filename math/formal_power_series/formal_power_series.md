---
title: Formal Power Series
documentation_of: ./formal_power_series.hpp
---

我们假设后文没有定义的都属于 NTT 友好的模数的形式幂级数环 $\mathbb{F} _ p\lbrack \lbrack x\rbrack \rbrack$。

注意：这篇文章可能有很多错误。

在这里我将“易于实现”放在第一位考虑，更复杂的算法我没有加入也没有阅读。

## 倍增法求逆元

给出 $f(x)$ 满足 $x\nmid f(x)$，为了方便省略 $x$，假设我们已经得到了 $gf\equiv 1\pmod{x^{2n}}$ 中的 $g_0=g\bmod{x^n}$ 那么

$$
g_0-g\equiv 0\pmod{x^n}
$$

两边平方后同时乘以 $f$ 后有

$$
fg_0^2-2fg_0g+fg^2\equiv 0\pmod{x^{2n}}
$$

那么

$$
fg_0^2-2g_0+g\equiv 0\pmod{x^{2n}}\iff g\equiv g_0+g_0(1-fg_0)\pmod{x^{2n}}
$$

观察上式，发现 $1-fg_0$ 的前 $n$ 项系数都为零，而对 $f$ 和 $g_0$ 都做 $2n$ 长 DFT 后点值相乘再 IDFT 可以求出 $fg_0\bmod (x^{2n}-1)$，溢出的项恰好会出现在前 $n$ 项里（我们没有必要做更长的 DFT），而我们只需要后 $n$ 项即可还原出 $1-fg_0$。这也是一个基础技巧，会在以后的文中用到。

## Newton 法

定义导子 $\mathfrak{D}$ 作用于函数 $f(x)$ 为其关于 $x$ 的导数（对于形式幂级数而言，其导数一般指形式导数（formal derivative））。

给出 $f_0=f\bmod{x^n}$，我们求出 $f$ 满足 $A(f)=0$，其中 $A(f)$ 可以是某个函数，例：假设给出 $g$ 要求 $g^{-1}$ 那么可设 $A(f)=f^{-1}-g$。我们观察 $A(f)$ 在 $f_0$ 处的 Taylor 公式

$$
A(f)=A(f_0)+\frac{\mathfrak{D}(A(f_0))(f-f_0)}{1!}+\frac{\mathfrak{D}^2(A(f_0))(f-f_0)^2}{2!}+\cdots
$$

因为 $f-f_0\equiv 0\pmod{x^n}$ 所以 $(f-f_0)^2\equiv 0\pmod{x^{2n}}$，那么

$$
A(f)\equiv A(f_0)+\mathfrak{D}(A(f_0))(f-f_0)\equiv 0\pmod{x^{2n}}
$$

稍加整理得

$$
f\equiv f_0-\frac{A(f_0)}{\mathfrak{D}(A(f_0))}\pmod{x^{2n}}
$$

那么我们每次迭代都可以将准确的系数翻倍。

我们考虑使用符号 $\mathsf{E}(n)$ 表示一次 $n$ 长 DFT 需要的时间，那么 $\mathsf{E}(2n)=2\mathsf{E}(n)+O(n)$ 但是为了方便，我们忽略线性的运算，记作 $\mathsf{E}(2n)=2\mathsf{E}(n)$，用 $F _ n(f)$ 表示求 $f$ 的 $n$ 长 DFT（必须保证 $\deg f\lt n$，否则需要写成 $F _ n(f\bmod x^n)$ 或 $F _ n(f\bmod{(x^n-1)})$ 或其他类似的）。

令 $F _ n^{-1}(F _ n(f)F _ n(g))=fg\bmod{(x^n-1)}$。若 $c$ 为某个常数，那么 $F _ n(c)$ 只需要消耗线性时间。

### Maclaurin 公式

对于幂级数 $f$ 的指数我们可以通过 Maclaurin 公式如

$$
\exp(f)=1+f+\frac{f^2}{2!}+\cdots =\sum _ {i\geq 0}\frac{f^i}{i!}
$$

而我们都知道幂级数可以是无限长的，若 $f(0)\neq 0$ 那么不收敛。所以这里认为其常数项为零。

同样的我们可以定义其逆运算即

$$
\log\left(\sum _ {i\geq 0}\frac{f^i}{i!}\right)=f
$$

我们知道 $\mathfrak{D}(\log(x))=1/x$ 而 $\mathfrak{D}(\log(f))=\mathfrak{D}(f)/f$ 那么 $\log(f)=\int (\mathfrak{D}(f)/f)$，这里使用 $\int ax^b=a/(b+1)x^{b+1}$ 其中 $b\geq 0$。省略 $\mathrm{d}x$ 使更简洁。实际上，可能将指数和对数理解为复合可能更合适。

### 逆元

也可称为幂级数的倒数。给出 $f$ 满足 $x\nmid f$ 和 $g_0=g\bmod{x^n}$ 其中 $g=1/f$。我们想求出 $g\bmod x^{2n}$。我们令 $A(g)=g^{-1}-f$ 那么

$$
g\equiv g_0-\frac{g_0^{-1}-f}{-g_0^{-2}}\pmod{x^{2n}}
$$

有

$$
g\equiv g_0(2-fg_0)\pmod{x^{2n}}
$$

和上述倍增法得到的结果一样。

#### 方法 1

计算

$$
F _ {4n}^{-1}(F _ {4n}(g_0)(F _ {4n}(2)-F _ {4n}(f\bmod x^{2n})F _ {4n}(g_0)))
$$

- 计算 $F _ {4n}(g_0)$ 需要 $4\mathsf{E}(n)$。
- 计算 $F _ {4n}(f\bmod x^{2n})$ 需要 $4\mathsf{E}(n)$。
- 计算 $F _ {4n}(2)$ 需要线性时间忽略。
- 计算 $F _ {4n}^{-1}(F _ {4n}(g_0)(F _ {4n}(2)-F _ {4n}(f\bmod x^{2n})F _ {4n}(g_0)))$ 需要 $4\mathsf{E}(n)$。

共 $12\mathsf{E}(n)$。

注意到由前 $n$ 项经过一次迭代求出前 $2n$ 项的时间和从第一项开始迭代至前 $n$ 项的时间一致（假设 $n$ 是二的幂次）。

#### 方法 2

令 $\epsilon =((f\bmod x^{2n})g_0-1)\bmod{x^{2n}}$ 注意到 $g\equiv g_0-\epsilon g_0\pmod{x^{2n}}$ 且注意 $(f\bmod x^{2n})g_0$ 的前 $n$ 项已知，即 $(f\bmod x^{2n})g_0\equiv 1\pmod{x^n}$ 那么我们只需计算

$$
F _ {2n}^{-1}(F _ {2n}(f\bmod x^{2n})F _ {2n}(g_0))=(f\bmod x^{2n})g_0\bmod{(x^{2n}-1)}
$$

将前 $n$ 项设置为 $0$ 则得到了 $\epsilon$。然后计算

$$
F _ {2n}^{-1}(F_{2n}(\epsilon)F _ {2n}(g_0))=\epsilon g_0\bmod{(x^{2n}-1)}
$$

将前 $n$ 项设置为 $0$ 则得到了 $\epsilon g_0\bmod{x^{2n}}$（因为我们知道 $\epsilon g_0$ 的前 $n$ 项为 $0$），而其中 $F _ {2n}(g_0)$ 用到了两次，我们可以重复使用。

- 计算 $F _ {2n}(g_0)$ 需要 $2\mathsf{E}(n)$。
- 计算 $F _ {2n}(f\bmod x^{2n})$ 需要 $2\mathsf{E}(n)$。
- 计算 $F _ {2n}^{-1}(F _ {2n}(f\bmod x^{2n})F _ {2n}(g_0))$ 需要 $2\mathsf{E}(n)$（若包括上面已经计算的式子则无需额外计算，若未提及则需要计算，后文中会有所省略）。
- 计算 $F _ {2n}(\epsilon )$ 需要 $2\mathsf{E}(n)$。
- 计算 $F _ {2n}^{-1}(F_{2n}(\epsilon)F _ {2n}(g_0))$ 需要 $2\mathsf{E}(n)$。

共 $10\mathsf{E}(n)$。

### 商数或对数

给出 $h$ 和 $f$ 且 $x\nmid f$ 求 $q=h/f\bmod x^{2n}$，我们依然定义 $g=1/f$ 和 $g_0=g\bmod{x^n}$ 而 $\epsilon =((f\bmod x^{2n})g_0-1)\bmod{x^{2n}}$。

令 $h_0=h\bmod x^n$ 且 $h\bmod x^{2n}=h_0+h_1x^n$ 且 $\epsilon =0+\epsilon_1x^n$。

对数直接使用一次求商数的方法即可。

#### 方法 1

直接计算

$$
F _ {4n}^{-1}(F _ {4n}(h\bmod x^{2n})F _ {4n}(g\bmod x^{2n}))
$$

- 计算 $g\bmod x^{2n}$ 需要 $20\mathsf{E}(n)$。
- 计算 $F _ {4n}^{-1}(F _ {4n}(h\bmod x^{2n})F _ {4n}(g\bmod x^{2n}))$ 需要 $12\mathsf{E}(n)$。

共 $32\mathsf{E}(n)$，计算 $q\bmod{x^n}$ 和 $g\bmod{x^n}$ 需 $16\mathsf{E}(n)$。

#### 方法 2

我们希望从 $g_0$ 来计算 $g\bmod x^{2n}$ 而 $g\equiv g_0(1-\epsilon)\pmod{x^{2n}}$ 那么可以计算 $hg\equiv g_0h(1-\epsilon)\pmod{x^{2n}}$ 我们优先选择计算

$$
h(1-\epsilon)\equiv h-h\epsilon \equiv h-h_0\epsilon \pmod{x^{2n}}
$$

因为我们注意到 $\epsilon \equiv 0\pmod{x^n}$ 那么

$$
\begin{aligned}
(h\bmod x^{2n})\epsilon &\equiv (h_0+h_1x^n)(\epsilon_1x^n)\\
&\equiv h_0\epsilon_1x^n+h_1\epsilon_1x^{2n}\\
&\equiv h_0\epsilon \pmod{x^{2n}}
\end{aligned}
$$

那么我们计算 $F _ {2n}^{-1}(F _ {2n}(h\bmod x^n)F _ {2n}(\epsilon))$ 后将前 $n$ 项设置为 $0$ 即得到了 $(h\epsilon )\bmod{x^{2n}}$。

- 计算 $g_0$ 需要 $10\mathsf{E}(n)$。
- 计算 $\epsilon$ 需要计算 $F _ {2n}^{-1}(F _ {2n}(f\bmod x^{2n})F _ {2n}(g_0))$ 共 $6\mathsf{E}(n)$。
- 计算 $h(1-\epsilon )\bmod{x^{2n}}$ 需要计算 $h-h_0\epsilon $ 需要计算 $F _ {2n}^{-1}(F _ {2n}(h_0)F _ {2n}(\epsilon))$ 共 $6\mathsf{E}(n)$。
- 计算 $g_0(h(1-\epsilon))\bmod{x^{2n}}$ 需要计算 $F _ {4n}^{-1}(F _ {4n}(g_0)F _ {4n}((h(1-\epsilon))\bmod x^{2n}))$ 而其中 $F _ {2n}(g_0)$ 已经计算过，那么只需要额外 $2\mathsf{E}(n)$ 时间就能得到 $F _ {4n}(g_0)$。

因为（假设）我们没有办法在做 $3$ 的倍数长度的 DFT，否则可以求 $F _ {3n}^{-1}(F _ {3n}(g_0)F _ {3n}((h(1-\epsilon))\bmod x^{2n}))$。

共 $32\mathsf{E}(n)$，计算 $q\bmod x^n$ 需要 $16\mathsf{E}(n)$（注意这里没有一同求出 $g\bmod{x^n}$）。

#### 方法 3

$$
q\bmod{x^{2n}}=g_0h_0+(g_0h_1+g_1h_0)x^n\bmod{x^{2n}}
$$

- 计算 $g_0$ 需要 $10\mathsf{E}(n)$ 
- 计算 $F _ {2n}(g_0)$ 需要 $2\mathsf{E}(n)$。
- 计算 $g_1$ 只需要额外 $8\mathsf{E}(n)$。
- 计算 $F _ {2n}(h_0)$ 、 $F _ {2n}(h_1)$ 和 $F _ {2n}(g_1)$ 需要 $6\mathsf{E}(n)$。
- 计算 $F _ {2n}^{-1}(F _ {2n}(g_0)F _ {2n}(h_0))$ 和 $F _ {2n}^{-1}(F _ {2n}(g_0)F _ {2n}(h_1)+F _ {2n}(g_1)F _ {2n}(h_0))$ 后只取前 $n$ 项即可，需要 $4\mathsf{E}(n)$。

共 $30\mathsf{E}(n)$ 那么计算 $q\bmod{x^n}$ 和 $g\bmod{x^n}$ 需 $15\mathsf{E}(n)$。

#### 方法 4

我们关注方法 2 中的

$$
q\equiv hg\equiv g_0h(1-\epsilon)\pmod{x^{2n}}
$$

我们希望计算 $h(1-\epsilon_1x^n)$ 再计算 $g_0h(1-\epsilon_1x^n)$。而这里 $\deg(\epsilon_1)\lt n$。

令 $u_1=h_1-\epsilon_1h_0\bmod{x^n}$ 那么

$$
\begin{aligned}
h(1-\epsilon_1x^n)&\equiv (h_0+h_1x^n)(1-\epsilon_1x^n)\\
&\equiv h_0+h_1x^n-\epsilon_1h_0x^n-\epsilon_1h_1x^{2n}\\
&\equiv h_0+(h_1-\epsilon_1h_0)x^n\pmod{x^{2n}}\\
&\equiv h_0+u_1x^n\pmod{x^{2n}}
\end{aligned}
$$

所以

$$
q\equiv h(1-\epsilon_1x^n)g_0\equiv h_0g_0+u_1g_0x^n\pmod{x^{2n}}
$$

- 计算 $g_0$ 需要 $10\mathsf{E}(n)$。
- 计算 $\epsilon $ 需要计算 $F _ {2n}^{-1}(F _ {2n}(f\bmod x^{2n})F _ {2n}(g_0))$ 需要 $6\mathsf{E}(n)$。
- 计算 $F _ {2n}^{-1}(F _ {2n}(\epsilon_1)F _ {2n}(h_0))$ 需要 $6\mathsf{E}(n)$。此时可以算出 $u_1$。
- 计算 $F _ {2n}^{-1}(F _ {2n}(u_1)F _ {2n}(g_0))$ 需要 $4\mathsf{E}(n)$。
- 计算 $F _ {2n}^{-1}(F _ {2n}(h_0)F _ {2n}(g_0))$ 需要 $2\mathsf{E}(n)$。

共需要 $28\mathsf{E}(n)$，那么计算 $q\bmod{x^n}$ 需要 $14\mathsf{E}(n)$。

#### 方法 5

以上方法都是 Dan. J. Bernstein 论文中的手法，这是 Guillaume Hanrot 和 Paul Zimmermann 论文中提出的。

令 $q_0=h_0g_0\bmod{x^n}=q\bmod{x^n}$ 和 $A(q)=qf-h$ 那么

$$
q\equiv q_0-\frac{q_0f-h}{f}\pmod{x^{2n}}
$$

此时我们发现 $q_0f\equiv h\pmod{x^n}$ 那么意味着我们只需计算

$$
q\equiv q_0-(q_0f-h)g_0\pmod{x^{2n}}
$$

令 $(q_0f-h)\bmod{x^{2n}}=t_1x^n$ 那么 $q\equiv q_0-t_1g_0x^n\pmod{x^{2n}}$。

- 计算 $g_0$ 需要 $10\mathsf{E}(n)$。
- 计算 $q_0$ 需要计算 $F _ {2n}^{-1}(F _ {2n}(h_0)F _ {2n}(g_0))$ 需要 $6\mathsf{E}(n)$。
- 计算 $t_1$ 需要计算 $F _ {2n}^{-1}(F _ {2n}(q_0)F _ {2n}(f\bmod x^{2n}))$ 需要 $6\mathsf{E}(n)$。
- 计算 $t_1g_0\bmod x^n$ 需要计算 $F _ {2n}^{-1}(F _ {2n}(t_1)F _ {2n}(g_0))$ 需要 $4\mathsf{E}(n)$。

共 $26\mathsf{E}(n)$，那么计算 $q\bmod{x^n}$ 需要 $13\mathsf{E}(n)$。

论文哥在这里提出了一个优化，但是我没有理解如何应用，可以做到 $12.5\mathsf{E}(n)$（原文更小一些，因为倒数的算法更快）。

### 指数

给出 $h$，令 $f=\exp(h)$ 和已知 $f_0=f\bmod{x^n}$ 求 $f\bmod{x^{2n}}$。

令 $A(f)=\log(f)-h$ 那么

$$
\begin{aligned}
f&\equiv f_0-\frac{\log(f_0)-h}{1/f_0}\pmod{x^{2n}}\\
&\equiv f_0-f_0(\log(f_0)-h)\pmod{x^{2n}}\\
&\equiv f_0-f_0\left(\smallint (\mathfrak{D}(f_0)/f_0)-h\right)\pmod{x^{2n}}
\end{aligned}
$$

其中 $\log(f_0)\equiv h\pmod{x^n}$ 显然。

令 $g=1/f=1/\exp(h)$ 和 $g_0=g\bmod x^n$。注意这里需要求出 $1/f_0\bmod{x^{2n}}$。

基础的复合函数求导公式在这里很重要 $\mathfrak{D}(\exp(h))=\mathfrak{D}(h)\exp(h)$。

#### 方法 1

- 计算 $\log(f_0)\bmod{x^{2n}}$ 需要 $26\mathsf{E}(n)$ 也可以一起计算 $F _ {2n}(f_0)$。
- 计算 $F _ {2n}^{-1}(F _ {2n}(\log(f_0)-h\bmod{x^{2n}})F _ {2n}(f_0))$ 需要 $4\mathsf{E}(n)$。

共 $30\mathsf{E}(n)$，所以计算 $\exp(h)\bmod{x^n}$ 需要 $30\mathsf{E}(n)$。

注意这里利用商数时的做法只需求 $g_0=1/f_0\bmod{x^n}$ 那么我们是否可以一直维护 $g_0$ 呢？

#### 方法 2

令 $q=\mathfrak{D}(h)\bmod x^{n-1}$ 和 $w=q+g_0(\mathfrak{D}(f_0)-f_0q)\bmod x^{2n-1}$ 那么

$$
f\equiv f_0+f_0(h-\smallint w)\pmod{x^{2n}}
$$

我们只需说明 $w\equiv \mathfrak{D}(f_0)/f_0\pmod {x^{2n-1}}$，因为 $h=\log(f)=\smallint \mathfrak{D}(f)/f$ 所以

$$
q\equiv \mathfrak{D}(h)\equiv \mathfrak{D}(f_0)/f_0\pmod{x^{n-1}}
$$

而 $\mathfrak{D}(f)\equiv fq\pmod{x^{n-1}}$ 和商数的方法 5 如出一辙。

注意在算法结束后可以得到 $g_0$ 和 $f\bmod x^{2n}$ 那么在迭代前我们有 $g_1=g\bmod x^{n/2}$。

- 由 $g_1$ 计算 $g_0$ 使用上述倒数的方法 2 需要 $5\mathsf{E}(n)$。
- 计算 $F _ {2n}^{-1}(F _ {2n}(f_0)F _ {2n}(q))$ 需要 $6\mathsf{E}(n)$。
- 计算 $F _ {2n}^{-1}(F _ {2n}(g_0)F _ {2n}((\mathfrak{D}(f_0)-f_0q)\bmod x^{2n-1}))$ 需要 $6\mathsf{E}(n)$。
- 计算 $F _ {2n}^{-1}(F _ {2n}(f_0)F _ {2n}((h-\smallint w)\bmod x^{2n}))$ 需要额外 $4\mathsf{E}(n)$。

共 $21\mathsf{E}(n)$，所以计算 $\exp(h)\bmod{x^n}$ 需要 $21\mathsf{E}(n)$。

#### 方法 3

仍然考虑方法 2 中的式子，我们令

$$
\begin{aligned}
r&=(f_0q)\bmod{(x^n-1)}\\
s&=(x(\mathfrak{D}(f_0)-r))\bmod{(x^n-1)}\\
t&=(g_0s)\bmod{x^n}\\
u&=(h\bmod{x^{2n}}-\smallint tx^{n-1})\operatorname{div}x^n\\
v&=(f_0u)\bmod{x^n}\\
\end{aligned}
$$

其中二元运算符 $a\operatorname{div}b$ 表示 $(a-a\bmod{b})/b$ 那么 $f\equiv f_0+x^nv\pmod{x^{2n}}$。

我们认为该方法与方法 2 的输出相同，首先观察方法 2 中的第二步并不需要求出 $f_0q$，因为 $\deg(f_0q)\lt 2n$ 而 $\mathfrak{D}(f_0)\equiv f_0q\pmod{x^{n-1}}$ 使用 $n$ 长的循环卷积足以还原出 $\mathfrak{D}(f_0)-f_0q$。

- 计算 $F_n^{-1}(F_n(f_0)F_n(q))$ 需要 $3\mathsf{E}(n)$。
- 计算 $F _ {2n}^{-1}(F _ {2n}(g_0)F _ {2n}(s))$ 需要 $6\mathsf{E}(n)$。
- 计算 $F _ {2n}^{-1}(F _ {2n}(f_0)F _ {2n}(u))$ 需要额外 $5\mathsf{E}(n)$。
- 由 $f\bmod{x^{2n}}$ 计算 $g\bmod{x^{2n}}$ 需要 $10\mathsf{E}(n)$ 但考虑算出 $F _ {4n}(f\bmod{x^{2n}})$ 给下一次迭代使用，且已有 $F _ {2n}(g_0)$ 故仍需 $10\mathsf{E}(n)$ 但上面的 $F_n(f_0)$ 和 $F _ {2n}(f_0)$ 不用再求，可减少 $2\mathsf{E}(n)$。

共 $22\mathsf{E}(n)$，所以计算 $\exp(h)\bmod{x^n}$ 需要 $22\mathsf{E}(n)$ 而最后一次迭代中可以省去 $5\mathsf{E}(n)$ 故需要 $17\mathsf{E}(n)$，在 negiizhao 的博客中提供了更优秀的 $16\mathsf{E}(n)$ 到 $15.5\mathsf{E}(n)$，但上面这种实现是非常简单的。

在实际实现时，直接考虑

$$
f\equiv f_0+f_0(h-\smallint(\mathfrak{D}(h)+g_0(\mathfrak{D}(f_0)-f_0\mathfrak{D}(h))))\pmod{x^{2n}}
$$

还原出 $\mathfrak{D}(f_0)-f_0q$ 会比较清晰一些。

### 平方根

给出 $h$ 且 $h(0)=1$，令 $f=\sqrt{h},g=1/f,g_0=g\bmod{x^n}$ 和已知 $f_0=f\bmod{x^n}$ 求 $f\bmod{x^{2n}}$。

令 $A(f)=f^2-h$ 那么

$$
\begin{aligned}
f&\equiv f_0-\frac{f_0^2-h}{2f_0}\pmod{x^{2n}}\\
&\equiv f_0-(f_0^2-h)g_0/2\pmod{x^{2n}}
\end{aligned}
$$

在这里仅描述一个简单的做法，观察到 $f_0^2\equiv h\pmod{x^n}$ 那么

- 计算 $F_n^{-1}(F_n(f_0)F_n(f_0))$ 后因为 $\deg (f_0^2)\lt 2n$ 所以可还原出 $(f_0^2-h)\bmod{x^{2n}}$ 需要 $2\mathsf{E}(n)$。
- 计算 $g_0$ 需要 $10\mathsf{E}(n)$ 这里不需要计算 $(1/f_0)\bmod{x^{2n}}$ 因为 $f_0^2-h=x^ns$ 其低位为零。但是在结束时我们得到 $g_0$ 意味着下一轮可以维护。
- 计算 $F _ {2n}^{-1}(F _ {2n}((f_0^2-h)\bmod{x^{2n}})F _ {2n}(g_0))$ 需要 $6\mathsf{E}(n)$。

和在指数时的方法相同，我们在迭代的最后维护下一轮要用到的 $g_0$，因此需要计算 $F _ {2n}(f\bmod{x^{2n}})$ 可给下一轮迭代使用，而前面计算过 $F _ {2n}(g_0)$ 故需要额外 $8\mathsf{E}(n)$ 共 $15\mathsf{E}(n)$ 最后一次迭代中省去 $4\mathsf{E}(n)$，所以计算 $\sqrt{h}\bmod{x^n}$ 需要 $11\mathsf{E}(n)$，更优秀的方法见参考文献。

## 半在线算法

见 [半在线算法](https://hly1204.github.io/library/math/formal_power_series/semi_relaxed_convolution.hpp)。

## 参考文献

- negiizhao 的[博客](https://negiizhao.blog.uoj.ac/blog/4671)
- D. J. Bernstein. [Removing redundancy in high-precision Newton iteration](http://cr.yp.to/fastnewton.html), 2004.
- Alin Bostan and Eric Schost. [A simple and fast algorithm for computing exponentials of power series](https://arxiv.org/abs/1301.5804), 2013.
- Guillaume Hanrot and Paul Zimmermann. [Newton iteration revisited](http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.415.9164).