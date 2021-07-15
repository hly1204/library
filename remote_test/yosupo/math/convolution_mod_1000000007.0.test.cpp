#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include <iostream>
#include <vector>

#include "math/formal_power_series/arbitrary_modulo_convolution.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m;
  std::cin >> n >> m;
  std::vector<int> A(n), B(m);
  for (auto &i : A) std::cin >> i;
  for (auto &i : B) std::cin >> i;
  for (auto i : lib::convolve_mod(A, B, 1000000007)) std::cout << i << ' ';
  return 0;
}