#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_E"

#include <iostream>

#include "math/basic/exgcd.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int a, b;
  std::cin >> a >> b;
  int c, d;
  std::tie(std::ignore, c, d) = lib::exgcd(a, b);
  std::cout << c << ' ' << d << '\n';
  return 0;
}