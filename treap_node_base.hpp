#pragma once

#include "rng.hpp"
#include <array>
#include <random>
#include <utility>

template<typename FlipableTreapNodeT> class FlipableTreapNodeBase;

template<typename TreapNodeT> class TreapNodeBase {
    friend class FlipableTreapNodeBase<TreapNodeT>;

    TreapNodeBase *L;
    TreapNodeBase *R;
    const int Rank;
    int Size;

    TreapNodeT &underlying() { return (TreapNodeT &)*this; }
    const TreapNodeT &underlying() const { return (const TreapNodeT &)*this; }

    static inline xoshiro256starstar gen{std::random_device{}()};
    static inline std::uniform_int_distribution<int> dis{0, 998244353 - 1};

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
        underlying().do_update();
    }

    static TreapNodeBase *base_join(TreapNodeBase *a, TreapNodeBase *b) {
        if (a == nullptr) {
            if (b) b->propagate(), b->update();
            return b;
        }
        if (b == nullptr) {
            if (a) a->propagate(), a->update();
            return a;
        }
        a->propagate();
        b->propagate();
        // MAX HEAP
        if (a->rank() < b->rank()) {
            b->L = base_join(a, b->L);
            b->update();
            return b;
        } else {
            a->R = base_join(a->R, b);
            a->update();
            return a;
        }
    }

    static std::array<TreapNodeBase *, 2> base_split(TreapNodeBase *a, int k) {
        if (a == nullptr) return {nullptr, nullptr};
        a->propagate();
        if (k == 0) return {nullptr, a};
        if (k == a->Size) return {a, nullptr};
        const int leftsize = a->L != nullptr ? a->L->Size : 0;
        if (leftsize < k) {
            auto [b, c] = base_split(a->R, k - leftsize - 1);
            a->R        = b;
            a->update();
            return {a, c};
        } else {
            auto [b, c] = base_split(a->L, k);
            a->L        = c;
            a->update();
            return {b, a};
        }
    }

    TreapNodeBase *base_rotate_left() {
        /*    x              b
             / \            / \
            a   b    =>    x   d
               / \        / \
              c   d      a   c    */
        TreapNodeBase *b = R;
        b->propagate();
        R = b->L, b->L = this;
        update();
        b->update();
        return b;
    }
    TreapNodeBase *base_rotate_right() {
        /*    x              a
             / \            / \
            a   b    =>    c   x
           / \                / \
          c   d              d   b */
        TreapNodeBase *a = L;
        a->propagate();
        L = a->R, a->R = this;
        update();
        a->update();
        return a;
    }

protected:
    TreapNodeBase() : L(), R(), Rank(dis(gen)), Size(1) {}

