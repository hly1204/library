---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: math/formal_power_series/formal_power_series.hpp
    title: "basic operations of formal power series / \u5F62\u5F0F\u5E42\u7EA7\u6570\
      \u7684\u57FA\u672C\u64CD\u4F5C"
  - icon: ':question:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362"
  - icon: ':question:'
    path: traits/modint.hpp
    title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
    title: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
    title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
    title: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
    title: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
    title: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    _deprecated_at_docs: docs/math/formal_power_series/polynomial.md
    document_title: "polynomial / \u591A\u9879\u5F0F"
    links: []
  bundledCode: "#line 1 \"math/formal_power_series/polynomial.hpp\"\n\n\n\r\n/**\r\
    \n * @brief polynomial / \u591A\u9879\u5F0F\r\n * @docs docs/math/formal_power_series/polynomial.md\r\
    \n */\r\n\r\n#line 1 \"math/formal_power_series/formal_power_series.hpp\"\n\n\n\
    \r\n/**\r\n * @brief basic operations of formal power series / \u5F62\u5F0F\u5E42\
    \u7EA7\u6570\u7684\u57FA\u672C\u64CD\u4F5C\r\n * @docs docs/math/formal_power_series/formal_power_series.md\r\
    \n */\r\n\r\n#include <algorithm>\r\n#include <cassert>\r\n#include <numeric>\r\
    \n#include <tuple>\r\n#include <utility>\r\n#include <vector>\r\n\r\n#line 1 \"\
    traits/modint.hpp\"\n\n\n\r\n/**\r\n * @brief modint traits / \u53D6\u6A21\u7C7B\
    \u8403\u53D6\r\n *\r\n */\r\n\r\nnamespace lib {\r\n\r\ntemplate <typename mod_t>\r\
    \nstruct modint_traits {\r\n  using type = typename mod_t::value_type;\r\n  static\
    \ constexpr type get_mod() { return mod_t::get_mod(); }\r\n  static constexpr\
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
    \n}\r\n\r\n} // namespace lib\r\n\r\n\n#line 18 \"math/formal_power_series/formal_power_series.hpp\"\
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
    \n\r\n  static inline vec INV;\r\n\r\n  static void init_inv(int n) { // \u9884\
    \u5904\u7406 [1, n) \u7684\u9006\u5143\r\n    static constexpr auto mod = modint_traits<mod_t>::get_mod();\r\
    \n    int lim                   = INV.size();\r\n    if (lim < n) {\r\n      INV.resize(n);\r\
    \n      if (lim == 0) INV[1] = 1, lim = 2;\r\n      for (int i = lim; i < n; ++i)\
    \ INV[i] = mod_t(mod - mod / i) * INV[mod % i];\r\n    }\r\n  }\r\n\r\npublic:\r\
    \n  using std::vector<mod_t>::vector;\r\n\r\n  /**\r\n   * @brief \u83B7\u53D6\
    \u5EA6\u6570\r\n   * @note \u7279\u4F8B\u4E3A deg(0)=-1\r\n   * @return int\r\n\
    \   */\r\n  int deg() const {\r\n    static constexpr mod_t Z = 0;\r\n    int\
    \ n                    = int(this->size()) - 1;\r\n    while (n >= 0 && this->operator[](n)\
    \ == Z) --n;\r\n    return n;\r\n  }\r\n\r\n  /**\r\n   * @brief \u83B7\u53D6\u6700\
    \u9AD8\u6B21\u9879\u7684\u7CFB\u6570\r\n   * @return mod_t\r\n   */\r\n  mod_t\
    \ leading_coeff() const {\r\n    int d = deg();\r\n    return d == -1 ? mod_t(0)\
    \ : this->operator[](d);\r\n  }\r\n\r\n  /**\r\n   * @brief \u53BB\u9664\u5C3E\
    \ 0 \uFF0C\u4F46\u5982\u679C\u53EA\u6709\u4E00\u4E2A 0 \u5219\u4F1A\u4FDD\u7559\
    \r\n   */\r\n  void shrink() { this->resize(std::max(deg() + 1, 1)); }\r\n  fps\
    \ slice() const { return fps(*this); }\r\n  fps slice(int n) const {\r\n    assert(n\
    \ >= 0);\r\n    int sz = this->size();\r\n    if (sz >= n) return fps(this->begin(),\
    \ this->begin() + n);\r\n    fps res(*this);\r\n    res.resize(n, mod_t(0));\r\
    \n    return res;\r\n  }\r\n\r\n  fps deriv() const {\r\n    int n = this->size();\r\
    \n    if (n <= 1) return {0};\r\n    fps res(n - 1);\r\n    for (int i = 1; i\
    \ != n; ++i) res[i - 1] = this->operator[](i) * mod_t(i);\r\n    return res;\r\
    \n  }\r\n\r\n  fps integr(const mod_t &c = mod_t(0)) const {\r\n    int n = this->size()\
    \ + 1;\r\n    fps res(n);\r\n    res[0] = c;\r\n    init_inv(n);\r\n    for (int\
    \ i = 1; i != n; ++i) res[i] = this->operator[](i - 1) * INV[i];\r\n    return\
    \ res;\r\n  }\r\n\r\n  fps operator-() const {\r\n    fps res(this->size());\r\
    \n    for (int i = 0, e = this->size(); i != e; ++i) res[i] = -this->operator[](i);\r\
    \n    return res;\r\n  }\r\n\r\n  fps &operator+=(const fps &rhs) {\r\n    if\
    \ (this->size() < rhs.size()) this->resize(rhs.size(), mod_t(0));\r\n    for (int\
    \ i = 0, e = rhs.size(); i != e; ++i) this->operator[](i) += rhs[i];\r\n    return\
    \ *this;\r\n  }\r\n  fps &operator-=(const fps &rhs) {\r\n    if (this->size()\
    \ < rhs.size()) this->resize(rhs.size(), mod_t(0));\r\n    for (int i = 0, e =\
    \ rhs.size(); i != e; ++i) this->operator[](i) -= rhs[i];\r\n    return *this;\r\
    \n  }\r\n  fps &operator*=(const fps &rhs) {\r\n    int n = this->size(), m =\
    \ rhs.size();\r\n    if (std::min(n, m) <= 32) {\r\n      fps res(n + m - 1, mod_t(0));\r\
    \n      for (int i = 0; i != n; ++i) {\r\n        for (int j = 0; j != m; ++j)\
    \ { res[i + j] += this->operator[](i) * rhs[j]; }\r\n      }\r\n      return this->operator=(res);\r\
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
    \r\n\n#line 10 \"math/formal_power_series/polynomial.hpp\"\n\r\nnamespace lib\
    \ {\r\n\r\n/**\r\n * @brief \u591A\u9879\u5F0F\u7C7B\r\n * @note \u57FA\u7C7B\
    \ FormalPowerSeries \u4E2D\u51FD\u6570\u90FD\u6CA1\u6709\u4F7F\u7528 virtual\r\
    \n *       \u6240\u4EE5\u5728\u8BE5\u7C7B\u4E2D\u6709\u5B9A\u4E49\u76F8\u540C\u7684\
    \u51FD\u6570\u5219\u4F1A\u963B\u6B62\u8C03\u7528\u57FA\u7C7B\u7684\u51FD\u6570\
    \r\n *       \u8FD9\u88AB\u79F0\u4E3A\u9690\u85CF\uFF08 hide \uFF09\u3002\r\n\
    \ *       \u800C\u5982\u679C\u4F7F\u7528\u4E86 virtual \u5219\u88AB\u79F0\u4E3A\
    \u8986\u76D6\uFF08 override \uFF09\uFF0C\u800C\u8986\u76D6\u4F1A\u5BFC\u51FA\u591A\
    \u6001\u3002\r\n */\r\ntemplate <typename mod_t>\r\nclass Polynomial : public\
    \ FormalPowerSeries<mod_t> {\r\npublic:\r\n  using fps  = FormalPowerSeries<mod_t>;\r\
    \n  using poly = Polynomial<mod_t>;\r\n  using FormalPowerSeries<mod_t>::FormalPowerSeries;\r\
    \n\r\n  // \u4F7F\u5F97\u80FD\u591F\u4ECE FormalPowerSeries \u8F6C\u6362\u4E3A\
    \ Polynomial \u7C7B\u578B\uFF0C\u4F46\u4E0D\u6E05\u695A\u662F\u5426\u6709\u4EC0\
    \u4E48\u95EE\u9898\r\n  Polynomial(const fps &rhs) : fps(rhs) {}\r\n  Polynomial(fps\
    \ &&rhs) : fps(std::move(rhs)) {}\r\n\r\n  poly operator-() const {\r\n    poly\
    \ res = this->fps::operator-();\r\n    res.shrink();\r\n    return res;\r\n  }\r\
    \n  poly &operator+=(const poly &rhs) {\r\n    this->fps::operator+=(rhs);\r\n\
    \    this->shrink();\r\n    return *this;\r\n  }\r\n  poly &operator-=(const poly\
    \ &rhs) {\r\n    this->fps::operator-=(rhs);\r\n    this->shrink();\r\n    return\
    \ *this;\r\n  }\r\n  poly &operator*=(const poly &rhs) {\r\n    this->fps::operator*=(rhs);\r\
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
    \ shift(mod_t c) const {\r\n    static std::vector<mod_t> FAC, IFAC;\r\n    int\
    \ lim = FAC.size();\r\n    int n   = this->deg();\r\n    if (n < 1) return poly(*this);\r\
    \n    if (lim <= n) {\r\n      FAC.resize(n + 1);\r\n      IFAC.resize(n + 1);\r\
    \n      if (lim == 0) FAC[0] = IFAC[0] = mod_t(1), lim = 1;\r\n      for (int\
    \ i = lim; i <= n; ++i) FAC[i] = FAC[i - 1] * mod_t(i);\r\n      IFAC.back() =\
    \ mod_t(1) / FAC.back();\r\n      mod_t t     = IFAC.back();\r\n      for (int\
    \ i = n - 1; i >= lim; --i) IFAC[i] = (t *= mod_t(i + 1));\r\n    }\r\n    poly\
    \ A(*this), B(n + 1);\r\n    mod_t c_i(1);\r\n    for (int i = 0; i <= n; ++i)\
    \ A[i] *= FAC[i], B[i] = c_i * IFAC[i], c_i *= c;\r\n    std::reverse(A.begin(),\
    \ A.end());\r\n    A *= B;\r\n    A.resize(n + 1);\r\n    std::reverse(A.begin(),\
    \ A.end());\r\n    for (int i = 0; i <= n; ++i) A[i] *= IFAC[i];\r\n    return\
    \ A;\r\n  }\r\n\r\n  friend poly operator+(const poly &lhs, const poly &rhs) {\
    \ return poly(lhs) += rhs; }\r\n  friend poly operator-(const poly &lhs, const\
    \ poly &rhs) { return poly(lhs) -= rhs; }\r\n  friend poly operator*(const poly\
    \ &lhs, const poly &rhs) { return poly(lhs) *= rhs; }\r\n  friend poly operator/(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) /= rhs; }\r\n  friend poly operator%(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) %= rhs; }\r\n};\r\n\r\ntemplate\
    \ <typename mod_t>\r\nusing Poly = Polynomial<mod_t>;\r\n\r\n} // namespace lib\r\
    \n\r\n\n"
  code: "#ifndef POLYNOMIAL_HEADER_HPP\r\n#define POLYNOMIAL_HEADER_HPP\r\n\r\n/**\r\
    \n * @brief polynomial / \u591A\u9879\u5F0F\r\n * @docs docs/math/formal_power_series/polynomial.md\r\
    \n */\r\n\r\n#include \"formal_power_series.hpp\"\r\n\r\nnamespace lib {\r\n\r\
    \n/**\r\n * @brief \u591A\u9879\u5F0F\u7C7B\r\n * @note \u57FA\u7C7B FormalPowerSeries\
    \ \u4E2D\u51FD\u6570\u90FD\u6CA1\u6709\u4F7F\u7528 virtual\r\n *       \u6240\u4EE5\
    \u5728\u8BE5\u7C7B\u4E2D\u6709\u5B9A\u4E49\u76F8\u540C\u7684\u51FD\u6570\u5219\
    \u4F1A\u963B\u6B62\u8C03\u7528\u57FA\u7C7B\u7684\u51FD\u6570\r\n *       \u8FD9\
    \u88AB\u79F0\u4E3A\u9690\u85CF\uFF08 hide \uFF09\u3002\r\n *       \u800C\u5982\
    \u679C\u4F7F\u7528\u4E86 virtual \u5219\u88AB\u79F0\u4E3A\u8986\u76D6\uFF08 override\
    \ \uFF09\uFF0C\u800C\u8986\u76D6\u4F1A\u5BFC\u51FA\u591A\u6001\u3002\r\n */\r\n\
    template <typename mod_t>\r\nclass Polynomial : public FormalPowerSeries<mod_t>\
    \ {\r\npublic:\r\n  using fps  = FormalPowerSeries<mod_t>;\r\n  using poly = Polynomial<mod_t>;\r\
    \n  using FormalPowerSeries<mod_t>::FormalPowerSeries;\r\n\r\n  // \u4F7F\u5F97\
    \u80FD\u591F\u4ECE FormalPowerSeries \u8F6C\u6362\u4E3A Polynomial \u7C7B\u578B\
    \uFF0C\u4F46\u4E0D\u6E05\u695A\u662F\u5426\u6709\u4EC0\u4E48\u95EE\u9898\r\n \
    \ Polynomial(const fps &rhs) : fps(rhs) {}\r\n  Polynomial(fps &&rhs) : fps(std::move(rhs))\
    \ {}\r\n\r\n  poly operator-() const {\r\n    poly res = this->fps::operator-();\r\
    \n    res.shrink();\r\n    return res;\r\n  }\r\n  poly &operator+=(const poly\
    \ &rhs) {\r\n    this->fps::operator+=(rhs);\r\n    this->shrink();\r\n    return\
    \ *this;\r\n  }\r\n  poly &operator-=(const poly &rhs) {\r\n    this->fps::operator-=(rhs);\r\
    \n    this->shrink();\r\n    return *this;\r\n  }\r\n  poly &operator*=(const\
    \ poly &rhs) {\r\n    this->fps::operator*=(rhs);\r\n    this->shrink();\r\n \
    \   return *this;\r\n  }\r\n  poly &operator/=(const poly &rhs) {\r\n    assert(rhs.deg()\
    \ >= 0);\r\n    this->shrink();\r\n    int quo_size = this->deg() - rhs.deg()\
    \ + 1;\r\n    if (quo_size <= 0) {\r\n      this->resize(1);\r\n      this->operator[](0)\
    \ = 0;\r\n      return *this;\r\n    }\r\n    poly rhs_cpy(rhs);\r\n    rhs_cpy.shrink();\r\
    \n    std::reverse(this->begin(), this->end());\r\n    std::reverse(rhs_cpy.begin(),\
    \ rhs_cpy.end());\r\n    poly quo(this->div(quo_size, rhs_cpy));\r\n    this->resize(quo_size);\r\
    \n    std::reverse_copy(quo.begin(), quo.end(), this->begin());\r\n    return\
    \ *this;\r\n  }\r\n  poly &operator%=(const poly &rhs) {\r\n    // f/g => f=gq+r,\
    \ deg(r)<deg(g) \u5728\u8FD9\u91CC f \u5C31\u662F (*this) \u800C g \u5C31\u662F\
    \ rhs\r\n    // r=f-gq (mod ((x^deg(rhs)) - 1))\r\n    // \u6240\u4EE5\u6211\u4EEC\
    \u505A NTT \u7684\u957F\u5EA6\u53EF\u4EE5\u662F O(deg(rhs)) \u7EA7\u522B\u7684\
    \r\n    int rem_size = rhs.deg();\r\n    assert(rem_size >= 0);\r\n    if (rem_size\
    \ == 0) {\r\n      this->resize(1);\r\n      this->operator[](0) = 0;\r\n    \
    \  return *this;\r\n    }\r\n    this->shrink();\r\n    if (this->deg() < rem_size)\
    \ return *this;\r\n    poly quo((*this) / rhs), rhs_cpy(rhs);\r\n    int len =\
    \ get_ntt_len(rem_size);\r\n    // \u4EE4 (*this) \u548C quo \u548C rhs_cpy \u90FD\
    \u5728 mod ((x^len) - 1) \u610F\u4E49\u4E0B\r\n    int mask = len - 1;\r\n   \
    \ for (int i = len, e = this->size(); i < e; ++i)\r\n      this->operator[](i\
    \ &mask) += this->operator[](i);\r\n    for (int i = len, e = quo.size(); i <\
    \ e; ++i) quo[i & mask] += quo[i];\r\n    for (int i = len, e = rhs_cpy.size();\
    \ i < e; ++i) rhs_cpy[i & mask] += rhs_cpy[i];\r\n    this->resize(len, mod_t(0));\r\
    \n    quo.resize(len, mod_t(0));\r\n    rhs_cpy.resize(len, mod_t(0));\r\n   \
    \ dft(len, rhs_cpy.data());\r\n    dft(len, quo.data());\r\n    for (int i = 0;\
    \ i != len; ++i) rhs_cpy[i] *= quo[i];\r\n    idft(len, rhs_cpy.data());\r\n \
    \   this->resize(rem_size);\r\n    for (int i = 0; i != rem_size; ++i) this->operator[](i)\
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
    \ shift(mod_t c) const {\r\n    static std::vector<mod_t> FAC, IFAC;\r\n    int\
    \ lim = FAC.size();\r\n    int n   = this->deg();\r\n    if (n < 1) return poly(*this);\r\
    \n    if (lim <= n) {\r\n      FAC.resize(n + 1);\r\n      IFAC.resize(n + 1);\r\
    \n      if (lim == 0) FAC[0] = IFAC[0] = mod_t(1), lim = 1;\r\n      for (int\
    \ i = lim; i <= n; ++i) FAC[i] = FAC[i - 1] * mod_t(i);\r\n      IFAC.back() =\
    \ mod_t(1) / FAC.back();\r\n      mod_t t     = IFAC.back();\r\n      for (int\
    \ i = n - 1; i >= lim; --i) IFAC[i] = (t *= mod_t(i + 1));\r\n    }\r\n    poly\
    \ A(*this), B(n + 1);\r\n    mod_t c_i(1);\r\n    for (int i = 0; i <= n; ++i)\
    \ A[i] *= FAC[i], B[i] = c_i * IFAC[i], c_i *= c;\r\n    std::reverse(A.begin(),\
    \ A.end());\r\n    A *= B;\r\n    A.resize(n + 1);\r\n    std::reverse(A.begin(),\
    \ A.end());\r\n    for (int i = 0; i <= n; ++i) A[i] *= IFAC[i];\r\n    return\
    \ A;\r\n  }\r\n\r\n  friend poly operator+(const poly &lhs, const poly &rhs) {\
    \ return poly(lhs) += rhs; }\r\n  friend poly operator-(const poly &lhs, const\
    \ poly &rhs) { return poly(lhs) -= rhs; }\r\n  friend poly operator*(const poly\
    \ &lhs, const poly &rhs) { return poly(lhs) *= rhs; }\r\n  friend poly operator/(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) /= rhs; }\r\n  friend poly operator%(const\
    \ poly &lhs, const poly &rhs) { return poly(lhs) %= rhs; }\r\n};\r\n\r\ntemplate\
    \ <typename mod_t>\r\nusing Poly = Polynomial<mod_t>;\r\n\r\n} // namespace lib\r\
    \n\r\n#endif"
  dependsOn:
  - math/formal_power_series/formal_power_series.hpp
  - traits/modint.hpp
  - math/formal_power_series/radix_2_NTT.hpp
  isVerificationFile: false
  path: math/formal_power_series/polynomial.hpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.2.test.cpp
  - remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
