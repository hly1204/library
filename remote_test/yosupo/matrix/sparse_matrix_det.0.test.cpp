#define PROBLEM "https://judge.yosupo.jp/problem/sparse_matrix_det"

#include <iostream>

#include "math/matrix/black_box_linear_algebra.hpp"
#include "math/matrix/sparse_square_matrix.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, k;
  std::cin >> n >> k;
  lib::SparseSquareMatrix<lib::MontModInt<998244353>> m(n, 0);
  while (k--) {
    int r, c, v;
    std::cin >> r >> c >> v;
    m.at(r, c) = v;
  }
  std::cout << lib::black_box_det(m);
  return 0;
}