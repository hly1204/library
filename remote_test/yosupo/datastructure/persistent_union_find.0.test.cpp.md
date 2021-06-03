---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/basic/rollbackable_disjoint_set.hpp
    title: datastructure/basic/rollbackable_disjoint_set.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/persistent_unionfind
    links:
    - https://judge.yosupo.jp/problem/persistent_unionfind
  bundledCode: "#line 1 \"remote_test/yosupo/datastructure/persistent_union_find.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\n\
    #include <functional>\n#include <iostream>\n#include <vector>\n\n#line 1 \"datastructure/basic/rollbackable_disjoint_set.hpp\"\
    \n\n\n\n#include <stack>\n#line 6 \"datastructure/basic/rollbackable_disjoint_set.hpp\"\
    \n\nnamespace lib {\n\n// \u4E3A\u4E86\u65B9\u4FBF\u8FD9\u91CC\u8BBE\u7F6E\u4E3A\
    \ [0,n+1] \u90FD\u662F\u7F16\u53F7\nclass RollbackableDisjointSet {\npublic:\n\
    \  RollbackableDisjointSet() {}\n  RollbackableDisjointSet(int n) : p_(n + 1),\
    \ sz_(n + 1, 1) {\n    for (int i = 0; i <= n; ++i) p_[i] = i;\n  }\n  ~RollbackableDisjointSet()\
    \ = default;\n\n  void make_set(int n) {\n    p_.resize(n + 1);\n    sz_.assign(n\
    \ + 1, 1);\n    while (!stk_.empty()) stk_.pop();\n    for (int i = 0; i <= n;\
    \ ++i) p_[i] = i;\n  }\n\n  int find(int u) const {\n    while (u != p_[u]) u\
    \ = p_[u];\n    return u;\n  }\n\n  bool same(int u, int v) const { return find(u)\
    \ == find(v); }\n\n  int unite(int u, int v) {\n    u = find(u), v = find(v);\n\
    \    if (u == v) return u;\n    return link(u, v);\n  }\n\n  int get_component_size(int\
    \ u) const { return sz_[find(u)]; }\n\n  void undo() {\n    // \u53EA\u80FD undo\
    \ \u6210\u529F\u7684 unite \u5982\u679C\u4E0D\u6210\u529F\u662F\u4E0D\u80FD undo\
    \ \u7684\n    // \u53D6\u51FA\u5C0F\u6811\uFF0C\u4FEE\u6539\u5C0F\u6811\u7684\
    \ parent\n    int u = stk_.top();\n    stk_.pop();\n    sz_[p_[u]] -= sz_[u];\n\
    \    p_[u] = u;\n  }\n\n  void rollback(int k) {\n    while (k--) undo();\n  }\n\
    \nprivate:\n  std::vector<int> p_, sz_;\n  std::stack<int, std::vector<int>> stk_;\n\
    \n  int link(int u, int v) {\n    if (sz_[u] > sz_[v]) return link(v, u);\n  \
    \  // u \u662F\u5C0F\u6811\uFF0C v \u662F\u5927\u6811\uFF0C\u628A\u5C0F\u6811\u63A5\
    \u5230\u5927\u6811\u4E0A\n    sz_[v] += sz_[u];\n    stk_.push(u); // \u5C06\u5C0F\
    \u6811\u653E\u5165\u6808\u4E2D\n    return p_[u] = v;\n  }\n};\n\n} // namespace\
    \ lib\n\n\n#line 8 \"remote_test/yosupo/datastructure/persistent_union_find.0.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, q;\n  std::cin >> n >> q;\n  std::vector<std::tuple<int, int, int>>\
    \ query(1);\n  std::vector<int> ans(q + 1, -1);\n  std::vector<std::vector<int>>\
    \ g;\n  g.resize(q + 1);\n  for (int i = 1; i <= q; ++i) {\n    int t, k, u, v;\n\
    \    std::cin >> t >> k >> u >> v;\n    ++k; // let k in [0, i]\n    query.push_back({t,\
    \ u, v});\n    g[k].push_back(i);\n  }\n  lib::RollbackableDisjointSet ds(n);\n\
    \  std::function<void(int)> dfs = [&](int s) {\n    auto [a, b, c] = query[s];\n\
    \    if (a == 1) {\n      ans[s] = int(ds.same(b, c));\n    } else {\n      b\
    \ = ds.find(b);\n      c = ds.find(c);\n      bool flag = (b != c);\n      if\
    \ (flag) ds.unite(b, c);\n      for (auto i : g[s]) dfs(i);\n      if (flag) ds.undo();\n\
    \    }\n  };\n  for (auto i : g[0]) dfs(i);\n  for (auto i : ans)\n    if (i !=\
    \ -1) std::cout << i << '\\n';\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/persistent_unionfind\"\n\
    \n#include <functional>\n#include <iostream>\n#include <vector>\n\n#include \"\
    datastructure/basic/rollbackable_disjoint_set.hpp\"\n\nint main() {\n#ifdef LOCAL\n\
    \  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n\
    #endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n  int n, q;\n\
    \  std::cin >> n >> q;\n  std::vector<std::tuple<int, int, int>> query(1);\n \
    \ std::vector<int> ans(q + 1, -1);\n  std::vector<std::vector<int>> g;\n  g.resize(q\
    \ + 1);\n  for (int i = 1; i <= q; ++i) {\n    int t, k, u, v;\n    std::cin >>\
    \ t >> k >> u >> v;\n    ++k; // let k in [0, i]\n    query.push_back({t, u, v});\n\
    \    g[k].push_back(i);\n  }\n  lib::RollbackableDisjointSet ds(n);\n  std::function<void(int)>\
    \ dfs = [&](int s) {\n    auto [a, b, c] = query[s];\n    if (a == 1) {\n    \
    \  ans[s] = int(ds.same(b, c));\n    } else {\n      b = ds.find(b);\n      c\
    \ = ds.find(c);\n      bool flag = (b != c);\n      if (flag) ds.unite(b, c);\n\
    \      for (auto i : g[s]) dfs(i);\n      if (flag) ds.undo();\n    }\n  };\n\
    \  for (auto i : g[0]) dfs(i);\n  for (auto i : ans)\n    if (i != -1) std::cout\
    \ << i << '\\n';\n  return 0;\n}"
  dependsOn:
  - datastructure/basic/rollbackable_disjoint_set.hpp
  isVerificationFile: true
  path: remote_test/yosupo/datastructure/persistent_union_find.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-03 15:01:19+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/datastructure/persistent_union_find.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/datastructure/persistent_union_find.0.test.cpp
- /verify/remote_test/yosupo/datastructure/persistent_union_find.0.test.cpp.html
title: remote_test/yosupo/datastructure/persistent_union_find.0.test.cpp
---
