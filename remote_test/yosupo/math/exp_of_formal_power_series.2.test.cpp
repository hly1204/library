#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include <iostream>
#include <vector>

#include "math/formal_power_series/semi_relaxed_convolution.hpp"
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
  std::vector<mint> A(n), B;
  for (auto &i : A) std::cin >> i;
  for (int i = 1; i < n; ++i) A[i - 1] = A[i] * i;
  auto res = lib::semi_relaxed_convolve(n, A, B, [](int idx, const std::vector<mint> &contri) {
    if (idx == 0) return mint(1);
    return contri[idx - 1] / idx;
  });
  for (auto i : B) std::cout << i << ' ';
  return 0;
}