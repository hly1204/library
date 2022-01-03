#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

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
  int n, m;
  std::cin >> n >> m;
  lib::ImplicitSeries<mint> A([](int) {
    mint v;
    std::cin >> v;
    return v;
  }),
      pA(A.pow(m));
  for (int i = 0; i != n; ++i) std::cout << pA[i] << ' ';
  return 0;
}