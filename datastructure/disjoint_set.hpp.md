---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/datastructure/union_find.0.test.cpp
    title: remote_test/yosupo/datastructure/union_find.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/disjoint_set.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
    \n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 5 \"datastructure/disjoint_set.hpp\"\n\n#include\
    \ <numeric>\n#include <vector>\n\nLIB_BEGIN\n\nclass disjoint_set {\n  mutable\
    \ std::vector<int> p_{}; // parent\n  std::vector<int> s_{};         // size\n\
    \npublic:\n  disjoint_set() {}\n  explicit disjoint_set(int n) : p_(n), s_(n,\
    \ 1) { std::iota(p_.begin(), p_.end(), 0); }\n  void make_set(int n) {\n    p_.resize(n);\n\
    \    s_.assign(n, 1);\n    std::iota(p_.begin(), p_.end(), 0);\n  }\n  int find(int\
    \ u) const {\n    // path havling\n    while (p_[u] != p_[p_[u]]) u = p_[u] =\
    \ p_[p_[u]];\n    return p_[u];\n  }\n  bool is_same(int u, int v) const { return\
    \ find(u) == find(v); }\n  int unite(int u, int v) {\n    u = find(u), v = find(v);\n\
    \    if (u == v) return u;\n    if (s_[u] < s_[v]) {\n      s_[v] += s_[u];\n\
    \      return p_[u] = v;\n    } else {\n      s_[u] += s_[v];\n      return p_[v]\
    \ = u;\n    }\n  }\n  int get_component_size(int u) const { return s_[find(u)];\
    \ }\n};\n\nLIB_END\n\n\n"
  code: "#ifndef DISJOINT_SET_HPP\n#define DISJOINT_SET_HPP\n\n#include \"../common.hpp\"\
    \n\n#include <numeric>\n#include <vector>\n\nLIB_BEGIN\n\nclass disjoint_set {\n\
    \  mutable std::vector<int> p_{}; // parent\n  std::vector<int> s_{};        \
    \ // size\n\npublic:\n  disjoint_set() {}\n  explicit disjoint_set(int n) : p_(n),\
    \ s_(n, 1) { std::iota(p_.begin(), p_.end(), 0); }\n  void make_set(int n) {\n\
    \    p_.resize(n);\n    s_.assign(n, 1);\n    std::iota(p_.begin(), p_.end(),\
    \ 0);\n  }\n  int find(int u) const {\n    // path havling\n    while (p_[u] !=\
    \ p_[p_[u]]) u = p_[u] = p_[p_[u]];\n    return p_[u];\n  }\n  bool is_same(int\
    \ u, int v) const { return find(u) == find(v); }\n  int unite(int u, int v) {\n\
    \    u = find(u), v = find(v);\n    if (u == v) return u;\n    if (s_[u] < s_[v])\
    \ {\n      s_[v] += s_[u];\n      return p_[u] = v;\n    } else {\n      s_[u]\
    \ += s_[v];\n      return p_[v] = u;\n    }\n  }\n  int get_component_size(int\
    \ u) const { return s_[find(u)]; }\n};\n\nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: datastructure/disjoint_set.hpp
  requiredBy: []
  timestamp: '2022-04-23 15:43:11+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/datastructure/union_find.0.test.cpp
documentation_of: datastructure/disjoint_set.hpp
layout: document
title: Disjoint Set
---
