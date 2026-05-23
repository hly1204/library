---
title: Rational Approximation
documentation_of: ../../../standalone_test/other/find_linear_recurrence.rational_approximation.test.cpp
---

Chinese version: <https://hly1204.blog.uoj.ac/blog/9207>.

## Rational (Function) Approximation

Given $A, B \in \mathbb{C} \left\lbrack x\right\rbrack$ with $\deg A \lt \deg B$ and $B \neq 0$, $k \in \mathbb{N}$, our goal is to find $P, Q \in \mathbb{C} \left\lbrack x\right\rbrack$ such that

$$
\deg \left(AQ - PB\right) \lt -k + \left(\deg B\right)\left(\deg Q\right)
$$

**and** $\deg Q$ is minimized. If we let $A, B$ be elements in $\mathbb{C}\left(\left(x^{-1}\right)\right)$[^ref1][^ref2], it is equivalent to

$$
\deg \left(\frac{A}{B} - \frac{P}{Q}\right) \lt -k
$$

where $\frac{A}{B} = \sum _ {j \geq \deg B - \deg A}c _ j x^{-j}$, so our goal is to find such $\frac{P}{Q}$ that

$$
\left\lbrack x^{\left\lbrack -k, 0\right)}\right\rbrack \frac{P}{Q} = \left\lbrack x^{\left\lbrack -k, 0\right)}\right\rbrack \frac{A}{B}
$$

### The Algorithm

I will first show you the recursive algorithm and explain it later.

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{RationalApprox}(A, B, k)\text{:} \\
&\textbf{Input}\text{: }A, B \in \mathbb{C} \left\lbrack x\right\rbrack, \deg A\lt \deg B, B \neq 0, k \in \mathbb{N}\text{.} \\
&\textbf{Output}\text{: }C, D \in \mathbb{C}\left\lbrack x\right\rbrack\text{ such that } \\
&\qquad \qquad \left\lbrack x^{\left\lbrack -k, 0\right)}\right\rbrack A/B = \left\lbrack x^{\left\lbrack -k, 0\right)}\right\rbrack C/D, \\
&\qquad \qquad\deg C\lt \deg D, \deg D \text{ is minimized.} \\
1&\textbf{if }\deg A - \deg B \lt -k\textbf{ then return }(0, 1) \\
2&(Q, R) \gets (\left\lfloor B/A \right\rfloor, B \bmod{A}) \\
3&\textbf{if }\deg R - \deg A \lt -k + 2\deg Q \textbf{ then return }(1, Q) \\
4&(E, F)\gets \operatorname{RationalApprox}(R, A, k - 2\deg Q) \\
5&\textbf{return }(F, QF + E)
\end{array}
$$

After Ln 2, we have

$$
\cfrac{A}{B} = \cfrac{1}{\cfrac{B}{A}} = \cfrac{1}{Q + \cfrac{R}{A}}
$$

If we have $\left\lbrack x^{\left\lbrack -k, -\deg Q \right\rbrack}\right\rbrack\frac{A}{B} = \left\lbrack x^{\left\lbrack -k, -\deg Q \right\rbrack}\right\rbrack\frac{1}{Q}$, then we can simply drop the term $\frac{R}{A}$. Let $C := Q$ and $D := \frac{R}{A}$, we have

$$
\begin{aligned}
& \frac{A}{B} = \frac{1}{C + D} \\
\iff & \frac{A}{B}\cdot C + \frac{A}{B}\cdot D = 1 \\
\iff & \frac{A}{B} + \frac{A}{B} \cdot \frac{D}{C} = \frac{1}{C} \\
\implies & \deg \left(\frac{A}{B} \cdot \frac{D}{C}\right) \lt -k \\
\implies & \left(\deg A - \deg B\right) + \left(\deg D - \deg C\right) \lt -k \\
\implies & -\deg Q + \left(\deg R - \deg A - \deg Q\right) \lt -k \\
\implies & \deg R - \deg A \lt -k + 2\deg Q
\end{aligned}
$$

which explains Ln 3. Otherwise, we cannot just drop the term $\frac{R}{A}$, instead, since we donot care about the coefficients of $x^{\lt -k + 2\deg Q}$ of $\frac{R}{A}$, it is enough to find an approximant $\frac{E}{F}$ such that $\deg \left(\frac{R}{A} - \frac{E}{F}\right) \lt -k + 2\deg Q$ **and** $\deg F$ is minimized.

It is simple to convert the recursive algorithm to an iterative algorithm, since we are actually computing the continued fraction.

Now we may wonder if the algorithm could be replaced by the famous Half-GCD algorithm, since we could take advantage of the Half-GCD algorithm. Accroding to Ber08[^ref3], it is possible to use Half-GCD algorithm as a subprocedure.

To explain why we could use $\operatorname{hgcd}(x^n, \sum _ {j = 0}^{n - 1} a _ {n - 1 - j} x^j)$ to compute the result of $\operatorname{RationalApprox}\left(\sum _ {j = 0}^{n - 1} a _ {n - 1 - j} x^j, x^n, n\right)$, we must know that what `hgcd` computed contains the result of `RationalApprox`. We could use Thull–Yap's `hgcd` algorithm[^ref4] for simplicity.

