---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series/linearly_recurrent_sequence.hpp
    title: "linearly recurrent sequence / \u5E38\u7CFB\u6570\u7EBF\u6027\u9012\u63A8\
      \u5E8F\u5217"
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
    PROBLEM: https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
    links:
    - https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence
  bundledCode: "#line 1 \"remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\"\
    \n\n#include <algorithm>\n#include <iostream>\n\n#line 1 \"math/formal_power_series/linearly_recurrent_sequence.hpp\"\
    \n\n\n\n/**\n * @brief linearly recurrent sequence / \u5E38\u7CFB\u6570\u7EBF\u6027\
    \u9012\u63A8\u5E8F\u5217\n *\n */\n\n#include <numeric>\n\n#line 1 \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n\n\n\n/**\n * @brief radix-2 NTT / \u57FA-2 \u6570\u8BBA\u53D8\u6362\n *\n */\n\
    \n#line 10 \"math/formal_power_series/radix_2_NTT.hpp\"\n#include <cassert>\n\
    #include <cstdint>\n#include <vector>\n\n#line 1 \"traits/modint.hpp\"\n\n\n\n\
    /**\n * @brief modint traits / \u53D6\u6A21\u7C7B\u8403\u53D6\n *\n */\n\nnamespace\
    \ lib {\n\ntemplate <typename mod_t> struct modint_traits {\n  using type = typename\
    \ mod_t::value_type;\n  static constexpr type get_mod() { return mod_t::get_mod();\
    \ }\n  static constexpr type get_primitive_root_prime() { return mod_t::get_primitive_root_prime();\
    \ }\n};\n\n} // namespace lib\n\n\n#line 15 \"math/formal_power_series/radix_2_NTT.hpp\"\
    \n\nnamespace lib {\n\n// \u5FC5\u987B\u7528 NTT \u53CB\u597D\u7684\u6A21\u6570\
    \uFF01\uFF01\uFF01\ntemplate <typename mod_t> class NTT {\npublic:\n  NTT() =\
    \ delete;\n\n  static void set_root(int len) {\n    static int lim = 0;\n    static\
    \ constexpr mod_t g(modint_traits<mod_t>::get_primitive_root_prime());\n    if\
    \ (lim == 0) {\n      rt.resize(1 << 20);\n      irt.resize(1 << 20);\n      rt[0]\
    \ = irt[0] = 1;\n      mod_t g_t = g.pow(modint_traits<mod_t>::get_mod() >> 21),\
    \ ig_t = g_t.inv();\n      rt[1 << 19] = g_t, irt[1 << 19] = ig_t;\n      for\
    \ (int i = 18; i >= 0; --i) {\n        g_t *= g_t, ig_t *= ig_t;\n        rt[1\
    \ << i] = g_t, irt[1 << i] = ig_t;\n      }\n      lim = 1;\n    }\n    for (;\
    \ (lim << 1) < len; lim <<= 1) {\n      mod_t g = rt[lim], ig = irt[lim];\n  \
    \    for (int i = lim + 1, e = lim << 1; i < e; ++i) {\n        rt[i] = rt[i -\
    \ lim] * g;\n        irt[i] = irt[i - lim] * ig;\n      }\n    }\n  }\n\n  static\
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
    \ x(-1) \u7B49\uFF0C\n * \u5BF9\u4E8E\u4E0B\u6807 i \u548C i^1 \u5FC5\u7136\u662F\
    \u4E24\u4E2A\u4E92\u4E3A\u76F8\u53CD\u6570\u7684\u70B9\u503C\n *\n * @tparam mod_t\n\
    \ * @param n\n * @param x\n */\ntemplate <typename mod_t> void dft(int n, mod_t\
    \ *x) {\n  NTT<mod_t>::set_root(n);\n  NTT<mod_t>::dft(n, x);\n}\n\n/**\n * @brief\
    \ \u63A5\u6536\u4E8C\u8FDB\u5236\u7FFB\u8F6C\u540E\u7684 DFT \u5E8F\u5217\uFF0C\
    \u8FD4\u56DE\u591A\u9879\u5F0F\u5E8F\u5217 mod (x^n - 1)\n *\n * @tparam mod_t\n\
    \ * @param n\n * @param x\n */\ntemplate <typename mod_t> void idft(int n, mod_t\
    \ *x) {\n  NTT<mod_t>::set_root(n);\n  NTT<mod_t>::idft(n, x);\n}\n\ntemplate\
    \ <typename mod_t> void dft(std::vector<mod_t> &x) {\n  NTT<mod_t>::set_root(x.size());\n\
    \  NTT<mod_t>::dft(x.size(), x.data());\n}\n\ntemplate <typename mod_t> void idft(std::vector<mod_t>\
    \ &x) {\n  NTT<mod_t>::set_root(x.size());\n  NTT<mod_t>::idft(x.size(), x.data());\n\
    }\n\n} // namespace lib\n\n\n#line 12 \"math/formal_power_series/linearly_recurrent_sequence.hpp\"\
    \n\nnamespace lib {\n\ntemplate <typename mod_t> class LinearlyRecurrentSequence\
    \ {\npublic:\n  /**\n   * @brief \u521B\u5EFA\u4E00\u4E2A\u65B0\u7684\u7EBF\u6027\
    \u9012\u63A8\u5E8F\u5217\u5BF9\u8C61\n   *\n   * @param rec_seq \u9012\u63A8\u5F0F\
    \n   * @param init_val \u521D\u503C\n   */\n  LinearlyRecurrentSequence(const\
    \ std::vector<mod_t> &rec_seq, const std::vector<mod_t> &init_val)\n      : p_(init_val)\
    \ {\n    // rec_seq = {c_0, c_1, c_2, ..., c_{d-1}}\n    // init_val = {u_0, u_1,\
    \ u_2, ..., u_{d-1}}\n    // u_d = c_0u_0 + c_1u_1 + ... + c_{d-1}u_{d-1}\n  \
    \  // d \u9636\u7684\u9012\u63A8\n    int d = rec_seq.size();\n    q_.resize(d\
    \ + 1);\n    q_[0] = 1;\n    for (int i = 1; i <= d; ++i) q_[i] = -rec_seq[d -\
    \ i];\n    // q_ = 1 - c_{d-1}x - c_{d-2}x^2 - ... - c_0x^d\n    std::vector<mod_t>\
    \ q_cpy(q_);\n    int len = get_ntt_len((d << 1) + 1);\n    q_cpy.resize(len,\
    \ mod_t(0));\n    p_.resize(len, mod_t(0));\n    dft(q_cpy);\n    dft(p_);\n \
    \   for (int i = 0; i != len; ++i) p_[i] *= q_cpy[i];\n    idft(p_);\n    p_.resize(d);\n\
    \  }\n  ~LinearlyRecurrentSequence() = default;\n\n  /**\n   * @brief \u5E42\u7EA7\
    \u6570\u5C55\u5F00\u7684\u7B2C n \u9879\n   *\n   * @param n\n   * @return mod_t\
    \ [x^n]p(x)/q(x)\n   */\n  mod_t operator[](unsigned long long n) const {\n  \
    \  if (n == 0) return p_[0];\n    std::vector<mod_t> p_cpy(p_), q_cpy(q_);\n \
    \   int len = get_ntt_len((q_cpy.size() << 1) - 1);\n    p_cpy.resize(len, mod_t(0));\n\
    \    q_cpy.resize(len, mod_t(0));\n    dft(p_cpy);\n    dft(q_cpy);\n    for (;;\
    \ n >>= 1) {                                         // p(x)/q(x) = p(x)q(-x)/(q(x)q(-x))\n\
    \      for (int i = 0; i != len; ++i) p_cpy[i] *= q_cpy[i ^ 1]; // p(x)q(-x) \u5206\
    \u5B50\n      if (n & 1) {                                             // \u957F\
    \u5EA6\u4F1A\u53D8\u4E3A\u539F\u5148\u7684\u4E00\u534A\n        NTT<mod_t>::odd_dft(len,\
    \ p_cpy.data());\n      } else {\n        NTT<mod_t>::even_dft(len, p_cpy.data());\n\
    \      }\n      for (int i = 0; i != len; i += 2) q_cpy[i] = q_cpy[i + 1] = q_cpy[i]\
    \ * q_cpy[i + 1];\n      NTT<mod_t>::even_dft(len, q_cpy.data());\n      if (n\
    \ == 1) // [x^0](q(x)q(-x))=1 \uFF0C\u4F7F\u7528\u7B2C\u4E00\u79CD\u7C7B\u578B\
    \u7684 accumulate \u5373\u4ECE\u5DE6\u5F00\u59CB fold \u5E76\u7D2F\u52A0\u7B54\
    \u6848\n        return std::accumulate(p_cpy.begin(), p_cpy.begin() + (len >>\
    \ 1), mod_t(0)) /\n               mod_t(len >> 1);\n      // \u82E5\u8981\u5B9E\
    \u73B0\u4EFB\u610F\u6A21\u6570\uFF0C\u6211\u4EEC\u5728\u7528 3 \u6A21\u6570\u7684\
    \u540C\u65F6\uFF0C\u5728 dft_doubling \u7684\u65F6\u5019\u7528 CRT\n      // \u5408\
    \u5E76\u51FA\u5F53\u524D\u51C6\u786E\u7684\u503C\u5373\u53EF\uFF0C\u800C\u4E0D\
    \u7528\u53BB\u6D6A\u8D39\u65F6\u95F4\u771F\u7684\u505A\u5B8C\u6574\u7684\u4E58\
    \u6CD5\n      NTT<mod_t>::dft_doubling(len >> 1, q_cpy.data());\n      NTT<mod_t>::dft_doubling(len\
    \ >> 1, p_cpy.data());\n    }\n  }\n\nprivate:\n  std::vector<mod_t> p_, q_; //\
    \ p(x)/q(x)\n};\n\n} // namespace lib\n\n\n#line 1 \"modint/Montgomery_modint.hpp\"\
    \n\n\n\n/**\n * @brief Montgomery modint / Montgomery \u53D6\u6A21\u7C7B\n *\n\
    \ */\n\n#line 11 \"modint/Montgomery_modint.hpp\"\n#include <type_traits>\n\n\
    namespace lib {\n\n/**\n * @brief Montgomery \u53D6\u6A21\u7C7B\n * @ref https://nyaannyaan.github.io/library/modint/montgomery-modint.hpp\n\
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
    \ // namespace lib\n\n\n#line 8 \"remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp\"\
    \n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(0);\n\
    \  using mint = lib::MontModInt<998244353>;\n  int d;\n  long long k;\n  std::cin\
    \ >> d >> k;\n  std::vector<mint> rec(d), init_v(d);\n  for (auto &i : init_v)\
    \ std::cin >> i;\n  for (auto &i : rec) std::cin >> i;\n  std::reverse(rec.begin(),\
    \ rec.end());\n  lib::LinearlyRecurrentSequence seq(rec, init_v);\n  std::cout\
    \ << seq[k];\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence\"\
    \n\n#include <algorithm>\n#include <iostream>\n\n#include \"math/formal_power_series/linearly_recurrent_sequence.hpp\"\
    \n#include \"modint/Montgomery_modint.hpp\"\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"\
    in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(0);\n  using mint = lib::MontModInt<998244353>;\n  int d;\n  long\
    \ long k;\n  std::cin >> d >> k;\n  std::vector<mint> rec(d), init_v(d);\n  for\
    \ (auto &i : init_v) std::cin >> i;\n  for (auto &i : rec) std::cin >> i;\n  std::reverse(rec.begin(),\
    \ rec.end());\n  lib::LinearlyRecurrentSequence seq(rec, init_v);\n  std::cout\
    \ << seq[k];\n  return 0;\n}"
  dependsOn:
  - math/formal_power_series/linearly_recurrent_sequence.hpp
  - math/formal_power_series/radix_2_NTT.hpp
  - traits/modint.hpp
  - modint/Montgomery_modint.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  requiredBy: []
  timestamp: '2021-06-11 23:09:55+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
- /verify/remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp.html
title: remote_test/yosupo/math/kth_term_of_linearly_recurrent_sequence.0.test.cpp
---