documentation_of: math/formal_power_series/polynomial.hpp
layout: document
redirect_from:
- /library/math/formal_power_series/polynomial.hpp
- /library/math/formal_power_series/polynomial.hpp.html
title: "polynomial / \u591A\u9879\u5F0F"
---
## 欧几里得商数和欧几里得余数

或称为带余除法。对于多项式 $f$ 与 $g$ 且 $\deg(f)\geq\deg(g)$ 我们假设其属于欧几里得整环上，那么存在 $f=gq+r$ 其中 $\deg(r)\lt \deg(g)$ 且 $\deg(q)=\deg(f)-\deg(g)$ ，那么说 $r$ 是欧几里得余数和 $q$ 是欧几里得商数（存在且唯一，证略）。我们可以考虑使用幂级数的逆元来得到这两者。我们发现 $gq$ 与 $f$ 的高位是相等的，那么

$$
x^{\deg(f)}f\left(x^{-1}\right)=g\left(x^{-1}\right)q\left(x^{-1}\right)x^{\deg(f)}+r\left(x^{-1}\right)x^{\deg(f)}
$$

发现 $r\left(x^{-1}\right)x^{\deg(f)}$ 影响的是高位，有

$$
x^{\deg(f)}f\left(x^{-1}\right)=\left(x^{\deg(g)}g\left(x^{-1}\right)\right)\left(x^{\deg(q)}q\left(x^{-1}\right)\right)+\left(x^{\deg(r)}r\left(x^{-1}\right)x^{\deg(f)-\deg(r)}\right)
$$

