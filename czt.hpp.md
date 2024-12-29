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
    path: fps_basic.hpp
    title: fps_basic.hpp
  - icon: ':heavy_check_mark:'
    path: middle_product.hpp
    title: middle_product.hpp
  - icon: ':heavy_check_mark:'
    path: poly_basic.hpp
    title: poly_basic.hpp
  - icon: ':heavy_check_mark:'
    path: semi_relaxed_conv.hpp
    title: semi_relaxed_conv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/convolution/convolution_mod.1.test.cpp
    title: test/convolution/convolution_mod.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
    title: test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
    title: test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://noshi91.github.io/algorithm-encyclopedia/polynomial-interpolation-geometric
  bundledCode: "#line 2 \"czt.hpp\"\n\n#line 2 \"batch_inv.hpp\"\n\n#include <cassert>\n\
    #include <vector>\n\ntemplate <typename Tp>\ninline std::vector<Tp> batch_inv(const\
    \ std::vector<Tp> &a) {\n    if (a.empty()) return {};\n    const int n = a.size();\n\
    \    std::vector<Tp> b(n);\n    Tp v = 1;\n    for (int i = 0; i < n; ++i) b[i]\
    \ = v, v *= a[i];\n    assert(v != 0);\n    v = v.inv();\n    for (int i = n -\
    \ 1; i >= 0; --i) b[i] *= v, v *= a[i];\n    return b;\n}\n#line 2 \"middle_product.hpp\"\
    \n\n#line 2 \"fft.hpp\"\n\n#include <algorithm>\n#line 5 \"fft.hpp\"\n#include\
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
    }\n#line 7 \"middle_product.hpp\"\n\n// see:\n// [1]: Guillaume Hanrot, Michel\
    \ Quercia, Paul Zimmermann. The Middle Product Algorithm I.\n// [2]: Alin Bostan,\
    \ Gr\xE9goire Lecerf, \xC9ric Schost. Tellegen's principle into practice.\n\n\
    // returns (fg)_(n-1),...,(fg)_(m-1)\n// f: f_0 + ... + f_(m-1)x^(m-1)\n// g:\
    \ g_0 + ... + g_(n-1)x^(n-1)\n// m >= n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ middle_product(std::vector<Tp> f, std::vector<Tp> g) {\n    const int m = f.size();\n\
    \    const int n = g.size();\n    assert(m >= n);\n    std::reverse(g.begin(),\
    \ g.end());\n    const int len = fft_len(m);\n    f.resize(len);\n    g.resize(len);\n\
    \    transposed_inv_fft(f);\n    fft(g);\n    for (int i = 0; i < len; ++i) f[i]\
    \ *= g[i];\n    transposed_fft(f);\n    f.resize(m - n + 1);\n    return f;\n\
    }\n#line 2 \"poly_basic.hpp\"\n\n#line 2 \"binomial.hpp\"\n\n#line 5 \"binomial.hpp\"\
    \n\ntemplate <typename Tp>\nclass Binomial {\n    std::vector<Tp> factorial_,\
    \ invfactorial_;\n\n    Binomial() : factorial_{Tp(1)}, invfactorial_{Tp(1)} {}\n\
    \n    void preprocess(int n) {\n        if (const int nn = factorial_.size();\
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
    \ invfactorial_[n]; }\n};\n#line 2 \"fps_basic.hpp\"\n\n#line 2 \"semi_relaxed_conv.hpp\"\
    \n\n#line 5 \"semi_relaxed_conv.hpp\"\n#include <type_traits>\n#include <utility>\n\
    #line 8 \"semi_relaxed_conv.hpp\"\n\ntemplate <typename Tp, typename Closure>\n\
    inline std::enable_if_t<std::is_invocable_r_v<Tp, Closure, int, const std::vector<Tp>\
    \ &>,\n                        std::vector<Tp>>\nsemi_relaxed_convolution_naive(const\
    \ std::vector<Tp> &A, Closure gen, int n) {\n    std::vector<Tp> B(n), AB(n);\n\
    \    for (int i = 0; i < n; ++i) {\n        for (int j = std::max(0, i - (int)A.size()\
    \ + 1); j < i; ++j) AB[i] += A[i - j] * B[j];\n        B[i] = gen(i, AB);\n  \
    \      if (!A.empty()) AB[i] += A[0] * B[i];\n    }\n    return B;\n}\n\n// returns\
    \ coefficients generated by closure\n// closure: gen(index, current_product)\n\
    template <typename Tp, typename Closure>\ninline std::enable_if_t<std::is_invocable_r_v<Tp,\
    \ Closure, int, const std::vector<Tp> &>,\n                        std::vector<Tp>>\n\
    semi_relaxed_convolution(const std::vector<Tp> &A, Closure gen, int n) {\n   \
    \ if (A.size() < 60) return semi_relaxed_convolution_naive(A, gen, n);\n    enum\
    \ { BaseCaseSize = 32 };\n    static_assert((BaseCaseSize & (BaseCaseSize - 1))\
    \ == 0);\n\n    static const int Block[]     = {16, 16, 16, 16, 16};\n    static\
    \ const int BlockSize[] = {\n        BaseCaseSize,\n        BaseCaseSize * Block[0],\n\
    \        BaseCaseSize * Block[0] * Block[1],\n        BaseCaseSize * Block[0]\
    \ * Block[1] * Block[2],\n        BaseCaseSize * Block[0] * Block[1] * Block[2]\
    \ * Block[3],\n        BaseCaseSize * Block[0] * Block[1] * Block[2] * Block[3]\
    \ * Block[4],\n    };\n\n    // returns (which_block, level)\n    auto blockinfo\
    \ = [](int ind) {\n        int i = ind / BaseCaseSize, lv = 0;\n        while\
    \ ((i & (Block[lv] - 1)) == 0) i /= Block[lv++];\n        return std::make_pair(i\
    \ & (Block[lv] - 1), lv);\n    };\n\n    std::vector<Tp> B(n), AB(n);\n    std::vector<std::vector<std::vector<Tp>>>\
    \ dftA, dftB;\n\n    for (int i = 0; i < n; ++i) {\n        const int s = i &\
    \ (BaseCaseSize - 1);\n\n        // blocked contribution\n        if (i >= BaseCaseSize\
    \ && s == 0) {\n            const auto [j, lv]  = blockinfo(i);\n            const\
    \ int blocksize = BlockSize[lv];\n\n            if (blocksize * j == i) {\n  \
    \              if ((int)dftA.size() == lv) {\n                    dftA.emplace_back();\n\
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
    \    std::reverse(Q.begin(), Q.end());\n    return Q;\n}\n#line 8 \"czt.hpp\"\n\
    \n// returns F(a),F(ac),F(ac^2),...,F(ac^(n-1))\n// Use        ij = binom(i,2)\
    \   + binom(-j,2) - binom(i-j,2)\n// instead of ij = binom(i+j,2) - binom(i,2)\
    \  - binom(j,2)\ntemplate <typename Tp>\ninline std::vector<Tp> czt(std::vector<Tp>\
    \ F, Tp c, int n, Tp a = 1) {\n    if (n <= 0) return {};\n    const int degF\
    \ = degree(F);\n    shrink(F);\n    if (degF < 0) return std::vector<Tp>(n);\n\
    \    if (degF == 0 || a == 0) return std::vector<Tp>(n, F[0]);\n    if (a != 1)\
    \ {\n        // F(x) <- F(ax)\n        Tp aa = 1;\n        for (int i = 0; i <=\
    \ degF; ++i) F[i] *= aa, aa *= a;\n    }\n    if (c == 0) {\n        std::vector<Tp>\
    \ res(n, F[0]);\n        for (int i = 1; i <= degF; ++i) res[0] += F[i];\n   \
    \     return res;\n    }\n    std::vector<Tp> H(std::max(degF + 1, n - 1));\n\
    \    Tp cc = H[0] = 1;\n    for (int i = 1; i < (int)H.size(); ++i) H[i] = H[i\
    \ - 1] * (cc *= c);\n    std::vector<Tp> G(degF + n); // G[i+degF]=c^(-binom(i,2))\n\
    \    auto GG     = G.begin() + degF;\n    const Tp ic = c.inv();\n    cc = GG[0]\
    \ = 1;\n    for (int i = 1; i < n; ++i) GG[i] = GG[i - 1] * cc, cc *= ic;\n  \
    \  cc = 1;\n    for (int i = -1; i >= -degF; --i) GG[i] = GG[i + 1] * (cc *= ic);\n\
    \    // F[i] <- c^(binom(i+1,2))*F[i]\n    for (int i = 0; i <= degF; ++i) F[i]\
    \ *= H[i];\n    F = middle_product(G, F);\n    // F[i] <- c^(binom(i,2))*F[i]\n\
    \    for (int i = 1; i < n; ++i) F[i] *= H[i - 1];\n    return F;\n}\n\n// returns\
    \ f s.t. f(aq^i)=F[i]\n// aq^i != aq^j for all i != j\n// see: https://noshi91.github.io/algorithm-encyclopedia/polynomial-interpolation-geometric\n\
    // noshi91. \u6A19\u672C\u70B9\u304C\u7B49\u6BD4\u6570\u5217\u3092\u6210\u3059\
    \u5834\u5408\u306B\u88DC\u9593\u591A\u9805\u5F0F\u3092\u8A08\u7B97\u3059\u308B\
    \u30A2\u30EB\u30B4\u30EA\u30BA\u30E0.\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ inv_czt(const std::vector<Tp> &F, Tp q, Tp a = 1) {\n    if (F.empty()) return\
    \ {};\n    if (a == 0) return {F[0]};\n    const int n = F.size();\n    std::vector<Tp>\
    \ Q(n), S(n), M(n), D(n);\n    Tp qq = 1;\n    // Q[i]=q^i\n    for (int i = 0;\
    \ i < n; ++i) Q[i] = qq, qq *= q;\n    // S[i]=prod_(i=1..i)(1-q^i)\n    S[0]\
    \ = 1;\n    for (int i = 1; i < n; ++i) S[i] = S[i - 1] * (1 - Q[i]);\n    const\
    \ auto Sn   = S[n - 1] * (1 - qq);\n    const auto invS = batch_inv(S);\n    qq\
    \              = 1;\n    // M[n-i]=qbinom(n,i)*q^(binom(i,2))*(-1)^i\n    for\
    \ (int i = 1; i < n; ++i) M[n - i] = Sn * invS[i] * invS[n - i] * (qq *= -Q[i\
    \ - 1]);\n    M[0] = qq * -Q[n - 1]; // in case of q^n=1\n    // D[i]=S[i]*S[n-i-1]*q^(binom(i,2)+i(n-i-1))*(-1)^i\n\
    \    D[0] = 1;\n    for (int i = 0; i < n - 1; ++i) D[i + 1] = D[i] * -Q[n - i\
    \ - 2];\n    for (int i = 0; i < n; ++i) D[i] *= S[i] * S[n - i - 1];\n    //\
    \ D[i] <- -F[i]/D[i]\n    D = batch_inv(D);\n    for (int i = 0; i < n; ++i) D[i]\
    \ *= -F[i];\n    auto res = convolution(M, czt(D, q.inv(), n, q.inv()));\n   \
    \ res.resize(n);\n    if (a != 1) {\n        const auto ia = a.inv();\n      \
    \  Tp aa         = 1;\n        for (int i = 0; i < n; ++i) res[i] *= aa, aa *=\
    \ ia;\n    }\n    return res;\n}\n"
  code: "#pragma once\n\n#include \"batch_inv.hpp\"\n#include \"middle_product.hpp\"\
    \n#include \"poly_basic.hpp\"\n#include <algorithm>\n#include <vector>\n\n// returns\
    \ F(a),F(ac),F(ac^2),...,F(ac^(n-1))\n// Use        ij = binom(i,2)   + binom(-j,2)\
    \ - binom(i-j,2)\n// instead of ij = binom(i+j,2) - binom(i,2)  - binom(j,2)\n\
    template <typename Tp>\ninline std::vector<Tp> czt(std::vector<Tp> F, Tp c, int\
    \ n, Tp a = 1) {\n    if (n <= 0) return {};\n    const int degF = degree(F);\n\
    \    shrink(F);\n    if (degF < 0) return std::vector<Tp>(n);\n    if (degF ==\
    \ 0 || a == 0) return std::vector<Tp>(n, F[0]);\n    if (a != 1) {\n        //\
    \ F(x) <- F(ax)\n        Tp aa = 1;\n        for (int i = 0; i <= degF; ++i) F[i]\
    \ *= aa, aa *= a;\n    }\n    if (c == 0) {\n        std::vector<Tp> res(n, F[0]);\n\
    \        for (int i = 1; i <= degF; ++i) res[0] += F[i];\n        return res;\n\
    \    }\n    std::vector<Tp> H(std::max(degF + 1, n - 1));\n    Tp cc = H[0] =\
    \ 1;\n    for (int i = 1; i < (int)H.size(); ++i) H[i] = H[i - 1] * (cc *= c);\n\
    \    std::vector<Tp> G(degF + n); // G[i+degF]=c^(-binom(i,2))\n    auto GG  \
    \   = G.begin() + degF;\n    const Tp ic = c.inv();\n    cc = GG[0] = 1;\n   \
    \ for (int i = 1; i < n; ++i) GG[i] = GG[i - 1] * cc, cc *= ic;\n    cc = 1;\n\
    \    for (int i = -1; i >= -degF; --i) GG[i] = GG[i + 1] * (cc *= ic);\n    //\
    \ F[i] <- c^(binom(i+1,2))*F[i]\n    for (int i = 0; i <= degF; ++i) F[i] *= H[i];\n\
    \    F = middle_product(G, F);\n    // F[i] <- c^(binom(i,2))*F[i]\n    for (int\
    \ i = 1; i < n; ++i) F[i] *= H[i - 1];\n    return F;\n}\n\n// returns f s.t.\
    \ f(aq^i)=F[i]\n// aq^i != aq^j for all i != j\n// see: https://noshi91.github.io/algorithm-encyclopedia/polynomial-interpolation-geometric\n\
    // noshi91. \u6A19\u672C\u70B9\u304C\u7B49\u6BD4\u6570\u5217\u3092\u6210\u3059\
    \u5834\u5408\u306B\u88DC\u9593\u591A\u9805\u5F0F\u3092\u8A08\u7B97\u3059\u308B\
    \u30A2\u30EB\u30B4\u30EA\u30BA\u30E0.\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ inv_czt(const std::vector<Tp> &F, Tp q, Tp a = 1) {\n    if (F.empty()) return\
    \ {};\n    if (a == 0) return {F[0]};\n    const int n = F.size();\n    std::vector<Tp>\
    \ Q(n), S(n), M(n), D(n);\n    Tp qq = 1;\n    // Q[i]=q^i\n    for (int i = 0;\
    \ i < n; ++i) Q[i] = qq, qq *= q;\n    // S[i]=prod_(i=1..i)(1-q^i)\n    S[0]\
    \ = 1;\n    for (int i = 1; i < n; ++i) S[i] = S[i - 1] * (1 - Q[i]);\n    const\
    \ auto Sn   = S[n - 1] * (1 - qq);\n    const auto invS = batch_inv(S);\n    qq\
    \              = 1;\n    // M[n-i]=qbinom(n,i)*q^(binom(i,2))*(-1)^i\n    for\
    \ (int i = 1; i < n; ++i) M[n - i] = Sn * invS[i] * invS[n - i] * (qq *= -Q[i\
    \ - 1]);\n    M[0] = qq * -Q[n - 1]; // in case of q^n=1\n    // D[i]=S[i]*S[n-i-1]*q^(binom(i,2)+i(n-i-1))*(-1)^i\n\
    \    D[0] = 1;\n    for (int i = 0; i < n - 1; ++i) D[i + 1] = D[i] * -Q[n - i\
    \ - 2];\n    for (int i = 0; i < n; ++i) D[i] *= S[i] * S[n - i - 1];\n    //\
    \ D[i] <- -F[i]/D[i]\n    D = batch_inv(D);\n    for (int i = 0; i < n; ++i) D[i]\
    \ *= -F[i];\n    auto res = convolution(M, czt(D, q.inv(), n, q.inv()));\n   \
    \ res.resize(n);\n    if (a != 1) {\n        const auto ia = a.inv();\n      \
    \  Tp aa         = 1;\n        for (int i = 0; i < n; ++i) res[i] *= aa, aa *=\
    \ ia;\n    }\n    return res;\n}\n"
  dependsOn:
  - batch_inv.hpp
  - middle_product.hpp
  - fft.hpp
  - poly_basic.hpp
  - binomial.hpp
  - fps_basic.hpp
  - semi_relaxed_conv.hpp
  isVerificationFile: false
  path: czt.hpp
  requiredBy: []
  timestamp: '2024-12-29 01:44:15+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  - test/convolution/convolution_mod.1.test.cpp
documentation_of: czt.hpp
layout: document
title: Chirp Z Transform
---

## Chirp Z transform

The Chirp Z transform is by definition

$$
\operatorname{\mathsf{CZT}} _ n:\left(f(x),q\right) \mapsto \begin{bmatrix}f(1)&f(q)&\cdots &f\left(q^{n-1}\right)\end{bmatrix}
$$

where $f(x):=\sum _ {i=0}^{m-1}f _ i x^i\in\mathbb{C}\left\lbrack x\right\rbrack$ and $q\in\mathbb{C}\setminus \left\lbrace 0\right\rbrace$. Since

$$
ij = \binom{i}{2} + \binom{-j}{2} - \binom{i - j}{2}
$$

where $i,j\in\mathbb{Z}$, we can construct

$$
\begin{aligned}
G(x)&:=\sum _ {i = -(m - 1)}^{n - 1}q^{-\binom{i}{2}}x^i, \\
F(x)&:=\sum _ {i = 0}^{m - 1}f _ i q^{\binom{-i}{2}}x^i
\end{aligned}
$$

note that $G(x)\in\mathbb{C}\left\lbrack x,x^{-1}\right\rbrack$, and for $i=0,\dots,n-1$ we have

$$
\begin{aligned}
\left\lbrack x^i\right\rbrack\left(G(x)F(x)\right) &= \sum _ {j = 0}^{m - 1}\left(\left(\left\lbrack x^{i-j}\right\rbrack G(x)\right)\left(\left\lbrack x^j\right\rbrack F(x)\right)\right) \\
&= \sum _ {j=0}^{m-1}f _ jq^{\binom{-j}{2} - \binom{i - j}{2}} \\
&= q^{-\binom{i}{2}}\cdot f\left(q^i\right)
\end{aligned}
$$

note that $q^{\binom{i+1}{2}}=q^{\binom{i}{2}}\cdot q^i$ and $\binom{-i}{2} = \binom{i+1}{2}$.

One can take advantage of the "middle product" algorithm. CZT could be done in time $O\left(\mathsf{M}(n+m)\right)$.

## Inverse Chirp Z transform

The inverse Chirp Z transform is by definition

$$
\operatorname{\mathsf{ICZT}} _ n:\left(\begin{bmatrix}f(1)&f(q)&\cdots &f\left(q^{n-1}\right)\end{bmatrix},q\right) \mapsto f(x)
$$

where $f(x)\in\mathbb{C}\left\lbrack x\right\rbrack _ {\lt n}$ and $q\in\mathbb{C}\setminus\left\lbrace 0\right\rbrace$, $q^{i}\neq q^{j}$ for all $i\neq j$.

### (Modified) Lagrange interpolation formula

Recall the Lagrange interpolation formula, we have

$$
f(x) = \sum _ {i=0}^{n-1}\left(f\left(x _ i\right)\prod _ {0\leq j\lt n\atop j\neq i} \frac{x - x _ j}{x _ i - x _ j}\right)
$$

for $x _ i \neq x _ j$ for all $i\neq j$.

> L'Hôpital's Rule:
> The derivative of $f = \sum _ {i} f _ i x^i$ is $f' = \sum _ {i} i f_i x^{i - 1}$, for $g\in\mathbb{C}\left\lbrack x\right\rbrack$ we have the product rule: $\left(fg\right)' = f'g + fg'$. Let $\alpha\in\mathbb{C}$ and $f(\alpha) = 0$ then $\left(fg\right)'(\alpha) = f'(\alpha)g(\alpha)$, if $f'(\alpha)\neq 0$ then $(fg/f)(\alpha) = g(\alpha) = (fg)'(\alpha)/f'(\alpha)$.

Let $M(x):=\prod _ {i=0}^{n-1}\left(x - x _ i\right)$, we have

$$
M'(x _ i)=\prod_{0\leq j\lt n\atop j\neq i}\left(x _ i - x _ j\right)
$$

The **modified Lagrange interpolation formula** is

$$
f(x)=M(x)\cdot \sum _ {i=0}^{n-1}\frac{f\left(x _ i\right)/M'(x _ i)}{x - x _ i}
$$

Now we have

$$
f(x)=M(x)\cdot\sum _ {i=0}^{n-1}\frac{f\left(q^i\right)/M'\left(q^i\right)}{x-q^i}
$$

where $M(x)=\prod _ {j=0}^{n-1}\left(x - q^j\right)$. If we set $n-1=2k$ and $H(x):=\prod_{j=0}^{k-1}\left(x - q^j\right)$ then

$$
M(x)=H(x)\cdot q^{k^2}\cdot H\left(\frac{x}{q^k}\right)
$$

So we could compute $M(x)$ in time $O\left(\mathsf{M}(n)\right)$. We could use CZT to compute $M'(1),\dots ,M'(q^{n-1})$. Let $c _ i := f\left(q^i\right)/M'\left(q^i\right)$, we have

$$
f(x) = M(x)\cdot\sum _ {i=0}^{n-1}\frac{c _ i}{x-q^i}
$$

since $\deg f(x) \lt n$, we only need to compute $\sum _ {i=0}^{n-1}\frac{c _ i}{x - q^i}\bmod{x^n}$, which is

$$
\begin{aligned}
\sum _ {i=0}^{n-1}\frac{c _ i}{x - q^i}\bmod x^n&=-\sum _ {i=0}^{n-1}\left(\sum _ {j=0}^{n-1}c _ i q^{-i(j+1)}x^j\right) \\
&=-\sum _ {j=0}^{n-1}C\left(q^{-j-1}\right)x^j
\end{aligned}
$$

where $C(x)=\sum _ {i=0}^{n-1}c _ i x^i$. We can use another CZT to compute $C\left(q^{-1}\right),\dots ,C\left(q^{-n}\right)$.

```c++
// An alternative implementation of this file.
template <typename Tp>
inline std::vector<Tp> inv_czt(const std::vector<Tp> &f, const Tp q) {
    if (f.empty()) return {};
    const int n = f.size();
    // prod_(i=0..(n-1))(x-q^i)
    auto rec = [q, iq = q.inv()](auto &&rec, int n) -> std::vector<Tp> {
        if (n == 0) return std::vector<Tp>{Tp(1)};
        if (n == 1) return std::vector<Tp>{Tp(-1), Tp(1)};
        const auto H   = rec(rec, n / 2);
        auto HH        = H;
        const auto qn  = q.pow(n / 2);
        const auto iqn = qn.inv();
        Tp qq          = q.pow((long long)(n / 2) * (n / 2));
        for (int i = 0; i <= n / 2; ++i) HH[i] *= qq, qq *= iqn;
        const auto res = convolution(H, HH);
        return (n & 1) ? convolution(res, std::vector<Tp>{-q.pow(n - 1), Tp(1)}) : res;
    };

    const auto M = rec(rec, n);
    auto C       = czt(deriv(M), q, n);
    for (int i = 0; i < n; ++i) C[i] = f[i] / C[i];
    C = czt(C, q.inv(), n, q.inv());
    for (int i = 0; i < n; ++i) C[i] = -C[i];
    auto res = convolution(M, C);
    res.resize(n);
    return res;
}
```

noshi91 showed that we could compute $M(x)$ and $M'(1),\dots ,M'(q^{n-1})$ faster. Let $s _ i:=\prod _ {j=1}^i\left(1-q^j\right)$ and $s _ 0 := 0$ followed by noshi91's definition. We have

$$
\begin{aligned}
\prod _ {0\leq j\lt n\atop j\neq i}\left(q^i-q^j\right)&=\left(\prod _ {j=0}^{i-1}\left(q^i-q^j\right)\right)\left(\prod _ {j=i+1}^{n-1}\left(q^i-q^j\right)\right) \\
&=\left(\prod _ {j=0}^{i-1}q^j\left(q^{i-j}-1\right)\right)\left(\prod _ {j=i+1}^{n-1}q^i\left(1-q^{j-i}\right)\right) \\
&=(-1)^iq^{\sum _ {j=0}^{i-1}j}\left(\prod _ {j=0}^{i-1}\left(1-q^{i-j}\right)\right)\cdot q^{i(n-i-1)}\left(\prod _ {j=i+1}^{n-1}\left(1-q^{j-i}\right)\right) \\
&=(-1)^iq^{\binom{i}{2}}\left(\prod _ {k=1}^{i}\left(1-q^k\right)\right)\cdot q^{i(n-i-1)}\left(\prod _ {k=1}^{n-i-1}\left(1-q^k\right)\right) \\
&=(-1)^iq^{\binom{i}{2}}s _ i\cdot q^{i(n-i-1)}s _ {n-i-1}
\end{aligned}
$$

note that $q^{\binom{i+1}{2}}\cdot q^{(i+1)(n-(i+1)-1)}=\left(q^{\binom{i}{2}}\cdot q^{i}\right)\left(q^{i(n-i-1)}\cdot q^{n-2i-2}\right)$. Now we only need to compute $M(x)$.

### $q$-analog

Let $n\in\mathbb{N}$, the $q$-analog of $n$ is defined by

$$
\left\lbrack n\right\rbrack _ q :=
\begin{cases}
0,&\text{if }n=0, \\
1+q+\cdots +q^{n-1},&\text{otherwise}.
\end{cases}
$$

note that $\left\lbrack n\right\rbrack _ q = n$ when $q = 1$. And $q\left\lbrack n\right\rbrack _ q =q+q^2+\cdots +q^n$, so

$$
\left\lbrack n\right\rbrack _ q=
\begin{cases}
n,&\text{if }q=1, \\
\frac{1-q^n}{1-q},&\text{otherwise}.
\end{cases}
$$

We could also findout that

$$
\begin{aligned}
\left\lbrack -n\right\rbrack _ q &=
\frac{1-q^{-n}}{1-q} \\
&= q^{-n}\frac{q^n-1}{1-q} \\
&= -q^{-n}\left\lbrack n\right\rbrack _ q
\end{aligned}
$$

Now we define the $q$-factorial

$$
n! _ q :=
\begin{cases}
1,&\text{if }n=0, \\
\left\lbrack 1\right\rbrack_q\left\lbrack 2\right\rbrack _ q\cdots \left\lbrack n\right\rbrack _ q,&\text{otherwise}.
\end{cases}
$$

Finally we could define the $q$-binomial coefficients

$$
\binom{n}{k} _ q :=
\begin{cases}
\frac{n! _ q}{k! _ q(n-k)! _ q},&\text{if }0\leq k\leq n, \\
0,&\text{otherwise}.
\end{cases}
$$

Before introducing the $q$-binomial theorem, let's show some common identities. If $q \neq 1$, we have

$$
\begin{aligned}
\left\lbrack n\right\rbrack _ q&=\frac{1-q^n}{1-q} \\
&=\frac{1-q^k+q^k-q^n}{1-q} \\
&=\frac{1-q^k}{1-q}+q^k\frac{1-q^{n-k}}{1-q} \\
&=\left\lbrack k\right\rbrack _ q +q^k\left\lbrack n-k\right\rbrack _ q
\end{aligned}
$$

which still works when $q = 1$ since $n = k + (n - k)$. We have

$$
\begin{aligned}
\binom{n+1}{k} _ q&=\frac{(n+1)! _ q}{k! _ q(n+1-k)! _ q} \\
&=\frac{n! _ q}{k! _ q(n+1-k)! _ q}\cdot \left(\left\lbrack k\right\rbrack _ q +q^k\left\lbrack n+1-k\right\rbrack _ q\right) \\
&=\frac{n! _ q}{(k-1)! _ q(n+1-k)! _ q}\cdot \left\lbrack k\right\rbrack _ q^{-1}\cdot \left(\left\lbrack k\right\rbrack _ q +q^k\left\lbrack n+1-k\right\rbrack _ q\right) \\
&=\frac{n! _ q}{(k-1)! _ q(n+1-k)! _ q}+q^k\frac{n! _ q\left\lbrack n+1-k\right\rbrack _ q}{k! _ q(n+1-k)! _ q} \\
&=\binom{n}{k-1} _ q+q^k\binom{n}{k} _ q
\end{aligned}
$$

Since $\binom{n}{k} _ q=\binom{n}{n-k} _ q$, we could replace $k$ by $n-k$ which gives

$$
\begin{aligned}
\binom{n+1}{k} _ q&=\binom{n+1}{n+1-k} _ q \\
&=\binom{n}{n-k} _ q+q^{n+1-k}\binom{n}{n+1-k} _ q \\
&=\binom{n}{k} _ q+q^{n-k+1}\binom{n}{k-1} _ q
\end{aligned}
$$

These are called the $q$-Pascal relation.

#### Rothe's $q$-binomial Theorem

For variable $q,a,x$, we have

$$
\prod _ {i=0}^{n-1}\left(a+q^ix\right) = \sum _ {k=0}^n\binom{n}{k} _ q q^{\binom{k}{2}}a^{n-k}x^k
$$

and LHS is defined to be $1$ when $n = 0$.

*Proof*: Let RHS equals $r_n(x,a)$, apply $q$-Pascal relation here, we have

$$
\begin{aligned}
r _ {n+1}(x,a)&=\sum _ {k=0}^{n+1}\binom{n+1}{k} _ q q^{\binom{k}{2}}x^ka^{n+1-k} \\
&=\sum _ {k=0}^{n+1}\left(\binom{n}{k-1} _ q+q^k\binom{n}{k} _ q\right)q^{\binom{k}{2}}x^ka^{n+1-k} \\
&=\left(\sum _ {k=1}^{n+1}\binom{n}{k-1} _ q q^{\binom{k}{2}}x^ka^{n+1-k}\right)+\left(\sum _ {k=0}^{n}\binom{n}{k} _ q q^{\binom{k}{2}}\left(qx\right)^ka^{n+1-k}\right) \\
&=\left(\sum _ {j=0}^{n}\binom{n}{j} _ qq^{\binom{j+1}{2}}x^{j+1}a^{n-j}\right)+\left(\sum _ {j=0}^{n}\binom{n}{j} _ q q^{\binom{j}{2}}\left(qx\right)^ja^{n+1-j}\right)
\end{aligned}
$$

Since $\binom{n}{-1} _ q = \binom{n}{n+1} _ q = 0$ and $\binom{j+1}{2}=\binom{j}{2}+j$ for $j\in\mathbb{N}$, we have

$$
\begin{aligned}
r _ {n+1}(x,a)&=\left(\sum _ {j=0}^{n}\binom{n}{j} _ q q^{\binom{j}{2}}q^jx^{j+1}a^{n-j}\right)+\left(\sum _ {j=0}^{n}\binom{n}{j} _ q q^{\binom{j}{2}}\left(qx\right)^ja^{n+1-j}\right) \\
&=\left(\sum _ {j=0}^{n}\binom{n}{j} _ q q^{\binom{j}{2}}\left(qx\right)^ja^{n-j}x\right)+\left(\sum _ {j=0}^{n}\binom{n}{j} _ q q^{\binom{j}{2}}\left(qx\right)^ja^{n+1-j}\right) \\
&=\sum _ {j=0}^{n}\binom{n}{j} _ q q^{\binom{j}{2}}\left(qx\right)^ja^{n-j}(x+a) \\
&=(a+x)r _ n(qx,a)
\end{aligned}
$$

By induction, we have

$$
\begin{aligned}
r _ {n+1}(x,a)&=(a+x)r _ n(qx,a) \\
&=(a+x)(a+qx)r_{n-1}\left(q^2x,a\right) \\
&=\cdots \\
&=(a+x)(a+qx)\cdots \left(a+q^nx\right)r _ 0\left(q^{n+1}x,a\right)
\end{aligned}
$$

and $r_0(u,v) = 1$ agrees with our definition.

Now back to our problem: Computing $M(x)$ mentioned above.

$$
\begin{aligned}
M(x)&=\prod _ {j=0}^{n-1}\left(x-q^j\right) \\
&=\sum _ {k=0}^n\binom{n}{k} _ q q^{\binom{k}{2}}(-1)^kx^{n-k}
\end{aligned}
$$

where

$$
\binom{n}{k} _ q=\frac{\left(1-q\right)\cdots \left(1-q^n\right)}{\left(1-q\right)\cdots \left(1-q^k\right)\cdot \left(1-q\right)\cdots \left(1-q^{n-k}\right)}=\frac{s _ n}{s _ k s _ {n-k}}
$$

Since $q^n \neq 1$ is not guaranteed, $M(0)$ should be computed separately.

## References

1. 37zigen. 多項式補間：アルゴリズム. url: <https://37zigen.com/lagrange-interpolation/>
2. noshi91. 標本点が等比数列を成す場合に補間多項式を計算するアルゴリズム. url: <https://noshi91.github.io/algorithm-encyclopedia/polynomial-interpolation-geometric>
3. Bostan, A. (2010). Fast algorithms for polynomials and matrices. JNCF 2010. Algorithms Project, INRIA. url: <https://specfun.inria.fr/bostan/publications/exposeJNCF.pdf>
4. Warren P. Johnson. An Introduction to $q$-analysis. American Mathematical Soc., 2020.
