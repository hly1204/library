---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: avl_tree_node_base.hpp
    title: avl_tree_node_base.hpp
  - icon: ':heavy_check_mark:'
    path: node_pool.hpp
    title: node_pool.hpp
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
  bundledCode: "#line 1 \"test/data_structure/range_reverse_range_sum.1.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_reverse_range_sum\"\n\
    \n#line 2 \"avl_tree_node_base.hpp\"\n\n#include <algorithm>\n#include <array>\n\
    #include <cassert>\n#include <utility>\n\ntemplate<typename FlipableAVLTreeNodeT>\
    \ class FlipableAVLTreeNodeBase;\n\ntemplate<typename AVLTreeNodeT> class AVLTreeNodeBase\
    \ {\n    friend class FlipableAVLTreeNodeBase<AVLTreeNodeT>;\n\n    AVLTreeNodeBase\
    \ *L;\n    AVLTreeNodeBase *R;\n    int Height;\n    int Size;\n\n    AVLTreeNodeT\
    \ &underlying() { return (AVLTreeNodeT &)*this; }\n    const AVLTreeNodeT &underlying()\
    \ const { return (const AVLTreeNodeT &)*this; }\n\n    // CRTP reimplement\n \
    \   void do_propagate() {}\n    void do_update() {}\n\n    // base_propagate()\
    \ is called to propagate the update information to child(ren).\n    // There is\
    \ no need to update the information combined from child(ren)\n    // which should\
    \ be done in base_update().\n    void base_propagate() { underlying().do_propagate();\
    \ }\n    // base_update() is called to update the information combined from child(ren).\n\
    \    void base_update() {\n        Size = 1;\n        if (L) Size += L->Size;\n\
    \        if (R) Size += R->Size;\n        Height = std::max(L ? L->Height : 0,\
    \ R ? R->Height : 0) + 1;\n        underlying().do_update();\n    }\n\n    AVLTreeNodeBase\
    \ *base_rotate_left() {\n        /*    x              b\n             / \\   \
    \         / \\\n            a   b    =>    x   d\n               / \\        /\
    \ \\\n              c   d      a   c    */\n        AVLTreeNodeBase *b = R;\n\
    \        b->propagate(), R = b->L, b->L = this, update(), b->update();\n     \
    \   return b;\n    }\n    AVLTreeNodeBase *base_rotate_right() {\n        /* \
    \   x              a\n             / \\            / \\\n            a   b   \
    \ =>    c   x\n           / \\                / \\\n          c   d          \
    \    d   b */\n        AVLTreeNodeBase *a = L;\n        a->propagate(), L = a->R,\
    \ a->R = this, update(), a->update();\n        return a;\n    }\n\n    enum class\
    \ Child { LEFT, RIGHT };\n    std::pair<AVLTreeNodeBase *, Child> taller_child()\
    \ const {\n        return (L ? L->Height : 0) > (R ? R->Height : 0) ? std::make_pair(L,\
    \ Child::LEFT)\n                                                         : std::make_pair(R,\
    \ Child::RIGHT);\n    }\n\n    bool is_balanced() const { return std::abs((L ?\
    \ L->Height : 0) - (R ? R->Height : 0)) <= 1; }\n\n    AVLTreeNodeBase *balance()\
    \ {\n        if (is_balanced()) return this;\n        auto [y, dy] = taller_child();\n\
    \        if (dy == Child::LEFT) {\n            if ((y->L ? y->L->Height : 0) <\
    \ (y->R ? y->R->Height : 0))\n                y->propagate(), L = y->base_rotate_left(),\
    \ update();\n            return base_rotate_right();\n        }\n        if ((y->L\
    \ ? y->L->Height : 0) > (y->R ? y->R->Height : 0))\n            y->propagate(),\
    \ R = y->base_rotate_right(), update();\n        return base_rotate_left();\n\
    \    }\n\n    std::array<AVLTreeNodeBase *, 2> extract_leftmost() {\n        propagate();\n\
    \        if (L == nullptr) {\n            AVLTreeNodeBase *b = R;\n          \
    \  R                  = nullptr, update();\n            return {b, this};\n  \
    \      }\n        auto [l, e] = L->extract_leftmost();\n        L           =\
    \ l, update();\n        return {balance(), e};\n    }\n\n    std::array<AVLTreeNodeBase\
    \ *, 2> extract_rightmost() {\n        propagate();\n        if (R == nullptr)\
    \ {\n            AVLTreeNodeBase *b = L;\n            L                  = nullptr,\
    \ update();\n            return {b, this};\n        }\n        auto [r, e] = R->extract_rightmost();\n\
    \        R           = r, update();\n        return {balance(), e};\n    }\n\n\
    \    // join(this, single, small)\n    AVLTreeNodeBase *base_join_right(AVLTreeNodeBase\
    \ *single, AVLTreeNodeBase *s) {\n        assert(single != nullptr && single->L\
    \ == nullptr && single->R == nullptr);\n        assert(s != nullptr);\n      \
    \  assert(Height >= s->Height);\n        propagate();\n        if (Height - s->Height\
    \ <= 1)\n            return single->L = this, single->R = s, single->update(),\
    \ single;\n        return R = R->base_join_right(single, s), update(), balance();\n\
    \    }\n\n    // join(small, single, this)\n    AVLTreeNodeBase *base_join_left(AVLTreeNodeBase\
    \ *s, AVLTreeNodeBase *single) {\n        assert(single != nullptr && single->L\
    \ == nullptr && single->R == nullptr);\n        assert(s != nullptr);\n      \
    \  assert(Height >= s->Height);\n        propagate();\n        if (Height - s->Height\
    \ <= 1)\n            return single->L = s, single->R = this, single->update(),\
    \ single;\n        return L = L->base_join_left(s, single), update(), balance();\n\
    \    }\n\n    // join(this, small)\n    AVLTreeNodeBase *base_join_right(AVLTreeNodeBase\
    \ *s) {\n        assert(s != nullptr);\n        assert(Height >= s->Height);\n\
    \        propagate();\n        if (Height - s->Height <= 1) {\n            auto\
    \ [r, e] = extract_rightmost();\n            return e->L = r, e->R = s, e->update(),\
    \ e;\n        }\n        return R = R->base_join_right(s), update(), balance();\n\
    \    }\n\n    // join(small, this)\n    AVLTreeNodeBase *base_join_left(AVLTreeNodeBase\
    \ *s) {\n        assert(s != nullptr);\n        assert(Height >= s->Height);\n\
    \        propagate();\n        if (Height - s->Height <= 1) {\n            auto\
    \ [r, e] = extract_leftmost();\n            return e->L = s, e->R = r, e->update(),\
    \ e;\n        }\n        return L = L->base_join_left(s), update(), balance();\n\
    \    }\n\n    static AVLTreeNodeBase *base_join(AVLTreeNodeBase *a, AVLTreeNodeBase\
    \ *b) {\n        if (a == nullptr) {\n            if (b) b->propagate(), b->update();\n\
    \            return b;\n        }\n        if (b == nullptr) {\n            if\
    \ (a) a->propagate(), a->update();\n            return a;\n        }\n       \
    \ if (a->Height >= b->Height) return b->propagate(), a->base_join_right(b);\n\
    \        return a->propagate(), b->base_join_left(a);\n    }\n\n    static AVLTreeNodeBase\
    \ *base_join(AVLTreeNodeBase *a, AVLTreeNodeBase *single,\n                  \
    \                    AVLTreeNodeBase *b) {\n        assert(single != nullptr &&\
    \ single->L == nullptr && single->R == nullptr);\n        if (a == nullptr) return\
    \ base_join(single, b);\n        if (b == nullptr) return base_join(a, single);\n\
    \        if (a->Height >= b->Height) return b->propagate(), a->base_join_right(single,\
    \ b);\n        return a->propagate(), b->base_join_left(a, single);\n    }\n\n\
    \    static std::array<AVLTreeNodeBase *, 2> base_split(AVLTreeNodeBase *a, int\
    \ k) {\n        if (a == nullptr) return {nullptr, nullptr};\n        a->propagate();\n\
    \        if (k == 0) return {nullptr, a};\n        if (k == a->Size) return {a,\
    \ nullptr};\n        const int leftsize = a->L != nullptr ? a->L->Size : 0;\n\
    \        if (leftsize < k) {\n            auto [b, c]        = base_split(a->R,\
    \ k - leftsize - 1);\n            AVLTreeNodeBase *l = a->L;\n            a->L\
    \ = a->R = nullptr, a->update();\n            return {base_join(l, a, b), c};\n\
    \        } else {\n            auto [b, c]        = base_split(a->L, k);\n   \
    \         AVLTreeNodeBase *r = a->R;\n            a->L = a->R = nullptr, a->update();\n\
    \            return {b, base_join(c, a, r)};\n        }\n    }\n\nprotected:\n\
    \    AVLTreeNodeBase() : L(), R(), Height(1), Size(1) {}\n\npublic:\n    int size()\
    \ const { return Size; }\n    int height() const { return Height; }\n    AVLTreeNodeT\
    \ *left() const { return (AVLTreeNodeT *)L; }\n    AVLTreeNodeT *right() const\
    \ { return (AVLTreeNodeT *)R; }\n    void update() { base_update(); }\n    void\
    \ propagate() { underlying().base_propagate(); }\n\n    template<typename... Nodes>\
    \ static AVLTreeNodeT *join(Nodes... root) {\n        struct Helper {\n      \
    \      AVLTreeNodeBase *Val;\n            Helper &operator|(AVLTreeNodeBase *A)\
    \ {\n                Val = base_join(Val, A);\n                return *this;\n\
    \            }\n        } nil{nullptr};\n        return (AVLTreeNodeT *)(nil |\
    \ ... | root).Val;\n    }\n    template<typename... Parts> static std::array<AVLTreeNodeT\
    \ *, sizeof...(Parts) + 1>\n    split(AVLTreeNodeT *root, Parts... part) {\n \
    \       std::array<AVLTreeNodeT *, sizeof...(Parts) + 1> res;\n        res[0]\
    \    = root;\n        int index = 0;\n        (\n            [&](int s) {\n  \
    \              auto [l, r]  = base_split(res[index], s);\n                res[index]\
    \   = (AVLTreeNodeT *)l;\n                res[++index] = (AVLTreeNodeT *)r;\n\
    \            }(part),\n            ...);\n        return res;\n    }\n};\n\ntemplate<typename\
    \ FlipableAVLTreeNodeT> class FlipableAVLTreeNodeBase\n    : public AVLTreeNodeBase<FlipableAVLTreeNodeT>\
    \ {\n    friend class AVLTreeNodeBase<FlipableAVLTreeNodeT>;\n\n    bool NeedFlip;\n\
    \n    FlipableAVLTreeNodeT &underlying() { return (FlipableAVLTreeNodeT &)*this;\
    \ }\n    const FlipableAVLTreeNodeT &underlying() const { return (const FlipableAVLTreeNodeT\
    \ &)*this; }\n\n    // CRTP reimplement\n    void do_flip() {}\n\n    void base_flip()\
    \ {\n        NeedFlip = !NeedFlip;\n        std::swap(this->L, this->R);\n   \
    \     underlying().do_flip();\n    }\n    void base_propagate() {\n        underlying().do_propagate();\n\
    \        if (NeedFlip) {\n            NeedFlip = false;\n            if (this->left())\
    \ this->left()->underlying().base_flip();\n            if (this->right()) this->right()->underlying().base_flip();\n\
    \        }\n    }\n\nprotected:\n    FlipableAVLTreeNodeBase() : NeedFlip() {}\n\
    \npublic:\n    void flip() { base_flip(); }\n};\n#line 2 \"node_pool.hpp\"\n\n\
    #include <list>\n#include <memory>\n#line 6 \"node_pool.hpp\"\n#include <vector>\n\
    \ntemplate<typename NodeT> class FixedSizeNodePool {\n    std::vector<NodeT> pool;\n\
    \npublic:\n    explicit FixedSizeNodePool(int n) : pool(n) {}\n    NodeT *at(int\
    \ ind) { return pool.data() + ind; }\n    int id(NodeT *a) const { return a -\
    \ pool.data(); }\n    auto get_func() {\n        return std::make_pair([this](int\
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
    };\n#line 5 \"test/data_structure/range_reverse_range_sum.1.test.cpp\"\n#include\
    \ <iostream>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    struct AVLTreeNode : FlipableAVLTreeNodeBase<AVLTreeNode> {\n        int\
    \ Val;\n        long long Sum;\n        void do_update() {\n            Sum =\
    \ Val;\n            if (left()) Sum += left()->Sum;\n            if (right())\
    \ Sum += right()->Sum;\n        }\n    };\n    int n, q;\n    std::cin >> n >>\
    \ q;\n    FixedSizeNodePool<AVLTreeNode> pool(n);\n    auto [node, id]   = pool.get_func();\n\
    \    AVLTreeNode *root = nullptr;\n    for (int i = 0; i < n; ++i) {\n       \
    \ std::cin >> node(i)->Val;\n        node(i)->Sum = node(i)->Val;\n        root\
    \         = AVLTreeNode::join(root, node(i));\n    }\n    while (q--) {\n    \
    \    int t, l, r;\n        std::cin >> t >> l >> r;\n        auto [a, b, c] =\
    \ AVLTreeNode::split(root, l, r - l);\n        if (t == 0) {\n            if (b)\
    \ b->flip();\n        } else {\n            std::cout << (b ? b->Sum : 0LL) <<\
    \ '\\n';\n        }\n        root = AVLTreeNode::join(a, b, c);\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_reverse_range_sum\"\
    \n\n#include \"avl_tree_node_base.hpp\"\n#include \"node_pool.hpp\"\n#include\
    \ <iostream>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    struct AVLTreeNode : FlipableAVLTreeNodeBase<AVLTreeNode> {\n        int\
    \ Val;\n        long long Sum;\n        void do_update() {\n            Sum =\
    \ Val;\n            if (left()) Sum += left()->Sum;\n            if (right())\
    \ Sum += right()->Sum;\n        }\n    };\n    int n, q;\n    std::cin >> n >>\
    \ q;\n    FixedSizeNodePool<AVLTreeNode> pool(n);\n    auto [node, id]   = pool.get_func();\n\
    \    AVLTreeNode *root = nullptr;\n    for (int i = 0; i < n; ++i) {\n       \
    \ std::cin >> node(i)->Val;\n        node(i)->Sum = node(i)->Val;\n        root\
    \         = AVLTreeNode::join(root, node(i));\n    }\n    while (q--) {\n    \
    \    int t, l, r;\n        std::cin >> t >> l >> r;\n        auto [a, b, c] =\
    \ AVLTreeNode::split(root, l, r - l);\n        if (t == 0) {\n            if (b)\
    \ b->flip();\n        } else {\n            std::cout << (b ? b->Sum : 0LL) <<\
    \ '\\n';\n        }\n        root = AVLTreeNode::join(a, b, c);\n    }\n    return\
    \ 0;\n}\n"
  dependsOn:
  - avl_tree_node_base.hpp
  - node_pool.hpp
  isVerificationFile: true
  path: test/data_structure/range_reverse_range_sum.1.test.cpp
  requiredBy: []
  timestamp: '2026-01-25 23:04:59+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/data_structure/range_reverse_range_sum.1.test.cpp
layout: document
redirect_from:
- /verify/test/data_structure/range_reverse_range_sum.1.test.cpp
- /verify/test/data_structure/range_reverse_range_sum.1.test.cpp.html
title: test/data_structure/range_reverse_range_sum.1.test.cpp
---
