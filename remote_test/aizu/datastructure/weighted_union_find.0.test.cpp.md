---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: datastructure/weighted_disjoint_set.hpp
    title: Weighted Disjoint Set (Abelian)
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_B
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_B
  bundledCode: "#line 1 \"remote_test/aizu/datastructure/weighted_union_find.0.test.cpp\"\
    \n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_B\"\
    \n\n#line 1 \"datastructure/weighted_disjoint_set.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
    \n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 5 \"datastructure/weighted_disjoint_set.hpp\"\
    \n\n#include <numeric>\n#include <optional>\n#include <utility>\n#include <vector>\n\
    \nLIB_BEGIN\n\ntemplate <typename TypeT>\nclass weighted_disjoint_set {\n  //\
    \ assume `TypeT`(a) + `TypeT`(b) = `TypeT`(b) + `TypeT`(a).\n  mutable std::vector<int>\
    \ p_{};   // parent\n  std::vector<int> s_{};           // size\n  mutable std::vector<TypeT>\
    \ d_{}; // difference\n\n  std::pair<int, TypeT> find_pair(int u) const {\n  \
    \  TypeT d = d_[u];\n    while (p_[u] != p_[p_[u]]) {\n      d_[u] += d_[p_[u]];\n\
    \      d += d_[p_[u]];\n      d += d_[u = p_[u] = p_[p_[u]]];\n    }\n    return\
    \ std::make_pair(p_[u], d);\n  }\n\npublic:\n  weighted_disjoint_set() = default;\n\
    \  explicit weighted_disjoint_set(int n) : p_(n), s_(n, 1), d_(n) {\n    std::iota(p_.begin(),\
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
    \ s_[find(u)]; }\n};\n\nLIB_END\n\n\n#line 4 \"remote_test/aizu/datastructure/weighted_union_find.0.test.cpp\"\
    \n\n#include <iostream>\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\",\
    \ \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(nullptr);\n  int n, q;\n  std::cin >> n >> q;\n  lib::weighted_disjoint_set<int>\
    \ ds(n);\n  while (q--) {\n    int op, x, y, z;\n    std::cin >> op >> x >> y;\n\
    \    if (op == 0) {\n      std::cin >> z;\n      ds.relate(x, y, z);\n    } else\
    \ {\n      if (auto res = ds.diff(x, y)) {\n        std::cout << *res << '\\n';\n\
    \      } else {\n        std::cout << \"?\\n\";\n      }\n    }\n  }\n  return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/library/3/DSL/1/DSL_1_B\"\
    \n\n#include \"datastructure/weighted_disjoint_set.hpp\"\n\n#include <iostream>\n\
    \nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  int n, q;\n  std::cin >> n >> q;\n  lib::weighted_disjoint_set<int> ds(n);\n\
    \  while (q--) {\n    int op, x, y, z;\n    std::cin >> op >> x >> y;\n    if\
    \ (op == 0) {\n      std::cin >> z;\n      ds.relate(x, y, z);\n    } else {\n\
    \      if (auto res = ds.diff(x, y)) {\n        std::cout << *res << '\\n';\n\
    \      } else {\n        std::cout << \"?\\n\";\n      }\n    }\n  }\n  return\
    \ 0;\n}\n"
  dependsOn:
  - datastructure/weighted_disjoint_set.hpp
  - common.hpp
  isVerificationFile: true
  path: remote_test/aizu/datastructure/weighted_union_find.0.test.cpp
  requiredBy: []
  timestamp: '2023-08-05 09:04:07+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/aizu/datastructure/weighted_union_find.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/aizu/datastructure/weighted_union_find.0.test.cpp
- /verify/remote_test/aizu/datastructure/weighted_union_find.0.test.cpp.html
title: remote_test/aizu/datastructure/weighted_union_find.0.test.cpp
---
