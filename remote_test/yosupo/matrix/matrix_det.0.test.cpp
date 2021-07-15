#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include <iostream>

#include "math/matrix/square_matrix.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  lib::SquareMatrix<lib::MontModInt<998244353>> m(n);
  std::cin >> m;
  std::cout << m.det();
  return 0;
}