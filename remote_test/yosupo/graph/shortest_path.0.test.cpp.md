---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/heap/pairing_heap.hpp
    title: "pairing heap / \u914D\u5BF9\u5806"
  - icon: ':heavy_check_mark:'
    path: datastructure/heap/priority_queue.hpp
    title: "priority queue / \u4F18\u5148\u961F\u5217"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/shortest_path
    links:
    - https://judge.yosupo.jp/problem/shortest_path
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ datastructure/heap/priority_queue.hpp: line 11: unable to process #include in\
    \ #if / #ifdef / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/shortest_path\"\n\n#include\
    \ <iostream>\n#include <limits>\n#include <vector>\n\n#include \"datastructure/heap/priority_queue.hpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int n, m, s, t;\n  std::cin >> n >> m >> s >> t;\n  std::vector<std::vector<std::pair<int,\
    \ int>>> g(n);\n  while (m--) {\n    int a, b, c;\n    std::cin >> a >> b >> c;\n\
    \    g[a].push_back({b, c});\n  }\n  const long long INF = std::numeric_limits<long\
    \ long>::max();\n  std::vector<long long> dist(n, INF);\n  std::vector<int> pred(n,\
    \ -1);\n  auto cmp = [&dist](int x, int y) -> bool { return dist[x] < dist[y];\
    \ };\n  lib::PriorityQueue<int, decltype(cmp)> pq(cmp);\n  std::vector<lib::PriorityQueue<int,\
    \ decltype(cmp)>::const_node_ptr_type> box(n);\n  dist[s] = 0;\n  pq.insert(s);\n\
    \  while (!pq.is_empty()) {\n    auto x = pq.find_min();\n    pq.delete_min();\n\
    \    auto dx = dist[x];\n    for (auto &i : g[x]) {\n      int j = i.first;\n\
    \      if (dist[j] > dx + i.second) {\n        if (dist[j] == INF) {\n       \
    \   dist[j] = dx + i.second;\n          box[j] = pq.insert(j);\n        } else\
    \ {\n          dist[j] = dx + i.second;\n          pq.decrease_key(box[j], j);\n\
    \        }\n        pred[j] = x;\n      }\n    }\n  }\n  if (pred[t] == -1) {\n\
    \    std::cout << -1 << '\\n';\n  } else {\n    std::vector<std::pair<int, int>>\
    \ path;\n    int prev = -1;\n    int end = t;\n    while (prev != s) {\n     \
    \ path.push_back({prev = pred[end], end});\n      end = pred[end];\n    }\n  \
    \  std::reverse(path.begin(), path.end());\n    std::cout << dist[t] << ' ' <<\
    \ path.size() << '\\n';\n    for (auto &i : path) std::cout << i.first << ' '\
    \ << i.second << '\\n';\n  }\n  return 0;\n}"
  dependsOn:
  - datastructure/heap/priority_queue.hpp
  - datastructure/heap/pairing_heap.hpp
  isVerificationFile: true
  path: remote_test/yosupo/graph/shortest_path.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/graph/shortest_path.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/graph/shortest_path.0.test.cpp
- /verify/remote_test/yosupo/graph/shortest_path.0.test.cpp.html
title: remote_test/yosupo/graph/shortest_path.0.test.cpp
---
