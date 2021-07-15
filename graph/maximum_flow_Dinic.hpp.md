---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/aizuoj/graph/max_flow.0.test.cpp
    title: remote_test/aizuoj/graph/max_flow.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "maximum flow Dinic / \u6700\u5927\u6D41 Dinic \u7B97\u6CD5"
    links: []
  bundledCode: "#line 1 \"graph/maximum_flow_Dinic.hpp\"\n\n\n\n/**\n * @brief maximum\
    \ flow Dinic / \u6700\u5927\u6D41 Dinic \u7B97\u6CD5\n *\n */\n\n#include <limits>\n\
    #include <queue>\n#include <vector>\n\nnamespace lib {\n\ntemplate <typename CapacityType>\n\
    class MaximumFlowGraph {\npublic:\n  struct InputEdge {\n    int from, to;\n \
    \   CapacityType cap;\n    InputEdge(int from, int to, CapacityType cap) : from(from),\
    \ to(to), cap(cap) {}\n    ~InputEdge() = default;\n  };\n\n  struct Edge {\n\
    \    int to;\n    CapacityType cap;\n  };\n\n  MaximumFlowGraph(int n) : n_(n)\
    \ {}\n  ~MaximumFlowGraph() = default;\n\n  void add_directed_edge(int from, int\
    \ to, CapacityType cap) {\n    input_edge_.emplace_back(from, to, cap);\n  }\n\
    \n  CapacityType\n  get_max_flow(int s, int t,\n               const CapacityType\
    \ CAPACITY_LIM = std::numeric_limits<CapacityType>::max()) {\n    convert_to_forwardstar();\n\
    \    CapacityType max_flow = 0;\n    while (create_layer_graph(s, t)) {\n    \
    \  cur_edge_ = idx_;\n      max_flow += augment(s, CAPACITY_LIM, t);\n    }\n\
    \    return max_flow;\n  }\n\nprivate:\n  void convert_to_forwardstar() {\n  \
    \  int m = input_edge_.size() << 1;\n    edge_.resize(m);\n    idx_.assign(n_\
    \ + 1, 0);\n    rev_idx_.resize(m);\n    for (auto &i : input_edge_) ++idx_[i.from],\
    \ ++idx_[i.to];\n    for (int i = 0, sum = 0; i != n_ + 1; ++i) sum += idx_[i],\
    \ idx_[i] = sum - idx_[i];\n    for (auto &i : input_edge_) {\n      edge_[idx_[i.from]].to\
    \  = i.to;\n      edge_[idx_[i.from]].cap = i.cap;\n      edge_[idx_[i.to]].to\
    \    = i.from;\n      edge_[idx_[i.to]].cap   = 0;\n      rev_idx_[idx_[i.from]]\
    \  = idx_[i.to];\n      rev_idx_[idx_[i.to]]    = idx_[i.from];\n      ++idx_[i.from];\n\
    \      ++idx_[i.to];\n    }\n    for (int i = n_ - 1; i > 0; --i) idx_[i] = idx_[i\
    \ - 1];\n    idx_[0] = 0;\n  }\n\n  bool create_layer_graph(int s, int t) {\n\
    \    level_.assign(n_, -1);\n    std::queue<int> q;\n    q.push(s);\n    level_[s]\
    \ = 0;\n    while (!q.empty()) {\n      int u = q.front();\n      q.pop();\n \
    \     for (int i = idx_[u], ie = idx_[u + 1]; i < ie; ++i)\n        if (edge_[i].cap\
    \ > 0 && level_[edge_[i].to] == -1) {\n          level_[edge_[i].to] = level_[u]\
    \ + 1;\n          q.push(edge_[i].to);\n        }\n    }\n    return level_[t]\
    \ != -1;\n  }\n\n  CapacityType augment(int from, CapacityType bottleneck, int\
    \ t) {\n    if (bottleneck == 0 || from == t) return bottleneck;\n    CapacityType\
    \ max_flow = 0;\n    for (int &i = cur_edge_[from], ie = idx_[from + 1]; i < ie;\
    \ ++i) {\n      if (level_[edge_[i].to] == level_[from] + 1 && edge_[i].cap >\
    \ 0) {\n        CapacityType flow = augment(edge_[i].to, std::min(bottleneck,\
    \ edge_[i].cap), t);\n        if (flow == 0) continue;\n        edge_[i].cap -=\
    \ flow;\n        edge_[rev_idx_[i]].cap += flow;\n        max_flow += flow;\n\
    \        bottleneck -= flow;\n        if (bottleneck == 0) break;\n      }\n \
    \   }\n    return max_flow;\n  }\n\n  const int n_; // n \u4E2A vertex \u4E14\u7F16\
    \u53F7\u5728 [0,n-1] \u8303\u56F4\u5185\n  std::vector<InputEdge> input_edge_;\n\
    \  std::vector<Edge> edge_;\n  std::vector<int> idx_, rev_idx_, cur_edge_, level_;\n\
    };\n\n} // namespace lib\n\n\n"
  code: "#ifndef MAXIMUM_FLOW_DINIC_HEADER_HPP\n#define MAXIMUM_FLOW_DINIC_HEADER_HPP\n\
    \n/**\n * @brief maximum flow Dinic / \u6700\u5927\u6D41 Dinic \u7B97\u6CD5\n\
    \ *\n */\n\n#include <limits>\n#include <queue>\n#include <vector>\n\nnamespace\
    \ lib {\n\ntemplate <typename CapacityType>\nclass MaximumFlowGraph {\npublic:\n\
    \  struct InputEdge {\n    int from, to;\n    CapacityType cap;\n    InputEdge(int\
    \ from, int to, CapacityType cap) : from(from), to(to), cap(cap) {}\n    ~InputEdge()\
    \ = default;\n  };\n\n  struct Edge {\n    int to;\n    CapacityType cap;\n  };\n\
    \n  MaximumFlowGraph(int n) : n_(n) {}\n  ~MaximumFlowGraph() = default;\n\n \
    \ void add_directed_edge(int from, int to, CapacityType cap) {\n    input_edge_.emplace_back(from,\
    \ to, cap);\n  }\n\n  CapacityType\n  get_max_flow(int s, int t,\n           \
    \    const CapacityType CAPACITY_LIM = std::numeric_limits<CapacityType>::max())\
    \ {\n    convert_to_forwardstar();\n    CapacityType max_flow = 0;\n    while\
    \ (create_layer_graph(s, t)) {\n      cur_edge_ = idx_;\n      max_flow += augment(s,\
    \ CAPACITY_LIM, t);\n    }\n    return max_flow;\n  }\n\nprivate:\n  void convert_to_forwardstar()\
    \ {\n    int m = input_edge_.size() << 1;\n    edge_.resize(m);\n    idx_.assign(n_\
    \ + 1, 0);\n    rev_idx_.resize(m);\n    for (auto &i : input_edge_) ++idx_[i.from],\
    \ ++idx_[i.to];\n    for (int i = 0, sum = 0; i != n_ + 1; ++i) sum += idx_[i],\
    \ idx_[i] = sum - idx_[i];\n    for (auto &i : input_edge_) {\n      edge_[idx_[i.from]].to\
    \  = i.to;\n      edge_[idx_[i.from]].cap = i.cap;\n      edge_[idx_[i.to]].to\
    \    = i.from;\n      edge_[idx_[i.to]].cap   = 0;\n      rev_idx_[idx_[i.from]]\
    \  = idx_[i.to];\n      rev_idx_[idx_[i.to]]    = idx_[i.from];\n      ++idx_[i.from];\n\
    \      ++idx_[i.to];\n    }\n    for (int i = n_ - 1; i > 0; --i) idx_[i] = idx_[i\
    \ - 1];\n    idx_[0] = 0;\n  }\n\n  bool create_layer_graph(int s, int t) {\n\
    \    level_.assign(n_, -1);\n    std::queue<int> q;\n    q.push(s);\n    level_[s]\
    \ = 0;\n    while (!q.empty()) {\n      int u = q.front();\n      q.pop();\n \
    \     for (int i = idx_[u], ie = idx_[u + 1]; i < ie; ++i)\n        if (edge_[i].cap\
    \ > 0 && level_[edge_[i].to] == -1) {\n          level_[edge_[i].to] = level_[u]\
    \ + 1;\n          q.push(edge_[i].to);\n        }\n    }\n    return level_[t]\
    \ != -1;\n  }\n\n  CapacityType augment(int from, CapacityType bottleneck, int\
    \ t) {\n    if (bottleneck == 0 || from == t) return bottleneck;\n    CapacityType\
    \ max_flow = 0;\n    for (int &i = cur_edge_[from], ie = idx_[from + 1]; i < ie;\
    \ ++i) {\n      if (level_[edge_[i].to] == level_[from] + 1 && edge_[i].cap >\
    \ 0) {\n        CapacityType flow = augment(edge_[i].to, std::min(bottleneck,\
    \ edge_[i].cap), t);\n        if (flow == 0) continue;\n        edge_[i].cap -=\
    \ flow;\n        edge_[rev_idx_[i]].cap += flow;\n        max_flow += flow;\n\
    \        bottleneck -= flow;\n        if (bottleneck == 0) break;\n      }\n \
    \   }\n    return max_flow;\n  }\n\n  const int n_; // n \u4E2A vertex \u4E14\u7F16\
    \u53F7\u5728 [0,n-1] \u8303\u56F4\u5185\n  std::vector<InputEdge> input_edge_;\n\
    \  std::vector<Edge> edge_;\n  std::vector<int> idx_, rev_idx_, cur_edge_, level_;\n\
    };\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: graph/maximum_flow_Dinic.hpp
  requiredBy: []
  timestamp: '2021-07-15 14:25:20+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/aizuoj/graph/max_flow.0.test.cpp
documentation_of: graph/maximum_flow_Dinic.hpp
layout: document
redirect_from:
- /library/graph/maximum_flow_Dinic.hpp
- /library/graph/maximum_flow_Dinic.hpp.html
title: "maximum flow Dinic / \u6700\u5927\u6D41 Dinic \u7B97\u6CD5"
---
