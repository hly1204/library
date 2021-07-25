#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_1_C"

#include <iostream>
#include <vector>

#include "math/basic/linear_sieve.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  auto prime = lib::prime_table(100000001);
  std::vector<bool> is_pri(100000001, false);
  for (auto i : prime) is_pri[i] = true;
  int n, cnt = 0;
  std::cin >> n;
  while (n--) {
    int v;
    std::cin >> v;
    cnt += is_pri[v];
  }
  std::cout << cnt << '\n';
  return 0;
}