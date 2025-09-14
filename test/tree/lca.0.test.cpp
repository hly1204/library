#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include "st_tree_node_base.hpp"
#include <iostream>
#include <memory>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    struct STTreeNode : STTreeNodeBase<STTreeNode> {};
    auto buf = std::make_unique<STTreeNode[]>(n);
    for (int i = 0; i < n - 1; ++i) {
        int p;
        std::cin >> p;
        buf[p].link(&buf[i + 1]);
    }
    buf[0].evert();
    while (m--) {
        int u, v;
        std::cin >> u >> v;
        buf[u].expose();
        std::cout << buf[v].expose() - &buf[0] << '\n';
    }
    return 0;
}
