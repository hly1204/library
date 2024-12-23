---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fft.hpp
    title: FFT
  - icon: ':heavy_check_mark:'
    path: ks.hpp
    title: ks.hpp
  - icon: ':question:'
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
    PROBLEM: https://judge.yosupo.jp/problem/aplusb
    links:
    - https://judge.yosupo.jp/problem/aplusb
  bundledCode: "#line 1 \"test/convolution/2d_convolution.0.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/aplusb\"\n\n#line 2 \"ks.hpp\"\n\n#line 2\
    \ \"fft.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#include <iterator>\n\
    #include <memory>\n#include <vector>\n\ntemplate <typename Tp>\nclass FftInfo\
    \ {\n    static Tp least_quadratic_nonresidue() {\n        for (int i = 2;; ++i)\n\
    \            if (Tp(i).pow((Tp::mod() - 1) / 2) == -1) return Tp(i);\n    }\n\n\
    \    const int ordlog2_;\n    const Tp zeta_;\n    const Tp invzeta_;\n    const\
    \ Tp imag_;\n    const Tp invimag_;\n\n    mutable std::vector<Tp> root_;\n  \
    \  mutable std::vector<Tp> invroot_;\n\n    FftInfo()\n        : ordlog2_(__builtin_ctzll(Tp::mod()\
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
    }\n#line 7 \"ks.hpp\"\n\n// returns max[0 <= j < a.size()]{a[j].size()}\ntemplate\
    \ <typename Tp>\ninline int max_len_x_ks(const std::vector<std::vector<Tp>> &a)\
    \ {\n    int len = -1;\n    for (int i = 0; i < (int)a.size(); ++i) len = std::max<int>(len,\
    \ a[i].size());\n    return len;\n}\n\n// returns a(x, x^N) where a(x,y) in R[x][y]\n\
    template <typename Tp>\ninline std::vector<Tp> pack_2d_ks(const std::vector<std::vector<Tp>>\
    \ &a, int N) {\n    assert(N > 0);\n    // y |-> x^N\n    std::vector<Tp> b(N\
    \ * a.size());\n    for (int i = 0; i < (int)a.size(); ++i)\n        for (int\
    \ j = 0; j < (int)a[i].size(); ++j) b[i * N + j] += a[i][j]; // if N < a[i].size()\n\
    \    return b;\n}\n\ntemplate <typename Tp>\ninline std::vector<std::vector<Tp>>\
    \ unpack_2d_ks(const std::vector<Tp> &a, int N) {\n    assert(N > 0);\n    //\
    \ x^N |-> y\n    std::vector<std::vector<Tp>> b((a.size() + (N - 1)) / N, std::vector<Tp>(N));\n\
    \    for (int i = 0; i < (int)((a.size() + N - 1) / N); ++i)\n        for (int\
    \ j = 0; j < N && i * N + j < (int)a.size(); ++j) b[i][j] = a[i * N + j];\n  \
    \  return b;\n}\n\ntemplate <typename Tp>\ninline std::vector<std::vector<Tp>>\
    \ convolution_2d_naive(const std::vector<std::vector<Tp>> &a,\n              \
    \                                           const std::vector<std::vector<Tp>>\
    \ &b) {\n    if (a.empty() || b.empty()) return {};\n    const int lenA = max_len_x_ks(a);\n\
    \    const int lenB = max_len_x_ks(b);\n    if (lenA == 0 || lenB == 0) return\
    \ std::vector<std::vector<Tp>>(a.size() + b.size() - 1);\n    const int N = lenA\
    \ + lenB - 1;\n    std::vector<std::vector<Tp>> ab(a.size() + b.size() - 1, std::vector<Tp>(N));\n\
    \    for (int i = 0; i < (int)a.size(); ++i)\n        for (int j = 0; j < (int)b.size();\
    \ ++j) {\n            const auto aibj = convolution(a[i], b[j]);\n           \
    \ for (int k = 0; k < (int)aibj.size(); ++k) ab[i + j][k] += aibj[k];\n      \
    \  }\n    return ab;\n}\n\n// standard Kronecker substitution\ntemplate <typename\
    \ Tp>\ninline std::vector<std::vector<Tp>> convolution_2d_ks(const std::vector<std::vector<Tp>>\
    \ &a,\n                                                      const std::vector<std::vector<Tp>>\
    \ &b) {\n    if (a.empty() || b.empty()) return {};\n    const int lenA = max_len_x_ks(a);\n\
    \    const int lenB = max_len_x_ks(b);\n    if (lenA == 0 || lenB == 0) return\
    \ std::vector<std::vector<Tp>>(a.size() + b.size() - 1);\n    const int N = lenA\
    \ + lenB - 1;\n    auto ab     = convolution(pack_2d_ks(a, N), pack_2d_ks(b, N));\n\
    \    ab.resize((a.size() + b.size() - 1) * N);\n    return unpack_2d_ks(ab, N);\n\
    }\n\n// see:\n// [1]: David Harvey. Faster polynomial multiplication via multipoint\
    \ Kronecker substitution.\n//      https://doi.org/10.1016/j.jsc.2009.05.004\n\
    template <typename Tp>\ninline std::vector<std::vector<Tp>>\nconvolution_2d_ks_reciprocal(const\
    \ std::vector<std::vector<Tp>> &a,\n                             const std::vector<std::vector<Tp>>\
    \ &b) {\n    if (a.empty() || b.empty()) return {};\n    const int lenA = max_len_x_ks(a);\n\
    \    const int lenB = max_len_x_ks(b);\n    if (lenA == 0 || lenB == 0) return\
    \ std::vector<std::vector<Tp>>(a.size() + b.size() - 1);\n    const int N = std::max(lenA,\
    \ lenB);\n    // original version: compute a(x, x^(-N)) b(x, x^(-N))\n    // modified\
    \ version (this version): compute x^(2N-2) a(x^(-1), x^N) b(x^(-1), x^N)\n   \
    \ // ab0 = a(x, x^N) b(x, x^N)\n    auto ab0 = convolution(pack_2d_ks(a, N), pack_2d_ks(b,\
    \ N));\n\n    // returns x^(N-1) a(x^(-1), y)\n    auto make_reciprocal = [](const\
    \ std::vector<std::vector<Tp>> &a, int N) {\n        std::vector<std::vector<Tp>>\
    \ b(a.size());\n        for (int i = 0; i < (int)a.size(); ++i) {\n          \
    \  b[i] = a[i];\n            b[i].resize(N);\n            std::reverse(b[i].begin(),\
    \ b[i].end());\n        }\n        return b;\n    };\n\n    // ab1 = x^(2N-2)\
    \ a(x^(-1), x^N) b(x^(-1), x^N)\n    auto ab1 =\n        convolution(pack_2d_ks(make_reciprocal(a,\
    \ N), N), pack_2d_ks(make_reciprocal(b, N), N));\n    std::vector<std::vector<Tp>>\
    \ ab(a.size() + b.size() - 1, std::vector<Tp>(N * 2 - 1));\n\n    /*\n       \
    \ example:\n                 let pack: a(x,y) |-> a(x,x^3)\n                 \
    \     rec: a(x,y) |-> x^2 a(x^(-1),y)\n\n                 a = 1 + 2*x + 4*x^2\
    \ + (3 + 4*x)*y\n                 b = 2 + 4*x + 5*x^2 + (5 + 8*x)*y\n        \
    \   pack(a) = 1 + 2*x + 4*x^2 + 3*x^3 + 4*x^4\n           pack(b) = 2 + 4*x +\
    \ 5*x^2 + 5*x^3 + 8*x^4\n      pack(rec(a)) = 4 + 2*x +   x^2 + (0 + 4*x + 3*x^2)*y\n\
    \      pack(rec(b)) = 5 + 4*x + 2*x^2 + (0 + 8*x + 5*x^2)*y\n                ab\
    \ = 2 + 8*x + 21*x^2 + 26*x^3 + 20*x^4 +\n                                   \
    \    (11     + 38*x   + 67*x^2 +  52*x^3)*y +\n                              \
    \                                   + (15        + 44*x   + 32*x^2)*y^2\n    pack(a)pack(b)\
    \ = 2 + 8*x + 21*x^2 + 37*x^3 + 58*x^4 + 67*x^5 +  67*x^6    + 44*x^7 + 32*x^8\n\
    \    pack(rec(a))pack(rec(b))\n                   = 20 + 26*x + 21*x^2 + 8*x^3\
    \ + 2*x^4 +\n                                        + ... (overlap)\n    */\n\
    \n    // restore ab[0]\n    for (int i = 0; i < N; ++i) ab[0][i] = ab0[i];\n \
    \   // ab1[0] = [x^0](x^(2N - 2) a(x^(-1), x^N) b(x^(-1), x^N))\n    for (int\
    \ i = 0; i < N; ++i) ab[0][(N - 1) * 2 - i] = ab1[i];\n    // restore ab[1..]\
    \ by subtracting the overlap coefficients\n    for (int i = 1; i < (int)(a.size()\
    \ + b.size() - 1); ++i) {\n        // TODO: remove redundant assignment/subtraction\n\
    \        for (int j = 0; j < N * 2 - 1; ++j) {\n            ab0[(i - 1) * N +\
    \ j] -= ab[i - 1][j];\n            ab1[(i - 1) * N + j] -= ab[i - 1][(N - 1) *\
    \ 2 - j];\n        }\n        for (int j = 0; j < N; ++j) ab[i][j] = ab0[i * N\
    \ + j];\n        for (int j = 0; j < N; ++j) ab[i][(N - 1) * 2 - j] = ab1[i *\
    \ N + j];\n    }\n    for (int i = 0; i < (int)(a.size() + b.size() - 1); ++i)\
    \ ab[i].resize(lenA + lenB - 1);\n    return ab;\n}\n\n// see:\n// [1]: David\
    \ Harvey. Faster polynomial multiplication via multipoint Kronecker substitution.\n\
    //      https://doi.org/10.1016/j.jsc.2009.05.004\ntemplate <typename Tp>\ninline\
    \ std::vector<std::vector<Tp>>\nconvolution_2d_ks_negated(const std::vector<std::vector<Tp>>\
    \ &a,\n                          const std::vector<std::vector<Tp>> &b) {\n  \
    \  if (a.empty() || b.empty()) return {};\n    const int lenA = max_len_x_ks(a);\n\
    \    const int lenB = max_len_x_ks(b);\n    if (lenA == 0 || lenB == 0) return\
    \ std::vector<std::vector<Tp>>(a.size() + b.size() - 1);\n    const int N = std::max(lenA,\
    \ lenB);\n    // ab0 = a(x, x^N) b(x, x^N)\n    const auto ab0 = convolution(pack_2d_ks(a,\
    \ N), pack_2d_ks(b, N));\n\n    // returns a(x, -y)\n    auto make_negated = [](const\
    \ std::vector<std::vector<Tp>> &a) {\n        auto b = a;\n        for (int i\
    \ = 1; i < (int)b.size(); i += 2)\n            for (int j = 0; j < (int)b[i].size();\
    \ ++j) b[i][j] = -b[i][j];\n        return b;\n    };\n\n    // ab1 = a(x, -x^N)\
    \ b(x, -x^N)\n    const auto ab1 = convolution(pack_2d_ks(make_negated(a), N),\
    \ pack_2d_ks(make_negated(b), N));\n\n    /*\n        example:\n             \
    \    let pack: a(x,y) |-> a(x,x^3)\n\n                 a = 1 + 2*x + 4*x^2 + (3\
    \ + 4*x)*y\n                 b = 2 + 4*x + 5*x^2 + (5 + 8*x)*y\n           pack(a)\
    \ = 1 + 2*x + 4*x^2 + 3*x^3 + 4*x^4\n           pack(b) = 2 + 4*x + 5*x^2 + 5*x^3\
    \ + 8*x^4\n     pack(a(x,-y)) = 1 + 2*x + 4*x^2 + -(3*x^3 + 4*x^4)\n     pack(b(x,-y))\
    \ = 2 + 4*x + 5*x^2 + -(5*x^3 + 8*x^4)\n                ab = 2 + 8*x + 21*x^2\
    \ + 26*x^3 + 20*x^4 +\n                                       (11     + 38*x \
    \  + 67*x^2 +  52*x^3)*y +\n                                                 \
    \                + (15        + 44*x   + 32*x^2)*y^2\n    pack(a)pack(b) = 2 +\
    \ 8*x + 21*x^2 + 37*x^3 + 58*x^4 + 67*x^5 +  67*x^6    + 44*x^7 + 32*x^8\n   \
    \                                    (26+11)   (20+38) ...\n    pack(a(x,-y))pack(b(x,-y))\n\
    \                   = 2 + 8*x + 21*x^2 + 15*x^3 + -18*x^4 + ...\n            \
    \                           (26-11)   (20-38)\n    */\n\n    std::vector<std::vector<Tp>>\
    \ ab(a.size() + b.size() - 1, std::vector<Tp>(lenA + lenB - 1));\n    for (int\
    \ i = 0; i < (int)(a.size() + b.size() - 1); ++i) {\n        if (i & 1) {\n  \
    \          for (int j = 0; j < lenA + lenB - 1; ++j)\n                ab[i][j]\
    \ = (ab0[i * N + j] - ab1[i * N + j]).div_by_2();\n        } else {\n        \
    \    for (int j = 0; j < lenA + lenB - 1; ++j)\n                ab[i][j] = (ab0[i\
    \ * N + j] + ab1[i * N + j]).div_by_2();\n        }\n    }\n    return ab;\n}\n\
    #line 2 \"modint.hpp\"\n\n#include <iostream>\n#include <type_traits>\n\ntemplate\
    \ <unsigned Mod>\nclass ModInt {\n    static_assert((Mod >> 31) == 0, \"`Mod`\
    \ must less than 2^(31)\");\n    template <typename Int>\n    static std::enable_if_t<std::is_integral_v<Int>,\
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
    \    return res;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> random_vector_without_zero(int\
    \ n) {\n    std::vector<Tp> res(n);\n    xoshiro256starstar rng(std::random_device{}());\n\
    \    std::uniform_int_distribution<decltype(Tp::mod())> dis(1, Tp::mod() - 1);\n\
    \    for (int i = 0; i < n; ++i) res[i] = dis(rng);\n    return res;\n}\n#line\
    \ 11 \"test/convolution/2d_convolution.0.test.cpp\"\n\nbool verify0() {\n    std::uniform_int_distribution<>\
    \ dis(2, 50);\n    xoshiro256starstar gen(std::random_device{}());\n    using\
    \ mint        = ModInt<998244353>;\n    const int maxLenA = dis(gen);\n    const\
    \ int maxLenB = dis(gen);\n    std::vector<std::vector<mint>> A(maxLenA);\n  \
    \  std::vector<std::vector<mint>> B(maxLenB);\n    for (int i = 0; i < maxLenA;\
    \ ++i) A[i] = random_vector<mint>(dis(gen));\n    for (int i = 0; i < maxLenB;\
    \ ++i) B[i] = random_vector<mint>(dis(gen));\n    return convolution_2d_ks(A,\
    \ B) == convolution_2d_naive(A, B);\n}\n\nbool verify1() {\n    std::uniform_int_distribution<>\
    \ dis(2, 50);\n    xoshiro256starstar gen(std::random_device{}());\n    using\
    \ mint        = ModInt<998244353>;\n    const int maxLenA = dis(gen);\n    const\
    \ int maxLenB = dis(gen);\n    std::vector<std::vector<mint>> A(maxLenA);\n  \
    \  std::vector<std::vector<mint>> B(maxLenB);\n    for (int i = 0; i < maxLenA;\
    \ ++i) A[i] = random_vector<mint>(dis(gen));\n    for (int i = 0; i < maxLenB;\
    \ ++i) B[i] = random_vector<mint>(dis(gen));\n    return convolution_2d_ks_reciprocal(A,\
    \ B) == convolution_2d_naive(A, B);\n}\n\nbool verify2() {\n    std::uniform_int_distribution<>\
    \ dis(2, 50);\n    xoshiro256starstar gen(std::random_device{}());\n    using\
    \ mint        = ModInt<998244353>;\n    const int maxLenA = dis(gen);\n    const\
    \ int maxLenB = dis(gen);\n    std::vector<std::vector<mint>> A(maxLenA);\n  \
    \  std::vector<std::vector<mint>> B(maxLenB);\n    for (int i = 0; i < maxLenA;\
    \ ++i) A[i] = random_vector<mint>(dis(gen));\n    for (int i = 0; i < maxLenB;\
    \ ++i) B[i] = random_vector<mint>(dis(gen));\n    return convolution_2d_ks_negated(A,\
    \ B) == convolution_2d_naive(A, B);\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    assert(verify0());\n    assert(verify1());\n\
    \    assert(verify2());\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b;\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/aplusb\"\n\n#include \"\
    ks.hpp\"\n#include \"modint.hpp\"\n#include \"random.hpp\"\n#include \"rng.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#include <random>\n#include <vector>\n\
    \nbool verify0() {\n    std::uniform_int_distribution<> dis(2, 50);\n    xoshiro256starstar\
    \ gen(std::random_device{}());\n    using mint        = ModInt<998244353>;\n \
    \   const int maxLenA = dis(gen);\n    const int maxLenB = dis(gen);\n    std::vector<std::vector<mint>>\
    \ A(maxLenA);\n    std::vector<std::vector<mint>> B(maxLenB);\n    for (int i\
    \ = 0; i < maxLenA; ++i) A[i] = random_vector<mint>(dis(gen));\n    for (int i\
    \ = 0; i < maxLenB; ++i) B[i] = random_vector<mint>(dis(gen));\n    return convolution_2d_ks(A,\
    \ B) == convolution_2d_naive(A, B);\n}\n\nbool verify1() {\n    std::uniform_int_distribution<>\
    \ dis(2, 50);\n    xoshiro256starstar gen(std::random_device{}());\n    using\
    \ mint        = ModInt<998244353>;\n    const int maxLenA = dis(gen);\n    const\
    \ int maxLenB = dis(gen);\n    std::vector<std::vector<mint>> A(maxLenA);\n  \
    \  std::vector<std::vector<mint>> B(maxLenB);\n    for (int i = 0; i < maxLenA;\
    \ ++i) A[i] = random_vector<mint>(dis(gen));\n    for (int i = 0; i < maxLenB;\
    \ ++i) B[i] = random_vector<mint>(dis(gen));\n    return convolution_2d_ks_reciprocal(A,\
    \ B) == convolution_2d_naive(A, B);\n}\n\nbool verify2() {\n    std::uniform_int_distribution<>\
    \ dis(2, 50);\n    xoshiro256starstar gen(std::random_device{}());\n    using\
    \ mint        = ModInt<998244353>;\n    const int maxLenA = dis(gen);\n    const\
    \ int maxLenB = dis(gen);\n    std::vector<std::vector<mint>> A(maxLenA);\n  \
    \  std::vector<std::vector<mint>> B(maxLenB);\n    for (int i = 0; i < maxLenA;\
    \ ++i) A[i] = random_vector<mint>(dis(gen));\n    for (int i = 0; i < maxLenB;\
    \ ++i) B[i] = random_vector<mint>(dis(gen));\n    return convolution_2d_ks_negated(A,\
    \ B) == convolution_2d_naive(A, B);\n}\n\nint main() {\n    std::ios::sync_with_stdio(false);\n\
    \    std::cin.tie(nullptr);\n    assert(verify0());\n    assert(verify1());\n\
    \    assert(verify2());\n    long long a, b;\n    std::cin >> a >> b;\n    std::cout\
    \ << a + b;\n    return 0;\n}\n"
  dependsOn:
  - ks.hpp
  - fft.hpp
  - modint.hpp
  - random.hpp
  - rng.hpp
  isVerificationFile: true
  path: test/convolution/2d_convolution.0.test.cpp
  requiredBy: []
  timestamp: '2024-12-23 20:42:13+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/convolution/2d_convolution.0.test.cpp
layout: document
redirect_from:
- /verify/test/convolution/2d_convolution.0.test.cpp
- /verify/test/convolution/2d_convolution.0.test.cpp.html
title: test/convolution/2d_convolution.0.test.cpp
---
