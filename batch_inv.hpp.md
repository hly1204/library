---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: czt.hpp
    title: czt.hpp
  - icon: ':warning:'
    path: poly_interpolation.hpp
    title: poly_interpolation.hpp
  - icon: ':heavy_check_mark:'
    path: subproduct_tree.hpp
    title: subproduct_tree.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
    title: test/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/convolution_mod.1.test.cpp
    title: test/convolution_mod.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/multipoint_evaluation.0.test.cpp
    title: test/multipoint_evaluation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/multipoint_evaluation_on_geometric_sequence.0.test.cpp
    title: test/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/polynomial_interpolation.0.test.cpp
    title: test/polynomial_interpolation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/polynomial_interpolation_on_geometric_sequence.0.test.cpp
    title: test/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"batch_inv.hpp\"\n\n#include <cassert>\n#include <vector>\n\
    \ntemplate <typename Tp>\ninline std::vector<Tp> batch_inv(const std::vector<Tp>\
    \ &a) {\n    if (a.empty()) return {};\n    const int n = a.size();\n    std::vector<Tp>\
    \ b(n);\n    Tp v = 1;\n    for (int i = 0; i < n; ++i) b[i] = v, v *= a[i];\n\
    \    assert(v != 0);\n    v = v.inv();\n    for (int i = n - 1; i >= 0; --i) b[i]\
    \ *= v, v *= a[i];\n    return b;\n}\n"
  code: "#pragma once\n\n#include <cassert>\n#include <vector>\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> batch_inv(const std::vector<Tp> &a) {\n    if (a.empty())\
    \ return {};\n    const int n = a.size();\n    std::vector<Tp> b(n);\n    Tp v\
    \ = 1;\n    for (int i = 0; i < n; ++i) b[i] = v, v *= a[i];\n    assert(v !=\
    \ 0);\n    v = v.inv();\n    for (int i = n - 1; i >= 0; --i) b[i] *= v, v *=\
    \ a[i];\n    return b;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: batch_inv.hpp
  requiredBy:
  - poly_interpolation.hpp
  - czt.hpp
  - subproduct_tree.hpp
  timestamp: '2024-06-16 14:16:14+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/multipoint_evaluation.0.test.cpp
  - test/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
  - test/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - test/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  - test/polynomial_interpolation.0.test.cpp
  - test/convolution_mod.1.test.cpp
documentation_of: batch_inv.hpp
layout: document
redirect_from:
- /library/batch_inv.hpp
- /library/batch_inv.hpp.html
title: batch_inv.hpp
---
