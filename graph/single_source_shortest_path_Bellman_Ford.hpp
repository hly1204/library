#ifndef SINGLE_SOURCE_SHORTEST_PATH_BELLMAN_FORD_HEADER_HPP
#define SINGLE_SOURCE_SHORTEST_PATH_BELLMAN_FORD_HEADER_HPP

/**
 * @brief single source shortest path Bellman-Ford / 单源最短路 Bellman-Ford 算法
 *
 */

#include <limits>
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

  /**
   * @brief 获取最短路
   * @ref R. E. Tarjan. Data Structures and Network Algorithms. Page 93.
   * @param source 起点
   * @return std::pair<std::vector<DistType>, std::vector<int>>
   */
  std::pair<std::vector<DistType>, std::vector<int>>
  get_sssp(int source, const DistType INF = std::numeric_limits<DistType>::max()) const {
    std::vector<int> idx(n_ + 1, 0);
    std::vector<Edge> edge(input_edge_.size());
    for (auto &i : input_edge_) ++idx[i.from];
    for (int i = 0, sum = 0; i <= n_; ++i) sum += idx[i], idx[i] = sum - idx[i];
    for (auto &i : input_edge_) edge[idx[i.from]++] = Edge{i.to, i.dist};
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