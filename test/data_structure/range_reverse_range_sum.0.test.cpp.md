---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: rng.hpp
    title: rng.hpp
  - icon: ':heavy_check_mark:'
    path: treap_node_base.hpp
    title: treap_node_base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_reverse_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_reverse_range_sum
  bundledCode: "#line 1 \"test/data_structure/range_reverse_range_sum.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_reverse_range_sum\"\n\
    \n#line 2 \"treap_node_base.hpp\"\n\n#line 2 \"rng.hpp\"\n\n#include <cstdint>\n\
    #include <limits>\n\n// see: https://prng.di.unimi.it/xoshiro256starstar.c\n//\
    \ original license CC0 1.0\nclass xoshiro256starstar {\n    using u64 = std::uint64_t;\n\
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
    \n#include <array>\n#include <random>\n#include <utility>\n\ntemplate<typename\
    \ TreapNodeT> class TreapNodeBase {\n    TreapNodeBase *L;\n    TreapNodeBase\
    \ *R;\n    int Rank;\n    int Size;\n    bool NeedFlip;\n\n    static inline xoshiro256starstar\
    \ gen{std::random_device{}()};\n    static inline std::uniform_int_distribution<int>\
    \ dis{0, 998244353};\n\n    TreapNodeT *derived() { return (TreapNodeT *)this;\
    \ }\n\n    // CRTP reimplement\n    void do_flip() {}\n    void do_propagate()\
    \ {}\n    void do_update() {}\n\nprotected:\n    void base_flip() {\n        NeedFlip\
    \ = !NeedFlip;\n        std::swap(L, R);\n        derived()->do_flip();\n    }\n\
    \    // base_propagate() is called to propagate the update information to child(ren).\n\
    \    // There is no need to update the information combined from child(ren)\n\
    \    // which should be done in base_update().\n    void base_propagate() {\n\
    \        derived()->do_propagate();\n        if (NeedFlip) {\n            NeedFlip\
    \ = false;\n            if (L) L->base_flip();\n            if (R) R->base_flip();\n\
    \        }\n    }\n    // base_update() is called to update the information combined\
    \ from child(ren).\n    void base_update() {\n        Size = 1;\n        if (L)\
    \ Size += L->Size;\n        if (R) Size += R->Size;\n        derived()->do_update();\n\
    \    }\n\n    static TreapNodeBase *base_join(TreapNodeBase *a, TreapNodeBase\
    \ *b) {\n        if (a == nullptr) {\n            if (b) b->base_propagate(),\
    \ b->base_update();\n            return b;\n        }\n        if (b == nullptr)\
    \ {\n            if (a) a->base_propagate(), a->base_update();\n            return\
    \ a;\n        }\n        a->base_propagate();\n        b->base_propagate();\n\
    \        if (a->Rank < b->Rank) {\n            b->L = base_join(a, b->L);\n  \
    \          b->base_update();\n            return b;\n        }\n        a->R =\
    \ base_join(a->R, b);\n        a->base_update();\n        return a;\n    }\n\n\
    \    static std::array<TreapNodeBase *, 2> base_split(TreapNodeBase *a, int k)\
    \ {\n        if (a == nullptr) return {nullptr, nullptr};\n        a->base_propagate();\n\
    \        if (k == 0) return {nullptr, a};\n        if (k == a->Size) return {a,\
    \ nullptr};\n        const int leftsize = a->L != nullptr ? a->L->Size : 0;\n\
    \        if (leftsize < k) {\n            auto [b, c] = base_split(a->R, k - leftsize\
    \ - 1);\n            a->R        = b;\n            a->base_update();\n       \
    \     return {a, c};\n        }\n        auto [b, c] = base_split(a->L, k);\n\
    \        a->L        = c;\n        a->base_update();\n        return {b, a};\n\
    \    }\n\n    TreapNodeBase() : L(), R(), Rank(dis(gen)), Size(1), NeedFlip()\
    \ {}\n\npublic:\n    int size() const { return Size; }\n    int rank() const {\
    \ return Rank; }\n\n    TreapNodeT *left() const { return (TreapNodeT *)L; }\n\
    \    TreapNodeT *right() const { return (TreapNodeT *)R; }\n\n    void flip()\
    \ { base_flip(); }\n    template<typename... Nodes> static TreapNodeT *join(Nodes...\
    \ node) {\n        struct Helper {\n            TreapNodeBase *Val;\n        \
    \    Helper &operator|(TreapNodeBase *A) {\n                Val = TreapNodeBase::base_join(Val,\
    \ A);\n                return *this;\n            }\n        } nil{nullptr};\n\
    \        return (TreapNodeT *)(nil | ... | node).Val;\n    }\n    template<typename...\
    \ Parts>\n    static std::array<TreapNodeT *, sizeof...(Parts) + 1> split(TreapNodeT\
    \ *a, Parts... part) {\n        std::array<TreapNodeT *, sizeof...(Parts) + 1>\
    \ res;\n        res[0]    = a;\n        int index = 0;\n        (\n          \
    \  [&](int s) {\n                auto [l, r]  = base_split(res[index], s);\n \
    \               res[index]   = (TreapNodeT *)l;\n                res[++index]\
    \ = (TreapNodeT *)r;\n            }(part),\n            ...);\n        return\
    \ res;\n    }\n\n    TreapNodeT *select(int k) {\n        base_propagate();\n\
    \        const int leftsize = left() ? left()->size() : 0;\n        if (k == leftsize)\
    \ return (TreapNodeT *)this;\n        if (k < leftsize) return left()->select(k);\n\
    \        return right()->select(k - leftsize - 1);\n    }\n};\n#line 4 \"test/data_structure/range_reverse_range_sum.0.test.cpp\"\
    \n#include <iostream>\n#include <memory>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    struct TreapNode : TreapNodeBase<TreapNode> {\n\
    \        int Val;\n        long long Sum;\n        void do_update() {\n      \
    \      Sum = Val;\n            if (left()) Sum += left()->Sum;\n            if\
    \ (right()) Sum += right()->Sum;\n        }\n    };\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    auto buf        = std::make_unique<TreapNode[]>(n);\n    TreapNode\
    \ *root = nullptr;\n    for (int i = 0; i < n; ++i) {\n        std::cin >> buf[i].Val;\n\
    \        root = TreapNode::join(root, &buf[i]);\n    }\n    while (q--) {\n  \
    \      int t, l, r;\n        std::cin >> t >> l >> r;\n        auto [a, b, c]\
    \ = TreapNode::split(root, l, r - l);\n        if (t == 0) {\n            if (b)\
    \ b->flip();\n        } else {\n            std::cout << (b ? b->Sum : 0LL) <<\
    \ '\\n';\n        }\n        root = TreapNode::join(a, b, c);\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_reverse_range_sum\"\
    \n\n#include \"treap_node_base.hpp\"\n#include <iostream>\n#include <memory>\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    struct TreapNode : TreapNodeBase<TreapNode> {\n        int Val;\n       \
    \ long long Sum;\n        void do_update() {\n            Sum = Val;\n       \
    \     if (left()) Sum += left()->Sum;\n            if (right()) Sum += right()->Sum;\n\
    \        }\n    };\n    int n, q;\n    std::cin >> n >> q;\n    auto buf     \
    \   = std::make_unique<TreapNode[]>(n);\n    TreapNode *root = nullptr;\n    for\
    \ (int i = 0; i < n; ++i) {\n        std::cin >> buf[i].Val;\n        root = TreapNode::join(root,\
    \ &buf[i]);\n    }\n    while (q--) {\n        int t, l, r;\n        std::cin\
    \ >> t >> l >> r;\n        auto [a, b, c] = TreapNode::split(root, l, r - l);\n\
    \        if (t == 0) {\n            if (b) b->flip();\n        } else {\n    \
    \        std::cout << (b ? b->Sum : 0LL) << '\\n';\n        }\n        root =\
    \ TreapNode::join(a, b, c);\n    }\n    return 0;\n}\n"
  dependsOn:
  - treap_node_base.hpp
  - rng.hpp
  isVerificationFile: true
  path: test/data_structure/range_reverse_range_sum.0.test.cpp
  requiredBy: []
  timestamp: '2025-09-14 18:03:01+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/data_structure/range_reverse_range_sum.0.test.cpp
layout: document
redirect_from:
- /verify/test/data_structure/range_reverse_range_sum.0.test.cpp
- /verify/test/data_structure/range_reverse_range_sum.0.test.cpp.html
title: test/data_structure/range_reverse_range_sum.0.test.cpp
---
