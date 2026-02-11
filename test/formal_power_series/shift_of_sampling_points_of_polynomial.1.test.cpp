// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial

#include "modint.hpp"
#include "shift_sample_points.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, m;
    mint c;
    std::cin >> n >> m >> c;
    std::vector<mint> F(n);
    for (int i = 0; i < n; ++i) std::cin >> F[i];
    const auto res = shift_sample_points(F, c, m);
    for (int i = 0; i < m; ++i) std::cout << res[i] << ' ';
    return 0;
}
