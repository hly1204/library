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
  bundledCode: "#line 1 \"datastructure/basic/rollbackable_disjoint_set.hpp\"\n/**\n\
    \ * @brief rollbackable disjoint set / \u56DE\u6EDA\u5E76\u67E5\u96C6\n *\n */\n\
    \n#ifndef ROLLBACKABLE_DISJOINT_SET_HEADER_HPP\n#define ROLLBACKABLE_DISJOINT_SET_HEADER_HPP\n\
    \n#include <stack>\n#include <vector>\n\nnamespace lib {\n\n// \u4E3A\u4E86\u65B9\
    \u4FBF\u8FD9\u91CC\u8BBE\u7F6E\u4E3A [0,n+1] \u90FD\u662F\u7F16\u53F7\nclass RollbackableDisjointSet\
    \ {\npublic:\n  RollbackableDisjointSet() {}\n  RollbackableDisjointSet(int n)\
    \ : p_(n + 1), sz_(n + 1, 1) {\n    for (int i = 0; i <= n; ++i) p_[i] = i;\n\
    \  }\n  ~RollbackableDisjointSet() = default;\n\n  void make_set(int n) {\n  \
    \  p_.resize(n + 1);\n    sz_.assign(n + 1, 1);\n    while (!stk_.empty()) stk_.pop();\n\
    \    for (int i = 0; i <= n; ++i) p_[i] = i;\n  }\n\n  int find(int u) const {\n\
    \    while (u != p_[u]) u = p_[u];\n    return u;\n  }\n\n  bool same(int u, int\
    \ v) const { return find(u) == find(v); }\n\n  int unite(int u, int v) {\n   \
    \ u = find(u), v = find(v);\n    if (u == v) return u;\n    return link(u, v);\n\
    \  }\n\n  int get_component_size(int u) const { return sz_[find(u)]; }\n\n  void\
    \ undo() {\n    // \u53EA\u80FD undo \u6210\u529F\u7684 unite \u5982\u679C\u4E0D\
    \u6210\u529F\u662F\u4E0D\u80FD undo \u7684\n    // \u53D6\u51FA\u5C0F\u6811\uFF0C\
    \u4FEE\u6539\u5C0F\u6811\u7684 parent\n    int u = stk_.top();\n    stk_.pop();\n\
    \    sz_[p_[u]] -= sz_[u];\n    p_[u] = u;\n  }\n\n  void rollback(int k) {\n\
    \    while (k--) undo();\n  }\n\nprivate:\n  std::vector<int> p_, sz_;\n  std::stack<int,\
    \ std::vector<int>> stk_;\n\n  int link(int u, int v) {\n    if (sz_[u] > sz_[v])\
    \ return link(v, u);\n    // u \u662F\u5C0F\u6811\uFF0C v \u662F\u5927\u6811\uFF0C\
    \u628A\u5C0F\u6811\u63A5\u5230\u5927\u6811\u4E0A\n    sz_[v] += sz_[u];\n    stk_.push(u);\
    \ // \u5C06\u5C0F\u6811\u653E\u5165\u6808\u4E2D\n    return p_[u] = v;\n  }\n\
    };\n\n} // namespace lib\n\n#endif\n"
  code: "/**\n * @brief rollbackable disjoint set / \u56DE\u6EDA\u5E76\u67E5\u96C6\
    \n *\n */\n\n#ifndef ROLLBACKABLE_DISJOINT_SET_HEADER_HPP\n#define ROLLBACKABLE_DISJOINT_SET_HEADER_HPP\n\
    \n#include <stack>\n#include <vector>\n\nnamespace lib {\n\n// \u4E3A\u4E86\u65B9\
    \u4FBF\u8FD9\u91CC\u8BBE\u7F6E\u4E3A [0,n+1] \u90FD\u662F\u7F16\u53F7\nclass RollbackableDisjointSet\
    \ {\npublic:\n  RollbackableDisjointSet() {}\n  RollbackableDisjointSet(int n)\
    \ : p_(n + 1), sz_(n + 1, 1) {\n    for (int i = 0; i <= n; ++i) p_[i] = i;\n\
    \  }\n  ~RollbackableDisjointSet() = default;\n\n  void make_set(int n) {\n  \
    \  p_.resize(n + 1);\n    sz_.assign(n + 1, 1);\n    while (!stk_.empty()) stk_.pop();\n\
    \    for (int i = 0; i <= n; ++i) p_[i] = i;\n  }\n\n  int find(int u) const {\n\
    \    while (u != p_[u]) u = p_[u];\n    return u;\n  }\n\n  bool same(int u, int\
    \ v) const { return find(u) == find(v); }\n\n  int unite(int u, int v) {\n   \
    \ u = find(u), v = find(v);\n    if (u == v) return u;\n    return link(u, v);\n\
    \  }\n\n  int get_component_size(int u) const { return sz_[find(u)]; }\n\n  void\
    \ undo() {\n    // \u53EA\u80FD undo \u6210\u529F\u7684 unite \u5982\u679C\u4E0D\
    \u6210\u529F\u662F\u4E0D\u80FD undo \u7684\n    // \u53D6\u51FA\u5C0F\u6811\uFF0C\
    \u4FEE\u6539\u5C0F\u6811\u7684 parent\n    int u = stk_.top();\n    stk_.pop();\n\
    \    sz_[p_[u]] -= sz_[u];\n    p_[u] = u;\n  }\n\n  void rollback(int k) {\n\
    \    while (k--) undo();\n  }\n\nprivate:\n  std::vector<int> p_, sz_;\n  std::stack<int,\
    \ std::vector<int>> stk_;\n\n  int link(int u, int v) {\n    if (sz_[u] > sz_[v])\
    \ return link(v, u);\n    // u \u662F\u5C0F\u6811\uFF0C v \u662F\u5927\u6811\uFF0C\
    \u628A\u5C0F\u6811\u63A5\u5230\u5927\u6811\u4E0A\n    sz_[v] += sz_[u];\n    stk_.push(u);\
    \ // \u5C06\u5C0F\u6811\u653E\u5165\u6808\u4E2D\n    return p_[u] = v;\n  }\n\
    };\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/basic/rollbackable_disjoint_set.hpp
  requiredBy: []
  timestamp: '2021-06-06 20:18:21+08:00'
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
