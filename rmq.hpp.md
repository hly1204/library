---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structure/staticrmq.1.test.cpp
    title: test/data_structure/staticrmq.1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"rmq.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <functional>\n#include <vector>\n\ntemplate<typename Tp, typename Comp\
    \ = std::less<>, typename UInt = unsigned> class RMQ {\n    class SparseTableInner\
    \ {\n        const RMQ &Rmq;\n        int N;\n        std::vector<Tp> T;\n\n \
    \   public:\n        explicit SparseTableInner(const RMQ &R) : Rmq(R), N() {}\n\
    \n        void build(const std::vector<Tp> &V) {\n            N        = V.size();\n\
    \            int LogN = 0;\n            while ((1 << LogN) < N) ++LogN;\n    \
    \        T.resize((LogN + 1) * N);\n            for (int i = 0; i < N; ++i) T[i]\
    \ = V[i];\n            for (int i = 1; i <= LogN; ++i) {\n                auto\
    \ P = T.begin() + (i - 1) * N, C = P + N;\n                for (int j = 0; j <\
    \ N - (1 << i) + 1; ++j)\n                    C[j] = std::min(P[j], P[j + (1 <<\
    \ (i - 1))], Rmq.Cmp);\n            }\n        }\n\n        // returns M(V[L],...,V[R-1])\n\
    \        Tp query(int L, int R) const {\n            assert(L < R);\n        \
    \    const int lv = 31 - __builtin_clz(R - L);\n            return std::min(T[lv\
    \ * N + L], T[lv * N + R - (1 << lv)], Rmq.Cmp);\n        }\n    };\n\n    Tp\
    \ build_block(typename std::vector<Tp>::const_iterator A, int N,\n           \
    \        typename std::vector<UInt>::iterator D) {\n        UInt stack_num = 0;\n\
    \        for (int i = 0, sta[W], top = 0; i < N; ++i) {\n            while (top\
    \ > 0 && Cmp(A[i], A[sta[top - 1]])) stack_num ^= 1U << sta[--top];\n        \
    \    D[i] = (stack_num |= 1U << (sta[top++] = i));\n        }\n        return\
    \ A[__builtin_ctzll(stack_num)];\n    }\n\n    // [L, R) in same block\n    Tp\
    \ block(int L, int R) const { return T[L + __builtin_ctzll(StackNum[R - 1] >>\
    \ (L % W))]; }\n\n    static constexpr int W = sizeof(UInt) * 8;\n\n    std::vector<Tp>\
    \ T;\n    Comp Cmp;\n    SparseTableInner ST;\n    std::vector<UInt> StackNum;\n\
    \npublic:\n    explicit RMQ(const std::vector<Tp> &V, Comp comp = Comp())\n  \
    \      : T(V), Cmp(comp), ST(*this), StackNum(V.size()) {\n        std::vector<Tp>\
    \ b;\n        const int B = ((int)V.size() + (W - 1)) / W;\n        b.reserve(B);\n\
    \        for (int i = 0; i < B; ++i)\n            b.emplace_back(build_block(V.begin()\
    \ + i * W,\n                                       std::min<int>((i + 1) * W,\
    \ V.size()) - i * W,\n                                       StackNum.begin()\
    \ + i * W));\n        ST.build(b);\n    }\n\n    Tp query(int L, int R) const\
    \ {\n        assert(L < R);\n        const int BL = L / W, BR = (R - 1) / W;\n\
    \        if (BL == BR) return block(L, R);\n        if (BL + 1 == BR) return std::min(block(L,\
    \ BR * W), block(BR * W, R), Cmp);\n        return std::min({block(L, (BL + 1)\
    \ * W), ST.query(BL + 1, BR), block(BR * W, R)}, Cmp);\n    }\n};\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <functional>\n\
    #include <vector>\n\ntemplate<typename Tp, typename Comp = std::less<>, typename\
    \ UInt = unsigned> class RMQ {\n    class SparseTableInner {\n        const RMQ\
    \ &Rmq;\n        int N;\n        std::vector<Tp> T;\n\n    public:\n        explicit\
    \ SparseTableInner(const RMQ &R) : Rmq(R), N() {}\n\n        void build(const\
    \ std::vector<Tp> &V) {\n            N        = V.size();\n            int LogN\
    \ = 0;\n            while ((1 << LogN) < N) ++LogN;\n            T.resize((LogN\
    \ + 1) * N);\n            for (int i = 0; i < N; ++i) T[i] = V[i];\n         \
    \   for (int i = 1; i <= LogN; ++i) {\n                auto P = T.begin() + (i\
    \ - 1) * N, C = P + N;\n                for (int j = 0; j < N - (1 << i) + 1;\
    \ ++j)\n                    C[j] = std::min(P[j], P[j + (1 << (i - 1))], Rmq.Cmp);\n\
    \            }\n        }\n\n        // returns M(V[L],...,V[R-1])\n        Tp\
    \ query(int L, int R) const {\n            assert(L < R);\n            const int\
    \ lv = 31 - __builtin_clz(R - L);\n            return std::min(T[lv * N + L],\
    \ T[lv * N + R - (1 << lv)], Rmq.Cmp);\n        }\n    };\n\n    Tp build_block(typename\
    \ std::vector<Tp>::const_iterator A, int N,\n                   typename std::vector<UInt>::iterator\
    \ D) {\n        UInt stack_num = 0;\n        for (int i = 0, sta[W], top = 0;\
    \ i < N; ++i) {\n            while (top > 0 && Cmp(A[i], A[sta[top - 1]])) stack_num\
    \ ^= 1U << sta[--top];\n            D[i] = (stack_num |= 1U << (sta[top++] = i));\n\
    \        }\n        return A[__builtin_ctzll(stack_num)];\n    }\n\n    // [L,\
    \ R) in same block\n    Tp block(int L, int R) const { return T[L + __builtin_ctzll(StackNum[R\
    \ - 1] >> (L % W))]; }\n\n    static constexpr int W = sizeof(UInt) * 8;\n\n \
    \   std::vector<Tp> T;\n    Comp Cmp;\n    SparseTableInner ST;\n    std::vector<UInt>\
    \ StackNum;\n\npublic:\n    explicit RMQ(const std::vector<Tp> &V, Comp comp =\
    \ Comp())\n        : T(V), Cmp(comp), ST(*this), StackNum(V.size()) {\n      \
    \  std::vector<Tp> b;\n        const int B = ((int)V.size() + (W - 1)) / W;\n\
    \        b.reserve(B);\n        for (int i = 0; i < B; ++i)\n            b.emplace_back(build_block(V.begin()\
    \ + i * W,\n                                       std::min<int>((i + 1) * W,\
    \ V.size()) - i * W,\n                                       StackNum.begin()\
    \ + i * W));\n        ST.build(b);\n    }\n\n    Tp query(int L, int R) const\
    \ {\n        assert(L < R);\n        const int BL = L / W, BR = (R - 1) / W;\n\
    \        if (BL == BR) return block(L, R);\n        if (BL + 1 == BR) return std::min(block(L,\
    \ BR * W), block(BR * W, R), Cmp);\n        return std::min({block(L, (BL + 1)\
    \ * W), ST.query(BL + 1, BR), block(BR * W, R)}, Cmp);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: rmq.hpp
  requiredBy: []
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/data_structure/staticrmq.1.test.cpp
documentation_of: rmq.hpp
layout: document
redirect_from:
- /library/rmq.hpp
- /library/rmq.hpp.html
title: rmq.hpp
---
