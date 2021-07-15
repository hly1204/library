#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include <algorithm>
#include <iostream>

#include "math/formal_power_series/polynomial.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::MontModInt<998244353>;
  int n, m;
  std::cin >> n >> m;
  lib::Poly<mint> f(n), g(m);
  for (auto &i : f) std::cin >> i;
  for (auto &i : g) std::cin >> i;
  auto [q, r] = f.divmod(g);
  std::cout << q.deg() + 1 << ' ' << r.deg() + 1 << '\n';
  if (q.deg() != -1)
    for (auto i : q) std::cout << i << ' ';
  std::cout << '\n';
  if (r.deg() != -1)
    for (auto i : r) std::cout << i << ' ';
  return 0;
}