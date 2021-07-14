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
  bundledCode: "#line 1 \"math/formal_power_series/subproduct_tree.hpp\"\n\n\n\n/**\n\
    \ * @brief multi-point evaluation & interpolation / \u591A\u70B9\u6C42\u503C\u548C\
    \u63D2\u503C\n * @docs docs/math/formal_power_series/subproduct_tree.md\n */\n\
    \n#include <cassert>\n#include <functional>\n#include <numeric>\n#include <vector>\n\
    \nnamespace lib {\n\ntemplate <typename mod_t, typename PolyType> class SubproductTree\
    \ {\npublic:\n  SubproductTree(const std::vector<mod_t> &x_set) : tree_(x_set.size()\
    \ << 2) {\n    assert(!tree_.empty());\n    // tree_ \u4E3A 1-indexed\n    std::function<void(int,\
    \ int, int)> build_tree = [&](int idx, int l, int r) {\n      if (l == r - 1)\
    \ {\n        tree_[idx] = PolyType{-x_set[l], mod_t(1)};\n      } else {\n   \
    \     build_tree(idx << 1, l, (l + r) >> 1), build_tree(idx << 1 | 1, (l + r)\
    \ >> 1, r);\n        tree_[idx] = tree_[idx << 1] * tree_[idx << 1 | 1];\n   \
    \   }\n    };\n    build_tree(1, 0, x_set.size());\n  }\n  ~SubproductTree() =\
    \ default;\n\n  std::vector<mod_t> godown(const PolyType &f) const {\n    std::vector<mod_t>\
    \ res;\n    res.reserve(tree_.size() >> 2);\n    std::function<void(int, int,\
    \ int, const PolyType &)> dfs = [&](int idx, int l, int r,\n                 \
    \                                                  const PolyType &t) {\n    \
    \  PolyType t_mod = t % tree_[idx];\n      if (l == r - 1) {\n        res.emplace_back(t_mod[0]);\n\
    \      } else {\n        dfs(idx << 1, l, (l + r) >> 1, t_mod), dfs(idx << 1 |\
    \ 1, (l + r) >> 1, r, t_mod);\n      }\n    };\n    dfs(1, 0, tree_.size() >>\
    \ 2, f);\n    return res;\n  }\n\n  PolyType goup(const std::vector<mod_t> &y_set)\
    \ const {\n    assert(y_set.size() == (tree_.size() >> 2));\n    std::vector<mod_t>\
    \ in_set = godown(tree_[1].deriv());\n    std::vector<mod_t> p_sum(in_set.size()),\
    \ n_set(in_set.size());\n    std::partial_sum(in_set.begin(), in_set.end(), p_sum.begin(),\
    \ std::multiplies<>());\n    mod_t p_inv = mod_t(1) / p_sum.back();\n    for (int\
    \ i = int(n_set.size()) - 1; i > 0; --i)\n      n_set[i] = p_sum[i - 1] * y_set[i]\
    \ * p_inv, p_inv *= in_set[i];\n    n_set[0] = y_set[0] * p_inv;\n    std::function<PolyType(int,\
    \ int, int)> dfs = [&](int idx, int l, int r) {\n      if (l == r - 1) {\n   \
    \     return PolyType{n_set[l]};\n      } else {\n        return dfs(idx << 1,\
    \ l, (l + r) >> 1) * tree_[idx << 1 | 1] +\n               dfs(idx << 1 | 1, (l\
    \ + r) >> 1, r) * tree_[idx << 1];\n      }\n    };\n    return dfs(1, 0, y_set.size());\n\
    \  }\n\nprivate:\n  std::vector<PolyType> tree_;\n};\n\ntemplate <typename PolyType,\
    \ typename mod_t>\nstd::vector<mod_t> evaluate(const PolyType &f, const std::vector<mod_t>\
    \ &x_set) {\n  return SubproductTree<mod_t, PolyType>(x_set).godown(f);\n}\n\n\
    template <typename PolyType, typename mod_t>\nvoid interpolate(const std::vector<mod_t>\
    \ &x_set, const std::vector<mod_t> &y_set, PolyType &res) {\n  res = SubproductTree<mod_t,\
    \ PolyType>(x_set).goup(y_set);\n}\n\n} // namespace lib\n\n\n"
  code: "#ifndef SUBPRODUCT_TREE_HEADER_HPP\n#define SUBPRODUCT_TREE_HEADER_HPP\n\n\
    /**\n * @brief multi-point evaluation & interpolation / \u591A\u70B9\u6C42\u503C\
    \u548C\u63D2\u503C\n * @docs docs/math/formal_power_series/subproduct_tree.md\n\
    \ */\n\n#include <cassert>\n#include <functional>\n#include <numeric>\n#include\
    \ <vector>\n\nnamespace lib {\n\ntemplate <typename mod_t, typename PolyType>\
    \ class SubproductTree {\npublic:\n  SubproductTree(const std::vector<mod_t> &x_set)\
    \ : tree_(x_set.size() << 2) {\n    assert(!tree_.empty());\n    // tree_ \u4E3A\
    \ 1-indexed\n    std::function<void(int, int, int)> build_tree = [&](int idx,\
    \ int l, int r) {\n      if (l == r - 1) {\n        tree_[idx] = PolyType{-x_set[l],\
    \ mod_t(1)};\n      } else {\n        build_tree(idx << 1, l, (l + r) >> 1), build_tree(idx\
    \ << 1 | 1, (l + r) >> 1, r);\n        tree_[idx] = tree_[idx << 1] * tree_[idx\
    \ << 1 | 1];\n      }\n    };\n    build_tree(1, 0, x_set.size());\n  }\n  ~SubproductTree()\
    \ = default;\n\n  std::vector<mod_t> godown(const PolyType &f) const {\n    std::vector<mod_t>\
    \ res;\n    res.reserve(tree_.size() >> 2);\n    std::function<void(int, int,\
    \ int, const PolyType &)> dfs = [&](int idx, int l, int r,\n                 \
    \                                                  const PolyType &t) {\n    \
    \  PolyType t_mod = t % tree_[idx];\n      if (l == r - 1) {\n        res.emplace_back(t_mod[0]);\n\
    \      } else {\n        dfs(idx << 1, l, (l + r) >> 1, t_mod), dfs(idx << 1 |\
    \ 1, (l + r) >> 1, r, t_mod);\n      }\n    };\n    dfs(1, 0, tree_.size() >>\
    \ 2, f);\n    return res;\n  }\n\n  PolyType goup(const std::vector<mod_t> &y_set)\
    \ const {\n    assert(y_set.size() == (tree_.size() >> 2));\n    std::vector<mod_t>\
    \ in_set = godown(tree_[1].deriv());\n    std::vector<mod_t> p_sum(in_set.size()),\
    \ n_set(in_set.size());\n    std::partial_sum(in_set.begin(), in_set.end(), p_sum.begin(),\
    \ std::multiplies<>());\n    mod_t p_inv = mod_t(1) / p_sum.back();\n    for (int\
    \ i = int(n_set.size()) - 1; i > 0; --i)\n      n_set[i] = p_sum[i - 1] * y_set[i]\
    \ * p_inv, p_inv *= in_set[i];\n    n_set[0] = y_set[0] * p_inv;\n    std::function<PolyType(int,\
    \ int, int)> dfs = [&](int idx, int l, int r) {\n      if (l == r - 1) {\n   \
    \     return PolyType{n_set[l]};\n      } else {\n        return dfs(idx << 1,\
    \ l, (l + r) >> 1) * tree_[idx << 1 | 1] +\n               dfs(idx << 1 | 1, (l\
    \ + r) >> 1, r) * tree_[idx << 1];\n      }\n    };\n    return dfs(1, 0, y_set.size());\n\
    \  }\n\nprivate:\n  std::vector<PolyType> tree_;\n};\n\ntemplate <typename PolyType,\
    \ typename mod_t>\nstd::vector<mod_t> evaluate(const PolyType &f, const std::vector<mod_t>\
    \ &x_set) {\n  return SubproductTree<mod_t, PolyType>(x_set).godown(f);\n}\n\n\
    template <typename PolyType, typename mod_t>\nvoid interpolate(const std::vector<mod_t>\
    \ &x_set, const std::vector<mod_t> &y_set, PolyType &res) {\n  res = SubproductTree<mod_t,\
    \ PolyType>(x_set).goup(y_set);\n}\n\n} // namespace lib\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/formal_power_series/subproduct_tree.hpp
  requiredBy: []
  timestamp: '2021-07-14 21:25:20+08:00'
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