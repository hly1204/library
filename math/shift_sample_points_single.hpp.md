---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/shift_sample_points_single.hpp\"\n\n\n\n#line 1 \"\
    common.hpp\"\n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define\
    \ LIB_END }\n#define LIB ::lib::\n\n\n#line 5 \"math/shift_sample_points_single.hpp\"\
    \n\n#include <vector>\n\nLIB_BEGIN\n\ntemplate <typename ModIntT>\nModIntT shift_sample_points(const\
    \ std::vector<ModIntT> &f, ModIntT c) {\n  const int n = static_cast<int>(f.size());\n\
    \  if (n == 0) return ModIntT();\n  std::vector<ModIntT> inv(n), k(n);\n  ModIntT\
    \ v(1);\n  for (int i = 1; i != n; ++i) inv[i] = v, v *= i;\n  v = v.inv();\n\
    \  for (int i = n - 1; i != 0; --i) inv[i] *= v, v *= i;\n  k.front() = f.front();\n\
    \  for (int i = 1; i != n; ++i) k[i] = f[i] * (v *= (c - (i - 1)) * inv[i]);\n\
    \  ModIntT res(k.back());\n  v = 1;\n  for (int i = n - 2; i >= 0; --i) res +=\
    \ k[i] * (v *= -(c - (i + 1)) * inv[n - 1 - i]);\n  return res;\n}\n\nLIB_END\n\
    \n\n"
  code: "#ifndef SHIFT_SAMPLE_POINTS_SINGLE_HPP\n#define SHIFT_SAMPLE_POINTS_SINGLE_HPP\n\
    \n#include \"../common.hpp\"\n\n#include <vector>\n\nLIB_BEGIN\n\ntemplate <typename\
    \ ModIntT>\nModIntT shift_sample_points(const std::vector<ModIntT> &f, ModIntT\
    \ c) {\n  const int n = static_cast<int>(f.size());\n  if (n == 0) return ModIntT();\n\
    \  std::vector<ModIntT> inv(n), k(n);\n  ModIntT v(1);\n  for (int i = 1; i !=\
    \ n; ++i) inv[i] = v, v *= i;\n  v = v.inv();\n  for (int i = n - 1; i != 0; --i)\
    \ inv[i] *= v, v *= i;\n  k.front() = f.front();\n  for (int i = 1; i != n; ++i)\
    \ k[i] = f[i] * (v *= (c - (i - 1)) * inv[i]);\n  ModIntT res(k.back());\n  v\
    \ = 1;\n  for (int i = n - 2; i >= 0; --i) res += k[i] * (v *= -(c - (i + 1))\
    \ * inv[n - 1 - i]);\n  return res;\n}\n\nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  isVerificationFile: false
  path: math/shift_sample_points_single.hpp
  requiredBy: []
  timestamp: '2022-05-03 01:06:07+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/shift_sample_points_single.hpp
layout: document
title: Shift Sample Points (Single) (in $\mathbb{F} _ p \lbrack z \rbrack$)
---

## Lagrange Interpolation Formula

**Problem**: Given sample points $f(0), f(1), \dots ,f(n - 1)$ of polynomial $f$ with $\deg f \lt n$, find $f(c)$.

Recall the Lagrange interpolation formula,

$$
f(x) = \sum _ {0 \leq i \lt n} f(i) \prod _ {0 \leq j \lt n \atop j \neq i} \frac{x - j}{i - j}
$$

and define $k_i$ with

$$
k_i := \frac{f(i)}{i!} \prod _ {0 \leq j \lt i}(x - j)
$$

for some $i$, we have

$$
f(x) = \sum _ {0 \leq i \lt n} k_i \frac{(-1)^{n - 1 - i}}{(n - 1 - i)!} \prod _ {i \lt j \lt n}(x - j).
$$