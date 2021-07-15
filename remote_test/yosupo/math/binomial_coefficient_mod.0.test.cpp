#define PROBLEM "https://judge.yosupo.jp/problem/binomial_coefficient"

#include "math/modulo/binomial_coefficient_mod.hpp"

#include <iostream>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int t, m;
  std::cin >> t >> m;
  lib::BinomialCoefficientModSmall bc(m);
  while (t--) {
    long long n, m;
    std::cin >> n >> m;
    std::cout << bc(n, m) << '\n';
  }
  return 0;
}