---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: fft.hpp
    title: FFT
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/2d_convolution.0.test.cpp
    title: test/convolution/2d_convolution.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://doi.org/10.1016/j.jsc.2009.05.004
  bundledCode: "#line 2 \"ks.hpp\"\n\n#line 2 \"fft.hpp\"\n\n#include <algorithm>\n\
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
    }\n#line 6 \"ks.hpp\"\n\n// returns max[0 <= j < a.size()]{a[j].size()}\ntemplate\
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
    \ ab(a.size() + b.size() - 1, std::vector<Tp>(N * 2 - 1));\n    // restore ab[0]\n\
    \    for (int i = 0; i < N; ++i) ab[0][i] = ab0[i];\n    // ab1[0] = [x^0](x^(2N\
    \ - 2) a(x^(-1), x^N) b(x^(-1), x^N))\n    for (int i = 0; i < N; ++i) ab[0][(N\
    \ - 1) * 2 - i] = ab1[i];\n    // restore ab[1..] by subtracting the overlap coefficients\n\
    \    for (int i = 1; i < (int)(a.size() + b.size() - 1); ++i) {\n        // TODO:\
    \ remove redundant assignment/subtraction\n        for (int j = 0; j < N * 2 -\
    \ 1; ++j) {\n            ab0[(i - 1) * N + j] -= ab[i - 1][j];\n            ab1[(i\
    \ - 1) * N + j] -= ab[i - 1][(N - 1) * 2 - j];\n        }\n        for (int j\
    \ = 0; j < N; ++j) ab[i][j] = ab0[i * N + j];\n        for (int j = 0; j < N;\
    \ ++j) ab[i][(N - 1) * 2 - j] = ab1[i * N + j];\n    }\n    for (int i = 0; i\
    \ < (int)(a.size() + b.size() - 1); ++i) ab[i].resize(lenA + lenB - 1);\n    return\
    \ ab;\n}\n\n// see:\n// [1]: David Harvey. Faster polynomial multiplication via\
    \ multipoint Kronecker substitution.\n//      https://doi.org/10.1016/j.jsc.2009.05.004\n\
    template <typename Tp>\ninline std::vector<std::vector<Tp>>\nconvolution_2d_ks_negated(const\
    \ std::vector<std::vector<Tp>> &a,\n                          const std::vector<std::vector<Tp>>\
    \ &b) {\n    if (a.empty() || b.empty()) return {};\n    const int lenA = max_len_x_ks(a);\n\
    \    const int lenB = max_len_x_ks(b);\n    if (lenA == 0 || lenB == 0) return\
    \ std::vector<std::vector<Tp>>(a.size() + b.size() - 1);\n    const int N = std::max(lenA,\
    \ lenB);\n    // ab0 = a(x, x^N) b(x, x^N)\n    auto ab0 = convolution(pack_2d_ks(a,\
    \ N), pack_2d_ks(b, N));\n\n    // returns a(x, -y)\n    auto make_negated = [](const\
    \ std::vector<std::vector<Tp>> &a) {\n        auto b = a;\n        for (int i\
    \ = 1; i < (int)b.size(); i += 2)\n            for (int j = 0; j < (int)b[i].size();\
    \ ++j) b[i][j] = -b[i][j];\n        return b;\n    };\n\n    // ab1 = a(x, -x^N)\
    \ b(x, -x^N)\n    auto ab1 = convolution(pack_2d_ks(make_negated(a), N), pack_2d_ks(make_negated(b),\
    \ N));\n\n    std::vector<std::vector<Tp>> ab(a.size() + b.size() - 1, std::vector<Tp>(lenA\
    \ + lenB - 1));\n    for (int i = 0; i < (int)(a.size() + b.size() - 1); ++i)\
    \ {\n        if (i & 1) {\n            for (int j = 0; j < lenA + lenB - 1; ++j)\n\
    \                ab[i][j] = (ab0[i * N + j] - ab1[i * N + j]).div_by_2();\n  \
    \      } else {\n            for (int j = 0; j < lenA + lenB - 1; ++j)\n     \
    \           ab[i][j] = (ab0[i * N + j] + ab1[i * N + j]).div_by_2();\n       \
    \ }\n    }\n    return ab;\n}\n"
  code: "#pragma once\n\n#include \"fft.hpp\"\n#include <cassert>\n#include <vector>\n\
    \n// returns max[0 <= j < a.size()]{a[j].size()}\ntemplate <typename Tp>\ninline\
    \ int max_len_x_ks(const std::vector<std::vector<Tp>> &a) {\n    int len = -1;\n\
    \    for (int i = 0; i < (int)a.size(); ++i) len = std::max<int>(len, a[i].size());\n\
    \    return len;\n}\n\n// returns a(x, x^N) where a(x,y) in R[x][y]\ntemplate\
    \ <typename Tp>\ninline std::vector<Tp> pack_2d_ks(const std::vector<std::vector<Tp>>\
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
    \ ab(a.size() + b.size() - 1, std::vector<Tp>(N * 2 - 1));\n    // restore ab[0]\n\
    \    for (int i = 0; i < N; ++i) ab[0][i] = ab0[i];\n    // ab1[0] = [x^0](x^(2N\
    \ - 2) a(x^(-1), x^N) b(x^(-1), x^N))\n    for (int i = 0; i < N; ++i) ab[0][(N\
    \ - 1) * 2 - i] = ab1[i];\n    // restore ab[1..] by subtracting the overlap coefficients\n\
    \    for (int i = 1; i < (int)(a.size() + b.size() - 1); ++i) {\n        // TODO:\
    \ remove redundant assignment/subtraction\n        for (int j = 0; j < N * 2 -\
    \ 1; ++j) {\n            ab0[(i - 1) * N + j] -= ab[i - 1][j];\n            ab1[(i\
    \ - 1) * N + j] -= ab[i - 1][(N - 1) * 2 - j];\n        }\n        for (int j\
    \ = 0; j < N; ++j) ab[i][j] = ab0[i * N + j];\n        for (int j = 0; j < N;\
    \ ++j) ab[i][(N - 1) * 2 - j] = ab1[i * N + j];\n    }\n    for (int i = 0; i\
    \ < (int)(a.size() + b.size() - 1); ++i) ab[i].resize(lenA + lenB - 1);\n    return\
    \ ab;\n}\n\n// see:\n// [1]: David Harvey. Faster polynomial multiplication via\
    \ multipoint Kronecker substitution.\n//      https://doi.org/10.1016/j.jsc.2009.05.004\n\
    template <typename Tp>\ninline std::vector<std::vector<Tp>>\nconvolution_2d_ks_negated(const\
    \ std::vector<std::vector<Tp>> &a,\n                          const std::vector<std::vector<Tp>>\
    \ &b) {\n    if (a.empty() || b.empty()) return {};\n    const int lenA = max_len_x_ks(a);\n\
    \    const int lenB = max_len_x_ks(b);\n    if (lenA == 0 || lenB == 0) return\
    \ std::vector<std::vector<Tp>>(a.size() + b.size() - 1);\n    const int N = std::max(lenA,\
    \ lenB);\n    // ab0 = a(x, x^N) b(x, x^N)\n    auto ab0 = convolution(pack_2d_ks(a,\
    \ N), pack_2d_ks(b, N));\n\n    // returns a(x, -y)\n    auto make_negated = [](const\
    \ std::vector<std::vector<Tp>> &a) {\n        auto b = a;\n        for (int i\
    \ = 1; i < (int)b.size(); i += 2)\n            for (int j = 0; j < (int)b[i].size();\
    \ ++j) b[i][j] = -b[i][j];\n        return b;\n    };\n\n    // ab1 = a(x, -x^N)\
    \ b(x, -x^N)\n    auto ab1 = convolution(pack_2d_ks(make_negated(a), N), pack_2d_ks(make_negated(b),\
    \ N));\n\n    std::vector<std::vector<Tp>> ab(a.size() + b.size() - 1, std::vector<Tp>(lenA\
    \ + lenB - 1));\n    for (int i = 0; i < (int)(a.size() + b.size() - 1); ++i)\
    \ {\n        if (i & 1) {\n            for (int j = 0; j < lenA + lenB - 1; ++j)\n\
    \                ab[i][j] = (ab0[i * N + j] - ab1[i * N + j]).div_by_2();\n  \
    \      } else {\n            for (int j = 0; j < lenA + lenB - 1; ++j)\n     \
    \           ab[i][j] = (ab0[i * N + j] + ab1[i * N + j]).div_by_2();\n       \
    \ }\n    }\n    return ab;\n}\n"
  dependsOn:
  - fft.hpp
  isVerificationFile: false
  path: ks.hpp
  requiredBy: []
  timestamp: '2024-12-22 21:19:26+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/convolution/2d_convolution.0.test.cpp
documentation_of: ks.hpp
layout: document
redirect_from:
- /library/ks.hpp
- /library/ks.hpp.html
title: ks.hpp
---
