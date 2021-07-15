---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
    title: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
    title: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: docs/math/formal_power_series/subproduct_tree.md
    document_title: "multi-point evaluation & interpolation / \u591A\u70B9\u6C42\u503C\
      \u548C\u63D2\u503C"
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/subproduct_tree.hpp\"\n\n\n\r\n\
    /**\r\n * @brief multi-point evaluation & interpolation / \u591A\u70B9\u6C42\u503C\
    \u548C\u63D2\u503C\r\n * @docs docs/math/formal_power_series/subproduct_tree.md\r\
    \n */\r\n\r\n#include <cassert>\r\n#include <functional>\r\n#include <numeric>\r\
    \n#include <vector>\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename mod_t, typename\
    \ PolyType>\r\nclass SubproductTree {\r\npublic:\r\n  SubproductTree(const std::vector<mod_t>\
    \ &x_set) : tree_(x_set.size() << 2) {\r\n    assert(!tree_.empty());\r\n    //\
    \ tree_ \u4E3A 1-indexed\r\n    std::function<void(int, int, int)> build_tree\
    \ = [&](int idx, int l, int r) {\r\n      if (l == r - 1) {\r\n        tree_[idx]\
    \ = PolyType{-x_set[l], mod_t(1)};\r\n      } else {\r\n        build_tree(idx\
    \ << 1, l, (l + r) >> 1), build_tree(idx << 1 | 1, (l + r) >> 1, r);\r\n     \
    \   tree_[idx] = tree_[idx << 1] * tree_[idx << 1 | 1];\r\n      }\r\n    };\r\
    \n    build_tree(1, 0, x_set.size());\r\n  }\r\n  ~SubproductTree() = default;\r\
    \n\r\n  std::vector<mod_t> godown(const PolyType &f) const {\r\n    std::vector<mod_t>\
    \ res;\r\n    res.reserve(tree_.size() >> 2);\r\n    std::function<void(int, int,\
    \ int, const PolyType &)> dfs = [&](int idx, int l, int r,\r\n               \
    \                                                    const PolyType &t) {\r\n\
    \      PolyType t_mod = t % tree_[idx];\r\n      if (l == r - 1) {\r\n       \
    \ res.emplace_back(t_mod[0]);\r\n      } else {\r\n        dfs(idx << 1, l, (l\
    \ + r) >> 1, t_mod), dfs(idx << 1 | 1, (l + r) >> 1, r, t_mod);\r\n      }\r\n\
    \    };\r\n    dfs(1, 0, tree_.size() >> 2, f);\r\n    return res;\r\n  }\r\n\r\
    \n  PolyType goup(const std::vector<mod_t> &y_set) const {\r\n    assert(y_set.size()\
    \ == (tree_.size() >> 2));\r\n    std::vector<mod_t> in_set = godown(tree_[1].deriv());\r\
    \n    std::vector<mod_t> p_sum(in_set.size()), n_set(in_set.size());\r\n    std::partial_sum(in_set.begin(),\
    \ in_set.end(), p_sum.begin(), std::multiplies<>());\r\n    mod_t p_inv = mod_t(1)\
    \ / p_sum.back();\r\n    for (int i = int(n_set.size()) - 1; i > 0; --i)\r\n \
    \     n_set[i] = p_sum[i - 1] * y_set[i] * p_inv, p_inv *= in_set[i];\r\n    n_set[0]\
    \                                   = y_set[0] * p_inv;\r\n    std::function<PolyType(int,\
    \ int, int)> dfs = [&](int idx, int l, int r) {\r\n      if (l == r - 1) {\r\n\
    \        return PolyType{n_set[l]};\r\n      } else {\r\n        return dfs(idx\
    \ << 1, l, (l + r) >> 1) * tree_[idx << 1 | 1] +\r\n               dfs(idx <<\
    \ 1 | 1, (l + r) >> 1, r) * tree_[idx << 1];\r\n      }\r\n    };\r\n    return\
    \ dfs(1, 0, y_set.size());\r\n  }\r\n\r\nprivate:\r\n  std::vector<PolyType> tree_;\r\
    \n};\r\n\r\ntemplate <typename PolyType, typename mod_t>\r\nstd::vector<mod_t>\
    \ evaluate(const PolyType &f, const std::vector<mod_t> &x_set) {\r\n  return SubproductTree<mod_t,\
    \ PolyType>(x_set).godown(f);\r\n}\r\n\r\ntemplate <typename PolyType, typename\
    \ mod_t>\r\nvoid interpolate(const std::vector<mod_t> &x_set, const std::vector<mod_t>\
    \ &y_set, PolyType &res) {\r\n  res = SubproductTree<mod_t, PolyType>(x_set).goup(y_set);\r\
    \n}\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef SUBPRODUCT_TREE_HEADER_HPP\r\n#define SUBPRODUCT_TREE_HEADER_HPP\r\
    \n\r\n/**\r\n * @brief multi-point evaluation & interpolation / \u591A\u70B9\u6C42\
    \u503C\u548C\u63D2\u503C\r\n * @docs docs/math/formal_power_series/subproduct_tree.md\r\
    \n */\r\n\r\n#include <cassert>\r\n#include <functional>\r\n#include <numeric>\r\
    \n#include <vector>\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename mod_t, typename\
    \ PolyType>\r\nclass SubproductTree {\r\npublic:\r\n  SubproductTree(const std::vector<mod_t>\
    \ &x_set) : tree_(x_set.size() << 2) {\r\n    assert(!tree_.empty());\r\n    //\
    \ tree_ \u4E3A 1-indexed\r\n    std::function<void(int, int, int)> build_tree\
    \ = [&](int idx, int l, int r) {\r\n      if (l == r - 1) {\r\n        tree_[idx]\
    \ = PolyType{-x_set[l], mod_t(1)};\r\n      } else {\r\n        build_tree(idx\
    \ << 1, l, (l + r) >> 1), build_tree(idx << 1 | 1, (l + r) >> 1, r);\r\n     \
    \   tree_[idx] = tree_[idx << 1] * tree_[idx << 1 | 1];\r\n      }\r\n    };\r\
    \n    build_tree(1, 0, x_set.size());\r\n  }\r\n  ~SubproductTree() = default;\r\
    \n\r\n  std::vector<mod_t> godown(const PolyType &f) const {\r\n    std::vector<mod_t>\
    \ res;\r\n    res.reserve(tree_.size() >> 2);\r\n    std::function<void(int, int,\
    \ int, const PolyType &)> dfs = [&](int idx, int l, int r,\r\n               \
    \                                                    const PolyType &t) {\r\n\
    \      PolyType t_mod = t % tree_[idx];\r\n      if (l == r - 1) {\r\n       \
    \ res.emplace_back(t_mod[0]);\r\n      } else {\r\n        dfs(idx << 1, l, (l\
    \ + r) >> 1, t_mod), dfs(idx << 1 | 1, (l + r) >> 1, r, t_mod);\r\n      }\r\n\
    \    };\r\n    dfs(1, 0, tree_.size() >> 2, f);\r\n    return res;\r\n  }\r\n\r\
    \n  PolyType goup(const std::vector<mod_t> &y_set) const {\r\n    assert(y_set.size()\
    \ == (tree_.size() >> 2));\r\n    std::vector<mod_t> in_set = godown(tree_[1].deriv());\r\
    \n    std::vector<mod_t> p_sum(in_set.size()), n_set(in_set.size());\r\n    std::partial_sum(in_set.begin(),\
    \ in_set.end(), p_sum.begin(), std::multiplies<>());\r\n    mod_t p_inv = mod_t(1)\
    \ / p_sum.back();\r\n    for (int i = int(n_set.size()) - 1; i > 0; --i)\r\n \
    \     n_set[i] = p_sum[i - 1] * y_set[i] * p_inv, p_inv *= in_set[i];\r\n    n_set[0]\
    \                                   = y_set[0] * p_inv;\r\n    std::function<PolyType(int,\
    \ int, int)> dfs = [&](int idx, int l, int r) {\r\n      if (l == r - 1) {\r\n\
    \        return PolyType{n_set[l]};\r\n      } else {\r\n        return dfs(idx\
    \ << 1, l, (l + r) >> 1) * tree_[idx << 1 | 1] +\r\n               dfs(idx <<\
    \ 1 | 1, (l + r) >> 1, r) * tree_[idx << 1];\r\n      }\r\n    };\r\n    return\
    \ dfs(1, 0, y_set.size());\r\n  }\r\n\r\nprivate:\r\n  std::vector<PolyType> tree_;\r\
    \n};\r\n\r\ntemplate <typename PolyType, typename mod_t>\r\nstd::vector<mod_t>\
    \ evaluate(const PolyType &f, const std::vector<mod_t> &x_set) {\r\n  return SubproductTree<mod_t,\
    \ PolyType>(x_set).godown(f);\r\n}\r\n\r\ntemplate <typename PolyType, typename\
    \ mod_t>\r\nvoid interpolate(const std::vector<mod_t> &x_set, const std::vector<mod_t>\
    \ &y_set, PolyType &res) {\r\n  res = SubproductTree<mod_t, PolyType>(x_set).goup(y_set);\r\
    \n}\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/formal_power_series/subproduct_tree.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
