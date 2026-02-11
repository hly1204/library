// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/matrix_product

#include "mat_basic.hpp"
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
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) std::cin >> A[i][j];
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < k; ++j) std::cin >> B[i][j];
    const auto AB = mat_mul(A, B);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < k; ++j) std::cout << AB[i][j] << " \n"[j == k - 1];
    return 0;
}
