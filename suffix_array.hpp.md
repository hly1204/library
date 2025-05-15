---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/string/suffixarray.0.test.cpp
    title: test/string/suffixarray.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"suffix_array.hpp\"\n\n#include <algorithm>\n#include <string>\n\
    #include <vector>\n\ninline std::vector<int> suffix_array(const std::string &s)\
    \ {\n    if (s.empty()) return {};\n    auto radix_pass = [](auto &&a, auto &&b,\
    \ auto &&r, int n, int K) {\n        std::vector<int> c(K + 1);\n        for (int\
    \ i = 0; i < n; ++i) ++c[r[a[i]]];\n        for (int i = 1; i <= K; ++i) c[i]\
    \ += c[i - 1];\n        for (int i = n - 1; i >= 0; --i) b[--c[r[a[i]]]] = a[i];\n\
    \    };\n    const int n = s.size();\n    int K       = *std::max_element(s.begin(),\
    \ s.end());\n    std::vector<int> rank0(n), rank1(n), t(n), sa(n);\n    for (int\
    \ i = 0; i < n; ++i) rank0[sa[i] = i] = s[i];\n    for (int i = 1;; i *= 2) {\n\
    \        for (int j = 0; j < n; ++j) rank1[j] = (i + j < n) ? rank0[i + j] : 0;\n\
    \        radix_pass(sa, t, rank1, n, K);\n        radix_pass(t, sa, rank0, n,\
    \ K);\n        t[sa[0]] = K = 1;\n        for (int j = 1; j < n; ++j)\n      \
    \      t[sa[j]] =\n                (rank0[sa[j]] == rank0[sa[j - 1]] && rank1[sa[j]]\
    \ == rank1[sa[j - 1]]) ? K : ++K;\n        if (K == n) return sa;\n        rank0.swap(t);\n\
    \    }\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <string>\n#include <vector>\n\
    \ninline std::vector<int> suffix_array(const std::string &s) {\n    if (s.empty())\
    \ return {};\n    auto radix_pass = [](auto &&a, auto &&b, auto &&r, int n, int\
    \ K) {\n        std::vector<int> c(K + 1);\n        for (int i = 0; i < n; ++i)\
    \ ++c[r[a[i]]];\n        for (int i = 1; i <= K; ++i) c[i] += c[i - 1];\n    \
    \    for (int i = n - 1; i >= 0; --i) b[--c[r[a[i]]]] = a[i];\n    };\n    const\
    \ int n = s.size();\n    int K       = *std::max_element(s.begin(), s.end());\n\
    \    std::vector<int> rank0(n), rank1(n), t(n), sa(n);\n    for (int i = 0; i\
    \ < n; ++i) rank0[sa[i] = i] = s[i];\n    for (int i = 1;; i *= 2) {\n       \
    \ for (int j = 0; j < n; ++j) rank1[j] = (i + j < n) ? rank0[i + j] : 0;\n   \
    \     radix_pass(sa, t, rank1, n, K);\n        radix_pass(t, sa, rank0, n, K);\n\
    \        t[sa[0]] = K = 1;\n        for (int j = 1; j < n; ++j)\n            t[sa[j]]\
    \ =\n                (rank0[sa[j]] == rank0[sa[j - 1]] && rank1[sa[j]] == rank1[sa[j\
    \ - 1]]) ? K : ++K;\n        if (K == n) return sa;\n        rank0.swap(t);\n\
    \    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: suffix_array.hpp
  requiredBy: []
  timestamp: '2025-05-15 17:15:01+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/string/suffixarray.0.test.cpp
documentation_of: suffix_array.hpp
layout: document
redirect_from:
- /library/suffix_array.hpp
- /library/suffix_array.hpp.html
title: suffix_array.hpp
---