documentation_of: math/formal_power_series/subproduct_tree.hpp
layout: document
redirect_from:
- /library/math/formal_power_series/subproduct_tree.hpp
- /library/math/formal_power_series/subproduct_tree.hpp.html
title: "multi-point evaluation & interpolation / \u591A\u70B9\u6C42\u503C\u548C\u63D2\
  \u503C"
---
## 多项式多点求值

多点求值即 $\operatorname{eval}:\mathbb{F} _ p\lbrack x\rbrack\to \mathbb{F} _ p^n,f\mapsto (f(x_0),f(x_1),\dots ,f(x_{n-1}))$ 我们假设多项式 $f\in\mathbb{F} _ p\lbrack x\rbrack$ 有 $O(\deg (f))=O(n)$ 。我们可以通过分治取模的来计算。建立一棵 subproduct 树，树的叶子为 $x-x_i$ 而其余节点为叶子的乘积，而 FFT 的思想显然与此相同，为了简便可以使用线段树的递归建树方式。其中 $f(x_i)=f\bmod(x-x_i)$ 显然。

## 拉格朗日插值

插值即解同余方程组

$$
\begin{cases}
f\bmod (x-x_0)=y_0\\
f\bmod (x-x_1)=y_1\\
\vdots \\
f\bmod (x-x _ {n-1})=y _ {n-1}
\end{cases}
$$

