#define PROBLEM "https://judge.yosupo.jp/problem/composition_of_formal_power_series_large"

#include "math/fps_composition.hpp"
#include "modint/montgomery_modint.hpp"

#include <algorithm>
#include <iostream>
#include <iterator>

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
  std::cin >> f >> g;
  for (auto &&c : lib::composition(f, g, n)) std::cout << c << ' ';
  return 0;
}
