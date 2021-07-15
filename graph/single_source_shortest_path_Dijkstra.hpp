#ifndef SINGLE_SOURCE_SHORTEST_PATH_DIJKSTRA_HEADER_HPP
#define SINGLE_SOURCE_SHORTEST_PATH_DIJKSTRA_HEADER_HPP

/**
 * @brief single source shortest path Dijkstra / 单源最短路 Dijkstra 算法
 *
 */

#include <limits>
#include <utility>
#include <vector>

#include "../datastructure/heap/priority_queue.hpp"

namespace lib {

template <typename DistType>
class NonnegativeShortestPathGraph {
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

  NonnegativeShortestPathGraph(int n) : n_(n) {}
  ~NonnegativeShortestPathGraph() = default;

  void add_directed_edge(int from, int to, DistType dist) {
    input_edge_.emplace_back(from, to, dist);
  }

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
    auto cmp = [&dist](int x, int y) -> bool { return dist[x] < dist[y]; };
    lib::PriorityQueue<int, decltype(cmp)> pq(cmp);
    std::vector<typename PriorityQueue<int, decltype(cmp)>::const_node_ptr_type> box(n_);
    dist[source] = 0;
    pq.insert(source);
    while (!pq.is_empty()) {
      auto x = pq.find_min();
      pq.delete_min();
      auto dx = dist[x];
      for (int i = idx[x], ie = idx[x + 1]; i < ie; ++i) {
        int j      = edge[i].to;
        DistType d = edge[i].dist;
        if (dist[j] > dx + d) {
          if (dist[j] == INF) {
            dist[j] = dx + d;
            box[j]  = pq.insert(j);
          } else {
            dist[j] = dx + d;
            pq.decrease_key(box[j], j);
          }
          pred[j] = x;
        }
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