其中对于 $\forall i\neq j$ 有 $x_i\neq x_j$ 。

令

$$
M=\prod _ {0\leq i\lt n}(x-x_i)\\
M_i=\frac{M}{x-x_i}\\
N_i=M_i^{-1}\bmod(x-x_i)=\prod _ {j\neq i}\frac{1}{x_i-x_j}
$$

那么

$$
f\equiv \sum _ {0\leq i\lt n}y_iM_iN_i\pmod{M}
$$

因为任取 $0\leq k\lt n$ 都满足

$$
f=y_k+\sum _ {i\neq k}y_iM_iN_i\pmod{(x-x_k)}
$$

后式中 $M_i$ 显然是 $x-x_k$ 的倍式所以同余零，得证。

稍加整理即

$$
f\equiv \sum _ {0\leq i\lt n}f(x_i)\prod  _ {j\neq i}\frac{x-x_j}{x_i-x_j}\pmod{M}
$$

观察到

$$
M'=\sum _ {0\leq i\lt n}\frac{M}{x-x_i}\\
M'(x_i)=\lim _ {x\to x_i}\frac{M(x)-M(x_i)}{x-x_i}=\lim _ {x\to x_i}\frac{M(x)}{x-x_i}=N_i^{-1}
$$

令

$$
M_a=\prod _ {0\leq i\lt \left\lfloor n/2\right\rfloor}(x-x_i)\\
M_b=\prod _ {\left\lfloor n/2\right\rfloor\leq i\lt n}(x-x_i)\\
f_a=\sum _ {0\leq i\lt \left\lfloor n/2\right\rfloor}y_iN_i\frac{M_a}{x-x_i}\\
f_b=\sum _ {\left\lfloor n/2\right\rfloor\leq i\lt n}y_iN_i\frac{M_b}{x-x_i}
$$

那么

$$
f\equiv f_aM_b+f_bM_a\pmod{M}
$$

可分治计算。

## 高速化

该算法有必要高速化吗？好像没有，因为有更快的转置算法，但是依然在这里指出我们只需在维护 subproduct 树的同时维护树中多项式对应的 DFT 发现如果要做乘法，那么上一次的 DFT 的一半是可用的，意味着只需要额外做另一半长度的 DFT ，而在插值时我们将多项式描述为一个线性组合，注意这里 `a*b+c*d` 中的加法也可以在 DFT 下运算，不维护其系数直接维护 DFT 即可。