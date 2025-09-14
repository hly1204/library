---
data:
  _extendedDependsOn:
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
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"test/tree/lca.0.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\
    \n\n#line 2 \"st_tree_node_base.hpp\"\n\n#include <cassert>\n#include <utility>\n\
    \ntemplate<typename STTreeNodeT> class STTreeNodeBase {\n    STTreeNodeBase *L;\n\
    \    STTreeNodeBase *R;\n    STTreeNodeBase *P;\n    int Size;\n    bool NeedFlip;\n\
    \n    STTreeNodeT *derived() { return (STTreeNodeT *)this; }\n    enum class Child\
    \ { LEFT, RIGHT };\n    Child which() const {\n        assert(P != nullptr);\n\
    \        return P->L == this ? Child::LEFT : Child::RIGHT;\n    }\n    // has\
    \ NO parent OR NOT a prefered child\n    bool is_root() const { return P == nullptr\
    \ || (P->L != this && P->R != this); }\n    bool is_left_child() const { return\
    \ which() == Child::LEFT; }\n    bool is_right_child() const { return which()\
    \ == Child::RIGHT; }\n\n    // CRTP reimplement\n    void do_flip() {}\n    void\
    \ do_propagate() {}\n    void do_update() {}\n\nprotected:\n    void base_flip()\
    \ {\n        NeedFlip = !NeedFlip;\n        std::swap(L, R);\n        derived()->do_flip();\n\
    \    }\n    // base_propagate() is called to propagate the update information\
    \ to child(ren).\n    // There is no need to update the information combined from\
    \ child(ren)\n    // which should be done in base_update().\n    void base_propagate()\
    \ {\n        derived()->do_propagate();\n        if (NeedFlip) {\n           \
    \ NeedFlip = false;\n            if (L) L->base_flip();\n            if (R) R->base_flip();\n\
    \        }\n    }\n    // base_update() is called to update the information combined\
    \ from child(ren).\n    void base_update() {\n        Size = 1;\n        if (L)\
    \ Size += L->Size;\n        if (R) Size += R->Size;\n        derived()->do_update();\n\
    \    }\n    void base_rotate() {\n        assert(P != nullptr);\n        P->base_propagate();\n\
    \        base_propagate();\n        if (is_left_child()) {\n            if ((P->L\
    \ = R)) R->P = P;\n            if (!P->is_root()) {\n                if (P->is_left_child())\
    \ P->P->L = this;\n                else { P->P->R = this; }\n            }\n \
    \           R = P, P = P->P, R->P = this;\n            R->base_update();\n   \
    \     } else {\n            if ((P->R = L)) L->P = P;\n            if (!P->is_root())\
    \ {\n                if (P->is_left_child()) P->P->L = this;\n               \
    \ else { P->P->R = this; }\n            }\n            L = P, P = P->P, L->P =\
    \ this;\n            L->base_update();\n        }\n    }\n    void base_splay()\
    \ {\n        for (base_propagate(); !is_root(); base_rotate()) {\n           \
    \ if (!P->is_root()) {\n                P->P->base_propagate();\n            \
    \    P->which() == which() ? P->base_rotate() : base_rotate();\n            }\n\
    \        }\n        base_update();\n    }\n\n    STTreeNodeBase() : L(), R(),\
    \ P(), Size(1), NeedFlip() {}\n\npublic:\n    int size() const { return Size;\
    \ }\n\n    STTreeNodeT *left() const { return (STTreeNodeT *)L; }\n    STTreeNodeT\
    \ *right() const { return (STTreeNodeT *)R; }\n\n    void update() { base_update();\
    \ }\n\n    STTreeNodeT *expose() {\n        STTreeNodeBase *a = this, *lca = a;\n\
    \        base_splay();\n        a->R = nullptr;\n        while (a->P) {\n    \
    \        lca = a->P;\n            lca->base_splay();\n            a->P->R = a;\n\
    \            a->base_rotate();\n        }\n        a->base_update(); // now a\
    \ is the root\n        return (STTreeNodeT *)lca;\n    }\n    void evert() {\n\
    \        expose();\n        base_flip();\n    }\n    STTreeNodeT *root() {\n \
    \       expose();\n        STTreeNodeBase *a = this;\n        while (a->L) a =\
    \ a->L;\n        a->base_splay();\n        return (STTreeNodeT *)a;\n    }\n \
    \   STTreeNodeT *parent() {\n        expose();\n        if (!L) return nullptr;\n\
    \        STTreeNodeBase *a = L;\n        a->base_propagate();\n        while (a->R)\
    \ {\n            a = a->R;\n            a->base_propagate();\n        }\n    \
    \    a->base_splay();\n        return (STTreeNodeT *)a;\n    }\n    void link(STTreeNodeT\
    \ *a) {\n        evert();\n        if (a->root() != derived()) P = a;\n    }\n\
    \    void cut() {\n        expose();\n        STTreeNodeBase *b = L;\n       \
    \ L                 = nullptr;\n        if (b) b->P = nullptr;\n        base_update();\n\
    \    }\n    void cut(STTreeNodeT *b) {\n        if (parent() == b) {\n       \
    \     cut();\n        } else if (b->parent() == derived()) {\n            b->cut();\n\
    \        }\n    }\n    STTreeNodeT *select(int k) {\n        STTreeNodeBase *a\
    \ = this;\n        a->base_propagate();\n        while ((a->L ? a->L->size() :\
    \ 0) != 0) {\n            if ((a->L ? a->L->size() : 0) < k) {\n             \
    \   k -= (a->L ? a->L->size() : 0) + 1;\n                a = a->R;\n         \
    \   } else {\n                a = a->L;\n            }\n            a->base_propagate();\n\
    \        }\n        a->base_splay();\n        return a;\n    }\n};\n#line 4 \"\
    test/tree/lca.0.test.cpp\"\n#include <iostream>\n#include <memory>\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n, m;\n    std::cin >> n >> m;\n    struct STTreeNode : STTreeNodeBase<STTreeNode>\
    \ {};\n    auto buf = std::make_unique<STTreeNode[]>(n);\n    for (int i = 0;\
    \ i < n - 1; ++i) {\n        int p;\n        std::cin >> p;\n        buf[p].link(&buf[i\
    \ + 1]);\n    }\n    buf[0].evert();\n    while (m--) {\n        int u, v;\n \
    \       std::cin >> u >> v;\n        buf[u].expose();\n        std::cout << buf[v].expose()\
    \ - &buf[0] << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include \"st_tree_node_base.hpp\"\
    \n#include <iostream>\n#include <memory>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    int n, m;\n    std::cin >> n >> m;\n    struct\
    \ STTreeNode : STTreeNodeBase<STTreeNode> {};\n    auto buf = std::make_unique<STTreeNode[]>(n);\n\
    \    for (int i = 0; i < n - 1; ++i) {\n        int p;\n        std::cin >> p;\n\
    \        buf[p].link(&buf[i + 1]);\n    }\n    buf[0].evert();\n    while (m--)\
    \ {\n        int u, v;\n        std::cin >> u >> v;\n        buf[u].expose();\n\
    \        std::cout << buf[v].expose() - &buf[0] << '\\n';\n    }\n    return 0;\n\
    }\n"
  dependsOn:
  - st_tree_node_base.hpp
  isVerificationFile: true
  path: test/tree/lca.0.test.cpp
  requiredBy: []
  timestamp: '2025-09-14 22:04:07+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/tree/lca.0.test.cpp
layout: document
redirect_from:
- /verify/test/tree/lca.0.test.cpp
- /verify/test/tree/lca.0.test.cpp.html
title: test/tree/lca.0.test.cpp
---
