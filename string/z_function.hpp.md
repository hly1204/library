---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/string/z_algorithm.0.test.cpp
    title: remote_test/yosupo/string/z_algorithm.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"string/z_function.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\
    \n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n\
    #define LIB ::lib::\n\n\n#line 5 \"string/z_function.hpp\"\n\n#include <vector>\n\
    \nLIB_BEGIN\n\ntemplate <typename ContainerT>\nstd::vector<int> z_function(ContainerT\
    \ &&s) {\n  const int n = static_cast<int>(s.size());\n  std::vector<int> z(n,\
    \ 0);\n  if (n == 0) return z;\n  if ((z[0] = n) == 1) return z;\n  int zi = 0,\
    \ l = -1, r = -1, i = 2;\n  for (auto s0 = s[0]; zi + 1 < n && s[zi + 1] == s0;\
    \ ++zi) {}\n  if ((z[1] = r = zi) > 0)\n    for (l = 1; i < n && zi >= 0;) z[i++]\
    \ = --zi;\n  for (; i < n; ++i)\n    if (r < i) {\n      for (zi = 0; zi + i <\
    \ n && s[zi] == s[zi + i]; ++zi) {}\n      if ((z[i] = zi) > 0) l = i, r = zi\
    \ + i - 1;\n    } else if ((z[i] = z[i - l]) >= r - i + 1) {\n      for (zi =\
    \ r - i + 1; zi + i < n && s[zi] == s[zi + i]; ++zi) {}\n      z[i] = zi, l =\
    \ i, r = zi + i - 1;\n    }\n  return z;\n}\n\nLIB_END\n\n\n"
  code: "#ifndef Z_FUNCTION_HPP\n#define Z_FUNCTION_HPP\n\n#include \"../common.hpp\"\
    \n\n#include <vector>\n\nLIB_BEGIN\n\ntemplate <typename ContainerT>\nstd::vector<int>\
    \ z_function(ContainerT &&s) {\n  const int n = static_cast<int>(s.size());\n\
    \  std::vector<int> z(n, 0);\n  if (n == 0) return z;\n  if ((z[0] = n) == 1)\
    \ return z;\n  int zi = 0, l = -1, r = -1, i = 2;\n  for (auto s0 = s[0]; zi +\
    \ 1 < n && s[zi + 1] == s0; ++zi) {}\n  if ((z[1] = r = zi) > 0)\n    for (l =\
    \ 1; i < n && zi >= 0;) z[i++] = --zi;\n  for (; i < n; ++i)\n    if (r < i) {\n\
    \      for (zi = 0; zi + i < n && s[zi] == s[zi + i]; ++zi) {}\n      if ((z[i]\
    \ = zi) > 0) l = i, r = zi + i - 1;\n    } else if ((z[i] = z[i - l]) >= r - i\
    \ + 1) {\n      for (zi = r - i + 1; zi + i < n && s[zi] == s[zi + i]; ++zi) {}\n\
    \      z[i] = zi, l = i, r = zi + i - 1;\n    }\n  return z;\n}\n\nLIB_END\n\n\
    #endif"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: string/z_function.hpp
  requiredBy: []
  timestamp: '2022-05-01 23:45:11+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/string/z_algorithm.0.test.cpp
documentation_of: string/z_function.hpp
layout: document
title: Z Function
---

## Bibliography

1. Dan Gusfield. [Algorithms on Strings, Trees, and Sequences: Computer Science and Computational Biology](https://www.amazon.com/Algorithms-Strings-Trees-Sequences-Computational/dp/0521585198).
