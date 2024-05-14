---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: chinese_remainder.hpp
    title: chinese_remainder.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/187.0.test.cpp
    title: test/187.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"xgcd.hpp\"\n\n#include <type_traits>\n\ntemplate <typename\
    \ Int>\nstruct XGcdResult {\n    Int x, y, gcd;\n};\n\ntemplate <typename Int>\n\
    inline std::enable_if_t<std::is_signed_v<Int>, XGcdResult<Int>> xgcd(Int a, Int\
    \ b) {\n    Int x11 = 1, x12 = 0, x21 = 0, x22 = 1;\n    while (b) {\n       \
    \ Int q = a / b, x11_old = x11, x12_old = x12, a_old = a;\n        x11 = x21,\
    \ x21 = x11_old - x21 * q;\n        x12 = x22, x22 = x12_old - x22 * q;\n    \
    \    a = b, b = a_old - b * q;\n    }\n    return XGcdResult<Int>{x11, x12, a};\n\
    }\n\ntemplate <typename Int>\nstruct InvGcdResult {\n    Int inv, gcd;\n};\n\n\
    template <typename Int>\ninline std::enable_if_t<std::is_signed_v<Int>, InvGcdResult<Int>>\
    \ inv_gcd(Int a, Int b) {\n    Int x11 = 1, x21 = 0;\n    while (b) {\n      \
    \  Int q = a / b, x11_old = x11, a_old = a;\n        x11 = x21, x21 = x11_old\
    \ - x21 * q;\n        a = b, b = a_old - b * q;\n    }\n    return InvGcdResult<Int>{x11,\
    \ a};\n}\n"
  code: "#pragma once\n\n#include <type_traits>\n\ntemplate <typename Int>\nstruct\
    \ XGcdResult {\n    Int x, y, gcd;\n};\n\ntemplate <typename Int>\ninline std::enable_if_t<std::is_signed_v<Int>,\
    \ XGcdResult<Int>> xgcd(Int a, Int b) {\n    Int x11 = 1, x12 = 0, x21 = 0, x22\
    \ = 1;\n    while (b) {\n        Int q = a / b, x11_old = x11, x12_old = x12,\
    \ a_old = a;\n        x11 = x21, x21 = x11_old - x21 * q;\n        x12 = x22,\
    \ x22 = x12_old - x22 * q;\n        a = b, b = a_old - b * q;\n    }\n    return\
    \ XGcdResult<Int>{x11, x12, a};\n}\n\ntemplate <typename Int>\nstruct InvGcdResult\
    \ {\n    Int inv, gcd;\n};\n\ntemplate <typename Int>\ninline std::enable_if_t<std::is_signed_v<Int>,\
    \ InvGcdResult<Int>> inv_gcd(Int a, Int b) {\n    Int x11 = 1, x21 = 0;\n    while\
    \ (b) {\n        Int q = a / b, x11_old = x11, a_old = a;\n        x11 = x21,\
    \ x21 = x11_old - x21 * q;\n        a = b, b = a_old - b * q;\n    }\n    return\
    \ InvGcdResult<Int>{x11, a};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: xgcd.hpp
  requiredBy:
  - chinese_remainder.hpp
  timestamp: '2024-05-15 00:00:04+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/187.0.test.cpp
documentation_of: xgcd.hpp
layout: document
redirect_from:
- /library/xgcd.hpp
- /library/xgcd.hpp.html
title: xgcd.hpp
---
