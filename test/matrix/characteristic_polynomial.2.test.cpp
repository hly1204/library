#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"

#include "mat_extra.hpp"
#include "modint.hpp"
#include <array>
#include <cassert>
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    using poly = std::array<mint, 2>;
    int n;
    std::cin >> n;
    Matrix<poly> A(n, std::vector<poly>(n));
    for (int i = 0; i < n; ++i) {
        A[i][i][1] = 1;
        for (int j = 0; j < n; ++j) {
            std::cin >> A[i][j][0];
            A[i][j][0] = -A[i][j][0];
        }
    }
    const auto P = det2(A);
    assert((int)P.size() == n + 1);
    for (int i = 0; i <= n; ++i) std::cout << P[i] << ' ';
    return 0;
}
