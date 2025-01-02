---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fft.hpp
    title: FFT
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: czt.hpp
    title: Chirp Z Transform
  - icon: ':heavy_check_mark:'
    path: shift_sample_points.hpp
    title: Shift Sample Points
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/convolution_mod.1.test.cpp
    title: test/convolution/convolution_mod.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
    title: test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
    title: test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/shift_of_sampling_points_of_polynomial.1.test.cpp
    title: test/formal_power_series/shift_of_sampling_points_of_polynomial.1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"middle_product.hpp\"\n\n#line 2 \"fft.hpp\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <iterator>\n#include <memory>\n#include\
    \ <vector>\n\ntemplate <typename Tp>\nclass FftInfo {\n    static Tp least_quadratic_nonresidue()\
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
    }\n#line 7 \"middle_product.hpp\"\n\n// see:\n// [1]: Guillaume Hanrot, Michel\
    \ Quercia, Paul Zimmermann. The Middle Product Algorithm I.\n// [2]: Alin Bostan,\
    \ Gr\xE9goire Lecerf, \xC9ric Schost. Tellegen's principle into practice.\n\n\
    // returns (fg)_(n-1),...,(fg)_(m-1)\n// f: f_0 + ... + f_(m-1)x^(m-1)\n// g:\
    \ g_0 + ... + g_(n-1)x^(n-1)\n// m >= n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ middle_product(std::vector<Tp> f, std::vector<Tp> g) {\n    const int m = f.size();\n\
    \    const int n = g.size();\n    assert(m >= n);\n    std::reverse(g.begin(),\
    \ g.end());\n    const int len = fft_len(m);\n    f.resize(len);\n    g.resize(len);\n\
    \    transposed_inv_fft(f);\n    fft(g);\n    for (int i = 0; i < len; ++i) f[i]\
    \ *= g[i];\n    transposed_fft(f);\n    f.resize(m - n + 1);\n    return f;\n\
    }\n"
  code: "#pragma once\n\n#include \"fft.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <vector>\n\n// see:\n// [1]: Guillaume Hanrot, Michel Quercia, Paul Zimmermann.\
    \ The Middle Product Algorithm I.\n// [2]: Alin Bostan, Gr\xE9goire Lecerf, \xC9\
    ric Schost. Tellegen's principle into practice.\n\n// returns (fg)_(n-1),...,(fg)_(m-1)\n\
    // f: f_0 + ... + f_(m-1)x^(m-1)\n// g: g_0 + ... + g_(n-1)x^(n-1)\n// m >= n\n\
    template <typename Tp>\ninline std::vector<Tp> middle_product(std::vector<Tp>\
    \ f, std::vector<Tp> g) {\n    const int m = f.size();\n    const int n = g.size();\n\
    \    assert(m >= n);\n    std::reverse(g.begin(), g.end());\n    const int len\
    \ = fft_len(m);\n    f.resize(len);\n    g.resize(len);\n    transposed_inv_fft(f);\n\
    \    fft(g);\n    for (int i = 0; i < len; ++i) f[i] *= g[i];\n    transposed_fft(f);\n\
    \    f.resize(m - n + 1);\n    return f;\n}\n"
  dependsOn:
  - fft.hpp
  isVerificationFile: false
  path: middle_product.hpp
  requiredBy:
  - shift_sample_points.hpp
  - czt.hpp
  timestamp: '2024-12-03 09:02:32+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  - test/formal_power_series/shift_of_sampling_points_of_polynomial.1.test.cpp
  - test/convolution/convolution_mod.1.test.cpp
documentation_of: middle_product.hpp
layout: document
redirect_from:
- /library/middle_product.hpp
- /library/middle_product.hpp.html
title: middle_product.hpp
---
