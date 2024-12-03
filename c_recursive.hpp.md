---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: binomial.hpp
    title: binomial.hpp
  - icon: ':question:'
    path: fft.hpp
    title: FFT
  - icon: ':x:'
    path: fft_doubling.hpp
    title: FFT Doubling
  - icon: ':question:'
    path: fps_basic.hpp
    title: fps_basic.hpp
  - icon: ':question:'
    path: poly_basic.hpp
    title: poly_basic.hpp
  - icon: ':question:'
    path: semi_relaxed_conv.hpp
    title: semi_relaxed_conv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/formal_power_series/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
    title: test/formal_power_series/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
  - icon: ':x:'
    path: test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
    title: test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - icon: ':x:'
    path: test/formal_power_series/shift_of_sampling_points_of_polynomial.0.test.cpp
    title: test/formal_power_series/shift_of_sampling_points_of_polynomial.0.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links:
    - https://arxiv.org/abs/2008.08822
  bundledCode: "#line 2 \"c_recursive.hpp\"\n\n#line 2 \"fft.hpp\"\n\n#include <algorithm>\n\
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
    }\n#line 2 \"fft_doubling.hpp\"\n\n#line 8 \"fft_doubling.hpp\"\n\ntemplate <typename\
    \ Iterator>\ninline void fft_doubling_n(Iterator a, int n) {\n    using Tp = typename\
    \ std::iterator_traits<Iterator>::value_type;\n    assert((n & (n - 1)) == 0);\n\
    \    std::copy_n(a, n, a + n);\n    inv_fft_n(a + n, n);\n    Tp k         = 1;\n\
    \    const auto t = FftInfo<Tp>::get().root(n).at(n / 2);\n    for (int i = 0;\
    \ i < n; ++i) a[i + n] *= k, k *= t;\n    fft_n(a + n, n);\n}\n\ntemplate <typename\
    \ Tp>\ninline void fft_doubling(std::vector<Tp> &a) {\n    const int n = a.size();\n\
    \    a.resize(n * 2);\n    fft_doubling_n(a.begin(), n);\n}\n#line 2 \"fps_basic.hpp\"\
    \n\n#line 2 \"binomial.hpp\"\n\n#line 5 \"binomial.hpp\"\n\ntemplate <typename\
    \ Tp>\nclass Binomial {\n    std::vector<Tp> factorial_, invfactorial_;\n\n  \
    \  Binomial() : factorial_{Tp(1)}, invfactorial_{Tp(1)} {}\n\n    void preprocess(int\
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
    \ invfactorial_[n]; }\n};\n#line 2 \"semi_relaxed_conv.hpp\"\n\n#line 5 \"semi_relaxed_conv.hpp\"\
    \n#include <type_traits>\n#include <utility>\n#line 8 \"semi_relaxed_conv.hpp\"\
    \n\ntemplate <typename Tp, typename Closure>\ninline std::enable_if_t<std::is_invocable_r_v<Tp,\
    \ Closure, int, const std::vector<Tp> &>,\n                        std::vector<Tp>>\n\
    semi_relaxed_convolution_naive(const std::vector<Tp> &A, Closure gen, int n) {\n\
    \    std::vector<Tp> B(n), AB(n);\n    for (int i = 0; i < n; ++i) {\n       \
    \ for (int j = std::max(0, i - (int)A.size() + 1); j < i; ++j) AB[i] += A[i -\
    \ j] * B[j];\n        B[i] = gen(i, AB);\n        if (!A.empty()) AB[i] += A[0]\
    \ * B[i];\n    }\n    return B;\n}\n\n// returns coefficients generated by closure\n\
    // closure: gen(index, current_product)\ntemplate <typename Tp, typename Closure>\n\
    inline std::enable_if_t<std::is_invocable_r_v<Tp, Closure, int, const std::vector<Tp>\
    \ &>,\n                        std::vector<Tp>>\nsemi_relaxed_convolution(const\
    \ std::vector<Tp> &A, Closure gen, int n) {\n    if (A.size() < 60) return semi_relaxed_convolution_naive(A,\
    \ gen, n);\n    enum { BaseCaseSize = 32 };\n    static_assert((BaseCaseSize &\
    \ (BaseCaseSize - 1)) == 0);\n\n    static const int Block[]     = {16, 16, 16,\
    \ 16, 16};\n    static const int BlockSize[] = {\n        BaseCaseSize,\n    \
    \    BaseCaseSize * Block[0],\n        BaseCaseSize * Block[0] * Block[1],\n \
    \       BaseCaseSize * Block[0] * Block[1] * Block[2],\n        BaseCaseSize *\
    \ Block[0] * Block[1] * Block[2] * Block[3],\n        BaseCaseSize * Block[0]\
    \ * Block[1] * Block[2] * Block[3] * Block[4],\n    };\n\n    // returns (which_block,\
    \ level)\n    auto blockinfo = [](int ind) {\n        int i = ind / BaseCaseSize,\
    \ lv = 0;\n        while ((i & (Block[lv] - 1)) == 0) i /= Block[lv++];\n    \
    \    return std::make_pair(i & (Block[lv] - 1), lv);\n    };\n\n    std::vector<Tp>\
    \ B(n), AB(n);\n    std::vector<std::vector<std::vector<Tp>>> dftA, dftB;\n\n\
    \    for (int i = 0; i < n; ++i) {\n        const int s = i & (BaseCaseSize -\
    \ 1);\n\n        // blocked contribution\n        if (i >= BaseCaseSize && s ==\
    \ 0) {\n            const auto [j, lv]  = blockinfo(i);\n            const int\
    \ blocksize = BlockSize[lv];\n\n            if (blocksize * j == i) {\n      \
    \          if ((int)dftA.size() == lv) {\n                    dftA.emplace_back();\n\
    \                    dftB.emplace_back(Block[lv] - 1);\n                }\n  \
    \              if ((j - 1) * blocksize < (int)A.size()) {\n                  \
    \  dftA[lv]\n                        .emplace_back(A.begin() + (j - 1) * blocksize,\n\
    \                                      A.begin() + std::min<int>((j + 1) * blocksize,\
    \ A.size()))\n                        .resize(blocksize * 2);\n              \
    \      fft(dftA[lv][j - 1]);\n                }\n            }\n\n           \
    \ if (!dftA[lv].empty()) {\n                dftB[lv][j - 1].resize(blocksize *\
    \ 2);\n                std::copy_n(B.begin() + (i - blocksize), blocksize, dftB[lv][j\
    \ - 1].begin());\n                std::fill_n(dftB[lv][j - 1].begin() + blocksize,\
    \ blocksize, Tp(0));\n                fft(dftB[lv][j - 1]);\n\n              \
    \  // middle product\n                std::vector<Tp> mp(blocksize * 2);\n   \
    \             for (int k = 0; k < std::min<int>(j, dftA[lv].size()); ++k)\n  \
    \                  for (int l = 0; l < blocksize * 2; ++l)\n                 \
    \       mp[l] += dftA[lv][k][l] * dftB[lv][j - 1 - k][l];\n                inv_fft(mp);\n\
    \n                for (int k = 0; k < blocksize && i + k < n; ++k) AB[i + k] +=\
    \ mp[k + blocksize];\n            }\n        }\n\n        // basecase contribution\n\
    \        for (int j = std::max(i - s, i - (int)A.size() + 1); j < i; ++j) AB[i]\
    \ += A[i - j] * B[j];\n        B[i] = gen(i, AB);\n        if (!A.empty()) AB[i]\
    \ += A[0] * B[i];\n    }\n\n    return B;\n}\n#line 7 \"fps_basic.hpp\"\n\ntemplate\
    \ <typename Tp>\ninline int order(const std::vector<Tp> &a) {\n    for (int i\
    \ = 0; i < (int)a.size(); ++i)\n        if (a[i] != 0) return i;\n    return -1;\n\
    }\n\ntemplate <typename Tp>\ninline std::vector<Tp> fps_inv(const std::vector<Tp>\
    \ &a, int n) {\n    assert(!a.empty());\n    if (n <= 0) return {};\n    return\
    \ semi_relaxed_convolution(\n        a, [v = a[0].inv()](int n, auto &&c) { return\
    \ n == 0 ? v : -c[n] * v; }, n);\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ fps_div(const std::vector<Tp> &a, const std::vector<Tp> &b, int n) {\n    assert(!b.empty());\n\
    \    if (n <= 0) return {};\n    return semi_relaxed_convolution(\n        b,\n\
    \        [&, v = b[0].inv()](int n, auto &&c) {\n            if (n < (int)a.size())\
    \ return (a[n] - c[n]) * v;\n            return -c[n] * v;\n        },\n     \
    \   n);\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> deriv(const std::vector<Tp>\
    \ &a) {\n    const int n = (int)a.size() - 1;\n    if (n <= 0) return {};\n  \
    \  std::vector<Tp> res(n);\n    for (int i = 1; i <= n; ++i) res[i - 1] = a[i]\
    \ * i;\n    return res;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> integr(const\
    \ std::vector<Tp> &a, Tp c = {}) {\n    const int n = a.size() + 1;\n    auto\
    \ &&bin  = Binomial<Tp>::get(n);\n    std::vector<Tp> res(n);\n    res[0] = c;\n\
    \    for (int i = 1; i < n; ++i) res[i] = a[i - 1] * bin.inv(i);\n    return res;\n\
    }\n\ntemplate <typename Tp>\ninline std::vector<Tp> fps_log(const std::vector<Tp>\
    \ &a, int n) {\n    return integr(fps_div(deriv(a), a, n - 1));\n}\n\ntemplate\
    \ <typename Tp>\ninline std::vector<Tp> fps_exp(const std::vector<Tp> &a, int\
    \ n) {\n    if (n <= 0) return {};\n    assert(!a.empty() && a[0] == 0);\n   \
    \ return semi_relaxed_convolution(\n        deriv(a),\n        [bin = Binomial<Tp>::get(n)](int\
    \ n, auto &&c) {\n            return n == 0 ? Tp(1) : c[n - 1] * bin.inv(n);\n\
    \        },\n        n);\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ fps_pow(std::vector<Tp> a, long long e, int n) {\n    if (n <= 0) return {};\n\
    \    if (e == 0) {\n        std::vector<Tp> res(n);\n        res[0] = 1;\n   \
    \     return res;\n    }\n\n    const int o = order(a);\n    if (o < 0 || o >\
    \ n / e || (o == n / e && n % e == 0)) return std::vector<Tp>(n);\n    if (o !=\
    \ 0) a.erase(a.begin(), a.begin() + o);\n\n    const Tp ia0 = a[0].inv();\n  \
    \  const Tp a0e = a[0].pow(e);\n    const Tp me  = e;\n\n    for (int i = 0; i\
    \ < (int)a.size(); ++i) a[i] *= ia0;\n    a = fps_log(a, n - o * e);\n    for\
    \ (int i = 0; i < (int)a.size(); ++i) a[i] *= me;\n    a = fps_exp(a, n - o *\
    \ e);\n    for (int i = 0; i < (int)a.size(); ++i) a[i] *= a0e;\n\n    a.insert(a.begin(),\
    \ o * e, Tp(0));\n    return a;\n}\n#line 2 \"poly_basic.hpp\"\n\n#line 10 \"\
    poly_basic.hpp\"\n\ntemplate <typename Tp>\ninline int degree(const std::vector<Tp>\
    \ &a) {\n    int n = (int)a.size() - 1;\n    while (n >= 0 && a[n] == 0) --n;\n\
    \    return n;\n}\n\ntemplate <typename Tp>\ninline void shrink(std::vector<Tp>\
    \ &a) {\n    a.resize(degree(a) + 1);\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ taylor_shift(std::vector<Tp> a, Tp c) {\n    const int n = a.size();\n    auto\
    \ &&bin  = Binomial<Tp>::get(n);\n    for (int i = 0; i < n; ++i) a[i] *= bin.factorial(i);\n\
    \    Tp cc = 1;\n    std::vector<Tp> b(n);\n    for (int i = 0; i < n; ++i) {\n\
    \        b[i] = cc * bin.inv_factorial(i);\n        cc *= c;\n    }\n    std::reverse(a.begin(),\
    \ a.end());\n    auto ab = convolution(a, b);\n    ab.resize(n);\n    std::reverse(ab.begin(),\
    \ ab.end());\n    for (int i = 0; i < n; ++i) ab[i] *= bin.inv_factorial(i);\n\
    \    return ab;\n}\n\n// returns (quotient, remainder)\n// O(deg(Q)deg(B))\ntemplate\
    \ <typename Tp>\ninline std::pair<std::vector<Tp>, std::vector<Tp>> euclidean_div_naive(const\
    \ std::vector<Tp> &A,\n                                                      \
    \                 const std::vector<Tp> &B) {\n    const int degA = degree(A);\n\
    \    const int degB = degree(B);\n    assert(degB >= 0);\n    const int degQ =\
    \ degA - degB;\n    if (degQ < 0) return {std::vector<Tp>{Tp(0)}, A};\n    std::vector<Tp>\
    \ Q(degQ + 1), R = A;\n    const auto inv = B[degB].inv();\n    for (int i = degQ,\
    \ n = degA; i >= 0; --i)\n        if ((Q[i] = R[n--] * inv) != 0)\n          \
    \  for (int j = 0; j <= degB; ++j) R[i + j] -= Q[i] * B[j];\n    R.resize(degB);\n\
    \    return {Q, R};\n}\n\n// O(min(deg(Q)^2,deg(Q)deg(B)))\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> euclidean_div_quotient_naive(const std::vector<Tp>\
    \ &A,\n                                                    const std::vector<Tp>\
    \ &B) {\n    const int degA = degree(A);\n    const int degB = degree(B);\n  \
    \  assert(degB >= 0);\n    const int degQ = degA - degB;\n    if (degQ < 0) return\
    \ {Tp(0)};\n    const auto inv = B[degB].inv();\n    std::vector<Tp> Q(degQ +\
    \ 1);\n    for (int i = 0; i <= degQ; ++i) {\n        for (int j = 1; j <= std::min(i,\
    \ degB); ++j) Q[degQ - i] += B[degB - j] * Q[degQ - i + j];\n        Q[degQ -\
    \ i] = (A[degA - i] - Q[degQ - i]) * inv;\n    }\n    return Q;\n}\n\n// returns\
    \ (quotient, remainder)\ntemplate <typename Tp>\ninline std::pair<std::vector<Tp>,\
    \ std::vector<Tp>> euclidean_div(const std::vector<Tp> &A,\n                 \
    \                                                const std::vector<Tp> &B) {\n\
    \    const int degA = degree(A);\n    const int degB = degree(B);\n    assert(degB\
    \ >= 0);\n    // A = Q*B + R => A/B = Q + R/B in R((x^(-1)))\n    const int degQ\
    \ = degA - degB;\n    if (degQ < 0) return {std::vector<Tp>{Tp(0)}, A};\n    if\
    \ (degQ < 60 || degB < 60) return euclidean_div_naive(A, B);\n\n    auto Q = fps_div(std::vector(A.rend()\
    \ - (degA + 1), A.rend()),\n                     std::vector(B.rend() - (degB\
    \ + 1), B.rend()), degQ + 1);\n    std::reverse(Q.begin(), Q.end());\n\n    //\
    \ returns a mod (x^n-1)\n    auto make_cyclic = [](const std::vector<Tp> &a, int\
    \ n) {\n        assert((n & (n - 1)) == 0);\n        std::vector<Tp> b(n);\n \
    \       for (int i = 0; i < (int)a.size(); ++i) b[i & (n - 1)] += a[i];\n    \
    \    return b;\n    };\n\n    const int len      = fft_len(std::max(degB, 1));\n\
    \    const auto cyclicA = make_cyclic(A, len);\n    auto cyclicB       = make_cyclic(B,\
    \ len);\n    auto cyclicQ       = make_cyclic(Q, len);\n\n    fft(cyclicQ);\n\
    \    fft(cyclicB);\n    for (int i = 0; i < len; ++i) cyclicQ[i] *= cyclicB[i];\n\
    \    inv_fft(cyclicQ);\n\n    // R = A - QB mod (x^n-1) (n >= degB)\n    std::vector<Tp>\
    \ R(degB);\n    for (int i = 0; i < degB; ++i) R[i] = cyclicA[i] - cyclicQ[i];\n\
    \    return {Q, R};\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> euclidean_div_quotient(const\
    \ std::vector<Tp> &A, const std::vector<Tp> &B) {\n    const int degA = degree(A);\n\
    \    const int degB = degree(B);\n    assert(degB >= 0);\n    // A = Q*B + R =>\
    \ A/B = Q + R/B in R((x^(-1)))\n    const int degQ = degA - degB;\n    if (degQ\
    \ < 0) return {Tp(0)};\n    if (std::min(degQ, degB) < 60) return euclidean_div_quotient_naive(A,\
    \ B);\n\n    auto Q = fps_div(std::vector(A.rend() - (degA + 1), A.rend()),\n\
    \                     std::vector(B.rend() - (degB + 1), B.rend()), degQ + 1);\n\
    \    std::reverse(Q.begin(), Q.end());\n    return Q;\n}\n#line 10 \"c_recursive.hpp\"\
    \n\n// see:\n// [1]: Alin Bostan, Ryuhei Mori.\n//      A Simple and Fast Algorithm\
    \ for Computing the N-th Term of a Linearly Recurrent Sequence.\n//      https://arxiv.org/abs/2008.08822\n\
    \ntemplate <typename Tp>\ninline std::vector<Tp> fps_inv_newton(const std::vector<Tp>\
    \ &a, int n) {\n    assert(!a.empty());\n    if (a <= 0) return {};\n    const\
    \ int len = fft_len(n);\n    std::vector<Tp> invA(len), shopA(len), shopB(len);\n\
    \    invA[0] = a[0].inv();\n    for (int i = 2; i <= len; i *= 2) {\n        std::fill(std::copy_n(a.begin(),\
    \ std::min<int>(a.size(), i), shopA.begin()),\n                  shopA.begin()\
    \ + i, Tp(0));\n        std::copy_n(invA.begin(), i, shopB.begin());\n       \
    \ fft_n(shopA.begin(), i);\n        fft_n(shopB.begin(), i);\n        for (int\
    \ j = 0; j < i; ++j) shopA[j] *= shopB[j];\n        inv_fft_n(shopA.begin(), i);\n\
    \        std::fill_n(shopA.begin(), i / 2, MInt());\n        fft_n(shopA.begin(),\
    \ i);\n        for (int j = 0; j < i; ++j) shopA[j] *= shopB[j];\n        inv_fft_n(shopA.begin(),\
    \ i);\n        for (int j = i / 2; j < i; ++j) invA[j] = -shopA[j];\n    }\n \
    \   invA.resize(n);\n    return invA;\n}\n\ntemplate <typename Tp>\ninline void\
    \ fft_high(std::vector<Tp> &a) {\n    const int n = a.size();\n    inv_fft_n(a.begin()\
    \ + n / 2, n / 2);\n    Tp k         = 1;\n    const auto t = FftInfo<Tp>::get().inv_root(n\
    \ / 2).at(n / 4);\n    for (int i = 0; i < n / 2; ++i) a[i + n / 2] *= k, k *=\
    \ t;\n    fft_n(a.begin() + n / 2, n / 2);\n    for (int i = 0; i < n / 2; ++i)\
    \ a[i] = (a[i] - a[i + n / 2]).div_by_2();\n    a.resize(n / 2);\n}\n\n// returns\
    \ DFT([x^[L,L+len/2)]1/Q)\n// 1/Q in R((x))\n// requires len/2 > deg(Q), len/2\
    \ is even\ntemplate <typename Tp>\ninline std::vector<Tp> bostan_mori_laurent_series(std::vector<Tp>\
    \ dftQ, long long L) {\n    const int len = dftQ.size() * 2;\n    if (L <= 0)\
    \ {\n        inv_fft(dftQ);\n        const int ordQ = order(dftQ);\n        assert(ordQ\
    \ >= 0);\n        if (L + len / 2 <= -ordQ) return std::vector<Tp>(len / 2);\n\
    \        auto invQ =\n            fps_inv_newton(std::vector(dftQ.begin() + ordQ,\
    \ dftQ.end()), L + len / 2 + ordQ);\n        if (-ordQ < (int)L) {\n         \
    \   // ?x^(-ord(Q)) + ... + ?x^L + ... + ?x^(L+len/2-1)\n            invQ.erase(invQ.begin(),\
    \ invQ.begin() + (L + ordQ));\n        } else {\n            // ?x^L + ... + ?x^(-ord(Q))\
    \ + ... + ?x^(L+len/2-1)\n            invQ.insert(invQ.begin(), -ordQ - L, Tp(0));\n\
    \        }\n        fft(invQ);\n        return invQ;\n    }\n\n    fft_doubling(dftQ);\n\
    \    std::vector<Tp> dftV(len / 2);\n    for (int i = 0; i < len; i += 2) dftV[i\
    \ / 2] = dftQ[i] * dftQ[i + 1];\n    const auto dftT =\n        bostan_mori_laurent_series(dftV,\
    \ (L - len / 2 + (L & 1)) / 2 /* ceil((L-len/2)/2) */);\n\n    std::vector<Tp>\
    \ dftU(len);\n    if (L & 1) {\n        auto &&root = FftInfo<Tp>::get().root(len\
    \ / 2);\n        for (int i = 0; i < len; i += 2) {\n            dftU[i]     =\
    \ dftT[i / 2] * dftQ[i + 1] * root[i / 2];\n            dftU[i + 1] = dftT[i /\
    \ 2] * dftQ[i] * -root[i / 2];\n        }\n    } else {\n        for (int i =\
    \ 0; i < len; i += 2) {\n            dftU[i]     = dftT[i / 2] * dftQ[i + 1];\n\
    \            dftU[i + 1] = dftT[i / 2] * dftQ[i];\n        }\n    }\n\n    fft_high(dftU);\n\
    \    return dftU;\n}\n\n// returns DFT([x^[-len/2,0)]x^k/Q)\n// x^k/Q in R((x^(-1)))\n\
    // requires len/2 > degQ\ntemplate <typename Tp>\ninline std::vector<Tp> bostan_mori_reversed_laurent_series(std::vector<Tp>\
    \ dftQ, long long k) {\n    assert(k >= 0);\n    const int len = dftQ.size() *\
    \ 2;\n    if (k < len / 2LL) {\n        inv_fft(dftQ);\n        const int degQ\
    \ = degree(dftQ);\n        assert(degQ >= 0);\n        dftQ.resize(degQ + 1);\n\
    \        std::reverse(dftQ.begin(), dftQ.end());\n        auto invQ = fps_inv_newton(dftQ,\
    \ len / 2 - degQ + k + 1);\n        std::reverse(invQ.begin(), invQ.end());\n\
    \        invQ.resize(len / 2);\n        fft(invQ);\n        return invQ;\n   \
    \ }\n\n    fft_doubling(dftQ);\n    std::vector<Tp> dftV(len / 2);\n    for (int\
    \ i = 0; i < len; i += 2) dftV[i / 2] = dftQ[i] * dftQ[i + 1];\n    const auto\
    \ dftT = bostan_mori_reversed_laurent_series(dftV, k / 2);\n\n    std::vector<Tp>\
    \ dftU(len);\n    if (k & 1) {\n        auto &&root = FftInfo<Tp>::get().root(len\
    \ / 2);\n        for (int i = 0; i < len; i += 2) {\n            dftU[i]     =\
    \ dftT[i / 2] * dftQ[i + 1] * root[i / 2];\n            dftU[i + 1] = dftT[i /\
    \ 2] * dftQ[i] * -root[i / 2];\n        }\n    } else {\n        for (int i =\
    \ 0; i < len; i += 2) {\n            dftU[i]     = dftT[i / 2] * dftQ[i + 1];\n\
    \            dftU[i + 1] = dftT[i / 2] * dftQ[i];\n        }\n    }\n\n    fft_high(dftU);\n\
    \    return dftU;\n}\n\n// returns x^k mod Q\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ xk_mod(long long k, const std::vector<Tp> &Q) {\n    assert(k >= 0);\n    const\
    \ int degQ = degree(Q);\n    assert(degQ >= 0);\n    if (degQ == 0) return {};\n\
    \    if (k < degQ) {\n        std::vector<Tp> res(degQ);\n        res[k] = 1;\n\
    \        return res;\n    }\n\n    const int len = fft_len(degQ * 2 + 1);\n  \
    \  if (k < len / 2LL) {\n        auto invQ = fps_inv_newton(std::vector(Q.rend()\
    \ - (degQ + 1), Q.rend()), k + 1);\n        std::reverse(invQ.begin(), invQ.end());\n\
    \        invQ.resize(degQ);\n        auto res = convolution(invQ, Q);\n      \
    \  res.erase(res.begin(), res.begin() + degQ);\n        res.resize(degQ);\n  \
    \      return res;\n    }\n\n    auto dftQ = std::vector(Q.rend() - (degQ + 1),\
    \ Q.rend());\n    dftQ.resize(len);\n    fft(dftQ);\n    std::vector<Tp> dftV(len\
    \ / 2);\n    for (int i = 0; i < len; i += 2) dftV[i / 2] = dftQ[i] * dftQ[i +\
    \ 1];\n    const long long L = k + 1 - degQ;\n    const auto dftT   = bostan_mori_laurent_series(dftV,\
    \ (L - len / 2 + (L & 1)) / 2);\n    std::vector<Tp> dftU(len);\n    if (L & 1)\
    \ {\n        auto &&root = FftInfo<Tp>::get().root(len / 2);\n        for (int\
    \ i = 0; i < len; i += 2) {\n            dftU[i]     = dftT[i / 2] * dftQ[i +\
    \ 1] * root[i / 2];\n            dftU[i + 1] = dftT[i / 2] * dftQ[i] * -root[i\
    \ / 2];\n        }\n    } else {\n        for (int i = 0; i < len; i += 2) {\n\
    \            dftU[i]     = dftT[i / 2] * dftQ[i + 1];\n            dftU[i + 1]\
    \ = dftT[i / 2] * dftQ[i];\n        }\n    }\n    inv_fft(dftU);\n    dftU.erase(dftU.begin(),\
    \ dftU.begin() + len / 2);\n    dftU.resize(degQ);\n    dftU.resize(len);\n  \
    \  fft(dftU);\n    for (int i = 0; i < len; ++i) dftU[i] *= dftQ[i];\n    inv_fft(dftU);\n\
    \    dftU.resize(degQ);\n    std::reverse(dftU.begin(), dftU.end());\n    return\
    \ dftU;\n}\n\n// returns [x^[L,R)]P/Q\n// P: polynomial\n// Q: non-zero polynomial,\
    \ ord(Q)=0\ntemplate <typename Tp>\ninline std::vector<Tp> slice_coeff_rational(const\
    \ std::vector<Tp> &P, const std::vector<Tp> &Q,\n                            \
    \                long long L, long long R) {\n    assert(L >= 0);\n    assert(order(Q)\
    \ == 0);\n    const int degP = degree(P);\n    if (degP < 0) return std::vector<Tp>(R\
    \ - L);\n    const int degQ = degree(Q);\n    const int N    = std::max(degP +\
    \ 1, degQ);\n    auto P0 = P, Q0 = Q;\n    P0.resize(N);\n    std::reverse(P0.begin(),\
    \ P0.end());\n    Q0.resize(N + 1);\n    std::reverse(Q0.begin(), Q0.end());\n\
    \    auto [q, r] = euclidean_div(convolution(xk_mod(L, Q0), P0), Q0);\n    r.resize(N);\n\
    \    std::reverse(r.begin(), r.end());\n    return fps_div(r, Q, R - L);\n}\n\n\
    // returns [x^k]P/Q\n// P: polynomial\n// Q: non-zero polynomial, ord(Q)=0\ntemplate\
    \ <typename Tp>\ninline Tp div_at(const std::vector<Tp> &P, const std::vector<Tp>\
    \ &Q, long long k) {\n    return slice_coeff_rational(P, Q, k, k + 1).at(0);\n\
    }\n"
  code: "#pragma once\n\n#include \"fft.hpp\"\n#include \"fft_doubling.hpp\"\n#include\
    \ \"fps_basic.hpp\"\n#include \"poly_basic.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\n// see:\n// [1]: Alin Bostan, Ryuhei Mori.\n\
    //      A Simple and Fast Algorithm for Computing the N-th Term of a Linearly\
    \ Recurrent Sequence.\n//      https://arxiv.org/abs/2008.08822\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> fps_inv_newton(const std::vector<Tp> &a, int n)\
    \ {\n    assert(!a.empty());\n    if (a <= 0) return {};\n    const int len =\
    \ fft_len(n);\n    std::vector<Tp> invA(len), shopA(len), shopB(len);\n    invA[0]\
    \ = a[0].inv();\n    for (int i = 2; i <= len; i *= 2) {\n        std::fill(std::copy_n(a.begin(),\
    \ std::min<int>(a.size(), i), shopA.begin()),\n                  shopA.begin()\
    \ + i, Tp(0));\n        std::copy_n(invA.begin(), i, shopB.begin());\n       \
    \ fft_n(shopA.begin(), i);\n        fft_n(shopB.begin(), i);\n        for (int\
    \ j = 0; j < i; ++j) shopA[j] *= shopB[j];\n        inv_fft_n(shopA.begin(), i);\n\
    \        std::fill_n(shopA.begin(), i / 2, MInt());\n        fft_n(shopA.begin(),\
    \ i);\n        for (int j = 0; j < i; ++j) shopA[j] *= shopB[j];\n        inv_fft_n(shopA.begin(),\
    \ i);\n        for (int j = i / 2; j < i; ++j) invA[j] = -shopA[j];\n    }\n \
    \   invA.resize(n);\n    return invA;\n}\n\ntemplate <typename Tp>\ninline void\
    \ fft_high(std::vector<Tp> &a) {\n    const int n = a.size();\n    inv_fft_n(a.begin()\
    \ + n / 2, n / 2);\n    Tp k         = 1;\n    const auto t = FftInfo<Tp>::get().inv_root(n\
    \ / 2).at(n / 4);\n    for (int i = 0; i < n / 2; ++i) a[i + n / 2] *= k, k *=\
    \ t;\n    fft_n(a.begin() + n / 2, n / 2);\n    for (int i = 0; i < n / 2; ++i)\
    \ a[i] = (a[i] - a[i + n / 2]).div_by_2();\n    a.resize(n / 2);\n}\n\n// returns\
    \ DFT([x^[L,L+len/2)]1/Q)\n// 1/Q in R((x))\n// requires len/2 > deg(Q), len/2\
    \ is even\ntemplate <typename Tp>\ninline std::vector<Tp> bostan_mori_laurent_series(std::vector<Tp>\
    \ dftQ, long long L) {\n    const int len = dftQ.size() * 2;\n    if (L <= 0)\
    \ {\n        inv_fft(dftQ);\n        const int ordQ = order(dftQ);\n        assert(ordQ\
    \ >= 0);\n        if (L + len / 2 <= -ordQ) return std::vector<Tp>(len / 2);\n\
    \        auto invQ =\n            fps_inv_newton(std::vector(dftQ.begin() + ordQ,\
    \ dftQ.end()), L + len / 2 + ordQ);\n        if (-ordQ < (int)L) {\n         \
    \   // ?x^(-ord(Q)) + ... + ?x^L + ... + ?x^(L+len/2-1)\n            invQ.erase(invQ.begin(),\
    \ invQ.begin() + (L + ordQ));\n        } else {\n            // ?x^L + ... + ?x^(-ord(Q))\
    \ + ... + ?x^(L+len/2-1)\n            invQ.insert(invQ.begin(), -ordQ - L, Tp(0));\n\
    \        }\n        fft(invQ);\n        return invQ;\n    }\n\n    fft_doubling(dftQ);\n\
    \    std::vector<Tp> dftV(len / 2);\n    for (int i = 0; i < len; i += 2) dftV[i\
    \ / 2] = dftQ[i] * dftQ[i + 1];\n    const auto dftT =\n        bostan_mori_laurent_series(dftV,\
    \ (L - len / 2 + (L & 1)) / 2 /* ceil((L-len/2)/2) */);\n\n    std::vector<Tp>\
    \ dftU(len);\n    if (L & 1) {\n        auto &&root = FftInfo<Tp>::get().root(len\
    \ / 2);\n        for (int i = 0; i < len; i += 2) {\n            dftU[i]     =\
    \ dftT[i / 2] * dftQ[i + 1] * root[i / 2];\n            dftU[i + 1] = dftT[i /\
    \ 2] * dftQ[i] * -root[i / 2];\n        }\n    } else {\n        for (int i =\
    \ 0; i < len; i += 2) {\n            dftU[i]     = dftT[i / 2] * dftQ[i + 1];\n\
    \            dftU[i + 1] = dftT[i / 2] * dftQ[i];\n        }\n    }\n\n    fft_high(dftU);\n\
    \    return dftU;\n}\n\n// returns DFT([x^[-len/2,0)]x^k/Q)\n// x^k/Q in R((x^(-1)))\n\
    // requires len/2 > degQ\ntemplate <typename Tp>\ninline std::vector<Tp> bostan_mori_reversed_laurent_series(std::vector<Tp>\
    \ dftQ, long long k) {\n    assert(k >= 0);\n    const int len = dftQ.size() *\
    \ 2;\n    if (k < len / 2LL) {\n        inv_fft(dftQ);\n        const int degQ\
    \ = degree(dftQ);\n        assert(degQ >= 0);\n        dftQ.resize(degQ + 1);\n\
    \        std::reverse(dftQ.begin(), dftQ.end());\n        auto invQ = fps_inv_newton(dftQ,\
    \ len / 2 - degQ + k + 1);\n        std::reverse(invQ.begin(), invQ.end());\n\
    \        invQ.resize(len / 2);\n        fft(invQ);\n        return invQ;\n   \
    \ }\n\n    fft_doubling(dftQ);\n    std::vector<Tp> dftV(len / 2);\n    for (int\
    \ i = 0; i < len; i += 2) dftV[i / 2] = dftQ[i] * dftQ[i + 1];\n    const auto\
    \ dftT = bostan_mori_reversed_laurent_series(dftV, k / 2);\n\n    std::vector<Tp>\
    \ dftU(len);\n    if (k & 1) {\n        auto &&root = FftInfo<Tp>::get().root(len\
    \ / 2);\n        for (int i = 0; i < len; i += 2) {\n            dftU[i]     =\
    \ dftT[i / 2] * dftQ[i + 1] * root[i / 2];\n            dftU[i + 1] = dftT[i /\
    \ 2] * dftQ[i] * -root[i / 2];\n        }\n    } else {\n        for (int i =\
    \ 0; i < len; i += 2) {\n            dftU[i]     = dftT[i / 2] * dftQ[i + 1];\n\
    \            dftU[i + 1] = dftT[i / 2] * dftQ[i];\n        }\n    }\n\n    fft_high(dftU);\n\
    \    return dftU;\n}\n\n// returns x^k mod Q\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ xk_mod(long long k, const std::vector<Tp> &Q) {\n    assert(k >= 0);\n    const\
    \ int degQ = degree(Q);\n    assert(degQ >= 0);\n    if (degQ == 0) return {};\n\
    \    if (k < degQ) {\n        std::vector<Tp> res(degQ);\n        res[k] = 1;\n\
    \        return res;\n    }\n\n    const int len = fft_len(degQ * 2 + 1);\n  \
    \  if (k < len / 2LL) {\n        auto invQ = fps_inv_newton(std::vector(Q.rend()\
    \ - (degQ + 1), Q.rend()), k + 1);\n        std::reverse(invQ.begin(), invQ.end());\n\
    \        invQ.resize(degQ);\n        auto res = convolution(invQ, Q);\n      \
    \  res.erase(res.begin(), res.begin() + degQ);\n        res.resize(degQ);\n  \
    \      return res;\n    }\n\n    auto dftQ = std::vector(Q.rend() - (degQ + 1),\
    \ Q.rend());\n    dftQ.resize(len);\n    fft(dftQ);\n    std::vector<Tp> dftV(len\
    \ / 2);\n    for (int i = 0; i < len; i += 2) dftV[i / 2] = dftQ[i] * dftQ[i +\
    \ 1];\n    const long long L = k + 1 - degQ;\n    const auto dftT   = bostan_mori_laurent_series(dftV,\
    \ (L - len / 2 + (L & 1)) / 2);\n    std::vector<Tp> dftU(len);\n    if (L & 1)\
    \ {\n        auto &&root = FftInfo<Tp>::get().root(len / 2);\n        for (int\
    \ i = 0; i < len; i += 2) {\n            dftU[i]     = dftT[i / 2] * dftQ[i +\
    \ 1] * root[i / 2];\n            dftU[i + 1] = dftT[i / 2] * dftQ[i] * -root[i\
    \ / 2];\n        }\n    } else {\n        for (int i = 0; i < len; i += 2) {\n\
    \            dftU[i]     = dftT[i / 2] * dftQ[i + 1];\n            dftU[i + 1]\
    \ = dftT[i / 2] * dftQ[i];\n        }\n    }\n    inv_fft(dftU);\n    dftU.erase(dftU.begin(),\
    \ dftU.begin() + len / 2);\n    dftU.resize(degQ);\n    dftU.resize(len);\n  \
    \  fft(dftU);\n    for (int i = 0; i < len; ++i) dftU[i] *= dftQ[i];\n    inv_fft(dftU);\n\
    \    dftU.resize(degQ);\n    std::reverse(dftU.begin(), dftU.end());\n    return\
    \ dftU;\n}\n\n// returns [x^[L,R)]P/Q\n// P: polynomial\n// Q: non-zero polynomial,\
    \ ord(Q)=0\ntemplate <typename Tp>\ninline std::vector<Tp> slice_coeff_rational(const\
    \ std::vector<Tp> &P, const std::vector<Tp> &Q,\n                            \
    \                long long L, long long R) {\n    assert(L >= 0);\n    assert(order(Q)\
    \ == 0);\n    const int degP = degree(P);\n    if (degP < 0) return std::vector<Tp>(R\
    \ - L);\n    const int degQ = degree(Q);\n    const int N    = std::max(degP +\
    \ 1, degQ);\n    auto P0 = P, Q0 = Q;\n    P0.resize(N);\n    std::reverse(P0.begin(),\
    \ P0.end());\n    Q0.resize(N + 1);\n    std::reverse(Q0.begin(), Q0.end());\n\
    \    auto [q, r] = euclidean_div(convolution(xk_mod(L, Q0), P0), Q0);\n    r.resize(N);\n\
    \    std::reverse(r.begin(), r.end());\n    return fps_div(r, Q, R - L);\n}\n\n\
    // returns [x^k]P/Q\n// P: polynomial\n// Q: non-zero polynomial, ord(Q)=0\ntemplate\
    \ <typename Tp>\ninline Tp div_at(const std::vector<Tp> &P, const std::vector<Tp>\
    \ &Q, long long k) {\n    return slice_coeff_rational(P, Q, k, k + 1).at(0);\n\
    }\n"
  dependsOn:
  - fft.hpp
  - fft_doubling.hpp
  - fps_basic.hpp
  - binomial.hpp
  - semi_relaxed_conv.hpp
  - poly_basic.hpp
  isVerificationFile: false
  path: c_recursive.hpp
  requiredBy: []
  timestamp: '2024-12-03 20:03:27+08:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/formal_power_series/consecutive_terms_of_linear_recurrent_sequence.0.test.cpp
  - test/formal_power_series/kth_term_of_linearly_recurrent_sequence.0.test.cpp
  - test/formal_power_series/shift_of_sampling_points_of_polynomial.0.test.cpp
documentation_of: c_recursive.hpp
layout: document
title: C-recursive Sequence
---

## C-recursive Sequence

The sequence $\left(a _ n\right) _ {n\geq 0}$ is said to be C-recursive if it has form

$$
a _ n=\sum _ {j=1}^d c _ j a _ {n-j}, \qquad (n \geq d)
$$

here C-recursive means linear with **constant** coefficients. $d$ is said to be the **order** of the recurrent relation. We are given $c _ 1, \dots , c _ d$ and **initial terms** $a _ 0, \dots, a _ {d-1}$ in $\mathbb{C}$, the following algorithm could help us computing $a _ k$ for $k\gg d$.

We define $\Gamma(x):=x^d-\sum _ {j=0}^{d-1}c _ {d-j}x^j$ to be the **characteristic polynomial** of $\left(a _ n\right) _ {n\geq 0}$.

### Companion matrix

The companion matrix of monic polynomial $\Gamma (x)$ is

$$
C_\Gamma:=
\begin{bmatrix}
&&&c _ d \\
1&&&c _ {d-1} \\
&\ddots &&\vdots \\
&&1&c _ 1
\end{bmatrix}
$$

We define $b(x):=\sum _ {j=0}^{d-1}b _ jx^j$ and

$$
B _ b:=\begin{bmatrix}b _ 0 & b _ 1 & \cdots & b _ {d-1}\end{bmatrix}^{\intercal}
$$

One could simply check that

$$
\underbrace{\begin{bmatrix}
&&&c _ d \\
1&&&c _ {d-1} \\
&\ddots &&\vdots \\
&&1&c _ 1
\end{bmatrix}} _ {C _ \Gamma}
\underbrace{\begin{bmatrix}
b _ 0 \\
b _ 1 \\
\vdots \\
b _ {d-1}
\end{bmatrix}} _ {B _ b}=
\underbrace{\begin{bmatrix}
c _ d b _ {d-1} \\
b _ 0 + c _ {d-1} b _ {d-1} \\
\vdots \\
b _ {d-2} + c _ 1 b _ {d-1}
\end{bmatrix}} _ {B _ {xb\bmod{\Gamma}}}
$$

and

$$
\begin{aligned}
C _ \Gamma &= \begin{bmatrix}B _ {x\bmod{\Gamma}} & B _ {x^2\bmod{\Gamma}} & \cdots & B _ {x^d\bmod{\Gamma}}\end{bmatrix}, \\
\left(C _ \Gamma\right)^2 &= \begin{bmatrix}B _ {x^2\bmod{\Gamma}} & B _ {x^3\bmod{\Gamma}} & \cdots & B _ {x^{d+1}\bmod{\Gamma}}\end{bmatrix}, \\
\vdots \\
\left(C _ \Gamma\right)^k&=\begin{bmatrix}B _ {x^k\bmod{\Gamma}} & B _ {x^{k+1}\bmod{\Gamma}} & \cdots & B _ {x^{k+d}\bmod{\Gamma}}\end{bmatrix}
\end{aligned}
$$

### Reduce the order

Since the order $d$ maybe large, we can use matrix to reduce the order by

$$
\begin{bmatrix}
a _ {k} \\
a _ {k+1} \\
\vdots \\
a _ {k+d-1}
\end{bmatrix}=\underbrace{\begin{bmatrix}
&1&& \\
&&\ddots & \\
&&&1 \\
c _ d&c _ {d-1}&\cdots &c _ 1
\end{bmatrix}^k} _ {\left(\left(C _ \Gamma\right)^{\intercal}\right)^k=\left(\left(C _ \Gamma\right)^{k}\right)^{\intercal}}
\begin{bmatrix}
a _ 0 \\
a _ {1} \\
\vdots \\
a _ {d-1}
\end{bmatrix}
$$

Using the [exponentiation by squaring](https://en.wikipedia.org/wiki/Exponentiation_by_squaring) trick, we could simply have an algorithm with time $O\left(\mathsf{MM}(d)\log k\right)$.

### Fiduccia's algorithm

Fiduccia showed that

$$
a _ k=\left\langle x^k\bmod{\Gamma(x)},\left\lbrack a _ 0,\dots,a _ {d-1}\right\rbrack\right\rangle
$$

so we could reduce the matrix exponentiation to modular exponentiation in $\mathbb{C}\left\lbrack x\right\rbrack /\left(\Gamma\right)$, which is apparent.

### Bostan–Mori's algorithm

Bostan and Mori have introduced a new algorithm to compute $x^k\bmod{Q(x)}$ faster. It is called the LSB-first algorithm in their paper, but I would like to show this in a slightly different way which is still equivalent to the original Bostan–Mori's algorithm.

#### Graeffe iteration

Before introducing Bostan–Mori's algorithm, let's introduce the Graeffe iteration first, which could be used to compute truncated (multiplicative) inverse of a formal power series.

Given $Q(x)\in\mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack$ and $Q(0)\neq 0$. We want to compute $Q(x)^{-1}\bmod{x^{2n}}$, Graeffe iteration is that

$$
\begin{aligned}
\frac{1}{Q(x)}\bmod{x^{2n}}&=\left(\frac{1}{Q(x)Q(-x)}\bmod{x^{2n}}\right)\cdot Q(-x)\bmod{x^{2n}} \\
&=\left.\left(\frac{1}{V(z)}\bmod{z^{n}}\right)\right| _ {z=x^2}\cdot Q(-x)\bmod{x^{2n}}
\end{aligned}
$$

where $Q(x)Q(-x)$ is an even function written $V\left(x^2\right)$.

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{FPSInv}}\text{:} \\
&\textbf{Input}\text{: }A(x)\bmod{x^n},n\gt 0,A(0)\neq 0\text{.} \\
&\textbf{Output}\text{: }A(x)^{-1}\bmod{x^n}\text{.} \\
1&\textbf{if }n=1\textbf{ then return }A(0)^{-1}\\
2&B\left(x^2\right)\gets A(x)A(-x)\bmod{x^n} \\
3&C(x)\gets\operatorname{\mathsf{FPSInv}}\left(B(x),\left\lceil n/2\right\rceil\right) \\
4&\textbf{return }C\left(x^2\right)A(-x)\bmod{x^n}
\end{array}
$$

If we are using FFT, we can do better.

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{FPSInv}}\text{:} \\
&\textbf{Input}\text{: }A(x)\bmod{x^n},n\gt 0,A(0)\neq 0\text{.} \\
&\textbf{Output}\text{: }A(x)^{-1}\bmod{x^n}\text{.} \\
1&\textbf{if }n=1\textbf{ then return }A(0)^{-1}\\
2&\ell \gets 2^{\left\lceil\log _ 2 \left(2n-1\right)\right\rceil} \\
3&\left\lbrack b _ 0,\dots,b _ {\ell - 1}\right\rbrack \gets \operatorname{\mathsf{FFT}} _ {\ell}\left(A(x)\right) \\
4&V(x) \gets \operatorname{\mathsf{IFFT}} _ {\ell /2}\left(\left\lbrack b _ 0 b _ 1,b _ 2 b _ 3,\dots,b _ {\ell -2} b _ {\ell - 1}\right\rbrack\right) \bmod{x^{\left\lceil n/2\right\rceil}} \\
5&T(x) \gets \operatorname{\mathsf{FPSInv}}\left(V(x) \bmod{x^{\left\lfloor n/2\right\rfloor}},\left\lfloor n/2\right\rfloor\right) \\
6&\textbf{if }n \bmod{2} = 1 \textbf{ then} \\
7&\qquad T(x) \gets T(x)-\left(\left\lbrack x^{\left\lfloor n/2\right\rfloor}\right\rbrack V(x)T(x)\right)V(0)^{-1}x^{\left\lfloor n/2\right\rfloor} \\
8&\textbf{end if} \\
9&\left\lbrack c _ 0,\dots,c  _{\ell/2 - 1}\right\rbrack \gets \operatorname{\mathsf{FFT}}  _{\ell/2}\left(T(x)\right) \\
10&U(x) \gets \operatorname{\mathsf{IFFT}} _ {\ell}\left(\left\lbrack b _ 0 c _ 0, b _ 1 c _ 0, \dots, b _ {\ell - 1} c _ {\ell/2 - 1}\right\rbrack\right) \bmod{x^n} \\
11&\textbf{return }U(x)
\end{array}
$$

which runs in time $12\mathsf{E}(n)+O(n)$.

#### Formal Laurent series

If finitely many terms of form $x^{\lt 0}$ are allowed, we define the formal Laurent series ring:

$$
\mathbb{C}\left(\left(x\right)\right) := \left\lbrace \sum _ {j\geq N}a _ j x^j : N\in\mathbb{Z},a _ j \in\mathbb{C}\right\rbrace
$$

and actually $\mathbb{C}\left(\left(x\right)\right)$ is a field since $\mathbb{C}$ is a field. To compute the truncated inverse of a given formal Laurent series, we could use the algorithm which we used in the formal power series cases.

#### Reversed Laurent series

I will not give the definition of reversed Laurent series, since it is quite nature if one replace $x$ with $x^{-1}$ for the formal Laurent series. We will use the notation $\mathbb{C}\left(\left(x^{-1}\right)\right)$.

Since we want to compute $x^k\bmod{Q(x)}$, we could find that

$$
\begin{aligned}
\frac{1}{Q(x)}&=\cdots +a _ {0}x^{-\deg Q} \in \mathbb{C}\left(\left(x^{-1}\right)\right) \\
\frac{x^k}{Q(x)}&=\cdots +a _ kx^{-\deg Q}+\cdots +a _ 0x^{k-\deg Q} \in \mathbb{C}\left(\left(x^{-1}\right)\right) \\
\left\lbrack x^{\left(-\infty,0\right)}\right\rbrack \frac{x^k}{Q(x)}&=\left\lbrack x^{\left(-\infty,0\right)}\right\rbrack \frac{x^k\bmod{Q(x)}}{Q(x)}
\end{aligned}
$$

If we know $\left\lbrack x^{\left\lbrack -\deg Q,0\right)}\right\rbrack\frac{x^k}{Q(x)}$, then we could compute $x^k\bmod{Q(x)}$ by a simple convolution, Bostan–Mori's algorithm showed that

$$
\frac{x^k}{Q(x)}=\frac{x^k}{Q(x)Q(-x)}\cdot Q(-x)
$$

whether $k=2n$ or $k=2n+1$, we only need to compute

$$
\left\lbrack x^{\left\lbrack -2\deg Q,0\right)}\right\rbrack \frac{x^{2n}}{Q(x)Q(-x)}
$$

since $\left\lbrack x^{-2\deg Q-1}\right\rbrack \frac{x^{2n}}{Q(x)Q(-x)}=0$, if we set $V\left(x^2\right)=Q(x)Q(-x)$, then our goal is to compute

$$
\left\lbrack x^{\left\lbrack -\deg Q,0\right)}\right\rbrack \frac{x^{n}}{V(x)}
$$

