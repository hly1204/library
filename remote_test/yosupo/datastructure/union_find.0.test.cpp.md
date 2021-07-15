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
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\r\n\r\n#line 1\
    \ \"datastructure/basic/disjoint_set.hpp\"\n\n\n\r\n/**\r\n * @brief disjoint\
    \ set / \u5E76\u67E5\u96C6\r\n *\r\n */\r\n\r\n#include <vector>\r\n\r\nnamespace\
    \ lib {\r\n\r\nclass DisjointSet {\r\npublic:\r\n  DisjointSet() = default;\r\n\
    \  DisjointSet(int n) : p_(n + 1), sz_(n + 1, 1) {\r\n    for (int i = 0; i <=\
    \ n; ++i) p_[i] = i;\r\n  }\r\n  ~DisjointSet() = default;\r\n\r\n  void make_set(int\
    \ n) {\r\n    p_.resize(n + 1);\r\n    sz_.assign(n + 1, 1);\r\n    for (int i\
    \ = 0; i <= n; ++i) p_[i] = i;\r\n  }\r\n\r\n  int find(int u) { // path havling\r\
    \n    while (p_[u] != p_[p_[u]]) u = p_[u] = p_[p_[u]];\r\n    return p_[u];\r\
    \n  }\r\n\r\n  bool same(int u, int v) { return find(u) == find(v); }\r\n\r\n\
    \  int unite(int u, int v) {\r\n    u = find(u), v = find(v);\r\n    if (u ==\
    \ v) return u;\r\n    return link(u, v);\r\n  }\r\n\r\n  int get_component_size(int\
    \ u) { return sz_[find(u)]; }\r\n\r\nprivate:\r\n  std::vector<int> p_, sz_;\r\
    \n  int link(int u, int v) {\r\n    if (sz_[u] > sz_[v]) return link(v, u);\r\n\
    \    // u \u662F\u5C0F\u6811\uFF0C v \u662F\u5927\u6811\uFF0C\u628A\u5C0F\u6811\
    \u63A5\u5230\u5927\u6811\u4E0A\r\n    sz_[v] += sz_[u];\r\n    // sz_[u] = 0;\r\
    \n    return p_[u] = v;\r\n  }\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line\
    \ 4 \"remote_test/yosupo/datastructure/union_find.0.test.cpp\"\n\r\n#include <iostream>\r\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int n, q;\r\n  std::cin >> n >> q;\r\n  lib::DisjointSet ds(n);\r\n  while\
    \ (q--) {\r\n    int cmd, u, v;\r\n    std::cin >> cmd >> u >> v;\r\n    if (cmd\
    \ == 0) {\r\n      ds.unite(u, v);\r\n    } else {\r\n      std::cout << int(ds.same(u,\
    \ v)) << '\\n';\r\n    }\r\n  }\r\n  return 0;\r\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\r\n\r\n#include\
    \ \"datastructure/basic/disjoint_set.hpp\"\r\n\r\n#include <iostream>\r\n\r\n\
    int main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  int n, q;\r\n  std::cin >> n >> q;\r\n  lib::DisjointSet ds(n);\r\n  while\
    \ (q--) {\r\n    int cmd, u, v;\r\n    std::cin >> cmd >> u >> v;\r\n    if (cmd\
    \ == 0) {\r\n      ds.unite(u, v);\r\n    } else {\r\n      std::cout << int(ds.same(u,\
    \ v)) << '\\n';\r\n    }\r\n  }\r\n  return 0;\r\n}"
  dependsOn:
  - datastructure/basic/disjoint_set.hpp
  isVerificationFile: true
  path: remote_test/yosupo/datastructure/union_find.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/datastructure/union_find.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/datastructure/union_find.0.test.cpp
- /verify/remote_test/yosupo/datastructure/union_find.0.test.cpp.html
title: remote_test/yosupo/datastructure/union_find.0.test.cpp
---
