#pragma once

#include <cassert>
#include <utility>

template<typename STTreeNodeT> class STTreeNodeBase {
    STTreeNodeBase *L;
    STTreeNodeBase *R;
    STTreeNodeBase *P;
    int Size;
    bool NeedFlip;

    STTreeNodeT *derived() { return (STTreeNodeT *)this; }
    enum class Child { LEFT, RIGHT };
    Child which() const {
        assert(P != nullptr);
        return P->L == this ? Child::LEFT : Child::RIGHT;
    }
    // not root OR not a prefered child
    bool is_root() const { return P == nullptr || (P->L != this && P->R != this); }
    bool is_left_child() const { return which() == Child::LEFT; }
    bool is_right_child() const { return which() == Child::RIGHT; }

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
    // There is no need to update the information combined from child(ren)
    // which should be done in base_update().
    void base_propagate() {
        derived()->do_propagate();
        if (NeedFlip) {
            NeedFlip = false;
            if (L) L->base_flip();
            if (R) R->base_flip();
        }
    }
    // base_update() is called to update the information combined from child(ren).
    void base_update() {
        Size = 1;
        if (L) Size += L->Size;
        if (R) Size += R->Size;
        derived()->do_update();
    }
    void base_rotate() {
        assert(P != nullptr);
        P->base_propagate();
        base_propagate();
        if (is_left_child()) {
            if ((P->L = R)) R->P = P;
            if (!P->is_root()) {
                if (P->is_left_child()) P->P->L = this;
                else { P->P->R = this; }
            }
            R = P, P = P->P, R->P = this;
            R->base_update();
        } else {
            if ((P->R = L)) L->P = P;
            if (!P->is_root()) {
                if (P->is_left_child()) P->P->L = this;
                else { P->P->R = this; }
            }
            L = P, P = P->P, L->P = this;
            L->base_update();
        }
    }
    void base_splay() {
        for (base_propagate(); !is_root(); base_rotate()) {
            if (!P->is_root()) {
                P->P->base_propagate();
                P->which() == which() ? P->base_rotate() : base_rotate();
            }
        }
        base_update();
    }

    STTreeNodeBase() : L(), R(), P(), Size(1), NeedFlip() {}

public:
    int size() const { return Size; }

    STTreeNodeT *left() const { return (STTreeNodeT *)L; }
    STTreeNodeT *right() const { return (STTreeNodeT *)R; }

    void update() { base_update(); }

    STTreeNodeT *expose() {
        STTreeNodeBase *a = this, *lca = a;
        base_splay();
        a->R = nullptr;
        while (a->P) {
            lca = a->P;
            lca->base_splay();
            a->P->R = a;
            a->base_rotate();
        }
        a->base_update(); // now a is the root
        return (STTreeNodeT *)lca;
    }
    void evert() {
        expose();
        base_flip();
    }
    STTreeNodeT *root() {
        expose();
        STTreeNodeBase *a = this;
        while (a->L) a = a->L;
        a->base_splay();
        return (STTreeNodeT *)a;
    }
    STTreeNodeT *parent() {
        expose();
        if (!L) return nullptr;
        STTreeNodeBase *a = L;
        a->base_propagate();
        while (a->R) {
            a = a->R;
            a->base_propagate();
        }
        a->base_splay();
        return (STTreeNodeT *)a;
    }
    void link(STTreeNodeT *a) {
        evert();
        if (a->root() != derived()) P = a;
    }
    void cut() {
        expose();
        STTreeNodeBase *b = L;
        L                 = nullptr;
        if (b) b->P = nullptr;
        base_update();
    }
    void cut(STTreeNodeT *b) {
        if (parent() == b) {
            cut();
        } else if (b->parent() == derived()) {
            b->cut();
        }
    }
    STTreeNodeT *select(int k) {
        STTreeNodeBase *a = this;
        a->base_propagate();
        while ((a->L ? a->L->size() : 0) != 0) {
            if ((a->L ? a->L->size() : 0) < k) {
                k -= (a->L ? a->L->size() : 0) + 1;
                a = a->R;
            } else {
                a = a->L;
            }
            a->base_propagate();
        }
        a->base_splay();
        return a;
    }
};
