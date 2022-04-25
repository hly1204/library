#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_E"

#include "math/extended_gcd.hpp"

#include <iostream>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int a, b;
  std::cin >> a >> b;
  auto [c, d, g] = lib::ext_gcd(a, b);
  std::cout << c << ' ' << d << '\n';
  return 0;
}