---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':question:'
    path: math/radix2_ntt.hpp
    title: Radix-2 NTT (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  - icon: ':heavy_check_mark:'
    path: math/truncated_fourier_transform.hpp
    title: Truncated Fourier Transform (in $\mathbb{F} _ p \lbrack z \rbrack$ for
      FFT prime $p$)
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: remote_test/yosupo/math/multivariate_convolution.0.test.cpp
    title: remote_test/yosupo/math/multivariate_convolution.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/multivariate_convolution.hpp\"\n\n\n\n#line 1 \"common.hpp\"\
    \n\n\n\n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END\
    \ }\n#define LIB ::lib::\n\n\n#line 1 \"math/truncated_fourier_transform.hpp\"\
    \n\n\n\n#line 1 \"math/radix2_ntt.hpp\"\n\n\n\n#line 5 \"math/radix2_ntt.hpp\"\
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
    \n\n#line 6 \"math/truncated_fourier_transform.hpp\"\n\n#line 8 \"math/truncated_fourier_transform.hpp\"\
    \n#include <utility>\n#line 10 \"math/truncated_fourier_transform.hpp\"\n\nLIB_BEGIN\n\
    \ntemplate <typename ContainerT>\nvoid tft(ContainerT &&a) {\n  using Container\
    \          = std::decay_t<ContainerT>;\n  using T                  = typename\
    \ Container::value_type;\n  static constexpr auto rt = detail::root<T>();\n  static\
    \ std::vector<T> root(1);\n  const int n = static_cast<int>(a.size());\n  if ((n\
    \ & (n - 1)) == 0) return dft(std::forward<ContainerT>(a));\n  const int len =\
    \ ntt_len(n);\n  if (int s = static_cast<int>(root.size()); s << 1 < len) {\n\
    \    root.resize(len >> 1);\n    for (int i = detail::bsf(s), j; 1 << i < len\
    \ >> 1; ++i) {\n      root[j = 1 << i] = rt[i];\n      for (int k = j + 1; k <\
    \ j << 1; ++k) root[k] = root[k - j] * root[j];\n    }\n  }\n  a.resize(len);\n\
    \  for (int j = 0, l = len >> 1; j != l; ++j) {\n    T u(a[j]), v(a[j + l]);\n\
    \    a[j] = u + v, a[j + l] = u - v;\n  }\n  for (int i = len >> 1; i >= 2; i\
    \ >>= 1) {\n    for (int j = 0, l = i >> 1; j != l; ++j) {\n      T u(a[j]), v(a[j\
    \ + l]);\n      a[j] = u + v, a[j + l] = u - v;\n    }\n    for (int j = i, l\
    \ = i >> 1, m = 1; j < n && j != len; j += i, ++m)\n      for (int k = j; k !=\
    \ j + l; ++k) {\n        T u(a[k]), v(a[k + l] * root[m]);\n        a[k] = u +\
    \ v, a[k + l] = u - v;\n      }\n  }\n  a.resize(n);\n}\n\ntemplate <typename\
    \ ContainerT>\nvoid itft(ContainerT &&a) {\n  using Container           = std::decay_t<ContainerT>;\n\
    \  using T                   = typename Container::value_type;\n  static constexpr\
    \ auto rt  = detail::root<T>();\n  static constexpr auto irt = detail::iroot<T>();\n\
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
    \  } rec(a);\n  rec.run(0, n, len);\n  a.resize(n);\n}\n\nLIB_END\n\n\n#line 6\
    \ \"math/multivariate_convolution.hpp\"\n\n#line 10 \"math/multivariate_convolution.hpp\"\
    \n\nLIB_BEGIN\n\ntemplate <typename ModIntT>\nstd::vector<ModIntT> multivariate_convolution(const\
    \ std::vector<ModIntT> &lhs,\n                                              const\
    \ std::vector<ModIntT> &rhs,\n                                              const\
    \ std::vector<int> n) {\n  const int d  = std::max(1, static_cast<int>(n.size()));\n\
    \  const int ls = static_cast<int>(lhs.size());\n  assert(rhs.size() == ls);\n\
    \  const int len = (ls << 1) - 1; // slower than using `ls << 1`.\n  std::vector<int>\
    \ base(d - 1);\n  if (d > 1) base.front() = n.front();\n  for (int i = 1; i <\
    \ d - 1; ++i) base[i] = base[i - 1] * n[i];\n  auto chi_mod = [&base, d](int i)\
    \ {\n    int x = 0;\n    for (int v : base) x += i / v;\n    return x % d;\n \
    \ };\n  std::vector<int> chi(ls);\n  for (int i = 0; i != ls; ++i) chi[i] = chi_mod(i);\n\
    \  std::vector<std::vector<ModIntT>> a(d, std::vector<ModIntT>(len)),\n      b(d,\
    \ std::vector<ModIntT>(len)), ab(d, std::vector<ModIntT>(len));\n  for (int i\
    \ = 0; i != ls; ++i) a[chi[i]][i] = lhs[i], b[chi[i]][i] = rhs[i];\n  for (auto\
    \ &&i : a) tft(i);\n  for (auto &&i : b) tft(i);\n  for (int i = 0; i != d; ++i)\n\
    \    for (int j = 0; j != d; ++j)\n      for (int k = 0, l = i + j < d ? i + j\
    \ : i + j - d; k != len; ++k)\n        ab[l][k] += a[i][k] * b[j][k];\n  for (auto\
    \ &&i : ab) itft(i);\n  std::vector<ModIntT> res(ls);\n  for (int i = 0; i !=\
    \ ls; ++i) res[i] = ab[chi[i]][i];\n  return res;\n}\n\nLIB_END\n\n\n"
  code: "#ifndef MULTIVARIATE_CONVOLUTION_HPP\n#define MULTIVARIATE_CONVOLUTION_HPP\n\
    \n#include \"../common.hpp\"\n#include \"truncated_fourier_transform.hpp\"\n\n\
    #include <algorithm>\n#include <cassert>\n#include <vector>\n\nLIB_BEGIN\n\ntemplate\
    \ <typename ModIntT>\nstd::vector<ModIntT> multivariate_convolution(const std::vector<ModIntT>\
    \ &lhs,\n                                              const std::vector<ModIntT>\
    \ &rhs,\n                                              const std::vector<int>\
    \ n) {\n  const int d  = std::max(1, static_cast<int>(n.size()));\n  const int\
    \ ls = static_cast<int>(lhs.size());\n  assert(rhs.size() == ls);\n  const int\
    \ len = (ls << 1) - 1; // slower than using `ls << 1`.\n  std::vector<int> base(d\
    \ - 1);\n  if (d > 1) base.front() = n.front();\n  for (int i = 1; i < d - 1;\
    \ ++i) base[i] = base[i - 1] * n[i];\n  auto chi_mod = [&base, d](int i) {\n \
    \   int x = 0;\n    for (int v : base) x += i / v;\n    return x % d;\n  };\n\
    \  std::vector<int> chi(ls);\n  for (int i = 0; i != ls; ++i) chi[i] = chi_mod(i);\n\
    \  std::vector<std::vector<ModIntT>> a(d, std::vector<ModIntT>(len)),\n      b(d,\
    \ std::vector<ModIntT>(len)), ab(d, std::vector<ModIntT>(len));\n  for (int i\
    \ = 0; i != ls; ++i) a[chi[i]][i] = lhs[i], b[chi[i]][i] = rhs[i];\n  for (auto\
    \ &&i : a) tft(i);\n  for (auto &&i : b) tft(i);\n  for (int i = 0; i != d; ++i)\n\
    \    for (int j = 0; j != d; ++j)\n      for (int k = 0, l = i + j < d ? i + j\
    \ : i + j - d; k != len; ++k)\n        ab[l][k] += a[i][k] * b[j][k];\n  for (auto\
    \ &&i : ab) itft(i);\n  std::vector<ModIntT> res(ls);\n  for (int i = 0; i !=\
    \ ls; ++i) res[i] = ab[chi[i]][i];\n  return res;\n}\n\nLIB_END\n\n#endif"
  dependsOn:
  - common.hpp
  - math/truncated_fourier_transform.hpp
  - math/radix2_ntt.hpp
  isVerificationFile: false
  path: math/multivariate_convolution.hpp
  requiredBy: []
  timestamp: '2022-06-22 23:05:33+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - remote_test/yosupo/math/multivariate_convolution.0.test.cpp
