// C++17 & GCC/Clang

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <iterator>
#include <memory>
#include <tuple>
#include <utility>
#include <vector>

// clang-format off
namespace hly {

template<unsigned Mod> class ZZ {
  static_assert((Mod >> 31) == 0, "`Mod` must less than 2^(31)");
  template<typename Int> static unsigned safe_mod(Int a) {
    if ((a%=(int)Mod) < 0) a += (int)Mod;
    return a;
  }
  struct PrivateCtor {};
  static inline PrivateCtor p{};
  ZZ(PrivateCtor, unsigned a) : a_(a) {}
  unsigned a_;

public:
  static unsigned mod() { return Mod; }
  static ZZ from_raw(unsigned a) { return ZZ(p, a); }
  ZZ() : a_() {}
  template<typename Int> ZZ(Int a) : a_(safe_mod(a)) {}
  unsigned val() const { return a_; }
  ZZ operator-() const { return from_raw(a_==0 ? a_ : Mod-a_); }
  ZZ pow(long long e) const {
    if (e<0) return inv().pow(-e);
    for (ZZ x(*this), y(from_raw(1));; x *= x) {
      if (e&1) y *= x;
      if ((e/=2) == 0) return y;
    }
  }
  ZZ inv() const {
    int s = 1, t = 0, a = val(), b = Mod;
    while (b) {
      const int q = a/b;
      s = std::exchange(t, s - q*t);
      a = std::exchange(b, a - q*b);
    }
    return from_raw(s<0 ? s+(int)Mod : s);
  }
  ZZ &operator+=(const ZZ &R) { if ((a_+=R.a_) >= Mod) a_ -= Mod; return *this; }
  ZZ &operator-=(const ZZ &R) { if ((a_+=Mod-R.a_) >= Mod) a_ -= Mod; return *this; }
  ZZ &operator*=(const ZZ &R) { a_ = (unsigned long long)a_*R.a_ % Mod; return *this; }
  ZZ &operator/=(const ZZ &R) { return *this *= R.inv(); }
  friend ZZ operator+(const ZZ &L, const ZZ &R) { return ZZ(L) += R; }
  friend ZZ operator-(const ZZ &L, const ZZ &R) { return ZZ(L) -= R; }
  friend ZZ operator*(const ZZ &L, const ZZ &R) { return ZZ(L) *= R; }
  friend ZZ operator/(const ZZ &L, const ZZ &R) { return ZZ(L) /= R; }
  friend bool operator==(const ZZ &L, const ZZ &R) { return L.val() == R.val(); }
  friend bool operator!=(const ZZ &L, const ZZ &R) { return L.val() != R.val(); }
  friend std::istream &operator>>(std::istream &L, ZZ &R) { int a; L >> a; R.a_ = safe_mod(a); return L; }
  friend std::ostream &operator<<(std::ostream &L, const ZZ &R) { return L << R.val(); }
};

using MInt = ZZ<998244353>;

// only works for odd prime moduli
bool is_square(MInt A) { return A.pow((A.mod()-1)/2) != MInt::from_raw(A.mod()-1); }
MInt quadratic_nonresidue() {
  for (int i = 2;; ++i) {
    const MInt a = i;
    if (!is_square(a)) return a;
  }
}
std::vector<MInt> sqrt(MInt A) {
  if (MInt::mod() == 2 || A == 0) return {A};
  if (!is_square(A)) return {};
  if (MInt::mod()%4 == 3) {
    const MInt res = A.pow((MInt::mod()+1) / 4);
    return {res, -res};
  }
  MInt t = 1;
  while (is_square(t*t - 4*A)) t += 1;
  MInt k0 = 1, k1, k2 = -t, k3 = A;
  for (int e = (MInt::mod()+1) / 2;; k2 = k3+k3 - k2*k2, k3 *= k3) {
    if (e&1) k0 = k1 - k0*k2, k1 *= k3;
    else k1 = k0*k3 - k1*k2;
    if ((e/=2) == 0) return {k0, -k0};
  }
}

class Binomial {
  std::vector<MInt> factorial_ = {MInt(1)};
  std::vector<MInt> invfactorial_ = {MInt(1)};

public:
  void ensure(int N) {
    const int NN = factorial_.size();
    if (NN < N) {
      int k = NN;
      while (k < N) k *= 2;
      k = std::min<long long>(k, MInt::mod());
      factorial_.resize(k);
      invfactorial_.resize(k);
      for (int i = NN; i < k; ++i) factorial_[i] = factorial_[i-1] * i;
      invfactorial_.back() = factorial_.back().inv();
      for (int i = k-2; i >= NN; --i) invfactorial_[i] = invfactorial_[i+1] * (i+1);
    }
  }

