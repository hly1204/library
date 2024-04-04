---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: math/radix2_ntt.hpp
    title: Radix-2 NTT (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  - icon: ':heavy_check_mark:'
    path: math/zeta_transform.hpp
    title: Zeta Transform
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/subset_convolution.0.test.cpp
    title: remote_test/yosupo/math/subset_convolution.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://codeforces.com/blog/entry/126418
  bundledCode: "#line 1 \"math/set_power_series.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
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
    \n\n#line 1 \"math/zeta_transform.hpp\"\n\n\n\n#line 5 \"math/zeta_transform.hpp\"\
    \n\n#line 8 \"math/zeta_transform.hpp\"\n\n#ifdef _MSC_VER\n  #include <intrin.h>\n\
    #endif\n\nLIB_BEGIN\n\nint popcount(unsigned int c) {\n#ifdef _MSC_VER\n  return\
    \ __popcnt(c);\n#else\n  return __builtin_popcount(c);\n#endif\n}\n\nint popcount(unsigned\
    \ long c) {\n#ifdef _MSC_VER\n  return sizeof(unsigned long) == 8 ? __popcnt64(c)\
    \ : __popcnt(c);\n#else\n  return __builtin_popcountl(c);\n#endif\n}\n\nint popcount(unsigned\
    \ long long c) {\n#ifdef _MSC_VER\n  return __popcnt64(c);\n#else\n  return __builtin_popcountll(c);\n\
    #endif\n}\n\n// Input:           f(x) = `a[0]` + `a[1]`x_1 + ... + `a[n - 1]`x_1...x_n.\n\
    // Output(inplace): [f mod (x_1,...,x_n), f mod (x_1-1,x_2,...,x_n), ..., f mod\
    \ (x_1-1,...,x_n-1)].\ntemplate <typename ModIntT>\nvoid zeta_transform(std::vector<ModIntT>\
    \ &x) {\n  const int n = static_cast<int>(x.size());\n  assert((n & (n - 1)) ==\
    \ 0);\n  // assume a + b = b + a\n  for (int i = 1; i < n; i <<= 1)\n    for (int\
    \ j = i; j < n; j = (j + 1) | i) x[j] += x[j ^ i];\n}\n\n// Input:           [f\
    \ mod (x_1,...,x_n), f mod (x_1-1,x_2,...,x_n), ..., f mod (x_1-1,...,x_n-1)].\n\
    // Output(inplace): f(x) = `a[0]` + `a[1]`x_1 + ... + `a[n - 1]`x_1...x_n.\ntemplate\
    \ <typename ModIntT>\nvoid moebius_transform(std::vector<ModIntT> &x) {\n  const\
    \ int n = static_cast<int>(x.size());\n  assert((n & (n - 1)) == 0);\n  // assume\
    \ a + b = b + a\n  for (int i = n >> 1; i != 0; i >>= 1)\n    for (int j = i;\
    \ j < n; j = (j + 1) | i) x[j] -= x[j ^ i];\n}\n\nLIB_END\n\n\n#line 7 \"math/set_power_series.hpp\"\
    \n\n#line 10 \"math/set_power_series.hpp\"\n\nLIB_BEGIN\n\nstruct set_power_series\
    \ {\n  set_power_series() = delete;\n\n  template <typename ModIntT>\n  static\
    \ std::vector<std::vector<ModIntT>> add_rank(const std::vector<ModIntT> &x) {\n\
    \    const int n = static_cast<int>(x.size());\n    assert((n & (n - 1)) == 0);\n\
    \    const int rank = detail::bsf(x.size()) + 1;\n    std::vector rz(rank, std::vector<ModIntT>(x.size()));\n\
    \    for (int i = 0; i != n; ++i) rz[popcount(static_cast<unsigned>(i))][i] =\
    \ x[i];\n    return rz;\n  }\n\n  template <typename ModIntT>\n  static std::vector<ModIntT>\
    \ remove_rank(const std::vector<std::vector<ModIntT>> &x) {\n    const int rank\
    \ = static_cast<int>(x.size());\n    assert(rank != 0);\n    const int n = static_cast<int>(x.front().size());\n\
    \    assert((n & (n - 1)) == 0);\n    std::vector<ModIntT> z(n);\n    for (int\
    \ i = 0; i != n; ++i) z[i] = x[popcount(static_cast<unsigned>(i))][i];\n    return\
    \ z;\n  }\n\n  template <typename ModIntT>\n  static std::vector<ModIntT> subset_convolution(const\
    \ std::vector<ModIntT> &x,\n                                                 const\
    \ std::vector<ModIntT> &y) {\n    // https://codeforces.com/blog/entry/126418\n\
    \    // 0 -> 1 -> 3 -> 7 -> 15\n    // 2 -> 5 -> 11\n    // ...\n    static const\
    \ int map[] = {0, 0, 1, 0, 2, 1, 3, 0, 4,  2, 5,  1,\n                       \
    \       6, 3, 7, 0, 8, 4, 9, 2, 10, 5, 11, 1};\n\n    const int n = static_cast<int>(x.size());\n\
    \n    assert(static_cast<int>(y.size()) == n);\n    auto rx        = add_rank(x);\n\
    \    auto ry        = add_rank(y);\n    const int rank = static_cast<int>(rx.size());\n\
    \    for (auto &&i : rx) zeta_transform(i);\n    for (auto &&i : ry) zeta_transform(i);\n\
    \n    std::vector<std::vector<ModIntT>> rxy(rank / 2 + 1, std::vector<ModIntT>(x.size()));\n\
    \n    for (int i = 0; i != rank; ++i)\n      for (int j = i; j >= 0; --j)\n  \
    \      for (int k = 0; k != n; ++k) rxy[map[i]][k] += rx[j][k] * ry[i - j][k];\n\
    \n    for (auto &&i : rxy) moebius_transform(i);\n    std::vector<ModIntT> res(n);\n\
    \    for (int i = 0; i != n; ++i) res[i] = rxy[map[popcount(static_cast<unsigned>(i))]][i];\n\
    \    return res;\n  }\n};\n\nLIB_END\n\n\n"
  code: "#ifndef SUBSET_CONVOLUTION_HPP\n#define SUBSET_CONVOLUTION_HPP\n\n#include\
    \ \"../common.hpp\"\n#include \"radix2_ntt.hpp\"\n#include \"zeta_transform.hpp\"\
    \n\n#include <cassert>\n#include <vector>\n\nLIB_BEGIN\n\nstruct set_power_series\
    \ {\n  set_power_series() = delete;\n\n  template <typename ModIntT>\n  static\
    \ std::vector<std::vector<ModIntT>> add_rank(const std::vector<ModIntT> &x) {\n\
    \    const int n = static_cast<int>(x.size());\n    assert((n & (n - 1)) == 0);\n\
    \    const int rank = detail::bsf(x.size()) + 1;\n    std::vector rz(rank, std::vector<ModIntT>(x.size()));\n\
    \    for (int i = 0; i != n; ++i) rz[popcount(static_cast<unsigned>(i))][i] =\
    \ x[i];\n    return rz;\n  }\n\n  template <typename ModIntT>\n  static std::vector<ModIntT>\
    \ remove_rank(const std::vector<std::vector<ModIntT>> &x) {\n    const int rank\
    \ = static_cast<int>(x.size());\n    assert(rank != 0);\n    const int n = static_cast<int>(x.front().size());\n\
    \    assert((n & (n - 1)) == 0);\n    std::vector<ModIntT> z(n);\n    for (int\
    \ i = 0; i != n; ++i) z[i] = x[popcount(static_cast<unsigned>(i))][i];\n    return\
    \ z;\n  }\n\n  template <typename ModIntT>\n  static std::vector<ModIntT> subset_convolution(const\
    \ std::vector<ModIntT> &x,\n                                                 const\
    \ std::vector<ModIntT> &y) {\n    // https://codeforces.com/blog/entry/126418\n\
    \    // 0 -> 1 -> 3 -> 7 -> 15\n    // 2 -> 5 -> 11\n    // ...\n    static const\
    \ int map[] = {0, 0, 1, 0, 2, 1, 3, 0, 4,  2, 5,  1,\n                       \
    \       6, 3, 7, 0, 8, 4, 9, 2, 10, 5, 11, 1};\n\n    const int n = static_cast<int>(x.size());\n\
    \n    assert(static_cast<int>(y.size()) == n);\n    auto rx        = add_rank(x);\n\
    \    auto ry        = add_rank(y);\n    const int rank = static_cast<int>(rx.size());\n\
    \    for (auto &&i : rx) zeta_transform(i);\n    for (auto &&i : ry) zeta_transform(i);\n\
    \n    std::vector<std::vector<ModIntT>> rxy(rank / 2 + 1, std::vector<ModIntT>(x.size()));\n\
    \n    for (int i = 0; i != rank; ++i)\n      for (int j = i; j >= 0; --j)\n  \
    \      for (int k = 0; k != n; ++k) rxy[map[i]][k] += rx[j][k] * ry[i - j][k];\n\
    \n    for (auto &&i : rxy) moebius_transform(i);\n    std::vector<ModIntT> res(n);\n\
    \    for (int i = 0; i != n; ++i) res[i] = rxy[map[popcount(static_cast<unsigned>(i))]][i];\n\
    \    return res;\n  }\n};\n\nLIB_END\n\n#endif\n"
  dependsOn:
  - common.hpp
  - math/radix2_ntt.hpp
  - math/zeta_transform.hpp
  isVerificationFile: false
  path: math/set_power_series.hpp
  requiredBy: []
  timestamp: '2024-02-28 21:37:45+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/subset_convolution.0.test.cpp
documentation_of: math/set_power_series.hpp
layout: document
title: Set Power Series
---
