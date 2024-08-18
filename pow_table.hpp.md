---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: famous_sequence.hpp
    title: famous_sequence.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/enumerative_combinatorics/partition_function.0.test.cpp
    title: test/enumerative_combinatorics/partition_function.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/enumerative_combinatorics/stirling_number_of_the_first_kind.0.test.cpp
    title: test/enumerative_combinatorics/stirling_number_of_the_first_kind.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/enumerative_combinatorics/stirling_number_of_the_first_kind_fixed_k.0.test.cpp
    title: test/enumerative_combinatorics/stirling_number_of_the_first_kind_fixed_k.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/enumerative_combinatorics/stirling_number_of_the_second_kind.0.test.cpp
    title: test/enumerative_combinatorics/stirling_number_of_the_second_kind.0.test.cpp
  - icon: ':x:'
    path: test/enumerative_combinatorics/stirling_number_of_the_second_kind_fixed_k.0.test.cpp
    title: test/enumerative_combinatorics/stirling_number_of_the_second_kind_fixed_k.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 2 \"pow_table.hpp\"\n\n#include <vector>\n\n// returns 0^e,\
    \ 1^e, ..., (n-1)^e\ntemplate <typename Tp>\ninline std::vector<Tp> pow_table(int\
    \ e, int n) {\n    if (n <= 0) return {};\n    std::vector<bool> is_comp(n);\n\
    \    std::vector<int> p;\n    std::vector<Tp> res(n);\n    res[0] = (e == 0 ?\
    \ Tp(1) : Tp()); // 0^0=1\n    if (n >= 2) res[1] = Tp(1);\n    for (int i = 2;\
    \ i < n; ++i) {\n        if (!is_comp[i]) res[i] = Tp(p.emplace_back(i)).pow(e);\n\
    \        for (int j = 0; j < (int)p.size() && i * p[j] < n; ++j) {\n         \
    \   is_comp[i * p[j]] = true;\n            res[i * p[j]]     = res[i] * res[p[j]];\n\
    \            if (i % p[j] == 0) break;\n        }\n    }\n    return res;\n}\n"
  code: "#pragma once\n\n#include <vector>\n\n// returns 0^e, 1^e, ..., (n-1)^e\n\
    template <typename Tp>\ninline std::vector<Tp> pow_table(int e, int n) {\n   \
    \ if (n <= 0) return {};\n    std::vector<bool> is_comp(n);\n    std::vector<int>\
    \ p;\n    std::vector<Tp> res(n);\n    res[0] = (e == 0 ? Tp(1) : Tp()); // 0^0=1\n\
    \    if (n >= 2) res[1] = Tp(1);\n    for (int i = 2; i < n; ++i) {\n        if\
    \ (!is_comp[i]) res[i] = Tp(p.emplace_back(i)).pow(e);\n        for (int j = 0;\
    \ j < (int)p.size() && i * p[j] < n; ++j) {\n            is_comp[i * p[j]] = true;\n\
    \            res[i * p[j]]     = res[i] * res[p[j]];\n            if (i % p[j]\
    \ == 0) break;\n        }\n    }\n    return res;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: pow_table.hpp
  requiredBy:
  - famous_sequence.hpp
  timestamp: '2024-08-18 17:57:40+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/enumerative_combinatorics/stirling_number_of_the_second_kind.0.test.cpp
  - test/enumerative_combinatorics/partition_function.0.test.cpp
  - test/enumerative_combinatorics/stirling_number_of_the_first_kind.0.test.cpp
  - test/enumerative_combinatorics/stirling_number_of_the_second_kind_fixed_k.0.test.cpp
  - test/enumerative_combinatorics/stirling_number_of_the_first_kind_fixed_k.0.test.cpp
documentation_of: pow_table.hpp
layout: document
redirect_from:
- /library/pow_table.hpp
- /library/pow_table.hpp.html
title: pow_table.hpp
---
