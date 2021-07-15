#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

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
  int n, m;
  std::cin >> n >> m;
  poly f(n);
  for (auto &i : f) std::cin >> i;
  std::vector<mint> x_set(m);
  for (auto &i : x_set) std::cin >> i;
  auto y_set = lib::evaluate(f, x_set);
  for (auto i : y_set) std::cout << i << ' ';
  return 0;
}