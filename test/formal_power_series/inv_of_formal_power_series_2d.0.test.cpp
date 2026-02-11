// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/inv_of_formal_power_series_2d

#include "modint.hpp"
#include "mps_basic.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, m;
    std::cin >> n >> m;
    std::vector<mint> a(n * m);
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) std::cin >> a[i * m + j];
    const auto invA = mps_inv(MDConvInfo({m, n}), a);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j) std::cout << ' ';
            std::cout << invA[i * m + j];
        }
        std::cout << '\n';
    }
    return 0;
}
