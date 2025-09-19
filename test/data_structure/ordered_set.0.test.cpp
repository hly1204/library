#define PROBLEM "https://judge.yosupo.jp/problem/ordered_set"

#include "node_pool.hpp"
#include "treap_node_base.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    struct TreapNode : TreapNodeBase<TreapNode> {
        int Val;
        explicit TreapNode(int Val) : Val(Val) {}
        bool operator<(const TreapNode &other) const { return Val < other.Val; }
    };
    int n, q;
    std::cin >> n >> q;
    DynamicSizeNodePool<TreapNode> pool;
    TreapNode *root = nullptr;
    for (int i = 0; i < n; ++i) {
        int v;
        std::cin >> v;
        root = TreapNode::insert(root, pool.make(v));
    }
    while (q--) {
        int cmd, x;
        std::cin >> cmd >> x;
        const TreapNode t(x);
        switch (cmd) {
        case 0: {
            TreapNode *found = TreapNode::find(root, &t);
            if (!found) root = TreapNode::insert(root, pool.make(t.Val));
            break;
        }
        case 1: {
            TreapNode *found = TreapNode::find(root, &t);
            if (found) {
                auto [a, b, c] = TreapNode::split3(root, &t);
                TreapNode *d   = b;
                b              = TreapNode::join(b->left(), b->right());
                pool.retrieve(d);
                root = TreapNode::join(a, b, c);
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
            auto [a, b, c] = TreapNode::count3(root, &t);
            std::cout << a + b << '\n';
            break;
        }
        case 4: {
            if (TreapNode *found = TreapNode::find(root, &t)) {
                std::cout << found->Val << '\n';
            } else if (TreapNode *pred = TreapNode::predecessor(root, &t)) {
                std::cout << pred->Val << '\n';
            } else {
                std::cout << "-1\n";
            }
            break;
        }
        case 5: {
            if (TreapNode *found = TreapNode::find(root, &t)) {
                std::cout << found->Val << '\n';
            } else if (TreapNode *succ = TreapNode::successor(root, &t)) {
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
