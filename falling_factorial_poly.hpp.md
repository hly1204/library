---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: binomial.hpp
    title: binomial.hpp
  - icon: ':question:'
    path: fft.hpp
    title: FFT
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: shift_sample_points.hpp
    title: shift_sample_points.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/shift_of_sampling_points_of_polynomial.1.test.cpp
    title: test/formal_power_series/shift_of_sampling_points_of_polynomial.1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"falling_factorial_poly.hpp\"\n\n#line 2 \"binomial.hpp\"\
    \n\n#include <algorithm>\n#include <vector>\n\ntemplate <typename Tp>\nclass Binomial\
    \ {\n    std::vector<Tp> factorial_, invfactorial_;\n\n    Binomial() : factorial_{Tp(1)},\
    \ invfactorial_{Tp(1)} {}\n\n    void preprocess(int n) {\n        if (const int\
    \ nn = factorial_.size(); nn < n) {\n            int k = nn;\n            while\
    \ (k < n) k *= 2;\n            k = std::min<long long>(k, Tp::mod());\n      \
    \      factorial_.resize(k);\n            invfactorial_.resize(k);\n         \
    \   for (int i = nn; i < k; ++i) factorial_[i] = factorial_[i - 1] * i;\n    \
    \        invfactorial_.back() = factorial_.back().inv();\n            for (int\
    \ i = k - 2; i >= nn; --i) invfactorial_[i] = invfactorial_[i + 1] * (i + 1);\n\
    \        }\n    }\n\npublic:\n    static const Binomial &get(int n) {\n      \
    \  static Binomial bin;\n        bin.preprocess(n);\n        return bin;\n   \
    \ }\n\n    Tp binom(int n, int m) const {\n        return n < m ? Tp() : factorial_[n]\
    \ * invfactorial_[m] * invfactorial_[n - m];\n    }\n    Tp inv(int n) const {\
    \ return factorial_[n - 1] * invfactorial_[n]; }\n    Tp factorial(int n) const\
    \ { return factorial_[n]; }\n    Tp inv_factorial(int n) const { return invfactorial_[n];\
    \ }\n};\n#line 2 \"fft.hpp\"\n\n#line 4 \"fft.hpp\"\n#include <cassert>\n#include\
    \ <iterator>\n#include <memory>\n#line 8 \"fft.hpp\"\n\ntemplate <typename Tp>\n\
    class FftInfo {\n    static Tp least_quadratic_nonresidue() {\n        for (int\
    \ i = 2;; ++i)\n            if (Tp(i).pow((Tp::mod() - 1) / 2) == -1) return Tp(i);\n\
    \    }\n\n    const int ordlog2_;\n    const Tp zeta_;\n    const Tp invzeta_;\n\
    \    const Tp imag_;\n    const Tp invimag_;\n\n    mutable std::vector<Tp> root_;\n\
    \    mutable std::vector<Tp> invroot_;\n\n    FftInfo()\n        : ordlog2_(__builtin_ctzll(Tp::mod()\
    \ - 1)),\n          zeta_(least_quadratic_nonresidue().pow((Tp::mod() - 1) >>\
    \ ordlog2_)),\n          invzeta_(zeta_.inv()), imag_(zeta_.pow(1LL << (ordlog2_\
    \ - 2))), invimag_(-imag_),\n          root_{Tp(1), imag_}, invroot_{Tp(1), invimag_}\
    \ {}\n\npublic:\n    static const FftInfo &get() {\n        static FftInfo info;\n\
    \        return info;\n    }\n\n    Tp imag() const { return imag_; }\n    Tp\
    \ inv_imag() const { return invimag_; }\n    Tp zeta() const { return zeta_; }\n\
    \    Tp inv_zeta() const { return invzeta_; }\n    const std::vector<Tp> &root(int\
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
    \    assert((n & (n - 1)) == 0);\n    const int bn = __builtin_ctz(n);\n    if\
    \ (bn & 1) {\n        for (int i = 0; i < n / 2; ++i) {\n            const auto\
    \ a0 = a[i], a1 = a[i + n / 2];\n            a[i] = a0 + a1, a[i + n / 2] = a0\
    \ - a1;\n        }\n    }\n    auto &&root = FftInfo<Tp>::get().root(n / 2);\n\
    \    for (int i = n >> (bn & 1); i >= 4; i /= 4) {\n        const int i4 = i /\
    \ 4;\n        for (int k = 0; k < i4; ++k) {\n            const auto a0 = a[k\
    \ + i4 * 0], a1 = a[k + i4 * 1];\n            const auto a2 = a[k + i4 * 2], a3\
    \ = a[k + i4 * 3];\n            const auto a02p = a0 + a2, a02m = a0 - a2;\n \
    \           const auto a13p = a1 + a3, a13m = (a1 - a3) * FftInfo<Tp>::get().imag();\n\
    \            a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p - a13p;\n     \
    \       a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;\n        }\n\
    \        for (int j = i, m = 2; j < n; j += i, m += 2) {\n            const auto\
    \ r = root[m], r2 = r * r, r3 = r2 * r;\n            for (int k = j; k < j + i4;\
    \ ++k) {\n                const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1] *\
    \ r;\n                const auto a2 = a[k + i4 * 2] * r2, a3 = a[k + i4 * 3] *\
    \ r3;\n                const auto a02p = a0 + a2, a02m = a0 - a2;\n          \
    \      const auto a13p = a1 + a3, a13m = (a1 - a3) * FftInfo<Tp>::get().imag();\n\
    \                a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p - a13p;\n \
    \               a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;\n  \
    \          }\n        }\n    }\n}\n\ntemplate <typename Tp>\ninline void fft(std::vector<Tp>\
    \ &a) {\n    fft_n(a.begin(), a.size());\n}\n\ntemplate <typename Iterator>\n\
    inline void inv_fft_n(Iterator a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    assert((n & (n - 1)) == 0);\n    const int bn = __builtin_ctz(n);\n    auto\
    \ &&root  = FftInfo<Tp>::get().inv_root(n / 2);\n    for (int i = 4; i <= (n >>\
    \ (bn & 1)); i *= 4) {\n        const int i4 = i / 4;\n        for (int k = 0;\
    \ k < i4; ++k) {\n            const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];\n\
    \            const auto a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];\n            const\
    \ auto a01p = a0 + a1, a01m = a0 - a1;\n            const auto a23p = a2 + a3,\
    \ a23m = (a2 - a3) * FftInfo<Tp>::get().imag();\n            a[k + i4 * 0] = a01p\
    \ + a23p, a[k + i4 * 1] = a01m - a23m;\n            a[k + i4 * 2] = a01p - a23p,\
    \ a[k + i4 * 3] = a01m + a23m;\n        }\n        for (int j = i, m = 2; j <\
    \ n; j += i, m += 2) {\n            const auto r = root[m], r2 = r * r, r3 = r2\
    \ * r;\n            for (int k = j; k < j + i4; ++k) {\n                const\
    \ auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];\n                const auto a2\
    \ = a[k + i4 * 2], a3 = a[k + i4 * 3];\n                const auto a01p = a0 +\
    \ a1, a01m = a0 - a1;\n                const auto a23p = a2 + a3, a23m = (a2 -\
    \ a3) * FftInfo<Tp>::get().imag();\n                a[k + i4 * 0] = a01p + a23p,\
    \ a[k + i4 * 1] = (a01m - a23m) * r;\n                a[k + i4 * 2] = (a01p -\
    \ a23p) * r2, a[k + i4 * 3] = (a01m + a23m) * r3;\n            }\n        }\n\
    \    }\n    if (bn & 1) {\n        for (int i = 0; i < n / 2; ++i) {\n       \
    \     const auto a0 = a[i], a1 = a[i + n / 2];\n            a[i] = a0 + a1, a[i\
    \ + n / 2] = a0 - a1;\n        }\n    }\n    const Tp iv = Tp::mod() - (Tp::mod()\
    \ - 1) / n;\n    for (int i = 0; i < n; ++i) a[i] *= iv;\n}\n\ntemplate <typename\
    \ Tp>\ninline void inv_fft(std::vector<Tp> &a) {\n    inv_fft_n(a.begin(), a.size());\n\
    }\n\ntemplate <typename Tp>\ninline std::vector<Tp> convolution_fft(std::vector<Tp>\
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
    }\n#line 7 \"falling_factorial_poly.hpp\"\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ sample_points_to_ffp(const std::vector<Tp> &F) {\n    const int n = F.size();\n\
    \    auto &&bin  = Binomial<Tp>::get(n);\n    std::vector<Tp> egfF(F), ee(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        egfF[i] *= bin.inv_factorial(i);\n\
    \        ee[i] = bin.inv_factorial(i);\n        if (i & 1) ee[i] = -ee[i];\n \
    \   }\n    auto ffp = convolution(egfF, ee);\n    ffp.resize(n);\n    return ffp;\n\
    }\n\ntemplate <typename Tp>\ninline std::vector<Tp> ffp_to_sample_points(const\
    \ std::vector<Tp> &ffp, int n) {\n    auto &&bin = Binomial<Tp>::get(n);\n   \
    \ std::vector<Tp> ee(n);\n    for (int i = 0; i < n; ++i) ee[i] = bin.inv_factorial(i);\n\
    \    auto F = convolution(std::vector(ffp.begin(), ffp.begin() + std::min<int>(n,\
    \ ffp.size())), ee);\n    F.resize(n);\n    for (int i = 0; i < n; ++i) F[i] *=\
    \ bin.factorial(i);\n    return F;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ shift_ffp(std::vector<Tp> ffp, Tp c) {\n    const int n = ffp.size();\n    auto\
    \ &&bin  = Binomial<Tp>::get(n);\n    std::vector<Tp> C(n);\n    Tp cc = 1;\n\
    \    for (int i = 0; i < n; ++i) {\n        ffp[i] *= bin.factorial(i);\n    \
    \    C[i] = cc * bin.inv_factorial(i);\n        cc *= c - i;\n    }\n    std::reverse(ffp.begin(),\
    \ ffp.end());\n    auto res = convolution(ffp, C);\n    res.resize(n);\n    std::reverse(res.begin(),\
    \ res.end());\n    for (int i = 0; i < n; ++i) res[i] *= bin.inv_factorial(i);\n\
    \    return res;\n}\n"
  code: "#pragma once\n\n#include \"binomial.hpp\"\n#include \"fft.hpp\"\n#include\
    \ <algorithm>\n#include <vector>\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ sample_points_to_ffp(const std::vector<Tp> &F) {\n    const int n = F.size();\n\
    \    auto &&bin  = Binomial<Tp>::get(n);\n    std::vector<Tp> egfF(F), ee(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        egfF[i] *= bin.inv_factorial(i);\n\
    \        ee[i] = bin.inv_factorial(i);\n        if (i & 1) ee[i] = -ee[i];\n \
    \   }\n    auto ffp = convolution(egfF, ee);\n    ffp.resize(n);\n    return ffp;\n\
    }\n\ntemplate <typename Tp>\ninline std::vector<Tp> ffp_to_sample_points(const\
    \ std::vector<Tp> &ffp, int n) {\n    auto &&bin = Binomial<Tp>::get(n);\n   \
    \ std::vector<Tp> ee(n);\n    for (int i = 0; i < n; ++i) ee[i] = bin.inv_factorial(i);\n\
    \    auto F = convolution(std::vector(ffp.begin(), ffp.begin() + std::min<int>(n,\
    \ ffp.size())), ee);\n    F.resize(n);\n    for (int i = 0; i < n; ++i) F[i] *=\
    \ bin.factorial(i);\n    return F;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ shift_ffp(std::vector<Tp> ffp, Tp c) {\n    const int n = ffp.size();\n    auto\
    \ &&bin  = Binomial<Tp>::get(n);\n    std::vector<Tp> C(n);\n    Tp cc = 1;\n\
    \    for (int i = 0; i < n; ++i) {\n        ffp[i] *= bin.factorial(i);\n    \
    \    C[i] = cc * bin.inv_factorial(i);\n        cc *= c - i;\n    }\n    std::reverse(ffp.begin(),\
    \ ffp.end());\n    auto res = convolution(ffp, C);\n    res.resize(n);\n    std::reverse(res.begin(),\
    \ res.end());\n    for (int i = 0; i < n; ++i) res[i] *= bin.inv_factorial(i);\n\
    \    return res;\n}\n"
  dependsOn:
  - binomial.hpp
  - fft.hpp
  isVerificationFile: false
  path: falling_factorial_poly.hpp
  requiredBy:
  - shift_sample_points.hpp
  timestamp: '2024-12-02 00:00:45+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/formal_power_series/shift_of_sampling_points_of_polynomial.1.test.cpp
documentation_of: falling_factorial_poly.hpp
layout: document
redirect_from:
- /library/falling_factorial_poly.hpp
- /library/falling_factorial_poly.hpp.html
title: falling_factorial_poly.hpp
---
