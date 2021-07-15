#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_A"

#include <iostream>

#include "graph/single_source_shortest_path_Dijkstra.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m, s;
  std::cin >> n >> m >> s;
  lib::NonnegativeShortestPathGraph<int> g(n);
  while (m--) {
    int u, v, w;
    std::cin >> u >> v >> w;
    g.add_directed_edge(u, v, w);
  }
  auto [dist, pred] = g.get_sssp(s);
  for (int i = 0; i < n; ++i) {
    if (pred[i] == -1 && i != s) {
      std::cout << "INF\n";
    } else {
      std::cout << dist[i] << '\n';
    }
  }
  return 0;
}