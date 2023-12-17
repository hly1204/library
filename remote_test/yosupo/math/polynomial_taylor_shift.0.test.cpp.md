---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':x:'
    path: math/binomial.hpp
    title: Binomial Coefficient (in $\mathbb{F} _ p$)
  - icon: ':question:'
    path: math/extended_gcd.hpp
    title: Extended Euclidean Algorithm (in $\mathbb{Z}$)
  - icon: ':question:'
    path: math/polynomial.hpp
    title: Polynomial (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  - icon: ':question:'
    path: math/radix2_ntt.hpp
    title: Radix-2 NTT (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  - icon: ':question:'
    path: math/random.hpp
    title: Pseudo Random Number Generator
  - icon: ':question:'
    path: math/semi_relaxed_convolution.hpp
    title: Semi-Relaxed Convolution (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT
      prime $p$)
  - icon: ':question:'
    path: math/sqrt_mod.hpp
    title: Square Roots (in $\mathbb{F} _ p$)
  - icon: ':x:'
    path: math/taylor_shift.hpp
    title: Polynomial Taylor Shift (in $\mathbb{F} _ p$ for FFT prime $p$)
  - icon: ':question:'
    path: math/truncated_formal_power_series.hpp
    title: Truncated Formal Power Series (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack
      \rbrack$ for FFT prime $p$)
  - icon: ':question:'
    path: math/truncated_fourier_transform.hpp
    title: Truncated Fourier Transform (in $\mathbb{F} _ p \lbrack z \rbrack$ for
      FFT prime $p$)
  - icon: ':question:'
    path: modint/montgomery_modint.hpp
    title: Montgomery ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/polynomial_taylor_shift
    links:
    - https://judge.yosupo.jp/problem/polynomial_taylor_shift
  bundledCode: "#line 1 \"remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/polynomial_taylor_shift\"\n\
    \n#line 1 \"math/polynomial.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\n\n#define\
    \ LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n#define LIB\
    \ ::lib::\n\n\n#line 1 \"math/truncated_formal_power_series.hpp\"\n\n\n\n#line\
    \ 1 \"math/extended_gcd.hpp\"\n\n\n\n#line 5 \"math/extended_gcd.hpp\"\n\n#include\
    \ <tuple>\n#include <utility>\n#include <vector>\n\nLIB_BEGIN\n\n// Input:  integer\
    \ `a` and `b`.\n// Output: (x, y, z) such that `a`x + `b`y = z = gcd(`a`, `b`).\n\
    [[deprecated]] std::tuple<long long, long long, long long> ext_gcd(long long a,\
    \ long long b) {\n  long long x11 = 1, x12 = 0, x21 = 0, x22 = 1;\n  while (b\
    \ != 0) {\n    long long q = a / b, x11_cpy = x11, x12_cpy = x12, a_cpy = a;\n\
    \    x11 = x21, x21 = x11_cpy - q * x21;\n    x12 = x22, x22 = x12_cpy - q * x22;\n\
    \    a = b, b = a_cpy - q * b;\n  }\n  return std::make_tuple(x11, x12, a);\n\
    }\n\n// Input:  integer `a` and `b`.\n// Output: (x, gcd(`a`, `b`)) such that\
    \ `a`x \u2261 gcd(`a`, `b`) (mod `b`).\nstd::pair<long long, long long> inv_gcd(long\
    \ long a, long long b) {\n  long long x11 = 1, x21 = 0;\n  while (b != 0) {\n\
    \    long long q = a / b, x11_cpy = x11, a_cpy = a;\n    x11 = x21, x21 = x11_cpy\
    \ - q * x21;\n    a = b, b = a_cpy - q * b;\n  }\n  return std::make_pair(x11,\
    \ a);\n}\n\nnamespace detail {\n\ntemplate <typename ModIntT>\nclass modular_inverse\
    \ {\n  std::vector<ModIntT> ivs{ModIntT()};\n\n  enum : int { LIM = 1 << 20 };\n\
    \npublic:\n  modular_inverse() {}\n  ModIntT operator()(int k) {\n    // assume\
    \ `ModIntT::mod()` is prime.\n    if (k > LIM) return ModIntT(k).inv();\n    //\
    \ preprocess modular inverse from 1 to `k`\n    if (int n = static_cast<int>(ivs.size());\
    \ n <= k) {\n      int nn = n;\n      while (nn <= k) nn <<= 1;\n      ivs.resize(nn);\n\
    \      ModIntT v(1);\n      for (int i = n; i != nn; ++i) ivs[i] = v, v *= ModIntT(i);\n\
    \      v = v.inv();\n      for (int i = nn - 1; i >= n; --i) ivs[i] *= v, v *=\
    \ ModIntT(i);\n    }\n    return ivs[k];\n  }\n};\n\n} // namespace detail\n\n\
    LIB_END\n\n\n#line 1 \"math/semi_relaxed_convolution.hpp\"\n\n\n\n#line 1 \"math/radix2_ntt.hpp\"\
    \n\n\n\n#line 5 \"math/radix2_ntt.hpp\"\n\n#include <algorithm>\n#include <array>\n\
    #include <cassert>\n#include <type_traits>\n#line 11 \"math/radix2_ntt.hpp\"\n\
    \nLIB_BEGIN\n\nnamespace detail {\n\ntemplate <typename IntT>\nconstexpr std::enable_if_t<std::is_integral_v<IntT>,\
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
    \n\n#line 6 \"math/semi_relaxed_convolution.hpp\"\n\n#line 11 \"math/semi_relaxed_convolution.hpp\"\
    \n\nLIB_BEGIN\n\ntemplate <typename ModIntT, typename FnT>\nclass semi_relaxed_convolution\
    \ {\n  std::vector<ModIntT> fixed_A_{}, B_{}, c_{};\n  std::vector<std::vector<std::vector<ModIntT>>>\
    \ dft_A_cache_{}, dft_B_cache_{};\n  int n_{};\n  FnT handle_;\n\n  enum : int\
    \ { BASE_CASE_SIZE = 32, LOG_BLOCK = 4, BLOCK = 1 << LOG_BLOCK, MASK = BLOCK -\
    \ 1 };\n\n  static_assert((BASE_CASE_SIZE & (BASE_CASE_SIZE - 1)) == 0);\n\n \
    \ template <typename>\n  static constexpr bool semi_relaxed_convolution_false\
    \ = false;\n\npublic:\n  template <typename ClosureT>\n  semi_relaxed_convolution(const\
    \ std::vector<ModIntT> &A, ClosureT &&handle)\n      : fixed_A_(A), c_(1024),\
    \ handle_(std::forward<ClosureT>(handle)) {}\n  const std::vector<ModIntT> &get_multiplier()\
    \ const { return B_; }\n  const std::vector<ModIntT> &get_multiplicand() const\
    \ { return fixed_A_; }\n  const std::vector<ModIntT> &get_lhs() const { return\
    \ get_multiplicand(); }\n  const std::vector<ModIntT> &get_rhs() const { return\
    \ get_multiplier(); }\n  semi_relaxed_convolution &await(int k) {\n    while (n_\
    \ < k) next();\n    return *this;\n  }\n  ModIntT at(int k) {\n    while (n_ <=\
    \ k) next();\n    return c_[k];\n  }\n  ModIntT operator[](int k) { return at(k);\
    \ }\n  ModIntT next() {\n    {\n      // enlarge space\n      const int len =\
    \ ntt_len(n_ << 1 | 1);\n      if (static_cast<int>(c_.size()) < len) c_.resize(len);\n\
    \      if (static_cast<int>(fixed_A_.size()) < len) fixed_A_.resize(len);\n  \
    \  }\n    if ((n_ & (BASE_CASE_SIZE - 1)) == 0)\n      for (int t = n_ / BASE_CASE_SIZE,\
    \ block_size = BASE_CASE_SIZE, lv = 0; t != 0;\n           t >>= LOG_BLOCK, block_size\
    \ <<= LOG_BLOCK, ++lv)\n        if (int i = t & MASK, block_size2 = block_size\
    \ << 1, l = n_ - block_size; i != 0) {\n          if (block_size * i == n_) {\n\
    \            if (static_cast<int>(dft_A_cache_.size()) == lv) {\n            \
    \  dft_A_cache_.emplace_back();\n              dft_B_cache_.emplace_back(BLOCK\
    \ - 1);\n            }\n            dft(dft_A_cache_[lv].emplace_back(fixed_A_.cbegin()\
    \ + (i - 1) * block_size,\n                                              fixed_A_.cbegin()\
    \ + (i + 1) * block_size));\n          }\n          auto &&B_cache = dft_B_cache_[lv];\n\
    \          B_cache[i - 1].resize(block_size2);\n          std::fill_n(std::copy_n(B_.cbegin()\
    \ + l, block_size, B_cache[i - 1].begin()), block_size,\n                    \
    \  ModIntT());\n          dft(B_cache[i - 1]);\n          std::vector<ModIntT>\
    \ temp_sum(block_size2);\n          for (int j = 0; j != i; ++j)\n           \
    \ for (int k = 0; k != block_size2; ++k)\n              temp_sum[k] += dft_A_cache_[lv][i\
    \ - 1 - j][k] * B_cache[j][k];\n          idft(temp_sum);\n          for (int\
    \ j = block_size; j != block_size2; ++j) c_[j + n_ - block_size] += temp_sum[j];\n\
    \          break;\n        }\n    for (int i = 0, l = n_ & ~(BASE_CASE_SIZE -\
    \ 1); i < n_ - l; ++i)\n      c_[n_] += fixed_A_[n_ - l - i] * B_[l + i];\n  \
    \  if constexpr (std::is_invocable_r_v<ModIntT, FnT, int, const std::vector<ModIntT>\
    \ &>) {\n      c_[n_] += fixed_A_.front() * B_.emplace_back(handle_(n_, c_));\n\
    \    } else if constexpr (std::is_invocable_r_v<ModIntT, FnT, int>) {\n      c_[n_]\
    \ += fixed_A_.front() * B_.emplace_back(handle_(n_));\n    } else {\n      static_assert(semi_relaxed_convolution_false<FnT>);\n\
    \    }\n    return c_[n_++];\n  }\n};\n\ntemplate <typename VectorT, typename\
    \ ClosureT>\nsemi_relaxed_convolution(VectorT, ClosureT)\n    -> semi_relaxed_convolution<typename\
    \ VectorT::value_type, std::decay_t<ClosureT>>;\n\nLIB_END\n\n\n#line 1 \"math/sqrt_mod.hpp\"\
    \n\n\n\n#line 1 \"math/random.hpp\"\n\n\n\n#line 5 \"math/random.hpp\"\n\n#include\
    \ <cstdint>\n#include <limits>\n\nLIB_BEGIN\n\n// see https://prng.di.unimi.it/xoshiro256starstar.c\n\
    // original license CC0 1.0\nclass xoshiro256starstar {\n  using u64 = std::uint64_t;\n\
    \n  static inline u64 rotl(const u64 x, int k) { return (x << k) | (x >> (64 -\
    \ k)); }\n\n  u64 s_[4];\n\n  u64 next() {\n    const u64 res = rotl(s_[1] * 5,\
    \ 7) * 9;\n    const u64 t   = s_[1] << 17;\n    s_[2] ^= s_[0];\n    s_[3] ^=\
    \ s_[1];\n    s_[1] ^= s_[2];\n    s_[0] ^= s_[3];\n    s_[2] ^= t;\n    s_[3]\
    \ = rotl(s_[3], 45);\n    return res;\n  }\n\npublic:\n  // see https://prng.di.unimi.it/splitmix64.c\n\
    \  // original license CC0 1.0\n  explicit xoshiro256starstar(u64 seed) {\n  \
    \  for (int i = 0; i != 4; ++i) {\n      u64 z = (seed += 0x9e3779b97f4a7c15);\n\
    \      z     = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n      z     = (z ^ (z >>\
    \ 27)) * 0x94d049bb133111eb;\n      s_[i] = z ^ (z >> 31);\n    }\n  }\n  // see\
    \ https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator\n  using\
    \ result_type = u64;\n  static constexpr u64 min() { return std::numeric_limits<u64>::min();\
    \ }\n  static constexpr u64 max() { return std::numeric_limits<u64>::max(); }\n\
    \  u64 operator()() { return next(); }\n};\n\nLIB_END\n\n\n#line 6 \"math/sqrt_mod.hpp\"\
    \n\n#include <random>\n#line 10 \"math/sqrt_mod.hpp\"\n\nLIB_BEGIN\n\ntemplate\
    \ <typename ModIntT>\nstd::vector<ModIntT> sqrt_mod_prime(ModIntT a) {\n  // Bostan--Mori's\
    \ algorithm\n  const auto p = ModIntT::mod();\n  if (p == 2 || a.is_zero()) return\
    \ {a};\n  if (a.pow(p >> 1) == -1) return {};\n  if ((p & 3) == 3) {\n    ModIntT\
    \ b(a.pow((p + 1) >> 2));\n    return {b, -b};\n  }\n  xoshiro256starstar gen(std::random_device{}());\n\
    \  std::uniform_int_distribution<std::decay_t<decltype(p)>> dis(2, p - 1);\n \
    \ ModIntT t;\n  do { t = dis(gen); } while ((t * t - 4 * a).pow(p >> 1) != -1);\n\
    \  ModIntT k0(1), k1, k2(-t), k3(a);\n  for (auto e = (p + 1) >> 1;;) {\n    //\
    \ clang-format off\n    if (e & 1) k0 = k1 - k0 * k2, k1 *= k3;\n    else k1 =\
    \ k0 * k3 - k1 * k2;\n    // clang-format on\n    if ((e >>= 1) == 0) return {k0,\
    \ -k0};\n    k2 = k3 + k3 - k2 * k2, k3 *= k3;\n  }\n}\n\nLIB_END\n\n\n#line 1\
    \ \"math/truncated_fourier_transform.hpp\"\n\n\n\n#line 6 \"math/truncated_fourier_transform.hpp\"\
    \n\n#line 10 \"math/truncated_fourier_transform.hpp\"\n\nLIB_BEGIN\n\ntemplate\
    \ <typename ContainerT>\nvoid tft(ContainerT &&a) {\n  using Container       \
    \   = std::decay_t<ContainerT>;\n  using T                  = typename Container::value_type;\n\
    \  static constexpr auto rt = detail::root<T>();\n  static std::vector<T> root(1);\n\
    \  const int n = static_cast<int>(a.size());\n  if ((n & (n - 1)) == 0) return\
    \ dft(std::forward<ContainerT>(a));\n  const int len = ntt_len(n);\n  if (int\
    \ s = static_cast<int>(root.size()); s << 1 < len) {\n    root.resize(len >> 1);\n\
    \    for (int i = detail::bsf(s), j; 1 << i < len >> 1; ++i) {\n      root[j =\
    \ 1 << i] = rt[i];\n      for (int k = j + 1; k < j << 1; ++k) root[k] = root[k\
    \ - j] * root[j];\n    }\n  }\n  a.resize(len);\n  for (int j = 0, l = len >>\
    \ 1; j != l; ++j) {\n    T u(a[j]), v(a[j + l]);\n    a[j] = u + v, a[j + l] =\
    \ u - v;\n  }\n  for (int i = len >> 1; i >= 2; i >>= 1) {\n    for (int j = 0,\
    \ l = i >> 1; j != l; ++j) {\n      T u(a[j]), v(a[j + l]);\n      a[j] = u +\
    \ v, a[j + l] = u - v;\n    }\n    for (int j = i, l = i >> 1, m = 1; j < n &&\
    \ j != len; j += i, ++m)\n      for (int k = j; k != j + l; ++k) {\n        T\
    \ u(a[k]), v(a[k + l] * root[m]);\n        a[k] = u + v, a[k + l] = u - v;\n \
    \     }\n  }\n  a.resize(n);\n}\n\ntemplate <typename ContainerT>\nvoid itft(ContainerT\
    \ &&a) {\n  using Container           = std::decay_t<ContainerT>;\n  using T \
    \                  = typename Container::value_type;\n  static constexpr auto\
    \ rt  = detail::root<T>();\n  static constexpr auto irt = detail::iroot<T>();\n\
    \  static std::vector<T> root{T(1)}, iroot{T(1)};\n  const int n = static_cast<int>(a.size());\n\
    \  if ((n & (n - 1)) == 0) return idft(std::forward<ContainerT>(a));\n  const\
    \ int len = ntt_len(n);\n  if (int s = static_cast<int>(root.size()); s << 1 <\
    \ len) {\n    root.resize(len >> 1);\n    iroot.resize(len >> 1);\n    for (int\
    \ i = detail::bsf(s), j; 1 << i < len >> 1; ++i) {\n      root[j = 1 << i] = rt[i],\
    \ iroot[j] = irt[i];\n      for (int k = j + 1; k < j << 1; ++k)\n        root[k]\
    \ = root[k - j] * root[j], iroot[k] = iroot[k - j] * iroot[j];\n    }\n  }\n \
    \ a.resize(len);\n  struct itft_rec {\n    itft_rec(Container &a) : a_(a), i2_(T(2).inv())\
    \ {}\n    // [`head`, `tail`), [`tail`, `last`)\n    void run(int head, int tail,\
    \ int last) {\n      if (head >= tail) return;\n      if (int mid = (last - head)\
    \ / 2 + head, len = mid - head; mid <= tail) {\n        // pull up [`head`, `mid`)\n\
    \        T i2p(1);\n        for (int i = 1; i != len; i <<= 1, i2p *= i2_)\n \
    \         for (int j = head, m = head / (i << 1); j != mid; j += i << 1, ++m)\n\
    \            for (int k = j; k != j + i; ++k) {\n              T u(a_[k]), v(a_[k\
    \ + i]);\n              a_[k] = u + v, a_[k + i] = (u - v) * iroot[m];\n     \
    \       }\n        for (int i = head; i != mid; ++i) a_[i] *= i2p;\n        //\
    \ push down [`tail`, `last`)\n        T r(root[head / (len << 1)] * 2);\n    \
    \    for (int i = tail; i != last; ++i) a_[i] = a_[i - len] - a_[i] * r;\n   \
    \     run(mid, tail, last);\n        // pull up [`head`, `last`)\n        r =\
    \ iroot[head / (len << 1)] * i2_;\n        for (int i = head; i != mid; ++i) {\n\
    \          T u(a_[i]), v(a_[i + len]);\n          a_[i] = (u + v) * i2_, a_[i\
    \ + len] = (u - v) * r;\n        }\n      } else {\n        T r(root[head / (len\
    \ << 1)]);\n        // push down [`tail`, `mid`)\n        for (int i = tail; i\
    \ != mid; ++i) a_[i] += a_[i + len] * r;\n        run(head, tail, mid);\n    \
    \    // pull up [`head`, `mid`)\n        for (int i = head; i != mid; ++i) a_[i]\
    \ -= a_[i + len] * r;\n      }\n    }\n    Container &a_;\n    const T i2_;\n\
    \  } rec(a);\n  rec.run(0, n, len);\n  a.resize(n);\n}\n\nLIB_END\n\n\n#line 9\
    \ \"math/truncated_formal_power_series.hpp\"\n\n#line 12 \"math/truncated_formal_power_series.hpp\"\
    \n#include <iostream>\n#include <iterator>\n#include <optional>\n#line 18 \"math/truncated_formal_power_series.hpp\"\
    \n\nLIB_BEGIN\n\ntemplate <typename ModIntT>\nclass truncated_formal_power_series\
    \ : public std::vector<ModIntT> {\n  using MyBase = std::vector<ModIntT>;\n  static_assert(std::is_same_v<typename\
    \ MyBase::value_type, ModIntT>);\n  static typename detail::modular_inverse<ModIntT>\
    \ invs;\n\npublic:\n  using std::vector<ModIntT>::vector;\n\n  truncated_formal_power_series(const\
    \ std::vector<ModIntT> &v) : std::vector<ModIntT>(v) {}\n  truncated_formal_power_series(std::vector<ModIntT>\
    \ &&v) : std::vector<ModIntT>(std::move(v)) {}\n\n  enum : int { NEGATIVE_INFINITY\
    \ = -1 };\n\n  // leading coefficient\n  ModIntT lc() const {\n    int d = deg();\n\
    \    return d == NEGATIVE_INFINITY ? ModIntT() : this->operator[](d);\n  }\n \
    \ // degree\n  int deg() const {\n    // treat formal power series like polynomials\n\
    \    int n = static_cast<int>(this->size()) - 1;\n    while (n >= 0 && this->operator[](n).is_zero())\
    \ --n;\n    return n == -1 ? NEGATIVE_INFINITY : n;\n  }\n  // order\n  int ord()\
    \ const {\n    int d = deg();\n    if (d == NEGATIVE_INFINITY) return NEGATIVE_INFINITY;\n\
    \    for (int i = 0;; ++i)\n      if (!this->operator[](i).is_zero()) return i;\n\
    \  }\n  bool is_zero() const { return deg() == NEGATIVE_INFINITY; }\n  void shrink()\
    \ { this->resize(deg() + 1); }\n  truncated_formal_power_series operator-() const\
    \ {\n    truncated_formal_power_series res(*this);\n    for (auto &&i : res) i\
    \ = -i;\n    return res;\n  }\n\n  truncated_formal_power_series &operator+=(const\
    \ truncated_formal_power_series &rhs) {\n    if (this->size() < rhs.size()) this->resize(rhs.size());\n\
    \    for (int i = 0, e = static_cast<int>(rhs.size()); i != e; ++i) this->operator[](i)\
    \ += rhs[i];\n    return *this;\n  }\n  truncated_formal_power_series &operator-=(const\
    \ truncated_formal_power_series &rhs) {\n    if (this->size() < rhs.size()) this->resize(rhs.size());\n\
    \    for (int i = 0, e = static_cast<int>(rhs.size()); i != e; ++i) this->operator[](i)\
    \ -= rhs[i];\n    return *this;\n  }\n  truncated_formal_power_series &operator*=(const\
    \ truncated_formal_power_series &rhs);\n  truncated_formal_power_series integr(ModIntT\
    \ c = ModIntT()) const {\n    const int n = static_cast<int>(this->size()) + 1;\n\
    \    truncated_formal_power_series res(n);\n    res.front() = c;\n    for (int\
    \ i = 1; i < n; ++i) res[i] = this->operator[](i - 1) * invs(i);\n    return res;\n\
    \  }\n  truncated_formal_power_series deriv() const {\n    const int n = static_cast<int>(this->size())\
    \ - 1;\n    if (n <= 0) return truncated_formal_power_series{};\n    truncated_formal_power_series\
    \ res(n);\n    for (int i = 1; i <= n; ++i) res[i - 1] = this->operator[](i) *\
    \ i;\n    return res;\n  }\n  truncated_formal_power_series inv(int n) const;\n\
    \  truncated_formal_power_series log(int n) const { return deriv().div(*this,\
    \ n - 1).integr(); }\n  truncated_formal_power_series exp(int n) const;\n  truncated_formal_power_series\
    \ div(const truncated_formal_power_series &rhs, int n) const;\n  truncated_formal_power_series\
    \ pow(int n, long long e) const;\n  std::optional<truncated_formal_power_series>\
    \ sqrt_hint(int n, ModIntT c) const;\n  std::optional<truncated_formal_power_series>\
    \ sqrt(int n) const;\n\n  friend truncated_formal_power_series operator+(const\
    \ truncated_formal_power_series &lhs,\n                                      \
    \           const truncated_formal_power_series &rhs) {\n    return truncated_formal_power_series(lhs)\
    \ += rhs;\n  }\n  friend truncated_formal_power_series operator-(const truncated_formal_power_series\
    \ &lhs,\n                                                 const truncated_formal_power_series\
    \ &rhs) {\n    return truncated_formal_power_series(lhs) -= rhs;\n  }\n  friend\
    \ truncated_formal_power_series operator*(const truncated_formal_power_series\
    \ &lhs,\n                                                 const truncated_formal_power_series\
    \ &rhs) {\n    return truncated_formal_power_series(lhs) *= rhs;\n  }\n\n  friend\
    \ std::istream &operator>>(std::istream &lhs, truncated_formal_power_series &rhs)\
    \ {\n    for (auto &&i : rhs) lhs >> i;\n    return lhs;\n  }\n  friend std::ostream\
    \ &operator<<(std::ostream &lhs, const truncated_formal_power_series &rhs) {\n\
    \    int s = 0, e = static_cast<int>(rhs.size());\n    lhs << '[';\n    for (auto\
    \ &&i : rhs) {\n      lhs << i;\n      if (s >= 1) lhs << 'x';\n      // clang-format\
    \ off\n      if (s > 9) lhs << \"^(\" << s << ')';\n      else if (s > 1) lhs\
    \ << '^' << s;\n      // clang-format on\n      if (++s != e) lhs << \" + \";\n\
    \    }\n    return lhs << ']';\n  }\n};\n\ntemplate <typename IterT>\ntruncated_formal_power_series(IterT,\
    \ IterT)\n    -> truncated_formal_power_series<typename std::iterator_traits<IterT>::value_type>;\n\
    \ntemplate <typename ModIntT>\ntypename detail::modular_inverse<ModIntT> truncated_formal_power_series<ModIntT>::invs;\n\
    \ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT> &\ntruncated_formal_power_series<ModIntT>::operator*=(const\
    \ truncated_formal_power_series &rhs) {\n  // 6E\n  int n = static_cast<int>(this->size()),\
    \ m = static_cast<int>(rhs.size());\n  if (n == 0 || m == 0) {\n    this->clear();\n\
    \    return *this;\n  }\n  if (std::min(n, m) <= 32) {\n    truncated_formal_power_series\
    \ res(n + m - 1);\n    for (int i = 0; i != n; ++i)\n      for (int j = 0; j !=\
    \ m; ++j) res[i + j] += this->operator[](i) * rhs[j];\n    return this->operator=(res);\n\
    \  }\n  int len = n + m - 1;\n  truncated_formal_power_series rhs_cpy(len);\n\
    \  std::copy_n(rhs.cbegin(), m, rhs_cpy.begin());\n  this->resize(len);\n  tft(*this),\
    \ tft(rhs_cpy);\n  for (int i = 0; i != len; ++i) this->operator[](i) *= rhs_cpy[i];\n\
    \  itft(*this);\n  return *this;\n}\n\ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT>\
    \ truncated_formal_power_series<ModIntT>::inv(int n) const {\n  return semi_relaxed_convolution(static_cast<const\
    \ MyBase &>(*this),\n                                  [iv = this->front().inv()](int\
    \ n, const std::vector<ModIntT> &c) {\n                                    return\
    \ n == 0 ? iv : -c[n] * iv;\n                                  })\n      .await(n)\n\
    \      .get_rhs();\n}\n\ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT>\
    \ truncated_formal_power_series<ModIntT>::exp(int n) const {\n  return semi_relaxed_convolution(static_cast<MyBase>(deriv()),\n\
    \                                  [](int n, const std::vector<ModIntT> &c) {\n\
    \                                    return n == 0 ? ModIntT(1) : c[n - 1] * invs(n);\n\
    \                                  })\n      .await(n)\n      .get_rhs();\n}\n\
    \ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT>\ntruncated_formal_power_series<ModIntT>::div(const\
    \ truncated_formal_power_series &rhs, int n) const {\n  assert(!rhs.is_zero());\n\
    \  return semi_relaxed_convolution(static_cast<const MyBase &>(rhs),\n       \
    \                           [this, sz = static_cast<int>(this->size()),\n    \
    \                               iv = rhs.front().inv()](int n, const std::vector<ModIntT>\
    \ &c) {\n                                    return ((n < sz ? this->operator[](n)\
    \ : ModIntT()) - c[n]) * iv;\n                                  })\n      .await(n)\n\
    \      .get_rhs();\n}\n\ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT>\n\
    truncated_formal_power_series<ModIntT>::pow(int n, long long e) const {\n  if\
    \ (e == 0) {\n    truncated_formal_power_series res{1};\n    res.resize(n);\n\
    \    return res;\n  }\n  const int o = ord();\n  if (o == NEGATIVE_INFINITY ||\
    \ (o > n / e || (o == n / e && n % e == 0)))\n    return truncated_formal_power_series(n);\n\
    \  const long long zs = static_cast<long long>(o) * e; // count zeros\n  const\
    \ int nn       = n - static_cast<int>(zs);\n  const ModIntT c(this->operator[](o)),\
    \ ic(c.inv()), ce(c.pow(e)), me(e);\n  truncated_formal_power_series cpy(this->cbegin()\
    \ + o, this->cend()); // optimize?\n  for (auto &&i : cpy) i *= ic;\n  cpy = cpy.log(nn);\n\
    \  for (auto &&i : cpy) i *= me;\n  cpy = cpy.exp(nn);\n  for (auto &&i : cpy)\
    \ i *= ce;\n  cpy.insert(cpy.begin(), zs, ModIntT());\n  return cpy;\n}\n\ntemplate\
    \ <typename ModIntT>\nstd::optional<truncated_formal_power_series<ModIntT>>\n\
    truncated_formal_power_series<ModIntT>::sqrt_hint(int n, ModIntT c) const {\n\
    \  if (this->empty()) return {};\n  const int o = ord();\n  if (o == NEGATIVE_INFINITY)\
    \ return truncated_formal_power_series(n);\n  if ((o & 1) || c * c != this->operator[](o))\
    \ return {};\n  truncated_formal_power_series cpy(this->cbegin() + o, this->cend());\n\
    \  const ModIntT iv(cpy.front().inv());\n  for (auto &&i : cpy) i *= iv;\n  cpy\
    \ = cpy.pow(n - (o >> 1), static_cast<long long>(ModIntT(2).inv()));\n  for (auto\
    \ &&i : cpy) i *= c;\n  cpy.insert(cpy.begin(), o >> 1, ModIntT());\n  return\
    \ cpy;\n}\n\ntemplate <typename ModIntT>\nstd::optional<truncated_formal_power_series<ModIntT>>\n\
    truncated_formal_power_series<ModIntT>::sqrt(int n) const {\n  if (this->empty())\
    \ return {};\n  const int o = ord();\n  if (o == NEGATIVE_INFINITY) return truncated_formal_power_series(n);\n\
    \  if (o & 1) return {};\n  auto res = sqrt_mod_prime(this->operator[](o));\n\
    \  if (res.empty()) return {};\n  return sqrt_hint(n, res.front());\n}\n\ntemplate\
    \ <typename ModIntT>\nusing tfps = truncated_formal_power_series<ModIntT>;\n\n\
    LIB_END\n\n\n#line 6 \"math/polynomial.hpp\"\n\n#line 12 \"math/polynomial.hpp\"\
    \n\nLIB_BEGIN\n\ntemplate <typename ModIntT>\nclass polynomial : public truncated_formal_power_series<ModIntT>\
    \ {\n  using MyBase = truncated_formal_power_series<ModIntT>;\n  static_assert(std::is_same_v<typename\
    \ MyBase::value_type, ModIntT>);\n\npublic:\n  using truncated_formal_power_series<ModIntT>::truncated_formal_power_series;\n\
    \n  polynomial(const MyBase &rhs) : MyBase(rhs) {}\n  ModIntT operator()(ModIntT\
    \ c) const {\n    ModIntT res;\n    for (int i = this->deg(); i >= 0; --i) res\
    \ = res * c + this->operator[](i);\n    return res;\n  }\n  polynomial operator-()\
    \ { return MyBase::operator-(); }\n  polynomial &operator+=(const polynomial &rhs)\
    \ {\n    MyBase::operator+=(rhs);\n    this->shrink();\n    return *this;\n  }\n\
    \  polynomial &operator-=(const polynomial &rhs) {\n    MyBase::operator-=(rhs);\n\
    \    this->shrink();\n    return *this;\n  }\n  polynomial &operator*=(const polynomial\
    \ &rhs) {\n    MyBase::operator*=(rhs);\n    this->shrink();\n    return *this;\n\
    \  }\n  polynomial &operator/=(const polynomial &rhs) {\n    const int n = this->deg(),\
    \ m = rhs.deg();\n    assert(m != MyBase::NEGATIVE_INFINITY);\n    if (n < m)\
    \ {\n      this->clear();\n      return *this;\n    }\n    auto irev_rhs = polynomial(rhs.crbegin()\
    \ + (rhs.size() - m - 1), rhs.crend()).inv(n - m + 1);\n    auto lhsirhs  = *this\
    \ * polynomial(irev_rhs.crbegin(), irev_rhs.crend());\n    this->resize(n - m\
    \ + 1);\n    std::copy(lhsirhs.cbegin() + n, lhsirhs.cend(), this->begin());\n\
    \    return *this;\n  }\n  polynomial &operator%=(const polynomial &rhs) {\n \
    \   return this->operator=(div_with_rem(rhs).second);\n  }\n  std::pair<polynomial,\
    \ polynomial> div_with_rem(const polynomial &rhs) const {\n    const int n = this->deg(),\
    \ m = rhs.deg();\n    if (n < m) return std::make_pair(polynomial(), *this);\n\
    \    auto q    = *this / rhs;\n    auto qrhs = q * rhs;\n    polynomial r(m);\n\
    \    for (int i = 0; i != m; ++i) r[i] = this->operator[](i) - qrhs[i];\n    r.shrink();\n\
    \    return std::make_pair(q, r);\n  }\n\n  friend polynomial operator+(const\
    \ polynomial &lhs, const polynomial &rhs) {\n    return polynomial(lhs) += rhs;\n\
    \  }\n  friend polynomial operator-(const polynomial &lhs, const polynomial &rhs)\
    \ {\n    return polynomial(lhs) -= rhs;\n  }\n  friend polynomial operator*(const\
    \ polynomial &lhs, const polynomial &rhs) {\n    return polynomial(lhs) *= rhs;\n\
    \  }\n  friend polynomial operator/(const polynomial &lhs, const polynomial &rhs)\
    \ {\n    return polynomial(lhs) /= rhs;\n  }\n  friend polynomial operator%(const\
    \ polynomial &lhs, const polynomial &rhs) {\n    return polynomial(lhs) %= rhs;\n\
    \  }\n  friend std::istream &operator>>(std::istream &lhs, polynomial &rhs) {\n\
    \    for (auto &&i : rhs) lhs >> i;\n    return lhs;\n  }\n  friend std::ostream\
    \ &operator<<(std::ostream &lhs, const polynomial &rhs) {\n    return lhs << static_cast<MyBase>(rhs);\n\
    \  }\n};\n\ntemplate <typename IterT>\npolynomial(IterT, IterT) -> polynomial<typename\
    \ std::iterator_traits<IterT>::value_type>;\n\nLIB_END\n\n\n#line 1 \"math/taylor_shift.hpp\"\
    \n\n\n\n#line 1 \"math/binomial.hpp\"\n\n\n\n#line 5 \"math/binomial.hpp\"\n\n\
    #line 7 \"math/binomial.hpp\"\n\nLIB_BEGIN\n\n// helper class for precomputation\
    \ of factorials and multiplicative inverse of them.\ntemplate <typename ModIntT>\n\
    class binomial {\n  mutable std::vector<ModIntT> factorial_{ModIntT(1)}, invfactorial_{ModIntT(1)};\n\
    \npublic:\n  explicit binomial(int n) { preprocess(n); }\n  binomial() {}\n  void\
    \ preprocess(int n) const {\n    if (int nn = static_cast<int>(factorial_.size());\
    \ nn <= n) {\n      int k = nn;\n      while (k <= n) k <<= 1;\n      factorial_.resize(k);\n\
    \      invfactorial_.resize(k);\n      for (int i = nn; i != k; ++i) factorial_[i]\
    \ = factorial_[i - 1] * i;\n      invfactorial_.back() = factorial_.back().inv();\n\
    \      for (int i = k - 2; i >= nn; --i) invfactorial_[i] = invfactorial_[i +\
    \ 1] * (i + 1);\n    }\n  }\n  // binomial coefficient `n`C`m`\n  ModIntT binom(int\
    \ n, int m) const {\n    return n < m ? ModIntT()\n                 : (preprocess(n),\
    \ factorial_[n] * invfactorial_[m] * invfactorial_[n - m]);\n  }\n  ModIntT inv(int\
    \ n) const { return preprocess(n), factorial_[n - 1] * invfactorial_[n]; }\n \
    \ ModIntT factorial(int n) const { return preprocess(n), factorial_[n]; }\n  ModIntT\
    \ inv_factorial(int n) const { return preprocess(n), invfactorial_[n]; }\n};\n\
    \nLIB_END\n\n\n#line 6 \"math/taylor_shift.hpp\"\n\n#line 8 \"math/taylor_shift.hpp\"\
    \n\nLIB_BEGIN\n\ntemplate <typename PolyT>\nPolyT taylor_shift(const PolyT &a,\
    \ typename PolyT::value_type c) {\n  using T     = typename PolyT::value_type;\n\
    \  const int n = static_cast<int>(a.size());\n  binomial<T> b(n);\n  PolyT rev_a_cpy(n),\
    \ pc(n);\n  for (int i = 0; i != n; ++i) rev_a_cpy[n - 1 - i] = a[i] * b.factorial(i);\n\
    \  T cc(1);\n  for (int i = 0; i != n; ++i) pc[i] = cc * b.inv_factorial(i), cc\
    \ *= c;\n  (rev_a_cpy *= pc).resize(n);\n  std::reverse(rev_a_cpy.begin(), rev_a_cpy.end());\n\
    \  for (int i = 0; i != n; ++i) rev_a_cpy[i] *= b.inv_factorial(i);\n  return\
    \ rev_a_cpy;\n}\n\nLIB_END\n\n\n#line 1 \"modint/montgomery_modint.hpp\"\n\n\n\
    \n#line 5 \"modint/montgomery_modint.hpp\"\n\n#ifdef LIB_DEBUG\n  #include <stdexcept>\n\
    #endif\n#line 12 \"modint/montgomery_modint.hpp\"\n\nLIB_BEGIN\n\ntemplate <std::uint32_t\
    \ ModT>\nclass montgomery_modint30 {\n  using i32 = std::int32_t;\n  using u32\
    \ = std::uint32_t;\n  using u64 = std::uint64_t;\n\n  u32 v_{};\n\n  static constexpr\
    \ u32 get_r() {\n    u32 t = 2, iv = MOD * (t - MOD * MOD);\n    iv *= t - MOD\
    \ * iv, iv *= t - MOD * iv;\n    return iv * (MOD * iv - t);\n  }\n  static constexpr\
    \ u32 redc(u64 x) {\n    return (x + static_cast<u64>(static_cast<u32>(x) * R)\
    \ * MOD) >> 32;\n  }\n  static constexpr u32 norm(u32 x) { return x - (MOD & -((MOD\
    \ - 1 - x) >> 31)); }\n\n  static constexpr u32 MOD  = ModT;\n  static constexpr\
    \ u32 MOD2 = MOD << 1;\n  static constexpr u32 R    = get_r();\n  static constexpr\
    \ u32 R2   = -static_cast<u64>(MOD) % MOD;\n  static constexpr i32 SMOD = static_cast<i32>(MOD);\n\
    \n  static_assert(MOD & 1);\n  static_assert(-R * MOD == 1);\n  static_assert((MOD\
    \ >> 30) == 0);\n  static_assert(MOD != 1);\n\npublic:\n  static constexpr u32\
    \ mod() { return MOD; }\n  static constexpr i32 smod() { return SMOD; }\n  constexpr\
    \ montgomery_modint30() {}\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>,\
    \ int> = 0>\n  constexpr montgomery_modint30(IntT v) : v_(redc(static_cast<u64>(v\
    \ % SMOD + SMOD) * R2)) {}\n  constexpr u32 val() const { return norm(redc(v_));\
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
    using mm30 = montgomery_modint30<ModT>;\n\nLIB_END\n\n\n#line 6 \"remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp\"\
    \n\n#line 10 \"remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp\"\n\n\
    int main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin), std::freopen(\"\
    out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n  std::cin.tie(nullptr);\n\
    \  using mint = lib::mm30<998244353>;\n  int n;\n  mint c;\n  std::cin >> n >>\
    \ c;\n  lib::polynomial<mint> f;\n  std::copy_n(std::istream_iterator<mint>(std::cin),\
    \ n, std::back_inserter(f));\n  auto fc = lib::taylor_shift(f, c);\n  std::copy(fc.cbegin(),\
    \ fc.cend(), std::ostream_iterator<mint>(std::cout, \" \"));\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/polynomial_taylor_shift\"\
    \n\n#include \"math/polynomial.hpp\"\n#include \"math/taylor_shift.hpp\"\n#include\
    \ \"modint/montgomery_modint.hpp\"\n\n#include <algorithm>\n#include <iostream>\n\
    #include <iterator>\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\"\
    , stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(nullptr);\n  using mint = lib::mm30<998244353>;\n  int n;\n  mint\
    \ c;\n  std::cin >> n >> c;\n  lib::polynomial<mint> f;\n  std::copy_n(std::istream_iterator<mint>(std::cin),\
    \ n, std::back_inserter(f));\n  auto fc = lib::taylor_shift(f, c);\n  std::copy(fc.cbegin(),\
    \ fc.cend(), std::ostream_iterator<mint>(std::cout, \" \"));\n  return 0;\n}"
  dependsOn:
  - math/polynomial.hpp
  - common.hpp
  - math/truncated_formal_power_series.hpp
  - math/extended_gcd.hpp
  - math/semi_relaxed_convolution.hpp
  - math/radix2_ntt.hpp
  - math/sqrt_mod.hpp
  - math/random.hpp
  - math/truncated_fourier_transform.hpp
  - math/taylor_shift.hpp
  - math/binomial.hpp
  - modint/montgomery_modint.hpp
  - common.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  requiredBy: []
  timestamp: '2023-12-17 11:51:45+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
- /verify/remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp.html
title: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
---
