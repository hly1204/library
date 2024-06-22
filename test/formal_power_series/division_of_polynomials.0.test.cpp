#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include "modint.hpp"
#include "poly_basic.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, m;
    std::cin >> n >> m;
    std::vector<mint> f(n), g(m);
    for (int i = 0; i < n; ++i) std::cin >> f[i];
    for (int i = 0; i < m; ++i) std::cin >> g[i];
    auto [q, r] = euclidean_div(f, g);
    const int u = degree(q) + 1;
    const int v = degree(r) + 1;
    std::cout << u << ' ' << v << '\n';
    for (int i = 0; i < u; ++i) std::cout << q[i] << ' ';
    std::cout << '\n';
    for (int i = 0; i < v; ++i) std::cout << r[i] << ' ';
    return 0;
}
