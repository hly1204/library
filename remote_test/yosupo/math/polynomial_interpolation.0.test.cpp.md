---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/NTT_binomial.hpp
    title: "NTT prime binomial / NTT \u7D20\u6570\u7528\u4E8C\u9879\u5F0F\u7CFB\u6570"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/formal_power_series.hpp
    title: "basic operations of formal power series / \u5F62\u5F0F\u5E42\u7EA7\u6570\
      \u7684\u57FA\u672C\u64CD\u4F5C"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/polynomial.hpp
    title: "polynomial / \u591A\u9879\u5F0F"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/subproduct_tree.hpp
    title: "multi-point evaluation & interpolation / \u591A\u70B9\u6C42\u503C\u548C\
      \u63D2\u503C"
  - icon: ':heavy_check_mark:'
    path: modint/Montgomery_modint.hpp
    title: "Montgomery modint / Montgomery \u53D6\u6A21\u7C7B"
  - icon: ':heavy_check_mark:'
    path: traits/modint.hpp
    title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/polynomial_interpolation
    links:
    - https://judge.yosupo.jp/problem/polynomial_interpolation
  bundledCode: "#line 1 \"remote_test/yosupo/math/polynomial_interpolation.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/polynomial_interpolation\"\
    \r\n\r\n#include <iostream>\r\n#include <vector>\r\n\r\n#line 1 \"math/formal_power_series/polynomial.hpp\"\
    \n\n\n\r\n/**\r\n * @brief polynomial / \u591A\u9879\u5F0F\r\n * @docs docs/math/formal_power_series/polynomial.md\r\
    \n */\r\n\r\n#line 1 \"math/formal_power_series/NTT_binomial.hpp\"\n\n\n\r\n/**\r\
    \n * @brief NTT prime binomial / NTT \u7D20\u6570\u7528\u4E8C\u9879\u5F0F\u7CFB\
    \u6570\r\n *\r\n */\r\n\r\n#line 10 \"math/formal_power_series/NTT_binomial.hpp\"\
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
    \ fac_, ifac_;\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line 1 \"math/formal_power_series/formal_power_series.hpp\"\
    \n\n\n\r\n/**\r\n * @brief basic operations of formal power series / \u5F62\u5F0F\
    \u5E42\u7EA7\u6570\u7684\u57FA\u672C\u64CD\u4F5C\r\n * @docs docs/math/formal_power_series/formal_power_series.md\r\
    \n */\r\n\r\n#include <algorithm>\r\n#include <cassert>\r\n#include <numeric>\r\
    \n#include <tuple>\r\n#include <utility>\r\n#line 15 \"math/formal_power_series/formal_power_series.hpp\"\
    \n\r\n#line 1 \"traits/modint.hpp\"\n\n\n\r\n/**\r\n * @brief modint traits /\
    \ \u53D6\u6A21\u7C7B\u8403\u53D6\r\n *\r\n */\r\n\r\nnamespace lib {\r\n\r\ntemplate\
    \ <typename mod_t>\r\nstruct modint_traits {\r\n  using type = typename mod_t::value_type;\r\
    \n  static constexpr type get_mod() { return mod_t::get_mod(); }\r\n  static constexpr\
    \ type get_primitive_root_prime() { return mod_t::get_primitive_root_prime();\
    \ }\r\n};\r\n\r\n} // namespace lib\r\n\r\n\n#line 1 \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n\n\n\r\n/**\r\n * @brief radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362\r\n\
    \ * @docs docs/math/formal_power_series/radix_2_NTT.md\r\n */\r\n\r\n#line 11\
    \ \"math/formal_power_series/radix_2_NTT.hpp\"\n#include <cstdint>\r\n#line 13\
    \ \"math/formal_power_series/radix_2_NTT.hpp\"\n\r\n#line 15 \"math/formal_power_series/radix_2_NTT.hpp\"\
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
    \n}\r\n\r\n} // namespace lib\r\n\r\n\n#line 19 \"math/formal_power_series/formal_power_series.hpp\"\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @note \u5FC5\u987B\u4F7F\u7528 NTT \u53CB\
    \u597D\u7684\u6A21\u6570\uFF01\uFF01\uFF01\r\n *       \u5728\u4F7F\u7528\u6A21\
    \u677F\u7C7B\u7EE7\u627F\u65F6\uFF0C\u5BF9\u4E8E\u7EE7\u627F\u6765\u7684 public\
    \ \u6210\u5458\u51FD\u6570\uFF0C\u8981\u4E48\u4F7F\u7528 using \u6765\u58F0\u660E\
    \uFF0C\u8981\u4E48\u4F7F\u7528\u57DF\u9650\u5B9A\u7B26\r\n *       \u8981\u4E48\
    \u4F7F\u7528 this \u6307\u9488\uFF0C\u8FD9\u6837\u5728\u7B2C\u4E00\u6B21\u626B\
    \u63CF\u65F6\u4E0D\u4F1A\u5904\u7406\uFF0C\u7B2C\u4E8C\u6B21\u624D\u4F1A\u5206\
    \u6790\u57FA\u7C7B\u4E2D\u7684\u51FD\u6570\uFF0C\r\n *       \u5426\u5219\u4E0D\
    \u80FD\u901A\u8FC7\u7F16\u8BD1\u3002MSVC \u56E0\u4E3A\u6709\u6269\u5C55\u7684\u539F\
    \u56E0\u53EF\u4EE5\u901A\u8FC7\u7F16\u8BD1\uFF0C\u4F46\u6807\u51C6\u89C4\u5B9A\
    \u662F\u8FD9\u6837\u3002\r\n *       \u82E5\u4E0D\u662F\u6A21\u677F\u7C7B\u7EE7\
    \u627F\u5219\u6CA1\u6709\u8FD9\u6837\u7684\u95EE\u9898\u3002\r\n *\r\n */\r\n\
    template <typename mod_t>\r\nclass FormalPowerSeries : public std::vector<mod_t>\
    \ {\r\nprivate:\r\n  using vec = std::vector<mod_t>;\r\n  using fps = FormalPowerSeries<mod_t>;\r\
    \n\r\npublic:\r\n  using std::vector<mod_t>::vector;\r\n  using value_type = mod_t;\r\
    \n\r\n  /**\r\n   * @brief \u83B7\u53D6\u5EA6\u6570\r\n   * @note \u7279\u4F8B\
    \u4E3A deg(0)=-1\r\n   * @return int\r\n   */\r\n  int deg() const {\r\n    static\
    \ constexpr mod_t Z = 0;\r\n    int n                    = int(this->size()) -\
    \ 1;\r\n    while (n >= 0 && this->operator[](n) == Z) --n;\r\n    return n;\r\
    \n  }\r\n\r\n  /**\r\n   * @brief \u83B7\u53D6\u6700\u9AD8\u6B21\u9879\u7684\u7CFB\
    \u6570\r\n   * @return mod_t\r\n   */\r\n  mod_t leading_coeff() const {\r\n \
    \   int d = deg();\r\n    return d == -1 ? mod_t(0) : this->operator[](d);\r\n\
    \  }\r\n\r\n  /**\r\n   * @brief \u53BB\u9664\u5C3E 0 \uFF0C\u4F46\u5982\u679C\
    \u53EA\u6709\u4E00\u4E2A 0 \u5219\u4F1A\u4FDD\u7559\r\n   */\r\n  void shrink()\
    \ { this->resize(std::max(deg() + 1, 1)); }\r\n  fps slice() const { return fps(*this);\
    \ }\r\n  fps slice(int n) const {\r\n    assert(n >= 0);\r\n    int sz = this->size();\r\
    \n    if (sz >= n) return fps(this->begin(), this->begin() + n);\r\n    fps res(*this);\r\
    \n    res.resize(n, mod_t(0));\r\n    return res;\r\n  }\r\n\r\n  fps deriv()\
    \ const {\r\n    int n = this->size();\r\n    if (n <= 1) return {0};\r\n    fps\
    \ res(n - 1);\r\n    for (int i = 1; i != n; ++i) res[i - 1] = this->operator[](i)\
    \ * mod_t(i);\r\n    return res;\r\n  }\r\n\r\n  fps integr(const mod_t &c = mod_t(0))\
    \ const {\r\n    int n = this->size() + 1;\r\n    NTTBinomial<mod_t> bi(n);\r\n\
    \    fps res(n);\r\n    res[0] = c;\r\n    for (int i = 1; i != n; ++i) res[i]\
    \ = this->operator[](i - 1) * bi.inv_unsafe(i);\r\n    return res;\r\n  }\r\n\r\
    \n  fps operator-() const {\r\n    fps res(this->size());\r\n    for (int i =\
    \ 0, e = this->size(); i != e; ++i) res[i] = -this->operator[](i);\r\n    return\
    \ res;\r\n  }\r\n\r\n  fps &operator+=(const fps &rhs) {\r\n    if (this->size()\
    \ < rhs.size()) this->resize(rhs.size(), mod_t(0));\r\n    for (int i = 0, e =\
    \ rhs.size(); i != e; ++i) this->operator[](i) += rhs[i];\r\n    return *this;\r\
    \n  }\r\n  fps &operator-=(const fps &rhs) {\r\n    if (this->size() < rhs.size())\
    \ this->resize(rhs.size(), mod_t(0));\r\n    for (int i = 0, e = rhs.size(); i\
    \ != e; ++i) this->operator[](i) -= rhs[i];\r\n    return *this;\r\n  }\r\n  fps\
    \ &operator*=(const fps &rhs) {\r\n    int n = this->size(), m = rhs.size();\r\
    \n    if (std::min(n, m) <= 32) {\r\n      fps res(n + m - 1, mod_t(0));\r\n \
    \     for (int i = 0; i != n; ++i) {\r\n        for (int j = 0; j != m; ++j) {\
    \ res[i + j] += this->operator[](i) * rhs[j]; }\r\n      }\r\n      return this->operator=(res);\r\
    \n    }\r\n    int len = get_ntt_len(n + m - 1);\r\n    this->resize(len, mod_t(0));\r\
    \n    if (this == &rhs) {\r\n      dft(len, this->data());\r\n      for (int i\
    \ = 0; i != len; ++i) this->operator[](i) *= this->operator[](i);\r\n      idft(len,\
    \ this->data());\r\n      this->resize(n + m - 1);\r\n      return *this;\r\n\
    \    }\r\n    auto b = rhs.slice(len);\r\n    dft(len, this->data());\r\n    dft(len,\
    \ b.data());\r\n    for (int i = 0; i != len; ++i) this->operator[](i) *= b[i];\r\
    \n    idft(len, this->data());\r\n    this->resize(n + m - 1);\r\n    return *this;\r\
    \n  }\r\n\r\n  fps &operator/=(const fps &rhs) { // 13E\r\n    int n = this->size();\r\
    \n    if (n == 0) return *this;\r\n    assert(rhs[0] != 0);\r\n    if (n == 1)\
    \ {\r\n      this->operator[](0) /= rhs[0];\r\n      return *this;\r\n    }\r\n\
    \    int len = get_ntt_len(n), len2 = len >> 1;\r\n    fps work_tmp1(rhs.inv(len2)),\
    \ work_tmp2(slice(len2)), work_tmp3(rhs.slice(len));\r\n    // rhs.inv(len2) \u82B1\
    \u8D39 5E\r\n    work_tmp1.resize(len, mod_t(0));\r\n    dft(len, work_tmp1.data());\
    \ // 1E\r\n    work_tmp2.resize(len, mod_t(0));\r\n    dft(len, work_tmp2.data());\
    \ // 1E\r\n    for (int i = 0; i != len; ++i) work_tmp2[i] *= work_tmp1[i];\r\n\
    \    idft(len, work_tmp2.data()); // 1E\r\n    std::copy_n(work_tmp2.begin(),\
    \ len2, this->begin());\r\n    std::fill_n(work_tmp2.begin() + len2, len2, mod_t(0));\r\
    \n    dft(len, work_tmp2.data()); // 1E\r\n    dft(len, work_tmp3.data()); //\
    \ 1E\r\n    for (int i = 0; i != len; ++i) work_tmp3[i] *= work_tmp2[i];\r\n \
    \   idft(len, work_tmp3.data()); // 1E\r\n    std::fill_n(work_tmp3.begin(), len2,\
    \ mod_t(0));\r\n    this->resize(len);\r\n    for (int i = len2; i != len; ++i)\
    \ work_tmp3[i] = this->operator[](i) - work_tmp3[i];\r\n    dft(len, work_tmp3.data());\
    \ // 1E\r\n    for (int i = 0; i != len; ++i) work_tmp3[i] *= work_tmp1[i];\r\n\
    \    idft(len, work_tmp3.data()); // 1E\r\n    std::copy_n(work_tmp3.begin() +\
    \ len2, n - len2, this->begin() + len2);\r\n    this->resize(n);\r\n    return\
    \ *this;\r\n  }\r\n\r\n  fps inv(int n) const { // 10E\r\n    assert(n > 0);\r\
    \n    assert(this->operator[](0) != 0);\r\n    if (n == 1) return {mod_t(1) /\
    \ this->operator[](0)};\r\n    int len = get_ntt_len(n);\r\n    fps res(len, mod_t(0)),\
    \ work_tmp1(len), work_tmp2(len), cpy(slice(len));\r\n    res[0] = mod_t(1) /\
    \ this->operator[](0);\r\n    for (int i = 2; i <= len; i <<= 1) {\r\n      std::copy_n(cpy.begin(),\
    \ i, work_tmp1.begin());\r\n      dft(i, work_tmp1.data()); // 2E\r\n      std::copy_n(res.begin(),\
    \ i, work_tmp2.begin());\r\n      dft(i, work_tmp2.data()); // 2E\r\n      for\
    \ (int j = 0; j != i; ++j) work_tmp1[j] *= work_tmp2[j];\r\n      idft(i, work_tmp1.data());\
    \ // 2E\r\n      std::fill_n(work_tmp1.begin(), i >> 1, mod_t(0));\r\n      dft(i,\
    \ work_tmp1.data()); // 2E\r\n      for (int j = 0; j != i; ++j) work_tmp1[j]\
    \ *= work_tmp2[j];\r\n      idft(i, work_tmp1.data()); // 2E\r\n      for (int\
    \ j = i >> 1; j != i; ++j) res[j] = -work_tmp1[j];\r\n    }\r\n    res.resize(n);\r\
    \n    return res;\r\n  }\r\n\r\n  fps div(int n, const fps &rhs) const { return\
    \ slice(n) /= rhs; }\r\n\r\n  mod_t div_at(const fps &rhs, unsigned long long\
    \ k) const { // [x^k](*this)/rhs\r\n    // \u5F53 this->deg>rhs.deg() \u65F6\u6211\
    \u4EEC\u53EF\u4EE5\u8BA1\u7B97\u4E00\u6B21\u6B27\u51E0\u91CC\u5F97\u9664\u6CD5\
    \u5F97\u5230\u5546\u548C\u4F59\u6570 (q, r)\r\n    // q + r/rhs \u6CE8\u610F\u6B64\
    \u65F6\u82E5 k<=q.deg() \u5219\u7B54\u6848\u9700\u8981\u52A0\u4E0A[x^k]q\uFF0C\
    \u5426\u5219\u7684\u8BDD\u6211\u4EEC\u8F6C\u800C\u8BA1\u7B97 r/rhs\r\n    // \u4F46\
    \u662F\u6B64\u5904\u6CA1\u6709\u4F7F\u7528\u8FD9\u4E2A\u65B9\u6CD5\r\n    assert(rhs.deg()\
    \ >= 0);\r\n    assert(rhs[0] != 0);\r\n    int offset = std::max(deg(), rhs.deg())\
    \ + 1;\r\n    if (k <= offset) return div(k + 1, rhs).back();\r\n    fps cpy(*this),\
    \ rhs_cpy(rhs);\r\n    int len = get_ntt_len((offset << 1) - 1);\r\n    cpy.resize(len,\
    \ mod_t(0));\r\n    rhs_cpy.resize(len, mod_t(0));\r\n    dft(len, cpy.data());\r\
    \n    dft(len, rhs_cpy.data());\r\n    for (;;) {\r\n      for (int i = 0; i !=\
    \ len; ++i) cpy[i] *= rhs_cpy[i ^ 1];\r\n      if (k & 1) {\r\n        NTT<mod_t>::odd_dft(len,\
    \ cpy.data());\r\n      } else {\r\n        NTT<mod_t>::even_dft(len, cpy.data());\r\
    \n      }\r\n      for (int i = 0; i != len; i += 2) rhs_cpy[i] = rhs_cpy[i +\
    \ 1] = rhs_cpy[i] * rhs_cpy[i + 1];\r\n      NTT<mod_t>::even_dft(len, rhs_cpy.data());\r\
    \n      k >>= 1;\r\n      if (k <= offset) break;\r\n      NTT<mod_t>::dft_doubling(len\
    \ >> 1, cpy.data());\r\n      NTT<mod_t>::dft_doubling(len >> 1, rhs_cpy.data());\r\
    \n    }\r\n    cpy.resize(len >> 1);\r\n    rhs_cpy.resize(len >> 1);\r\n    idft(len\
    \ >> 1, cpy.data());\r\n    idft(len >> 1, rhs_cpy.data());\r\n    return cpy.div(k\
    \ + 1, rhs_cpy).back();\r\n  }\r\n\r\n  fps log(int n) const {\r\n    assert(n\
    \ > 0);\r\n    assert(!this->empty());\r\n    assert(this->operator[](0) == 1);\r\
    \n    if (this->size() == 1) return fps(n, mod_t(0));\r\n    return deriv().div(n\
    \ - 1, *this).integr();\r\n  }\r\n\r\n  // TODO\r\n  fps exp(int n) const;\r\n\
    \r\n  // TODO\r\n  fps pow(int n, mod_t e) const;\r\n\r\n  // TODO\r\n  fps sqrt(int\
    \ n) const;\r\n\r\n  friend fps operator+(const fps &lhs, const fps &rhs) { return\
    \ fps(lhs) += rhs; }\r\n  friend fps operator-(const fps &lhs, const fps &rhs)\
    \ { return fps(lhs) -= rhs; }\r\n  friend fps operator*(const fps &lhs, const\
    \ fps &rhs) { return fps(lhs) *= rhs; }\r\n  friend fps operator/(const fps &lhs,\
    \ const fps &rhs) { return fps(lhs) /= rhs; }\r\n};\r\n\r\ntemplate <typename\
    \ mod_t>\r\nusing FPS = FormalPowerSeries<mod_t>;\r\n\r\n} // namespace lib\r\n\
    \r\n\n#line 11 \"math/formal_power_series/polynomial.hpp\"\n\r\nnamespace lib\
    \ {\r\n\r\n/**\r\n * @brief \u591A\u9879\u5F0F\u7C7B\r\n * @note \u57FA\u7C7B\
    \ FormalPowerSeries \u4E2D\u51FD\u6570\u90FD\u6CA1\u6709\u4F7F\u7528 virtual\r\
    \n *       \u6240\u4EE5\u5728\u8BE5\u7C7B\u4E2D\u6709\u5B9A\u4E49\u76F8\u540C\u7684\
    \u51FD\u6570\u5219\u4F1A\u963B\u6B62\u8C03\u7528\u57FA\u7C7B\u7684\u51FD\u6570\
    \r\n *       \u8FD9\u88AB\u79F0\u4E3A\u9690\u85CF\uFF08 hide \uFF09\u3002\r\n\
    \ *       \u800C\u5982\u679C\u4F7F\u7528\u4E86 virtual \u5219\u88AB\u79F0\u4E3A\
    \u8986\u76D6\uFF08 override \uFF09\uFF0C\u800C\u8986\u76D6\u4F1A\u5BFC\u51FA\u591A\
    \u6001\u3002\r\n */\r\ntemplate <typename mod_t>\r\nclass Polynomial : public\
    \ FormalPowerSeries<mod_t> {\r\nprivate:\r\n  using fps  = FormalPowerSeries<mod_t>;\r\
    \n  using poly = Polynomial<mod_t>;\r\n\r\npublic:\r\n  using FormalPowerSeries<mod_t>::FormalPowerSeries;\r\
    \n  using value_type = mod_t;\r\n\r\n  // \u4F7F\u5F97\u80FD\u591F\u4ECE FormalPowerSeries\
    \ \u8F6C\u6362\u4E3A Polynomial \u7C7B\u578B\uFF0C\u4F46\u4E0D\u6E05\u695A\u662F\
    \u5426\u6709\u4EC0\u4E48\u95EE\u9898\r\n  Polynomial(const fps &rhs) : fps(rhs)\
    \ {}\r\n  Polynomial(fps &&rhs) : fps(std::move(rhs)) {}\r\n\r\n  poly operator-()\
    \ const {\r\n    poly res = this->fps::operator-();\r\n    res.shrink();\r\n \
    \   return res;\r\n  }\r\n  poly &operator+=(const poly &rhs) {\r\n    this->fps::operator+=(rhs);\r\
    \n    this->shrink();\r\n    return *this;\r\n  }\r\n  poly &operator-=(const\
    \ poly &rhs) {\r\n    this->fps::operator-=(rhs);\r\n    this->shrink();\r\n \
    \   return *this;\r\n  }\r\n  poly &operator*=(const poly &rhs) {\r\n    this->fps::operator*=(rhs);\r\
    \n    this->shrink();\r\n    return *this;\r\n  }\r\n  poly &operator/=(const\
    \ poly &rhs) {\r\n    assert(rhs.deg() >= 0);\r\n    this->shrink();\r\n    int\
    \ quo_size = this->deg() - rhs.deg() + 1;\r\n    if (quo_size <= 0) {\r\n    \
    \  this->resize(1);\r\n      this->operator[](0) = 0;\r\n      return *this;\r\
    \n    }\r\n    poly rhs_cpy(rhs);\r\n    rhs_cpy.shrink();\r\n    std::reverse(this->begin(),\
    \ this->end());\r\n    std::reverse(rhs_cpy.begin(), rhs_cpy.end());\r\n    poly\
    \ quo(this->div(quo_size, rhs_cpy));\r\n    this->resize(quo_size);\r\n    std::reverse_copy(quo.begin(),\
    \ quo.end(), this->begin());\r\n    return *this;\r\n  }\r\n  poly &operator%=(const\
    \ poly &rhs) {\r\n    // f/g => f=gq+r, deg(r)<deg(g) \u5728\u8FD9\u91CC f \u5C31\
    \u662F (*this) \u800C g \u5C31\u662F rhs\r\n    // r=f-gq (mod ((x^deg(rhs)) -\
    \ 1))\r\n    // \u6240\u4EE5\u6211\u4EEC\u505A NTT \u7684\u957F\u5EA6\u53EF\u4EE5\
    \u662F O(deg(rhs)) \u7EA7\u522B\u7684\r\n    int rem_size = rhs.deg();\r\n   \
    \ assert(rem_size >= 0);\r\n    if (rem_size == 0) {\r\n      this->resize(1);\r\
    \n      this->operator[](0) = 0;\r\n      return *this;\r\n    }\r\n    this->shrink();\r\
    \n    if (this->deg() < rem_size) return *this;\r\n    poly quo((*this) / rhs),\
    \ rhs_cpy(rhs);\r\n    int len = get_ntt_len(rem_size);\r\n    // \u4EE4 (*this)\
    \ \u548C quo \u548C rhs_cpy \u90FD\u5728 mod ((x^len) - 1) \u610F\u4E49\u4E0B\r\
    \n    int mask = len - 1;\r\n    for (int i = len, e = this->size(); i < e; ++i)\r\
    \n      this->operator[](i &mask) += this->operator[](i);\r\n    for (int i =\
    \ len, e = quo.size(); i < e; ++i) quo[i & mask] += quo[i];\r\n    for (int i\
    \ = len, e = rhs_cpy.size(); i < e; ++i) rhs_cpy[i & mask] += rhs_cpy[i];\r\n\
    \    this->resize(len, mod_t(0));\r\n    quo.resize(len, mod_t(0));\r\n    rhs_cpy.resize(len,\
    \ mod_t(0));\r\n    dft(len, rhs_cpy.data());\r\n    dft(len, quo.data());\r\n\
    \    for (int i = 0; i != len; ++i) rhs_cpy[i] *= quo[i];\r\n    idft(len, rhs_cpy.data());\r\
    \n    this->resize(rem_size);\r\n    for (int i = 0; i != rem_size; ++i) this->operator[](i)\
    \ -= rhs_cpy[i];\r\n    this->shrink();\r\n    return *this;\r\n  }\r\n  std::pair<poly,\
    \ poly> divmod(const poly &rhs) const {\r\n    int rem_size = rhs.deg();\r\n \
    \   assert(rem_size >= 0);\r\n    if (rem_size == 0) return {(*this) * poly{rhs[0].inv()},\
    \ poly{0}};\r\n    poly cpy(*this);\r\n    cpy.shrink();\r\n    if (cpy.deg()\
    \ < rem_size) return {poly{0}, cpy};\r\n    poly quo(cpy / rhs), quo_cpy(quo),\
    \ rhs_cpy(rhs);\r\n    int len = get_ntt_len(rem_size), mask = len - 1;\r\n  \
    \  for (int i = len, e = cpy.size(); i < e; ++i) cpy[i & mask] += cpy[i];\r\n\
    \    for (int i = len, e = quo_cpy.size(); i < e; ++i) quo_cpy[i & mask] += quo_cpy[i];\r\
    \n    for (int i = len, e = rhs_cpy.size(); i < e; ++i) rhs_cpy[i & mask] += rhs_cpy[i];\r\
    \n    cpy.resize(len, mod_t(0));\r\n    quo_cpy.resize(len, mod_t(0));\r\n   \
    \ rhs_cpy.resize(len, mod_t(0));\r\n    dft(len, rhs_cpy.data());\r\n    dft(len,\
    \ quo_cpy.data());\r\n    for (int i = 0; i != len; ++i) rhs_cpy[i] *= quo_cpy[i];\r\
    \n    idft(len, rhs_cpy.data());\r\n    cpy.resize(rem_size);\r\n    for (int\
    \ i = 0; i != rem_size; ++i) cpy[i] -= rhs_cpy[i];\r\n    cpy.shrink();\r\n  \
    \  return {quo, cpy};\r\n  }\r\n\r\n  poly pow_mod(unsigned long long e, const\
    \ poly &mod) const {\r\n    int rem_size = mod.deg();\r\n    assert(rem_size >=\
    \ 0);\r\n    if (rem_size == 0) return poly{0};\r\n    poly res{1}, cpy(*this\
    \ % mod), mod_cpy(mod), rev_mod(mod);\r\n    mod_cpy.shrink();\r\n    rev_mod.shrink();\r\
    \n    std::reverse(rev_mod.begin(), rev_mod.end());        // x^{deg(mod)}mod(-x)\r\
    \n    int len          = get_ntt_len((rem_size << 1) - 1); // \u4E24\u4E2A rem_size\
    \ \u957F\u7684\u591A\u9879\u5F0F\u76F8\u4E58\r\n    int len2         = get_ntt_len(rem_size);\r\
    \n    int mask         = len2 - 1;\r\n    int max_quo_size = rem_size;\r\n#define\
    \ MODIFY_POLY(t)                                                  \\\r\n  {  \
    \                                                                   \\\r\n   \
    \ for (int i = len2, ie = t.size(); i < ie; ++i) t[i & mask] += t[i]; \\\r\n \
    \   t.resize(len2);                                                     \\\r\n\
    \  }\r\n    MODIFY_POLY(mod_cpy);\r\n    dft(len2, mod_cpy.data());\r\n    poly\
    \ rev_mod_inv(rev_mod.inv(max_quo_size));\r\n    rev_mod_inv.resize(len, mod_t(0));\r\
    \n    dft(len, rev_mod_inv.data());\r\n    for (; e; e >>= 1) {\r\n      if (e\
    \ & 1) {\r\n        // res=res*cpy%mod,cpy=cpy*cpy%mod\r\n        // \u5148\u8FDB\
    \u884C\u4E24\u6B21\u5377\u79EF\uFF0C\u540E\u7FFB\u8F6C\uFF0C\u53D6\u524D quo_size\
    \ \u9879\u4E0E rev_mod \u7684\u9006\u5377\u79EF\u6C42\u51FA rev_quo\r\n      \
    \  // \u7FFB\u8F6C\u6C42\u51FA quo \u540E\u4E0E mod \u5377\u79EF\uFF0C\u8FD9\u4E00\
    \u6B65\u7684 dft \u53EF\u4EE5\u5728 O(deg(mod)) \u7EA7\u522B\r\n        // \u540E\
    \u4F5C\u4E00\u6B21\u51CF\u6CD5\u5373\u53EF\r\n        res.resize(len, mod_t(0));\r\
    \n        cpy.resize(len, mod_t(0));\r\n        dft(len, res.data());\r\n    \
    \    dft(len, cpy.data());\r\n        for (int i = 0; i != len; ++i) res[i] *=\
    \ cpy[i], cpy[i] *= cpy[i];\r\n        idft(len, res.data());\r\n        idft(len,\
    \ cpy.data());\r\n        int quo_size_res = res.deg() - rem_size + 1;\r\n   \
    \     if (quo_size_res > 0) {\r\n          poly rev_res(res);\r\n          rev_res.shrink();\r\
    \n          std::reverse(rev_res.begin(), rev_res.end());\r\n          rev_res.resize(len);\r\
    \n          std::fill(rev_res.begin() + quo_size_res, rev_res.end(), mod_t(0));\r\
    \n          dft(len, rev_res.data());\r\n          for (int i = 0; i != len; ++i)\
    \ rev_res[i] *= rev_mod_inv[i];\r\n          idft(len, rev_res.data());\r\n  \
    \        rev_res.resize(quo_size_res);\r\n          std::reverse(rev_res.begin(),\
    \ rev_res.end());\r\n          MODIFY_POLY(res);\r\n          MODIFY_POLY(rev_res);\r\
    \n          dft(len2, rev_res.data());\r\n          for (int i = 0; i != len2;\
    \ ++i) rev_res[i] *= mod_cpy[i];\r\n          idft(len2, rev_res.data());\r\n\
    \          for (int i = 0; i != len2; ++i) res[i] -= rev_res[i];\r\n        }\r\
    \n      } else {\r\n        cpy *= cpy;\r\n      }\r\n      int quo_size_cpy =\
    \ cpy.deg() - rem_size + 1;\r\n      if (quo_size_cpy > 0) {\r\n        poly rev_cpy(cpy);\r\
    \n        rev_cpy.shrink();\r\n        std::reverse(rev_cpy.begin(), rev_cpy.end());\r\
    \n        rev_cpy.resize(len);\r\n        std::fill(rev_cpy.begin() + quo_size_cpy,\
    \ rev_cpy.end(), mod_t(0));\r\n        dft(len, rev_cpy.data());\r\n        for\
    \ (int i = 0; i != len; ++i) rev_cpy[i] *= rev_mod_inv[i];\r\n        idft(len,\
    \ rev_cpy.data());\r\n        rev_cpy.resize(quo_size_cpy);\r\n        std::reverse(rev_cpy.begin(),\
    \ rev_cpy.end());\r\n        MODIFY_POLY(cpy);\r\n        MODIFY_POLY(rev_cpy);\r\
    \n        dft(len2, rev_cpy.data());\r\n        for (int i = 0; i != len2; ++i)\
    \ rev_cpy[i] *= mod_cpy[i];\r\n        idft(len2, rev_cpy.data());\r\n       \
    \ for (int i = 0; i != len2; ++i) cpy[i] -= rev_cpy[i];\r\n      }\r\n    }\r\n\
    #undef MODIFY_POLY\r\n    res.shrink();\r\n    return res;\r\n  }\r\n\r\n  poly\
    \ shift(mod_t c) const {\r\n    int n = this->deg();\r\n    if (n < 1) return\
    \ poly(*this);\r\n    NTTBinomial<mod_t> bi(n + 1);\r\n    poly A(*this), B(n\
    \ + 1);\r\n    mod_t c_i(1);\r\n    for (int i = 0; i <= n; ++i) A[i] *= bi.fac_unsafe(i),\
    \ B[i] = c_i * bi.ifac_unsafe(i), c_i *= c;\r\n    std::reverse(A.begin(), A.end());\r\
    \n    A *= B;\r\n    A.resize(n + 1);\r\n    std::reverse(A.begin(), A.end());\r\
    \n    for (int i = 0; i <= n; ++i) A[i] *= bi.ifac_unsafe(i);\r\n    return A;\r\
    \n  }\r\n\r\n  friend poly operator+(const poly &lhs, const poly &rhs) { return\
    \ poly(lhs) += rhs; }\r\n  friend poly operator-(const poly &lhs, const poly &rhs)\
    \ { return poly(lhs) -= rhs; }\r\n  friend poly operator*(const poly &lhs, const\
    \ poly &rhs) { return poly(lhs) *= rhs; }\r\n  friend poly operator/(const poly\
    \ &lhs, const poly &rhs) { return poly(lhs) /= rhs; }\r\n  friend poly operator%(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) %= rhs; }\r\n};\r\n\r\ntemplate\
    \ <typename mod_t>\r\nusing Poly = Polynomial<mod_t>;\r\n\r\n} // namespace lib\r\
    \n\r\n\n#line 1 \"math/formal_power_series/subproduct_tree.hpp\"\n\n\n\r\n/**\r\
    \n * @brief multi-point evaluation & interpolation / \u591A\u70B9\u6C42\u503C\u548C\
    \u63D2\u503C\r\n * @docs docs/math/formal_power_series/subproduct_tree.md\r\n\
    \ */\r\n\r\n#line 10 \"math/formal_power_series/subproduct_tree.hpp\"\n#include\
    \ <functional>\r\n#line 13 \"math/formal_power_series/subproduct_tree.hpp\"\n\r\
    \nnamespace lib {\r\n\r\ntemplate <typename mod_t, typename PolyType>\r\nclass\
    \ SubproductTree {\r\npublic:\r\n  SubproductTree(const std::vector<mod_t> &x_set)\
    \ : tree_(x_set.size() << 2) {\r\n    assert(!tree_.empty());\r\n    // tree_\
    \ \u4E3A 1-indexed\r\n    std::function<void(int, int, int)> build_tree = [&](int\
    \ idx, int l, int r) {\r\n      if (l == r - 1) {\r\n        tree_[idx] = PolyType{-x_set[l],\
    \ mod_t(1)};\r\n      } else {\r\n        build_tree(idx << 1, l, (l + r) >> 1),\
    \ build_tree(idx << 1 | 1, (l + r) >> 1, r);\r\n        tree_[idx] = tree_[idx\
    \ << 1] * tree_[idx << 1 | 1];\r\n      }\r\n    };\r\n    build_tree(1, 0, x_set.size());\r\
    \n  }\r\n  ~SubproductTree() = default;\r\n\r\n  std::vector<mod_t> godown(const\
    \ PolyType &f) const {\r\n    std::vector<mod_t> res;\r\n    res.reserve(tree_.size()\
    \ >> 2);\r\n    std::function<void(int, int, int, const PolyType &)> dfs = [&](int\
    \ idx, int l, int r,\r\n                                                     \
    \              const PolyType &t) {\r\n      PolyType t_mod = t % tree_[idx];\r\
    \n      if (l == r - 1) {\r\n        res.emplace_back(t_mod[0]);\r\n      } else\
    \ {\r\n        dfs(idx << 1, l, (l + r) >> 1, t_mod), dfs(idx << 1 | 1, (l + r)\
    \ >> 1, r, t_mod);\r\n      }\r\n    };\r\n    dfs(1, 0, tree_.size() >> 2, f);\r\
    \n    return res;\r\n  }\r\n\r\n  PolyType goup(const std::vector<mod_t> &y_set)\
    \ const {\r\n    assert(y_set.size() == (tree_.size() >> 2));\r\n    std::vector<mod_t>\
    \ in_set = godown(tree_[1].deriv());\r\n    std::vector<mod_t> p_sum(in_set.size()),\
    \ n_set(in_set.size());\r\n    std::partial_sum(in_set.begin(), in_set.end(),\
    \ p_sum.begin(), std::multiplies<>());\r\n    mod_t p_inv = mod_t(1) / p_sum.back();\r\
    \n    for (int i = int(n_set.size()) - 1; i > 0; --i)\r\n      n_set[i] = p_sum[i\
    \ - 1] * y_set[i] * p_inv, p_inv *= in_set[i];\r\n    n_set[0]               \
    \                    = y_set[0] * p_inv;\r\n    std::function<PolyType(int, int,\
    \ int)> dfs = [&](int idx, int l, int r) {\r\n      if (l == r - 1) {\r\n    \
    \    return PolyType{n_set[l]};\r\n      } else {\r\n        return dfs(idx <<\
    \ 1, l, (l + r) >> 1) * tree_[idx << 1 | 1] +\r\n               dfs(idx << 1 |\
    \ 1, (l + r) >> 1, r) * tree_[idx << 1];\r\n      }\r\n    };\r\n    return dfs(1,\
    \ 0, y_set.size());\r\n  }\r\n\r\nprivate:\r\n  std::vector<PolyType> tree_;\r\
    \n};\r\n\r\ntemplate <typename PolyType, typename mod_t>\r\nstd::vector<mod_t>\
    \ evaluate(const PolyType &f, const std::vector<mod_t> &x_set) {\r\n  return SubproductTree<mod_t,\
    \ PolyType>(x_set).godown(f);\r\n}\r\n\r\ntemplate <typename PolyType, typename\
    \ mod_t>\r\nvoid interpolate(const std::vector<mod_t> &x_set, const std::vector<mod_t>\
    \ &y_set, PolyType &res) {\r\n  res = SubproductTree<mod_t, PolyType>(x_set).goup(y_set);\r\
    \n}\r\n\r\n} // namespace lib\r\n\r\n\n#line 1 \"modint/Montgomery_modint.hpp\"\
    \n\n\n\r\n/**\r\n * @brief Montgomery modint / Montgomery \u53D6\u6A21\u7C7B\r\
    \n * @docs docs/modint/Montgomery_modint.md\r\n */\r\n\r\n#line 11 \"modint/Montgomery_modint.hpp\"\
    \n#include <type_traits>\r\n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief Montgomery\
    \ \u53D6\u6A21\u7C7B\r\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\
    \n * @author Nyaan\r\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\r\n\
    \ */\r\ntemplate <std::uint32_t mod>\r\nclass MontgomeryModInt {\r\npublic:\r\n\
    \  using i32 = std::int32_t;\r\n  using u32 = std::uint32_t;\r\n  using u64 =\
    \ std::uint64_t;\r\n  using m32 = MontgomeryModInt;\r\n\r\n  using value_type\
    \ = u32;\r\n\r\n  static constexpr u32 get_mod() { return mod; }\r\n\r\n  static\
    \ constexpr u32 get_primitive_root_prime() {\r\n    u32 tmp[32]   = {};\r\n  \
    \  int cnt       = 0;\r\n    const u32 phi = mod - 1;\r\n    u32 m         = phi;\r\
    \n    for (u32 i = 2; i * i <= m; ++i) {\r\n      if (m % i == 0) {\r\n      \
    \  tmp[cnt++] = i;\r\n        do { m /= i; } while (m % i == 0);\r\n      }\r\n\
    \    }\r\n    if (m != 1) tmp[cnt++] = m;\r\n    for (m32 res = 2;; res += 1)\
    \ {\r\n      bool f = true;\r\n      for (int i = 0; i < cnt && f; ++i) f &= res.pow(phi\
    \ / tmp[i]) != 1;\r\n      if (f) return u32(res);\r\n    }\r\n  }\r\n\r\n  constexpr\
    \ MontgomeryModInt() = default;\r\n  ~MontgomeryModInt()          = default;\r\
    \n\r\n  template <typename T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\
    \n  constexpr MontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) + i32(mod)) *\
    \ r2)) {}\r\n\r\n  constexpr MontgomeryModInt(const m32 &) = default;\r\n\r\n\
    \  constexpr u32 get() const { return norm(reduce(v_)); }\r\n\r\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\r\n  explicit constexpr\
    \ operator T() const {\r\n    return T(get());\r\n  }\r\n\r\n  constexpr m32 operator-()\
    \ const {\r\n    m32 res;\r\n    res.v_ = (mod2 & -(v_ != 0)) - v_;\r\n    return\
    \ res;\r\n  }\r\n\r\n  constexpr m32 inv() const {\r\n    i32 x1 = 1, x3 = 0,\
    \ a = get(), b = mod;\r\n    while (b != 0) {\r\n      i32 q = a / b, x1_old =\
    \ x1, a_old = a;\r\n      x1 = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b\
    \ * q;\r\n    }\r\n    return m32(x1);\r\n  }\r\n\r\n  constexpr m32 &operator=(const\
    \ m32 &) = default;\r\n\r\n  constexpr m32 &operator+=(const m32 &rhs) {\r\n \
    \   v_ += rhs.v_ - mod2;\r\n    v_ += mod2 & -(v_ >> 31);\r\n    return *this;\r\
    \n  }\r\n  constexpr m32 &operator-=(const m32 &rhs) {\r\n    v_ -= rhs.v_;\r\n\
    \    v_ += mod2 & -(v_ >> 31);\r\n    return *this;\r\n  }\r\n  constexpr m32\
    \ &operator*=(const m32 &rhs) {\r\n    v_ = reduce(u64(v_) * rhs.v_);\r\n    return\
    \ *this;\r\n  }\r\n  constexpr m32 &operator/=(const m32 &rhs) { return operator*=(rhs.inv());\
    \ }\r\n  friend constexpr m32 operator+(const m32 &lhs, const m32 &rhs) { return\
    \ m32(lhs) += rhs; }\r\n  friend constexpr m32 operator-(const m32 &lhs, const\
    \ m32 &rhs) { return m32(lhs) -= rhs; }\r\n  friend constexpr m32 operator*(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }\r\n  friend constexpr\
    \ m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs) /= rhs; }\r\n\
    \  friend constexpr bool operator==(const m32 &lhs, const m32 &rhs) {\r\n    return\
    \ norm(lhs.v_) == norm(rhs.v_);\r\n  }\r\n  friend constexpr bool operator!=(const\
    \ m32 &lhs, const m32 &rhs) {\r\n    return norm(lhs.v_) != norm(rhs.v_);\r\n\
    \  }\r\n\r\n  friend std::istream &operator>>(std::istream &is, m32 &rhs) {\r\n\
    \    i32 x;\r\n    is >> x;\r\n    rhs = m32(x);\r\n    return is;\r\n  }\r\n\
    \  friend std::ostream &operator<<(std::ostream &os, const m32 &rhs) { return\
    \ os << rhs.get(); }\r\n\r\n  constexpr m32 pow(u64 y) const {\r\n    m32 res(1),\
    \ x(*this);\r\n    for (; y != 0; y >>= 1, x *= x)\r\n      if (y & 1) res *=\
    \ x;\r\n    return res;\r\n  }\r\n\r\nprivate:\r\n  static constexpr u32 get_r()\
    \ {\r\n    u32 two = 2, iv = mod * (two - mod * mod);\r\n    iv *= two - mod *\
    \ iv;\r\n    iv *= two - mod * iv;\r\n    return iv * (mod * iv - two);\r\n  }\r\
    \n\r\n  static constexpr u32 reduce(u64 x) { return (x + u64(u32(x) * r) * mod)\
    \ >> 32; }\r\n  static constexpr u32 norm(u32 x) { return x - (mod & -((mod -\
    \ 1 - x) >> 31)); }\r\n\r\n  u32 v_;\r\n\r\n  static constexpr u32 r    = get_r();\r\
    \n  static constexpr u32 r2   = -u64(mod) % mod;\r\n  static constexpr u32 mod2\
    \ = mod << 1;\r\n\r\n  static_assert((mod & 1) == 1, \"mod % 2 == 0\\n\");\r\n\
    \  static_assert(-r * mod == 1, \"???\\n\");\r\n  static_assert((mod & (3U <<\
    \ 30)) == 0, \"mod >= (1 << 30)\\n\");\r\n  static_assert(mod != 1, \"mod == 1\\\
    n\");\r\n};\r\n\r\n// \u522B\u540D\r\ntemplate <std::uint32_t mod>\r\nusing MontModInt\
    \ = MontgomeryModInt<mod>;\r\n\r\n} // namespace lib\r\n\r\n\n#line 9 \"remote_test/yosupo/math/polynomial_interpolation.0.test.cpp\"\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  using mint = lib::MontModInt<998244353>;\r\n  using poly = lib::Poly<mint>;\r\
    \n  int n;\r\n  std::cin >> n;\r\n  std::vector<mint> x(n), y(n);\r\n  for (auto\
    \ &i : x) std::cin >> i;\r\n  for (auto &i : y) std::cin >> i;\r\n  poly res;\r\
    \n  lib::interpolate(x, y, res);\r\n  res.resize(n, 0);\r\n  for (auto i : res)\
    \ std::cout << i << ' ';\r\n  return 0;\r\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/polynomial_interpolation\"\
    \r\n\r\n#include <iostream>\r\n#include <vector>\r\n\r\n#include \"math/formal_power_series/polynomial.hpp\"\
    \r\n#include \"math/formal_power_series/subproduct_tree.hpp\"\r\n#include \"modint/Montgomery_modint.hpp\"\
    \r\n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin),\
    \ std::freopen(\"out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\
    \n  std::cin.tie(0);\r\n  using mint = lib::MontModInt<998244353>;\r\n  using\
    \ poly = lib::Poly<mint>;\r\n  int n;\r\n  std::cin >> n;\r\n  std::vector<mint>\
    \ x(n), y(n);\r\n  for (auto &i : x) std::cin >> i;\r\n  for (auto &i : y) std::cin\
    \ >> i;\r\n  poly res;\r\n  lib::interpolate(x, y, res);\r\n  res.resize(n, 0);\r\
    \n  for (auto i : res) std::cout << i << ' ';\r\n  return 0;\r\n}"
  dependsOn:
  - math/formal_power_series/polynomial.hpp
  - math/formal_power_series/NTT_binomial.hpp
  - math/formal_power_series/formal_power_series.hpp
  - traits/modint.hpp
  - math/formal_power_series/radix_2_NTT.hpp
  - math/formal_power_series/subproduct_tree.hpp
  - modint/Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-19 03:14:01+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
- /verify/remote_test/yosupo/math/polynomial_interpolation.0.test.cpp.html
title: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
---
