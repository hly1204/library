#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include <iostream>
#include <vector>

#include "math/formal_power_series/convolution.hpp"
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
  lib::RelaxedConvolution<mint, decltype(lib::convolve<mint>)> rc(C, D, lib::convolve<mint>);
  for (int i = 0; i < n + m - 1; ++i) {
    if (i < n) C.emplace_back(A[i]);
    if (i < m) D.emplace_back(B[i]);
    std::cout << rc.next() << ' ';
  }
  return 0;
}