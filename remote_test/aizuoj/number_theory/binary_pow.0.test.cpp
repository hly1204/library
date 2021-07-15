#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_1_B"

#include <iostream>

#include "math/basic/binary_pow.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m;
  std::cin >> n >> m;
  std::cout << lib::pow_mod(n, m, 1000000007) << '\n';
  return 0;
}