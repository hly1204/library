#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum"

#include "node_pool.hpp"
#include "st_tree_node_base.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    struct STTreeNode : STTreeNodeBase<STTreeNode> {
        long long Val, Sum;
        void do_update() {
            Sum = Val;
            if (left()) Sum += left()->Sum;
            if (right()) Sum += right()->Sum;
        }
    };
    FixedSizeNodePool<STTreeNode> pool(n);
    auto [node, id] = pool.get_func();
    for (int i = 0; i < n; ++i) {
        std::cin >> node(i)->Val;
        node(i)->update();
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        node(u)->link(node(v));
    }
    while (q--) {
        int cmd;
        std::cin >> cmd;
        if (cmd == 0) {
            int u, v, w, x;
            std::cin >> u >> v >> w >> x;
            node(u)->cut(node(v));
            node(w)->link(node(x));
        } else if (cmd == 1) {
            int p, x;
            std::cin >> p >> x;
            node(p)->expose();
            node(p)->Val += x;
            node(p)->update();
        } else {
            int u, v;
            std::cin >> u >> v;
            node(u)->evert();
            node(v)->expose();
            std::cout << node(v)->Sum << '\n';
        }
    }
    return 0;
}
