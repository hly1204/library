---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/maximum_flow_Dinic.hpp
    title: "maximum flow Dinic / \u6700\u5927\u6D41 Dinic \u7B97\u6CD5"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A
  bundledCode: "#line 1 \"remote_test/aizuoj/graph/max_flow.0.test.cpp\"\n#define\
    \ PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A\"\
    \r\n\r\n#include <iostream>\r\n\r\n#line 1 \"graph/maximum_flow_Dinic.hpp\"\n\n\
    \n\r\n/**\r\n * @brief maximum flow Dinic / \u6700\u5927\u6D41 Dinic \u7B97\u6CD5\
    \r\n *\r\n */\r\n\r\n#include <limits>\r\n#include <queue>\r\n#include <vector>\r\
    \n\r\nnamespace lib {\r\n\r\ntemplate <typename CapacityType>\r\nclass MaximumFlowGraph\
    \ {\r\npublic:\r\n  struct InputEdge {\r\n    int from, to;\r\n    CapacityType\
    \ cap;\r\n    InputEdge(int from, int to, CapacityType cap) : from(from), to(to),\
    \ cap(cap) {}\r\n    ~InputEdge() = default;\r\n  };\r\n\r\n  struct Edge {\r\n\
    \    int to;\r\n    CapacityType cap;\r\n  };\r\n\r\n  MaximumFlowGraph(int n)\
    \ : n_(n) {}\r\n  ~MaximumFlowGraph() = default;\r\n\r\n  void add_directed_edge(int\
    \ from, int to, CapacityType cap) {\r\n    input_edge_.emplace_back(from, to,\
    \ cap);\r\n  }\r\n\r\n  CapacityType\r\n  get_max_flow(int s, int t,\r\n     \
    \          const CapacityType CAPACITY_LIM = std::numeric_limits<CapacityType>::max())\
    \ {\r\n    convert_to_forwardstar();\r\n    CapacityType max_flow = 0;\r\n   \
    \ while (create_layer_graph(s, t)) {\r\n      cur_edge_ = idx_;\r\n      max_flow\
    \ += augment(s, CAPACITY_LIM, t);\r\n    }\r\n    return max_flow;\r\n  }\r\n\r\
    \nprivate:\r\n  void convert_to_forwardstar() {\r\n    int m = input_edge_.size()\
    \ << 1;\r\n    edge_.resize(m);\r\n    idx_.assign(n_ + 1, 0);\r\n    rev_idx_.resize(m);\r\
    \n    for (auto &i : input_edge_) ++idx_[i.from], ++idx_[i.to];\r\n    for (int\
    \ i = 0, sum = 0; i != n_ + 1; ++i) sum += idx_[i], idx_[i] = sum - idx_[i];\r\
    \n    for (auto &i : input_edge_) {\r\n      edge_[idx_[i.from]].to  = i.to;\r\
    \n      edge_[idx_[i.from]].cap = i.cap;\r\n      edge_[idx_[i.to]].to    = i.from;\r\
    \n      edge_[idx_[i.to]].cap   = 0;\r\n      rev_idx_[idx_[i.from]]  = idx_[i.to];\r\
    \n      rev_idx_[idx_[i.to]]    = idx_[i.from];\r\n      ++idx_[i.from];\r\n \
    \     ++idx_[i.to];\r\n    }\r\n    for (int i = n_ - 1; i > 0; --i) idx_[i] =\
    \ idx_[i - 1];\r\n    idx_[0] = 0;\r\n  }\r\n\r\n  bool create_layer_graph(int\
    \ s, int t) {\r\n    level_.assign(n_, -1);\r\n    std::queue<int> q;\r\n    q.push(s);\r\
    \n    level_[s] = 0;\r\n    while (!q.empty()) {\r\n      int u = q.front();\r\
    \n      q.pop();\r\n      for (int i = idx_[u], ie = idx_[u + 1]; i < ie; ++i)\r\
    \n        if (edge_[i].cap > 0 && level_[edge_[i].to] == -1) {\r\n          level_[edge_[i].to]\
    \ = level_[u] + 1;\r\n          q.push(edge_[i].to);\r\n        }\r\n    }\r\n\
    \    return level_[t] != -1;\r\n  }\r\n\r\n  CapacityType augment(int from, CapacityType\
    \ bottleneck, int t) {\r\n    if (bottleneck == 0 || from == t) return bottleneck;\r\
    \n    CapacityType max_flow = 0;\r\n    for (int &i = cur_edge_[from], ie = idx_[from\
    \ + 1]; i < ie; ++i) {\r\n      if (level_[edge_[i].to] == level_[from] + 1 &&\
    \ edge_[i].cap > 0) {\r\n        CapacityType flow = augment(edge_[i].to, std::min(bottleneck,\
    \ edge_[i].cap), t);\r\n        if (flow == 0) continue;\r\n        edge_[i].cap\
    \ -= flow;\r\n        edge_[rev_idx_[i]].cap += flow;\r\n        max_flow += flow;\r\
    \n        bottleneck -= flow;\r\n        if (bottleneck == 0) break;\r\n     \
    \ }\r\n    }\r\n    return max_flow;\r\n  }\r\n\r\n  const int n_; // n \u4E2A\
    \ vertex \u4E14\u7F16\u53F7\u5728 [0,n-1] \u8303\u56F4\u5185\r\n  std::vector<InputEdge>\
    \ input_edge_;\r\n  std::vector<Edge> edge_;\r\n  std::vector<int> idx_, rev_idx_,\
    \ cur_edge_, level_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line 6 \"remote_test/aizuoj/graph/max_flow.0.test.cpp\"\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int n, m;\r\n  std::cin >> n >> m;\r\n  lib::MaximumFlowGraph<long long> g(n);\r\
    \n  while (m--) {\r\n    int u, v, c;\r\n    std::cin >> u >> v >> c;\r\n    g.add_directed_edge(u,\
    \ v, c);\r\n  }\r\n  std::cout << g.get_max_flow(0, n - 1) << '\\n';\r\n  return\
    \ 0;\r\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/all/GRL_6_A\"\
    \r\n\r\n#include <iostream>\r\n\r\n#include \"graph/maximum_flow_Dinic.hpp\"\r\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int n, m;\r\n  std::cin >> n >> m;\r\n  lib::MaximumFlowGraph<long long> g(n);\r\
    \n  while (m--) {\r\n    int u, v, c;\r\n    std::cin >> u >> v >> c;\r\n    g.add_directed_edge(u,\
    \ v, c);\r\n  }\r\n  std::cout << g.get_max_flow(0, n - 1) << '\\n';\r\n  return\
    \ 0;\r\n}"
  dependsOn:
  - graph/maximum_flow_Dinic.hpp
  isVerificationFile: true
  path: remote_test/aizuoj/graph/max_flow.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/aizuoj/graph/max_flow.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/aizuoj/graph/max_flow.0.test.cpp
- /verify/remote_test/aizuoj/graph/max_flow.0.test.cpp.html
title: remote_test/aizuoj/graph/max_flow.0.test.cpp
---
