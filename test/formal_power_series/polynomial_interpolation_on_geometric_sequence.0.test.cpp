#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation_on_geometric_sequence"

#include "czt.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    mint a, r;
    std::cin >> n >> a >> r;
    std::vector<mint> F(n);
    for (int i = 0; i < n; ++i) std::cin >> F[i];
    const auto res = inv_czt(F, r, a);
    for (int i = 0; i < n; ++i) std::cout << res[i] << ' ';
    return 0;
}
