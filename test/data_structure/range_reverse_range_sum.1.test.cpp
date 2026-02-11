// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/range_reverse_range_sum

#include "avl_tree_node_base.hpp"
#include "node_pool.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    struct AVLTreeNode : FlipableAVLTreeNodeBase<AVLTreeNode> {
        int Val;
        long long Sum;
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
        node(i)->Sum = node(i)->Val;
        root         = AVLTreeNode::join(root, node(i));
    }
    while (q--) {
        int t, l, r;
        std::cin >> t >> l >> r;
        auto [a, b, c] = AVLTreeNode::split(root, l, r - l);
        if (t == 0) {
            if (b) b->flip();
        } else {
            std::cout << (b ? b->Sum : 0LL) << '\n';
        }
        root = AVLTreeNode::join(a, b, c);
    }
    return 0;
}
