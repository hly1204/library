---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: fft.hpp
    title: FFT
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: c_recursive.hpp
    title: C-recursive Sequence
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
    title: test/formal_power_series/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
    title: test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/kth_term_of_linearly_recurrent_sequence.1.test.cpp
    title: test/formal_power_series/kth_term_of_linearly_recurrent_sequence.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/shift_of_sampling_points_of_polynomial.0.test.cpp
    title: test/formal_power_series/shift_of_sampling_points_of_polynomial.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fft_doubling.hpp\"\n\n#line 2 \"fft.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iterator>\n#include <memory>\n#include <vector>\n\
    \ntemplate <typename Tp>\nclass FftInfo {\n    static Tp least_quadratic_nonresidue()\
    \ {\n        for (int i = 2;; ++i)\n            if (Tp(i).pow((Tp::mod() - 1)\
    \ / 2) == -1) return Tp(i);\n    }\n\n    const int ordlog2_;\n    const Tp zeta_;\n\
    \    const Tp invzeta_;\n    const Tp imag_;\n    const Tp invimag_;\n\n    mutable\
    \ std::vector<Tp> root_;\n    mutable std::vector<Tp> invroot_;\n\n    FftInfo()\n\
    \        : ordlog2_(__builtin_ctzll(Tp::mod() - 1)),\n          zeta_(least_quadratic_nonresidue().pow((Tp::mod()\
    \ - 1) >> ordlog2_)),\n          invzeta_(zeta_.inv()), imag_(zeta_.pow(1LL <<\
    \ (ordlog2_ - 2))), invimag_(-imag_),\n          root_{Tp(1), imag_}, invroot_{Tp(1),\
    \ invimag_} {}\n\npublic:\n    static const FftInfo &get() {\n        static FftInfo\
    \ info;\n        return info;\n    }\n\n    Tp imag() const { return imag_; }\n\
    \    Tp inv_imag() const { return invimag_; }\n    Tp zeta() const { return zeta_;\
    \ }\n    Tp inv_zeta() const { return invzeta_; }\n    const std::vector<Tp> &root(int\
    \ n) const {\n        // [0, n)\n        assert((n & (n - 1)) == 0);\n       \
    \ if (const int s = root_.size(); s < n) {\n            root_.resize(n);\n   \
    \         for (int i = __builtin_ctz(s); (1 << i) < n; ++i) {\n              \
    \  const int j = 1 << i;\n                root_[j]    = zeta_.pow(1LL << (ordlog2_\
    \ - i - 2));\n                for (int k = j + 1; k < j * 2; ++k) root_[k] = root_[k\
    \ - j] * root_[j];\n            }\n        }\n        return root_;\n    }\n \
    \   const std::vector<Tp> &inv_root(int n) const {\n        // [0, n)\n      \
    \  assert((n & (n - 1)) == 0);\n        if (const int s = invroot_.size(); s <\
    \ n) {\n            invroot_.resize(n);\n            for (int i = __builtin_ctz(s);\
    \ (1 << i) < n; ++i) {\n                const int j = 1 << i;\n              \
    \  invroot_[j] = invzeta_.pow(1LL << (ordlog2_ - i - 2));\n                for\
    \ (int k = j + 1; k < j * 2; ++k) invroot_[k] = invroot_[k - j] * invroot_[j];\n\
    \            }\n        }\n        return invroot_;\n    }\n};\n\ninline int fft_len(int\
    \ n) {\n    --n;\n    n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8;\n  \
    \  return (n | n >> 16) + 1;\n}\n\ntemplate <typename Iterator>\ninline void fft_n(Iterator\
    \ a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    assert((n & (n - 1)) == 0);\n    for (int j = 0; j < n / 2; ++j) {\n    \
    \    auto u = a[j], v = a[j + n / 2];\n        a[j] = u + v, a[j + n / 2] = u\
    \ - v;\n    }\n    auto &&root = FftInfo<Tp>::get().root(n / 2);\n    for (int\
    \ i = n / 2; i >= 2; i /= 2) {\n        for (int j = 0; j < i / 2; ++j) {\n  \
    \          auto u = a[j], v = a[j + i / 2];\n            a[j] = u + v, a[j + i\
    \ / 2] = u - v;\n        }\n        for (int j = i, m = 1; j < n; j += i, ++m)\n\
    \            for (int k = j; k < j + i / 2; ++k) {\n                auto u = a[k],\
    \ v = a[k + i / 2] * root[m];\n                a[k] = u + v, a[k + i / 2] = u\
    \ - v;\n            }\n    }\n}\n\ntemplate <typename Tp>\ninline void fft(std::vector<Tp>\
    \ &a) {\n    fft_n(a.begin(), a.size());\n}\n\ntemplate <typename Iterator>\n\
    inline void inv_fft_n(Iterator a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    assert((n & (n - 1)) == 0);\n    auto &&root = FftInfo<Tp>::get().inv_root(n\
    \ / 2);\n    for (int i = 2; i < n; i *= 2) {\n        for (int j = 0; j < i /\
    \ 2; ++j) {\n            auto u = a[j], v = a[j + i / 2];\n            a[j] =\
    \ u + v, a[j + i / 2] = u - v;\n        }\n        for (int j = i, m = 1; j <\
    \ n; j += i, ++m)\n            for (int k = j; k < j + i / 2; ++k) {\n       \
    \         auto u = a[k], v = a[k + i / 2];\n                a[k] = u + v, a[k\
    \ + i / 2] = (u - v) * root[m];\n            }\n    }\n    const Tp iv = Tp::mod()\
    \ - Tp::mod() / n;\n    for (int j = 0; j < n / 2; ++j) {\n        auto u = a[j]\
    \ * iv, v = a[j + n / 2] * iv;\n        a[j] = u + v, a[j + n / 2] = u - v;\n\
    \    }\n}\n\ntemplate <typename Tp>\ninline void inv_fft(std::vector<Tp> &a) {\n\
    \    inv_fft_n(a.begin(), a.size());\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ convolution_fft(std::vector<Tp> a, std::vector<Tp> b) {\n    if (a.empty() ||\
    \ b.empty()) return {};\n    const int n   = a.size();\n    const int m   = b.size();\n\
    \    const int len = fft_len(n + m - 1);\n    a.resize(len);\n    b.resize(len);\n\
    \    fft(a);\n    fft(b);\n    for (int i = 0; i < len; ++i) a[i] *= b[i];\n \
    \   inv_fft(a);\n    a.resize(n + m - 1);\n    return a;\n}\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> square_fft(std::vector<Tp> a) {\n    if (a.empty())\
    \ return {};\n    const int n   = a.size();\n    const int len = fft_len(n * 2\
    \ - 1);\n    a.resize(len);\n    fft(a);\n    for (int i = 0; i < len; ++i) a[i]\
    \ *= a[i];\n    inv_fft(a);\n    a.resize(n * 2 - 1);\n    return a;\n}\n\ntemplate\
    \ <typename Tp>\ninline std::vector<Tp> convolution_naive(const std::vector<Tp>\
    \ &a, const std::vector<Tp> &b) {\n    if (a.empty() || b.empty()) return {};\n\
    \    const int n = a.size();\n    const int m = b.size();\n    std::vector<Tp>\
    \ res(n + m - 1);\n    for (int i = 0; i < n; ++i)\n        for (int j = 0; j\
    \ < m; ++j) res[i + j] += a[i] * b[j];\n    return res;\n}\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> convolution(const std::vector<Tp> &a, const std::vector<Tp>\
    \ &b) {\n    if (std::min(a.size(), b.size()) < 60) return convolution_naive(a,\
    \ b);\n    if (std::addressof(a) == std::addressof(b)) return square_fft(a);\n\
    \    return convolution_fft(a, b);\n}\n#line 8 \"fft_doubling.hpp\"\n\ntemplate\
    \ <typename Iterator>\ninline void fft_doubling_n(Iterator a, int n) {\n    using\
    \ Tp = typename std::iterator_traits<Iterator>::value_type;\n    assert((n & (n\
    \ - 1)) == 0);\n    std::copy_n(a, n, a + n);\n    inv_fft_n(a + n, n);\n    Tp\
    \ k         = 1;\n    const auto t = FftInfo<Tp>::get().root(n).at(n / 2);\n \
    \   for (int i = 0; i < n; ++i) a[i + n] *= k, k *= t;\n    fft_n(a + n, n);\n\
    }\n\ntemplate <typename Tp>\ninline void fft_doubling(std::vector<Tp> &a) {\n\
    \    const int n = a.size();\n    a.resize(n * 2);\n    fft_doubling_n(a.begin(),\
    \ n);\n}\n"
  code: "#pragma once\n\n#include \"fft.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <iterator>\n#include <vector>\n\ntemplate <typename Iterator>\ninline\
    \ void fft_doubling_n(Iterator a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    assert((n & (n - 1)) == 0);\n    std::copy_n(a, n, a + n);\n    inv_fft_n(a\
    \ + n, n);\n    Tp k         = 1;\n    const auto t = FftInfo<Tp>::get().root(n).at(n\
    \ / 2);\n    for (int i = 0; i < n; ++i) a[i + n] *= k, k *= t;\n    fft_n(a +\
    \ n, n);\n}\n\ntemplate <typename Tp>\ninline void fft_doubling(std::vector<Tp>\
    \ &a) {\n    const int n = a.size();\n    a.resize(n * 2);\n    fft_doubling_n(a.begin(),\
    \ n);\n}\n"
  dependsOn:
  - fft.hpp
  isVerificationFile: false
  path: fft_doubling.hpp
  requiredBy:
  - c_recursive.hpp
  timestamp: '2024-11-30 21:12:38+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/formal_power_series/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
  - test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - test/formal_power_series/shift_of_sampling_points_of_polynomial.0.test.cpp
  - test/formal_power_series/kth_term_of_linearly_recurrent_sequence.1.test.cpp
