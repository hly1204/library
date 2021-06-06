---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/fps_basic.hpp
    title: "basic operations of formal power series / \u5F62\u5F0F\u5E42\u7EA7\u6570\
      \u7684\u57FA\u672C\u64CD\u4F5C"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/linearly_recurrent_sequence.hpp
    title: "linearly recurrent sequence / \u5E38\u7CFB\u6570\u7EBF\u6027\u9012\u63A8\
      \u5E8F\u5217"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.0.test.cpp
    title: remote_test/yosupo/math/convolution_mod.0.test.cpp
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
    path: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
    links: []
  bundledCode: "#line 1 \"traits/modint.hpp\"\n\n\n\nnamespace lib {\n\ntemplate <typename\
    \ mod_t> struct modint_traits {\n  using type = typename mod_t::value_type;\n\
    \  static constexpr type get_mod() { return mod_t::get_mod(); }\n  static constexpr\
    \ type get_primitive_root_prime() { return mod_t::get_primitive_root_prime();\
    \ }\n};\n\n} // namespace lib\n\n/**\n * @brief modint traits / \u53D6\u6A21\u7C7B\
    \u8403\u53D6\n *\n */\n\n\n"
  code: "#ifndef MODINT_TRAITS_HEADER_HPP\n#define MODINT_TRAITS_HEADER_HPP\n\nnamespace\
    \ lib {\n\ntemplate <typename mod_t> struct modint_traits {\n  using type = typename\
    \ mod_t::value_type;\n  static constexpr type get_mod() { return mod_t::get_mod();\
    \ }\n  static constexpr type get_primitive_root_prime() { return mod_t::get_primitive_root_prime();\
    \ }\n};\n\n} // namespace lib\n\n/**\n * @brief modint traits / \u53D6\u6A21\u7C7B\
    \u8403\u53D6\n *\n */\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: traits/modint.hpp
  requiredBy:
  - math/formal_power_series/radix_2_NTT.hpp
  - math/formal_power_series/fps_basic.hpp
  - math/formal_power_series/linearly_recurrent_sequence.hpp
  timestamp: '2021-06-06 20:47:15+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/convolution_mod.0.test.cpp
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
documentation_of: traits/modint.hpp
layout: document
redirect_from:
- /library/traits/modint.hpp
- /library/traits/modint.hpp.html
title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
---
