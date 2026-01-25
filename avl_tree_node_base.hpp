#pragma once

#include <algorithm>
#include <array>
#include <cassert>
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
