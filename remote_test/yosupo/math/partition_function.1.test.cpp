#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include <iostream>

#include "math/formal_power_series/implicit_series.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::MontModInt<998244353>;
  lib::ImplicitSeries<mint> A({0, 1}), B(A.Q().Exp());
  int n;
  std::cin >> n;
  for (int i = 0; i <= n; ++i) std::cout << B[i] << ' ';
  return 0;
}