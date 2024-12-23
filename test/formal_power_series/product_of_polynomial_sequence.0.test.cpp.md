---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fft.hpp
    title: FFT
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: poly_product.hpp
    title: poly_product.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/product_of_polynomial_sequence
    links:
    - https://judge.yosupo.jp/problem/product_of_polynomial_sequence
  bundledCode: "#line 1 \"test/formal_power_series/product_of_polynomial_sequence.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/product_of_polynomial_sequence\"\
    \n\n#line 2 \"modint.hpp\"\n\n#include <iostream>\n#include <type_traits>\n\n\
    template <unsigned Mod>\nclass ModInt {\n    static_assert((Mod >> 31) == 0, \"\
    `Mod` must less than 2^(31)\");\n    template <typename Int>\n    static std::enable_if_t<std::is_integral_v<Int>,\
    \ unsigned> safe_mod(Int v) {\n        using D = std::common_type_t<Int, unsigned>;\n\
    \        return (v %= (int)Mod) < 0 ? (D)(v + (int)Mod) : (D)v;\n    }\n\n   \
    \ struct PrivateConstructor {};\n    static inline PrivateConstructor private_constructor{};\n\
    \    ModInt(PrivateConstructor, unsigned v) : v_(v) {}\n\n    unsigned v_;\n\n\
    public:\n    static unsigned mod() { return Mod; }\n    static ModInt from_raw(unsigned\
    \ v) { return ModInt(private_constructor, v); }\n    static ModInt zero() { return\
    \ from_raw(0); }\n    static ModInt one() { return from_raw(1); }\n\n    ModInt()\
    \ : v_() {}\n    template <typename Int, typename std::enable_if_t<std::is_signed_v<Int>,\
    \ int> = 0>\n    ModInt(Int v) : v_(safe_mod(v)) {}\n    template <typename Int,\
    \ typename std::enable_if_t<std::is_unsigned_v<Int>, int> = 0>\n    ModInt(Int\
    \ v) : v_(v % Mod) {}\n    unsigned val() const { return v_; }\n\n    ModInt operator-()\
    \ const { return from_raw(v_ == 0 ? v_ : Mod - v_); }\n    ModInt pow(long long\
    \ e) const {\n        if (e < 0) return inv().pow(-e);\n        for (ModInt x(*this),\
    \ res(from_raw(1));; x *= x) {\n            if (e & 1) res *= x;\n           \
    \ if ((e >>= 1) == 0) return res;\n        }\n    }\n    ModInt inv() const {\n\
    \        int x1 = 1, x3 = 0, a = val(), b = Mod;\n        while (b) {\n      \
    \      const int q = a / b, x1_old = x1, a_old = a;\n            x1 = x3, x3 =\
    \ x1_old - x3 * q, a = b, b = a_old - b * q;\n        }\n        return from_raw(x1\
    \ < 0 ? x1 + (int)Mod : x1);\n    }\n    template <bool Odd = (Mod & 1)>\n   \
    \ std::enable_if_t<Odd, ModInt> div_by_2() const {\n        if (v_ & 1) return\
    \ from_raw((v_ + Mod) >> 1);\n        return from_raw(v_ >> 1);\n    }\n\n   \
    \ ModInt &operator+=(const ModInt &a) {\n        if ((v_ += a.v_) >= Mod) v_ -=\
    \ Mod;\n        return *this;\n    }\n    ModInt &operator-=(const ModInt &a)\
    \ {\n        if ((v_ += Mod - a.v_) >= Mod) v_ -= Mod;\n        return *this;\n\
    \    }\n    ModInt &operator*=(const ModInt &a) {\n        v_ = (unsigned long\
    \ long)v_ * a.v_ % Mod;\n        return *this;\n    }\n    ModInt &operator/=(const\
    \ ModInt &a) { return *this *= a.inv(); }\n\n    friend ModInt operator+(const\
    \ ModInt &a, const ModInt &b) { return ModInt(a) += b; }\n    friend ModInt operator-(const\
    \ ModInt &a, const ModInt &b) { return ModInt(a) -= b; }\n    friend ModInt operator*(const\
    \ ModInt &a, const ModInt &b) { return ModInt(a) *= b; }\n    friend ModInt operator/(const\
    \ ModInt &a, const ModInt &b) { return ModInt(a) /= b; }\n    friend bool operator==(const\
    \ ModInt &a, const ModInt &b) { return a.v_ == b.v_; }\n    friend bool operator!=(const\
    \ ModInt &a, const ModInt &b) { return a.v_ != b.v_; }\n    friend std::istream\
    \ &operator>>(std::istream &a, ModInt &b) {\n        int v;\n        a >> v;\n\
    \        b.v_ = safe_mod(v);\n        return a;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &a, const ModInt &b) { return a << b.val(); }\n};\n\
    #line 2 \"poly_product.hpp\"\n\n#line 2 \"fft.hpp\"\n\n#include <algorithm>\n\
    #include <cassert>\n#include <iterator>\n#include <memory>\n#include <vector>\n\
    \ntemplate <typename Tp>\nclass FftInfo {\n    static Tp least_quadratic_nonresidue()\
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
    \  return (n | n >> 16) + 1;\n}\n\nnamespace detail {\n\ntemplate <typename Iterator>\n\
    inline void\nbutterfly_n(Iterator a, int n,\n            const std::vector<typename\
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
    \          }\n        }\n    }\n}\n\ntemplate <typename Iterator>\ninline void\n\
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
    \ A(x) |-> bit-reversed order of [A(1), A(zeta_n), ..., A(zeta_n^(n-1))]\ntemplate\
    \ <typename Iterator>\ninline void fft_n(Iterator a, int n) {\n    using Tp =\
    \ typename std::iterator_traits<Iterator>::value_type;\n    detail::butterfly_n(a,\
    \ n, FftInfo<Tp>::get().root(n / 2));\n}\n\ntemplate <typename Tp>\ninline void\
    \ fft(std::vector<Tp> &a) {\n    fft_n(a.begin(), a.size());\n}\n\n// IFFT_n:\
    \ bit-reversed order of [A(1), A(zeta_n), ..., A(zeta_n^(n-1))] |-> A(x)\ntemplate\
    \ <typename Iterator>\ninline void inv_fft_n(Iterator a, int n) {\n    using Tp\
    \ = typename std::iterator_traits<Iterator>::value_type;\n    detail::inv_butterfly_n(a,\
    \ n, FftInfo<Tp>::get().inv_root(n / 2));\n    const Tp iv = Tp::mod() - (Tp::mod()\
    \ - 1) / n;\n    for (int i = 0; i < n; ++i) a[i] *= iv;\n}\n\ntemplate <typename\
    \ Tp>\ninline void inv_fft(std::vector<Tp> &a) {\n    inv_fft_n(a.begin(), a.size());\n\
    }\n\n// IFFT_n^T: A(x) |-> 1/n FFT_n((x^n A(x^(-1))) mod (x^n - 1))\ntemplate\
    \ <typename Iterator>\ninline void transposed_inv_fft_n(Iterator a, int n) {\n\
    \    using Tp    = typename std::iterator_traits<Iterator>::value_type;\n    const\
    \ Tp iv = Tp::mod() - (Tp::mod() - 1) / n;\n    for (int i = 0; i < n; ++i) a[i]\
    \ *= iv;\n    detail::butterfly_n(a, n, FftInfo<Tp>::get().inv_root(n / 2));\n\
    }\n\ntemplate <typename Tp>\ninline void transposed_inv_fft(std::vector<Tp> &a)\
    \ {\n    transposed_inv_fft_n(a.begin(), a.size());\n}\n\n// FFT_n^T : FFT_n((x^n\
    \ A(x^(-1))) mod (x^n - 1)) |-> n A(x)\ntemplate <typename Iterator>\ninline void\
    \ transposed_fft_n(Iterator a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    detail::inv_butterfly_n(a, n, FftInfo<Tp>::get().root(n / 2));\n}\n\ntemplate\
    \ <typename Tp>\ninline void transposed_fft(std::vector<Tp> &a) {\n    transposed_fft_n(a.begin(),\
    \ a.size());\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> convolution_fft(std::vector<Tp>\
    \ a, std::vector<Tp> b) {\n    if (a.empty() || b.empty()) return {};\n    const\
    \ int n   = a.size();\n    const int m   = b.size();\n    const int len = fft_len(n\
    \ + m - 1);\n    a.resize(len);\n    b.resize(len);\n    fft(a);\n    fft(b);\n\
    \    for (int i = 0; i < len; ++i) a[i] *= b[i];\n    inv_fft(a);\n    a.resize(n\
    \ + m - 1);\n    return a;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ square_fft(std::vector<Tp> a) {\n    if (a.empty()) return {};\n    const int\
    \ n   = a.size();\n    const int len = fft_len(n * 2 - 1);\n    a.resize(len);\n\
    \    fft(a);\n    for (int i = 0; i < len; ++i) a[i] *= a[i];\n    inv_fft(a);\n\
    \    a.resize(n * 2 - 1);\n    return a;\n}\n\ntemplate <typename Tp>\ninline\
    \ std::vector<Tp> convolution_naive(const std::vector<Tp> &a, const std::vector<Tp>\
    \ &b) {\n    if (a.empty() || b.empty()) return {};\n    const int n = a.size();\n\
    \    const int m = b.size();\n    std::vector<Tp> res(n + m - 1);\n    for (int\
    \ i = 0; i < n; ++i)\n        for (int j = 0; j < m; ++j) res[i + j] += a[i] *\
    \ b[j];\n    return res;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ convolution(const std::vector<Tp> &a, const std::vector<Tp> &b) {\n    if (std::min(a.size(),\
    \ b.size()) < 60) return convolution_naive(a, b);\n    if (std::addressof(a) ==\
    \ std::addressof(b)) return square_fft(a);\n    return convolution_fft(a, b);\n\
    }\n#line 4 \"poly_product.hpp\"\n#include <utility>\n#line 6 \"poly_product.hpp\"\
    \n\n// TODO: cache dft\ntemplate <typename Tp>\ninline std::vector<Tp> poly_product(std::vector<std::vector<Tp>>\
    \ L) {\n    if (L.empty()) return {Tp(1)};\n    while (L.size() > 1) {\n     \
    \   std::vector<std::vector<Tp>> t;\n        for (int i = 0; i + 1 < (int)L.size();\
    \ i += 2) t.push_back(convolution(L[i], L[i + 1]));\n        if (L.size() & 1)\
    \ t.push_back(L.back());\n        L = std::move(t);\n    }\n    return L[0];\n\
    }\n#line 7 \"test/formal_power_series/product_of_polynomial_sequence.0.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = ModInt<998244353>;\n    int n;\n    std::cin >> n;\n    std::vector<std::vector<mint>>\
    \ L;\n    while (n--) {\n        int d;\n        std::cin >> d;\n        auto\
    \ &&p = L.emplace_back(d + 1);\n        for (int i = 0; i <= d; ++i) std::cin\
    \ >> p[i];\n    }\n    const auto res = poly_product(L);\n    for (int i = 0;\
    \ i < (int)res.size(); ++i) std::cout << res[i] << ' ';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/product_of_polynomial_sequence\"\
    \n\n#include \"modint.hpp\"\n#include \"poly_product.hpp\"\n#include <iostream>\n\
    #include <vector>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n   \
    \ std::cin.tie(nullptr);\n    using mint = ModInt<998244353>;\n    int n;\n  \
    \  std::cin >> n;\n    std::vector<std::vector<mint>> L;\n    while (n--) {\n\
    \        int d;\n        std::cin >> d;\n        auto &&p = L.emplace_back(d +\
    \ 1);\n        for (int i = 0; i <= d; ++i) std::cin >> p[i];\n    }\n    const\
    \ auto res = poly_product(L);\n    for (int i = 0; i < (int)res.size(); ++i) std::cout\
    \ << res[i] << ' ';\n    return 0;\n}\n"
  dependsOn:
  - modint.hpp
  - poly_product.hpp
  - fft.hpp
  isVerificationFile: true
  path: test/formal_power_series/product_of_polynomial_sequence.0.test.cpp
  requiredBy: []
  timestamp: '2024-12-23 20:42:13+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/formal_power_series/product_of_polynomial_sequence.0.test.cpp
layout: document
redirect_from:
- /verify/test/formal_power_series/product_of_polynomial_sequence.0.test.cpp
- /verify/test/formal_power_series/product_of_polynomial_sequence.0.test.cpp.html
title: test/formal_power_series/product_of_polynomial_sequence.0.test.cpp
---
