#define PROBLEM "https://judge.yosupo.jp/problem/sharp_p_subset_sum"

#include "math/formal_power_series.hpp"
#include "modint/montgomery_modint.hpp"

#include <iostream>
#include <vector>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, t;
  std::cin >> n >> t;
  using mint = lib::mm30<998244353>;
  std::vector<mint> a(t + 1);
  for (int k; n--;) {
    std::cin >> k;
    a[k] += 1;
  }
  lib::fps<mint> f(a), res(f.Exp_m());
  for (int i = 1; i <= t; ++i) std::cout << res[i] << ' ';
  return 0;
}