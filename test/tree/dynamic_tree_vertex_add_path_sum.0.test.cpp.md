---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: node_pool.hpp
    title: node_pool.hpp
  - icon: ':heavy_check_mark:'
    path: st_tree_node_base.hpp
    title: st_tree_node_base.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum
  bundledCode: "#line 1 \"test/tree/dynamic_tree_vertex_add_path_sum.0.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum\"\
    \n\n#line 2 \"node_pool.hpp\"\n\n#include <list>\n#include <memory>\n#include\
    \ <utility>\n#include <vector>\n\ntemplate<typename NodeT> class FixedSizeNodePool\
    \ {\n    std::vector<NodeT> pool;\n\npublic:\n    explicit FixedSizeNodePool(int\
    \ n) : pool(n) {}\n    NodeT *at(int ind) { return pool.data() + ind; }\n    int\
    \ id(NodeT *a) const { return a - pool.data(); }\n    auto get_func() {\n    \
    \    return std::make_pair([this](int ind) { return at(ind); },\n            \
    \                  [this](NodeT *a) { return id(a); });\n    }\n};\n\ntemplate<typename\
    \ NodeT> class DynamicSizeNodePool {\n    struct Wrapped : public NodeT {\n  \
    \      using NodeT::NodeT;\n        typename std::list<Wrapped>::iterator i;\n\
    \    };\n    std::list<Wrapped> used_list;\n    std::list<Wrapped> free_list;\n\
    \npublic:\n    template<typename... Args> NodeT *make(Args &&...arg) {\n     \
    \   if (free_list.empty()) {\n            auto &&node = used_list.emplace_back(std::forward<Args>(arg)...);\n\
    \            node.i      = std::prev(used_list.end());\n            return std::addressof(node);\n\
    \        }\n        used_list.splice(used_list.end(), free_list, std::prev(free_list.end()));\n\
    \        auto &&node = used_list.back();\n        node.~NodeT(); // i remains\
    \ unchanged\n        new (std::addressof(node)) NodeT(std::forward<Args>(arg)...);\n\
    \        return std::addressof(node);\n    }\n    // this is lazy, if sth. relies\
    \ on the order of dtor, do NOT use\n    void retrieve(NodeT *node) {\n       \
    \ free_list.splice(free_list.end(), used_list, ((Wrapped *)node)->i);\n    }\n\
    };\n#line 2 \"st_tree_node_base.hpp\"\n\n#line 4 \"st_tree_node_base.hpp\"\n\n\
    template<typename STTreeNodeT> class STTreeNodeBase {\n    STTreeNodeBase *L;\n\
    \    STTreeNodeBase *R;\n    STTreeNodeBase *P;\n    int Size;\n    bool NeedFlip;\n\
    \n    STTreeNodeT *derived() { return (STTreeNodeT *)this; }\n    enum class Child\
    \ { LEFT, RIGHT };\n    Child which() const { return P->L == this ? Child::LEFT\
    \ : Child::RIGHT; }\n    // has NO parent OR NOT a prefered child\n    bool is_root()\
    \ const { return P == nullptr || (P->L != this && P->R != this); }\n    bool is_left_child()\
    \ const { return which() == Child::LEFT; }\n    bool is_right_child() const {\
    \ return which() == Child::RIGHT; }\n\n    // CRTP reimplement\n    void do_flip()\
    \ {}\n    void do_propagate() {}\n    void do_update() {}\n\nprotected:\n    void\
    \ base_flip() {\n        NeedFlip = !NeedFlip;\n        std::swap(L, R);\n   \
    \     derived()->do_flip();\n    }\n    // base_propagate() is called to propagate\
    \ the update information to child(ren).\n    // There is no need to update the\
    \ information combined from child(ren)\n    // which should be done in base_update().\n\
    \    void base_propagate() {\n        derived()->do_propagate();\n        if (NeedFlip)\
    \ {\n            NeedFlip = false;\n            if (L) L->base_flip();\n     \
    \       if (R) R->base_flip();\n        }\n    }\n    // base_update() is called\
    \ to update the information combined from child(ren).\n    void base_update()\
    \ {\n        Size = 1;\n        if (L) Size += L->Size;\n        if (R) Size +=\
    \ R->Size;\n        derived()->do_update();\n    }\n    void base_rotate() {\n\
    \        P->base_propagate();\n        base_propagate();\n        if (is_left_child())\
    \ {\n            if ((P->L = R)) R->P = P;\n            if (!P->is_root()) {\n\
    \                if (P->is_left_child()) P->P->L = this;\n                else\
    \ { P->P->R = this; }\n            }\n            R = P, P = P->P, R->P = this;\n\
    \            R->base_update();\n        } else {\n            if ((P->R = L))\
    \ L->P = P;\n            if (!P->is_root()) {\n                if (P->is_left_child())\
    \ P->P->L = this;\n                else { P->P->R = this; }\n            }\n \
    \           L = P, P = P->P, L->P = this;\n            L->base_update();\n   \
    \     }\n    }\n    void base_splay() {\n        for (base_propagate(); !is_root();\
    \ base_rotate()) {\n            if (!P->is_root()) {\n                P->P->base_propagate();\n\
    \                P->which() == which() ? P->base_rotate() : base_rotate();\n \
    \           }\n        }\n        base_update();\n    }\n\n    STTreeNodeBase()\
    \ : L(), R(), P(), Size(1), NeedFlip() {}\n\npublic:\n    int size() const { return\
    \ Size; }\n\n    STTreeNodeT *left() const { return (STTreeNodeT *)L; }\n    STTreeNodeT\
    \ *right() const { return (STTreeNodeT *)R; }\n\n    void update() { base_update();\
    \ }\n\n    STTreeNodeT *expose() {\n        STTreeNodeBase *a = this, *lca = a;\n\
    \        base_splay();\n        a->R = nullptr;\n        while (a->P) {\n    \
    \        lca = a->P;\n            lca->base_splay();\n            a->P->R = a;\n\
    \            a->base_rotate();\n        }\n        a->base_update();\n       \
    \ // now a is the root of the virtual tree\n        return (STTreeNodeT *)lca;\n\
    \    }\n    void evert() { expose(), base_flip(); }\n    STTreeNodeT *root() {\n\
    \        expose();\n        STTreeNodeBase *a = this;\n        while (a->L) a\
    \ = a->L;\n        a->base_splay();\n        return (STTreeNodeT *)a;\n    }\n\
    \    STTreeNodeT *parent() {\n        expose();\n        if (!L) return nullptr;\n\
    \        STTreeNodeBase *a = L;\n        a->base_propagate();\n        while (a->R)\
    \ {\n            a = a->R;\n            a->base_propagate();\n        }\n    \
    \    a->base_splay();\n        return (STTreeNodeT *)a;\n    }\n    // this op.\
    \ WILL change the root\n    void link(STTreeNodeT *a) {\n        evert();\n  \
    \      if (a->root() != derived()) P = a;\n    }\n    // this op. will NOT change\
    \ the root\n    void cut() {\n        expose();\n        STTreeNodeBase *b = L;\n\
    \        L                 = nullptr;\n        if (b) b->P = nullptr;\n      \
    \  base_update();\n    }\n    // this op. will NOT change the root\n    void cut(STTreeNodeT\
    \ *b) {\n        if (parent() == b) {\n            cut();\n        } else if (b->parent()\
    \ == derived()) {\n            b->cut();\n        }\n    }\n    STTreeNodeT *select(int\
    \ k) {\n        STTreeNodeBase *a = this;\n        a->base_propagate();\n    \
    \    while ((a->L ? a->L->size() : 0) != k) {\n            if ((a->L ? a->L->size()\
    \ : 0) < k) {\n                k -= (a->L ? a->L->size() : 0) + 1;\n         \
    \       a = a->R;\n            } else {\n                a = a->L;\n         \
    \   }\n            a->base_propagate();\n        }\n        a->base_splay();\n\
    \        return (STTreeNodeT *)a;\n    }\n};\n#line 5 \"test/tree/dynamic_tree_vertex_add_path_sum.0.test.cpp\"\
    \n#include <iostream>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, q;\n    std::cin >> n >> q;\n    struct\
    \ STTreeNode : STTreeNodeBase<STTreeNode> {\n        long long Val, Sum;\n   \
    \     void do_update() {\n            Sum = Val;\n            if (left()) Sum\
    \ += left()->Sum;\n            if (right()) Sum += right()->Sum;\n        }\n\
    \    };\n    FixedSizeNodePool<STTreeNode> pool(n);\n    auto [node, id] = pool.get_func();\n\
    \    for (int i = 0; i < n; ++i) {\n        std::cin >> node(i)->Val;\n      \
    \  node(i)->update();\n    }\n    for (int i = 0; i < n - 1; ++i) {\n        int\
    \ u, v;\n        std::cin >> u >> v;\n        node(u)->link(node(v));\n    }\n\
    \    while (q--) {\n        int cmd;\n        std::cin >> cmd;\n        if (cmd\
    \ == 0) {\n            int u, v, w, x;\n            std::cin >> u >> v >> w >>\
    \ x;\n            node(u)->cut(node(v));\n            node(w)->link(node(x));\n\
    \        } else if (cmd == 1) {\n            int p, x;\n            std::cin >>\
    \ p >> x;\n            node(p)->expose();\n            node(p)->Val += x;\n  \
    \          node(p)->update();\n        } else {\n            int u, v;\n     \
    \       std::cin >> u >> v;\n            node(u)->evert();\n            node(v)->expose();\n\
    \            std::cout << node(v)->Sum << '\\n';\n        }\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum\"\
    \n\n#include \"node_pool.hpp\"\n#include \"st_tree_node_base.hpp\"\n#include <iostream>\n\
    \nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n, q;\n    std::cin >> n >> q;\n    struct STTreeNode : STTreeNodeBase<STTreeNode>\
    \ {\n        long long Val, Sum;\n        void do_update() {\n            Sum\
    \ = Val;\n            if (left()) Sum += left()->Sum;\n            if (right())\
    \ Sum += right()->Sum;\n        }\n    };\n    FixedSizeNodePool<STTreeNode> pool(n);\n\
    \    auto [node, id] = pool.get_func();\n    for (int i = 0; i < n; ++i) {\n \
    \       std::cin >> node(i)->Val;\n        node(i)->update();\n    }\n    for\
    \ (int i = 0; i < n - 1; ++i) {\n        int u, v;\n        std::cin >> u >> v;\n\
    \        node(u)->link(node(v));\n    }\n    while (q--) {\n        int cmd;\n\
    \        std::cin >> cmd;\n        if (cmd == 0) {\n            int u, v, w, x;\n\
    \            std::cin >> u >> v >> w >> x;\n            node(u)->cut(node(v));\n\
    \            node(w)->link(node(x));\n        } else if (cmd == 1) {\n       \
    \     int p, x;\n            std::cin >> p >> x;\n            node(p)->expose();\n\
    \            node(p)->Val += x;\n            node(p)->update();\n        } else\
    \ {\n            int u, v;\n            std::cin >> u >> v;\n            node(u)->evert();\n\
    \            node(v)->expose();\n            std::cout << node(v)->Sum << '\\\
    n';\n        }\n    }\n    return 0;\n}\n"
  dependsOn:
  - node_pool.hpp
  - st_tree_node_base.hpp
  isVerificationFile: true
  path: test/tree/dynamic_tree_vertex_add_path_sum.0.test.cpp
  requiredBy: []
  timestamp: '2025-09-15 20:50:57+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/tree/dynamic_tree_vertex_add_path_sum.0.test.cpp
layout: document
redirect_from:
- /verify/test/tree/dynamic_tree_vertex_add_path_sum.0.test.cpp
- /verify/test/tree/dynamic_tree_vertex_add_path_sum.0.test.cpp.html
title: test/tree/dynamic_tree_vertex_add_path_sum.0.test.cpp
---
