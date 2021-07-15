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
    \ \"https://judge.yosupo.jp/problem/scc\"\n\n#include <iostream>\n#include <vector>\n\
    \n#line 1 \"graph/strongly_connected_components_Tarjan.hpp\"\n\n\n\n/**\n * @brief\
    \ strongly connected components Tarjan / \u5F3A\u8FDE\u901A\u5206\u91CF Tarjan\
    \ \u7B97\u6CD5\n *\n */\n\n#include <algorithm>\n#include <functional>\n#include\
    \ <stack>\n#include <utility>\n#line 14 \"graph/strongly_connected_components_Tarjan.hpp\"\
    \n\nnamespace lib {\n\nclass StronglyConnectedComponentsGraph {\npublic:\n  struct\
    \ InputEdge {\n    int from, to;\n    InputEdge(int from, int to) : from(from),\
    \ to(to) {}\n    ~InputEdge() = default;\n  };\n\n  StronglyConnectedComponentsGraph(int\
    \ n) : n_(n) {}\n  ~StronglyConnectedComponentsGraph() = default;\n\n  void add_directed_edge(int\
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
    \n\n#line 7 \"remote_test/yosupo/graph/scc.0.test.cpp\"\n\nint main() {\n#ifdef\
    \ LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n\
    #endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n  int n, m;\n\
    \  std::cin >> n >> m;\n  lib::StronglyConnectedComponentsGraph g(n);\n  while\
    \ (m--) {\n    int u, v;\n    std::cin >> u >> v;\n    g.add_directed_edge(u,\
    \ v);\n  }\n  auto [scccnt, sccno] = g.get_scc();\n  std::vector<std::vector<int>>\
    \ topo(scccnt);\n  for (int i = 0; i < n; ++i) topo[sccno[i]].push_back(i);\n\
    \  std::reverse(topo.begin(), topo.end());\n  std::cout << scccnt << '\\n';\n\
    \  for (auto &i : topo) {\n    std::cout << i.size() << ' ';\n    for (auto j\
    \ : i) std::cout << j << ' ';\n    std::cout << '\\n';\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/scc\"\n\n#include <iostream>\n\
    #include <vector>\n\n#include \"graph/strongly_connected_components_Tarjan.hpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, m;\n  std::cin >> n >> m;\n  lib::StronglyConnectedComponentsGraph g(n);\n\
    \  while (m--) {\n    int u, v;\n    std::cin >> u >> v;\n    g.add_directed_edge(u,\
    \ v);\n  }\n  auto [scccnt, sccno] = g.get_scc();\n  std::vector<std::vector<int>>\
    \ topo(scccnt);\n  for (int i = 0; i < n; ++i) topo[sccno[i]].push_back(i);\n\
    \  std::reverse(topo.begin(), topo.end());\n  std::cout << scccnt << '\\n';\n\
    \  for (auto &i : topo) {\n    std::cout << i.size() << ' ';\n    for (auto j\
    \ : i) std::cout << j << ' ';\n    std::cout << '\\n';\n  }\n  return 0;\n}"
  dependsOn:
  - graph/strongly_connected_components_Tarjan.hpp
  isVerificationFile: true
  path: remote_test/yosupo/graph/scc.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 14:25:20+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/graph/scc.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/graph/scc.0.test.cpp
- /verify/remote_test/yosupo/graph/scc.0.test.cpp.html
title: remote_test/yosupo/graph/scc.0.test.cpp
---
