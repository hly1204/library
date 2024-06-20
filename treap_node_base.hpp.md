---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: rng.hpp
    title: rng.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/range_reverse_range_sum.0.test.cpp
    title: test/range_reverse_range_sum.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"treap_node_base.hpp\"\n\n#line 2 \"rng.hpp\"\n\n#include\
    \ <cstdint>\n#include <limits>\n\n// see: https://prng.di.unimi.it/xoshiro256starstar.c\n\
    // original license CC0 1.0\nclass xoshiro256starstar {\n    using u64 = std::uint64_t;\n\
    \n    static inline u64 rotl(const u64 x, int k) { return (x << k) | (x >> (64\
    \ - k)); }\n\n    u64 s_[4];\n\n    u64 next() {\n        const u64 res = rotl(s_[1]\
    \ * 5, 7) * 9;\n        const u64 t   = s_[1] << 17;\n        s_[2] ^= s_[0];\n\
    \        s_[3] ^= s_[1];\n        s_[1] ^= s_[2];\n        s_[0] ^= s_[3];\n \
    \       s_[2] ^= t;\n        s_[3] = rotl(s_[3], 45);\n        return res;\n \
    \   }\n\npublic:\n    // see: https://prng.di.unimi.it/splitmix64.c\n    // original\
    \ license CC0 1.0\n    explicit xoshiro256starstar(u64 seed) {\n        for (int\
    \ i = 0; i < 4; ++i) {\n            u64 z = (seed += 0x9e3779b97f4a7c15);\n  \
    \          z     = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n            z     =\
    \ (z ^ (z >> 27)) * 0x94d049bb133111eb;\n            s_[i] = z ^ (z >> 31);\n\
    \        }\n    }\n    // see: https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator\n\
    \    using result_type = u64;\n    static constexpr u64 min() { return std::numeric_limits<u64>::min();\
    \ }\n    static constexpr u64 max() { return std::numeric_limits<u64>::max();\
    \ }\n    u64 operator()() { return next(); }\n};\n#line 4 \"treap_node_base.hpp\"\
    \n#include <random>\n#include <tuple>\n#include <utility>\n\ntemplate <typename\
    \ TreapNode>\nclass TreapNodeBase {\n    TreapNodeBase *L;\n    TreapNodeBase\
    \ *R;\n    int Rank;\n    int Size;\n    bool NeedFlip;\n\n    static inline xoshiro256starstar\
    \ gen{std::random_device{}()};\n    static inline std::uniform_int_distribution<int>\
    \ dis{0, 998244353};\n\n    TreapNode *derived() { return (TreapNode *)this; }\n\
    \n    // CRTP reimplement\n    void do_flip() {}\n    void do_propagate() {}\n\
    \    void do_update() {}\n\nprotected:\n    void base_flip() {\n        NeedFlip\
    \ = !NeedFlip;\n        std::swap(L, R);\n        derived()->do_flip();\n    }\n\
    \    void base_propagate() {\n        derived()->do_propagate();\n        if (NeedFlip)\
    \ {\n            NeedFlip = false;\n            if (L) L->base_flip();\n     \
    \       if (R) R->base_flip();\n        }\n    }\n    void base_update() {\n \
    \       Size = 1;\n        if (L) Size += L->Size;\n        if (R) Size += R->Size;\n\
    \        derived()->do_update();\n    }\n\n    static TreapNodeBase *base_join(TreapNodeBase\
    \ *a, TreapNodeBase *b) {\n        if (a == nullptr) return b;\n        if (b\
    \ == nullptr) return a;\n        a->base_propagate();\n        b->base_propagate();\n\
    \        if (a->Rank < b->Rank) {\n            b->L = base_join(a, b->L);\n  \
    \          b->base_update();\n            return b;\n        }\n        a->R =\
    \ base_join(a->R, b);\n        a->base_update();\n        return a;\n    }\n\n\
    \    static TreapNodeBase *base_join3(TreapNodeBase *a, TreapNodeBase *b, TreapNodeBase\
    \ *c) {\n        return base_join(base_join(a, b), c);\n    }\n\n    static std::pair<TreapNodeBase\
    \ *, TreapNodeBase *> base_split(TreapNodeBase *a, int k) {\n        if (a ==\
    \ nullptr) return {nullptr, nullptr};\n        if (k == 0) return {nullptr, a};\n\
    \        a->base_propagate();\n        const int leftsize = a->L != nullptr ?\
    \ a->L->Size : 0;\n        if (leftsize < k) {\n            auto [b, c] = base_split(a->R,\
    \ k - leftsize - 1);\n            a->R        = b;\n            a->base_update();\n\
    \            return {a, c};\n        }\n        auto [b, c] = base_split(a->L,\
    \ k);\n        a->L        = c;\n        a->base_update();\n        return {b,\
    \ a};\n    }\n\n    static std::tuple<TreapNodeBase *, TreapNodeBase *, TreapNodeBase\
    \ *>\n    base_split3(TreapNodeBase *a, int l, int m) {\n        auto [b, c] =\
    \ base_split(a, l);\n        auto [d, e] = base_split(c, m);\n        return {b,\
    \ d, e};\n    }\n\n    TreapNodeBase() : L(), R(), Rank(dis(gen)), Size(1), NeedFlip()\
    \ {}\n\npublic:\n    int size() const { return Size; }\n    int rank() const {\
    \ return Rank; }\n\n    TreapNode *left() const { return (TreapNode *)L; }\n \
    \   TreapNode *right() const { return (TreapNode *)R; }\n\n    void flip() { base_flip();\
    \ }\n    static TreapNode *join(TreapNode *a, TreapNode *b) { return (TreapNode\
    \ *)base_join(a, b); }\n    static TreapNode *join3(TreapNode *a, TreapNode *b,\
    \ TreapNode *c) {\n        return (TreapNode *)base_join3(a, b, c);\n    }\n \
    \   static std::pair<TreapNode *, TreapNode *> split(TreapNode *a, int k) {\n\
    \        auto [b, c] = base_split(a, k);\n        return {(TreapNode *)b, (TreapNode\
    \ *)c};\n    }\n    static std::tuple<TreapNode *, TreapNode *, TreapNode *> split3(TreapNode\
    \ *a, int l, int m) {\n        auto [b, c, d] = base_split3(a, l, m);\n      \
    \  return {(TreapNode *)b, (TreapNode *)c, (TreapNode *)d};\n    }\n};\n"
  code: "#pragma once\n\n#include \"rng.hpp\"\n#include <random>\n#include <tuple>\n\
    #include <utility>\n\ntemplate <typename TreapNode>\nclass TreapNodeBase {\n \
    \   TreapNodeBase *L;\n    TreapNodeBase *R;\n    int Rank;\n    int Size;\n \
    \   bool NeedFlip;\n\n    static inline xoshiro256starstar gen{std::random_device{}()};\n\
    \    static inline std::uniform_int_distribution<int> dis{0, 998244353};\n\n \
    \   TreapNode *derived() { return (TreapNode *)this; }\n\n    // CRTP reimplement\n\
    \    void do_flip() {}\n    void do_propagate() {}\n    void do_update() {}\n\n\
    protected:\n    void base_flip() {\n        NeedFlip = !NeedFlip;\n        std::swap(L,\
    \ R);\n        derived()->do_flip();\n    }\n    void base_propagate() {\n   \
    \     derived()->do_propagate();\n        if (NeedFlip) {\n            NeedFlip\
    \ = false;\n            if (L) L->base_flip();\n            if (R) R->base_flip();\n\
    \        }\n    }\n    void base_update() {\n        Size = 1;\n        if (L)\
    \ Size += L->Size;\n        if (R) Size += R->Size;\n        derived()->do_update();\n\
    \    }\n\n    static TreapNodeBase *base_join(TreapNodeBase *a, TreapNodeBase\
    \ *b) {\n        if (a == nullptr) return b;\n        if (b == nullptr) return\
    \ a;\n        a->base_propagate();\n        b->base_propagate();\n        if (a->Rank\
    \ < b->Rank) {\n            b->L = base_join(a, b->L);\n            b->base_update();\n\
    \            return b;\n        }\n        a->R = base_join(a->R, b);\n      \
    \  a->base_update();\n        return a;\n    }\n\n    static TreapNodeBase *base_join3(TreapNodeBase\
    \ *a, TreapNodeBase *b, TreapNodeBase *c) {\n        return base_join(base_join(a,\
    \ b), c);\n    }\n\n    static std::pair<TreapNodeBase *, TreapNodeBase *> base_split(TreapNodeBase\
    \ *a, int k) {\n        if (a == nullptr) return {nullptr, nullptr};\n       \
    \ if (k == 0) return {nullptr, a};\n        a->base_propagate();\n        const\
    \ int leftsize = a->L != nullptr ? a->L->Size : 0;\n        if (leftsize < k)\
    \ {\n            auto [b, c] = base_split(a->R, k - leftsize - 1);\n         \
    \   a->R        = b;\n            a->base_update();\n            return {a, c};\n\
    \        }\n        auto [b, c] = base_split(a->L, k);\n        a->L        =\
    \ c;\n        a->base_update();\n        return {b, a};\n    }\n\n    static std::tuple<TreapNodeBase\
    \ *, TreapNodeBase *, TreapNodeBase *>\n    base_split3(TreapNodeBase *a, int\
    \ l, int m) {\n        auto [b, c] = base_split(a, l);\n        auto [d, e] =\
    \ base_split(c, m);\n        return {b, d, e};\n    }\n\n    TreapNodeBase() :\
    \ L(), R(), Rank(dis(gen)), Size(1), NeedFlip() {}\n\npublic:\n    int size()\
    \ const { return Size; }\n    int rank() const { return Rank; }\n\n    TreapNode\
    \ *left() const { return (TreapNode *)L; }\n    TreapNode *right() const { return\
    \ (TreapNode *)R; }\n\n    void flip() { base_flip(); }\n    static TreapNode\
    \ *join(TreapNode *a, TreapNode *b) { return (TreapNode *)base_join(a, b); }\n\
    \    static TreapNode *join3(TreapNode *a, TreapNode *b, TreapNode *c) {\n   \
    \     return (TreapNode *)base_join3(a, b, c);\n    }\n    static std::pair<TreapNode\
    \ *, TreapNode *> split(TreapNode *a, int k) {\n        auto [b, c] = base_split(a,\
    \ k);\n        return {(TreapNode *)b, (TreapNode *)c};\n    }\n    static std::tuple<TreapNode\
    \ *, TreapNode *, TreapNode *> split3(TreapNode *a, int l, int m) {\n        auto\
    \ [b, c, d] = base_split3(a, l, m);\n        return {(TreapNode *)b, (TreapNode\
    \ *)c, (TreapNode *)d};\n    }\n};\n"
  dependsOn:
  - rng.hpp
  isVerificationFile: false
  path: treap_node_base.hpp
  requiredBy: []
  timestamp: '2024-06-20 22:48:12+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/range_reverse_range_sum.0.test.cpp
documentation_of: treap_node_base.hpp
layout: document
redirect_from:
- /library/treap_node_base.hpp
- /library/treap_node_base.hpp.html
title: treap_node_base.hpp
---