The algorithm halts when $k=0$.

$$
\begin{array}{ll}
&\textbf{Algorithm }\operatorname{\mathsf{RLSBostanMori}}\text{:} \\
&\textbf{Input}\text{: }Q(x),k\in\mathbb{N}\text{.} \\
&\textbf{Output}\text{: }\left\lbrack x^{\left\lbrack -\deg Q,0\right)}\right\rbrack \dfrac{x^k}{Q(x)},\text{where }Q(x)^{-1}\in\mathbb{C}\left(\left( x^{-1}\right)\right)\text{.} \\
1&\textbf{if }k=0 \textbf{ then return }\left\lbrack \left(\left\lbrack x^{\deg Q}\right\rbrack Q(x)\right)^{-1},0,\dots,0\right\rbrack \\
2&V\left(x^2\right)\gets Q(x)Q(-x) \\
3&\left\lbrack c _ {-\deg Q},\dots,c _ {-1}\right\rbrack \gets \operatorname{\mathsf{RLSBostanMori}}\left(V(x),\left\lfloor k/2\right\rfloor\right) \\
4&T(x)\gets \sum _ {j=0}^{-1+\deg Q}c _ {j-\deg Q}x^j \\
5&\sum _ {j=0}^{-1+3\deg Q} u _ jx^j\gets T\left(x^2\right)x^{k\bmod{2}}Q(-x) \\
6&\textbf{return }\left\lbrack u _ {\deg Q},\dots,u _ {-1+2\deg Q}\right\rbrack
\end{array}
$$

