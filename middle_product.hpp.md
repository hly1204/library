---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: fft.hpp
    title: FFT
  _extendedRequiredBy:
  - icon: ':question:'
    path: czt.hpp
    title: czt.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/convolution_mod.1.test.cpp
    title: test/convolution/convolution_mod.1.test.cpp
  - icon: ':x:'
    path: test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
    title: test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - icon: ':x:'
    path: test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
    title: test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
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
    \  return (n | n >> 16) + 1;\n}\n\ntemplate <typename Iterator>\ninline void fft_n(Iterator\
    \ a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    assert((n & (n - 1)) == 0);\n    auto &&root = FftInfo<Tp>::get().root(n\
    \ / 2);\n    for (int i = n; i >= 2; i /= 2) {\n        for (int k = 0; k < i\
    \ / 2; ++k) {\n            const auto u = a[k], v = a[k + i / 2];\n          \
    \  a[k] = u + v, a[k + i / 2] = u - v;\n        }\n        for (int j = i, m =\
    \ 1; j < n; j += i, ++m)\n            for (int k = j; k < j + i / 2; ++k) {\n\
    \                const auto u = a[k], v = a[k + i / 2] * root[m];\n          \
    \      a[k] = u + v, a[k + i / 2] = u - v;\n            }\n    }\n}\n\ntemplate\
    \ <typename Tp>\ninline void fft(std::vector<Tp> &a) {\n    fft_n(a.begin(), a.size());\n\
    }\n\ntemplate <typename Iterator>\ninline void inv_fft_n(Iterator a, int n) {\n\
    \    using Tp = typename std::iterator_traits<Iterator>::value_type;\n    assert((n\
    \ & (n - 1)) == 0);\n    auto &&root = FftInfo<Tp>::get().inv_root(n / 2);\n \
    \   for (int i = 2; i <= n; i *= 2) {\n        for (int j = 0; j < i / 2; ++j)\
    \ {\n            const auto u = a[j], v = a[j + i / 2];\n            a[j] = u\
    \ + v, a[j + i / 2] = u - v;\n        }\n        for (int j = i, m = 1; j < n;\
    \ j += i, ++m)\n            for (int k = j; k < j + i / 2; ++k) {\n          \
    \      const auto u = a[k], v = a[k + i / 2];\n                a[k] = u + v, a[k\
    \ + i / 2] = (u - v) * root[m];\n            }\n    }\n    const Tp iv = Tp::mod()\
    \ - (Tp::mod() - 1) / n;\n    for (int i = 0; i < n; ++i) a[i] *= iv;\n}\n\ntemplate\
    \ <typename Tp>\ninline void inv_fft(std::vector<Tp> &a) {\n    inv_fft_n(a.begin(),\
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
    }\n#line 6 \"middle_product.hpp\"\n\n// see:\n// [1]: Guillaume Hanrot, Michel\
    \ Quercia, Paul Zimmermann. The Middle Product Algorithm I.\n// [2]: Alin Bostan,\
    \ Gr\xE9goire Lecerf, \xC9ric Schost. Tellegen's principle into practice.\n\n\
    // returns (fg)_(n-1),...,(fg)_(m-1)\n// f: f_0 + ... + f_(m-1)x^(m-1)\n// g:\
    \ g_0 + ... + g_(n-1)x^(n-1)\n// m >= n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ middle_product(std::vector<Tp> f, std::vector<Tp> g) {\n    const int m = f.size();\n\
    \    const int n = g.size();\n    assert(m >= n);\n    const int len = fft_len(m);\n\
    \    f.resize(len);\n    g.resize(len);\n    fft(f);\n    fft(g);\n    for (int\
    \ i = 0; i < len; ++i) f[i] *= g[i];\n    inv_fft(f);\n    f.erase(f.begin(),\
    \ f.begin() + (n - 1));\n    f.resize(m - n + 1);\n    return f;\n}\n"
  code: "#pragma once\n\n#include \"fft.hpp\"\n#include <cassert>\n#include <vector>\n\
    \n// see:\n// [1]: Guillaume Hanrot, Michel Quercia, Paul Zimmermann. The Middle\
    \ Product Algorithm I.\n// [2]: Alin Bostan, Gr\xE9goire Lecerf, \xC9ric Schost.\
    \ Tellegen's principle into practice.\n\n// returns (fg)_(n-1),...,(fg)_(m-1)\n\
    // f: f_0 + ... + f_(m-1)x^(m-1)\n// g: g_0 + ... + g_(n-1)x^(n-1)\n// m >= n\n\
    template <typename Tp>\ninline std::vector<Tp> middle_product(std::vector<Tp>\
    \ f, std::vector<Tp> g) {\n    const int m = f.size();\n    const int n = g.size();\n\
    \    assert(m >= n);\n    const int len = fft_len(m);\n    f.resize(len);\n  \
    \  g.resize(len);\n    fft(f);\n    fft(g);\n    for (int i = 0; i < len; ++i)\
    \ f[i] *= g[i];\n    inv_fft(f);\n    f.erase(f.begin(), f.begin() + (n - 1));\n\
    \    f.resize(m - n + 1);\n    return f;\n}\n"
  dependsOn:
  - fft.hpp
  isVerificationFile: false
  path: middle_product.hpp
  requiredBy:
  - czt.hpp
  timestamp: '2024-12-01 23:46:11+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  - test/convolution/convolution_mod.1.test.cpp
documentation_of: middle_product.hpp
layout: document
redirect_from:
- /library/middle_product.hpp
- /library/middle_product.hpp.html
title: middle_product.hpp
---
