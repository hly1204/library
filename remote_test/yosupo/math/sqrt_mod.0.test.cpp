#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include "math/sqrt_mod.hpp"
#include "modint/runtime_montgomery_modint.hpp"

#include <cassert>
#include <iostream>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) {
    int k, p;
    std::cin >> k >> p;
    if (p == 2) {
      std::cout << k << '\n';
    } else {
      bool ok = lib::rmm30<-1>::set_mod(p);
      assert(ok);
      auto res = lib::sqrt_mod_prime<lib::rmm30<-1>>(k);
      if (res.empty()) {
        std::cout << "-1\n";
      } else {
        std::cout << res.front() << '\n';
      }
    }
  }
  return 0;
}