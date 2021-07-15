#define PROBLEM "https://judge.yosupo.jp/problem/matrix_product"

#include <iostream>

#include "math/matrix/matrix_base.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m, k;
  std::cin >> n >> m >> k;
  lib::Matrix<lib::MontModInt<998244353>> a(n, m), b(m, k);
  std::cin >> a >> b;
  std::cout << a * b;
  return 0;
}