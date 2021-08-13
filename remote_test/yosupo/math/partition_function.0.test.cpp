#define PROBLEM "https://judge.yosupo.jp/problem/partition_function"

#include <iostream>

#include "math/famous_sequence/partition_function_P.hpp"
#include "math/formal_power_series/formal_power_series.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::MontModInt<998244353>;
  using fps  = lib::FPS<mint>;
  int n;
  std::cin >> n;
  fps res;
  lib::partition_function_P(n + 1, res);
  for (auto i : res) std::cout << i << ' ';
  return 0;
}