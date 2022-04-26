#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include "math/formal_power_series.hpp"
#include "modint/montgomery_modint.hpp"

#include <iostream>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  using mint = lib::mm30<998244353>;
  lib::fps<mint> f({0, 1}), res(f.Q().Exp());
  for (int i = 0; i <= n; ++i) std::cout << res[i] << ' ';
  return 0;
}