documentation_of: math/multivariate_convolution.hpp
layout: document
title: Multivariate Convolution (in $\mathbb{F} _ p \lbrack z_1, \dots, z_d \rbrack
  \left/ \left( z_1^{l_1}, \dots, z_d^{l_d} \right)\right.$ for FFT prime $p$)
---

## Basic Notation

Multivariate polynomials in $\mathbb{F} _ p \lbrack z_1, \dots, z_d \rbrack$ are something like

$$
A(z_1, \dots, z_d) := \sum _ {}a _ {i_1, \dots, i_d} z_1^{i_1} \cdots z_d^{i_d}.
$$

## Lexicographical Encoding

Hoeven showed that we could use lexicographical encoding to transform the multivariate polynomials to univariate polynomials like

$$
A(z) := \sum a _ {i_1, \dots, i_d} z^{\operatorname{lex} _ {n_1, \dots, n_d}(i_1, \dots, i_d)}
$$

where

$$
n_i := \deg _ {z_i} A(z_1, \dots, z_d)
$$

and

$$
\operatorname{lex} _ {n_1, \dots, n_d}(i_1, \dots, i_d) := i_1 + i_2n_1 + \cdots + i_dn_1 \cdots n _ {d - 1}.
$$

It's some kind of mixed radix representation of an integer.

