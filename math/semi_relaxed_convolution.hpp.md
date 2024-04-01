---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: math/radix2_ntt.hpp
    title: Radix-2 NTT (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/enum_kth_term_of_power.hpp
    title: math/enum_kth_term_of_power.hpp
  - icon: ':heavy_check_mark:'
    path: math/fps_composition.hpp
    title: Enumeration of $k$-th Term of Power of Formal Power Series (in $\mathbb{F}
      _ p \lbrack \lbrack z \rbrack \rbrack$ for FFT prime $p$)
  - icon: ':heavy_check_mark:'
    path: math/polynomial.hpp
    title: Polynomial (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  - icon: ':heavy_check_mark:'
    path: math/truncated_formal_power_series.hpp
    title: Truncated Formal Power Series (in $\mathbb{F} _ p \lbrack \lbrack z \rbrack
      \rbrack$ for FFT prime $p$)
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/composition_of_formal_power_series_large.0.test.cpp
    title: remote_test/yosupo/math/composition_of_formal_power_series_large.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/compositional_inverse_of_formal_power_series_large.0.test.cpp
    title: remote_test/yosupo/math/compositional_inverse_of_formal_power_series_large.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.1.test.cpp
    title: remote_test/yosupo/math/convolution_mod.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
    title: remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
    title: remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
    title: remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
    title: remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
    title: remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
    title: remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
    title: remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
    title: remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
    title: remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
    title: remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/semi_relaxed_convolution.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
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
    \n\n#line 6 \"math/semi_relaxed_convolution.hpp\"\n\n#line 9 \"math/semi_relaxed_convolution.hpp\"\
    \n#include <utility>\n#line 11 \"math/semi_relaxed_convolution.hpp\"\n\nLIB_BEGIN\n\
    \ntemplate <typename ModIntT, typename FnT>\nclass semi_relaxed_convolution {\n\
    \  std::vector<ModIntT> fixed_A_{}, B_{}, c_{};\n  std::vector<std::vector<std::vector<ModIntT>>>\
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
    \ VectorT::value_type, std::decay_t<ClosureT>>;\n\nLIB_END\n\n\n"
  code: "#ifndef SEMI_RELAXED_CONVOLUTION_HPP\n#define SEMI_RELAXED_CONVOLUTION_HPP\n\
    \n#include \"../common.hpp\"\n#include \"radix2_ntt.hpp\"\n\n#include <algorithm>\n\
    #include <type_traits>\n#include <utility>\n#include <vector>\n\nLIB_BEGIN\n\n\
    template <typename ModIntT, typename FnT>\nclass semi_relaxed_convolution {\n\
    \  std::vector<ModIntT> fixed_A_{}, B_{}, c_{};\n  std::vector<std::vector<std::vector<ModIntT>>>\
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
    \ VectorT::value_type, std::decay_t<ClosureT>>;\n\nLIB_END\n\n#endif\n"
  dependsOn:
  - common.hpp
  - math/radix2_ntt.hpp
  isVerificationFile: false
  path: math/semi_relaxed_convolution.hpp
  requiredBy:
  - math/fps_composition.hpp
  - math/truncated_formal_power_series.hpp
  - math/enum_kth_term_of_power.hpp
  - math/polynomial.hpp
  timestamp: '2023-12-17 11:51:45+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/convolution_mod.1.test.cpp
  - remote_test/yosupo/math/stirling_number_of_the_second_kind.0.test.cpp
  - remote_test/yosupo/math/pow_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/composition_of_formal_power_series_large.0.test.cpp
  - remote_test/yosupo/math/stirling_number_of_the_first_kind.0.test.cpp
  - remote_test/yosupo/math/inv_of_formal_power_series.2.test.cpp
  - remote_test/yosupo/math/sqrt_of_formal_power_series.0.test.cpp
  - remote_test/yosupo/math/multipoint_evaluation.0.test.cpp
  - remote_test/yosupo/math/polynomial_interpolation.0.test.cpp
  - remote_test/yosupo/math/inv_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/division_of_polynomials.0.test.cpp
  - remote_test/yosupo/math/polynomial_taylor_shift.0.test.cpp
  - remote_test/yosupo/math/exp_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/log_of_formal_power_series.1.test.cpp
  - remote_test/yosupo/math/compositional_inverse_of_formal_power_series_large.0.test.cpp
documentation_of: math/semi_relaxed_convolution.hpp
layout: document
title: Semi-Relaxed Convolution (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime
  $p$)
---
