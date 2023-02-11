---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: math/radix2_ntt.hpp
    title: Radix-2 NTT (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/convolution_mod.2.test.cpp
    title: remote_test/yosupo/math/convolution_mod.2.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/czt.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\n\n#define\
    \ LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n#define LIB\
    \ ::lib::\n\n\n#line 1 \"math/radix2_ntt.hpp\"\n\n\n\n#line 5 \"math/radix2_ntt.hpp\"\
    \n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#include <type_traits>\n\
    #include <vector>\n\nLIB_BEGIN\n\nnamespace detail {\n\ntemplate <typename IntT>\n\
    constexpr std::enable_if_t<std::is_integral_v<IntT>, int> bsf(IntT v) {\n  if\
    \ (static_cast<std::make_signed_t<IntT>>(v) <= 0) return -1;\n  int res = 0;\n\
    \  for (; (v & 1) == 0; ++res) v >>= 1;\n  return res;\n}\n\ntemplate <typename\
    \ ModIntT>\nconstexpr ModIntT quadratic_nonresidue_prime() {\n  auto mod = ModIntT::mod();\n\
    \  for (int i = 2;; ++i)\n    if (ModIntT(i).pow(mod >> 1) == mod - 1) return\
    \ ModIntT(i);\n}\n\ntemplate <typename ModIntT>\nconstexpr ModIntT gen_of_sylow_2_subgroup()\
    \ {\n  auto mod = ModIntT::mod();\n  return quadratic_nonresidue_prime<ModIntT>().pow(mod\
    \ >> bsf(mod - 1));\n}\n\ntemplate <typename ModIntT>\nconstexpr std::array<ModIntT,\
    \ bsf(ModIntT::mod() - 1) - 1> root() {\n  std::array<ModIntT, bsf(ModIntT::mod()\
    \ - 1) - 1> rt; // order(`rt[i]`) = 2^(i + 2).\n  rt.back() = gen_of_sylow_2_subgroup<ModIntT>();\n\
    \  for (int i = bsf(ModIntT::mod() - 1) - 3; i >= 0; --i) rt[i] = rt[i + 1] *\
    \ rt[i + 1];\n  return rt;\n}\n\ntemplate <typename ModIntT>\nconstexpr std::array<ModIntT,\
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
    \  return a_cpy;\n}\n\nLIB_END\n\n\n"
  code: "#ifndef CZT_HPP\n#define CZT_HPP\n\n#include \"../common.hpp\"\n#include\
    \ \"radix2_ntt.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include <numeric>\n\
    #include <vector>\n\nLIB_BEGIN\n\n// Chirp Z-transform\n// Input:  A(x) = `a[0]`\
    \ + `a[1]`x + ..., constant `c`, and integer `n`.\n// Output: [A(1), A(c), A(c^2),\
    \ ..., A(c^(n - 1))].\ntemplate <typename ModIntT>\nstd::vector<ModIntT> czt(const\
    \ std::vector<ModIntT> &a, const ModIntT &c, int n) {\n  assert(n >= 0);\n  if\
    \ (n == 0) return {};\n  int m = static_cast<int>(a.size());\n  while (m > 0 &&\
    \ a[m - 1].is_zero()) --m;\n  if (m == 0) return std::vector<ModIntT>(n);\n  if\
    \ (c.is_zero()) {\n    std::vector<ModIntT> res(n, a.front());\n    res.front()\
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
    \  return a_cpy;\n}\n\nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  - math/radix2_ntt.hpp
  isVerificationFile: false
  path: math/czt.hpp
  requiredBy: []
  timestamp: '2022-04-26 19:23:58+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/convolution_mod.2.test.cpp
documentation_of: math/czt.hpp
layout: document
title: Chirp Z-transform (Bluestein's algorithm) (in $\mathbb{F} _ p \lbrack z \rbrack$
  for FFT prime $p$)
---
