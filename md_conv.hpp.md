---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fft.hpp
    title: FFT
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/multivariate_convolution.0.test.cpp
    title: test/convolution/multivariate_convolution.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://rushcheyo.blog.uoj.ac/blog/6547
    - https://www.luogu.com/article/wje8kchr
  bundledCode: "#line 2 \"md_conv.hpp\"\n\n#line 2 \"fft.hpp\"\n\n#include <algorithm>\n\
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
    }\n#line 5 \"md_conv.hpp\"\n#include <iostream>\n#line 7 \"md_conv.hpp\"\n\n//\
    \ see:\n// [1]: Elegia. Hello, multivariate multiplication.\n//      https://www.luogu.com/article/wje8kchr\n\
    // [2]: rushcheyo. \u96C6\u8BAD\u961F\u4E92\u6D4B 2021 Round #1 \u9898\u89E3.\n\
    //      https://rushcheyo.blog.uoj.ac/blog/6547\ntemplate <typename Tp>\nclass\
    \ MDConvInfo {\n    int len_;\n    std::vector<int> degree_bound_;\n    std::vector<int>\
    \ prefix_prod_degree_bound_;\n    std::vector<int> chi_;\n\npublic:\n    MDConvInfo(const\
    \ std::vector<int> &d) : len_(1), degree_bound_(d) {\n        for (auto deg :\
    \ degree_bound_) {\n            assert(deg > 1);\n            len_ *= deg;\n \
    \       }\n        chi_.resize(len_);\n        auto &&pp = prefix_prod_degree_bound_\
    \ = degree_bound_;\n        for (int i = 1; i < (int)pp.size(); ++i) pp[i] *=\
    \ pp[i - 1];\n        for (int i = 1; i < len_; ++i) {\n            // chi(i)\
    \ = floor(i/d[0]) + floor(i/(d[0]*d[1])) + ... + floor(i/(d[0]*...))\n       \
    \     for (int j = 0; j < (int)pp.size() - 1; ++j) chi_[i] += i / pp[j];\n   \
    \         chi_[i] %= (int)pp.size();\n        }\n    }\n\n    int dim() const\
    \ { return degree_bound_.size(); }\n    const std::vector<int> &degree_bound()\
    \ const { return degree_bound_; }\n    const std::vector<int> &chi() const { return\
    \ chi_; }\n\n    std::vector<Tp> convolution(const std::vector<Tp> &a, const std::vector<Tp>\
    \ &b) const {\n        assert((int)a.size() == len_);\n        assert((int)b.size()\
    \ == len_);\n        const int d = dim();\n        if (d == 0) return {a[0] *\
    \ b[0]};\n        const int len = fft_len(len_ * 2 - 1);\n        std::vector\
    \ aa(d, std::vector<Tp>(len));\n        std::vector bb(d, std::vector<Tp>(len));\n\
    \        std::vector aabb(d, std::vector<Tp>(len));\n        for (int i = 0; i\
    \ < len_; ++i) {\n            aa[chi_[i]][i] = a[i];\n            bb[chi_[i]][i]\
    \ = b[i];\n        }\n        for (int i = 0; i < d; ++i) {\n            fft(aa[i]);\n\
    \            fft(bb[i]);\n        }\n        for (int i = 0; i < d; ++i) {\n \
    \           for (int j = 0; j < d; ++j) {\n                const int k = (i +\
    \ j) % d;\n                for (int l = 0; l < len; ++l) aabb[k][l] += aa[i][l]\
    \ * bb[j][l];\n            }\n        }\n        for (int i = 0; i < d; ++i) inv_fft(aabb[i]);\n\
    \        std::vector<Tp> ab(len_);\n        for (int i = 0; i < len_; ++i) ab[i]\
    \ = aabb[chi_[i]][i];\n        return ab;\n    }\n\n    std::ostream &pretty_print(std::ostream\
    \ &os, const std::vector<Tp> &a) const {\n        assert((int)a.size() == len_);\n\
    \        os << '[';\n        std::vector<int> deg(dim());\n        for (int i\
    \ = 0; i < len_; ++i) {\n            if (i) os << \" + \";\n            os <<\
    \ a[i];\n            for (int j = 0; j < (int)deg.size(); ++j) os << \"*x\" <<\
    \ j << \"^(\" << deg[j] << ')';\n            for (int j = 0; j < (int)deg.size();\
    \ ++j) {\n                if (++deg[j] < degree_bound_[j]) break;\n          \
    \      deg[j] = 0;\n            }\n        }\n        return os << ']';\n    }\n\
    };\n"
  code: "#pragma once\n\n#include \"fft.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #include <vector>\n\n// see:\n// [1]: Elegia. Hello, multivariate multiplication.\n\
    //      https://www.luogu.com/article/wje8kchr\n// [2]: rushcheyo. \u96C6\u8BAD\
    \u961F\u4E92\u6D4B 2021 Round #1 \u9898\u89E3.\n//      https://rushcheyo.blog.uoj.ac/blog/6547\n\
    template <typename Tp>\nclass MDConvInfo {\n    int len_;\n    std::vector<int>\
    \ degree_bound_;\n    std::vector<int> prefix_prod_degree_bound_;\n    std::vector<int>\
    \ chi_;\n\npublic:\n    MDConvInfo(const std::vector<int> &d) : len_(1), degree_bound_(d)\
    \ {\n        for (auto deg : degree_bound_) {\n            assert(deg > 1);\n\
    \            len_ *= deg;\n        }\n        chi_.resize(len_);\n        auto\
    \ &&pp = prefix_prod_degree_bound_ = degree_bound_;\n        for (int i = 1; i\
    \ < (int)pp.size(); ++i) pp[i] *= pp[i - 1];\n        for (int i = 1; i < len_;\
    \ ++i) {\n            // chi(i) = floor(i/d[0]) + floor(i/(d[0]*d[1])) + ... +\
    \ floor(i/(d[0]*...))\n            for (int j = 0; j < (int)pp.size() - 1; ++j)\
    \ chi_[i] += i / pp[j];\n            chi_[i] %= (int)pp.size();\n        }\n \
    \   }\n\n    int dim() const { return degree_bound_.size(); }\n    const std::vector<int>\
    \ &degree_bound() const { return degree_bound_; }\n    const std::vector<int>\
    \ &chi() const { return chi_; }\n\n    std::vector<Tp> convolution(const std::vector<Tp>\
    \ &a, const std::vector<Tp> &b) const {\n        assert((int)a.size() == len_);\n\
    \        assert((int)b.size() == len_);\n        const int d = dim();\n      \
    \  if (d == 0) return {a[0] * b[0]};\n        const int len = fft_len(len_ * 2\
    \ - 1);\n        std::vector aa(d, std::vector<Tp>(len));\n        std::vector\
    \ bb(d, std::vector<Tp>(len));\n        std::vector aabb(d, std::vector<Tp>(len));\n\
    \        for (int i = 0; i < len_; ++i) {\n            aa[chi_[i]][i] = a[i];\n\
    \            bb[chi_[i]][i] = b[i];\n        }\n        for (int i = 0; i < d;\
    \ ++i) {\n            fft(aa[i]);\n            fft(bb[i]);\n        }\n      \
    \  for (int i = 0; i < d; ++i) {\n            for (int j = 0; j < d; ++j) {\n\
    \                const int k = (i + j) % d;\n                for (int l = 0; l\
    \ < len; ++l) aabb[k][l] += aa[i][l] * bb[j][l];\n            }\n        }\n \
    \       for (int i = 0; i < d; ++i) inv_fft(aabb[i]);\n        std::vector<Tp>\
    \ ab(len_);\n        for (int i = 0; i < len_; ++i) ab[i] = aabb[chi_[i]][i];\n\
    \        return ab;\n    }\n\n    std::ostream &pretty_print(std::ostream &os,\
    \ const std::vector<Tp> &a) const {\n        assert((int)a.size() == len_);\n\
    \        os << '[';\n        std::vector<int> deg(dim());\n        for (int i\
    \ = 0; i < len_; ++i) {\n            if (i) os << \" + \";\n            os <<\
    \ a[i];\n            for (int j = 0; j < (int)deg.size(); ++j) os << \"*x\" <<\
    \ j << \"^(\" << deg[j] << ')';\n            for (int j = 0; j < (int)deg.size();\
    \ ++j) {\n                if (++deg[j] < degree_bound_[j]) break;\n          \
    \      deg[j] = 0;\n            }\n        }\n        return os << ']';\n    }\n\
    };\n"
  dependsOn:
  - fft.hpp
  isVerificationFile: false
  path: md_conv.hpp
  requiredBy: []
  timestamp: '2025-01-09 19:10:15+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution/multivariate_convolution.0.test.cpp
documentation_of: md_conv.hpp
layout: document
redirect_from:
- /library/md_conv.hpp
- /library/md_conv.hpp.html
title: md_conv.hpp
---