## Multiplication in $\mathbb{F} _ p \lbrack z_1, \dots, z_d \rbrack \left/ \left( z_1^{l_1}, \dots, z_d^{l_d} \right)\right.$

Our goal is to compute multiplication in $\mathbb{F} _ p \lbrack z_1, \dots, z_d \rbrack \left/ \left( z_1^{l_1}, \dots, z_d^{l_d} \right)\right.$. When we multiply $A(z)$ above by $B(z) = \sum b _ {i_1, \dots ,i_d} z^{\operatorname{lex} _ {n_1, \dots, n_d}(i_1, \dots, i_d)}$, we should drop the terms that carries appear when adding the exponents of $z$ (in the mixed radix representation).

Elegia showed that if there exists a function $\chi : \mathbb{N} \to \mathbb{N}$ that

$$
\chi (i) + \chi (j) = \chi (i + j)
$$

if and only if there is no carry when adding $i$ and $j$, thus we could compute multiplication of bivariate polynomials like $A = \sum_i a_i z^i t^{\chi (i)}$ and $B = \sum_i b_i z^i t^{\chi (i)}$, extract the coefficients of $\sum c _ {i + j} z^{i + j} t^{\chi (i) + \chi (j)} = AB$ where $\chi (i) + \chi (j) = \chi (i + j)$, which will give us the right answer.

If $\max_i\lbrace \chi (i) \rbrace$ is small, we could form a univariate polynomial for each $t^{\chi (i)}$. For example, we only assign non-zero coefficients $a_i$ to $z^i t^{\chi (i)}$. But we can't afford doing so much multiplications. Elegia gave the defination of $\chi$

$$
\chi (i) := \left\lfloor \frac{i}{n_1} \right\rfloor + \cdots + \left\lfloor \frac{i}{n_1 n_2 \cdots n _ {d - 1}} \right\rfloor
$$

and

$$
\chi (i + j) - \chi (i) - \chi (j) \in \lbrace 0, 1, \dots, d - 1 \rbrace
$$

for all $i, j$ as lexicographical encoding. Which means we could assign $a_i$ to $z^i t^{\chi (i) \bmod d}$. Time complexity is $O\left( dn \log n \right)$ where $n := \prod_i n_i$.

This algorithm may too hard for me. The remaining question is that how Elegia's mind works?

## Reference

1. J. van der Hoeven. [Notes on the Truncated Fourier Transform](https://www.texmacs.org/joris/tft/tft.pdf).
2. Elegia. [Hello, multivariate multiplication](https://blog.csdn.net/EI_Captain/article/details/112400493).
3. 37zigen. [多変数畳み込み（切り捨て）のアルゴリズム](https://37zigen.com/truncated-multivariate-convolution/).