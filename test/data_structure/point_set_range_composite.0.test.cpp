#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "modint.hpp"
#include "treap_node_base.hpp"
#include <array>
#include <iostream>
#include <memory>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint           = ModInt<998244353>;
    using LinearFunction = std::array<mint, 2>;
    struct TreapNode : TreapNodeBase<TreapNode> {
        LinearFunction Val, Sum;
        static LinearFunction composition(const LinearFunction &L, const LinearFunction &R) {
            return LinearFunction{L[0] + L[1] * R[0], L[1] * R[1]};
        }
        void do_update() {
            Sum = Val;
            if (left()) Sum = composition(Sum, left()->Sum);
            if (right()) Sum = composition(right()->Sum, Sum);
        }
    };
    int n, q;
    std::cin >> n >> q;
    auto buf        = std::make_unique<TreapNode[]>(n);
    TreapNode *root = nullptr;
    for (int i = 0; i < n; ++i) {
        std::cin >> buf[i].Val[1] >> buf[i].Val[0];
        root = TreapNode::join(root, &buf[i]);
    }
    while (q--) {
        int cmd;
        std::cin >> cmd;
        if (cmd == 0) {
            int p;
            std::cin >> p;
            auto [R0, R1, R2] = TreapNode::split(root, p, 1);
            std::cin >> R1->Val[1] >> R1->Val[0];
            root = TreapNode::join(R0, R1, R2);
        } else {
            int l, r;
            mint x;
            std::cin >> l >> r >> x;
            auto [R0, R1, R2] = TreapNode::split(root, l, r - l);
            std::cout << TreapNode::composition(R1->Sum, {x, 0}).at(0) << '\n';
            root = TreapNode::join(R0, R1, R2);
        }
    }
    return 0;
}
