#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_point_get"

#include "modint.hpp"
#include "node_pool.hpp"
#include "treap_node_base.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    struct TreapNode : TreapNodeBase<TreapNode> {
        mint Val, Add, Mul = {1};
        void do_propagate() {
            if (left()) {
                left()->Add = Mul * left()->Add + Add;
                left()->Mul *= Mul;
            }
            if (right()) {
                right()->Add = Mul * right()->Add + Add;
                right()->Mul *= Mul;
            }
            Val = Add + Mul * Val;
            Add = 0;
            Mul = 1;
        }
    };
    int n, q;
    std::cin >> n >> q;
    FixedSizeNodePool<TreapNode> pool(n);
    auto [node, id] = pool.get_func();
    TreapNode *root = nullptr;
    for (int i = 0; i < n; ++i) {
        std::cin >> node(i)->Val;
        root = TreapNode::join(root, node(i));
    }
    while (q--) {
        int cmd;
        std::cin >> cmd;
        if (cmd == 0) {
            int l, r;
            std::cin >> l >> r;
            auto [R0, R1, R2] = TreapNode::split(root, l, r - l);
            std::cin >> R1->Mul >> R1->Add;
            root = TreapNode::join(R0, R1, R2);
        } else {
            int pos;
            std::cin >> pos;
            std::cout << root->select(pos)->Val << '\n';
        }
    }
    return 0;
}
