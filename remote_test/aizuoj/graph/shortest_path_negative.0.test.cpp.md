---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/single_source_shortest_path_Bellman_Ford.hpp
    title: "single source shortest path Bellman-Ford / \u5355\u6E90\u6700\u77ED\u8DEF\
      \ Bellman-Ford \u7B97\u6CD5"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B
  bundledCode: "#line 1 \"remote_test/aizuoj/graph/shortest_path_negative.0.test.cpp\"\
    \n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B\"\
    \n\n#include <iostream>\n\n#line 1 \"graph/single_source_shortest_path_Bellman_Ford.hpp\"\
    \n\n\n\n/**\n * @brief single source shortest path Bellman-Ford / \u5355\u6E90\
    \u6700\u77ED\u8DEF Bellman-Ford \u7B97\u6CD5\n *\n */\n\n#include <limits>\n#include\
    \ <queue>\n#include <vector>\n\nnamespace lib {\n\ntemplate <typename DistType>\
    \ class ShortestPathGraph {\npublic:\n  struct InputEdge {\n    int from, to;\n\
    \    DistType dist;\n    InputEdge(int from, int to, DistType dist) : from(from),\
    \ to(to), dist(dist) {}\n    ~InputEdge() = default;\n  };\n\n  struct Edge {\n\
    \    int to;\n    DistType dist;\n  };\n\n  ShortestPathGraph(int n) : n_(n) {}\n\
    \  ~ShortestPathGraph() = default;\n\n  void add_directed_edge(int from, int to,\
    \ DistType dist) {\n    input_edge_.emplace_back(from, to, dist);\n  }\n\n  /**\n\
    \   * @brief \u83B7\u53D6\u6700\u77ED\u8DEF\n   * @ref Data Structures and Network\
    \ Algorithms P93\n   *\n   * @param source\n   * @return std::pair<std::vector<DistType>,\
    \ std::vector<int>>\n   */\n  std::pair<std::vector<DistType>, std::vector<int>>\
    \ get_sssp(int source) const {\n    std::vector<int> idx(n_ + 1, 0);\n    std::vector<Edge>\
    \ edge(input_edge_.size());\n    for (auto &i : input_edge_) ++idx[i.from];\n\
    \    for (int i = 0, sum = 0; i <= n_; ++i) sum += idx[i], idx[i] = sum - idx[i];\n\
    \    for (auto &i : input_edge_) edge[idx[i.from]++] = Edge{i.to, i.dist};\n \
    \   for (int i = n_ - 1; i > 0; --i) idx[i] = idx[i - 1];\n    idx[0] = 0;\n \
    \   const DistType INF = std::numeric_limits<DistType>::max();\n    std::vector<DistType>\
    \ dist(n_, INF);\n    std::vector<int> pred(n_, -1);\n    std::deque<int> q;\n\
    \    std::vector<bool> inq(n_, false);\n    int pass = 0, last = source;\n   \
    \ dist[source] = 0;\n    q.push_back(source);\n    inq[source] = true;\n    while\
    \ (!q.empty()) {\n      int t = q.front();\n      q.pop_front();\n      inq[t]\
    \ = false;\n      for (int i = idx[t], ie = idx[t + 1]; i < ie; ++i) {\n     \
    \   int to = edge[i].to;\n        DistType d = edge[i].dist;\n        if (dist[t]\
    \ + d < dist[to]) {\n          dist[to] = dist[t] + d;\n          pred[to] = t;\n\
    \          if (!inq[to]) {\n            inq[to] = true;\n            q.push_back(to);\n\
    \          }\n        }\n      }\n      if (t == last) {\n        if (++pass ==\
    \ n_ && !q.empty()) return {{}, {}}; // \u62A5\u544A\u8D1F\u5708\n        if (!q.empty())\
    \ last = q.back();\n      }\n    }\n    return {dist, pred};\n  }\n\nprivate:\n\
    \  const int n_; // \u8282\u70B9\u7F16\u53F7\u5728 [0, n-1] \u4E2D\uFF01\n  std::vector<InputEdge>\
    \ input_edge_;\n};\n\n} // namespace lib\n\n\n#line 6 \"remote_test/aizuoj/graph/shortest_path_negative.0.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, m, s;\n  std::cin >> n >> m >> s;\n  lib::ShortestPathGraph<int> g(n);\n\
    \  while (m--) {\n    int u, v, w;\n    std::cin >> u >> v >> w;\n    g.add_directed_edge(u,\
    \ v, w);\n  }\n  auto [dist, pred] = g.get_sssp(s);\n  if (dist.empty()) {\n \
    \   std::cout << \"NEGATIVE CYCLE\\n\";\n  } else {\n    for (int i = 0; i < n;\
    \ ++i) {\n      if (pred[i] == -1 && i != s) {\n        std::cout << \"INF\\n\"\
    ;\n      } else {\n        std::cout << dist[i] << '\\n';\n      }\n    }\n  }\n\
    \  return 0;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B\"\
    \n\n#include <iostream>\n\n#include \"graph/single_source_shortest_path_Bellman_Ford.hpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, m, s;\n  std::cin >> n >> m >> s;\n  lib::ShortestPathGraph<int> g(n);\n\
    \  while (m--) {\n    int u, v, w;\n    std::cin >> u >> v >> w;\n    g.add_directed_edge(u,\
    \ v, w);\n  }\n  auto [dist, pred] = g.get_sssp(s);\n  if (dist.empty()) {\n \
    \   std::cout << \"NEGATIVE CYCLE\\n\";\n  } else {\n    for (int i = 0; i < n;\
    \ ++i) {\n      if (pred[i] == -1 && i != s) {\n        std::cout << \"INF\\n\"\
    ;\n      } else {\n        std::cout << dist[i] << '\\n';\n      }\n    }\n  }\n\
    \  return 0;\n}"
  dependsOn:
  - graph/single_source_shortest_path_Bellman_Ford.hpp
  isVerificationFile: true
  path: remote_test/aizuoj/graph/shortest_path_negative.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-15 12:32:01+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/aizuoj/graph/shortest_path_negative.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/aizuoj/graph/shortest_path_negative.0.test.cpp
- /verify/remote_test/aizuoj/graph/shortest_path_negative.0.test.cpp.html
title: remote_test/aizuoj/graph/shortest_path_negative.0.test.cpp
---
