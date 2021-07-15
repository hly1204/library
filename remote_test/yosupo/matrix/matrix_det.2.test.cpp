#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det"

#include <iostream>

#include "math/matrix/arbitrary_modulo_square_matrix.hpp"
#include "modint/runtime_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::RuntimeModInt<0>;
  mint::set_mod(998244353);
  int n;
  std::cin >> n;
  lib::ArbitraryModuloSquareMatrix<mint> m(n);
  std::cin >> m;
  std::cout << m.det();
  return 0;
}