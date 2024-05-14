---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"poly_interpolation.hpp\"\n\n#include <cassert>\n#include\
    \ <vector>\n\ntemplate <typename Tp>\nstd::vector<Tp> lagrange_interpolation_naive(const\
    \ std::vector<Tp> &x, const std::vector<Tp> &y) {\n    assert(x.size() == y.size());\n\
    \    const int n = x.size();\n    std::vector<Tp> M(n + 1), xx(n), f(n);\n   \
    \ M[0] = 1;\n    for (int i = 0; i < n; ++i)\n        for (int j = i; j >= 0;\
    \ --j) M[j + 1] += M[j], M[j] *= -x[i];\n    for (int i = n - 1; i >= 0; --i)\n\
    \        for (int j = 0; j < n; ++j) xx[j] = xx[j] * x[j] + M[i + 1] * (i + 1);\n\
    \    for (int i = 0; i < n; ++i) {\n        Tp t = y[i] / xx[i], k = M[n];\n \
    \       for (int j = n - 1; j >= 0; --j) f[j] += k * t, k = M[j] + k * x[i];\n\
    \    }\n    return f;\n}\n"
  code: "#pragma once\n\n#include <cassert>\n#include <vector>\n\ntemplate <typename\
    \ Tp>\nstd::vector<Tp> lagrange_interpolation_naive(const std::vector<Tp> &x,\
    \ const std::vector<Tp> &y) {\n    assert(x.size() == y.size());\n    const int\
    \ n = x.size();\n    std::vector<Tp> M(n + 1), xx(n), f(n);\n    M[0] = 1;\n \
    \   for (int i = 0; i < n; ++i)\n        for (int j = i; j >= 0; --j) M[j + 1]\
    \ += M[j], M[j] *= -x[i];\n    for (int i = n - 1; i >= 0; --i)\n        for (int\
    \ j = 0; j < n; ++j) xx[j] = xx[j] * x[j] + M[i + 1] * (i + 1);\n    for (int\
    \ i = 0; i < n; ++i) {\n        Tp t = y[i] / xx[i], k = M[n];\n        for (int\
    \ j = n - 1; j >= 0; --j) f[j] += k * t, k = M[j] + k * x[i];\n    }\n    return\
    \ f;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: poly_interpolation.hpp
  requiredBy: []
  timestamp: '2024-05-15 00:00:04+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: poly_interpolation.hpp
layout: document
redirect_from:
- /library/poly_interpolation.hpp
- /library/poly_interpolation.hpp.html
title: poly_interpolation.hpp
---
