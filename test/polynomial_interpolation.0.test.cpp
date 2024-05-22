#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

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
    std::vector<mint> X(n), Y(n);
    for (int i = 0; i < n; ++i) std::cin >> X[i];
    for (int i = 0; i < n; ++i) std::cin >> Y[i];
    SubproductTree<mint> T(X);
    const auto res = T.interpolation(Y);
    for (int i = 0; i < n; ++i) std::cout << res[i] << ' ';
    return 0;
}
