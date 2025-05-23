#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include "modint.hpp"
#include "poly.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    std::vector<mint> A(n);
    for (int i = 0; i < n; ++i) std::cin >> A[i];
    const auto [P, Q] = rational_reconstruction(A);
    const auto res    = Q.monic();
    std::cout << res.deg() << '\n';
    for (int i = res.deg() - 1; i >= 0; --i) std::cout << -res[i] << ' ';
    return 0;
}
