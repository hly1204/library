---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: datastructure/disjoint_set.hpp
    title: Disjoint Set
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"remote_test/yosupo/datastructure/union_find.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#line 1 \"\
    datastructure/disjoint_set.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\n\n#define\
    \ LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n#define LIB\
    \ ::lib::\n\n\n#line 5 \"datastructure/disjoint_set.hpp\"\n\n#include <numeric>\n\
    #include <vector>\n\nLIB_BEGIN\n\nclass disjoint_set {\n  mutable std::vector<int>\
    \ p_{}; // parent\n  std::vector<int> s_{};         // size\n\npublic:\n  disjoint_set()\
    \ {}\n  explicit disjoint_set(int n) : p_(n), s_(n, 1) { std::iota(p_.begin(),\
    \ p_.end(), 0); }\n  void make_set(int n) {\n    p_.resize(n);\n    s_.assign(n,\
    \ 1);\n    std::iota(p_.begin(), p_.end(), 0);\n  }\n  int find(int u) const {\n\
    \    // path havling\n    while (p_[u] != p_[p_[u]]) u = p_[u] = p_[p_[u]];\n\
    \    return p_[u];\n  }\n  bool is_same(int u, int v) const { return find(u) ==\
    \ find(v); }\n  int unite(int u, int v) {\n    u = find(u), v = find(v);\n   \
    \ if (u == v) return u;\n    if (s_[u] < s_[v]) {\n      s_[v] += s_[u];\n   \
    \   return p_[u] = v;\n    } else {\n      s_[u] += s_[v];\n      return p_[v]\
    \ = u;\n    }\n  }\n  int get_component_size(int u) const { return s_[find(u)];\
    \ }\n};\n\nLIB_END\n\n\n#line 4 \"remote_test/yosupo/datastructure/union_find.0.test.cpp\"\
    \n\n#include <iostream>\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\",\
    \ \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(nullptr);\n  int n, q;\n  std::cin >> n >> q;\n  lib::disjoint_set\
    \ ds(n);\n  while (q--) {\n    int cmd, u, v;\n    std::cin >> cmd >> u >> v;\n\
    \    if (cmd == 0) {\n      ds.unite(u, v);\n    } else {\n      std::cout <<\
    \ static_cast<int>(ds.is_same(u, v)) << '\\n';\n    }\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ \"datastructure/disjoint_set.hpp\"\n\n#include <iostream>\n\nint main() {\n\
    #ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\", \"w\"\
    , stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  int n, q;\n  std::cin >> n >> q;\n  lib::disjoint_set ds(n);\n  while (q--)\
    \ {\n    int cmd, u, v;\n    std::cin >> cmd >> u >> v;\n    if (cmd == 0) {\n\
    \      ds.unite(u, v);\n    } else {\n      std::cout << static_cast<int>(ds.is_same(u,\
    \ v)) << '\\n';\n    }\n  }\n  return 0;\n}"
  dependsOn:
  - datastructure/disjoint_set.hpp
  - common.hpp
  isVerificationFile: true
  path: remote_test/yosupo/datastructure/union_find.0.test.cpp
  requiredBy: []
  timestamp: '2022-04-23 15:43:11+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/datastructure/union_find.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/datastructure/union_find.0.test.cpp
- /verify/remote_test/yosupo/datastructure/union_find.0.test.cpp.html
title: remote_test/yosupo/datastructure/union_find.0.test.cpp
---
