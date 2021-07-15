---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/datastructure/persistent_union_find.0.test.cpp
    title: remote_test/yosupo/datastructure/persistent_union_find.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "rollbackable disjoint set / \u56DE\u6EDA\u5E76\u67E5\u96C6"
    links: []
  bundledCode: "#line 1 \"datastructure/basic/rollbackable_disjoint_set.hpp\"\n\n\n\
    \r\n/**\r\n * @brief rollbackable disjoint set / \u56DE\u6EDA\u5E76\u67E5\u96C6\
    \r\n *\r\n */\r\n\r\n#include <stack>\r\n#include <vector>\r\n\r\nnamespace lib\
    \ {\r\n\r\nclass RollbackableDisjointSet {\r\npublic:\r\n  RollbackableDisjointSet()\
    \ = default;\r\n  RollbackableDisjointSet(int n) : p_(n + 1), sz_(n + 1, 1) {\r\
    \n    for (int i = 0; i <= n; ++i) p_[i] = i;\r\n  }\r\n  ~RollbackableDisjointSet()\
    \ = default;\r\n\r\n  void make_set(int n) {\r\n    p_.resize(n + 1);\r\n    sz_.assign(n\
    \ + 1, 1);\r\n    while (!stk_.empty()) stk_.pop();\r\n    for (int i = 0; i <=\
    \ n; ++i) p_[i] = i;\r\n  }\r\n\r\n  int find(int u) const {\r\n    while (u !=\
    \ p_[u]) u = p_[u];\r\n    return u;\r\n  }\r\n\r\n  bool same(int u, int v) const\
    \ { return find(u) == find(v); }\r\n\r\n  int unite(int u, int v) {\r\n    u =\
    \ find(u), v = find(v);\r\n    if (u == v) return u;\r\n    return link(u, v);\r\
    \n  }\r\n\r\n  int get_component_size(int u) const { return sz_[find(u)]; }\r\n\
    \r\n  /**\r\n   * @brief \u64A4\u9500\u4E0A\u4E00\u6B21\u6210\u529F\u7684 unite\r\
    \n   * @note \u53EA\u80FD\u64A4\u9500\u6210\u529F\u7684 unite \u5982\u679C\u4E0D\
    \u6210\u529F\u662F\u4E0D\u80FD\u64A4\u9500\u7684\r\n   */\r\n  void undo() {\r\
    \n    int u = stk_.top(); // \u53D6\u51FA\u5C0F\u6811\uFF0C\u4FEE\u6539\u5C0F\u6811\
    \u7684 parent\r\n    stk_.pop();\r\n    sz_[p_[u]] -= sz_[u];\r\n    p_[u] = u;\r\
    \n  }\r\n\r\n  void rollback(int k) {\r\n    while (k--) undo();\r\n  }\r\n\r\n\
    private:\r\n  std::vector<int> p_, sz_;\r\n  std::stack<int, std::vector<int>>\
    \ stk_;\r\n\r\n  int link(int u, int v) {\r\n    if (sz_[u] > sz_[v]) return link(v,\
    \ u);\r\n    sz_[v] += sz_[u];\r\n    stk_.push(u);     // \u5C06\u5C0F\u6811\u653E\
    \u5165\u6808\u4E2D\r\n    return p_[u] = v; // u \u662F\u5C0F\u6811\uFF0C v \u662F\
    \u5927\u6811\uFF0C\u628A\u5C0F\u6811\u63A5\u5230\u5927\u6811\u4E0A\r\n  }\r\n\
    };\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef ROLLBACKABLE_DISJOINT_SET_HEADER_HPP\r\n#define ROLLBACKABLE_DISJOINT_SET_HEADER_HPP\r\
    \n\r\n/**\r\n * @brief rollbackable disjoint set / \u56DE\u6EDA\u5E76\u67E5\u96C6\
    \r\n *\r\n */\r\n\r\n#include <stack>\r\n#include <vector>\r\n\r\nnamespace lib\
    \ {\r\n\r\nclass RollbackableDisjointSet {\r\npublic:\r\n  RollbackableDisjointSet()\
    \ = default;\r\n  RollbackableDisjointSet(int n) : p_(n + 1), sz_(n + 1, 1) {\r\
    \n    for (int i = 0; i <= n; ++i) p_[i] = i;\r\n  }\r\n  ~RollbackableDisjointSet()\
    \ = default;\r\n\r\n  void make_set(int n) {\r\n    p_.resize(n + 1);\r\n    sz_.assign(n\
    \ + 1, 1);\r\n    while (!stk_.empty()) stk_.pop();\r\n    for (int i = 0; i <=\
    \ n; ++i) p_[i] = i;\r\n  }\r\n\r\n  int find(int u) const {\r\n    while (u !=\
    \ p_[u]) u = p_[u];\r\n    return u;\r\n  }\r\n\r\n  bool same(int u, int v) const\
    \ { return find(u) == find(v); }\r\n\r\n  int unite(int u, int v) {\r\n    u =\
    \ find(u), v = find(v);\r\n    if (u == v) return u;\r\n    return link(u, v);\r\
    \n  }\r\n\r\n  int get_component_size(int u) const { return sz_[find(u)]; }\r\n\
    \r\n  /**\r\n   * @brief \u64A4\u9500\u4E0A\u4E00\u6B21\u6210\u529F\u7684 unite\r\
    \n   * @note \u53EA\u80FD\u64A4\u9500\u6210\u529F\u7684 unite \u5982\u679C\u4E0D\
    \u6210\u529F\u662F\u4E0D\u80FD\u64A4\u9500\u7684\r\n   */\r\n  void undo() {\r\
    \n    int u = stk_.top(); // \u53D6\u51FA\u5C0F\u6811\uFF0C\u4FEE\u6539\u5C0F\u6811\
    \u7684 parent\r\n    stk_.pop();\r\n    sz_[p_[u]] -= sz_[u];\r\n    p_[u] = u;\r\
    \n  }\r\n\r\n  void rollback(int k) {\r\n    while (k--) undo();\r\n  }\r\n\r\n\
    private:\r\n  std::vector<int> p_, sz_;\r\n  std::stack<int, std::vector<int>>\
    \ stk_;\r\n\r\n  int link(int u, int v) {\r\n    if (sz_[u] > sz_[v]) return link(v,\
    \ u);\r\n    sz_[v] += sz_[u];\r\n    stk_.push(u);     // \u5C06\u5C0F\u6811\u653E\
    \u5165\u6808\u4E2D\r\n    return p_[u] = v; // u \u662F\u5C0F\u6811\uFF0C v \u662F\
    \u5927\u6811\uFF0C\u628A\u5C0F\u6811\u63A5\u5230\u5927\u6811\u4E0A\r\n  }\r\n\
    };\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/basic/rollbackable_disjoint_set.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/datastructure/persistent_union_find.0.test.cpp
documentation_of: datastructure/basic/rollbackable_disjoint_set.hpp
layout: document
redirect_from:
- /library/datastructure/basic/rollbackable_disjoint_set.hpp
- /library/datastructure/basic/rollbackable_disjoint_set.hpp.html
title: "rollbackable disjoint set / \u56DE\u6EDA\u5E76\u67E5\u96C6"
---
