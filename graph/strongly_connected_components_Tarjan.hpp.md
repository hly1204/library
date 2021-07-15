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
  bundledCode: "#line 1 \"graph/strongly_connected_components_Tarjan.hpp\"\n\n\n\r\
    \n/**\r\n * @brief strongly connected components Tarjan / \u5F3A\u8FDE\u901A\u5206\
    \u91CF Tarjan \u7B97\u6CD5\r\n *\r\n */\r\n\r\n#include <algorithm>\r\n#include\
    \ <functional>\r\n#include <stack>\r\n#include <utility>\r\n#include <vector>\r\
    \n\r\nnamespace lib {\r\n\r\nclass StronglyConnectedComponentsGraph {\r\npublic:\r\
    \n  struct InputEdge {\r\n    int from, to;\r\n    InputEdge(int from, int to)\
    \ : from(from), to(to) {}\r\n    ~InputEdge() = default;\r\n  };\r\n\r\n  StronglyConnectedComponentsGraph(int\
    \ n) : n_(n) {}\r\n  ~StronglyConnectedComponentsGraph() = default;\r\n\r\n  void\
    \ add_directed_edge(int u, int v) { input_edge_.emplace_back(u, v); }\r\n\r\n\
    \  std::pair<int, std::vector<int>> get_scc() const {\r\n    std::vector<int>\
    \ idx(n_ + 1, 0), edge(input_edge_.size()), dfn(n_, 0), low(n_, 0),\r\n      \
    \  sccno(n_, -1);\r\n    std::stack<int, std::vector<int>> s;\r\n    int dfs_clock\
    \ = 0, scc_cnt = 0;\r\n    for (auto &i : input_edge_) ++idx[i.from];\r\n    for\
    \ (int i = 0, sum = 0; i <= n_; ++i) sum += idx[i], idx[i] = sum - idx[i];\r\n\
    \    for (auto &i : input_edge_) edge[idx[i.from]++] = i.to;\r\n    for (int i\
    \ = n_ - 1; i > 0; --i) idx[i] = idx[i - 1];\r\n    idx[0]                   \
    \    = 0;\r\n    std::function<void(int)> dfs = [&](int u) {\r\n      dfn[u] =\
    \ low[u] = ++dfs_clock;\r\n      s.push(u);\r\n      for (int i = idx[u], ie =\
    \ idx[u + 1]; i < ie; ++i) {\r\n        int v = edge[i];\r\n        if (dfn[v]\
    \ == 0) {\r\n          dfs(v);\r\n          low[u] = std::min(low[u], low[v]);\r\
    \n        } else if (sccno[v] == -1) {\r\n          low[u] = std::min(low[u],\
    \ dfn[v]);\r\n        }\r\n      }\r\n      if (dfn[u] == low[u]) {\r\n      \
    \  int v;\r\n        do {\r\n          v = s.top();\r\n          s.pop();\r\n\
    \          sccno[v] = scc_cnt;\r\n        } while (v != u);\r\n        ++scc_cnt;\r\
    \n      }\r\n    };\r\n    for (int i = 0; i < n_; ++i)\r\n      if (dfn[i] ==\
    \ 0) dfs(i);\r\n    return {scc_cnt, sccno};\r\n  }\r\n\r\nprivate:\r\n  const\
    \ int n_; // \u8282\u70B9\u7F16\u53F7\u5728 [0, n-1] \u4EE5\u5185\uFF01\r\n  std::vector<InputEdge>\
    \ input_edge_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef STRONGLY_CONNECTED_COMPONENTS_TARJAN_HEADER_HPP\r\n#define STRONGLY_CONNECTED_COMPONENTS_TARJAN_HEADER_HPP\r\
    \n\r\n/**\r\n * @brief strongly connected components Tarjan / \u5F3A\u8FDE\u901A\
    \u5206\u91CF Tarjan \u7B97\u6CD5\r\n *\r\n */\r\n\r\n#include <algorithm>\r\n\
    #include <functional>\r\n#include <stack>\r\n#include <utility>\r\n#include <vector>\r\
    \n\r\nnamespace lib {\r\n\r\nclass StronglyConnectedComponentsGraph {\r\npublic:\r\
    \n  struct InputEdge {\r\n    int from, to;\r\n    InputEdge(int from, int to)\
    \ : from(from), to(to) {}\r\n    ~InputEdge() = default;\r\n  };\r\n\r\n  StronglyConnectedComponentsGraph(int\
    \ n) : n_(n) {}\r\n  ~StronglyConnectedComponentsGraph() = default;\r\n\r\n  void\
    \ add_directed_edge(int u, int v) { input_edge_.emplace_back(u, v); }\r\n\r\n\
    \  std::pair<int, std::vector<int>> get_scc() const {\r\n    std::vector<int>\
    \ idx(n_ + 1, 0), edge(input_edge_.size()), dfn(n_, 0), low(n_, 0),\r\n      \
    \  sccno(n_, -1);\r\n    std::stack<int, std::vector<int>> s;\r\n    int dfs_clock\
    \ = 0, scc_cnt = 0;\r\n    for (auto &i : input_edge_) ++idx[i.from];\r\n    for\
    \ (int i = 0, sum = 0; i <= n_; ++i) sum += idx[i], idx[i] = sum - idx[i];\r\n\
    \    for (auto &i : input_edge_) edge[idx[i.from]++] = i.to;\r\n    for (int i\
    \ = n_ - 1; i > 0; --i) idx[i] = idx[i - 1];\r\n    idx[0]                   \
    \    = 0;\r\n    std::function<void(int)> dfs = [&](int u) {\r\n      dfn[u] =\
    \ low[u] = ++dfs_clock;\r\n      s.push(u);\r\n      for (int i = idx[u], ie =\
    \ idx[u + 1]; i < ie; ++i) {\r\n        int v = edge[i];\r\n        if (dfn[v]\
    \ == 0) {\r\n          dfs(v);\r\n          low[u] = std::min(low[u], low[v]);\r\
    \n        } else if (sccno[v] == -1) {\r\n          low[u] = std::min(low[u],\
    \ dfn[v]);\r\n        }\r\n      }\r\n      if (dfn[u] == low[u]) {\r\n      \
    \  int v;\r\n        do {\r\n          v = s.top();\r\n          s.pop();\r\n\
    \          sccno[v] = scc_cnt;\r\n        } while (v != u);\r\n        ++scc_cnt;\r\
    \n      }\r\n    };\r\n    for (int i = 0; i < n_; ++i)\r\n      if (dfn[i] ==\
    \ 0) dfs(i);\r\n    return {scc_cnt, sccno};\r\n  }\r\n\r\nprivate:\r\n  const\
    \ int n_; // \u8282\u70B9\u7F16\u53F7\u5728 [0, n-1] \u4EE5\u5185\uFF01\r\n  std::vector<InputEdge>\
    \ input_edge_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: graph/strongly_connected_components_Tarjan.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
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
