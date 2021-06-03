---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: math/formal_power_series/fps_basic.hpp
    title: "\u5F62\u5F0F\u5E42\u7EA7\u6570\u7684\u57FA\u672C\u64CD\u4F5C"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/linearly_recurrent_sequence.hpp
    title: "\u5E38\u7CFB\u6570\u9F50\u6B21\u7EBF\u6027\u9012\u63A8"
  - icon: ':question:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "\u57FA-2 NTT"
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
  - icon: ':x:'
    path: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"traits/modint.hpp\"\n\n\n\nnamespace lib {\n\ntemplate <typename\
    \ mod_t> struct modint_traits {\n  using type = typename mod_t::value_type;\n\
    \  static constexpr type get_mod() { return mod_t::get_mod(); }\n  static constexpr\
    \ type get_primitive_root_prime() { return mod_t::get_primitive_root_prime();\
    \ }\n};\n\n} // namespace lib\n\n\n"
  code: "#ifndef MODINT_TRAITS_HEADER_HPP\n#define MODINT_TRAITS_HEADER_HPP\n\nnamespace\
    \ lib {\n\ntemplate <typename mod_t> struct modint_traits {\n  using type = typename\
    \ mod_t::value_type;\n  static constexpr type get_mod() { return mod_t::get_mod();\
    \ }\n  static constexpr type get_primitive_root_prime() { return mod_t::get_primitive_root_prime();\
    \ }\n};\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: traits/modint.hpp
  requiredBy:
  - math/formal_power_series/radix_2_NTT.hpp
  - math/formal_power_series/fps_basic.hpp
  - math/formal_power_series/linearly_recurrent_sequence.hpp
  timestamp: '2021-06-03 15:01:19+08:00'
  verificationStatus: LIBRARY_SOME_WA
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
title: traits/modint.hpp
---
