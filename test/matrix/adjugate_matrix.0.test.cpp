// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/adjugate_matrix

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
    // P_A(x)=x^n+...+(-1)^n det(A)
    // A adj(A) = adj(A) A = det(A) I
    // A^n+...+(-1)^n det(A) I = O
    auto P = F.charpoly();
    P.erase(P.begin());
    if ((n & 1) == 0) {
        for (auto &&c : P) c = -c;
    }
    const auto res = F.transition_matrix() * F.eval(P) * F.inv_transition_matrix();
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) std::cout << res[i][j] << " \n"[j == n - 1];
    return 0;
}
