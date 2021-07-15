#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include "datastructure/basic/disjoint_set.hpp"

#include <iostream>

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, q;
  std::cin >> n >> q;
  lib::DisjointSet ds(n);
  while (q--) {
    int cmd, u, v;
    std::cin >> cmd >> u >> v;
    if (cmd == 0) {
      ds.unite(u, v);
    } else {
      std::cout << int(ds.same(u, v)) << '\n';
    }
  }
  return 0;
}