---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: binomial.hpp
    title: binomial.hpp
  - icon: ':heavy_check_mark:'
    path: fft.hpp
    title: fft.hpp
  - icon: ':heavy_check_mark:'
    path: fps_basic.hpp
    title: fps_basic.hpp
  - icon: ':heavy_check_mark:'
    path: poly.hpp
    title: poly.hpp
  - icon: ':heavy_check_mark:'
    path: poly_basic.hpp
    title: poly_basic.hpp
  - icon: ':heavy_check_mark:'
    path: random.hpp
    title: random.hpp
  - icon: ':heavy_check_mark:'
    path: rng.hpp
    title: rng.hpp
  - icon: ':heavy_check_mark:'
    path: semi_relaxed_conv.hpp
    title: semi_relaxed_conv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/matrix/sparse_matrix_det.0.test.cpp
    title: test/matrix/sparse_matrix_det.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"mat_sparse.hpp\"\n\n#line 2 \"poly.hpp\"\n\n#line 2 \"poly_basic.hpp\"\
    \n\n#line 2 \"binomial.hpp\"\n\n#include <algorithm>\n#include <vector>\n\ntemplate\
    \ <typename Tp>\nclass Binomial {\n    std::vector<Tp> factorial_, invfactorial_;\n\
    \n    Binomial() : factorial_{Tp(1)}, invfactorial_{Tp(1)} {}\n\n    void preprocess(int\
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
    \  return (n | n >> 16) + 1;\n}\n\ntemplate <typename Iterator>\ninline void fft_n(Iterator\
    \ a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
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
    \    return convolution_fft(a, b);\n}\n#line 2 \"fps_basic.hpp\"\n\n#line 2 \"\
    semi_relaxed_conv.hpp\"\n\n#line 5 \"semi_relaxed_conv.hpp\"\n#include <type_traits>\n\
    #include <utility>\n#line 8 \"semi_relaxed_conv.hpp\"\n\n// returns coefficients\
    \ generated by closure\n// closure: gen(index, current_product)\ntemplate <typename\
    \ Tp, typename Closure>\ninline std::enable_if_t<std::is_invocable_r_v<Tp, Closure,\
    \ int, const std::vector<Tp> &>,\n                        std::vector<Tp>>\nsemi_relaxed_convolution(const\
    \ std::vector<Tp> &A, Closure gen, int n) {\n    enum { BaseCaseSize = 32 };\n\
    \    static_assert((BaseCaseSize & (BaseCaseSize - 1)) == 0);\n\n    static const\
    \ int Block[]     = {16, 16, 16, 16, 16};\n    static const int BlockSize[] =\
    \ {\n        BaseCaseSize,\n        BaseCaseSize * Block[0],\n        BaseCaseSize\
    \ * Block[0] * Block[1],\n        BaseCaseSize * Block[0] * Block[1] * Block[2],\n\
    \        BaseCaseSize * Block[0] * Block[1] * Block[2] * Block[3],\n        BaseCaseSize\
    \ * Block[0] * Block[1] * Block[2] * Block[3] * Block[4],\n    };\n\n    // returns\
    \ (which_block, level)\n    auto blockinfo = [](int ind) {\n        int i = ind\
    \ / BaseCaseSize, lv = 0;\n        while ((i & (Block[lv] - 1)) == 0) i /= Block[lv++];\n\
    \        return std::make_pair(i & (Block[lv] - 1), lv);\n    };\n\n    std::vector<Tp>\
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
    \      fft(dftA[lv][j - 1]);\n                } else {\n                    dftA[lv].emplace_back(blocksize\
    \ * 2);\n                }\n            }\n\n            dftB[lv][j - 1].resize(blocksize\
    \ * 2);\n            std::copy_n(B.begin() + (i - blocksize), blocksize, dftB[lv][j\
    \ - 1].begin());\n            std::fill_n(dftB[lv][j - 1].begin() + blocksize,\
    \ blocksize, 0);\n            fft(dftB[lv][j - 1]);\n\n            // middle product\n\
    \            std::vector<Tp> mp(blocksize * 2);\n            for (int k = 0; k\
    \ < j; ++k)\n                for (int l = 0; l < blocksize * 2; ++l)\n       \
    \             mp[l] += dftA[lv][j - 1 - k][l] * dftB[lv][k][l];\n            inv_fft(mp);\n\
    \n            for (int k = 0; k < blocksize && i + k < n; ++k) AB[i + k] += mp[k\
    \ + blocksize];\n        }\n\n        // basecase contribution\n        for (int\
    \ j = std::max(i - s, i - (int)A.size() + 1); j < i; ++j) AB[i] += A[i - j] *\
    \ B[j];\n        B[i] = gen(i, AB);\n        if (!A.empty()) AB[i] += A[0] * B[i];\n\
    \    }\n\n    return B;\n}\n#line 7 \"fps_basic.hpp\"\n\ntemplate <typename Tp>\n\
    inline int order(const std::vector<Tp> &a) {\n    for (int i = 0; i < (int)a.size();\
    \ ++i)\n        if (a[i] != 0) return i;\n    return -1;\n}\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> inv(const std::vector<Tp> &a, int n) {\n    assert(!a.empty());\n\
    \    if (n <= 0) return {};\n    return semi_relaxed_convolution(\n        a,\
    \ [v = a[0].inv()](int n, auto &&c) { return n == 0 ? v : -c[n] * v; }, n);\n\
    }\n\ntemplate <typename Tp>\ninline std::vector<Tp> div(const std::vector<Tp>\
    \ &a, const std::vector<Tp> &b, int n) {\n    assert(!b.empty());\n    if (n <=\
    \ 0) return {};\n    return semi_relaxed_convolution(\n        b,\n        [&,\
    \ v = b[0].inv()](int n, auto &&c) {\n            if (n < (int)a.size()) return\
    \ (a[n] - c[n]) * v;\n            return -c[n] * v;\n        },\n        n);\n\
    }\n\ntemplate <typename Tp>\ninline std::vector<Tp> deriv(const std::vector<Tp>\
    \ &a) {\n    const int n = (int)a.size() - 1;\n    if (n <= 0) return {};\n  \
    \  std::vector<Tp> res(n);\n    for (int i = 1; i <= n; ++i) res[i - 1] = a[i]\
    \ * i;\n    return res;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> integr(const\
    \ std::vector<Tp> &a, Tp c = {}) {\n    const int n = a.size() + 1;\n    auto\
    \ &&bin  = Binomial<Tp>::get(n);\n    std::vector<Tp> res(n);\n    res[0] = c;\n\
    \    for (int i = 1; i < n; ++i) res[i] = a[i - 1] * bin.inv(i);\n    return res;\n\
    }\n\ntemplate <typename Tp>\ninline std::vector<Tp> log(const std::vector<Tp>\
    \ &a, int n) {\n    return integr(div(deriv(a), a, n - 1));\n}\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> exp(const std::vector<Tp> &a, int n) {\n    if (n\
    \ <= 0) return {};\n    assert(!a.empty() && a[0] == 0);\n    return semi_relaxed_convolution(\n\
    \        deriv(a),\n        [bin = Binomial<Tp>::get(n)](int n, auto &&c) {\n\
    \            return n == 0 ? Tp(1) : c[n - 1] * bin.inv(n);\n        },\n    \
    \    n);\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> pow(std::vector<Tp>\
    \ a, long long e, int n) {\n    if (n <= 0) return {};\n    if (e == 0) {\n  \
    \      std::vector<Tp> res(n);\n        res[0] = 1;\n        return res;\n   \
    \ }\n\n    const int o = order(a);\n    if (o < 0 || o > n / e || (o == n / e\
    \ && n % e == 0)) return std::vector<Tp>(n);\n    if (o != 0) a.erase(a.begin(),\
    \ a.begin() + o);\n\n    const Tp ia0 = a[0].inv();\n    const Tp a0e = a[0].pow(e);\n\
    \    const Tp me  = e;\n\n    for (int i = 0; i < (int)a.size(); ++i) a[i] *=\
    \ ia0;\n    a = log(a, n - o * e);\n    for (int i = 0; i < (int)a.size(); ++i)\
    \ a[i] *= me;\n    a = exp(a, n - o * e);\n    for (int i = 0; i < (int)a.size();\
    \ ++i) a[i] *= a0e;\n\n    a.insert(a.begin(), o * e, 0);\n    return a;\n}\n\
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
    \ (degQ < 60 || degB < 60) return euclidean_div_naive(A, B);\n\n    auto Q = div(std::vector(A.rend()\
    \ - (degA + 1), A.rend()),\n                 std::vector(B.rend() - (degB + 1),\
    \ B.rend()), degQ + 1);\n    std::reverse(Q.begin(), Q.end());\n\n    // returns\
    \ a mod (x^n-1)\n    auto make_cyclic = [](const std::vector<Tp> &a, int n) {\n\
    \        assert((n & (n - 1)) == 0);\n        std::vector<Tp> b(n);\n        for\
    \ (int i = 0; i < (int)a.size(); ++i) b[i & (n - 1)] += a[i];\n        return\
    \ b;\n    };\n\n    const int len      = fft_len(std::max(degB, 1));\n    const\
    \ auto cyclicA = make_cyclic(A, len);\n    auto cyclicB       = make_cyclic(B,\
    \ len);\n    auto cyclicQ       = make_cyclic(Q, len);\n\n    fft(cyclicQ);\n\
    \    fft(cyclicB);\n    for (int i = 0; i < len; ++i) cyclicQ[i] *= cyclicB[i];\n\
    \    inv_fft(cyclicQ);\n\n    // R = A - QB mod (x^n-1) (n >= degB)\n    std::vector<Tp>\
    \ R(degB);\n    for (int i = 0; i < degB; ++i) R[i] = cyclicA[i] - cyclicQ[i];\n\
    \    return {Q, R};\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> euclidean_div_quotient(const\
    \ std::vector<Tp> &A, const std::vector<Tp> &B) {\n    const int degA = degree(A);\n\
    \    const int degB = degree(B);\n    assert(degB >= 0);\n    // A = Q*B + R =>\
    \ A/B = Q + R/B in R((x^(-1)))\n    const int degQ = degA - degB;\n    if (degQ\
    \ < 0) return {Tp(0)};\n    if (std::min(degQ, degB) < 60) return euclidean_div_quotient_naive(A,\
    \ B);\n\n    auto Q = div(std::vector(A.rend() - (degA + 1), A.rend()),\n    \
    \             std::vector(B.rend() - (degB + 1), B.rend()), degQ + 1);\n    std::reverse(Q.begin(),\
    \ Q.end());\n    return Q;\n}\n#line 5 \"poly.hpp\"\n#include <array>\n#line 7\
    \ \"poly.hpp\"\n#include <iostream>\n#include <tuple>\n#line 11 \"poly.hpp\"\n\
    \ntemplate <typename Tp>\nclass Poly : public std::vector<Tp> {\n    using Base\
    \ = std::vector<Tp>;\n\npublic:\n    using Base::Base;\n\n    int deg() const\
    \ { return degree(*this); }\n\n    int ord() const { return order(*this); }\n\n\
    \    Poly rev() const {\n        const int d = deg();\n        Poly res(d + 1);\n\
    \        for (int i = d; i >= 0; --i) res[i] = Base::operator[](d - i);\n    \
    \    return res;\n    }\n\n    Poly slice(int L, int R) const {\n        Poly\
    \ res(R - L);\n        for (int i = L; i < std::min<int>(R, Base::size()); ++i)\
    \ res[i - L] = Base::operator[](i);\n        return res;\n    }\n\n    Poly trunc(int\
    \ D) const {\n        Poly res(D);\n        for (int i = 0; i < std::min<int>(D,\
    \ Base::size()); ++i) res[i] = Base::operator[](i);\n        return res;\n   \
    \ }\n\n    Poly &shrink() {\n        Base::resize(deg() + 1);\n        return\
    \ *this;\n    }\n\n    Tp lc() const {\n        const int d = deg();\n       \
    \ return d == -1 ? Tp() : Base::operator[](d);\n    }\n\n    Poly taylor_shift(Tp\
    \ c) const {\n        Base::operator=(taylor_shift(*this, c));\n        return\
    \ shrink();\n    }\n\n    Poly operator-() const {\n        const int d = deg();\n\
    \        Poly res(d + 1);\n        for (int i = 0; i <= d; ++i) res[i] = -Base::operator[](i);\n\
    \        res.shrink();\n        return res;\n    }\n\n    std::pair<Poly, Poly>\
    \ divmod(const Poly &R) const {\n        const auto [q, r] = euclidean_div(*this,\
    \ R);\n        return std::make_pair(Poly(q.begin(), q.end()), Poly(r.begin(),\
    \ r.end()));\n    }\n    Poly &operator+=(const Poly &R) {\n        if (Base::size()\
    \ < R.size()) Base::resize(R.size());\n        for (int i = 0; i < (int)R.size();\
    \ ++i) Base::operator[](i) += R[i];\n        return shrink();\n    }\n    Poly\
    \ &operator-=(const Poly &R) {\n        if (Base::size() < R.size()) Base::resize(R.size());\n\
    \        for (int i = 0; i < (int)R.size(); ++i) Base::operator[](i) -= R[i];\n\
    \        return shrink();\n    }\n    Poly &operator*=(const Poly &R) {\n    \
    \    Base::operator=(convolution(*this, R));\n        return shrink();\n    }\n\
    \    Poly &operator/=(const Poly &R) {\n        Base::operator=(euclidean_div_quotient(*this,\
    \ R));\n        return shrink();\n    }\n    Poly &operator%=(const Poly &R) {\n\
    \        Base::operator=(divmod(R).second);\n        return shrink();\n    }\n\
    \    Poly &operator<<=(int D) {\n        if (D > 0) {\n            Base::insert(Base::begin(),\
    \ D, Tp());\n        } else if (D < 0) {\n            if (-D < (int)Base::size())\
    \ {\n                Base::erase(Base::begin(), Base::begin() + (-D));\n     \
    \       } else {\n                Base::clear();\n            }\n        }\n \
    \       return shrink();\n    }\n    Poly &operator>>=(int D) { return operator<<=(-D);\
    \ }\n\n    friend Poly operator+(const Poly &L, const Poly &R) { return Poly(L)\
    \ += R; }\n    friend Poly operator-(const Poly &L, const Poly &R) { return Poly(L)\
    \ -= R; }\n    friend Poly operator*(const Poly &L, const Poly &R) { return Poly(L)\
    \ *= R; }\n    friend Poly operator/(const Poly &L, const Poly &R) { return Poly(L)\
    \ /= R; }\n    friend Poly operator%(const Poly &L, const Poly &R) { return Poly(L)\
    \ %= R; }\n    friend Poly operator<<(const Poly &L, int D) { return Poly(L) <<=\
    \ D; }\n    friend Poly operator>>(const Poly &L, int D) { return Poly(L) >>=\
    \ D; }\n\n    friend std::ostream &operator<<(std::ostream &L, const Poly &R)\
    \ {\n        L << '[';\n        const int d = R.deg();\n        if (d < 0) {\n\
    \            L << '0';\n        } else {\n            for (int i = 0; i <= d;\
    \ ++i) {\n                L << R[i];\n                if (i == 1) L << \"*x\"\
    ;\n                if (i > 1) L << \"*x^\" << i;\n                if (i != d)\
    \ L << \" + \";\n            }\n        }\n        return L << ']';\n    }\n};\n\
    \n// 2x2 matrix for Euclidean algorithm\ntemplate <typename Tp>\nclass GCDMatrix\
    \ : public std::array<std::array<Tp, 2>, 2> {\npublic:\n    GCDMatrix(const Tp\
    \ &x00, const Tp &x01, const Tp &x10, const Tp &x11)\n        : std::array<std::array<Tp,\
    \ 2>, 2>{std::array{x00, x01}, std::array{x10, x11}} {}\n\n    GCDMatrix operator*(const\
    \ GCDMatrix &R) const {\n        return {(*this)[0][0] * R[0][0] + (*this)[0][1]\
    \ * R[1][0],\n                (*this)[0][0] * R[0][1] + (*this)[0][1] * R[1][1],\n\
    \                (*this)[1][0] * R[0][0] + (*this)[1][1] * R[1][0],\n        \
    \        (*this)[1][0] * R[0][1] + (*this)[1][1] * R[1][1]};\n    }\n\n    std::array<Tp,\
    \ 2> operator*(const std::array<Tp, 2> &R) const {\n        return {(*this)[0][0]\
    \ * R[0] + (*this)[0][1] * R[1],\n                (*this)[1][0] * R[0] + (*this)[1][1]\
    \ * R[1]};\n    }\n\n    Tp det() const { return (*this)[0][0] * (*this)[1][1]\
    \ - (*this)[0][1] * (*this)[1][0]; }\n    GCDMatrix adj() const { return {(*this)[1][1],\
    \ -(*this)[0][1], -(*this)[1][0], (*this)[0][0]}; }\n};\n\n// returns M s.t. deg(M)\
    \ <= d and deg(M21*A+M22*B) < max(deg(A),deg(B))-d\n//                det(M) in\
    \ {-1,1}\n// see:\n// [1]: Daniel J. Bernstein. Fast multiplication and its applications.\n\
    template <typename Tp>\ninline GCDMatrix<Poly<Tp>> hgcd(const Poly<Tp> &A, const\
    \ Poly<Tp> &B, int d) {\n    using Mat = GCDMatrix<Poly<Tp>>;\n    assert(!(A.deg()\
    \ < 0 && B.deg() < 0));\n    if (A.deg() < B.deg()) return hgcd(B, A, d) * Mat({},\
    \ {Tp(1)}, {Tp(1)}, {});\n    if (A.deg() < d) return hgcd(A, B, A.deg());\n \
    \   if (B.deg() < A.deg() - d) return Mat({Tp(1)}, {}, {}, {Tp(1)});\n    if (int\
    \ dd = A.deg() - d * 2; dd > 0) return hgcd(A >> dd, B >> dd, d);\n    if (d ==\
    \ 0) return Mat({}, {Tp(1)}, {Tp(1)}, -(A / B));\n    const auto M = hgcd(A, B,\
    \ d / 2);\n    const auto D = M[1][0] * A + M[1][1] * B;\n    if (D.deg() < A.deg()\
    \ - d) return M;\n    const auto C      = M[0][0] * A + M[0][1] * B;\n    const\
    \ auto [Q, R] = C.divmod(D);\n    return hgcd(D, R, D.deg() - (A.deg() - d)) *\
    \ Mat({}, {Tp(1)}, {Tp(1)}, -Q) * M;\n}\n\ntemplate <typename Tp>\ninline std::tuple<Poly<Tp>,\
    \ Poly<Tp>, Poly<Tp>> xgcd(const Poly<Tp> &A, const Poly<Tp> &B) {\n    const\
    \ auto M = hgcd(A, B, std::max(A.deg(), B.deg()));\n    return std::make_tuple(M[0][0],\
    \ M[0][1], M[0][0] * A + M[0][1] * B);\n}\n\ntemplate <typename Tp>\ninline std::pair<Poly<Tp>,\
    \ Poly<Tp>> inv_gcd(const Poly<Tp> &A, const Poly<Tp> &B) {\n    const auto M\
    \ = hgcd(A, B, std::max(A.deg(), B.deg()));\n    return std::make_pair(M[0][0],\
    \ M[0][0] * A + M[0][1] * B);\n}\n\n// returns P,Q s.t. [x^([-k,-1])]P/Q=[x^([-k,-1])]A/B\n\
    // where P,Q in F[x], deg(Q) is minimized\n// requires deg(A)<deg(B)\ntemplate\
    \ <typename Tp>\ninline std::pair<Poly<Tp>, Poly<Tp>> rational_approximation(const\
    \ Poly<Tp> &A, const Poly<Tp> &B,\n                                          \
    \                  int k) {\n    auto M            = hgcd(B, A, k / 2);\n    const\
    \ auto [C, D] = M * std::array{B, A};\n    if (D.deg() >= 0 && D.deg() - C.deg()\
    \ >= -(k - (B.deg() - C.deg()) * 2))\n        M = GCDMatrix<Poly<Tp>>({}, {Tp(1)},\
    \ {Tp(1)}, -(C / D)) * M;\n    return std::make_pair(M.adj()[1][0], M.adj()[0][0]);\n\
    }\n\ntemplate <typename Tp>\ninline std::pair<Poly<Tp>, Poly<Tp>> rational_reconstruction(const\
    \ std::vector<Tp> &A) {\n    return rational_approximation(Poly<Tp>(A.rbegin(),\
    \ A.rend()), Poly<Tp>{Tp(1)} << A.size(),\n                                  A.size());\n\
    }\n\n// returns [x^([-k,-1])]A/B\n// requires deg(A)<deg(B)\ntemplate <typename\
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
    \ 8 \"mat_sparse.hpp\"\n\ntemplate <typename Tp>\nusing SparseMatrix = std::vector<std::tuple<int,\
    \ int, Tp>>;\n\ntemplate <typename Tp>\ninline std::vector<Tp> mat_apply(const\
    \ SparseMatrix<Tp> &A, const std::vector<Tp> &b) {\n    const int n = b.size();\n\
    \    std::vector<Tp> Ab(n);\n    for (auto &&[x, y, z] : A) Ab[x] += z * b[y];\n\
    \    return Ab;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> minpoly(const\
    \ SparseMatrix<Tp> &A, int n) {\n    const auto u = random_vector<Tp>(n);\n  \
    \  auto v       = random_vector<Tp>(n);\n    // u^T A^([0..2n)) v\n    std::vector<Tp>\
    \ proj(n * 2);\n    for (int i = 0; i < n * 2; v = mat_apply(A, v), ++i)\n   \
    \     for (int j = 0; j < n; ++j) proj[i] += u[j] * v[j];\n    const auto [P,\
    \ Q] = rational_reconstruction(proj);\n    assert(Q.deg() <= n);\n    return Q\
    \ / Poly<Tp>{Q.lc()};\n}\n\ntemplate <typename Tp>\ninline Tp det(SparseMatrix<Tp>\
    \ A, int n) {\n    const auto D = random_vector_without_zero<Tp>(n);\n    Tp detD\
    \      = 1;\n    for (int i = 0; i < n; ++i) detD *= D[i];\n    // preconditioner\
    \ D = diag(D[0], ..., D[n-1])\n    for (auto &&[x, y, z] : A) z *= D[x];\n   \
    \ return Tp((n & 1) ? -1 : 1) * minpoly(A, n).at(0) / detD;\n}\n"
  code: "#pragma once\n\n#include \"poly.hpp\"\n#include \"random.hpp\"\n#include\
    \ <cassert>\n#include <tuple>\n#include <vector>\n\ntemplate <typename Tp>\nusing\
    \ SparseMatrix = std::vector<std::tuple<int, int, Tp>>;\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> mat_apply(const SparseMatrix<Tp> &A, const std::vector<Tp>\
    \ &b) {\n    const int n = b.size();\n    std::vector<Tp> Ab(n);\n    for (auto\
    \ &&[x, y, z] : A) Ab[x] += z * b[y];\n    return Ab;\n}\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> minpoly(const SparseMatrix<Tp> &A, int n) {\n  \
    \  const auto u = random_vector<Tp>(n);\n    auto v       = random_vector<Tp>(n);\n\
    \    // u^T A^([0..2n)) v\n    std::vector<Tp> proj(n * 2);\n    for (int i =\
    \ 0; i < n * 2; v = mat_apply(A, v), ++i)\n        for (int j = 0; j < n; ++j)\
    \ proj[i] += u[j] * v[j];\n    const auto [P, Q] = rational_reconstruction(proj);\n\
    \    assert(Q.deg() <= n);\n    return Q / Poly<Tp>{Q.lc()};\n}\n\ntemplate <typename\
    \ Tp>\ninline Tp det(SparseMatrix<Tp> A, int n) {\n    const auto D = random_vector_without_zero<Tp>(n);\n\
    \    Tp detD      = 1;\n    for (int i = 0; i < n; ++i) detD *= D[i];\n    //\
    \ preconditioner D = diag(D[0], ..., D[n-1])\n    for (auto &&[x, y, z] : A) z\
    \ *= D[x];\n    return Tp((n & 1) ? -1 : 1) * minpoly(A, n).at(0) / detD;\n}\n"
  dependsOn:
  - poly.hpp
  - poly_basic.hpp
  - binomial.hpp
  - fft.hpp
  - fps_basic.hpp
  - semi_relaxed_conv.hpp
  - random.hpp
  - rng.hpp
  isVerificationFile: false
  path: mat_sparse.hpp
  requiredBy: []
  timestamp: '2024-10-10 23:07:33+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/matrix/sparse_matrix_det.0.test.cpp
documentation_of: mat_sparse.hpp
layout: document
redirect_from:
- /library/mat_sparse.hpp
- /library/mat_sparse.hpp.html
title: mat_sparse.hpp
---