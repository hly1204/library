#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include <iostream>
#include <vector>

#include "math/Walsh_transform_relatives/radix_2_Walsh_transform.hpp"
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
  int len = 1 << n;
  std::vector<mint> A(len), B(len);
  for (auto &i : A) std::cin >> i;
  for (auto &i : B) std::cin >> i;
  auto AB = lib::dyadic_convolve(A, B);
  for (auto i : AB) std::cout << i << ' ';
  return 0;
}