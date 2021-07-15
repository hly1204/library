#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"

#include <iostream>

#include "math/matrix/characteristic_polynomial.hpp"
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
  for (auto i : lib::get_charpoly(m)) std::cout << i << ' ';
  return 0;
}