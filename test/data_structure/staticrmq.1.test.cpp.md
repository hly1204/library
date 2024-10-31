---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: rmq.hpp
    title: rmq.hpp
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
  bundledCode: "#line 1 \"test/data_structure/staticrmq.1.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#line 2 \"rmq.hpp\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <functional>\n#include <vector>\n\n\
    template <typename Tp, typename Comp = std::less<>>\nclass RMQ {\npublic:\n  \
    \  class SparseTableInner {\n        const RMQ &Rmq;\n        int N;\n       \
    \ std::vector<Tp> T;\n\n    public:\n        explicit SparseTableInner(const RMQ\
    \ &R) : Rmq(R), N() {}\n\n        void build(const std::vector<Tp> &V) {\n   \
    \         N        = V.size();\n            int LogN = 0;\n            while ((1\
    \ << LogN) < N) ++LogN;\n            T.resize((LogN + 1) * N);\n            for\
    \ (int i = 0; i < N; ++i) T[i] = V[i];\n            for (int i = 1; i <= LogN;\
    \ ++i) {\n                auto P = T.begin() + (i - 1) * N, C = P + N;\n     \
    \           for (int j = 0; j < N - (1 << i) + 1; ++j)\n                    C[j]\
    \ = std::min(P[j], P[j + (1 << (i - 1))], Rmq.Cmp);\n            }\n        }\n\
    \n        // returns M(V[L],...,V[R-1])\n        Tp query(int L, int R) const\
    \ {\n            assert(L < R);\n            const int lv = 31 - __builtin_clz(R\
    \ - L);\n            return std::min(T[lv * N + L], T[lv * N + R - (1 << lv)],\
    \ Rmq.Cmp);\n        }\n    };\n\n    std::vector<Tp> T;\n    Comp Cmp;\n    SparseTableInner\
    \ ST;\n    std::vector<unsigned> StackNum;\n\n    explicit RMQ(const std::vector<Tp>\
    \ &V, Comp comp = Comp())\n        : T(V), Cmp(comp), ST(*this), StackNum(V.size())\
    \ {\n        if (V.empty()) return;\n        std::vector<Tp> b;\n        const\
    \ int B = ((int)V.size() - 1) / 32 + 1;\n        b.reserve(B);\n        for (int\
    \ i = 0; i < B; ++i)\n            b.emplace_back(build_block(V.begin() + i * 32,\n\
    \                                       std::min<int>((i + 1) * 32, V.size())\
    \ - i * 32,\n                                       StackNum.begin() + i * 32));\n\
    \        ST.build(b);\n    }\n\n    Tp build_block(typename std::vector<Tp>::const_iterator\
    \ A, int N,\n                   typename std::vector<unsigned>::iterator D) {\n\
    \        unsigned stack_num = 0;\n        for (int i = 0, sta[32], top = 0; i\
    \ < N; ++i) {\n            while (top > 0 && Cmp(A[i], A[sta[top - 1]])) stack_num\
    \ ^= 1U << sta[--top];\n            D[i] = (stack_num |= 1U << (sta[top++] = i));\n\
    \        }\n        return A[__builtin_ctz(stack_num)];\n    }\n\n    // [L, R)\
    \ in same block\n    Tp query_block(int L, int R) { return T[L + __builtin_ctz(StackNum[R\
    \ - 1] >> (L % 32))]; }\n\n    Tp query(int L, int R) {\n        assert(L < R);\n\
    \        const int BL = L / 32, BR = (R - 1) / 32;\n        if (BL == BR) return\
    \ query_block(L, R);\n        if (BL + 1 == BR) return std::min(query_block(L,\
    \ BR * 32), query_block(BR * 32, R), Cmp);\n        return std::min(\n       \
    \     {query_block(L, (BL + 1) * 32), ST.query(BL + 1, BR), query_block(BR * 32,\
    \ R)}, Cmp);\n    }\n};\n#line 4 \"test/data_structure/staticrmq.1.test.cpp\"\n\
    #include <iostream>\n#line 6 \"test/data_structure/staticrmq.1.test.cpp\"\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    std::vector<int> V(n);\n    for (int\
    \ i = 0; i < n; ++i) std::cin >> V[i];\n    RMQ rmq(V);\n    while (q--) {\n \
    \       int l, r;\n        std::cin >> l >> r;\n        std::cout << rmq.query(l,\
    \ r) << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ \"rmq.hpp\"\n#include <iostream>\n#include <vector>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    std::vector<int>\
    \ V(n);\n    for (int i = 0; i < n; ++i) std::cin >> V[i];\n    RMQ rmq(V);\n\
    \    while (q--) {\n        int l, r;\n        std::cin >> l >> r;\n        std::cout\
    \ << rmq.query(l, r) << '\\n';\n    }\n    return 0;\n}\n"
  dependsOn:
  - rmq.hpp
  isVerificationFile: true
  path: test/data_structure/staticrmq.1.test.cpp
  requiredBy: []
  timestamp: '2024-10-31 23:57:54+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/data_structure/staticrmq.1.test.cpp
layout: document
redirect_from:
- /verify/test/data_structure/staticrmq.1.test.cpp
- /verify/test/data_structure/staticrmq.1.test.cpp.html
title: test/data_structure/staticrmq.1.test.cpp
---
