#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

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
  std::vector<mint> A(n);
  for (auto &i : A) std::cin >> i;
  mint iv = 1 / A[0];
  lib::SemiRelaxedConvolution rc(A, [&iv](int idx, const std::vector<mint> &contri) {
    if (idx == 0) return iv;
    return -contri[idx] * iv;
  });
  for (auto i : rc.await(n).get_multiplier()) std::cout << i << ' ';
  return 0;
}