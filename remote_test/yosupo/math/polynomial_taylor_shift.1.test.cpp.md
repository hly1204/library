---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':question:'
    path: common.hpp
    title: common.hpp
  - icon: ':heavy_check_mark:'
    path: math/binomial_convolution.hpp
    title: Binomial Convolution (in $\mathbb{Z} / m \mathbb{Z}$)
  - icon: ':heavy_check_mark:'
    path: math/convolution.hpp
    title: Convolution (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  - icon: ':question:'
    path: math/extended_gcd.hpp
    title: Extended Euclidean Algorithm (in $\mathbb{Z}$)
  - icon: ':question:'
    path: math/radix2_ntt.hpp
    title: Radix-2 NTT (in $\mathbb{F} _ p \lbrack z \rbrack$ for FFT prime $p$)
  - icon: ':question:'
    path: math/truncated_fourier_transform.hpp
    title: Truncated Fourier Transform (in $\mathbb{F} _ p \lbrack z \rbrack$ for
      FFT prime $p$)
  - icon: ':heavy_check_mark:'
    path: modint/long_montgomery_modint.hpp
    title: Long Montgomery ModInt
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/polynomial_taylor_shift
    links:
    - https://judge.yosupo.jp/problem/polynomial_taylor_shift
  bundledCode: "#line 1 \"remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/polynomial_taylor_shift\"\n\
    \n#line 1 \"math/binomial_convolution.hpp\"\n\n\n\n#line 1 \"common.hpp\"\n\n\n\
    \n#define LIB_DEBUG\n\n#define LIB_BEGIN namespace lib {\n#define LIB_END }\n\
    #define LIB ::lib::\n\n\n#line 1 \"modint/long_montgomery_modint.hpp\"\n\n\n\n\
    #line 5 \"modint/long_montgomery_modint.hpp\"\n\n#ifdef LIB_DEBUG\n  #include\
    \ <stdexcept>\n#endif\n#include <cstdint>\n#include <iostream>\n#include <type_traits>\n\
    \nLIB_BEGIN\n\ntemplate <std::uint64_t ModT>\nclass montgomery_modint63 {\n  using\
    \ u32 = std::uint32_t;\n  using i64 = std::int64_t;\n  using u64 = std::uint64_t;\n\
    \n  u64 v_{};\n\n  static constexpr u64 get_r() {\n    u64 t = 2, iv = MOD * (t\
    \ - MOD * MOD);\n    iv *= t - MOD * iv, iv *= t - MOD * iv, iv *= t - MOD * iv;\n\
    \    return iv * (t - MOD * iv);\n  }\n  static constexpr u64 get_r2() {\n   \
    \ u64 iv = -MOD % MOD;\n    for (int i = 0; i != 64; ++i)\n      if ((iv <<= 1)\
    \ >= MOD) iv -= MOD;\n    return iv;\n  }\n  static constexpr u64 mul_high(u64\
    \ x, u64 y) {\n    u64 a = x >> 32, b = static_cast<u32>(x), c = y >> 32, d =\
    \ static_cast<u32>(y), ad = a * d,\n        bc = b * c;\n    return a * c + (ad\
    \ >> 32) + (bc >> 32) +\n           (((ad & 0xFFFFFFFF) + (bc & 0xFFFFFFFF) +\
    \ (b * d >> 32)) >> 32);\n  }\n  static constexpr u64 redc_mul(u64 x, u64 y) {\n\
    \    u64 res = mul_high(x, y) - mul_high(x * y * R, MOD);\n    return res + (MOD\
    \ & -(res >> 63));\n  }\n  static constexpr u64 norm(i64 x) { return x + (MOD\
    \ & -(x < 0)); }\n\n  static constexpr u64 MOD  = ModT;\n  static constexpr u64\
    \ R    = get_r();\n  static constexpr u64 R2   = get_r2();\n  static constexpr\
    \ i64 SMOD = static_cast<i64>(MOD);\n\n  static_assert(MOD & 1);\n  static_assert(R\
    \ * MOD == 1);\n  static_assert((MOD >> 63) == 0);\n  static_assert(MOD != 1);\n\
    \npublic:\n  static constexpr u64 mod() { return MOD; }\n  static constexpr i64\
    \ smod() { return SMOD; }\n  constexpr montgomery_modint63() {}\n  template <typename\
    \ IntT, std::enable_if_t<std::is_integral_v<IntT>, int> = 0>\n  constexpr montgomery_modint63(IntT\
    \ v) : v_(redc_mul(norm(v % SMOD), R2)) {}\n  constexpr u64 val() const {\n  \
    \  u64 res = -mul_high(v_ * R, MOD);\n    return res + (MOD & -(res >> 63));\n\
    \  }\n  constexpr i64 sval() const { return val(); }\n  constexpr bool is_zero()\
    \ const { return v_ == 0; }\n  template <typename IntT, std::enable_if_t<std::is_integral_v<IntT>,\
    \ int> = 0>\n  explicit constexpr operator IntT() const {\n    return static_cast<IntT>(val());\n\
    \  }\n  constexpr montgomery_modint63 operator-() const {\n    montgomery_modint63\
    \ res;\n    res.v_ = (MOD & -(v_ != 0)) - v_;\n    return res;\n  }\n  constexpr\
    \ montgomery_modint63 inv() const {\n    i64 x1 = 1, x3 = 0, a = sval(), b = SMOD;\n\
    \    while (b != 0) {\n      i64 q = a / b, x1_old = x1, a_old = a;\n      x1\
    \ = x3, x3 = x1_old - x3 * q, a = b, b = a_old - b * q;\n    }\n#ifdef LIB_DEBUG\n\
    \    if (a != 1) throw std::runtime_error(\"modular inverse error\");\n#endif\n\
    \    return montgomery_modint63(x1);\n  }\n  constexpr montgomery_modint63 &operator+=(const\
    \ montgomery_modint63 &rhs) {\n    v_ += rhs.v_ - MOD, v_ += MOD & -(v_ >> 63);\n\
    \    return *this;\n  }\n  constexpr montgomery_modint63 &operator-=(const montgomery_modint63\
    \ &rhs) {\n    v_ -= rhs.v_, v_ += MOD & -(v_ >> 63);\n    return *this;\n  }\n\
    \  constexpr montgomery_modint63 &operator*=(const montgomery_modint63 &rhs) {\n\
    \    v_ = redc_mul(v_, rhs.v_);\n    return *this;\n  }\n  constexpr montgomery_modint63\
    \ &operator/=(const montgomery_modint63 &rhs) {\n    return operator*=(rhs.inv());\n\
    \  }\n  constexpr montgomery_modint63 pow(u64 e) const {\n    for (montgomery_modint63\
    \ res(1), x(*this);; x *= x) {\n      if (e & 1) res *= x;\n      if ((e >>= 1)\
    \ == 0) return res;\n    }\n  }\n  constexpr void swap(montgomery_modint63 &rhs)\
    \ {\n    auto v = v_;\n    v_ = rhs.v_, rhs.v_ = v;\n  }\n  friend constexpr montgomery_modint63\
    \ operator+(const montgomery_modint63 &lhs,\n                                \
    \                 const montgomery_modint63 &rhs) {\n    return montgomery_modint63(lhs)\
    \ += rhs;\n  }\n  friend constexpr montgomery_modint63 operator-(const montgomery_modint63\
    \ &lhs,\n                                                 const montgomery_modint63\
    \ &rhs) {\n    return montgomery_modint63(lhs) -= rhs;\n  }\n  friend constexpr\
    \ montgomery_modint63 operator*(const montgomery_modint63 &lhs,\n            \
    \                                     const montgomery_modint63 &rhs) {\n    return\
    \ montgomery_modint63(lhs) *= rhs;\n  }\n  friend constexpr montgomery_modint63\
    \ operator/(const montgomery_modint63 &lhs,\n                                \
    \                 const montgomery_modint63 &rhs) {\n    return montgomery_modint63(lhs)\
    \ /= rhs;\n  }\n  friend constexpr bool operator==(const montgomery_modint63 &lhs,\
    \ const montgomery_modint63 &rhs) {\n    return lhs.v_ == rhs.v_;\n  }\n  friend\
    \ constexpr bool operator!=(const montgomery_modint63 &lhs, const montgomery_modint63\
    \ &rhs) {\n    return lhs.v_ != rhs.v_;\n  }\n  friend std::istream &operator>>(std::istream\
    \ &is, montgomery_modint63 &rhs) {\n    i64 x;\n    is >> x;\n    rhs = montgomery_modint63(x);\n\
    \    return is;\n  }\n  friend std::ostream &operator<<(std::ostream &os, const\
    \ montgomery_modint63 &rhs) {\n    return os << rhs.val();\n  }\n};\n\ntemplate\
    \ <std::uint64_t ModT>\nusing mm63 = montgomery_modint63<ModT>;\n\nLIB_END\n\n\
    \n#line 1 \"math/convolution.hpp\"\n\n\n\n#line 1 \"math/truncated_fourier_transform.hpp\"\
    \n\n\n\n#line 1 \"math/radix2_ntt.hpp\"\n\n\n\n#line 5 \"math/radix2_ntt.hpp\"\
    \n\n#include <algorithm>\n#include <array>\n#include <cassert>\n#line 10 \"math/radix2_ntt.hpp\"\
    \n#include <vector>\n\nLIB_BEGIN\n\nnamespace detail {\n\ntemplate <typename IntT>\n\
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
    \ \"math/convolution.hpp\"\n\n#line 8 \"math/convolution.hpp\"\n#include <memory>\n\
    #line 10 \"math/convolution.hpp\"\n\nLIB_BEGIN\n\ntemplate <typename ModIntT>\n\
    std::vector<ModIntT> convolution(const std::vector<ModIntT> &lhs, const std::vector<ModIntT>\
    \ &rhs) {\n  int n = static_cast<int>(lhs.size()), m = static_cast<int>(rhs.size());\n\
    \  if (n == 0 || m == 0) return {};\n  if (std::min(n, m) <= 32) {\n    std::vector<ModIntT>\
    \ res(n + m - 1);\n    for (int i = 0; i != n; ++i)\n      for (int j = 0; j !=\
    \ m; ++j) res[i + j] += lhs[i] * rhs[j];\n    return res;\n  }\n  int len = n\
    \ + m - 1;\n  std::vector<ModIntT> lhs_cpy(len);\n  std::copy_n(lhs.cbegin(),\
    \ n, lhs_cpy.begin());\n  tft(lhs_cpy);\n  if (std::addressof(lhs) != std::addressof(rhs))\
    \ {\n    std::vector<ModIntT> rhs_cpy(len);\n    std::copy_n(rhs.cbegin(), m,\
    \ rhs_cpy.begin());\n    tft(rhs_cpy);\n    for (int i = 0; i != len; ++i) lhs_cpy[i]\
    \ *= rhs_cpy[i];\n  } else {\n    for (int i = 0; i != len; ++i) lhs_cpy[i] *=\
    \ lhs_cpy[i];\n  }\n  itft(lhs_cpy);\n  return lhs_cpy;\n}\n\nLIB_END\n\n\n#line\
    \ 1 \"math/extended_gcd.hpp\"\n\n\n\n#line 5 \"math/extended_gcd.hpp\"\n\n#include\
    \ <tuple>\n#line 9 \"math/extended_gcd.hpp\"\n\nLIB_BEGIN\n\n// Input:  integer\
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
    LIB_END\n\n\n#line 8 \"math/binomial_convolution.hpp\"\n\n#line 11 \"math/binomial_convolution.hpp\"\
    \n\nLIB_BEGIN\n\n// helper class for binomial convolution\nclass binomial_convolution\
    \ {\n  using i32 = std::int32_t;\n  using u32 = std::uint32_t;\n  using i64 =\
    \ std::int64_t;\n  using u64 = std::uint64_t;\n\n  using mint0 = mm63<0x3F9A000000000001>;\n\
    \  using mint1 = mm63<0x3FC6000000000001>;\n\n  struct factor_info {\n    const\
    \ u32 p_, e_, pe_; // `p_`^`e_` = `pe_`, `p_` prime\n    mutable std::vector<mint0>\
    \ pp0_, ipp0_;\n    mutable std::vector<mint1> pp1_, ipp1_;\n    mutable std::vector<u32>\
    \ nu_{0}, fact_{1}, ifact_{1}; // `fact_[i]` = `i`! / `p_`^(`nu_[i]`)\n    factor_info(u32\
    \ p, u32 e, u32 pe)\n        : p_(p), e_(e), pe_(pe), pp0_{mint0(1), mint0(p)},\
    \ ipp0_{mint0(1), mint0(p).inv()},\n          pp1_{mint1(1), mint1(p)}, ipp1_{mint1(1),\
    \ mint1(p).inv()} {}\n    void preprocess(int n) const {\n      int os = static_cast<int>(nu_.size());\n\
    \      if (os >= n) return;\n      nu_.resize(n);\n      fact_.resize(n);\n  \
    \    ifact_.resize(n);\n      for (int i = os; i != n; ++i) {\n        auto j\
    \ = static_cast<u32>(i);\n        auto v = nu_[i - 1];\n        for (; j % p_\
    \ == 0; j /= p_) ++v;\n        nu_[i]    = v;\n        fact_[i]  = static_cast<u64>(fact_[i\
    \ - 1]) * j % pe_;\n        ifact_[i] = static_cast<u64>(fact_[i]) * ifact_[i\
    \ - 1] % pe_;\n      }\n      {\n        auto iv = [](u32 a, u32 b) -> u64 {\n\
    \          auto v = inv_gcd(a, b).first /* % b */;\n          return v < 0 ? v\
    \ + b : v;\n        }(ifact_.back(), pe_);\n        for (int i = n - 1; i >= os;\
    \ --i)\n          ifact_[i] = ifact_[i - 1] * iv % pe_, iv = iv * fact_[i] % pe_;\n\
    \      }\n      if (int maxnu = static_cast<int>(nu_.back()), pos = static_cast<int>(pp0_.size());\n\
    \          pos <= maxnu) {\n        pp0_.resize(maxnu + 1);\n        ipp0_.resize(maxnu\
    \ + 1);\n        pp1_.resize(maxnu + 1);\n        ipp1_.resize(maxnu + 1);\n \
    \       mint0 p0(pp0_[1]), ip0(ipp0_[1]);\n        mint1 p1(pp1_[1]), ip1(ipp1_[1]);\n\
    \        for (int i = pos; i <= maxnu; ++i) {\n          pp0_[i]  = pp0_[i - 1]\
    \ * p0;\n          ipp0_[i] = ipp0_[i - 1] * ip0;\n          pp1_[i]  = pp1_[i\
    \ - 1] * p1;\n          ipp1_[i] = ipp1_[i - 1] * ip1;\n        }\n      }\n \
    \   }\n  };\n\n  static std::vector<u32> convolution(const std::vector<u32> &a,\
    \ const std::vector<u32> &b,\n                                      const factor_info\
    \ &info);\n  static std::vector<u32> convolutionT(const std::vector<u32> &a, const\
    \ std::vector<u32> &b,\n                                       const factor_info\
    \ &info);\n  const u32 modular_;\n  std::vector<factor_info> info_;\n\npublic:\n\
    \  explicit binomial_convolution(u32 modular) : modular_(modular) {\n    for (u32\
    \ i = 2; static_cast<u64>(i) * i <= modular; ++i)\n      if (modular % i == 0)\
    \ {\n        int e        = 0;\n        const u32 mm = modular;\n        do {\
    \ modular /= i, ++e; } while (modular % i == 0);\n        info_.emplace_back(i,\
    \ e, mm / modular);\n      }\n    if (modular != 1) info_.emplace_back(modular,\
    \ 1, modular);\n  }\n  u32 mod() const { return modular_; }\n  template <typename\
    \ IntT>\n  std::enable_if_t<std::is_integral_v<IntT>, std::vector<IntT>>\n  operator()(const\
    \ std::vector<IntT> &a, const std::vector<IntT> &b) const;\n\n  // apply Borel\
    \ transform to `a` and then apply B(`a`)(D) to `b` where D = d/dx.\n  template\
    \ <typename IntT>\n  std::enable_if_t<std::is_integral_v<IntT>, std::vector<IntT>>\n\
    \  bapply(const std::vector<IntT> &a, const std::vector<IntT> &b) const;\n};\n\
    \nstd::vector<typename binomial_convolution::u32>\nbinomial_convolution::convolution(const\
    \ std::vector<u32> &a, const std::vector<u32> &b,\n                          \
    \        const factor_info &info) {\n  const int n = static_cast<int>(a.size()),\
    \ m = static_cast<int>(b.size()), len = n + m - 1;\n  info.preprocess(len);\n\
    \  std::vector<mint0> a0(len), b0(len);\n  std::vector<mint1> a1(len), b1(len);\n\
    \  const auto pe = info.pe_;\n  for (int i = 0; i != n; ++i) {\n    u64 a_hat\
    \ = static_cast<u64>(a[i]) * info.ifact_[i] % pe;\n    auto j    = info.nu_[i];\n\
    \    a0[i] = a_hat * info.ipp0_[j], a1[i] = a_hat * info.ipp1_[j];\n  }\n  for\
    \ (int i = 0; i != m; ++i) {\n    u64 b_hat = static_cast<u64>(b[i]) * info.ifact_[i]\
    \ % pe;\n    auto j    = info.nu_[i];\n    b0[i] = b_hat * info.ipp0_[j], b1[i]\
    \ = b_hat * info.ipp1_[j];\n  }\n  tft(a0), tft(b0), tft(a1), tft(b1);\n  for\
    \ (int i = 0; i != len; ++i) a0[i] *= b0[i], a1[i] *= b1[i];\n  itft(a0), itft(a1);\n\
    \  // Chinese remainder algorithm\n  auto cra = [pe, ip1 = mint0(mint1::mod()).inv(),\
    \ p1_mod_pe = mint1::mod() % pe](mint0 a,\n                                  \
    \                                                mint1 b) -> u64 {\n    auto bv\
    \ = b.val();\n    return (static_cast<u64>((a - bv) * ip1) % pe * p1_mod_pe +\
    \ bv) % pe;\n  };\n  std::vector<u32> res(len);\n  for (int i = 0; i != len; ++i)\
    \ {\n    int j  = info.nu_[i];\n    res[i] = cra(a0[i] * info.pp0_[j], a1[i] *\
    \ info.pp1_[j]) * info.fact_[i] % pe;\n  }\n  return res;\n}\n\nstd::vector<typename\
    \ binomial_convolution::u32>\nbinomial_convolution::convolutionT(const std::vector<u32>\
    \ &a, const std::vector<u32> &b,\n                                   const factor_info\
    \ &info) {\n  const int n = static_cast<int>(a.size()), m = static_cast<int>(b.size()),\
    \ len = n + m - 1;\n  info.preprocess(m);\n  std::vector<mint0> a0(len), b0(len);\n\
    \  std::vector<mint1> a1(len), b1(len);\n  const auto pe = info.pe_;\n  for (int\
    \ i = 0; i != n; ++i) {\n    u64 a_hat = static_cast<u64>(a[i]) * info.ifact_[i]\
    \ % pe;\n    auto j    = info.nu_[i];\n    a0[i] = a_hat * info.ipp0_[j], a1[i]\
    \ = a_hat * info.ipp1_[j];\n  }\n  for (int i = 0; i != m; ++i) {\n    u64 b_hat\
    \     = static_cast<u64>(b[i]) * info.fact_[i] % pe;\n    auto j        = info.nu_[i];\n\
    \    b0[m - 1 - i] = b_hat * info.pp0_[j], b1[m - 1 - i] = b_hat * info.pp1_[j];\n\
    \  }\n  tft(a0), tft(b0), tft(a1), tft(b1);\n  for (int i = 0; i != len; ++i)\
    \ a0[i] *= b0[i], a1[i] *= b1[i];\n  itft(a0), itft(a1);\n  // Chinese remainder\
    \ algorithm\n  auto cra = [pe, ip1 = mint0(mint1::mod()).inv(), p1_mod_pe = mint1::mod()\
    \ % pe](mint0 a,\n                                                           \
    \                       mint1 b) -> u64 {\n    auto bv = b.val();\n    return\
    \ (static_cast<u64>((a - bv) * ip1) % pe * p1_mod_pe + bv) % pe;\n  };\n  std::vector<u32>\
    \ res(m);\n  for (int i = 0; i != m; ++i) {\n    int j = info.nu_[i];\n    res[i]\
    \ =\n        cra(a0[m - 1 - i] * info.ipp0_[j], a1[m - 1 - i] * info.ipp1_[j])\
    \ * info.ifact_[i] % pe;\n  }\n  return res;\n}\n\ntemplate <typename IntT>\n\
    std::enable_if_t<std::is_integral_v<IntT>, std::vector<IntT>>\nbinomial_convolution::operator()(const\
    \ std::vector<IntT> &a, const std::vector<IntT> &b) const {\n  const int n = static_cast<int>(a.size()),\
    \ m = static_cast<int>(b.size()), len = n + m - 1;\n  std::vector<u32> a_cpy(n),\
    \ b_cpy(m);\n  for (int i = 0; i != n; ++i) a_cpy[i] = static_cast<u32>(a[i]);\n\
    \  for (int i = 0; i != m; ++i) b_cpy[i] = static_cast<u32>(b[i]);\n  u32 modular\
    \ = 1;\n  std::vector<u32> res(len);\n  {\n    auto cra = [len](std::vector<u32>\
    \ &a, u32 &m, const std::vector<u32> &b, u32 m0) {\n      auto im_mod_m0 = [](u32\
    \ a, u32 b) -> i64 {\n        auto v = inv_gcd(a, b).first /* % b */;\n      \
    \  return v < 0 ? v + b : v;\n      }(m, m0);\n      for (int i = 0; i != len;\
    \ ++i) {\n        auto v = static_cast<i32>((static_cast<i64>(b[i]) - a[i]) *\
    \ im_mod_m0 % m0);\n        a[i] += (v < 0 ? v + m0 : v) * m;\n      }\n     \
    \ m *= m0;\n    };\n    for (auto &&i : info_) cra(res, modular, convolution(a_cpy,\
    \ b_cpy, i), i.pe_);\n  }\n  return std::vector<IntT>(res.cbegin(), res.cend());\n\
    }\n\ntemplate <typename IntT>\nstd::enable_if_t<std::is_integral_v<IntT>, std::vector<IntT>>\n\
    binomial_convolution::bapply(const std::vector<IntT> &a, const std::vector<IntT>\
    \ &b) const {\n  const int n = static_cast<int>(a.size()), m = static_cast<int>(b.size()),\
    \ minnm = n < m ? n : m,\n            len = m;\n  std::vector<u32> a_cpy(minnm),\
    \ b_cpy(m);\n  for (int i = 0; i != minnm; ++i) a_cpy[i] = static_cast<u32>(a[i]);\n\
    \  for (int i = 0; i != m; ++i) b_cpy[i] = static_cast<u32>(b[i]);\n  u32 modular\
    \ = 1;\n  std::vector<u32> res(len);\n  {\n    auto cra = [len](std::vector<u32>\
    \ &a, u32 &m, const std::vector<u32> &b, u32 m0) {\n      auto im_mod_m0 = [](u32\
    \ a, u32 b) -> i64 {\n        auto v = inv_gcd(a, b).first /* % b */;\n      \
    \  return v < 0 ? v + b : v;\n      }(m, m0);\n      for (int i = 0; i != len;\
    \ ++i) {\n        auto v = static_cast<i32>((static_cast<i64>(b[i]) - a[i]) *\
    \ im_mod_m0 % m0);\n        a[i] += (v < 0 ? v + m0 : v) * m;\n      }\n     \
    \ m *= m0;\n    };\n    for (auto &&i : info_) cra(res, modular, convolutionT(a_cpy,\
    \ b_cpy, i), i.pe_);\n  }\n  return std::vector<IntT>(res.cbegin(), res.cend());\n\
    }\n\nusing bin_conv = binomial_convolution;\n\nLIB_END\n\n\n#line 4 \"remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp\"\
    \n\n#line 7 \"remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp\"\n#include\
    \ <iterator>\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"in\", \"r\", stdin),\
    \ std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(nullptr);\n  int n, c;\n  const int modular = 998244353;\n  std::cin\
    \ >> n >> c;\n  std::vector<int> p, ecx(n);\n  std::copy_n(std::istream_iterator<int>(std::cin),\
    \ n, std::back_inserter(p));\n  lib::bin_conv bc(modular);\n  long long v = 1;\n\
    \  for (int i = 0; i != n; ++i) ecx[i] = v, v = v * c % modular;\n  auto res =\
    \ bc.bapply(ecx, p);\n  std::copy(res.cbegin(), res.cend(), std::ostream_iterator<int>(std::cout,\
    \ \" \"));\n  return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/polynomial_taylor_shift\"\
    \n\n#include \"math/binomial_convolution.hpp\"\n\n#include <algorithm>\n#include\
    \ <iostream>\n#include <iterator>\n\nint main() {\n#ifdef LOCAL\n  std::freopen(\"\
    in\", \"r\", stdin), std::freopen(\"out\", \"w\", stdout);\n#endif\n  std::ios::sync_with_stdio(false);\n\
    \  std::cin.tie(nullptr);\n  int n, c;\n  const int modular = 998244353;\n  std::cin\
    \ >> n >> c;\n  std::vector<int> p, ecx(n);\n  std::copy_n(std::istream_iterator<int>(std::cin),\
    \ n, std::back_inserter(p));\n  lib::bin_conv bc(modular);\n  long long v = 1;\n\
    \  for (int i = 0; i != n; ++i) ecx[i] = v, v = v * c % modular;\n  auto res =\
    \ bc.bapply(ecx, p);\n  std::copy(res.cbegin(), res.cend(), std::ostream_iterator<int>(std::cout,\
    \ \" \"));\n  return 0;\n}"
  dependsOn:
  - math/binomial_convolution.hpp
  - common.hpp
  - modint/long_montgomery_modint.hpp
  - common.hpp
  - math/convolution.hpp
  - math/truncated_fourier_transform.hpp
  - math/radix2_ntt.hpp
  - math/extended_gcd.hpp
  isVerificationFile: true
  path: remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp
  requiredBy: []
  timestamp: '2022-06-22 23:05:33+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp
layout: document
redirect_from:
- /verify/remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp
- /verify/remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp.html
title: remote_test/yosupo/math/polynomial_taylor_shift.1.test.cpp
---
