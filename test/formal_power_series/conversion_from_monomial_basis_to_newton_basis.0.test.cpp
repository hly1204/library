// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/conversion_from_monomial_basis_to_newton_basis

#include "modint.hpp"
#include "subproduct_tree.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    std::vector<mint> F(n), X(n);
    for (int i = 0; i < n; ++i) std::cin >> F[i];
    for (int i = 0; i < n; ++i) std::cin >> X[i];
    SubproductTree<mint> T(X);
    const auto res = T.monomial_to_newton(F);
    for (int i = 0; i < n; ++i) std::cout << res[i] << ' ';
    return 0;
}
