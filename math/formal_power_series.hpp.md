---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':question:'
    path: math/extended_gcd.hpp
    title: Extended Euclidean Algorithm (in $\mathbb{Z}$)
  - icon: ':question:'
    path: math/radix2_ntt.hpp
    title: Radix-2 NTT (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  - icon: ':question:'
    path: math/relaxed_convolution.hpp
    title: Relaxed Convolution (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack \rbrack$
      for FFT prime $p$)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/exp_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/exp_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/partition_function.0.test.cpp
    title: remote_test/yosupo/math/partition_function.0.test.cpp
  - icon: ':x:'
    path: remote_test/yosupo/math/pow_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/pow_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/sharp_p_subset_sum.0.test.cpp
    title: remote_test/yosupo/math/sharp_p_subset_sum.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':question:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/formal_power_series.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
    \n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 1 \"math/extended_gcd.hpp\"\n\n\n\n#line 5\
    \ \"math/extended_gcd.hpp\"\n\n#include <tuple>\n#include <utility>\n#include\
    \ <vector>\n\nLIB_BEGIN\n\n// Input:  integer `a` and `b`.\n// Output: (x, y,\
    \ z) such that `a`x + `b`y = z = gcd(`a`, `b`).\n[[deprecated]] std::tuple<long\
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
    \n\n#line 1 \"math/relaxed_convolution.hpp\"\n\n\n\n#line 6 \"math/relaxed_convolution.hpp\"\
    \n\n#include <functional>\n#line 11 \"math/relaxed_convolution.hpp\"\n\nLIB_BEGIN\n\
    \ntemplate <typename ModIntT>\nclass relaxed_convolution {                   \
    \    // O(n log^2 n) impl\n  std::vector<ModIntT> a_{}, b_{}, c_{};          //\
    \ `a_ * b_` = `c_`\n  std::vector<std::vector<ModIntT>> ac_{}, bc_{}; // cached\
    \ DFTs\n  std::function<ModIntT()> ha_{}, hb_{};          // handle for `a_` and\
    \ `b_`\n  int n_{};                                       // counter\n\n  template\
    \ <typename FnT>\n  static auto wrap(FnT &&f, int &n, const std::vector<ModIntT>\
    \ &c, std::vector<ModIntT> &e) {\n    if constexpr (std::is_invocable_r_v<ModIntT,\
    \ FnT, int, const std::vector<ModIntT> &>) {\n      return std::bind(\n      \
    \    [f](int n, const std::vector<ModIntT> &c, std::vector<ModIntT> &e) mutable\
    \ {\n            return ModIntT(e.emplace_back(f(n, c)));\n          },\n    \
    \      std::cref(n), std::cref(c), std::ref(e));\n    } else if constexpr (std::is_invocable_r_v<ModIntT,\
    \ FnT, int>) {\n      return std::bind(\n          [f](int n, std::vector<ModIntT>\
    \ &e) mutable { return ModIntT(e.emplace_back(f(n))); },\n          std::cref(n),\
    \ std::ref(e));\n    } else if constexpr (std::is_invocable_r_v<ModIntT, FnT>)\
    \ {\n      return std::bind(\n          [f](std::vector<ModIntT> &e) mutable {\
    \ return ModIntT(e.emplace_back(f())); },\n          std::ref(e));\n    } else\
    \ {\n      throw;\n    }\n  }\n\n  enum : int { BASE_CASE_SIZE = 32 };\n\n  static_assert((BASE_CASE_SIZE\
    \ & (BASE_CASE_SIZE - 1)) == 0);\n\npublic:\n  // `h0` multiplicand, `h1` multiplier\n\
    \  template <typename Fn0T, typename Fn1T>\n  relaxed_convolution(Fn0T &&h0, Fn1T\
    \ &&h1)\n      : c_(4), ha_(wrap(std::forward<Fn0T>(h0), n_, c_, a_)),\n     \
    \   hb_(wrap(std::forward<Fn1T>(h1), n_, c_, b_)) {}\n  const std::vector<ModIntT>\
    \ &get_multiplier() const { return b_; }\n  const std::vector<ModIntT> &get_multiplicand()\
    \ const { return a_; }\n  relaxed_convolution &await(int k) {\n    while (n_ <\
    \ k) next();\n    return *this;\n  }\n  ModIntT at(int k) {\n    while (n_ <=\
    \ k) next();\n    return c_[k];\n  }\n  ModIntT operator[](int k) { return at(k);\
    \ }\n  ModIntT next();\n};\n\ntemplate <typename ModIntT>\nModIntT relaxed_convolution<ModIntT>::next()\
    \ {\n  {\n    // enlarge space\n    int len = ntt_len(n_ << 1 | 1);\n    if (static_cast<int>(c_.size())\
    \ < len) c_.resize(len);\n  }\n  switch (n_) {\n  case 0: c_[0] = ha_() * hb_();\
    \ break;\n  case 1:\n    c_[1] = ha_() * b_.front() + a_.front() * hb_();\n  \
    \  c_[2] = a_[1] * b_[1];\n    break;\n  case 2:\n    c_[2] += ha_() * b_.front()\
    \ + a_.front() * hb_();\n    c_[3] = a_[2] * b_[1] + a_[1] * b_[2];\n    break;\n\
    \  default:\n    if ((n_ & (n_ - 1)) == 0) {\n      auto &&c0 = ac_.emplace_back(n_);\n\
    \      auto &&c1 = bc_.emplace_back(n_);\n      std::copy_n(a_.cbegin() + (n_\
    \ >> 1), n_ >> 1, c0.begin());\n      std::copy_n(b_.cbegin() + (n_ >> 1), n_\
    \ >> 1, c1.begin());\n      dft(c0), dft(c1);\n      std::vector c0_cpy(c0);\n\
    \      for (int i = 0; i != n_; ++i) c0_cpy[i] *= c1[i];\n      idft(c0_cpy);\n\
    \      for (int i = 0; i != n_ - 1; ++i) c_[n_ + i] += c0_cpy[i];\n    }\n   \
    \ c_[n_] += ha_() * b_.front() + a_.front() * hb_();\n    c_[n_ + 1] += a_[1]\
    \ * b_.back() + a_.back() * b_[1];\n    for (int sft = 1, offset = ntt_len(n_\
    \ + 1) >> 1, t = n_ + 1 - offset;\n         (t & 1) == 0 && 1 << sft < offset;\
    \ ++sft, t >>= 1)\n      if (1 << sft <= BASE_CASE_SIZE) {\n        for (int i\
    \ = 0, m = n_ + 1 - (1 << sft); i != 1 << sft; ++i)\n          for (int j = 0;\
    \ j != 1 << sft; ++j)\n            c_[n_ + 1 + i + j] += a_[m + i] * b_[j + (1\
    \ << sft)] + a_[j + (1 << sft)] * b_[m + i];\n      } else {\n        std::vector<ModIntT>\
    \ c0(2 << sft), c1(2 << sft);\n        std::copy_n(a_.cbegin() + n_ + 1 - (1 <<\
    \ sft), 1 << sft, c0.begin());\n        std::copy_n(b_.cbegin() + n_ + 1 - (1\
    \ << sft), 1 << sft, c1.begin());\n        dft(c0), dft(c1);\n        for (int\
    \ i = 0; i != 2 << sft; ++i)\n          c0[i] = c0[i] * bc_[sft - 1][i] + c1[i]\
    \ * ac_[sft - 1][i];\n        idft(c0);\n        for (int i = 0; i != (2 << sft)\
    \ - 1; ++i) c_[n_ + 1 + i] += c0[i];\n      }\n  }\n  return c_[n_++];\n}\n\n\
    LIB_END\n\n\n#line 8 \"math/formal_power_series.hpp\"\n\n#line 10 \"math/formal_power_series.hpp\"\
    \n#include <memory>\n#include <optional>\n#line 14 \"math/formal_power_series.hpp\"\
    \n\nLIB_BEGIN\n\ntemplate <typename ModIntT>\nclass formal_power_series {\n  using\
    \ F = std::function<ModIntT(int)>;\n  F h_;\n\n  static typename detail::modular_inverse<ModIntT>\
    \ invs;\n\npublic:\n  formal_power_series() : h_([](int) { return ModIntT(); })\
    \ {}\n  explicit formal_power_series(F f)\n      : h_([f, cache = std::make_shared<std::vector<ModIntT>>()](int\
    \ k) {\n          for (int i = static_cast<int>(cache->size()); i <= k; ++i) cache->emplace_back(f(i));\n\
    \          return ModIntT(cache->at(k));\n        }) {}\n  explicit formal_power_series(const\
    \ std::vector<ModIntT> &coeff)\n      : h_([cache = std::make_shared<std::vector<ModIntT>>(coeff)](int\
    \ k) {\n          return k < static_cast<int>(cache->size()) ? ModIntT(cache->at(k))\
    \ : ModIntT();\n        }) {}\n  formal_power_series(ModIntT v) : h_([v](int k)\
    \ { return k == 0 ? v : ModIntT(); }) {}\n  F handle() const { return h_; }\n\
    \  ModIntT operator[](int k) const { return h_(k); }\n  formal_power_series scale(int\
    \ k) const {\n    return formal_power_series([h = h_, k](int i) { return i % k\
    \ == 0 ? h(i / k) : ModIntT(); });\n  }\n  formal_power_series shift(int k) const\
    \ {\n    return formal_power_series([h = h_, k](int i) { return i - k < 0 ? ModIntT()\
    \ : h(i - k); });\n  }\n  formal_power_series deriv() const {\n    return formal_power_series([h\
    \ = h_](int i) { return h(i + 1) * (i + 1); });\n  }\n  formal_power_series integr(ModIntT\
    \ c = ModIntT()) const {\n    return formal_power_series([h = h_, c](int i) {\
    \ return i == 0 ? c : h(i - 1) * invs(i); });\n  }\n  formal_power_series inv()\
    \ const {\n    auto rc = std::make_shared<relaxed_convolution<ModIntT>>(\n   \
    \     [h = h_](int i) { return h(i); },\n        [h = h_, iv = ModIntT()](int\
    \ i, const auto &c) mutable {\n          return i == 0 ? ModIntT(iv = h(0).inv())\
    \ : -(c[i] + h(i) * iv) * iv;\n        });\n    return formal_power_series([rc](int\
    \ i) { return rc->next(), rc->get_multiplier()[i]; });\n  }\n  formal_power_series\
    \ exp() const {\n    auto rc = std::make_shared<relaxed_convolution<ModIntT>>(\n\
    \        [h = h_](int i) { return h(i + 1) * (i + 1); },\n        [](int i, const\
    \ auto &c) { return i == 0 ? ModIntT(1) : c[i - 1] * invs(i); });\n    return\
    \ formal_power_series(\n        [rc](int i) { return i == 0 ? ModIntT(1) : rc->at(i\
    \ - 1) * invs(i); });\n  }\n  formal_power_series log() const { return (deriv()\
    \ / (*this)).integr(); }\n  formal_power_series pow(int k) const {\n    return\
    \ formal_power_series(\n        [h = h_, kk = ModIntT(k), k, zero_cnt = 0ull,\
    \ s = std::optional<F>()](int i) mutable {\n          if (s) return i < zero_cnt\
    \ ? ModIntT() : (*s)(i - zero_cnt);\n          ModIntT v(h(i));\n          if\
    \ (v.is_zero()) return ++zero_cnt, ModIntT();\n          zero_cnt *= k;\n    \
    \      formal_power_series t0([os = i, iv = v.inv(), h](int i) { return h(i +\
    \ os) * iv; });\n          formal_power_series t1([h0 = t0.log().handle(), kk](int\
    \ i) { return h0(i) * kk; });\n          s.emplace([vk = v.pow(k), h1 = t1.exp().handle()](int\
    \ i) { return h1(i) * vk; });\n          return zero_cnt == 0 ? (*s)(i) : ModIntT();\n\
    \        });\n  }\n  template <typename SqrtFuncT,\n            typename std::enable_if_t<std::is_invocable_r_v<ModIntT,\
    \ SqrtFuncT, ModIntT>, int> = 0>\n  formal_power_series sqrt(SqrtFuncT &&f) const\
    \ {\n    // `h_(0) == 0` is not allowed.\n    auto t = [h = h_, f, i2 = ModIntT()](int\
    \ i, auto const &c) mutable {\n      if (i != 0) return (h(i) - c[i]) * i2;\n\
    \      ModIntT fi(f(h(i)));\n      i2 = (fi * ModIntT(2)).inv();\n      return\
    \ fi;\n    };\n    auto rc = std::make_shared<relaxed_convolution<ModIntT>>(t,\
    \ t);\n    return formal_power_series([rc](int i) { return rc->next(), rc->get_multiplier()[i];\
    \ });\n  }\n  formal_power_series operator+(const formal_power_series &rhs) const\
    \ {\n    return formal_power_series([h0 = h_, h1 = rhs.h_](int i) { return h0(i)\
    \ + h1(i); });\n  }\n  formal_power_series operator-(const formal_power_series\
    \ &rhs) const {\n    return formal_power_series([h0 = h_, h1 = rhs.h_](int i)\
    \ { return h0(i) - h1(i); });\n  }\n  formal_power_series operator-() const {\n\
    \    return formal_power_series([h = h_](int i) { return -h(i); });\n  }\n  formal_power_series\
    \ operator*(const formal_power_series &rhs) const {\n    auto rc = std::make_shared<relaxed_convolution<ModIntT>>([h\
    \ = h_](int i) { return h(i); },\n                                           \
    \                  [h = rhs.h_](int i) { return h(i); });\n    return formal_power_series([rc](int)\
    \ { return rc->next(); });\n  }\n  formal_power_series operator/(const formal_power_series\
    \ &rhs) const {\n    auto rc = std::make_shared<relaxed_convolution<ModIntT>>(\n\
    \        [h0 = h_, h1 = rhs.h_, iv = ModIntT(), t0 = ModIntT()](int i, const auto\
    \ &c) mutable {\n          if (i == 0) t0 = h0(0) * (iv = h1(0).inv());\n    \
    \      return i == 0 ? t0 : (h0(i) - h1(i) * t0 - c[i]) * iv;\n        },\n  \
    \      [h = rhs.h_](int i) { return h(i); });\n    return formal_power_series([rc](int\
    \ i) { return rc->next(), rc->get_multiplicand()[i]; });\n  }\n  // P\xF3lya operator\
    \ Q = SEQUENCE(SEQ)\n  formal_power_series Q() const {\n    // `h_(0) != 0` is\
    \ not allowed.\n    return formal_power_series([h = h_](int i) { return i == 0\
    \ ? ModIntT(1) : -h(i); }).inv();\n  }\n  // P\xF3lya operator Exp = MULTISET(MSET)\n\
    \  formal_power_series Exp() const {\n    // `h_(0) != 0` is not allowed.\n  \
    \  formal_power_series res([h = h_, cache = std::make_shared<std::vector<ModIntT>>()](int\
    \ i) {\n      if (i == 0) return ModIntT();\n      if ((i & (i - 1)) == 0) {\n\
    \        cache->resize(i << 1);\n        for (int j = 1; j < i; ++j) {\n     \
    \     ModIntT hj(h(j));\n          for (int k = 2; j * k < i << 1; ++k)\n    \
    \        if (j * k >= i) cache->at(j * k) += hj * invs(k);\n        }\n      }\n\
    \      return cache->at(i) += h(i);\n    });\n    return res.exp();\n  }\n  //\
    \ P\xF3lya operator Exp(modified) = POWERSET(PSET)\n  formal_power_series Exp_m()\
    \ const {\n    // `h_(0) != 0` is not allowed.\n    formal_power_series res([h\
    \ = h_, cache = std::make_shared<std::vector<ModIntT>>()](int i) {\n      if (i\
    \ == 0) return ModIntT();\n      if ((i & (i - 1)) == 0) {\n        cache->resize(i\
    \ << 1);\n        for (int j = 1; j < i; ++j) {\n          ModIntT hj(h(j));\n\
    \          for (int k = 2; j * k < i << 1; ++k)\n            if (j * k >= i) {\n\
    \              if (k & 1) {\n                cache->at(j * k) += hj * invs(k);\n\
    \              } else {\n                cache->at(j * k) -= hj * invs(k);\n \
    \             }\n            }\n        }\n      }\n      return cache->at(i)\
    \ += h(i);\n    });\n    return res.exp();\n  }\n};\n\ntemplate <typename ModIntT>\n\
    typename detail::modular_inverse<ModIntT> formal_power_series<ModIntT>::invs;\n\
    \ntemplate <typename ModIntT>\nusing fps = formal_power_series<ModIntT>;\n\nLIB_END\n\
    \n\n"
  code: "#ifndef FORMAL_POWER_SERIES\n#define FORMAL_POWER_SERIES\n\n#include \"../common.hpp\"\
    \n#include \"extended_gcd.hpp\"\n#include \"radix2_ntt.hpp\"\n#include \"relaxed_convolution.hpp\"\
    \n\n#include <functional>\n#include <memory>\n#include <optional>\n#include <type_traits>\n\
    #include <vector>\n\nLIB_BEGIN\n\ntemplate <typename ModIntT>\nclass formal_power_series\
    \ {\n  using F = std::function<ModIntT(int)>;\n  F h_;\n\n  static typename detail::modular_inverse<ModIntT>\
    \ invs;\n\npublic:\n  formal_power_series() : h_([](int) { return ModIntT(); })\
    \ {}\n  explicit formal_power_series(F f)\n      : h_([f, cache = std::make_shared<std::vector<ModIntT>>()](int\
    \ k) {\n          for (int i = static_cast<int>(cache->size()); i <= k; ++i) cache->emplace_back(f(i));\n\
    \          return ModIntT(cache->at(k));\n        }) {}\n  explicit formal_power_series(const\
    \ std::vector<ModIntT> &coeff)\n      : h_([cache = std::make_shared<std::vector<ModIntT>>(coeff)](int\
    \ k) {\n          return k < static_cast<int>(cache->size()) ? ModIntT(cache->at(k))\
    \ : ModIntT();\n        }) {}\n  formal_power_series(ModIntT v) : h_([v](int k)\
    \ { return k == 0 ? v : ModIntT(); }) {}\n  F handle() const { return h_; }\n\
    \  ModIntT operator[](int k) const { return h_(k); }\n  formal_power_series scale(int\
    \ k) const {\n    return formal_power_series([h = h_, k](int i) { return i % k\
    \ == 0 ? h(i / k) : ModIntT(); });\n  }\n  formal_power_series shift(int k) const\
    \ {\n    return formal_power_series([h = h_, k](int i) { return i - k < 0 ? ModIntT()\
    \ : h(i - k); });\n  }\n  formal_power_series deriv() const {\n    return formal_power_series([h\
    \ = h_](int i) { return h(i + 1) * (i + 1); });\n  }\n  formal_power_series integr(ModIntT\
    \ c = ModIntT()) const {\n    return formal_power_series([h = h_, c](int i) {\
    \ return i == 0 ? c : h(i - 1) * invs(i); });\n  }\n  formal_power_series inv()\
    \ const {\n    auto rc = std::make_shared<relaxed_convolution<ModIntT>>(\n   \
    \     [h = h_](int i) { return h(i); },\n        [h = h_, iv = ModIntT()](int\
    \ i, const auto &c) mutable {\n          return i == 0 ? ModIntT(iv = h(0).inv())\
    \ : -(c[i] + h(i) * iv) * iv;\n        });\n    return formal_power_series([rc](int\
    \ i) { return rc->next(), rc->get_multiplier()[i]; });\n  }\n  formal_power_series\
    \ exp() const {\n    auto rc = std::make_shared<relaxed_convolution<ModIntT>>(\n\
    \        [h = h_](int i) { return h(i + 1) * (i + 1); },\n        [](int i, const\
    \ auto &c) { return i == 0 ? ModIntT(1) : c[i - 1] * invs(i); });\n    return\
    \ formal_power_series(\n        [rc](int i) { return i == 0 ? ModIntT(1) : rc->at(i\
    \ - 1) * invs(i); });\n  }\n  formal_power_series log() const { return (deriv()\
    \ / (*this)).integr(); }\n  formal_power_series pow(int k) const {\n    return\
    \ formal_power_series(\n        [h = h_, kk = ModIntT(k), k, zero_cnt = 0ull,\
    \ s = std::optional<F>()](int i) mutable {\n          if (s) return i < zero_cnt\
    \ ? ModIntT() : (*s)(i - zero_cnt);\n          ModIntT v(h(i));\n          if\
    \ (v.is_zero()) return ++zero_cnt, ModIntT();\n          zero_cnt *= k;\n    \
    \      formal_power_series t0([os = i, iv = v.inv(), h](int i) { return h(i +\
    \ os) * iv; });\n          formal_power_series t1([h0 = t0.log().handle(), kk](int\
    \ i) { return h0(i) * kk; });\n          s.emplace([vk = v.pow(k), h1 = t1.exp().handle()](int\
    \ i) { return h1(i) * vk; });\n          return zero_cnt == 0 ? (*s)(i) : ModIntT();\n\
    \        });\n  }\n  template <typename SqrtFuncT,\n            typename std::enable_if_t<std::is_invocable_r_v<ModIntT,\
    \ SqrtFuncT, ModIntT>, int> = 0>\n  formal_power_series sqrt(SqrtFuncT &&f) const\
    \ {\n    // `h_(0) == 0` is not allowed.\n    auto t = [h = h_, f, i2 = ModIntT()](int\
    \ i, auto const &c) mutable {\n      if (i != 0) return (h(i) - c[i]) * i2;\n\
    \      ModIntT fi(f(h(i)));\n      i2 = (fi * ModIntT(2)).inv();\n      return\
    \ fi;\n    };\n    auto rc = std::make_shared<relaxed_convolution<ModIntT>>(t,\
    \ t);\n    return formal_power_series([rc](int i) { return rc->next(), rc->get_multiplier()[i];\
    \ });\n  }\n  formal_power_series operator+(const formal_power_series &rhs) const\
    \ {\n    return formal_power_series([h0 = h_, h1 = rhs.h_](int i) { return h0(i)\
    \ + h1(i); });\n  }\n  formal_power_series operator-(const formal_power_series\
    \ &rhs) const {\n    return formal_power_series([h0 = h_, h1 = rhs.h_](int i)\
    \ { return h0(i) - h1(i); });\n  }\n  formal_power_series operator-() const {\n\
    \    return formal_power_series([h = h_](int i) { return -h(i); });\n  }\n  formal_power_series\
    \ operator*(const formal_power_series &rhs) const {\n    auto rc = std::make_shared<relaxed_convolution<ModIntT>>([h\
    \ = h_](int i) { return h(i); },\n                                           \
    \                  [h = rhs.h_](int i) { return h(i); });\n    return formal_power_series([rc](int)\
    \ { return rc->next(); });\n  }\n  formal_power_series operator/(const formal_power_series\
    \ &rhs) const {\n    auto rc = std::make_shared<relaxed_convolution<ModIntT>>(\n\
    \        [h0 = h_, h1 = rhs.h_, iv = ModIntT(), t0 = ModIntT()](int i, const auto\
    \ &c) mutable {\n          if (i == 0) t0 = h0(0) * (iv = h1(0).inv());\n    \
    \      return i == 0 ? t0 : (h0(i) - h1(i) * t0 - c[i]) * iv;\n        },\n  \
    \      [h = rhs.h_](int i) { return h(i); });\n    return formal_power_series([rc](int\
    \ i) { return rc->next(), rc->get_multiplicand()[i]; });\n  }\n  // P\xF3lya operator\
    \ Q = SEQUENCE(SEQ)\n  formal_power_series Q() const {\n    // `h_(0) != 0` is\
    \ not allowed.\n    return formal_power_series([h = h_](int i) { return i == 0\
    \ ? ModIntT(1) : -h(i); }).inv();\n  }\n  // P\xF3lya operator Exp = MULTISET(MSET)\n\
    \  formal_power_series Exp() const {\n    // `h_(0) != 0` is not allowed.\n  \
    \  formal_power_series res([h = h_, cache = std::make_shared<std::vector<ModIntT>>()](int\
    \ i) {\n      if (i == 0) return ModIntT();\n      if ((i & (i - 1)) == 0) {\n\
    \        cache->resize(i << 1);\n        for (int j = 1; j < i; ++j) {\n     \
    \     ModIntT hj(h(j));\n          for (int k = 2; j * k < i << 1; ++k)\n    \
    \        if (j * k >= i) cache->at(j * k) += hj * invs(k);\n        }\n      }\n\
    \      return cache->at(i) += h(i);\n    });\n    return res.exp();\n  }\n  //\
    \ P\xF3lya operator Exp(modified) = POWERSET(PSET)\n  formal_power_series Exp_m()\
    \ const {\n    // `h_(0) != 0` is not allowed.\n    formal_power_series res([h\
    \ = h_, cache = std::make_shared<std::vector<ModIntT>>()](int i) {\n      if (i\
    \ == 0) return ModIntT();\n      if ((i & (i - 1)) == 0) {\n        cache->resize(i\
    \ << 1);\n        for (int j = 1; j < i; ++j) {\n          ModIntT hj(h(j));\n\
    \          for (int k = 2; j * k < i << 1; ++k)\n            if (j * k >= i) {\n\
    \              if (k & 1) {\n                cache->at(j * k) += hj * invs(k);\n\
    \              } else {\n                cache->at(j * k) -= hj * invs(k);\n \
    \             }\n            }\n        }\n      }\n      return cache->at(i)\
    \ += h(i);\n    });\n    return res.exp();\n  }\n};\n\ntemplate <typename ModIntT>\n\
    typename detail::modular_inverse<ModIntT> formal_power_series<ModIntT>::invs;\n\
    \ntemplate <typename ModIntT>\nusing fps = formal_power_series<ModIntT>;\n\nLIB_END\n\
    \n#endif"
  dependsOn:
  - common.hpp
  - math/extended_gcd.hpp
  - math/radix2_ntt.hpp
  - math/relaxed_convolution.hpp
  isVerificationFile: false
  path: math/formal_power_series.hpp
  requiredBy: []
  timestamp: '2022-05-15 15:19:08+08:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/sharp_p_subset_sum.0.test.cpp
  - remote_test/yosupo/math/exp_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/partition_function.0.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/pow_of_formal_power_series.0.test.cpp
documentation_of: math/formal_power_series.hpp
layout: document
title: Formal Power Series (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack \rbrack$
  for FFT prime $p$)
---

I got wrong answer when I was testing my library locally. Check [Wandbox](https://wandbox.org/permlink/smgnVZ0lcZvk6ZYJ). It seems okay when compiling with Clang.

The reason I found was the lambda expression in `main` function, but I don't know why.