#define PROBLEM "https://judge.yosupo.jp/problem/jump_on_tree"

#include "st_tree_node_base.hpp"
#include <iostream>
#include <memory>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    struct STTreeNode : STTreeNodeBase<STTreeNode> {};
    auto buf = std::make_unique<STTreeNode[]>(n);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        buf[a].link(&buf[b]);
    }
    while (q--) {
        int s, t, i;
        std::cin >> s >> t >> i;
        buf[t].evert();
        buf[s].expose();
        if (buf[s].size() <= i) {
            std::cout << "-1\n";
        } else {
            std::cout << buf[s].select(buf[s].size() - i - 1) - &buf[0] << '\n';
        }
    }
    return 0;
}
