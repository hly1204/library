#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_polynomials"

#include <iostream>

#include "math/formal_power_series/poly_gcd.hpp"
#include "math/formal_power_series/polynomial.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using poly = lib::Poly<lib::MontModInt<998244353>>;
  int n, m;
  std::cin >> n >> m;
  if (m == 1) {
    std::cout << "0";
    return 0;
  }
  poly A(n), B(m);
  for (auto &i : A) std::cin >> i;
  for (auto &i : B) std::cin >> i;
  auto iA = lib::poly_inv(A, B);
  if (iA) {
    std::cout << iA.value().deg() + 1 << '\n';
    for (auto i : iA.value()) std::cout << i << ' ';
  } else {
    std::cout << "-1";
  }
  return 0;
}