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
    title: fft.hpp
  - icon: ':heavy_check_mark:'
    path: fps_basic.hpp
    title: fps_basic.hpp
  - icon: ':heavy_check_mark:'
    path: poly_basic.hpp
    title: poly_basic.hpp
  - icon: ':heavy_check_mark:'
    path: semi_relaxed_conv.hpp
    title: semi_relaxed_conv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
    title: test/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/multipoint_evaluation.0.test.cpp
    title: test/multipoint_evaluation.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/polynomial_interpolation.0.test.cpp
    title: test/polynomial_interpolation.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://noshi91.hatenablog.com/entry/2023/05/01/022946
  bundledCode: "#line 2 \"subproduct_tree.hpp\"\n\n#line 2 \"batch_inv.hpp\"\n\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ batch_inv(const std::vector<Tp> &a) {\n    if (a.empty()) return {};\n    const\
    \ int n = a.size();\n    std::vector<Tp> b(n);\n    Tp v = 1;\n    for (int i\
    \ = 0; i < n; ++i) b[i] = v, v *= a[i];\n    assert(v != 0);\n    v = v.inv();\n\
    \    for (int i = n - 1; i >= 0; --i) b[i] *= v, v *= a[i];\n    return b;\n}\n\
    #line 2 \"fft.hpp\"\n\n#include <algorithm>\n#line 5 \"fft.hpp\"\n#include <iterator>\n\
    #include <memory>\n#line 8 \"fft.hpp\"\n\ntemplate <typename Tp>\nclass FftInfo\
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
    binomial.hpp\"\n\n#line 5 \"binomial.hpp\"\n\ntemplate <typename Tp>\nclass Binomial\
    \ {\n    std::vector<Tp> factorial_, invfactorial_;\n\n    Binomial() : factorial_{Tp(1)},\
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
    \ }\n};\n#line 2 \"semi_relaxed_conv.hpp\"\n\n#line 5 \"semi_relaxed_conv.hpp\"\
    \n#include <type_traits>\n#include <utility>\n#line 8 \"semi_relaxed_conv.hpp\"\
    \n\n// returns coefficients generated by closure\n// closure: gen(index, current_product)\n\
    template <typename Tp, typename Closure>\ninline std::enable_if_t<std::is_invocable_r_v<Tp,\
    \ Closure, int, const std::vector<Tp> &>,\n                        std::vector<Tp>>\n\
    semi_relaxed_convolution(const std::vector<Tp> &A, Closure gen, int n) {\n   \
    \ enum { BaseCaseSize = 32 };\n    static_assert((BaseCaseSize & (BaseCaseSize\
    \ - 1)) == 0);\n\n    static const int Block[]     = {16, 16, 16, 16, 16};\n \
    \   static const int BlockSize[] = {\n        BaseCaseSize,\n        BaseCaseSize\
    \ * Block[0],\n        BaseCaseSize * Block[0] * Block[1],\n        BaseCaseSize\
    \ * Block[0] * Block[1] * Block[2],\n        BaseCaseSize * Block[0] * Block[1]\
    \ * Block[2] * Block[3],\n        BaseCaseSize * Block[0] * Block[1] * Block[2]\
    \ * Block[3] * Block[4],\n    };\n\n    // returns (which_block, level)\n    auto\
    \ blockinfo = [](int ind) {\n        int i = ind / BaseCaseSize, lv = 0;\n   \
    \     while ((i & (Block[lv] - 1)) == 0) i /= Block[lv++];\n        return std::make_pair(i\
    \ & (Block[lv] - 1), lv);\n    };\n\n    std::vector<Tp> B(n), AB(n);\n    std::vector<std::vector<std::vector<Tp>>>\
    \ dftA, dftB;\n\n    for (int i = 0; i < n; ++i) {\n        const int s = i &\
    \ (BaseCaseSize - 1);\n\n        // blocked contribution\n        if (i >= BaseCaseSize\
    \ && s == 0) {\n            const auto [j, lv]  = blockinfo(i);\n            const\
    \ int blocksize = BlockSize[lv];\n\n            if (blocksize * j == i) {\n  \
    \              if ((int)dftA.size() == lv) {\n                    dftA.emplace_back();\n\
    \                    dftB.emplace_back(Block[lv] - 1);\n                }\n  \
    \              if ((j - 1) * blocksize < (int)A.size()) {\n                  \
    \  dftA[lv]\n                        .emplace_back(A.begin() + (j - 1) * blocksize,\n\
    \                                      A.begin() + std::min((j + 1) * blocksize,\
    \ (int)A.size()))\n                        .resize(blocksize * 2);\n         \
    \           fft(dftA[lv][j - 1]);\n                } else {\n                \
    \    dftA[lv].emplace_back(blocksize * 2);\n                }\n            }\n\
    \n            dftB[lv][j - 1].resize(blocksize * 2);\n            std::copy_n(B.begin()\
    \ + (i - blocksize), blocksize, dftB[lv][j - 1].begin());\n            std::fill_n(dftB[lv][j\
    \ - 1].begin() + blocksize, blocksize, 0);\n            fft(dftB[lv][j - 1]);\n\
    \n            // middle product\n            std::vector<Tp> mp(blocksize * 2);\n\
    \            for (int k = 0; k < j; ++k)\n                for (int l = 0; l <\
    \ blocksize * 2; ++l)\n                    mp[l] += dftA[lv][j - 1 - k][l] * dftB[lv][k][l];\n\
    \            inv_fft(mp);\n\n            for (int k = 0; k < blocksize && i +\
    \ k < n; ++k) AB[i + k] += mp[k + blocksize];\n        }\n\n        // basecase\
    \ contribution\n        for (int j = std::max(i - s, i - (int)A.size() + 1); j\
    \ < i; ++j) AB[i] += A[i - j] * B[j];\n        B[i] = gen(i, AB);\n        if\
    \ (!A.empty()) AB[i] += A[0] * B[i];\n    }\n\n    return B;\n}\n#line 7 \"fps_basic.hpp\"\
    \n\ntemplate <typename Tp>\ninline int order(const std::vector<Tp> &a) {\n   \
    \ for (int i = 0; i < (int)a.size(); ++i)\n        if (a[i] != 0) return i;\n\
    \    return -1;\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> inv(const\
    \ std::vector<Tp> &a, int n) {\n    assert(!a.empty());\n    if (n <= 0) return\
    \ {};\n    return semi_relaxed_convolution(\n        a, [v = a[0].inv()](int n,\
    \ auto &&c) { return n == 0 ? v : -c[n] * v; }, n);\n}\n\ntemplate <typename Tp>\n\
    inline std::vector<Tp> div(const std::vector<Tp> &a, const std::vector<Tp> &b,\
    \ int n) {\n    assert(!b.empty());\n    if (n <= 0) return {};\n    return semi_relaxed_convolution(\n\
    \        b,\n        [&, v = b[0].inv()](int n, auto &&c) {\n            if (n\
    \ < (int)a.size()) return (a[n] - c[n]) * v;\n            return -c[n] * v;\n\
    \        },\n        n);\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ deriv(const std::vector<Tp> &a) {\n    const int n = (int)a.size() - 1;\n  \
    \  if (n <= 0) return {};\n    std::vector<Tp> res(n);\n    for (int i = 1; i\
    \ <= n; ++i) res[i - 1] = a[i] * i;\n    return res;\n}\n\ntemplate <typename\
    \ Tp>\ninline std::vector<Tp> integr(const std::vector<Tp> &a, Tp c = {}) {\n\
    \    const int n = a.size() + 1;\n    auto &&bin  = Binomial<Tp>::get(n);\n  \
    \  std::vector<Tp> res(n);\n    res[0] = c;\n    for (int i = 1; i < n; ++i) res[i]\
    \ = a[i - 1] * bin.inv(i);\n    return res;\n}\n\ntemplate <typename Tp>\ninline\
    \ std::vector<Tp> log(const std::vector<Tp> &a, int n) {\n    return integr(div(deriv(a),\
    \ a, n - 1));\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp> exp(const std::vector<Tp>\
    \ &a, int n) {\n    if (n <= 0) return {};\n    assert(!a.empty() && a[0] == 0);\n\
    \    return semi_relaxed_convolution(\n        deriv(a),\n        [bin = Binomial<Tp>::get(n)](int\
    \ n, auto &&c) {\n            return n == 0 ? Tp(1) : c[n - 1] * bin.inv(n);\n\
    \        },\n        n);\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ pow(std::vector<Tp> a, long long e, int n) {\n    if (n <= 0) return {};\n \
    \   if (e == 0) {\n        std::vector<Tp> res(n);\n        res[0] = 1;\n    \
    \    return res;\n    }\n\n    const int o = order(a);\n    if (o < 0 || o > n\
    \ / e || (o == n / e && n % e == 0)) return std::vector<Tp>(n);\n    if (o !=\
    \ 0) a.erase(a.begin(), a.begin() + o);\n\n    const Tp ia0 = a[0].inv();\n  \
    \  const Tp a0e = a[0].pow(e);\n    const Tp me  = e;\n\n    for (int i = 0; i\
    \ < (int)a.size(); ++i) a[i] *= ia0;\n    a = log(a, n - o * e);\n    for (int\
    \ i = 0; i < (int)a.size(); ++i) a[i] *= me;\n    a = exp(a, n - o * e);\n   \
    \ for (int i = 0; i < (int)a.size(); ++i) a[i] *= a0e;\n\n    a.insert(a.begin(),\
    \ o * e, 0);\n    return a;\n}\n#line 2 \"poly_basic.hpp\"\n\n#line 10 \"poly_basic.hpp\"\
    \n\ntemplate <typename Tp>\ninline int degree(const std::vector<Tp> &a) {\n  \
    \  int n = (int)a.size() - 1;\n    while (n >= 0 && a[n] == 0) --n;\n    return\
    \ n;\n}\n\ntemplate <typename Tp>\ninline void shrink(std::vector<Tp> &a) {\n\
    \    a.resize(degree(a) + 1);\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ taylor_shift(std::vector<Tp> a, Tp c) {\n    const int n = a.size();\n    auto\
    \ &&bin  = Binomial<Tp>::get(n);\n    for (int i = 0; i < n; ++i) a[i] *= bin.factorial(i);\n\
    \    Tp cc = 1;\n    std::vector<Tp> b(n);\n    for (int i = 0; i < n; ++i) {\n\
    \        b[i] = cc * bin.inv_factorial(i);\n        cc *= c;\n    }\n    std::reverse(a.begin(),\
    \ a.end());\n    auto ab = convolution(a, b);\n    ab.resize(n);\n    std::reverse(ab.begin(),\
    \ ab.end());\n    for (int i = 0; i < n; ++i) ab[i] *= bin.inv_factorial(i);\n\
    \    return ab;\n}\n\n// returns (quotient, remainder)\ntemplate <typename Tp>\n\
    inline std::pair<std::vector<Tp>, std::vector<Tp>> euclidean_div(const std::vector<Tp>\
    \ &A,\n                                                                 const\
    \ std::vector<Tp> &B) {\n    // returns a mod (x^n-1)\n    auto make_cyclic =\
    \ [](const std::vector<Tp> &a, int n) {\n        assert((n & (n - 1)) == 0);\n\
    \        std::vector<Tp> b(n);\n        for (int i = 0; i < (int)a.size(); ++i)\
    \ b[i & (n - 1)] += a[i];\n        return b;\n    };\n\n    const int degA = degree(A);\n\
    \    const int degB = degree(B);\n    assert(degB >= 0);\n    // A = Q*B + R =>\
    \ A/B = Q + R/B in R((x^(-1)))\n    const int degQ = degA - degB;\n    if (degQ\
    \ < 0) return {std::vector<Tp>{Tp(0)}, A};\n\n    auto Q = div(std::vector(A.rend()\
    \ - (degA + 1), A.rend()),\n                 std::vector(B.rend() - (degB + 1),\
    \ B.rend()), degQ + 1);\n    std::reverse(Q.begin(), Q.end());\n\n    const int\
    \ len      = fft_len(std::max(degB, 1));\n    const auto cyclicA = make_cyclic(A,\
    \ len);\n    auto cyclicB       = make_cyclic(B, len);\n    auto cyclicQ     \
    \  = make_cyclic(Q, len);\n\n    fft(cyclicQ);\n    fft(cyclicB);\n    for (int\
    \ i = 0; i < len; ++i) cyclicQ[i] *= cyclicB[i];\n    inv_fft(cyclicQ);\n\n  \
    \  // R = A - QB mod (x^n-1) (n >= degB)\n    std::vector<Tp> R(degB);\n    for\
    \ (int i = 0; i < degB; ++i) R[i] = cyclicA[i] - cyclicQ[i];\n    return {Q, R};\n\
    }\n\ntemplate <typename Tp>\ninline std::vector<Tp> euclidean_div_quotient(const\
    \ std::vector<Tp> &A, const std::vector<Tp> &B) {\n    const int degA = degree(A);\n\
    \    const int degB = degree(B);\n    assert(degB >= 0);\n    // A = Q*B + R =>\
    \ A/B = Q + R/B in R((x^(-1)))\n    const int degQ = degA - degB;\n    if (degQ\
    \ < 0) return {Tp(0)};\n\n    auto Q = div(std::vector(A.rend() - (degA + 1),\
    \ A.rend()),\n                 std::vector(B.rend() - (degB + 1), B.rend()), degQ\
    \ + 1);\n    std::reverse(Q.begin(), Q.end());\n    return Q;\n}\n#line 10 \"\
    subproduct_tree.hpp\"\n\ntemplate <typename Tp>\nclass SubproductTree {\npublic:\n\
    \    // LV=0   => T[0..S]  = DFT((x-X_0)..(x-X_(N-1))     mod (x^S     - 1))\n\
    \    //        => T[S..2S] = (x-X_0)..(x-X_(N-1))         mod (x^S     + 1)  (*\
    \ SPECIAL CASE)\n    // LV=1   => T[..]    = DFT((x-X_0)..(x-X_(S/2-1))   mod\
    \ (x^(S/2) - 1))\n    //        => T[..]    = DFT((x-X_(S/2))..(x-X_(N-1)) mod\
    \ (x^(S/2) - 1)) (* GENERAL CASE)\n    // LV=2.. => ..                       \
    \                                  (* GENERAL CASE)\n    std::vector<Tp> T;\n\
    \    int N;\n    int S;\n\n    explicit SubproductTree(const std::vector<Tp> &X)\n\
    \        : N(X.size()), S(N == 0 ? 2 : std::max(fft_len(N), 2)) {\n        int\
    \ LogS = 1;\n        while ((1 << LogS) < S) ++LogS;\n        T.assign((LogS +\
    \ 1) * S * 2, 1);\n        for (int i = 0; i < N; ++i) {\n            T[LogS *\
    \ S * 2 + i * 2]     = 1 - X[i];\n            T[LogS * S * 2 + i * 2 + 1] = -1\
    \ - X[i];\n        }\n        for (int lv = LogS - 1, len = 2; lv >= 0; --lv,\
    \ len *= 2) {\n            for (int i = 0; i < (1 << lv); ++i) {\n           \
    \     auto C = T.begin() + (lv * S * 2 + i * len * 2);       // current\n    \
    \            auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child\n\
    \                for (int j = 0; j < len; ++j) C[j] = C[len + j] = L[j] * L[len\
    \ + j];\n                inv_fft_n(C + len, len);\n                if ((i + 1)\
    \ * len <= N) C[len] -= 2;\n                if (lv) {\n                    Tp\
    \ k         = 1;\n                    const auto t = FftInfo<Tp>::get().root(len).at(len\
    \ / 2);\n                    for (int j = 0; j < len; ++j) C[len + j] *= k, k\
    \ *= t;\n                    fft_n(C + len, len);\n                }\n       \
    \     }\n        }\n    }\n\n    std::vector<Tp> product() const {\n        std::vector\
    \ res(T.begin() + S, T.begin() + S * 2);\n        if (N == S) {\n            res[0]\
    \ += 1;\n            res.emplace_back(1);\n        }\n        res.resize(N + 1);\n\
    \        return res;\n    }\n\n    // see:\n    // [1]: A. Bostan, Gr\xE9goire\
    \ Lecerf, \xC9. Schost. Tellegen's principle into practice.\n    // [2]: D. Bernstein.\
    \ SCALED REMAINDER TREES.\n    std::vector<Tp> evaluation(const std::vector<Tp>\
    \ &F) const {\n        const int degF = degree(F);\n        const auto P   = product();\n\
    \        // find coefficients of x^(-1),...,x^(-N) of F/P in R((x^(-1)))\n   \
    \     auto res = div(std::vector(F.rend() - (degF + 1), F.rend()),\n         \
    \              std::vector(P.rbegin(), P.rend()), degF + 1);\n        if (degF\
    \ >= N) res.erase(res.begin(), res.begin() + (degF - N + 1));\n        std::reverse(res.begin(),\
    \ res.end());\n        res.resize(N);\n        res.insert(res.begin(), S - N,\
    \ 0); // res[S-1]=[x^(-1)]F/P, res[S-2]=[x^(-2)]F/P, ...\n        for (int lv\
    \ = 0, len = S; (1 << lv) < S; ++lv, len /= 2) {\n            std::vector<Tp>\
    \ LL(len);\n            for (int i = 0; i < (1 << lv); ++i) {\n              \
    \  auto C = res.begin() + i * len;                        // current\n       \
    \         auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child\n\
    \                fft_n(C, len);\n                for (int j = 0; j < len; ++j)\
    \ LL[j] = C[j] * L[len + j], C[j] *= L[j];\n                inv_fft(LL);\n   \
    \             inv_fft_n(C, len);\n                std::copy_n(LL.begin() + len\
    \ / 2, len / 2, C);\n            }\n        }\n        res.resize(N);\n      \
    \  return res;\n    }\n\n    std::vector<Tp> interpolation(const std::vector<Tp>\
    \ &Y) const {\n        assert((int)Y.size() == N);\n        const auto invD =\
    \ batch_inv(evaluation(deriv(product()))); // denominator => P'(x_i)\n       \
    \ std::vector<Tp> res(S * 2);\n        for (int i = 0; i < N; ++i) res[i * 2]\
    \ = res[i * 2 + 1] = Y[i] * invD[i];\n        int LogS = 1;\n        while ((1\
    \ << LogS) < S) ++LogS;\n        for (int lv = LogS - 1, len = 2; lv >= 0; --lv,\
    \ len *= 2) {\n            for (int i = 0; i < (1 << lv); ++i) {\n           \
    \     auto C = res.begin() + i * len * 2;                    // current\n    \
    \            auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child\n\
    \                for (int j = 0; j < len; ++j)\n                    C[j] = C[len\
    \ + j] = C[j] * L[len + j] + C[len + j] * L[j];\n                inv_fft_n(C +\
    \ len, len);\n                if (lv) {\n                    Tp k         = 1;\n\
    \                    const auto t = FftInfo<Tp>::get().root(len).at(len / 2);\n\
    \                    for (int j = 0; j < len; ++j) C[len + j] *= k, k *= t;\n\
    \                    fft_n(C + len, len);\n                }\n            }\n\
    \        }\n        return std::vector(res.begin() + S, res.begin() + (S + N));\n\
    \    }\n\n    // see:\n    // [1]: A. Bostan, \xC9. Schost. Polynomial evaluation\
    \ and interpolation on special sets of points.\n    // [2]: noshi91. \u8EE2\u7F6E\
    \u539F\u7406\u306A\u3057\u3067 Monomial \u57FA\u5E95\u304B\u3089 Newton \u57FA\
    \u5E95\u3078\u306E\u5909\u63DB.\n    //      https://noshi91.hatenablog.com/entry/2023/05/01/022946\n\
    \    std::vector<Tp> monomial_to_newton(const std::vector<Tp> &F) const {\n  \
    \      const int degF = degree(F);\n        assert(degF < N);\n        const auto\
    \ P = product();\n        // find coefficients of x^(-1),...,x^(-N) of F/P in\
    \ R((x^(-1)))\n        auto res = div(std::vector(F.rend() - (degF + 1), F.rend()),\n\
    \                       std::vector(P.rbegin(), P.rend()), degF + 1);\n      \
    \  std::reverse(res.begin(), res.end());\n        res.resize(N);\n        res.insert(res.begin(),\
    \ S - N, 0); // res[S-1]=[x^(-1)]F/P, res[S-2]=[x^(-2)]F/P, ...\n        for (int\
    \ lv = 0, len = S; (1 << lv) < S; ++lv, len /= 2) {\n            std::vector<Tp>\
    \ RR(len / 2);\n            for (int i = 0; i < (1 << lv); ++i) {\n          \
    \      auto C = res.begin() + i * len;                              // current\n\
    \                auto R = T.begin() + ((lv + 1) * S * 2 + (i * 2 + 1) * len);\
    \ // right child\n                std::copy_n(C + len / 2, len / 2, RR.begin());\n\
    \                fft_n(C, len);\n                for (int j = 0; j < len; ++j)\
    \ C[j] *= R[j];\n                inv_fft_n(C, len);\n                std::copy_n(C\
    \ + len / 2, len / 2, C);\n                std::copy_n(RR.begin(), len / 2, C\
    \ + len / 2);\n            }\n        }\n        res.resize(N);\n        return\
    \ res;\n    }\n\n    std::vector<Tp> newton_to_monomial(const std::vector<Tp>\
    \ &F) const {\n        const int degF = degree(F);\n        assert(degF < N);\n\
    \        std::vector<Tp> res(S * 2);\n        for (int i = 0; i <= degF; ++i)\
    \ res[i * 2] = res[i * 2 + 1] = F[i];\n        int LogS = 1;\n        while ((1\
    \ << LogS) < S) ++LogS;\n        for (int lv = LogS - 1, len = 2; lv >= 0; --lv,\
    \ len *= 2) {\n            for (int i = 0; i < (1 << lv); ++i) {\n           \
    \     auto C = res.begin() + i * len * 2;                    // current\n    \
    \            auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child\n\
    \                for (int j = 0; j < len; ++j) C[j] = C[len + j] = C[j] + C[len\
    \ + j] * L[j];\n                inv_fft_n(C + len, len);\n                if (lv)\
    \ {\n                    Tp k         = 1;\n                    const auto t =\
    \ FftInfo<Tp>::get().root(len).at(len / 2);\n                    for (int j =\
    \ 0; j < len; ++j) C[len + j] *= k, k *= t;\n                    fft_n(C + len,\
    \ len);\n                }\n            }\n        }\n        return std::vector(res.begin()\
    \ + S, res.begin() + (S + N));\n    }\n};\n"
  code: "#pragma once\n\n#include \"batch_inv.hpp\"\n#include \"fft.hpp\"\n#include\
    \ \"fps_basic.hpp\"\n#include \"poly_basic.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <vector>\n\ntemplate <typename Tp>\nclass SubproductTree\
    \ {\npublic:\n    // LV=0   => T[0..S]  = DFT((x-X_0)..(x-X_(N-1))     mod (x^S\
    \     - 1))\n    //        => T[S..2S] = (x-X_0)..(x-X_(N-1))         mod (x^S\
    \     + 1)  (* SPECIAL CASE)\n    // LV=1   => T[..]    = DFT((x-X_0)..(x-X_(S/2-1))\
    \   mod (x^(S/2) - 1))\n    //        => T[..]    = DFT((x-X_(S/2))..(x-X_(N-1))\
    \ mod (x^(S/2) - 1)) (* GENERAL CASE)\n    // LV=2.. => ..                   \
    \                                      (* GENERAL CASE)\n    std::vector<Tp> T;\n\
    \    int N;\n    int S;\n\n    explicit SubproductTree(const std::vector<Tp> &X)\n\
    \        : N(X.size()), S(N == 0 ? 2 : std::max(fft_len(N), 2)) {\n        int\
    \ LogS = 1;\n        while ((1 << LogS) < S) ++LogS;\n        T.assign((LogS +\
    \ 1) * S * 2, 1);\n        for (int i = 0; i < N; ++i) {\n            T[LogS *\
    \ S * 2 + i * 2]     = 1 - X[i];\n            T[LogS * S * 2 + i * 2 + 1] = -1\
    \ - X[i];\n        }\n        for (int lv = LogS - 1, len = 2; lv >= 0; --lv,\
    \ len *= 2) {\n            for (int i = 0; i < (1 << lv); ++i) {\n           \
    \     auto C = T.begin() + (lv * S * 2 + i * len * 2);       // current\n    \
    \            auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child\n\
    \                for (int j = 0; j < len; ++j) C[j] = C[len + j] = L[j] * L[len\
    \ + j];\n                inv_fft_n(C + len, len);\n                if ((i + 1)\
    \ * len <= N) C[len] -= 2;\n                if (lv) {\n                    Tp\
    \ k         = 1;\n                    const auto t = FftInfo<Tp>::get().root(len).at(len\
    \ / 2);\n                    for (int j = 0; j < len; ++j) C[len + j] *= k, k\
    \ *= t;\n                    fft_n(C + len, len);\n                }\n       \
    \     }\n        }\n    }\n\n    std::vector<Tp> product() const {\n        std::vector\
    \ res(T.begin() + S, T.begin() + S * 2);\n        if (N == S) {\n            res[0]\
    \ += 1;\n            res.emplace_back(1);\n        }\n        res.resize(N + 1);\n\
    \        return res;\n    }\n\n    // see:\n    // [1]: A. Bostan, Gr\xE9goire\
    \ Lecerf, \xC9. Schost. Tellegen's principle into practice.\n    // [2]: D. Bernstein.\
    \ SCALED REMAINDER TREES.\n    std::vector<Tp> evaluation(const std::vector<Tp>\
    \ &F) const {\n        const int degF = degree(F);\n        const auto P   = product();\n\
    \        // find coefficients of x^(-1),...,x^(-N) of F/P in R((x^(-1)))\n   \
    \     auto res = div(std::vector(F.rend() - (degF + 1), F.rend()),\n         \
    \              std::vector(P.rbegin(), P.rend()), degF + 1);\n        if (degF\
    \ >= N) res.erase(res.begin(), res.begin() + (degF - N + 1));\n        std::reverse(res.begin(),\
    \ res.end());\n        res.resize(N);\n        res.insert(res.begin(), S - N,\
    \ 0); // res[S-1]=[x^(-1)]F/P, res[S-2]=[x^(-2)]F/P, ...\n        for (int lv\
    \ = 0, len = S; (1 << lv) < S; ++lv, len /= 2) {\n            std::vector<Tp>\
    \ LL(len);\n            for (int i = 0; i < (1 << lv); ++i) {\n              \
    \  auto C = res.begin() + i * len;                        // current\n       \
    \         auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child\n\
    \                fft_n(C, len);\n                for (int j = 0; j < len; ++j)\
    \ LL[j] = C[j] * L[len + j], C[j] *= L[j];\n                inv_fft(LL);\n   \
    \             inv_fft_n(C, len);\n                std::copy_n(LL.begin() + len\
    \ / 2, len / 2, C);\n            }\n        }\n        res.resize(N);\n      \
    \  return res;\n    }\n\n    std::vector<Tp> interpolation(const std::vector<Tp>\
    \ &Y) const {\n        assert((int)Y.size() == N);\n        const auto invD =\
    \ batch_inv(evaluation(deriv(product()))); // denominator => P'(x_i)\n       \
    \ std::vector<Tp> res(S * 2);\n        for (int i = 0; i < N; ++i) res[i * 2]\
    \ = res[i * 2 + 1] = Y[i] * invD[i];\n        int LogS = 1;\n        while ((1\
    \ << LogS) < S) ++LogS;\n        for (int lv = LogS - 1, len = 2; lv >= 0; --lv,\
    \ len *= 2) {\n            for (int i = 0; i < (1 << lv); ++i) {\n           \
    \     auto C = res.begin() + i * len * 2;                    // current\n    \
    \            auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child\n\
    \                for (int j = 0; j < len; ++j)\n                    C[j] = C[len\
    \ + j] = C[j] * L[len + j] + C[len + j] * L[j];\n                inv_fft_n(C +\
    \ len, len);\n                if (lv) {\n                    Tp k         = 1;\n\
    \                    const auto t = FftInfo<Tp>::get().root(len).at(len / 2);\n\
    \                    for (int j = 0; j < len; ++j) C[len + j] *= k, k *= t;\n\
    \                    fft_n(C + len, len);\n                }\n            }\n\
    \        }\n        return std::vector(res.begin() + S, res.begin() + (S + N));\n\
    \    }\n\n    // see:\n    // [1]: A. Bostan, \xC9. Schost. Polynomial evaluation\
    \ and interpolation on special sets of points.\n    // [2]: noshi91. \u8EE2\u7F6E\
    \u539F\u7406\u306A\u3057\u3067 Monomial \u57FA\u5E95\u304B\u3089 Newton \u57FA\
    \u5E95\u3078\u306E\u5909\u63DB.\n    //      https://noshi91.hatenablog.com/entry/2023/05/01/022946\n\
    \    std::vector<Tp> monomial_to_newton(const std::vector<Tp> &F) const {\n  \
    \      const int degF = degree(F);\n        assert(degF < N);\n        const auto\
    \ P = product();\n        // find coefficients of x^(-1),...,x^(-N) of F/P in\
    \ R((x^(-1)))\n        auto res = div(std::vector(F.rend() - (degF + 1), F.rend()),\n\
    \                       std::vector(P.rbegin(), P.rend()), degF + 1);\n      \
    \  std::reverse(res.begin(), res.end());\n        res.resize(N);\n        res.insert(res.begin(),\
    \ S - N, 0); // res[S-1]=[x^(-1)]F/P, res[S-2]=[x^(-2)]F/P, ...\n        for (int\
    \ lv = 0, len = S; (1 << lv) < S; ++lv, len /= 2) {\n            std::vector<Tp>\
    \ RR(len / 2);\n            for (int i = 0; i < (1 << lv); ++i) {\n          \
    \      auto C = res.begin() + i * len;                              // current\n\
    \                auto R = T.begin() + ((lv + 1) * S * 2 + (i * 2 + 1) * len);\
    \ // right child\n                std::copy_n(C + len / 2, len / 2, RR.begin());\n\
    \                fft_n(C, len);\n                for (int j = 0; j < len; ++j)\
    \ C[j] *= R[j];\n                inv_fft_n(C, len);\n                std::copy_n(C\
    \ + len / 2, len / 2, C);\n                std::copy_n(RR.begin(), len / 2, C\
    \ + len / 2);\n            }\n        }\n        res.resize(N);\n        return\
    \ res;\n    }\n\n    std::vector<Tp> newton_to_monomial(const std::vector<Tp>\
    \ &F) const {\n        const int degF = degree(F);\n        assert(degF < N);\n\
    \        std::vector<Tp> res(S * 2);\n        for (int i = 0; i <= degF; ++i)\
    \ res[i * 2] = res[i * 2 + 1] = F[i];\n        int LogS = 1;\n        while ((1\
    \ << LogS) < S) ++LogS;\n        for (int lv = LogS - 1, len = 2; lv >= 0; --lv,\
    \ len *= 2) {\n            for (int i = 0; i < (1 << lv); ++i) {\n           \
    \     auto C = res.begin() + i * len * 2;                    // current\n    \
    \            auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child\n\
    \                for (int j = 0; j < len; ++j) C[j] = C[len + j] = C[j] + C[len\
    \ + j] * L[j];\n                inv_fft_n(C + len, len);\n                if (lv)\
    \ {\n                    Tp k         = 1;\n                    const auto t =\
    \ FftInfo<Tp>::get().root(len).at(len / 2);\n                    for (int j =\
    \ 0; j < len; ++j) C[len + j] *= k, k *= t;\n                    fft_n(C + len,\
    \ len);\n                }\n            }\n        }\n        return std::vector(res.begin()\
    \ + S, res.begin() + (S + N));\n    }\n};\n"
  dependsOn:
  - batch_inv.hpp
  - fft.hpp
  - fps_basic.hpp
  - binomial.hpp
  - semi_relaxed_conv.hpp
  - poly_basic.hpp
  isVerificationFile: false
  path: subproduct_tree.hpp
  requiredBy: []
  timestamp: '2024-06-16 14:16:14+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/multipoint_evaluation.0.test.cpp
  - test/conversion_from_monomial_basis_to_newton_basis.0.test.cpp
  - test/polynomial_interpolation.0.test.cpp
documentation_of: subproduct_tree.hpp
layout: document
redirect_from:
- /library/subproduct_tree.hpp
- /library/subproduct_tree.hpp.html
title: subproduct_tree.hpp
---