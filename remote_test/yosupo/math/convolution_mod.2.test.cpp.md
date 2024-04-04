---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: math/czt.hpp
    title: Chirp Z-transform (Bluestein's algorithm) (in $\mathbb{F} _ p \lbrack z
      \rbrack$ for FFT prime $p$)
  - icon: ':heavy_check_mark:'
    path: math/radix2_ntt.hpp
    title: Radix-2 NTT (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  - icon: ':heavy_check_mark:'
    path: modint/montgomery_modint.hpp
    title: Montgomery ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/convolution_mod
    links:
    - https://judge.yosupo.jp/problem/convolution_mod
  bundledCode: "#line 1 \"remote_test/yosupo/math/convolution_mod.2.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#line 1 \"math/czt.hpp\"\
    \n\n\n\n#line 1 \"common.hpp\"\n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace\
    \ lib {\n#define LIB_END }\n#define LIB ::lib::\n\n\n#line 1 \"math/radix2_ntt.hpp\"\
    \n\n\n\n#line 5 \"math/radix2_ntt.hpp\"\n\n#include <algorithm>\n#include <array>\n\
    #include <cassert>\n#include <type_traits>\n#include <vector>\n\nLIB_BEGIN\n\n\
    namespace detail {\n\ntemplate <typename IntT>\nconstexpr std::enable_if_t<std::is_integral_v<IntT>,\
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
    \n\n#line 6 \"math/czt.hpp\"\n\n#line 9 \"math/czt.hpp\"\n#include <numeric>\n\
    #line 11 \"math/czt.hpp\"\n\nLIB_BEGIN\n\n// Chirp Z-transform\n// Input:  A(x)\
    \ = `a[0]` + `a[1]`x + ..., constant `c`, and integer `n`.\n// Output: [A(1),\
    \ A(c), A(c^2), ..., A(c^(n - 1))].\ntemplate <typename ModIntT>\nstd::vector<ModIntT>\
    \ czt(const std::vector<ModIntT> &a, const ModIntT &c, int n) {\n  assert(n >=\
    \ 0);\n  if (n == 0) return {};\n  int m = static_cast<int>(a.size());\n  while\
    \ (m > 0 && a[m - 1].is_zero()) --m;\n  if (m == 0) return std::vector<ModIntT>(n);\n\
    \  if (c.is_zero()) {\n    std::vector<ModIntT> res(n, a.front());\n    res.front()\
    \ = std::accumulate(a.begin(), a.begin() + m, ModIntT());\n    return res;\n \
    \ }\n  const int sz = n + m - 1, len = ntt_len(sz), nm_max = std::max(n, m);\n\
    \  std::vector<ModIntT> a_cpy(len), c_binom{1, 1}, ic_binom{1, 1};\n  c_binom.resize(len);\n\
    \  ic_binom.resize(nm_max);\n  {\n    const ModIntT ic(c.inv());\n    ModIntT\
    \ c_temp(1), ic_temp(1);\n    for (int i = 2; i < sz; ++i) c_binom[i] = c_binom[i\
    \ - 1] * (c_temp *= c);\n    for (int i = 2; i < nm_max; ++i) ic_binom[i] = ic_binom[i\
    \ - 1] * (ic_temp *= ic);\n  }\n  for (int i = 0; i != m; ++i) a_cpy[m - 1 - i]\
    \ = a[i] * ic_binom[i];\n  dft(a_cpy), dft(c_binom);\n  for (int i = 0; i != len;\
    \ ++i) a_cpy[i] *= c_binom[i];\n  idft(a_cpy);\n  a_cpy.erase(a_cpy.begin(), a_cpy.begin()\
    \ + m - 1);\n  a_cpy.resize(n);\n  for (int i = 0; i != n; ++i) a_cpy[i] *= ic_binom[i];\n\
    \  return a_cpy;\n}\n\nLIB_END\n\n\n#line 1 \"modint/montgomery_modint.hpp\"\n\
    \n\n\n#line 5 \"modint/montgomery_modint.hpp\"\n\n#ifdef LIB_DEBUG\n  #include\
    \ <stdexcept>\n#endif\n#include <cstdint>\n#include <iostream>\n#line 12 \"modint/montgomery_modint.hpp\"\
    \n\nLIB_BEGIN\n\ntemplate <std::uint32_t ModT>\nclass montgomery_modint30 {\n\
    \  using i32 = std::int32_t;\n  using u32 = std::uint32_t;\n  using u64 = std::uint64_t;\n\
    \n  u32 v_{};\n\n  static constexpr u32 get_r() {\n    u32 t = 2, iv = MOD * (t\
    \ - MOD * MOD);\n    iv *= t - MOD * iv, iv *= t - MOD * iv;\n    return iv *\
    \ (MOD * iv - t);\n  }\n  static constexpr u32 redc(u64 x) {\n    return (x +\
    \ static_cast<u64>(static_cast<u32>(x) * R) * MOD) >> 32;\n  }\n  static constexpr\
    \ u32 norm(u32 x) { return x - (MOD & -((MOD - 1 - x) >> 31)); }\n\n  static constexpr\
    \ u32 MOD  = ModT;\n  static constexpr u32 MOD2 = MOD << 1;\n  static constexpr\
    \ u32 R    = get_r();\n  static constexpr u32 R2   = -static_cast<u64>(MOD) %\
    \ MOD;\n  static constexpr i32 SMOD = static_cast<i32>(MOD);\n\n  static_assert(MOD\
    \ & 1);\n  static_assert(-R * MOD == 1);\n  static_assert((MOD >> 30) == 0);\n\
    \  static_assert(MOD != 1);\n\npublic:\n  static constexpr u32 mod() { return\
    \ MOD; }\n  static constexpr i32 smod() { return SMOD; }\n  constexpr montgomery_modint30()\
    \ {}\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>, int>\
    \ = 0>\n  constexpr montgomery_modint30(IntT v) : v_(redc(static_cast<u64>(v %\
    \ SMOD + SMOD) * R2)) {}\n  constexpr u32 val() const { return norm(redc(v_));\
    \ }\n  constexpr i32 sval() const { return norm(redc(v_)); }\n  constexpr bool\
    \ is_zero() const { return v_ == 0 || v_ == MOD; }\n  template <typename IntT,\
    \ std::enable_if_t<std::is_integral_v<IntT>, int> = 0>\n  explicit constexpr operator\
    \ IntT() const {\n    return static_cast<IntT>(val());\n  }\n  constexpr montgomery_modint30\
    \ operator-() const {\n    montgomery_modint30 res;\n    res.v_ = (MOD2 & -(v_\
    \ != 0)) - v_;\n    return res;\n  }\n  constexpr montgomery_modint30 inv() const\
    \ {\n    i32 x1 = 1, x3 = 0, a = sval(), b = SMOD;\n    while (b != 0) {\n   \
    \   i32 q = a / b, x1_old = x1, a_old = a;\n      x1 = x3, x3 = x1_old - x3 *\
    \ q, a = b, b = a_old - b * q;\n    }\n#ifdef LIB_DEBUG\n    if (a != 1) throw\
    \ std::runtime_error(\"modular inverse error\");\n#endif\n    return montgomery_modint30(x1);\n\
    \  }\n  constexpr montgomery_modint30 &operator+=(const montgomery_modint30 &rhs)\
    \ {\n    v_ += rhs.v_ - MOD2, v_ += MOD2 & -(v_ >> 31);\n    return *this;\n \
    \ }\n  constexpr montgomery_modint30 &operator-=(const montgomery_modint30 &rhs)\
    \ {\n    v_ -= rhs.v_, v_ += MOD2 & -(v_ >> 31);\n    return *this;\n  }\n  constexpr\
    \ montgomery_modint30 &operator*=(const montgomery_modint30 &rhs) {\n    v_ =\
    \ redc(static_cast<u64>(v_) * rhs.v_);\n    return *this;\n  }\n  constexpr montgomery_modint30\
    \ &operator/=(const montgomery_modint30 &rhs) {\n    return operator*=(rhs.inv());\n\
    \  }\n  constexpr montgomery_modint30 pow(u64 e) const {\n    for (montgomery_modint30\
    \ res(1), x(*this);; x *= x) {\n      if (e & 1) res *= x;\n      if ((e >>= 1)\
    \ == 0) return res;\n    }\n  }\n  constexpr void swap(montgomery_modint30 &rhs)\
    \ {\n    auto v = v_;\n    v_ = rhs.v_, rhs.v_ = v;\n  }\n  friend constexpr montgomery_modint30\
    \ operator+(const montgomery_modint30 &lhs,\n                                \
    \                 const montgomery_modint30 &rhs) {\n    return montgomery_modint30(lhs)\
    \ += rhs;\n  }\n  friend constexpr montgomery_modint30 operator-(const montgomery_modint30\
    \ &lhs,\n                                                 const montgomery_modint30\
    \ &rhs) {\n    return montgomery_modint30(lhs) -= rhs;\n  }\n  friend constexpr\
    \ montgomery_modint30 operator*(const montgomery_modint30 &lhs,\n            \
    \                                     const montgomery_modint30 &rhs) {\n    return\
    \ montgomery_modint30(lhs) *= rhs;\n  }\n  friend constexpr montgomery_modint30\
    \ operator/(const montgomery_modint30 &lhs,\n                                \
    \                 const montgomery_modint30 &rhs) {\n    return montgomery_modint30(lhs)\
    \ /= rhs;\n  }\n  friend constexpr bool operator==(const montgomery_modint30 &lhs,\
    \ const montgomery_modint30 &rhs) {\n    return norm(lhs.v_) == norm(rhs.v_);\n\
    \  }\n  friend constexpr bool operator!=(const montgomery_modint30 &lhs, const\
    \ montgomery_modint30 &rhs) {\n    return norm(lhs.v_) != norm(rhs.v_);\n  }\n\
    \  friend std::istream &operator>>(std::istream &is, montgomery_modint30 &rhs)\
    \ {\n    i32 x;\n    is >> x;\n    rhs = montgomery_modint30(x);\n    return is;\n\
    \  }\n  friend std::ostream &operator<<(std::ostream &os, const montgomery_modint30\
    \ &rhs) {\n    return os << rhs.val();\n  }\n};\n\ntemplate <std::uint32_t ModT>\n\
    using mm30 = montgomery_modint30<ModT>;\n\nLIB_END\n\n\n#line 6 \"remote_test/yosupo/math/convolution_mod.2.test.cpp\"\
    \n\n#line 9 \"remote_test/yosupo/math/convolution_mod.2.test.cpp\"\n#include <iterator>\n\
    #line 11 \"remote_test/yosupo/math/convolution_mod.2.test.cpp\"\n\nint main()\
    \ {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\"\
    , \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  int n, m;\n  std::cin >> n >> m;\n  using mint = lib::mm30<998244353>;\n  std::vector<mint>\
    \ a, b;\n  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(a));\n\
    \  std::copy_n(std::istream_iterator<mint>(std::cin), m, std::back_inserter(b));\n\
    \  int len = lib::ntt_len(n + m - 1);\n  const mint PR(3), c(PR.pow((mint::mod()\
    \ - 1) / len));\n  auto a_czt = lib::czt(a, c, len);\n  auto b_czt = lib::czt(b,\
    \ c, len);\n  for (int i = 0; i != len; ++i) a_czt[i] *= b_czt[i];\n  auto ab\
    \ = lib::czt(a_czt, c.inv(), len);\n  ab.resize(n + m - 1);\n  const mint iv(mint(len).inv());\n\
    \  for (auto &&i : ab) std::cout << i * iv << ' ';\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ \"math/czt.hpp\"\n#include \"math/radix2_ntt.hpp\"\n#include \"modint/montgomery_modint.hpp\"\
    \n\n#include <algorithm>\n#include <iostream>\n#include <iterator>\n#include <vector>\n\
    \nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  int n, m;\n  std::cin >> n >> m;\n  using mint = lib::mm30<998244353>;\n  std::vector<mint>\
    \ a, b;\n  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(a));\n\
    \  std::copy_n(std::istream_iterator<mint>(std::cin), m, std::back_inserter(b));\n\
    \  int len = lib::ntt_len(n + m - 1);\n  const mint PR(3), c(PR.pow((mint::mod()\
    \ - 1) / len));\n  auto a_czt = lib::czt(a, c, len);\n  auto b_czt = lib::czt(b,\
    \ c, len);\n  for (int i = 0; i != len; ++i) a_czt[i] *= b_czt[i];\n  auto ab\
    \ = lib::czt(a_czt, c.inv(), len);\n  ab.resize(n + m - 1);\n  const mint iv(mint(len).inv());\n\
    \  for (auto &&i : ab) std::cout << i * iv << ' ';\n  return 0;\n}"
  dependsOn:
  - math/czt.hpp
  - common.hpp
  - math/radix2_ntt.hpp
  - modint/montgomery_modint.hpp
  - common.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/convolution_mod.2.test.cpp
  requiredBy: []
  timestamp: '2022-05-04 19:31:16+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/convolution_mod.2.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/convolution_mod.2.test.cpp
- /verify/remote_test/yosupo/math/convolution_mod.2.test.cpp.html
title: remote_test/yosupo/math/convolution_mod.2.test.cpp
---
