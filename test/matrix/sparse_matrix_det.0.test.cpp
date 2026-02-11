// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/sparse_matrix_det

#include "mat_sparse.hpp"
#include "modint.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, k;
    std::cin >> n >> k;
    SparseMatrix<mint> M;
    while (k--) {
        int x, y;
        mint z;
        std::cin >> x >> y >> z;
        M.emplace_back(x, y, z);
    }
    std::cout << det(M, n);
    return 0;
}
