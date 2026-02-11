// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/ordered_set

#include "avl_tree_node_base.hpp"
#include "node_pool.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    struct AVLTreeNode : AVLTreeNodeBase<AVLTreeNode> {
        int Val;
        explicit AVLTreeNode(int Val) : Val(Val) {}
        bool operator<(const AVLTreeNode &other) const { return Val < other.Val; }
    };
    int n, q;
    std::cin >> n >> q;
    DynamicSizeNodePool<AVLTreeNode> pool;
    AVLTreeNode *root = nullptr;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        const AVLTreeNode t(v);
        AVLTreeNode *found = AVLTreeNode::find(root, &t);
        if (!found) root = AVLTreeNode::insert(root, pool.make(v));
    }
    while (q--) {
        int cmd, x;
        std::cin >> cmd >> x;
        const AVLTreeNode t(x);
        switch (cmd) {
        case 0: {
            AVLTreeNode *found = AVLTreeNode::find(root, &t);
            if (!found) root = AVLTreeNode::insert(root, pool.make(t.Val));
            break;
        }
        case 1: {
            AVLTreeNode *found = AVLTreeNode::find(root, &t);
            if (found) {
                auto [a, b, c] = AVLTreeNode::split3(root, &t);
                AVLTreeNode *d = b;
                b              = AVLTreeNode::join(b->left(), b->right());
                pool.retrieve(d);
                root = AVLTreeNode::join(a, b, c);
            }
            break;
        }
        case 2: {
            if (root && root->size() >= x) {
                std::cout << root->select(x - 1)->Val << '\n';
            } else {
                std::cout << "-1\n";
            }
            break;
        }
        case 3: {
            std::cout << AVLTreeNode::count_less_equal(root, &t) << '\n';
            break;
        }
        case 4: {
            if (AVLTreeNode *found = AVLTreeNode::find(root, &t)) {
                std::cout << found->Val << '\n';
            } else if (AVLTreeNode *pred = AVLTreeNode::predecessor(root, &t)) {
                std::cout << pred->Val << '\n';
            } else {
                std::cout << "-1\n";
            }
            break;
        }
        case 5: {
            if (AVLTreeNode *found = AVLTreeNode::find(root, &t)) {
                std::cout << found->Val << '\n';
            } else if (AVLTreeNode *succ = AVLTreeNode::successor(root, &t)) {
                std::cout << succ->Val << '\n';
            } else {
                std::cout << "-1\n";
            }
            break;
        }
        default: break;
        }
    }
    return 0;
}
