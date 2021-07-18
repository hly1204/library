---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/formal_power_series/NTT_binomial.hpp
    title: "NTT prime binomial / NTT \u7D20\u6570\u7528\u4E8C\u9879\u5F0F\u7CFB\u6570"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/convolution.hpp
    title: "convolution / \u5377\u79EF"
  - icon: ':question:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362"
  - icon: ':question:'
    path: traits/modint.hpp
    title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/formal_power_series/sample_points_shift.hpp
    title: "sample points shift / \u6837\u672C\u70B9\u5E73\u79FB"
  - icon: ':warning:'
    path: math/modulo/factorial_modulo_prime.hpp
    title: "factorial modulo prime / \u9636\u4E58\u6A21\u7D20\u6570"
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    _deprecated_at_docs: docs/math/formal_power_series/falling_factorial_polynomial_multiplication.md
    document_title: "falling factorial polynomial multiplication / \u4E0B\u964D\u5E42\
      \u591A\u9879\u5F0F\u4E58\u6CD5"
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/falling_factorial_polynomial_multiplication.hpp\"\
    \n\n\n\r\n/**\r\n * @brief falling factorial polynomial multiplication / \u4E0B\
    \u964D\u5E42\u591A\u9879\u5F0F\u4E58\u6CD5\r\n * @docs docs/math/formal_power_series/falling_factorial_polynomial_multiplication.md\r\
    \n */\r\n\r\n#include <algorithm>\r\n#include <type_traits>\r\n#include <utility>\r\
    \n#include <vector>\r\n\r\n#line 1 \"math/formal_power_series/NTT_binomial.hpp\"\
    \n\n\n\r\n/**\r\n * @brief NTT prime binomial / NTT \u7D20\u6570\u7528\u4E8C\u9879\
    \u5F0F\u7CFB\u6570\r\n *\r\n */\r\n\r\n#line 10 \"math/formal_power_series/NTT_binomial.hpp\"\
    \n\r\nnamespace lib {\r\n\r\ntemplate <typename mod_t>\r\nclass NTTBinomial {\r\
    \npublic:\r\n  NTTBinomial(int lim = 0) {\r\n    if (fac_.empty()) {\r\n     \
    \ fac_.emplace_back(1);\r\n      ifac_.emplace_back(1);\r\n    }\r\n    init(lim);\r\
    \n  }\r\n  ~NTTBinomial() = default;\r\n\r\n  /**\r\n   * @brief \u9884\u5904\u7406\
    \ [0, n) \u7684\u9636\u4E58\u548C\u5176\u9006\u5143\r\n   */\r\n  static void\
    \ init(int n) {\r\n    if (int(fac_.size()) < n) {\r\n      int old_size = fac_.size();\r\
    \n      fac_.resize(n);\r\n      ifac_.resize(n);\r\n      for (int i = old_size;\
    \ i < n; ++i) fac_[i] = fac_[i - 1] * mod_t(i);\r\n      ifac_.back() = mod_t(1)\
    \ / fac_.back();\r\n      for (int i = n - 2; i >= old_size; --i) ifac_[i] = ifac_[i\
    \ + 1] * mod_t(i + 1);\r\n    }\r\n  }\r\n\r\n  mod_t fac_unsafe(int n) const\
    \ { return fac_[n]; }\r\n  mod_t ifac_unsafe(int n) const { return ifac_[n]; }\r\
    \n  mod_t inv_unsafe(int n) const { return ifac_[n] * fac_[n - 1]; }\r\n  mod_t\
    \ choose_unsafe(int n, int k) const {\r\n    // \u8FD4\u56DE binom{n}{k} \u6CE8\
    \u610F\u4E0A\u6307\u6807\u53EF\u4EE5\u4E3A\u8D1F\u6570\u4F46\u8FD9\u91CC\u5E76\
    \u672A\u5B9E\u73B0\uFF01\r\n    return n >= k ? fac_[n] * ifac_[k] * ifac_[n -\
    \ k] : mod_t(0);\r\n  }\r\n\r\nprivate:\r\n  static inline std::vector<mod_t>\
    \ fac_, ifac_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line 1 \"math/formal_power_series/convolution.hpp\"\
    \n\n\n\r\n/**\r\n * @brief convolution / \u5377\u79EF\r\n *\r\n */\r\n\r\n#line\
    \ 10 \"math/formal_power_series/convolution.hpp\"\n\r\n#line 1 \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n\n\n\r\n/**\r\n * @brief radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362\r\n\
    \ * @docs docs/math/formal_power_series/radix_2_NTT.md\r\n */\r\n\r\n#line 10\
    \ \"math/formal_power_series/radix_2_NTT.hpp\"\n#include <cassert>\r\n#include\
    \ <cstdint>\r\n#line 13 \"math/formal_power_series/radix_2_NTT.hpp\"\n\r\n#line\
    \ 1 \"traits/modint.hpp\"\n\n\n\r\n/**\r\n * @brief modint traits / \u53D6\u6A21\
    \u7C7B\u8403\u53D6\r\n *\r\n */\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename\
    \ mod_t>\r\nstruct modint_traits {\r\n  using type = typename mod_t::value_type;\r\
    \n  static constexpr type get_mod() { return mod_t::get_mod(); }\r\n  static constexpr\
    \ type get_primitive_root_prime() { return mod_t::get_primitive_root_prime();\
    \ }\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line 15 \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @note \u5FC5\u987B\u7528 NTT \u53CB\u597D\
    \u7684\u6A21\u6570\uFF01\uFF01\uFF01\r\n */\r\ntemplate <typename mod_t>\r\nclass\
    \ NTT {\r\npublic:\r\n  NTT() = delete;\r\n\r\n  static void set_root(int len)\
    \ {\r\n    static int lim = 0;\r\n    static constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\r\
    \n    if (lim == 0) {\r\n      constexpr int offset = 20;\r\n      rt.resize(1\
    \ << offset);\r\n      irt.resize(1 << offset);\r\n      rt[0] = irt[0] = 1;\r\
    \n      mod_t g_t = g.pow(modint_traits<mod_t>::get_mod() >> (offset + 1)), ig_t\
    \ = g_t.inv();\r\n      rt[1 << (offset - 1)] = g_t, irt[1 << (offset - 1)] =\
    \ ig_t;\r\n      for (int i = offset - 2; i >= 0; --i) {\r\n        g_t *= g_t,\
    \ ig_t *= ig_t;\r\n        rt[1 << i] = g_t, irt[1 << i] = ig_t;\r\n      }\r\n\
    \      lim = 1;\r\n    }\r\n    for (; (lim << 1) < len; lim <<= 1) {\r\n    \
    \  mod_t g = rt[lim], ig = irt[lim];\r\n      for (int i = lim + 1, e = lim <<\
    \ 1; i < e; ++i) {\r\n        rt[i]  = rt[i - lim] * g;\r\n        irt[i] = irt[i\
    \ - lim] * ig;\r\n      }\r\n    }\r\n  }\r\n\r\n  static void dft(int n, mod_t\
    \ *x) {\r\n    for (int j = 0, l = n >> 1; j != l; ++j) {\r\n      mod_t u = x[j],\
    \ v = x[j + l];\r\n      x[j] = u + v, x[j + l] = u - v;\r\n    }\r\n    for (int\
    \ i = n >> 1; i >= 2; i >>= 1) {\r\n      for (int j = 0, l = i >> 1; j != l;\
    \ ++j) {\r\n        mod_t u = x[j], v = x[j + l];\r\n        x[j] = u + v, x[j\
    \ + l] = u - v;\r\n      }\r\n      for (int j = i, l = i >> 1, m = 1; j != n;\
    \ j += i, ++m) {\r\n        mod_t root = rt[m];\r\n        for (int k = 0; k !=\
    \ l; ++k) {\r\n          mod_t u = x[j + k], v = x[j + k + l] * root;\r\n    \
    \      x[j + k] = u + v, x[j + k + l] = u - v;\r\n        }\r\n      }\r\n   \
    \ }\r\n  }\r\n\r\n  static void idft(int n, mod_t *x) {\r\n    for (int i = 2;\
    \ i < n; i <<= 1) {\r\n      for (int j = 0, l = i >> 1; j != l; ++j) {\r\n  \
    \      mod_t u = x[j], v = x[j + l];\r\n        x[j] = u + v, x[j + l] = u - v;\r\
    \n      }\r\n      for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {\r\
    \n        mod_t root = irt[m];\r\n        for (int k = 0; k != l; ++k) {\r\n \
    \         mod_t u = x[j + k], v = x[j + k + l];\r\n          x[j + k] = u + v,\
    \ x[j + k + l] = (u - v) * root;\r\n        }\r\n      }\r\n    }\r\n    mod_t\
    \ iv(mod_t(n).inv());\r\n    for (int j = 0, l = n >> 1; j != l; ++j) {\r\n  \
    \    mod_t u = x[j] * iv, v = x[j + l] * iv;\r\n      x[j] = u + v, x[j + l] =\
    \ u - v;\r\n    }\r\n  }\r\n\r\n  static void even_dft(int n, mod_t *x) {\r\n\
    \    static constexpr mod_t IT(mod_t(2).inv());\r\n    for (int i = 0, j = 0;\
    \ i != n; i += 2, ++j) x[j] = IT * (x[i] + x[i + 1]);\r\n  }\r\n\r\n  static void\
    \ odd_dft(int n, mod_t *x) {\r\n    static constexpr mod_t IT(mod_t(2).inv());\r\
    \n    for (int i = 0, j = 0; i != n; i += 2, ++j) x[j] = IT * irt[j] * (x[i] -\
    \ x[i + 1]);\r\n  }\r\n\r\n  static void dft_doubling(int n, mod_t *x) {\r\n \
    \   static constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\r\
    \n    std::copy_n(x, n, x + n);\r\n    idft(n, x + n);\r\n    mod_t k(1), t(g.pow((modint_traits<mod_t>::get_mod()\
    \ - 1) / (n << 1)));\r\n    for (int i = 0; i != n; ++i) x[n + i] *= k, k *= t;\r\
    \n    dft(n, x + n);\r\n  }\r\n\r\nprivate:\r\n  static inline std::vector<mod_t>\
    \ rt, irt;\r\n};\r\n\r\nstd::uint32_t get_ntt_len(std::uint32_t n) {\r\n  --n;\r\
    \n  n |= n >> 1;\r\n  n |= n >> 2;\r\n  n |= n >> 4;\r\n  n |= n >> 8;\r\n  return\
    \ (n | n >> 16) + 1;\r\n}\r\n\r\n/**\r\n * @brief \u63A5\u6536\u4E00\u4E2A\u591A\
    \u9879\u5F0F\uFF0C\u8FD4\u56DE\u4E8C\u8FDB\u5236\u7FFB\u8F6C\u540E\u7684 DFT \u5E8F\
    \u5217\uFF0C\u5373 x(1), x(-1) \u7B49\uFF0C\r\n *        \u5BF9\u4E8E\u4E0B\u6807\
    \ i \u548C i^1 \u5FC5\u7136\u662F\u4E24\u4E2A\u4E92\u4E3A\u76F8\u53CD\u6570\u7684\
    \u70B9\u503C\r\n *\r\n * @tparam mod_t\r\n * @param n\r\n * @param x\r\n */\r\n\
    template <typename mod_t>\r\nvoid dft(int n, mod_t *x) {\r\n  NTT<mod_t>::set_root(n);\r\
    \n  NTT<mod_t>::dft(n, x);\r\n}\r\n\r\n/**\r\n * @brief \u63A5\u6536\u4E8C\u8FDB\
    \u5236\u7FFB\u8F6C\u540E\u7684 DFT \u5E8F\u5217\uFF0C\u8FD4\u56DE\u591A\u9879\u5F0F\
    \u5E8F\u5217 mod (x^n - 1)\r\n *\r\n * @tparam mod_t\r\n * @param n\r\n * @param\
    \ x\r\n */\r\ntemplate <typename mod_t>\r\nvoid idft(int n, mod_t *x) {\r\n  NTT<mod_t>::set_root(n);\r\
    \n  NTT<mod_t>::idft(n, x);\r\n}\r\n\r\ntemplate <typename mod_t>\r\nvoid dft(std::vector<mod_t>\
    \ &x) {\r\n  NTT<mod_t>::set_root(x.size());\r\n  NTT<mod_t>::dft(x.size(), x.data());\r\
    \n}\r\n\r\ntemplate <typename mod_t>\r\nvoid idft(std::vector<mod_t> &x) {\r\n\
    \  NTT<mod_t>::set_root(x.size());\r\n  NTT<mod_t>::idft(x.size(), x.data());\r\
    \n}\r\n\r\n} // namespace lib\r\n\r\n\n#line 12 \"math/formal_power_series/convolution.hpp\"\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief NTT \u6A21\u6570\u5377\u79EF\r\n\
    \ * @tparam mod_t NTT \u53CB\u597D\u7684\u6A21\u6570\u7C7B\r\n */\r\ntemplate\
    \ <typename mod_t>\r\nstd::vector<mod_t> convolve(const std::vector<mod_t> &x,\
    \ const std::vector<mod_t> &y) {\r\n  int n = x.size(), m = y.size();\r\n  if\
    \ (std::min(n, m) <= 32) {\r\n    std::vector<mod_t> res(n + m - 1, mod_t(0));\r\
    \n    for (int i = 0; i < n; ++i)\r\n      for (int j = 0; j < m; ++j) res[i +\
    \ j] += x[i] * y[j];\r\n    return res;\r\n  }\r\n  int len = get_ntt_len(n +\
    \ m - 1);\r\n  std::vector<mod_t> res(len);\r\n  std::copy_n(x.begin(), n, res.begin());\r\
    \n  std::fill(res.begin() + n, res.end(), mod_t(0));\r\n  dft(res);\r\n  if (&x\
    \ == &y) {\r\n    for (int i = 0; i < len; ++i) res[i] *= res[i];\r\n  } else\
    \ {\r\n    std::vector<mod_t> y_tmp(len);\r\n    std::copy_n(y.begin(), m, y_tmp.begin());\r\
    \n    std::fill(y_tmp.begin() + m, y_tmp.end(), mod_t(0));\r\n    dft(y_tmp);\r\
    \n    for (int i = 0; i < len; ++i) res[i] *= y_tmp[i];\r\n  }\r\n  idft(res);\r\
    \n  res.resize(n + m - 1);\r\n  return res;\r\n}\r\n\r\n} // namespace lib\r\n\
    \r\n\n#line 16 \"math/formal_power_series/falling_factorial_polynomial_multiplication.hpp\"\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u6837\u672C\u70B9\u8F6C\u6362\u4E3A\
    \u4E0B\u964D\u5E42\u591A\u9879\u5F0F\r\n *\r\n * @tparam mod_t NTT \u53CB\u597D\
    \u7684\u6A21\u6570\r\n * @param pts f(0), f(1), \u2026, f(n-1)\r\n * @return std::vector<mod_t>\
    \ \u4E0B\u964D\u5E42\u591A\u9879\u5F0F\u7CFB\u6570\r\n */\r\ntemplate <typename\
    \ mod_t>\r\nstd::vector<mod_t> sample_points_to_FFP(const std::vector<mod_t> &pts)\
    \ {\r\n  int n = pts.size();\r\n  NTTBinomial<mod_t> bi(n);\r\n  std::vector<mod_t>\
    \ emx(n), pts_egf(n);\r\n  for (int i = 0; i < n; ++i) {\r\n    pts_egf[i] = pts[i]\
    \ * (emx[i] = bi.ifac_unsafe(i));\r\n    if (i & 1) emx[i] = -emx[i];\r\n  }\r\
    \n  pts_egf = std::move(convolve(emx, pts_egf));\r\n  pts_egf.resize(n);\r\n \
    \ return pts_egf;\r\n}\r\n\r\n/**\r\n * @brief \u4E0B\u964D\u5E42\u591A\u9879\u5F0F\
    \u8F6C\u6362\u4E3A\u6837\u672C\u70B9\r\n *\r\n * @tparam mod_t NTT \u53CB\u597D\
    \u7684\u6A21\u6570\r\n * @param n\r\n * @param ffp \u4E0B\u964D\u5E42\u591A\u9879\
    \u5F0F\r\n * @return std::vector<mod_t> f(0), f(1), \u2026, f(n-1)\r\n */\r\n\
    template <typename mod_t>\r\nstd::vector<mod_t> FFP_to_sample_points(int n, const\
    \ std::vector<mod_t> &ffp) {\r\n  NTTBinomial<mod_t> bi(n);\r\n  std::vector<mod_t>\
    \ ex(n);\r\n  for (int i = 0; i < n; ++i) ex[i] = bi.ifac_unsafe(i);\r\n  if (ffp.size()\
    \ > n) {\r\n    ex = std::move(convolve(ex, std::vector<mod_t>(ffp.begin(), ffp.begin()\
    \ + n)));\r\n  } else {\r\n    ex = std::move(convolve(ex, ffp));\r\n  }\r\n \
    \ for (int i = 0; i < n; ++i) ex[i] *= bi.fac_unsafe(i);\r\n  ex.resize(n);\r\n\
    \  return ex;\r\n}\r\n\r\n/**\r\n * @brief \u4E0B\u964D\u5E42\u591A\u9879\u5F0F\
    \u4E58\u6CD5\r\n * @note \u8FD9\u91CC\u82E5\u5C55\u5F00\u5199\u53EF\u4EE5\u8282\
    \u7701\u4E00\u6B21 DFT\r\n */\r\ntemplate <typename mod_t>\r\nstd::vector<mod_t>\
    \ convolve_FFP(const std::vector<mod_t> &lhs, const std::vector<mod_t> &rhs) {\r\
    \n  int d = lhs.size() + rhs.size() - 1;\r\n  std::vector<mod_t> lhs_pts(FFP_to_sample_points(d,\
    \ lhs)), rhs_pts(FFP_to_sample_points(d, rhs));\r\n  for (int i = 0; i < d; ++i)\
    \ lhs_pts[i] *= rhs_pts[i];\r\n  return sample_points_to_FFP(lhs_pts);\r\n}\r\n\
    \r\n/**\r\n * @brief \u4E0B\u964D\u5E42\u591A\u9879\u5F0F\u5E73\u79FB\r\n */\r\
    \ntemplate <typename mod_t>\r\nstd::vector<mod_t> shift_FFP(const std::vector<mod_t>\
    \ &ffp, mod_t c) {\r\n  int n = ffp.size();\r\n  NTTBinomial<mod_t> bi(n);\r\n\
    \  std::vector<mod_t> A(ffp), B(n);\r\n  mod_t c_i(1);\r\n  for (int i = 0; i\
    \ < n; ++i)\r\n    A[i] *= bi.fac_unsafe(i), B[i] = c_i * bi.ifac_unsafe(i), c_i\
    \ *= c - mod_t(i);\r\n  std::reverse(A.begin(), A.end());\r\n  A = std::move(convolve(A,\
    \ B));\r\n  A.resize(n);\r\n  std::reverse(A.begin(), A.end());\r\n  for (int\
    \ i = 0; i < n; ++i) A[i] *= bi.ifac_unsafe(i);\r\n  return A;\r\n}\r\n\r\n} //\
    \ namespace lib\r\n\r\n\n"
  code: "#ifndef FALLING_FACTORIAL_POLYNOMIAL_MULTIPLICATION_HEADER_HPP\r\n#define\
    \ FALLING_FACTORIAL_POLYNOMIAL_MULTIPLICATION_HEADER_HPP\r\n\r\n/**\r\n * @brief\
    \ falling factorial polynomial multiplication / \u4E0B\u964D\u5E42\u591A\u9879\
    \u5F0F\u4E58\u6CD5\r\n * @docs docs/math/formal_power_series/falling_factorial_polynomial_multiplication.md\r\
    \n */\r\n\r\n#include <algorithm>\r\n#include <type_traits>\r\n#include <utility>\r\
    \n#include <vector>\r\n\r\n#include \"NTT_binomial.hpp\"\r\n#include \"convolution.hpp\"\
    \r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u6837\u672C\u70B9\u8F6C\u6362\
    \u4E3A\u4E0B\u964D\u5E42\u591A\u9879\u5F0F\r\n *\r\n * @tparam mod_t NTT \u53CB\
    \u597D\u7684\u6A21\u6570\r\n * @param pts f(0), f(1), \u2026, f(n-1)\r\n * @return\
    \ std::vector<mod_t> \u4E0B\u964D\u5E42\u591A\u9879\u5F0F\u7CFB\u6570\r\n */\r\
    \ntemplate <typename mod_t>\r\nstd::vector<mod_t> sample_points_to_FFP(const std::vector<mod_t>\
    \ &pts) {\r\n  int n = pts.size();\r\n  NTTBinomial<mod_t> bi(n);\r\n  std::vector<mod_t>\
    \ emx(n), pts_egf(n);\r\n  for (int i = 0; i < n; ++i) {\r\n    pts_egf[i] = pts[i]\
    \ * (emx[i] = bi.ifac_unsafe(i));\r\n    if (i & 1) emx[i] = -emx[i];\r\n  }\r\
    \n  pts_egf = std::move(convolve(emx, pts_egf));\r\n  pts_egf.resize(n);\r\n \
    \ return pts_egf;\r\n}\r\n\r\n/**\r\n * @brief \u4E0B\u964D\u5E42\u591A\u9879\u5F0F\
    \u8F6C\u6362\u4E3A\u6837\u672C\u70B9\r\n *\r\n * @tparam mod_t NTT \u53CB\u597D\
    \u7684\u6A21\u6570\r\n * @param n\r\n * @param ffp \u4E0B\u964D\u5E42\u591A\u9879\
    \u5F0F\r\n * @return std::vector<mod_t> f(0), f(1), \u2026, f(n-1)\r\n */\r\n\
    template <typename mod_t>\r\nstd::vector<mod_t> FFP_to_sample_points(int n, const\
    \ std::vector<mod_t> &ffp) {\r\n  NTTBinomial<mod_t> bi(n);\r\n  std::vector<mod_t>\
    \ ex(n);\r\n  for (int i = 0; i < n; ++i) ex[i] = bi.ifac_unsafe(i);\r\n  if (ffp.size()\
    \ > n) {\r\n    ex = std::move(convolve(ex, std::vector<mod_t>(ffp.begin(), ffp.begin()\
    \ + n)));\r\n  } else {\r\n    ex = std::move(convolve(ex, ffp));\r\n  }\r\n \
    \ for (int i = 0; i < n; ++i) ex[i] *= bi.fac_unsafe(i);\r\n  ex.resize(n);\r\n\
    \  return ex;\r\n}\r\n\r\n/**\r\n * @brief \u4E0B\u964D\u5E42\u591A\u9879\u5F0F\
    \u4E58\u6CD5\r\n * @note \u8FD9\u91CC\u82E5\u5C55\u5F00\u5199\u53EF\u4EE5\u8282\
    \u7701\u4E00\u6B21 DFT\r\n */\r\ntemplate <typename mod_t>\r\nstd::vector<mod_t>\
    \ convolve_FFP(const std::vector<mod_t> &lhs, const std::vector<mod_t> &rhs) {\r\
    \n  int d = lhs.size() + rhs.size() - 1;\r\n  std::vector<mod_t> lhs_pts(FFP_to_sample_points(d,\
    \ lhs)), rhs_pts(FFP_to_sample_points(d, rhs));\r\n  for (int i = 0; i < d; ++i)\
    \ lhs_pts[i] *= rhs_pts[i];\r\n  return sample_points_to_FFP(lhs_pts);\r\n}\r\n\
    \r\n/**\r\n * @brief \u4E0B\u964D\u5E42\u591A\u9879\u5F0F\u5E73\u79FB\r\n */\r\
    \ntemplate <typename mod_t>\r\nstd::vector<mod_t> shift_FFP(const std::vector<mod_t>\
    \ &ffp, mod_t c) {\r\n  int n = ffp.size();\r\n  NTTBinomial<mod_t> bi(n);\r\n\
    \  std::vector<mod_t> A(ffp), B(n);\r\n  mod_t c_i(1);\r\n  for (int i = 0; i\
    \ < n; ++i)\r\n    A[i] *= bi.fac_unsafe(i), B[i] = c_i * bi.ifac_unsafe(i), c_i\
    \ *= c - mod_t(i);\r\n  std::reverse(A.begin(), A.end());\r\n  A = std::move(convolve(A,\
    \ B));\r\n  A.resize(n);\r\n  std::reverse(A.begin(), A.end());\r\n  for (int\
    \ i = 0; i < n; ++i) A[i] *= bi.ifac_unsafe(i);\r\n  return A;\r\n}\r\n\r\n} //\
    \ namespace lib\r\n\r\n#endif"
  dependsOn:
  - math/formal_power_series/NTT_binomial.hpp
  - math/formal_power_series/convolution.hpp
  - math/formal_power_series/radix_2_NTT.hpp
  - traits/modint.hpp
  isVerificationFile: false
  path: math/formal_power_series/falling_factorial_polynomial_multiplication.hpp
  requiredBy:
  - math/formal_power_series/sample_points_shift.hpp
  - math/modulo/factorial_modulo_prime.hpp
  timestamp: '2021-07-19 03:14:01+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/formal_power_series/falling_factorial_polynomial_multiplication.hpp
