// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/multipoint_evaluation

#include "modint.hpp"
#include "subproduct_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, m;
    std::cin >> n >> m;
    std::vector<mint> f(n), p(m);
    for (int i = 0; i < n; ++i) std::cin >> f[i];
    for (int i = 0; i < m; ++i) std::cin >> p[i];
    SubproductTree<mint> T(p);
    const auto res = T.evaluation(f);
    for (int i = 0; i < m; ++i) std::cout << res[i] << ' ';
    return 0;
}
