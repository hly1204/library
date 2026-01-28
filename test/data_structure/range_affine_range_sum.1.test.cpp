#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"

#include "avl_tree_node_base.hpp"
#include "modint.hpp"
#include "node_pool.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    struct AVLTreeNode : AVLTreeNodeBase<AVLTreeNode> {
        mint Val, Sum, Add, Mul = {1};
        void do_propagate() {
            if (left()) {
                left()->Add = Mul * left()->Add + Add;
                left()->Mul *= Mul;
                left()->Sum = Add * left()->size() + Mul * left()->Sum;
            }
            if (right()) {
                right()->Add = Mul * right()->Add + Add;
                right()->Mul *= Mul;
                right()->Sum = Add * right()->size() + Mul * right()->Sum;
            }
            Val = Add + Mul * Val;
            Add = 0;
            Mul = 1;
        }
        void do_update() {
            Sum = Val;
            if (left()) Sum += left()->Sum;
            if (right()) Sum += right()->Sum;
        }
    };
    int n, q;
    std::cin >> n >> q;
    FixedSizeNodePool<AVLTreeNode> pool(n);
    auto [node, id]   = pool.get_func();
    AVLTreeNode *root = nullptr;
    for (int i = 0; i < n; ++i) {
        std::cin >> node(i)->Val;
        node(i)->update();
        root = AVLTreeNode::join(root, node(i));
    }
    while (q--) {
        int cmd, l, r;
        std::cin >> cmd >> l >> r;
        auto [R0, R1, R2] = AVLTreeNode::split(root, l, r - l);
        if (cmd == 0) {
            std::cin >> R1->Mul >> R1->Add;
            R1->propagate();
            R1->update();
        } else {
            std::cout << R1->Sum << '\n';
        }
        root = AVLTreeNode::join(R0, R1, R2);
    }
    return 0;
}
