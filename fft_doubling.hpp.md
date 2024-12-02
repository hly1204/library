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
    \  return (n | n >> 16) + 1;\n}\n\nnamespace detail {\n\ntemplate <typename Iterator>\n\
    inline void\nbutterfly_n(Iterator a, int n,\n            const std::vector<typename\
    \ std::iterator_traits<Iterator>::value_type> &root) {\n    assert(n > 0);\n \
    \   assert((n & (n - 1)) == 0);\n    const int bn = __builtin_ctz(n);\n    if\
    \ (bn & 1) {\n        for (int i = 0; i < n / 2; ++i) {\n            const auto\
    \ a0 = a[i], a1 = a[i + n / 2];\n            a[i] = a0 + a1, a[i + n / 2] = a0\
    \ - a1;\n        }\n    }\n    for (int i = n >> (bn & 1); i >= 4; i /= 4) {\n\
    \        const int i4 = i / 4;\n        for (int k = 0; k < i4; ++k) {\n     \
    \       const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];\n            const\
    \ auto a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];\n            const auto a02p =\
    \ a0 + a2, a02m = a0 - a2;\n            const auto a13p = a1 + a3, a13m = (a1\
    \ - a3) * root[1];\n            a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p\
    \ - a13p;\n            a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;\n\
    \        }\n        for (int j = i, m = 2; j < n; j += i, m += 2) {\n        \
    \    const auto r = root[m], r2 = r * r, r3 = r2 * r;\n            for (int k\
    \ = j; k < j + i4; ++k) {\n                const auto a0 = a[k + i4 * 0], a1 =\
    \ a[k + i4 * 1] * r;\n                const auto a2 = a[k + i4 * 2] * r2, a3 =\
    \ a[k + i4 * 3] * r3;\n                const auto a02p = a0 + a2, a02m = a0 -\
    \ a2;\n                const auto a13p = a1 + a3, a13m = (a1 - a3) * root[1];\n\
    \                a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p - a13p;\n \
    \               a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;\n  \
    \          }\n        }\n    }\n}\n\ntemplate <typename Iterator>\ninline void\n\
    inv_butterfly_n(Iterator a, int n,\n                const std::vector<typename\
    \ std::iterator_traits<Iterator>::value_type> &root) {\n    assert(n > 0);\n \
    \   assert((n & (n - 1)) == 0);\n    const int bn = __builtin_ctz(n);\n    for\
    \ (int i = 4; i <= (n >> (bn & 1)); i *= 4) {\n        const int i4 = i / 4;\n\
    \        for (int k = 0; k < i4; ++k) {\n            const auto a0 = a[k + i4\
    \ * 0], a1 = a[k + i4 * 1];\n            const auto a2 = a[k + i4 * 2], a3 = a[k\
    \ + i4 * 3];\n            const auto a01p = a0 + a1, a01m = a0 - a1;\n       \
    \     const auto a23p = a2 + a3, a23m = (a2 - a3) * root[1];\n            a[k\
    \ + i4 * 0] = a01p + a23p, a[k + i4 * 1] = a01m + a23m;\n            a[k + i4\
    \ * 2] = a01p - a23p, a[k + i4 * 3] = a01m - a23m;\n        }\n        for (int\
    \ j = i, m = 2; j < n; j += i, m += 2) {\n            const auto r = root[m],\
    \ r2 = r * r, r3 = r2 * r;\n            for (int k = j; k < j + i4; ++k) {\n \
    \               const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];\n         \
    \       const auto a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];\n                const\
    \ auto a01p = a0 + a1, a01m = a0 - a1;\n                const auto a23p = a2 +\
    \ a3, a23m = (a2 - a3) * root[1];\n                a[k + i4 * 0] = a01p + a23p,\
    \ a[k + i4 * 1] = (a01m + a23m) * r;\n                a[k + i4 * 2] = (a01p -\
    \ a23p) * r2, a[k + i4 * 3] = (a01m - a23m) * r3;\n            }\n        }\n\
    \    }\n    if (bn & 1) {\n        for (int i = 0; i < n / 2; ++i) {\n       \
    \     const auto a0 = a[i], a1 = a[i + n / 2];\n            a[i] = a0 + a1, a[i\
    \ + n / 2] = a0 - a1;\n        }\n    }\n}\n\n} // namespace detail\n\n// FFT_n:\
    \ A(x) |-> bit-reversed order of [A(1), A(zeta_n), ..., A(zeta_n^(n-1))]\ntemplate\
    \ <typename Iterator>\ninline void fft_n(Iterator a, int n) {\n    using Tp =\
    \ typename std::iterator_traits<Iterator>::value_type;\n    detail::butterfly_n(a,\
    \ n, FftInfo<Tp>::get().root(n / 2));\n}\n\ntemplate <typename Tp>\ninline void\
    \ fft(std::vector<Tp> &a) {\n    fft_n(a.begin(), a.size());\n}\n\n// IFFT_n:\
    \ bit-reversed order of [A(1), A(zeta_n), ..., A(zeta_n^(n-1))] |-> A(x)\ntemplate\
    \ <typename Iterator>\ninline void inv_fft_n(Iterator a, int n) {\n    using Tp\
    \ = typename std::iterator_traits<Iterator>::value_type;\n    detail::inv_butterfly_n(a,\
    \ n, FftInfo<Tp>::get().inv_root(n / 2));\n    const Tp iv = Tp::mod() - (Tp::mod()\
    \ - 1) / n;\n    for (int i = 0; i < n; ++i) a[i] *= iv;\n}\n\ntemplate <typename\
    \ Tp>\ninline void inv_fft(std::vector<Tp> &a) {\n    inv_fft_n(a.begin(), a.size());\n\
    }\n\n// IFFT_n^T: A(x) |-> 1/n FFT_n((x^n A(x)) mod (x^n - 1))\ntemplate <typename\
    \ Iterator>\ninline void transposed_inv_fft_n(Iterator a, int n) {\n    using\
    \ Tp    = typename std::iterator_traits<Iterator>::value_type;\n    const Tp iv\
    \ = Tp::mod() - (Tp::mod() - 1) / n;\n    for (int i = 0; i < n; ++i) a[i] *=\
    \ iv;\n    detail::butterfly_n(a, n, FftInfo<Tp>::get().inv_root(n / 2));\n}\n\
    \ntemplate <typename Tp>\ninline void transposed_inv_fft(std::vector<Tp> &a) {\n\
    \    transposed_inv_fft_n(a.begin(), a.size());\n}\n\n// FFT_n^T : FFT_n((x^n\
    \ A(x)) mod (x^n - 1)) |-> n A(x)\ntemplate <typename Iterator>\ninline void transposed_fft_n(Iterator\
    \ a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    detail::inv_butterfly_n(a, n, FftInfo<Tp>::get().root(n / 2));\n}\n\ntemplate\
    \ <typename Tp>\ninline void transposed_fft(std::vector<Tp> &a) {\n    transposed_fft_n(a.begin(),\
    \ a.size());\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> convolution_fft(std::vector<Tp>\
    \ a, std::vector<Tp> b) {\n    if (a.empty() || b.empty()) return {};\n    const\
    \ int n   = a.size();\n    const int m   = b.size();\n    const int len = fft_len(n\
    \ + m - 1);\n    a.resize(len);\n    b.resize(len);\n    fft(a);\n    fft(b);\n\
    \    for (int i = 0; i < len; ++i) a[i] *= b[i];\n    inv_fft(a);\n    a.resize(n\
    \ + m - 1);\n    return a;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ square_fft(std::vector<Tp> a) {\n    if (a.empty()) return {};\n    const int\
    \ n   = a.size();\n    const int len = fft_len(n * 2 - 1);\n    a.resize(len);\n\
    \    fft(a);\n    for (int i = 0; i < len; ++i) a[i] *= a[i];\n    inv_fft(a);\n\
    \    a.resize(n * 2 - 1);\n    return a;\n}\n\ntemplate <typename Tp>\ninline\
    \ std::vector<Tp> convolution_naive(const std::vector<Tp> &a, const std::vector<Tp>\
    \ &b) {\n    if (a.empty() || b.empty()) return {};\n    const int n = a.size();\n\
    \    const int m = b.size();\n    std::vector<Tp> res(n + m - 1);\n    for (int\
    \ i = 0; i < n; ++i)\n        for (int j = 0; j < m; ++j) res[i + j] += a[i] *\
    \ b[j];\n    return res;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ convolution(const std::vector<Tp> &a, const std::vector<Tp> &b) {\n    if (std::min(a.size(),\
    \ b.size()) < 60) return convolution_naive(a, b);\n    if (std::addressof(a) ==\
    \ std::addressof(b)) return square_fft(a);\n    return convolution_fft(a, b);\n\
    }\n#line 8 \"fft_doubling.hpp\"\n\ntemplate <typename Iterator>\ninline void fft_doubling_n(Iterator\
    \ a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    assert((n & (n - 1)) == 0);\n    std::copy_n(a, n, a + n);\n    inv_fft_n(a\
    \ + n, n);\n    Tp k         = 1;\n    const auto t = FftInfo<Tp>::get().root(n).at(n\
    \ / 2);\n    for (int i = 0; i < n; ++i) a[i + n] *= k, k *= t;\n    fft_n(a +\
    \ n, n);\n}\n\ntemplate <typename Tp>\ninline void fft_doubling(std::vector<Tp>\
    \ &a) {\n    const int n = a.size();\n    a.resize(n * 2);\n    fft_doubling_n(a.begin(),\
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
  timestamp: '2024-12-02 23:15:40+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/formal_power_series/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
  - test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - test/formal_power_series/shift_of_sampling_points_of_polynomial.0.test.cpp
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
