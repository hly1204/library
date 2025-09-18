---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
    links:
    - https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum
  bundledCode: "#line 1 \"test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n\n#line 2 \"modint.hpp\"\n\n#include <iostream>\n#include <type_traits>\n\n\
    // clang-format off\ntemplate<unsigned Mod> class ModInt {\n    static_assert((Mod\
    \ >> 31) == 0, \"`Mod` must less than 2^(31)\");\n    template<typename Int>\n\
    \    static std::enable_if_t<std::is_integral_v<Int>, unsigned> safe_mod(Int v)\
    \ { using D = std::common_type_t<Int, unsigned>; return (v %= (int)Mod) < 0 ?\
    \ (D)(v + (int)Mod) : (D)v; }\n    struct PrivateConstructor {} static inline\
    \ private_constructor{};\n    ModInt(PrivateConstructor, unsigned v) : v_(v) {}\n\
    \    unsigned v_;\n\npublic:\n    static unsigned mod() { return Mod; }\n    static\
    \ ModInt from_raw(unsigned v) { return ModInt(private_constructor, v); }\n   \
    \ static ModInt zero() { return from_raw(0); }\n    static ModInt one() { return\
    \ from_raw(1); }\n    bool is_zero() const { return v_ == 0; }\n    bool is_one()\
    \ const { return v_ == 1; }\n    ModInt() : v_() {}\n    template<typename Int,\
    \ typename std::enable_if_t<std::is_signed_v<Int>, int> = 0> ModInt(Int v) : v_(safe_mod(v))\
    \ {}\n    template<typename Int, typename std::enable_if_t<std::is_unsigned_v<Int>,\
    \ int> = 0> ModInt(Int v) : v_(v % Mod) {}\n    unsigned val() const { return\
    \ v_; }\n    ModInt operator-() const { return from_raw(v_ == 0 ? v_ : Mod - v_);\
    \ }\n    ModInt pow(long long e) const { if (e < 0) return inv().pow(-e); for\
    \ (ModInt x(*this), res(from_raw(1));; x *= x) { if (e & 1) res *= x; if ((e >>=\
    \ 1) == 0) return res; }}\n    ModInt inv() const { int x1 = 1, x3 = 0, a = val(),\
    \ b = Mod; while (b) { const int q = a / b, x1_old = x1, a_old = a; x1 = x3, x3\
    \ = x1_old - x3 * q, a = b, b = a_old - b * q; } return from_raw(x1 < 0 ? x1 +\
    \ (int)Mod : x1); }\n    template<bool Odd = (Mod & 1)> std::enable_if_t<Odd,\
    \ ModInt> div_by_2() const { if (v_ & 1) return from_raw((v_ + Mod) >> 1); return\
    \ from_raw(v_ >> 1); }\n    ModInt &operator+=(const ModInt &a) { if ((v_ += a.v_)\
    \ >= Mod) v_ -= Mod; return *this; }\n    ModInt &operator-=(const ModInt &a)\
    \ { if ((v_ += Mod - a.v_) >= Mod) v_ -= Mod; return *this; }\n    ModInt &operator*=(const\
    \ ModInt &a) { v_ = (unsigned long long)v_ * a.v_ % Mod; return *this; }\n   \
    \ ModInt &operator/=(const ModInt &a) { return *this *= a.inv(); }\n    ModInt\
    \ &operator++() { return *this += one(); }\n    ModInt operator++(int) { ModInt\
    \ o(*this); *this += one(); return o; }\n    ModInt &operator--() { return *this\
    \ -= one(); }\n    ModInt operator--(int) { ModInt o(*this); *this -= one(); return\
    \ o; }\n    friend ModInt operator+(const ModInt &a, const ModInt &b) { return\
    \ ModInt(a) += b; }\n    friend ModInt operator-(const ModInt &a, const ModInt\
    \ &b) { return ModInt(a) -= b; }\n    friend ModInt operator*(const ModInt &a,\
    \ const ModInt &b) { return ModInt(a) *= b; }\n    friend ModInt operator/(const\
    \ ModInt &a, const ModInt &b) { return ModInt(a) /= b; }\n    friend bool operator==(const\
    \ ModInt &a, const ModInt &b) { return a.v_ == b.v_; }\n    friend bool operator!=(const\
    \ ModInt &a, const ModInt &b) { return a.v_ != b.v_; }\n    friend std::istream\
    \ &operator>>(std::istream &a, ModInt &b) { int v; a >> v; b.v_ = safe_mod(v);\
    \ return a; }\n    friend std::ostream &operator<<(std::ostream &a, const ModInt\
    \ &b) { return a << b.val(); }\n};\n// clang-format on\n#line 2 \"node_pool.hpp\"\
    \n\n#include <list>\n#include <memory>\n#include <utility>\n#include <vector>\n\
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
    \    void flip() { base_flip(); }\n};\n#line 7 \"test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = ModInt<998244353>;\n    struct Node : FlipableSplayTreeNodeBase<Node>\
    \ {\n        mint Val, Sum, Add, Mul = {1};\n        void do_propagate() {\n \
    \           if (left()) {\n                left()->Add = Mul * left()->Add + Add;\n\
    \                left()->Mul *= Mul;\n                left()->Sum = Add * left()->size()\
    \ + Mul * left()->Sum;\n            }\n            if (right()) {\n          \
    \      right()->Add = Mul * right()->Add + Add;\n                right()->Mul\
    \ *= Mul;\n                right()->Sum = Add * right()->size() + Mul * right()->Sum;\n\
    \            }\n            Val = Add + Mul * Val;\n            Add = 0;\n   \
    \         Mul = 1;\n        }\n        void do_update() {\n            Sum = Val;\n\
    \            if (left()) Sum += left()->Sum;\n            if (right()) Sum +=\
    \ right()->Sum;\n        }\n    };\n    int n, q;\n    std::cin >> n >> q;\n \
    \   DynamicSizeNodePool<Node> pool;\n    Node *root = nullptr;\n    for (int i\
    \ = 0; i < n; ++i) {\n        auto node = pool.make();\n        std::cin >> node->Val;\n\
    \        root = Node::join(root, node);\n    }\n    for (int i = 0; i < q; ++i)\
    \ {\n        int cmd;\n        std::cin >> cmd;\n        switch (cmd) {\n    \
    \    case 0: {\n            int pos;\n            auto node = pool.make();\n \
    \           std::cin >> pos >> node->Val;\n            auto [R0, R1] = Node::split(root,\
    \ pos);\n            root          = Node::join(R0, node, R1);\n            break;\n\
    \        }\n        case 1: {\n            int pos;\n            std::cin >> pos;\n\
    \            auto [R0, R1, R2] = Node::split(root, pos, 1);\n            pool.retrieve(R1);\n\
    \            root = Node::join(R0, R2);\n            break;\n        }\n     \
    \   case 2: {\n            int l, r;\n            std::cin >> l >> r;\n      \
    \      auto [R0, R1, R2] = Node::split(root, l, r - l);\n            R1->flip();\n\
    \            root = Node::join(R0, R1, R2);\n            break;\n        }\n \
    \       case 3: {\n            int l, r;\n            std::cin >> l >> r;\n  \
    \          auto [R0, R1, R2] = Node::split(root, l, r - l);\n            std::cin\
    \ >> R1->Mul >> R1->Add;\n            root = Node::join(R0, R1, R2);\n       \
    \     break;\n        }\n        case 4: {\n            int l, r;\n          \
    \  std::cin >> l >> r;\n            auto [R0, R1, R2] = Node::split(root, l, r\
    \ - l);\n            std::cout << R1->Sum << '\\n';\n            root = Node::join(R0,\
    \ R1, R2);\n            break;\n        }\n        default: break;\n        }\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum\"\
    \n\n#include \"modint.hpp\"\n#include \"node_pool.hpp\"\n#include \"splay_tree_node_base.hpp\"\
    \n#include <iostream>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    using mint = ModInt<998244353>;\n    struct Node\
    \ : FlipableSplayTreeNodeBase<Node> {\n        mint Val, Sum, Add, Mul = {1};\n\
    \        void do_propagate() {\n            if (left()) {\n                left()->Add\
    \ = Mul * left()->Add + Add;\n                left()->Mul *= Mul;\n          \
    \      left()->Sum = Add * left()->size() + Mul * left()->Sum;\n            }\n\
    \            if (right()) {\n                right()->Add = Mul * right()->Add\
    \ + Add;\n                right()->Mul *= Mul;\n                right()->Sum =\
    \ Add * right()->size() + Mul * right()->Sum;\n            }\n            Val\
    \ = Add + Mul * Val;\n            Add = 0;\n            Mul = 1;\n        }\n\
    \        void do_update() {\n            Sum = Val;\n            if (left()) Sum\
    \ += left()->Sum;\n            if (right()) Sum += right()->Sum;\n        }\n\
    \    };\n    int n, q;\n    std::cin >> n >> q;\n    DynamicSizeNodePool<Node>\
    \ pool;\n    Node *root = nullptr;\n    for (int i = 0; i < n; ++i) {\n      \
    \  auto node = pool.make();\n        std::cin >> node->Val;\n        root = Node::join(root,\
    \ node);\n    }\n    for (int i = 0; i < q; ++i) {\n        int cmd;\n       \
    \ std::cin >> cmd;\n        switch (cmd) {\n        case 0: {\n            int\
    \ pos;\n            auto node = pool.make();\n            std::cin >> pos >> node->Val;\n\
    \            auto [R0, R1] = Node::split(root, pos);\n            root       \
    \   = Node::join(R0, node, R1);\n            break;\n        }\n        case 1:\
    \ {\n            int pos;\n            std::cin >> pos;\n            auto [R0,\
    \ R1, R2] = Node::split(root, pos, 1);\n            pool.retrieve(R1);\n     \
    \       root = Node::join(R0, R2);\n            break;\n        }\n        case\
    \ 2: {\n            int l, r;\n            std::cin >> l >> r;\n            auto\
    \ [R0, R1, R2] = Node::split(root, l, r - l);\n            R1->flip();\n     \
    \       root = Node::join(R0, R1, R2);\n            break;\n        }\n      \
    \  case 3: {\n            int l, r;\n            std::cin >> l >> r;\n       \
    \     auto [R0, R1, R2] = Node::split(root, l, r - l);\n            std::cin >>\
    \ R1->Mul >> R1->Add;\n            root = Node::join(R0, R1, R2);\n          \
    \  break;\n        }\n        case 4: {\n            int l, r;\n            std::cin\
    \ >> l >> r;\n            auto [R0, R1, R2] = Node::split(root, l, r - l);\n \
    \           std::cout << R1->Sum << '\\n';\n            root = Node::join(R0,\
    \ R1, R2);\n            break;\n        }\n        default: break;\n        }\n\
    \    }\n    return 0;\n}\n"
  dependsOn:
  - modint.hpp
  - node_pool.hpp
  - splay_tree_node_base.hpp
  isVerificationFile: true
  path: test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
  requiredBy: []
  timestamp: '2025-09-18 20:33:53+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
layout: document
redirect_from:
- /verify/test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
- /verify/test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp.html
title: test/data_structure/dynamic_sequence_range_affine_range_sum.0.test.cpp
---
