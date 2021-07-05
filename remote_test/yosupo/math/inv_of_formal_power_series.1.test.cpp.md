---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/formal_power_series.hpp
    title: "basic operations of formal power series / \u5F62\u5F0F\u5E42\u7EA7\u6570\
      \u7684\u57FA\u672C\u64CD\u4F5C"
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362"
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
    PROBLEM: https://judge.yosupo.jp/problem/inv_of_formal_power_series
    links:
    - https://judge.yosupo.jp/problem/inv_of_formal_power_series
  bundledCode: "#line 1 \"remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/inv_of_formal_power_series\"\
    \n\n#include <iostream>\n#include <vector>\n\n#line 1 \"math/formal_power_series/formal_power_series.hpp\"\
    \n\n\n\n/**\n * @brief basic operations of formal power series / \u5F62\u5F0F\u5E42\
    \u7EA7\u6570\u7684\u57FA\u672C\u64CD\u4F5C\n * @docs docs/math/formal_power_series/formal_power_series.md\n\
    \ */\n\n#include <algorithm>\n#include <cassert>\n#include <numeric>\n#include\
    \ <tuple>\n#include <utility>\n#line 15 \"math/formal_power_series/formal_power_series.hpp\"\
    \n\n#line 1 \"traits/modint.hpp\"\n\n\n\n/**\n * @brief modint traits / \u53D6\
    \u6A21\u7C7B\u8403\u53D6\n *\n */\n\nnamespace lib {\n\ntemplate <typename mod_t>\
    \ struct modint_traits {\n  using type = typename mod_t::value_type;\n  static\
    \ constexpr type get_mod() { return mod_t::get_mod(); }\n  static constexpr type\
    \ get_primitive_root_prime() { return mod_t::get_primitive_root_prime(); }\n};\n\
    \n} // namespace lib\n\n\n#line 1 \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n\n\n\n/**\n * @brief radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362\n *\n */\n\
    \n#line 11 \"math/formal_power_series/radix_2_NTT.hpp\"\n#include <cstdint>\n\
    #line 13 \"math/formal_power_series/radix_2_NTT.hpp\"\n\n#line 15 \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n\nnamespace lib {\n\n/**\n * @note \u5FC5\u987B\u7528 NTT \u53CB\u597D\u7684\
    \u6A21\u6570\uFF01\uFF01\uFF01\n */\ntemplate <typename mod_t> class NTT {\npublic:\n\
    \  NTT() = delete;\n\n  static void set_root(int len) {\n    static int lim =\
    \ 0;\n    static constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\n\
    \    if (lim == 0) {\n      rt.resize(1 << 20);\n      irt.resize(1 << 20);\n\
    \      rt[0] = irt[0] = 1;\n      mod_t g_t = g.pow(modint_traits<mod_t>::get_mod()\
    \ >> 21), ig_t = g_t.inv();\n      rt[1 << 19] = g_t, irt[1 << 19] = ig_t;\n \
    \     for (int i = 18; i >= 0; --i) {\n        g_t *= g_t, ig_t *= ig_t;\n   \
    \     rt[1 << i] = g_t, irt[1 << i] = ig_t;\n      }\n      lim = 1;\n    }\n\
    \    for (; (lim << 1) < len; lim <<= 1) {\n      mod_t g = rt[lim], ig = irt[lim];\n\
    \      for (int i = lim + 1, e = lim << 1; i < e; ++i) {\n        rt[i] = rt[i\
    \ - lim] * g;\n        irt[i] = irt[i - lim] * ig;\n      }\n    }\n  }\n\n  static\
    \ void dft(int n, mod_t *x) {\n    for (int j = 0, l = n >> 1; j != l; ++j) {\n\
    \      mod_t u = x[j], v = x[j + l];\n      x[j] = u + v, x[j + l] = u - v;\n\
    \    }\n    for (int i = n >> 1; i >= 2; i >>= 1) {\n      for (int j = 0, l =\
    \ i >> 1; j != l; ++j) {\n        mod_t u = x[j], v = x[j + l];\n        x[j]\
    \ = u + v, x[j + l] = u - v;\n      }\n      for (int j = i, l = i >> 1, m = 1;\
    \ j != n; j += i, ++m) {\n        mod_t root = rt[m];\n        for (int k = 0;\
    \ k != l; ++k) {\n          mod_t u = x[j + k], v = x[j + k + l] * root;\n   \
    \       x[j + k] = u + v, x[j + k + l] = u - v;\n        }\n      }\n    }\n \
    \ }\n\n  static void idft(int n, mod_t *x) {\n    for (int i = 2; i < n; i <<=\
    \ 1) {\n      for (int j = 0, l = i >> 1; j != l; ++j) {\n        mod_t u = x[j],\
    \ v = x[j + l];\n        x[j] = u + v, x[j + l] = u - v;\n      }\n      for (int\
    \ j = i, l = i >> 1, m = 1; j != n; j += i, ++m) {\n        mod_t root = irt[m];\n\
    \        for (int k = 0; k != l; ++k) {\n          mod_t u = x[j + k], v = x[j\
    \ + k + l];\n          x[j + k] = u + v, x[j + k + l] = (u - v) * root;\n    \
    \    }\n      }\n    }\n    mod_t iv(mod_t(n).inv());\n    for (int j = 0, l =\
    \ n >> 1; j != l; ++j) {\n      mod_t u = x[j] * iv, v = x[j + l] * iv;\n    \
    \  x[j] = u + v, x[j + l] = u - v;\n    }\n  }\n\n  static void even_dft(int n,\
    \ mod_t *x) {\n    static constexpr mod_t IT(mod_t(2).inv());\n    for (int i\
    \ = 0, j = 0; i != n; i += 2, ++j) x[j] = IT * (x[i] + x[i + 1]);\n  }\n\n  static\
    \ void odd_dft(int n, mod_t *x) {\n    static constexpr mod_t IT(mod_t(2).inv());\n\
    \    for (int i = 0, j = 0; i != n; i += 2, ++j) x[j] = IT * irt[j] * (x[i] -\
    \ x[i + 1]);\n  }\n\n  static void dft_doubling(int n, mod_t *x) {\n    static\
    \ constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\n    std::copy_n(x,\
    \ n, x + n);\n    idft(n, x + n);\n    mod_t k(1), t(g.pow((modint_traits<mod_t>::get_mod()\
    \ - 1) / (n << 1)));\n    for (int i = 0; i != n; ++i) x[n + i] *= k, k *= t;\n\
    \    dft(n, x + n);\n  }\n\nprivate:\n  static inline std::vector<mod_t> rt, irt;\n\
    };\n\nstd::uint32_t get_ntt_len(std::uint32_t n) {\n  --n;\n  n |= n >> 1;\n \
    \ n |= n >> 2;\n  n |= n >> 4;\n  n |= n >> 8;\n  return (n | n >> 16) + 1;\n\
    }\n\n/**\n * @brief \u63A5\u6536\u4E00\u4E2A\u591A\u9879\u5F0F\uFF0C\u8FD4\u56DE\
    \u4E8C\u8FDB\u5236\u7FFB\u8F6C\u540E\u7684 DFT \u5E8F\u5217\uFF0C\u5373 x(1),\
    \ x(-1) \u7B49\uFF0C\n *        \u5BF9\u4E8E\u4E0B\u6807 i \u548C i^1 \u5FC5\u7136\
    \u662F\u4E24\u4E2A\u4E92\u4E3A\u76F8\u53CD\u6570\u7684\u70B9\u503C\n *\n * @tparam\
    \ mod_t\n * @param n\n * @param x\n */\ntemplate <typename mod_t> void dft(int\
    \ n, mod_t *x) {\n  NTT<mod_t>::set_root(n);\n  NTT<mod_t>::dft(n, x);\n}\n\n\
    /**\n * @brief \u63A5\u6536\u4E8C\u8FDB\u5236\u7FFB\u8F6C\u540E\u7684 DFT \u5E8F\
    \u5217\uFF0C\u8FD4\u56DE\u591A\u9879\u5F0F\u5E8F\u5217 mod (x^n - 1)\n *\n * @tparam\
    \ mod_t\n * @param n\n * @param x\n */\ntemplate <typename mod_t> void idft(int\
    \ n, mod_t *x) {\n  NTT<mod_t>::set_root(n);\n  NTT<mod_t>::idft(n, x);\n}\n\n\
    template <typename mod_t> void dft(std::vector<mod_t> &x) {\n  NTT<mod_t>::set_root(x.size());\n\
    \  NTT<mod_t>::dft(x.size(), x.data());\n}\n\ntemplate <typename mod_t> void idft(std::vector<mod_t>\
    \ &x) {\n  NTT<mod_t>::set_root(x.size());\n  NTT<mod_t>::idft(x.size(), x.data());\n\
    }\n\n} // namespace lib\n\n\n#line 18 \"math/formal_power_series/formal_power_series.hpp\"\
    \n\nnamespace lib {\n\n/**\n * @note \u5FC5\u987B\u4F7F\u7528 NTT \u53CB\u597D\
    \u7684\u6A21\u6570\uFF01\uFF01\uFF01\n *       \u5728\u4F7F\u7528\u6A21\u677F\u7C7B\
    \u7EE7\u627F\u65F6\uFF0C\u5BF9\u4E8E\u7EE7\u627F\u6765\u7684 public \u6210\u5458\
    \u51FD\u6570\uFF0C\u8981\u4E48\u4F7F\u7528 using \u6765\u58F0\u660E\uFF0C\u8981\
    \u4E48\u4F7F\u7528\u57DF\u9650\u5B9A\u7B26\n *       \u8981\u4E48\u4F7F\u7528\
    \ this \u6307\u9488\uFF0C\u8FD9\u6837\u5728\u7B2C\u4E00\u6B21\u626B\u63CF\u65F6\
    \u4E0D\u4F1A\u5904\u7406\uFF0C\u7B2C\u4E8C\u6B21\u624D\u4F1A\u5206\u6790\u57FA\
    \u7C7B\u4E2D\u7684\u51FD\u6570\uFF0C\n *       \u5426\u5219\u4E0D\u80FD\u901A\u8FC7\
    \u7F16\u8BD1\u3002MSVC \u56E0\u4E3A\u6709\u6269\u5C55\u7684\u539F\u56E0\u53EF\u4EE5\
    \u901A\u8FC7\u7F16\u8BD1\uFF0C\u4F46\u6807\u51C6\u89C4\u5B9A\u662F\u8FD9\u6837\
    \u3002\n *       \u82E5\u4E0D\u662F\u6A21\u677F\u7C7B\u7EE7\u627F\u5219\u6CA1\u6709\
    \u8FD9\u6837\u7684\u95EE\u9898\u3002\n *\n */\ntemplate <typename mod_t> class\
    \ FormalPowerSeries : public std::vector<mod_t> {\nprivate:\n  using vec = std::vector<mod_t>;\n\
    \  using fps = FormalPowerSeries<mod_t>;\n\n  static inline vec INV;\n\n  static\
    \ void init_inv(int n) { // \u9884\u5904\u7406 [1, n) \u7684\u9006\u5143\n   \
    \ static constexpr auto mod = modint_traits<mod_t>::get_mod();\n    int lim =\
    \ INV.size();\n    if (lim < n) {\n      INV.resize(n);\n      if (lim == 0) INV[1]\
    \ = 1, lim = 2;\n      for (int i = lim; i < n; ++i) INV[i] = mod_t(mod - mod\
    \ / i) * INV[mod % i];\n    }\n  }\n\npublic:\n  using vec::vec;\n\n  /**\n  \
    \ * @brief \u83B7\u53D6\u5EA6\u6570\n   * @note \u7279\u4F8B\u4E3A deg(0)=-1\n\
    \   * @return int\n   */\n  int deg() const {\n    static constexpr mod_t Z =\
    \ 0;\n    int n = int(this->size()) - 1;\n    while (n >= 0 && this->operator[](n)\
    \ == Z) --n;\n    return n;\n  }\n\n  /**\n   * @brief \u83B7\u53D6\u6700\u9AD8\
    \u6B21\u9879\u7684\u7CFB\u6570\n   * @return mod_t\n   */\n  mod_t leading_coeff()\
    \ const {\n    int d = deg();\n    return d == -1 ? mod_t(0) : this->operator[](d);\n\
    \  }\n\n  /**\n   * @brief \u53BB\u9664\u5C3E 0 \uFF0C\u4F46\u5982\u679C\u53EA\
    \u6709\u4E00\u4E2A 0 \u5219\u4F1A\u4FDD\u7559\n   */\n  void shrink() { this->resize(std::max(deg()\
    \ + 1, 1)); }\n  fps slice() const { return fps(*this); }\n  fps slice(int n)\
    \ const {\n    assert(n >= 0);\n    int sz = this->size();\n    if (sz >= n) return\
    \ fps(this->begin(), this->begin() + n);\n    fps res(*this);\n    res.resize(n,\
    \ mod_t(0));\n    return res;\n  }\n\n  fps deriv() const {\n    int n = this->size();\n\
    \    if (n <= 1) return {0};\n    fps res(n - 1);\n    for (int i = 1; i != n;\
    \ ++i) res[i - 1] = this->operator[](i) * mod_t(i);\n    return res;\n  }\n\n\
    \  fps integr(const mod_t &c = mod_t(0)) const {\n    int n = this->size() + 1;\n\
    \    fps res(n);\n    res[0] = c;\n    init_inv(n);\n    for (int i = 1; i !=\
    \ n; ++i) res[i] = this->operator[](i - 1) * INV[i];\n    return res;\n  }\n\n\
    \  fps operator-() const {\n    fps res(this->size());\n    for (int i = 0, e\
    \ = this->size(); i != e; ++i) res[i] = -this->operator[](i);\n    return res;\n\
    \  }\n\n  fps &operator+=(const fps &rhs) {\n    if (this->size() < rhs.size())\
    \ this->resize(rhs.size(), mod_t(0));\n    for (int i = 0, e = rhs.size(); i !=\
    \ e; ++i) this->operator[](i) += rhs[i];\n    return *this;\n  }\n  fps &operator-=(const\
    \ fps &rhs) {\n    if (this->size() < rhs.size()) this->resize(rhs.size(), mod_t(0));\n\
    \    for (int i = 0, e = rhs.size(); i != e; ++i) this->operator[](i) -= rhs[i];\n\
    \    return *this;\n  }\n  fps &operator*=(const fps &rhs) {\n    int n = this->size(),\
    \ m = rhs.size();\n    if (std::min(n, m) <= 32) {\n      fps res(n + m - 1, mod_t(0));\n\
    \      for (int i = 0; i != n; ++i) {\n        for (int j = 0; j != m; ++j) {\n\
    \          res[i + j] += this->operator[](i) * rhs[j];\n        }\n      }\n \
    \     return this->operator=(res);\n    }\n    int len = get_ntt_len(n + m - 1);\n\
    \    this->resize(len, mod_t(0));\n    if (this == &rhs) {\n      dft(len, this->data());\n\
    \      for (int i = 0; i != len; ++i) this->operator[](i) *= this->operator[](i);\n\
    \      idft(len, this->data());\n      this->resize(n + m - 1);\n      return\
    \ *this;\n    }\n    auto b = rhs.slice(len);\n    dft(len, this->data());\n \
    \   dft(len, b.data());\n    for (int i = 0; i != len; ++i) this->operator[](i)\
    \ *= b[i];\n    idft(len, this->data());\n    this->resize(n + m - 1);\n    return\
    \ *this;\n  }\n\n  fps &operator/=(const fps &rhs) { // 13E\n    int n = this->size();\n\
    \    if (n == 0) return *this;\n    assert(rhs[0] != 0);\n    if (n == 1) {\n\
    \      this->operator[](0) /= rhs[0];\n      return *this;\n    }\n    int len\
    \ = get_ntt_len(n), len2 = len >> 1;\n    fps work_tmp1(rhs.inv(len2)), work_tmp2(slice(len2)),\
    \ work_tmp3(rhs.slice(len));\n    // rhs.inv(len2) \u82B1\u8D39 5E\n    work_tmp1.resize(len,\
    \ mod_t(0));\n    dft(len, work_tmp1.data()); // 1E\n    work_tmp2.resize(len,\
    \ mod_t(0));\n    dft(len, work_tmp2.data()); // 1E\n    for (int i = 0; i !=\
    \ len; ++i) work_tmp2[i] *= work_tmp1[i];\n    idft(len, work_tmp2.data()); //\
    \ 1E\n    std::copy_n(work_tmp2.begin(), len2, this->begin());\n    std::fill_n(work_tmp2.begin()\
    \ + len2, len2, mod_t(0));\n    dft(len, work_tmp2.data()); // 1E\n    dft(len,\
    \ work_tmp3.data()); // 1E\n    for (int i = 0; i != len; ++i) work_tmp3[i] *=\
    \ work_tmp2[i];\n    idft(len, work_tmp3.data()); // 1E\n    std::fill_n(work_tmp3.begin(),\
    \ len2, mod_t(0));\n    this->resize(len);\n    for (int i = len2; i != len; ++i)\
    \ work_tmp3[i] = this->operator[](i) - work_tmp3[i];\n    dft(len, work_tmp3.data());\
    \ // 1E\n    for (int i = 0; i != len; ++i) work_tmp3[i] *= work_tmp1[i];\n  \
    \  idft(len, work_tmp3.data()); // 1E\n    std::copy_n(work_tmp3.begin() + len2,\
    \ n - len2, this->begin() + len2);\n    this->resize(n);\n    return *this;\n\
    \  }\n\n  fps inv(int n) const { // 10E\n    assert(n > 0);\n    assert(this->operator[](0)\
    \ != 0);\n    if (n == 1) return {mod_t(1) / this->operator[](0)};\n    int len\
    \ = get_ntt_len(n);\n    fps res(len, mod_t(0)), work_tmp1(len), work_tmp2(len),\
    \ cpy(slice(len));\n    res[0] = mod_t(1) / this->operator[](0);\n    for (int\
    \ i = 2; i <= len; i <<= 1) {\n      std::copy_n(cpy.begin(), i, work_tmp1.begin());\n\
    \      dft(i, work_tmp1.data()); // 2E\n      std::copy_n(res.begin(), i, work_tmp2.begin());\n\
    \      dft(i, work_tmp2.data()); // 2E\n      for (int j = 0; j != i; ++j) work_tmp1[j]\
    \ *= work_tmp2[j];\n      idft(i, work_tmp1.data()); // 2E\n      std::fill_n(work_tmp1.begin(),\
    \ i >> 1, mod_t(0));\n      dft(i, work_tmp1.data()); // 2E\n      for (int j\
    \ = 0; j != i; ++j) work_tmp1[j] *= work_tmp2[j];\n      idft(i, work_tmp1.data());\
    \ // 2E\n      for (int j = i >> 1; j != i; ++j) res[j] = -work_tmp1[j];\n   \
    \ }\n    res.resize(n);\n    return res;\n  }\n\n  fps div(int n, const fps &rhs)\
    \ const { return slice(n) /= rhs; }\n\n  mod_t div_at(const fps &rhs, unsigned\
    \ long long k) const { // [x^k](*this)/rhs\n    // \u5F53 this->deg>rhs.deg()\
    \ \u65F6\u6211\u4EEC\u53EF\u4EE5\u8BA1\u7B97\u4E00\u6B21\u6B27\u51E0\u91CC\u5F97\
    \u9664\u6CD5\u5F97\u5230\u5546\u548C\u4F59\u6570 (q, r)\n    // q + r/rhs \u6CE8\
    \u610F\u6B64\u65F6\u82E5 k<=q.deg() \u5219\u7B54\u6848\u9700\u8981\u52A0\u4E0A\
    [x^k]q\uFF0C\u5426\u5219\u7684\u8BDD\u6211\u4EEC\u8F6C\u800C\u8BA1\u7B97 r/rhs\n\
    \    // \u4F46\u662F\u6B64\u5904\u6CA1\u6709\u4F7F\u7528\u8FD9\u4E2A\u65B9\u6CD5\
    \n    assert(rhs.deg() >= 0);\n    assert(rhs[0] != 0);\n    int offset = std::max(deg(),\
    \ rhs.deg()) + 1;\n    if (k <= offset) return div(k + 1, rhs).back();\n    fps\
    \ cpy(*this), rhs_cpy(rhs);\n    int len = get_ntt_len((offset << 1) - 1);\n \
    \   cpy.resize(len, mod_t(0));\n    rhs_cpy.resize(len, mod_t(0));\n    dft(len,\
    \ cpy.data());\n    dft(len, rhs_cpy.data());\n    for (;;) {\n      for (int\
    \ i = 0; i != len; ++i) cpy[i] *= rhs_cpy[i ^ 1];\n      if (k & 1) {\n      \
    \  NTT<mod_t>::odd_dft(len, cpy.data());\n      } else {\n        NTT<mod_t>::even_dft(len,\
    \ cpy.data());\n      }\n      for (int i = 0; i != len; i += 2) rhs_cpy[i] =\
    \ rhs_cpy[i + 1] = rhs_cpy[i] * rhs_cpy[i + 1];\n      NTT<mod_t>::even_dft(len,\
    \ rhs_cpy.data());\n      k >>= 1;\n      if (k <= offset) break;\n      NTT<mod_t>::dft_doubling(len\
    \ >> 1, cpy.data());\n      NTT<mod_t>::dft_doubling(len >> 1, rhs_cpy.data());\n\
    \    }\n    cpy.resize(len >> 1);\n    rhs_cpy.resize(len >> 1);\n    idft(len\
    \ >> 1, cpy.data());\n    idft(len >> 1, rhs_cpy.data());\n    return cpy.div(k\
    \ + 1, rhs_cpy).back();\n  }\n\n  fps log(int n) const {\n    assert(n > 0);\n\
    \    assert(!this->empty());\n    assert(this->operator[](0) == 1);\n    if (this->size()\
    \ == 1) return fps(n, mod_t(0));\n    return deriv().div(n - 1, *this).integr();\n\
    \  }\n\n  // TODO\n  fps exp(int n) const;\n\n  // TODO\n  fps pow(int n, mod_t\
    \ e) const;\n\n  // TODO\n  fps sqrt(int n) const;\n\n  friend fps operator+(const\
    \ fps &lhs, const fps &rhs) { return fps(lhs) += rhs; }\n  friend fps operator-(const\
    \ fps &lhs, const fps &rhs) { return fps(lhs) -= rhs; }\n  friend fps operator*(const\
    \ fps &lhs, const fps &rhs) { return fps(lhs) *= rhs; }\n  friend fps operator/(const\
    \ fps &lhs, const fps &rhs) { return fps(lhs) /= rhs; }\n};\n\ntemplate <typename\
    \ mod_t> using FPS = FormalPowerSeries<mod_t>;\n\n} // namespace lib\n\n\n#line\
    \ 1 \"modint/Montgomery_modint.hpp\"\n\n\n\n/**\n * @brief Montgomery modint /\
    \ Montgomery \u53D6\u6A21\u7C7B\n * @docs docs/modint/Montgomery_modint.md\n */\n\
    \n#line 11 \"modint/Montgomery_modint.hpp\"\n#include <type_traits>\n\nnamespace\
    \ lib {\n\n/**\n * @brief Montgomery \u53D6\u6A21\u7C7B\n * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\n\
    \ * @author Nyaan\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\n */\n\
    template <std::uint32_t mod> class MontgomeryModInt {\npublic:\n  using i32 =\
    \ std::int32_t;\n  using u32 = std::uint32_t;\n  using u64 = std::uint64_t;\n\
    \  using m32 = MontgomeryModInt;\n\n  using value_type = u32;\n\n  static constexpr\
    \ u32 get_mod() { return mod; }\n\n  static constexpr u32 get_primitive_root_prime()\
    \ {\n    u32 tmp[32] = {};\n    int cnt = 0;\n    const u32 phi = mod - 1;\n \
    \   u32 m = phi;\n    for (u32 i = 2; i * i <= m; ++i) {\n      if (m % i == 0)\
    \ {\n        tmp[cnt++] = i;\n        do {\n          m /= i;\n        } while\
    \ (m % i == 0);\n      }\n    }\n    if (m != 1) tmp[cnt++] = m;\n    for (m32\
    \ res = 2;; res += 1) {\n      bool f = true;\n      for (int i = 0; i < cnt &&\
    \ f; ++i) f &= res.pow(phi / tmp[i]) != 1;\n      if (f) return u32(res);\n  \
    \  }\n  }\n\n  constexpr MontgomeryModInt() = default;\n  ~MontgomeryModInt()\
    \ = default;\n\n  template <typename T, std::enable_if_t<std::is_integral_v<T>,\
    \ int> = 0>\n  constexpr MontgomeryModInt(T v) : v_(reduce(u64(v % i32(mod) +\
    \ i32(mod)) * r2)) {}\n\n  constexpr MontgomeryModInt(const m32 &) = default;\n\
    \n  constexpr u32 get() const { return norm(reduce(v_)); }\n\n  template <typename\
    \ T, std::enable_if_t<std::is_integral_v<T>, int> = 0>\n  explicit constexpr operator\
    \ T() const {\n    return T(get());\n  }\n\n  constexpr m32 operator-() const\
    \ {\n    m32 res;\n    res.v_ = (mod2 & -(v_ != 0)) - v_;\n    return res;\n \
    \ }\n\n  constexpr m32 inv() const {\n    i32 x1 = 1, x3 = 0, a = get(), b = mod;\n\
    \    while (b != 0) {\n      i32 q = a / b, x1_old = x1, a_old = a;\n      x1\
    \ = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\n    }\n    return m32(x1);\n\
    \  }\n\n  constexpr m32 &operator+=(const m32 &rhs) {\n    v_ += rhs.v_ - mod2;\n\
    \    v_ += mod2 & -(v_ >> 31);\n    return *this;\n  }\n  constexpr m32 &operator-=(const\
    \ m32 &rhs) {\n    v_ -= rhs.v_;\n    v_ += mod2 & -(v_ >> 31);\n    return *this;\n\
    \  }\n  constexpr m32 &operator*=(const m32 &rhs) {\n    v_ = reduce(u64(v_) *\
    \ rhs.v_);\n    return *this;\n  }\n  constexpr m32 &operator/=(const m32 &rhs)\
    \ { return operator*=(rhs.inv()); }\n  friend constexpr m32 operator+(const m32\
    \ &lhs, const m32 &rhs) { return m32(lhs) += rhs; }\n  friend constexpr m32 operator-(const\
    \ m32 &lhs, const m32 &rhs) { return m32(lhs) -= rhs; }\n  friend constexpr m32\
    \ operator*(const m32 &lhs, const m32 &rhs) { return m32(lhs) *= rhs; }\n  friend\
    \ constexpr m32 operator/(const m32 &lhs, const m32 &rhs) { return m32(lhs) /=\
    \ rhs; }\n  friend constexpr bool operator==(const m32 &lhs, const m32 &rhs) {\n\
    \    return norm(lhs.v_) == norm(rhs.v_);\n  }\n  friend constexpr bool operator!=(const\
    \ m32 &lhs, const m32 &rhs) {\n    return norm(lhs.v_) != norm(rhs.v_);\n  }\n\
    \n  friend std::istream &operator>>(std::istream &is, m32 &rhs) {\n    i32 x;\n\
    \    is >> x;\n    rhs = m32(x);\n    return is;\n  }\n  friend std::ostream &operator<<(std::ostream\
    \ &os, const m32 &rhs) { return os << rhs.get(); }\n\n  constexpr m32 pow(u64\
    \ y) const {\n    m32 res(1), x(*this);\n    for (; y != 0; y >>= 1, x *= x)\n\
    \      if (y & 1) res *= x;\n    return res;\n  }\n\nprivate:\n  static constexpr\
    \ u32 get_r() {\n    u32 two = 2, iv = mod * (two - mod * mod);\n    iv *= two\
    \ - mod * iv;\n    iv *= two - mod * iv;\n    return iv * (mod * iv - two);\n\
    \  }\n\n  static constexpr u32 reduce(u64 x) { return (x + u64(u32(x) * r) * mod)\
    \ >> 32; }\n  static constexpr u32 norm(u32 x) { return x - (mod & -((mod - 1\
    \ - x) >> 31)); }\n\n  u32 v_;\n\n  static constexpr u32 r = get_r();\n  static\
    \ constexpr u32 r2 = -u64(mod) % mod;\n  static constexpr u32 mod2 = mod << 1;\n\
    \n  static_assert((mod & 1) == 1, \"mod % 2 == 0\\n\");\n  static_assert(-r *\
    \ mod == 1, \"???\\n\");\n  static_assert((mod & (3U << 30)) == 0, \"mod >= (1\
    \ << 30)\\n\");\n  static_assert(mod != 1, \"mod == 1\\n\");\n};\n\n// \u522B\u540D\
    \ntemplate <std::uint32_t mod> using MontModInt = MontgomeryModInt<mod>;\n\n}\
    \ // namespace lib\n\n\n#line 8 \"remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  using mint = lib::MontModInt<998244353>;\n  int n;\n  std::cin >> n;\n  lib::FPS<mint>\
    \ a(n);\n  for (auto &i : a) std::cin >> i;\n  for (auto i : a.inv(n)) std::cout\
    \ << i << ' ';\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/inv_of_formal_power_series\"\
    \n\n#include <iostream>\n#include <vector>\n\n#include \"math/formal_power_series/formal_power_series.hpp\"\
    \n#include \"modint/Montgomery_modint.hpp\"\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"\
    in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(0);\n  using mint = lib::MontModInt<998244353>;\n  int n;\n  std::cin\
    \ >> n;\n  lib::FPS<mint> a(n);\n  for (auto &i : a) std::cin >> i;\n  for (auto\
    \ i : a.inv(n)) std::cout << i << ' ';\n  return 0;\n}"
  dependsOn:
  - math/formal_power_series/formal_power_series.hpp
  - traits/modint.hpp
  - math/formal_power_series/radix_2_NTT.hpp
  - modint/Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  requiredBy: []
  timestamp: '2021-07-05 20:51:34+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
- /verify/remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp.html
title: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
---
