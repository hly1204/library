// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/system_of_linear_equations

#include "matrix.hpp"
#include "modint.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, m;
    std::cin >> n >> m;
    Matrix<mint> A(n, std::vector<mint>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) std::cin >> A[i][j];
    Matrix<mint> w(1, std::vector<mint>(n));
    std::cin >> w;
    std::vector<int> p;
    auto [B, X] = A.transpose().gauss(&p);
    Matrix<mint> v(1, std::vector<mint>(m));
    // solve v*A = w
    for (int i = 0; i < (int)p.size(); ++i) v[0][i] = w[0][p[i]];
    if (v * B == w) {
        std::cout << m - (int)p.size() << '\n';
        std::cout << v * X << '\n';
        for (int i = m - (int)p.size() + 1; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                if (j) std::cout << ' ';
                std::cout << X[i][j];
            }
            std::cout << '\n';
        }
    } else {
        std::cout << "-1\n";
    }
    return 0;
}
