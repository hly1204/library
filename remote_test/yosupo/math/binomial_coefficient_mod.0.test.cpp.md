---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/basic/binary_mul.hpp
    title: "binary multiplication / \u5FEB\u901F\u4E58"
  - icon: ':heavy_check_mark:'
    path: math/basic/binary_pow.hpp
    title: "binary power / \u5FEB\u901F\u5E42"
  - icon: ':heavy_check_mark:'
    path: math/basic/crt.hpp
    title: "Chinese remainder theorem / \u4E2D\u56FD\u5269\u4F59\u5B9A\u7406"
  - icon: ':heavy_check_mark:'
    path: math/basic/exgcd.hpp
    title: "extended Euclidean algorithm / \u6269\u5C55\u6B27\u51E0\u91CC\u5F97\u7B97\
      \u6CD5"
  - icon: ':heavy_check_mark:'
    path: math/modulo/binomial_coefficient_mod.hpp
    title: math/modulo/binomial_coefficient_mod.hpp
  - icon: ':heavy_check_mark:'
    path: traits/base.hpp
    title: "type traits / \u7C7B\u578B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/binomial_coefficient
    links:
    - https://judge.yosupo.jp/problem/binomial_coefficient
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/modulo/binomial_coefficient_mod.hpp: line 14: unable to process #include\
    \ in #if / #ifdef / #ifndef other than include guards\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/binomial_coefficient\"\n\
    \n#include \"math/modulo/binomial_coefficient_mod.hpp\"\n\n#include <iostream>\n\
    \nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  int t, m;\n  std::cin >> t >> m;\n  lib::BinomialCoefficientModSmall bc(m);\n\
    \  while (t--) {\n    long long n, m;\n    std::cin >> n >> m;\n    std::cout\
    \ << bc(n, m) << '\\n';\n  }\n  return 0;\n}"
  dependsOn:
  - math/modulo/binomial_coefficient_mod.hpp
  - math/basic/binary_pow.hpp
  - traits/base.hpp
  - math/basic/binary_mul.hpp
  - math/basic/crt.hpp
  - math/basic/exgcd.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
- /verify/remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp.html
title: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
---
