#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"

#include "avl_tree_node_base.hpp"
#include "modint.hpp"
#include "node_pool.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    struct AVLTreeNode : FlipableAVLTreeNodeBase<AVLTreeNode> {
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
    DynamicSizeNodePool<AVLTreeNode> pool;
    AVLTreeNode *root = nullptr;
    for (int i = 0; i < n; ++i) {
        auto node = pool.make();
        std::cin >> node->Val;
        node->update();
        root = AVLTreeNode::join(root, node);
    }
    for (int i = 0; i < q; ++i) {
        int cmd;
        std::cin >> cmd;
        switch (cmd) {
        case 0: {
            int pos;
            auto node = pool.make();
            std::cin >> pos >> node->Val;
            node->update();
            auto [R0, R1] = AVLTreeNode::split(root, pos);
            root          = AVLTreeNode::join(R0, node, R1);
            break;
        }
        case 1: {
            int pos;
            std::cin >> pos;
            auto [R0, R1, R2] = AVLTreeNode::split(root, pos, 1);
            pool.retrieve(R1);
            root = AVLTreeNode::join(R0, R2);
            break;
        }
        case 2: {
            int l, r;
            std::cin >> l >> r;
            auto [R0, R1, R2] = AVLTreeNode::split(root, l, r - l);
            R1->flip();
            root = AVLTreeNode::join(R0, R1, R2);
            break;
        }
        case 3: {
            int l, r;
            std::cin >> l >> r;
            auto [R0, R1, R2] = AVLTreeNode::split(root, l, r - l);
            std::cin >> R1->Mul >> R1->Add;
            R1->propagate();
            R1->update();
            root = AVLTreeNode::join(R0, R1, R2);
            break;
        }
        case 4: {
            int l, r;
            std::cin >> l >> r;
            auto [R0, R1, R2] = AVLTreeNode::split(root, l, r - l);
            std::cout << R1->Sum << '\n';
            root = AVLTreeNode::join(R0, R1, R2);
            break;
        }
        default: break;
        }
    }
    return 0;
}
