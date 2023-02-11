---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/aizu/datastructure/weighted_union_find.0.test.cpp
    title: remote_test/aizu/datastructure/weighted_union_find.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/weighted_disjoint_set.hpp\"\n\n\n\n#line 1\
    \ \"common.hpp\"\n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n\
    #define LIB_END }\n#define LIB ::lib::\n\n\n#line 5 \"datastructure/weighted_disjoint_set.hpp\"\
    \n\n#include <numeric>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \nLIB_BEGIN\n\ntemplate <typename TypeT>\nclass weighted_disjoint_set {\n  //\
    \ assume `TypeT`(a) + `TypeT`(b) = `TypeT`(b) + `TypeT`(a).\n  mutable std::vector<int>\
    \ p_{};   // parent\n  std::vector<int> s_{};           // size\n  mutable std::vector<TypeT>\
    \ d_{}; // difference\n\n  std::pair<int, TypeT> find_pair(int u) const {\n  \
    \  TypeT d = d_[u];\n    while (p_[u] != p_[p_[u]]) {\n      d_[u] += d_[p_[u]];\n\
    \      d += d_[p_[u]];\n      d += d_[u = p_[u] = p_[p_[u]]];\n    }\n    return\
    \ std::make_pair(p_[u], d);\n  }\n\npublic:\n  weighted_disjoint_set() {}\n  explicit\
    \ weighted_disjoint_set(int n) : p_(n), s_(n, 1), d_(n) {\n    std::iota(p_.begin(),\
    \ p_.end(), 0);\n  }\n  void make_set(int n) {\n    p_.resize(n);\n    s_.assign(n,\
    \ 1);\n    d_.assign(n, TypeT());\n    std::iota(p_.begin(), p_.end(), 0);\n \
    \ }\n  int find(int u) const { return find_pair(u).first; }\n  bool relate(int\
    \ u, int v, TypeT w) {\n    // let val(v) - val(u) = w.\n    auto [uf, ud] = find_pair(u);\n\
    \    auto [vf, vd] = find_pair(v);\n    if (uf == vf) return vd - ud == w;\n \
    \   if (s_[uf] < s_[vf]) {\n      s_[p_[uf] = vf] += s_[uf];\n      d_[uf] = vd\
    \ - ud - w;\n    } else {\n      s_[p_[vf] = uf] += s_[vf];\n      d_[vf] = ud\
    \ - vd + w;\n    }\n    return true;\n  }\n  bool is_related(int u, int v) const\
    \ { return find(u) == find(v); }\n  bool is_related(int u, int v, TypeT w) const\
    \ {\n    auto [uf, ud] = find_pair(u);\n    auto [vf, vd] = find_pair(v);\n  \
    \  return uf == vf && vd - ud == w;\n  }\n  // returns val(v) - val(u).\n  std::optional<TypeT>\
    \ diff(int u, int v) const {\n    auto [uf, ud] = find_pair(u);\n    auto [vf,\
    \ vd] = find_pair(v);\n    return uf == vf ? std::make_optional<TypeT>(vd - ud)\
    \ : std::optional<TypeT>();\n  }\n  int get_component_size(int u) const { return\
    \ s_[find(u)]; }\n};\n\nLIB_END\n\n\n"
  code: "#ifndef WEIGHTED_DISJOINT_SET_HPP\n#define WEIGHTED_DISJOINT_SET_HPP\n\n\
    #include \"../common.hpp\"\n\n#include <numeric>\n#include <optional>\n#include\
    \ <utility>\n#include <vector>\n\nLIB_BEGIN\n\ntemplate <typename TypeT>\nclass\
    \ weighted_disjoint_set {\n  // assume `TypeT`(a) + `TypeT`(b) = `TypeT`(b) +\
    \ `TypeT`(a).\n  mutable std::vector<int> p_{};   // parent\n  std::vector<int>\
    \ s_{};           // size\n  mutable std::vector<TypeT> d_{}; // difference\n\n\
    \  std::pair<int, TypeT> find_pair(int u) const {\n    TypeT d = d_[u];\n    while\
    \ (p_[u] != p_[p_[u]]) {\n      d_[u] += d_[p_[u]];\n      d += d_[p_[u]];\n \
    \     d += d_[u = p_[u] = p_[p_[u]]];\n    }\n    return std::make_pair(p_[u],\
    \ d);\n  }\n\npublic:\n  weighted_disjoint_set() {}\n  explicit weighted_disjoint_set(int\
    \ n) : p_(n), s_(n, 1), d_(n) {\n    std::iota(p_.begin(), p_.end(), 0);\n  }\n\
    \  void make_set(int n) {\n    p_.resize(n);\n    s_.assign(n, 1);\n    d_.assign(n,\
    \ TypeT());\n    std::iota(p_.begin(), p_.end(), 0);\n  }\n  int find(int u) const\
    \ { return find_pair(u).first; }\n  bool relate(int u, int v, TypeT w) {\n   \
    \ // let val(v) - val(u) = w.\n    auto [uf, ud] = find_pair(u);\n    auto [vf,\
    \ vd] = find_pair(v);\n    if (uf == vf) return vd - ud == w;\n    if (s_[uf]\
    \ < s_[vf]) {\n      s_[p_[uf] = vf] += s_[uf];\n      d_[uf] = vd - ud - w;\n\
    \    } else {\n      s_[p_[vf] = uf] += s_[vf];\n      d_[vf] = ud - vd + w;\n\
    \    }\n    return true;\n  }\n  bool is_related(int u, int v) const { return\
    \ find(u) == find(v); }\n  bool is_related(int u, int v, TypeT w) const {\n  \
    \  auto [uf, ud] = find_pair(u);\n    auto [vf, vd] = find_pair(v);\n    return\
    \ uf == vf && vd - ud == w;\n  }\n  // returns val(v) - val(u).\n  std::optional<TypeT>\
    \ diff(int u, int v) const {\n    auto [uf, ud] = find_pair(u);\n    auto [vf,\
    \ vd] = find_pair(v);\n    return uf == vf ? std::make_optional<TypeT>(vd - ud)\
    \ : std::optional<TypeT>();\n  }\n  int get_component_size(int u) const { return\
    \ s_[find(u)]; }\n};\n\nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: datastructure/weighted_disjoint_set.hpp
  requiredBy: []
  timestamp: '2022-04-23 15:43:11+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/aizu/datastructure/weighted_union_find.0.test.cpp
documentation_of: datastructure/weighted_disjoint_set.hpp
layout: document
title: Weighted Disjoint Set (Abelian)
---
