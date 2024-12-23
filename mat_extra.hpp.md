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
  - icon: ':x:'
    path: mat_basic.hpp
    title: mat_basic.hpp
  - icon: ':question:'
    path: poly.hpp
    title: poly.hpp
  - icon: ':question:'
    path: poly_basic.hpp
    title: poly_basic.hpp
  - icon: ':question:'
    path: random.hpp
    title: random.hpp
  - icon: ':question:'
    path: rng.hpp
    title: rng.hpp
  - icon: ':question:'
    path: semi_relaxed_conv.hpp
    title: semi_relaxed_conv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://codeforces.com/blog/entry/92248?#comment-818786
    - https://qoj.ac/contest/1536/problem/59
  bundledCode: "#line 2 \"mat_extra.hpp\"\n\n#line 2 \"mat_basic.hpp\"\n\n#line 2\
    \ \"poly.hpp\"\n\n#line 2 \"poly_basic.hpp\"\n\n#line 2 \"binomial.hpp\"\n\n#include\
    \ <algorithm>\n#include <vector>\n\ntemplate <typename Tp>\nclass Binomial {\n\
    \    std::vector<Tp> factorial_, invfactorial_;\n\n    Binomial() : factorial_{Tp(1)},\
    \ invfactorial_{Tp(1)} {}\n\n    void preprocess(int n) {\n        if (const int\
    \ nn = factorial_.size(); nn < n) {\n            int k = nn;\n            while\
    \ (k < n) k *= 2;\n            k = std::min<long long>(k, Tp::mod());\n      \
    \      factorial_.resize(k);\n            invfactorial_.resize(k);\n         \
    \   for (int i = nn; i < k; ++i) factorial_[i] = factorial_[i - 1] * i;\n    \
    \        invfactorial_.back() = factorial_.back().inv();\n            for (int\
    \ i = k - 2; i >= nn; --i) invfactorial_[i] = invfactorial_[i + 1] * (i + 1);\n\
    \        }\n    }\n\npublic:\n    static const Binomial &get(int n) {\n      \
    \  static Binomial bin;\n        bin.preprocess(n);\n        return bin;\n   \
    \ }\n\n    Tp binom(int n, int m) const {\n        return n < m ? Tp() : factorial_[n]\
    \ * invfactorial_[m] * invfactorial_[n - m];\n    }\n    Tp inv(int n) const {\
    \ return factorial_[n - 1] * invfactorial_[n]; }\n    Tp factorial(int n) const\
    \ { return factorial_[n]; }\n    Tp inv_factorial(int n) const { return invfactorial_[n];\
    \ }\n};\n#line 2 \"fft.hpp\"\n\n#line 4 \"fft.hpp\"\n#include <cassert>\n#include\
    \ <iterator>\n#include <memory>\n#line 8 \"fft.hpp\"\n\ntemplate <typename Tp>\n\
    class FftInfo {\n    static Tp least_quadratic_nonresidue() {\n        for (int\
    \ i = 2;; ++i)\n            if (Tp(i).pow((Tp::mod() - 1) / 2) == -1) return Tp(i);\n\
    \    }\n\n    const int ordlog2_;\n    const Tp zeta_;\n    const Tp invzeta_;\n\
    \    const Tp imag_;\n    const Tp invimag_;\n\n    mutable std::vector<Tp> root_;\n\
    \    mutable std::vector<Tp> invroot_;\n\n    FftInfo()\n        : ordlog2_(__builtin_ctzll(Tp::mod()\
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
    \ += A[0] * B[i];\n    }\n\n    return B;\n}\n#line 8 \"fps_basic.hpp\"\n\ntemplate\
    \ <typename Tp>\ninline int order(const std::vector<Tp> &a) {\n    for (int i\
    \ = 0; i < (int)a.size(); ++i)\n        if (a[i] != 0) return i;\n    return -1;\n\
    }\n\ntemplate <typename Tp>\ninline std::vector<Tp> fps_inv(const std::vector<Tp>\
    \ &a, int n) {\n    assert(order(a) == 0);\n    if (n <= 0) return {};\n    if\
    \ (std::min<int>(a.size(), n) < 60)\n        return semi_relaxed_convolution(\n\
    \            a, [v = a[0].inv()](int n, auto &&c) { return n == 0 ? v : -c[n]\
    \ * v; }, n);\n    enum { Threshold = 32 };\n    const int len = fft_len(n);\n\
    \    std::vector<Tp> invA, shopA(len), shopB(len);\n    invA = semi_relaxed_convolution(\n\
    \        a, [v = a[0].inv()](int n, auto &&c) { return n == 0 ? v : -c[n] * v;\
    \ }, Threshold);\n    invA.resize(len);\n    for (int i = Threshold * 2; i <=\
    \ len; i *= 2) {\n        std::fill(std::copy_n(a.begin(), std::min<int>(a.size(),\
    \ i), shopA.begin()),\n                  shopA.begin() + i, Tp(0));\n        std::copy_n(invA.begin(),\
    \ i, shopB.begin());\n        fft_n(shopA.begin(), i);\n        fft_n(shopB.begin(),\
    \ i);\n        for (int j = 0; j < i; ++j) shopA[j] *= shopB[j];\n        inv_fft_n(shopA.begin(),\
    \ i);\n        std::fill_n(shopA.begin(), i / 2, Tp(0));\n        fft_n(shopA.begin(),\
    \ i);\n        for (int j = 0; j < i; ++j) shopA[j] *= shopB[j];\n        inv_fft_n(shopA.begin(),\
    \ i);\n        for (int j = i / 2; j < i; ++j) invA[j] = -shopA[j];\n    }\n \
    \   invA.resize(n);\n    return invA;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ fps_div(const std::vector<Tp> &a, const std::vector<Tp> &b, int n) {\n    assert(order(b)\
    \ == 0);\n    if (n <= 0) return {};\n    return semi_relaxed_convolution(\n \
    \       b,\n        [&, v = b[0].inv()](int n, auto &&c) {\n            if (n\
    \ < (int)a.size()) return (a[n] - c[n]) * v;\n            return -c[n] * v;\n\
    \        },\n        n);\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ deriv(const std::vector<Tp> &a) {\n    const int n = (int)a.size() - 1;\n  \
    \  if (n <= 0) return {};\n    std::vector<Tp> res(n);\n    for (int i = 1; i\
    \ <= n; ++i) res[i - 1] = a[i] * i;\n    return res;\n}\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> integr(const std::vector<Tp> &a, Tp c = {}) {\n\
    \    const int n = a.size() + 1;\n    auto &&bin  = Binomial<Tp>::get(n);\n  \
    \  std::vector<Tp> res(n);\n    res[0] = c;\n    for (int i = 1; i < n; ++i) res[i]\
    \ = a[i - 1] * bin.inv(i);\n    return res;\n}\n\ntemplate <typename Tp>\ninline\
    \ std::vector<Tp> fps_log(const std::vector<Tp> &a, int n) {\n    return integr(fps_div(deriv(a),\
    \ a, n - 1));\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> fps_exp(const\
    \ std::vector<Tp> &a, int n) {\n    if (n <= 0) return {};\n    assert(a.empty()\
    \ || a[0] == 0);\n    return semi_relaxed_convolution(\n        deriv(a),\n  \
    \      [bin = Binomial<Tp>::get(n)](int n, auto &&c) {\n            return n ==\
    \ 0 ? Tp(1) : c[n - 1] * bin.inv(n);\n        },\n        n);\n}\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> fps_pow(std::vector<Tp> a, long long e, int n) {\n\
    \    if (n <= 0) return {};\n    if (e == 0) {\n        std::vector<Tp> res(n);\n\
    \        res[0] = 1;\n        return res;\n    }\n\n    const int o = order(a);\n\
    \    if (o < 0 || o > n / e || (o == n / e && n % e == 0)) return std::vector<Tp>(n);\n\
    \    if (o != 0) a.erase(a.begin(), a.begin() + o);\n\n    const Tp ia0 = a[0].inv();\n\
    \    const Tp a0e = a[0].pow(e);\n    const Tp me  = e;\n\n    for (int i = 0;\
    \ i < (int)a.size(); ++i) a[i] *= ia0;\n    a = fps_log(a, n - o * e);\n    for\
    \ (int i = 0; i < (int)a.size(); ++i) a[i] *= me;\n    a = fps_exp(a, n - o *\
    \ e);\n    for (int i = 0; i < (int)a.size(); ++i) a[i] *= a0e;\n\n    a.insert(a.begin(),\
    \ o * e, Tp(0));\n    return a;\n}\n#line 7 \"poly_basic.hpp\"\n#include <array>\n\
    #line 10 \"poly_basic.hpp\"\n\ntemplate <typename Tp>\ninline int degree(const\
    \ std::vector<Tp> &a) {\n    int n = (int)a.size() - 1;\n    while (n >= 0 &&\
    \ a[n] == 0) --n;\n    return n;\n}\n\ntemplate <typename Tp>\ninline void shrink(std::vector<Tp>\
    \ &a) {\n    a.resize(degree(a) + 1);\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ taylor_shift(std::vector<Tp> a, Tp c) {\n    const int n = a.size();\n    auto\
    \ &&bin  = Binomial<Tp>::get(n);\n    for (int i = 0; i < n; ++i) a[i] *= bin.factorial(i);\n\
    \    Tp cc = 1;\n    std::vector<Tp> b(n);\n    for (int i = 0; i < n; ++i) {\n\
    \        b[i] = cc * bin.inv_factorial(i);\n        cc *= c;\n    }\n    std::reverse(a.begin(),\
    \ a.end());\n    auto ab = convolution(a, b);\n    ab.resize(n);\n    std::reverse(ab.begin(),\
    \ ab.end());\n    for (int i = 0; i < n; ++i) ab[i] *= bin.inv_factorial(i);\n\
    \    return ab;\n}\n\n// returns (quotient, remainder)\n// O(deg(Q)deg(B))\ntemplate\
    \ <typename Tp>\ninline std::array<std::vector<Tp>, 2> euclidean_div_naive(const\
    \ std::vector<Tp> &A,\n                                                      \
    \    const std::vector<Tp> &B) {\n    const int degA = degree(A);\n    const int\
    \ degB = degree(B);\n    assert(degB >= 0);\n    const int degQ = degA - degB;\n\
    \    if (degQ < 0) return {std::vector<Tp>{Tp(0)}, A};\n    std::vector<Tp> Q(degQ\
    \ + 1), R = A;\n    const auto inv = B[degB].inv();\n    for (int i = degQ, n\
    \ = degA; i >= 0; --i)\n        if ((Q[i] = R[n--] * inv) != 0)\n            for\
    \ (int j = 0; j <= degB; ++j) R[i + j] -= Q[i] * B[j];\n    R.resize(degB);\n\
    \    return {Q, R};\n}\n\n// O(min(deg(Q)^2,deg(Q)deg(B)))\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> euclidean_div_quotient_naive(const std::vector<Tp>\
    \ &A,\n                                                    const std::vector<Tp>\
    \ &B) {\n    const int degA = degree(A);\n    const int degB = degree(B);\n  \
    \  assert(degB >= 0);\n    const int degQ = degA - degB;\n    if (degQ < 0) return\
    \ {Tp(0)};\n    const auto inv = B[degB].inv();\n    std::vector<Tp> Q(degQ +\
    \ 1);\n    for (int i = 0; i <= degQ; ++i) {\n        for (int j = 1; j <= std::min(i,\
    \ degB); ++j) Q[degQ - i] += B[degB - j] * Q[degQ - i + j];\n        Q[degQ -\
    \ i] = (A[degA - i] - Q[degQ - i]) * inv;\n    }\n    return Q;\n}\n\n// returns\
    \ (quotient, remainder)\ntemplate <typename Tp>\ninline std::array<std::vector<Tp>,\
    \ 2> euclidean_div(const std::vector<Tp> &A,\n                               \
    \                     const std::vector<Tp> &B) {\n    const int degA = degree(A);\n\
    \    const int degB = degree(B);\n    assert(degB >= 0);\n    // A = Q*B + R =>\
    \ A/B = Q + R/B in R((x^(-1)))\n    const int degQ = degA - degB;\n    if (degQ\
    \ < 0) return {std::vector<Tp>{Tp(0)}, A};\n    if (degQ < 60 || degB < 60) return\
    \ euclidean_div_naive(A, B);\n\n    auto Q = fps_div(std::vector(A.rend() - (degA\
    \ + 1), A.rend()),\n                     std::vector(B.rend() - (degB + 1), B.rend()),\
    \ degQ + 1);\n    std::reverse(Q.begin(), Q.end());\n\n    // returns a mod (x^n-1)\n\
    \    auto make_cyclic = [](const std::vector<Tp> &a, int n) {\n        assert((n\
    \ & (n - 1)) == 0);\n        std::vector<Tp> b(n);\n        for (int i = 0; i\
    \ < (int)a.size(); ++i) b[i & (n - 1)] += a[i];\n        return b;\n    };\n\n\
    \    const int len      = fft_len(std::max(degB, 1));\n    const auto cyclicA\
    \ = make_cyclic(A, len);\n    auto cyclicB       = make_cyclic(B, len);\n    auto\
    \ cyclicQ       = make_cyclic(Q, len);\n\n    fft(cyclicQ);\n    fft(cyclicB);\n\
    \    for (int i = 0; i < len; ++i) cyclicQ[i] *= cyclicB[i];\n    inv_fft(cyclicQ);\n\
    \n    // R = A - QB mod (x^n-1) (n >= degB)\n    std::vector<Tp> R(degB);\n  \
    \  for (int i = 0; i < degB; ++i) R[i] = cyclicA[i] - cyclicQ[i];\n    return\
    \ {Q, R};\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> euclidean_div_quotient(const\
    \ std::vector<Tp> &A, const std::vector<Tp> &B) {\n    const int degA = degree(A);\n\
    \    const int degB = degree(B);\n    assert(degB >= 0);\n    // A = Q*B + R =>\
    \ A/B = Q + R/B in R((x^(-1)))\n    const int degQ = degA - degB;\n    if (degQ\
    \ < 0) return {Tp(0)};\n    if (std::min(degQ, degB) < 60) return euclidean_div_quotient_naive(A,\
    \ B);\n\n    auto Q = fps_div(std::vector(A.rend() - (degA + 1), A.rend()),\n\
    \                     std::vector(B.rend() - (degB + 1), B.rend()), degQ + 1);\n\
    \    std::reverse(Q.begin(), Q.end());\n    return Q;\n}\n#line 7 \"poly.hpp\"\
    \n#include <iostream>\n#line 9 \"poly.hpp\"\n\ntemplate <typename Tp>\nclass Poly\
    \ : public std::vector<Tp> {\n    using Base = std::vector<Tp>;\n\npublic:\n \
    \   using Base::Base;\n\n    static Poly zero() { return Poly(); }\n    static\
    \ Poly one() { return Poly{Tp::one()}; }\n\n    int deg() const { return degree(*this);\
    \ }\n    int ord() const { return order(*this); }\n\n    Poly rev() const {\n\
    \        const int d = deg();\n        Poly res(d + 1);\n        for (int i =\
    \ d; i >= 0; --i) res[i] = Base::operator[](d - i);\n        return res;\n   \
    \ }\n\n    Poly slice(int L, int R) const {\n        Poly res(R - L);\n      \
    \  for (int i = L; i < std::min<int>(R, Base::size()); ++i) res[i - L] = Base::operator[](i);\n\
    \        return res;\n    }\n\n    Poly trunc(int D) const {\n        Poly res(D);\n\
    \        for (int i = 0; i < std::min<int>(D, Base::size()); ++i) res[i] = Base::operator[](i);\n\
    \        return res;\n    }\n\n    Poly &shrink() {\n        Base::resize(deg()\
    \ + 1);\n        return *this;\n    }\n\n    Tp lc() const {\n        const int\
    \ d = deg();\n        return d == -1 ? Tp() : Base::operator[](d);\n    }\n\n\
    \    Poly monic() const {\n        const int d = deg();\n        assert(d >= 0);\n\
    \        const auto iv = Base::operator[](d).inv();\n        Poly res(*this);\n\
    \        for (int i = 0; i <= d; ++i) res[i] *= iv;\n        return res;\n   \
    \ }\n\n    Poly taylor_shift(Tp c) const {\n        Base::operator=(taylor_shift(*this,\
    \ c));\n        return shrink();\n    }\n\n    Poly operator-() const {\n    \
    \    const int d = deg();\n        Poly res(d + 1);\n        for (int i = 0; i\
    \ <= d; ++i) res[i] = -Base::operator[](i);\n        res.shrink();\n        return\
    \ res;\n    }\n\n    std::array<Poly, 2> divmod(const Poly &R) const {\n     \
    \   const auto [q, r] = euclidean_div(*this, R);\n        return {Poly(q.begin(),\
    \ q.end()), Poly(r.begin(), r.end())};\n    }\n    Poly &operator+=(const Poly\
    \ &R) {\n        if (Base::size() < R.size()) Base::resize(R.size());\n      \
    \  for (int i = 0; i < (int)R.size(); ++i) Base::operator[](i) += R[i];\n    \
    \    return shrink();\n    }\n    Poly &operator-=(const Poly &R) {\n        if\
    \ (Base::size() < R.size()) Base::resize(R.size());\n        for (int i = 0; i\
    \ < (int)R.size(); ++i) Base::operator[](i) -= R[i];\n        return shrink();\n\
    \    }\n    Poly &operator*=(const Poly &R) {\n        Base::operator=(convolution(*this,\
    \ R));\n        return shrink();\n    }\n    Poly &operator/=(const Poly &R) {\n\
    \        Base::operator=(euclidean_div_quotient(*this, R));\n        return shrink();\n\
    \    }\n    Poly &operator%=(const Poly &R) {\n        Base::operator=(std::get<1>(divmod(R)));\n\
    \        return shrink();\n    }\n    Poly &operator<<=(int D) {\n        if (D\
    \ > 0) {\n            Base::insert(Base::begin(), D, Tp(0));\n        } else if\
    \ (D < 0) {\n            if (-D < (int)Base::size()) {\n                Base::erase(Base::begin(),\
    \ Base::begin() + (-D));\n            } else {\n                Base::clear();\n\
    \            }\n        }\n        return shrink();\n    }\n    Poly &operator>>=(int\
    \ D) { return operator<<=(-D); }\n\n    friend Poly operator+(const Poly &L, const\
    \ Poly &R) { return Poly(L) += R; }\n    friend Poly operator-(const Poly &L,\
    \ const Poly &R) { return Poly(L) -= R; }\n    friend Poly operator*(const Poly\
    \ &L, const Poly &R) { return Poly(L) *= R; }\n    friend Poly operator/(const\
    \ Poly &L, const Poly &R) { return Poly(L) /= R; }\n    friend Poly operator%(const\
    \ Poly &L, const Poly &R) { return Poly(L) %= R; }\n    friend Poly operator<<(const\
    \ Poly &L, int D) { return Poly(L) <<= D; }\n    friend Poly operator>>(const\
    \ Poly &L, int D) { return Poly(L) >>= D; }\n\n    friend std::ostream &operator<<(std::ostream\
    \ &L, const Poly &R) {\n        L << '[';\n        const int d = R.deg();\n  \
    \      if (d < 0) {\n            L << '0';\n        } else {\n            for\
    \ (int i = 0; i <= d; ++i) {\n                L << R[i];\n                if (i\
    \ == 1) L << \"*x\";\n                if (i > 1) L << \"*x^\" << i;\n        \
    \        if (i != d) L << \" + \";\n            }\n        }\n        return L\
    \ << ']';\n    }\n};\n\n// 2x2 matrix for Euclidean algorithm\ntemplate <typename\
    \ Tp>\nclass GCDMatrix : public std::array<std::array<Tp, 2>, 2> {\npublic:\n\
    \    GCDMatrix(const Tp &x00, const Tp &x01, const Tp &x10, const Tp &x11)\n \
    \       : std::array<std::array<Tp, 2>, 2>{std::array{x00, x01}, std::array{x10,\
    \ x11}} {}\n\n    GCDMatrix operator*(const GCDMatrix &R) const {\n        return\
    \ {(*this)[0][0] * R[0][0] + (*this)[0][1] * R[1][0],\n                (*this)[0][0]\
    \ * R[0][1] + (*this)[0][1] * R[1][1],\n                (*this)[1][0] * R[0][0]\
    \ + (*this)[1][1] * R[1][0],\n                (*this)[1][0] * R[0][1] + (*this)[1][1]\
    \ * R[1][1]};\n    }\n\n    std::array<Tp, 2> operator*(const std::array<Tp, 2>\
    \ &R) const {\n        return {(*this)[0][0] * R[0] + (*this)[0][1] * R[1],\n\
    \                (*this)[1][0] * R[0] + (*this)[1][1] * R[1]};\n    }\n\n    Tp\
    \ det() const { return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0];\
    \ }\n    GCDMatrix adj() const { return {(*this)[1][1], -(*this)[0][1], -(*this)[1][0],\
    \ (*this)[0][0]}; }\n};\n\n// returns M s.t. deg(M) <= d and deg(M21*A+M22*B)\
    \ < max(deg(A),deg(B)) - d\n//                det(M) in {-1, 1}\n// see:\n// [1]:\
    \ Daniel J. Bernstein. Fast multiplication and its applications.\ntemplate <typename\
    \ Tp>\ninline GCDMatrix<Poly<Tp>> hgcd(const Poly<Tp> &A, const Poly<Tp> &B, int\
    \ d) {\n    using Mat = GCDMatrix<Poly<Tp>>;\n    assert(!(A.deg() < 0 && B.deg()\
    \ < 0));\n    if (A.deg() < B.deg()) return hgcd(B, A, d) * Mat({}, {Tp(1)}, {Tp(1)},\
    \ {});\n    if (A.deg() < d) return hgcd(A, B, A.deg());\n    if (B.deg() < A.deg()\
    \ - d) return Mat({Tp(1)}, {}, {}, {Tp(1)});\n    if (int dd = A.deg() - d * 2;\
    \ dd > 0) return hgcd(A >> dd, B >> dd, d);\n    if (d == 0) return Mat({}, {Tp(1)},\
    \ {Tp(1)}, -(A / B));\n    const auto M = hgcd(A, B, d / 2);\n    const auto D\
    \ = M[1][0] * A + M[1][1] * B;\n    if (D.deg() < A.deg() - d) return M;\n   \
    \ const auto C      = M[0][0] * A + M[0][1] * B;\n    const auto [Q, R] = C.divmod(D);\n\
    \    return hgcd(D, R, D.deg() - (A.deg() - d)) * Mat({}, {Tp(1)}, {Tp(1)}, -Q)\
    \ * M;\n}\n\ntemplate <typename Tp>\ninline std::array<Poly<Tp>, 3> xgcd(const\
    \ Poly<Tp> &A, const Poly<Tp> &B) {\n    const auto M = hgcd(A, B, std::max(A.deg(),\
    \ B.deg()));\n    return {M[0][0], M[0][1], M[0][0] * A + M[0][1] * B};\n}\n\n\
    template <typename Tp>\ninline std::array<Poly<Tp>, 2> inv_gcd(const Poly<Tp>\
    \ &A, const Poly<Tp> &B) {\n    const auto M = hgcd(A, B, std::max(A.deg(), B.deg()));\n\
    \    return {M[0][0], M[0][0] * A + M[0][1] * B};\n}\n\n// returns P, Q s.t. [x^[-k,\
    \ 0)] P/Q = [x^[-k, 0)] A/B\n// where P, Q in F[x], deg(Q) is minimized\n// requires\
    \ deg(A) < deg(B)\ntemplate <typename Tp>\ninline std::array<Poly<Tp>, 2> rational_approximation(const\
    \ Poly<Tp> &A, const Poly<Tp> &B, int k) {\n    auto M            = hgcd(B, A,\
    \ k / 2);\n    const auto [C, D] = M * std::array{B, A};\n    if (D.deg() >= 0\
    \ && D.deg() - C.deg() >= -(k - (B.deg() - C.deg()) * 2))\n        M = GCDMatrix<Poly<Tp>>({},\
    \ {Tp(1)}, {Tp(1)}, -(C / D)) * M;\n    return {M.adj()[1][0], M.adj()[0][0]};\n\
    }\n\ntemplate <typename Tp>\ninline std::array<Poly<Tp>, 2> rational_reconstruction(const\
    \ std::vector<Tp> &A) {\n    return rational_approximation(Poly<Tp>(A.rbegin(),\
    \ A.rend()), Poly<Tp>{Tp(1)} << A.size(),\n                                  A.size());\n\
    }\n\n// returns [x^[-k, 0)] A/B\n// requires deg(A) < deg(B)\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> fraction_to_series(const Poly<Tp> &A, const Poly<Tp>\
    \ &B, int k) {\n    return (((A << k) / B).rev() << (B.deg() - A.deg() - 1)).slice(0,\
    \ k);\n}\n#line 2 \"random.hpp\"\n\n#line 2 \"rng.hpp\"\n\n#include <cstdint>\n\
    #include <limits>\n\n// see: https://prng.di.unimi.it/xoshiro256starstar.c\n//\
    \ original license CC0 1.0\nclass xoshiro256starstar {\n    using u64 = std::uint64_t;\n\
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
    \ 6 \"mat_basic.hpp\"\n#include <optional>\n#line 9 \"mat_basic.hpp\"\n\ntemplate\
    \ <typename Tp>\nusing Matrix = std::vector<std::vector<Tp>>;\n\ntemplate <typename\
    \ Tp>\ninline int width(const Matrix<Tp> &A) {\n    return A.empty() ? 0 : (int)A[0].size();\n\
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
    \ det      = 1;\n    for (int i = 0; i < n; ++i) {\n        int pivot = i;\n \
    \       for (; pivot < n; ++pivot)\n            if (A[pivot][i] != 0) break;\n\
    \        if (pivot == n) return 0;\n        if (pivot != i) {\n            A[pivot].swap(A[i]);\n\
    \            det = -det;\n        }\n        det *= A[i][i];\n        const auto\
    \ iv = A[i][i].inv();\n        for (int j = i + 1; j < n; ++j) {\n           \
    \ const auto p = A[j][i] * iv;\n            if (p == 0) continue;\n          \
    \  for (int k = i; k < n; ++k) A[j][k] -= p * A[i][k];\n        }\n    }\n   \
    \ return det;\n}\n\ntemplate <typename Tp>\ninline Matrix<Tp> to_upper_hessenberg(Matrix<Tp>\
    \ A) {\n    assert(is_square_matrix(A));\n    const int n = height(A);\n    for\
    \ (int i = 0; i < n - 1; ++i) {\n        int pivot = i + 1;\n        for (; pivot\
    \ < n; ++pivot)\n            if (A[pivot][i] != 0) break;\n        if (pivot ==\
    \ n) continue;\n        if (pivot != i + 1) {\n            A[pivot].swap(A[i +\
    \ 1]);\n            for (int j = 0; j < n; ++j) std::swap(A[j][pivot], A[j][i\
    \ + 1]);\n        }\n        const auto iv = A[i + 1][i].inv();\n        for (int\
    \ j = i + 2; j < n; ++j) {\n            if (A[j][i] == 0) continue;\n        \
    \    const auto v = A[j][i] * iv;\n            for (int k = i; k < n; ++k) A[j][k]\
    \ -= v * A[i + 1][k];\n            for (int k = 0; k < n; ++k) A[k][i + 1] +=\
    \ v * A[k][j];\n        }\n    }\n    return A;\n}\n\n// returns det(xI - A)\n\
    template <typename Tp>\ninline std::vector<Tp> charpoly(const Matrix<Tp> &A) {\n\
    \    const auto H = to_upper_hessenberg(A);\n    const int n  = height(A);\n \
    \   std::vector<std::vector<Tp>> P(n + 1);\n    P[0] = {Tp(1)};\n    for (int\
    \ i = 1; i <= n; ++i) {\n        P[i].resize(i + 1);\n        for (int j = 0;\
    \ j < i; ++j)\n            P[i][j] -= H[i - 1][i - 1] * P[i - 1][j], P[i][j +\
    \ 1] += P[i - 1][j];\n        Tp t = 1;\n        for (int j = 1; j < i; ++j) {\n\
    \            t *= H[i - j][i - j - 1];\n            const auto prod = t * H[i\
    \ - j - 1][i - 1];\n            if (prod == 0) continue;\n            for (int\
    \ k = 0; k < i - j; ++k) P[i][k] -= prod * P[i - j - 1][k];\n        }\n    }\n\
    \    return P[n];\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> minpoly(const\
    \ Matrix<Tp> &A) {\n    assert(is_square_matrix(A));\n    const int n  = height(A);\n\
    \    const auto u = random_vector<Tp>(n);\n    auto v       = random_vector<Tp>(n);\n\
    \    // u^T A^([0..2n)) v\n    std::vector<Tp> proj(n * 2);\n    for (int i =\
    \ 0; i < n * 2; v = mat_apply(A, v), ++i)\n        for (int j = 0; j < n; ++j)\
    \ proj[i] += u[j] * v[j];\n    const auto [P, Q] = rational_reconstruction(proj);\n\
    \    assert(Q.deg() <= n);\n    return Q.monic();\n}\n#line 7 \"mat_extra.hpp\"\
    \n\n/*\ntest case generator:\n```sage\nimport random\nR.<x> = GF(998244353)[]\n\
    N = 5\nd = 4\nif __name__ == '__main__':\n    print(N, d)\n    A = zero_matrix(GF(998244353),\
    \ N)\n    L = []\n    for _ in range(d):\n        B = random_matrix(GF(998244353),\
    \ N, algorithm='echelonizable', rank=random.randint(1,N))\n        L.append(B)\n\
    \        A = x*A + B\n    L.reverse()\n    for i in range(len(L)):\n        for\
    \ j in range(N):\n            print(' '.join([str(k) for k in L[i][j].list()]),\
    \ end='\\n')\n    print(det(A).list())\n```\n*/\n\n// returns det(A0 + xA1 + ...\
    \ + x^(d-1) Ad)\n// test: https://qoj.ac/contest/1536/problem/59\n// see:\n//\
    \ [1]: Elegia's comment.\n//      https://codeforces.com/blog/entry/92248?#comment-818786\n\
    template <typename Tp>\ninline std::vector<Tp> det_d(Matrix<std::vector<Tp>> A)\
    \ {\n    assert(is_square_matrix(A));\n    auto sub = [](auto &a, const auto &b,\
    \ Tp v, int n, int d) {\n        if (v == 0) return;\n        for (int i = 0;\
    \ i < n; ++i)\n            for (int j = 0; j < d; ++j) a[i][j] -= v * b[i][j];\n\
    \    };\n    const int n = height(A);\n    const int d = (n == 0 ? 0 : (int)A[0][0].size());\n\
    \    Tp m        = 1;\n    for (int i = 0; i < n; ++i) {\n        int pivot =\
    \ i;\n        for (; pivot < n; ++pivot)\n            if (A[pivot][i][d - 1] !=\
    \ 0) break;\n        if (pivot == n) continue;\n        if (pivot != i) {\n  \
    \          A[pivot].swap(A[i]);\n            m = -m;\n        }\n        m *=\
    \ A[i][i][d - 1];\n        const auto iv = A[i][i][d - 1].inv();\n        for\
    \ (int j = 0; j < n; ++j)\n            for (int k = 0; k < d; ++k) A[i][j][k]\
    \ *= iv;\n        for (int j = 0; j < i; ++j) sub(A[j], A[i], A[j][i][d - 1],\
    \ n, d);\n        for (int j = i + 1; j < n; ++j) sub(A[j], A[i], A[j][i][d -\
    \ 1], n, d);\n    }\n    int t = 0;\n    for (; t <= n * (d - 1); ++t) {\n   \
    \     int s = 0;\n        for (; s < n; ++s)\n            if (std::all_of(A[s].begin(),\
    \ A[s].end(), [d](const auto &a) { return a[d - 1] == 0; }))\n               \
    \ break;\n        if (s == n) break;\n        for (int i = 0; i < n; ++i)\n  \
    \          std::rotate(A[s][i].rbegin(), A[s][i].rbegin() + 1, A[s][i].rend());\n\
    \        for (int i = 0; i < s; ++i) sub(A[s], A[i], A[s][i][d - 1], n, d);\n\
    \        for (int i = s + 1; i < n; ++i) sub(A[s], A[i], A[s][i][d - 1], n, d);\n\
    \        int pivot = 0;\n        for (; pivot < n; ++pivot)\n            if (A[s][pivot][d\
    \ - 1] != 0) break;\n        if (pivot == n) continue;\n        if (pivot != s)\
    \ {\n            A[pivot].swap(A[s]);\n            m = -m;\n            s = pivot;\n\
    \        }\n        m *= A[s][s][d - 1];\n        const auto iv = A[s][s][d -\
    \ 1].inv();\n        for (int i = 0; i < n; ++i)\n            for (int j = 0;\
    \ j < d; ++j) A[s][i][j] *= iv;\n        for (int i = 0; i < s; ++i) sub(A[i],\
    \ A[s], A[i][s][d - 1], n, d);\n        for (int i = s + 1; i < n; ++i) sub(A[i],\
    \ A[s], A[i][s][d - 1], n, d);\n    }\n    if (t > n * (d - 1)) return {};\n \
    \   //     [      I            ]\n    //     [         ...       ]\n    // B =\
    \ [             ...   ]\n    //     [                  I]\n    //     [C_0 C_1\
    \ ... C_(d-2)]\n    // charpoly(B) = det(x^(d-1)I - ... - C_0) (Elegia, zx2003,\
    \ mayaohua2003).\n    Matrix<Tp> B(n * (d - 1), std::vector<Tp>(n * (d - 1)));\n\
    \    for (int i = 0; i < d - 1; ++i)\n        for (int j = 0; j < n; ++j)\n  \
    \          for (int k = 0; k < n; ++k) B[(d - 2) * n + j][i * n + k] = -A[j][k][i];\n\
    \    for (int i = 0; i < d - 2; ++i)\n        for (int j = 0; j < n; ++j) B[i\
    \ * n + j][(i + 1) * n + j] = 1;\n    auto res = charpoly(B);\n    res.erase(res.begin(),\
    \ res.begin() + t);\n    for (int i = 0; i < (int)res.size(); ++i) res[i] *= m;\n\
    \    return res;\n}\n"
  code: "#pragma once\n\n#include \"mat_basic.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\n/*\ntest case generator:\n```sage\nimport random\n\
    R.<x> = GF(998244353)[]\nN = 5\nd = 4\nif __name__ == '__main__':\n    print(N,\
    \ d)\n    A = zero_matrix(GF(998244353), N)\n    L = []\n    for _ in range(d):\n\
    \        B = random_matrix(GF(998244353), N, algorithm='echelonizable', rank=random.randint(1,N))\n\
    \        L.append(B)\n        A = x*A + B\n    L.reverse()\n    for i in range(len(L)):\n\
    \        for j in range(N):\n            print(' '.join([str(k) for k in L[i][j].list()]),\
    \ end='\\n')\n    print(det(A).list())\n```\n*/\n\n// returns det(A0 + xA1 + ...\
    \ + x^(d-1) Ad)\n// test: https://qoj.ac/contest/1536/problem/59\n// see:\n//\
    \ [1]: Elegia's comment.\n//      https://codeforces.com/blog/entry/92248?#comment-818786\n\
    template <typename Tp>\ninline std::vector<Tp> det_d(Matrix<std::vector<Tp>> A)\
    \ {\n    assert(is_square_matrix(A));\n    auto sub = [](auto &a, const auto &b,\
    \ Tp v, int n, int d) {\n        if (v == 0) return;\n        for (int i = 0;\
    \ i < n; ++i)\n            for (int j = 0; j < d; ++j) a[i][j] -= v * b[i][j];\n\
    \    };\n    const int n = height(A);\n    const int d = (n == 0 ? 0 : (int)A[0][0].size());\n\
    \    Tp m        = 1;\n    for (int i = 0; i < n; ++i) {\n        int pivot =\
    \ i;\n        for (; pivot < n; ++pivot)\n            if (A[pivot][i][d - 1] !=\
    \ 0) break;\n        if (pivot == n) continue;\n        if (pivot != i) {\n  \
    \          A[pivot].swap(A[i]);\n            m = -m;\n        }\n        m *=\
    \ A[i][i][d - 1];\n        const auto iv = A[i][i][d - 1].inv();\n        for\
    \ (int j = 0; j < n; ++j)\n            for (int k = 0; k < d; ++k) A[i][j][k]\
    \ *= iv;\n        for (int j = 0; j < i; ++j) sub(A[j], A[i], A[j][i][d - 1],\
    \ n, d);\n        for (int j = i + 1; j < n; ++j) sub(A[j], A[i], A[j][i][d -\
    \ 1], n, d);\n    }\n    int t = 0;\n    for (; t <= n * (d - 1); ++t) {\n   \
    \     int s = 0;\n        for (; s < n; ++s)\n            if (std::all_of(A[s].begin(),\
    \ A[s].end(), [d](const auto &a) { return a[d - 1] == 0; }))\n               \
    \ break;\n        if (s == n) break;\n        for (int i = 0; i < n; ++i)\n  \
    \          std::rotate(A[s][i].rbegin(), A[s][i].rbegin() + 1, A[s][i].rend());\n\
    \        for (int i = 0; i < s; ++i) sub(A[s], A[i], A[s][i][d - 1], n, d);\n\
    \        for (int i = s + 1; i < n; ++i) sub(A[s], A[i], A[s][i][d - 1], n, d);\n\
    \        int pivot = 0;\n        for (; pivot < n; ++pivot)\n            if (A[s][pivot][d\
    \ - 1] != 0) break;\n        if (pivot == n) continue;\n        if (pivot != s)\
    \ {\n            A[pivot].swap(A[s]);\n            m = -m;\n            s = pivot;\n\
    \        }\n        m *= A[s][s][d - 1];\n        const auto iv = A[s][s][d -\
    \ 1].inv();\n        for (int i = 0; i < n; ++i)\n            for (int j = 0;\
    \ j < d; ++j) A[s][i][j] *= iv;\n        for (int i = 0; i < s; ++i) sub(A[i],\
    \ A[s], A[i][s][d - 1], n, d);\n        for (int i = s + 1; i < n; ++i) sub(A[i],\
    \ A[s], A[i][s][d - 1], n, d);\n    }\n    if (t > n * (d - 1)) return {};\n \
    \   //     [      I            ]\n    //     [         ...       ]\n    // B =\
    \ [             ...   ]\n    //     [                  I]\n    //     [C_0 C_1\
    \ ... C_(d-2)]\n    // charpoly(B) = det(x^(d-1)I - ... - C_0) (Elegia, zx2003,\
    \ mayaohua2003).\n    Matrix<Tp> B(n * (d - 1), std::vector<Tp>(n * (d - 1)));\n\
    \    for (int i = 0; i < d - 1; ++i)\n        for (int j = 0; j < n; ++j)\n  \
    \          for (int k = 0; k < n; ++k) B[(d - 2) * n + j][i * n + k] = -A[j][k][i];\n\
    \    for (int i = 0; i < d - 2; ++i)\n        for (int j = 0; j < n; ++j) B[i\
    \ * n + j][(i + 1) * n + j] = 1;\n    auto res = charpoly(B);\n    res.erase(res.begin(),\
    \ res.begin() + t);\n    for (int i = 0; i < (int)res.size(); ++i) res[i] *= m;\n\
    \    return res;\n}\n"
  dependsOn:
  - mat_basic.hpp
  - poly.hpp
  - poly_basic.hpp
  - binomial.hpp
  - fft.hpp
  - fps_basic.hpp
  - semi_relaxed_conv.hpp
  - random.hpp
  - rng.hpp
  isVerificationFile: false
  path: mat_extra.hpp
  requiredBy: []
  timestamp: '2024-12-23 21:08:20+08:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: mat_extra.hpp
layout: document
redirect_from:
- /library/mat_extra.hpp
- /library/mat_extra.hpp.html
title: mat_extra.hpp
---