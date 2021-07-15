#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path"

#include <iostream>
#include <limits>
#include <vector>

#include "graph/single_source_shortest_path_Dijkstra.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m, s, t;
  std::cin >> n >> m >> s >> t;
  lib::NonnegativeShortestPathGraph<long long> g(n);
  while (m--) {
    int a, b, c;
    std::cin >> a >> b >> c;
    g.add_directed_edge(a, b, c);
  }
  auto [dist, pred] = g.get_sssp(s);
  if (pred[t] == -1) {
    std::cout << -1 << '\n';
  } else {
    std::vector<std::pair<int, int>> path;
    int prev = -1;
    int end  = t;
    while (prev != s) {
      path.push_back({prev = pred[end], end});
      end = pred[end];
    }
    std::reverse(path.begin(), path.end());
    std::cout << dist[t] << ' ' << path.size() << '\n';
    for (auto &i : path) std::cout << i.first << ' ' << i.second << '\n';
  }
  return 0;
}