If we want make the algorithm faster, make the input and output in FFT.

#### Connection between $\mathbb{C}\left(\left(x\right)\right)$ and $\mathbb{C}\left(\left(x^{-1}\right)\right)$

Let $Q\in\mathbb{C}\left\lbrack x\right\rbrack$, we have

$$
\begin{aligned}
\left\lbrack x^{\left\lbrack L,L+\deg Q\right)}\right\rbrack \frac{1}{Q(x)}&=\left\lbrack x^{\left\lbrack 0,\deg Q\right)}\right\rbrack \frac{x^{-L}}{Q(x)} \in\mathbb{C}\left(\left(x\right)\right) \\
&=\left\lbrack x^{\left\lbrack -\deg Q+1,1\right)}\right\rbrack \frac{x^L}{Q\left(x^{-1}\right)} \in\mathbb{C}\left(\left(x^{-1}\right)\right) \\
&=\left\lbrack x^{\left\lbrack -\deg Q,0\right)}\right\rbrack \frac{x^{-1+\deg Q}x^L}{x^{\deg Q}Q\left(x^{-1}\right)} \in\mathbb{C}\left(\left(x^{-1}\right)\right)
\end{aligned}
$$

If we want to compute $\left\lbrack x^{\lbrack L,R)}\right\rbrack \frac{P(x)}{Q(x)}\in \mathbb{C}\left(\left(x\right)\right)$ where $P,Q\in\mathbb{C}\left\lbrack x\right\rbrack$, we have

