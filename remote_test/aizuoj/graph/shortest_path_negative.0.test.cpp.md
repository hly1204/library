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
    \r\n\r\n#include <iostream>\r\n\r\n#line 1 \"graph/single_source_shortest_path_Bellman_Ford.hpp\"\
    \n\n\n\r\n/**\r\n * @brief single source shortest path Bellman-Ford / \u5355\u6E90\
    \u6700\u77ED\u8DEF Bellman-Ford \u7B97\u6CD5\r\n *\r\n */\r\n\r\n#include <limits>\r\
    \n#include <queue>\r\n#include <utility>\r\n#include <vector>\r\n\r\nnamespace\
    \ lib {\r\n\r\ntemplate <typename DistType>\r\nclass ShortestPathGraph {\r\npublic:\r\
    \n  struct InputEdge {\r\n    int from, to;\r\n    DistType dist;\r\n    InputEdge(int\
    \ from, int to, DistType dist) : from(from), to(to), dist(dist) {}\r\n    ~InputEdge()\
    \ = default;\r\n  };\r\n\r\n  struct Edge {\r\n    int to;\r\n    DistType dist;\r\
    \n  };\r\n\r\n  ShortestPathGraph(int n) : n_(n) {}\r\n  ~ShortestPathGraph()\
    \ = default;\r\n\r\n  void add_directed_edge(int from, int to, DistType dist)\
    \ {\r\n    input_edge_.emplace_back(from, to, dist);\r\n  }\r\n\r\n  /**\r\n \
    \  * @brief \u83B7\u53D6\u6700\u77ED\u8DEF\r\n   * @ref R. E. Tarjan. Data Structures\
    \ and Network Algorithms. Page 93.\r\n   * @param source \u8D77\u70B9\r\n   *\
    \ @return std::pair<std::vector<DistType>, std::vector<int>>\r\n   */\r\n  std::pair<std::vector<DistType>,\
    \ std::vector<int>>\r\n  get_sssp(int source, const DistType INF = std::numeric_limits<DistType>::max())\
    \ const {\r\n    std::vector<int> idx(n_ + 1, 0);\r\n    std::vector<Edge> edge(input_edge_.size());\r\
    \n    for (auto &i : input_edge_) ++idx[i.from];\r\n    for (int i = 0, sum =\
    \ 0; i <= n_; ++i) sum += idx[i], idx[i] = sum - idx[i];\r\n    for (auto &i :\
    \ input_edge_) edge[idx[i.from]++] = Edge{i.to, i.dist};\r\n    for (int i = n_\
    \ - 1; i > 0; --i) idx[i] = idx[i - 1];\r\n    idx[0] = 0;\r\n    std::vector<DistType>\
    \ dist(n_, INF);\r\n    std::vector<int> pred(n_, -1);\r\n    std::deque<int>\
    \ q;\r\n    std::vector<bool> inq(n_, false);\r\n    int pass = 0, last = source;\r\
    \n    dist[source] = 0;\r\n    q.push_back(source);\r\n    inq[source] = true;\r\
    \n    while (!q.empty()) {\r\n      int t = q.front();\r\n      q.pop_front();\r\
    \n      inq[t] = false;\r\n      for (int i = idx[t], ie = idx[t + 1]; i < ie;\
    \ ++i) {\r\n        int to     = edge[i].to;\r\n        DistType d = edge[i].dist;\r\
    \n        if (dist[t] + d < dist[to]) {\r\n          dist[to] = dist[t] + d;\r\
    \n          pred[to] = t;\r\n          if (!inq[to]) {\r\n            inq[to]\
    \ = true;\r\n            q.push_back(to);\r\n          }\r\n        }\r\n    \
    \  }\r\n      if (t == last) {\r\n        if (++pass == n_ && !q.empty()) return\
    \ {{}, {}}; // \u62A5\u544A\u8D1F\u5708\r\n        if (!q.empty()) last = q.back();\r\
    \n      }\r\n    }\r\n    return {dist, pred};\r\n  }\r\n\r\nprivate:\r\n  const\
    \ int n_; // \u8282\u70B9\u7F16\u53F7\u5728 [0, n-1] \u4E2D\uFF01\r\n  std::vector<InputEdge>\
    \ input_edge_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line 6 \"remote_test/aizuoj/graph/shortest_path_negative.0.test.cpp\"\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int n, m, s;\r\n  std::cin >> n >> m >> s;\r\n  lib::ShortestPathGraph<int>\
    \ g(n);\r\n  while (m--) {\r\n    int u, v, w;\r\n    std::cin >> u >> v >> w;\r\
    \n    g.add_directed_edge(u, v, w);\r\n  }\r\n  auto [dist, pred] = g.get_sssp(s);\r\
    \n  if (dist.empty()) {\r\n    std::cout << \"NEGATIVE CYCLE\\n\";\r\n  } else\
    \ {\r\n    for (int i = 0; i < n; ++i) {\r\n      if (pred[i] == -1 && i != s)\
    \ {\r\n        std::cout << \"INF\\n\";\r\n      } else {\r\n        std::cout\
    \ << dist[i] << '\\n';\r\n      }\r\n    }\r\n  }\r\n  return 0;\r\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B\"\
    \r\n\r\n#include <iostream>\r\n\r\n#include \"graph/single_source_shortest_path_Bellman_Ford.hpp\"\
    \r\n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin),\
    \ std::freopen(\"out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\
    \n  std::cin.tie(0);\r\n  int n, m, s;\r\n  std::cin >> n >> m >> s;\r\n  lib::ShortestPathGraph<int>\
    \ g(n);\r\n  while (m--) {\r\n    int u, v, w;\r\n    std::cin >> u >> v >> w;\r\
    \n    g.add_directed_edge(u, v, w);\r\n  }\r\n  auto [dist, pred] = g.get_sssp(s);\r\
    \n  if (dist.empty()) {\r\n    std::cout << \"NEGATIVE CYCLE\\n\";\r\n  } else\
    \ {\r\n    for (int i = 0; i < n; ++i) {\r\n      if (pred[i] == -1 && i != s)\
    \ {\r\n        std::cout << \"INF\\n\";\r\n      } else {\r\n        std::cout\
    \ << dist[i] << '\\n';\r\n      }\r\n    }\r\n  }\r\n  return 0;\r\n}"
  dependsOn:
  - graph/single_source_shortest_path_Bellman_Ford.hpp
  isVerificationFile: true
  path: remote_test/aizuoj/graph/shortest_path_negative.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/aizuoj/graph/shortest_path_negative.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/aizuoj/graph/shortest_path_negative.0.test.cpp
- /verify/remote_test/aizuoj/graph/shortest_path_negative.0.test.cpp.html
title: remote_test/aizuoj/graph/shortest_path_negative.0.test.cpp
---
