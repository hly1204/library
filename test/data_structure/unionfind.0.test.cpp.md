---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: disjoint_set.hpp
    title: disjoint_set.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"test/data_structure/unionfind.0.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/unionfind\"\n\n#line 2 \"disjoint_set.hpp\"\
    \n\n#include <numeric>\n#include <vector>\n\nclass DisjointSet {\n    mutable\
    \ std::vector<int> P;\n    std::vector<int> S;\n\npublic:\n    DisjointSet() =\
    \ default;\n    explicit DisjointSet(int N) : P(N), S(N) { std::iota(P.begin(),\
    \ P.end(), 0); }\n    void make_set(int N) {\n        P.resize(N);\n        S.assign(N,\
    \ 1);\n        std::iota(P.begin(), P.end(), 0);\n    }\n    int root(int u) const\
    \ {\n        // path halving\n        while (P[u] != P[P[u]]) u = P[u] = P[P[u]];\n\
    \        return P[u];\n    }\n    bool is_same(int u, int v) const { return root(u)\
    \ == root(v); }\n    int unite(int u, int v) {\n        u = root(u), v = root(v);\n\
    \        if (u == v) return u;\n        if (S[u] < S[v]) return S[v] += S[u],\
    \ P[u] = v;\n        return S[u] += S[v], P[v] = u;\n    }\n    int component_size(int\
    \ u) const { return S[root(u)]; }\n};\n#line 4 \"test/data_structure/unionfind.0.test.cpp\"\
    \n#include <iostream>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    DisjointSet\
    \ s(n);\n    while (q--) {\n        int t, u, v;\n        std::cin >> t >> u >>\
    \ v;\n        if (t == 0) {\n            s.unite(u, v);\n        } else {\n  \
    \          std::cout << s.is_same(u, v) << '\\n';\n        }\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ \"disjoint_set.hpp\"\n#include <iostream>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    DisjointSet\
    \ s(n);\n    while (q--) {\n        int t, u, v;\n        std::cin >> t >> u >>\
    \ v;\n        if (t == 0) {\n            s.unite(u, v);\n        } else {\n  \
    \          std::cout << s.is_same(u, v) << '\\n';\n        }\n    }\n    return\
    \ 0;\n}\n"
  dependsOn:
  - disjoint_set.hpp
  isVerificationFile: true
  path: test/data_structure/unionfind.0.test.cpp
  requiredBy: []
  timestamp: '2024-06-23 11:19:57+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/data_structure/unionfind.0.test.cpp
layout: document
redirect_from:
- /verify/test/data_structure/unionfind.0.test.cpp
- /verify/test/data_structure/unionfind.0.test.cpp.html
title: test/data_structure/unionfind.0.test.cpp
---
