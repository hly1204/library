#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/6/NTL/all/NTL_2_E"

#include <iostream>
#include <string>

#include "math/basic/bigint.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  lib::BigInt a, b;
  std::cin >> a >> b;
  std::cout << a % b << '\n';
  return 0;
}