---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint/runtime_long_Montgomery_modint.hpp
    title: "runtime long Montgomery modint / \u8FD0\u884C\u65F6\u957F\u6574\u578B\
      \ Montgomery \u53D6\u6A21\u7C7B"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/factorize.0.test.cpp
    title: remote_test/yosupo/math/factorize.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "integer factorization / \u6574\u6570\u5206\u89E3"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/basic/integer_factorization.hpp: line 14: unable to process #include in\
    \ #if / #ifdef / #ifndef other than include guards\n"
  code: "/**\n * @brief integer factorization / \u6574\u6570\u5206\u89E3\n *\n */\n\
    \n#ifndef INTEGER_FACTORIZATION_HEADER_HPP\n#define INTEGER_FACTORIZATION_HEADER_HPP\n\
    \n#include <cstdint>\n#include <map>\n#include <numeric>\n#include <random>\n\n\
    #include \"../../modint/runtime_long_Montgomery_modint.hpp\"\n\nnamespace lib\
    \ {\n\nbool is_prime(std::uint64_t n) { // Miller-Rabin \u6D4B\u8BD5\n  if (n\
    \ <= 2) return n == 2;\n  if ((n & 1) == 0) return false;\n  if (n < 8) return\
    \ true;\n  using m64 = RuntimeLongMontModInt;\n  bool okay = m64::set_mod(n);\n\
    \  assert(okay);\n  int t = 0;\n  std::uint64_t u = n - 1;\n  do\n    u >>= 1,\
    \ ++t;\n  while ((u & 1) == 0);\n  const m64 ONE(1), MINUS_ONE(n - 1);\n  for\
    \ (int i : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {\n    if (n == i) return\
    \ true;\n    m64 x = m64(i).pow(u);\n    for (int i = 0; i != t && x != ONE; ++i)\
    \ {\n      m64 y = x * x;\n      if (x != MINUS_ONE && y == ONE) return false;\n\
    \      x = y;\n    }\n    if (x != ONE) return false;\n  }\n  return true;\n}\n\
    \nstd::uint64_t rho(std::uint64_t n) {\n  using u64 = std::uint64_t;\n  using\
    \ m64 = RuntimeLongMontModInt;\n  static std::random_device rd;\n  static std::mt19937\
    \ gen(rd());\n  std::uniform_int_distribution<u64> dis(2, n - 1);\n  if (m64::get_mod()\
    \ != n) m64::set_mod(n);\n  const m64 R(dis(gen));\n  auto f = [=](m64 x) -> m64\
    \ { return x * x + R; };\n  m64 x, y(dis(gen)), ys, q(1);\n  u64 g = 1;\n  const\
    \ int m = 128;\n  for (int r = 1; g == 1; r <<= 1) {\n    x = y;\n    for (int\
    \ i = 0; i < r; ++i) y = f(y);\n    for (int k = 0; g == 1 && k < r; k += m) {\n\
    \      ys = y;\n      for (int i = 0; i < m && i < r - k; ++i) q *= x - (y = f(y));\n\
    \      g = std::gcd(u64(q), n);\n    }\n  }\n  if (g == n) do\n      g = std::gcd(u64(x\
    \ - (ys = f(ys))), n);\n    while (g == 1);\n  return g == n ? rho(n) : g;\n}\n\
    \nvoid factorize_odd(std::uint64_t n, std::map<std::uint64_t, int> &mp) {\n  if\
    \ (n < 2) return;\n  if (is_prime(n)) {\n    ++mp[n];\n    return;\n  }\n  std::uint64_t\
    \ g = rho(n);\n  factorize_odd(n / g, mp);\n  factorize_odd(g, mp);\n}\n\nstd::map<std::uint64_t,\
    \ int> factorize(std::uint64_t n) {\n  std::map<std::uint64_t, int> res;\n  if\
    \ (n < 2) return res;\n  int t = 0;\n  while ((n & 1) == 0) n >>= 1, ++t;\n  if\
    \ (t) res[2] = t;\n  factorize_odd(n, res);\n  return res;\n}\n\n} // namespace\
    \ lib\n\n#endif"
  dependsOn:
  - modint/runtime_long_Montgomery_modint.hpp
  isVerificationFile: false
  path: math/basic/integer_factorization.hpp
  requiredBy: []
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/factorize.0.test.cpp
documentation_of: math/basic/integer_factorization.hpp
layout: document
redirect_from:
- /library/math/basic/integer_factorization.hpp
- /library/math/basic/integer_factorization.hpp.html
title: "integer factorization / \u6574\u6570\u5206\u89E3"
---
