---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: fft.hpp
    title: fft.hpp
  _extendedRequiredBy:
  - icon: ':question:'
    path: c_recursive.hpp
    title: c_recursive.hpp
  - icon: ':warning:'
    path: eulerian_number.hpp
    title: eulerian_number.hpp
  - icon: ':question:'
    path: fps_basic.hpp
    title: fps_basic.hpp
  - icon: ':heavy_check_mark:'
    path: fps_composition.hpp
    title: fps_composition.hpp
  - icon: ':question:'
    path: poly_basic.hpp
    title: poly_basic.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/composition_of_formal_power_series_large.0.test.cpp
    title: test/composition_of_formal_power_series_large.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/compositional_inverse_of_formal_power_series_large.0.test.cpp
    title: test/compositional_inverse_of_formal_power_series_large.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
    title: test/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/division_of_polynomials.0.test.cpp
    title: test/division_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/exp_of_formal_power_series.0.test.cpp
    title: test/exp_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/inv_of_formal_power_series.0.test.cpp
    title: test/inv_of_formal_power_series.0.test.cpp
  - icon: ':x:'
    path: test/kth_term_of_linearly_recurrent_sequence.0.test.cpp
    title: test/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - icon: ':x:'
    path: test/log_of_formal_power_series.0.test.cpp
    title: test/log_of_formal_power_series.0.test.cpp
  - icon: ':x:'
    path: test/polynomial_taylor_shift.0.test.cpp
    title: test/polynomial_taylor_shift.0.test.cpp
  - icon: ':x:'
    path: test/pow_of_formal_power_series.0.test.cpp
    title: test/pow_of_formal_power_series.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"semi_relaxed_conv.hpp\"\n\n#line 2 \"fft.hpp\"\n\n#include\
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
    \    return convolution_fft(a, b);\n}\n#line 5 \"semi_relaxed_conv.hpp\"\n#include\
    \ <type_traits>\n#include <utility>\n#line 8 \"semi_relaxed_conv.hpp\"\n\n// returns\
    \ coefficients generated by closure\n// closure: gen(index, current_product)\n\
    template <typename Tp, typename Closure>\ninline std::enable_if_t<std::is_invocable_r_v<Tp,\
    \ Closure, int, const std::vector<Tp> &>,\n                        std::vector<Tp>>\n\
    semi_relaxed_convolution(const std::vector<Tp> &A, Closure gen, int n) {\n   \
    \ enum { BaseCaseSize = 32 };\n    static_assert((BaseCaseSize & (BaseCaseSize\
    \ - 1)) == 0);\n\n    static const int Block[]     = {16, 16, 16, 16, 16};\n \
    \   static const int BlockSize[] = {\n        BaseCaseSize,\n        BaseCaseSize\
    \ * Block[0],\n        BaseCaseSize * Block[0] * Block[1],\n        BaseCaseSize\
    \ * Block[0] * Block[1] * Block[2],\n        BaseCaseSize * Block[0] * Block[1]\
    \ * Block[2] * Block[3],\n        BaseCaseSize * Block[0] * Block[1] * Block[2]\
    \ * Block[3] * Block[4],\n    };\n\n    // returns (which_block, level)\n    auto\
    \ blockinfo = [](int ind) {\n        int i = ind / BaseCaseSize, lv = 0;\n   \
    \     while ((i & (Block[lv] - 1)) == 0) i /= Block[lv++];\n        return std::make_pair(i\
    \ & (Block[lv] - 1), lv);\n    };\n\n    std::vector<Tp> B(n), AB(n);\n    std::vector<std::vector<std::vector<Tp>>>\
    \ dftA, dftB;\n\n    for (int i = 0; i < n; ++i) {\n        const int s = i &\
    \ (BaseCaseSize - 1);\n\n        // blocked contribution\n        if (i >= BaseCaseSize\
    \ && s == 0) {\n            const auto [j, lv]  = blockinfo(i);\n            const\
    \ int blocksize = BlockSize[lv];\n\n            if (blocksize * j == i) {\n  \
    \              if ((int)dftA.size() == lv) {\n                    dftA.emplace_back();\n\
    \                    dftB.emplace_back(Block[lv] - 1);\n                }\n  \
    \              if ((j - 1) * blocksize < (int)A.size()) {\n                  \
    \  dftA[lv]\n                        .emplace_back(A.begin() + (j - 1) * blocksize,\n\
    \                                      A.begin() + std::min((j + 1) * blocksize,\
    \ (int)A.size()))\n                        .resize(blocksize * 2);\n         \
    \           fft(dftA[lv][j - 1]);\n                } else {\n                \
    \    dftA[lv].emplace_back(blocksize * 2);\n                }\n            }\n\
    \n            dftB[lv][j - 1].resize(blocksize * 2);\n            std::copy_n(B.begin()\
    \ + (i - blocksize), blocksize, dftB[lv][j - 1].begin());\n            std::fill_n(dftB[lv][j\
    \ - 1].begin() + blocksize, blocksize, Tp());\n            fft(dftB[lv][j - 1]);\n\
    \n            // middle product\n            std::vector<Tp> mp(blocksize * 2);\n\
    \            for (int k = 0; k < j; ++k)\n                for (int l = 0; l <\
    \ blocksize * 2; ++l)\n                    mp[l] += dftA[lv][j - 1 - k][l] * dftB[lv][k][l];\n\
    \            inv_fft(mp);\n\n            for (int k = 0; k < blocksize && i +\
    \ k < n; ++k) AB[i + k] += mp[k + blocksize];\n        }\n\n        // basecase\
    \ contribution\n        for (int j = std::max(i - s, i - (int)A.size() + 1); j\
    \ < i; ++j) AB[i] += A[i - j] * B[j];\n        B[i] = gen(i, AB);\n        if\
    \ (!A.empty()) AB[i] += A[0] * B[i];\n    }\n\n    return B;\n}\n"
  code: "#pragma once\n\n#include \"fft.hpp\"\n#include <algorithm>\n#include <type_traits>\n\
    #include <utility>\n#include <vector>\n\n// returns coefficients generated by\
    \ closure\n// closure: gen(index, current_product)\ntemplate <typename Tp, typename\
    \ Closure>\ninline std::enable_if_t<std::is_invocable_r_v<Tp, Closure, int, const\
    \ std::vector<Tp> &>,\n                        std::vector<Tp>>\nsemi_relaxed_convolution(const\
    \ std::vector<Tp> &A, Closure gen, int n) {\n    enum { BaseCaseSize = 32 };\n\
    \    static_assert((BaseCaseSize & (BaseCaseSize - 1)) == 0);\n\n    static const\
    \ int Block[]     = {16, 16, 16, 16, 16};\n    static const int BlockSize[] =\
    \ {\n        BaseCaseSize,\n        BaseCaseSize * Block[0],\n        BaseCaseSize\
    \ * Block[0] * Block[1],\n        BaseCaseSize * Block[0] * Block[1] * Block[2],\n\
    \        BaseCaseSize * Block[0] * Block[1] * Block[2] * Block[3],\n        BaseCaseSize\
    \ * Block[0] * Block[1] * Block[2] * Block[3] * Block[4],\n    };\n\n    // returns\
    \ (which_block, level)\n    auto blockinfo = [](int ind) {\n        int i = ind\
    \ / BaseCaseSize, lv = 0;\n        while ((i & (Block[lv] - 1)) == 0) i /= Block[lv++];\n\
    \        return std::make_pair(i & (Block[lv] - 1), lv);\n    };\n\n    std::vector<Tp>\
    \ B(n), AB(n);\n    std::vector<std::vector<std::vector<Tp>>> dftA, dftB;\n\n\
    \    for (int i = 0; i < n; ++i) {\n        const int s = i & (BaseCaseSize -\
    \ 1);\n\n        // blocked contribution\n        if (i >= BaseCaseSize && s ==\
    \ 0) {\n            const auto [j, lv]  = blockinfo(i);\n            const int\
    \ blocksize = BlockSize[lv];\n\n            if (blocksize * j == i) {\n      \
    \          if ((int)dftA.size() == lv) {\n                    dftA.emplace_back();\n\
    \                    dftB.emplace_back(Block[lv] - 1);\n                }\n  \
    \              if ((j - 1) * blocksize < (int)A.size()) {\n                  \
    \  dftA[lv]\n                        .emplace_back(A.begin() + (j - 1) * blocksize,\n\
    \                                      A.begin() + std::min((j + 1) * blocksize,\
    \ (int)A.size()))\n                        .resize(blocksize * 2);\n         \
    \           fft(dftA[lv][j - 1]);\n                } else {\n                \
    \    dftA[lv].emplace_back(blocksize * 2);\n                }\n            }\n\
    \n            dftB[lv][j - 1].resize(blocksize * 2);\n            std::copy_n(B.begin()\
    \ + (i - blocksize), blocksize, dftB[lv][j - 1].begin());\n            std::fill_n(dftB[lv][j\
    \ - 1].begin() + blocksize, blocksize, Tp());\n            fft(dftB[lv][j - 1]);\n\
    \n            // middle product\n            std::vector<Tp> mp(blocksize * 2);\n\
    \            for (int k = 0; k < j; ++k)\n                for (int l = 0; l <\
    \ blocksize * 2; ++l)\n                    mp[l] += dftA[lv][j - 1 - k][l] * dftB[lv][k][l];\n\
    \            inv_fft(mp);\n\n            for (int k = 0; k < blocksize && i +\
    \ k < n; ++k) AB[i + k] += mp[k + blocksize];\n        }\n\n        // basecase\
    \ contribution\n        for (int j = std::max(i - s, i - (int)A.size() + 1); j\
    \ < i; ++j) AB[i] += A[i - j] * B[j];\n        B[i] = gen(i, AB);\n        if\
    \ (!A.empty()) AB[i] += A[0] * B[i];\n    }\n\n    return B;\n}\n"
  dependsOn:
  - fft.hpp
  isVerificationFile: false
  path: semi_relaxed_conv.hpp
  requiredBy:
  - eulerian_number.hpp
  - fps_basic.hpp
  - fps_composition.hpp
  - poly_basic.hpp
  - c_recursive.hpp
  timestamp: '2024-05-17 19:15:49+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - test/inv_of_formal_power_series.0.test.cpp
  - test/compositional_inverse_of_formal_power_series_large.0.test.cpp
  - test/division_of_polynomials.0.test.cpp
  - test/log_of_formal_power_series.0.test.cpp
  - test/pow_of_formal_power_series.0.test.cpp
  - test/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
  - test/exp_of_formal_power_series.0.test.cpp
  - test/composition_of_formal_power_series_large.0.test.cpp
  - test/polynomial_taylor_shift.0.test.cpp
documentation_of: semi_relaxed_conv.hpp
layout: document
redirect_from:
- /library/semi_relaxed_conv.hpp
- /library/semi_relaxed_conv.hpp.html
title: semi_relaxed_conv.hpp
---
