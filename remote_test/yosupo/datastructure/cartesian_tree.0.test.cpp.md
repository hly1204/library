---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: datastructure/cartesian_tree.hpp
    title: Cartesian Tree
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/cartesian_tree
    links:
    - https://judge.yosupo.jp/problem/cartesian_tree
  bundledCode: "#line 1 \"remote_test/yosupo/datastructure/cartesian_tree.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n\n#line\
    \ 1 \"datastructure/cartesian_tree.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\n\n\
    #define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n#define\
    \ LIB ::lib::\n\n\n#line 5 \"datastructure/cartesian_tree.hpp\"\n\n#include <functional>\n\
    #include <stack>\n#include <tuple>\n#include <vector>\n\nLIB_BEGIN\n\ntemplate\
    \ <typename ContainerT, typename CmpT = std::less<>>\nstd::tuple<std::vector<int>,\
    \ std::vector<int>, std::vector<int>>\nbuild_cartesian_tree(ContainerT &&a) {\n\
    \  int n = static_cast<int>(a.size());\n  CmpT cmp;\n  std::vector<int> l(n, -1),\
    \ r(n, -1), p(n, -1);\n  std::stack<int, std::vector<int>> s;\n  for (int i =\
    \ 0; i != n; ++i) {\n    int last_poped = -1;\n    while (!s.empty() && cmp(a[i],\
    \ a[s.top()])) last_poped = s.top(), s.pop();\n    if (last_poped != -1) p[l[i]\
    \ = last_poped] = i;\n    if (!s.empty()) r[p[i] = s.top()] = i;\n    s.push(i);\n\
    \  }\n  return {l, r, p};\n}\n\nLIB_END\n\n\n#line 4 \"remote_test/yosupo/datastructure/cartesian_tree.0.test.cpp\"\
    \n\n#include <iostream>\n#line 8 \"remote_test/yosupo/datastructure/cartesian_tree.0.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  int n;\n  std::cin >> n;\n  std::vector<int> a(n);\n  for (auto &&i : a) std::cin\
    \ >> i;\n  std::tie(std::ignore, std::ignore, a) = lib::build_cartesian_tree(a);\n\
    \  for (int i = 0; i != n; ++i) std::cout << (a[i] == -1 ? i : a[i]) << ' ';\n\
    \  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/cartesian_tree\"\n\n#include\
    \ \"datastructure/cartesian_tree.hpp\"\n\n#include <iostream>\n#include <tuple>\n\
    #include <vector>\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\"\
    , stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(nullptr);\n  int n;\n  std::cin >> n;\n  std::vector<int> a(n);\n\
    \  for (auto &&i : a) std::cin >> i;\n  std::tie(std::ignore, std::ignore, a)\
    \ = lib::build_cartesian_tree(a);\n  for (int i = 0; i != n; ++i) std::cout <<\
    \ (a[i] == -1 ? i : a[i]) << ' ';\n  return 0;\n}"
  dependsOn:
  - datastructure/cartesian_tree.hpp
  - common.hpp
  isVerificationFile: true
  path: remote_test/yosupo/datastructure/cartesian_tree.0.test.cpp
  requiredBy: []
  timestamp: '2022-05-02 00:19:44+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/datastructure/cartesian_tree.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/datastructure/cartesian_tree.0.test.cpp
- /verify/remote_test/yosupo/datastructure/cartesian_tree.0.test.cpp.html
title: remote_test/yosupo/datastructure/cartesian_tree.0.test.cpp
---
