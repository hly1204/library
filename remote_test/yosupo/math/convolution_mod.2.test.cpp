#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <iostream>
#include <vector>

#include "math/formal_power_series/relaxed_convolution.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::MontModInt<998244353>;
  int n, m;
  std::cin >> n >> m;
  std::vector<mint> A(n), B(m), C, D;
  for (auto &i : A) std::cin >> i;
  for (auto &i : B) std::cin >> i;
  lib::RelaxedConvolution<mint> rc(
      [&A](int i, const auto &) { return i < static_cast<int>(A.size()) ? A[i] : mint(0); },
      [&B](int i, const auto &) { return i < static_cast<int>(B.size()) ? B[i] : mint(0); });
  for (int i = 0; i < n + m - 1; ++i) std::cout << rc[i] << ' ';
  return 0;
}