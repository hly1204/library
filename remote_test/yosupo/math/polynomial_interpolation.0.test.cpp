#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"

#include <iostream>
#include <vector>

#include "math/formal_power_series/polynomial.hpp"
#include "math/formal_power_series/subproduct_tree.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::MontModInt<998244353>;
  using poly = lib::Poly<mint>;
  int n;
  std::cin >> n;
  std::vector<mint> x(n), y(n);
  for (auto &i : x) std::cin >> i;
  for (auto &i : y) std::cin >> i;
  poly res;
  lib::interpolate(x, y, res);
  res.resize(n, 0);
  for (auto i : res) std::cout << i << ' ';
  return 0;
}