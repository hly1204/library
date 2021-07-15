---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/strongly_connected_components_Tarjan.hpp
    title: "strongly connected components Tarjan / \u5F3A\u8FDE\u901A\u5206\u91CF\
      \ Tarjan \u7B97\u6CD5"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/scc
    links:
    - https://judge.yosupo.jp/problem/scc
  bundledCode: "#line 1 \"remote_test/yosupo/graph/scc.0.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/scc\"\r\n\r\n#include <iostream>\r\n#include\
    \ <vector>\r\n\r\n#line 1 \"graph/strongly_connected_components_Tarjan.hpp\"\n\
    \n\n\r\n/**\r\n * @brief strongly connected components Tarjan / \u5F3A\u8FDE\u901A\
    \u5206\u91CF Tarjan \u7B97\u6CD5\r\n *\r\n */\r\n\r\n#include <algorithm>\r\n\
    #include <functional>\r\n#include <stack>\r\n#include <utility>\r\n#line 14 \"\
    graph/strongly_connected_components_Tarjan.hpp\"\n\r\nnamespace lib {\r\n\r\n\
    class StronglyConnectedComponentsGraph {\r\npublic:\r\n  struct InputEdge {\r\n\
    \    int from, to;\r\n    InputEdge(int from, int to) : from(from), to(to) {}\r\
    \n    ~InputEdge() = default;\r\n  };\r\n\r\n  StronglyConnectedComponentsGraph(int\
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
    \ input_edge_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line 7 \"remote_test/yosupo/graph/scc.0.test.cpp\"\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int n, m;\r\n  std::cin >> n >> m;\r\n  lib::StronglyConnectedComponentsGraph\
    \ g(n);\r\n  while (m--) {\r\n    int u, v;\r\n    std::cin >> u >> v;\r\n   \
    \ g.add_directed_edge(u, v);\r\n  }\r\n  auto [scccnt, sccno] = g.get_scc();\r\
    \n  std::vector<std::vector<int>> topo(scccnt);\r\n  for (int i = 0; i < n; ++i)\
    \ topo[sccno[i]].push_back(i);\r\n  std::reverse(topo.begin(), topo.end());\r\n\
    \  std::cout << scccnt << '\\n';\r\n  for (auto &i : topo) {\r\n    std::cout\
    \ << i.size() << ' ';\r\n    for (auto j : i) std::cout << j << ' ';\r\n    std::cout\
    \ << '\\n';\r\n  }\r\n  return 0;\r\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/scc\"\r\n\r\n#include <iostream>\r\
    \n#include <vector>\r\n\r\n#include \"graph/strongly_connected_components_Tarjan.hpp\"\
    \r\n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin),\
    \ std::freopen(\"out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\
    \n  std::cin.tie(0);\r\n  int n, m;\r\n  std::cin >> n >> m;\r\n  lib::StronglyConnectedComponentsGraph\
    \ g(n);\r\n  while (m--) {\r\n    int u, v;\r\n    std::cin >> u >> v;\r\n   \
    \ g.add_directed_edge(u, v);\r\n  }\r\n  auto [scccnt, sccno] = g.get_scc();\r\
    \n  std::vector<std::vector<int>> topo(scccnt);\r\n  for (int i = 0; i < n; ++i)\
    \ topo[sccno[i]].push_back(i);\r\n  std::reverse(topo.begin(), topo.end());\r\n\
    \  std::cout << scccnt << '\\n';\r\n  for (auto &i : topo) {\r\n    std::cout\
    \ << i.size() << ' ';\r\n    for (auto j : i) std::cout << j << ' ';\r\n    std::cout\
    \ << '\\n';\r\n  }\r\n  return 0;\r\n}"
  dependsOn:
  - graph/strongly_connected_components_Tarjan.hpp
  isVerificationFile: true
  path: remote_test/yosupo/graph/scc.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/graph/scc.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/graph/scc.0.test.cpp
- /verify/remote_test/yosupo/graph/scc.0.test.cpp.html
title: remote_test/yosupo/graph/scc.0.test.cpp
---
