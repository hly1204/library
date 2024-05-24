---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
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
    path: test/convolution_mod.0.test.cpp
    title: test/convolution_mod.0.test.cpp
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
    path: test/polynomial_taylor_shift.0.test.cpp
    title: test/polynomial_taylor_shift.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/pow_of_formal_power_series.0.test.cpp
    title: test/pow_of_formal_power_series.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
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
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/multipoint_evaluation.0.test.cpp
  - test/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - test/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
  - test/convolution_mod.0.test.cpp
  - test/inv_of_formal_power_series.0.test.cpp
  - test/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - test/compositional_inverse_of_formal_power_series_large.0.test.cpp
  - test/division_of_polynomials.0.test.cpp
  - test/polynomial_interpolation.0.test.cpp
  - test/log_of_formal_power_series.0.test.cpp
  - test/pow_of_formal_power_series.0.test.cpp
  - test/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
  - test/exp_of_formal_power_series.0.test.cpp
  - test/composition_of_formal_power_series_large.0.test.cpp
  - test/polynomial_taylor_shift.0.test.cpp
documentation_of: modint.hpp
layout: document
redirect_from:
- /library/modint.hpp
- /library/modint.hpp.html
title: modint.hpp
---