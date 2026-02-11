#pragma once

#include <algorithm>
#include <array>
#include <cassert>
#include <cmath>
#include <utility>

template<typename FlipableAVLTreeNodeT> class FlipableAVLTreeNodeBase;

template<typename AVLTreeNodeT> class AVLTreeNodeBase {
    friend class FlipableAVLTreeNodeBase<AVLTreeNodeT>;

    AVLTreeNodeBase *L;
    AVLTreeNodeBase *R;
    int Height;
    int Size;

    AVLTreeNodeT &underlying() { return (AVLTreeNodeT &)*this; }
    const AVLTreeNodeT &underlying() const { return (const AVLTreeNodeT &)*this; }

    // CRTP reimplement
    void do_propagate() {}
    void do_update() {}

    // base_propagate() is called to propagate the update information to child(ren).
    // There is no need to update the information combined from child(ren)
    // which should be done in base_update().
    void base_propagate() { underlying().do_propagate(); }
    // base_update() is called to update the information combined from child(ren).
    void base_update() {
        Size = 1;
        if (L) Size += L->Size;
        if (R) Size += R->Size;
        Height = std::max(L ? L->Height : 0, R ? R->Height : 0) + 1;
        underlying().do_update();
    }

    AVLTreeNodeBase *base_rotate_left() {
        /*    x              b
             / \            / \
            a   b    =>    x   d
               / \        / \
              c   d      a   c    */
        AVLTreeNodeBase *b = R;
        b->propagate(), R = b->L, b->L = this, update(), b->update();
        return b;
    }
    AVLTreeNodeBase *base_rotate_right() {
        /*    x              a
             / \            / \
            a   b    =>    c   x
           / \                / \
          c   d              d   b */
        AVLTreeNodeBase *a = L;
        a->propagate(), L = a->R, a->R = this, update(), a->update();
        return a;
    }

    enum class Child { LEFT, RIGHT };
    std::pair<AVLTreeNodeBase *, Child> taller_child() const {
        return (L ? L->Height : 0) > (R ? R->Height : 0) ? std::make_pair(L, Child::LEFT)
                                                         : std::make_pair(R, Child::RIGHT);
    }

    bool is_balanced() const { return std::abs((L ? L->Height : 0) - (R ? R->Height : 0)) <= 1; }

    AVLTreeNodeBase *balance() {
        if (is_balanced()) return this;
        auto [y, dy] = taller_child();
        if (dy == Child::LEFT) {
            if ((y->L ? y->L->Height : 0) < (y->R ? y->R->Height : 0))
                y->propagate(), L = y->base_rotate_left(), update();
            return base_rotate_right();
        }
        if ((y->L ? y->L->Height : 0) > (y->R ? y->R->Height : 0))
            y->propagate(), R = y->base_rotate_right(), update();
        return base_rotate_left();
    }

    std::array<AVLTreeNodeBase *, 2> extract_leftmost() {
        propagate();
        if (L == nullptr) {
            AVLTreeNodeBase *b = R;
            R                  = nullptr, update();
            return {b, this};
        }
        auto [l, e] = L->extract_leftmost();
        L           = l, update();
        return {balance(), e};
    }

    std::array<AVLTreeNodeBase *, 2> extract_rightmost() {
        propagate();
        if (R == nullptr) {
            AVLTreeNodeBase *b = L;
            L                  = nullptr, update();
            return {b, this};
        }
        auto [r, e] = R->extract_rightmost();
        R           = r, update();
        return {balance(), e};
    }

    // join(this, single, small)
    AVLTreeNodeBase *base_join_right(AVLTreeNodeBase *single, AVLTreeNodeBase *s) {
        assert(single != nullptr && single->L == nullptr && single->R == nullptr);
        assert(s != nullptr);
        assert(Height >= s->Height);
        propagate();
        if (Height - s->Height <= 1)
            return single->L = this, single->R = s, single->update(), single;
        return R = R->base_join_right(single, s), update(), balance();
    }

    // join(small, single, this)
    AVLTreeNodeBase *base_join_left(AVLTreeNodeBase *s, AVLTreeNodeBase *single) {
        assert(single != nullptr && single->L == nullptr && single->R == nullptr);
        assert(s != nullptr);
        assert(Height >= s->Height);
        propagate();
        if (Height - s->Height <= 1)
            return single->L = s, single->R = this, single->update(), single;
        return L = L->base_join_left(s, single), update(), balance();
    }

    // join(this, small)
    AVLTreeNodeBase *base_join_right(AVLTreeNodeBase *s) {
        assert(s != nullptr);
        assert(Height >= s->Height);
        propagate();
        if (Height - s->Height <= 1) {
            auto [r, e] = extract_rightmost();
            return e->L = r, e->R = s, e->update(), e;
        }
        return R = R->base_join_right(s), update(), balance();
    }

    // join(small, this)
    AVLTreeNodeBase *base_join_left(AVLTreeNodeBase *s) {
        assert(s != nullptr);
        assert(Height >= s->Height);
        propagate();
        if (Height - s->Height <= 1) {
            auto [r, e] = extract_leftmost();
            return e->L = s, e->R = r, e->update(), e;
        }
        return L = L->base_join_left(s), update(), balance();
    }

    static AVLTreeNodeBase *base_join(AVLTreeNodeBase *a, AVLTreeNodeBase *b) {
        if (a == nullptr) {
            if (b) b->propagate(), b->update();
            return b;
        }
        if (b == nullptr) {
            if (a) a->propagate(), a->update();
            return a;
        }
        if (a->Height >= b->Height) return b->propagate(), a->base_join_right(b);
        return a->propagate(), b->base_join_left(a);
    }

    static AVLTreeNodeBase *base_join(AVLTreeNodeBase *a, AVLTreeNodeBase *single,
                                      AVLTreeNodeBase *b) {
        assert(single != nullptr && single->L == nullptr && single->R == nullptr);
        if (a == nullptr) return base_join(single, b);
        if (b == nullptr) return base_join(a, single);
        if (a->Height >= b->Height) return b->propagate(), a->base_join_right(single, b);
        return a->propagate(), b->base_join_left(a, single);
    }

    static std::array<AVLTreeNodeBase *, 2> base_split(AVLTreeNodeBase *a, int k) {
        if (a == nullptr) return {nullptr, nullptr};
        a->propagate();
        if (k == 0) return {nullptr, a};
        if (k == a->Size) return {a, nullptr};
        const int leftsize = a->L != nullptr ? a->L->Size : 0;
        if (leftsize < k) {
            auto [b, c]        = base_split(a->R, k - leftsize - 1);
            AVLTreeNodeBase *l = a->L;
            a->L = a->R = nullptr, a->update();
            return {base_join(l, a, b), c};
        } else {
            auto [b, c]        = base_split(a->L, k);
            AVLTreeNodeBase *r = a->R;
            a->L = a->R = nullptr, a->update();
            return {b, base_join(c, a, r)};
        }
    }

protected:
    AVLTreeNodeBase() : L(), R(), Height(1), Size(1) {}

public:
    int size() const { return Size; }
    int height() const { return Height; }
    AVLTreeNodeT *left() const { return (AVLTreeNodeT *)L; }
    AVLTreeNodeT *right() const { return (AVLTreeNodeT *)R; }
    void update() { base_update(); }
    void propagate() { underlying().base_propagate(); }
    static AVLTreeNodeT *insert(AVLTreeNodeT *root, AVLTreeNodeT *t) {
        if (root == nullptr) return t;
        root->propagate();
        if (std::as_const(*t) < std::as_const(*root)) root->L = insert(root->left(), t);
        else { root->R = insert(root->right(), t); }
        return root->update(), (AVLTreeNodeT *)root->balance();
    }
    static int count_less_than(AVLTreeNodeT *root, const AVLTreeNodeT *t) {
        if (root == nullptr) return 0;
        root->propagate();
        if (std::as_const(*root) < *t)
            return (root->left() ? root->left()->size() : 0) + 1 +
                   count_less_than(root->right(), t);
        return count_less_than(root->left(), t);
    }
    static int count_less_equal(AVLTreeNodeT *root, const AVLTreeNodeT *t) {
        if (root == nullptr) return 0;
        root->propagate();
        if (*t < std::as_const(*root)) return count_less_equal(root->left(), t);
        return (root->left() ? root->left()->size() : 0) + 1 + count_less_equal(root->right(), t);
    }
    // [<, >=]
    static std::array<AVLTreeNodeT *, 2> split_less_than(AVLTreeNodeT *root,
                                                         const AVLTreeNodeT *t) {
        if (root == nullptr) return {nullptr, nullptr};
        root->propagate();
        if (std::as_const(*root) < *t) {
            auto [a, b] = split_less_than(root->right(), t);
            auto l      = root->L;
            root->L = root->R = nullptr, root->update();
            return {(AVLTreeNodeT *)base_join(l, root, a), b};
        }
        auto [a, b] = split_less_than(root->left(), t);
        auto r      = root->R;
        root->L = root->R = nullptr, root->update();
        return {a, (AVLTreeNodeT *)base_join(b, root, r)};
    }
    static int count_greater_than(AVLTreeNodeT *root, const AVLTreeNodeT *t) {
        if (root == nullptr) return 0;
        root->propagate();
        if (*t < std::as_const(*root))
            return (root->right() ? root->right()->size() : 0) + 1 +
                   count_greater_than(root->left(), t);
        return count_greater_than(root->right(), t);
    }
    static int count_greater_equal(AVLTreeNodeT *root, const AVLTreeNodeT *t) {
        if (root == nullptr) return 0;
        root->propagate();
        if (std::as_const(*root) < *t) return count_greater_equal(root->right(), t);
        return (root->right() ? root->right()->size() : 0) + 1 +
               count_greater_equal(root->left(), t);
    }
    // [<=, >]
    static std::array<AVLTreeNodeT *, 2> split_less_equal(AVLTreeNodeT *root,
                                                          const AVLTreeNodeT *t) {
        if (root == nullptr) return {nullptr, nullptr};
        root->propagate();
        if (*t < std::as_const(*root)) {
            auto [a, b] = split_less_equal(root->left(), t);
            auto r      = root->R;
            root->L = root->R = nullptr, root->update();
            return {a, (AVLTreeNodeT *)base_join(b, root, r)};
        }
        auto [a, b] = split_less_equal(root->right(), t);
        auto l      = root->L;
        root->L = root->R = nullptr, root->update();
        return {(AVLTreeNodeT *)base_join(l, root, a), b};
    }
    static int count(AVLTreeNodeT *root, const AVLTreeNodeT *t) {
        if (root == nullptr) return 0;
        root->propagate();
        if (*t < std::as_const(*root)) return count(root->left(), t);
        if (std::as_const(*root) < *t) return count(root->right(), t);
        int res = 1;
        if (root->left()) res += root->left()->size() - count_less_than(root->left(), t);
        if (root->right()) res += root->right()->size() - count_greater_than(root->right(), t);
        return res;
    }
    static bool contains(AVLTreeNodeT *root, const AVLTreeNodeT *t) {
        if (root == nullptr) return false;
        root->propagate();
        if (*t < std::as_const(*root)) return contains(root->left(), t);
        if (std::as_const(*root) < *t) return contains(root->right(), t);
        return true;
    }
    static std::array<int, 3> count3(AVLTreeNodeT *root, const AVLTreeNodeT *t) {
        if (root == nullptr) return {0, 0, 0};
        root->propagate();
        if (*t < std::as_const(*root)) {
            auto [a, b, c] = count3(root->left(), t);
            return {a, b, c + 1 + (root->right() ? root->right()->size() : 0)};
        }
        if (std::as_const(*root) < *t) {
            auto [a, b, c] = count3(root->right(), t);
            return {a + 1 + (root->left() ? root->left()->size() : 0), b, c};
        }
        const int a = count_less_than(root->left(), t);
        const int c = count_greater_than(root->right(), t);
        return {a, root->size() - a - c, c};
    }
    static std::array<AVLTreeNodeT *, 3> split3(AVLTreeNodeT *root, const AVLTreeNodeT *t) {
        if (root == nullptr) return {nullptr, nullptr, nullptr};
        root->propagate();
        if (*t < std::as_const(*root)) {
            auto [a, b, c] = split3(root->left(), t);
            auto r         = root->R;
            root->L = root->R = nullptr, root->update();
            return {a, b, (AVLTreeNodeT *)base_join(c, root, r)};
        }
        if (std::as_const(*root) < *t) {
            auto [a, b, c] = split3(root->right(), t);
            auto l         = root->L;
            root->L = root->R = nullptr, root->update();
            return {(AVLTreeNodeT *)base_join(l, root, a), b, c};
        }
        auto [a, b] = split_less_than(root->left(), t);
        auto [c, d] = split_less_equal(root->right(), t);
        root->L = root->R = nullptr, root->update();
        return {a, (AVLTreeNodeT *)base_join(b, root, c), d};
    }
    static AVLTreeNodeT *predecessor(AVLTreeNodeT *root, const AVLTreeNodeT *t) {
        AVLTreeNodeT *res = nullptr;
        while (root) {
            root->propagate();
            if (std::as_const(*root) < *t) {
                res = root, root = root->right();
            } else {
                root = root->left();
            }
        }
        return res;
    }
    static AVLTreeNodeT *successor(AVLTreeNodeT *root, const AVLTreeNodeT *t) {
        AVLTreeNodeT *res = nullptr;
        while (root) {
            root->propagate();
            if (*t < std::as_const(*root)) {
                res = root, root = root->left();
            } else {
                root = root->right();
            }
        }
        return res;
    }

    template<typename... Nodes> static AVLTreeNodeT *join(Nodes... root) {
        struct Helper {
            AVLTreeNodeBase *Val;
            Helper &operator|(AVLTreeNodeBase *A) {
                Val = base_join(Val, A);
                return *this;
            }
        } nil{nullptr};
        return (AVLTreeNodeT *)(nil | ... | root).Val;
    }
    template<typename... Parts> static std::array<AVLTreeNodeT *, sizeof...(Parts) + 1>
    split(AVLTreeNodeT *root, Parts... part) {
        std::array<AVLTreeNodeT *, sizeof...(Parts) + 1> res;
        res[0]    = root;
        int index = 0;
        (
            [&](int s) {
                auto [l, r]  = base_split(res[index], s);
                res[index]   = (AVLTreeNodeT *)l;
                res[++index] = (AVLTreeNodeT *)r;
            }(part),
            ...);
        return res;
    }

    static AVLTreeNodeT *find(AVLTreeNodeT *root, const AVLTreeNodeT *t) {
        if (root == nullptr) return nullptr;
        root->propagate();
        if (std::as_const(*root) < *t) return find(root->right(), t);
        if (*t < std::as_const(*root)) return find(root->left(), t);
        return root;
    }

    AVLTreeNodeT *select(int k) {
        propagate();
        const int leftsize = left() ? left()->size() : 0;
        if (k == leftsize) return (AVLTreeNodeT *)this;
        if (k < leftsize) return left()->select(k);
        return right()->select(k - leftsize - 1);
    }
};

template<typename FlipableAVLTreeNodeT> class FlipableAVLTreeNodeBase
    : public AVLTreeNodeBase<FlipableAVLTreeNodeT> {
    friend class AVLTreeNodeBase<FlipableAVLTreeNodeT>;

    bool NeedFlip;

    FlipableAVLTreeNodeT &underlying() { return (FlipableAVLTreeNodeT &)*this; }
    const FlipableAVLTreeNodeT &underlying() const { return (const FlipableAVLTreeNodeT &)*this; }

    // CRTP reimplement
    void do_flip() {}

    void base_flip() {
        NeedFlip = !NeedFlip;
        std::swap(this->L, this->R);
        underlying().do_flip();
    }
    void base_propagate() {
        underlying().do_propagate();
        if (NeedFlip) {
            NeedFlip = false;
            if (this->left()) this->left()->underlying().base_flip();
            if (this->right()) this->right()->underlying().base_flip();
        }
    }

protected:
    FlipableAVLTreeNodeBase() : NeedFlip() {}

public:
    void flip() { base_flip(); }
};
