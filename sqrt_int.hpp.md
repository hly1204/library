---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/enumerative_combinatorics/factorial.0.test.cpp
    title: test/enumerative_combinatorics/factorial.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"sqrt_int.hpp\"\n\n#include <cassert>\n#include <type_traits>\n\
    \n// see:\n// [1]: Richard P. Brent and Paul Zimmermann. Modern Computer Arithmetic.\n\
    \n// returns floor(m^(1/2))\ntemplate <typename Int>\ninline std::enable_if_t<std::is_integral_v<Int>,\
    \ Int> sqrt_int(Int m) {\n    assert(m >= 0);\n    if (m == 0) return 0;\n   \
    \ for (Int u = m;;) {\n        std::add_const_t<Int> s = u;\n        u       \
    \                = (s + m / s) / 2;\n        if (u >= s) return s;\n    }\n}\n"
  code: "#pragma once\n\n#include <cassert>\n#include <type_traits>\n\n// see:\n//\
    \ [1]: Richard P. Brent and Paul Zimmermann. Modern Computer Arithmetic.\n\n//\
    \ returns floor(m^(1/2))\ntemplate <typename Int>\ninline std::enable_if_t<std::is_integral_v<Int>,\
    \ Int> sqrt_int(Int m) {\n    assert(m >= 0);\n    if (m == 0) return 0;\n   \
    \ for (Int u = m;;) {\n        std::add_const_t<Int> s = u;\n        u       \
    \                = (s + m / s) / 2;\n        if (u >= s) return s;\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: sqrt_int.hpp
  requiredBy: []
  timestamp: '2025-01-04 19:35:46+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/enumerative_combinatorics/factorial.0.test.cpp
documentation_of: sqrt_int.hpp
layout: document
redirect_from:
- /library/sqrt_int.hpp
- /library/sqrt_int.hpp.html
title: sqrt_int.hpp
---
