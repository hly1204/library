---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':question:'
    path: math/radix2_ntt.hpp
    title: Radix-2 NTT (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  - icon: ':question:'
    path: math/relaxed_convolution.hpp
    title: Relaxed Convolution (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack \rbrack$
      for FFT prime $p$)
  - icon: ':question:'
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
  bundledCode: "#line 1 \"remote_test/yosupo/math/convolution_mod.3.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#line 1 \"math/relaxed_convolution.hpp\"\
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
    \n\n#line 6 \"math/relaxed_convolution.hpp\"\n\n#include <exception>\n#include\
    \ <functional>\n#line 10 \"math/relaxed_convolution.hpp\"\n#include <utility>\n\
    #line 12 \"math/relaxed_convolution.hpp\"\n\nLIB_BEGIN\n\n// This implementation\
    \ is NOT optimal and NOT lazy enough so IT IS SLOW.\ntemplate <typename ModIntT,\
    \ typename Fn0, typename Fn1>\nclass relaxed_convolution {                   \
    \    // O(n log^2 n) impl\n  std::vector<ModIntT> a_{}, b_{}, c_{};          //\
    \ `a_ * b_` = `c_`\n  std::vector<std::vector<ModIntT>> ac_{}, bc_{}; // cached\
    \ DFTs\n  Fn0 ha_;\n  Fn1 hb_;\n  int n_{}; // counter\n\n  enum : int { BASE_CASE_SIZE\
    \ = 32 };\n  static_assert((BASE_CASE_SIZE & (BASE_CASE_SIZE - 1)) == 0);\n\n\
    \  template <typename>\n  static constexpr bool relaxed_convolution_false = false;\n\
    \n  template <typename FnT>\n  ModIntT get_next_coeff(FnT &&f, std::vector<ModIntT>\
    \ &e) {\n    if constexpr (std::is_invocable_r_v<ModIntT, FnT, int, const std::vector<ModIntT>\
    \ &>) {\n      return e.emplace_back(f(n_, c_));\n    } else if constexpr (std::is_invocable_r_v<ModIntT,\
    \ FnT, int>) {\n      return e.emplace_back(f(n_));\n    } else if constexpr (std::is_invocable_r_v<ModIntT,\
    \ FnT>) {\n      return e.emplace_back(f());\n    } else {\n      static_assert(relaxed_convolution_false<FnT>);\n\
    \      return ModIntT();\n    }\n  }\n\npublic:\n  template <typename, typename\
    \ Closure0T, typename Closure1T>\n  friend auto make_relaxed_convolution(Closure0T\
    \ &&, Closure1T &&);\n  // `h0` multiplicand, `h1` multiplier\n  template <typename\
    \ Closure0T, typename Closure1T>\n  relaxed_convolution(Closure0T &&h0, Closure1T\
    \ &&h1)\n      : c_(4), ha_(std::forward<Closure0T>(h0)), hb_(std::forward<Closure1T>(h1))\
    \ {}\n  const std::vector<ModIntT> &get_multiplier() const { return b_; }\n  const\
    \ std::vector<ModIntT> &get_multiplicand() const { return a_; }\n  const std::vector<ModIntT>\
    \ &get_lhs() const { return get_multiplicand(); }\n  const std::vector<ModIntT>\
    \ &get_rhs() const { return get_multiplier(); }\n  relaxed_convolution &await(int\
    \ k) {\n    while (n_ < k) next();\n    return *this;\n  }\n  ModIntT at(int k)\
    \ {\n    while (n_ <= k) next();\n    return c_[k];\n  }\n  ModIntT operator[](int\
    \ k) { return at(k); }\n  ModIntT next() {\n    {\n      // enlarge space\n  \
    \    int len = ntt_len(n_ << 1 | 1);\n      if (static_cast<int>(c_.size()) <\
    \ len) c_.resize(len);\n    }\n\n    switch (n_) {\n    case 0: c_[0] = get_next_coeff(ha_,\
    \ a_) * get_next_coeff(hb_, b_); break;\n    case 1:\n      c_[1] = get_next_coeff(ha_,\
    \ a_) * b_.front() + a_.front() * get_next_coeff(hb_, b_);\n      c_[2] = a_[1]\
    \ * b_[1];\n      break;\n    case 2:\n      c_[2] += get_next_coeff(ha_, a_)\
    \ * b_.front() + a_.front() * get_next_coeff(hb_, b_);\n      c_[3] = a_[2] *\
    \ b_[1] + a_[1] * b_[2];\n      break;\n    default:\n      if ((n_ & (n_ - 1))\
    \ == 0) {\n        auto &&c0 = ac_.emplace_back(n_);\n        auto &&c1 = bc_.emplace_back(n_);\n\
    \        std::copy_n(a_.cbegin() + (n_ >> 1), n_ >> 1, c0.begin());\n        std::copy_n(b_.cbegin()\
    \ + (n_ >> 1), n_ >> 1, c1.begin());\n        dft(c0), dft(c1);\n        std::vector\
    \ c0_cpy(c0);\n        for (int i = 0; i != n_; ++i) c0_cpy[i] *= c1[i];\n   \
    \     idft(c0_cpy);\n        for (int i = 0; i != n_ - 1; ++i) c_[n_ + i] += c0_cpy[i];\n\
    \      }\n      c_[n_] += get_next_coeff(ha_, a_) * b_.front() + a_.front() *\
    \ get_next_coeff(hb_, b_);\n      c_[n_ + 1] += a_[1] * b_.back() + a_.back()\
    \ * b_[1];\n      for (int sft = 1, offset = ntt_len(n_ + 1) >> 1, t = n_ + 1\
    \ - offset;\n           (t & 1) == 0 && 1 << sft < offset; ++sft, t >>= 1)\n \
    \       if (1 << sft <= BASE_CASE_SIZE) {\n          for (int i = 0, m = n_ +\
    \ 1 - (1 << sft); i != 1 << sft; ++i)\n            for (int j = 0; j != 1 << sft;\
    \ ++j)\n              c_[n_ + 1 + i + j] += a_[m + i] * b_[j + (1 << sft)] + a_[j\
    \ + (1 << sft)] * b_[m + i];\n        } else {\n          std::vector<ModIntT>\
    \ c0(2 << sft), c1(2 << sft);\n          std::copy_n(a_.cbegin() + n_ + 1 - (1\
    \ << sft), 1 << sft, c0.begin());\n          std::copy_n(b_.cbegin() + n_ + 1\
    \ - (1 << sft), 1 << sft, c1.begin());\n          dft(c0), dft(c1);\n        \
    \  for (int i = 0; i != 2 << sft; ++i)\n            c0[i] = c0[i] * bc_[sft -\
    \ 1][i] + c1[i] * ac_[sft - 1][i];\n          idft(c0);\n          for (int i\
    \ = 0; i != (2 << sft) - 1; ++i) c_[n_ + 1 + i] += c0[i];\n        }\n    }\n\
    \    return c_[n_++];\n  }\n};\n\ntemplate <typename ModIntT, typename Closure0T,\
    \ typename Closure1T>\nauto make_relaxed_convolution(Closure0T &&f0, Closure1T\
    \ &&f1)\n    -> relaxed_convolution<ModIntT, std::decay_t<Closure0T>, std::decay_t<Closure1T>>\
    \ {\n  return relaxed_convolution<ModIntT, std::decay_t<Closure0T>, std::decay_t<Closure1T>>(f0,\
    \ f1);\n}\n\nLIB_END\n\n\n#line 1 \"modint/montgomery_modint.hpp\"\n\n\n\n#line\
    \ 5 \"modint/montgomery_modint.hpp\"\n\n#ifdef LIB_DEBUG\n  #include <stdexcept>\n\
    #endif\n#include <cstdint>\n#include <iostream>\n#line 12 \"modint/montgomery_modint.hpp\"\
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
    using mm30 = montgomery_modint30<ModT>;\n\nLIB_END\n\n\n#line 5 \"remote_test/yosupo/math/convolution_mod.3.test.cpp\"\
    \n\n#line 8 \"remote_test/yosupo/math/convolution_mod.3.test.cpp\"\n#include <iterator>\n\
    #line 10 \"remote_test/yosupo/math/convolution_mod.3.test.cpp\"\n\nint main()\
    \ {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"out\"\
    , \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  int n, m;\n  std::cin >> n >> m;\n  using mint = lib::mm30<998244353>;\n  std::vector<mint>\
    \ a, b;\n  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(a));\n\
    \  std::copy_n(std::istream_iterator<mint>(std::cin), m, std::back_inserter(b));\n\
    \  auto rc = lib::make_relaxed_convolution<mint>(\n      [&a](int n) { return\
    \ n < static_cast<int>(a.size()) ? a[n] : mint(); },\n      [&b](int n) { return\
    \ n < static_cast<int>(b.size()) ? b[n] : mint(); });\n  for (int i = 0; i !=\
    \ n + m - 1; ++i) std::cout << rc[i] << ' ';\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/convolution_mod\"\n\n#include\
    \ \"math/relaxed_convolution.hpp\"\n#include \"modint/montgomery_modint.hpp\"\n\
    \n#include <algorithm>\n#include <iostream>\n#include <iterator>\n#include <vector>\n\
    \nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  int n, m;\n  std::cin >> n >> m;\n  using mint = lib::mm30<998244353>;\n  std::vector<mint>\
    \ a, b;\n  std::copy_n(std::istream_iterator<mint>(std::cin), n, std::back_inserter(a));\n\
    \  std::copy_n(std::istream_iterator<mint>(std::cin), m, std::back_inserter(b));\n\
    \  auto rc = lib::make_relaxed_convolution<mint>(\n      [&a](int n) { return\
    \ n < static_cast<int>(a.size()) ? a[n] : mint(); },\n      [&b](int n) { return\
    \ n < static_cast<int>(b.size()) ? b[n] : mint(); });\n  for (int i = 0; i !=\
    \ n + m - 1; ++i) std::cout << rc[i] << ' ';\n  return 0;\n}\n"
  dependsOn:
  - math/relaxed_convolution.hpp
  - common.hpp
  - math/radix2_ntt.hpp
  - modint/montgomery_modint.hpp
  - common.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/convolution_mod.3.test.cpp
  requiredBy: []
  timestamp: '2023-12-17 11:51:45+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/convolution_mod.3.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/convolution_mod.3.test.cpp
- /verify/remote_test/yosupo/math/convolution_mod.3.test.cpp.html
title: remote_test/yosupo/math/convolution_mod.3.test.cpp
---