layout: document
redirect_from:
- /library/math/formal_power_series/falling_factorial_polynomial_multiplication.hpp
- /library/math/formal_power_series/falling_factorial_polynomial_multiplication.hpp.html
title: "falling factorial polynomial multiplication / \u4E0B\u964D\u5E42\u591A\u9879\
  \u5F0F\u4E58\u6CD5"
---
## 下降幂多项式

下降幂多项式 $f\in\mathbb{F} _ p\lbrack x\rbrack$ 是形如

$$
f=\sum _ {i=0}^nf_ix^{\underline{i}},\quad x^{\underline{k}}=x(x-1)\cdots (x-k+1)=\frac{x!}{(x-k)!}
$$

的多项式，且对于 $\forall j\gt n$ 令 $f_j=0$ ，其中 $x^{\underline{0}}=1$ 。

我们知道

$$
\begin{aligned}
\mathrm{e}^x&=0!+\frac{x}{1!}+\frac{x^2}{2!}+\cdots =\sum _ {i\geq 0}\frac{x^i}{i!}\\
\mathrm{e}^{-x}&=0!+(-1)\frac{x}{1!}+(-1)^2\frac{x^2}{2!}+\cdots =\sum _ {i\geq 0}(-1)^i\frac{x^i}{i!}\\
\left(\mathrm{e}^x\right)^\prime &=0+\frac{x^0}{1!}+\frac{2x}{2!}+\cdots =\sum _ {i\geq 0}\frac{x^i}{i!}=\mathrm{e}^x
\end{aligned}
$$

