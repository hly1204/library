#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

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
  int n;
  std::cin >> n;
  std::vector<mint> A, B(n), C(n);
  for (auto &i : B) std::cin >> i;
  for (int i = 0; i < n - 1; ++i) C[i] = B[i + 1] * (i + 1);
  lib::RelaxedConvolution<mint, decltype(lib::convolve<mint>)> rc(A, C, lib::convolve<mint>);
  A.emplace_back(1);
  std::cout << "1 ";
  for (int i = 1; i < n; ++i) {
    auto t = rc.next() / i;
    A.emplace_back(t);
    std::cout << t << ' ';
  }
  return 0;
}