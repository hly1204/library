---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: chinese_remainder.hpp
    title: chinese_remainder.hpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/number_theory/sqrt_mod.0.test.cpp
    title: test/number_theory/sqrt_mod.0.test.cpp
  - icon: ':x:'
    path: test/number_theory/yukicoder187.0.test.cpp
    title: test/number_theory/yukicoder187.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"xgcd.hpp\"\n\n#include <array>\n#include <type_traits>\n\
    #include <utility>\n\n// returns [x, y, gcd(a, b)] s.t. ax+by = gcd(a, b)\ntemplate<typename\
    \ Int>\ninline std::enable_if_t<std::is_signed_v<Int>, std::array<Int, 3>> xgcd(Int\
    \ a, Int b) {\n    Int x11 = 1, x12 = 0, x21 = 0, x22 = 1;\n    while (b) {\n\
    \        std::add_const_t<Int> q = a / b;\n        x11                     = std::exchange(x21,\
    \ x11 - x21 * q);\n        x12                     = std::exchange(x22, x12 -\
    \ x22 * q);\n        a                       = std::exchange(b, a - b * q);\n\
    \    }\n    return {x11, x12, a};\n}\n\n// returns [a^(-1) mod b, gcd(a, b)]\n\
    template<typename Int>\ninline std::enable_if_t<std::is_signed_v<Int>, std::array<Int,\
    \ 2>> inv_gcd(Int a, Int b) {\n    Int x11 = 1, x21 = 0;\n    while (b) {\n  \
    \      std::add_const_t<Int> q = a / b;\n        x11                     = std::exchange(x21,\
    \ x11 - x21 * q);\n        a                       = std::exchange(b, a - b *\
    \ q);\n    }\n    return {x11, a}; // check x11 < 0, check a = 1\n}\n"
  code: "#pragma once\n\n#include <array>\n#include <type_traits>\n#include <utility>\n\
    \n// returns [x, y, gcd(a, b)] s.t. ax+by = gcd(a, b)\ntemplate<typename Int>\n\
    inline std::enable_if_t<std::is_signed_v<Int>, std::array<Int, 3>> xgcd(Int a,\
    \ Int b) {\n    Int x11 = 1, x12 = 0, x21 = 0, x22 = 1;\n    while (b) {\n   \
    \     std::add_const_t<Int> q = a / b;\n        x11                     = std::exchange(x21,\
    \ x11 - x21 * q);\n        x12                     = std::exchange(x22, x12 -\
    \ x22 * q);\n        a                       = std::exchange(b, a - b * q);\n\
    \    }\n    return {x11, x12, a};\n}\n\n// returns [a^(-1) mod b, gcd(a, b)]\n\
    template<typename Int>\ninline std::enable_if_t<std::is_signed_v<Int>, std::array<Int,\
    \ 2>> inv_gcd(Int a, Int b) {\n    Int x11 = 1, x21 = 0;\n    while (b) {\n  \
    \      std::add_const_t<Int> q = a / b;\n        x11                     = std::exchange(x21,\
    \ x11 - x21 * q);\n        a                       = std::exchange(b, a - b *\
    \ q);\n    }\n    return {x11, a}; // check x11 < 0, check a = 1\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: xgcd.hpp
  requiredBy:
  - chinese_remainder.hpp
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/number_theory/yukicoder187.0.test.cpp
  - test/number_theory/sqrt_mod.0.test.cpp
documentation_of: xgcd.hpp
layout: document
redirect_from:
- /library/xgcd.hpp
- /library/xgcd.hpp.html
title: xgcd.hpp
---
