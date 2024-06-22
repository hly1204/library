---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structure/point_set_range_composite.0.test.cpp
    title: test/data_structure/point_set_range_composite.0.test.cpp
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
    path: test/formal_power_series/shift_of_sampling_points_of_polynomial.0.test.cpp
    title: test/formal_power_series/shift_of_sampling_points_of_polynomial.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
    title: test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/characteristic_polynomial.0.test.cpp
    title: test/matrix/characteristic_polynomial.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/inverse_matrix.0.test.cpp
    title: test/matrix/inverse_matrix.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/matrix_det.0.test.cpp
    title: test/matrix/matrix_det.0.test.cpp
  - icon: ':x:'
    path: test/matrix/matrix_product.0.test.cpp
    title: test/matrix/matrix_product.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"modint.hpp\"\n\n#include <iostream>\n#include <type_traits>\n\
    \ntemplate <unsigned Mod>\nclass ModInt {\n    static_assert((Mod >> 31) == 0,\
    \ \"`Mod` must less than 2^(31)\");\n    template <typename Int>\n    static std::enable_if_t<std::is_integral_v<Int>,\
    \ unsigned> safe_mod(Int v) {\n        using D = std::common_type_t<Int, unsigned>;\n\
    \        return (v %= (int)Mod) < 0 ? (D)(v + (int)Mod) : (D)v;\n    }\n\n   \
    \ struct PrivateConstructor {};\n    static inline PrivateConstructor private_constructor{};\n\
    \    ModInt(PrivateConstructor, unsigned v) : v_(v) {}\n\n    unsigned v_;\n\n\
    public:\n    static unsigned mod() { return Mod; }\n    static ModInt from_raw(unsigned\
    \ v) { return ModInt(private_constructor, v); }\n    ModInt() : v_() {}\n    template\
    \ <typename Int, typename std::enable_if_t<std::is_signed_v<Int>, int> = 0>\n\
    \    ModInt(Int v) : v_(safe_mod(v)) {}\n    template <typename Int, typename\
    \ std::enable_if_t<std::is_unsigned_v<Int>, int> = 0>\n    ModInt(Int v) : v_(v\
    \ % Mod) {}\n    unsigned val() const { return v_; }\n\n    ModInt operator-()\
    \ const { return from_raw(v_ == 0 ? v_ : Mod - v_); }\n    ModInt pow(long long\
    \ e) const {\n        if (e < 0) return inv().pow(-e);\n        for (ModInt x(*this),\
    \ res(from_raw(1));; x *= x) {\n            if (e & 1) res *= x;\n           \
    \ if ((e >>= 1) == 0) return res;\n        }\n    }\n    ModInt inv() const {\n\
    \        int x1 = 1, x3 = 0, a = val(), b = Mod;\n        while (b) {\n      \
    \      int q = a / b, x1_old = x1, a_old = a;\n            x1 = x3, x3 = x1_old\
    \ - x3 * q, a = b, b = a_old - b * q;\n        }\n        return from_raw(x1 <\
    \ 0 ? x1 + (int)Mod : x1);\n    }\n    template <bool Odd = (Mod & 1)>\n    std::enable_if_t<Odd,\
    \ ModInt> div_by_2() const {\n        if (v_ & 1) return from_raw((v_ + Mod) >>\
    \ 1);\n        return from_raw(v_ >> 1);\n    }\n\n    ModInt &operator+=(const\
    \ ModInt &a) {\n        if ((v_ += a.v_) >= Mod) v_ -= Mod;\n        return *this;\n\
    \    }\n    ModInt &operator-=(const ModInt &a) {\n        if ((v_ += Mod - a.v_)\
    \ >= Mod) v_ -= Mod;\n        return *this;\n    }\n    ModInt &operator*=(const\
    \ ModInt &a) {\n        v_ = (unsigned long long)v_ * a.v_ % Mod;\n        return\
    \ *this;\n    }\n    ModInt &operator/=(const ModInt &a) { return *this *= a.inv();\
    \ }\n\n    friend ModInt operator+(const ModInt &a, const ModInt &b) { return\
    \ ModInt(a) += b; }\n    friend ModInt operator-(const ModInt &a, const ModInt\
    \ &b) { return ModInt(a) -= b; }\n    friend ModInt operator*(const ModInt &a,\
    \ const ModInt &b) { return ModInt(a) *= b; }\n    friend ModInt operator/(const\
    \ ModInt &a, const ModInt &b) { return ModInt(a) /= b; }\n    friend bool operator==(const\
    \ ModInt &a, const ModInt &b) { return a.v_ == b.v_; }\n    friend bool operator!=(const\
    \ ModInt &a, const ModInt &b) { return a.v_ != b.v_; }\n    friend std::istream\
    \ &operator>>(std::istream &a, ModInt &b) {\n        int v;\n        a >> v;\n\
    \        b.v_ = safe_mod(v);\n        return a;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &a, const ModInt &b) { return a << b.val(); }\n};\n"
  code: "#pragma once\n\n#include <iostream>\n#include <type_traits>\n\ntemplate <unsigned\
    \ Mod>\nclass ModInt {\n    static_assert((Mod >> 31) == 0, \"`Mod` must less\
    \ than 2^(31)\");\n    template <typename Int>\n    static std::enable_if_t<std::is_integral_v<Int>,\
    \ unsigned> safe_mod(Int v) {\n        using D = std::common_type_t<Int, unsigned>;\n\
    \        return (v %= (int)Mod) < 0 ? (D)(v + (int)Mod) : (D)v;\n    }\n\n   \
    \ struct PrivateConstructor {};\n    static inline PrivateConstructor private_constructor{};\n\
    \    ModInt(PrivateConstructor, unsigned v) : v_(v) {}\n\n    unsigned v_;\n\n\
    public:\n    static unsigned mod() { return Mod; }\n    static ModInt from_raw(unsigned\
    \ v) { return ModInt(private_constructor, v); }\n    ModInt() : v_() {}\n    template\
    \ <typename Int, typename std::enable_if_t<std::is_signed_v<Int>, int> = 0>\n\
    \    ModInt(Int v) : v_(safe_mod(v)) {}\n    template <typename Int, typename\
    \ std::enable_if_t<std::is_unsigned_v<Int>, int> = 0>\n    ModInt(Int v) : v_(v\
    \ % Mod) {}\n    unsigned val() const { return v_; }\n\n    ModInt operator-()\
    \ const { return from_raw(v_ == 0 ? v_ : Mod - v_); }\n    ModInt pow(long long\
    \ e) const {\n        if (e < 0) return inv().pow(-e);\n        for (ModInt x(*this),\
    \ res(from_raw(1));; x *= x) {\n            if (e & 1) res *= x;\n           \
    \ if ((e >>= 1) == 0) return res;\n        }\n    }\n    ModInt inv() const {\n\
    \        int x1 = 1, x3 = 0, a = val(), b = Mod;\n        while (b) {\n      \
    \      int q = a / b, x1_old = x1, a_old = a;\n            x1 = x3, x3 = x1_old\
    \ - x3 * q, a = b, b = a_old - b * q;\n        }\n        return from_raw(x1 <\
    \ 0 ? x1 + (int)Mod : x1);\n    }\n    template <bool Odd = (Mod & 1)>\n    std::enable_if_t<Odd,\
    \ ModInt> div_by_2() const {\n        if (v_ & 1) return from_raw((v_ + Mod) >>\
    \ 1);\n        return from_raw(v_ >> 1);\n    }\n\n    ModInt &operator+=(const\
    \ ModInt &a) {\n        if ((v_ += a.v_) >= Mod) v_ -= Mod;\n        return *this;\n\
    \    }\n    ModInt &operator-=(const ModInt &a) {\n        if ((v_ += Mod - a.v_)\
    \ >= Mod) v_ -= Mod;\n        return *this;\n    }\n    ModInt &operator*=(const\
    \ ModInt &a) {\n        v_ = (unsigned long long)v_ * a.v_ % Mod;\n        return\
    \ *this;\n    }\n    ModInt &operator/=(const ModInt &a) { return *this *= a.inv();\
    \ }\n\n    friend ModInt operator+(const ModInt &a, const ModInt &b) { return\
    \ ModInt(a) += b; }\n    friend ModInt operator-(const ModInt &a, const ModInt\
    \ &b) { return ModInt(a) -= b; }\n    friend ModInt operator*(const ModInt &a,\
    \ const ModInt &b) { return ModInt(a) *= b; }\n    friend ModInt operator/(const\
    \ ModInt &a, const ModInt &b) { return ModInt(a) /= b; }\n    friend bool operator==(const\
    \ ModInt &a, const ModInt &b) { return a.v_ == b.v_; }\n    friend bool operator!=(const\
    \ ModInt &a, const ModInt &b) { return a.v_ != b.v_; }\n    friend std::istream\
    \ &operator>>(std::istream &a, ModInt &b) {\n        int v;\n        a >> v;\n\
    \        b.v_ = safe_mod(v);\n        return a;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &a, const ModInt &b) { return a << b.val(); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: modint.hpp
  requiredBy: []
  timestamp: '2024-05-15 00:00:04+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/data_structure/point_set_range_composite.0.test.cpp
  - test/formal_power_series/polynomial_interpolation.0.test.cpp
  - test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - test/formal_power_series/log_of_formal_power_series.0.test.cpp
  - test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  - test/formal_power_series/compositional_inverse_of_formal_power_series_large.0.test.cpp
  - test/formal_power_series/convolution_mod.0.test.cpp
  - test/formal_power_series/exp_of_formal_power_series.0.test.cpp
  - test/formal_power_series/pow_of_formal_power_series.0.test.cpp
  - test/formal_power_series/polynomial_taylor_shift.0.test.cpp
  - test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
  - test/formal_power_series/division_of_polynomials.0.test.cpp
  - test/formal_power_series/inv_of_formal_power_series.0.test.cpp
  - test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - test/formal_power_series/shift_of_sampling_points_of_polynomial.0.test.cpp
  - test/formal_power_series/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
  - test/formal_power_series/multipoint_evaluation.0.test.cpp
  - test/formal_power_series/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
  - test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
  - test/formal_power_series/convolution_mod.1.test.cpp
  - test/matrix/matrix_product.0.test.cpp
  - test/matrix/characteristic_polynomial.0.test.cpp
  - test/matrix/matrix_det.0.test.cpp
  - test/matrix/inverse_matrix.0.test.cpp
documentation_of: modint.hpp
layout: document
redirect_from:
- /library/modint.hpp
- /library/modint.hpp.html
title: modint.hpp
---
