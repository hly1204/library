#pragma once

#include "rng.hpp"
#include <random>
#include <tuple>
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
    void base_propagate() {
        derived()->do_propagate();
        if (NeedFlip) {
            NeedFlip = false;
            if (L) L->base_flip();
            if (R) R->base_flip();
        }
    }
    void base_update() {
        Size = 1;
        if (L) Size += L->Size;
        if (R) Size += R->Size;
        derived()->do_update();
    }

    static TreapNodeBase *base_join(TreapNodeBase *a, TreapNodeBase *b) {
        if (a == nullptr) return b;
        if (b == nullptr) return a;
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

    static TreapNodeBase *base_join3(TreapNodeBase *a, TreapNodeBase *b, TreapNodeBase *c) {
        return base_join(base_join(a, b), c);
    }

    static std::pair<TreapNodeBase *, TreapNodeBase *> base_split(TreapNodeBase *a, int k) {
        if (a == nullptr) return {nullptr, nullptr};
        if (k == 0) return {nullptr, a};
        a->base_propagate();
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

    static std::tuple<TreapNodeBase *, TreapNodeBase *, TreapNodeBase *>
    base_split3(TreapNodeBase *a, int l, int m) {
        auto [b, c] = base_split(a, l);
        auto [d, e] = base_split(c, m);
        return {b, d, e};
    }

    TreapNodeBase() : L(), R(), Rank(dis(gen)), Size(1), NeedFlip() {}

public:
    int size() const { return Size; }
    int rank() const { return Rank; }

    TreapNode *left() const { return (TreapNode *)L; }
    TreapNode *right() const { return (TreapNode *)R; }

    void flip() { base_flip(); }
    static TreapNode *join(TreapNode *a, TreapNode *b) { return (TreapNode *)base_join(a, b); }
    static TreapNode *join3(TreapNode *a, TreapNode *b, TreapNode *c) {
        return (TreapNode *)base_join3(a, b, c);
    }
    static std::pair<TreapNode *, TreapNode *> split(TreapNode *a, int k) {
        auto [b, c] = base_split(a, k);
        return {(TreapNode *)b, (TreapNode *)c};
    }
    static std::tuple<TreapNode *, TreapNode *, TreapNode *> split3(TreapNode *a, int l, int m) {
        auto [b, c, d] = base_split3(a, l, m);
        return {(TreapNode *)b, (TreapNode *)c, (TreapNode *)d};
    }
};
