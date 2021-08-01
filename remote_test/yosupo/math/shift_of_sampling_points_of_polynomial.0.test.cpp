#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"

#include <iostream>
#include <vector>

#include "math/formal_power_series/convolution.hpp"
#include "math/formal_power_series/sample_points_shift.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::MontModInt<998244353>;
  int n, m;
  mint c;
  std::cin >> n >> m >> c;
  std::vector<mint> pts(n);
  for (auto &i : pts) std::cin >> i;
  pts = lib::shift_sample_points(m, pts, c, lib::convolve_cyclic<mint>);
  for (auto i : pts) std::cout << i << ' ';
  return 0;
}