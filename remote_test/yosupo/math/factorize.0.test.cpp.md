---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/basic/integer_factorization.hpp
    title: "integer factorization / \u6574\u6570\u5206\u89E3"
  - icon: ':heavy_check_mark:'
    path: modint/runtime_long_Montgomery_modint.hpp
    title: "runtime long Montgomery modint / \u8FD0\u884C\u65F6\u957F\u6574\u578B\
      \ Montgomery \u53D6\u6A21\u7C7B"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/factorize
    links:
    - https://judge.yosupo.jp/problem/factorize
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/basic/integer_factorization.hpp: line 14: unable to process #include in\
    \ #if / #ifdef / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/factorize\"\n\n#include\
    \ <iostream>\n\n#include \"math/basic/integer_factorization.hpp\"\n\nint main()\
    \ {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\"\
    , \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int Q;\n  std::cin >> Q;\n  while (Q--) {\n    long long a;\n    std::cin >>\
    \ a;\n    std::vector<long long> factor;\n    auto mp = lib::factorize(a);\n \
    \   for (auto i : mp) {\n      for (int j = i.second; j > 0; --j) factor.push_back(i.first);\n\
    \    }\n    std::cout << factor.size() << ' ';\n    for (auto i : factor) std::cout\
    \ << i << ' ';\n    std::cout << '\\n';\n  }\n  return 0;\n}"
  dependsOn:
  - math/basic/integer_factorization.hpp
  - modint/runtime_long_Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/factorize.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/factorize.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/factorize.0.test.cpp
- /verify/remote_test/yosupo/math/factorize.0.test.cpp.html
title: remote_test/yosupo/math/factorize.0.test.cpp
---
