---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: disjoint_sparse_table.hpp
    title: disjoint_sparse_table.hpp
  - icon: ':heavy_check_mark:'
    path: monoid.hpp
    title: monoid.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/static_range_sum
    links:
    - https://judge.yosupo.jp/problem/static_range_sum
  bundledCode: "#line 1 \"test/data_structure/static_range_sum.0.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\n\n#line 2 \"disjoint_sparse_table.hpp\"\
    \n\n#line 2 \"monoid.hpp\"\n\n#include <type_traits>\n\ntemplate <typename Tp,\
    \ typename Op,\n          std::enable_if_t<std::is_invocable_r_v<Tp, Op, const\
    \ Tp &, const Tp &>, int> = 0>\nclass Monoid {\npublic:\n    Op F;\n    Tp Id;\n\
    \n    explicit Monoid(Op F, const Tp &Id = {}) : F(F), Id(Id) {}\n\n    const\
    \ Tp &id() const { return Id; }\n    Tp operator()(const Tp &L, const Tp &R) const\
    \ { return F(L, R); }\n};\n#line 4 \"disjoint_sparse_table.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\ntemplate <typename Tp, typename Op>\n\
    class DisjointSparseTable {\npublic:\n    int S;\n    const Monoid<Tp, Op> M;\n\
    \    std::vector<Tp> T;\n\n    DisjointSparseTable(const std::vector<Tp> &V, const\
    \ Monoid<Tp, Op> &M) : M(M) {\n        const int N = V.size();\n        int LogN\
    \    = 0;\n        while ((1 << LogN) < N) ++LogN;\n        S = (1 << LogN);\n\
    \        T.resize(std::max(LogN, 1) * S);\n        for (int i = 0; i < N; ++i)\
    \ T[i] = V[i];\n        for (int i = N; i < S; ++i) T[i] = this->M.id();\n   \
    \     for (int i = 2; i <= LogN; ++i) {\n            auto C = T.begin() + (i -\
    \ 1) * S;\n            for (int j = 0; j < S; j += (1 << i)) {\n             \
    \   const int mid = j + (1 << (i - 1));\n                C[mid - 1]    = T[mid\
    \ - 1];\n                for (int k = mid - 2; k >= j; --k) C[k] = M(T[k], C[k\
    \ + 1]);\n                C[mid] = T[mid];\n                for (int k = mid +\
    \ 1; k < j + (1 << i); ++k) C[k] = M(C[k - 1], T[k]);\n            }\n       \
    \ }\n    }\n\n    // returns M(V[L],...,V[R-1])\n    Tp query(int L, int R) const\
    \ {\n        assert(L <= R);\n        if (L == R) return M.id();\n        if (R\
    \ - L == 1) return T[L];\n        const int lv = 31 - __builtin_clz(L ^ (R - 1));\n\
    \        return M(T[lv * S + L], T[lv * S + (R - 1)]);\n    }\n};\n#line 5 \"\
    test/data_structure/static_range_sum.0.test.cpp\"\n#include <functional>\n#include\
    \ <iostream>\n#line 8 \"test/data_structure/static_range_sum.0.test.cpp\"\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<long long> V(n);\n  \
    \  for (int i = 0; i < n; ++i) std::cin >> V[i];\n    DisjointSparseTable dst(V,\
    \ Monoid(std::plus<long long>(), 0LL));\n    while (q--) {\n        int l, r;\n\
    \        std::cin >> l >> r;\n        std::cout << dst.query(l, r) << '\\n';\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/static_range_sum\"\n\n\
    #include \"disjoint_sparse_table.hpp\"\n#include \"monoid.hpp\"\n#include <functional>\n\
    #include <iostream>\n#include <vector>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<long\
    \ long> V(n);\n    for (int i = 0; i < n; ++i) std::cin >> V[i];\n    DisjointSparseTable\
    \ dst(V, Monoid(std::plus<long long>(), 0LL));\n    while (q--) {\n        int\
    \ l, r;\n        std::cin >> l >> r;\n        std::cout << dst.query(l, r) <<\
    \ '\\n';\n    }\n    return 0;\n}\n"
  dependsOn:
  - disjoint_sparse_table.hpp
  - monoid.hpp
  isVerificationFile: true
  path: test/data_structure/static_range_sum.0.test.cpp
  requiredBy: []
  timestamp: '2024-08-27 23:34:26+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/data_structure/static_range_sum.0.test.cpp
layout: document
redirect_from:
- /verify/test/data_structure/static_range_sum.0.test.cpp
- /verify/test/data_structure/static_range_sum.0.test.cpp.html
title: test/data_structure/static_range_sum.0.test.cpp
---
