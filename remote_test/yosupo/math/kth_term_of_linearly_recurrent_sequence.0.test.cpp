#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include <algorithm>
#include <iostream>

#include "math/formal_power_series/linearly_recurrent_sequence_Bostan_Mori.hpp"
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
  std::vector<mint> rec(d), init_v(d);
  for (auto &i : init_v) std::cin >> i;
  for (auto &i : rec) std::cin >> i;
  std::reverse(rec.begin(), rec.end());
  lib::LinearlyRecurrentSequence seq(rec, init_v);
  std::cout << seq[k];
  return 0;
}