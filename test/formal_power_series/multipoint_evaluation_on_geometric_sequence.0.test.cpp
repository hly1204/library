#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation_on_geometric_sequence"

#include "czt.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, m;
    mint a, r;
    std::cin >> n >> m >> a >> r;
    std::vector<mint> F(n);
    for (int i = 0; i < n; ++i) std::cin >> F[i];
    const auto res = czt(F, r, m, a);
    for (int i = 0; i < m; ++i) std::cout << res[i] << ' ';
    return 0;
}
