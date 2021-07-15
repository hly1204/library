#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include <algorithm>
#include <iostream>

#include "math/formal_power_series/formal_power_series.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::MontModInt<998244353>;
  int d;
  long long k;
  std::cin >> d >> k;
  lib::FPS<mint> rec(d), init_v(d), res{1};
  for (auto &i : init_v) std::cin >> i;
  for (auto &i : rec) std::cin >> i, i = -i;
  rec.insert(rec.begin(), 1);
  std::cout << (init_v * rec).slice(d).div_at(rec, k);
  return 0;
}