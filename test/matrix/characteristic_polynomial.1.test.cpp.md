---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: basis.hpp
    title: basis.hpp
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
  - icon: ':heavy_check_mark:'
    path: sbpoly.hpp
    title: sbpoly.hpp
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
    \ * res[i][k];\n        return transpose(res);\n    }\n};\n#line 2 \"modint.hpp\"\
    \n\n#include <iostream>\n#include <type_traits>\n\ntemplate <unsigned Mod>\nclass\
    \ ModInt {\n    static_assert((Mod >> 31) == 0, \"`Mod` must less than 2^(31)\"\
    );\n    template <typename Int>\n    static std::enable_if_t<std::is_integral_v<Int>,\
    \ unsigned> safe_mod(Int v) {\n        using D = std::common_type_t<Int, unsigned>;\n\
    \        return (v %= (int)Mod) < 0 ? (D)(v + (int)Mod) : (D)v;\n    }\n\n   \
    \ struct PrivateConstructor {};\n    static inline PrivateConstructor private_constructor{};\n\
    \    ModInt(PrivateConstructor, unsigned v) : v_(v) {}\n\n    unsigned v_;\n\n\
    public:\n    static unsigned mod() { return Mod; }\n    static ModInt from_raw(unsigned\
    \ v) { return ModInt(private_constructor, v); }\n    ModInt() : v_() {}\n    template\
    \ <typename Int, typename std::enable_if_t<std::is_signed_v<Int>, int> = 0>\n\
    \    ModInt(Int v) : v_(safe_mod(v)) {}\n    template <typename Int, typename\
    \ std::enable_if_t<std::is_unsigned_v<Int>, int> = 0>\n    ModInt(Int v) : v_(v\
    \ % Mod) {}\n    unsigned val() const { return v_; }\n\n    ModInt operator-()\
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
    \    return res;\n}\n#line 2 \"sbpoly.hpp\"\n\n#include <algorithm>\n#line 6 \"\
    sbpoly.hpp\"\n#include <tuple>\n#line 9 \"sbpoly.hpp\"\n\n// Schoolbook Polynomial\n\
    template <typename Tp>\nclass SBPoly : public std::vector<Tp> {\n    using Base\
    \ = std::vector<Tp>;\n\npublic:\n    using Base::Base;\n\n    int deg() const\
    \ {\n        for (int i = (int)Base::size() - 1; i >= 0; --i)\n            if\
    \ (Base::operator[](i) != 0) return i;\n        return -1;\n    }\n\n    int ord()\
    \ const {\n        for (int i = 0; i < (int)Base::size(); ++i)\n            if\
    \ (Base::operator[](i) != 0) return i;\n        return -1;\n    }\n\n    SBPoly\
    \ rev() const {\n        const int d = deg();\n        SBPoly res(d + 1);\n  \
    \      for (int i = d; i >= 0; --i) res[i] = Base::operator[](d - i);\n      \
    \  return res;\n    }\n\n    SBPoly slice(int L, int R) const {\n        SBPoly\
    \ res(R - L);\n        for (int i = L; i < std::min(R, (int)Base::size()); ++i)\
    \ res[i - L] = Base::operator[](i);\n        return res;\n    }\n\n    SBPoly\
    \ trunc(int D) const {\n        SBPoly res(D);\n        for (int i = 0; i < std::min(D,\
    \ (int)Base::size()); ++i) res[i] = Base::operator[](i);\n        return res;\n\
    \    }\n\n    SBPoly &shrink() {\n        Base::resize(deg() + 1);\n        return\
    \ *this;\n    }\n\n    Tp lc() const {\n        const int d = deg();\n       \
    \ return d == -1 ? Tp() : Base::operator[](d);\n    }\n\n    SBPoly operator-()\
    \ const {\n        const int d = deg();\n        SBPoly res(d + 1);\n        for\
    \ (int i = 0; i <= d; ++i) res[i] = -Base::operator[](i);\n        res.shrink();\n\
    \        return res;\n    }\n\n    // O(deg(Q)deg(R))\n    std::pair<SBPoly, SBPoly>\
    \ divmod(const SBPoly &R) const {\n        const int degL = deg(), degR = R.deg(),\
    \ degQ = degL - degR;\n        assert(degR >= 0);\n        SBPoly quo(degQ + 1),\
    \ rem(*this);\n        if (degQ >= 0) {\n            const auto inv = R.lc().inv();\n\
    \            for (int i = degQ, n = degL; i >= 0; --i)\n                if ((quo[i]\
    \ = rem[n--] * inv) != 0)\n                    for (int j = 0; j <= degR; ++j)\
    \ rem[i + j] -= quo[i] * R[j];\n        }\n        rem.shrink();\n        return\
    \ std::make_pair(quo, rem);\n    }\n    SBPoly &operator+=(const SBPoly &R) {\n\
    \        if (Base::size() < R.size()) Base::resize(R.size());\n        for (int\
    \ i = 0; i < (int)R.size(); ++i) Base::operator[](i) += R[i];\n        return\
    \ shrink();\n    }\n    SBPoly &operator-=(const SBPoly &R) {\n        if (Base::size()\
    \ < R.size()) Base::resize(R.size());\n        for (int i = 0; i < (int)R.size();\
    \ ++i) Base::operator[](i) -= R[i];\n        return shrink();\n    }\n    SBPoly\
    \ &operator*=(const SBPoly &R) {\n        const int degL = deg(), degR = R.deg();\n\
    \        if (degL < 0 || degR < 0) {\n            Base::clear();\n           \
    \ return *this;\n        }\n        SBPoly res(degL + degR + 1);\n        for\
    \ (int i = 0; i <= degL; ++i)\n            for (int j = 0; j <= degR; ++j) res[i\
    \ + j] += Base::operator[](i) * R[j];\n        Base::swap(res);\n        return\
    \ *this;\n    }\n    // O(min(deg(Q)^2,deg(Q)deg(R)))\n    SBPoly &operator/=(const\
    \ SBPoly &R) {\n        const int degL = deg(), degR = R.deg(), degQ = degL -\
    \ degR;\n        assert(degR >= 0);\n        if (degQ < 0) {\n            Base::clear();\n\
    \            return *this;\n        }\n        SBPoly quo(degQ + 1);\n       \
    \ const auto inv = R.lc().inv();\n        for (int i = 0; i <= degQ; ++i) {\n\
    \            for (int j = 1; j <= std::min(i, degR); ++j)\n                quo[degQ\
    \ - i] += R[degR - j] * quo[degQ - i + j];\n            quo[degQ - i] = (Base::operator[](degL\
    \ - i) - quo[degQ - i]) * inv;\n        }\n        Base::swap(quo);\n        return\
    \ *this;\n    }\n    SBPoly &operator%=(const SBPoly &R) {\n        const int\
    \ degL = deg(), degR = R.deg(), degQ = degL - degR;\n        assert(degR >= 0);\n\
    \        const auto inv = R.lc().inv();\n        for (int i = degQ, n = degL;\
    \ i >= 0; --i)\n            if (const Tp res = Base::operator[](n--) * inv; res\
    \ != 0)\n                for (int j = 0; j <= degR; ++j) Base::operator[](i +\
    \ j) -= res * R[j];\n        return shrink();\n    }\n    SBPoly &operator<<=(int\
    \ D) {\n        if (D > 0) {\n            Base::insert(Base::begin(), D, Tp());\n\
    \        } else if (D < 0) {\n            if (-D < Base::size()) {\n         \
    \       Base::erase(Base::begin(), Base::begin() + (-D));\n            } else\
    \ {\n                Base::clear();\n            }\n        }\n        return\
    \ shrink();\n    }\n    SBPoly &operator>>=(int D) { return operator<<=(-D); }\n\
    \n    friend SBPoly operator+(const SBPoly &L, const SBPoly &R) { return SBPoly(L)\
    \ += R; }\n    friend SBPoly operator-(const SBPoly &L, const SBPoly &R) { return\
    \ SBPoly(L) -= R; }\n    friend SBPoly operator*(const SBPoly &L, const SBPoly\
    \ &R) { return SBPoly(L) *= R; }\n    friend SBPoly operator/(const SBPoly &L,\
    \ const SBPoly &R) { return SBPoly(L) /= R; }\n    friend SBPoly operator%(const\
    \ SBPoly &L, const SBPoly &R) { return SBPoly(L) %= R; }\n    friend SBPoly operator<<(const\
    \ SBPoly &L, int D) { return SBPoly(L) <<= D; }\n    friend SBPoly operator>>(const\
    \ SBPoly &L, int D) { return SBPoly(L) >>= D; }\n\n    friend std::ostream &operator<<(std::ostream\
    \ &L, const SBPoly &R) {\n        L << '[';\n        const int d = R.deg();\n\
    \        if (d < 0) {\n            L << '0';\n        } else {\n            for\
    \ (int i = 0; i <= d; ++i) {\n                L << R[i];\n                if (i\
    \ == 1) L << \"*X\";\n                if (i > 1) L << \"*X^\" << i;\n        \
    \        if (i != d) L << \" + \";\n            }\n        }\n        return L\
    \ << ']';\n    }\n};\n\ntemplate <typename Tp>\ninline std::tuple<SBPoly<Tp>,\
    \ SBPoly<Tp>, SBPoly<Tp>> xgcd(SBPoly<Tp> A, SBPoly<Tp> B) {\n    SBPoly<Tp> x11\
    \ = {1}, x12 = {}, x21 = {}, x22 = {1};\n    while (B.deg() >= 0) {\n        auto\
    \ [Q, R]  = A.divmod(B);\n        auto x11_old = x11, x12_old = x12;\n       \
    \ x11 = x21, x21 = x11_old - x21 * Q;\n        x12 = x22, x22 = x12_old - x22\
    \ * Q;\n        A = B, B = R;\n    }\n    return std::make_tuple(x11, x12, A);\n\
    }\n\ntemplate <typename Tp>\ninline std::pair<SBPoly<Tp>, SBPoly<Tp>> inv_gcd(SBPoly<Tp>\
    \ A, SBPoly<Tp> B) {\n    SBPoly<Tp> x11 = {1}, x21 = {};\n    while (B.deg()\
    \ >= 0) {\n        auto [Q, R]  = A.divmod(B);\n        auto x11_old = x11;\n\
    \        x11 = x21, x21 = x11_old - x21 * Q;\n        A = B, B = R;\n    }\n \
    \   return std::make_pair(x11, A);\n}\n#line 9 \"test/matrix/characteristic_polynomial.1.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = ModInt<998244353>;\n    int n;\n    std::cin >> n;\n    Matrix<mint>\
    \ A(n, std::vector<mint>(n));\n    for (int i = 0; i < n; ++i)\n        for (int\
    \ j = 0; j < n; ++j) std::cin >> A[i][j];\n    Basis<mint> B(n);\n    SBPoly<mint>\
    \ cp = {1};\n    while (B.size() < n) {\n        int deg = 0;\n        for (auto\
    \ R = random_vector<mint>(n);; R = mat_apply(A, R)) {\n            if (auto comb\
    \ = B.insert(R)) {\n                SBPoly<mint> p(comb->begin() + (B.size() -\
    \ deg), comb->begin() + B.size());\n                p.emplace_back(1);\n     \
    \           cp *= p;\n                break;\n            }\n            ++deg;\n\
    \        }\n    }\n    for (int i = 0; i <= n; ++i) std::cout << cp[i] << ' ';\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/characteristic_polynomial\"\
    \n\n#include \"basis.hpp\"\n#include \"mat_basic.hpp\"\n#include \"modint.hpp\"\
    \n#include \"random.hpp\"\n#include \"sbpoly.hpp\"\n#include <iostream>\n\nint\
    \ main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = ModInt<998244353>;\n    int n;\n    std::cin >> n;\n    Matrix<mint>\
    \ A(n, std::vector<mint>(n));\n    for (int i = 0; i < n; ++i)\n        for (int\
    \ j = 0; j < n; ++j) std::cin >> A[i][j];\n    Basis<mint> B(n);\n    SBPoly<mint>\
    \ cp = {1};\n    while (B.size() < n) {\n        int deg = 0;\n        for (auto\
    \ R = random_vector<mint>(n);; R = mat_apply(A, R)) {\n            if (auto comb\
    \ = B.insert(R)) {\n                SBPoly<mint> p(comb->begin() + (B.size() -\
    \ deg), comb->begin() + B.size());\n                p.emplace_back(1);\n     \
    \           cp *= p;\n                break;\n            }\n            ++deg;\n\
    \        }\n    }\n    for (int i = 0; i <= n; ++i) std::cout << cp[i] << ' ';\n\
    \    return 0;\n}\n"
  dependsOn:
  - basis.hpp
  - mat_basic.hpp
  - modint.hpp
  - random.hpp
  - rng.hpp
  - sbpoly.hpp
  isVerificationFile: true
  path: test/matrix/characteristic_polynomial.1.test.cpp
  requiredBy: []
  timestamp: '2024-07-02 22:17:39+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/matrix/characteristic_polynomial.1.test.cpp
layout: document
redirect_from:
- /verify/test/matrix/characteristic_polynomial.1.test.cpp
- /verify/test/matrix/characteristic_polynomial.1.test.cpp.html
title: test/matrix/characteristic_polynomial.1.test.cpp
---