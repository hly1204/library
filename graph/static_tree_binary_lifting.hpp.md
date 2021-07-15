---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/graph/lca.0.test.cpp
    title: remote_test/yosupo/graph/lca.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "static tree binary lifting / \u6811\u4E0A\u500D\u589E\u6CD5"
    links: []
  bundledCode: "#line 1 \"graph/static_tree_binary_lifting.hpp\"\n\n\n\r\n/**\r\n\
    \ * @brief static tree binary lifting / \u6811\u4E0A\u500D\u589E\u6CD5\r\n *\r\
    \n */\r\n\r\n#include <cassert>\r\n#include <queue>\r\n#include <vector>\r\n\r\
    \nnamespace lib {\r\n\r\n/**\r\n * @brief \u9759\u6001\u6811 LCA \u548C LA \u7684\
    \u56DE\u7B54\uFF0C\u6BCF\u6B21\u5728 O(\\log n) \u65F6\u95F4\uFF0C\u9700\u8981\
    \ O(n\\log n) \u65F6\u95F4\u9884\u5904\u7406\r\n *\r\n */\r\nclass StaticTreeBinaryLifting\
    \ {\r\npublic:\r\n  /**\r\n   * @param parent \u6CE8\u610F\u8BBE\u7F6E parent[root]=-1\r\
    \n   */\r\n  StaticTreeBinaryLifting(const std::vector<int> &parent) : depth_(parent.size(),\
    \ -1) {\r\n    int n = parent.size(), root, lg2_n = 0;\r\n    assert(n > 0);\r\
    \n    while ((1 << lg2_n) < n) ++lg2_n;\r\n    parent_.assign(lg2_n, std::vector<int>(n,\
    \ -1));\r\n    std::vector<int> g(n), idx(n + 1, 0);\r\n    for (int i = 0; i\
    \ < n; ++i)\r\n      if (parent[i] != -1) {\r\n        ++idx[parent[i]];\r\n \
    \     } else {\r\n        root = i;\r\n      }\r\n    for (int i = 0, sum = 0;\
    \ i <= n; ++i) sum += idx[i], idx[i] = sum - idx[i];\r\n    for (int i = 0; i\
    \ < n; ++i)\r\n      if (parent[i] != -1) g[idx[parent[i]]++] = i;\r\n    for\
    \ (int i = n - 1; i > 0; --i) idx[i] = idx[i - 1];\r\n    idx[0] = 0;\r\n    std::queue<int>\
    \ q;\r\n    q.push(root);\r\n    for (int dep = 1; !q.empty(); ++dep)\r\n    \
    \  for (int s = q.size(); s != 0; --s) {\r\n        int t = q.front();\r\n   \
    \     q.pop();\r\n        depth_[t] = dep;\r\n        for (int i = 1; (1 << i)\
    \ < dep; ++i) parent_[i][t] = parent_[i - 1][parent_[i - 1][t]];\r\n        for\
    \ (int i = idx[t], ie = idx[t + 1]; i < ie; ++i)\r\n          if (depth_[g[i]]\
    \ == -1) {\r\n            parent_[0][g[i]] = t;\r\n            q.push(g[i]);\r\
    \n          }\r\n      }\r\n  }\r\n  ~StaticTreeBinaryLifting() = default;\r\n\
    \r\n  int query_la(int x, int k) const {\r\n    assert(k < depth_[x]);\r\n   \
    \ for (int i = 0; (1 << i) <= k; ++i)\r\n      if (1 << i & k) x = parent_[i][x];\r\
    \n    return x;\r\n  }\r\n\r\n  int query_lca(int x, int y) const {\r\n    if\
    \ (depth_[x] < depth_[y]) std::swap(x, y);\r\n    if ((x = query_la(x, depth_[x]\
    \ - depth_[y])) == y) return x;\r\n    for (int i = parent_.size() - 1; i >= 0;\
    \ --i)\r\n      if (parent_[i][x] != parent_[i][y]) x = parent_[i][x], y = parent_[i][y];\r\
    \n    return parent_[0][x];\r\n  }\r\n\r\nprivate:\r\n  std::vector<int> depth_;\r\
    \n  std::vector<std::vector<int>> parent_;\r\n};\r\n\r\n} // namespace lib\r\n\
    \r\n\n"
  code: "#ifndef STATIC_TREE_BINARY_LIFTING_HEADER_HPP\r\n#define STATIC_TREE_BINARY_LIFTING_HEADER_HPP\r\
    \n\r\n/**\r\n * @brief static tree binary lifting / \u6811\u4E0A\u500D\u589E\u6CD5\
    \r\n *\r\n */\r\n\r\n#include <cassert>\r\n#include <queue>\r\n#include <vector>\r\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u9759\u6001\u6811 LCA \u548C LA\
    \ \u7684\u56DE\u7B54\uFF0C\u6BCF\u6B21\u5728 O(\\log n) \u65F6\u95F4\uFF0C\u9700\
    \u8981 O(n\\log n) \u65F6\u95F4\u9884\u5904\u7406\r\n *\r\n */\r\nclass StaticTreeBinaryLifting\
    \ {\r\npublic:\r\n  /**\r\n   * @param parent \u6CE8\u610F\u8BBE\u7F6E parent[root]=-1\r\
    \n   */\r\n  StaticTreeBinaryLifting(const std::vector<int> &parent) : depth_(parent.size(),\
    \ -1) {\r\n    int n = parent.size(), root, lg2_n = 0;\r\n    assert(n > 0);\r\
    \n    while ((1 << lg2_n) < n) ++lg2_n;\r\n    parent_.assign(lg2_n, std::vector<int>(n,\
    \ -1));\r\n    std::vector<int> g(n), idx(n + 1, 0);\r\n    for (int i = 0; i\
    \ < n; ++i)\r\n      if (parent[i] != -1) {\r\n        ++idx[parent[i]];\r\n \
    \     } else {\r\n        root = i;\r\n      }\r\n    for (int i = 0, sum = 0;\
    \ i <= n; ++i) sum += idx[i], idx[i] = sum - idx[i];\r\n    for (int i = 0; i\
    \ < n; ++i)\r\n      if (parent[i] != -1) g[idx[parent[i]]++] = i;\r\n    for\
    \ (int i = n - 1; i > 0; --i) idx[i] = idx[i - 1];\r\n    idx[0] = 0;\r\n    std::queue<int>\
    \ q;\r\n    q.push(root);\r\n    for (int dep = 1; !q.empty(); ++dep)\r\n    \
    \  for (int s = q.size(); s != 0; --s) {\r\n        int t = q.front();\r\n   \
    \     q.pop();\r\n        depth_[t] = dep;\r\n        for (int i = 1; (1 << i)\
    \ < dep; ++i) parent_[i][t] = parent_[i - 1][parent_[i - 1][t]];\r\n        for\
    \ (int i = idx[t], ie = idx[t + 1]; i < ie; ++i)\r\n          if (depth_[g[i]]\
    \ == -1) {\r\n            parent_[0][g[i]] = t;\r\n            q.push(g[i]);\r\
    \n          }\r\n      }\r\n  }\r\n  ~StaticTreeBinaryLifting() = default;\r\n\
    \r\n  int query_la(int x, int k) const {\r\n    assert(k < depth_[x]);\r\n   \
    \ for (int i = 0; (1 << i) <= k; ++i)\r\n      if (1 << i & k) x = parent_[i][x];\r\
    \n    return x;\r\n  }\r\n\r\n  int query_lca(int x, int y) const {\r\n    if\
    \ (depth_[x] < depth_[y]) std::swap(x, y);\r\n    if ((x = query_la(x, depth_[x]\
    \ - depth_[y])) == y) return x;\r\n    for (int i = parent_.size() - 1; i >= 0;\
    \ --i)\r\n      if (parent_[i][x] != parent_[i][y]) x = parent_[i][x], y = parent_[i][y];\r\
    \n    return parent_[0][x];\r\n  }\r\n\r\nprivate:\r\n  std::vector<int> depth_;\r\
    \n  std::vector<std::vector<int>> parent_;\r\n};\r\n\r\n} // namespace lib\r\n\
    \r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: graph/static_tree_binary_lifting.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/graph/lca.0.test.cpp
documentation_of: graph/static_tree_binary_lifting.hpp
layout: document
redirect_from:
- /library/graph/static_tree_binary_lifting.hpp
- /library/graph/static_tree_binary_lifting.hpp.html
title: "static tree binary lifting / \u6811\u4E0A\u500D\u589E\u6CD5"
---
