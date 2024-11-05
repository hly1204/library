---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: poly_998244353_portable.hpp
    title: poly_998244353_portable.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/pow_of_formal_power_series
    links:
    - https://judge.yosupo.jp/problem/pow_of_formal_power_series
  bundledCode: "#line 1 \"test/poly_998244353_portable/pow_of_formal_power_series.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/pow_of_formal_power_series\"\
    \n\n#line 1 \"poly_998244353_portable.hpp\"\n// C++17 & GCC/Clang\n\n#include\
    \ <algorithm>\n#include <array>\n#include <cassert>\n#include <iostream>\n#include\
    \ <iterator>\n#include <memory>\n#include <tuple>\n#include <utility>\n#include\
    \ <vector>\n\n// clang-format off\nnamespace hly {\n\ntemplate<unsigned Mod> class\
    \ ZZ {\n  static_assert((Mod >> 31) == 0, \"`Mod` must less than 2^(31)\");\n\
    \  template<typename Int> static unsigned safe_mod(Int a) {\n    if ((a%=(int)Mod)\
    \ < 0) a += (int)Mod;\n    return a;\n  }\n  struct PrivateCtor {};\n  static\
    \ inline PrivateCtor p{};\n  ZZ(PrivateCtor, unsigned a) : a_(a) {}\n  unsigned\
    \ a_;\n\npublic:\n  static unsigned mod() { return Mod; }\n  static ZZ from_raw(unsigned\
    \ a) { return ZZ(p, a); }\n  ZZ() : a_() {}\n  template<typename Int> ZZ(Int a)\
    \ : a_(safe_mod(a)) {}\n  unsigned val() const { return a_; }\n  ZZ operator-()\
    \ const { return from_raw(a_==0 ? a_ : Mod-a_); }\n  ZZ pow(long long e) const\
    \ {\n    if (e<0) return inv().pow(-e);\n    for (ZZ x(*this), y(from_raw(1));;\
    \ x *= x) {\n      if (e&1) y *= x;\n      if ((e/=2) == 0) return y;\n    }\n\
    \  }\n  ZZ inv() const {\n    int s = 1, t = 0, a = val(), b = Mod;\n    while\
    \ (b) {\n      const int q = a/b;\n      s = std::exchange(t, s - q*t);\n    \
    \  a = std::exchange(b, a - q*b);\n    }\n    return from_raw(s<0 ? s+(int)Mod\
    \ : s);\n  }\n  ZZ &operator+=(const ZZ &R) { if ((a_+=R.a_) >= Mod) a_ -= Mod;\
    \ return *this; }\n  ZZ &operator-=(const ZZ &R) { if ((a_+=Mod-R.a_) >= Mod)\
    \ a_ -= Mod; return *this; }\n  ZZ &operator*=(const ZZ &R) { a_ = (unsigned long\
    \ long)a_*R.a_ % Mod; return *this; }\n  ZZ &operator/=(const ZZ &R) { return\
    \ *this *= R.inv(); }\n  friend ZZ operator+(const ZZ &L, const ZZ &R) { return\
    \ ZZ(L) += R; }\n  friend ZZ operator-(const ZZ &L, const ZZ &R) { return ZZ(L)\
    \ -= R; }\n  friend ZZ operator*(const ZZ &L, const ZZ &R) { return ZZ(L) *= R;\
    \ }\n  friend ZZ operator/(const ZZ &L, const ZZ &R) { return ZZ(L) /= R; }\n\
    \  friend bool operator==(const ZZ &L, const ZZ &R) { return L.val() == R.val();\
    \ }\n  friend bool operator!=(const ZZ &L, const ZZ &R) { return L.val() != R.val();\
    \ }\n  friend std::istream &operator>>(std::istream &L, ZZ &R) { int a; L >> a;\
    \ R.a_ = safe_mod(a); return L; }\n  friend std::ostream &operator<<(std::ostream\
    \ &L, const ZZ &R) { return L << R.val(); }\n};\n\nusing MInt = ZZ<998244353>;\n\
    \n// only works for odd prime moduli\nbool is_square(MInt A) { return A.pow((A.mod()-1)/2)\
    \ != MInt::from_raw(A.mod()-1); }\nMInt quadratic_nonresidue() {\n  for (int i\
    \ = 2;; ++i) {\n    const MInt a = i;\n    if (!is_square(a)) return a;\n  }\n\
    }\nstd::vector<MInt> sqrt(MInt A) {\n  if (MInt::mod() == 2 || A == 0) return\
    \ {A};\n  if (!is_square(A)) return {};\n  if (MInt::mod()%4 == 3) {\n    const\
    \ MInt res = A.pow((MInt::mod()+1) / 4);\n    return {res, -res};\n  }\n  MInt\
    \ t = 1;\n  while (is_square(t*t - 4*A)) t += 1;\n  MInt k0 = 1, k1, k2 = -t,\
    \ k3 = A;\n  for (int e = (MInt::mod()+1) / 2;; k2 = k3+k3 - k2*k2, k3 *= k3)\
    \ {\n    if (e&1) k0 = k1 - k0*k2, k1 *= k3;\n    else k1 = k0*k3 - k1*k2;\n \
    \   if ((e/=2) == 0) return {k0, -k0};\n  }\n}\n\nclass Binomial {\n  std::vector<MInt>\
    \ factorial_ = {MInt(1)};\n  std::vector<MInt> invfactorial_ = {MInt(1)};\n\n\
    public:\n  void ensure(int N) {\n    const int NN = factorial_.size();\n    if\
    \ (NN < N) {\n      int k = NN;\n      while (k < N) k *= 2;\n      k = std::min<long\
    \ long>(k, MInt::mod());\n      factorial_.resize(k);\n      invfactorial_.resize(k);\n\
    \      for (int i = NN; i < k; ++i) factorial_[i] = factorial_[i-1] * i;\n   \
    \   invfactorial_.back() = factorial_.back().inv();\n      for (int i = k-2; i\
    \ >= NN; --i) invfactorial_[i] = invfactorial_[i+1] * (i+1);\n    }\n  }\n\n \
    \ MInt binom(int N, int K) const { return N<K ? MInt() : factorial_[N]*invfactorial_[K]*invfactorial_[N-K];\
    \ }\n  MInt inv(int N) const { return factorial_[N-1] * invfactorial_[N]; }\n\
    \  MInt factorial(int N) const { return factorial_[N]; }\n  MInt inv_factorial(int\
    \ N) const { return invfactorial_[N]; }\n} BIN;\n\nclass FftInfo {\n  const int\
    \ ordlog2_ = __builtin_ctzll(MInt::mod()-1);\n  const MInt zeta_ = quadratic_nonresidue().pow((MInt::mod()-1)\
    \ >> ordlog2_);\n  const MInt invzeta_ = zeta_.inv();\n  const MInt imag_ = zeta_.pow(1LL\
    \ << (ordlog2_-2));\n  const MInt invimag_ = -imag_;\n  mutable std::vector<MInt>\
    \ root_ = {MInt::from_raw(1), imag_};\n  mutable std::vector<MInt> invroot_ =\
    \ {MInt::from_raw(1), invimag_};\n\npublic:\n  // [0, N)\n  const std::vector<MInt>\
    \ &root(int N) const {\n    assert((N & (N-1)) == 0);\n    const int S = root_.size();\n\
    \    if (S < N) {\n      root_.resize(N);\n      for (int i = __builtin_ctz(S);\
    \ (1<<i) < N; ++i) {\n        const int j = 1<<i;\n        root_[j] = zeta_.pow(1LL\
    \ << (ordlog2_-i-2));\n        for (int k = j+1; k < j*2; ++k) root_[k] = root_[k-j]\
    \ * root_[j];\n      }\n    }\n    return root_;\n  }\n  // [0, N)\n  const std::vector<MInt>\
    \ &inv_root(int N) const {\n    assert((N & (N-1)) == 0);\n    const int S = invroot_.size();\n\
    \    if (S < N) {\n      invroot_.resize(N);\n      for (int i = __builtin_ctz(S);\
    \ (1<<i) < N; ++i) {\n        const int j = 1<<i;\n        invroot_[j] = invzeta_.pow(1LL\
    \ << (ordlog2_-i-2));\n        for (int k = j+1; k < j*2; ++k) invroot_[k] = invroot_[k-j]\
    \ * invroot_[j];\n      }\n    }\n    return invroot_;\n  }\n} FFT_INFO;\n\nint\
    \ fft_len(int N) {\n  if (N==0) return 0;\n  --N; N |= N>>1; N |= N>>2; N |= N>>4;\
    \ N |= N>>8; N |= N>>16;\n  return ++N;\n}\n\nvoid butterfly_n(std::vector<MInt>::iterator\
    \ A, int N, const std::vector<MInt> &root) {\n  assert((N & (N-1)) == 0);\n  for\
    \ (int j = 0; j < N/2; ++j) {\n    const MInt u = A[j], v = A[j + N/2];\n    A[j]\
    \ = u+v, A[j + N/2] = u-v;\n  }\n  for (int i = N/2; i >= 2; i /= 2) {\n    for\
    \ (int j = 0; j < i/2; ++j) {\n      const MInt u = A[j], v = A[j + i/2];\n  \
    \    A[j] = u+v, A[j + i/2] = u-v;\n    }\n    for (int j = i, m = 1; j < N; j\
    \ += i, ++m)\n      for (int k = j; k < j + i/2; ++k) {\n        const MInt u\
    \ = A[k], v = A[k + i/2] * root[m];\n        A[k] = u+v, A[k + i/2] = u-v;\n \
    \     }\n  }\n}\n\nvoid inv_butterfly_n(std::vector<MInt>::iterator A, int N,\
    \ const std::vector<MInt> &root) {\n  assert((N & (N-1)) == 0);\n  for (int i\
    \ = 2; i < N; i *= 2) {\n    for (int j = 0; j < i/2; ++j) {\n      const MInt\
    \ u = A[j], v = A[j + i/2];\n      A[j] = u+v, A[j + i/2] = u-v;\n    }\n    for\
    \ (int j = i, m = 1; j < N; j += i, ++m)\n      for (int k = j; k < j + i/2; ++k)\
    \ {\n        const MInt u = A[k], v = A[k + i/2];\n        A[k] = u+v, A[k + i/2]\
    \ = (u-v) * root[m];\n      }\n  }\n  for (int j = 0; j < N/2; ++j) {\n    const\
    \ MInt u = A[j], v = A[j + N/2];\n    A[j] = u+v, A[j + N/2] = u-v;\n  }\n}\n\n\
    void fft_n(std::vector<MInt>::iterator A, int N) { butterfly_n(A, N, FFT_INFO.root(N/2));\
    \ }\nvoid inv_fft_n(std::vector<MInt>::iterator A, int N) {\n  inv_butterfly_n(A,\
    \ N, FFT_INFO.inv_root(N/2));\n  const MInt iv = MInt(N).inv();\n  for (int i\
    \ = 0; i < N; ++i) A[i] *= iv;\n}\n\nvoid fft(std::vector<MInt> &A) { fft_n(A.begin(),\
    \ A.size()); }\nvoid inv_fft(std::vector<MInt> &A) { inv_fft_n(A.begin(), A.size());\
    \ }\n\n// returns coefficients generated by closure\n// closure: gen(index, current_product)\n\
    template<typename Closure> std::vector<MInt>\nsemi_relaxed_conv(const std::vector<MInt>\
    \ &A, Closure Gen, int N) {\n  enum { BaseCaseSize = 32 };\n  static_assert((BaseCaseSize\
    \ & (BaseCaseSize - 1)) == 0);\n  static const int Block[] = {16, 16, 16, 16,\
    \ 16};\n  // returns (which_block, level, blocksize)\n  auto blockinfo = [](int\
    \ ind) {\n    int i = ind / BaseCaseSize, lv = 0, blocksize = BaseCaseSize;\n\
    \    while ((i & (Block[lv] - 1)) == 0) i /= Block[lv], blocksize *= Block[lv],\
    \ ++lv;\n    return std::make_tuple(i & (Block[lv]-1), lv, blocksize);\n  };\n\
    \  std::vector<MInt> B(N), AB(N);\n  std::vector<std::vector<std::vector<MInt>>>\
    \ dftA, dftB;\n  for (int i = 0; i < N; ++i) {\n    const int S = i & (BaseCaseSize-1);\n\
    \    // blocked contribution\n    if (i >= BaseCaseSize && S == 0) {\n      const\
    \ auto [j, lv, blocksize]  = blockinfo(i);\n      if (blocksize * j == i) {\n\
    \        if ((int)dftA.size() == lv) {\n          dftA.emplace_back();\n     \
    \     dftB.emplace_back(Block[lv]-1);\n        }\n        if ((j-1) * blocksize\
    \ < (int)A.size()) {\n          dftA[lv].emplace_back(A.begin() + (j-1) * blocksize,\n\
    \                                A.begin() + std::min<int>((j+1) * blocksize,\
    \ A.size()))\n                  .resize(blocksize * 2);\n          fft(dftA[lv][j-1]);\n\
    \        }\n      }\n      // if A is not empty, ...\n      if (!dftA[lv].empty())\
    \ {\n        dftB[lv][j-1].resize(blocksize*2);\n        std::fill_n(std::copy_n(B.begin()\
    \ + (i-blocksize), blocksize, dftB[lv][j-1].begin()), blocksize, MInt());\n  \
    \      fft(dftB[lv][j-1]);\n        // middle product\n        std::vector<MInt>\
    \ mp(blocksize*2);\n        for (int k = 0; k < std::min<int>(j, dftA[lv].size());\
    \ ++k)\n          for (int l = 0; l < blocksize*2; ++l)\n            mp[l] +=\
    \ dftA[lv][k][l] * dftB[lv][j-1-k][l];\n        inv_fft(mp);\n        for (int\
    \ k = 0; k < blocksize && i+k < N; ++k) AB[i+k] += mp[k+blocksize];\n      }\n\
    \    }\n    // basecase contribution\n    for (int j = std::max(i-S, i-(int)A.size()+1);\
    \ j < i; ++j) AB[i] += A[i-j] * B[j];\n    B[i] = Gen(i, AB);\n    if (!A.empty())\
    \ AB[i] += A[0] * B[i];\n  }\n  return B;\n}\n\n// Polynomial operations:\n//\
    \    add(+), sub(-), mul(*), quo(/), rem(%), shl(<<=), shr(>>=) <- auto shrink\n\
    //    taylor_shift                                               <- no shrink\n\
    // Formal Power Series operations:\n//    inv, div, log, exp                 \
    \                        <- no shrink\nclass Poly : public std::vector<MInt> {\n\
    \  using Base = std::vector<MInt>;\n  using Base::Base;\n\n  Poly &mul_naive(const\
    \ Poly &B) {\n    const int degA = deg();\n    const int degB = B.deg();\n   \
    \ if (degA < 0 || degB < 0) {\n      clear();\n      return *this;\n    }\n  \
    \  Poly AB(degA+degB+1);\n    for (int i = 0; i <= degA; ++i)\n      for (int\
    \ j = 0; j <= degB; ++j)\n        AB[i+j] += (*this)[i] * B[j];\n    swap(AB);\n\
    \    return *this;\n  }\n\n  Poly &mul_fft(Poly B) {\n    const int degA = deg();\n\
    \    const int degB = B.deg();\n    if (degA < 0 || degB < 0) {\n      clear();\n\
    \      return *this;\n    }\n    const int len = fft_len(degA+degB+1);\n    resize(len);\n\
    \    B.resize(len);\n    fft(*this);\n    fft(B);\n    for (int i = 0; i < len;\
    \ ++i) (*this)[i] *= B[i];\n    inv_fft(*this);\n    resize(degA+degB+1);\n  \
    \  return *this;\n  }\n\n  Poly &square_fft() {\n    const int degA = deg();\n\
    \    if (degA < 0) return *this;\n    const int len = fft_len(degA*2 + 1);\n \
    \   resize(len);\n    fft(*this);\n    for (int i = 0; i < len; ++i) (*this)[i]\
    \ *= (*this)[i];\n    inv_fft(*this);\n    resize(degA*2 + 1);\n    return *this;\n\
    \  }\n\n  // returns (quotient, remainder)\n  // O(deg(Q)deg(B))\n  std::array<Poly,\
    \ 2> euclid_div_naive(const Poly &B) const {\n    const int degA = deg();\n  \
    \  const int degB = B.deg();\n    assert(degB >= 0);\n    const int degQ = degA-degB;\n\
    \    if (degQ < 0) return {Poly{}, *this};\n    Poly Q(degQ+1), R(*this);\n  \
    \  const MInt iv = B[degB].inv();\n    for (int i = degQ, n = degA; i >= 0; --i)\n\
    \      if ((Q[i] = R[n--] * iv) != 0)\n        for (int j = 0; j <= degB; ++j)\n\
    \          R[i+j] -= Q[i] * B[j];\n    R.resize(degB);\n    return {Q, R};\n \
    \ }\n\n  // O(min(deg(Q)^2,deg(Q)deg(B)))\n  Poly euclid_div_quotient_naive(const\
    \ Poly &B) const {\n    const int degA = deg();\n    const int degB = B.deg();\n\
    \    assert(degB >= 0);\n    const int degQ = degA-degB;\n    if (degQ < 0) return\
    \ {};\n    Poly Q(degQ+1);\n    const MInt iv = B[degB].inv();\n    for (int i\
    \ = 0; i <= degQ; ++i) {\n      for (int j = 1; j <= std::min(i, degB); ++j)\n\
    \        Q[degQ-i] += B[degB-j] * Q[degQ-i+j];\n      Q[degQ-i] = ((*this)[degA-i]-Q[degQ-i])\
    \ * iv;\n    }\n    return Q;\n  }\n\npublic:\n  int deg() const {\n    int N\
    \ = (int)size()-1;\n    while (N >= 0 && (*this)[N] == 0) --N;\n    return N;\n\
    \  }\n  int ord() const {\n    for (int N = 0; N < (int)size(); ++N)\n      if\
    \ ((*this)[N] != 0) return N;\n    return -1;\n  }\n  Poly rev() const {\n   \
    \ return Poly(std::make_reverse_iterator(begin()+(deg()+1)),\n               \
    \ std::make_reverse_iterator(begin()));\n  }\n  Poly rev(int N) const {\n    Poly\
    \ res = trunc(N);\n    std::reverse(res.begin(), res.end());\n    return res;\n\
    \  }\n  Poly slice(int L, int R) const {\n    Poly res(R-L);\n    for (int i =\
    \ L; i < std::min<int>(R, size()); ++i) res[i-L] = (*this)[i];\n    return res;\n\
    \  }\n  Poly trunc(int D) const { return slice(0, D); }\n  Poly &shrink() {\n\
    \    resize(deg()+1);\n    return *this;\n  }\n  MInt lc() const {\n    const\
    \ int D = deg();\n    return D<0 ? MInt() : (*this)[D];\n  }\n\n  Poly deriv()\
    \ const {\n    const int N = (int)size()-1;\n    if (N <= 0) return {};\n    Poly\
    \ res(N);\n    for (int i = 1; i <= N; ++i) res[i-1] = (*this)[i] * i;\n    return\
    \ res;\n  }\n  Poly integr(MInt c = 0) const {\n    const int N = (int)size()+1;\n\
    \    BIN.ensure(N);\n    Poly res(N);\n    res[0] = c;\n    for (int i = 1; i\
    \ < N; ++i) res[i] = (*this)[i-1] * BIN.inv(i);\n    return res;\n  }\n\n  Poly\
    \ taylor_shift(MInt c) const {\n    if (c == 0) return Poly(*this);\n    Poly\
    \ A(*this);\n    const int N = A.size();\n    BIN.ensure(N);\n    for (int i =\
    \ 0; i < N; ++i) A[i] *= BIN.factorial(i);\n    MInt cc = 1;\n    Poly B(N);\n\
    \    for (int i = 0; i < N; ++i) {\n      B[i] = cc * BIN.inv_factorial(i);\n\
    \      cc *= c;\n    }\n    std::reverse(A.begin(), A.end());\n    A.mul_assign(B);\n\
    \    A.resize(N);\n    std::reverse(A.begin(), A.end());\n    for (int i = 0;\
    \ i < N; ++i) A[i] *= BIN.inv_factorial(i);\n    return A;\n  }\n\n  Poly inv(int\
    \ N) const {\n    assert(N >= 0);\n    assert(ord() == 0);\n    auto Gen = [iv\
    \ = (*this)[0].inv()](int N, const std::vector<MInt> &C) {\n      return N==0\
    \ ? iv : -C[N]*iv;\n    };\n    const std::vector<MInt> res = semi_relaxed_conv(*this,\
    \ Gen, N);\n    return Poly(res.begin(), res.end());\n  }\n\n  Poly div(const\
    \ Poly &R, int N) const {\n    assert(N >= 0);\n    assert(R.ord() == 0);\n  \
    \  auto Gen = [this, iv = R[0].inv()](int N, const std::vector<MInt> &C) {\n \
    \     return (N<(int)size() ? ((*this)[N]-C[N]) : -C[N]) * iv;\n    };\n    const\
    \ std::vector<MInt> res = semi_relaxed_conv(R, Gen, N);\n    return Poly(res.begin(),\
    \ res.end());\n  }\n\n  Poly log(int N) const {\n    assert(N >= 0);\n    assert(ord()\
    \ == 0);\n    assert((*this)[0] == 1);\n    if (N == 0) return {};\n    return\
    \ deriv().div(*this, N-1).integr();\n  }\n\n  Poly exp(int N) const {\n    assert(N\
    \ >= 0);\n    assert(ord() != 0);\n    BIN.ensure(N);\n    auto Gen = [](int N,\
    \ const std::vector<MInt> &C) {\n      return N==0 ? MInt(1) : C[N-1]*BIN.inv(N);\n\
    \    };\n    const std::vector<MInt> res = semi_relaxed_conv(deriv(), Gen, N);\n\
    \    return Poly(res.begin(), res.end());\n  }\n\n  Poly pow1(long long e, int\
    \ N) const {\n    assert(N >= 0);\n    assert(ord() == 0);\n    assert((*this)[0]\
    \ == 1);\n    return log(N).mul(Poly{MInt(e)}).exp(N);\n  }\n\n  Poly pow(long\
    \ long e, int N) {\n    assert(e >= 0);\n    assert(N >= 0);\n    if (e == 0)\
    \ return Poly{MInt(1)}.trunc(N);\n    const int O = ord();\n    if (O < 0 || O\
    \ > N/e || (O == N/e && N%e == 0)) return Poly(N);\n    return shr(O).mul(Poly{(*this)[O].inv()})\n\
    \                 .pow1(e, N - O*e)\n                 .mul(Poly{(*this)[O].pow(e)})\n\
    \                 .shl(O*e)\n                 .trunc(N);\n  }\n\n  std::array<Poly,\
    \ 2> euclid_div(const Poly &B) const {\n    const int degA = deg();\n    const\
    \ int degB = B.deg();\n    assert(degB >= 0);\n    const int degQ = degA-degB;\n\
    \    if (degQ < 0) return {Poly{}, *this};\n    if (degQ <= 60 || degB <= 60)\
    \ return euclid_div_naive(B);\n    const Poly Q = rev().div(B.rev(), degQ+1).rev(degQ+1);\n\
    \    auto make_cyclic = [](const Poly &A, int N) {\n      assert((N & (N-1)) ==\
    \ 0);\n      Poly B(N);\n      for (int i = 0; i < (int)A.size(); ++i) B[i & (N-1)]\
    \ += A[i];\n      return B;\n    };\n    assert(degB > 0);\n    const int len\
    \ = fft_len(degB);\n    Poly cyclicA = make_cyclic(*this, len);\n    Poly cyclicB\
    \ = make_cyclic(B, len);\n    Poly cyclicQ = make_cyclic(Q, len);\n    fft(cyclicB);\n\
    \    fft(cyclicQ);\n    for (int i = 0; i < len; ++i) cyclicQ[i] *= cyclicB[i];\n\
    \    inv_fft(cyclicQ);\n    cyclicA.resize(degB);\n    // R=A-QB (mod (x^n - 1))\
    \ (n >= deg(B))\n    for (int i = 0; i < degB; ++i) cyclicA[i] -= cyclicQ[i];\n\
    \    cyclicA.shrink();\n    return {Q, cyclicA};\n  }\n\n  Poly neg() const {\n\
    \    const int D = deg();\n    Poly res(D+1);\n    for (int i = 0; i <= D; ++i)\
    \ res[i] = -(*this)[i];\n    return res;\n  }\n  Poly add(const Poly &B) const\
    \ { return Poly(*this).add_assign(B); }\n  Poly sub(const Poly &B) const { return\
    \ Poly(*this).sub_assign(B); }\n  Poly mul(const Poly &B) const { return Poly(*this).mul_assign(B);\
    \ }\n  Poly quo(const Poly &B) const { return Poly(*this).quo_assign(B); }\n \
    \ Poly rem(const Poly &B) const { return Poly(*this).rem_assign(B); }\n  Poly\
    \ shl(int D) const { return Poly(*this).shl_assign(D); }\n  Poly shr(int D) const\
    \ { return Poly(*this).shr_assign(D); }\n\n  Poly &add_assign(const Poly &B) {\n\
    \    if (size() < B.size()) resize(B.size());\n    for (int i = 0; i < (int)B.size();\
    \ ++i) (*this)[i] += B[i];\n    return shrink();\n  }\n  Poly &sub_assign(const\
    \ Poly &B) {\n    if (size() < B.size()) resize(B.size());\n    for (int i = 0;\
    \ i < (int)B.size(); ++i) (*this)[i] -= B[i];\n    return shrink();\n  }\n  Poly\
    \ &mul_assign(const Poly &B) {\n    if (deg() <= 60 || B.deg() <= 60) return mul_naive(B);\n\
    \    if (std::addressof(*this) == std::addressof(B)) return square_fft();\n  \
    \  return mul_fft(B);\n  }\n  Poly &quo_assign(const Poly &B) {\n    const int\
    \ degA = deg();\n    const int degB = B.deg();\n    assert(degB >= 0);\n    const\
    \ int degQ = degA-degB;\n    if (degQ <= 60 || degB <= 60) return *this = euclid_div_quotient_naive(B);\n\
    \    return *this = rev().div(B.rev(), degQ+1).rev(degQ+1);\n  }\n  Poly &rem_assign(const\
    \ Poly &B) { return *this = std::get<1>(euclid_div(B)); }\n  Poly &shl_assign(int\
    \ D) {\n    if (D > 0) {\n      insert(begin(), D, MInt());\n    } else if (D\
    \ < 0) {\n      if (-D < (int)size()) erase(begin(), begin() + (-D));\n      else\
    \ clear();\n    }\n    return shrink();\n  }\n  Poly &shr_assign(int D) { return\
    \ shl_assign(-D); }\n\n  friend std::ostream &operator<<(std::ostream &L, const\
    \ Poly &R) {\n    L << '[';\n    const int D = R.deg();\n    if (D < 0) {\n  \
    \    L << '0';\n    } else {\n      for (int i = 0; i <= D; ++i) {\n        L\
    \ << R[i];\n        if (i == 1) L << \"*x\";\n        if (i >  1) L << \"*x^\"\
    \ << i;\n        if (i != D) L << \" + \";\n      }\n    }\n    return L << ']';\n\
    \  }\n};\n\n// returns F(G) mod x^N\n// see:\n// [1]: Yasunori Kinoshita, Baitian\
    \ Li. Power Series Composition in Near-Linear Time.\n//      https://arxiv.org/abs/2404.05177\n\
    Poly composition(const Poly &F, const Poly &G, int N) {\n  if (N == 0) return\
    \ {};\n  // [y^(-1)] (f(y) / (-g(x) + y)) mod x^N in R[x]((y^(-1)))\n  auto rec\
    \ = [](auto &&rec, const Poly &P, const Poly &Q, int D, int N) {\n    assert((int)P.size()\
    \ == D*N);\n    assert((int)Q.size() == D*N);\n    if (N == 1) return P;\n   \
    \ Poly dftQ(D*N*4);\n    for (int i = 0; i < D; ++i)\n      for (int j = 0; j\
    \ < N; ++j)\n        dftQ[i*N*2 + j] = Q[i*N + j];\n    dftQ[D*N*2] = 1;\n   \
    \ fft(dftQ);\n    Poly V(D*N*2);\n    for (int i = 0; i < D*N*4; i += 2) V[i/2]\
    \ = dftQ[i] * dftQ[i+1];\n    inv_fft(V);\n    V[0] -= 1;\n    for (int i = 1;\
    \ i < D*2; ++i)\n      for (int j = 0; j < N/2; ++j)\n        V[i*(N/2) + j] =\
    \ V[i*N + j];\n    V.resize(D*N);\n    const Poly T = rec(rec, P, V, D*2, N/2);\n\
    \    Poly dftT(D*N*2);\n    for (int i = 0; i < D*2; ++i)\n      for (int j =\
    \ 0; j < N/2; ++j)\n        dftT[i*N + j] = T[i*(N/2) + j];\n    fft(dftT);\n\
    \    Poly U(D*N*4);\n    for (int i = 0; i < D*N*4; i += 2) {\n      U[i] = dftT[i/2]\
    \ * dftQ[i+1];\n      U[i+1] = dftT[i/2] * dftQ[i];\n    }\n    inv_fft(U);\n\
    \    for (int i = 0; i < D; ++i)\n      for (int j = 0; j < N; ++j)\n        U[i*N\
    \ + j] = U[(i+D)*(N*2) + j];\n    U.resize(D*N);\n    return U;\n  };\n  const\
    \ int L = fft_len(N);\n  const MInt c = G.empty() ? MInt() : G[0];\n  return rec(rec,\
    \ F.taylor_shift(c).trunc(L), G.sub(Poly{c}).neg().trunc(L), 1, L).trunc(N);\n\
    }\n\n}\n// clang-format on\n#line 5 \"test/poly_998244353_portable/pow_of_formal_power_series.0.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using namespace hly;\n    int n;\n    long long m;\n    std::cin >> n >>\
    \ m;\n    Poly A(n);\n    for (int i = 0; i < n; ++i) std::cin >> A[i];\n    const\
    \ Poly powA = A.pow(m, n);\n    for (int i = 0; i < n; ++i) std::cout << powA[i]\
    \ << ' ';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/pow_of_formal_power_series\"\
    \n\n#include \"poly_998244353_portable.hpp\"\n#include <iostream>\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    using\
    \ namespace hly;\n    int n;\n    long long m;\n    std::cin >> n >> m;\n    Poly\
    \ A(n);\n    for (int i = 0; i < n; ++i) std::cin >> A[i];\n    const Poly powA\
    \ = A.pow(m, n);\n    for (int i = 0; i < n; ++i) std::cout << powA[i] << ' ';\n\
    \    return 0;\n}\n"
  dependsOn:
  - poly_998244353_portable.hpp
  isVerificationFile: true
  path: test/poly_998244353_portable/pow_of_formal_power_series.0.test.cpp
  requiredBy: []
  timestamp: '2024-11-05 20:53:43+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/poly_998244353_portable/pow_of_formal_power_series.0.test.cpp
layout: document
redirect_from:
- /verify/test/poly_998244353_portable/pow_of_formal_power_series.0.test.cpp
- /verify/test/poly_998244353_portable/pow_of_formal_power_series.0.test.cpp.html
title: test/poly_998244353_portable/pow_of_formal_power_series.0.test.cpp
---
