---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: binomial.hpp
    title: binomial.hpp
  - icon: ':question:'
    path: fft.hpp
    title: FFT
  - icon: ':question:'
    path: fps_basic.hpp
    title: fps_basic.hpp
  - icon: ':heavy_check_mark:'
    path: fps_composition.hpp
    title: fps_composition.hpp
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':question:'
    path: semi_relaxed_conv.hpp
    title: semi_relaxed_conv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/composition_of_formal_power_series_large
    links:
    - https://judge.yosupo.jp/problem/composition_of_formal_power_series_large
  bundledCode: "#line 1 \"test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/composition_of_formal_power_series_large\"\
    \n\n#line 2 \"fps_composition.hpp\"\n\n#line 2 \"binomial.hpp\"\n\n#include <algorithm>\n\
    #include <vector>\n\ntemplate <typename Tp>\nclass Binomial {\n    std::vector<Tp>\
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
    \ invfactorial_[n]; }\n};\n#line 2 \"fft.hpp\"\n\n#line 4 \"fft.hpp\"\n#include\
    \ <cassert>\n#include <iterator>\n#include <memory>\n#line 8 \"fft.hpp\"\n\ntemplate\
    \ <typename Tp>\nclass FftInfo {\n    static Tp least_quadratic_nonresidue() {\n\
    \        for (int i = 2;; ++i)\n            if (Tp(i).pow((Tp::mod() - 1) / 2)\
    \ == -1) return Tp(i);\n    }\n\n    const int ordlog2_;\n    const Tp zeta_;\n\
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
    }\n#line 2 \"fps_basic.hpp\"\n\n#line 2 \"semi_relaxed_conv.hpp\"\n\n#line 5 \"\
    semi_relaxed_conv.hpp\"\n#include <type_traits>\n#include <utility>\n#line 8 \"\
    semi_relaxed_conv.hpp\"\n\ntemplate <typename Tp, typename Closure>\ninline std::enable_if_t<std::is_invocable_r_v<Tp,\
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
    \ o * e, Tp(0));\n    return a;\n}\n#line 10 \"fps_composition.hpp\"\n\n// returns\
    \ f(g) mod x^n\n// see: https://arxiv.org/abs/2404.05177\n// Yasunori Kinoshita,\
    \ Baitian Li. Power Series Composition in Near-Linear Time.\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> composition(const std::vector<Tp> &f, const std::vector<Tp>\
    \ &g, int n) {\n    if (n <= 0) return {};\n    if (g.empty()) {\n        std::vector<Tp>\
    \ res(n);\n        if (!f.empty()) res[0] = f[0];\n        return res;\n    }\n\
    \n    // [y^(-1)] (f(y) / (-g(x) + y)) mod x^n\n    // R[x]((y^(-1)))\n    auto\
    \ rec = [g0 = g[0]](auto &&rec, const std::vector<Tp> &P, const std::vector<Tp>\
    \ &Q, int d,\n                           int n) {\n        if (n == 1) {\n   \
    \         std::vector<Tp> invQ(d + 1);\n            auto &&bin = Binomial<Tp>::get(d\
    \ * 2);\n            Tp gg      = 1;\n            for (int i = 0; i <= d; ++i)\
    \ invQ[d - i] = bin.binom(d + i - 1, d - 1) * gg, gg *= g0;\n            // invQ[i]\
    \ = [y^(-2d + i)]Q^(-1)\n            // P[0,d-1] * invQ[-2d,-d] => [0,d-1] * [0,d]\n\
    \            // take [-d,-1] => take [d,2d-1]\n            auto PinvQ = convolution(P,\
    \ invQ);\n            PinvQ.erase(PinvQ.begin(), PinvQ.begin() + d);\n       \
    \     PinvQ.resize(d);\n            return PinvQ;\n        }\n\n        std::vector<Tp>\
    \ dftQ(d * n * 4);\n        for (int i = 0; i < d; ++i)\n            for (int\
    \ j = 0; j < n; ++j) dftQ[i * (n * 2) + j] = Q[i * n + j];\n        dftQ[d * n\
    \ * 2] = 1;\n        fft(dftQ);\n        std::vector<Tp> V(d * n * 2);\n     \
    \   for (int i = 0; i < d * n * 4; i += 2) V[i / 2] = dftQ[i] * dftQ[i + 1];\n\
    \        inv_fft(V);\n        V[0] -= 1;\n\n        for (int i = 1; i < d * 2;\
    \ ++i)\n            for (int j = 0; j < n / 2; ++j) V[i * (n / 2) + j] = V[i *\
    \ n + j];\n        V.resize(d * n);\n\n        const auto T = rec(rec, P, std::move(V),\
    \ d * 2, n / 2);\n\n        std::vector<Tp> dftT(d * n * 2);\n        for (int\
    \ i = 0; i < d * 2; ++i)\n            for (int j = 0; j < n / 2; ++j) dftT[i *\
    \ n + j] = T[i * (n / 2) + j];\n        fft(dftT);\n\n        std::vector<Tp>\
    \ U(d * n * 4);\n        for (int i = 0; i < d * n * 4; i += 2) {\n          \
    \  U[i]     = dftT[i / 2] * dftQ[i + 1];\n            U[i + 1] = dftT[i / 2] *\
    \ dftQ[i];\n        }\n        inv_fft(U);\n\n        // [-2d,d-1] => [0,3d-1]\n\
    \        // take [-d,-1] => take [d,2d-1]\n        for (int i = 0; i < d; ++i)\n\
    \            for (int j = 0; j < n; ++j) U[i * n + j] = U[(i + d) * (n * 2) +\
    \ j];\n        U.resize(d * n);\n        return U;\n    };\n\n    int k = 1;\n\
    \    while (k < std::max<int>(n, f.size())) k *= 2;\n    std::vector<Tp> Q(k);\n\
    \    for (int i = 0; i < std::min<int>(k, g.size()); ++i) Q[i] = -g[i];\n\n  \
    \  auto res = rec(rec, f, Q, 1, k);\n    res.resize(n);\n    return res;\n}\n\n\
    // returns [x^k]gf^0, [x^k]gf, ..., [x^k]gf^(n-1)\n// see: https://noshi91.hatenablog.com/entry/2024/03/16/224034\n\
    // noshi91. FPS \u306E\u5408\u6210\u3068\u9006\u95A2\u6570\u3001\u51AA\u4E57\u306E\
    \u4FC2\u6570\u5217\u6319 \u0398(n (log(n))^2)\ntemplate <typename Tp>\ninline\
    \ std::vector<Tp> enum_kth_term_of_power(const std::vector<Tp> &f, const std::vector<Tp>\
    \ &g,\n                                              int k, int n) {\n    if (k\
    \ < 0 || n <= 0) return {};\n    if (f.empty()) {\n        std::vector<Tp> res(n);\n\
    \        if (k < (int)g.size()) res[0] = g[k];\n        return res;\n    }\n\n\
    \    // [x^k] (g(x) / (-f(x) + y))\n    // R[x]((y^(-1)))\n    std::vector<Tp>\
    \ P(g), Q(k + 1);\n    P.resize(k + 1);\n    for (int i = 0; i < std::min<int>(k\
    \ + 1, f.size()); ++i) Q[i] = -f[i];\n\n    int d = 1;\n    for (; k; d *= 2,\
    \ k /= 2) {\n        const int len = fft_len((d * 2) * ((k + 1) * 2) - 1);\n \
    \       std::vector<Tp> dftP(len), dftQ(len);\n        for (int i = 0; i < d;\
    \ ++i)\n            for (int j = 0; j <= k; ++j) {\n                dftP[i * ((k\
    \ + 1) * 2) + j] = P[i * (k + 1) + j];\n                dftQ[i * ((k + 1) * 2)\
    \ + j] = Q[i * (k + 1) + j];\n            }\n        dftQ[d * (k + 1) * 2] = 1;\n\
    \        fft(dftP);\n        fft(dftQ);\n\n        P.resize(len / 2);\n      \
    \  Q.resize(len / 2);\n        if (k & 1) {\n            auto &&root = FftInfo<Tp>::get().inv_root(len\
    \ / 2);\n            for (int i = 0; i < len; i += 2) {\n                P[i /\
    \ 2] = (dftP[i] * dftQ[i + 1] - dftP[i + 1] * dftQ[i]).div_by_2() * root[i / 2];\n\
    \                Q[i / 2] = dftQ[i] * dftQ[i + 1];\n            }\n        } else\
    \ {\n            for (int i = 0; i < len; i += 2) {\n                P[i / 2]\
    \ = (dftP[i] * dftQ[i + 1] + dftP[i + 1] * dftQ[i]).div_by_2();\n            \
    \    Q[i / 2] = dftQ[i] * dftQ[i + 1];\n            }\n        }\n        inv_fft(P);\n\
    \        inv_fft(Q);\n        if (d * (k + 1) * 4 >= len) Q[(d * (k + 1) * 4)\
    \ % len] -= 1;\n\n        for (int i = 1; i < d * 2; ++i)\n            for (int\
    \ j = 0; j <= k / 2; ++j) {\n                P[i * (k / 2 + 1) + j] = P[i * (k\
    \ + 1) + j];\n                Q[i * (k / 2 + 1) + j] = Q[i * (k + 1) + j];\n \
    \           }\n        P.resize(d * 2 * (k / 2 + 1));\n        Q.resize(d * 2\
    \ * (k / 2 + 1));\n    }\n\n    std::vector<Tp> invQ(n + 1);\n    auto &&bin =\
    \ Binomial<Tp>::get(d + n);\n    Tp ff      = 1;\n    for (int i = 0; i <= n;\
    \ ++i) invQ[n - i] = bin.binom(d + i - 1, d - 1) * ff, ff *= f[0];\n    // invQ[i]\
    \ = [y^(-2d + i)]Q^(-1)\n    // P[0,d-1] * invQ[-(d+n),-d] => [0,d-1] * [0,n]\n\
    \    auto PinvQ = convolution(P, invQ);\n    // take [-n,-1] => take [d,d+n-1]\n\
    \    PinvQ.erase(PinvQ.begin(), PinvQ.begin() + d);\n    PinvQ.resize(n);\n  \
    \  // output => [-1,-n] reverse\n    // before I just reverse it and mistaken\
    \ something.\n    std::reverse(PinvQ.begin(), PinvQ.end());\n    return PinvQ;\n\
    }\n\n// returns g s.t. f(g) = g(f) = x mod x^n\ntemplate <typename Tp>\ninline\
    \ std::vector<Tp> reversion(std::vector<Tp> f, int n) {\n    if (n <= 0 || f.size()\
    \ < 2) return {};\n    assert(order(f) == 1);\n    const auto if1 = f[1].inv();\n\
    \    if (n == 1) return {Tp(0)};\n    f.resize(n);\n    Tp ff = 1;\n    for (int\
    \ i = 1; i < n; ++i) f[i] *= ff *= if1;\n    auto a     = enum_kth_term_of_power(f,\
    \ {Tp(1)}, n - 1, n);\n    auto &&bin = Binomial<Tp>::get(n);\n    for (int i\
    \ = 1; i < n; ++i) a[i] *= (n - 1) * bin.inv(i);\n    auto b = fps_pow(std::vector(a.rbegin(),\
    \ a.rend() - 1), Tp(1 - n).inv().val(), n - 1);\n    for (int i = 0; i < n - 1;\
    \ ++i) b[i] *= if1;\n    b.insert(b.begin(), Tp(0));\n    return b;\n}\n#line\
    \ 2 \"modint.hpp\"\n\n#include <iostream>\n#line 5 \"modint.hpp\"\n\ntemplate\
    \ <unsigned Mod>\nclass ModInt {\n    static_assert((Mod >> 31) == 0, \"`Mod`\
    \ must less than 2^(31)\");\n    template <typename Int>\n    static std::enable_if_t<std::is_integral_v<Int>,\
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
    #line 7 \"test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = ModInt<998244353>;\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ f(n), g(n);\n    for (int i = 0; i < n; ++i) std::cin >> f[i];\n    for (int\
    \ i = 0; i < n; ++i) std::cin >> g[i];\n    const auto fg = composition(f, g,\
    \ n);\n    for (int i = 0; i < n; ++i) std::cout << fg[i] << ' ';\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/composition_of_formal_power_series_large\"\
    \n\n#include \"fps_composition.hpp\"\n#include \"modint.hpp\"\n#include <iostream>\n\
    #include <vector>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n   \
    \ std::cin.tie(nullptr);\n    using mint = ModInt<998244353>;\n    int n;\n  \
    \  std::cin >> n;\n    std::vector<mint> f(n), g(n);\n    for (int i = 0; i <\
    \ n; ++i) std::cin >> f[i];\n    for (int i = 0; i < n; ++i) std::cin >> g[i];\n\
    \    const auto fg = composition(f, g, n);\n    for (int i = 0; i < n; ++i) std::cout\
    \ << fg[i] << ' ';\n    return 0;\n}\n"
  dependsOn:
  - fps_composition.hpp
  - binomial.hpp
  - fft.hpp
  - fps_basic.hpp
  - semi_relaxed_conv.hpp
  - modint.hpp
  isVerificationFile: true
  path: test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
  requiredBy: []
  timestamp: '2024-12-04 20:47:37+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
layout: document
redirect_from:
- /verify/test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
- /verify/test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp.html
title: test/formal_power_series/composition_of_formal_power_series_large.0.test.cpp
---
