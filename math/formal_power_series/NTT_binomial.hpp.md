---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/formal_power_series/falling_factorial_polynomial_multiplication.hpp
    title: "falling factorial polynomial multiplication / \u4E0B\u964D\u5E42\u591A\
      \u9879\u5F0F\u4E58\u6CD5"
  - icon: ':question:'
    path: math/formal_power_series/formal_power_series.hpp
    title: "basic operations of formal power series / \u5F62\u5F0F\u5E42\u7EA7\u6570\
      \u7684\u57FA\u672C\u64CD\u4F5C"
  - icon: ':question:'
    path: math/formal_power_series/polynomial.hpp
    title: "polynomial / \u591A\u9879\u5F0F"
  - icon: ':warning:'
    path: math/formal_power_series/sample_points_shift.hpp
    title: "sample points shift / \u6837\u672C\u70B9\u5E73\u79FB"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.0.test.cpp
    title: remote_test/yosupo/math/convolution_mod.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
    title: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
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
    document_title: "NTT prime binomial / NTT \u7D20\u6570\u7528\u4E8C\u9879\u5F0F\
      \u7CFB\u6570"
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/NTT_binomial.hpp\"\n\n\n\r\n/**\r\
    \n * @brief NTT prime binomial / NTT \u7D20\u6570\u7528\u4E8C\u9879\u5F0F\u7CFB\
    \u6570\r\n *\r\n */\r\n\r\n#include <vector>\r\n\r\nnamespace lib {\r\n\r\ntemplate\
    \ <typename mod_t>\r\nclass NTTBinomial {\r\npublic:\r\n  NTTBinomial(int lim\
    \ = 0) {\r\n    if (fac_.empty()) {\r\n      fac_.emplace_back(1);\r\n      ifac_.emplace_back(1);\r\
    \n    }\r\n    init(lim);\r\n  }\r\n  ~NTTBinomial() = default;\r\n\r\n  /**\r\
    \n   * @brief \u9884\u5904\u7406 [0, n) \u7684\u9636\u4E58\u548C\u5176\u9006\u5143\
    \r\n   */\r\n  static void init(int n) {\r\n    if (int(fac_.size()) < n) {\r\n\
    \      int old_size = fac_.size();\r\n      fac_.resize(n);\r\n      ifac_.resize(n);\r\
    \n      for (int i = old_size; i < n; ++i) fac_[i] = fac_[i - 1] * mod_t(i);\r\
    \n      ifac_.back() = mod_t(1) / fac_.back();\r\n      for (int i = n - 2; i\
    \ >= old_size; --i) ifac_[i] = ifac_[i + 1] * mod_t(i + 1);\r\n    }\r\n  }\r\n\
    \r\n  mod_t fac_unsafe(int n) const { return fac_[n]; }\r\n  mod_t ifac_unsafe(int\
    \ n) const { return ifac_[n]; }\r\n  mod_t inv_unsafe(int n) const { return ifac_[n]\
    \ * fac_[n - 1]; }\r\n  mod_t choose_unsafe(int n, int k) const {\r\n    // \u8FD4\
    \u56DE binom{n}{k} \u6CE8\u610F\u4E0A\u6307\u6807\u53EF\u4EE5\u4E3A\u8D1F\u6570\
    \u4F46\u8FD9\u91CC\u5E76\u672A\u5B9E\u73B0\uFF01\r\n    return n >= k ? fac_[n]\
    \ * ifac_[k] * ifac_[n - k] : mod_t(0);\r\n  }\r\n\r\nprivate:\r\n  static inline\
    \ std::vector<mod_t> fac_, ifac_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef NTT_BINOMIAL_HEADER_HPP\r\n#define NTT_BINOMIAL_HEADER_HPP\r\n\r\n\
    /**\r\n * @brief NTT prime binomial / NTT \u7D20\u6570\u7528\u4E8C\u9879\u5F0F\
    \u7CFB\u6570\r\n *\r\n */\r\n\r\n#include <vector>\r\n\r\nnamespace lib {\r\n\r\
    \ntemplate <typename mod_t>\r\nclass NTTBinomial {\r\npublic:\r\n  NTTBinomial(int\
    \ lim = 0) {\r\n    if (fac_.empty()) {\r\n      fac_.emplace_back(1);\r\n   \
    \   ifac_.emplace_back(1);\r\n    }\r\n    init(lim);\r\n  }\r\n  ~NTTBinomial()\
    \ = default;\r\n\r\n  /**\r\n   * @brief \u9884\u5904\u7406 [0, n) \u7684\u9636\
    \u4E58\u548C\u5176\u9006\u5143\r\n   */\r\n  static void init(int n) {\r\n   \
    \ if (int(fac_.size()) < n) {\r\n      int old_size = fac_.size();\r\n      fac_.resize(n);\r\
    \n      ifac_.resize(n);\r\n      for (int i = old_size; i < n; ++i) fac_[i] =\
    \ fac_[i - 1] * mod_t(i);\r\n      ifac_.back() = mod_t(1) / fac_.back();\r\n\
    \      for (int i = n - 2; i >= old_size; --i) ifac_[i] = ifac_[i + 1] * mod_t(i\
    \ + 1);\r\n    }\r\n  }\r\n\r\n  mod_t fac_unsafe(int n) const { return fac_[n];\
    \ }\r\n  mod_t ifac_unsafe(int n) const { return ifac_[n]; }\r\n  mod_t inv_unsafe(int\
    \ n) const { return ifac_[n] * fac_[n - 1]; }\r\n  mod_t choose_unsafe(int n,\
    \ int k) const {\r\n    // \u8FD4\u56DE binom{n}{k} \u6CE8\u610F\u4E0A\u6307\u6807\
    \u53EF\u4EE5\u4E3A\u8D1F\u6570\u4F46\u8FD9\u91CC\u5E76\u672A\u5B9E\u73B0\uFF01\
    \r\n    return n >= k ? fac_[n] * ifac_[k] * ifac_[n - k] : mod_t(0);\r\n  }\r\
    \n\r\nprivate:\r\n  static inline std::vector<mod_t> fac_, ifac_;\r\n};\r\n\r\n\
    } // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/formal_power_series/NTT_binomial.hpp
  requiredBy:
  - math/formal_power_series/falling_factorial_polynomial_multiplication.hpp
  - math/formal_power_series/polynomial.hpp
  - math/formal_power_series/sample_points_shift.hpp
  - math/formal_power_series/formal_power_series.hpp
  timestamp: '2021-07-17 05:32:32+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
  - remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/convolution_mod.0.test.cpp
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
  - remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
documentation_of: math/formal_power_series/NTT_binomial.hpp
layout: document
redirect_from:
- /library/math/formal_power_series/NTT_binomial.hpp
- /library/math/formal_power_series/NTT_binomial.hpp.html
title: "NTT prime binomial / NTT \u7D20\u6570\u7528\u4E8C\u9879\u5F0F\u7CFB\u6570"
---