而 $\deg(r)\lt\deg(g)\implies \deg(f)-\deg(r)\geq\deg(f)-\deg(g)+1\gt\deg(q)$ 那么

$$
x^{\deg(q)}q\left(x^{-1}\right)\equiv x^{\deg(f)}f\left(x^{-1}\right)\left(x^{\deg(g)}g\left(x^{-1}\right)\right)^{-1}\pmod{x^{\deg(f)-\deg(g)+1}}
$$

且我们保留了 $q$ 的所有信息，所需要的无非是将多项式“系数翻转”。

求出 $q$ 后代入可求得 $r$ ，而我们知道 $f$ 和 $gq$ 高位是相等的，可以求 $r\equiv f-qg\pmod{(x^{\deg(g)}-1)}$ 。当 $\deg(f)-\deg(g)$ 较小时，我们不使用 NTT 计算会更快。 [EntropyIncreaser](https://loj.ac/u/EntropyIncreaser) 很早在 <https://loj.ac/s/943026> 已经使用了这个方法（不愧是 EI ！），当时我也并未理解。

## 多项式平移

给出多项式 $A(x)=\sum _ {i=0}^na _ {i}x^{i}$ 且 $\deg(A(x))=n\gt 0$ ，要求 $A(x+c)$ 的系数，我们在 $c$ 处应用泰勒公式，有

$$
A(x)=A(c)+\frac{A'(c)}{1!}(x-c)+\frac{A''(c)}{2!}(x-c)^{2}+\cdots +\frac{A^{(n)}(c)}{1!}(x-c)^{n}
$$

那么 $A(x+c)$ 是

$$
A(x+c)=A(c)+\frac{A'(c)}{1!}x+\frac{A''(c)}{2!}x^{2}+\cdots +\frac{A^{(n)}(c)}{1!}x^{n}
$$

观察发现

$$
\begin{aligned}
t!\lbrack x^t\rbrack A(x+c)&=A^{(t)}(c)\\
&=\sum _ {i=t}^{n}a _ {i}i!\frac{c^{i-t}}{(i-t)!}\\
&=\sum _ {i=0}^{n-t}a _ {i+t}(i+t)!\frac{c^i}{i!}
\end{aligned}
$$

我们令 $A_0(x)=\sum _ {i=0}^na _ {n-i}(n-i)!x^i$ 和 $B_0(x)=\sum _ {i=0}^n\frac{c^i}{i!}x^i$ 那么

$$
\begin{aligned}
\lbrack x^{n-t}\rbrack (A_0(x)B_0(x))&=\sum _ {i=0}^{n-t}(\lbrack x^{n-t-i}\rbrack A_0(x))(\lbrack x^i\rbrack B_0(x))\\
&=\sum _ {i=0}^{n-t}a _ {i+t}(i+t)!\frac{c^i}{i!}\\
&=t!\lbrack x^t\rbrack A(x+c)
\end{aligned}
$$

<!-- 注意这里的 Markdown 中 `[]()` 这种不能挨着写，否则会识别错误！ -->

可以通过一次多项式乘法得到。一般来说我们假设 $A(x)\in\mathbb{F} _ p\lbrack x\rbrack$ 其中 $p$ 比较大使得 $\deg(A(x))\lt p$ 。
