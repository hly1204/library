---
data:
  _extendedDependsOn:
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
    PROBLEM: https://judge.yosupo.jp/problem/inv_of_formal_power_series
    links:
    - https://judge.yosupo.jp/problem/inv_of_formal_power_series
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/formal_power_series/radix_2_NTT.hpp: line 14: unable to process #include\
    \ in #if / #ifdef / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/inv_of_formal_power_series\"\
    \n\n#include <iostream>\n#include <vector>\n\n#include \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n#include \"modint/Montgomery_modint.hpp\"\n\ntemplate <typename mod_t> std::vector<mod_t>\
    \ inv_helper_func(std::vector<mod_t> Q) {\n  int n = Q.size();\n  if (n == 1)\
    \ return {Q[0].inv()};\n  // Q(x)Q(-x)=V(x^2)\n  // \u9012\u5F52\u6C42 1/V(x)\
    \ \u7684\u524D n/2 \u9879\uFF0C\u8FD8\u539F\u51FA 1/V(x^2) \u7684\u524D n \u9879\
    \uFF0C\u4E0E Q(-x) \u5377\u79EF\u622A\u53D6\u524D n \u9879\u5373\u53EF\n  Q.resize(n\
    \ << 1, 0);\n  lib::dft(n << 1, Q.data());\n  std::vector<mod_t> V(n << 1);\n\
    \  for (int i = 0, j = 0; i != n << 1; i += 2) V[j++] = Q[i] * Q[i ^ 1];\n  lib::idft(n,\
    \ V.data());\n  V.resize(n >> 1);\n  auto S = inv_helper_func(V);\n  S.resize(n\
    \ << 1, 0);\n  lib::dft(n, S.data());\n  std::vector<mod_t> res(n << 1);\n  for\
    \ (int i = 0; i != n << 1; ++i) res[i] = Q[i ^ 1] * S[i >> 1];\n  lib::idft(n\
    \ << 1, res.data());\n  res.resize(n);\n  return res;\n}\n\ntemplate <typename\
    \ mod_t> std::vector<mod_t> inv(std::vector<mod_t> x) {\n  int n = x.size(), len\
    \ = lib::get_ntt_len(n);\n  x.resize(len);\n  auto res = inv_helper_func(x);\n\
    \  return res.resize(n), res;\n}\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"\
    in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(0);\n  using mint = lib::MontModInt<998244353>;\n  int n;\n  std::cin\
    \ >> n;\n  std::vector<mint> s(n);\n  for (auto &i : s) std::cin >> i;\n  for\
    \ (auto i : inv(s)) std::cout << i << ' ';\n  return 0;\n}"
  dependsOn:
  - math/formal_power_series/radix_2_NTT.hpp
  - traits/modint.hpp
  - modint/Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
- /verify/remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp.html
title: remote_test/yosupo/math/inv_of_formal_power_series.0.test.cpp
---
