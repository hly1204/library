---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
    title: test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
  - icon: ':x:'
    path: test/data_structure/point_set_range_composite.0.test.cpp
    title: test/data_structure/point_set_range_composite.0.test.cpp
  - icon: ':x:'
    path: test/data_structure/range_affine_point_get.0.test.cpp
    title: test/data_structure/range_affine_point_get.0.test.cpp
  - icon: ':x:'
    path: test/data_structure/range_affine_range_sum.0.test.cpp
    title: test/data_structure/range_affine_range_sum.0.test.cpp
  - icon: ':x:'
    path: test/data_structure/range_reverse_range_sum.0.test.cpp
    title: test/data_structure/range_reverse_range_sum.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"splay_tree_node_base.hpp\"\n\n#include <array>\n#include\
    \ <utility>\n\ntemplate<typename FlipableSplayTreeNodeT> class FlipableSplayTreeNodeBase;\n\
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
    \        return a;\n    }\n    std::array<SplayTreeNodeBase *, 2> base_split(int\
    \ k) {\n        propagate();\n        if (k == 0) return {nullptr, this};\n  \
    \      if (k == Size) return {this, nullptr};\n        SplayTreeNodeBase *a =\
    \ select(k);\n        SplayTreeNodeBase *b = a->L;\n        a->L             \
    \    = nullptr;\n        if (b) {\n            b->propagate();\n            b->P\
    \ = nullptr;\n        }\n        a->update();\n        return {b, a};\n    }\n\
    \n    SplayTreeNodeBase() : L(), R(), P(), Size(1) {}\n\npublic:\n    int size()\
    \ const { return Size; }\n    SplayTreeNodeT *left() const { return (SplayTreeNodeT\
    \ *)L; }\n    SplayTreeNodeT *right() const { return (SplayTreeNodeT *)R; }\n\
    \    SplayTreeNodeT *parent() const { return (SplayTreeNodeT *)P; }\n    void\
    \ update() { base_update(); }\n    void propagate() { underlying().base_propagate();\
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
    \    = a;\n        int index = 0;\n        (\n            [&](int s) {\n     \
    \           auto [l, r]  = res[index]->base_split(s);\n                res[index]\
    \   = (SplayTreeNodeT *)l;\n                res[++index] = (SplayTreeNodeT *)r;\n\
    \            }(part),\n            ...);\n        return res;\n    }\n    SplayTreeNodeT\
    \ *select(int k) {\n        SplayTreeNodeBase *a = this;\n        a->propagate();\n\
    \        while ((a->L ? a->L->Size : 0) != k) {\n            if ((a->L ? a->L->Size\
    \ : 0) < k) {\n                k -= (a->L ? a->L->Size : 0) + 1;\n           \
    \     a = a->R;\n            } else {\n                a = a->L;\n           \
    \ }\n            a->propagate();\n        }\n        a->splay();\n        return\
    \ (SplayTreeNodeT *)a;\n    }\n};\n\ntemplate<typename FlipableSplayTreeNodeT>\
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
    \    void flip() { base_flip(); }\n};\n"
  code: "#pragma once\n\n#include <array>\n#include <utility>\n\ntemplate<typename\
    \ FlipableSplayTreeNodeT> class FlipableSplayTreeNodeBase;\n\ntemplate<typename\
    \ SplayTreeNodeT> class SplayTreeNodeBase {\n    friend class FlipableSplayTreeNodeBase<SplayTreeNodeT>;\n\
    \n    SplayTreeNodeBase *L;\n    SplayTreeNodeBase *R;\n    SplayTreeNodeBase\
    \ *P;\n    int Size;\n\n    SplayTreeNodeT &underlying() { return (SplayTreeNodeT\
    \ &)*this; }\n    const SplayTreeNodeT &underlying() const { return (const SplayTreeNodeT\
    \ &)*this; }\n\n    enum class Child { LEFT, RIGHT };\n    Child which() const\
    \ { return P->L == this ? Child::LEFT : Child::RIGHT; }\n    bool is_root() const\
    \ { return P == nullptr; }\n    bool is_left_child() const { return which() ==\
    \ Child::LEFT; }\n    bool is_right_child() const { return which() == Child::RIGHT;\
    \ }\n\nprotected:\n    // CRTP reimplement\n    void do_propagate() {}\n    void\
    \ do_update() {}\n\n    // base_propagate() is called to propagate the update\
    \ information to child(ren).\n    // There is no need to update the information\
    \ combined from child(ren)\n    // which should be done in base_update().\n  \
    \  // * CRTP reimplementable\n    void base_propagate() { underlying().do_propagate();\
    \ }\n    // base_update() is called to update the information combined from child(ren).\n\
    \    void base_update() {\n        Size = 1;\n        if (L) Size += L->Size;\n\
    \        if (R) Size += R->Size;\n        underlying().do_update();\n    }\n \
    \   void base_rotate() {\n        P->propagate();\n        propagate();\n    \
    \    if (is_left_child()) {\n            if ((P->L = R)) R->P = P;\n         \
    \   if (!P->is_root()) {\n                if (P->is_left_child()) P->P->L = this;\n\
    \                else { P->P->R = this; }\n            }\n            R = P, P\
    \ = P->P, R->P = this;\n            R->update();\n        } else {\n         \
    \   if ((P->R = L)) L->P = P;\n            if (!P->is_root()) {\n            \
    \    if (P->is_left_child()) P->P->L = this;\n                else { P->P->R =\
    \ this; }\n            }\n            L = P, P = P->P, L->P = this;\n        \
    \    L->update();\n        }\n    }\n    static SplayTreeNodeBase *base_join(SplayTreeNodeBase\
    \ *a, SplayTreeNodeBase *b) {\n        if (a == nullptr) {\n            if (b)\
    \ b->propagate(), b->update();\n            return b;\n        }\n        if (b\
    \ == nullptr) {\n            if (a) a->propagate(), a->update();\n           \
    \ return a;\n        }\n        a->propagate();\n        while (a->R) {\n    \
    \        a = a->R;\n            a->propagate();\n        }\n        a->splay();\n\
    \        b->propagate();\n        a->R = b, b->P = a;\n        a->update();\n\
    \        return a;\n    }\n    std::array<SplayTreeNodeBase *, 2> base_split(int\
    \ k) {\n        propagate();\n        if (k == 0) return {nullptr, this};\n  \
    \      if (k == Size) return {this, nullptr};\n        SplayTreeNodeBase *a =\
    \ select(k);\n        SplayTreeNodeBase *b = a->L;\n        a->L             \
    \    = nullptr;\n        if (b) {\n            b->propagate();\n            b->P\
    \ = nullptr;\n        }\n        a->update();\n        return {b, a};\n    }\n\
    \n    SplayTreeNodeBase() : L(), R(), P(), Size(1) {}\n\npublic:\n    int size()\
    \ const { return Size; }\n    SplayTreeNodeT *left() const { return (SplayTreeNodeT\
    \ *)L; }\n    SplayTreeNodeT *right() const { return (SplayTreeNodeT *)R; }\n\
    \    SplayTreeNodeT *parent() const { return (SplayTreeNodeT *)P; }\n    void\
    \ update() { base_update(); }\n    void propagate() { underlying().base_propagate();\
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
    \    = a;\n        int index = 0;\n        (\n            [&](int s) {\n     \
    \           auto [l, r]  = res[index]->base_split(s);\n                res[index]\
    \   = (SplayTreeNodeT *)l;\n                res[++index] = (SplayTreeNodeT *)r;\n\
    \            }(part),\n            ...);\n        return res;\n    }\n    SplayTreeNodeT\
    \ *select(int k) {\n        SplayTreeNodeBase *a = this;\n        a->propagate();\n\
    \        while ((a->L ? a->L->Size : 0) != k) {\n            if ((a->L ? a->L->Size\
    \ : 0) < k) {\n                k -= (a->L ? a->L->Size : 0) + 1;\n           \
    \     a = a->R;\n            } else {\n                a = a->L;\n           \
    \ }\n            a->propagate();\n        }\n        a->splay();\n        return\
    \ (SplayTreeNodeT *)a;\n    }\n};\n\ntemplate<typename FlipableSplayTreeNodeT>\
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
    \    void flip() { base_flip(); }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: splay_tree_node_base.hpp
  requiredBy: []
  timestamp: '2025-09-18 19:32:39+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
  - test/data_structure/range_affine_range_sum.0.test.cpp
  - test/data_structure/point_set_range_composite.0.test.cpp
  - test/data_structure/range_affine_point_get.0.test.cpp
  - test/data_structure/range_reverse_range_sum.0.test.cpp
documentation_of: splay_tree_node_base.hpp
layout: document
redirect_from:
- /library/splay_tree_node_base.hpp
- /library/splay_tree_node_base.hpp.html
title: splay_tree_node_base.hpp
---
