---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/poly_998244353_portable/composition_of_formal_power_series_large.0.test.cpp
    title: test/poly_998244353_portable/composition_of_formal_power_series_large.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/poly_998244353_portable/convolution_mod.0.test.cpp
    title: test/poly_998244353_portable/convolution_mod.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/poly_998244353_portable/division_of_polynomials.0.test.cpp
    title: test/poly_998244353_portable/division_of_polynomials.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/poly_998244353_portable/inv_of_formal_power_series.0.test.cpp
    title: test/poly_998244353_portable/inv_of_formal_power_series.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/poly_998244353_portable/polynomial_taylor_shift.0.test.cpp
    title: test/poly_998244353_portable/polynomial_taylor_shift.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://arxiv.org/abs/2404.05177
    - https://negiizhao.blog.uoj.ac/blog/4671
  bundledCode: "#line 1 \"poly_998244353_portable.hpp\"\n// C++17 & GCC/Clang\n\n\
    #include <algorithm>\n#include <array>\n#include <cassert>\n#include <iostream>\n\
    #include <iterator>\n#include <memory>\n#include <utility>\n#include <vector>\n\
    \n// clang-format off\nnamespace hly {\n\ntemplate<unsigned Mod> class ZZ {\n\
    \  static_assert((Mod >> 31) == 0, \"`Mod` must less than 2^(31)\");\n  template<typename\
    \ Int> static unsigned safe_mod(Int a) {\n    if ((a%=(int)Mod) < 0) a += (int)Mod;\n\
    \    return a;\n  }\n  struct PrivateCtor {};\n  static inline PrivateCtor p{};\n\
    \  ZZ(PrivateCtor, unsigned a) : a_(a) {}\n  unsigned a_;\n\npublic:\n  static\
    \ unsigned mod() { return Mod; }\n  static ZZ from_raw(unsigned a) { return ZZ(p,\
    \ a); }\n  ZZ() : a_() {}\n  template<typename Int> ZZ(Int a) : a_(safe_mod(a))\
    \ {}\n  unsigned val() const { return a_; }\n  ZZ operator-() const { return from_raw(a_==0\
    \ ? a_ : Mod-a_); }\n  ZZ pow(long long e) const {\n    if (e<0) return inv().pow(-e);\n\
    \    for (ZZ x(*this), y(from_raw(1));; x *= x) {\n      if (e&1) y *= x;\n  \
    \    if ((e/=2) == 0) return y;\n    }\n  }\n  ZZ inv() const {\n    int s = 1,\
    \ t = 0, a = val(), b = Mod;\n    while (b) {\n      const int q = a/b;\n    \
    \  s = std::exchange(t, s - q*t);\n      a = std::exchange(b, a - q*b);\n    }\n\
    \    return from_raw(s<0 ? s+(int)Mod : s);\n  }\n  ZZ &operator+=(const ZZ &R)\
    \ { if ((a_+=R.a_) >= Mod) a_ -= Mod; return *this; }\n  ZZ &operator-=(const\
    \ ZZ &R) { if ((a_+=Mod-R.a_) >= Mod) a_ -= Mod; return *this; }\n  ZZ &operator*=(const\
    \ ZZ &R) { a_ = (unsigned long long)a_*R.a_ % Mod; return *this; }\n  ZZ &operator/=(const\
    \ ZZ &R) { return *this *= R.inv(); }\n  friend ZZ operator+(const ZZ &L, const\
    \ ZZ &R) { return ZZ(L) += R; }\n  friend ZZ operator-(const ZZ &L, const ZZ &R)\
    \ { return ZZ(L) -= R; }\n  friend ZZ operator*(const ZZ &L, const ZZ &R) { return\
    \ ZZ(L) *= R; }\n  friend ZZ operator/(const ZZ &L, const ZZ &R) { return ZZ(L)\
    \ /= R; }\n  friend bool operator==(const ZZ &L, const ZZ &R) { return L.val()\
    \ == R.val(); }\n  friend bool operator!=(const ZZ &L, const ZZ &R) { return L.val()\
    \ != R.val(); }\n  friend std::istream &operator>>(std::istream &L, ZZ &R) { int\
    \ a; L >> a; R.a_ = safe_mod(a); return L; }\n  friend std::ostream &operator<<(std::ostream\
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
    public:\n  void preprocess(int N) {\n    const int NN = factorial_.size();\n \
    \   if (NN < N) {\n      int k = NN;\n      while (k < N) k *= 2;\n      k = std::min<long\
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
    \ }\n\nclass Poly : public std::vector<MInt> {\n  using Base = std::vector<MInt>;\n\
    \  using Base::Base;\n\n  Poly &mul_naive(const Poly &B) {\n    const int degA\
    \ = deg();\n    const int degB = B.deg();\n    if (degA < 0 || degB < 0) {\n \
    \     clear();\n      return *this;\n    }\n    Poly AB(degA+degB+1);\n    for\
    \ (int i = 0; i <= degA; ++i)\n      for (int j = 0; j <= degB; ++j)\n       \
    \ AB[i+j] += (*this)[i] * B[j];\n    swap(AB);\n    return *this;\n  }\n\n  Poly\
    \ &mul_fft(Poly B) {\n    const int degA = deg();\n    const int degB = B.deg();\n\
    \    if (degA < 0 || degB < 0) {\n      clear();\n      return *this;\n    }\n\
    \    const int len = fft_len(degA+degB+1);\n    resize(len);\n    B.resize(len);\n\
    \    fft(*this);\n    fft(B);\n    for (int i = 0; i < len; ++i) (*this)[i] *=\
    \ B[i];\n    inv_fft(*this);\n    resize(degA+degB+1);\n    return *this;\n  }\n\
    \n  Poly &square_fft() {\n    const int degA = deg();\n    if (degA < 0) return\
    \ *this;\n    const int len = fft_len(degA*2 + 1);\n    resize(len);\n    fft(*this);\n\
    \    for (int i = 0; i < len; ++i) (*this)[i] *= (*this)[i];\n    inv_fft(*this);\n\
    \    resize(degA*2 + 1);\n    return *this;\n  }\n\n  // returns (quotient, remainder)\n\
    \  // O(deg(Q)deg(B))\n  std::array<Poly, 2> euclid_div_naive(const Poly &B) const\
    \ {\n    const int degA = deg();\n    const int degB = B.deg();\n    assert(degB\
    \ >= 0);\n    const int degQ = degA-degB;\n    if (degQ < 0) return {Poly{}, *this};\n\
    \    Poly Q(degQ+1), R(*this);\n    const MInt iv = B[degB].inv();\n    for (int\
    \ i = degQ, n = degA; i >= 0; --i)\n      if ((Q[i] = R[n--] * iv) != 0)\n   \
    \     for (int j = 0; j <= degB; ++j)\n          R[i+j] -= Q[i] * B[j];\n    R.resize(degB);\n\
    \    return {Q, R};\n  }\n\n  // O(min(deg(Q)^2,deg(Q)deg(B)))\n  Poly euclid_div_quotient_naive(const\
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
    \ int D = deg();\n    return D<0 ? MInt() : (*this)[D];\n  }\n\n  Poly taylor_shift(MInt\
    \ c) const {\n    Poly A(*this);\n    const int N = A.size();\n    BIN.preprocess(N);\n\
    \    for (int i = 0; i < N; ++i) A[i] *= BIN.factorial(i);\n    MInt cc = 1;\n\
    \    Poly B(N);\n    for (int i = 0; i < N; ++i) {\n      B[i] = cc * BIN.inv_factorial(i);\n\
    \      cc *= c;\n    }\n    std::reverse(A.begin(), A.end());\n    Poly AB = A*B;\n\
    \    AB.resize(N);\n    std::reverse(AB.begin(), AB.end());\n    for (int i =\
    \ 0; i < N; ++i) AB[i] *= BIN.inv_factorial(i);\n    return AB;\n  }\n\n  // FPS\
    \ operation\n  // see:\n  // [1]: \u5173\u4E8E\u4F18\u5316\u5F62\u5F0F\u5E42\u7EA7\
    \u6570\u8BA1\u7B97\u7684 Newton \u6CD5\u7684\u5E38\u6570\n  //      https://negiizhao.blog.uoj.ac/blog/4671\n\
    \  Poly inv(int N) const {\n    // total cost = 10 E(N)\n    assert(N >= 0);\n\
    \    assert(ord() == 0);\n    if (N == 0) return {};\n    const int len = fft_len(N);\n\
    \    Poly invA(len), shopA(len), shopB(len);\n    invA[0] = (*this)[0].inv();\n\
    \    // total cost = cost of last iteration * 2\n    for (int i = 2; i <= len;\
    \ i *= 2) {\n      std::fill(std::copy_n(begin(), std::min<int>(size(), i), shopA.begin()),\n\
    \                shopA.begin() + i, MInt());\n      std::copy_n(invA.begin(),\
    \ i, shopB.begin());\n      fft_n(shopA.begin(), i); // E(N)\n      fft_n(shopB.begin(),\
    \ i); // E(N)\n      for (int j = 0; j < i; ++j) shopA[j] *= shopB[j];\n     \
    \ inv_fft_n(shopA.begin(), i); // E(N)\n      std::fill_n(shopA.begin(), i/2,\
    \ MInt());\n      fft_n(shopA.begin(), i); // E(N)\n      for (int j = 0; j <\
    \ i; ++j) shopA[j] *= shopB[j];\n      inv_fft_n(shopA.begin(), i); // E(N)\n\
    \      for (int j = i/2; j < i; ++j) invA[j] = -shopA[j];\n    }\n    invA.resize(N);\n\
    \    return invA;\n  }\n\n  // see:\n  // [1]: \u5173\u4E8E\u4F18\u5316\u5F62\u5F0F\
    \u5E42\u7EA7\u6570\u8BA1\u7B97\u7684 Newton \u6CD5\u7684\u5E38\u6570\n  //   \
    \   https://negiizhao.blog.uoj.ac/blog/4671\n  Poly div(const Poly &R, int N)\
    \ const {\n    // total cost = 13 E(N)\n    assert(N >= 0);\n    assert(R.ord()\
    \ == 0);\n    if (N == 1) return {(*this)[0]/R[0]};\n    const int len = fft_len(N);\n\
    \    Poly LdivR(len);\n    Poly shopA = R.inv(len/2); // 5 E(N)\n    Poly shopB\
    \ = trunc(len/2);\n    Poly shopC = R.trunc(len);\n    shopA.resize(len);\n  \
    \  fft(shopA); // E(N)\n    shopB.resize(len);\n    fft(shopB); // E(N)\n    for\
    \ (int i = 0; i < len; ++i) shopB[i] *= shopA[i];\n    inv_fft(shopB); // E(N)\n\
    \    std::copy_n(shopB.begin(), len/2, LdivR.begin());\n    std::fill_n(shopB.begin()\
    \ + len/2, len/2, MInt());\n    fft(shopB); // E(N)\n    fft(shopC); // E(N)\n\
    \    for (int i = 0; i < len; ++i) shopC[i] *= shopB[i];\n    inv_fft(shopC);\
    \ // E(N)\n    std::fill_n(shopC.begin(), len/2, MInt());\n    for (int i = len/2;\
    \ i < std::min<int>(len, size()); ++i) shopC[i] = (*this)[i] - shopC[i];\n   \
    \ for (int i = std::min<int>(len, size()); i < len; ++i) shopC[i] = -shopC[i];\n\
    \    fft(shopC); // E(N)\n    for (int i = 0; i < len; ++i) shopC[i] *= shopA[i];\n\
    \    inv_fft(shopC); // E(N)\n    std::copy_n(shopC.begin() + len/2, len/2, LdivR.begin()\
    \ + len/2);\n    LdivR.resize(N);\n    return LdivR;\n  }\n\n  std::array<Poly,\
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
    \    cyclicA.shrink();\n    return {Q, cyclicA};\n  }\n\n  Poly operator-() const\
    \ {\n    const int D = deg();\n    Poly res(D+1);\n    for (int i = 0; i <= D;\
    \ ++i) res[i] = -(*this)[i];\n    return res;\n  }\n  Poly &operator+=(const Poly\
    \ &B) {\n    if (size() < B.size()) resize(B.size());\n    for (int i = 0; i <\
    \ (int)B.size(); ++i) (*this)[i] += B[i];\n    return shrink();\n  }\n  Poly &operator-=(const\
    \ Poly &B) {\n    if (size() < B.size()) resize(B.size());\n    for (int i = 0;\
    \ i < (int)B.size(); ++i) (*this)[i] -= B[i];\n    return shrink();\n  }\n  Poly\
    \ &operator*=(const Poly &B) {\n    if (deg() <= 60 || B.deg() <= 60) return mul_naive(B);\n\
    \    if (std::addressof(*this) == std::addressof(B)) return square_fft();\n  \
    \  return mul_fft(B);\n  }\n  Poly &operator/=(const Poly &B) {\n    const int\
    \ degA = deg();\n    const int degB = B.deg();\n    assert(degB >= 0);\n    const\
    \ int degQ = degA-degB;\n    if (degQ <= 60 || degB <= 60) return *this = euclid_div_quotient_naive(B);\n\
    \    return *this = rev().div(B.rev(), degQ+1).rev(degQ+1);\n  }\n  Poly &operator%=(const\
    \ Poly &B) { return *this = std::get<1>(euclid_div(B)); }\n\n  Poly &operator<<=(int\
    \ D) {\n    if (D > 0) {\n      insert(begin(), D, MInt());\n    } else if (D\
    \ < 0) {\n      if (-D < (int)size()) erase(begin(), begin() + (-D));\n      else\
    \ clear();\n    }\n    return shrink();\n  }\n  Poly &operator>>=(int D) { return\
    \ operator<<=(-D); }\n  friend Poly operator+(const Poly &L, const Poly &R) {\
    \ return Poly(L) += R; }\n  friend Poly operator-(const Poly &L, const Poly &R)\
    \ { return Poly(L) -= R; }\n  friend Poly operator*(const Poly &L, const Poly\
    \ &R) { return Poly(L) *= R; }\n  friend Poly operator/(const Poly &L, const Poly\
    \ &R) { return Poly(L) /= R; }\n  friend Poly operator%(const Poly &L, const Poly\
    \ &R) { return Poly(L) %= R; }\n  friend Poly operator<<(const Poly &L, int D)\
    \ { return Poly(L) <<= D; }\n  friend Poly operator>>(const Poly &L, int D) {\
    \ return Poly(L) >>= D; }\n  friend std::ostream &operator<<(std::ostream &L,\
    \ const Poly &R) {\n    L << '[';\n    const int D = R.deg();\n    if (D < 0)\
    \ {\n      L << '0';\n    } else {\n      for (int i = 0; i <= D; ++i) {\n   \
    \     L << R[i];\n        if (i == 1) L << \"*x\";\n        if (i >  1) L << \"\
    *x^\" << i;\n        if (i != D) L << \" + \";\n      }\n    }\n    return L <<\
    \ ']';\n  }\n};\n\n// returns F(G) mod x^N\n// see:\n// [1]: Yasunori Kinoshita,\
    \ Baitian Li. Power Series Composition in Near-Linear Time.\n//      https://arxiv.org/abs/2404.05177\n\
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
    \ int L = fft_len(N);\n  const MInt c = G.empty() ? MInt() : G[0];\n  Poly P,\
    \ Q;\n  if (c == 0) {\n    P = F.trunc(L);\n    Q = (-G).trunc(L);\n  } else {\n\
    \    P = F.taylor_shift(-c).trunc(L);\n    Q = (-(G - Poly{c})).trunc(L);\n  }\n\
    \  return rec(rec, P, Q, 1, L).trunc(N);\n}\n\n}\n// clang-format on\n"
  code: "// C++17 & GCC/Clang\n\n#include <algorithm>\n#include <array>\n#include\
    \ <cassert>\n#include <iostream>\n#include <iterator>\n#include <memory>\n#include\
    \ <utility>\n#include <vector>\n\n// clang-format off\nnamespace hly {\n\ntemplate<unsigned\
    \ Mod> class ZZ {\n  static_assert((Mod >> 31) == 0, \"`Mod` must less than 2^(31)\"\
    );\n  template<typename Int> static unsigned safe_mod(Int a) {\n    if ((a%=(int)Mod)\
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
    public:\n  void preprocess(int N) {\n    const int NN = factorial_.size();\n \
    \   if (NN < N) {\n      int k = NN;\n      while (k < N) k *= 2;\n      k = std::min<long\
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
    \ }\n\nclass Poly : public std::vector<MInt> {\n  using Base = std::vector<MInt>;\n\
    \  using Base::Base;\n\n  Poly &mul_naive(const Poly &B) {\n    const int degA\
    \ = deg();\n    const int degB = B.deg();\n    if (degA < 0 || degB < 0) {\n \
    \     clear();\n      return *this;\n    }\n    Poly AB(degA+degB+1);\n    for\
    \ (int i = 0; i <= degA; ++i)\n      for (int j = 0; j <= degB; ++j)\n       \
    \ AB[i+j] += (*this)[i] * B[j];\n    swap(AB);\n    return *this;\n  }\n\n  Poly\
    \ &mul_fft(Poly B) {\n    const int degA = deg();\n    const int degB = B.deg();\n\
    \    if (degA < 0 || degB < 0) {\n      clear();\n      return *this;\n    }\n\
    \    const int len = fft_len(degA+degB+1);\n    resize(len);\n    B.resize(len);\n\
    \    fft(*this);\n    fft(B);\n    for (int i = 0; i < len; ++i) (*this)[i] *=\
    \ B[i];\n    inv_fft(*this);\n    resize(degA+degB+1);\n    return *this;\n  }\n\
    \n  Poly &square_fft() {\n    const int degA = deg();\n    if (degA < 0) return\
    \ *this;\n    const int len = fft_len(degA*2 + 1);\n    resize(len);\n    fft(*this);\n\
    \    for (int i = 0; i < len; ++i) (*this)[i] *= (*this)[i];\n    inv_fft(*this);\n\
    \    resize(degA*2 + 1);\n    return *this;\n  }\n\n  // returns (quotient, remainder)\n\
    \  // O(deg(Q)deg(B))\n  std::array<Poly, 2> euclid_div_naive(const Poly &B) const\
    \ {\n    const int degA = deg();\n    const int degB = B.deg();\n    assert(degB\
    \ >= 0);\n    const int degQ = degA-degB;\n    if (degQ < 0) return {Poly{}, *this};\n\
    \    Poly Q(degQ+1), R(*this);\n    const MInt iv = B[degB].inv();\n    for (int\
    \ i = degQ, n = degA; i >= 0; --i)\n      if ((Q[i] = R[n--] * iv) != 0)\n   \
    \     for (int j = 0; j <= degB; ++j)\n          R[i+j] -= Q[i] * B[j];\n    R.resize(degB);\n\
    \    return {Q, R};\n  }\n\n  // O(min(deg(Q)^2,deg(Q)deg(B)))\n  Poly euclid_div_quotient_naive(const\
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
    \ int D = deg();\n    return D<0 ? MInt() : (*this)[D];\n  }\n\n  Poly taylor_shift(MInt\
    \ c) const {\n    Poly A(*this);\n    const int N = A.size();\n    BIN.preprocess(N);\n\
    \    for (int i = 0; i < N; ++i) A[i] *= BIN.factorial(i);\n    MInt cc = 1;\n\
    \    Poly B(N);\n    for (int i = 0; i < N; ++i) {\n      B[i] = cc * BIN.inv_factorial(i);\n\
    \      cc *= c;\n    }\n    std::reverse(A.begin(), A.end());\n    Poly AB = A*B;\n\
    \    AB.resize(N);\n    std::reverse(AB.begin(), AB.end());\n    for (int i =\
    \ 0; i < N; ++i) AB[i] *= BIN.inv_factorial(i);\n    return AB;\n  }\n\n  // FPS\
    \ operation\n  // see:\n  // [1]: \u5173\u4E8E\u4F18\u5316\u5F62\u5F0F\u5E42\u7EA7\
    \u6570\u8BA1\u7B97\u7684 Newton \u6CD5\u7684\u5E38\u6570\n  //      https://negiizhao.blog.uoj.ac/blog/4671\n\
    \  Poly inv(int N) const {\n    // total cost = 10 E(N)\n    assert(N >= 0);\n\
    \    assert(ord() == 0);\n    if (N == 0) return {};\n    const int len = fft_len(N);\n\
    \    Poly invA(len), shopA(len), shopB(len);\n    invA[0] = (*this)[0].inv();\n\
    \    // total cost = cost of last iteration * 2\n    for (int i = 2; i <= len;\
    \ i *= 2) {\n      std::fill(std::copy_n(begin(), std::min<int>(size(), i), shopA.begin()),\n\
    \                shopA.begin() + i, MInt());\n      std::copy_n(invA.begin(),\
    \ i, shopB.begin());\n      fft_n(shopA.begin(), i); // E(N)\n      fft_n(shopB.begin(),\
    \ i); // E(N)\n      for (int j = 0; j < i; ++j) shopA[j] *= shopB[j];\n     \
    \ inv_fft_n(shopA.begin(), i); // E(N)\n      std::fill_n(shopA.begin(), i/2,\
    \ MInt());\n      fft_n(shopA.begin(), i); // E(N)\n      for (int j = 0; j <\
    \ i; ++j) shopA[j] *= shopB[j];\n      inv_fft_n(shopA.begin(), i); // E(N)\n\
    \      for (int j = i/2; j < i; ++j) invA[j] = -shopA[j];\n    }\n    invA.resize(N);\n\
    \    return invA;\n  }\n\n  // see:\n  // [1]: \u5173\u4E8E\u4F18\u5316\u5F62\u5F0F\
    \u5E42\u7EA7\u6570\u8BA1\u7B97\u7684 Newton \u6CD5\u7684\u5E38\u6570\n  //   \
    \   https://negiizhao.blog.uoj.ac/blog/4671\n  Poly div(const Poly &R, int N)\
    \ const {\n    // total cost = 13 E(N)\n    assert(N >= 0);\n    assert(R.ord()\
    \ == 0);\n    if (N == 1) return {(*this)[0]/R[0]};\n    const int len = fft_len(N);\n\
    \    Poly LdivR(len);\n    Poly shopA = R.inv(len/2); // 5 E(N)\n    Poly shopB\
    \ = trunc(len/2);\n    Poly shopC = R.trunc(len);\n    shopA.resize(len);\n  \
    \  fft(shopA); // E(N)\n    shopB.resize(len);\n    fft(shopB); // E(N)\n    for\
    \ (int i = 0; i < len; ++i) shopB[i] *= shopA[i];\n    inv_fft(shopB); // E(N)\n\
    \    std::copy_n(shopB.begin(), len/2, LdivR.begin());\n    std::fill_n(shopB.begin()\
    \ + len/2, len/2, MInt());\n    fft(shopB); // E(N)\n    fft(shopC); // E(N)\n\
    \    for (int i = 0; i < len; ++i) shopC[i] *= shopB[i];\n    inv_fft(shopC);\
    \ // E(N)\n    std::fill_n(shopC.begin(), len/2, MInt());\n    for (int i = len/2;\
    \ i < std::min<int>(len, size()); ++i) shopC[i] = (*this)[i] - shopC[i];\n   \
    \ for (int i = std::min<int>(len, size()); i < len; ++i) shopC[i] = -shopC[i];\n\
    \    fft(shopC); // E(N)\n    for (int i = 0; i < len; ++i) shopC[i] *= shopA[i];\n\
    \    inv_fft(shopC); // E(N)\n    std::copy_n(shopC.begin() + len/2, len/2, LdivR.begin()\
    \ + len/2);\n    LdivR.resize(N);\n    return LdivR;\n  }\n\n  std::array<Poly,\
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
    \    cyclicA.shrink();\n    return {Q, cyclicA};\n  }\n\n  Poly operator-() const\
    \ {\n    const int D = deg();\n    Poly res(D+1);\n    for (int i = 0; i <= D;\
    \ ++i) res[i] = -(*this)[i];\n    return res;\n  }\n  Poly &operator+=(const Poly\
    \ &B) {\n    if (size() < B.size()) resize(B.size());\n    for (int i = 0; i <\
    \ (int)B.size(); ++i) (*this)[i] += B[i];\n    return shrink();\n  }\n  Poly &operator-=(const\
    \ Poly &B) {\n    if (size() < B.size()) resize(B.size());\n    for (int i = 0;\
    \ i < (int)B.size(); ++i) (*this)[i] -= B[i];\n    return shrink();\n  }\n  Poly\
    \ &operator*=(const Poly &B) {\n    if (deg() <= 60 || B.deg() <= 60) return mul_naive(B);\n\
    \    if (std::addressof(*this) == std::addressof(B)) return square_fft();\n  \
    \  return mul_fft(B);\n  }\n  Poly &operator/=(const Poly &B) {\n    const int\
    \ degA = deg();\n    const int degB = B.deg();\n    assert(degB >= 0);\n    const\
    \ int degQ = degA-degB;\n    if (degQ <= 60 || degB <= 60) return *this = euclid_div_quotient_naive(B);\n\
    \    return *this = rev().div(B.rev(), degQ+1).rev(degQ+1);\n  }\n  Poly &operator%=(const\
    \ Poly &B) { return *this = std::get<1>(euclid_div(B)); }\n\n  Poly &operator<<=(int\
    \ D) {\n    if (D > 0) {\n      insert(begin(), D, MInt());\n    } else if (D\
    \ < 0) {\n      if (-D < (int)size()) erase(begin(), begin() + (-D));\n      else\
    \ clear();\n    }\n    return shrink();\n  }\n  Poly &operator>>=(int D) { return\
    \ operator<<=(-D); }\n  friend Poly operator+(const Poly &L, const Poly &R) {\
    \ return Poly(L) += R; }\n  friend Poly operator-(const Poly &L, const Poly &R)\
    \ { return Poly(L) -= R; }\n  friend Poly operator*(const Poly &L, const Poly\
    \ &R) { return Poly(L) *= R; }\n  friend Poly operator/(const Poly &L, const Poly\
    \ &R) { return Poly(L) /= R; }\n  friend Poly operator%(const Poly &L, const Poly\
    \ &R) { return Poly(L) %= R; }\n  friend Poly operator<<(const Poly &L, int D)\
    \ { return Poly(L) <<= D; }\n  friend Poly operator>>(const Poly &L, int D) {\
    \ return Poly(L) >>= D; }\n  friend std::ostream &operator<<(std::ostream &L,\
    \ const Poly &R) {\n    L << '[';\n    const int D = R.deg();\n    if (D < 0)\
    \ {\n      L << '0';\n    } else {\n      for (int i = 0; i <= D; ++i) {\n   \
    \     L << R[i];\n        if (i == 1) L << \"*x\";\n        if (i >  1) L << \"\
    *x^\" << i;\n        if (i != D) L << \" + \";\n      }\n    }\n    return L <<\
    \ ']';\n  }\n};\n\n// returns F(G) mod x^N\n// see:\n// [1]: Yasunori Kinoshita,\
    \ Baitian Li. Power Series Composition in Near-Linear Time.\n//      https://arxiv.org/abs/2404.05177\n\
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
    \ int L = fft_len(N);\n  const MInt c = G.empty() ? MInt() : G[0];\n  Poly P,\
    \ Q;\n  if (c == 0) {\n    P = F.trunc(L);\n    Q = (-G).trunc(L);\n  } else {\n\
    \    P = F.taylor_shift(-c).trunc(L);\n    Q = (-(G - Poly{c})).trunc(L);\n  }\n\
    \  return rec(rec, P, Q, 1, L).trunc(N);\n}\n\n}\n// clang-format on\n"
  dependsOn: []
  isVerificationFile: false
  path: poly_998244353_portable.hpp
  requiredBy: []
  timestamp: '2024-11-03 20:41:23+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/poly_998244353_portable/division_of_polynomials.0.test.cpp
  - test/poly_998244353_portable/inv_of_formal_power_series.0.test.cpp
  - test/poly_998244353_portable/convolution_mod.0.test.cpp
  - test/poly_998244353_portable/composition_of_formal_power_series_large.0.test.cpp
  - test/poly_998244353_portable/polynomial_taylor_shift.0.test.cpp
documentation_of: poly_998244353_portable.hpp
layout: document
redirect_from:
- /library/poly_998244353_portable.hpp
- /library/poly_998244353_portable.hpp.html
title: poly_998244353_portable.hpp
---
