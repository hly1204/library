---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: math/formal_power_series/linearly_recurrent_sequence_Bostan_Mori.hpp
    title: "linearly recurrent sequence Bostan-Mori / \u5E38\u7CFB\u6570\u7EBF\u6027\
      \u9012\u63A8\u5E8F\u5217 Bostan-Mori \u7B97\u6CD5"
  - icon: ':question:'
    path: math/formal_power_series/radix_2_NTT.hpp
    title: "radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362"
  - icon: ':question:'
    path: modint/Montgomery_modint.hpp
    title: "Montgomery modint / Montgomery \u53D6\u6A21\u7C7B"
  - icon: ':question:'
    path: traits/modint.hpp
    title: "modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
    links:
    - https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
  bundledCode: "#line 1 \"remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\"\
    \r\n\r\n#include <algorithm>\r\n#include <iostream>\r\n\r\n#line 1 \"math/formal_power_series/linearly_recurrent_sequence_Bostan_Mori.hpp\"\
    \n\n\n\r\n/**\r\n * @brief linearly recurrent sequence Bostan-Mori / \u5E38\u7CFB\
    \u6570\u7EBF\u6027\u9012\u63A8\u5E8F\u5217 Bostan-Mori \u7B97\u6CD5\r\n *\r\n\
    \ */\r\n\r\n#include <numeric>\r\n\r\n#line 1 \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n\n\n\r\n/**\r\n * @brief radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362\r\n\
    \ * @docs docs/math/formal_power_series/radix_2_NTT.md\r\n */\r\n\r\n#line 10\
    \ \"math/formal_power_series/radix_2_NTT.hpp\"\n#include <cassert>\r\n#include\
    \ <cstdint>\r\n#include <vector>\r\n\r\n#line 1 \"traits/modint.hpp\"\n\n\n\r\n\
    /**\r\n * @brief modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6\r\n *\r\n */\r\
    \n\r\nnamespace lib {\r\n\r\ntemplate <typename mod_t>\r\nstruct modint_traits\
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
    \n}\r\n\r\n} // namespace lib\r\n\r\n\n#line 12 \"math/formal_power_series/linearly_recurrent_sequence_Bostan_Mori.hpp\"\
    \n\r\nnamespace lib {\r\n\r\ntemplate <typename mod_t>\r\nclass LinearlyRecurrentSequence\
    \ {\r\npublic:\r\n  /**\r\n   * @brief \u7EBF\u6027\u9012\u63A8\u5E8F\u5217\r\n\
    \   * @param rec_seq \u9012\u63A8\u5F0F rec_seq = {c_0, c_1, c_2, ..., c_{d-1}}\r\
    \n   * @param init_val \u521D\u503C init_val = {u_0, u_1, u_2, ..., u_{d-1}}\r\
    \n   * @note d \u9636\u7684\u9012\u63A8 u_d = c_0u_0 + c_1u_1 + ... + c_{d-1}u_{d-1}\r\
    \n   */\r\n  LinearlyRecurrentSequence(const std::vector<mod_t> &rec_seq, const\
    \ std::vector<mod_t> &init_val)\r\n      : p_(init_val) {\r\n    int d = rec_seq.size();\r\
    \n    q_.resize(d + 1);\r\n    q_[0] = 1;\r\n    for (int i = 1; i <= d; ++i)\
    \ q_[i] = -rec_seq[d - i];\r\n    // q_ = 1 - c_{d-1}x - c_{d-2}x^2 - ... - c_0x^d\r\
    \n    std::vector<mod_t> q_cpy(q_);\r\n    int len = get_ntt_len((d << 1) + 1);\r\
    \n    q_cpy.resize(len, mod_t(0));\r\n    p_.resize(len, mod_t(0));\r\n    dft(q_cpy);\r\
    \n    dft(p_);\r\n    for (int i = 0; i != len; ++i) p_[i] *= q_cpy[i];\r\n  \
    \  idft(p_);\r\n    p_.resize(d);\r\n  }\r\n  ~LinearlyRecurrentSequence() = default;\r\
    \n\r\n  /**\r\n   * @brief \u5E42\u7EA7\u6570\u5C55\u5F00\u7684\u7B2C n \u9879\
    \r\n   * @param n\r\n   * @return mod_t [x^n]p(x)/q(x)\r\n   */\r\n  mod_t operator[](unsigned\
    \ long long n) const {\r\n    if (n == 0) return p_[0];\r\n    std::vector<mod_t>\
    \ p_cpy(p_), q_cpy(q_);\r\n    int len = get_ntt_len((q_cpy.size() << 1) - 1);\r\
    \n    p_cpy.resize(len, mod_t(0));\r\n    q_cpy.resize(len, mod_t(0));\r\n   \
    \ dft(p_cpy);\r\n    dft(q_cpy);\r\n    for (;; n >>= 1) {                   \
    \                      // p(x)/q(x) = p(x)q(-x)/(q(x)q(-x))\r\n      for (int\
    \ i = 0; i != len; ++i) p_cpy[i] *= q_cpy[i ^ 1]; // p(x)q(-x) \u5206\u5B50\r\n\
    \      if (n & 1) {                                             // \u957F\u5EA6\
    \u4F1A\u53D8\u4E3A\u539F\u5148\u7684\u4E00\u534A\r\n        NTT<mod_t>::odd_dft(len,\
    \ p_cpy.data());\r\n      } else {\r\n        NTT<mod_t>::even_dft(len, p_cpy.data());\r\
    \n      }\r\n      for (int i = 0; i != len; i += 2) q_cpy[i] = q_cpy[i + 1] =\
    \ q_cpy[i] * q_cpy[i + 1];\r\n      NTT<mod_t>::even_dft(len, q_cpy.data());\r\
    \n      if (n == 1) // [x^0](q(x)q(-x))=1 \uFF0C\u4F7F\u7528\u7B2C\u4E00\u79CD\
    \u7C7B\u578B\u7684 accumulate \u5373\u4ECE\u5DE6\u5F00\u59CB fold \u5E76\u7D2F\
    \u52A0\u7B54\u6848\r\n        return std::accumulate(p_cpy.begin(), p_cpy.begin()\
    \ + (len >> 1), mod_t(0)) /\r\n               mod_t(len >> 1);\r\n      // \u82E5\
    \u8981\u5B9E\u73B0\u4EFB\u610F\u6A21\u6570\uFF0C\u6211\u4EEC\u5728\u7528 3 \u6A21\
    \u6570\u7684\u540C\u65F6\uFF0C\u5728 dft_doubling \u7684\u65F6\u5019\u7528 CRT\r\
    \n      // \u5408\u5E76\u51FA\u5F53\u524D\u51C6\u786E\u7684\u503C\u5373\u53EF\uFF0C\
    \u800C\u4E0D\u7528\u53BB\u6D6A\u8D39\u65F6\u95F4\u771F\u7684\u505A\u5B8C\u6574\
    \u7684\u4E58\u6CD5\r\n      NTT<mod_t>::dft_doubling(len >> 1, q_cpy.data());\r\
    \n      NTT<mod_t>::dft_doubling(len >> 1, p_cpy.data());\r\n    }\r\n  }\r\n\r\
    \nprivate:\r\n  std::vector<mod_t> p_, q_; // p(x)/q(x)\r\n};\r\n\r\n} // namespace\
    \ lib\r\n\r\n\n#line 1 \"modint/Montgomery_modint.hpp\"\n\n\n\r\n/**\r\n * @brief\
    \ Montgomery modint / Montgomery \u53D6\u6A21\u7C7B\r\n * @docs docs/modint/Montgomery_modint.md\r\
    \n */\r\n\r\n#line 11 \"modint/Montgomery_modint.hpp\"\n#include <type_traits>\r\
    \n\r\nnamespace lib {\r\n\r\n/**\r\n * @brief Montgomery \u53D6\u6A21\u7C7B\r\n\
    \ * @see https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\r\n\
    \ * @author Nyaan\r\n * @tparam mod \u4E3A\u5947\u6570\u4E14\u5927\u4E8E 1\r\n\
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
    \ = MontgomeryModInt<mod>;\r\n\r\n} // namespace lib\r\n\r\n\n#line 8 \"remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp\"\
    \n\r\nint main() {\r\n#ifdef LOCAL\r\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\r\n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\
    \n  using mint = lib::MontModInt<998244353>;\r\n  int d;\r\n  long long k;\r\n\
    \  std::cin >> d >> k;\r\n  std::vector<mint> rec(d), init_v(d);\r\n  for (auto\
    \ &i : init_v) std::cin >> i;\r\n  for (auto &i : rec) std::cin >> i;\r\n  std::reverse(rec.begin(),\
    \ rec.end());\r\n  lib::LinearlyRecurrentSequence seq(rec, init_v);\r\n  std::cout\
    \ << seq[k];\r\n  return 0;\r\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\"\
    \r\n\r\n#include <algorithm>\r\n#include <iostream>\r\n\r\n#include \"math/formal_power_series/linearly_recurrent_sequence_Bostan_Mori.hpp\"\
    \r\n#include \"modint/Montgomery_modint.hpp\"\r\n\r\nint main() {\r\n#ifdef LOCAL\r\
    \n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\r\
    \n#endif\r\n  std::ios::sync_with_stdio(false);\r\n  std::cin.tie(0);\r\n  using\
    \ mint = lib::MontModInt<998244353>;\r\n  int d;\r\n  long long k;\r\n  std::cin\
    \ >> d >> k;\r\n  std::vector<mint> rec(d), init_v(d);\r\n  for (auto &i : init_v)\
    \ std::cin >> i;\r\n  for (auto &i : rec) std::cin >> i;\r\n  std::reverse(rec.begin(),\
    \ rec.end());\r\n  lib::LinearlyRecurrentSequence seq(rec, init_v);\r\n  std::cout\
    \ << seq[k];\r\n  return 0;\r\n}"
  dependsOn:
  - math/formal_power_series/linearly_recurrent_sequence_Bostan_Mori.hpp
  - math/formal_power_series/radix_2_NTT.hpp
  - traits/modint.hpp
  - modint/Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  requiredBy: []
  timestamp: '2021-07-15 17:09:18+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
- /verify/remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp.html
title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
---