public:
    int size() const { return Size; }
    int rank() const { return Rank; }
    TreapNodeT *left() const { return (TreapNodeT *)L; }
    TreapNodeT *right() const { return (TreapNodeT *)R; }
    void update() { base_update(); }
    void propagate() { underlying().base_propagate(); }
    static TreapNodeT *insert(TreapNodeT *root, TreapNodeT *t) {
        if (root == nullptr) return t;
        root->propagate();
        if (std::as_const(*t) < std::as_const(*root)) {
            root->L = insert(root->left(), t);
            root->update();
            if (root->rank() < root->left()->rank()) return (TreapNodeT *)root->base_rotate_right();
        } else {
            root->R = insert(root->right(), t);
            root->update();
            if (root->rank() < root->right()->rank()) return (TreapNodeT *)root->base_rotate_left();
        }
        return root;
    }
    static int count_less_than(TreapNodeT *root, const TreapNodeT *t) {
        if (root == nullptr) return 0;
        root->propagate();
        if (std::as_const(*root) < *t) {
            return (root->left() ? root->left()->size() : 0) + 1 +
                   count_less_than(root->right(), t);
        } else {
            return count_less_than(root->left(), t);
        }
    }
    static int count_less_equal(TreapNodeT *root, const TreapNodeT *t) {
        if (root == nullptr) return 0;
        root->propagate();
        if (*t < std::as_const(*root)) {
            return count_less_equal(root->left(), t);
        } else {
            return (root->left() ? root->left()->size() : 0) + 1 +
                   count_less_equal(root->right(), t);
        }
    }
    // [<, >=]
    static std::array<TreapNodeT *, 2> split_less_than(TreapNodeT *root, const TreapNodeT *t) {
        if (root == nullptr) return {nullptr, nullptr};
        root->propagate();
        if (std::as_const(*root) < *t) {
            auto [a, b] = split_less_than(root->right(), t);
            root->R     = a;
            root->update();
            return {root, b};
        } else {
            auto [a, b] = split_less_than(root->left(), t);
            root->L     = b;
            root->update();
            return {a, root};
        }
    }
    static int count_greater_than(TreapNodeT *root, const TreapNodeT *t) {
        if (root == nullptr) return 0;
        root->propagate();
        if (*t < std::as_const(*root)) {
            return (root->right() ? root->right()->size() : 0) + 1 +
                   count_greater_than(root->left(), t);
        } else {
            return count_greater_than(root->right(), t);
        }
    }
    static int count_greater_equal(TreapNodeT *root, const TreapNodeT *t) {
        if (root == nullptr) return 0;
        root->propagate();
        if (std::as_const(*root) < *t) {
            return count_greater_equal(root->right(), t);
        } else {
            return (root->right() ? root->right()->size() : 0) + 1 +
                   count_greater_equal(root->left(), t);
        }
    }
    // [<=, >]
    static std::array<TreapNodeT *, 2> split_less_equal(TreapNodeT *root, const TreapNodeT *t) {
        if (root == nullptr) return {nullptr, nullptr};
        root->propagate();
        if (*t < std::as_const(*root)) {
            auto [a, b] = split_less_equal(root->left(), t);
            root->L     = b;
            root->update();
            return {a, root};
        } else {
            auto [a, b] = split_less_equal(root->right(), t);
            root->R     = a;
            root->update();
            return {root, b};
        }
    }
    static int count(TreapNodeT *root, const TreapNodeT *t) {
        if (root == nullptr) return 0;
        root->propagate();
        if (*t < std::as_const(*root)) return count(root->left(), t);
        if (std::as_const(*root) < *t) return count(root->right(), t);
        int res = 1;
        if (root->left()) res += root->left()->size() - count_less_than(root->left(), t);
        if (root->right()) res += root->right()->size() - count_greater_than(root->right(), t);
        return res;
    }
    static std::array<int, 3> count3(TreapNodeT *root, const TreapNodeT *t) {
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
    static std::array<TreapNodeT *, 3> split3(TreapNodeT *root, const TreapNodeT *t) {
        if (root == nullptr) return {nullptr, nullptr, nullptr};
        root->propagate();
        if (*t < std::as_const(*root)) {
            auto [a, b, c] = split3(root->left(), t);
            root->L        = c;
            root->update();
            return {a, b, root};
        }
        if (std::as_const(*root) < *t) {
            auto [a, b, c] = split3(root->right(), t);
            root->R        = a;
            root->update();
            return {root, b, c};
        }
        auto [a, b] = split_less_than(root->left(), t);
        auto [c, d] = split_less_equal(root->right(), t);
        root->L = b, root->R = c;
        root->update();
        return {a, root, d};
    }
    static TreapNodeT *predecessor(TreapNodeT *root, const TreapNodeT *t) {
        TreapNodeT *res = nullptr;
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
    static TreapNodeT *successor(TreapNodeT *root, const TreapNodeT *t) {
        TreapNodeT *res = nullptr;
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

    template<typename... Nodes> static TreapNodeT *join(Nodes... root) {
        struct Helper {
            TreapNodeBase *Val;
            Helper &operator|(TreapNodeBase *A) {
                Val = TreapNodeBase::base_join(Val, A);
                return *this;
            }
        } nil{nullptr};
        return (TreapNodeT *)(nil | ... | root).Val;
    }
    template<typename... Parts>
    static std::array<TreapNodeT *, sizeof...(Parts) + 1> split(TreapNodeT *root, Parts... part) {
        std::array<TreapNodeT *, sizeof...(Parts) + 1> res;
        res[0]    = root;
        int index = 0;
        (
            [&](int s) {
                auto [l, r]  = base_split(res[index], s);
                res[index]   = (TreapNodeT *)l;
                res[++index] = (TreapNodeT *)r;
            }(part),
            ...);
        return res;
    }

    static TreapNodeT *find(TreapNodeT *root, const TreapNodeT *t) {
        if (root == nullptr) return nullptr;
        root->propagate();
        if (std::as_const(*root) < *t) return find(root->right(), t);
        if (*t < std::as_const(*root)) return find(root->left(), t);
        return root;
    }

    TreapNodeT *select(int k) {
        propagate();
        const int leftsize = left() ? left()->size() : 0;
        if (k == leftsize) return (TreapNodeT *)this;
        if (k < leftsize) return left()->select(k);
        return right()->select(k - leftsize - 1);
    }
};

template<typename FlipableTreapNodeT> class FlipableTreapNodeBase
    : public TreapNodeBase<FlipableTreapNodeT> {
    friend class TreapNodeBase<FlipableTreapNodeT>;

    bool NeedFlip;

    FlipableTreapNodeT &underlying() { return (FlipableTreapNodeT &)*this; }
    const FlipableTreapNodeT &underlying() const { return (const FlipableTreapNodeT &)*this; }

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
    FlipableTreapNodeBase() : NeedFlip() {}

public:
    void flip() { base_flip(); }
};
