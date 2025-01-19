---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid.hpp
    title: monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structure/staticrmq.0.test.cpp
    title: test/data_structure/staticrmq.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"sparse_table.hpp\"\n\n#line 2 \"monoid.hpp\"\n\n#include\
    \ <type_traits>\n\ntemplate<typename Tp, typename Op,\n         std::enable_if_t<std::is_invocable_r_v<Tp,\
    \ Op, const Tp &, const Tp &>, int> = 0>\nclass Monoid {\npublic:\n    Op F;\n\
    \    Tp Id;\n\n    explicit Monoid(Op F, const Tp &Id = {}) : F(F), Id(Id) {}\n\
    \n    const Tp &id() const { return Id; }\n    Tp operator()(const Tp &L, const\
    \ Tp &R) const { return F(L, R); }\n};\n#line 4 \"sparse_table.hpp\"\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate<typename Tp, typename Op> class SparseTable\
    \ {\npublic:\n    const int N;\n    const Monoid<Tp, Op> M;\n    std::vector<Tp>\
    \ T;\n\n    SparseTable(const std::vector<Tp> &V, const Monoid<Tp, Op> &M) : N(V.size()),\
    \ M(M) {\n        int LogN = 0;\n        while ((1 << LogN) < N) ++LogN;\n   \
    \     T.resize((LogN + 1) * N);\n        for (int i = 0; i < N; ++i) T[i] = V[i];\n\
    \        for (int i = 1; i <= LogN; ++i) {\n            auto P = T.begin() + (i\
    \ - 1) * N, C = P + N;\n            for (int j = 0; j < N - (1 << i) + 1; ++j)\
    \ C[j] = M(P[j], P[j + (1 << (i - 1))]);\n        }\n    }\n\n    // returns M(V[L],...,V[R-1])\n\
    \    Tp query(int L, int R) const {\n        assert(L <= R);\n        if (L ==\
    \ R) return M.id();\n        const int lv = 31 - __builtin_clz(R - L);\n     \
    \   return M(T[lv * N + L], T[lv * N + R - (1 << lv)]);\n    }\n};\n"
  code: "#pragma once\n\n#include \"monoid.hpp\"\n#include <cassert>\n#include <vector>\n\
    \ntemplate<typename Tp, typename Op> class SparseTable {\npublic:\n    const int\
    \ N;\n    const Monoid<Tp, Op> M;\n    std::vector<Tp> T;\n\n    SparseTable(const\
    \ std::vector<Tp> &V, const Monoid<Tp, Op> &M) : N(V.size()), M(M) {\n       \
    \ int LogN = 0;\n        while ((1 << LogN) < N) ++LogN;\n        T.resize((LogN\
    \ + 1) * N);\n        for (int i = 0; i < N; ++i) T[i] = V[i];\n        for (int\
    \ i = 1; i <= LogN; ++i) {\n            auto P = T.begin() + (i - 1) * N, C =\
    \ P + N;\n            for (int j = 0; j < N - (1 << i) + 1; ++j) C[j] = M(P[j],\
    \ P[j + (1 << (i - 1))]);\n        }\n    }\n\n    // returns M(V[L],...,V[R-1])\n\
    \    Tp query(int L, int R) const {\n        assert(L <= R);\n        if (L ==\
    \ R) return M.id();\n        const int lv = 31 - __builtin_clz(R - L);\n     \
    \   return M(T[lv * N + L], T[lv * N + R - (1 << lv)]);\n    }\n};\n"
  dependsOn:
  - monoid.hpp
  isVerificationFile: false
  path: sparse_table.hpp
  requiredBy: []
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structure/staticrmq.0.test.cpp
documentation_of: sparse_table.hpp
layout: document
redirect_from:
- /library/sparse_table.hpp
- /library/sparse_table.hpp.html
title: sparse_table.hpp
---
