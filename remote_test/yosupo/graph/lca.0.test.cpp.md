---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/static_tree_binary_lifting.hpp
    title: "static tree binary lifting / \u6811\u4E0A\u500D\u589E\u6CD5"
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
    \ \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n#include <vector>\n\
    \n#line 1 \"graph/static_tree_binary_lifting.hpp\"\n\n\n\n/**\n * @brief static\
    \ tree binary lifting / \u6811\u4E0A\u500D\u589E\u6CD5\n *\n */\n\n#include <cassert>\n\
    #include <queue>\n#line 12 \"graph/static_tree_binary_lifting.hpp\"\n\nnamespace\
    \ lib {\n\n/**\n * @brief \u9759\u6001\u6811 LCA \u548C LA \u7684\u56DE\u7B54\uFF0C\
    \u6BCF\u6B21\u5728 O(\\log n) \u65F6\u95F4\uFF0C\u9700\u8981 O(n\\log n) \u65F6\
    \u95F4\u9884\u5904\u7406\n *\n */\nclass StaticTreeBinaryLifting {\npublic:\n\
    \  /**\n   * @param parent \u6CE8\u610F\u8BBE\u7F6E parent[root]=-1\n   */\n \
    \ StaticTreeBinaryLifting(const std::vector<int> &parent) : depth_(parent.size(),\
    \ -1) {\n    int n = parent.size(), root, lg2_n = 0;\n    assert(n > 0);\n   \
    \ while ((1 << lg2_n) < n) ++lg2_n;\n    parent_.assign(lg2_n, std::vector<int>(n,\
    \ -1));\n    std::vector<int> g(n), idx(n + 1, 0);\n    for (int i = 0; i < n;\
    \ ++i)\n      if (parent[i] != -1) {\n        ++idx[parent[i]];\n      } else\
    \ {\n        root = i;\n      }\n    for (int i = 0, sum = 0; i <= n; ++i) sum\
    \ += idx[i], idx[i] = sum - idx[i];\n    for (int i = 0; i < n; ++i)\n      if\
    \ (parent[i] != -1) g[idx[parent[i]]++] = i;\n    for (int i = n - 1; i > 0; --i)\
    \ idx[i] = idx[i - 1];\n    idx[0] = 0;\n    std::queue<int> q;\n    q.push(root);\n\
    \    for (int dep = 1; !q.empty(); ++dep)\n      for (int s = q.size(); s != 0;\
    \ --s) {\n        int t = q.front();\n        q.pop();\n        depth_[t] = dep;\n\
    \        for (int i = 1; (1 << i) < dep; ++i) parent_[i][t] = parent_[i - 1][parent_[i\
    \ - 1][t]];\n        for (int i = idx[t], ie = idx[t + 1]; i < ie; ++i)\n    \
    \      if (depth_[g[i]] == -1) {\n            parent_[0][g[i]] = t;\n        \
    \    q.push(g[i]);\n          }\n      }\n  }\n  ~StaticTreeBinaryLifting() =\
    \ default;\n\n  int query_la(int x, int k) const {\n    assert(k < depth_[x]);\n\
    \    for (int i = 0; (1 << i) <= k; ++i)\n      if (1 << i & k) x = parent_[i][x];\n\
    \    return x;\n  }\n\n  int query_lca(int x, int y) const {\n    if (depth_[x]\
    \ < depth_[y]) std::swap(x, y);\n    if ((x = query_la(x, depth_[x] - depth_[y]))\
    \ == y) return x;\n    for (int i = parent_.size() - 1; i >= 0; --i)\n      if\
    \ (parent_[i][x] != parent_[i][y]) x = parent_[i][x], y = parent_[i][y];\n   \
    \ return parent_[0][x];\n  }\n\nprivate:\n  std::vector<int> depth_;\n  std::vector<std::vector<int>>\
    \ parent_;\n};\n\n} // namespace lib\n\n\n#line 7 \"remote_test/yosupo/graph/lca.0.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, q;\n  std::cin >> n >> q;\n  std::vector<int> p(n);\n  p[0] = -1;\n\
    \  for (int i = 1; i < n; ++i) std::cin >> p[i];\n  lib::StaticTreeBinaryLifting\
    \ tree(p);\n  while (q--) {\n    int u, v;\n    std::cin >> u >> v;\n    std::cout\
    \ << tree.query_lca(u, v) << '\\n';\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n\n#include <iostream>\n\
    #include <vector>\n\n#include \"graph/static_tree_binary_lifting.hpp\"\n\nint\
    \ main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, q;\n  std::cin >> n >> q;\n  std::vector<int> p(n);\n  p[0] = -1;\n\
    \  for (int i = 1; i < n; ++i) std::cin >> p[i];\n  lib::StaticTreeBinaryLifting\
    \ tree(p);\n  while (q--) {\n    int u, v;\n    std::cin >> u >> v;\n    std::cout\
    \ << tree.query_lca(u, v) << '\\n';\n  }\n  return 0;\n}"
  dependsOn:
  - graph/static_tree_binary_lifting.hpp
  isVerificationFile: true
  path: remote_test/yosupo/graph/lca.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-14 00:44:43+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/graph/lca.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/graph/lca.0.test.cpp
- /verify/remote_test/yosupo/graph/lca.0.test.cpp.html
title: remote_test/yosupo/graph/lca.0.test.cpp
---