  MInt binom(int N, int K) const { return N<K ? MInt() : factorial_[N]*invfactorial_[K]*invfactorial_[N-K]; }
  MInt inv(int N) const { return factorial_[N-1] * invfactorial_[N]; }
  MInt factorial(int N) const { return factorial_[N]; }
  MInt inv_factorial(int N) const { return invfactorial_[N]; }
} BIN;

class FftInfo {
  const int ordlog2_ = __builtin_ctzll(MInt::mod()-1);
  const MInt zeta_ = quadratic_nonresidue().pow((MInt::mod()-1) >> ordlog2_);
  const MInt invzeta_ = zeta_.inv();
  const MInt imag_ = zeta_.pow(1LL << (ordlog2_-2));
  const MInt invimag_ = -imag_;
  mutable std::vector<MInt> root_ = {MInt::from_raw(1), imag_};
  mutable std::vector<MInt> invroot_ = {MInt::from_raw(1), invimag_};

public:
  // [0, N)
  const std::vector<MInt> &root(int N) const {
    assert((N & (N-1)) == 0);
    const int S = root_.size();
    if (S < N) {
      root_.resize(N);
      for (int i = __builtin_ctz(S); (1<<i) < N; ++i) {
        const int j = 1<<i;
        root_[j] = zeta_.pow(1LL << (ordlog2_-i-2));
        for (int k = j+1; k < j*2; ++k) root_[k] = root_[k-j] * root_[j];
      }
    }
    return root_;
  }
  // [0, N)
  const std::vector<MInt> &inv_root(int N) const {
    assert((N & (N-1)) == 0);
    const int S = invroot_.size();
    if (S < N) {
      invroot_.resize(N);
      for (int i = __builtin_ctz(S); (1<<i) < N; ++i) {
        const int j = 1<<i;
        invroot_[j] = invzeta_.pow(1LL << (ordlog2_-i-2));
        for (int k = j+1; k < j*2; ++k) invroot_[k] = invroot_[k-j] * invroot_[j];
      }
    }
    return invroot_;
  }
} FFT_INFO;

int fft_len(int N) {
  if (N==0) return 0;
  --N; N |= N>>1; N |= N>>2; N |= N>>4; N |= N>>8; N |= N>>16;
  return ++N;
}

void butterfly_n(std::vector<MInt>::iterator A, int N, const std::vector<MInt> &root) {
  assert((N & (N-1)) == 0);
  for (int j = 0; j < N/2; ++j) {
    const MInt u = A[j], v = A[j + N/2];
    A[j] = u+v, A[j + N/2] = u-v;
  }
  for (int i = N/2; i >= 2; i /= 2) {
    for (int j = 0; j < i/2; ++j) {
      const MInt u = A[j], v = A[j + i/2];
      A[j] = u+v, A[j + i/2] = u-v;
    }
    for (int j = i, m = 1; j < N; j += i, ++m)
      for (int k = j; k < j + i/2; ++k) {
        const MInt u = A[k], v = A[k + i/2] * root[m];
        A[k] = u+v, A[k + i/2] = u-v;
      }
  }
}

void inv_butterfly_n(std::vector<MInt>::iterator A, int N, const std::vector<MInt> &root) {
  assert((N & (N-1)) == 0);
  for (int i = 2; i < N; i *= 2) {
    for (int j = 0; j < i/2; ++j) {
      const MInt u = A[j], v = A[j + i/2];
      A[j] = u+v, A[j + i/2] = u-v;
    }
    for (int j = i, m = 1; j < N; j += i, ++m)
      for (int k = j; k < j + i/2; ++k) {
        const MInt u = A[k], v = A[k + i/2];
        A[k] = u+v, A[k + i/2] = (u-v) * root[m];
      }
  }
  for (int j = 0; j < N/2; ++j) {
    const MInt u = A[j], v = A[j + N/2];
    A[j] = u+v, A[j + N/2] = u-v;
  }
}

void fft_n(std::vector<MInt>::iterator A, int N) { butterfly_n(A, N, FFT_INFO.root(N/2)); }
void inv_fft_n(std::vector<MInt>::iterator A, int N) {
  inv_butterfly_n(A, N, FFT_INFO.inv_root(N/2));
  const MInt iv = MInt(N).inv();
  for (int i = 0; i < N; ++i) A[i] *= iv;
}

void fft(std::vector<MInt> &A) { fft_n(A.begin(), A.size()); }
void inv_fft(std::vector<MInt> &A) { inv_fft_n(A.begin(), A.size()); }

// returns coefficients generated by closure
// closure: gen(index, current_product)
template<typename Closure> std::vector<MInt>
semi_relaxed_conv(const std::vector<MInt> &A, Closure Gen, int N) {
  enum { BaseCaseSize = 32 };
  static_assert((BaseCaseSize & (BaseCaseSize - 1)) == 0);
  static const int Block[] = {16, 16, 16, 16, 16};
  // returns (which_block, level, blocksize)
  auto blockinfo = [](int ind) {
    int i = ind / BaseCaseSize, lv = 0, blocksize = BaseCaseSize;
    while ((i & (Block[lv] - 1)) == 0) i /= Block[lv], blocksize *= Block[lv], ++lv;
    return std::make_tuple(i & (Block[lv]-1), lv, blocksize);
  };
  std::vector<MInt> B(N), AB(N);
  std::vector<std::vector<std::vector<MInt>>> dftA, dftB;
  for (int i = 0; i < N; ++i) {
    const int S = i & (BaseCaseSize-1);
    // blocked contribution
    if (i >= BaseCaseSize && S == 0) {
      const auto [j, lv, blocksize]  = blockinfo(i);
      if (blocksize * j == i) {
        if ((int)dftA.size() == lv) {
          dftA.emplace_back();
          dftB.emplace_back(Block[lv]-1);
        }
        if ((j-1) * blocksize < (int)A.size()) {
          dftA[lv].emplace_back(A.begin() + (j-1) * blocksize,
                                A.begin() + std::min<int>((j+1) * blocksize, A.size()))
                  .resize(blocksize * 2);
          fft(dftA[lv][j-1]);
        }
      }
      // if A is not empty, ...
      if (!dftA[lv].empty()) {
        dftB[lv][j-1].resize(blocksize*2);
        std::fill_n(std::copy_n(B.begin() + (i-blocksize), blocksize, dftB[lv][j-1].begin()), blocksize, MInt());
        fft(dftB[lv][j-1]);
        // middle product
        std::vector<MInt> mp(blocksize*2);
        for (int k = 0; k < std::min<int>(j, dftA[lv].size()); ++k)
          for (int l = 0; l < blocksize*2; ++l)
            mp[l] += dftA[lv][k][l] * dftB[lv][j-1-k][l];
        inv_fft(mp);
        for (int k = 0; k < blocksize && i+k < N; ++k) AB[i+k] += mp[k+blocksize];
      }
    }
    // basecase contribution
    for (int j = std::max(i-S, i-(int)A.size()+1); j < i; ++j) AB[i] += A[i-j] * B[j];
    B[i] = Gen(i, AB);
    if (!A.empty()) AB[i] += A[0] * B[i];
  }
  return B;
}

// Polynomial operations:
//    add(+), sub(-), mul(*), quo(/), rem(%), shl(<<=), shr(>>=) <- auto shrink
//    taylor_shift                                               <- no shrink
// Formal Power Series operations:
//    inv, div, log, exp                                         <- no shrink
class Poly : public std::vector<MInt> {
  using Base = std::vector<MInt>;
  using Base::Base;

