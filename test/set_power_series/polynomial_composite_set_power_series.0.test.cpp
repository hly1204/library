// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/polynomial_composite_set_power_series

#include "modint.hpp"
#include "sps_in_poly.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, m;
    std::cin >> n >> m;
    std::vector<mint> F(n), G(1 << m);
    for (int i = 0; i < n; ++i) std::cin >> F[i];
    for (int i = 0; i < (1 << m); ++i) std::cin >> G[i];
    const auto FG = sps_in_poly(F, G);
    for (int i = 0; i < (1 << m); ++i) std::cout << FG[i] << ' ';
    return 0;
}
