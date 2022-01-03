#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include <iostream>

#include "math/formal_power_series/formal_power_series.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  lib::FPS<lib::MontModInt<998244353>> A(n);
  for (auto &i : A) std::cin >> i;
  for (auto i : A.exp(n)) std::cout << i << ' ';
  return 0;
}