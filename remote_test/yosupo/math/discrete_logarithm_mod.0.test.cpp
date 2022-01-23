#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"

#include <iostream>

#include "math/modulo/discrete_log_BSGS.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int T;
  std::cin >> T;
  while (T--) {
    int x, y, m;
    std::cin >> x >> y >> m;
    std::cout << lib::discrete_log(x, y, m) << '\n';
  }
  return 0;
}