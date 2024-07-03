#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_matrix"

#include "frobenius.hpp"
#include "mat_basic.hpp"
#include "modint.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    long long k;
    std::cin >> n >> k;
    Matrix<mint> A(n, std::vector<mint>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) std::cin >> A[i][j];
    Frobenius<mint> F(A);
    const auto res = mat_mul(F.transition_matrix(), mat_mul(F.pow(k), F.inv_transition_matrix()));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) std::cout << res[i][j] << " \n"[j == n - 1];
    return 0;
}
