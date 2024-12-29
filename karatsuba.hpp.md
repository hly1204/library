---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fft.hpp
    title: FFT
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://cr.yp.to/papers.html#m3
  bundledCode: "#line 2 \"karatsuba.hpp\"\n\n#line 2 \"fft.hpp\"\n\n#include <algorithm>\n\
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
    }\n\n// IFFT_n^T: A(x) |-> 1/n FFT_n((x^n A(x^(-1))) mod (x^n - 1))\ntemplate\
    \ <typename Iterator>\ninline void transposed_inv_fft_n(Iterator a, int n) {\n\
    \    using Tp    = typename std::iterator_traits<Iterator>::value_type;\n    const\
    \ Tp iv = Tp::mod() - (Tp::mod() - 1) / n;\n    for (int i = 0; i < n; ++i) a[i]\
    \ *= iv;\n    detail::butterfly_n(a, n, FftInfo<Tp>::get().inv_root(n / 2));\n\
    }\n\ntemplate <typename Tp>\ninline void transposed_inv_fft(std::vector<Tp> &a)\
    \ {\n    transposed_inv_fft_n(a.begin(), a.size());\n}\n\n// FFT_n^T : FFT_n((x^n\
    \ A(x^(-1))) mod (x^n - 1)) |-> n A(x)\ntemplate <typename Iterator>\ninline void\
    \ transposed_fft_n(Iterator a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
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
    }\n#line 6 \"karatsuba.hpp\"\n\n// see:\n// [1]: Daniel J. Bernstein. Multidigit\
    \ multiplication for mathematicians.\n//      https://cr.yp.to/papers.html#m3\n\
    template <typename Tp>\ninline std::vector<Tp> convolution_karatsuba(const std::vector<Tp>\
    \ &a, const std::vector<Tp> &b) {\n    const int n = a.size();\n    const int\
    \ m = b.size();\n    if (std::min(n, m) < 60) return convolution_naive(a, b);\n\
    \    const int half = (std::max(n, m) + 1) / 2;\n    const std::vector a0(a.begin(),\
    \ a.begin() + std::min(n, half));\n    const std::vector a1(a.begin() + std::min(n,\
    \ half), a.end());\n    const std::vector b0(b.begin(), b.begin() + std::min(m,\
    \ half));\n    const std::vector b1(b.begin() + std::min(m, half), b.end());\n\
    \    // Let y := x^(half)\n    // a = a0 + a1y, b = b0 + b1y\n    // ab = a0b0\
    \ + (a0b1 + a1b0)y + (a1b1)y^2\n    // ab = a0b0 + ((a0 + a1)(b0 + b1) - a0b0\
    \ - a1b1)y + (a1b1)y^2\n    // ab mod (y^2 - y) = a0b0 + (a0b1 + a1b0)y + a1b1y\n\
    \    // R[x] -> R[x][y]/(y^2 - y)\n\n    // eval for y = 0\n    const auto low\
    \ = convolution_karatsuba(a0, b0);\n\n    auto add = [](std::vector<Tp> a, const\
    \ std::vector<Tp> &b) {\n        if (a.size() < b.size()) a.resize(b.size());\n\
    \        for (int i = 0; i < (int)b.size(); ++i) a[i] += b[i];\n        return\
    \ a;\n    };\n    // eval for y = 1\n    const auto mid = convolution_karatsuba(add(a0,\
    \ a1), add(b0, b1));\n    // If we want to compute ab mod (y^2 - y), we only need\
    \ to extract low from mid.\n    // To restore the full product, we need to eval\
    \ at inf.\n    // eval for y = inf\n    const auto hig = convolution_karatsuba(a1,\
    \ b1);\n\n    // restore ab\n    std::vector<Tp> ab(n + m - 1);\n    for (int\
    \ i = 0; i < (int)low.size(); ++i) ab[i] += low[i], ab[i + half] -= low[i];\n\
    \    for (int i = 0; i < (int)mid.size(); ++i) ab[i + half] += mid[i];\n    for\
    \ (int i = 0; i < (int)hig.size(); ++i) ab[i + half] -= hig[i], ab[i + half *\
    \ 2] += hig[i];\n    return ab;\n}\n"
  code: "#pragma once\n\n#include \"fft.hpp\"\n#include <algorithm>\n#include <vector>\n\
    \n// see:\n// [1]: Daniel J. Bernstein. Multidigit multiplication for mathematicians.\n\
    //      https://cr.yp.to/papers.html#m3\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ convolution_karatsuba(const std::vector<Tp> &a, const std::vector<Tp> &b) {\n\
    \    const int n = a.size();\n    const int m = b.size();\n    if (std::min(n,\
    \ m) < 60) return convolution_naive(a, b);\n    const int half = (std::max(n,\
    \ m) + 1) / 2;\n    const std::vector a0(a.begin(), a.begin() + std::min(n, half));\n\
    \    const std::vector a1(a.begin() + std::min(n, half), a.end());\n    const\
    \ std::vector b0(b.begin(), b.begin() + std::min(m, half));\n    const std::vector\
    \ b1(b.begin() + std::min(m, half), b.end());\n    // Let y := x^(half)\n    //\
    \ a = a0 + a1y, b = b0 + b1y\n    // ab = a0b0 + (a0b1 + a1b0)y + (a1b1)y^2\n\
    \    // ab = a0b0 + ((a0 + a1)(b0 + b1) - a0b0 - a1b1)y + (a1b1)y^2\n    // ab\
    \ mod (y^2 - y) = a0b0 + (a0b1 + a1b0)y + a1b1y\n    // R[x] -> R[x][y]/(y^2 -\
    \ y)\n\n    // eval for y = 0\n    const auto low = convolution_karatsuba(a0,\
    \ b0);\n\n    auto add = [](std::vector<Tp> a, const std::vector<Tp> &b) {\n \
    \       if (a.size() < b.size()) a.resize(b.size());\n        for (int i = 0;\
    \ i < (int)b.size(); ++i) a[i] += b[i];\n        return a;\n    };\n    // eval\
    \ for y = 1\n    const auto mid = convolution_karatsuba(add(a0, a1), add(b0, b1));\n\
    \    // If we want to compute ab mod (y^2 - y), we only need to extract low from\
    \ mid.\n    // To restore the full product, we need to eval at inf.\n    // eval\
    \ for y = inf\n    const auto hig = convolution_karatsuba(a1, b1);\n\n    // restore\
    \ ab\n    std::vector<Tp> ab(n + m - 1);\n    for (int i = 0; i < (int)low.size();\
    \ ++i) ab[i] += low[i], ab[i + half] -= low[i];\n    for (int i = 0; i < (int)mid.size();\
    \ ++i) ab[i + half] += mid[i];\n    for (int i = 0; i < (int)hig.size(); ++i)\
    \ ab[i + half] -= hig[i], ab[i + half * 2] += hig[i];\n    return ab;\n}\n"
  dependsOn:
  - fft.hpp
  isVerificationFile: false
  path: karatsuba.hpp
  requiredBy: []
  timestamp: '2024-12-12 19:21:16+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: karatsuba.hpp
