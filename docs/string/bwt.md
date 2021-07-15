## Burrows-Wheeler 变换

对于字符串 $s=\texttt{banana0}$ 定义其后缀数组 SA 为

$$
\operatorname{SA}(s)=(6,5,3,1,0,4,2)
$$

也就是

$$
\texttt{0}\\
\texttt{a0}\\
\texttt{ana0}\\
\texttt{anana0}\\
\texttt{banana0}\\
\texttt{na0}\\
\texttt{nana0}\\
$$

而 BWT 则是对循环串进行排序，有

$$
\texttt{0banana}\\
\texttt{a0banan}\\
\texttt{ana0ban}\\
\texttt{anana0b}\\
\texttt{banana0}\\
\texttt{na0bana}\\
\texttt{nana0ba}\\
$$

我们取其末尾的字符为 $\operatorname{BWT}(s)=\texttt{annb0aa}$ 。

注意这里需要这个末尾的字符 $\texttt{0}$ 作为“哨兵”表示文本串的结尾，其必须在文本串中没有出现过且为字典序最小的字符，如此一来我们可以通过后缀数组来进行构建，有

$$
\operatorname{BWT} _ i(s)=
\begin{cases}
s _ {\operatorname{SA}_i(s)-1}&\text{if }\operatorname{SA}_i(s)\gt 0\\
\texttt{0}&\text{otherwise}
\end{cases}
$$

不难发现这是正确的。如果没有“哨兵”字符，我们需要将串拷贝一份拼接在后面再求其后缀数组，例如 [P4051 [JSOI2007]字符加密](https://www.luogu.com.cn/problem/P4051) 如果我们使用倍增法求 SA ，不难在过程中改为其循环串的 SA 。但这也不符合 BWT 的定义了。

BWT 在计算过程中没有丢失信息，这也意味着 BWT 是可逆的。

## Last-First 映射

我们还是注意该串

$$
\texttt{\textcolor{red}{0}banan\textcolor{red}{a}}\\
\texttt{\textcolor{red}{a}0bana\textcolor{red}{n}}\\
\texttt{\textcolor{red}{a}na0ba\textcolor{red}{n}}\\
\texttt{\textcolor{red}{a}nana0\textcolor{red}{b}}\\
\texttt{\textcolor{red}{b}anana\textcolor{red}{0}}\\
\texttt{\textcolor{red}{n}a0ban\textcolor{red}{a}}\\
\texttt{\textcolor{red}{n}ana0b\textcolor{red}{a}}\\
$$

我们注意 First 即第一列是其 SA 中按照排名的后缀的首个字符且 Last 即 BWT 中的第 $i$ 个 $\texttt{a}$ 也对应 SA 中的第 $i$ 个 $\texttt{a}$ ，以此类推。

## FM-index

TODO

## 参考文献

- M. Burrows and D. J. Wheeler. [A block-sorting lossless data compression algorithm](https://www.cl.cam.ac.uk/teaching/2003/DSAlgs/SRC-124.pdf). Technical Report 124, Digital Equipment Corporation, Palo Alto, California, 1994.