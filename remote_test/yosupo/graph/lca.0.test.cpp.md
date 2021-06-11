---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/binary_lifting.hpp
    title: "binary lifting / \u500D\u589E\u6CD5"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"remote_test/yosupo/graph/lca.0.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n\n#line 1 \"\
    graph/binary_lifting.hpp\"\n\n\n\n/**\n * @brief binary lifting / \u500D\u589E\
    \u6CD5\n *\n */\n\n#include <cassert>\n#include <queue>\n#include <vector>\n\n\
    namespace lib {\n\n/**\n * @brief \u9759\u6001\u6811 LCA \u548C LA \u7684\u56DE\
    \u7B54\uFF0C\u6BCF\u6B21\u5728 O(\\log n) \u65F6\u95F4\uFF0C\u9700\u8981 O(n\\\
    log n) \u65F6\u95F4\u9884\u5904\u7406\n *\n */\nclass StaticTree {\npublic:\n\
    \  template <typename Type> using vec = std::vector<Type>;\n\n  StaticTree(int\
    \ N) : N_(N), g_(N_ + 1) {}\n  ~StaticTree() = default;\n\n  void add_edge(int\
    \ from, int to) { g_[from].emplace_back(to); }\n\n  /**\n   * @brief \u9884\u5904\
    \u7406\n   *\n   * @param r \u4E3A\u6811\u6839\n   */\n  void preprocess(const\
    \ int r) {\n    int lg2_N = 0;\n    while ((1 << lg2_N) <= N_) ++lg2_N;\n    p_.assign(lg2_N,\
    \ vec<int>(N_ + 1, -1));\n    d_.assign(N_ + 1, -1);\n    int dep = 1; // \u6839\
    \u8282\u70B9\u7684\u6DF1\u5EA6\u8BBE\u7F6E\u4E3A 1 \u800C\u4E0D\u662F 0\n    std::queue<int>\
    \ q;\n    q.push(r); // d[r] = 1\n    while (!q.empty()) {\n      for (int s =\
    \ q.size(); s != 0; --s) {\n        int t = q.front();\n        q.pop();\n   \
    \     d_[t] = dep;\n        for (int i = 1; (1 << i) < dep; ++i) p_[i][t] = p_[i\
    \ - 1][p_[i - 1][t]];\n        for (auto i : g_[t])\n          if (d_[i] == -1)\
    \ {\n            p_[0][i] = t;\n            q.push(i);\n          }\n      }\n\
    \      ++dep;\n    }\n  }\n\n  int query_la(int x, int k) const {\n    assert(k\
    \ < d_[x]);\n    for (int i = 0; (1 << i) <= k; ++i)\n      if (1 << i & k) x\
    \ = p_[i][x];\n    return x;\n  }\n\n  int query_lca(int x, int y) const {\n \
    \   if (d_[x] < d_[y]) std::swap(x, y);\n    if ((x = query_la(x, d_[x] - d_[y]))\
    \ == y) return x;\n    for (int i = p_.size() - 1; i >= 0; --i)\n      if (p_[i][x]\
    \ != p_[i][y]) x = p_[i][x], y = p_[i][y];\n    return p_[0][x];\n  }\n\nprivate:\n\
    \  const int N_;\n  vec<vec<int>> g_, p_; // graph & 2^i th parent\n  vec<int>\
    \ d_;          // depth\n};\n\n} // namespace lib\n\n\n#line 6 \"remote_test/yosupo/graph/lca.0.test.cpp\"\
    \n\nint main() {\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n  int\
    \ n, q;\n  std::cin >> n >> q;\n  lib::StaticTree tree(n);\n  for (int i = 1;\
    \ i < n; ++i) {\n    int p;\n    std::cin >> p;\n    tree.add_edge(p, i);\n  }\n\
    \  tree.preprocess(0);\n  while (q--) {\n    int u, v;\n    std::cin >> u >> v;\n\
    \    std::cout << tree.query_lca(u, v) << '\\n';\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n\
    \n#include \"graph/binary_lifting.hpp\"\n\nint main() {\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(0);\n  int n, q;\n  std::cin >> n >> q;\n  lib::StaticTree tree(n);\n\
    \  for (int i = 1; i < n; ++i) {\n    int p;\n    std::cin >> p;\n    tree.add_edge(p,\
    \ i);\n  }\n  tree.preprocess(0);\n  while (q--) {\n    int u, v;\n    std::cin\
    \ >> u >> v;\n    std::cout << tree.query_lca(u, v) << '\\n';\n  }\n  return 0;\n\
    }"
  dependsOn:
  - graph/binary_lifting.hpp
  isVerificationFile: true
  path: remote_test/yosupo/graph/lca.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-11 23:14:06+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/graph/lca.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/graph/lca.0.test.cpp
- /verify/remote_test/yosupo/graph/lca.0.test.cpp.html
title: remote_test/yosupo/graph/lca.0.test.cpp
---
