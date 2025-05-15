---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: suffix_array.hpp
    title: suffix_array.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/suffixarray
    links:
    - https://judge.yosupo.jp/problem/suffixarray
  bundledCode: "#line 1 \"test/string/suffixarray.0.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/suffixarray\"\n\n#line 2 \"suffix_array.hpp\"\n\
    \n#include <algorithm>\n#include <string>\n#include <vector>\n\ninline std::vector<int>\
    \ suffix_array(const std::string &s) {\n    if (s.empty()) return {};\n    auto\
    \ radix_pass = [](auto &&a, auto &&b, auto &&r, int n, int K) {\n        std::vector<int>\
    \ c(K + 1);\n        for (int i = 0; i < n; ++i) ++c[r[a[i]]];\n        for (int\
    \ i = 1; i <= K; ++i) c[i] += c[i - 1];\n        for (int i = n - 1; i >= 0; --i)\
    \ b[--c[r[a[i]]]] = a[i];\n    };\n    const int n = s.size();\n    int K    \
    \   = *std::max_element(s.begin(), s.end());\n    std::vector<int> rank0(n), rank1(n),\
    \ t(n), sa(n);\n    for (int i = 0; i < n; ++i) rank0[sa[i] = i] = s[i];\n   \
    \ for (int i = 1;; i *= 2) {\n        for (int j = 0; j < n; ++j) rank1[j] = (i\
    \ + j < n) ? rank0[i + j] : 0;\n        radix_pass(sa, t, rank1, n, K);\n    \
    \    radix_pass(t, sa, rank0, n, K);\n        t[sa[0]] = K = 1;\n        for (int\
    \ j = 1; j < n; ++j)\n            t[sa[j]] =\n                (rank0[sa[j]] ==\
    \ rank0[sa[j - 1]] && rank1[sa[j]] == rank1[sa[j - 1]]) ? K : ++K;\n        if\
    \ (K == n) return sa;\n        rank0.swap(t);\n    }\n}\n#line 4 \"test/string/suffixarray.0.test.cpp\"\
    \n#include <iostream>\n#line 7 \"test/string/suffixarray.0.test.cpp\"\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    std::string\
    \ s;\n    std::cin >> s;\n    const auto sa = suffix_array(s);\n    for (int i\
    \ = 0; i < (int)sa.size(); ++i) std::cout << sa[i] << ' ';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\n\n#include\
    \ \"suffix_array.hpp\"\n#include <iostream>\n#include <string>\n#include <vector>\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    std::string s;\n    std::cin >> s;\n    const auto sa = suffix_array(s);\n\
    \    for (int i = 0; i < (int)sa.size(); ++i) std::cout << sa[i] << ' ';\n   \
    \ return 0;\n}\n"
  dependsOn:
  - suffix_array.hpp
  isVerificationFile: true
  path: test/string/suffixarray.0.test.cpp
  requiredBy: []
  timestamp: '2025-05-15 17:15:01+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/string/suffixarray.0.test.cpp
layout: document
redirect_from:
- /verify/test/string/suffixarray.0.test.cpp
- /verify/test/string/suffixarray.0.test.cpp.html
title: test/string/suffixarray.0.test.cpp
---
