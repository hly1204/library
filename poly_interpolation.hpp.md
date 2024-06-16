---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: batch_inv.hpp
    title: batch_inv.hpp
  - icon: ':heavy_check_mark:'
    path: binomial.hpp
    title: binomial.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"poly_interpolation.hpp\"\n\n#line 2 \"batch_inv.hpp\"\n\n\
    #include <cassert>\n#include <vector>\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ batch_inv(const std::vector<Tp> &a) {\n    if (a.empty()) return {};\n    const\
    \ int n = a.size();\n    std::vector<Tp> b(n);\n    Tp v = 1;\n    for (int i\
    \ = 0; i < n; ++i) b[i] = v, v *= a[i];\n    assert(v != 0);\n    v = v.inv();\n\
    \    for (int i = n - 1; i >= 0; --i) b[i] *= v, v *= a[i];\n    return b;\n}\n\
    #line 2 \"binomial.hpp\"\n\n#include <algorithm>\n#line 5 \"binomial.hpp\"\n\n\
    template <typename Tp>\nclass Binomial {\n    std::vector<Tp> factorial_, invfactorial_;\n\
    \n    Binomial() : factorial_{Tp(1)}, invfactorial_{Tp(1)} {}\n\n    void preprocess(int\
    \ n) {\n        if (const int nn = factorial_.size(); nn < n) {\n            int\
    \ k = nn;\n            while (k < n) k *= 2;\n            k = std::min<long long>(k,\
    \ Tp::mod());\n            factorial_.resize(k);\n            invfactorial_.resize(k);\n\
    \            for (int i = nn; i < k; ++i) factorial_[i] = factorial_[i - 1] *\
    \ i;\n            invfactorial_.back() = factorial_.back().inv();\n          \
    \  for (int i = k - 2; i >= nn; --i) invfactorial_[i] = invfactorial_[i + 1] *\
    \ (i + 1);\n        }\n    }\n\npublic:\n    static const Binomial &get(int n)\
    \ {\n        static Binomial bin;\n        bin.preprocess(n);\n        return\
    \ bin;\n    }\n\n    Tp binom(int n, int m) const {\n        return n < m ? Tp()\
    \ : factorial_[n] * invfactorial_[m] * invfactorial_[n - m];\n    }\n    Tp inv(int\
    \ n) const { return factorial_[n - 1] * invfactorial_[n]; }\n    Tp factorial(int\
    \ n) const { return factorial_[n]; }\n    Tp inv_factorial(int n) const { return\
    \ invfactorial_[n]; }\n};\n#line 7 \"poly_interpolation.hpp\"\n\n// returns f\n\
    // x: x_0,...\n// y: f(x_0),...\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ lagrange_interpolation_naive(const std::vector<Tp> &x,\n                   \
    \                                 const std::vector<Tp> &y) {\n    assert(x.size()\
    \ == y.size());\n    const int n = x.size();\n    std::vector<Tp> M(n + 1), xx(n),\
    \ f(n);\n    M[0] = 1;\n    for (int i = 0; i < n; ++i)\n        for (int j =\
    \ i; j >= 0; --j) M[j + 1] += M[j], M[j] *= -x[i];\n    for (int i = n - 1; i\
    \ >= 0; --i)\n        for (int j = 0; j < n; ++j) xx[j] = xx[j] * x[j] + M[i +\
    \ 1] * (i + 1);\n    xx = batch_inv(xx);\n    for (int i = 0; i < n; ++i) {\n\
    \        Tp t = y[i] * xx[i], k = M[n];\n        for (int j = n - 1; j >= 0; --j)\
    \ f[j] += k * t, k = M[j] + k * x[i];\n    }\n    return f;\n}\n\n// returns f(c)\n\
    // f: polynomial f -> f[0]=f(0),...\ntemplate <typename Tp>\ninline Tp lagrange_interpolation_iota(const\
    \ std::vector<Tp> &f, Tp c) {\n    if (f.empty()) return 0;\n    const int n =\
    \ f.size();\n    auto &&bin  = Binomial<Tp>::get(n);\n    std::vector<Tp> k(n);\n\
    \    k[0] = f[0];\n    Tp v = 1;\n    for (int i = 1; i < n; ++i) k[i] = f[i]\
    \ * (v *= (c - (i - 1)) * bin.inv(i));\n    Tp res = k[n - 1];\n    v      = 1;\n\
    \    for (int i = n - 2; i >= 0; --i) res += k[i] * (v *= -(c - (i + 1)) * bin.inv(n\
    \ - 1 - i));\n    return res;\n}\n"
  code: "#pragma once\n\n#include \"batch_inv.hpp\"\n#include \"binomial.hpp\"\n#include\
    \ <cassert>\n#include <vector>\n\n// returns f\n// x: x_0,...\n// y: f(x_0),...\n\
    template <typename Tp>\ninline std::vector<Tp> lagrange_interpolation_naive(const\
    \ std::vector<Tp> &x,\n                                                    const\
    \ std::vector<Tp> &y) {\n    assert(x.size() == y.size());\n    const int n =\
    \ x.size();\n    std::vector<Tp> M(n + 1), xx(n), f(n);\n    M[0] = 1;\n    for\
    \ (int i = 0; i < n; ++i)\n        for (int j = i; j >= 0; --j) M[j + 1] += M[j],\
    \ M[j] *= -x[i];\n    for (int i = n - 1; i >= 0; --i)\n        for (int j = 0;\
    \ j < n; ++j) xx[j] = xx[j] * x[j] + M[i + 1] * (i + 1);\n    xx = batch_inv(xx);\n\
    \    for (int i = 0; i < n; ++i) {\n        Tp t = y[i] * xx[i], k = M[n];\n \
    \       for (int j = n - 1; j >= 0; --j) f[j] += k * t, k = M[j] + k * x[i];\n\
    \    }\n    return f;\n}\n\n// returns f(c)\n// f: polynomial f -> f[0]=f(0),...\n\
    template <typename Tp>\ninline Tp lagrange_interpolation_iota(const std::vector<Tp>\
    \ &f, Tp c) {\n    if (f.empty()) return 0;\n    const int n = f.size();\n   \
    \ auto &&bin  = Binomial<Tp>::get(n);\n    std::vector<Tp> k(n);\n    k[0] = f[0];\n\
    \    Tp v = 1;\n    for (int i = 1; i < n; ++i) k[i] = f[i] * (v *= (c - (i -\
    \ 1)) * bin.inv(i));\n    Tp res = k[n - 1];\n    v      = 1;\n    for (int i\
    \ = n - 2; i >= 0; --i) res += k[i] * (v *= -(c - (i + 1)) * bin.inv(n - 1 - i));\n\
    \    return res;\n}\n"
  dependsOn:
  - batch_inv.hpp
  - binomial.hpp
  isVerificationFile: false
  path: poly_interpolation.hpp
  requiredBy: []
  timestamp: '2024-06-16 14:16:14+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: poly_interpolation.hpp
layout: document
redirect_from:
- /library/poly_interpolation.hpp
- /library/poly_interpolation.hpp.html
title: poly_interpolation.hpp
---