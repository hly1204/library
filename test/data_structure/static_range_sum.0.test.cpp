// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/static_range_sum

#include "disjoint_sparse_table.hpp"
#include "monoid.hpp"
#include <functional>
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, q;
    std::cin >> n >> q;
    std::vector<long long> V(n);
    for (int i = 0; i < n; ++i) std::cin >> V[i];
    DisjointSparseTable dst(V, Monoid(std::plus<long long>(), 0LL));
    while (q--) {
        int l, r;
        std::cin >> l >> r;
        std::cout << dst.query(l, r) << '\n';
    }
    return 0;
}
