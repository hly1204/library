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
    path: traits/base.hpp
    title: "type traits / \u7C7B\u578B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
    title: remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "binomial coefficient mod / \u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\
      \u6A21"
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.5/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 400, in update\n    raise BundleErrorAt(path, i + 1, \"unable to process\
    \ #include in #if / #ifdef / #ifndef other than include guards\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ math/modulo/binomial_coefficient_mod.hpp: line 14: unable to process #include\
    \ in #if / #ifdef / #ifndef other than include guards\n"
  code: "/**\n * @brief binomial coefficient mod / \u4E8C\u9879\u5F0F\u7CFB\u6570\u53D6\
    \u6A21\n *\n */\n\n#ifndef BINOMIAL_COEFFICIENT_MOD_HEADER_HPP\n#define BINOMIAL_COEFFICIENT_MOD_HEADER_HPP\n\
    \n#include <cassert>\n#include <cstdint>\n#include <tuple>\n#include <vector>\n\
    \n#include \"../basic/binary_pow.hpp\"\n#include \"../basic/crt.hpp\"\n#include\
    \ \"../basic/exgcd.hpp\"\n\nnamespace lib {\n\nclass BinomialCoefficientModSmall\
    \ {\npublic:\n  using u32 = std::uint32_t;\n  using u64 = std::uint64_t;\n\n \
    \ BinomialCoefficientModSmall(u32 mod) {\n    for (u32 i = 2; i * i <= mod; ++i)\
    \ {\n      if (mod % i == 0) {\n        u32 e = 0, old_mod = mod;\n        do\
    \ {\n          ++e;\n          mod /= i;\n        } while (mod % i == 0);\n  \
    \      u32 ie = old_mod / mod;\n        factor_.push_back({i, e, ie, {}, {}});\n\
    \        auto &fac = std::get<3>(factor_.back());\n        auto &ifac = std::get<4>(factor_.back());\n\
    \        fac.resize(ie);\n        ifac.resize(ie);\n        if (e == 1) {\n  \
    \        fac[0] = ifac[0] = 1;\n          for (int j = 1; j != ie; ++j) fac[j]\
    \ = u64(fac[j - 1]) * j % ie;\n          ifac[ie - 1] = ie - 1; // Wilson's theorem\n\
    \          for (int j = ie - 2; j > 0; --j) ifac[j] = u64(ifac[j + 1]) * (j +\
    \ 1) % ie;\n        } else {\n          ifac[0] = fac[0] = 1;\n          for (int\
    \ j = 1; j != ie; ++j) {\n            fac[j] = (j % i == 0) ? fac[j - 1] : u64(fac[j\
    \ - 1]) * j % ie;\n            ifac[j] = u64(fac[j]) * ifac[j - 1] % ie;\n   \
    \       }\n          u32 ivie = inv_mod(ifac[ie - 1], ie);\n          for (int\
    \ j = ie - 1; j > 0; --j)\n            ifac[j] = u64(ivie) * ifac[j - 1] % ie,\
    \ ivie = u64(ivie) * fac[j] % ie;\n        }\n      }\n    }\n    if (mod != 1)\
    \ {\n      u32 ie = mod;\n      factor_.push_back({mod, 1, mod, {}, {}});\n  \
    \    auto &fac = std::get<3>(factor_.back());\n      auto &ifac = std::get<4>(factor_.back());\n\
    \      fac.resize(ie);\n      ifac.resize(ie);\n      fac[0] = ifac[0] = 1;\n\
    \      for (int j = 1; j != ie; ++j) fac[j] = u64(fac[j - 1]) * j % ie;\n    \
    \  ifac[ie - 1] = ie - 1; // Wilson's theorem\n      for (int j = ie - 2; j >\
    \ 0; --j) ifac[j] = u64(ifac[j + 1]) * (j + 1) % ie;\n    }\n    std::vector<u32>\
    \ factor(factor_.size());\n    for (int i = 0, e = factor_.size(); i < e; ++i)\
    \ factor[i] = std::get<2>(factor_[i]);\n    crt_.set_m(factor);\n  }\n\n  ~BinomialCoefficientModSmall()\
    \ = default;\n\n  u32 operator()(u64 n, u64 m) const {\n    if (n < m) return\
    \ 0;\n    std::vector<u32> v;\n    for (auto &i : factor_) {\n      u32 p = std::get<0>(i),\
    \ q = std::get<1>(i), pq = std::get<2>(i);\n      const std::vector<u32> &fac\
    \ = std::get<3>(i), &ifac = std::get<4>(i);\n      u64 n_t = n, m_t = m, res =\
    \ 1;\n      if (q == 1) {\n        for (; n_t; n_t /= p, m_t /= p) {\n       \
    \   if (n_t % p < m_t % p) {\n            res = 0;\n            break;\n     \
    \     }\n          res = res * u64(fac[n_t % p]) % p * ifac[m_t % p] % p * ifac[n_t\
    \ % p - m_t % p] % p;\n        }\n      } else {\n        u64 r = n_t - m_t, k\
    \ = 0;\n        for (u64 n1 = n_t / p; n1; n1 /= p) k += n1;\n        for (u64\
    \ m1 = m_t / p; m1; m1 /= p) k -= m1;\n        for (u64 r1 = r / p; r1; r1 /=\
    \ p) k -= r1;\n        if (k >= q) {\n          res = 0;\n        } else {\n \
    \         u32 pk = lib::pow(p, k);\n          u64 is_negative = 0;\n         \
    \ for (; n_t; n_t /= p, m_t /= p, r /= p) {\n            res = res * fac[n_t %\
    \ pq] % pq * ifac[m_t % pq] % pq * ifac[r % pq] % pq;\n            is_negative\
    \ += n_t / pq + m_t / pq + r / pq;\n          }\n          if ((p == 2 && q >=\
    \ 3) || (is_negative & 1) == 0)\n            res = res * pk % pq;\n          else\n\
    \            res = (pq - res) * pk % pq;\n        }\n      }\n      v.push_back(res);\n\
    \    }\n    return crt_(v);\n  }\n\nprivate:\n  std::vector<std::tuple<u32, u32,\
    \ u32, std::vector<u32>, std::vector<u32>>> factor_;\n  CoprimeCRT<u32> crt_;\n\
    };\n\n} // namespace lib\n\n#endif"
  dependsOn:
  - math/basic/binary_pow.hpp
  - traits/base.hpp
  - math/basic/binary_mul.hpp
  - math/basic/crt.hpp
  - math/basic/exgcd.hpp
  isVerificationFile: false
  path: math/modulo/binomial_coefficient_mod.hpp
  requiredBy: []
  timestamp: '2021-06-06 20:18:21+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/binomial_coefficient_mod.0.test.cpp
documentation_of: math/modulo/binomial_coefficient_mod.hpp
layout: document
---

## 二项式系数取模

类 `class BinomialCoefficientModSmall` 中有

- `BinomialCoefficientModSmall(M)` 为构造函数，在线性时间预处理阶乘，一般 $1\lt M\leq 10^6$ 。
- `operator()(n, m)` 返回 $\binom{n}{m}\bmod{M}$ 的值。

我们可以预处理 CRT 需要用到的逆元。

