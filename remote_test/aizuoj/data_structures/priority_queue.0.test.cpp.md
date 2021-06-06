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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C
    links:
    - https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C
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
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/courses/lesson/1/ALDS1/all/ALDS1_9_C\"\
    \n\n#include <iostream>\n\n#include \"datastructure/heap/priority_queue.hpp\"\n\
    \nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  auto cmp = [](long long a, long long b) -> bool { return a > b; };\n  lib::PriorityQueue<long\
    \ long, decltype(cmp)> pq(cmp);\n  char cmd[10];\n  while (std::cin >> cmd &&\
    \ cmd[2] != 'd') {\n    if (cmd[0] == 'i') {\n      long long v;\n      std::cin\
    \ >> v;\n      pq.insert(v);\n    } else {\n      std::cout << pq.find_min() <<\
    \ '\\n';\n      pq.delete_min();\n    }\n  }\n  return 0;\n}"
  dependsOn:
  - datastructure/heap/priority_queue.hpp
  - datastructure/heap/pairing_heap.hpp
  isVerificationFile: true
  path: remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
- /verify/remote_test/aizuoj/data_structures/priority_queue.0.test.cpp.html
title: remote_test/aizuoj/data_structures/priority_queue.0.test.cpp
---
