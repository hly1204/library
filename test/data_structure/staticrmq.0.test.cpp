#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include "monoid.hpp"
#include "sparse_table.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<int> V(n);
    for (int i = 0; i < n; ++i) std::cin >> V[i];
    SparseTable st(V, Monoid([](int a, int b) { return a < b ? a : b; }, -1));
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << st.query(l, r) << '\n';
    }
    return 0;
}
