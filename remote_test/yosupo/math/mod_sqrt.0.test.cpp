#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include <iostream>
#include <vector>

#include "math/modulo/sqrt_mod.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int t;
  std::cin >> t;
  while (t--) {
    int k, p;
    std::cin >> k >> p;
    auto res = lib::sqrt_mod_prime(k, p);
    if (res.empty()) std::cout << "-1\n";
    else
      std::cout << res[0] << '\n';
  }
  return 0;
}