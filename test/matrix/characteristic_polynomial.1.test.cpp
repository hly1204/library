#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"

#include "frobenius.hpp"
#include "mat_basic.hpp"
#include "modint.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    Matrix<mint> A(n, std::vector<mint>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) std::cin >> A[i][j];
    Frobenius<mint> F(A);
    const auto charp = F.charpoly();
    for (int i = 0; i <= n; ++i) std::cout << charp[i] << ' ';
    return 0;
}
