// C++17 & GCC/Clang

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <memory>
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
  void preprocess(int N) {
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

  Poly taylor_shift(MInt c) const {
    Poly A(*this);
    const int N = A.size();
    BIN.preprocess(N);
    for (int i = 0; i < N; ++i) A[i] *= BIN.factorial(i);
    MInt cc = 1;
    Poly B(N);
    for (int i = 0; i < N; ++i) {
      B[i] = cc * BIN.inv_factorial(i);
      cc *= c;
    }
    std::reverse(A.begin(), A.end());
    Poly AB = A*B;
    AB.resize(N);
    std::reverse(AB.begin(), AB.end());
    for (int i = 0; i < N; ++i) AB[i] *= BIN.inv_factorial(i);
    return AB;
  }

  // FPS operation
  // see:
  // [1]: 关于优化形式幂级数计算的 Newton 法的常数
  //      https://negiizhao.blog.uoj.ac/blog/4671
  Poly inv(int N) const {
    // total cost = 10 E(N)
    assert(N >= 0);
    assert(ord() == 0);
    if (N == 0) return {};
    const int len = fft_len(N);
    Poly invL(len), shopA(len), shopB(len);
    invL[0] = (*this)[0].inv();
    // total cost = cost of last iteration * 2
    for (int i = 2; i <= len; i *= 2) {
      std::fill(std::copy_n(begin(), std::min<int>(size(), i), shopA.begin()),
                shopA.begin() + i, MInt());
      std::copy_n(invL.begin(), i, shopB.begin());
      fft_n(shopA.begin(), i); // E(N)
      fft_n(shopB.begin(), i); // E(N)
      for (int j = 0; j < i; ++j) shopA[j] *= shopB[j];
      inv_fft_n(shopA.begin(), i); // E(N)
      std::fill_n(shopA.begin(), i/2, MInt());
      fft_n(shopA.begin(), i); // E(N)
      for (int j = 0; j < i; ++j) shopA[j] *= shopB[j];
      inv_fft_n(shopA.begin(), i); // E(N)
      for (int j = i/2; j < i; ++j) invL[j] = -shopA[j];
    }
    return invL.trunc(N);
  }

  // see:
  // [1]: 关于优化形式幂级数计算的 Newton 法的常数
  //      https://negiizhao.blog.uoj.ac/blog/4671
  Poly div(const Poly &R, int N) const {
    // total cost = 13 E(N)
    assert(N >= 0);
    assert(R.ord() == 0);
    if (N == 1) return {(*this)[0]/R[0]};
    const int len = fft_len(N);
    Poly LdivR(len);
    Poly shopA = R.inv(len/2); // 5 E(N)
    Poly shopB = trunc(len/2);
    Poly shopC = R.trunc(len);
    shopA.resize(len);
    fft(shopA); // E(N)
    shopB.resize(len);
    fft(shopB); // E(N)
    for (int i = 0; i < len; ++i) shopB[i] *= shopA[i];
    inv_fft(shopB); // E(N)
    std::copy_n(shopB.begin(), len/2, LdivR.begin());
    std::fill_n(shopB.begin() + len/2, len/2, MInt());
    fft(shopB); // E(N)
    fft(shopC); // E(N)
    for (int i = 0; i < len; ++i) shopC[i] *= shopB[i];
    inv_fft(shopC); // E(N)
    std::fill_n(shopC.begin(), len/2, MInt());
    for (int i = len/2; i < std::min<int>(len, size()); ++i) shopC[i] = (*this)[i] - shopC[i];
    for (int i = std::min<int>(len, size()); i < len; ++i) shopC[i] = -shopC[i];
    fft(shopC); // E(N)
    for (int i = 0; i < len; ++i) shopC[i] *= shopA[i];
    inv_fft(shopC); // E(N)
    std::copy_n(shopC.begin() + len/2, len/2, LdivR.begin() + len/2);
    LdivR.resize(N);
    return LdivR;
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

  Poly operator-() const {
    const int D = deg();
    Poly res(D+1);
    for (int i = 0; i <= D; ++i) res[i] = -(*this)[i];
    return res;
  }
  Poly &operator+=(const Poly &B) {
    if (size() < B.size()) resize(B.size());
    for (int i = 0; i < (int)B.size(); ++i) (*this)[i] += B[i];
    return shrink();
  }
  Poly &operator-=(const Poly &B) {
    if (size() < B.size()) resize(B.size());
    for (int i = 0; i < (int)B.size(); ++i) (*this)[i] -= B[i];
    return shrink();
  }
  Poly &operator*=(const Poly &B) {
    if (deg() <= 60 || B.deg() <= 60) return mul_naive(B);
    if (std::addressof(*this) == std::addressof(B)) return square_fft();
    return mul_fft(B);
  }
  Poly &operator/=(const Poly &B) {
    const int degA = deg();
    const int degB = B.deg();
    assert(degB >= 0);
    const int degQ = degA-degB;
    if (degQ <= 60 || degB <= 60) return *this = euclid_div_quotient_naive(B);
    return *this = rev().div(B.rev(), degQ+1).rev(degQ+1);
  }
  Poly &operator%=(const Poly &B) { return *this = std::get<1>(euclid_div(B)); }

  Poly &operator<<=(int D) {
    if (D > 0) {
      insert(begin(), D, MInt());
    } else if (D < 0) {
      if (-D < (int)size()) erase(begin(), begin() + (-D));
      else clear();
    }
    return shrink();
  }
  Poly &operator>>=(int D) { return operator<<=(-D); }
  friend Poly operator+(const Poly &L, const Poly &R) { return Poly(L) += R; }
  friend Poly operator-(const Poly &L, const Poly &R) { return Poly(L) -= R; }
  friend Poly operator*(const Poly &L, const Poly &R) { return Poly(L) *= R; }
  friend Poly operator/(const Poly &L, const Poly &R) { return Poly(L) /= R; }
  friend Poly operator%(const Poly &L, const Poly &R) { return Poly(L) %= R; }
  friend Poly operator<<(const Poly &L, int D) { return Poly(L) <<= D; }
  friend Poly operator>>(const Poly &L, int D) { return Poly(L) >>= D; }
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

}
// clang-format on
