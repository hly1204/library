#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include <iostream>
#include <vector>

#include "math/formal_power_series/egf.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m, mod = 998244353;
  unsigned long long c, uc = 1;
  std::cin >> n >> c;
  lib::EGF egf(mod);
  std::vector<int> A(n), B(n);
  for (int i = 0; i < n; ++i) std::cin >> A[i];
  for (int i = 0; i < n; ++i) B[i] = uc, uc = uc * c % mod;
  auto res = egf.binom_convolveT(A, B);
  for (auto i : res) std::cout << i << ' ';
  return 0;
}