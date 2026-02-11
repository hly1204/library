// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/product_of_polynomial_sequence

#include "modint.hpp"
#include "poly_product.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    std::vector<std::vector<mint>> L;
    while (n--) {
        int d;
        std::cin >> d;
        auto &&p = L.emplace_back(d + 1);
        for (int i = 0; i <= d; ++i) std::cin >> p[i];
    }
    const auto res = poly_product(L);
    for (int i = 0; i < (int)res.size(); ++i) std::cout << res[i] << ' ';
    return 0;
}
