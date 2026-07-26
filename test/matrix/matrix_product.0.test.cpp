// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/matrix_product

#include "matrix.hpp"
#include "modint.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, m, k;
    std::cin >> n >> m >> k;
    Matrix<mint> A(n, std::vector<mint>(m));
    Matrix<mint> B(m, std::vector<mint>(k));
    std::cin >> A >> B;
    std::cout << A * B << '\n';
    return 0;
}
