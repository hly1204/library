#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_polynomials"

#include "modint.hpp"
#include "poly.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, m;
    std::cin >> n >> m;
    Poly<mint> A(n), B(m);
    for (int i = 0; i < n; ++i) std::cin >> A[i];
    for (int i = 0; i < m; ++i) std::cin >> B[i];
    auto [I, G] = inv_gcd(A, B);
    if (G.deg() == 0) {
        I /= G;
        std::cout << I.deg() + 1 << '\n';
        for (int i = 0; i <= I.deg(); ++i) std::cout << I[i] << ' ';
    } else {
        std::cout << "-1";
    }
    return 0;
}
