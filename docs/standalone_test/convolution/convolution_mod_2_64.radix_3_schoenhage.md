---
title: Radix-3 Schönhage's Algorithm (a.k.a. Radix-3 Schönhage–Strassen Algorithm)
documentation_of: ../../../standalone_test/convolution/convolution_mod_2_64.radix_3_schoenhage.test.cpp
---

This algorithm was published by Schönhage alone, but somehow it was named after Schönhage and Strassen. The Schönhage–Strassen algorithm is for integers.

The idea here is learned from Bernstein's paper, the pseudocode here is modified from AECF (it gives the Radix-2 version).

I want to write this blog because there is almost no resource/code examples for describing the detailed steps for this algorithm. It is easy for mathematicians, but it is not such easy for programmers who want to really implement it.

## Radix-3 Schönhage's trick

Given polynomials $a, b \in R\lbrack x\rbrack _ {\lt n}$, where $1/3 \in R$, Schönhage's trick will give us an algorithm works in time $O(n \log(n) \log(\log(n)))$ (arithmetic model) to compute $ab \bmod{(x^{2n} + x^n + 1)}$ where $n$ is a power of $3$. I will omit the details here for the proof of the time complexity which could be found in Mateer's paper.

$$
\begin{array}{ll}
   & \textbf{Algorithm}\operatorname{\mathsf{Schoenhage}}(a, b, n) \\
   & \textbf{Input}\text{: } a, b \in R\lbrack x\rbrack _ {\lt 2n}, n = 3^k, k \in \mathbb{N} \\
   & \textbf{Output}\text{: } ab \bmod{(x^{2n} + x^n + 1)} \\
