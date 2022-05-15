#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_polynomials"

#include "math/poly_extended_gcd.hpp"
#include "math/polynomial.hpp"
#include "modint/montgomery_modint.hpp"

#include <iostream>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, m;
  std::cin >> n >> m;
  lib::polynomial<lib::mm30<998244353>> A(n), B(m);
  for (auto &&i : A) std::cin >> i;
  for (auto &&i : B) std::cin >> i;
  auto iA = lib::poly_inv(A, B);
  if (iA) {
    std::cout << iA->deg() + 1 << '\n';
    for (auto i : iA.value()) std::cout << i << ' ';
  } else {
    std::cout << "-1";
  }
  return 0;
}