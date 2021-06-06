---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/basic/binary_mul.hpp
    title: "binary multiplication / \u5FEB\u901F\u4E58"
  - icon: ':heavy_check_mark:'
    path: traits/base.hpp
    title: "type traits / \u7C7B\u578B\u8403\u53D6"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/modulo/binomial_coefficient_mod.hpp
    title: "\u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\u6A21"
  - icon: ':heavy_check_mark:'
    path: math/modulo/sqrt_mod.hpp
    title: "\u6A21\u5E73\u65B9\u6839"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
    title: remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
    title: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/mod_sqrt.0.test.cpp
    title: remote_test/yosupo/math/mod_sqrt.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "binary power / \u5FEB\u901F\u5E42"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/basic/binary_pow.hpp: line 12: unable to process #include in #if / #ifdef\
    \ / #ifndef other than include guards\n"
  code: "/**\n * @brief binary power / \u5FEB\u901F\u5E42\n *\n */\n\n#ifndef BINARY_POW_HEADER_HPP\n\
    #define BINARY_POW_HEADER_HPP\n\n#include <cassert>\n#include <type_traits>\n\n\
    #include \"../../traits/base.hpp\"\n#include \"binary_mul.hpp\"\n\nnamespace lib\
    \ {\n\ntemplate <typename T1, typename T2>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2>, T1> pow(T1 x, T2 y) {\n  assert(y >= 0);\n  T1 res\
    \ = 1;\n  for (; y != 0; y >>= 1, x *= x)\n    if (y & 1) res *= x;\n  return\
    \ res;\n}\n\ntemplate <typename T1, typename T2, typename T3>\nstd::enable_if_t<std::is_integral_v<T1>\
    \ && std::is_integral_v<T2> && std::is_integral_v<T3>, T1>\npow_mod(T1 x, T2 y,\
    \ T3 mod) {\n  assert(y >= 0);\n  T1 res = (mod != 1);\n  if constexpr (sizeof(T1)\
    \ < 8) {\n    using S = promote_integral_t<T1>;\n    for (; y != 0; y >>= 1, x\
    \ = static_cast<S>(x) * x % mod)\n      if (y & 1) res = static_cast<S>(res) *\
    \ x % mod;\n  } else {\n    // \u4F7F\u5F97 T1 \u4E3A 64 \u4F4D\u6574\u578B\u65F6\
    \u4E5F\u80FD\u5DE5\u4F5C\n    for (; y != 0; y >>= 1, x = mul_mod(x, x, mod))\n\
    \      if (y & 1) res = mul_mod(res, x, mod);\n  }\n  return res;\n}\n\n} // namespace\
    \ lib\n\n#endif\n"
  dependsOn:
  - traits/base.hpp
  - math/basic/binary_mul.hpp
  isVerificationFile: false
  path: math/basic/binary_pow.hpp
  requiredBy:
  - math/modulo/sqrt_mod.hpp
  - math/modulo/binomial_coefficient_mod.hpp
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  - remote_test/yosupo/math/mod_sqrt.0.test.cpp
  - remote_test/aizuoj/number_theory/binary_pow.0.test.cpp
documentation_of: math/basic/binary_pow.hpp
layout: document
redirect_from:
- /library/math/basic/binary_pow.hpp
- /library/math/basic/binary_pow.hpp.html
title: "binary power / \u5FEB\u901F\u5E42"
---
