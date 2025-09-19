---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: binomial.hpp
    title: binomial.hpp
  - icon: ':heavy_check_mark:'
    path: fft.hpp
    title: FFT
  - icon: ':heavy_check_mark:'
    path: md_conv.hpp
    title: Multidimensional Convolution (Truncated)
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: mps_basic.hpp
    title: Multivariate Power Series
  - icon: ':heavy_check_mark:'
    path: random.hpp
    title: random.hpp
  - icon: ':question:'
    path: rng.hpp
    title: rng.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"test/formal_power_series/multivariate_power_series.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 2 \"modint.hpp\"\
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
    \ &b) { return a << b.val(); }\n};\n// clang-format on\n#line 2 \"mps_basic.hpp\"\
    \n\n#line 2 \"binomial.hpp\"\n\n#include <algorithm>\n#include <vector>\n\ntemplate<typename\
    \ Tp> class Binomial {\n    std::vector<Tp> factorial_, invfactorial_;\n\n   \
    \ Binomial() : factorial_{Tp(1)}, invfactorial_{Tp(1)} {}\n\n    void preprocess(int\
    \ n) {\n        if (const int nn = factorial_.size(); nn < n) {\n            int\
    \ k = nn;\n            while (k < n) k *= 2;\n            k = std::min<long long>(k,\
    \ Tp::mod());\n            factorial_.resize(k);\n            invfactorial_.resize(k);\n\
    \            for (int i = nn; i < k; ++i) factorial_[i] = factorial_[i - 1] *\
    \ i;\n            invfactorial_.back() = factorial_.back().inv();\n          \
    \  for (int i = k - 2; i >= nn; --i) invfactorial_[i] = invfactorial_[i + 1] *\
    \ (i + 1);\n        }\n    }\n\npublic:\n    static const Binomial &get(int n)\
    \ {\n        static Binomial bin;\n        bin.preprocess(n);\n        return\
    \ bin;\n    }\n\n    Tp binom(int n, int m) const {\n        return n < m ? Tp()\
    \ : factorial_[n] * invfactorial_[m] * invfactorial_[n - m];\n    }\n    Tp inv(int\
    \ n) const { return factorial_[n - 1] * invfactorial_[n]; }\n    Tp factorial(int\
    \ n) const { return factorial_[n]; }\n    Tp inv_factorial(int n) const { return\
    \ invfactorial_[n]; }\n};\n#line 2 \"fft.hpp\"\n\n#line 4 \"fft.hpp\"\n#include\
    \ <cassert>\n#include <iterator>\n#include <memory>\n#line 8 \"fft.hpp\"\n\ntemplate<typename\
    \ Tp> class FftInfo {\n    static Tp least_quadratic_nonresidue() {\n        for\
    \ (int i = 2;; ++i)\n            if (Tp(i).pow((Tp::mod() - 1) / 2) == -1) return\
    \ Tp(i);\n    }\n\n    const int ordlog2_;\n    const Tp zeta_;\n    const Tp\
    \ invzeta_;\n    const Tp imag_;\n    const Tp invimag_;\n\n    mutable std::vector<Tp>\
    \ root_;\n    mutable std::vector<Tp> invroot_;\n\n    FftInfo()\n        : ordlog2_(__builtin_ctzll(Tp::mod()\
    \ - 1)),\n          zeta_(least_quadratic_nonresidue().pow((Tp::mod() - 1) >>\
    \ ordlog2_)),\n          invzeta_(zeta_.inv()), imag_(zeta_.pow(1LL << (ordlog2_\
    \ - 2))), invimag_(-imag_),\n          root_{Tp(1), imag_}, invroot_{Tp(1), invimag_}\
    \ {}\n\npublic:\n    static const FftInfo &get() {\n        static FftInfo info;\n\
    \        return info;\n    }\n\n    Tp imag() const { return imag_; }\n    Tp\
    \ inv_imag() const { return invimag_; }\n    Tp zeta() const { return zeta_; }\n\
    \    Tp inv_zeta() const { return invzeta_; }\n    const std::vector<Tp> &root(int\
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
    }\n#line 2 \"md_conv.hpp\"\n\n#line 5 \"md_conv.hpp\"\n#include <functional>\n\
    #include <numeric>\n#line 8 \"md_conv.hpp\"\n\nclass MDConvInfo {\n    int len_;\n\
    \    std::vector<int> degree_bound_;\n\npublic:\n    explicit MDConvInfo(const\
    \ std::vector<int> &d)\n        : len_(std::accumulate(d.begin(), d.end(), 1,\
    \ std::multiplies<>())), degree_bound_(d) {}\n\n    int len() const { return len_;\
    \ }\n    int dim() const { return degree_bound_.size(); }\n    std::vector<int>\
    \ degree_bound() const { return degree_bound_; }\n\n    // see:\n    // [1]: Elegia.\
    \ Hello, multivariate multiplication.\n    //      https://www.luogu.com/article/wje8kchr\n\
    \    std::vector<int> chi() const {\n        auto pp = degree_bound_;\n      \
    \  for (int i = 1; i < (int)pp.size(); ++i) pp[i] *= pp[i - 1];\n        std::vector<int>\
    \ diff(pp.size());\n        // O(max(dim^2, len))\n        for (int i = 1; i <\
    \ (int)diff.size(); ++i) {\n            for (int j = 0; j < i; ++j) diff[i] +=\
    \ pp[i - 1] / pp[j];\n            diff[i] %= dim();\n        }\n        std::vector<int>\
    \ c(len());\n        for (int i = 1; i < (int)pp.size(); ++i)\n            for\
    \ (int j = pp[i - 1]; j < pp[i]; ++j)\n                if ((c[j] = c[j - pp[i\
    \ - 1]] + diff[i]) >= dim()) c[j] -= dim();\n        return c;\n    }\n};\n\n\
    namespace detail {\n\ntemplate<typename Tp>\ninline std::vector<std::vector<Tp>>\
    \ multidimensional_hadamard(const std::vector<std::vector<Tp>> &a,\n         \
    \                                                     const std::vector<std::vector<Tp>>\
    \ &b,\n                                                              int dim,\
    \ int len) {\n    std::vector c(dim, std::vector<Tp>(len));\n    for (int i =\
    \ 0; i < dim; ++i)\n        for (int j = 0; j < dim; ++j) {\n            const\
    \ int k = (i + j) % dim;\n            for (int l = 0; l < len; ++l) c[k][l] +=\
    \ a[i][l] * b[j][l];\n        }\n    return c;\n}\n\n} // namespace detail\n\n\
    template<typename Tp>\ninline std::vector<Tp> multidimensional_convolution(const\
    \ MDConvInfo &info,\n                                                    const\
    \ std::vector<Tp> &a,\n                                                    const\
    \ std::vector<Tp> &b) {\n    assert((int)a.size() == info.len());\n    assert((int)b.size()\
    \ == info.len());\n    if (info.dim() == 0) return {a[0] * b[0]};\n    const int\
    \ len = fft_len(info.len() * 2 - 1);\n    std::vector aa(info.dim(), std::vector<Tp>(len));\n\
    \    std::vector bb(info.dim(), std::vector<Tp>(len));\n    const auto chi = info.chi();\n\
    \    for (int i = 0; i < info.len(); ++i) aa[chi[i]][i] = a[i], bb[chi[i]][i]\
    \ = b[i];\n    for (int i = 0; i < info.dim(); ++i) fft(aa[i]), fft(bb[i]);\n\
    \    auto cc = detail::multidimensional_hadamard(aa, bb, info.dim(), len);\n \
    \   for (int i = 0; i < info.dim(); ++i) inv_fft(cc[i]);\n    std::vector<Tp>\
    \ c(info.len());\n    for (int i = 0; i < info.len(); ++i) c[i] = cc[chi[i]][i];\n\
    \    return c;\n}\n#line 8 \"mps_basic.hpp\"\n#include <sstream>\n#include <string>\n\
    #line 11 \"mps_basic.hpp\"\n\n// Multivariate Power Series [inv, exp, log, pow]\n\
    // Store MPS A(x0, x1, ..., x(d-1)) with A(x, x1^N0, ...) in a 1-dim array\n//\
    \ using Kronecker substitution\n// TODO: opt\n\ntemplate<typename Tp>\ninline\
    \ std::string to_string(const MDConvInfo &info, const std::vector<Tp> &a) {\n\
    \    assert((int)a.size() == info.len());\n    std::stringstream ss;\n    ss <<\
    \ '[';\n    const auto degree_bound = info.degree_bound();\n    std::vector<int>\
    \ deg(info.dim());\n    for (int i = 0; i < (int)a.size(); ++i) {\n        if\
    \ (i) ss << \" + \";\n        ss << a[i];\n        for (int j = 0; j < (int)deg.size();\
    \ ++j) ss << \"*x\" << j << \"^(\" << deg[j] << ')';\n        for (int j = 0;\
    \ j < (int)deg.size(); ++j) {\n            if (++deg[j] < degree_bound[j]) break;\n\
    \            deg[j] = 0;\n        }\n    }\n    ss << ']';\n    return ss.str();\n\
    }\n\ntemplate<typename Tp>\ninline std::vector<Tp> mps_inv(const MDConvInfo &info,\
    \ const std::vector<Tp> &a) {\n    assert((int)a.size() == info.len());\n    assert(a[0]\
    \ != 0);\n    const auto bound = info.degree_bound();\n    std::vector<Tp> res(info.len());\n\
    \    res[0] = a[0].inv();\n    std::vector<int> d(info.dim());\n    for (int i\
    \ = 0, pp = 1; i < (int)bound.size(); pp *= bound[i++]) {\n        for (d[i] =\
    \ 1; d[i] < bound[i]; d[i] = std::min(d[i] * 2, bound[i])) {\n            auto\
    \ nextd     = std::vector(d.begin(), d.begin() + (i + 1));\n            nextd[i]\
    \       = std::min(d[i] * 2, bound[i]);\n            const int len  = fft_len(pp\
    \ * nextd[i]);\n            const auto chi = MDConvInfo(nextd).chi();\n      \
    \      std::vector shopA(i + 1, std::vector<Tp>(len));\n            std::vector\
    \ shopB(i + 1, std::vector<Tp>(len));\n            for (int j = 0; j < pp * nextd[i];\
    \ ++j) shopA[chi[j]][j] = a[j];\n            for (int j = 0; j < pp * d[i]; ++j)\
    \ shopB[chi[j]][j] = res[j];\n            for (int j = 0; j <= i; ++j) fft(shopA[j]),\
    \ fft(shopB[j]);\n            shopA = detail::multidimensional_hadamard(shopA,\
    \ shopB, i + 1, len);\n            for (int j = 0; j <= i; ++j) inv_fft(shopA[j]);\n\
    \            {\n                std::vector<Tp> shopC(pp * (nextd[i] - d[i]));\n\
    \                for (int j = pp * d[i]; j < pp * nextd[i]; ++j)\n           \
    \         shopC[j - pp * d[i]] = shopA[chi[j]][j];\n                for (int j\
    \ = 0; j <= i; ++j) std::fill(shopA[j].begin(), shopA[j].end(), Tp(0));\n    \
    \            for (int j = pp * d[i]; j < pp * nextd[i]; ++j)\n               \
    \     shopA[chi[j]][j] = shopC[j - pp * d[i]];\n            }\n            for\
    \ (int j = 0; j <= i; ++j) fft(shopA[j]);\n            shopA = detail::multidimensional_hadamard(shopA,\
    \ shopB, i + 1, len);\n            for (int j = 0; j <= i; ++j) inv_fft(shopA[j]);\n\
    \            for (int j = pp * d[i]; j < pp * nextd[i]; ++j) res[j] = -shopA[chi[j]][j];\n\
    \        }\n    }\n    return res;\n}\n\n// see:\n// [1]: Elegia. Hello, multivariate\
    \ multiplication.\n//      https://www.luogu.com/article/wje8kchr\ntemplate<typename\
    \ Tp> inline std::vector<Tp> mps_deriv(std::vector<Tp> a) {\n    for (int i =\
    \ 0; i < (int)a.size(); ++i) a[i] *= i;\n    return a;\n}\n\ntemplate<typename\
    \ Tp> inline std::vector<Tp> mps_integr(std::vector<Tp> a, Tp c = {}) {\n    auto\
    \ &&bin = Binomial<Tp>::get(a.size());\n    a[0]       = c;\n    for (int i =\
    \ 1; i < (int)a.size(); ++i) a[i] *= bin.inv(i);\n    return a;\n}\n\ntemplate<typename\
    \ Tp>\ninline std::vector<Tp> mps_log(const MDConvInfo &info, const std::vector<Tp>\
    \ &a) {\n    assert((int)a.size() == info.len());\n    assert(a[0] == 1);\n  \
    \  return mps_integr(multidimensional_convolution(info, mps_deriv(a), mps_inv(info,\
    \ a)));\n}\n\ntemplate<typename Tp>\ninline std::vector<Tp> mps_exp(const MDConvInfo\
    \ &info, const std::vector<Tp> &a) {\n    assert((int)a.size() == info.len());\n\
    \    assert(a[0] == 0);\n    const auto bound = info.degree_bound();\n    std::vector<Tp>\
    \ res(info.len());\n    res[0] = 1;\n    std::vector<int> d(info.dim());\n   \
    \ for (int i = 0, pp = 1; i < (int)bound.size(); pp *= bound[i++]) {\n       \
    \ for (d[i] = 1; d[i] < bound[i]; d[i] = std::min(d[i] * 2, bound[i])) {\n   \
    \         auto nextd = std::vector(d.begin(), d.begin() + (i + 1));\n        \
    \    nextd[i]   = std::min(d[i] * 2, bound[i]);\n            const MDConvInfo\
    \ ainfo(nextd);\n            auto shopA = mps_log(ainfo, std::vector(res.begin(),\
    \ res.begin() + pp * nextd[i]));\n            std::fill_n(shopA.begin(), pp *\
    \ d[i], Tp(0));\n            for (int j = pp * d[i]; j < pp * nextd[i]; ++j) shopA[j]\
    \ -= a[j];\n            shopA = multidimensional_convolution(\n              \
    \  ainfo, std::vector(res.begin(), res.begin() + pp * nextd[i]), shopA);\n   \
    \         for (int j = pp * d[i]; j < pp * nextd[i]; ++j) res[j] = -shopA[j];\n\
    \        }\n    }\n    return res;\n}\n\ntemplate<typename Tp>\ninline std::vector<Tp>\
    \ mps_pow(const MDConvInfo &info, std::vector<Tp> a, long long e) {\n    assert((int)a.size()\
    \ == info.len());\n    if (e == 0) {\n        std::vector<Tp> res(info.len());\n\
    \        res[0] = 1;\n        return res;\n    }\n\n    if (a[0] != 0) {\n   \
    \     const Tp ia0 = a[0].inv();\n        const Tp a0e = a[0].pow(e);\n      \
    \  const Tp me  = e;\n\n        for (int i = 0; i < (int)a.size(); ++i) a[i] *=\
    \ ia0;\n        a = mps_log(info, a);\n        for (int i = 0; i < (int)a.size();\
    \ ++i) a[i] *= me;\n        a = mps_exp(info, a);\n        for (int i = 0; i <\
    \ (int)a.size(); ++i) a[i] *= a0e;\n\n        return a;\n    }\n\n    assert(e\
    \ > 0);\n    std::vector<Tp> res(info.len());\n    res[0] = 1;\n    for (;;) {\n\
    \        if (e & 1) res = multidimensional_convolution(info, res, a);\n      \
    \  if ((e >>= 1) == 0) return res;\n        a = multidimensional_convolution(info,\
    \ a, a);\n    }\n}\n#line 2 \"random.hpp\"\n\n#line 2 \"rng.hpp\"\n\n#include\
    \ <cstdint>\n#include <limits>\n\n// see: https://prng.di.unimi.it/xoshiro256starstar.c\n\
    // original license CC0 1.0\nclass xoshiro256starstar {\n    using u64 = std::uint64_t;\n\
    \n    static inline u64 rotl(const u64 x, int k) { return (x << k) | (x >> (64\
    \ - k)); }\n\n    u64 s_[4];\n\n    u64 next() {\n        const u64 res = rotl(s_[1]\
    \ * 5, 7) * 9;\n        const u64 t   = s_[1] << 17;\n        s_[2] ^= s_[0];\n\
    \        s_[3] ^= s_[1];\n        s_[1] ^= s_[2];\n        s_[0] ^= s_[3];\n \
    \       s_[2] ^= t;\n        s_[3] = rotl(s_[3], 45);\n        return res;\n \
    \   }\n\npublic:\n    // see: https://prng.di.unimi.it/splitmix64.c\n    // original\
    \ license CC0 1.0\n    explicit xoshiro256starstar(u64 seed) {\n        for (int\
    \ i = 0; i < 4; ++i) {\n            u64 z = (seed += 0x9e3779b97f4a7c15);\n  \
    \          z     = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;\n            z     =\
    \ (z ^ (z >> 27)) * 0x94d049bb133111eb;\n            s_[i] = z ^ (z >> 31);\n\
    \        }\n    }\n    // see: https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator\n\
    \    using result_type = u64;\n    static constexpr u64 min() { return std::numeric_limits<u64>::min();\
    \ }\n    static constexpr u64 max() { return std::numeric_limits<u64>::max();\
    \ }\n    u64 operator()() { return next(); }\n};\n#line 4 \"random.hpp\"\n#include\
    \ <random>\n#line 6 \"random.hpp\"\n\ntemplate<typename Tp> inline std::vector<Tp>\
    \ random_vector(int n) {\n    std::vector<Tp> res(n);\n    xoshiro256starstar\
    \ rng(std::random_device{}());\n    std::uniform_int_distribution<decltype(Tp::mod())>\
    \ dis(0, Tp::mod() - 1);\n    for (int i = 0; i < n; ++i) res[i] = dis(rng);\n\
    \    return res;\n}\n\ntemplate<typename Tp> inline std::vector<Tp> random_vector_without_zero(int\
    \ n) {\n    std::vector<Tp> res(n);\n    xoshiro256starstar rng(std::random_device{}());\n\
    \    std::uniform_int_distribution<decltype(Tp::mod())> dis(1, Tp::mod() - 1);\n\
    \    for (int i = 0; i < n; ++i) res[i] = dis(rng);\n    return res;\n}\n#line\
    \ 11 \"test/formal_power_series/multivariate_power_series.0.test.cpp\"\n\nbool\
    \ verify_inv(int dim) {\n    assert(dim > 0);\n    std::uniform_int_distribution<>\
    \ dis(2, 10);\n    xoshiro256starstar gen(std::random_device{}());\n    using\
    \ mint = ModInt<998244353>;\n    std::vector<int> degree_bound(dim);\n    for\
    \ (int i = 0; i < dim; ++i) degree_bound[i] = dis(gen);\n    const MDConvInfo\
    \ info(degree_bound);\n    auto a         = random_vector<mint>(info.len());\n\
    \    a[0]           = dis(gen);\n    const auto res = multidimensional_convolution(info,\
    \ a, mps_inv(info, a));\n    std::vector<mint> correct(info.len());\n    correct[0]\
    \ = 1;\n    return res == correct;\n}\n\nbool verify_log_exp(int dim) {\n    assert(dim\
    \ > 0);\n    std::uniform_int_distribution<> dis(2, 10);\n    xoshiro256starstar\
    \ gen(std::random_device{}());\n    using mint = ModInt<998244353>;\n    std::vector<int>\
    \ degree_bound(dim);\n    for (int i = 0; i < dim; ++i) degree_bound[i] = dis(gen);\n\
    \    const MDConvInfo info(degree_bound);\n    auto a          = random_vector<mint>(info.len());\n\
    \    a[0]            = 1;\n    const auto loga = mps_log(info, a);\n    return\
    \ mps_exp(info, loga) == a;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    for (int i = 0; i < 5; ++i) {\n        const\
    \ bool ok = verify_inv(i + 1);\n        if (!ok) return 1;\n    }\n    for (int\
    \ i = 0; i < 5; ++i) {\n        const bool ok = verify_log_exp(i + 1);\n     \
    \   if (!ok) return 1;\n    }\n    long long a, b;\n    std::cin >> a >> b;\n\
    \    std::cout << a + b;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    modint.hpp\"\n#include \"mps_basic.hpp\"\n#include \"random.hpp\"\n#include \"\
    rng.hpp\"\n#include <cassert>\n#include <iostream>\n#include <random>\n#include\
    \ <vector>\n\nbool verify_inv(int dim) {\n    assert(dim > 0);\n    std::uniform_int_distribution<>\
    \ dis(2, 10);\n    xoshiro256starstar gen(std::random_device{}());\n    using\
    \ mint = ModInt<998244353>;\n    std::vector<int> degree_bound(dim);\n    for\
    \ (int i = 0; i < dim; ++i) degree_bound[i] = dis(gen);\n    const MDConvInfo\
    \ info(degree_bound);\n    auto a         = random_vector<mint>(info.len());\n\
    \    a[0]           = dis(gen);\n    const auto res = multidimensional_convolution(info,\
    \ a, mps_inv(info, a));\n    std::vector<mint> correct(info.len());\n    correct[0]\
    \ = 1;\n    return res == correct;\n}\n\nbool verify_log_exp(int dim) {\n    assert(dim\
    \ > 0);\n    std::uniform_int_distribution<> dis(2, 10);\n    xoshiro256starstar\
    \ gen(std::random_device{}());\n    using mint = ModInt<998244353>;\n    std::vector<int>\
    \ degree_bound(dim);\n    for (int i = 0; i < dim; ++i) degree_bound[i] = dis(gen);\n\
    \    const MDConvInfo info(degree_bound);\n    auto a          = random_vector<mint>(info.len());\n\
    \    a[0]            = 1;\n    const auto loga = mps_log(info, a);\n    return\
    \ mps_exp(info, loga) == a;\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    for (int i = 0; i < 5; ++i) {\n        const\
    \ bool ok = verify_inv(i + 1);\n        if (!ok) return 1;\n    }\n    for (int\
    \ i = 0; i < 5; ++i) {\n        const bool ok = verify_log_exp(i + 1);\n     \
    \   if (!ok) return 1;\n    }\n    long long a, b;\n    std::cin >> a >> b;\n\
    \    std::cout << a + b;\n    return 0;\n}\n"
  dependsOn:
  - modint.hpp
  - mps_basic.hpp
  - binomial.hpp
  - fft.hpp
  - md_conv.hpp
  - random.hpp
  - rng.hpp
  isVerificationFile: true
  path: test/formal_power_series/multivariate_power_series.0.test.cpp
  requiredBy: []
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/formal_power_series/multivariate_power_series.0.test.cpp
layout: document
redirect_from:
- /verify/test/formal_power_series/multivariate_power_series.0.test.cpp
- /verify/test/formal_power_series/multivariate_power_series.0.test.cpp.html
title: test/formal_power_series/multivariate_power_series.0.test.cpp
---
