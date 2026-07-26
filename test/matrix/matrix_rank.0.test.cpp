// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/matrix_rank

#include "matrix.hpp"
#include "modint.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int m, n;
    std::cin >> m >> n;
    Matrix<mint> A(m, std::vector<mint>(n));
    std::cin >> A;
    std::cout << A.rank() << '\n';
    return 0;
}
