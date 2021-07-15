#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

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
  int d;
  long long k;
  std::cin >> d >> k;
  lib::Poly<mint> rec(d), init(d), t{0, 1};
  for (auto &i : init) std::cin >> i;
  for (auto &i : rec) std::cin >> i, i = -i;
  std::reverse(rec.begin(), rec.end());
  rec.emplace_back(1);
  auto res = t.pow_mod(k, rec);
  res.resize(d, 0);
  mint ans = 0;
  for (int i = 0; i < d; ++i) ans += res[i] * init[i];
  std::cout << ans;
  return 0;
}