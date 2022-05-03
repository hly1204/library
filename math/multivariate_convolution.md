---
title: Multivariate Convolution (in $\mathbb{F} _ p \lbrack z_1, \dots, z_d \rbrack \left/ \left( z_1^{l_1}, \dots, z_d^{l_d} \right)\right.$ for FFT prime $p$)
documentation_of: ./multivariate_convolution.hpp
---

## Basic Notation

Multivariate polynomials in $\mathbb{F} _ p \lbrack z_1, \dots, z_d \rbrack$ are something like

$$
A(z_1, \dots, z_d) := \sum _ {}a _ {i_1, \dots, i_d} z_1^{i_1} \cdots z_d^{i_d}.
$$

## Lexicographical Encoding

Hoeven showed that we could use lexicographical encoding to transform the multivariate polynomials to univariate polynomials like

$$
A(z) := \sum a _ {i_1, \dots, i_d} z^{\operatorname{lex} _ {n_1, \dots, n_d}(i_1, \dots, i_d)}
$$

where

$$
n_i := \deg _ {z_i} A(z_1, \dots, z_d)
$$

and

$$
\operatorname{lex} _ {n_1, \dots, n_d}(i_1, \dots, i_d) := i_1 + i_2n_1 + \cdots + i_dn_1 \cdots n _ {d - 1}.
$$

It's some kind of mixed radix representation of an integer.

## Multiplication in $\mathbb{F} _ p \lbrack z_1, \dots, z_d \rbrack \left/ \left( z_1^{l_1}, \dots, z_d^{l_d} \right)\right.$

Our goal is to compute multiplication in $\mathbb{F} _ p \lbrack z_1, \dots, z_d \rbrack \left/ \left( z_1^{l_1}, \dots, z_d^{l_d} \right)\right.$. When we multiply $A(z)$ above by $B(z) = \sum b _ {i_1, \dots ,i_d} z^{\operatorname{lex} _ {n_1, \dots, n_d}(i_1, \dots, i_d)}$, we should drop the terms that carries appear when adding the exponents of $z$ (in the mixed radix representation).

Elegia showed that if there exists a function $\chi : \mathbb{N} \to \mathbb{N}$ that

$$
\chi (i) + \chi (j) = \chi (i + j)
$$

if and only if there is no carry when adding $i$ and $j$, thus we could compute multiplication of bivariate polynomials like $A = \sum_i a_i z^i t^{\chi (i)}$ and $B = \sum_i b_i z^i t^{\chi (i)}$, extract the coefficients of $\sum c _ {i + j} z^{i + j} t^{\chi (i) + \chi (j)} = AB$ where $\chi (i) + \chi (j) = \chi (i + j)$, which will give us the right answer.

If $\max_i\lbrace \chi (i) \rbrace$ is small, we could form a univariate polynomial for each $t^{\chi (i)}$. For example, we only assign non-zero coefficients $a_i$ to $z^i t^{\chi (i)}$. But we can't afford doing so much multiplications. Elegia gave the defination of $\chi$

$$
\chi (i) := \left\lfloor \frac{i}{n_1} \right\rfloor + \cdots + \left\lfloor \frac{i}{n_1 n_2 \cdots n _ {d - 1}} \right\rfloor
$$

and

$$
\chi (i + j) - \chi (i) - \chi (j) \in \lbrace 0, 1, \dots, d - 1 \rbrace
$$

for all $i, j$ as lexicographical encoding. Which means we could assign $a_i$ to $z^i t^{\chi (i) \bmod d}$. Time complexity is $O\left( dn \log n \right)$ where $n := \prod_i n_i$.

## Reference

1. J. van der Hoeven. [Notes on the Truncated Fourier Transform](https://www.texmacs.org/joris/tft/tft.pdf).
2. Elegia. [Hello, multivariate multiplication](https://blog.csdn.net/EI_Captain/article/details/112400493).
3. 37zigen. [多変数畳み込み（切り捨て）のアルゴリズム](https://37zigen.com/truncated-multivariate-convolution/).