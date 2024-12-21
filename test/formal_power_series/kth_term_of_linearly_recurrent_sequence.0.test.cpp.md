---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.12.8/x64/lib/python3.12/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.12.8/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.12.8/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \                ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n \
    \ File \"/opt/hostedtoolcache/Python/3.12.8/x64/lib/python3.12/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 260, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: c_recursive.hpp:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\"\
    \n\n#include \"c_recursive.hpp\"\n#include \"modint.hpp\"\n#include <iostream>\n\
    #include <vector>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n   \
    \ std::cin.tie(nullptr);\n    using mint = ModInt<998244353>;\n    int d;\n  \
    \  long long k;\n    std::cin >> d >> k;\n    std::vector<mint> Q(d + 1), init_v(d);\n\
    \    for (int i = 0; i < d; ++i) std::cin >> init_v[i];\n    Q[0] = 1;\n    for\
    \ (int i = 1; i <= d; ++i) {\n        std::cin >> Q[i];\n        Q[i] = -Q[i];\n\
    \    }\n    const auto M = xk_mod(k, std::vector(Q.rbegin(), Q.rend()));\n   \
    \ mint res;\n    for (int i = 0; i < (int)M.size(); ++i) res += M[i] * init_v[i];\n\
    \    std::cout << res << '\\n';\n    return 0;\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
layout: document
redirect_from:
- /verify/test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
- /verify/test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp.html
title: test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
---
