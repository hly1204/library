#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A"

#include <iostream>

#include "graph/maximum_flow_Dinic.hpp"

int main() {
#ifdef LOCAL
  std::freopen("in", "r", stdin), std::freopen("out", "w", stdout);
#endif
  std::ios::sync_with_stdio(false);
  std::cin.tie(0);
  int n, m;
  std::cin >> n >> m;
  lib::MaximumFlowGraph<long long> g(n);
  while (m--) {
    int u, v, c;
    std::cin >> u >> v >> c;
    g.add_directed_edge(u, v, c);
  }
  std::cout << g.get_max_flow(0, n - 1) << '\n';
  return 0;
}