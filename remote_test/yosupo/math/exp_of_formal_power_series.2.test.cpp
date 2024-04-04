#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include "math/binomial.hpp"
#include "math/fps_composition.hpp"
#include "math/truncated_formal_power_series.hpp"
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
  lib::tfps<mint> f(n), g(n);
  std::cin >> f;
  lib::binomial<mint> bin(n);
  for (int i = 0; i != n; ++i) g[i] = bin.inv_factorial(i);
  for (auto &&c : lib::composition(g, f, n)) std::cout << c << ' ';
  return 0;
}
