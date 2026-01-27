---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: batch_inv.hpp
    title: batch_inv.hpp
  - icon: ':heavy_check_mark:'
    path: binomial.hpp
    title: binomial.hpp
  - icon: ':heavy_check_mark:'
    path: fft.hpp
    title: FFT
  - icon: ':heavy_check_mark:'
    path: middle_product.hpp
    title: Middle Product
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: poly_interpolation.hpp
    title: Polynomial Interpolation (Lagrange Interpolation)
  - icon: ':heavy_check_mark:'
    path: shift_sample_points.hpp
    title: Shift Sample Points
  - icon: ':heavy_check_mark:'
    path: sqrt_int.hpp
    title: sqrt_int.hpp
  - icon: ':heavy_check_mark:'
    path: swag.hpp
    title: swag.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/factorial
    links:
    - https://judge.yosupo.jp/problem/factorial
  bundledCode: "#line 1 \"test/enumerative_combinatorics/factorial.0.test.cpp\"\n\
    #define PROBLEM \"https://judge.yosupo.jp/problem/factorial\"\n\n#line 2 \"modint.hpp\"\
    \n\n#include <iostream>\n#include <type_traits>\n\n// clang-format off\ntemplate<unsigned\
    \ Mod> class ModInt {\n    static_assert((Mod >> 31) == 0, \"`Mod` must less than\
    \ 2^(31)\");\n    template<typename Int>\n    static std::enable_if_t<std::is_integral_v<Int>,\
    \ unsigned> safe_mod(Int v) { using D = std::common_type_t<Int, unsigned>; return\
    \ (v %= (int)Mod) < 0 ? (D)(v + (int)Mod) : (D)v; }\n    struct PrivateConstructor\
    \ {} static inline private_constructor{};\n    ModInt(PrivateConstructor, unsigned\
    \ v) : v_(v) {}\n    unsigned v_;\n\npublic:\n    static unsigned mod() { return\
    \ Mod; }\n    static ModInt from_raw(unsigned v) { return ModInt(private_constructor,\
    \ v); }\n    static ModInt zero() { return from_raw(0); }\n    static ModInt one()\
    \ { return from_raw(1); }\n    bool is_zero() const { return v_ == 0; }\n    bool\
    \ is_one() const { return v_ == 1; }\n    ModInt() : v_() {}\n    template<typename\
    \ Int, typename std::enable_if_t<std::is_signed_v<Int>, int> = 0> ModInt(Int v)\
    \ : v_(safe_mod(v)) {}\n    template<typename Int, typename std::enable_if_t<std::is_unsigned_v<Int>,\
    \ int> = 0> ModInt(Int v) : v_(v % Mod) {}\n    unsigned val() const { return\
    \ v_; }\n    ModInt operator-() const { return from_raw(v_ == 0 ? v_ : Mod - v_);\
    \ }\n    ModInt pow(long long e) const { if (e < 0) return inv().pow(-e); for\
    \ (ModInt x(*this), res(from_raw(1));; x *= x) { if (e & 1) res *= x; if ((e >>=\
    \ 1) == 0) return res; }}\n    ModInt inv() const { int x1 = 1, x3 = 0, a = val(),\
    \ b = Mod; while (b) { const int q = a / b, x1_old = x1, a_old = a; x1 = x3, x3\
    \ = x1_old - x3 * q, a = b, b = a_old - b * q; } return from_raw(x1 < 0 ? x1 +\
    \ (int)Mod : x1); }\n    template<bool Odd = (Mod & 1)> std::enable_if_t<Odd,\
    \ ModInt> div_by_2() const { if (v_ & 1) return from_raw((v_ + Mod) >> 1); return\
    \ from_raw(v_ >> 1); }\n    ModInt &operator+=(const ModInt &a) { if ((v_ += a.v_)\
    \ >= Mod) v_ -= Mod; return *this; }\n    ModInt &operator-=(const ModInt &a)\
    \ { if ((v_ += Mod - a.v_) >= Mod) v_ -= Mod; return *this; }\n    ModInt &operator*=(const\
    \ ModInt &a) { v_ = (unsigned long long)v_ * a.v_ % Mod; return *this; }\n   \
    \ ModInt &operator/=(const ModInt &a) { return *this *= a.inv(); }\n    ModInt\
    \ &operator++() { return *this += one(); }\n    ModInt operator++(int) { ModInt\
    \ o(*this); *this += one(); return o; }\n    ModInt &operator--() { return *this\
    \ -= one(); }\n    ModInt operator--(int) { ModInt o(*this); *this -= one(); return\
    \ o; }\n    friend ModInt operator+(const ModInt &a, const ModInt &b) { return\
    \ ModInt(a) += b; }\n    friend ModInt operator-(const ModInt &a, const ModInt\
    \ &b) { return ModInt(a) -= b; }\n    friend ModInt operator*(const ModInt &a,\
    \ const ModInt &b) { return ModInt(a) *= b; }\n    friend ModInt operator/(const\
    \ ModInt &a, const ModInt &b) { return ModInt(a) /= b; }\n    friend bool operator==(const\
    \ ModInt &a, const ModInt &b) { return a.v_ == b.v_; }\n    friend bool operator!=(const\
    \ ModInt &a, const ModInt &b) { return a.v_ != b.v_; }\n    friend std::istream\
    \ &operator>>(std::istream &a, ModInt &b) { int v; a >> v; b.v_ = safe_mod(v);\
    \ return a; }\n    friend std::ostream &operator<<(std::ostream &a, const ModInt\
    \ &b) { return a << b.val(); }\n};\n// clang-format on\n#line 2 \"poly_interpolation.hpp\"\
    \n\n#line 2 \"batch_inv.hpp\"\n\n#include <cassert>\n#include <vector>\n\ntemplate<typename\
    \ Tp> inline std::vector<Tp> batch_inv(const std::vector<Tp> &a) {\n    if (a.empty())\
    \ return {};\n    const int n = a.size();\n    std::vector<Tp> b(n);\n    Tp v\
    \ = 1;\n    for (int i = 0; i < n; ++i) b[i] = v, v *= a[i];\n    assert(v !=\
    \ 0);\n    v = v.inv();\n    for (int i = n - 1; i >= 0; --i) b[i] *= v, v *=\
    \ a[i];\n    return b;\n}\n#line 2 \"binomial.hpp\"\n\n#include <algorithm>\n\
    #line 5 \"binomial.hpp\"\n\ntemplate<typename Tp> class Binomial {\n    std::vector<Tp>\
    \ factorial_, invfactorial_;\n\n    Binomial() : factorial_{Tp(1)}, invfactorial_{Tp(1)}\
    \ {}\n\n    void preprocess(int n) {\n        if (const int nn = factorial_.size();\
    \ nn < n) {\n            int k = nn;\n            while (k < n) k *= 2;\n    \
    \        k = std::min<long long>(k, Tp::mod());\n            factorial_.resize(k);\n\
    \            invfactorial_.resize(k);\n            for (int i = nn; i < k; ++i)\
    \ factorial_[i] = factorial_[i - 1] * i;\n            invfactorial_.back() = factorial_.back().inv();\n\
    \            for (int i = k - 2; i >= nn; --i) invfactorial_[i] = invfactorial_[i\
    \ + 1] * (i + 1);\n        }\n    }\n\npublic:\n    static const Binomial &get(int\
    \ n) {\n        static Binomial bin;\n        bin.preprocess(n);\n        return\
    \ bin;\n    }\n\n    Tp binom(int n, int m) const {\n        return n < m ? Tp()\
    \ : factorial_[n] * invfactorial_[m] * invfactorial_[n - m];\n    }\n    Tp inv(int\
    \ n) const { return factorial_[n - 1] * invfactorial_[n]; }\n    Tp factorial(int\
    \ n) const { return factorial_[n]; }\n    Tp inv_factorial(int n) const { return\
    \ invfactorial_[n]; }\n};\n#line 7 \"poly_interpolation.hpp\"\n\n// returns f\n\
    // x: x_0,...\n// y: f(x_0),...\ntemplate<typename Tp> inline std::vector<Tp>\n\
    lagrange_interpolation_naive(const std::vector<Tp> &x, const std::vector<Tp> &y)\
    \ {\n    assert(x.size() == y.size());\n    const int n = x.size();\n    std::vector<Tp>\
    \ M(n + 1), xx(n), f(n);\n    M[0] = 1;\n    for (int i = 0; i < n; ++i)\n   \
    \     for (int j = i; j >= 0; --j) M[j + 1] += M[j], M[j] *= -x[i];\n    for (int\
    \ i = n - 1; i >= 0; --i)\n        for (int j = 0; j < n; ++j) xx[j] = xx[j] *\
    \ x[j] + M[i + 1] * (i + 1);\n    xx = batch_inv(xx);\n    for (int i = 0; i <\
    \ n; ++i) {\n        Tp t = y[i] * xx[i], k = M[n];\n        for (int j = n -\
    \ 1; j >= 0; --j) f[j] += k * t, k = M[j] + k * x[i];\n    }\n    return f;\n\
    }\n\n// returns f(c)\n// f: polynomial f -> f[0]=f(0),...\ntemplate<typename Tp>\
    \ inline Tp lagrange_interpolation_iota(const std::vector<Tp> &f, Tp c) {\n  \
    \  if (f.empty()) return 0;\n    const int n = f.size();\n    auto &&bin  = Binomial<Tp>::get(n);\n\
    \    std::vector<Tp> k(n);\n    k[0] = f[0];\n    Tp v = 1;\n    for (int i =\
    \ 1; i < n; ++i) k[i] = f[i] * (v *= (c - (i - 1)) * bin.inv(i));\n    Tp res\
    \ = k[n - 1];\n    v      = 1;\n    for (int i = n - 2; i >= 0; --i) res += k[i]\
    \ * (v *= -(c - (i + 1)) * bin.inv(n - 1 - i));\n    return res;\n}\n#line 2 \"\
    shift_sample_points.hpp\"\n\n#line 2 \"middle_product.hpp\"\n\n#line 2 \"fft.hpp\"\
    \n\n#line 5 \"fft.hpp\"\n#include <iterator>\n#include <memory>\n#line 8 \"fft.hpp\"\
    \n\ntemplate<typename Tp> class FftInfo {\n    static Tp least_quadratic_nonresidue()\
    \ {\n        for (int i = 2;; ++i)\n            if (Tp(i).pow((Tp::mod() - 1)\
    \ / 2) == -1) return Tp(i);\n    }\n\n    const int ordlog2_;\n    const Tp zeta_;\n\
    \    const Tp invzeta_;\n    const Tp imag_;\n    const Tp invimag_;\n\n    mutable\
    \ std::vector<Tp> root_;\n    mutable std::vector<Tp> invroot_;\n\n    FftInfo()\n\
    \        : ordlog2_(__builtin_ctzll(Tp::mod() - 1)),\n          zeta_(least_quadratic_nonresidue().pow((Tp::mod()\
    \ - 1) >> ordlog2_)),\n          invzeta_(zeta_.inv()), imag_(zeta_.pow(1LL <<\
    \ (ordlog2_ - 2))), invimag_(-imag_),\n          root_{Tp(1), imag_}, invroot_{Tp(1),\
    \ invimag_} {}\n\npublic:\n    static const FftInfo &get() {\n        static FftInfo\
    \ info;\n        return info;\n    }\n\n    Tp imag() const { return imag_; }\n\
    \    Tp inv_imag() const { return invimag_; }\n    Tp zeta() const { return zeta_;\
    \ }\n    Tp inv_zeta() const { return invzeta_; }\n    const std::vector<Tp> &root(int\
    \ n) const {\n        // [0, n)\n        assert((n & (n - 1)) == 0);\n       \
    \ if (const int s = root_.size(); s < n) {\n            root_.resize(n);\n   \
    \         for (int i = __builtin_ctz(s); (1 << i) < n; ++i) {\n              \
    \  const int j = 1 << i;\n                root_[j]    = zeta_.pow(1LL << (ordlog2_\
    \ - i - 2));\n                for (int k = j + 1; k < j * 2; ++k) root_[k] = root_[k\
    \ - j] * root_[j];\n            }\n        }\n        return root_;\n    }\n \
    \   const std::vector<Tp> &inv_root(int n) const {\n        // [0, n)\n      \
    \  assert((n & (n - 1)) == 0);\n        if (const int s = invroot_.size(); s <\
    \ n) {\n            invroot_.resize(n);\n            for (int i = __builtin_ctz(s);\
    \ (1 << i) < n; ++i) {\n                const int j = 1 << i;\n              \
    \  invroot_[j] = invzeta_.pow(1LL << (ordlog2_ - i - 2));\n                for\
    \ (int k = j + 1; k < j * 2; ++k) invroot_[k] = invroot_[k - j] * invroot_[j];\n\
    \            }\n        }\n        return invroot_;\n    }\n};\n\ninline int fft_len(int\
    \ n) {\n    --n;\n    n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8;\n  \
    \  return (n | n >> 16) + 1;\n}\n\nnamespace detail {\n\ntemplate<typename Iterator>\
    \ inline void\nbutterfly_n(Iterator a, int n,\n            const std::vector<typename\
    \ std::iterator_traits<Iterator>::value_type> &root) {\n    assert(n > 0);\n \
    \   assert((n & (n - 1)) == 0);\n    const int bn = __builtin_ctz(n);\n    if\
    \ (bn & 1) {\n        for (int i = 0; i < n / 2; ++i) {\n            const auto\
    \ a0 = a[i], a1 = a[i + n / 2];\n            a[i] = a0 + a1, a[i + n / 2] = a0\
    \ - a1;\n        }\n    }\n    for (int i = n >> (bn & 1); i >= 4; i /= 4) {\n\
    \        const int i4 = i / 4;\n        for (int k = 0; k < i4; ++k) {\n     \
    \       const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];\n            const\
    \ auto a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];\n            const auto a02p =\
    \ a0 + a2, a02m = a0 - a2;\n            const auto a13p = a1 + a3, a13m = (a1\
    \ - a3) * root[1];\n            a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p\
    \ - a13p;\n            a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;\n\
    \        }\n        for (int j = i, m = 2; j < n; j += i, m += 2) {\n        \
    \    const auto r = root[m], r2 = r * r, r3 = r2 * r;\n            for (int k\
    \ = j; k < j + i4; ++k) {\n                const auto a0 = a[k + i4 * 0], a1 =\
    \ a[k + i4 * 1] * r;\n                const auto a2 = a[k + i4 * 2] * r2, a3 =\
    \ a[k + i4 * 3] * r3;\n                const auto a02p = a0 + a2, a02m = a0 -\
    \ a2;\n                const auto a13p = a1 + a3, a13m = (a1 - a3) * root[1];\n\
    \                a[k + i4 * 0] = a02p + a13p, a[k + i4 * 1] = a02p - a13p;\n \
    \               a[k + i4 * 2] = a02m + a13m, a[k + i4 * 3] = a02m - a13m;\n  \
    \          }\n        }\n    }\n}\n\ntemplate<typename Iterator> inline void\n\
    inv_butterfly_n(Iterator a, int n,\n                const std::vector<typename\
    \ std::iterator_traits<Iterator>::value_type> &root) {\n    assert(n > 0);\n \
    \   assert((n & (n - 1)) == 0);\n    const int bn = __builtin_ctz(n);\n    for\
    \ (int i = 4; i <= (n >> (bn & 1)); i *= 4) {\n        const int i4 = i / 4;\n\
    \        for (int k = 0; k < i4; ++k) {\n            const auto a0 = a[k + i4\
    \ * 0], a1 = a[k + i4 * 1];\n            const auto a2 = a[k + i4 * 2], a3 = a[k\
    \ + i4 * 3];\n            const auto a01p = a0 + a1, a01m = a0 - a1;\n       \
    \     const auto a23p = a2 + a3, a23m = (a2 - a3) * root[1];\n            a[k\
    \ + i4 * 0] = a01p + a23p, a[k + i4 * 1] = a01m + a23m;\n            a[k + i4\
    \ * 2] = a01p - a23p, a[k + i4 * 3] = a01m - a23m;\n        }\n        for (int\
    \ j = i, m = 2; j < n; j += i, m += 2) {\n            const auto r = root[m],\
    \ r2 = r * r, r3 = r2 * r;\n            for (int k = j; k < j + i4; ++k) {\n \
    \               const auto a0 = a[k + i4 * 0], a1 = a[k + i4 * 1];\n         \
    \       const auto a2 = a[k + i4 * 2], a3 = a[k + i4 * 3];\n                const\
    \ auto a01p = a0 + a1, a01m = a0 - a1;\n                const auto a23p = a2 +\
    \ a3, a23m = (a2 - a3) * root[1];\n                a[k + i4 * 0] = a01p + a23p,\
    \ a[k + i4 * 1] = (a01m + a23m) * r;\n                a[k + i4 * 2] = (a01p -\
    \ a23p) * r2, a[k + i4 * 3] = (a01m - a23m) * r3;\n            }\n        }\n\
    \    }\n    if (bn & 1) {\n        for (int i = 0; i < n / 2; ++i) {\n       \
    \     const auto a0 = a[i], a1 = a[i + n / 2];\n            a[i] = a0 + a1, a[i\
    \ + n / 2] = a0 - a1;\n        }\n    }\n}\n\n} // namespace detail\n\n// FFT_n:\
    \ A(x) |-> bit-reversed order of [A(1), A(zeta_n), ..., A(zeta_n^(n-1))]\ntemplate<typename\
    \ Iterator> inline void fft_n(Iterator a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    detail::butterfly_n(a, n, FftInfo<Tp>::get().root(n / 2));\n}\n\ntemplate<typename\
    \ Tp> inline void fft(std::vector<Tp> &a) { fft_n(a.begin(), a.size()); }\n\n\
    // IFFT_n: bit-reversed order of [A(1), A(zeta_n), ..., A(zeta_n^(n-1))] |-> A(x)\n\
    template<typename Iterator> inline void inv_fft_n(Iterator a, int n) {\n    using\
    \ Tp = typename std::iterator_traits<Iterator>::value_type;\n    detail::inv_butterfly_n(a,\
    \ n, FftInfo<Tp>::get().inv_root(n / 2));\n    const Tp iv = Tp::mod() - (Tp::mod()\
    \ - 1) / n;\n    for (int i = 0; i < n; ++i) a[i] *= iv;\n}\n\ntemplate<typename\
    \ Tp> inline void inv_fft(std::vector<Tp> &a) { inv_fft_n(a.begin(), a.size());\
    \ }\n\n// IFFT_n^T: A(x) |-> 1/n FFT_n((x^n A(x^(-1))) mod (x^n - 1))\ntemplate<typename\
    \ Iterator> inline void transposed_inv_fft_n(Iterator a, int n) {\n    using Tp\
    \    = typename std::iterator_traits<Iterator>::value_type;\n    const Tp iv =\
    \ Tp::mod() - (Tp::mod() - 1) / n;\n    for (int i = 0; i < n; ++i) a[i] *= iv;\n\
    \    detail::butterfly_n(a, n, FftInfo<Tp>::get().inv_root(n / 2));\n}\n\ntemplate<typename\
    \ Tp> inline void transposed_inv_fft(std::vector<Tp> &a) {\n    transposed_inv_fft_n(a.begin(),\
    \ a.size());\n}\n\n// FFT_n^T : FFT_n((x^n A(x^(-1))) mod (x^n - 1)) |-> n A(x)\n\
    template<typename Iterator> inline void transposed_fft_n(Iterator a, int n) {\n\
    \    using Tp = typename std::iterator_traits<Iterator>::value_type;\n    detail::inv_butterfly_n(a,\
    \ n, FftInfo<Tp>::get().root(n / 2));\n}\n\ntemplate<typename Tp> inline void\
    \ transposed_fft(std::vector<Tp> &a) {\n    transposed_fft_n(a.begin(), a.size());\n\
    }\n\ntemplate<typename Tp> inline std::vector<Tp> convolution_fft(std::vector<Tp>\
    \ a, std::vector<Tp> b) {\n    if (a.empty() || b.empty()) return {};\n    const\
    \ int n   = a.size();\n    const int m   = b.size();\n    const int len = fft_len(n\
    \ + m - 1);\n    a.resize(len);\n    b.resize(len);\n    fft(a);\n    fft(b);\n\
    \    for (int i = 0; i < len; ++i) a[i] *= b[i];\n    inv_fft(a);\n    a.resize(n\
    \ + m - 1);\n    return a;\n}\n\ntemplate<typename Tp> inline std::vector<Tp>\
    \ square_fft(std::vector<Tp> a) {\n    if (a.empty()) return {};\n    const int\
    \ n   = a.size();\n    const int len = fft_len(n * 2 - 1);\n    a.resize(len);\n\
    \    fft(a);\n    for (int i = 0; i < len; ++i) a[i] *= a[i];\n    inv_fft(a);\n\
    \    a.resize(n * 2 - 1);\n    return a;\n}\n\ntemplate<typename Tp>\ninline std::vector<Tp>\
    \ convolution_naive(const std::vector<Tp> &a, const std::vector<Tp> &b) {\n  \
    \  if (a.empty() || b.empty()) return {};\n    const int n = a.size();\n    const\
    \ int m = b.size();\n    std::vector<Tp> res(n + m - 1);\n    for (int i = 0;\
    \ i < n; ++i)\n        for (int j = 0; j < m; ++j) res[i + j] += a[i] * b[j];\n\
    \    return res;\n}\n\ntemplate<typename Tp>\ninline std::vector<Tp> convolution(const\
    \ std::vector<Tp> &a, const std::vector<Tp> &b) {\n    if (std::min(a.size(),\
    \ b.size()) < 60) return convolution_naive(a, b);\n    if (std::addressof(a) ==\
    \ std::addressof(b)) return square_fft(a);\n    return convolution_fft(a, b);\n\
    }\n#line 7 \"middle_product.hpp\"\n\n// see:\n// [1]: Guillaume Hanrot, Michel\
    \ Quercia, Paul Zimmermann. The Middle Product Algorithm I.\n// [2]: Alin Bostan,\
    \ Gr\xE9goire Lecerf, \xC9ric Schost. Tellegen's principle into practice.\n\n\
    template<typename Tp>\ninline std::vector<Tp> middle_product_naive(const std::vector<Tp>\
    \ &f, const std::vector<Tp> &g) {\n    const int m = f.size();\n    const int\
    \ n = g.size();\n    assert(m >= n);\n    std::vector<Tp> res(m - n + 1);\n  \
    \  for (int i = n - 1; i < m; ++i)\n        for (int j = i - (n - 1); j <= i;\
    \ ++j) res[i - (n - 1)] += f[j] * g[i - j];\n    return res;\n}\n\ntemplate<typename\
    \ Tp>\ninline std::vector<Tp> middle_product_fft(std::vector<Tp> f, std::vector<Tp>\
    \ g) {\n    const int m = f.size();\n    const int n = g.size();\n    assert(m\
    \ >= n);\n    std::reverse(g.begin(), g.end());\n    const int len = fft_len(m);\n\
    \    f.resize(len);\n    g.resize(len);\n    transposed_inv_fft(f);\n    fft(g);\n\
    \    for (int i = 0; i < len; ++i) f[i] *= g[i];\n    transposed_fft(f);\n   \
    \ f.resize(m - n + 1);\n    return f;\n}\n\n// returns (fg)_(n-1),...,(fg)_(m-1)\n\
    // f: f_0 + ... + f_(m-1)x^(m-1)\n// g: g_0 + ... + g_(n-1)x^(n-1)\n// requires\
    \ m >= n\ntemplate<typename Tp>\ninline std::vector<Tp> middle_product(const std::vector<Tp>\
    \ &f, const std::vector<Tp> &g) {\n    assert(f.size() >= g.size());\n    if (f.size()\
    \ < 60) return middle_product_naive(f, g);\n    return middle_product_fft(f, g);\n\
    }\n#line 2 \"swag.hpp\"\n\n#line 4 \"swag.hpp\"\n#include <cstddef>\n#include\
    \ <optional>\n#include <stack>\n#line 9 \"swag.hpp\"\n\n// see: https://www.hirzels.com/martin/papers/debs17-tutorial.pdf\n\
    // requires: Op(Op(A,B),C) = Op(A,Op(B,C))\ntemplate<typename Tp, typename Op,\n\
    \         std::enable_if_t<std::is_invocable_r_v<Tp, Op, const Tp &, const Tp\
    \ &>, int> = 0>\nclass SWAG {\npublic:\n    Op F;\n    std::stack<Tp, std::vector<Tp>>\
    \ Front, Back;\n    std::optional<Tp> Agg;\n\n    explicit SWAG(Op F) : F(F) {}\n\
    \    bool empty() const { return Front.empty() && Back.empty(); }\n    std::size_t\
    \ size() const { return Front.size() + Back.size(); }\n    void push_back(const\
    \ Tp &v) {\n        Back.push(v);\n        Agg.emplace(Agg ? F(*Agg, v) : v);\n\
    \    }\n    void pop_front() {\n        assert(!empty());\n        if (Front.empty())\
    \ {\n            Front.push(Back.top());\n            Back.pop();\n          \
    \  while (!Back.empty()) {\n                Front.push(F(Back.top(), Front.top()));\n\
    \                Back.pop();\n            }\n            Agg.reset();\n      \
    \  }\n        Front.pop();\n    }\n\n    // returns F(...F(F(Q[0],Q[1]),Q[2]),...,Q[N-1])\n\
    \    std::optional<Tp> query() const {\n        if (empty()) return {};\n    \
    \    if (Front.empty()) return Agg;\n        if (!Agg) return Front.top();\n \
    \       return F(Front.top(), *Agg);\n    }\n};\n#line 8 \"shift_sample_points.hpp\"\
    \n#include <functional>\n#line 10 \"shift_sample_points.hpp\"\n\ntemplate<typename\
    \ Tp>\ninline std::vector<Tp> shift_sample_points(const std::vector<Tp> &f, Tp\
    \ c, int m) {\n    if (f.empty()) return std::vector<Tp>(m);\n    assert(m > 0);\n\
    \    const int n = f.size();\n    auto &&bin  = Binomial<Tp>::get(n);\n    std::vector<Tp>\
    \ F(n), G(n + m - 1);\n    for (int i = 0; i < n; ++i) {\n        F[i] = f[i]\
    \ * bin.inv_factorial(i) * bin.inv_factorial(n - 1 - i);\n        if ((n - 1 -\
    \ i) & 1) F[i] = -F[i];\n    }\n    for (int i = 0; i < n + m - 1; ++i) {\n  \
    \      const auto v = c + (i - (n - 1));\n        // We don't care about G[i]\
    \ when v = 0.\n        // We assigned 1 for G[i] when v = 0 for calling batch_inv().\n\
    \        G[i] = (v == 0) ? Tp(1) : v;\n    }\n    auto res = middle_product(batch_inv(G),\
    \ F);\n    SWAG<Tp, std::multiplies<>> P(std::multiplies<>{});\n    // P = c!/(c-n)!\
    \ = prod[-n < i <= 0](c + i)\n    for (int i = -n + 1; i <= 0; ++i) P.push_back(c\
    \ + i);\n    // res[i] <- (c+i)!/(c+i-n)! * res[i]\n    for (int i = 0; i < m;\
    \ ++i) {\n        if (i) P.pop_front(), P.push_back(c + i);\n        const auto\
    \ v = P.query().value();\n        // 0 <= c+i < n iff (c+i)!/(c+i-n)! = 0\n  \
    \      res[i] = (v == 0) ? f[(c + i).val()] : v * res[i];\n    }\n    return res;\n\
    }\n#line 2 \"sqrt_int.hpp\"\n\n#line 5 \"sqrt_int.hpp\"\n\n// see:\n// [1]: Richard\
    \ P. Brent and Paul Zimmermann. Modern Computer Arithmetic.\n\n// returns floor(m^(1/2))\n\
    template<typename Int> inline std::enable_if_t<std::is_integral_v<Int>, Int> sqrt_int(Int\
    \ m) {\n    assert(m >= 0);\n    if (m == 0) return 0;\n    for (Int u = m;;)\
    \ {\n        std::add_const_t<Int> s = u;\n        u                       = (s\
    \ + m / s) / 2;\n        if (u >= s) return s;\n    }\n}\n#line 10 \"test/enumerative_combinatorics/factorial.0.test.cpp\"\
    \n\ntemplate<typename Tp> Tp factorial(int N) {\n    if (N >= (int)Tp::mod())\
    \ return 0;\n    if (N == 0) return 1;\n    const int v = sqrt_int(N);\n    //\
    \ Let g_d(x) = prod[1 <= i <= d](x + i)\n    // g_1(x) = x + 1, g[i] = g_1(i *\
    \ v)\n    std::vector<Tp> g{Tp(1), Tp(v + 1)};\n    int mask = 1 << 30;\n    while\
    \ ((mask & v) == 0) mask >>= 1;\n    for (int d = 1; d != v;) {\n        const\
    \ auto g0 = shift_sample_points(g, Tp(d + 1), d);\n        const auto g1 = shift_sample_points(g,\
    \ Tp(d) / v, d << 1 | 1);\n        std::copy(g0.begin(), g0.end(), std::back_inserter(g));\n\
    \        d <<= 1;\n        // g_(2d)(x) = g_d(x)g_d(x + d)\n        for (int i\
    \ = 0; i <= d; ++i) g[i] *= g1[i];\n        if ((mask >>= 1) & v) {\n        \
    \    d |= 1;\n            g.push_back(lagrange_interpolation_iota(g, Tp(d)));\n\
    \            // g_(d + 1)(x) = (x + d + 1)g_d(x)\n            for (int i = 0;\
    \ i <= d; ++i) g[i] *= i * v + d;\n        }\n    }\n    Tp res = 1;\n    // g[0]\
    \ = g_v(0), g[1] = g_v(v), ...\n    for (int i = 0; i < v; ++i) res *= g[i];\n\
    \    for (int i = v * v + 1; i <= N; ++i) res *= i;\n    return res;\n}\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = ModInt<998244353>;\n    int T;\n    std::cin >> T;\n    while\
    \ (T--) {\n        int N;\n        std::cin >> N;\n        std::cout << factorial<mint>(N)\
    \ << '\\n';\n    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/factorial\"\n\n#include\
    \ \"modint.hpp\"\n#include \"poly_interpolation.hpp\"\n#include \"shift_sample_points.hpp\"\
    \n#include \"sqrt_int.hpp\"\n#include <algorithm>\n#include <iostream>\n#include\
    \ <iterator>\n\ntemplate<typename Tp> Tp factorial(int N) {\n    if (N >= (int)Tp::mod())\
    \ return 0;\n    if (N == 0) return 1;\n    const int v = sqrt_int(N);\n    //\
    \ Let g_d(x) = prod[1 <= i <= d](x + i)\n    // g_1(x) = x + 1, g[i] = g_1(i *\
    \ v)\n    std::vector<Tp> g{Tp(1), Tp(v + 1)};\n    int mask = 1 << 30;\n    while\
    \ ((mask & v) == 0) mask >>= 1;\n    for (int d = 1; d != v;) {\n        const\
    \ auto g0 = shift_sample_points(g, Tp(d + 1), d);\n        const auto g1 = shift_sample_points(g,\
    \ Tp(d) / v, d << 1 | 1);\n        std::copy(g0.begin(), g0.end(), std::back_inserter(g));\n\
    \        d <<= 1;\n        // g_(2d)(x) = g_d(x)g_d(x + d)\n        for (int i\
    \ = 0; i <= d; ++i) g[i] *= g1[i];\n        if ((mask >>= 1) & v) {\n        \
    \    d |= 1;\n            g.push_back(lagrange_interpolation_iota(g, Tp(d)));\n\
    \            // g_(d + 1)(x) = (x + d + 1)g_d(x)\n            for (int i = 0;\
    \ i <= d; ++i) g[i] *= i * v + d;\n        }\n    }\n    Tp res = 1;\n    // g[0]\
    \ = g_v(0), g[1] = g_v(v), ...\n    for (int i = 0; i < v; ++i) res *= g[i];\n\
    \    for (int i = v * v + 1; i <= N; ++i) res *= i;\n    return res;\n}\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = ModInt<998244353>;\n    int T;\n    std::cin >> T;\n    while\
    \ (T--) {\n        int N;\n        std::cin >> N;\n        std::cout << factorial<mint>(N)\
    \ << '\\n';\n    }\n    return 0;\n}\n"
  dependsOn:
  - modint.hpp
  - poly_interpolation.hpp
  - batch_inv.hpp
  - binomial.hpp
  - shift_sample_points.hpp
  - middle_product.hpp
  - fft.hpp
  - swag.hpp
  - sqrt_int.hpp
  isVerificationFile: true
  path: test/enumerative_combinatorics/factorial.0.test.cpp
  requiredBy: []
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/enumerative_combinatorics/factorial.0.test.cpp
layout: document
redirect_from:
- /verify/test/enumerative_combinatorics/factorial.0.test.cpp
- /verify/test/enumerative_combinatorics/factorial.0.test.cpp.html
title: test/enumerative_combinatorics/factorial.0.test.cpp
---
