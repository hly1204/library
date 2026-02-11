// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/jump_on_tree

#include "node_pool.hpp"
#include "st_tree_node_base.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    struct STTreeNode : STTreeNodeBase<STTreeNode> {};
    FixedSizeNodePool<STTreeNode> pool(n);
    auto [node, id] = pool.get_func();
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        node(a)->link(node(b));
    }
    while (q--) {
        int s, t, i;
        std::cin >> s >> t >> i;
        node(t)->evert();
        node(s)->expose();
        if (node(s)->size() > i) {
            std::cout << id(node(s)->jump(i)) << '\n';
        } else {
            std::cout << "-1\n";
        }
    }
    return 0;
}
