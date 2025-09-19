---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: rng.hpp
    title: rng.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
    title: test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
  - icon: ':x:'
    path: test/data_structure/ordered_set.0.test.cpp
    title: test/data_structure/ordered_set.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/point_set_range_composite.0.test.cpp
    title: test/data_structure/point_set_range_composite.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/range_affine_point_get.0.test.cpp
    title: test/data_structure/range_affine_point_get.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/range_affine_range_sum.0.test.cpp
    title: test/data_structure/range_affine_range_sum.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/data_structure/range_reverse_range_sum.0.test.cpp
    title: test/data_structure/range_reverse_range_sum.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
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
    \n#include <array>\n#include <random>\n#include <utility>\n\ntemplate<typename\
    \ FlipableTreapNodeT> class FlipableTreapNodeBase;\n\ntemplate<typename TreapNodeT>\
    \ class TreapNodeBase {\n    friend class FlipableTreapNodeBase<TreapNodeT>;\n\
    \n    TreapNodeBase *L;\n    TreapNodeBase *R;\n    const int Rank;\n    int Size;\n\
    \n    TreapNodeT &underlying() { return (TreapNodeT &)*this; }\n    const TreapNodeT\
    \ &underlying() const { return (const TreapNodeT &)*this; }\n\n    static inline\
    \ xoshiro256starstar gen{std::random_device{}()};\n    static inline std::uniform_int_distribution<int>\
    \ dis{0, 998244353 - 1};\n\n    // CRTP reimplement\n    void do_propagate() {}\n\
    \    void do_update() {}\n\n    // base_propagate() is called to propagate the\
    \ update information to child(ren).\n    // There is no need to update the information\
    \ combined from child(ren)\n    // which should be done in base_update().\n  \
    \  void base_propagate() { underlying().do_propagate(); }\n    // base_update()\
    \ is called to update the information combined from child(ren).\n    void base_update()\
    \ {\n        Size = 1;\n        if (L) Size += L->Size;\n        if (R) Size +=\
    \ R->Size;\n        underlying().do_update();\n    }\n\n    static TreapNodeBase\
    \ *base_join(TreapNodeBase *a, TreapNodeBase *b) {\n        if (a == nullptr)\
    \ {\n            if (b) b->propagate(), b->update();\n            return b;\n\
    \        }\n        if (b == nullptr) {\n            if (a) a->propagate(), a->update();\n\
    \            return a;\n        }\n        a->propagate();\n        b->propagate();\n\
    \        // MAX HEAP\n        if (a->rank() < b->rank()) {\n            b->L =\
    \ base_join(a, b->L);\n            b->update();\n            return b;\n     \
    \   } else {\n            a->R = base_join(a->R, b);\n            a->update();\n\
    \            return a;\n        }\n    }\n\n    static std::array<TreapNodeBase\
    \ *, 2> base_split(TreapNodeBase *a, int k) {\n        if (a == nullptr) return\
    \ {nullptr, nullptr};\n        a->propagate();\n        if (k == 0) return {nullptr,\
    \ a};\n        if (k == a->Size) return {a, nullptr};\n        const int leftsize\
    \ = a->L != nullptr ? a->L->Size : 0;\n        if (leftsize < k) {\n         \
    \   auto [b, c] = base_split(a->R, k - leftsize - 1);\n            a->R      \
    \  = b;\n            a->update();\n            return {a, c};\n        } else\
    \ {\n            auto [b, c] = base_split(a->L, k);\n            a->L        =\
    \ c;\n            a->update();\n            return {b, a};\n        }\n    }\n\
    \n    TreapNodeBase *base_rotate_left() {\n        /*    x              b\n  \
    \           / \\            / \\\n            a   b    =>    x   d\n         \
    \      / \\        / \\\n              c   d      a   c    */\n        TreapNodeBase\
    \ *b = R;\n        b->propagate();\n        R = b->L, b->L = this;\n        update();\n\
    \        b->update();\n        return b;\n    }\n    TreapNodeBase *base_rotate_right()\
    \ {\n        /*    x              a\n             / \\            / \\\n     \
    \       a   b    =>    c   x\n           / \\                / \\\n          c\
    \   d              d   b */\n        TreapNodeBase *a = L;\n        a->propagate();\n\
    \        L = a->R, a->R = this;\n        update();\n        a->update();\n   \
    \     return a;\n    }\n\nprotected:\n    TreapNodeBase() : L(), R(), Rank(dis(gen)),\
    \ Size(1) {}\n\npublic:\n    int size() const { return Size; }\n    int rank()\
    \ const { return Rank; }\n    TreapNodeT *left() const { return (TreapNodeT *)L;\
    \ }\n    TreapNodeT *right() const { return (TreapNodeT *)R; }\n    void update()\
    \ { base_update(); }\n    void propagate() { underlying().base_propagate(); }\n\
    \    static TreapNodeT *insert(TreapNodeT *root, TreapNodeT *t) {\n        if\
    \ (root == nullptr) return t;\n        root->propagate();\n        if (std::as_const(*t)\
    \ < std::as_const(*root)) {\n            root->L = insert(root->left(), t);\n\
    \            root->update();\n            if (root->rank() < root->left()->rank())\
    \ return (TreapNodeT *)root->base_rotate_right();\n        } else {\n        \
    \    root->R = insert(root->right(), t);\n            root->update();\n      \
    \      if (root->rank() < root->right()->rank()) return (TreapNodeT *)root->base_rotate_left();\n\
    \        }\n        return root;\n    }\n    static int count_less_than(TreapNodeT\
    \ *root, const TreapNodeT *t) {\n        if (root == nullptr) return 0;\n    \
    \    root->propagate();\n        if (std::as_const(*root) < *t) {\n          \
    \  return (root->left() ? root->left()->size() : 0) + 1 +\n                  \
    \ count_less_than(root->right(), t);\n        } else {\n            return count_less_than(root->left(),\
    \ t);\n        }\n    }\n    // [<, >=]\n    static std::array<TreapNodeT *, 2>\
    \ split_less_than(TreapNodeT *root, const TreapNodeT *t) {\n        if (root ==\
    \ nullptr) return {nullptr, nullptr};\n        root->propagate();\n        if\
    \ (std::as_const(*root) < *t) {\n            auto [a, b] = split_less_than(root->right(),\
    \ t);\n            root->R     = a;\n            root->update();\n           \
    \ return {root, b};\n        } else {\n            auto [a, b] = split_less_than(root->left(),\
    \ t);\n            root->L     = b;\n            root->update();\n           \
    \ return {a, root};\n        }\n    }\n    static int count_greater_than(TreapNodeT\
    \ *root, const TreapNodeT *t) {\n        if (root == nullptr) return 0;\n    \
    \    root->propagate();\n        if (*t < std::as_const(*root)) {\n          \
    \  return (root->right() ? root->right()->size() : 0) + 1 +\n                \
    \   count_greater_than(root->left(), t);\n        } else {\n            return\
    \ count_greater_than(root->right(), t);\n        }\n    }\n    // [<=, >]\n  \
    \  static std::array<TreapNodeT *, 2> split_greater_than(TreapNodeT *root, const\
    \ TreapNodeT *t) {\n        if (root == nullptr) return {nullptr, nullptr};\n\
    \        root->propagate();\n        if (*t < std::as_const(*root)) {\n      \
    \      auto [a, b] = split_greater_than(root->left(), t);\n            root->L\
    \     = b;\n            root->update();\n            return {a, root};\n     \
    \   } else {\n            auto [a, b] = split_greater_than(root->right(), t);\n\
    \            root->R     = a;\n            root->update();\n            return\
    \ {root, b};\n        }\n    }\n    static int count(TreapNodeT *root, const TreapNodeT\
    \ *t) {\n        if (root == nullptr) return 0;\n        root->propagate();\n\
    \        if (*t < std::as_const(*root)) return count(root->left(), t);\n     \
    \   if (std::as_const(*root) < *t) return count(root->right(), t);\n        int\
    \ res = 1;\n        if (root->left()) res += root->left()->size() - count_less_than(root->left(),\
    \ t);\n        if (root->right()) res += root->right()->size() - count_greater_than(root->right(),\
    \ t);\n        return res;\n    }\n    static std::array<int, 3> count3(TreapNodeT\
    \ *root, const TreapNodeT *t) {\n        if (root == nullptr) return {0, 0, 0};\n\
    \        root->propagate();\n        if (*t < std::as_const(*root)) {\n      \
    \      auto [a, b, c] = count3(root->left(), t);\n            return {a, b, c\
    \ + 1 + (root->right() ? root->right()->size() : 0)};\n        }\n        if (std::as_const(*root)\
    \ < *t) {\n            auto [a, b, c] = count3(root->right(), t);\n          \
    \  return {a + 1 + (root->left() ? root->left()->size() : 0), b, c};\n       \
    \ }\n        const int a = count_less_than(root->left(), t);\n        const int\
    \ c = count_greater_than(root->right(), t);\n        return {a, root->size() -\
    \ a - c, c};\n    }\n    static std::array<TreapNodeT *, 3> split3(TreapNodeT\
    \ *root, const TreapNodeT *t) {\n        if (root == nullptr) return {nullptr,\
    \ nullptr, nullptr};\n        root->propagate();\n        if (*t < std::as_const(*root))\
    \ {\n            auto [a, b, c] = split3(root->left(), t);\n            root->L\
    \        = c;\n            root->update();\n            return {a, b, root};\n\
    \        }\n        if (std::as_const(*root) < *t) {\n            auto [a, b,\
    \ c] = split3(root->right(), t);\n            root->R        = a;\n          \
    \  root->update();\n            return {root, b, c};\n        }\n        auto\
    \ [a, b] = split_less_than(root->left(), t);\n        auto [c, d] = split_greater_than(root->right(),\
    \ t);\n        root->L = b, root->R = c;\n        root->update();\n        return\
    \ {a, root, d};\n    }\n    static TreapNodeT *predecessor(TreapNodeT *root, const\
    \ TreapNodeT *t) {\n        TreapNodeT *res = root;\n        while (root) {\n\
    \            root->propagate();\n            if (std::as_const(*root) < *t) {\n\
    \                res = root, root = root->right();\n            } else {\n   \
    \             root = root->left();\n            }\n        }\n        return res;\n\
    \    }\n    static TreapNodeT *successor(TreapNodeT *root, const TreapNodeT *t)\
    \ {\n        TreapNodeT *res = root;\n        while (root) {\n            root->propagate();\n\
    \            if (*t < std::as_const(*root)) {\n                res = root, root\
    \ = root->left();\n            } else {\n                root = root->right();\n\
    \            }\n        }\n        return res;\n    }\n\n    template<typename...\
    \ Nodes> static TreapNodeT *join(Nodes... node) {\n        struct Helper {\n \
    \           TreapNodeBase *Val;\n            Helper &operator|(TreapNodeBase *A)\
    \ {\n                Val = TreapNodeBase::base_join(Val, A);\n               \
    \ return *this;\n            }\n        } nil{nullptr};\n        return (TreapNodeT\
    \ *)(nil | ... | node).Val;\n    }\n    template<typename... Parts>\n    static\
    \ std::array<TreapNodeT *, sizeof...(Parts) + 1> split(TreapNodeT *a, Parts...\
    \ part) {\n        std::array<TreapNodeT *, sizeof...(Parts) + 1> res;\n     \
    \   res[0]    = a;\n        int index = 0;\n        (\n            [&](int s)\
    \ {\n                auto [l, r]  = base_split(res[index], s);\n             \
    \   res[index]   = (TreapNodeT *)l;\n                res[++index] = (TreapNodeT\
    \ *)r;\n            }(part),\n            ...);\n        return res;\n    }\n\n\
    \    static TreapNodeT *find(TreapNodeT *root, const TreapNodeT *t) {\n      \
    \  if (root == nullptr) return nullptr;\n        root->propagate();\n        if\
    \ (std::as_const(*root) < *t) return find(root->right(), t);\n        if (*t <\
    \ std::as_const(*root)) return find(root->left(), t);\n        return root;\n\
    \    }\n\n    TreapNodeT *select(int k) {\n        propagate();\n        const\
    \ int leftsize = left() ? left()->size() : 0;\n        if (k == leftsize) return\
    \ (TreapNodeT *)this;\n        if (k < leftsize) return left()->select(k);\n \
    \       return right()->select(k - leftsize - 1);\n    }\n};\n\ntemplate<typename\
    \ FlipableTreapNodeT> class FlipableTreapNodeBase\n    : public TreapNodeBase<FlipableTreapNodeT>\
    \ {\n    friend class TreapNodeBase<FlipableTreapNodeT>;\n\n    bool NeedFlip;\n\
    \n    FlipableTreapNodeT &underlying() { return (FlipableTreapNodeT &)*this; }\n\
    \    const FlipableTreapNodeT &underlying() const { return (const FlipableTreapNodeT\
    \ &)*this; }\n\n    // CRTP reimplement\n    void do_flip() {}\n\n    void base_flip()\
    \ {\n        NeedFlip = !NeedFlip;\n        std::swap(this->L, this->R);\n   \
    \     underlying().do_flip();\n    }\n    void base_propagate() {\n        underlying().do_propagate();\n\
    \        if (NeedFlip) {\n            NeedFlip = false;\n            if (this->left())\
    \ this->left()->underlying().base_flip();\n            if (this->right()) this->right()->underlying().base_flip();\n\
    \        }\n    }\n\nprotected:\n    FlipableTreapNodeBase() : NeedFlip() {}\n\
    \npublic:\n    void flip() { base_flip(); }\n};\n"
  code: "#pragma once\n\n#include \"rng.hpp\"\n#include <array>\n#include <random>\n\
    #include <utility>\n\ntemplate<typename FlipableTreapNodeT> class FlipableTreapNodeBase;\n\
    \ntemplate<typename TreapNodeT> class TreapNodeBase {\n    friend class FlipableTreapNodeBase<TreapNodeT>;\n\
    \n    TreapNodeBase *L;\n    TreapNodeBase *R;\n    const int Rank;\n    int Size;\n\
    \n    TreapNodeT &underlying() { return (TreapNodeT &)*this; }\n    const TreapNodeT\
    \ &underlying() const { return (const TreapNodeT &)*this; }\n\n    static inline\
    \ xoshiro256starstar gen{std::random_device{}()};\n    static inline std::uniform_int_distribution<int>\
    \ dis{0, 998244353 - 1};\n\n    // CRTP reimplement\n    void do_propagate() {}\n\
    \    void do_update() {}\n\n    // base_propagate() is called to propagate the\
    \ update information to child(ren).\n    // There is no need to update the information\
    \ combined from child(ren)\n    // which should be done in base_update().\n  \
    \  void base_propagate() { underlying().do_propagate(); }\n    // base_update()\
    \ is called to update the information combined from child(ren).\n    void base_update()\
    \ {\n        Size = 1;\n        if (L) Size += L->Size;\n        if (R) Size +=\
    \ R->Size;\n        underlying().do_update();\n    }\n\n    static TreapNodeBase\
    \ *base_join(TreapNodeBase *a, TreapNodeBase *b) {\n        if (a == nullptr)\
    \ {\n            if (b) b->propagate(), b->update();\n            return b;\n\
    \        }\n        if (b == nullptr) {\n            if (a) a->propagate(), a->update();\n\
    \            return a;\n        }\n        a->propagate();\n        b->propagate();\n\
    \        // MAX HEAP\n        if (a->rank() < b->rank()) {\n            b->L =\
    \ base_join(a, b->L);\n            b->update();\n            return b;\n     \
    \   } else {\n            a->R = base_join(a->R, b);\n            a->update();\n\
    \            return a;\n        }\n    }\n\n    static std::array<TreapNodeBase\
    \ *, 2> base_split(TreapNodeBase *a, int k) {\n        if (a == nullptr) return\
    \ {nullptr, nullptr};\n        a->propagate();\n        if (k == 0) return {nullptr,\
    \ a};\n        if (k == a->Size) return {a, nullptr};\n        const int leftsize\
    \ = a->L != nullptr ? a->L->Size : 0;\n        if (leftsize < k) {\n         \
    \   auto [b, c] = base_split(a->R, k - leftsize - 1);\n            a->R      \
    \  = b;\n            a->update();\n            return {a, c};\n        } else\
    \ {\n            auto [b, c] = base_split(a->L, k);\n            a->L        =\
    \ c;\n            a->update();\n            return {b, a};\n        }\n    }\n\
    \n    TreapNodeBase *base_rotate_left() {\n        /*    x              b\n  \
    \           / \\            / \\\n            a   b    =>    x   d\n         \
    \      / \\        / \\\n              c   d      a   c    */\n        TreapNodeBase\
    \ *b = R;\n        b->propagate();\n        R = b->L, b->L = this;\n        update();\n\
    \        b->update();\n        return b;\n    }\n    TreapNodeBase *base_rotate_right()\
    \ {\n        /*    x              a\n             / \\            / \\\n     \
    \       a   b    =>    c   x\n           / \\                / \\\n          c\
    \   d              d   b */\n        TreapNodeBase *a = L;\n        a->propagate();\n\
    \        L = a->R, a->R = this;\n        update();\n        a->update();\n   \
    \     return a;\n    }\n\nprotected:\n    TreapNodeBase() : L(), R(), Rank(dis(gen)),\
    \ Size(1) {}\n\npublic:\n    int size() const { return Size; }\n    int rank()\
    \ const { return Rank; }\n    TreapNodeT *left() const { return (TreapNodeT *)L;\
    \ }\n    TreapNodeT *right() const { return (TreapNodeT *)R; }\n    void update()\
    \ { base_update(); }\n    void propagate() { underlying().base_propagate(); }\n\
    \    static TreapNodeT *insert(TreapNodeT *root, TreapNodeT *t) {\n        if\
    \ (root == nullptr) return t;\n        root->propagate();\n        if (std::as_const(*t)\
    \ < std::as_const(*root)) {\n            root->L = insert(root->left(), t);\n\
    \            root->update();\n            if (root->rank() < root->left()->rank())\
    \ return (TreapNodeT *)root->base_rotate_right();\n        } else {\n        \
    \    root->R = insert(root->right(), t);\n            root->update();\n      \
    \      if (root->rank() < root->right()->rank()) return (TreapNodeT *)root->base_rotate_left();\n\
    \        }\n        return root;\n    }\n    static int count_less_than(TreapNodeT\
    \ *root, const TreapNodeT *t) {\n        if (root == nullptr) return 0;\n    \
    \    root->propagate();\n        if (std::as_const(*root) < *t) {\n          \
    \  return (root->left() ? root->left()->size() : 0) + 1 +\n                  \
    \ count_less_than(root->right(), t);\n        } else {\n            return count_less_than(root->left(),\
    \ t);\n        }\n    }\n    // [<, >=]\n    static std::array<TreapNodeT *, 2>\
    \ split_less_than(TreapNodeT *root, const TreapNodeT *t) {\n        if (root ==\
    \ nullptr) return {nullptr, nullptr};\n        root->propagate();\n        if\
    \ (std::as_const(*root) < *t) {\n            auto [a, b] = split_less_than(root->right(),\
    \ t);\n            root->R     = a;\n            root->update();\n           \
    \ return {root, b};\n        } else {\n            auto [a, b] = split_less_than(root->left(),\
    \ t);\n            root->L     = b;\n            root->update();\n           \
    \ return {a, root};\n        }\n    }\n    static int count_greater_than(TreapNodeT\
    \ *root, const TreapNodeT *t) {\n        if (root == nullptr) return 0;\n    \
    \    root->propagate();\n        if (*t < std::as_const(*root)) {\n          \
    \  return (root->right() ? root->right()->size() : 0) + 1 +\n                \
    \   count_greater_than(root->left(), t);\n        } else {\n            return\
    \ count_greater_than(root->right(), t);\n        }\n    }\n    // [<=, >]\n  \
    \  static std::array<TreapNodeT *, 2> split_greater_than(TreapNodeT *root, const\
    \ TreapNodeT *t) {\n        if (root == nullptr) return {nullptr, nullptr};\n\
    \        root->propagate();\n        if (*t < std::as_const(*root)) {\n      \
    \      auto [a, b] = split_greater_than(root->left(), t);\n            root->L\
    \     = b;\n            root->update();\n            return {a, root};\n     \
    \   } else {\n            auto [a, b] = split_greater_than(root->right(), t);\n\
    \            root->R     = a;\n            root->update();\n            return\
    \ {root, b};\n        }\n    }\n    static int count(TreapNodeT *root, const TreapNodeT\
    \ *t) {\n        if (root == nullptr) return 0;\n        root->propagate();\n\
    \        if (*t < std::as_const(*root)) return count(root->left(), t);\n     \
    \   if (std::as_const(*root) < *t) return count(root->right(), t);\n        int\
    \ res = 1;\n        if (root->left()) res += root->left()->size() - count_less_than(root->left(),\
    \ t);\n        if (root->right()) res += root->right()->size() - count_greater_than(root->right(),\
    \ t);\n        return res;\n    }\n    static std::array<int, 3> count3(TreapNodeT\
    \ *root, const TreapNodeT *t) {\n        if (root == nullptr) return {0, 0, 0};\n\
    \        root->propagate();\n        if (*t < std::as_const(*root)) {\n      \
    \      auto [a, b, c] = count3(root->left(), t);\n            return {a, b, c\
    \ + 1 + (root->right() ? root->right()->size() : 0)};\n        }\n        if (std::as_const(*root)\
    \ < *t) {\n            auto [a, b, c] = count3(root->right(), t);\n          \
    \  return {a + 1 + (root->left() ? root->left()->size() : 0), b, c};\n       \
    \ }\n        const int a = count_less_than(root->left(), t);\n        const int\
    \ c = count_greater_than(root->right(), t);\n        return {a, root->size() -\
    \ a - c, c};\n    }\n    static std::array<TreapNodeT *, 3> split3(TreapNodeT\
    \ *root, const TreapNodeT *t) {\n        if (root == nullptr) return {nullptr,\
    \ nullptr, nullptr};\n        root->propagate();\n        if (*t < std::as_const(*root))\
    \ {\n            auto [a, b, c] = split3(root->left(), t);\n            root->L\
    \        = c;\n            root->update();\n            return {a, b, root};\n\
    \        }\n        if (std::as_const(*root) < *t) {\n            auto [a, b,\
    \ c] = split3(root->right(), t);\n            root->R        = a;\n          \
    \  root->update();\n            return {root, b, c};\n        }\n        auto\
    \ [a, b] = split_less_than(root->left(), t);\n        auto [c, d] = split_greater_than(root->right(),\
    \ t);\n        root->L = b, root->R = c;\n        root->update();\n        return\
    \ {a, root, d};\n    }\n    static TreapNodeT *predecessor(TreapNodeT *root, const\
    \ TreapNodeT *t) {\n        TreapNodeT *res = root;\n        while (root) {\n\
    \            root->propagate();\n            if (std::as_const(*root) < *t) {\n\
    \                res = root, root = root->right();\n            } else {\n   \
    \             root = root->left();\n            }\n        }\n        return res;\n\
    \    }\n    static TreapNodeT *successor(TreapNodeT *root, const TreapNodeT *t)\
    \ {\n        TreapNodeT *res = root;\n        while (root) {\n            root->propagate();\n\
    \            if (*t < std::as_const(*root)) {\n                res = root, root\
    \ = root->left();\n            } else {\n                root = root->right();\n\
    \            }\n        }\n        return res;\n    }\n\n    template<typename...\
    \ Nodes> static TreapNodeT *join(Nodes... node) {\n        struct Helper {\n \
    \           TreapNodeBase *Val;\n            Helper &operator|(TreapNodeBase *A)\
    \ {\n                Val = TreapNodeBase::base_join(Val, A);\n               \
    \ return *this;\n            }\n        } nil{nullptr};\n        return (TreapNodeT\
    \ *)(nil | ... | node).Val;\n    }\n    template<typename... Parts>\n    static\
    \ std::array<TreapNodeT *, sizeof...(Parts) + 1> split(TreapNodeT *a, Parts...\
    \ part) {\n        std::array<TreapNodeT *, sizeof...(Parts) + 1> res;\n     \
    \   res[0]    = a;\n        int index = 0;\n        (\n            [&](int s)\
    \ {\n                auto [l, r]  = base_split(res[index], s);\n             \
    \   res[index]   = (TreapNodeT *)l;\n                res[++index] = (TreapNodeT\
    \ *)r;\n            }(part),\n            ...);\n        return res;\n    }\n\n\
    \    static TreapNodeT *find(TreapNodeT *root, const TreapNodeT *t) {\n      \
    \  if (root == nullptr) return nullptr;\n        root->propagate();\n        if\
    \ (std::as_const(*root) < *t) return find(root->right(), t);\n        if (*t <\
    \ std::as_const(*root)) return find(root->left(), t);\n        return root;\n\
    \    }\n\n    TreapNodeT *select(int k) {\n        propagate();\n        const\
    \ int leftsize = left() ? left()->size() : 0;\n        if (k == leftsize) return\
    \ (TreapNodeT *)this;\n        if (k < leftsize) return left()->select(k);\n \
    \       return right()->select(k - leftsize - 1);\n    }\n};\n\ntemplate<typename\
    \ FlipableTreapNodeT> class FlipableTreapNodeBase\n    : public TreapNodeBase<FlipableTreapNodeT>\
    \ {\n    friend class TreapNodeBase<FlipableTreapNodeT>;\n\n    bool NeedFlip;\n\
    \n    FlipableTreapNodeT &underlying() { return (FlipableTreapNodeT &)*this; }\n\
    \    const FlipableTreapNodeT &underlying() const { return (const FlipableTreapNodeT\
    \ &)*this; }\n\n    // CRTP reimplement\n    void do_flip() {}\n\n    void base_flip()\
    \ {\n        NeedFlip = !NeedFlip;\n        std::swap(this->L, this->R);\n   \
    \     underlying().do_flip();\n    }\n    void base_propagate() {\n        underlying().do_propagate();\n\
    \        if (NeedFlip) {\n            NeedFlip = false;\n            if (this->left())\
    \ this->left()->underlying().base_flip();\n            if (this->right()) this->right()->underlying().base_flip();\n\
    \        }\n    }\n\nprotected:\n    FlipableTreapNodeBase() : NeedFlip() {}\n\
    \npublic:\n    void flip() { base_flip(); }\n};\n"
  dependsOn:
  - rng.hpp
  isVerificationFile: false
  path: treap_node_base.hpp
  requiredBy: []
  timestamp: '2025-09-19 19:07:41+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
  - test/data_structure/range_affine_range_sum.0.test.cpp
  - test/data_structure/point_set_range_composite.0.test.cpp
  - test/data_structure/ordered_set.0.test.cpp
  - test/data_structure/range_affine_point_get.0.test.cpp
  - test/data_structure/range_reverse_range_sum.0.test.cpp
documentation_of: treap_node_base.hpp
layout: document
redirect_from:
- /library/treap_node_base.hpp
- /library/treap_node_base.hpp.html
title: treap_node_base.hpp
---
