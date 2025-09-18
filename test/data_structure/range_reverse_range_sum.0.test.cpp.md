---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: node_pool.hpp
    title: node_pool.hpp
  - icon: ':x:'
    path: splay_tree_node_base.hpp
    title: splay_tree_node_base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/range_reverse_range_sum
    links:
    - https://judge.yosupo.jp/problem/range_reverse_range_sum
  bundledCode: "#line 1 \"test/data_structure/range_reverse_range_sum.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_reverse_range_sum\"\n\
    \n#line 2 \"node_pool.hpp\"\n\n#include <list>\n#include <memory>\n#include <utility>\n\
    #include <vector>\n\ntemplate<typename NodeT> class FixedSizeNodePool {\n    std::vector<NodeT>\
    \ pool;\n\npublic:\n    explicit FixedSizeNodePool(int n) : pool(n) {}\n    NodeT\
    \ *at(int ind) { return pool.data() + ind; }\n    int id(NodeT *a) const { return\
    \ a - pool.data(); }\n    auto get_func() {\n        return std::make_pair([this](int\
    \ ind) { return at(ind); },\n                              [this](NodeT *a) {\
    \ return id(a); });\n    }\n};\n\ntemplate<typename NodeT> class DynamicSizeNodePool\
    \ {\n    struct Wrapped : public NodeT {\n        using NodeT::NodeT;\n      \
    \  typename std::list<Wrapped>::iterator i;\n    };\n    std::list<Wrapped> used_list;\n\
    \    std::list<Wrapped> free_list;\n\npublic:\n    template<typename... Args>\
    \ NodeT *make(Args &&...arg) {\n        if (free_list.empty()) {\n           \
    \ auto &&node = used_list.emplace_back(std::forward<Args>(arg)...);\n        \
    \    node.i      = std::prev(used_list.end());\n            return std::addressof(node);\n\
    \        }\n        used_list.splice(used_list.end(), free_list, std::prev(free_list.end()));\n\
    \        auto &&node = used_list.back();\n        node.~NodeT(); // i remains\
    \ unchanged\n        new (std::addressof(node)) NodeT(std::forward<Args>(arg)...);\n\
    \        return std::addressof(node);\n    }\n    // this is lazy, if sth. relies\
    \ on the order of dtor, do NOT use\n    void retrieve(NodeT *node) {\n       \
    \ free_list.splice(free_list.end(), used_list, ((Wrapped *)node)->i);\n    }\n\
    };\n#line 2 \"splay_tree_node_base.hpp\"\n\n#include <array>\n#line 5 \"splay_tree_node_base.hpp\"\
    \n\ntemplate<typename FlipableSplayTreeNodeT> class FlipableSplayTreeNodeBase;\n\
    \ntemplate<typename SplayTreeNodeT> class SplayTreeNodeBase {\n    friend class\
    \ FlipableSplayTreeNodeBase<SplayTreeNodeT>;\n\n    SplayTreeNodeBase *L;\n  \
    \  SplayTreeNodeBase *R;\n    SplayTreeNodeBase *P;\n    int Size;\n\n    SplayTreeNodeT\
    \ &underlying() { return (SplayTreeNodeT &)*this; }\n    const SplayTreeNodeT\
    \ &underlying() const { return (const SplayTreeNodeT &)*this; }\n\n    enum class\
    \ Child { LEFT, RIGHT };\n    Child which() const { return P->L == this ? Child::LEFT\
    \ : Child::RIGHT; }\n    bool is_root() const { return P == nullptr; }\n    bool\
    \ is_left_child() const { return which() == Child::LEFT; }\n    bool is_right_child()\
    \ const { return which() == Child::RIGHT; }\n\nprotected:\n    // CRTP reimplement\n\
    \    void do_propagate() {}\n    void do_update() {}\n\n    // base_propagate()\
    \ is called to propagate the update information to child(ren).\n    // There is\
    \ no need to update the information combined from child(ren)\n    // which should\
    \ be done in base_update().\n    // * CRTP reimplementable\n    void base_propagate()\
    \ { underlying().do_propagate(); }\n    // base_update() is called to update the\
    \ information combined from child(ren).\n    void base_update() {\n        Size\
    \ = 1;\n        if (L) Size += L->Size;\n        if (R) Size += R->Size;\n   \
    \     underlying().do_update();\n    }\n    void base_rotate() {\n        P->propagate();\n\
    \        propagate();\n        if (is_left_child()) {\n            if ((P->L =\
    \ R)) R->P = P;\n            if (!P->is_root()) {\n                if (P->is_left_child())\
    \ P->P->L = this;\n                else { P->P->R = this; }\n            }\n \
    \           R = P, P = P->P, R->P = this;\n            R->update();\n        }\
    \ else {\n            if ((P->R = L)) L->P = P;\n            if (!P->is_root())\
    \ {\n                if (P->is_left_child()) P->P->L = this;\n               \
    \ else { P->P->R = this; }\n            }\n            L = P, P = P->P, L->P =\
    \ this;\n            L->update();\n        }\n    }\n    static SplayTreeNodeBase\
    \ *base_join(SplayTreeNodeBase *a, SplayTreeNodeBase *b) {\n        if (a == nullptr)\
    \ {\n            if (b) b->propagate(), b->update();\n            return b;\n\
    \        }\n        if (b == nullptr) {\n            if (a) a->propagate(), a->update();\n\
    \            return a;\n        }\n        a->propagate();\n        while (a->R)\
    \ {\n            a = a->R;\n            a->propagate();\n        }\n        a->splay();\n\
    \        b->propagate();\n        a->R = b, b->P = a;\n        a->update();\n\
    \        return a;\n    }\n    static std::array<SplayTreeNodeBase *, 2> base_split(SplayTreeNodeBase\
    \ *a, int k) {\n        if (a == nullptr) return {nullptr, nullptr};\n       \
    \ a->propagate();\n        if (k == 0) return {nullptr, a};\n        if (k ==\
    \ a->Size) return {a, nullptr};\n        SplayTreeNodeBase *aa = a->select(k),\
    \ *b = aa->L;\n        aa->L = nullptr;\n        if (b) {\n            b->propagate();\n\
    \            b->P = nullptr;\n        }\n        aa->update();\n        return\
    \ {b, aa};\n    }\n\n    SplayTreeNodeBase() : L(), R(), P(), Size(1) {}\n\npublic:\n\
    \    int size() const { return Size; }\n    SplayTreeNodeT *left() const { return\
    \ (SplayTreeNodeT *)L; }\n    SplayTreeNodeT *right() const { return (SplayTreeNodeT\
    \ *)R; }\n    SplayTreeNodeT *parent() const { return (SplayTreeNodeT *)P; }\n\
    \    void update() { base_update(); }\n    void propagate() { underlying().base_propagate();\
    \ }\n    void splay(SplayTreeNodeT *guard = nullptr) {\n        for (propagate();\
    \ (SplayTreeNodeT *)P != guard; base_rotate()) {\n            if ((SplayTreeNodeT\
    \ *)P->P != guard) {\n                P->P->propagate();\n                P->which()\
    \ == which() ? P->base_rotate() : base_rotate();\n            }\n        }\n \
    \       update();\n    }\n    template<typename... Nodes> static SplayTreeNodeT\
    \ *join(Nodes... node) {\n        struct Helper {\n            SplayTreeNodeBase\
    \ *Val;\n            Helper &operator|(SplayTreeNodeBase *A) {\n             \
    \   Val = SplayTreeNodeBase::base_join(Val, A);\n                return *this;\n\
    \            }\n        } nil{nullptr};\n        return (SplayTreeNodeT *)(nil\
    \ | ... | node).Val;\n    }\n    template<typename... Parts> static std::array<SplayTreeNodeT\
    \ *, sizeof...(Parts) + 1>\n    split(SplayTreeNodeT *a, Parts... part) {\n  \
    \      std::array<SplayTreeNodeT *, sizeof...(Parts) + 1> res;\n        res[0]\
    \    = a;\n        int index = 0;\n        // clang-format off\n        ([&](int\
    \ s) {\n            const auto [l, r]  = base_split(res[index], s);\n        \
    \    res[index]   = (SplayTreeNodeT *)l;\n            res[++index] = (SplayTreeNodeT\
    \ *)r; }(part), ...);\n        // clang-format on\n        return res;\n    }\n\
    \    SplayTreeNodeT *select(int k) {\n        SplayTreeNodeBase *a = this;\n \
    \       a->propagate();\n        while ((a->L ? a->L->Size : 0) != k) {\n    \
    \        if ((a->L ? a->L->Size : 0) < k) {\n                k -= (a->L ? a->L->Size\
    \ : 0) + 1;\n                a = a->R;\n            } else {\n               \
    \ a = a->L;\n            }\n            a->propagate();\n        }\n        a->splay();\n\
    \        return (SplayTreeNodeT *)a;\n    }\n};\n\ntemplate<typename FlipableSplayTreeNodeT>\
    \ class FlipableSplayTreeNodeBase\n    : public SplayTreeNodeBase<FlipableSplayTreeNodeT>\
    \ {\n    friend class SplayTreeNodeBase<FlipableSplayTreeNodeT>;\n\n    bool NeedFlip;\n\
    \n    FlipableSplayTreeNodeT &underlying() { return (FlipableSplayTreeNodeT &)*this;\
    \ }\n    const FlipableSplayTreeNodeT &underlying() const {\n        return (const\
    \ FlipableSplayTreeNodeT &)*this;\n    }\n\nprotected:\n    // CRTP reimplement\n\
    \    void do_flip() {}\n\n    void base_flip() {\n        NeedFlip = !NeedFlip;\n\
    \        std::swap(this->L, this->R);\n        underlying().do_flip();\n    }\n\
    \    void base_propagate() {\n        underlying().do_propagate();\n        if\
    \ (NeedFlip) {\n            NeedFlip = false;\n            if (this->left()) this->left()->underlying().base_flip();\n\
    \            if (this->right()) this->right()->underlying().base_flip();\n   \
    \     }\n    }\n\n    FlipableSplayTreeNodeBase() : NeedFlip() {}\n\npublic:\n\
    \    void flip() { base_flip(); }\n};\n#line 5 \"test/data_structure/range_reverse_range_sum.0.test.cpp\"\
    \n#include <iostream>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    struct Node : FlipableSplayTreeNodeBase<Node>\
    \ {\n        int Val;\n        long long Sum;\n        void do_update() {\n  \
    \          Sum = Val;\n            if (left()) Sum += left()->Sum;\n         \
    \   if (right()) Sum += right()->Sum;\n        }\n    };\n    int n, q;\n    std::cin\
    \ >> n >> q;\n    FixedSizeNodePool<Node> pool(n);\n    auto [node, id] = pool.get_func();\n\
    \    Node *root      = nullptr;\n    for (int i = 0; i < n; ++i) {\n        std::cin\
    \ >> node(i)->Val;\n        root = Node::join(root, node(i));\n    }\n    while\
    \ (q--) {\n        int t, l, r;\n        std::cin >> t >> l >> r;\n        auto\
    \ [a, b, c] = Node::split(root, l, r - l);\n        if (t == 0) {\n          \
    \  if (b) b->flip();\n        } else {\n            std::cout << (b ? b->Sum :\
    \ 0LL) << '\\n';\n        }\n        root = Node::join(a, b, c);\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_reverse_range_sum\"\
    \n\n#include \"node_pool.hpp\"\n#include \"splay_tree_node_base.hpp\"\n#include\
    \ <iostream>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    struct Node : FlipableSplayTreeNodeBase<Node> {\n        int Val;\n     \
    \   long long Sum;\n        void do_update() {\n            Sum = Val;\n     \
    \       if (left()) Sum += left()->Sum;\n            if (right()) Sum += right()->Sum;\n\
    \        }\n    };\n    int n, q;\n    std::cin >> n >> q;\n    FixedSizeNodePool<Node>\
    \ pool(n);\n    auto [node, id] = pool.get_func();\n    Node *root      = nullptr;\n\
    \    for (int i = 0; i < n; ++i) {\n        std::cin >> node(i)->Val;\n      \
    \  root = Node::join(root, node(i));\n    }\n    while (q--) {\n        int t,\
    \ l, r;\n        std::cin >> t >> l >> r;\n        auto [a, b, c] = Node::split(root,\
    \ l, r - l);\n        if (t == 0) {\n            if (b) b->flip();\n        }\
    \ else {\n            std::cout << (b ? b->Sum : 0LL) << '\\n';\n        }\n \
    \       root = Node::join(a, b, c);\n    }\n    return 0;\n}\n"
  dependsOn:
  - node_pool.hpp
  - splay_tree_node_base.hpp
  isVerificationFile: true
  path: test/data_structure/range_reverse_range_sum.0.test.cpp
  requiredBy: []
  timestamp: '2025-09-18 20:33:53+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/data_structure/range_reverse_range_sum.0.test.cpp
layout: document
redirect_from:
- /verify/test/data_structure/range_reverse_range_sum.0.test.cpp
- /verify/test/data_structure/range_reverse_range_sum.0.test.cpp.html
title: test/data_structure/range_reverse_range_sum.0.test.cpp
---
