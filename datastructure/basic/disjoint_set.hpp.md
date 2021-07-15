---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/datastructure/union_find.0.test.cpp
    title: remote_test/yosupo/datastructure/union_find.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "disjoint set / \u5E76\u67E5\u96C6"
    links: []
  bundledCode: "#line 1 \"datastructure/basic/disjoint_set.hpp\"\n\n\n\r\n/**\r\n\
    \ * @brief disjoint set / \u5E76\u67E5\u96C6\r\n *\r\n */\r\n\r\n#include <vector>\r\
    \n\r\nnamespace lib {\r\n\r\nclass DisjointSet {\r\npublic:\r\n  DisjointSet()\
    \ = default;\r\n  DisjointSet(int n) : p_(n + 1), sz_(n + 1, 1) {\r\n    for (int\
    \ i = 0; i <= n; ++i) p_[i] = i;\r\n  }\r\n  ~DisjointSet() = default;\r\n\r\n\
    \  void make_set(int n) {\r\n    p_.resize(n + 1);\r\n    sz_.assign(n + 1, 1);\r\
    \n    for (int i = 0; i <= n; ++i) p_[i] = i;\r\n  }\r\n\r\n  int find(int u)\
    \ { // path havling\r\n    while (p_[u] != p_[p_[u]]) u = p_[u] = p_[p_[u]];\r\
    \n    return p_[u];\r\n  }\r\n\r\n  bool same(int u, int v) { return find(u) ==\
    \ find(v); }\r\n\r\n  int unite(int u, int v) {\r\n    u = find(u), v = find(v);\r\
    \n    if (u == v) return u;\r\n    return link(u, v);\r\n  }\r\n\r\n  int get_component_size(int\
    \ u) { return sz_[find(u)]; }\r\n\r\nprivate:\r\n  std::vector<int> p_, sz_;\r\
    \n  int link(int u, int v) {\r\n    if (sz_[u] > sz_[v]) return link(v, u);\r\n\
    \    // u \u662F\u5C0F\u6811\uFF0C v \u662F\u5927\u6811\uFF0C\u628A\u5C0F\u6811\
    \u63A5\u5230\u5927\u6811\u4E0A\r\n    sz_[v] += sz_[u];\r\n    // sz_[u] = 0;\r\
    \n    return p_[u] = v;\r\n  }\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef DISJOINT_SET_HEADER_HPP\r\n#define DISJOINT_SET_HEADER_HPP\r\n\r\n\
    /**\r\n * @brief disjoint set / \u5E76\u67E5\u96C6\r\n *\r\n */\r\n\r\n#include\
    \ <vector>\r\n\r\nnamespace lib {\r\n\r\nclass DisjointSet {\r\npublic:\r\n  DisjointSet()\
    \ = default;\r\n  DisjointSet(int n) : p_(n + 1), sz_(n + 1, 1) {\r\n    for (int\
    \ i = 0; i <= n; ++i) p_[i] = i;\r\n  }\r\n  ~DisjointSet() = default;\r\n\r\n\
    \  void make_set(int n) {\r\n    p_.resize(n + 1);\r\n    sz_.assign(n + 1, 1);\r\
    \n    for (int i = 0; i <= n; ++i) p_[i] = i;\r\n  }\r\n\r\n  int find(int u)\
    \ { // path havling\r\n    while (p_[u] != p_[p_[u]]) u = p_[u] = p_[p_[u]];\r\
    \n    return p_[u];\r\n  }\r\n\r\n  bool same(int u, int v) { return find(u) ==\
    \ find(v); }\r\n\r\n  int unite(int u, int v) {\r\n    u = find(u), v = find(v);\r\
    \n    if (u == v) return u;\r\n    return link(u, v);\r\n  }\r\n\r\n  int get_component_size(int\
    \ u) { return sz_[find(u)]; }\r\n\r\nprivate:\r\n  std::vector<int> p_, sz_;\r\
    \n  int link(int u, int v) {\r\n    if (sz_[u] > sz_[v]) return link(v, u);\r\n\
    \    // u \u662F\u5C0F\u6811\uFF0C v \u662F\u5927\u6811\uFF0C\u628A\u5C0F\u6811\
    \u63A5\u5230\u5927\u6811\u4E0A\r\n    sz_[v] += sz_[u];\r\n    // sz_[u] = 0;\r\
    \n    return p_[u] = v;\r\n  }\r\n};\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/basic/disjoint_set.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/datastructure/union_find.0.test.cpp
documentation_of: datastructure/basic/disjoint_set.hpp
layout: document
redirect_from:
- /library/datastructure/basic/disjoint_set.hpp
- /library/datastructure/basic/disjoint_set.hpp.html
title: "disjoint set / \u5E76\u67E5\u96C6"
---