  Poly &mul_naive(const Poly &B) {
    const int degA = deg();
    const int degB = B.deg();
    if (degA < 0 || degB < 0) {
      clear();
      return *this;
    }
    Poly AB(degA+degB+1);
    for (int i = 0; i <= degA; ++i)
      for (int j = 0; j <= degB; ++j)
        AB[i+j] += (*this)[i] * B[j];
    swap(AB);
    return *this;
  }

  Poly &mul_fft(Poly B) {
    const int degA = deg();
    const int degB = B.deg();
    if (degA < 0 || degB < 0) {
      clear();
      return *this;
    }
    const int len = fft_len(degA+degB+1);
    resize(len);
    B.resize(len);
    fft(*this);
    fft(B);
    for (int i = 0; i < len; ++i) (*this)[i] *= B[i];
    inv_fft(*this);
    resize(degA+degB+1);
    return *this;
  }

  Poly &square_fft() {
    const int degA = deg();
    if (degA < 0) return *this;
    const int len = fft_len(degA*2 + 1);
    resize(len);
    fft(*this);
    for (int i = 0; i < len; ++i) (*this)[i] *= (*this)[i];
    inv_fft(*this);
    resize(degA*2 + 1);
    return *this;
  }

  // returns (quotient, remainder)
  // O(deg(Q)deg(B))
  std::array<Poly, 2> euclid_div_naive(const Poly &B) const {
    const int degA = deg();
    const int degB = B.deg();
    assert(degB >= 0);
    const int degQ = degA-degB;
    if (degQ < 0) return {Poly{}, *this};
    Poly Q(degQ+1), R(*this);
    const MInt iv = B[degB].inv();
    for (int i = degQ, n = degA; i >= 0; --i)
      if ((Q[i] = R[n--] * iv) != 0)
        for (int j = 0; j <= degB; ++j)
          R[i+j] -= Q[i] * B[j];
    R.resize(degB);
    return {Q, R};
  }

