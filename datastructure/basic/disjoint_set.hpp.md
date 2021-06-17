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
  bundledCode: "#line 1 \"datastructure/basic/disjoint_set.hpp\"\n\n\n\n/**\n * @brief\
    \ disjoint set / \u5E76\u67E5\u96C6\n *\n */\n\n#include <vector>\n\nnamespace\
    \ lib {\n\nclass DisjointSet {\npublic:\n  DisjointSet() = default;\n  DisjointSet(int\
    \ n) : p_(n + 1), sz_(n + 1, 1) {\n    for (int i = 0; i <= n; ++i) p_[i] = i;\n\
    \  }\n  ~DisjointSet() = default;\n\n  void make_set(int n) {\n    p_.resize(n\
    \ + 1);\n    sz_.assign(n + 1, 1);\n    for (int i = 0; i <= n; ++i) p_[i] = i;\n\
    \  }\n\n  int find(int u) { // path havling\n    while (p_[u] != p_[p_[u]]) u\
    \ = p_[u] = p_[p_[u]];\n    return p_[u];\n  }\n\n  bool same(int u, int v) {\
    \ return find(u) == find(v); }\n\n  int unite(int u, int v) {\n    u = find(u),\
    \ v = find(v);\n    if (u == v) return u;\n    return link(u, v);\n  }\n\n  int\
    \ get_component_size(int u) { return sz_[find(u)]; }\n\nprivate:\n  std::vector<int>\
    \ p_, sz_;\n  int link(int u, int v) {\n    if (sz_[u] > sz_[v]) return link(v,\
    \ u);\n    // u \u662F\u5C0F\u6811\uFF0C v \u662F\u5927\u6811\uFF0C\u628A\u5C0F\
    \u6811\u63A5\u5230\u5927\u6811\u4E0A\n    sz_[v] += sz_[u];\n    // sz_[u] = 0;\n\
    \    return p_[u] = v;\n  }\n};\n\n} // namespace lib\n\n\n"
  code: "#ifndef DISJOINT_SET_HEADER_HPP\n#define DISJOINT_SET_HEADER_HPP\n\n/**\n\
    \ * @brief disjoint set / \u5E76\u67E5\u96C6\n *\n */\n\n#include <vector>\n\n\
    namespace lib {\n\nclass DisjointSet {\npublic:\n  DisjointSet() = default;\n\
    \  DisjointSet(int n) : p_(n + 1), sz_(n + 1, 1) {\n    for (int i = 0; i <= n;\
    \ ++i) p_[i] = i;\n  }\n  ~DisjointSet() = default;\n\n  void make_set(int n)\
    \ {\n    p_.resize(n + 1);\n    sz_.assign(n + 1, 1);\n    for (int i = 0; i <=\
    \ n; ++i) p_[i] = i;\n  }\n\n  int find(int u) { // path havling\n    while (p_[u]\
    \ != p_[p_[u]]) u = p_[u] = p_[p_[u]];\n    return p_[u];\n  }\n\n  bool same(int\
    \ u, int v) { return find(u) == find(v); }\n\n  int unite(int u, int v) {\n  \
    \  u = find(u), v = find(v);\n    if (u == v) return u;\n    return link(u, v);\n\
    \  }\n\n  int get_component_size(int u) { return sz_[find(u)]; }\n\nprivate:\n\
    \  std::vector<int> p_, sz_;\n  int link(int u, int v) {\n    if (sz_[u] > sz_[v])\
    \ return link(v, u);\n    // u \u662F\u5C0F\u6811\uFF0C v \u662F\u5927\u6811\uFF0C\
    \u628A\u5C0F\u6811\u63A5\u5230\u5927\u6811\u4E0A\n    sz_[v] += sz_[u];\n    //\
    \ sz_[u] = 0;\n    return p_[u] = v;\n  }\n};\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/basic/disjoint_set.hpp
  requiredBy: []
  timestamp: '2021-06-17 19:06:03+08:00'
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
