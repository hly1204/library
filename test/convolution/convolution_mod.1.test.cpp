// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod

#include "modint.hpp"
#include "poly_portable.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, m;
    std::cin >> n >> m;
    std::vector<mint> a(n), b(m);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < m; ++i) std::cin >> b[i];
    const std::vector<mint> ab = product(a, b);
    for (int i = 0; i < n + m - 1; ++i) std::cout << ab[i];
    return 0;
}
