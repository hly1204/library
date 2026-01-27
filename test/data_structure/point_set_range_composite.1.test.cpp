#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"

#include "avl_tree_node_base.hpp"
#include "modint.hpp"
#include "node_pool.hpp"
#include <array>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint           = ModInt<998244353>;
    using LinearFunction = std::array<mint, 2>;
    struct AVLTreeNode : AVLTreeNodeBase<AVLTreeNode> {
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
    FixedSizeNodePool<AVLTreeNode> pool(n);
    auto [node, id]   = pool.get_func();
    AVLTreeNode *root = nullptr;
    for (int i = 0; i < n; ++i) {
        std::cin >> node(i)->Val[1] >> node(i)->Val[0];
        node(i)->update();
        root = AVLTreeNode::join(root, node(i));
    }
    while (q--) {
        int cmd;
        std::cin >> cmd;
        if (cmd == 0) {
            int p;
            std::cin >> p;
            auto [R0, R1, R2] = AVLTreeNode::split(root, p, 1);
            std::cin >> R1->Val[1] >> R1->Val[0];
            root = AVLTreeNode::join(R0, R1, R2);
        } else {
            int l, r;
            mint x;
            std::cin >> l >> r >> x;
            auto [R0, R1, R2] = AVLTreeNode::split(root, l, r - l);
            std::cout << AVLTreeNode::composition(R1->Sum, {x, 0}).at(0) << '\n';
            root = AVLTreeNode::join(R0, R1, R2);
        }
    }
    return 0;
}
