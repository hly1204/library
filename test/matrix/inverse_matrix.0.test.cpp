// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/inverse_matrix

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
    if (const auto invA = mat_inv(A)) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) std::cout << invA->at(i).at(j) << " \n"[j == n - 1];
    } else {
        std::cout << "-1";
    }
    return 0;
}
