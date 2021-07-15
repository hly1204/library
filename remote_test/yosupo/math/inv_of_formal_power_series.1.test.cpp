#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include <iostream>
#include <vector>

#include "math/formal_power_series/formal_power_series.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::MontModInt<998244353>;
  int n;
  std::cin >> n;
  lib::FPS<mint> a(n);
  for (auto &i : a) std::cin >> i;
  for (auto i : a.inv(n)) std::cout << i << ' ';
  return 0;
}