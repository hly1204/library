// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/lca

#include "node_pool.hpp"
#include "st_tree_node_base.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    struct STTreeNode : STTreeNodeBase<STTreeNode> {};
    FixedSizeNodePool<STTreeNode> pool(n);
    auto [node, id] = pool.get_func();
    for (int i = 0; i < n - 1; ++i) {
        int p;
        std::cin >> p;
        node(p)->link(node(i + 1));
    }
    node(0)->evert();
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        node(u)->expose();
        std::cout << id(node(v)->expose()) << '\n';
    }
    return 0;
}
