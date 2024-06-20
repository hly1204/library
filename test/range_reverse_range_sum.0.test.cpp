#define PROBLEM "https://judge.yosupo.jp/problem/range_reverse_range_sum"

#include "treap_node_base.hpp"
#include <iostream>
#include <memory>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    struct TreapNode : TreapNodeBase<TreapNode> {
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
    auto buf        = std::make_unique<TreapNode[]>(n);
    TreapNode *root = nullptr;
    for (int i = 0; i < n; ++i) {
        std::cin >> buf[i].Val;
        buf[i].Sum = buf[i].Val;
        root       = TreapNode::join(root, &buf[i]);
    }
    while (q--) {
        int t, l, r;
        std::cin >> t >> l >> r;
        auto [a, b, c] = TreapNode::split3(root, l, r - l);
        if (t == 0) {
            if (b) b->flip();
        } else {
            std::cout << (b ? b->Sum : 0LL) << '\n';
        }
        root = TreapNode::join3(a, b, c);
    }
    return 0;
}
