#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "disjoint_set.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    DisjointSet s(n);
    while (q--) {
        int t, u, v;
        std::cin >> t >> u >> v;
        if (t == 0) {
            s.unite(u, v);
        } else {
            std::cout << s.is_same(u, v) << '\n';
        }
    }
    return 0;
}
