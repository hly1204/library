#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <iostream>
#include <vector>

#include "graph/static_tree_binary_lifting.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, q;
  std::cin >> n >> q;
  std::vector<int> p(n);
  p[0] = -1;
  for (int i = 1; i < n; ++i) std::cin >> p[i];
  lib::StaticTreeBinaryLifting tree(p);
  while (q--) {
    int u, v;
    std::cin >> u >> v;
    std::cout << tree.query_lca(u, v) << '\n';
  }
  return 0;
}