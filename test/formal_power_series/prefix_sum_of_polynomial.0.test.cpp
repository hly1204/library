// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/prefix_sum_of_polynomial

#include "prefix_sum_of_polynomial.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    std::vector<mint> f(n);
    for (int i = 0; i < n; ++i) std::cin >> f[i];
    const auto g = poly_prefix_sum(std::move(f));
    for (int i = 0; i <= n; ++i) std::cout << g[i] << ' ';
    return 0;
}