$$
\begin{aligned}
\frac{P\left(x^{-1}\right)}{Q\left(x^{-1}\right)}&=\sum _ {j\geq 0}a _ j x^{-j}\in\mathbb{C}\left(\left(x^{-1}\right)\right) \\
\frac{x^{n-1}P\left(x^{-1}\right)}{x^nQ\left(x^{-1}\right)}&=\sum _ {j\geq 0}a _ j x^{-j-1}\in\mathbb{C}\left(\left(x^{-1}\right)\right)
\end{aligned}
$$

Let $\tilde{P}(x):=x^{n-1}P\left(x^{-1}\right),\tilde{Q}(x):=x^nQ\left(x^{-1}\right)$ for sufficient large $n$ such that $\tilde{P},\tilde{Q}\in\mathbb{C}\left\lbrack x\right\rbrack$, we have

$$
\begin{aligned}
\left\lbrack x^{\left\lbrack -R,-L\right)}\right\rbrack \frac{\tilde{P}(x)}{\tilde{Q}(x)}&=\left\lbrack x^{\left\lbrack -R+L,0\right)}\right\rbrack \frac{x^L\cdot \tilde{P}(x)}{\tilde{Q}(x)} \\
&=\left\lbrack x^{\left\lbrack -R+L,0\right)}\right\rbrack \frac{\left(x^L\cdot \tilde{P}(x)\right)\bmod{\tilde{Q}(x)}}{\tilde{Q}(x)}
\end{aligned}
$$

## References

1. Alin Bostan, Ryuhei Mori. A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence. SOSA 2021: 118-132 url: <https://arxiv.org/abs/2008.08822>

2. Arne Storjohann. Algorithms for Matrix Canonical Forms. ETH Zürich. Diss., Technische Wissenschaften ETH Zürich, Nr. 13922, 2001. url: <https://www.research-collection.ethz.ch/handle/20.500.11850/145127>