documentation_of: fft_doubling.hpp
layout: document
title: FFT Doubling
---

## FFT Doubling

Given $\operatorname{\mathsf{FFT}} _ n(A(x))$ and $A(x)$, we want to compute $\operatorname{\mathsf{FFT}} _ {2n}(A(x))$. With the definition of FFT, we know that the left half of $\operatorname{\mathsf{FFT}} _ {2n}(A(x))$ equals $\operatorname{\mathsf{FFT}} _ n(A(x))$. And the right half is just $\operatorname{\mathsf{FFT}} _ n(A(\zeta _ {2n}x))$. If we don't know $A(x)$, we should ensure that $\deg A\lt n$ since we can only restore $A(x)\bmod{\left(x^{n}-1\right)}$.

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{FFTDoubling}}\text{:} \\
&\textbf{Input}\text{: }\left\lbrack A(1),A(-1),\dots,A\left(\zeta_n^{n-1}\right) \right\rbrack,n\text{ is a power of }2,\deg A\lt n\text{.} \\
&\textbf{Output}\text{: }\left\lbrack A(1),A(-1),\dots,A\left(\zeta_{2n}^{2n-1}\right)\right\rbrack\text{.} \\
1&A(x)\gets \operatorname{\mathsf{IFFT}}_n\left(\left\lbrack A(1),A(-1),\dots,A\left(\zeta_n^{n-1}\right) \right\rbrack\right) \\
2&\left\lbrack A\left(\zeta_{2n}\right),A\left(-\zeta_{2n}\right),\dots,A\left(\zeta_{2n}^{2n-1}\right)\right\rbrack \gets \operatorname{\mathsf{FFT}}_n\left(A\left(\zeta_{2n}x\right)\right) \\
3&\textbf{return } \left\lbrack A(1),A(-1),\dots,A\left(\zeta_{n}^{n-1}\right),A\left(\zeta_{2n}\right),A\left(-\zeta_{2n}\right),\dots,A\left(\zeta_{2n}^{2n-1}\right)\right\rbrack
\end{array}
$$

**Example**: If we are given $A(1),A(-1)$ and $\deg A\lt 2$, and we want to compute $A(\mathrm{i}),A(\mathrm{-i})$ since $\zeta _ 2=-1,\zeta _ 4=\mathrm{i}$ apparently.

## References

1. Alin Bostan, Ryuhei Mori. A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence. SOSA 2021: 118-132 url: <https://arxiv.org/abs/2008.08822>

2. Daniel J. Bernstein. "The tangent FFT." Pages 291–300 in Applied Algebra, Algebraic Algorithms and Error-Correcting Codes, 17th International Symposium, AAECC-17, Bangalore, India, December 16–20, 2007, Proceedings, edited by Serdar Boztas, Hsiao-feng Lu, Lecture Notes in Computer Science 4851, Springer, 2007, ISBN 978-3-540-77223-1. url: <https://cr.yp.to/papers.html#tangentfft>

3. noshi91. FFT の回数を削減するテクニック集. url: <https://noshi91.hatenablog.com/entry/2023/12/10/163348>
