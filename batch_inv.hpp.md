---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: czt.hpp
    title: Chirp Z Transform
  - icon: ':heavy_check_mark:'
    path: poly_interpolation.hpp
    title: Polynomial Interpolation (Lagrange Interpolation)
  - icon: ':warning:'
    path: poly_interpolation_with_error.hpp
    title: poly_interpolation_with_error.hpp
  - icon: ':heavy_check_mark:'
    path: shift_sample_points.hpp
    title: Shift Sample Points
  - icon: ':heavy_check_mark:'
    path: subproduct_tree.hpp
    title: Subproduct Tree
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/enumerative_combinatorics/factorial.0.test.cpp
    title: test/enumerative_combinatorics/factorial.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
    title: test/formal_power_series/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
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
    path: test/formal_power_series/shift_of_sampling_points_of_polynomial.1.test.cpp
    title: test/formal_power_series/shift_of_sampling_points_of_polynomial.1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"batch_inv.hpp\"\n\n#include <cassert>\n#include <vector>\n\
    \ntemplate<typename Tp> inline std::vector<Tp> batch_inv(const std::vector<Tp>\
    \ &a) {\n    if (a.empty()) return {};\n    const int n = a.size();\n    std::vector<Tp>\
    \ b(n);\n    Tp v = 1;\n    for (int i = 0; i < n; ++i) b[i] = v, v *= a[i];\n\
    \    assert(v != 0);\n    v = v.inv();\n    for (int i = n - 1; i >= 0; --i) b[i]\
    \ *= v, v *= a[i];\n    return b;\n}\n"
  code: "#pragma once\n\n#include <cassert>\n#include <vector>\n\ntemplate<typename\
    \ Tp> inline std::vector<Tp> batch_inv(const std::vector<Tp> &a) {\n    if (a.empty())\
    \ return {};\n    const int n = a.size();\n    std::vector<Tp> b(n);\n    Tp v\
    \ = 1;\n    for (int i = 0; i < n; ++i) b[i] = v, v *= a[i];\n    assert(v !=\
    \ 0);\n    v = v.inv();\n    for (int i = n - 1; i >= 0; --i) b[i] *= v, v *=\
    \ a[i];\n    return b;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: batch_inv.hpp
  requiredBy:
  - shift_sample_points.hpp
  - subproduct_tree.hpp
  - poly_interpolation.hpp
  - czt.hpp
  - poly_interpolation_with_error.hpp
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/formal_power_series/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
  - test/formal_power_series/multipoint_evaluation.0.test.cpp
  - test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  - test/formal_power_series/polynomial_interpolation.0.test.cpp
  - test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - test/formal_power_series/shift_of_sampling_points_of_polynomial.1.test.cpp
  - test/enumerative_combinatorics/factorial.0.test.cpp
documentation_of: batch_inv.hpp
layout: document
redirect_from:
- /library/batch_inv.hpp
- /library/batch_inv.hpp.html
title: batch_inv.hpp
---
