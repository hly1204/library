---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: c_recursive.hpp
    title: c_recursive.hpp
  - icon: ':heavy_check_mark:'
    path: conv_mod.hpp
    title: conv_mod.hpp
  - icon: ':heavy_check_mark:'
    path: czt.hpp
    title: czt.hpp
  - icon: ':warning:'
    path: eulerian_number.hpp
    title: eulerian_number.hpp
  - icon: ':heavy_check_mark:'
    path: fps_basic.hpp
    title: fps_basic.hpp
  - icon: ':heavy_check_mark:'
    path: fps_composition.hpp
    title: fps_composition.hpp
  - icon: ':heavy_check_mark:'
    path: fps_sqrt.hpp
    title: fps_sqrt.hpp
  - icon: ':heavy_check_mark:'
    path: middle_product.hpp
    title: middle_product.hpp
  - icon: ':heavy_check_mark:'
    path: poly_basic.hpp
    title: poly_basic.hpp
  - icon: ':heavy_check_mark:'
    path: poly_product.hpp
    title: poly_product.hpp
  - icon: ':heavy_check_mark:'
    path: semi_relaxed_conv.hpp
    title: semi_relaxed_conv.hpp
  - icon: ':heavy_check_mark:'
    path: subproduct_tree.hpp
    title: subproduct_tree.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
    title: test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/compositional_inverse_of_formal_power_series_large.0.test.cpp
    title: test/formal_power_series/compositional_inverse_of_formal_power_series_large.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
    title: test/formal_power_series/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
    title: test/formal_power_series/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/convolution_mod.0.test.cpp
    title: test/formal_power_series/convolution_mod.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/convolution_mod.1.test.cpp
    title: test/formal_power_series/convolution_mod.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/convolution_mod_1000000007.0.test.cpp
    title: test/formal_power_series/convolution_mod_1000000007.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/division_of_polynomials.0.test.cpp
    title: test/formal_power_series/division_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/exp_of_formal_power_series.0.test.cpp
    title: test/formal_power_series/exp_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/inv_of_formal_power_series.0.test.cpp
    title: test/formal_power_series/inv_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
    title: test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/log_of_formal_power_series.0.test.cpp
    title: test/formal_power_series/log_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/multipoint_evaluation.0.test.cpp
    title: test/formal_power_series/multipoint_evaluation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
    title: test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/polynomial_interpolation.0.test.cpp
    title: test/formal_power_series/polynomial_interpolation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
    title: test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/polynomial_taylor_shift.0.test.cpp
    title: test/formal_power_series/polynomial_taylor_shift.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/pow_of_formal_power_series.0.test.cpp
    title: test/formal_power_series/pow_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/product_of_polynomial_sequence.0.test.cpp
    title: test/formal_power_series/product_of_polynomial_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/shift_of_sampling_points_of_polynomial.0.test.cpp
    title: test/formal_power_series/shift_of_sampling_points_of_polynomial.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
    title: test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fft.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <iterator>\n#include <memory>\n#include <vector>\n\ntemplate <typename\
    \ Tp>\nclass FftInfo {\n    static Tp least_quadratic_nonresidue() {\n       \
    \ for (int i = 2;; ++i)\n            if (Tp(i).pow((Tp::mod() - 1) / 2) == -1)\
    \ return Tp(i);\n    }\n\n    const int ordlog2_;\n    const Tp zeta_;\n    const\
    \ Tp invzeta_;\n    const Tp imag_;\n    const Tp invimag_;\n\n    mutable std::vector<Tp>\
    \ root_;\n    mutable std::vector<Tp> invroot_;\n\n    FftInfo()\n        : ordlog2_(__builtin_ctzll(Tp::mod()\
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
    \    return convolution_fft(a, b);\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <iterator>\n\
    #include <memory>\n#include <vector>\n\ntemplate <typename Tp>\nclass FftInfo\
    \ {\n    static Tp least_quadratic_nonresidue() {\n        for (int i = 2;; ++i)\n\
    \            if (Tp(i).pow((Tp::mod() - 1) / 2) == -1) return Tp(i);\n    }\n\n\
    \    const int ordlog2_;\n    const Tp zeta_;\n    const Tp invzeta_;\n    const\
    \ Tp imag_;\n    const Tp invimag_;\n\n    mutable std::vector<Tp> root_;\n  \
    \  mutable std::vector<Tp> invroot_;\n\n    FftInfo()\n        : ordlog2_(__builtin_ctzll(Tp::mod()\
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
    \    return convolution_fft(a, b);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: fft.hpp
  requiredBy:
  - poly_basic.hpp
  - subproduct_tree.hpp
  - semi_relaxed_conv.hpp
  - eulerian_number.hpp
  - c_recursive.hpp
  - middle_product.hpp
  - fps_sqrt.hpp
  - fps_composition.hpp
  - conv_mod.hpp
  - czt.hpp
  - fps_basic.hpp
  - poly_product.hpp
  timestamp: '2024-05-17 19:15:49+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/formal_power_series/compositional_inverse_of_formal_power_series_large.0.test.cpp
  - test/formal_power_series/product_of_polynomial_sequence.0.test.cpp
  - test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
  - test/formal_power_series/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
  - test/formal_power_series/exp_of_formal_power_series.0.test.cpp
  - test/formal_power_series/multipoint_evaluation.0.test.cpp
  - test/formal_power_series/inv_of_formal_power_series.0.test.cpp
  - test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
  - test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - test/formal_power_series/convolution_mod.1.test.cpp
  - test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  - test/formal_power_series/convolution_mod_1000000007.0.test.cpp
  - test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - test/formal_power_series/convolution_mod.0.test.cpp
  - test/formal_power_series/polynomial_interpolation.0.test.cpp
  - test/formal_power_series/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
  - test/formal_power_series/log_of_formal_power_series.0.test.cpp
  - test/formal_power_series/pow_of_formal_power_series.0.test.cpp
  - test/formal_power_series/shift_of_sampling_points_of_polynomial.0.test.cpp
  - test/formal_power_series/polynomial_taylor_shift.0.test.cpp
  - test/formal_power_series/division_of_polynomials.0.test.cpp
documentation_of: fft.hpp
layout: document
redirect_from:
- /library/fft.hpp
- /library/fft.hpp.html
title: fft.hpp
---
