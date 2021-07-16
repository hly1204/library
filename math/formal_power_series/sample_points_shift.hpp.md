---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/NTT_binomial.hpp
    title: "NTT prime binomial / NTT \u7D20\u6570\u7528\u4E8C\u9879\u5F0F\u7CFB\u6570"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/convolution.hpp
    title: "convolution / \u5377\u79EF"
  - icon: ':warning:'
    path: math/formal_power_series/falling_factorial_polynomial_multiplication.hpp
    title: "falling factorial polynomial multiplication / \u4E0B\u964D\u5E42\u591A\
      \u9879\u5F0F\u4E58\u6CD5"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362"
  - icon: ':heavy_check_mark:'
    path: traits/modint.hpp
    title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    _deprecated_at_docs: docs/math/formal_power_series/sample_points_shift.md
    document_title: "sample points shift / \u6837\u672C\u70B9\u5E73\u79FB"
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/sample_points_shift.hpp\"\n\n\n\
    \r\n/**\r\n * @brief sample points shift / \u6837\u672C\u70B9\u5E73\u79FB\r\n\
    \ * @docs docs/math/formal_power_series/sample_points_shift.md\r\n */\r\n\r\n\
    #include <cassert>\r\n#include <functional>\r\n#include <numeric>\r\n#include\
    \ <utility>\r\n#include <vector>\r\n\r\n#line 1 \"math/formal_power_series/NTT_binomial.hpp\"\
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
    \ fac_, ifac_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line 1 \"math/formal_power_series/falling_factorial_polynomial_multiplication.hpp\"\
    \n\n\n\r\n/**\r\n * @brief falling factorial polynomial multiplication / \u4E0B\
    \u964D\u5E42\u591A\u9879\u5F0F\u4E58\u6CD5\r\n * @docs docs/math/formal_power_series/falling_factorial_polynomial_multiplication.md\r\
    \n */\r\n\r\n#include <algorithm>\r\n#include <type_traits>\r\n#line 13 \"math/formal_power_series/falling_factorial_polynomial_multiplication.hpp\"\
    \n\r\n#line 1 \"math/formal_power_series/convolution.hpp\"\n\n\n\r\n/**\r\n *\
    \ @brief convolution / \u5377\u79EF\r\n *\r\n */\r\n\r\n#line 10 \"math/formal_power_series/convolution.hpp\"\
    \n\r\n#line 1 \"math/formal_power_series/radix_2_NTT.hpp\"\n\n\n\r\n/**\r\n *\
    \ @brief radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362\r\n * @docs docs/math/formal_power_series/radix_2_NTT.md\r\
    \n */\r\n\r\n#line 11 \"math/formal_power_series/radix_2_NTT.hpp\"\n#include <cstdint>\r\
    \n#line 13 \"math/formal_power_series/radix_2_NTT.hpp\"\n\r\n#line 1 \"traits/modint.hpp\"\
    \n\n\n\r\n/**\r\n * @brief modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6\r\n\
    \ *\r\n */\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename mod_t>\r\nstruct modint_traits\
    \ {\r\n  using type = typename mod_t::value_type;\r\n  static constexpr type get_mod()\
    \ { return mod_t::get_mod(); }\r\n  static constexpr type get_primitive_root_prime()\
    \ { return mod_t::get_primitive_root_prime(); }\r\n};\r\n\r\n} // namespace lib\r\
    \n\r\n\n#line 15 \"math/formal_power_series/radix_2_NTT.hpp\"\n\r\nnamespace lib\
    \ {\r\n\r\n/**\r\n * @note \u5FC5\u987B\u7528 NTT \u53CB\u597D\u7684\u6A21\u6570\
    \uFF01\uFF01\uFF01\r\n */\r\ntemplate <typename mod_t>\r\nclass NTT {\r\npublic:\r\
    \n  NTT() = delete;\r\n\r\n  static void set_root(int len) {\r\n    static int\
    \ lim = 0;\r\n    static constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\r\
    \n    if (lim == 0) {\r\n      rt.resize(1 << 20);\r\n      irt.resize(1 << 20);\r\
    \n      rt[0] = irt[0] = 1;\r\n      mod_t g_t = g.pow(modint_traits<mod_t>::get_mod()\
    \ >> 21), ig_t = g_t.inv();\r\n      rt[1 << 19] = g_t, irt[1 << 19] = ig_t;\r\
    \n      for (int i = 18; i >= 0; --i) {\r\n        g_t *= g_t, ig_t *= ig_t;\r\
    \n        rt[1 << i] = g_t, irt[1 << i] = ig_t;\r\n      }\r\n      lim = 1;\r\
    \n    }\r\n    for (; (lim << 1) < len; lim <<= 1) {\r\n      mod_t g = rt[lim],\
    \ ig = irt[lim];\r\n      for (int i = lim + 1, e = lim << 1; i < e; ++i) {\r\n\
    \        rt[i]  = rt[i - lim] * g;\r\n        irt[i] = irt[i - lim] * ig;\r\n\
    \      }\r\n    }\r\n  }\r\n\r\n  static void dft(int n, mod_t *x) {\r\n    for\
    \ (int j = 0, l = n >> 1; j != l; ++j) {\r\n      mod_t u = x[j], v = x[j + l];\r\
    \n      x[j] = u + v, x[j + l] = u - v;\r\n    }\r\n    for (int i = n >> 1; i\
    \ >= 2; i >>= 1) {\r\n      for (int j = 0, l = i >> 1; j != l; ++j) {\r\n   \
    \     mod_t u = x[j], v = x[j + l];\r\n        x[j] = u + v, x[j + l] = u - v;\r\
    \n      }\r\n      for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {\r\
    \n        mod_t root = rt[m];\r\n        for (int k = 0; k != l; ++k) {\r\n  \
    \        mod_t u = x[j + k], v = x[j + k + l] * root;\r\n          x[j + k] =\
    \ u + v, x[j + k + l] = u - v;\r\n        }\r\n      }\r\n    }\r\n  }\r\n\r\n\
    \  static void idft(int n, mod_t *x) {\r\n    for (int i = 2; i < n; i <<= 1)\
    \ {\r\n      for (int j = 0, l = i >> 1; j != l; ++j) {\r\n        mod_t u = x[j],\
    \ v = x[j + l];\r\n        x[j] = u + v, x[j + l] = u - v;\r\n      }\r\n    \
    \  for (int j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {\r\n        mod_t\
    \ root = irt[m];\r\n        for (int k = 0; k != l; ++k) {\r\n          mod_t\
    \ u = x[j + k], v = x[j + k + l];\r\n          x[j + k] = u + v, x[j + k + l]\
    \ = (u - v) * root;\r\n        }\r\n      }\r\n    }\r\n    mod_t iv(mod_t(n).inv());\r\
    \n    for (int j = 0, l = n >> 1; j != l; ++j) {\r\n      mod_t u = x[j] * iv,\
    \ v = x[j + l] * iv;\r\n      x[j] = u + v, x[j + l] = u - v;\r\n    }\r\n  }\r\
    \n\r\n  static void even_dft(int n, mod_t *x) {\r\n    static constexpr mod_t\
    \ IT(mod_t(2).inv());\r\n    for (int i = 0, j = 0; i != n; i += 2, ++j) x[j]\
    \ = IT * (x[i] + x[i + 1]);\r\n  }\r\n\r\n  static void odd_dft(int n, mod_t *x)\
    \ {\r\n    static constexpr mod_t IT(mod_t(2).inv());\r\n    for (int i = 0, j\
    \ = 0; i != n; i += 2, ++j) x[j] = IT * irt[j] * (x[i] - x[i + 1]);\r\n  }\r\n\
    \r\n  static void dft_doubling(int n, mod_t *x) {\r\n    static constexpr mod_t\
    \ g(modint_traits<mod_t>::get_primitive_root_prime());\r\n    std::copy_n(x, n,\
    \ x + n);\r\n    idft(n, x + n);\r\n    mod_t k(1), t(g.pow((modint_traits<mod_t>::get_mod()\
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
    \ namespace lib\r\n\r\n\n#line 18 \"math/formal_power_series/sample_points_shift.hpp\"\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u6837\u672C\u70B9\u5E73\u79FB\uFF08\
    \u901A\u8FC7\u4E0B\u964D\u5E42\u591A\u9879\u5F0F\u5E73\u79FB\uFF09\r\n *\r\n *\
    \ @tparam mod_t NTT \u53CB\u597D\u7684\u6A21\u6570\r\n * @param n \u8FD4\u56DE\
    \u503C\u7684\u70B9\u6570\uFF0C\u9700\u5927\u4E8E\u96F6\r\n * @param pts f(0),\
    \ f(1), \u2026, f(k-1) \u786E\u5B9A\u4E00\u4E2A\u552F\u4E00\u591A\u9879\u5F0F\
    \ mod x^{\\underline{k}}\r\n * @param m \u5E73\u79FB\u8DDD\u79BB f(x) => f(x+m)\r\
    \n * @return std::vector<mod_t> f(m), f(m+1), \u2026, f(m+n-1)\r\n */\r\ntemplate\
    \ <typename mod_t>\r\nstd::vector<mod_t> shift_sample_points_via_FFP(int n, const\
    \ std::vector<mod_t> &pts, mod_t m) {\r\n  return FFP_to_sample_points(n, shift_FFP(sample_points_to_FFP(pts),\
    \ m));\r\n}\r\n\r\ntemplate <typename mod_t>\r\nstd::vector<mod_t> shift_sample_points_via_FFP(const\
    \ std::vector<mod_t> &pts, mod_t m) {\r\n  return shift_sample_points_via_FFP(pts.size(),\
    \ pts, m);\r\n}\r\n\r\n/**\r\n * @brief \u6837\u672C\u70B9\u5E73\u79FB\uFF08\u901A\
    \u8FC7\u62C9\u683C\u6717\u65E5\u63D2\u503C\u516C\u5F0F\uFF09\r\n * @note \u4E0D\
    \u5B89\u5168\u7684\u7B97\u6CD5\r\n * @tparam mod_t NTT \u53CB\u597D\u7684\u6A21\
    \u6570\r\n * @param n \u8FD4\u56DE\u503C\u7684\u70B9\u6570\uFF0C\u9700\u5927\u4E8E\
    \u96F6\r\n * @param pts f(0), f(1), \u2026, f(k-1) \u786E\u5B9A\u4E00\u4E2A\u552F\
    \u4E00\u591A\u9879\u5F0F mod x^{\\underline{k}}\r\n * @param m \u5E73\u79FB\u8DDD\
    \u79BB f(x) => f(x+m)\r\n * @return std::vector<mod_t> f(m), f(m+1), \u2026, f(m+n-1)\r\
    \n */\r\ntemplate <typename mod_t>\r\nstd::vector<mod_t> shift_sample_points_unsafe(int\
    \ n, const std::vector<mod_t> &pts, mod_t m) {\r\n  int s = pts.size(), deg_A\
    \ = s - 1;\r\n  NTTBinomial<mod_t> bi(s);\r\n  std::vector<mod_t> A(s), B(deg_A\
    \ + n), p_sum(deg_A + n);\r\n  for (int i = 0; i < s; ++i) {\r\n    A[i] = pts[i]\
    \ * bi.ifac_unsafe(i) * bi.ifac_unsafe(deg_A - i);\r\n    if ((deg_A - i) & 1)\
    \ A[i] = -A[i];\r\n  }\r\n  const mod_t ZERO(0);\r\n  for (int i = 0; i < deg_A\
    \ + n; ++i) {\r\n    B[i] = m + mod_t(i - deg_A);\r\n    assert(B[i] != ZERO);\r\
    \n  }\r\n  std::partial_sum(B.begin(), B.end(), p_sum.begin(), std::multiplies<>());\r\
    \n  mod_t p_inv = mod_t(1) / p_sum.back();\r\n  for (int i = deg_A + n - 1; i\
    \ > 0; --i) {\r\n    mod_t t = p_inv * B[i];\r\n    B[i]    = p_inv * p_sum[i\
    \ - 1];\r\n    p_inv   = t;\r\n  }\r\n  B[0]    = p_inv;\r\n  p_sum   = B;\r\n\
    \  int len = get_ntt_len(s + s - 1 + n - (s < 2 ? 0 : deg_A - 1) - 1);\r\n  p_sum.resize(len,\
    \ ZERO);\r\n  A.resize(len, ZERO);\r\n  dft(A), dft(p_sum);\r\n  for (int i =\
    \ 0; i < len; ++i) A[i] *= p_sum[i];\r\n  idft(A);\r\n  mod_t coeff(m);\r\n  for\
    \ (int i = 1; i < s; ++i) coeff *= m - mod_t(i);\r\n  for (int i = 0; i < n; ++i)\
    \ A[i] = A[deg_A + i] * coeff, coeff *= (m + mod_t(i + 1)) * B[i];\r\n  A.resize(n);\r\
    \n  return A;\r\n}\r\n\r\ntemplate <typename mod_t>\r\nstd::vector<mod_t> shift_sample_points_unsafe(const\
    \ std::vector<mod_t> &pts, mod_t m) {\r\n  return shift_sample_points_unsafe(pts.size(),\
    \ pts, m);\r\n}\r\n\r\n} // namespace lib\r\n\r\n\n"
  code: "#ifndef SAMPLE_POINTS_SHIFT_HEADER_HPP\r\n#define SAMPLE_POINTS_SHIFT_HEADER_HPP\r\
    \n\r\n/**\r\n * @brief sample points shift / \u6837\u672C\u70B9\u5E73\u79FB\r\n\
    \ * @docs docs/math/formal_power_series/sample_points_shift.md\r\n */\r\n\r\n\
    #include <cassert>\r\n#include <functional>\r\n#include <numeric>\r\n#include\
    \ <utility>\r\n#include <vector>\r\n\r\n#include \"NTT_binomial.hpp\"\r\n#include\
    \ \"falling_factorial_polynomial_multiplication.hpp\"\r\n#include \"radix_2_NTT.hpp\"\
    \r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief \u6837\u672C\u70B9\u5E73\u79FB\
    \uFF08\u901A\u8FC7\u4E0B\u964D\u5E42\u591A\u9879\u5F0F\u5E73\u79FB\uFF09\r\n *\r\
    \n * @tparam mod_t NTT \u53CB\u597D\u7684\u6A21\u6570\r\n * @param n \u8FD4\u56DE\
    \u503C\u7684\u70B9\u6570\uFF0C\u9700\u5927\u4E8E\u96F6\r\n * @param pts f(0),\
    \ f(1), \u2026, f(k-1) \u786E\u5B9A\u4E00\u4E2A\u552F\u4E00\u591A\u9879\u5F0F\
    \ mod x^{\\underline{k}}\r\n * @param m \u5E73\u79FB\u8DDD\u79BB f(x) => f(x+m)\r\
    \n * @return std::vector<mod_t> f(m), f(m+1), \u2026, f(m+n-1)\r\n */\r\ntemplate\
    \ <typename mod_t>\r\nstd::vector<mod_t> shift_sample_points_via_FFP(int n, const\
    \ std::vector<mod_t> &pts, mod_t m) {\r\n  return FFP_to_sample_points(n, shift_FFP(sample_points_to_FFP(pts),\
    \ m));\r\n}\r\n\r\ntemplate <typename mod_t>\r\nstd::vector<mod_t> shift_sample_points_via_FFP(const\
    \ std::vector<mod_t> &pts, mod_t m) {\r\n  return shift_sample_points_via_FFP(pts.size(),\
    \ pts, m);\r\n}\r\n\r\n/**\r\n * @brief \u6837\u672C\u70B9\u5E73\u79FB\uFF08\u901A\
    \u8FC7\u62C9\u683C\u6717\u65E5\u63D2\u503C\u516C\u5F0F\uFF09\r\n * @note \u4E0D\
    \u5B89\u5168\u7684\u7B97\u6CD5\r\n * @tparam mod_t NTT \u53CB\u597D\u7684\u6A21\
    \u6570\r\n * @param n \u8FD4\u56DE\u503C\u7684\u70B9\u6570\uFF0C\u9700\u5927\u4E8E\
    \u96F6\r\n * @param pts f(0), f(1), \u2026, f(k-1) \u786E\u5B9A\u4E00\u4E2A\u552F\
    \u4E00\u591A\u9879\u5F0F mod x^{\\underline{k}}\r\n * @param m \u5E73\u79FB\u8DDD\
    \u79BB f(x) => f(x+m)\r\n * @return std::vector<mod_t> f(m), f(m+1), \u2026, f(m+n-1)\r\
    \n */\r\ntemplate <typename mod_t>\r\nstd::vector<mod_t> shift_sample_points_unsafe(int\
    \ n, const std::vector<mod_t> &pts, mod_t m) {\r\n  int s = pts.size(), deg_A\
    \ = s - 1;\r\n  NTTBinomial<mod_t> bi(s);\r\n  std::vector<mod_t> A(s), B(deg_A\
    \ + n), p_sum(deg_A + n);\r\n  for (int i = 0; i < s; ++i) {\r\n    A[i] = pts[i]\
    \ * bi.ifac_unsafe(i) * bi.ifac_unsafe(deg_A - i);\r\n    if ((deg_A - i) & 1)\
    \ A[i] = -A[i];\r\n  }\r\n  const mod_t ZERO(0);\r\n  for (int i = 0; i < deg_A\
    \ + n; ++i) {\r\n    B[i] = m + mod_t(i - deg_A);\r\n    assert(B[i] != ZERO);\r\
    \n  }\r\n  std::partial_sum(B.begin(), B.end(), p_sum.begin(), std::multiplies<>());\r\
    \n  mod_t p_inv = mod_t(1) / p_sum.back();\r\n  for (int i = deg_A + n - 1; i\
    \ > 0; --i) {\r\n    mod_t t = p_inv * B[i];\r\n    B[i]    = p_inv * p_sum[i\
    \ - 1];\r\n    p_inv   = t;\r\n  }\r\n  B[0]    = p_inv;\r\n  p_sum   = B;\r\n\
    \  int len = get_ntt_len(s + s - 1 + n - (s < 2 ? 0 : deg_A - 1) - 1);\r\n  p_sum.resize(len,\
    \ ZERO);\r\n  A.resize(len, ZERO);\r\n  dft(A), dft(p_sum);\r\n  for (int i =\
    \ 0; i < len; ++i) A[i] *= p_sum[i];\r\n  idft(A);\r\n  mod_t coeff(m);\r\n  for\
    \ (int i = 1; i < s; ++i) coeff *= m - mod_t(i);\r\n  for (int i = 0; i < n; ++i)\
    \ A[i] = A[deg_A + i] * coeff, coeff *= (m + mod_t(i + 1)) * B[i];\r\n  A.resize(n);\r\
    \n  return A;\r\n}\r\n\r\ntemplate <typename mod_t>\r\nstd::vector<mod_t> shift_sample_points_unsafe(const\
    \ std::vector<mod_t> &pts, mod_t m) {\r\n  return shift_sample_points_unsafe(pts.size(),\
    \ pts, m);\r\n}\r\n\r\n} // namespace lib\r\n\r\n#endif"
  dependsOn:
  - math/formal_power_series/NTT_binomial.hpp
  - math/formal_power_series/falling_factorial_polynomial_multiplication.hpp
  - math/formal_power_series/convolution.hpp
  - math/formal_power_series/radix_2_NTT.hpp
  - traits/modint.hpp
  isVerificationFile: false
  path: math/formal_power_series/sample_points_shift.hpp
  requiredBy: []
  timestamp: '2021-07-17 06:24:28+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/formal_power_series/sample_points_shift.hpp
