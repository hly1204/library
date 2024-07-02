---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: basis.hpp
    title: basis.hpp
  - icon: ':heavy_check_mark:'
    path: fft.hpp
    title: fft.hpp
  - icon: ':heavy_check_mark:'
    path: mat_basic.hpp
    title: mat_basic.hpp
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: random.hpp
    title: random.hpp
  - icon: ':heavy_check_mark:'
    path: rng.hpp
    title: rng.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/characteristic_polynomial
    links:
    - https://judge.yosupo.jp/problem/characteristic_polynomial
  bundledCode: "#line 1 \"test/matrix/characteristic_polynomial.1.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/characteristic_polynomial\"\n\n#line\
    \ 2 \"basis.hpp\"\n\n#line 2 \"mat_basic.hpp\"\n\n#include <cassert>\n#include\
    \ <optional>\n#include <utility>\n#include <vector>\n\ntemplate <typename Tp>\n\
    using Matrix = std::vector<std::vector<Tp>>;\n\ntemplate <typename Tp>\ninline\
    \ int width(const Matrix<Tp> &A) {\n    return A.empty() ? 0 : (int)A[0].size();\n\
    }\n\ntemplate <typename Tp>\ninline int height(const Matrix<Tp> &A) {\n    return\
    \ A.size();\n}\n\ntemplate <typename Tp>\ninline bool is_square_matrix(const Matrix<Tp>\
    \ &A) {\n    return width(A) == height(A);\n}\n\ntemplate <typename Tp>\ninline\
    \ Matrix<Tp> transpose(const Matrix<Tp> &A) {\n    const int w = width(A);\n \
    \   const int h = height(A);\n    Matrix<Tp> TA(w, std::vector<Tp>(h));\n    for\
    \ (int i = 0; i < h; ++i)\n        for (int j = 0; j < w; ++j) TA[j][i] = A[i][j];\n\
    \    return TA;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> mat_apply(const\
    \ Matrix<Tp> &A, const std::vector<Tp> &b) {\n    const int w = width(A);\n  \
    \  const int h = height(A);\n    assert((int)b.size() == w);\n    std::vector<Tp>\
    \ Ab(h);\n    for (int i = 0; i < h; ++i)\n        for (int j = 0; j < w; ++j)\
    \ Ab[i] += A[i][j] * b[j];\n    return Ab;\n}\n\ntemplate <typename Tp>\ninline\
    \ Matrix<Tp> mat_mul(const Matrix<Tp> &A, const Matrix<Tp> &B) {\n    const int\
    \ wA = width(A);\n    const int hA = height(A);\n    assert(height(B) == wA);\n\
    \    const int wB = width(B);\n    Matrix<Tp> res(hA, std::vector<Tp>(wB));\n\
    \    for (int i = 0; i < hA; ++i)\n        for (int k = 0; k < wA; ++k)\n    \
    \        for (int j = 0; j < wB; ++j) res[i][j] += A[i][k] * B[k][j];\n    return\
    \ res;\n}\n\ntemplate <typename Tp>\ninline std::optional<Matrix<Tp>> mat_inv(Matrix<Tp>\
    \ A) {\n    assert(is_square_matrix(A));\n    const int n = height(A);\n    for\
    \ (int i = 0; i < n; ++i) {\n        A[i].resize(n * 2);\n        A[i][n + i]\
    \ = 1;\n    }\n    for (int i = 0; i < n; ++i) {\n        int pivot = i;\n   \
    \     for (; pivot < n; ++pivot)\n            if (A[pivot][i] != 0) break;\n \
    \       if (pivot == n) return {};\n        if (pivot != i) A[pivot].swap(A[i]);\n\
    \        if (A[i][i] != 1) {\n            const auto iv = A[i][i].inv();\n   \
    \         for (int j = i; j < n * 2; ++j) A[i][j] *= iv;\n        }\n        for\
    \ (int j = i + 1; j < n; ++j) {\n            const auto p = A[j][i];\n       \
    \     if (p == 0) continue;\n            for (int k = i + 1; k < n * 2; ++k) A[j][k]\
    \ -= p * A[i][k];\n        }\n    }\n    for (int i = n - 1; i > 0; --i) {\n \
    \       for (int j = i - 1; j >= 0; --j) {\n            const auto p = A[j][i];\n\
    \            if (p == 0) continue;\n            for (int k = n; k < n * 2; ++k)\
    \ A[j][k] -= p * A[i][k];\n        }\n    }\n    for (int i = 0; i < n; ++i) A[i].erase(A[i].begin(),\
    \ A[i].begin() + n);\n    return A;\n}\n\ntemplate <typename Tp>\ninline Tp det(Matrix<Tp>\
    \ A) {\n    assert(is_square_matrix(A));\n    const int n = height(A);\n    Tp\
    \ det      = 1;\n    bool neg    = false;\n    for (int i = 0; i < n; ++i) {\n\
    \        int pivot = i;\n        for (; pivot < n; ++pivot)\n            if (A[pivot][i]\
    \ != 0) break;\n        if (pivot == n) return 0;\n        if (pivot != i) {\n\
    \            A[pivot].swap(A[i]);\n            neg = !neg;\n        }\n      \
    \  det *= A[i][i];\n        const auto iv = A[i][i].inv();\n        for (int j\
    \ = i + 1; j < n; ++j) {\n            const auto p = A[j][i] * iv;\n         \
    \   if (p == 0) continue;\n            for (int k = i; k < n; ++k) A[j][k] -=\
    \ p * A[i][k];\n        }\n    }\n    return neg ? -det : det;\n}\n\ntemplate\
    \ <typename Tp>\ninline Matrix<Tp> to_upper_hessenberg(Matrix<Tp> A) {\n    assert(is_square_matrix(A));\n\
    \    const int n = height(A);\n    for (int i = 0; i < n - 1; ++i) {\n       \
    \ int pivot = i + 1;\n        for (; pivot < n; ++pivot)\n            if (A[pivot][i]\
    \ != 0) break;\n        if (pivot == n) continue;\n        if (pivot != i + 1)\
    \ {\n            A[pivot].swap(A[i + 1]);\n            for (int j = 0; j < n;\
    \ ++j) std::swap(A[j][pivot], A[j][i + 1]);\n        }\n        const auto iv\
    \ = A[i + 1][i].inv();\n        for (int j = i + 2; j < n; ++j) {\n          \
    \  if (A[j][i] == 0) continue;\n            const auto v = A[j][i] * iv;\n   \
    \         for (int k = i; k < n; ++k) A[j][k] -= v * A[i + 1][k];\n          \
    \  for (int k = 0; k < n; ++k) A[k][i + 1] += v * A[k][j];\n        }\n    }\n\
    \    return A;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> charpoly(const\
    \ Matrix<Tp> &A) {\n    const auto H = to_upper_hessenberg(A);\n    const int\
    \ n  = height(A);\n    std::vector<std::vector<Tp>> P(n + 1);\n    P[0] = {1};\n\
    \    for (int i = 1; i <= n; ++i) {\n        P[i].resize(i + 1);\n        for\
    \ (int j = 0; j < i; ++j)\n            P[i][j] -= H[i - 1][i - 1] * P[i - 1][j],\
    \ P[i][j + 1] += P[i - 1][j];\n        Tp t = 1;\n        for (int j = 1; j <\
    \ i; ++j) {\n            t *= H[i - j][i - j - 1];\n            const auto prod\
    \ = t * H[i - j - 1][i - 1];\n            if (prod == 0) continue;\n         \
    \   for (int k = 0; k < i - j; ++k) P[i][k] -= prod * P[i - j - 1][k];\n     \
    \   }\n    }\n    return P[n];\n}\n#line 7 \"basis.hpp\"\n\ntemplate <typename\
    \ Tp>\nclass Basis {\npublic:\n    const int Dim;\n    Matrix<Tp> Vectors; //\
    \ v_0, v_1, ...\n    Matrix<Tp> Augmented;\n    Matrix<Tp> Reduced; // upper triangular\
    \ matrix diag(Reduced)=(1,...,1)\n    // Augmented * Vectors = Reduced\n\n   \
    \ Basis(int dim) : Dim(dim), Augmented(dim), Reduced(dim) {}\n\n    int size()\
    \ const { return Vectors.size(); }\n    int dim() const { return Dim; }\n\n  \
    \  // if V is linear combination of v_0, ..., v_k then\n    // returns coefficients\
    \ (a_0, ..., a_k) s.t. -(a_0v_0 + ... + a_kv_k) = V\n    std::optional<std::vector<Tp>>\
    \ insert(const std::vector<Tp> &V) {\n        std::vector<Tp> Aug(dim()), RV =\
    \ V;\n        for (int i = 0; i < dim(); ++i) {\n            if (RV[i] == 0) continue;\n\
    \            if (Reduced[i].empty()) {\n                Aug[size()]    = 1;\n\
    \                const auto inv = RV[i].inv();\n                for (int j = i;\
    \ j < dim(); ++j) RV[j] *= inv;\n                for (int j = 0; j < dim(); ++j)\
    \ Aug[j] *= inv;\n                Augmented[i] = Aug;\n                Reduced[i]\
    \   = RV;\n                Vectors.push_back(V);\n                return {};\n\
    \            }\n            const auto v = RV[i];\n            for (int j = i;\
    \ j < dim(); ++j) RV[j] -= v * Reduced[i][j];\n            for (int j = 0; j <\
    \ dim(); ++j) Aug[j] -= v * Augmented[i][j];\n        }\n        return Aug;\n\
    \    }\n\n    // returns A s.t. A^(-1)MA is the linear transform respect to the\
    \ basis\n    Matrix<Tp> transition_matrix() const {\n        assert(size() ==\
    \ dim());\n        return transpose(Vectors);\n    }\n\n    // returns A^(-1)\
    \ s.t. A^(-1)MA is the linear transform respect to the basis\n    Matrix<Tp> inv_transition_matrix()\
    \ const {\n        assert(size() == dim());\n        auto res = Augmented;\n \
    \       for (int i = dim() - 1; i > 0; --i)\n            for (int j = i - 1; j\
    \ >= 0; --j)\n                for (int k = 0; k < dim(); ++k) res[j][k] -= Reduced[j][i]\
    \ * res[i][k];\n        return transpose(res);\n    }\n};\n#line 2 \"fft.hpp\"\
    \n\n#include <algorithm>\n#line 5 \"fft.hpp\"\n#include <iterator>\n#include <memory>\n\
    #line 8 \"fft.hpp\"\n\ntemplate <typename Tp>\nclass FftInfo {\n    static Tp\
    \ least_quadratic_nonresidue() {\n        for (int i = 2;; ++i)\n            if\
    \ (Tp(i).pow((Tp::mod() - 1) / 2) == -1) return Tp(i);\n    }\n\n    const int\
    \ ordlog2_;\n    const Tp zeta_;\n    const Tp invzeta_;\n    const Tp imag_;\n\
    \    const Tp invimag_;\n\n    mutable std::vector<Tp> root_;\n    mutable std::vector<Tp>\
    \ invroot_;\n\n    FftInfo()\n        : ordlog2_(__builtin_ctzll(Tp::mod() - 1)),\n\
    \          zeta_(least_quadratic_nonresidue().pow((Tp::mod() - 1) >> ordlog2_)),\n\
    \          invzeta_(zeta_.inv()), imag_(zeta_.pow(1LL << (ordlog2_ - 2))), invimag_(-imag_),\n\
    \          root_{Tp(1), imag_}, invroot_{Tp(1), invimag_} {}\n\npublic:\n    static\
    \ const FftInfo &get() {\n        static FftInfo info;\n        return info;\n\
    \    }\n\n    Tp imag() const { return imag_; }\n    Tp inv_imag() const { return\
    \ invimag_; }\n    Tp zeta() const { return zeta_; }\n    Tp inv_zeta() const\
    \ { return invzeta_; }\n    const std::vector<Tp> &root(int n) const {\n     \
    \   // [0, n)\n        assert((n & (n - 1)) == 0);\n        if (const int s =\
    \ root_.size(); s < n) {\n            root_.resize(n);\n            for (int i\
    \ = __builtin_ctz(s); (1 << i) < n; ++i) {\n                const int j = 1 <<\
    \ i;\n                root_[j]    = zeta_.pow(1LL << (ordlog2_ - i - 2));\n  \
    \              for (int k = j + 1; k < j * 2; ++k) root_[k] = root_[k - j] * root_[j];\n\
    \            }\n        }\n        return root_;\n    }\n    const std::vector<Tp>\
    \ &inv_root(int n) const {\n        // [0, n)\n        assert((n & (n - 1)) ==\
    \ 0);\n        if (const int s = invroot_.size(); s < n) {\n            invroot_.resize(n);\n\
    \            for (int i = __builtin_ctz(s); (1 << i) < n; ++i) {\n           \
    \     const int j = 1 << i;\n                invroot_[j] = invzeta_.pow(1LL <<\
    \ (ordlog2_ - i - 2));\n                for (int k = j + 1; k < j * 2; ++k) invroot_[k]\
    \ = invroot_[k - j] * invroot_[j];\n            }\n        }\n        return invroot_;\n\
    \    }\n};\n\ninline int fft_len(int n) {\n    --n;\n    n |= n >> 1, n |= n >>\
    \ 2, n |= n >> 4, n |= n >> 8;\n    return (n | n >> 16) + 1;\n}\n\ntemplate <typename\
    \ Iterator>\ninline void fft_n(Iterator a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    assert((n & (n - 1)) == 0);\n    for (int j = 0; j < n / 2; ++j) {\n    \
    \    auto u = a[j], v = a[j + n / 2];\n        a[j] = u + v, a[j + n / 2] = u\
    \ - v;\n    }\n    auto &&root = FftInfo<Tp>::get().root(n / 2);\n    for (int\
    \ i = n / 2; i >= 2; i /= 2) {\n        for (int j = 0; j < i / 2; ++j) {\n  \
    \          auto u = a[j], v = a[j + i / 2];\n            a[j] = u + v, a[j + i\
    \ / 2] = u - v;\n        }\n        for (int j = i, m = 1; j < n; j += i, ++m)\n\
    \            for (int k = j; k < j + i / 2; ++k) {\n                auto u = a[k],\
    \ v = a[k + i / 2] * root[m];\n                a[k] = u + v, a[k + i / 2] = u\
    \ - v;\n            }\n    }\n}\n\ntemplate <typename Tp>\ninline void fft(std::vector<Tp>\
    \ &a) {\n    fft_n(a.begin(), a.size());\n}\n\ntemplate <typename Iterator>\n\
    inline void inv_fft_n(Iterator a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    assert((n & (n - 1)) == 0);\n    auto &&root = FftInfo<Tp>::get().inv_root(n\
    \ / 2);\n    for (int i = 2; i < n; i *= 2) {\n        for (int j = 0; j < i /\
    \ 2; ++j) {\n            auto u = a[j], v = a[j + i / 2];\n            a[j] =\
    \ u + v, a[j + i / 2] = u - v;\n        }\n        for (int j = i, m = 1; j <\
    \ n; j += i, ++m)\n            for (int k = j; k < j + i / 2; ++k) {\n       \
    \         auto u = a[k], v = a[k + i / 2];\n                a[k] = u + v, a[k\
    \ + i / 2] = (u - v) * root[m];\n            }\n    }\n    const Tp iv = Tp::mod()\
    \ - Tp::mod() / n;\n    for (int j = 0; j < n / 2; ++j) {\n        auto u = a[j]\
    \ * iv, v = a[j + n / 2] * iv;\n        a[j] = u + v, a[j + n / 2] = u - v;\n\
    \    }\n}\n\ntemplate <typename Tp>\ninline void inv_fft(std::vector<Tp> &a) {\n\
    \    inv_fft_n(a.begin(), a.size());\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ convolution_fft(std::vector<Tp> a, std::vector<Tp> b) {\n    if (a.empty() ||\
    \ b.empty()) return {};\n    const int n   = a.size();\n    const int m   = b.size();\n\
    \    const int len = fft_len(n + m - 1);\n    a.resize(len);\n    b.resize(len);\n\
    \    fft(a);\n    fft(b);\n    for (int i = 0; i < len; ++i) a[i] *= b[i];\n \
    \   inv_fft(a);\n    a.resize(n + m - 1);\n    return a;\n}\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> square_fft(std::vector<Tp> a) {\n    if (a.empty())\
    \ return {};\n    const int n   = a.size();\n    const int len = fft_len(n * 2\
    \ - 1);\n    a.resize(len);\n    fft(a);\n    for (int i = 0; i < len; ++i) a[i]\
    \ *= a[i];\n    inv_fft(a);\n    a.resize(n * 2 - 1);\n    return a;\n}\n\ntemplate\
    \ <typename Tp>\ninline std::vector<Tp> convolution_naive(const std::vector<Tp>\
    \ &a, const std::vector<Tp> &b) {\n    if (a.empty() || b.empty()) return {};\n\
    \    const int n = a.size();\n    const int m = b.size();\n    std::vector<Tp>\
    \ res(n + m - 1);\n    for (int i = 0; i < n; ++i)\n        for (int j = 0; j\
    \ < m; ++j) res[i + j] += a[i] * b[j];\n    return res;\n}\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> convolution(const std::vector<Tp> &a, const std::vector<Tp>\
    \ &b) {\n    if (std::min(a.size(), b.size()) < 60) return convolution_naive(a,\
    \ b);\n    if (std::addressof(a) == std::addressof(b)) return square_fft(a);\n\
    \    return convolution_fft(a, b);\n}\n#line 2 \"modint.hpp\"\n\n#include <iostream>\n\
    #include <type_traits>\n\ntemplate <unsigned Mod>\nclass ModInt {\n    static_assert((Mod\
    \ >> 31) == 0, \"`Mod` must less than 2^(31)\");\n    template <typename Int>\n\
    \    static std::enable_if_t<std::is_integral_v<Int>, unsigned> safe_mod(Int v)\
    \ {\n        using D = std::common_type_t<Int, unsigned>;\n        return (v %=\
    \ (int)Mod) < 0 ? (D)(v + (int)Mod) : (D)v;\n    }\n\n    struct PrivateConstructor\
    \ {};\n    static inline PrivateConstructor private_constructor{};\n    ModInt(PrivateConstructor,\
    \ unsigned v) : v_(v) {}\n\n    unsigned v_;\n\npublic:\n    static unsigned mod()\
    \ { return Mod; }\n    static ModInt from_raw(unsigned v) { return ModInt(private_constructor,\
    \ v); }\n    ModInt() : v_() {}\n    template <typename Int, typename std::enable_if_t<std::is_signed_v<Int>,\
    \ int> = 0>\n    ModInt(Int v) : v_(safe_mod(v)) {}\n    template <typename Int,\
    \ typename std::enable_if_t<std::is_unsigned_v<Int>, int> = 0>\n    ModInt(Int\
    \ v) : v_(v % Mod) {}\n    unsigned val() const { return v_; }\n\n    ModInt operator-()\
    \ const { return from_raw(v_ == 0 ? v_ : Mod - v_); }\n    ModInt pow(long long\
    \ e) const {\n        if (e < 0) return inv().pow(-e);\n        for (ModInt x(*this),\
    \ res(from_raw(1));; x *= x) {\n            if (e & 1) res *= x;\n           \
    \ if ((e >>= 1) == 0) return res;\n        }\n    }\n    ModInt inv() const {\n\
    \        int x1 = 1, x3 = 0, a = val(), b = Mod;\n        while (b) {\n      \
    \      int q = a / b, x1_old = x1, a_old = a;\n            x1 = x3, x3 = x1_old\
    \ - x3 * q, a = b, b = a_old - b * q;\n        }\n        return from_raw(x1 <\
    \ 0 ? x1 + (int)Mod : x1);\n    }\n    template <bool Odd = (Mod & 1)>\n    std::enable_if_t<Odd,\
    \ ModInt> div_by_2() const {\n        if (v_ & 1) return from_raw((v_ + Mod) >>\
    \ 1);\n        return from_raw(v_ >> 1);\n    }\n\n    ModInt &operator+=(const\
    \ ModInt &a) {\n        if ((v_ += a.v_) >= Mod) v_ -= Mod;\n        return *this;\n\
    \    }\n    ModInt &operator-=(const ModInt &a) {\n        if ((v_ += Mod - a.v_)\
    \ >= Mod) v_ -= Mod;\n        return *this;\n    }\n    ModInt &operator*=(const\
    \ ModInt &a) {\n        v_ = (unsigned long long)v_ * a.v_ % Mod;\n        return\
    \ *this;\n    }\n    ModInt &operator/=(const ModInt &a) { return *this *= a.inv();\
    \ }\n\n    friend ModInt operator+(const ModInt &a, const ModInt &b) { return\
    \ ModInt(a) += b; }\n    friend ModInt operator-(const ModInt &a, const ModInt\
    \ &b) { return ModInt(a) -= b; }\n    friend ModInt operator*(const ModInt &a,\
    \ const ModInt &b) { return ModInt(a) *= b; }\n    friend ModInt operator/(const\
    \ ModInt &a, const ModInt &b) { return ModInt(a) /= b; }\n    friend bool operator==(const\
    \ ModInt &a, const ModInt &b) { return a.v_ == b.v_; }\n    friend bool operator!=(const\
    \ ModInt &a, const ModInt &b) { return a.v_ != b.v_; }\n    friend std::istream\
    \ &operator>>(std::istream &a, ModInt &b) {\n        int v;\n        a >> v;\n\
    \        b.v_ = safe_mod(v);\n        return a;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &a, const ModInt &b) { return a << b.val(); }\n};\n\
    #line 2 \"random.hpp\"\n\n#line 2 \"rng.hpp\"\n\n#include <cstdint>\n#include\
    \ <limits>\n\n// see: https://prng.di.unimi.it/xoshiro256starstar.c\n// original\
    \ license CC0 1.0\nclass xoshiro256starstar {\n    using u64 = std::uint64_t;\n\
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
    \ <random>\n#line 6 \"random.hpp\"\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ random_vector(int n) {\n    std::vector<Tp> res(n);\n    xoshiro256starstar\
    \ rng(std::random_device{}());\n    std::uniform_int_distribution<decltype(Tp::mod())>\
    \ dis(0, Tp::mod() - 1);\n    for (int i = 0; i < n; ++i) res[i] = dis(rng);\n\
    \    return res;\n}\n#line 9 \"test/matrix/characteristic_polynomial.1.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = ModInt<998244353>;\n    int n;\n    std::cin >> n;\n    Matrix<mint>\
    \ A(n, std::vector<mint>(n));\n    for (int i = 0; i < n; ++i)\n        for (int\
    \ j = 0; j < n; ++j) std::cin >> A[i][j];\n    Basis<mint> B(n);\n    std::vector<mint>\
    \ cp = {1};\n    while (B.size() < n) {\n        int deg = 0;\n        for (auto\
    \ R = random_vector<mint>(n);; R = mat_apply(A, R)) {\n            if (auto comb\
    \ = B.insert(R)) {\n                std::vector p(comb->begin() + (B.size() -\
    \ deg), comb->begin() + B.size());\n                p.emplace_back(1);\n     \
    \           cp = convolution(cp, p);\n                break;\n            }\n\
    \            ++deg;\n        }\n    }\n    for (int i = 0; i <= n; ++i) std::cout\
    \ << cp[i] << ' ';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/characteristic_polynomial\"\
    \n\n#include \"basis.hpp\"\n#include \"fft.hpp\"\n#include \"mat_basic.hpp\"\n\
    #include \"modint.hpp\"\n#include \"random.hpp\"\n#include <iostream>\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    using\
    \ mint = ModInt<998244353>;\n    int n;\n    std::cin >> n;\n    Matrix<mint>\
    \ A(n, std::vector<mint>(n));\n    for (int i = 0; i < n; ++i)\n        for (int\
    \ j = 0; j < n; ++j) std::cin >> A[i][j];\n    Basis<mint> B(n);\n    std::vector<mint>\
    \ cp = {1};\n    while (B.size() < n) {\n        int deg = 0;\n        for (auto\
    \ R = random_vector<mint>(n);; R = mat_apply(A, R)) {\n            if (auto comb\
    \ = B.insert(R)) {\n                std::vector p(comb->begin() + (B.size() -\
    \ deg), comb->begin() + B.size());\n                p.emplace_back(1);\n     \
    \           cp = convolution(cp, p);\n                break;\n            }\n\
    \            ++deg;\n        }\n    }\n    for (int i = 0; i <= n; ++i) std::cout\
    \ << cp[i] << ' ';\n    return 0;\n}\n"
  dependsOn:
  - basis.hpp
  - mat_basic.hpp
  - fft.hpp
  - modint.hpp
  - random.hpp
  - rng.hpp
  isVerificationFile: true
  path: test/matrix/characteristic_polynomial.1.test.cpp
  requiredBy: []
  timestamp: '2024-07-02 19:14:45+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/matrix/characteristic_polynomial.1.test.cpp
layout: document
redirect_from:
- /verify/test/matrix/characteristic_polynomial.1.test.cpp
- /verify/test/matrix/characteristic_polynomial.1.test.cpp.html
title: test/matrix/characteristic_polynomial.1.test.cpp
---
