#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"

#include <iostream>

#include "math/formal_power_series/formal_power_series.hpp"
#include "math/modulo/sqrt_mod.hpp"
#include "modint/Montgomery_modint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  using mint = lib::MontModInt<998244353>;
  using fps  = lib::FPS<mint>;
  int n;
  std::cin >> n;
  fps A(n);
  for (auto &i : A) std::cin >> i;
  if (A.deg() == -1) {
    for (int i = 0; i < n; ++i) std::cout << "0 ";
  } else
    for (int i = 0; i < n; ++i) {
      if (A[i] != 0) {
        auto t = lib::sqrt_mod_prime(A[i].get(), mint::get_mod());
        if (!t.empty()) {
          auto res = A.sqrt(n, mint(t[0]));
          if (res) {
            for (auto i : res.value()) std::cout << i << ' ';
          } else {
            std::cout << "-1\n";
          }
        } else {
          std::cout << "-1\n";
        }
        break;
      }
    }
  return 0;
}