layout: document
redirect_from:
- /library/math/formal_power_series/sample_points_shift.hpp
- /library/math/formal_power_series/sample_points_shift.hpp.html
title: "sample points shift / \u6837\u672C\u70B9\u5E73\u79FB"
---
## 样本点平移

给出 $f(0),f(1),\dots f(n)$ 求出 $f(c),f(c+1),\dots f(c+n)$ ，其中 $f\in\mathbb{F} _ p\lbrack x\rbrack,c\in\mathbb{F} _ p\setminus \lbrace 0\rbrace ,\deg(f)\leq n$ 。发现可使用下降幂多项式的平移完成，我们考虑拉格朗日插值公式，有

$$
\begin{aligned}
f(x)&=\sum _ {0\leq i\leq n}f(i)\prod _ {0\leq j\leq n\land j\neq i}\frac{x-j}{i-j}\\
&=\sum _ {0\leq i\leq n}f(i)\frac{x!}{(x-n-1)!(x-i)}\frac{(-1)^{n-i}}{i!(n-i)!}\\
&=\frac{x!}{(x-n-1)!}\sum _ {0\leq i\leq n}\frac{f(i)}{(x-i)}\frac{(-1)^{n-i}}{i!(n-i)!}
\end{aligned}
$$

上式虽然是一个卷积形式但是 $x-i$ 在分母上可能为零，故该方法有局限性，我们假设 $\lbrace 0,1,\dots ,n\rbrace \cap\lbrace c,c+1,\dots c+n\rbrace =\emptyset$ 那么此时令

$$
A(x)=\sum _ {0\leq i\leq n}\frac{f(i)(-1)^{n-i}}{i!(n-i)!}x^i,\quad B(x)=\sum _ {i\geq 0}\frac{1}{c-n+i}x^i
$$

那么对于 $t\geq 0$ 有

$$
\begin{aligned}
\lbrack x^{n+t}\rbrack (A(x)B(x))&=\sum _ {i=0}^{n+t}\lbrack x^i\rbrack A(x)\lbrack x^{n+t-i}\rbrack B(x)\\
&=\sum _ {i=0}^{n}\frac{f(i)(-1)^{n-i}}{i!(n-i)!}\frac{1}{c+t-i}\\
&=\frac{(c+t-n-1)!}{(c+t)!}f(c+t)
\end{aligned}
$$

也就是说我们可以求出 $f(c),f(c+1),\dots $ 只要 $B(x)$ 足够“长”且不要“跨越”零导致分母为零的话上述算法是正确的。