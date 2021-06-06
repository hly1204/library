---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/basic/binary_mul.hpp
    title: "binary multiplication / \u5FEB\u901F\u4E58"
  - icon: ':heavy_check_mark:'
    path: math/basic/exgcd.hpp
    title: "extended Euclidean algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\
      \u6CD5"
  - icon: ':heavy_check_mark:'
    path: traits/base.hpp
    title: "type traits / \u7C7B\u578B\u8403\u53D6"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/modulo/binomial_coefficient_mod.hpp
    title: math/modulo/binomial_coefficient_mod.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
    title: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Chinese remainder theorem / \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/basic/crt.hpp: line 13: unable to process #include in #if / #ifdef / #ifndef\
    \ other than include guards\n"
  code: "/**\n * @brief Chinese remainder theorem / \u4E2D\u56FD\u5269\u4F59\u5B9A\
    \u7406\n *\n */\n\n#ifndef CRT_HEADER_HPP\n#define CRT_HEADER_HPP\n\n#include\
    \ <cassert>\n#include <cstdint>\n#include <vector>\n\n#include \"binary_mul.hpp\"\
    \n#include \"exgcd.hpp\"\n\nnamespace lib {\n\ntemplate <typename T> class CoprimeCRT\
    \ {\npublic:\n  using u64 = std::uint64_t;\n\n  CoprimeCRT() = default;\n\n  CoprimeCRT(const\
    \ std::vector<T> &m) : m_(m), C_(m.size()) {\n    // \u5047\u8BBE m \u6570\u7EC4\
    \u4E2D\u6240\u6709\u5143\u7D20\u7684\u4E58\u79EF\u5728 std::int64_t \u8868\u793A\
    \u8303\u56F4\u5185\n    int n = m_.size();\n    u64 prod = 1;\n    for (int i\
    \ = 0; i < n; ++i) {\n      C_[i] = inv_mod(prod % m_[i], m_[i]);\n      prod\
    \ *= m_[i];\n    }\n  }\n\n  ~CoprimeCRT() = default;\n\n  void set_m(const std::vector<T>\
    \ &m) {\n    m_ = m;\n    int n = m_.size();\n    C_.resize(n);\n    u64 prod\
    \ = 1;\n    for (int i = 0; i < n; ++i) {\n      C_[i] = inv_mod(prod % m_[i],\
    \ m_[i]);\n      prod *= m_[i];\n    }\n  }\n\n  u64 operator()(const std::vector<T>\
    \ &v) const {\n    int n = m_.size();\n    assert(v.size() == n);\n    u64 x =\
    \ 0, prod = 1;\n    for (int i = 0; i < n; ++i) {\n      x += mul_mod(v[i] + m_[i]\
    \ - x % m_[i], C_[i], m_[i]) * prod;\n      prod *= m_[i];\n    }\n    return\
    \ x;\n  }\n\nprivate:\n  std::vector<T> m_, C_;\n};\n\n// TODO\ntemplate <typename\
    \ T> class CRT;\n\n} // namespace lib\n\n#endif"
  dependsOn:
  - math/basic/binary_mul.hpp
  - traits/base.hpp
  - math/basic/exgcd.hpp
  isVerificationFile: false
  path: math/basic/crt.hpp
  requiredBy:
  - math/modulo/binomial_coefficient_mod.hpp
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
documentation_of: math/basic/crt.hpp
layout: document
redirect_from:
- /library/math/basic/crt.hpp
- /library/math/basic/crt.hpp.html
title: "Chinese remainder theorem / \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406"
---
