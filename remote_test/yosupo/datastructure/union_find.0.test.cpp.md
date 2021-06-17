---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/basic/disjoint_set.hpp
    title: "disjoint set / \u5E76\u67E5\u96C6"
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
    datastructure/basic/disjoint_set.hpp\"\n\n\n\n/**\n * @brief disjoint set / \u5E76\
    \u67E5\u96C6\n *\n */\n\n#include <vector>\n\nnamespace lib {\n\nclass DisjointSet\
    \ {\npublic:\n  DisjointSet() = default;\n  DisjointSet(int n) : p_(n + 1), sz_(n\
    \ + 1, 1) {\n    for (int i = 0; i <= n; ++i) p_[i] = i;\n  }\n  ~DisjointSet()\
    \ = default;\n\n  void make_set(int n) {\n    p_.resize(n + 1);\n    sz_.assign(n\
    \ + 1, 1);\n    for (int i = 0; i <= n; ++i) p_[i] = i;\n  }\n\n  int find(int\
    \ u) { // path havling\n    while (p_[u] != p_[p_[u]]) u = p_[u] = p_[p_[u]];\n\
    \    return p_[u];\n  }\n\n  bool same(int u, int v) { return find(u) == find(v);\
    \ }\n\n  int unite(int u, int v) {\n    u = find(u), v = find(v);\n    if (u ==\
    \ v) return u;\n    return link(u, v);\n  }\n\n  int get_component_size(int u)\
    \ { return sz_[find(u)]; }\n\nprivate:\n  std::vector<int> p_, sz_;\n  int link(int\
    \ u, int v) {\n    if (sz_[u] > sz_[v]) return link(v, u);\n    // u \u662F\u5C0F\
    \u6811\uFF0C v \u662F\u5927\u6811\uFF0C\u628A\u5C0F\u6811\u63A5\u5230\u5927\u6811\
    \u4E0A\n    sz_[v] += sz_[u];\n    // sz_[u] = 0;\n    return p_[u] = v;\n  }\n\
    };\n\n} // namespace lib\n\n\n#line 4 \"remote_test/yosupo/datastructure/union_find.0.test.cpp\"\
    \n\n#include <iostream>\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\",\
    \ \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(0);\n  int n, q;\n  std::cin >> n >> q;\n  lib::DisjointSet ds(n);\n\
    \  while (q--) {\n    int cmd, u, v;\n    std::cin >> cmd >> u >> v;\n    if (cmd\
    \ == 0) {\n      ds.unite(u, v);\n    } else {\n      std::cout << int(ds.same(u,\
    \ v)) << '\\n';\n    }\n  }\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ \"datastructure/basic/disjoint_set.hpp\"\n\n#include <iostream>\n\nint main()\
    \ {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\"\
    , \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, q;\n  std::cin >> n >> q;\n  lib::DisjointSet ds(n);\n  while (q--)\
    \ {\n    int cmd, u, v;\n    std::cin >> cmd >> u >> v;\n    if (cmd == 0) {\n\
    \      ds.unite(u, v);\n    } else {\n      std::cout << int(ds.same(u, v)) <<\
    \ '\\n';\n    }\n  }\n  return 0;\n}"
  dependsOn:
  - datastructure/basic/disjoint_set.hpp
  isVerificationFile: true
  path: remote_test/yosupo/datastructure/union_find.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-17 19:06:03+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/datastructure/union_find.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/datastructure/union_find.0.test.cpp
- /verify/remote_test/yosupo/datastructure/union_find.0.test.cpp.html
title: remote_test/yosupo/datastructure/union_find.0.test.cpp
---
