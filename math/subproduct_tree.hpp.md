---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':question:'
    path: math/radix2_ntt.hpp
    title: Radix-2 NTT (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
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
    links: []
  bundledCode: "#line 1 \"math/subproduct_tree.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
    \n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 1 \"math/radix2_ntt.hpp\"\n\n\n\n#line 5 \"\
    math/radix2_ntt.hpp\"\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n\
    #include <type_traits>\n#include <vector>\n\nLIB_BEGIN\n\nnamespace detail {\n\
    \ntemplate <typename IntT>\nconstexpr std::enable_if_t<std::is_integral_v<IntT>,\
    \ int> bsf(IntT v) {\n  if (static_cast<std::make_signed_t<IntT>>(v) <= 0) return\
    \ -1;\n  int res = 0;\n  for (; (v & 1) == 0; ++res) v >>= 1;\n  return res;\n\
    }\n\ntemplate <typename ModIntT>\nconstexpr ModIntT quadratic_nonresidue_prime()\
    \ {\n  auto mod = ModIntT::mod();\n  for (int i = 2;; ++i)\n    if (ModIntT(i).pow(mod\
    \ >> 1) == mod - 1) return ModIntT(i);\n}\n\ntemplate <typename ModIntT>\nconstexpr\
    \ ModIntT gen_of_sylow_2_subgroup() {\n  auto mod = ModIntT::mod();\n  return\
    \ quadratic_nonresidue_prime<ModIntT>().pow(mod >> bsf(mod - 1));\n}\n\ntemplate\
    \ <typename ModIntT>\nconstexpr std::array<ModIntT, bsf(ModIntT::mod() - 1) -\
    \ 1> root() {\n  std::array<ModIntT, bsf(ModIntT::mod() - 1) - 1> rt; // order(`rt[i]`)\
    \ = 2^(i + 2).\n  rt.back() = gen_of_sylow_2_subgroup<ModIntT>();\n  for (int\
    \ i = bsf(ModIntT::mod() - 1) - 3; i >= 0; --i) rt[i] = rt[i + 1] * rt[i + 1];\n\
    \  return rt;\n}\n\ntemplate <typename ModIntT>\nconstexpr std::array<ModIntT,\
    \ bsf(ModIntT::mod() - 1) - 1> iroot() {\n  std::array<ModIntT, bsf(ModIntT::mod()\
    \ - 1) - 1> irt;\n  irt.back() = gen_of_sylow_2_subgroup<ModIntT>().inv();\n \
    \ for (int i = bsf(ModIntT::mod() - 1) - 3; i >= 0; --i) irt[i] = irt[i + 1] *\
    \ irt[i + 1];\n  return irt;\n}\n\n} // namespace detail\n\n// Input:  integer\
    \ `n`.\n// Output: 2^(\u2308log_2(`n`)\u2309).\nint ntt_len(int n) {\n  --n;\n\
    \  n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8;\n  return (n | n >> 16)\
    \ + 1;\n}\n\n// Input:           f(x) = `a[0]` + `a[1]`x + ... + `a[n - 1]`x^(`n`\
    \ - 1) where `n` is power of 2.\n// Output(inplace): reversed binary permutation\
    \ of [f(\u03B6^0), f(\u03B6), f(\u03B6^2), ..., f(\u03B6^(`n` - 1))].\ntemplate\
    \ <typename IterT>\nvoid dft_n(IterT a, int n) {\n  assert((n & (n - 1)) == 0);\n\
    \  using T                  = typename std::iterator_traits<IterT>::value_type;\n\
    \  static constexpr auto rt = detail::root<T>();\n  static std::vector<T> root(1);\n\
    \  if (int s = static_cast<int>(root.size()); s << 1 < n) {\n    root.resize(n\
    \ >> 1);\n    for (int i = detail::bsf(s), j; 1 << i < n >> 1; ++i) {\n      root[j\
    \ = 1 << i] = rt[i];\n      for (int k = j + 1; k < j << 1; ++k) root[k] = root[k\
    \ - j] * root[j];\n    }\n  }\n  for (int j = 0, l = n >> 1; j != l; ++j) {\n\
    \    T u(a[j]), v(a[j + l]);\n    a[j] = u + v, a[j + l] = u - v;\n  }\n  for\
    \ (int i = n >> 1; i >= 2; i >>= 1) {\n    for (int j = 0, l = i >> 1; j != l;\
    \ ++j) {\n      T u(a[j]), v(a[j + l]);\n      a[j] = u + v, a[j + l] = u - v;\n\
    \    }\n    for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m)\n      for\
    \ (int k = j; k != j + l; ++k) {\n        T u(a[k]), v(a[k + l] * root[m]);\n\
    \        a[k] = u + v, a[k + l] = u - v;\n      }\n  }\n}\n\n// Input:       \
    \    reversed binary permutation of [f(\u03B6^0), f(\u03B6), f(\u03B6^2), ...,\
    \ f(\u03B6^(`n` - 1))].\n// Output(inplace): f(x) = `a[0]` + `a[1]`x + ... + `a[n\
    \ - 1]`x^(`n` - 1) where `n` is power of 2.\ntemplate <typename IterT>\nvoid idft_n(IterT\
    \ a, int n) {\n  assert((n & (n - 1)) == 0);\n  using T                  = typename\
    \ std::iterator_traits<IterT>::value_type;\n  static constexpr auto rt = detail::iroot<T>();\n\
    \  static std::vector<T> root(1);\n  if (int s = static_cast<int>(root.size());\
    \ s << 1 < n) {\n    root.resize(n >> 1);\n    for (int i = detail::bsf(s), j;\
    \ 1 << i < n >> 1; ++i) {\n      root[j = 1 << i] = rt[i];\n      for (int k =\
    \ j + 1; k < j << 1; ++k) root[k] = root[k - j] * root[j];\n    }\n  }\n  for\
    \ (int i = 2; i < n; i <<= 1) {\n    for (int j = 0, l = i >> 1; j != l; ++j)\
    \ {\n      T u(a[j]), v(a[j + l]);\n      a[j] = u + v, a[j + l] = u - v;\n  \
    \  }\n    for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m)\n      for (int\
    \ k = j; k != j + l; ++k) {\n        T u(a[k]), v(a[k + l]);\n        a[k] = u\
    \ + v, a[k + l] = (u - v) * root[m];\n      }\n  }\n  const T iv(T::mod() - T::mod()\
    \ / n);\n  for (int j = 0, l = n >> 1; j != l; ++j) {\n    T u(a[j] * iv), v(a[j\
    \ + l] * iv);\n    a[j] = u + v, a[j + l] = u - v;\n  }\n}\n\n// clang-format\
    \ off\ntemplate <typename ContainerT> void dft(ContainerT &&a) { dft_n(a.begin(),\
    \ a.size()); }\ntemplate <typename ContainerT> void idft(ContainerT &&a) { idft_n(a.begin(),\
    \ a.size()); }\ntemplate <typename IterT> void dft(IterT beg, IterT end) { dft_n(beg,\
    \ end - beg); }\ntemplate <typename IterT> void idft(IterT beg, IterT end) { idft_n(beg,\
    \ end - beg); }\n// clang-format on\n\ntemplate <typename ModIntT>\nvoid dft_doubling(const\
    \ std::vector<ModIntT> &a, std::vector<ModIntT> &dft_a) {\n  static constexpr\
    \ auto rt = detail::root<ModIntT>();\n  int as = static_cast<int>(a.size()), n\
    \ = static_cast<int>(dft_a.size());\n  // `dft_a` = dft_n(`a` mod (x^n - 1))\n\
    \  // doubling `dft_a` is just computing dft_n((`a` mod (x^n + 1))(\u03B6^(2n))).\n\
    \  dft_a.resize(n << 1);\n  auto it = dft_a.begin() + n;\n  for (int i = 0, is_even\
    \ = 0, j; i != as; ++i) {\n    if ((j = i & (n - 1)) == 0) is_even ^= 1;\n   \
    \ it[j] += is_even ? a[i] : -a[i];\n  }\n  ModIntT r(n == 1 ? ModIntT(-1) : rt[detail::bsf(n)\
    \ - 1]), v(1);\n  for (int i = 0; i != n; ++i) it[i] *= v, v *= r;\n  dft_n(it,\
    \ n);\n}\n\ntemplate <typename ModIntT>\nvoid dft_doubling(std::vector<ModIntT>\
    \ &dft_a) {\n  static constexpr auto rt = detail::root<ModIntT>();\n  int n  \
    \                  = static_cast<int>(dft_a.size());\n  dft_a.resize(n << 1);\n\
    \  auto it = dft_a.begin() + n;\n  std::copy_n(dft_a.cbegin(), n, it);\n  idft_n(it,\
    \ n);\n  ModIntT r(n == 1 ? ModIntT(-1) : rt[detail::bsf(n) - 1]), v(1);\n  for\
    \ (int i = 0; i != n; ++i) it[i] *= v, v *= r;\n  dft_n(it, n);\n}\n\nLIB_END\n\
    \n\n#line 6 \"math/subproduct_tree.hpp\"\n\n#line 8 \"math/subproduct_tree.hpp\"\
    \n#include <utility>\n#line 10 \"math/subproduct_tree.hpp\"\n\nLIB_BEGIN\n\ntemplate\
    \ <typename PolyT>\nclass subproduct_tree {\n  using T = typename PolyT::value_type;\n\
    \n  struct poly_info {\n    PolyT poly_, cached_dft_;\n    poly_info(PolyT &&poly,\
    \ PolyT &&cached_dft)\n        : poly_(std::move(poly)), cached_dft_(std::move(cached_dft))\
    \ {}\n    poly_info(const PolyT &poly, const PolyT &cached_dft) : poly_(poly),\
    \ cached_dft_(cached_dft) {}\n    explicit poly_info(const poly_info &) = default;\n\
    \  };\n\n  std::vector<std::vector<poly_info>> tree_{};\n\npublic:\n  explicit\
    \ subproduct_tree(const std::vector<T> &x);\n  std::vector<T> evaluate(const PolyT\
    \ &a) const;\n  PolyT interpolate(const std::vector<T> &y) const;\n};\n\ntemplate\
    \ <typename PolyT>\nsubproduct_tree<PolyT>::subproduct_tree(const std::vector<T>\
    \ &x) {\n  if (x.empty()) return;\n  auto &&l0 = tree_.emplace_back();\n  for\
    \ (auto &&i : x) l0.emplace_back(PolyT{-i, T(1)}, PolyT{1 - i});\n  while (tree_.back().size()\
    \ != 1) {\n    auto &&a    = tree_.back();\n    const int n = static_cast<int>(a.size());\n\
    \    std::vector<poly_info> b;\n    for (int i = 0; i + 1 < n; i += 2) {\n   \
    \   auto &&aif  = a[i].poly_;\n      auto &&ais  = a[i].cached_dft_;\n      auto\
    \ &&ai1f = a[i + 1].poly_;\n      auto &&ai1s = a[i + 1].cached_dft_;\n      dft_doubling(aif,\
    \ ais);\n      while (ai1s.size() < ais.size()) dft_doubling(ai1f, ai1s);\n  \
    \    auto v = ais;\n      for (int j = 0, je = static_cast<int>(v.size()); j !=\
    \ je; ++j) v[j] *= ai1s[j];\n      auto dv = v;\n      idft(v);\n      auto vs\
    \ = aif.size() + ai1f.size() - 1;\n      if (v.size() < vs) {\n        v.emplace_back(1);\n\
    \        v.front() -= v.back();\n      }\n      v.resize(vs);\n      b.emplace_back(std::move(v),\
    \ std::move(dv));\n    }\n    if (n & 1) b.emplace_back(a.back());\n    tree_.emplace_back(std::move(b));\n\
    \  }\n}\n\ntemplate <typename PolyT>\nstd::vector<typename PolyT::value_type>\
    \ subproduct_tree<PolyT>::evaluate(const PolyT &a) const {\n  if (tree_.empty())\
    \ return {};\n  if (a.is_zero()) return std::vector<T>(tree_.front().size());\n\
    \  const int n = static_cast<int>(tree_.front().size()), m = a.deg();\n  // Compute\
    \ `a`/((x - `x.front()`)...(x - `x.back()`)) and\n  // take the coefficients of\
    \ x^(-1), ..., x^(-`n`)\n  const auto irev_x =\n      PolyT(tree_.back().front().poly_.crbegin(),\
    \ tree_.back().front().poly_.crend()).inv(m + 1);\n  auto aix = a * PolyT(irev_x.crbegin(),\
    \ irev_x.crend());\n  if (m - n < -1) aix.resize(m + n);\n  aix.erase(aix.begin(),\
    \ aix.begin() + m);\n  aix.resize(n);\n  std::vector<PolyT> resp{aix};\n  for\
    \ (auto t = tree_.rbegin() + 1, te = tree_.rend(); t != te; ++t) {\n    std::vector<PolyT>\
    \ res;\n    const int ts = static_cast<int>(t->size());\n    for (int i = 0, ie\
    \ = static_cast<int>(resp.size()); i != ie; ++i)\n      if ((i << 1 | 1) < ts)\
    \ {\n        auto &&l      = t->at(i << 1);\n        auto &&r      = t->at(i <<\
    \ 1 | 1);\n        const int len = static_cast<int>(l.cached_dft_.size());\n \
    \       resp[i].resize(len);\n        dft(resp[i]);\n        auto respi_cpy =\
    \ resp[i];\n        for (int j = 0; j != len; ++j)\n          resp[i][j] *= r.cached_dft_[j],\
    \ respi_cpy[j] *= l.cached_dft_[j];\n        res.emplace_back(std::move(resp[i]));\n\
    \        auto &&rr = res.emplace_back(std::move(respi_cpy));\n        auto &&lr\
    \ = *(res.rbegin() + 1);\n        idft(lr), idft(rr);\n        lr.erase(lr.begin(),\
    \ lr.begin() + r.poly_.deg());\n        lr.resize(l.poly_.deg());\n        rr.erase(rr.begin(),\
    \ rr.begin() + l.poly_.deg());\n        rr.resize(r.poly_.deg());\n      } else\
    \ {\n        res.emplace_back(std::move(resp[i]));\n      }\n    resp.swap(res);\n\
    \  }\n  std::vector<T> res(n);\n  for (int i = 0; i != n; ++i) res[i] = resp[i].front();\n\
    \  return res;\n}\n\ntemplate <typename PolyT>\nPolyT subproduct_tree<PolyT>::interpolate(const\
    \ std::vector<T> &y) const {\n  assert(y.size() == tree_.front().size());\n  const\
    \ int n = static_cast<int>(y.size());\n  auto yp     = evaluate(tree_.back().front().poly_.deriv());\n\
    \  std::vector<T> iyp(yp.size());\n  {\n    T v(1);\n    for (int i = 0; i !=\
    \ n; ++i) iyp[i] = v, v *= yp[i];\n    v = v.inv();\n    for (int i = n - 1; i\
    \ >= 0; --i) iyp[i] *= v, v *= yp[i];\n  }\n  std::vector<PolyT> resp;\n  resp.reserve(n);\n\
    \  for (int i = 0; i != n; ++i) resp.emplace_back(PolyT{y[i] * iyp[i]});\n  for\
    \ (auto t = tree_.begin(); resp.size() != 1; ++t) {\n    assert(t->size() == resp.size());\n\
    \    std::vector<PolyT> res;\n    for (int i = 0, ie = static_cast<int>(resp.size());\
    \ i + 1 < ie; i += 2) {\n      auto &&l = t->at(i).cached_dft_;\n      auto &&r\
    \ = t->at(i + 1).cached_dft_;\n      dft_doubling(resp[i]);\n      const int len\
    \ = static_cast<int>(l.size());\n      {\n        auto respi1 = resp[i + 1];\n\
    \        idft(respi1);\n        while (static_cast<int>(resp[i + 1].size()) <\
    \ len) dft_doubling(respi1, resp[i + 1]);\n      }\n      auto &&rr = res.emplace_back(std::move(resp[i]));\n\
    \      for (int j = 0; j != len; ++j) rr[j] = rr[j] * r[j] + resp[i + 1][j] *\
    \ l[j];\n    }\n    if (t->size() & 1) res.emplace_back(std::move(resp.back()));\n\
    \    resp.swap(res);\n  }\n  idft(resp.front());\n  resp.front().shrink();\n \
    \ return resp.front();\n}\n\ntemplate <typename PolyT>\nstd::vector<typename PolyT::value_type>\n\
    evaluation(const PolyT &a, const std::vector<typename PolyT::value_type> &x) {\n\
    \  return subproduct_tree<PolyT>(x).evaluate(a);\n}\n\ntemplate <template <typename>\
    \ typename PolyT, typename ModIntT>\nPolyT<ModIntT> interpolation(const std::vector<ModIntT>\
    \ &x, const std::vector<ModIntT> &y) {\n  return subproduct_tree<PolyT<ModIntT>>(x).interpolate(y);\n\
    }\n\nLIB_END\n\n\n"
  code: "#ifndef SUBPRODUCT_TREE_HPP\n#define SUBPRODUCT_TREE_HPP\n\n#include \"../common.hpp\"\
    \n#include \"radix2_ntt.hpp\"\n\n#include <cassert>\n#include <utility>\n#include\
    \ <vector>\n\nLIB_BEGIN\n\ntemplate <typename PolyT>\nclass subproduct_tree {\n\
    \  using T = typename PolyT::value_type;\n\n  struct poly_info {\n    PolyT poly_,\
    \ cached_dft_;\n    poly_info(PolyT &&poly, PolyT &&cached_dft)\n        : poly_(std::move(poly)),\
    \ cached_dft_(std::move(cached_dft)) {}\n    poly_info(const PolyT &poly, const\
    \ PolyT &cached_dft) : poly_(poly), cached_dft_(cached_dft) {}\n    explicit poly_info(const\
    \ poly_info &) = default;\n  };\n\n  std::vector<std::vector<poly_info>> tree_{};\n\
    \npublic:\n  explicit subproduct_tree(const std::vector<T> &x);\n  std::vector<T>\
    \ evaluate(const PolyT &a) const;\n  PolyT interpolate(const std::vector<T> &y)\
    \ const;\n};\n\ntemplate <typename PolyT>\nsubproduct_tree<PolyT>::subproduct_tree(const\
    \ std::vector<T> &x) {\n  if (x.empty()) return;\n  auto &&l0 = tree_.emplace_back();\n\
    \  for (auto &&i : x) l0.emplace_back(PolyT{-i, T(1)}, PolyT{1 - i});\n  while\
    \ (tree_.back().size() != 1) {\n    auto &&a    = tree_.back();\n    const int\
    \ n = static_cast<int>(a.size());\n    std::vector<poly_info> b;\n    for (int\
    \ i = 0; i + 1 < n; i += 2) {\n      auto &&aif  = a[i].poly_;\n      auto &&ais\
    \  = a[i].cached_dft_;\n      auto &&ai1f = a[i + 1].poly_;\n      auto &&ai1s\
    \ = a[i + 1].cached_dft_;\n      dft_doubling(aif, ais);\n      while (ai1s.size()\
    \ < ais.size()) dft_doubling(ai1f, ai1s);\n      auto v = ais;\n      for (int\
    \ j = 0, je = static_cast<int>(v.size()); j != je; ++j) v[j] *= ai1s[j];\n   \
    \   auto dv = v;\n      idft(v);\n      auto vs = aif.size() + ai1f.size() - 1;\n\
    \      if (v.size() < vs) {\n        v.emplace_back(1);\n        v.front() -=\
    \ v.back();\n      }\n      v.resize(vs);\n      b.emplace_back(std::move(v),\
    \ std::move(dv));\n    }\n    if (n & 1) b.emplace_back(a.back());\n    tree_.emplace_back(std::move(b));\n\
    \  }\n}\n\ntemplate <typename PolyT>\nstd::vector<typename PolyT::value_type>\
    \ subproduct_tree<PolyT>::evaluate(const PolyT &a) const {\n  if (tree_.empty())\
    \ return {};\n  if (a.is_zero()) return std::vector<T>(tree_.front().size());\n\
    \  const int n = static_cast<int>(tree_.front().size()), m = a.deg();\n  // Compute\
    \ `a`/((x - `x.front()`)...(x - `x.back()`)) and\n  // take the coefficients of\
    \ x^(-1), ..., x^(-`n`)\n  const auto irev_x =\n      PolyT(tree_.back().front().poly_.crbegin(),\
    \ tree_.back().front().poly_.crend()).inv(m + 1);\n  auto aix = a * PolyT(irev_x.crbegin(),\
    \ irev_x.crend());\n  if (m - n < -1) aix.resize(m + n);\n  aix.erase(aix.begin(),\
    \ aix.begin() + m);\n  aix.resize(n);\n  std::vector<PolyT> resp{aix};\n  for\
    \ (auto t = tree_.rbegin() + 1, te = tree_.rend(); t != te; ++t) {\n    std::vector<PolyT>\
    \ res;\n    const int ts = static_cast<int>(t->size());\n    for (int i = 0, ie\
    \ = static_cast<int>(resp.size()); i != ie; ++i)\n      if ((i << 1 | 1) < ts)\
    \ {\n        auto &&l      = t->at(i << 1);\n        auto &&r      = t->at(i <<\
    \ 1 | 1);\n        const int len = static_cast<int>(l.cached_dft_.size());\n \
    \       resp[i].resize(len);\n        dft(resp[i]);\n        auto respi_cpy =\
    \ resp[i];\n        for (int j = 0; j != len; ++j)\n          resp[i][j] *= r.cached_dft_[j],\
    \ respi_cpy[j] *= l.cached_dft_[j];\n        res.emplace_back(std::move(resp[i]));\n\
    \        auto &&rr = res.emplace_back(std::move(respi_cpy));\n        auto &&lr\
    \ = *(res.rbegin() + 1);\n        idft(lr), idft(rr);\n        lr.erase(lr.begin(),\
    \ lr.begin() + r.poly_.deg());\n        lr.resize(l.poly_.deg());\n        rr.erase(rr.begin(),\
    \ rr.begin() + l.poly_.deg());\n        rr.resize(r.poly_.deg());\n      } else\
    \ {\n        res.emplace_back(std::move(resp[i]));\n      }\n    resp.swap(res);\n\
    \  }\n  std::vector<T> res(n);\n  for (int i = 0; i != n; ++i) res[i] = resp[i].front();\n\
    \  return res;\n}\n\ntemplate <typename PolyT>\nPolyT subproduct_tree<PolyT>::interpolate(const\
    \ std::vector<T> &y) const {\n  assert(y.size() == tree_.front().size());\n  const\
    \ int n = static_cast<int>(y.size());\n  auto yp     = evaluate(tree_.back().front().poly_.deriv());\n\
    \  std::vector<T> iyp(yp.size());\n  {\n    T v(1);\n    for (int i = 0; i !=\
    \ n; ++i) iyp[i] = v, v *= yp[i];\n    v = v.inv();\n    for (int i = n - 1; i\
    \ >= 0; --i) iyp[i] *= v, v *= yp[i];\n  }\n  std::vector<PolyT> resp;\n  resp.reserve(n);\n\
    \  for (int i = 0; i != n; ++i) resp.emplace_back(PolyT{y[i] * iyp[i]});\n  for\
    \ (auto t = tree_.begin(); resp.size() != 1; ++t) {\n    assert(t->size() == resp.size());\n\
    \    std::vector<PolyT> res;\n    for (int i = 0, ie = static_cast<int>(resp.size());\
    \ i + 1 < ie; i += 2) {\n      auto &&l = t->at(i).cached_dft_;\n      auto &&r\
    \ = t->at(i + 1).cached_dft_;\n      dft_doubling(resp[i]);\n      const int len\
    \ = static_cast<int>(l.size());\n      {\n        auto respi1 = resp[i + 1];\n\
    \        idft(respi1);\n        while (static_cast<int>(resp[i + 1].size()) <\
    \ len) dft_doubling(respi1, resp[i + 1]);\n      }\n      auto &&rr = res.emplace_back(std::move(resp[i]));\n\
    \      for (int j = 0; j != len; ++j) rr[j] = rr[j] * r[j] + resp[i + 1][j] *\
    \ l[j];\n    }\n    if (t->size() & 1) res.emplace_back(std::move(resp.back()));\n\
    \    resp.swap(res);\n  }\n  idft(resp.front());\n  resp.front().shrink();\n \
    \ return resp.front();\n}\n\ntemplate <typename PolyT>\nstd::vector<typename PolyT::value_type>\n\
    evaluation(const PolyT &a, const std::vector<typename PolyT::value_type> &x) {\n\
    \  return subproduct_tree<PolyT>(x).evaluate(a);\n}\n\ntemplate <template <typename>\
    \ typename PolyT, typename ModIntT>\nPolyT<ModIntT> interpolation(const std::vector<ModIntT>\
    \ &x, const std::vector<ModIntT> &y) {\n  return subproduct_tree<PolyT<ModIntT>>(x).interpolate(y);\n\
    }\n\nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  - math/radix2_ntt.hpp
  isVerificationFile: false
  path: math/subproduct_tree.hpp
  requiredBy: []
  timestamp: '2022-07-02 07:42:02+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
documentation_of: math/subproduct_tree.hpp
layout: document
title: Multipoint Evaluation and Interpolation (in $\mathbb{F} _ p$ for FFT prime
  $p$)
---
