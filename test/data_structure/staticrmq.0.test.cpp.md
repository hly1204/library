---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: monoid.hpp
    title: monoid.hpp
  - icon: ':heavy_check_mark:'
    path: sparse_table.hpp
    title: sparse_table.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"test/data_structure/staticrmq.0.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#line 2 \"monoid.hpp\"\n\n\
    #include <type_traits>\n\ntemplate <typename Tp, typename Op,\n          std::enable_if_t<std::is_invocable_r_v<Tp,\
    \ Op, const Tp &, const Tp &>, int> = 0>\nclass Monoid {\npublic:\n    Op F;\n\
    \    Tp Id;\n\n    explicit Monoid(Op F, const Tp &Id = {}) : F(F), Id(Id) {}\n\
    \n    const Tp &id() const { return Id; }\n    Tp operator()(const Tp &L, const\
    \ Tp &R) const { return F(L, R); }\n};\n#line 2 \"sparse_table.hpp\"\n\n#line\
    \ 4 \"sparse_table.hpp\"\n#include <cassert>\n#include <vector>\n\ntemplate <typename\
    \ Tp, typename Op>\nclass SparseTable {\npublic:\n    const int N;\n    const\
    \ Monoid<Tp, Op> M;\n    std::vector<Tp> T;\n\n    SparseTable(const std::vector<Tp>\
    \ &V, const Monoid<Tp, Op> &M) : N(V.size()), M(M) {\n        int LogN = 0;\n\
    \        while ((1 << LogN) < N) ++LogN;\n        T.resize((LogN + 1) * N);\n\
    \        for (int i = 0; i < N; ++i) T[i] = V[i];\n        for (int i = 1; i <=\
    \ LogN; ++i) {\n            auto P = T.begin() + (i - 1) * N, C = P + N;\n   \
    \         for (int j = 0; j < N - (1 << i) + 1; ++j) C[j] = M(P[j], P[j + (1 <<\
    \ (i - 1))]);\n        }\n    }\n\n    // returns M(V[L],...,V[R-1])\n    Tp query(int\
    \ L, int R) const {\n        assert(L <= R);\n        if (L == R) return M.id();\n\
    \        const int lv = 31 - __builtin_clz(R - L);\n        return M(T[lv * N\
    \ + L], T[lv * N + R - (1 << lv)]);\n    }\n};\n#line 5 \"test/data_structure/staticrmq.0.test.cpp\"\
    \n#include <iostream>\n#line 7 \"test/data_structure/staticrmq.0.test.cpp\"\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<int> V(n);\n    for (int\
    \ i = 0; i < n; ++i) std::cin >> V[i];\n    SparseTable st(V, Monoid([](int a,\
    \ int b) { return a < b ? a : b; }, -1));\n    while (q--) {\n        int l, r;\n\
    \        std::cin >> l >> r;\n        std::cout << st.query(l, r) << '\\n';\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ \"monoid.hpp\"\n#include \"sparse_table.hpp\"\n#include <iostream>\n#include\
    \ <vector>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<int> V(n);\n    for (int\
    \ i = 0; i < n; ++i) std::cin >> V[i];\n    SparseTable st(V, Monoid([](int a,\
    \ int b) { return a < b ? a : b; }, -1));\n    while (q--) {\n        int l, r;\n\
    \        std::cin >> l >> r;\n        std::cout << st.query(l, r) << '\\n';\n\
    \    }\n    return 0;\n}\n"
  dependsOn:
  - monoid.hpp
  - sparse_table.hpp
  isVerificationFile: true
  path: test/data_structure/staticrmq.0.test.cpp
  requiredBy: []
  timestamp: '2024-08-27 23:34:26+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/data_structure/staticrmq.0.test.cpp
layout: document
redirect_from:
- /verify/test/data_structure/staticrmq.0.test.cpp
- /verify/test/data_structure/staticrmq.0.test.cpp.html
title: test/data_structure/staticrmq.0.test.cpp
---
