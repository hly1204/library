#ifndef STRONGLY_CONNECTED_COMPONENTS_TARJAN_HEADER_HPP
#define STRONGLY_CONNECTED_COMPONENTS_TARJAN_HEADER_HPP

/**
 * @brief strongly connected components Tarjan / 强连通分量 Tarjan 算法
 *
 */

#include <algorithm>
#include <functional>
#include <stack>
#include <utility>
#include <vector>

namespace lib {

class StronglyConnectedComponentsGraph {
public:
  struct InputEdge {
    int from, to;
    InputEdge(int from, int to) : from(from), to(to) {}
    ~InputEdge() = default;
  };

  StronglyConnectedComponentsGraph(int n) : n_(n) {}
  ~StronglyConnectedComponentsGraph() = default;

  void add_directed_edge(int u, int v) { input_edge_.emplace_back(u, v); }

  std::pair<int, std::vector<int>> get_scc() const {
    std::vector<int> idx(n_ + 1, 0), edge(input_edge_.size()), dfn(n_, 0), low(n_, 0),
        sccno(n_, -1);
    std::stack<int, std::vector<int>> s;
    int dfs_clock = 0, scc_cnt = 0;
    for (auto &i : input_edge_) ++idx[i.from];
    for (int i = 0, sum = 0; i <= n_; ++i) sum += idx[i], idx[i] = sum - idx[i];
    for (auto &i : input_edge_) edge[idx[i.from]++] = i.to;
    for (int i = n_ - 1; i > 0; --i) idx[i] = idx[i - 1];
    idx[0]                       = 0;
    std::function<void(int)> dfs = [&](int u) {
      dfn[u] = low[u] = ++dfs_clock;
      s.push(u);
      for (int i = idx[u], ie = idx[u + 1]; i < ie; ++i) {
        int v = edge[i];
        if (dfn[v] == 0) {
          dfs(v);
          low[u] = std::min(low[u], low[v]);
        } else if (sccno[v] == -1) {
          low[u] = std::min(low[u], dfn[v]);
        }
      }
      if (dfn[u] == low[u]) {
        int v;
        do {
          v = s.top();
          s.pop();
          sccno[v] = scc_cnt;
        } while (v != u);
        ++scc_cnt;
      }
    };
    for (int i = 0; i < n_; ++i)
      if (dfn[i] == 0) dfs(i);
    return {scc_cnt, sccno};
  }

private:
  const int n_; // 节点编号在 [0, n-1] 以内！
  std::vector<InputEdge> input_edge_;
};

} // namespace lib

#endif