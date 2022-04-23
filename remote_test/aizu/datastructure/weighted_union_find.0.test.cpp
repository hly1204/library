#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_B"

#include "datastructure/weighted_disjoint_set.hpp"

#include <iostream>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, q;
  std::cin >> n >> q;
  lib::weighted_disjoint_set<int> ds(n);
  while (q--) {
    int op, x, y, z;
    std::cin >> op >> x >> y;
    if (op == 0) {
      std::cin >> z;
      ds.relate(x, y, z);
    } else {
      if (auto res = ds.diff(x, y); res) {
        std::cout << *res << '\n';
      } else {
        std::cout << "?\n";
      }
    }
  }
  return 0;
}