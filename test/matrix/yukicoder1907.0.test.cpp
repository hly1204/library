// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/1907

#include "mat_extra.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    Matrix<std::vector<mint>> A(n, std::vector(n, std::vector<mint>(2)));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) { std::cin >> A[i][j][0]; }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) { std::cin >> A[i][j][1]; }
    }
    auto d = det_d(A);
    d.resize(n + 1);
    for (int i = 0; i <= n; ++i) std::cout << d[i] << '\n';
    return 0;
}
