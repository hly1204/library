// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/characteristic_polynomial

#include "matrix.hpp"
#include "modint.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    Matrix<mint> A(n, std::vector<mint>(n));
    std::cin >> A;
    const auto P = A.charpoly();
    for (int i = 0; i <= n; ++i) std::cout << P[i] << ' ';
    return 0;
}