  // O(min(deg(Q)^2,deg(Q)deg(B)))
  Poly euclid_div_quotient_naive(const Poly &B) const {
    const int degA = deg();
    const int degB = B.deg();
    assert(degB >= 0);
    const int degQ = degA-degB;
    if (degQ < 0) return {};
    Poly Q(degQ+1);
    const MInt iv = B[degB].inv();
    for (int i = 0; i <= degQ; ++i) {
      for (int j = 1; j <= std::min(i, degB); ++j)
        Q[degQ-i] += B[degB-j] * Q[degQ-i+j];
      Q[degQ-i] = ((*this)[degA-i]-Q[degQ-i]) * iv;
    }
    return Q;
  }

public:
  int deg() const {
    int N = (int)size()-1;
    while (N >= 0 && (*this)[N] == 0) --N;
    return N;
  }
  int ord() const {
    for (int N = 0; N < (int)size(); ++N)
      if ((*this)[N] != 0) return N;
    return -1;
  }
  Poly rev() const {
    return Poly(std::make_reverse_iterator(begin()+(deg()+1)),
                std::make_reverse_iterator(begin()));
  }
  Poly rev(int N) const {
    Poly res = trunc(N);
    std::reverse(res.begin(), res.end());
    return res;
  }
  Poly slice(int L, int R) const {
    Poly res(R-L);
    for (int i = L; i < std::min<int>(R, size()); ++i) res[i-L] = (*this)[i];
    return res;
  }
  Poly trunc(int D) const { return slice(0, D); }
  Poly &shrink() {
    resize(deg()+1);
    return *this;
  }
  MInt lc() const {
    const int D = deg();
    return D<0 ? MInt() : (*this)[D];
  }

  Poly deriv() const {
    const int N = (int)size()-1;
    if (N <= 0) return {};
    Poly res(N);
    for (int i = 1; i <= N; ++i) res[i-1] = (*this)[i] * i;
    return res;
  }
  Poly integr(MInt c = 0) const {
    const int N = (int)size()+1;
    BIN.ensure(N);
    Poly res(N);
    res[0] = c;
    for (int i = 1; i < N; ++i) res[i] = (*this)[i-1] * BIN.inv(i);
    return res;
  }

  Poly taylor_shift(MInt c) const {
    if (c == 0) return Poly(*this);
    Poly A(*this);
    const int N = A.size();
    BIN.ensure(N);
    for (int i = 0; i < N; ++i) A[i] *= BIN.factorial(i);
    MInt cc = 1;
    Poly B(N);
    for (int i = 0; i < N; ++i) {
      B[i] = cc * BIN.inv_factorial(i);
      cc *= c;
    }
    std::reverse(A.begin(), A.end());
    A.mul_assign(B);
    A.resize(N);
    std::reverse(A.begin(), A.end());
    for (int i = 0; i < N; ++i) A[i] *= BIN.inv_factorial(i);
    return A;
  }

