// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/pow_of_matrix

#include "frobenius.hpp"
#include "matrix.hpp"
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
    std::cin >> A;
    Frobenius<mint> F(A);
    const auto res = F.transition_matrix() * F.pow(k) * F.inv_transition_matrix();
    std::cout << res << '\n';
    return 0;
}
