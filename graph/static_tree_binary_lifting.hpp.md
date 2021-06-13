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
  bundledCode: "#line 1 \"graph/static_tree_binary_lifting.hpp\"\n\n\n\n/**\n * @brief\
    \ static tree binary lifting / \u6811\u4E0A\u500D\u589E\u6CD5\n *\n */\n\n#include\
    \ <cassert>\n#include <queue>\n#include <vector>\n\nnamespace lib {\n\n/**\n *\
    \ @brief \u9759\u6001\u6811 LCA \u548C LA \u7684\u56DE\u7B54\uFF0C\u6BCF\u6B21\
    \u5728 O(\\log n) \u65F6\u95F4\uFF0C\u9700\u8981 O(n\\log n) \u65F6\u95F4\u9884\
    \u5904\u7406\n *\n */\nclass StaticTreeBinaryLifting {\npublic:\n  /**\n   * @param\
    \ parent \u6CE8\u610F\u8BBE\u7F6E parent[root]=-1\n   */\n  StaticTreeBinaryLifting(const\
    \ std::vector<int> &parent) : depth_(parent.size(), -1) {\n    int n = parent.size(),\
    \ root, lg2_n = 0;\n    assert(n > 0);\n    while ((1 << lg2_n) < n) ++lg2_n;\n\
    \    parent_.assign(lg2_n, std::vector<int>(n, -1));\n    std::vector<int> g(n),\
    \ idx(n + 1, 0);\n    for (int i = 0; i < n; ++i)\n      if (parent[i] != -1)\
    \ {\n        ++idx[parent[i]];\n      } else {\n        root = i;\n      }\n \
    \   for (int i = 0, sum = 0; i <= n; ++i) sum += idx[i], idx[i] = sum - idx[i];\n\
    \    for (int i = 0; i < n; ++i)\n      if (parent[i] != -1) g[idx[parent[i]]++]\
    \ = i;\n    for (int i = n - 1; i > 0; --i) idx[i] = idx[i - 1];\n    idx[0] =\
    \ 0;\n    std::queue<int> q;\n    q.push(root);\n    for (int dep = 1; !q.empty();\
    \ ++dep)\n      for (int s = q.size(); s != 0; --s) {\n        int t = q.front();\n\
    \        q.pop();\n        depth_[t] = dep;\n        for (int i = 1; (1 << i)\
    \ < dep; ++i) parent_[i][t] = parent_[i - 1][parent_[i - 1][t]];\n        for\
    \ (int i = idx[t], ie = idx[t + 1]; i < ie; ++i)\n          if (depth_[g[i]] ==\
    \ -1) {\n            parent_[0][g[i]] = t;\n            q.push(g[i]);\n      \
    \    }\n      }\n  }\n  ~StaticTreeBinaryLifting() = default;\n\n  int query_la(int\
    \ x, int k) const {\n    assert(k < depth_[x]);\n    for (int i = 0; (1 << i)\
    \ <= k; ++i)\n      if (1 << i & k) x = parent_[i][x];\n    return x;\n  }\n\n\
    \  int query_lca(int x, int y) const {\n    if (depth_[x] < depth_[y]) std::swap(x,\
    \ y);\n    if ((x = query_la(x, depth_[x] - depth_[y])) == y) return x;\n    for\
    \ (int i = parent_.size() - 1; i >= 0; --i)\n      if (parent_[i][x] != parent_[i][y])\
    \ x = parent_[i][x], y = parent_[i][y];\n    return parent_[0][x];\n  }\n\nprivate:\n\
    \  std::vector<int> depth_;\n  std::vector<std::vector<int>> parent_;\n};\n\n\
    } // namespace lib\n\n\n"
  code: "#ifndef STATIC_TREE_BINARY_LIFTING_HEADER_HPP\n#define STATIC_TREE_BINARY_LIFTING_HEADER_HPP\n\
    \n/**\n * @brief static tree binary lifting / \u6811\u4E0A\u500D\u589E\u6CD5\n\
    \ *\n */\n\n#include <cassert>\n#include <queue>\n#include <vector>\n\nnamespace\
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
    \ parent_;\n};\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: graph/static_tree_binary_lifting.hpp
  requiredBy: []
  timestamp: '2021-06-14 00:44:43+08:00'
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
