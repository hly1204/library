#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include <iostream>

#include "math/formal_power_series/polynomial.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  lib::MontModInt<998244353> c;
  std::cin >> n >> c;
  lib::Poly<lib::MontModInt<998244353>> a(n);
  for (auto &i : a) std::cin >> i;
  a = a.shift(c);
  a.resize(n, 0);
  for (auto i : a) std::cout << i << ' ';
  return 0;
}