对某个非负整数 $m$ 我们令 $T=x^{\underline{m}}$ 的点值 $T(0),T(1),\dots $ 的指数生成函数

$$
\begin{aligned}
\sum _ {i\geq 0}\frac{T(i)}{i!}x^i&=\sum _ {i\geq 0}\frac{i!}{(i-m)!}\frac{x^i}{i!}\\
&=\sum _ {i\geq 0}\frac{1}{(i-m)!}x^i\\
&=\mathrm{e}^xx^m
\end{aligned}
$$

那么 $f$ 的点值 $f(0),f(1),\dots $ 的指数生成函数

$$
\sum _ {i\geq 0}\frac{f(i)}{i!}x^i=\mathrm{e}^x\left(\sum _ {i\geq 0}f_ix^i\right)
$$

注意这里的 $\sum _ {i\geq 0}f_ix^i$ 是下降幂多项式 $f$ 其下降幂系数 $\lbrack x^{\underline i}\rbrack$ 的生成函数。我们可以通过一次多项式乘法在下降幂系数和点值间转换。

## 下降幂多项式平移

考虑下降幂的二项式定理 $(n+m)^{\underline{k}}=\sum _ {i=0}^k\binom{k}{i}n^{\underline{i}}m^{\underline{k-i}}$ ，参考 [stackexchange](https://math.stackexchange.com/questions/1271688/combinatorial-proof-of-falling-factorial-and-binomial-theorem) 不妨考虑其组合意义，从 $n$ 个不同的黑球和 $m$ 个不同的白球中取出 $k$ 个球有

$$
(n+m)^{\underline{k}}
$$

种取法（第一次有 $n+m$ 种取法，第二次有 $n+m-1$ 种，以此类推）。而另一种计算方式是假设第一次取了 $0$ 个黑球，第二次取了 $1$ 个黑球，以此类推，那么

$$
\begin{aligned}
(n+m)^{\underline{k}}&=\sum _ {i=0}^kk!\frac{n^{\underline{i}}}{i!}\frac{m^{\underline{k-i}}}{(k-i)!}\\
&=\sum _ {i=0}^k\binom{k}{i}n^{\underline{i}}m^{\underline{k-i}}
\end{aligned}
$$

我们忽略黑球之间的顺序再忽略白球之间的顺序，再考虑 $k$ 个球之间的顺序即可。有

$$
\begin{aligned}
f(x+c)&=\sum _ {i=0}^nf_i(x+c)^{\underline{i}}\\
&=\sum _ {i=0}^nf_i\left(\sum _ {j=0}^i\binom{i}{j}x^{\underline{j}}c^{\underline{i-j}}\right)\\
&=\sum _ {i=0}^nf_ii!\left(\sum _ {j=0}^i\frac{x^{\underline{j}}}{j!}\frac{c^{\underline{i-j}}}{(i-j)!}\right)\\
&=\sum _ {i=0}^n\frac{x^{\underline{i}}}{i!}\left(\sum _ {j=i}^{n}f_jj!\frac{c^{\underline{j-i}}}{(j-i)!}\right)
\end{aligned}
$$

与多项式平移相似。