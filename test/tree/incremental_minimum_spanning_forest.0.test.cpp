// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/incremental_minimum_spanning_forest

#include "node_pool.hpp"
#include "st_tree_node_base.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    struct Node : STTreeNodeBase<Node> {
        int W     = -1;
        Node *Max = this;
        int From, To;
        void do_update() {
            Max = this;
            if (left() && left()->Max->W > Max->W) Max = left()->Max;
            if (right() && right()->Max->W > Max->W) Max = right()->Max;
        }
    };
    FixedSizeNodePool<Node> p(n + m);
    auto [node, id] = p.get_func();
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        std::cin >> u >> v >> w;
        node(n + i)->W    = w;
        node(n + i)->From = u;
        node(n + i)->To   = v;
        node(n + i)->update();
        if (node(u)->root() != node(v)->root()) {
            node(u)->link(node(n + i));
            node(v)->link(node(n + i));
            std::cout << "-1 ";
        } else if (node(u)->Max->W > w) {
            Node *max = node(u)->Max;
            max->cut(node(max->From));
            max->cut(node(max->To));
            node(u)->link(node(n + i));
            node(v)->link(node(n + i));
            std::cout << id(max) - n << ' ';
        } else {
            std::cout << i << ' ';
        }
    }
    return 0;
}
