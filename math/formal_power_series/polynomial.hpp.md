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
    path: traits/modint.hpp
    title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
    title: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
    title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "polynomial / \u591A\u9879\u5F0F"
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/polynomial.hpp\"\n\n\n\n/**\n *\
    \ @brief polynomial / \u591A\u9879\u5F0F\n *\n */\n\n#line 1 \"math/formal_power_series/formal_power_series.hpp\"\
    \n\n\n\n/**\n * @brief basic operations of formal power series / \u5F62\u5F0F\u5E42\
    \u7EA7\u6570\u7684\u57FA\u672C\u64CD\u4F5C\n * @docs docs/math/formal_power_series/fps.md\n\
    \ */\n\n#include <algorithm>\n#include <cassert>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n#include <numeric>\n\n#line 1 \"traits/modint.hpp\"\n\n\n\
    \n/**\n * @brief modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6\n *\n */\n\nnamespace\
    \ lib {\n\ntemplate <typename mod_t> struct modint_traits {\n  using type = typename\
    \ mod_t::value_type;\n  static constexpr type get_mod() { return mod_t::get_mod();\
    \ }\n  static constexpr type get_primitive_root_prime() { return mod_t::get_primitive_root_prime();\
    \ }\n};\n\n} // namespace lib\n\n\n#line 1 \"math/formal_power_series/radix_2_NTT.hpp\"\
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
    }\n\n} // namespace lib\n\n\n#line 19 \"math/formal_power_series/formal_power_series.hpp\"\
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
    \ static constexpr auto mod = modint_traits<mod_t>::get_mod();\n    static int\
    \ lim = 0;\n    if (lim < n) {\n      INV.resize(n);\n      if (lim == 0) INV[1]\
    \ = 1, lim = 2;\n      for (int i = lim; i < n; ++i) INV[i] = mod_t(mod - mod\
    \ / i) * INV[mod % i];\n      lim = n;\n    }\n  }\n\npublic:\n  using vec::vec;\n\
    \n  /**\n   * @brief \u83B7\u53D6\u5EA6\u6570\n   * @note \u7279\u4F8B\u4E3A deg(0)=-1\n\
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
    \      this->operator[](0) *= rhs[0].inv();\n      return *this;\n    }\n    int\
    \ len = get_ntt_len(n), len2 = len >> 1;\n    fps work_tmp1(rhs.inv(len2)), work_tmp2(slice(len2)),\
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
    \ != 0);\n    if (n == 1) return {this->operator[](0).inv()};\n    int len = get_ntt_len(n);\n\
    \    fps res(len, mod_t(0)), work_tmp1(len), work_tmp2(len), cpy(slice(len));\n\
    \    res[0] = this->operator[](0).inv();\n    for (int i = 2; i <= len; i <<=\
    \ 1) {\n      std::copy_n(cpy.begin(), i, work_tmp1.begin());\n      dft(i, work_tmp1.data());\
    \ // 2E\n      std::copy_n(res.begin(), i, work_tmp2.begin());\n      dft(i, work_tmp2.data());\
    \ // 2E\n      for (int j = 0; j != i; ++j) work_tmp1[j] *= work_tmp2[j];\n  \
    \    idft(i, work_tmp1.data()); // 2E\n      std::fill_n(work_tmp1.begin(), i\
    \ >> 1, mod_t(0));\n      dft(i, work_tmp1.data()); // 2E\n      for (int j =\
    \ 0; j != i; ++j) work_tmp1[j] *= work_tmp2[j];\n      idft(i, work_tmp1.data());\
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
    \ 10 \"math/formal_power_series/polynomial.hpp\"\n\nnamespace lib {\n\n/**\n *\
    \ @brief \u591A\u9879\u5F0F\u7C7B\n * @note \u57FA\u7C7B FormalPowerSeries \u4E2D\
    \u51FD\u6570\u90FD\u6CA1\u6709\u4F7F\u7528 virtual\n *       \u6240\u4EE5\u5728\
    \u8BE5\u7C7B\u4E2D\u6709\u5B9A\u4E49\u76F8\u540C\u7684\u51FD\u6570\u5219\u4F1A\
    \u963B\u6B62\u8C03\u7528\u57FA\u7C7B\u7684\u51FD\u6570\n *       \u8FD9\u88AB\u79F0\
    \u4E3A\u9690\u85CF\uFF08 hide \uFF09\u3002\n *       \u800C\u5982\u679C\u4F7F\u7528\
    \u4E86 virtual \u5219\u88AB\u79F0\u4E3A\u8986\u76D6\uFF08 override \uFF09\uFF0C\
    \u800C\u8986\u76D6\u4F1A\u5BFC\u51FA\u591A\u6001\u3002\n */\ntemplate <typename\
    \ mod_t> class Polynomial : public FormalPowerSeries<mod_t> {\npublic:\n  using\
    \ fps = FormalPowerSeries<mod_t>;\n  using poly = Polynomial<mod_t>;\n  using\
    \ fps::fps;\n\n  // \u4F7F\u5F97\u80FD\u591F\u4ECE FormalPowerSeries \u8F6C\u6362\
    \u4E3A Polynomial \u7C7B\u578B\uFF0C\u4F46\u4E0D\u6E05\u695A\u662F\u5426\u6709\
    \u4EC0\u4E48\u95EE\u9898\n  Polynomial(const fps &rhs) : fps(rhs) {}\n  Polynomial(fps\
    \ &&rhs) : fps(std::move(rhs)) {}\n\n  poly operator-() const {\n    poly res\
    \ = this->fps::operator-();\n    res.shrink();\n    return res;\n  }\n  poly &operator+=(const\
    \ poly &rhs) {\n    this->fps::operator+=(rhs);\n    this->shrink();\n    return\
    \ *this;\n  }\n  poly &operator-=(const poly &rhs) {\n    this->fps::operator-=(rhs);\n\
    \    this->shrink();\n    return *this;\n  }\n  poly &operator*=(const poly &rhs)\
    \ {\n    this->fps::operator*=(rhs);\n    this->shrink();\n    return *this;\n\
    \  }\n  poly &operator/=(const poly &rhs) {\n    assert(rhs.deg() >= 0);\n   \
    \ this->shrink();\n    int quo_size = this->deg() - rhs.deg() + 1;\n    if (quo_size\
    \ <= 0) {\n      this->resize(1);\n      this->operator[](0) = 0;\n      return\
    \ *this;\n    }\n    poly rhs_cpy(rhs);\n    rhs_cpy.shrink();\n    std::reverse(this->begin(),\
    \ this->end());\n    std::reverse(rhs_cpy.begin(), rhs_cpy.end());\n    poly quo(this->div(quo_size,\
    \ rhs_cpy));\n    this->resize(quo_size);\n    std::reverse_copy(quo.begin(),\
    \ quo.end(), this->begin());\n    return *this;\n  }\n  poly &operator%=(const\
    \ poly &rhs) {\n    // f/g => f=gq+r, deg(r)<deg(g) \u5728\u8FD9\u91CC f \u5C31\
    \u662F (*this) \u800C g \u5C31\u662F rhs\n    // r=f-gq (mod ((x^deg(rhs)) - 1))\n\
    \    // \u6240\u4EE5\u6211\u4EEC\u505A NTT \u7684\u957F\u5EA6\u53EF\u4EE5\u662F\
    \ O(deg(rhs)) \u7EA7\u522B\u7684\n    int rem_size = rhs.deg();\n    assert(rem_size\
    \ >= 0);\n    if (rem_size == 0) {\n      this->resize(1);\n      this->operator[](0)\
    \ = 0;\n      return *this;\n    }\n    this->shrink();\n    if (this->deg() <\
    \ rem_size) return *this;\n    poly quo((*this) / rhs), rhs_cpy(rhs);\n    int\
    \ len = get_ntt_len(rem_size);\n    // \u4EE4 (*this) \u548C quo \u548C rhs_cpy\
    \ \u90FD\u5728 mod ((x^len) - 1) \u610F\u4E49\u4E0B\n    int mask = len - 1;\n\
    \    for (int i = len, e = this->size(); i < e; ++i)\n      this->operator[](i\
    \ &mask) += this->operator[](i);\n    for (int i = len, e = quo.size(); i < e;\
    \ ++i) quo[i & mask] += quo[i];\n    for (int i = len, e = rhs_cpy.size(); i <\
    \ e; ++i) rhs_cpy[i & mask] += rhs_cpy[i];\n    this->resize(len, mod_t(0));\n\
    \    quo.resize(len, mod_t(0));\n    rhs_cpy.resize(len, mod_t(0));\n    dft(len,\
    \ rhs_cpy.data());\n    dft(len, quo.data());\n    for (int i = 0; i != len; ++i)\
    \ rhs_cpy[i] *= quo[i];\n    idft(len, rhs_cpy.data());\n    this->resize(rem_size);\n\
    \    for (int i = 0; i != rem_size; ++i) this->operator[](i) -= rhs_cpy[i];\n\
    \    this->shrink();\n    return *this;\n  }\n  std::pair<poly, poly> divmod(const\
    \ poly &rhs) const {\n    int rem_size = rhs.deg();\n    assert(rem_size >= 0);\n\
    \    if (rem_size == 0) return {(*this) * poly{rhs[0].inv()}, poly{0}};\n    poly\
    \ cpy(*this);\n    cpy.shrink();\n    if (cpy.deg() < rem_size) return {poly{0},\
    \ cpy};\n    poly quo(cpy / rhs), quo_cpy(quo), rhs_cpy(rhs);\n    int len = get_ntt_len(rem_size),\
    \ mask = len - 1;\n    for (int i = len, e = cpy.size(); i < e; ++i) cpy[i & mask]\
    \ += cpy[i];\n    for (int i = len, e = quo_cpy.size(); i < e; ++i) quo_cpy[i\
    \ & mask] += quo_cpy[i];\n    for (int i = len, e = rhs_cpy.size(); i < e; ++i)\
    \ rhs_cpy[i & mask] += rhs_cpy[i];\n    cpy.resize(len, mod_t(0));\n    quo_cpy.resize(len,\
    \ mod_t(0));\n    rhs_cpy.resize(len, mod_t(0));\n    dft(len, rhs_cpy.data());\n\
    \    dft(len, quo_cpy.data());\n    for (int i = 0; i != len; ++i) rhs_cpy[i]\
    \ *= quo_cpy[i];\n    idft(len, rhs_cpy.data());\n    cpy.resize(rem_size);\n\
    \    for (int i = 0; i != rem_size; ++i) cpy[i] -= rhs_cpy[i];\n    cpy.shrink();\n\
    \    return {quo, cpy};\n  }\n\n  poly pow_mod(unsigned long long e, const poly\
    \ &mod) const {\n    int rem_size = mod.deg();\n    assert(rem_size >= 0);\n \
    \   if (rem_size == 0) return poly{0};\n    poly res{1}, cpy(*this % mod), mod_cpy(mod),\
    \ rev_mod(mod);\n    mod_cpy.shrink();\n    rev_mod.shrink();\n    std::reverse(rev_mod.begin(),\
    \ rev_mod.end()); // x^{deg(mod)}mod(-x)\n    int len = get_ntt_len((rem_size\
    \ << 1) - 1);   // \u4E24\u4E2A rem_size \u957F\u7684\u591A\u9879\u5F0F\u76F8\u4E58\
    \n    int len2 = get_ntt_len(rem_size);\n    int mask = len2 - 1;\n    int max_quo_size\
    \ = rem_size;\n#define MODIFY_POLY(t)                                        \
    \                                     \\\n  {                                \
    \                                                                \\\n    for (int\
    \ i = len2, ie = t.size(); i < ie; ++i) t[i & mask] += t[i];                 \
    \           \\\n    t.resize(len2);                                          \
    \                                      \\\n  }\n    MODIFY_POLY(mod_cpy);\n  \
    \  dft(len2, mod_cpy.data());\n    poly rev_mod_inv(rev_mod.inv(max_quo_size));\n\
    \    rev_mod_inv.resize(len, mod_t(0));\n    dft(len, rev_mod_inv.data());\n \
    \   for (; e; e >>= 1) {\n      if (e & 1) {\n        // res=res*cpy%mod,cpy=cpy*cpy%mod\n\
    \        // \u5148\u8FDB\u884C\u4E24\u6B21\u5377\u79EF\uFF0C\u540E\u7FFB\u8F6C\
    \uFF0C\u53D6\u524D quo_size \u9879\u4E0E rev_mod \u7684\u9006\u5377\u79EF\u6C42\
    \u51FA rev_quo\n        // \u7FFB\u8F6C\u6C42\u51FA quo \u540E\u4E0E mod \u5377\
    \u79EF\uFF0C\u8FD9\u4E00\u6B65\u7684 dft \u53EF\u4EE5\u5728 O(deg(mod)) \u7EA7\
    \u522B\n        // \u540E\u4F5C\u4E00\u6B21\u51CF\u6CD5\u5373\u53EF\n        res.resize(len,\
    \ mod_t(0));\n        cpy.resize(len, mod_t(0));\n        dft(len, res.data());\n\
    \        dft(len, cpy.data());\n        for (int i = 0; i != len; ++i) res[i]\
    \ *= cpy[i], cpy[i] *= cpy[i];\n        idft(len, res.data());\n        idft(len,\
    \ cpy.data());\n        int quo_size_res = res.deg() - rem_size + 1;\n       \
    \ if (quo_size_res > 0) {\n          poly rev_res(res);\n          rev_res.shrink();\n\
    \          std::reverse(rev_res.begin(), rev_res.end());\n          rev_res.resize(len);\n\
    \          std::fill(rev_res.begin() + quo_size_res, rev_res.end(), mod_t(0));\n\
    \          dft(len, rev_res.data());\n          for (int i = 0; i != len; ++i)\
    \ rev_res[i] *= rev_mod_inv[i];\n          idft(len, rev_res.data());\n      \
    \    rev_res.resize(quo_size_res);\n          std::reverse(rev_res.begin(), rev_res.end());\n\
    \          MODIFY_POLY(res);\n          MODIFY_POLY(rev_res);\n          dft(len2,\
    \ rev_res.data());\n          for (int i = 0; i != len2; ++i) rev_res[i] *= mod_cpy[i];\n\
    \          idft(len2, rev_res.data());\n          for (int i = 0; i != len2; ++i)\
    \ res[i] -= rev_res[i];\n        }\n      } else {\n        cpy *= cpy;\n    \
    \  }\n      int quo_size_cpy = cpy.deg() - rem_size + 1;\n      if (quo_size_cpy\
    \ > 0) {\n        poly rev_cpy(cpy);\n        rev_cpy.shrink();\n        std::reverse(rev_cpy.begin(),\
    \ rev_cpy.end());\n        rev_cpy.resize(len);\n        std::fill(rev_cpy.begin()\
    \ + quo_size_cpy, rev_cpy.end(), mod_t(0));\n        dft(len, rev_cpy.data());\n\
    \        for (int i = 0; i != len; ++i) rev_cpy[i] *= rev_mod_inv[i];\n      \
    \  idft(len, rev_cpy.data());\n        rev_cpy.resize(quo_size_cpy);\n       \
    \ std::reverse(rev_cpy.begin(), rev_cpy.end());\n        MODIFY_POLY(cpy);\n \
    \       MODIFY_POLY(rev_cpy);\n        dft(len2, rev_cpy.data());\n        for\
    \ (int i = 0; i != len2; ++i) rev_cpy[i] *= mod_cpy[i];\n        idft(len2, rev_cpy.data());\n\
    \        for (int i = 0; i != len2; ++i) cpy[i] -= rev_cpy[i];\n      }\n    }\n\
    #undef MODIFY_POLY\n    res.shrink();\n    return res;\n  }\n  friend poly operator+(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) += rhs; }\n  friend poly operator-(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) -= rhs; }\n  friend poly operator*(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) *= rhs; }\n  friend poly operator/(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) /= rhs; }\n  friend poly operator%(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) %= rhs; }\n};\n\ntemplate <typename\
    \ mod_t> using Poly = Polynomial<mod_t>;\n\n} // namespace lib\n\n\n"
  code: "#ifndef POLYNOMIAL_HEADER_HPP\n#define POLYNOMIAL_HEADER_HPP\n\n/**\n * @brief\
    \ polynomial / \u591A\u9879\u5F0F\n *\n */\n\n#include \"formal_power_series.hpp\"\
    \n\nnamespace lib {\n\n/**\n * @brief \u591A\u9879\u5F0F\u7C7B\n * @note \u57FA\
    \u7C7B FormalPowerSeries \u4E2D\u51FD\u6570\u90FD\u6CA1\u6709\u4F7F\u7528 virtual\n\
    \ *       \u6240\u4EE5\u5728\u8BE5\u7C7B\u4E2D\u6709\u5B9A\u4E49\u76F8\u540C\u7684\
    \u51FD\u6570\u5219\u4F1A\u963B\u6B62\u8C03\u7528\u57FA\u7C7B\u7684\u51FD\u6570\
    \n *       \u8FD9\u88AB\u79F0\u4E3A\u9690\u85CF\uFF08 hide \uFF09\u3002\n *  \
    \     \u800C\u5982\u679C\u4F7F\u7528\u4E86 virtual \u5219\u88AB\u79F0\u4E3A\u8986\
    \u76D6\uFF08 override \uFF09\uFF0C\u800C\u8986\u76D6\u4F1A\u5BFC\u51FA\u591A\u6001\
    \u3002\n */\ntemplate <typename mod_t> class Polynomial : public FormalPowerSeries<mod_t>\
    \ {\npublic:\n  using fps = FormalPowerSeries<mod_t>;\n  using poly = Polynomial<mod_t>;\n\
    \  using fps::fps;\n\n  // \u4F7F\u5F97\u80FD\u591F\u4ECE FormalPowerSeries \u8F6C\
    \u6362\u4E3A Polynomial \u7C7B\u578B\uFF0C\u4F46\u4E0D\u6E05\u695A\u662F\u5426\
    \u6709\u4EC0\u4E48\u95EE\u9898\n  Polynomial(const fps &rhs) : fps(rhs) {}\n \
    \ Polynomial(fps &&rhs) : fps(std::move(rhs)) {}\n\n  poly operator-() const {\n\
    \    poly res = this->fps::operator-();\n    res.shrink();\n    return res;\n\
    \  }\n  poly &operator+=(const poly &rhs) {\n    this->fps::operator+=(rhs);\n\
    \    this->shrink();\n    return *this;\n  }\n  poly &operator-=(const poly &rhs)\
    \ {\n    this->fps::operator-=(rhs);\n    this->shrink();\n    return *this;\n\
    \  }\n  poly &operator*=(const poly &rhs) {\n    this->fps::operator*=(rhs);\n\
    \    this->shrink();\n    return *this;\n  }\n  poly &operator/=(const poly &rhs)\
    \ {\n    assert(rhs.deg() >= 0);\n    this->shrink();\n    int quo_size = this->deg()\
    \ - rhs.deg() + 1;\n    if (quo_size <= 0) {\n      this->resize(1);\n      this->operator[](0)\
    \ = 0;\n      return *this;\n    }\n    poly rhs_cpy(rhs);\n    rhs_cpy.shrink();\n\
    \    std::reverse(this->begin(), this->end());\n    std::reverse(rhs_cpy.begin(),\
    \ rhs_cpy.end());\n    poly quo(this->div(quo_size, rhs_cpy));\n    this->resize(quo_size);\n\
    \    std::reverse_copy(quo.begin(), quo.end(), this->begin());\n    return *this;\n\
    \  }\n  poly &operator%=(const poly &rhs) {\n    // f/g => f=gq+r, deg(r)<deg(g)\
    \ \u5728\u8FD9\u91CC f \u5C31\u662F (*this) \u800C g \u5C31\u662F rhs\n    //\
    \ r=f-gq (mod ((x^deg(rhs)) - 1))\n    // \u6240\u4EE5\u6211\u4EEC\u505A NTT \u7684\
    \u957F\u5EA6\u53EF\u4EE5\u662F O(deg(rhs)) \u7EA7\u522B\u7684\n    int rem_size\
    \ = rhs.deg();\n    assert(rem_size >= 0);\n    if (rem_size == 0) {\n      this->resize(1);\n\
    \      this->operator[](0) = 0;\n      return *this;\n    }\n    this->shrink();\n\
    \    if (this->deg() < rem_size) return *this;\n    poly quo((*this) / rhs), rhs_cpy(rhs);\n\
    \    int len = get_ntt_len(rem_size);\n    // \u4EE4 (*this) \u548C quo \u548C\
    \ rhs_cpy \u90FD\u5728 mod ((x^len) - 1) \u610F\u4E49\u4E0B\n    int mask = len\
    \ - 1;\n    for (int i = len, e = this->size(); i < e; ++i)\n      this->operator[](i\
    \ &mask) += this->operator[](i);\n    for (int i = len, e = quo.size(); i < e;\
    \ ++i) quo[i & mask] += quo[i];\n    for (int i = len, e = rhs_cpy.size(); i <\
    \ e; ++i) rhs_cpy[i & mask] += rhs_cpy[i];\n    this->resize(len, mod_t(0));\n\
    \    quo.resize(len, mod_t(0));\n    rhs_cpy.resize(len, mod_t(0));\n    dft(len,\
    \ rhs_cpy.data());\n    dft(len, quo.data());\n    for (int i = 0; i != len; ++i)\
    \ rhs_cpy[i] *= quo[i];\n    idft(len, rhs_cpy.data());\n    this->resize(rem_size);\n\
    \    for (int i = 0; i != rem_size; ++i) this->operator[](i) -= rhs_cpy[i];\n\
    \    this->shrink();\n    return *this;\n  }\n  std::pair<poly, poly> divmod(const\
    \ poly &rhs) const {\n    int rem_size = rhs.deg();\n    assert(rem_size >= 0);\n\
    \    if (rem_size == 0) return {(*this) * poly{rhs[0].inv()}, poly{0}};\n    poly\
    \ cpy(*this);\n    cpy.shrink();\n    if (cpy.deg() < rem_size) return {poly{0},\
    \ cpy};\n    poly quo(cpy / rhs), quo_cpy(quo), rhs_cpy(rhs);\n    int len = get_ntt_len(rem_size),\
    \ mask = len - 1;\n    for (int i = len, e = cpy.size(); i < e; ++i) cpy[i & mask]\
    \ += cpy[i];\n    for (int i = len, e = quo_cpy.size(); i < e; ++i) quo_cpy[i\
    \ & mask] += quo_cpy[i];\n    for (int i = len, e = rhs_cpy.size(); i < e; ++i)\
    \ rhs_cpy[i & mask] += rhs_cpy[i];\n    cpy.resize(len, mod_t(0));\n    quo_cpy.resize(len,\
    \ mod_t(0));\n    rhs_cpy.resize(len, mod_t(0));\n    dft(len, rhs_cpy.data());\n\
    \    dft(len, quo_cpy.data());\n    for (int i = 0; i != len; ++i) rhs_cpy[i]\
    \ *= quo_cpy[i];\n    idft(len, rhs_cpy.data());\n    cpy.resize(rem_size);\n\
    \    for (int i = 0; i != rem_size; ++i) cpy[i] -= rhs_cpy[i];\n    cpy.shrink();\n\
    \    return {quo, cpy};\n  }\n\n  poly pow_mod(unsigned long long e, const poly\
    \ &mod) const {\n    int rem_size = mod.deg();\n    assert(rem_size >= 0);\n \
    \   if (rem_size == 0) return poly{0};\n    poly res{1}, cpy(*this % mod), mod_cpy(mod),\
    \ rev_mod(mod);\n    mod_cpy.shrink();\n    rev_mod.shrink();\n    std::reverse(rev_mod.begin(),\
    \ rev_mod.end()); // x^{deg(mod)}mod(-x)\n    int len = get_ntt_len((rem_size\
    \ << 1) - 1);   // \u4E24\u4E2A rem_size \u957F\u7684\u591A\u9879\u5F0F\u76F8\u4E58\
    \n    int len2 = get_ntt_len(rem_size);\n    int mask = len2 - 1;\n    int max_quo_size\
    \ = rem_size;\n#define MODIFY_POLY(t)                                        \
    \                                     \\\n  {                                \
    \                                                                \\\n    for (int\
    \ i = len2, ie = t.size(); i < ie; ++i) t[i & mask] += t[i];                 \
    \           \\\n    t.resize(len2);                                          \
    \                                      \\\n  }\n    MODIFY_POLY(mod_cpy);\n  \
    \  dft(len2, mod_cpy.data());\n    poly rev_mod_inv(rev_mod.inv(max_quo_size));\n\
    \    rev_mod_inv.resize(len, mod_t(0));\n    dft(len, rev_mod_inv.data());\n \
    \   for (; e; e >>= 1) {\n      if (e & 1) {\n        // res=res*cpy%mod,cpy=cpy*cpy%mod\n\
    \        // \u5148\u8FDB\u884C\u4E24\u6B21\u5377\u79EF\uFF0C\u540E\u7FFB\u8F6C\
    \uFF0C\u53D6\u524D quo_size \u9879\u4E0E rev_mod \u7684\u9006\u5377\u79EF\u6C42\
    \u51FA rev_quo\n        // \u7FFB\u8F6C\u6C42\u51FA quo \u540E\u4E0E mod \u5377\
    \u79EF\uFF0C\u8FD9\u4E00\u6B65\u7684 dft \u53EF\u4EE5\u5728 O(deg(mod)) \u7EA7\
    \u522B\n        // \u540E\u4F5C\u4E00\u6B21\u51CF\u6CD5\u5373\u53EF\n        res.resize(len,\
    \ mod_t(0));\n        cpy.resize(len, mod_t(0));\n        dft(len, res.data());\n\
    \        dft(len, cpy.data());\n        for (int i = 0; i != len; ++i) res[i]\
    \ *= cpy[i], cpy[i] *= cpy[i];\n        idft(len, res.data());\n        idft(len,\
    \ cpy.data());\n        int quo_size_res = res.deg() - rem_size + 1;\n       \
    \ if (quo_size_res > 0) {\n          poly rev_res(res);\n          rev_res.shrink();\n\
    \          std::reverse(rev_res.begin(), rev_res.end());\n          rev_res.resize(len);\n\
    \          std::fill(rev_res.begin() + quo_size_res, rev_res.end(), mod_t(0));\n\
    \          dft(len, rev_res.data());\n          for (int i = 0; i != len; ++i)\
    \ rev_res[i] *= rev_mod_inv[i];\n          idft(len, rev_res.data());\n      \
    \    rev_res.resize(quo_size_res);\n          std::reverse(rev_res.begin(), rev_res.end());\n\
    \          MODIFY_POLY(res);\n          MODIFY_POLY(rev_res);\n          dft(len2,\
    \ rev_res.data());\n          for (int i = 0; i != len2; ++i) rev_res[i] *= mod_cpy[i];\n\
    \          idft(len2, rev_res.data());\n          for (int i = 0; i != len2; ++i)\
    \ res[i] -= rev_res[i];\n        }\n      } else {\n        cpy *= cpy;\n    \
    \  }\n      int quo_size_cpy = cpy.deg() - rem_size + 1;\n      if (quo_size_cpy\
    \ > 0) {\n        poly rev_cpy(cpy);\n        rev_cpy.shrink();\n        std::reverse(rev_cpy.begin(),\
    \ rev_cpy.end());\n        rev_cpy.resize(len);\n        std::fill(rev_cpy.begin()\
    \ + quo_size_cpy, rev_cpy.end(), mod_t(0));\n        dft(len, rev_cpy.data());\n\
    \        for (int i = 0; i != len; ++i) rev_cpy[i] *= rev_mod_inv[i];\n      \
    \  idft(len, rev_cpy.data());\n        rev_cpy.resize(quo_size_cpy);\n       \
    \ std::reverse(rev_cpy.begin(), rev_cpy.end());\n        MODIFY_POLY(cpy);\n \
    \       MODIFY_POLY(rev_cpy);\n        dft(len2, rev_cpy.data());\n        for\
    \ (int i = 0; i != len2; ++i) rev_cpy[i] *= mod_cpy[i];\n        idft(len2, rev_cpy.data());\n\
    \        for (int i = 0; i != len2; ++i) cpy[i] -= rev_cpy[i];\n      }\n    }\n\
    #undef MODIFY_POLY\n    res.shrink();\n    return res;\n  }\n  friend poly operator+(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) += rhs; }\n  friend poly operator-(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) -= rhs; }\n  friend poly operator*(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) *= rhs; }\n  friend poly operator/(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) /= rhs; }\n  friend poly operator%(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) %= rhs; }\n};\n\ntemplate <typename\
    \ mod_t> using Poly = Polynomial<mod_t>;\n\n} // namespace lib\n\n#endif"
  dependsOn:
  - math/formal_power_series/formal_power_series.hpp
  - traits/modint.hpp
  - math/formal_power_series/radix_2_NTT.hpp
  isVerificationFile: false
  path: math/formal_power_series/polynomial.hpp
  requiredBy: []
  timestamp: '2021-07-03 02:24:28+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
  - remote_test/yosupo/math/division_of_polynomials.0.test.cpp
documentation_of: math/formal_power_series/polynomial.hpp
layout: document
redirect_from:
- /library/math/formal_power_series/polynomial.hpp
- /library/math/formal_power_series/polynomial.hpp.html
title: "polynomial / \u591A\u9879\u5F0F"
---
