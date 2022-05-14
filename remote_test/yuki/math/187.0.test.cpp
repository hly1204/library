#define PROBLEM "https://yukicoder.me/problems/448"

#include "math/cra.hpp"

#include <algorithm>
#include <iostream>
#include <vector>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<int> a(n), m(n);
  for (int i = 0; i != n; ++i) std::cin >> a[i] >> m[i];
  auto res = lib::cra_mod(a, m, 1000000007);
  if (res) {
    if (std::all_of(a.begin(), a.end(), [](int n) { return n == 0; })) {
      std::cout << res->second << '\n';
    } else {
      std::cout << res->first << '\n';
    }
  } else {
    std::cout << -1 << '\n';
  }
  return 0;
}