  Poly inv(int N) const {
    assert(N >= 0);
    assert(ord() == 0);
    auto Gen = [iv = (*this)[0].inv()](int N, const std::vector<MInt> &C) {
      return N==0 ? iv : -C[N]*iv;
    };
    const std::vector<MInt> res = semi_relaxed_conv(*this, Gen, N);
    return Poly(res.begin(), res.end());
  }

  Poly div(const Poly &R, int N) const {
    assert(N >= 0);
    assert(R.ord() == 0);
    auto Gen = [this, iv = R[0].inv()](int N, const std::vector<MInt> &C) {
      return (N<(int)size() ? ((*this)[N]-C[N]) : -C[N]) * iv;
    };
    const std::vector<MInt> res = semi_relaxed_conv(R, Gen, N);
    return Poly(res.begin(), res.end());
  }

  Poly log(int N) const {
    assert(N >= 0);
    assert(ord() == 0);
    assert((*this)[0] == 1);
    if (N == 0) return {};
    return deriv().div(*this, N-1).integr();
  }

  Poly exp(int N) const {
    assert(N >= 0);
    assert(ord() != 0);
    BIN.ensure(N);
    auto Gen = [](int N, const std::vector<MInt> &C) {
      return N==0 ? MInt(1) : C[N-1]*BIN.inv(N);
    };
    const std::vector<MInt> res = semi_relaxed_conv(deriv(), Gen, N);
    return Poly(res.begin(), res.end());
  }

  Poly pow1(long long e, int N) const {
    assert(N >= 0);
    assert(ord() == 0);
    assert((*this)[0] == 1);
    return log(N).mul(Poly{MInt(e)}).exp(N);
  }

  Poly pow(long long e, int N) {
    assert(e >= 0);
    assert(N >= 0);
    if (e == 0) return Poly{MInt(1)}.trunc(N);
    const int O = ord();
    if (O < 0 || O > N/e || (O == N/e && N%e == 0)) return Poly(N);
    return shr(O).mul(Poly{(*this)[O].inv()})
                 .pow1(e, N - O*e)
                 .mul(Poly{(*this)[O].pow(e)})
                 .shl(O*e)
                 .trunc(N);
  }

  std::array<Poly, 2> euclid_div(const Poly &B) const {
    const int degA = deg();
    const int degB = B.deg();
    assert(degB >= 0);
    const int degQ = degA-degB;
    if (degQ < 0) return {Poly{}, *this};
    if (degQ <= 60 || degB <= 60) return euclid_div_naive(B);
    const Poly Q = rev().div(B.rev(), degQ+1).rev(degQ+1);
    auto make_cyclic = [](const Poly &A, int N) {
      assert((N & (N-1)) == 0);
      Poly B(N);
      for (int i = 0; i < (int)A.size(); ++i) B[i & (N-1)] += A[i];
      return B;
    };
    assert(degB > 0);
    const int len = fft_len(degB);
    Poly cyclicA = make_cyclic(*this, len);
    Poly cyclicB = make_cyclic(B, len);
    Poly cyclicQ = make_cyclic(Q, len);
    fft(cyclicB);
    fft(cyclicQ);
    for (int i = 0; i < len; ++i) cyclicQ[i] *= cyclicB[i];
    inv_fft(cyclicQ);
    cyclicA.resize(degB);
    // R=A-QB (mod (x^n - 1)) (n >= deg(B))
    for (int i = 0; i < degB; ++i) cyclicA[i] -= cyclicQ[i];
    cyclicA.shrink();
    return {Q, cyclicA};
  }

  Poly neg() const {
    const int D = deg();
    Poly res(D+1);
    for (int i = 0; i <= D; ++i) res[i] = -(*this)[i];
    return res;
  }
  Poly add(const Poly &B) const { return Poly(*this).add_assign(B); }
  Poly sub(const Poly &B) const { return Poly(*this).sub_assign(B); }
  Poly mul(const Poly &B) const { return Poly(*this).mul_assign(B); }
  Poly quo(const Poly &B) const { return Poly(*this).quo_assign(B); }
  Poly rem(const Poly &B) const { return Poly(*this).rem_assign(B); }
  Poly shl(int D) const { return Poly(*this).shl_assign(D); }
  Poly shr(int D) const { return Poly(*this).shr_assign(D); }

