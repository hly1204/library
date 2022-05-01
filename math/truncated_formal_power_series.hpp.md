---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: math/extended_gcd.hpp
    title: Extended Euclidean Algorithm
  - icon: ':heavy_check_mark:'
    path: math/radix2_ntt.hpp
    title: Radix-2 NTT
  - icon: ':heavy_check_mark:'
    path: math/semi_relaxed_convolution.hpp
    title: Semi-Relaxed Convolution
  - icon: ':heavy_check_mark:'
    path: math/sqrt_mod.hpp
    title: Square Roots in Finite Fields
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.1.test.cpp
    title: remote_test/yosupo/math/convolution_mod.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
    title: remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/truncated_formal_power_series.hpp\"\n\n\n\n#line 1\
    \ \"common.hpp\"\n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n\
    #define LIB_END }\n#define LIB ::lib::\n\n\n#line 1 \"math/extended_gcd.hpp\"\n\
    \n\n\n#line 5 \"math/extended_gcd.hpp\"\n\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\nLIB_BEGIN\n\n// Input:  integer `a` and `b`.\n// Output:\
    \ (x, y, z) such that `a`x + `b`y = z = gcd(`a`, `b`).\n[[deprecated]] std::tuple<long\
    \ long, long long, long long> ext_gcd(long long a, long long b) {\n  long long\
    \ x11 = 1, x12 = 0, x21 = 0, x22 = 1;\n  while (b != 0) {\n    long long q = a\
    \ / b, x11_cpy = x11, x12_cpy = x12, a_cpy = a;\n    x11 = x21, x21 = x11_cpy\
    \ - q * x21;\n    x12 = x22, x22 = x12_cpy - q * x22;\n    a = b, b = a_cpy -\
    \ q * b;\n  }\n  return std::make_tuple(x11, x12, a);\n}\n\n// Input:  integer\
    \ `a` and `b`.\n// Output: (x, gcd(`a`, `b`)) such that `a`x \u2261 gcd(`a`, `b`)\
    \ (mod `b`).\nstd::pair<long long, long long> inv_gcd(long long a, long long b)\
    \ {\n  long long x11 = 1, x21 = 0;\n  while (b != 0) {\n    long long q = a /\
    \ b, x11_cpy = x11, a_cpy = a;\n    x11 = x21, x21 = x11_cpy - q * x21;\n    a\
    \ = b, b = a_cpy - q * b;\n  }\n  return std::make_pair(x11, a);\n}\n\nnamespace\
    \ detail {\n\ntemplate <typename ModIntT>\nclass modular_inverse {\n  std::vector<ModIntT>\
    \ ivs{ModIntT()};\n\n  enum : int { LIM = 1 << 20 };\n\npublic:\n  modular_inverse()\
    \ {}\n  ModIntT operator()(int k) {\n    // assume `ModIntT::mod()` is prime.\n\
    \    if (k > LIM) return ModIntT(k).inv();\n    // preprocess modular inverse\
    \ from 1 to `k`\n    if (int n = static_cast<int>(ivs.size()); n <= k) {\n   \
    \   int nn = n;\n      while (nn <= k) nn <<= 1;\n      ivs.resize(nn);\n    \
    \  ModIntT v(1);\n      for (int i = n; i != nn; ++i) ivs[i] = v, v *= ModIntT(i);\n\
    \      v = v.inv();\n      for (int i = nn - 1; i >= n; --i) ivs[i] *= v, v *=\
    \ ModIntT(i);\n    }\n    return ivs[k];\n  }\n};\n\n} // namespace detail\n\n\
    LIB_END\n\n\n#line 1 \"math/radix2_ntt.hpp\"\n\n\n\n#line 5 \"math/radix2_ntt.hpp\"\
    \n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <type_traits>\n\
    #line 11 \"math/radix2_ntt.hpp\"\n\nLIB_BEGIN\n\nnamespace detail {\n\ntemplate\
    \ <typename IntT>\nconstexpr std::enable_if_t<std::is_integral_v<IntT>, int> bsf(IntT\
    \ v) {\n  if (static_cast<std::make_signed_t<IntT>>(v) <= 0) return -1;\n  int\
    \ res = 0;\n  for (; (v & 1) == 0; ++res) v >>= 1;\n  return res;\n}\n\ntemplate\
    \ <typename ModIntT>\nconstexpr ModIntT quadratic_nonresidue_prime() {\n  auto\
    \ mod = ModIntT::mod();\n  for (int i = 2;; ++i)\n    if (ModIntT(i).pow(mod >>\
    \ 1) == mod - 1) return ModIntT(i);\n}\n\ntemplate <typename ModIntT>\nconstexpr\
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
    \n\n#line 1 \"math/semi_relaxed_convolution.hpp\"\n\n\n\n#line 6 \"math/semi_relaxed_convolution.hpp\"\
    \n\n#line 11 \"math/semi_relaxed_convolution.hpp\"\n\nLIB_BEGIN\n\ntemplate <typename\
    \ ModIntT, typename FnT>\nclass semi_relaxed_convolution {\n  std::vector<ModIntT>\
    \ fixed_A_{}, B_{}, c_{};\n  std::vector<std::vector<std::vector<ModIntT>>> dft_A_cache_{},\
    \ dft_B_cache_{};\n  int n_{};\n  FnT handle_;\n\n  enum : int { BASE_CASE_SIZE\
    \ = 32, LOG_BLOCK = 4, BLOCK = 1 << LOG_BLOCK, MASK = BLOCK - 1 };\n\n  static_assert((BASE_CASE_SIZE\
    \ & (BASE_CASE_SIZE - 1)) == 0);\n  static_assert(std::is_invocable_r_v<ModIntT,\
    \ FnT, int, const std::vector<ModIntT> &> ||\n                std::is_invocable_r_v<ModIntT,\
    \ FnT, int>);\n\npublic:\n  semi_relaxed_convolution(const std::vector<ModIntT>\
    \ &A, FnT &&handle)\n      : fixed_A_(A), c_(1024), handle_(std::forward<FnT>(handle))\
    \ {}\n  const std::vector<ModIntT> &get_multiplier() const { return B_; }\n  const\
    \ std::vector<ModIntT> &get_multiplicand() const { return fixed_A_; }\n  semi_relaxed_convolution\
    \ &await(int k) {\n    while (n_ < k) next();\n    return *this;\n  }\n  ModIntT\
    \ at(int k) {\n    while (n_ <= k) next();\n    return c_[k];\n  }\n  ModIntT\
    \ operator[](int k) { return at(k); }\n  ModIntT next();\n};\n\ntemplate <typename\
    \ ModIntT, typename FnT>\nModIntT semi_relaxed_convolution<ModIntT, FnT>::next()\
    \ {\n  {\n    // enlarge space\n    int len = ntt_len(n_ << 1 | 1);\n    if (static_cast<int>(c_.size())\
    \ < len) c_.resize(len);\n    if (static_cast<int>(fixed_A_.size()) < len) fixed_A_.resize(len);\n\
    \  }\n  if ((n_ & (BASE_CASE_SIZE - 1)) == 0)\n    for (int t = n_ / BASE_CASE_SIZE,\
    \ block_size = BASE_CASE_SIZE, lv = 0; t != 0;\n         t >>= LOG_BLOCK, block_size\
    \ <<= LOG_BLOCK, ++lv)\n      if (int i = t & MASK, block_size2 = block_size <<\
    \ 1, l = n_ - block_size; i != 0) {\n        if (block_size * i == n_) {\n   \
    \       if (static_cast<int>(dft_A_cache_.size()) == lv) {\n            dft_A_cache_.emplace_back();\n\
    \            dft_B_cache_.emplace_back(BLOCK - 1);\n          }\n          dft(dft_A_cache_[lv].emplace_back(fixed_A_.cbegin()\
    \ + (i - 1) * block_size,\n                                            fixed_A_.cbegin()\
    \ + (i + 1) * block_size));\n        }\n        auto &B_cache = dft_B_cache_[lv];\n\
    \        B_cache[i - 1].resize(block_size2);\n        std::fill_n(std::copy_n(B_.cbegin()\
    \ + l, block_size, B_cache[i - 1].begin()), block_size,\n                    ModIntT());\n\
    \        dft(B_cache[i - 1]);\n        std::vector<ModIntT> temp_sum(block_size2);\n\
    \        for (int j = 0; j != i; ++j)\n          for (int k = 0; k != block_size2;\
    \ ++k)\n            temp_sum[k] += dft_A_cache_[lv][i - 1 - j][k] * B_cache[j][k];\n\
    \        idft(temp_sum);\n        for (int j = block_size; j != block_size2; ++j)\
    \ c_[j + n_ - block_size] += temp_sum[j];\n        break;\n      }\n  for (int\
    \ i = 0, l = n_ & ~(BASE_CASE_SIZE - 1); i < n_ - l; ++i)\n    c_[n_] += fixed_A_[n_\
    \ - l - i] * B_[l + i];\n  // clang-format off\n  if constexpr (std::is_invocable_r_v<ModIntT,\
    \ FnT, int, const std::vector<ModIntT> &>)\n    c_[n_] += fixed_A_.front() * B_.emplace_back(handle_(n_,\
    \ c_));\n  else\n    c_[n_] += fixed_A_.front() * B_.emplace_back(handle_(n_));\n\
    \  // clang-format on\n  return c_[n_++];\n}\n\nLIB_END\n\n\n#line 1 \"math/sqrt_mod.hpp\"\
    \n\n\n\n#line 5 \"math/sqrt_mod.hpp\"\n\n#include <random>\n#line 9 \"math/sqrt_mod.hpp\"\
    \n\nLIB_BEGIN\n\ntemplate <typename ModIntT>\nstd::vector<ModIntT> sqrt_mod_prime(ModIntT\
    \ a) {\n  // Bostan-Mori's algorithm\n  if (a.is_zero()) return {a};\n  const\
    \ auto p = ModIntT::mod();\n  if (a.pow(p >> 1) == -1) return {};\n  if ((p &\
    \ 3) == 3) {\n    ModIntT b(a.pow((p + 1) >> 2));\n    return {b, -b};\n  }\n\
    \  std::mt19937 gen(std::random_device{}());\n  std::uniform_int_distribution<std::remove_cv_t<decltype(p)>>\
    \ dis(2, p - 1);\n  ModIntT t;\n  do { t = dis(gen); } while ((t * t - 4 * a).pow(p\
    \ >> 1) != -1);\n  ModIntT k0(1), k1, k2(-t), k3(a);\n  for (auto e = (p + 1)\
    \ >> 1;;) {\n    // clang-format off\n    if (e & 1) k0 = k1 - k0 * k2, k1 *=\
    \ k3;\n    else k1 = k0 * k3 - k1 * k2;\n    // clang-format on\n    if ((e >>=\
    \ 1) == 0) return {k0, -k0};\n    k2 = k3 + k3 - k2 * k2, k3 *= k3;\n  }\n}\n\n\
    LIB_END\n\n\n#line 9 \"math/truncated_formal_power_series.hpp\"\n\n#line 12 \"\
    math/truncated_formal_power_series.hpp\"\n#include <iostream>\n#include <iterator>\n\
    #include <optional>\n#line 17 \"math/truncated_formal_power_series.hpp\"\n\nLIB_BEGIN\n\
    \ntemplate <typename ModIntT>\nclass truncated_formal_power_series : public std::vector<ModIntT>\
    \ {\n  static_assert(std::is_same_v<typename std::vector<ModIntT>::value_type,\
    \ ModIntT>);\n\n  static typename detail::modular_inverse<ModIntT> invs;\n\npublic:\n\
    \  using std::vector<ModIntT>::vector;\n\n  enum : int { NEGATIVE_INFINITY = -1\
    \ };\n\n  // leading coefficient\n  ModIntT lc() const {\n    int d = deg();\n\
    \    return d == NEGATIVE_INFINITY ? ModIntT() : this->operator[](d);\n  }\n \
    \ // degree\n  int deg() const {\n    // treat formal power series like polynomials\n\
    \    int n = static_cast<int>(this->size()) - 1;\n    while (n >= 0 && this->operator[](n).is_zero())\
    \ --n;\n    return n == -1 ? NEGATIVE_INFINITY : n;\n  }\n  // order\n  int ord()\
    \ const {\n    int d = deg();\n    if (d == NEGATIVE_INFINITY) return NEGATIVE_INFINITY;\n\
    \    for (int i = 0;; ++i)\n      if (!this->operator[](i).is_zero()) return i;\n\
    \  }\n  bool is_zero() const { return deg() == NEGATIVE_INFINITY; }\n  void shrink()\
    \ { this->resize(deg() + 1); }\n  truncated_formal_power_series operator-() {\n\
    \    truncated_formal_power_series res(*this);\n    for (auto &&i : res) i = -i;\n\
    \    return res;\n  }\n\n  truncated_formal_power_series &operator+=(const truncated_formal_power_series\
    \ &rhs) {\n    if (this->size() < rhs.size()) this->resize(rhs.size());\n    for\
    \ (int i = 0, e = static_cast<int>(rhs.size()); i != e; ++i) this->operator[](i)\
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
    \ pow(int n, int e) const;\n  std::optional<truncated_formal_power_series> sqrt_hint(int\
    \ n, ModIntT c) const;\n  std::optional<truncated_formal_power_series> sqrt(int\
    \ n) const;\n\n  friend truncated_formal_power_series operator+(const truncated_formal_power_series\
    \ &lhs,\n                                                 const truncated_formal_power_series\
    \ &rhs) {\n    return truncated_formal_power_series(lhs) += rhs;\n  }\n  friend\
    \ truncated_formal_power_series operator-(const truncated_formal_power_series\
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
    \ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT> &truncated_formal_power_series<ModIntT>::operator*=(\n\
    \    const truncated_formal_power_series<ModIntT> &rhs) {\n  // 6E\n  int n =\
    \ static_cast<int>(this->size()), m = static_cast<int>(rhs.size());\n  if (n ==\
    \ 0 || m == 0) {\n    this->clear();\n    return *this;\n  }\n  if (std::min(n,\
    \ m) <= 32) {\n    truncated_formal_power_series res(n + m - 1);\n    for (int\
    \ i = 0; i != n; ++i)\n      for (int j = 0; j != m; ++j) res[i + j] += this->operator[](i)\
    \ * rhs[j];\n    return this->operator=(res);\n  }\n  int len = ntt_len(n + m\
    \ - 1);\n  truncated_formal_power_series rhs_cpy(len);\n  std::copy_n(rhs.cbegin(),\
    \ m, rhs_cpy.begin());\n  this->resize(len);\n  dft_n(this->begin(), len), dft_n(rhs_cpy.begin(),\
    \ len);\n  for (int i = 0; i != len; ++i) this->operator[](i) *= rhs_cpy[i];\n\
    \  idft_n(this->begin(), len);\n  this->resize(n + m - 1);\n  return *this;\n\
    }\n\ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT> truncated_formal_power_series<ModIntT>::inv(int\
    \ n) const {\n  if (n <= 0) return {};\n  const std::vector a(this->cbegin(),\
    \ this->cend());\n  semi_relaxed_convolution src(a, [iv = a.front().inv()](int\
    \ n, const std::vector<ModIntT> &c) {\n    return n == 0 ? iv : -c[n] * iv;\n\
    \  });\n  auto &&multiplier = src.await(n).get_multiplier();\n  return truncated_formal_power_series(multiplier.cbegin(),\
    \ multiplier.cend());\n}\n\ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT>\
    \ truncated_formal_power_series<ModIntT>::exp(int n) const {\n  if (n <= 0) return\
    \ {};\n  auto &&d = deriv();\n  std::vector dv(d.cbegin(), d.cend());\n  semi_relaxed_convolution\
    \ src(dv, [](int n, const std::vector<ModIntT> &c) {\n    return n == 0 ? ModIntT(1)\
    \ : c[n - 1] * invs(n);\n  });\n  auto &&multiplier = src.await(n).get_multiplier();\n\
    \  return truncated_formal_power_series(multiplier.cbegin(), multiplier.cend());\n\
    }\n\ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT>\ntruncated_formal_power_series<ModIntT>::div(const\
    \ truncated_formal_power_series &rhs, int n) const {\n  assert(!rhs.is_zero());\n\
    \  if (n <= 0) return {};\n  const std::vector a(rhs.cbegin(), rhs.cend());\n\
    \  semi_relaxed_convolution src(\n      a, [this, iv = a.front().inv()](int n,\
    \ const std::vector<ModIntT> &c) {\n        return ((n < static_cast<int>(this->size())\
    \ ? this->operator[](n) : ModIntT()) - c[n]) * iv;\n      });\n  auto &&multiplier\
    \ = src.await(n).get_multiplier();\n  return truncated_formal_power_series(multiplier.cbegin(),\
    \ multiplier.cend());\n}\n\ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT>\
    \ truncated_formal_power_series<ModIntT>::pow(int n,\n                       \
    \                                                            int e) const {\n\
    \  const int o        = ord();\n  const long long zs = static_cast<long long>(o)\
    \ * e; // count zeros\n  if (o == NEGATIVE_INFINITY || zs >= n) return truncated_formal_power_series(n);\n\
    \  const int nn = n - static_cast<int>(zs);\n  const ModIntT c(this->operator[](o)),\
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
    \ = cpy.pow(n - (o >> 1), static_cast<int>(ModIntT(2).inv()));\n  for (auto &&i\
    \ : cpy) i *= c;\n  cpy.insert(cpy.begin(), o >> 1, ModIntT());\n  return cpy;\n\
    }\n\ntemplate <typename ModIntT>\nstd::optional<truncated_formal_power_series<ModIntT>>\n\
    truncated_formal_power_series<ModIntT>::sqrt(int n) const {\n  if (this->empty())\
    \ return {};\n  const int o = ord();\n  if (o == NEGATIVE_INFINITY) return truncated_formal_power_series(n);\n\
    \  if (o & 1) return {};\n  auto res = sqrt_mod_prime(this->operator[](o));\n\
    \  if (res.empty()) return {};\n  return sqrt_hint(n, res.front());\n}\n\ntemplate\
    \ <typename ModIntT>\nusing tfps = truncated_formal_power_series<ModIntT>;\n\n\
    LIB_END\n\n\n"
  code: "#ifndef TRUNCATED_FORMAL_POWER_SERIES_HPP\n#define TRUNCATED_FORMAL_POWER_SERIES_HPP\n\
    \n#include \"../common.hpp\"\n#include \"extended_gcd.hpp\"\n#include \"radix2_ntt.hpp\"\
    \n#include \"semi_relaxed_convolution.hpp\"\n#include \"sqrt_mod.hpp\"\n\n#include\
    \ <algorithm>\n#include <cassert>\n#include <iostream>\n#include <iterator>\n\
    #include <optional>\n#include <type_traits>\n#include <vector>\n\nLIB_BEGIN\n\n\
    template <typename ModIntT>\nclass truncated_formal_power_series : public std::vector<ModIntT>\
    \ {\n  static_assert(std::is_same_v<typename std::vector<ModIntT>::value_type,\
    \ ModIntT>);\n\n  static typename detail::modular_inverse<ModIntT> invs;\n\npublic:\n\
    \  using std::vector<ModIntT>::vector;\n\n  enum : int { NEGATIVE_INFINITY = -1\
    \ };\n\n  // leading coefficient\n  ModIntT lc() const {\n    int d = deg();\n\
    \    return d == NEGATIVE_INFINITY ? ModIntT() : this->operator[](d);\n  }\n \
    \ // degree\n  int deg() const {\n    // treat formal power series like polynomials\n\
    \    int n = static_cast<int>(this->size()) - 1;\n    while (n >= 0 && this->operator[](n).is_zero())\
    \ --n;\n    return n == -1 ? NEGATIVE_INFINITY : n;\n  }\n  // order\n  int ord()\
    \ const {\n    int d = deg();\n    if (d == NEGATIVE_INFINITY) return NEGATIVE_INFINITY;\n\
    \    for (int i = 0;; ++i)\n      if (!this->operator[](i).is_zero()) return i;\n\
    \  }\n  bool is_zero() const { return deg() == NEGATIVE_INFINITY; }\n  void shrink()\
    \ { this->resize(deg() + 1); }\n  truncated_formal_power_series operator-() {\n\
    \    truncated_formal_power_series res(*this);\n    for (auto &&i : res) i = -i;\n\
    \    return res;\n  }\n\n  truncated_formal_power_series &operator+=(const truncated_formal_power_series\
    \ &rhs) {\n    if (this->size() < rhs.size()) this->resize(rhs.size());\n    for\
    \ (int i = 0, e = static_cast<int>(rhs.size()); i != e; ++i) this->operator[](i)\
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
    \ pow(int n, int e) const;\n  std::optional<truncated_formal_power_series> sqrt_hint(int\
    \ n, ModIntT c) const;\n  std::optional<truncated_formal_power_series> sqrt(int\
    \ n) const;\n\n  friend truncated_formal_power_series operator+(const truncated_formal_power_series\
    \ &lhs,\n                                                 const truncated_formal_power_series\
    \ &rhs) {\n    return truncated_formal_power_series(lhs) += rhs;\n  }\n  friend\
    \ truncated_formal_power_series operator-(const truncated_formal_power_series\
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
    \ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT> &truncated_formal_power_series<ModIntT>::operator*=(\n\
    \    const truncated_formal_power_series<ModIntT> &rhs) {\n  // 6E\n  int n =\
    \ static_cast<int>(this->size()), m = static_cast<int>(rhs.size());\n  if (n ==\
    \ 0 || m == 0) {\n    this->clear();\n    return *this;\n  }\n  if (std::min(n,\
    \ m) <= 32) {\n    truncated_formal_power_series res(n + m - 1);\n    for (int\
    \ i = 0; i != n; ++i)\n      for (int j = 0; j != m; ++j) res[i + j] += this->operator[](i)\
    \ * rhs[j];\n    return this->operator=(res);\n  }\n  int len = ntt_len(n + m\
    \ - 1);\n  truncated_formal_power_series rhs_cpy(len);\n  std::copy_n(rhs.cbegin(),\
    \ m, rhs_cpy.begin());\n  this->resize(len);\n  dft_n(this->begin(), len), dft_n(rhs_cpy.begin(),\
    \ len);\n  for (int i = 0; i != len; ++i) this->operator[](i) *= rhs_cpy[i];\n\
    \  idft_n(this->begin(), len);\n  this->resize(n + m - 1);\n  return *this;\n\
    }\n\ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT> truncated_formal_power_series<ModIntT>::inv(int\
    \ n) const {\n  if (n <= 0) return {};\n  const std::vector a(this->cbegin(),\
    \ this->cend());\n  semi_relaxed_convolution src(a, [iv = a.front().inv()](int\
    \ n, const std::vector<ModIntT> &c) {\n    return n == 0 ? iv : -c[n] * iv;\n\
    \  });\n  auto &&multiplier = src.await(n).get_multiplier();\n  return truncated_formal_power_series(multiplier.cbegin(),\
    \ multiplier.cend());\n}\n\ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT>\
    \ truncated_formal_power_series<ModIntT>::exp(int n) const {\n  if (n <= 0) return\
    \ {};\n  auto &&d = deriv();\n  std::vector dv(d.cbegin(), d.cend());\n  semi_relaxed_convolution\
    \ src(dv, [](int n, const std::vector<ModIntT> &c) {\n    return n == 0 ? ModIntT(1)\
    \ : c[n - 1] * invs(n);\n  });\n  auto &&multiplier = src.await(n).get_multiplier();\n\
    \  return truncated_formal_power_series(multiplier.cbegin(), multiplier.cend());\n\
    }\n\ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT>\ntruncated_formal_power_series<ModIntT>::div(const\
    \ truncated_formal_power_series &rhs, int n) const {\n  assert(!rhs.is_zero());\n\
    \  if (n <= 0) return {};\n  const std::vector a(rhs.cbegin(), rhs.cend());\n\
    \  semi_relaxed_convolution src(\n      a, [this, iv = a.front().inv()](int n,\
    \ const std::vector<ModIntT> &c) {\n        return ((n < static_cast<int>(this->size())\
    \ ? this->operator[](n) : ModIntT()) - c[n]) * iv;\n      });\n  auto &&multiplier\
    \ = src.await(n).get_multiplier();\n  return truncated_formal_power_series(multiplier.cbegin(),\
    \ multiplier.cend());\n}\n\ntemplate <typename ModIntT>\ntruncated_formal_power_series<ModIntT>\
    \ truncated_formal_power_series<ModIntT>::pow(int n,\n                       \
    \                                                            int e) const {\n\
    \  const int o        = ord();\n  const long long zs = static_cast<long long>(o)\
    \ * e; // count zeros\n  if (o == NEGATIVE_INFINITY || zs >= n) return truncated_formal_power_series(n);\n\
    \  const int nn = n - static_cast<int>(zs);\n  const ModIntT c(this->operator[](o)),\
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
    \ = cpy.pow(n - (o >> 1), static_cast<int>(ModIntT(2).inv()));\n  for (auto &&i\
    \ : cpy) i *= c;\n  cpy.insert(cpy.begin(), o >> 1, ModIntT());\n  return cpy;\n\
    }\n\ntemplate <typename ModIntT>\nstd::optional<truncated_formal_power_series<ModIntT>>\n\
    truncated_formal_power_series<ModIntT>::sqrt(int n) const {\n  if (this->empty())\
    \ return {};\n  const int o = ord();\n  if (o == NEGATIVE_INFINITY) return truncated_formal_power_series(n);\n\
    \  if (o & 1) return {};\n  auto res = sqrt_mod_prime(this->operator[](o));\n\
    \  if (res.empty()) return {};\n  return sqrt_hint(n, res.front());\n}\n\ntemplate\
    \ <typename ModIntT>\nusing tfps = truncated_formal_power_series<ModIntT>;\n\n\
    LIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  - math/extended_gcd.hpp
  - math/radix2_ntt.hpp
  - math/semi_relaxed_convolution.hpp
  - math/sqrt_mod.hpp
  isVerificationFile: false
  path: math/truncated_formal_power_series.hpp
  requiredBy: []
  timestamp: '2022-04-28 09:57:37+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/convolution_mod.1.test.cpp
  - remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
  - remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
documentation_of: math/truncated_formal_power_series.hpp
layout: document
title: Truncated Formal Power Series
---