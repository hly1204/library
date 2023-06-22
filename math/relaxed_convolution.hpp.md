---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':question:'
    path: math/radix2_ntt.hpp
    title: Radix-2 NTT (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/formal_power_series.hpp
    title: Formal Power Series (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack \rbrack$
      for FFT prime $p$)
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.3.test.cpp
    title: remote_test/yosupo/math/convolution_mod.3.test.cpp
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
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/pow_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/pow_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/sharp_p_subset_sum.0.test.cpp
    title: remote_test/yosupo/math/sharp_p_subset_sum.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/relaxed_convolution.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
    \n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 1 \"math/radix2_ntt.hpp\"\n\n\n\n#line 5 \"\
    math/radix2_ntt.hpp\"\n\n#include <algorithm>\n#include <array>\n#include <cassert>\n\
    #include <type_traits>\n#include <vector>\n\nLIB_BEGIN\n\nnamespace detail {\n\
    \ntemplate <typename IntT>\nconstexpr std::enable_if_t<std::is_integral_v<IntT>,\
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
    \ is NOT optimal and NOT lazy enough so IT IS SLOW.\ntemplate <typename ModIntT>\n\
    class relaxed_convolution {                       // O(n log^2 n) impl\n  std::vector<ModIntT>\
    \ a_{}, b_{}, c_{};          // `a_ * b_` = `c_`\n  std::vector<std::vector<ModIntT>>\
    \ ac_{}, bc_{}; // cached DFTs\n  std::function<ModIntT()> ha_{}, hb_{};     \
    \     // handle for `a_` and `b_`\n  int n_{};                               \
    \        // counter\n\n  template <typename FnT,\n            typename std::enable_if_t<\n\
    \                std::is_invocable_r_v<ModIntT, FnT, int, const std::vector<ModIntT>\
    \ &>, int> = 0>\n  static auto wrap(FnT &&f, int &n, const std::vector<ModIntT>\
    \ &c, std::vector<ModIntT> &e) {\n    return [f, &n, &c, &e]() mutable { return\
    \ e.emplace_back(f(n, c)); };\n  }\n  template <typename FnT,\n            typename\
    \ std::enable_if_t<std::is_invocable_r_v<ModIntT, FnT, int>, int> = 0>\n  static\
    \ auto wrap(FnT &&f, int &n, const std::vector<ModIntT> &, std::vector<ModIntT>\
    \ &e) {\n    return [f, &n, &e]() mutable { return e.emplace_back(f(n)); };\n\
    \  }\n  template <typename FnT, typename std::enable_if_t<std::is_invocable_r_v<ModIntT,\
    \ FnT>, int> = 0>\n  static auto wrap(FnT &&f, int &, const std::vector<ModIntT>\
    \ &, std::vector<ModIntT> &e) {\n    return [f, &e]() mutable { return e.emplace_back(f());\
    \ };\n  }\n\n  enum : int { BASE_CASE_SIZE = 32 };\n\n  static_assert((BASE_CASE_SIZE\
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
    LIB_END\n\n\n"
  code: "#ifndef RELAXED_CONVOLUTION_HPP\n#define RELAXED_CONVOLUTION_HPP\n\n#include\
    \ \"../common.hpp\"\n#include \"radix2_ntt.hpp\"\n\n#include <exception>\n#include\
    \ <functional>\n#include <type_traits>\n#include <utility>\n#include <vector>\n\
    \nLIB_BEGIN\n\n// This implementation is NOT optimal and NOT lazy enough so IT\
    \ IS SLOW.\ntemplate <typename ModIntT>\nclass relaxed_convolution {         \
    \              // O(n log^2 n) impl\n  std::vector<ModIntT> a_{}, b_{}, c_{};\
    \          // `a_ * b_` = `c_`\n  std::vector<std::vector<ModIntT>> ac_{}, bc_{};\
    \ // cached DFTs\n  std::function<ModIntT()> ha_{}, hb_{};          // handle\
    \ for `a_` and `b_`\n  int n_{};                                       // counter\n\
    \n  template <typename FnT,\n            typename std::enable_if_t<\n        \
    \        std::is_invocable_r_v<ModIntT, FnT, int, const std::vector<ModIntT> &>,\
    \ int> = 0>\n  static auto wrap(FnT &&f, int &n, const std::vector<ModIntT> &c,\
    \ std::vector<ModIntT> &e) {\n    return [f, &n, &c, &e]() mutable { return e.emplace_back(f(n,\
    \ c)); };\n  }\n  template <typename FnT,\n            typename std::enable_if_t<std::is_invocable_r_v<ModIntT,\
    \ FnT, int>, int> = 0>\n  static auto wrap(FnT &&f, int &n, const std::vector<ModIntT>\
    \ &, std::vector<ModIntT> &e) {\n    return [f, &n, &e]() mutable { return e.emplace_back(f(n));\
    \ };\n  }\n  template <typename FnT, typename std::enable_if_t<std::is_invocable_r_v<ModIntT,\
    \ FnT>, int> = 0>\n  static auto wrap(FnT &&f, int &, const std::vector<ModIntT>\
    \ &, std::vector<ModIntT> &e) {\n    return [f, &e]() mutable { return e.emplace_back(f());\
    \ };\n  }\n\n  enum : int { BASE_CASE_SIZE = 32 };\n\n  static_assert((BASE_CASE_SIZE\
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
    LIB_END\n\n#endif\n"
  dependsOn:
  - common.hpp
  - math/radix2_ntt.hpp
  isVerificationFile: false
  path: math/relaxed_convolution.hpp
  requiredBy:
  - math/formal_power_series.hpp
  timestamp: '2023-02-11 14:43:28+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/partition_function.0.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/pow_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/log_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/sharp_p_subset_sum.0.test.cpp
  - remote_test/yosupo/math/exp_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/convolution_mod.3.test.cpp
documentation_of: math/relaxed_convolution.hpp
layout: document
title: Relaxed Convolution (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack \rbrack$
  for FFT prime $p$)
---

My implementation is NOT optimal. One may want to use the "middle product" trick and divide the problem into more subproblems to improve the efficiency. I don't want to improve my implementation.

## Bibliography

1. Romain Lebreton, Éric Schost. [A simple and fast online power series multiplication and its analysis](https://www.sciencedirect.com/science/article/pii/S0747717115000176).
2. J. van der Hoeven. [New algorithms for relaxed multiplication](http://www.texmacs.org/joris/newrelax/newrelax.html).
