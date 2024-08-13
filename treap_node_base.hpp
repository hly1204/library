#pragma once

#include "rng.hpp"
#include <array>
#include <random>
#include <utility>

template <typename TreapNode>
class TreapNodeBase {
    TreapNodeBase *L;
    TreapNodeBase *R;
    int Rank;
    int Size;
    bool NeedFlip;

    static inline xoshiro256starstar gen{std::random_device{}()};
    static inline std::uniform_int_distribution<int> dis{0, 998244353};

    TreapNode *derived() { return (TreapNode *)this; }

    // CRTP reimplement
    void do_flip() {}
    void do_propagate() {}
    void do_update() {}

protected:
    void base_flip() {
        NeedFlip = !NeedFlip;
        std::swap(L, R);
        derived()->do_flip();
    }
    // base_propagate() is called to propagate the update information to child(ren).
    // There is no need to update the infomation combined from child(ren)
    // which should be done in base_update().
    void base_propagate() {
        derived()->do_propagate();
        if (NeedFlip) {
            NeedFlip = false;
            if (L) L->base_flip();
            if (R) R->base_flip();
        }
    }
    // base_update() is called to update the infomation combined from child(ren).
    void base_update() {
        Size = 1;
        if (L) Size += L->Size;
        if (R) Size += R->Size;
        derived()->do_update();
    }

    static TreapNodeBase *base_join(TreapNodeBase *a, TreapNodeBase *b) {
        if (a == nullptr) {
            if (b) b->base_propagate(), b->base_update();
            return b;
        }
        if (b == nullptr) {
            if (a) a->base_propagate(), a->base_update();
            return a;
        }
        a->base_propagate();
        b->base_propagate();
        if (a->Rank < b->Rank) {
            b->L = base_join(a, b->L);
            b->base_update();
            return b;
        }
        a->R = base_join(a->R, b);
        a->base_update();
        return a;
    }

    static std::array<TreapNodeBase *, 2> base_split(TreapNodeBase *a, int k) {
        if (a == nullptr) return {nullptr, nullptr};
        a->base_propagate();
        if (k == 0) return {nullptr, a};
        if (k == a->Size) return {a, nullptr};
        const int leftsize = a->L != nullptr ? a->L->Size : 0;
        if (leftsize < k) {
            auto [b, c] = base_split(a->R, k - leftsize - 1);
            a->R        = b;
            a->base_update();
            return {a, c};
        }
        auto [b, c] = base_split(a->L, k);
        a->L        = c;
        a->base_update();
        return {b, a};
    }

    TreapNodeBase() : L(), R(), Rank(dis(gen)), Size(1), NeedFlip() {}

public:
    int size() const { return Size; }
    int rank() const { return Rank; }

    TreapNode *left() const { return (TreapNode *)L; }
    TreapNode *right() const { return (TreapNode *)R; }

    void flip() { base_flip(); }
    template <typename... Nodes>
    static TreapNode *join(Nodes... node) {
        struct Helper {
            TreapNodeBase *Val;
            Helper &operator|(TreapNodeBase *A) {
                Val = TreapNodeBase::base_join(Val, A);
                return *this;
            }
        } nil{nullptr};
        return (TreapNode *)(nil | ... | node).Val;
    }
    template <typename... Parts>
    static std::array<TreapNode *, sizeof...(Parts) + 1> split(TreapNode *a, Parts... part) {
        std::array<TreapNode *, sizeof...(Parts) + 1> res;
        res[0]    = a;
        int index = 0;
        (
            [&](int s) {
                auto [l, r]  = base_split(res[index], s);
                res[index]   = (TreapNode *)l;
                res[++index] = (TreapNode *)r;
            }(part),
            ...);
        return res;
    }

    TreapNode *select(int k) {
        base_propagate();
        const int leftsize = left() ? left()->size() : 0;
        if (k == leftsize) return (TreapNode *)this;
        if (k < leftsize) return left()->select(k);
        return right()->select(k - leftsize - 1);
    }
};
