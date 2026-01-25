#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"

#include "node_pool.hpp"
#include "treap_node_base.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    struct TreapNode : FlipableTreapNodeBase<TreapNode> {
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
    FixedSizeNodePool<TreapNode> pool(n);
    auto [node, id] = pool.get_func();
    TreapNode *root = nullptr;
    for (int i = 0; i < n; ++i) {
        std::cin >> node(i)->Val;
        node(i)->Sum = node(i)->Val;
        root         = TreapNode::join(root, node(i));
    }
    while (q--) {
        int t, l, r;
        std::cin >> t >> l >> r;
        auto [a, b, c] = TreapNode::split(root, l, r - l);
        if (t == 0) {
            if (b) b->flip();
        } else {
            std::cout << (b ? b->Sum : 0LL) << '\n';
        }
        root = TreapNode::join(a, b, c);
    }
    return 0;
}
