---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/graph/scc.0.test.cpp
    title: remote_test/yosupo/graph/scc.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "strongly connected components Tarjan / \u5F3A\u8FDE\u901A\u5206\
      \u91CF Tarjan \u7B97\u6CD5"
    links: []
  bundledCode: "#line 1 \"graph/strongly_connected_components_Tarjan.hpp\"\n\n\n\n\
    /**\n * @brief strongly connected components Tarjan / \u5F3A\u8FDE\u901A\u5206\
    \u91CF Tarjan \u7B97\u6CD5\n *\n */\n\n#include <algorithm>\n#include <functional>\n\
    #include <stack>\n#include <utility>\n#include <vector>\n\nnamespace lib {\n\n\
    class StronglyConnectedComponentsGraph {\npublic:\n  struct InputEdge {\n    int\
    \ from, to;\n    InputEdge(int from, int to) : from(from), to(to) {}\n    ~InputEdge()\
    \ = default;\n  };\n\n  StronglyConnectedComponentsGraph(int n) : n_(n) {}\n \
    \ ~StronglyConnectedComponentsGraph() = default;\n\n  void add_directed_edge(int\
    \ u, int v) { input_edge_.emplace_back(u, v); }\n\n  std::pair<int, std::vector<int>>\
    \ get_scc() const {\n    std::vector<int> idx(n_ + 1, 0), edge(input_edge_.size()),\
    \ dfn(n_, 0), low(n_, 0),\n        sccno(n_, -1);\n    std::stack<int, std::vector<int>>\
    \ s;\n    int dfs_clock = 0, scc_cnt = 0;\n    for (auto &i : input_edge_) ++idx[i.from];\n\
    \    for (int i = 0, sum = 0; i <= n_; ++i) sum += idx[i], idx[i] = sum - idx[i];\n\
    \    for (auto &i : input_edge_) edge[idx[i.from]++] = i.to;\n    for (int i =\
    \ n_ - 1; i > 0; --i) idx[i] = idx[i - 1];\n    idx[0]                       =\
    \ 0;\n    std::function<void(int)> dfs = [&](int u) {\n      dfn[u] = low[u] =\
    \ ++dfs_clock;\n      s.push(u);\n      for (int i = idx[u], ie = idx[u + 1];\
    \ i < ie; ++i) {\n        int v = edge[i];\n        if (dfn[v] == 0) {\n     \
    \     dfs(v);\n          low[u] = std::min(low[u], low[v]);\n        } else if\
    \ (sccno[v] == -1) {\n          low[u] = std::min(low[u], dfn[v]);\n        }\n\
    \      }\n      if (dfn[u] == low[u]) {\n        int v;\n        do {\n      \
    \    v = s.top();\n          s.pop();\n          sccno[v] = scc_cnt;\n       \
    \ } while (v != u);\n        ++scc_cnt;\n      }\n    };\n    for (int i = 0;\
    \ i < n_; ++i)\n      if (dfn[i] == 0) dfs(i);\n    return {scc_cnt, sccno};\n\
    \  }\n\nprivate:\n  const int n_; // \u8282\u70B9\u7F16\u53F7\u5728 [0, n-1] \u4EE5\
    \u5185\uFF01\n  std::vector<InputEdge> input_edge_;\n};\n\n} // namespace lib\n\
    \n\n"
  code: "#ifndef STRONGLY_CONNECTED_COMPONENTS_TARJAN_HEADER_HPP\n#define STRONGLY_CONNECTED_COMPONENTS_TARJAN_HEADER_HPP\n\
    \n/**\n * @brief strongly connected components Tarjan / \u5F3A\u8FDE\u901A\u5206\
    \u91CF Tarjan \u7B97\u6CD5\n *\n */\n\n#include <algorithm>\n#include <functional>\n\
    #include <stack>\n#include <utility>\n#include <vector>\n\nnamespace lib {\n\n\
    class StronglyConnectedComponentsGraph {\npublic:\n  struct InputEdge {\n    int\
    \ from, to;\n    InputEdge(int from, int to) : from(from), to(to) {}\n    ~InputEdge()\
    \ = default;\n  };\n\n  StronglyConnectedComponentsGraph(int n) : n_(n) {}\n \
    \ ~StronglyConnectedComponentsGraph() = default;\n\n  void add_directed_edge(int\
    \ u, int v) { input_edge_.emplace_back(u, v); }\n\n  std::pair<int, std::vector<int>>\
    \ get_scc() const {\n    std::vector<int> idx(n_ + 1, 0), edge(input_edge_.size()),\
    \ dfn(n_, 0), low(n_, 0),\n        sccno(n_, -1);\n    std::stack<int, std::vector<int>>\
    \ s;\n    int dfs_clock = 0, scc_cnt = 0;\n    for (auto &i : input_edge_) ++idx[i.from];\n\
    \    for (int i = 0, sum = 0; i <= n_; ++i) sum += idx[i], idx[i] = sum - idx[i];\n\
    \    for (auto &i : input_edge_) edge[idx[i.from]++] = i.to;\n    for (int i =\
    \ n_ - 1; i > 0; --i) idx[i] = idx[i - 1];\n    idx[0]                       =\
    \ 0;\n    std::function<void(int)> dfs = [&](int u) {\n      dfn[u] = low[u] =\
    \ ++dfs_clock;\n      s.push(u);\n      for (int i = idx[u], ie = idx[u + 1];\
    \ i < ie; ++i) {\n        int v = edge[i];\n        if (dfn[v] == 0) {\n     \
    \     dfs(v);\n          low[u] = std::min(low[u], low[v]);\n        } else if\
    \ (sccno[v] == -1) {\n          low[u] = std::min(low[u], dfn[v]);\n        }\n\
    \      }\n      if (dfn[u] == low[u]) {\n        int v;\n        do {\n      \
    \    v = s.top();\n          s.pop();\n          sccno[v] = scc_cnt;\n       \
    \ } while (v != u);\n        ++scc_cnt;\n      }\n    };\n    for (int i = 0;\
    \ i < n_; ++i)\n      if (dfn[i] == 0) dfs(i);\n    return {scc_cnt, sccno};\n\
    \  }\n\nprivate:\n  const int n_; // \u8282\u70B9\u7F16\u53F7\u5728 [0, n-1] \u4EE5\
    \u5185\uFF01\n  std::vector<InputEdge> input_edge_;\n};\n\n} // namespace lib\n\
    \n#endif"
  dependsOn: []
  isVerificationFile: false
  path: graph/strongly_connected_components_Tarjan.hpp
  requiredBy: []
  timestamp: '2021-07-15 14:25:20+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/graph/scc.0.test.cpp
documentation_of: graph/strongly_connected_components_Tarjan.hpp
layout: document
redirect_from:
- /library/graph/strongly_connected_components_Tarjan.hpp
- /library/graph/strongly_connected_components_Tarjan.hpp.html
title: "strongly connected components Tarjan / \u5F3A\u8FDE\u901A\u5206\u91CF Tarjan\
  \ \u7B97\u6CD5"
---
