#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "rmq.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> V(n);
    for (int i = 0; i < n; ++i) std::cin >> V[i];
    RMQ rmq(V);
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << rmq.query(l, r) << '\n';
    }
    return 0;
}
