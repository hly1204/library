---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/fps_basic.hpp
    title: "\u5F62\u5F0F\u5E42\u7EA7\u6570\u7684\u57FA\u672C\u64CD\u4F5C"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "\u57FA-2 NTT"
  - icon: ':heavy_check_mark:'
    path: modint/Montgomery_modint.hpp
    title: Montgomery modint
  - icon: ':heavy_check_mark:'
    path: traits/modint.hpp
    title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
    links:
    - https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/formal_power_series/fps_basic.hpp: line 17: unable to process #include\
    \ in #if / #ifdef / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\"\
    \n\n#include <algorithm>\n#include <iostream>\n\n#include \"math/formal_power_series/fps_basic.hpp\"\
    \n#include \"modint/Montgomery_modint.hpp\"\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"\
    in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(0);\n  using mint = lib::MontModInt<998244353>;\n  int d;\n  long\
    \ long k;\n  std::cin >> d >> k;\n  lib::FPS<mint> rec(d), init_v(d), res{1},\
    \ t{0, 1};\n  for (auto &i : init_v) std::cin >> i;\n  for (auto &i : rec) std::cin\
    \ >> i, i = -i;\n  rec.insert(rec.begin(), 1);\n  std::cout << (init_v * rec).slice(d).div_at(rec,\
    \ k);\n  return 0;\n}"
  dependsOn:
  - math/formal_power_series/fps_basic.hpp
  - traits/modint.hpp
  - math/formal_power_series/radix_2_NTT.hpp
  - modint/Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
  requiredBy: []
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
- /verify/remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp.html
title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.1.test.cpp
---
