// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/adjugate_matrix

#include "matrix.hpp"
#include "modint.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    Matrix<mint> A(n, std::vector<mint>(n));
    std::cin >> A;
    std::cout << A.adj() << '\n';
    return 0;
}
