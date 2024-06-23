---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structure/unionfind.0.test.cpp
    title: test/data_structure/unionfind.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"disjoint_set.hpp\"\n\n#include <numeric>\n#include <vector>\n\
    \nclass DisjointSet {\n    mutable std::vector<int> P;\n    std::vector<int> S;\n\
    \npublic:\n    DisjointSet() = default;\n    explicit DisjointSet(int N) : P(N),\
    \ S(N) { std::iota(P.begin(), P.end(), 0); }\n    void make_set(int N) {\n   \
    \     P.resize(N);\n        S.assign(N, 1);\n        std::iota(P.begin(), P.end(),\
    \ 0);\n    }\n    int root(int u) const {\n        // path halving\n        while\
    \ (P[u] != P[P[u]]) u = P[u] = P[P[u]];\n        return P[u];\n    }\n    bool\
    \ is_same(int u, int v) const { return root(u) == root(v); }\n    int unite(int\
    \ u, int v) {\n        u = root(u), v = root(v);\n        if (u == v) return u;\n\
    \        if (S[u] < S[v]) return S[v] += S[u], P[u] = v;\n        return S[u]\
    \ += S[v], P[v] = u;\n    }\n    int component_size(int u) const { return S[root(u)];\
    \ }\n};\n"
  code: "#pragma once\n\n#include <numeric>\n#include <vector>\n\nclass DisjointSet\
    \ {\n    mutable std::vector<int> P;\n    std::vector<int> S;\n\npublic:\n   \
    \ DisjointSet() = default;\n    explicit DisjointSet(int N) : P(N), S(N) { std::iota(P.begin(),\
    \ P.end(), 0); }\n    void make_set(int N) {\n        P.resize(N);\n        S.assign(N,\
    \ 1);\n        std::iota(P.begin(), P.end(), 0);\n    }\n    int root(int u) const\
    \ {\n        // path halving\n        while (P[u] != P[P[u]]) u = P[u] = P[P[u]];\n\
    \        return P[u];\n    }\n    bool is_same(int u, int v) const { return root(u)\
    \ == root(v); }\n    int unite(int u, int v) {\n        u = root(u), v = root(v);\n\
    \        if (u == v) return u;\n        if (S[u] < S[v]) return S[v] += S[u],\
    \ P[u] = v;\n        return S[u] += S[v], P[v] = u;\n    }\n    int component_size(int\
    \ u) const { return S[root(u)]; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: disjoint_set.hpp
  requiredBy: []
  timestamp: '2024-06-23 11:19:57+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structure/unionfind.0.test.cpp
documentation_of: disjoint_set.hpp
layout: document
redirect_from:
- /library/disjoint_set.hpp
- /library/disjoint_set.hpp.html
title: disjoint_set.hpp
---
