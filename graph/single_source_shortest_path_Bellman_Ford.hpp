#ifndef SINGLE_SOURCE_SHORTEST_PATH_BELLMAN_FORD_HEADER_HPP
#define SINGLE_SOURCE_SHORTEST_PATH_BELLMAN_FORD_HEADER_HPP

#include <algorithm>
#include <limits>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

namespace lib {

template <typename DistType>
class ShortestPathGraph {
public:
  struct InputEdge {
    int from, to;
    DistType dist;
    InputEdge(int from, int to, DistType dist) : from(from), to(to), dist(dist) {}
    ~InputEdge() = default;
  };

  struct Edge {
    int to;
    DistType dist;
  };

  ShortestPathGraph(int n) : n_(n) {}
  ~ShortestPathGraph() = default;

  void add_directed_edge(int from, int to, DistType dist) {
    input_edge_.emplace_back(from, to, dist);
  }

  // 参考文献：R. E. Tarjan. Data Structures and Network Algorithms. Page 93.
  std::pair<std::vector<DistType>, std::vector<int>>
  get_sssp(int source, const DistType INF = std::numeric_limits<DistType>::max()) const {
    std::vector<int> idx(n_ + 1, 0);
    std::vector<Edge> edge(input_edge_.size());
    std::for_each(input_edge_.begin(), input_edge_.end(),
                  [&idx](const InputEdge &i) { ++idx[i.from]; });
    std::exclusive_scan(idx.begin(), idx.end(), idx.begin(), 0);
    std::for_each(input_edge_.begin(), input_edge_.end(), [&idx, &edge](const InputEdge &i) {
      edge[idx[i.from]++] = Edge{i.to, i.dist};
    });
    for (int i = n_ - 1; i > 0; --i) idx[i] = idx[i - 1];
    idx[0] = 0;
    std::vector<DistType> dist(n_, INF);
    std::vector<int> pred(n_, -1);
    std::deque<int> q;
    std::vector<bool> inq(n_, false);
    int pass = 0, last = source;
    dist[source] = 0;
    q.push_back(source);
    inq[source] = true;
    while (!q.empty()) {
      int t = q.front();
      q.pop_front();
      inq[t] = false;
      for (int i = idx[t], ie = idx[t + 1]; i < ie; ++i) {
        int to     = edge[i].to;
        DistType d = edge[i].dist;
        if (dist[t] + d < dist[to]) {
          dist[to] = dist[t] + d;
          pred[to] = t;
          if (!inq[to]) {
            inq[to] = true;
            q.push_back(to);
          }
        }
      }
      if (t == last) {
        if (++pass == n_ && !q.empty()) return {{}, {}}; // 报告负圈
        if (!q.empty()) last = q.back();
      }
    }
    return {dist, pred};
  }

private:
  const int n_; // 节点编号在 [0, n-1] 中！
  std::vector<InputEdge> input_edge_;
};

} // namespace lib

#endif