layout: document
title: Karatsuba Multiplication
---

## Karatsuba Multiplication

Karatsuba multiplication algorithm is very easy and well explained in Bernstein's paper.

If we want to compute the product of $A(y) = a_0 + a_1y$ and $B(y) = b_0 + b_1y$, Karatsuba suggests that we could compute $A(y)B(y) \bmod {\left(y^2 - y\right)}$, and use $\left(AB\right)(\infty) = a_1b_1$ to restore the result of $A(y)B(y)$.

For computing $A(y)B(y) \bmod {\left(y^2 - y\right)}$, a FFT-styled algorithm is used. We evaluate for $A(0), A(1), B(0), B(1)$ then we will get $A(y)B(y) \bmod {\left(y^2 - y\right)}$ without division. We could restore $A(y)B(y)$ with $a_1b_1$. An alternative is that we could compute $A(y)B(y) \bmod {\left(y^2 + y\right)}$ by evaluating $A(0), A(-1), B(0), B(-1)$ which works similarly.

I think the most important thing we could learn is that, this could be modified and used in computing bitwise convolution such as "bitwise and/or/xor convolution".

## References

1. Daniel J. Bernstein. "Multidigit multiplication for mathematicians." Accepted to Advances in Applied Mathematics, but withdrawn by author to prevent irreparable mangling by Academic Press. url: <https://cr.yp.to/papers.html#m3>