  Poly &add_assign(const Poly &B) {
    if (size() < B.size()) resize(B.size());
    for (int i = 0; i < (int)B.size(); ++i) (*this)[i] += B[i];
    return shrink();
  }
  Poly &sub_assign(const Poly &B) {
    if (size() < B.size()) resize(B.size());
    for (int i = 0; i < (int)B.size(); ++i) (*this)[i] -= B[i];
    return shrink();
  }
  Poly &mul_assign(const Poly &B) {
    if (deg() <= 60 || B.deg() <= 60) return mul_naive(B);
    if (std::addressof(*this) == std::addressof(B)) return square_fft();
    return mul_fft(B);
  }
  Poly &quo_assign(const Poly &B) {
    const int degA = deg();
    const int degB = B.deg();
    assert(degB >= 0);
    const int degQ = degA-degB;
    if (degQ <= 60 || degB <= 60) return *this = euclid_div_quotient_naive(B);
    return *this = rev().div(B.rev(), degQ+1).rev(degQ+1);
  }
  Poly &rem_assign(const Poly &B) { return *this = std::get<1>(euclid_div(B)); }
  Poly &shl_assign(int D) {
    if (D > 0) {
      insert(begin(), D, MInt());
    } else if (D < 0) {
      if (-D < (int)size()) erase(begin(), begin() + (-D));
      else clear();
    }
    return shrink();
  }
  Poly &shr_assign(int D) { return shl_assign(-D); }

  friend std::ostream &operator<<(std::ostream &L, const Poly &R) {
    L << '[';
    const int D = R.deg();
    if (D < 0) {
      L << '0';
    } else {
      for (int i = 0; i <= D; ++i) {
        L << R[i];
        if (i == 1) L << "*x";
        if (i >  1) L << "*x^" << i;
        if (i != D) L << " + ";
      }
    }
    return L << ']';
  }
};

// returns F(G) mod x^N
// see:
// [1]: Yasunori Kinoshita, Baitian Li. Power Series Composition in Near-Linear Time.
//      https://arxiv.org/abs/2404.05177
Poly composition(const Poly &F, const Poly &G, int N) {
  if (N == 0) return {};
  // [y^(-1)] (f(y) / (-g(x) + y)) mod x^N in R[x]((y^(-1)))
  auto rec = [](auto &&rec, const Poly &P, const Poly &Q, int D, int N) {
    assert((int)P.size() == D*N);
    assert((int)Q.size() == D*N);
    if (N == 1) return P;
    Poly dftQ(D*N*4);
    for (int i = 0; i < D; ++i)
      for (int j = 0; j < N; ++j)
        dftQ[i*N*2 + j] = Q[i*N + j];
    dftQ[D*N*2] = 1;
    fft(dftQ);
    Poly V(D*N*2);
    for (int i = 0; i < D*N*4; i += 2) V[i/2] = dftQ[i] * dftQ[i+1];
    inv_fft(V);
    V[0] -= 1;
    for (int i = 1; i < D*2; ++i)
      for (int j = 0; j < N/2; ++j)
        V[i*(N/2) + j] = V[i*N + j];
    V.resize(D*N);
    const Poly T = rec(rec, P, V, D*2, N/2);
    Poly dftT(D*N*2);
    for (int i = 0; i < D*2; ++i)
      for (int j = 0; j < N/2; ++j)
        dftT[i*N + j] = T[i*(N/2) + j];
    fft(dftT);
    Poly U(D*N*4);
    for (int i = 0; i < D*N*4; i += 2) {
      U[i] = dftT[i/2] * dftQ[i+1];
      U[i+1] = dftT[i/2] * dftQ[i];
    }
    inv_fft(U);
    for (int i = 0; i < D; ++i)
      for (int j = 0; j < N; ++j)
        U[i*N + j] = U[(i+D)*(N*2) + j];
    U.resize(D*N);
    return U;
  };
  const int L = fft_len(N);
  const MInt c = G.empty() ? MInt() : G[0];
  return rec(rec, F.taylor_shift(c).trunc(L), G.sub(Poly{c}).neg().trunc(L), 1, L).trunc(N);
}

}
// clang-format on
