#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"

#include "modint.hpp"
#include "st_tree_node_base.hpp"
#include <array>
#include <iostream>
#include <memory>
#include <utility>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint           = ModInt<998244353>;
    using LinearFunction = std::array<mint, 2>;
    struct STTreeNode : STTreeNodeBase<STTreeNode> {
        LinearFunction Val, Sum, RevSum;
        static LinearFunction composition(const LinearFunction &L, const LinearFunction &R) {
            return LinearFunction{L[0] + L[1] * R[0], L[1] * R[1]};
        }
        void do_flip() { std::swap(Sum, RevSum); }
        void do_update() {
            Sum = RevSum = Val;
            if (left()) {
                Sum    = composition(left()->Sum, Sum);
                RevSum = composition(RevSum, left()->RevSum);
            }
            if (right()) {
                Sum    = composition(Sum, right()->Sum);
                RevSum = composition(right()->RevSum, RevSum);
            }
        }
    };
    int n, m;
    std::cin >> n >> m;
    auto buf = std::make_unique<STTreeNode[]>(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> buf[i].Val[1] >> buf[i].Val[0];
        buf[i].update();
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        buf[u].link(&buf[v]);
    }
    while (m--) {
        int cmd;
        std::cin >> cmd;
        if (cmd == 0) {
            int a, b, c, d;
            std::cin >> a >> b >> c >> d;
            buf[a].cut(&buf[b]);
            buf[c].link(&buf[d]);
        } else if (cmd == 1) {
            int a;
            std::cin >> a;
            buf[a].expose();
            std::cin >> buf[a].Val[1] >> buf[a].Val[0];
            buf[a].update();
        } else {
            int a, b;
            mint x;
            std::cin >> a >> b >> x;
            buf[b].evert();
            buf[a].expose();
            std::cout << STTreeNode::composition(buf[a].Sum, {x, 0}).at(0) << '\n';
        }
    }
    return 0;
}
