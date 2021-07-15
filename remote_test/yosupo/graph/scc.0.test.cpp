#define PROBLEM "https://judge.yosupo.jp/problem/scc"

#include <iostream>
#include <vector>

#include "graph/strongly_connected_components_Tarjan.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m;
  std::cin >> n >> m;
  lib::StronglyConnectedComponentsGraph g(n);
  while (m--) {
    int u, v;
    std::cin >> u >> v;
    g.add_directed_edge(u, v);
  }
  auto [scccnt, sccno] = g.get_scc();
  std::vector<std::vector<int>> topo(scccnt);
  for (int i = 0; i < n; ++i) topo[sccno[i]].push_back(i);
  std::reverse(topo.begin(), topo.end());
  std::cout << scccnt << '\n';
  for (auto &i : topo) {
    std::cout << i.size() << ' ';
    for (auto j : i) std::cout << j << ' ';
    std::cout << '\n';
  }
  return 0;
}