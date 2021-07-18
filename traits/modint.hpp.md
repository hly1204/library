---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/arbitrary_modulo_convolution.hpp
    title: "arbitrary modulo convolution / \u4EFB\u610F\u6A21\u6570\u5377\u79EF"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/chirp_z.hpp
    title: "chirp z transform / chirp z \u53D8\u6362"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/convolution.hpp
    title: "convolution / \u5377\u79EF"
  - icon: ':warning:'
    path: math/formal_power_series/falling_factorial_polynomial_multiplication.hpp
    title: "falling factorial polynomial multiplication / \u4E0B\u964D\u5E42\u591A\
      \u9879\u5F0F\u4E58\u6CD5"
  - icon: ':question:'
    path: math/formal_power_series/formal_power_series.hpp
    title: "basic operations of formal power series / \u5F62\u5F0F\u5E42\u7EA7\u6570\
      \u7684\u57FA\u672C\u64CD\u4F5C"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/linearly_recurrent_sequence_Bostan_Mori.hpp
    title: "linearly recurrent sequence Bostan-Mori / \u5E38\u7CFB\u6570\u7EBF\u6027\
      \u9012\u63A8\u5E8F\u5217 Bostan-Mori \u7B97\u6CD5"
  - icon: ':question:'
    path: math/formal_power_series/polynomial.hpp
    title: "polynomial / \u591A\u9879\u5F0F"
  - icon: ':question:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362"
  - icon: ':warning:'
    path: math/formal_power_series/sample_points_shift.hpp
    title: "sample points shift / \u6837\u672C\u70B9\u5E73\u79FB"
  - icon: ':warning:'
    path: math/modulo/factorial_modulo_prime.hpp
    title: "factorial modulo prime / \u9636\u4E58\u6A21\u7D20\u6570"
  - icon: ':warning:'
    path: math/modulo/factorial_modulo_prime.hpp
    title: "factorial modulo prime / \u9636\u4E58\u6A21\u7D20\u6570"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.0.test.cpp
    title: remote_test/yosupo/math/convolution_mod.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.1.test.cpp
    title: remote_test/yosupo/math/convolution_mod.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
    title: remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
    title: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
    title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
    title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
    title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
    title: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
    title: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
    title: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
    links: []
  bundledCode: "#line 1 \"traits/modint.hpp\"\n\n\n\r\n/**\r\n * @brief modint traits\
    \ / \u53D6\u6A21\u7C7B\u8403\u53D6\r\n *\r\n */\r\n\r\nnamespace lib {\r\n\r\n\
    template <typename mod_t>\r\nstruct modint_traits {\r\n  using type = typename\
    \ mod_t::value_type;\r\n  static constexpr type get_mod() { return mod_t::get_mod();\
    \ }\r\n  static constexpr type get_primitive_root_prime() { return mod_t::get_primitive_root_prime();\
    \ }\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef MODINT_TRAITS_HEADER_HPP\r\n#define MODINT_TRAITS_HEADER_HPP\r\n\r\
    \n/**\r\n * @brief modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6\r\n *\r\n */\r\
    \n\r\nnamespace lib {\r\n\r\ntemplate <typename mod_t>\r\nstruct modint_traits\
    \ {\r\n  using type = typename mod_t::value_type;\r\n  static constexpr type get_mod()\
    \ { return mod_t::get_mod(); }\r\n  static constexpr type get_primitive_root_prime()\
    \ { return mod_t::get_primitive_root_prime(); }\r\n};\r\n\r\n} // namespace lib\r\
    \n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: traits/modint.hpp
  requiredBy:
  - math/formal_power_series/radix_2_NTT.hpp
  - math/formal_power_series/convolution.hpp
  - math/formal_power_series/falling_factorial_polynomial_multiplication.hpp
  - math/formal_power_series/chirp_z.hpp
  - math/formal_power_series/arbitrary_modulo_convolution.hpp
  - math/formal_power_series/polynomial.hpp
  - math/formal_power_series/sample_points_shift.hpp
  - math/formal_power_series/linearly_recurrent_sequence_Bostan_Mori.hpp
  - math/formal_power_series/formal_power_series.hpp
  - math/modulo/factorial_modulo_prime.hpp
  - math/modulo/factorial_modulo_prime.hpp
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/convolution_mod_1000000007.0.test.cpp
  - remote_test/yosupo/math/convolution_mod.0.test.cpp
  - remote_test/yosupo/math/convolution_mod.1.test.cpp
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
  - remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
documentation_of: traits/modint.hpp
layout: document
redirect_from:
- /library/traits/modint.hpp
- /library/traits/modint.hpp.html
title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
---
