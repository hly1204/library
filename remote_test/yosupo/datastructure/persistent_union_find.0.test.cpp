#define PROBLEM "https://judge.yosupo.jp/problem/persistent_unionfind"

#include <functional>
#include <iostream>
#include <vector>

#include "datastructure/basic/rollbackable_disjoint_set.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, q;
  std::cin >> n >> q;
  std::vector<std::tuple<int, int, int>> query(1);
  std::vector<int> ans(q + 1, -1);
  std::vector<std::vector<int>> g;
  g.resize(q + 1);
  for (int i = 1; i <= q; ++i) {
    int t, k, u, v;
    std::cin >> t >> k >> u >> v;
    ++k; // let k in [0, i]
    query.push_back({t, u, v});
    g[k].push_back(i);
  }
  lib::RollbackableDisjointSet ds(n);
  std::function<void(int)> dfs = [&](int s) {
    auto [a, b, c] = query[s];
    if (a == 1) {
      ans[s] = int(ds.same(b, c));
    } else {
      b         = ds.find(b);
      c         = ds.find(c);
      bool flag = (b != c);
      if (flag) ds.unite(b, c);
      for (auto i : g[s]) dfs(i);
      if (flag) ds.undo();
    }
  };
  for (auto i : g[0]) dfs(i);
  for (auto i : ans)
    if (i != -1) std::cout << i << '\n';
  return 0;
}