1  & \textbf{if } n \leq 3 \textbf{ then} \\
2  & \qquad \text{Compute } ab \text{ use Karatsuba's algorithm.} \\
3  & \qquad \textbf{return } ab \bmod{(x^{2n} + x^n + 1)} \\
4  & \textbf{endif} \\
5  & d \gets 3^{\lceil k / 2 \rceil}, \delta \gets n / d \\
6  & \hat{a}(x, y) \gets a \bmod{(x^{d} - y)}, \hat{b}(x, y) \gets b \bmod{(x^{d} - y)} \\
7  & \text{Let } \hat{a}, \hat{b} \in (R\lbrack x\rbrack / (x^{2d} + x^d + 1)) \lbrack y\rbrack / (y^{2\delta} + y^{\delta} + 1) \text{ by doing some zero paddings.} \\
8  & (\hat{a_0}, \hat{a_1}) \gets \left(\hat{a} \bmod{(y^{\delta} - x^d)}, \hat{a} \bmod{(y^{\delta} - x^{2d})}\right), (\hat{b_0}, \hat{b_1}) \gets \left(\hat{b} \bmod{(y^{\delta} - x^d)}, \hat{b} \bmod{(y^{\delta} - x^{2d})}\right) \\
9  & \text{Apply Radix-3 FFT to } \hat{a_0}, \hat{a_1}, \hat{b_0}, \hat{b_1} \\
10 & \textbf{for } i \gets 0 \textbf{ to } \delta - 1 \textbf{ do} \\
11 & \qquad \hat{c_0} \bmod{(y - x^{e_1(i)})} \gets \operatorname{\mathsf{Schoenhage}}\left(\hat{a_0} \bmod{(y - x^{e_1(i)})}, \hat{b_0} \bmod{(y - x^{e_1(i)})}, d\right) \\
12 & \qquad \hat{c_1} \bmod{(y - x^{e_2(i)})} \gets \operatorname{\mathsf{Schoenhage}}\left(\hat{a_1} \bmod{(y - x^{e_2(i)})}, \hat{b_1} \bmod{(y - x^{e_2(i)})}, d\right) \\
13 & \textbf{endfor} \\
14 & \text{Apply Radix-3 IFFT to restore } \hat{c_0}, \hat{c_1} \\
15 & \text{Use FFT trick to restore } \hat{a}\hat{b} \text{ from } \hat{c_0}, \hat{c_1} \\
16 & \textbf{return } \left((\hat{a}\hat{b})\left(x, x^d\right)\right) \bmod{(x^{2n} + x^n + 1)}
\end{array}
$$

We will firstly show the algorithm for **Ln 8** in the pseudocode, thus **Ln 15** is also solved. Note that we could compute $A(x) x^N$ for any integer $N$ in $O(\min{(N, d)})$ inplace (Because memory movement is free in arithmetic model! e.g. Transposition of a matrix is free.) where $A \in R\lbrack x\rbrack / (x^{2d} + x^d + 1)$. It is also invertible, since $x^{3d} \equiv 1 \pmod{(x^{2d} + x^d + 1)}$.

For $D(x) = L + Hx^d \in R\lbrack x\rbrack / (x^{2d} + x^d + 1)$ and $\deg L \lt d, \deg H \lt d$, we have

$$
\begin{aligned}
(L + Hx^d)x^d &= Lx^d + Hx^{2d} &= -H + (L - H)x^d \\
(L + Hx^d)x^{2d} &= Lx^{2d} + H &= -L + H - Lx^d
\end{aligned}
$$

So we could give the pseudocode for **Ln 8**.

$$
\begin{array}{ll}
  & \textbf{Algorithm}\operatorname{\mathsf{Ln8}}(a, d, \delta) \\
  & \textbf{Input}\text{: } a \in (R\lbrack x\rbrack / (x^{2d} + x^d + 1))\lbrack y\rbrack / (y^{2\delta} + y^{\delta} + 1) \\
  & \textbf{Output}\text{: } (a \bmod{(y^{\delta} - x^d)}, a \bmod{(y^{\delta} - x^{2d})}) \\
1 & (a_0, a_1) \gets (a \bmod{y^{\delta}}, (a - a_0) / y^{\delta}) \\
2 & (b_0, b_1) \gets (0, 0) \\
3 & \textbf{for } i \gets 0 \textbf{ to } \delta - 1 \textbf{ do} \\
4 & \qquad (L_{a_0}, H_{a_0}) \gets ((\lbrack y^i \rbrack a_0) \bmod{x^d}, ((\lbrack y^i \rbrack a_0) - (\lbrack y^i \rbrack a_0) \bmod{x^d}) / x^d) \\
5 & \qquad (L_{a_1}, H_{a_1}) \gets ((\lbrack y^i \rbrack a_1) \bmod{x^d}, ((\lbrack y^i \rbrack a_1) - (\lbrack y^i \rbrack a_1) \bmod{x^d}) / x^d) \\
6 & \qquad
           \begin{bmatrix}L_0 \\ H_0 \\ L_1 \\ H_1\end{bmatrix} \gets
           \begin{bmatrix}
           1 & 0 & 0 & -1 \\
           0 & 1 & 1 & -1 \\
           1 & 0 & -1 & 1 \\
           0 & 1 & -1 & 0
           \end{bmatrix}
           \begin{bmatrix}L_{a_0} \\ H_{a_0} \\ L_{a_1} \\ H_{a_1}\end{bmatrix} \\
7 & \qquad (b_0, b_1) \gets (b_0 + (L_0 + H_0x^d)y^i, b_1 + (L_1 + H_1x^d)y^i) \\
8 & \textbf{endfor} \\
9 & \textbf{return } (b_0, b_1)
\end{array}
$$

Note that

$$
\begin{bmatrix}
1 & 0 & 0 & -1 \\
0 & 1 & 1 & -1 \\
1 & 0 & -1 & 1 \\
0 & 1 & -1 & 0
\end{bmatrix}^{-1} =
\frac{1}{3}
\begin{bmatrix}
1 & 1 & 2 & -1 \\
-1 & 2 & 1 & 1 \\
-1 & 2 & 1 & -2 \\
-2 & 1 & 2 & -1
\end{bmatrix}
$$

so **Ln 15** is solved automatically. Now the only reamining problem is the Radix-3 FFT trick.

## Radix-3 FFT trick

Bernstein showed that the Radix-3 FFT trick is

$$
\begin{aligned}
S\lbrack y \rbrack / (y^{3N} - t^3) &\to S\lbrack y \rbrack / (y^N - t) \\
&\times S\lbrack y \rbrack / (y^N - \omega t) \\
&\times S\lbrack y \rbrack / (y^N - \omega^2 t)
\end{aligned}
$$

where $\omega^2 + \omega + 1 = 0$, and the algorithm is invertible if $1 / (3t^2)$ is invertible. In our case, $S = R\lbrack x\rbrack / (x^{2d} + x^d + 1)$, so $\omega = x^{d}$. $t$ is some power of $x$ and $1 / 3 \in R$, so it is invertible.

$$
\begin{array}{ll}
  & \textbf{Algorithm}\operatorname{\mathsf{FFT}}(a, d, \delta, E) \\
  & \textbf{Input}\text{: } a \in (R\lbrack x\rbrack / (x^{2d} + x^d + 1))\lbrack y\rbrack / (y^{\delta} - x^E), \delta \leq d, \delta \mid E \\
  & \textbf{Output}\text{: } \begin{bmatrix}a \bmod{(y - x^{e_E(0)})} & \cdots & a \bmod{(y - x^{e_E(\delta - 1)})}\end{bmatrix} \\
1 & \textbf{if } \delta = 1 \textbf{ then} \\
2 & \qquad \textbf{return } \begin{bmatrix}a\end{bmatrix} \\
3 & \textbf{endif} \\
4 & a_0 \gets a \bmod{(y^{\delta / 3} - x^{E / 3})} \\
5 & a_1 \gets a \bmod{(y^{\delta / 3} - x^{E / 3 + d})} \\
6 & a_2 \gets a \bmod{(y^{\delta / 3} - x^{E / 3 + 2d})} \\
7 & \textbf{return } \begin{bmatrix}\operatorname{\mathsf{FFT}}(a_0, d, \delta / 3, E / 3) & \operatorname{\mathsf{FFT}}(a_1, d, \delta / 3, E / 3 + d) & \operatorname{\mathsf{FFT}}(a_2, d, \delta / 3, E / 3 + 2d)\end{bmatrix}
\end{array}
$$

If we set $a := (A_0(x) + A_1(x)x^d) + (B_0(x) + B_1(x)x^d)y^{\delta / 3} + (C_0(x) + C_1(x)x^d)y^{2\delta / 3}$, then

$$
\begin{aligned}
a \bmod{(y^{\delta / 3} - x^{E / 3})} &= (A_0(x) + A_1(x)x^d) &+ (B_0(x) + B_1(x)x^d)x^{E / 3}      &+ (C_0(x) + C_1(x)x^d)x^{2E / 3} \\
a \bmod{(y^{\delta / 3} - x^{E / 3 + d})} &= (A_0(x) + A_1(x)x^d) &+ (B_0(x) + B_1(x)x^d)x^{E / 3 + d}  &+ (C_0(x) + C_1(x)x^d)x^{2E / 3 + 2d} \\
a \bmod{(y^{\delta / 3} - x^{E / 3 + 2d})} &= (A_0(x) + A_1(x)x^d) &+ (B_0(x) + B_1(x)x^d)x^{E / 3 + 2d} &+ (C_0(x) + C_1(x)x^d)x^{2E / 3 + 4d}
\end{aligned}
$$

we could compute

$$
\begin{aligned}
(A_0(x) + A_1(x)x^d) &\gets (A_0(x) + A_1(x)x^d) \\
(B_0(x) + B_1(x)x^d) &\gets (B_0(x) + B_1(x)x^d)x^{E / 3} \\
(C_0(x) + C_1(x)x^d) &\gets (C_0(x) + C_1(x)x^d)x^{2E / 3}
\end{aligned}
$$

first. This could be done inplace. Then we compute

$$
\begin{bmatrix}
A_0(x) \\
A_1(x) \\
B_0(x) \\
B_1(x) \\
C_0(x) \\
C_1(x)
\end{bmatrix} \gets
\begin{bmatrix}
1 & 0 & 1 & 0 & 1 & 0 \\
0 & 1 & 0 & 1 & 0 & 1 \\
1 & 0 & 0 & -1 & -1 & 1 \\
0 & 1 & 1 & -1 & -1 & 0 \\
1 & 0 & -1 & 1 & 0 & -1 \\
0 & 1 & -1 & 0 & 1 & -1
\end{bmatrix}
\begin{bmatrix}
A_0(x) \\
A_1(x) \\
B_0(x) \\
B_1(x) \\
C_0(x) \\
C_1(x)
\end{bmatrix}
$$

and note that

$$
\begin{bmatrix}
1 & 0 & 1 & 0 & 1 & 0 \\
0 & 1 & 0 & 1 & 0 & 1 \\
1 & 0 & 0 & -1 & -1 & 1 \\
0 & 1 & 1 & -1 & -1 & 0 \\
1 & 0 & -1 & 1 & 0 & -1 \\
0 & 1 & -1 & 0 & 1 & -1
\end{bmatrix}^{-1} =
\frac{1}{3}
\begin{bmatrix}
1 & 0 & 1 & 0 & 1 & 0 \\
0 & 1 & 0 & 1 & 0 & 1 \\
1 & 0 & -1 & 1 & 0 & -1 \\
0 & 1 & -1 & 0 & 1 & -1 \\
1 & 0 & 0 & -1 & -1 & 1 \\
0 & 1 & 1 & -1 & -1 & 0
\end{bmatrix}
$$

which gives us the implementation of IFFT. In my code, I used two different matrix when $E$ is different because I want to store the result in same order but without modify the $e(i)$ stuff. Use the following code snippet to check what we are computing during each step of FFT in my code if one is curious about.

```c++
// real code omitted
#include <cassert>
#include <cstdio>
#include <vector>

using ull = unsigned long long;
// clang-format off
int PowOf3(int e) { for (int x = 3, res = 1;; x *= x) { if (e & 1) res *= x; if ((e /= 2) == 0) return res; } }
int Log3Ceil(int a) { int e = 0; for (int c = 1; c < a; c *= 3) ++e; return e; }
int Log3Floor(int a) { const int e = Log3Ceil(a); return a == PowOf3(e) ? e : e - 1; }
// clang-format on

template<int E_MULTIPLIER> void FFT_(ull a[], int d, int delta) {
    static_assert(E_MULTIPLIER == 1 || E_MULTIPLIER == 2);
    assert(delta <= d);
    for (int i = delta; i >= 3; i /= 3) {
        const int block = delta / i;
        std::vector<int> e(block);
        for (int j = e[0] = 1; j < block; ++j)
            e[j] = e[j - PowOf3(Log3Floor(j))] + block / PowOf3(Log3Floor(j));
        for (int j = 0; j < block; ++j) {
            const int ee[] = {
                (e[j] + block * 3 * 0) * (d / (block * 3)) * E_MULTIPLIER % (d * 3),
                (e[j] + block * 3 * 1) * (d / (block * 3)) * E_MULTIPLIER % (d * 3),
                (e[j] + block * 3 * 2) * (d / (block * 3)) * E_MULTIPLIER % (d * 3),
            };
            std::printf("S[y] / (y^%3d - x^%3d) -> "
                        "  S[y] / (y^%3d - x^%3d) "
                        "× S[y] / (y^%3d - x^%3d) "
                        "× S[y] / (y^%3d - x^%3d)\n",
                        i, e[j] * (d / block) * E_MULTIPLIER % (d * 3), i / 3, ee[0], i / 3, ee[1],
                        i / 3, ee[2]);
        }
    }
}
void FFT(ull a[], int d, int delta) { FFT_<1>(a, d, delta), FFT_<2>(a + delta * 2 * d, d, delta); }

int main() {
    const int d     = 27;
    const int delta = 27;
    std::vector<ull> A(delta * 2 * d * 2);
    FFT(data(A), d, delta);
    return 0;
}
```

## References

1. Daniel J. Bernstein. "Multidigit multiplication for mathematicians." Accepted to Advances in Applied Mathematics, but withdrawn by author to prevent irreparable mangling by Academic Press. url: <https://cr.yp.to/papers.html#m3>
2. Alin Bostan, Frédéric Chyzak, Marc Giusti, Romain Lebreton, Grégoire Lecerf, Bruno Salvy et Éric Schost. Algorithmes Efficaces en Calcul Formel. 686 pages. Imprimé par CreateSpace. Aussi disponible en version électronique. Palaiseau : Frédéric Chyzak (auto-édit.), sept. 2017. isbn : 979-10-699-0947-2. url: <https://hal.science/AECF/>
3. Mateer, Todd, "Fast Fourier Transform Algorithms with Applications" (2008). All Dissertations. 231.
url: <https://open.clemson.edu/all_dissertations/231>
