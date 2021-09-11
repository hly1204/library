#define PROBLEM "https://judge.yosupo.jp/problem/bernoulli_number"

#include "math/famous_sequence/Bernoulli_numbers.hpp"
#include "math/formal_power_series/formal_power_series.hpp"
#include "modint/Montgomery_modint.hpp"

#include <iostream>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n;
  std::cin >> n;
  lib::FPS<lib::MontModInt<998244353>> res;
  lib::Bernoulli_numbers(n + 1, res);
  for (auto i : res) std::cout << i << ' ';
  return 0;
}