$$
\begin{array}{ll}
&\textbf{Algorithm Polynomial }\operatorname{hgcd}(A,B)\text{:}\\
&\textbf{Input}\text{: }A,B\in\mathbb{C}\lbrack x\rbrack \text{, }\deg(A)\gt \deg(B)\geq 0 \text{.}\\
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

where $\langle Q\rangle = \begin{bmatrix} 0 & 1 \\ 1 & -Q \end{bmatrix}$. And I think it will be cleaner if we slightly modify the `RationalApprox` algorithm.

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{RationalApprox}(A, B, k)\text{:} \\
&\textbf{Input}\text{: }A, B \in \mathbb{C} \left\lbrack x\right\rbrack, \deg A\lt \deg B, B \neq 0, k \in \mathbb{Z}\text{.} \\
&\textbf{Output}\text{: }C, D \in \mathbb{C}\left\lbrack x\right\rbrack\text{ such that } \\
&\qquad \qquad \left\lbrack x^{\left\lbrack -k, 0\right)}\right\rbrack A/B = \left\lbrack x^{\left\lbrack -k, 0\right)}\right\rbrack C/D, \\
&\qquad \qquad\deg C\lt \deg D, \deg D \text{ is minimized.} \\
1&\textbf{if }\deg A - \deg B \lt -k\textbf{ then return }(0, 1) \\
2&(Q, R) \gets (\left\lfloor B/A \right\rfloor, B \bmod{A}) \\
3&(E, F)\gets \operatorname{RationalApprox}(R, A, k - 2\deg Q) \\
4&\textbf{return }(F, QF + E)
\end{array}
$$

We will compare $\operatorname{RationalApprox}\left(\sum _ {j = 0}^{n - 1} a _ {n - 1 - j} x^j, x^n, n\right)$ with $\operatorname{hgcd}(x^n, \sum _ {j = 0}^{n - 1} a _ {n - 1 - j} x^j)$. Since we know the output of `hgcd` (check $\operatorname{adj} \mathbf{M}$) already contains the result of `RationalApprox` if they halt at the same time, we only care about when they halt.

An observation is that `RationalApprox` halts when

1. $A = 0$,
2. or $k \lt 0$,
3. or $k \geq 0$ but if we do one more Euclidean division than the correct algorithm, $k < 0$ must hold.

And for `hgcd` algorithm, we have $\deg\mathbf{M} \leq \left\lfloor \frac{\deg A}{2}\right\rfloor$. So if we have a similar variable $k$ in `hgcd`, we will have $k \geq 0$ holds when `hgcd` returns because $\deg\mathbf{M}$ is almost the sum of all $\deg Q$ stuff. Still, if we do one more Euclidean division, $k < 0$ must hold. So we call `hgcd` once, and check if it meets the condition and perform one more Euclidean division if needed. adamant has written a blog ([Recovering a linear recurrence with the extended Euclidean algorithm](https://codeforces.com/blog/entry/101628)) about 4 years ago which is great but it seems that they didnot notice that if we want to find the linear recurrence, `hgcd` is almost done. I used this trick about 2 years ago, but I didnot give an explanation that time (also I didnot see any others use the same trick before). I donot know why adamant's algorithm have a different condition to halt when compared with mine. If you are curious about, maybe you could figure it out.

### Relationship between Euclidean algorithm and Berlekamp–Massey algorithm

A lot of papers showed they are equivalent. For example, if we want to find the minimal polynomial of the sequence $\left(a _ j\right) _ {j = 0}^{n - 1}$, which is the denominator of $\operatorname{RationalApprox}\left(\sum _ {j = 0}^{n - 1} a _ {n - 1 - j} x^j, x^n, n\right)$.

TODO: Give a clean implementation of Berlekamp–Massey algorithm from Euclidean algorithm.

## References

[^ref1]: Victor Shoup. A computational introduction to number theory and algebra. Cambridge University Press 2006, ISBN 978-0-521-85154-1, pp. I-XVI, 1-517 url: <https://www.shoup.net/ntb/>
[^ref2]: Daniel J. Bernstein. "Understanding binary-Goppa decoding." IACR Communications in Cryptology 1 (2024), article 1.14. url: <https://cr.yp.to/papers.html#goppadecoding>
[^ref3]: Daniel J. Bernstein. "Fast multiplication and its applications." Pages 325–384 in Algorithmic number theory: lattices, number fields, curves and cryptography (edited by Joe Buhler, Peter Stevenhagen), Cambridge University Press, 2008, ISBN 978-0521808545. url: <https://cr.yp.to/papers.html#multapps>
[^ref4]: K. Thull and C. K. Yap. A Unified Approach to HGCD Algorithms for polynomials and integers. url: <https://cs.nyu.edu/~yap/papers/SYNOP.htm#hgcd> (not availble)
