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
    int Rank;
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

protected:
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
        if (a->Rank < b->Rank) {
            b->L = base_join(a, b->L);
            b->update();
            return b;
        }
        a->R = base_join(a->R, b);
        a->update();
        return a;
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
        }
        auto [b, c] = base_split(a->L, k);
        a->L        = c;
        a->update();
        return {b, a};
    }

    TreapNodeBase() : L(), R(), Rank(dis(gen)), Size(1) {}

public:
    int size() const { return Size; }
    int rank() const { return Rank; }
    TreapNodeT *left() const { return (TreapNodeT *)L; }
    TreapNodeT *right() const { return (TreapNodeT *)R; }
    void update() { base_update(); }
    void propagate() { underlying().base_propagate(); }

    template<typename... Nodes> static TreapNodeT *join(Nodes... node) {
        struct Helper {
            TreapNodeBase *Val;
            Helper &operator|(TreapNodeBase *A) {
                Val = TreapNodeBase::base_join(Val, A);
                return *this;
            }
        } nil{nullptr};
        return (TreapNodeT *)(nil | ... | node).Val;
    }
    template<typename... Parts>
    static std::array<TreapNodeT *, sizeof...(Parts) + 1> split(TreapNodeT *a, Parts... part) {
        std::array<TreapNodeT *, sizeof...(Parts) + 1> res;
        res[0]    = a;
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
