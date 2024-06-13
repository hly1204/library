---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: c_recursive.hpp
    title: c_recursive.hpp
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
    path: poly_basic.hpp
    title: poly_basic.hpp
  - icon: ':warning:'
    path: poly_interpolation.hpp
    title: poly_interpolation.hpp
  - icon: ':heavy_check_mark:'
    path: subproduct_tree.hpp
    title: subproduct_tree.hpp
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
    path: test/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
    title: test/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/division_of_polynomials.0.test.cpp
    title: test/division_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/exp_of_formal_power_series.0.test.cpp
    title: test/exp_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/inv_of_formal_power_series.0.test.cpp
    title: test/inv_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/kth_term_of_linearly_recurrent_sequence.0.test.cpp
    title: test/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/log_of_formal_power_series.0.test.cpp
    title: test/log_of_formal_power_series.0.test.cpp
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
  - icon: ':heavy_check_mark:'
    path: test/polynomial_taylor_shift.0.test.cpp
    title: test/polynomial_taylor_shift.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/pow_of_formal_power_series.0.test.cpp
    title: test/pow_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/sqrt_of_formal_power_series.0.test.cpp
    title: test/sqrt_of_formal_power_series.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"binomial.hpp\"\n\n#include <algorithm>\n#include <vector>\n\
    \ntemplate <typename Tp>\nclass Binomial {\n    std::vector<Tp> factorial_, invfactorial_;\n\
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
    \ invfactorial_[n]; }\n};\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <vector>\n\ntemplate <typename\
    \ Tp>\nclass Binomial {\n    std::vector<Tp> factorial_, invfactorial_;\n\n  \
    \  Binomial() : factorial_{Tp(1)}, invfactorial_{Tp(1)} {}\n\n    void preprocess(int\
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
    \ invfactorial_[n]; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: binomial.hpp
  requiredBy:
  - eulerian_number.hpp
  - fps_sqrt.hpp
  - poly_interpolation.hpp
  - fps_basic.hpp
  - czt.hpp
  - fps_composition.hpp
  - poly_basic.hpp
  - c_recursive.hpp
  - subproduct_tree.hpp
  timestamp: '2024-05-15 00:00:04+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/multipoint_evaluation.0.test.cpp
  - test/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - test/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
  - test/inv_of_formal_power_series.0.test.cpp
  - test/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - test/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  - test/compositional_inverse_of_formal_power_series_large.0.test.cpp
  - test/division_of_polynomials.0.test.cpp
  - test/sqrt_of_formal_power_series.0.test.cpp
  - test/polynomial_interpolation.0.test.cpp
  - test/log_of_formal_power_series.0.test.cpp
  - test/pow_of_formal_power_series.0.test.cpp
  - test/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
  - test/exp_of_formal_power_series.0.test.cpp
  - test/composition_of_formal_power_series_large.0.test.cpp
  - test/polynomial_taylor_shift.0.test.cpp
documentation_of: binomial.hpp
layout: document
redirect_from:
- /library/binomial.hpp
- /library/binomial.hpp.html
title: binomial.hpp
---
