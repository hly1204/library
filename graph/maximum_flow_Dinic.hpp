#ifndef MAXIMUM_FLOW_DINIC_HEADER_HPP
#define MAXIMUM_FLOW_DINIC_HEADER_HPP

/**
 * @brief maximum flow Dinic / 最大流 Dinic 算法
 *
 */

#include <limits>
#include <queue>
#include <vector>

namespace lib {

template <typename CapacityType>
class MaximumFlowGraph {
public:
  struct InputEdge {
    int from, to;
    CapacityType cap;
    InputEdge(int from, int to, CapacityType cap) : from(from), to(to), cap(cap) {}
    ~InputEdge() = default;
  };

  struct Edge {
    int to;
    CapacityType cap;
  };

  MaximumFlowGraph(int n) : n_(n) {}
  ~MaximumFlowGraph() = default;

  void add_directed_edge(int from, int to, CapacityType cap) {
    input_edge_.emplace_back(from, to, cap);
  }

  CapacityType
  get_max_flow(int s, int t,
               const CapacityType CAPACITY_LIM = std::numeric_limits<CapacityType>::max()) {
    convert_to_forwardstar();
    CapacityType max_flow = 0;
    while (create_layer_graph(s, t)) {
      cur_edge_ = idx_;
      max_flow += augment(s, CAPACITY_LIM, t);
    }
    return max_flow;
  }

private:
  void convert_to_forwardstar() {
    int m = input_edge_.size() << 1;
    edge_.resize(m);
    idx_.assign(n_ + 1, 0);
    rev_idx_.resize(m);
    for (auto &i : input_edge_) ++idx_[i.from], ++idx_[i.to];
    for (int i = 0, sum = 0; i != n_ + 1; ++i) sum += idx_[i], idx_[i] = sum - idx_[i];
    for (auto &i : input_edge_) {
      edge_[idx_[i.from]].to  = i.to;
      edge_[idx_[i.from]].cap = i.cap;
      edge_[idx_[i.to]].to    = i.from;
      edge_[idx_[i.to]].cap   = 0;
      rev_idx_[idx_[i.from]]  = idx_[i.to];
      rev_idx_[idx_[i.to]]    = idx_[i.from];
      ++idx_[i.from];
      ++idx_[i.to];
    }
    for (int i = n_ - 1; i > 0; --i) idx_[i] = idx_[i - 1];
    idx_[0] = 0;
  }

  bool create_layer_graph(int s, int t) {
    level_.assign(n_, -1);
    std::queue<int> q;
    q.push(s);
    level_[s] = 0;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = idx_[u], ie = idx_[u + 1]; i < ie; ++i)
        if (edge_[i].cap > 0 && level_[edge_[i].to] == -1) {
          level_[edge_[i].to] = level_[u] + 1;
          q.push(edge_[i].to);
        }
    }
    return level_[t] != -1;
  }

  CapacityType augment(int from, CapacityType bottleneck, int t) {
    if (bottleneck == 0 || from == t) return bottleneck;
    CapacityType max_flow = 0;
    for (int &i = cur_edge_[from], ie = idx_[from + 1]; i < ie; ++i) {
      if (level_[edge_[i].to] == level_[from] + 1 && edge_[i].cap > 0) {
        CapacityType flow = augment(edge_[i].to, std::min(bottleneck, edge_[i].cap), t);
        if (flow == 0) continue;
        edge_[i].cap -= flow;
        edge_[rev_idx_[i]].cap += flow;
        max_flow += flow;
        bottleneck -= flow;
        if (bottleneck == 0) break;
      }
    }
    return max_flow;
  }

  const int n_; // n 个 vertex 且编号在 [0,n-1] 范围内
  std::vector<InputEdge> input_edge_;
  std::vector<Edge> edge_;
  std::vector<int> idx_, rev_idx_, cur_edge_, level_;
};

} // namespace lib

#endif