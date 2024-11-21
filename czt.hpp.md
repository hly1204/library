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
    \    return convolution_fft(a, b);\n}\n#line 6 \"middle_product.hpp\"\n\n// see:\n\
    // [1]: Guillaume Hanrot, Michel Quercia, Paul Zimmermann. The Middle Product\
    \ Algorithm I.\n// [2]: Alin Bostan, Gr\xE9goire Lecerf, \xC9ric Schost. Tellegen's\
    \ principle into practice.\n\n// returns (fg)_(n-1),...,(fg)_(m-1)\n// f: f_0\
    \ + ... + f_(m-1)x^(m-1)\n// g: g_0 + ... + g_(n-1)x^(n-1)\n// m >= n\ntemplate\
    \ <typename Tp>\ninline std::vector<Tp> middle_product(std::vector<Tp> f, std::vector<Tp>\
    \ g) {\n    const int m = f.size();\n    const int n = g.size();\n    assert(m\
    \ >= n);\n    const int len = fft_len(m);\n    f.resize(len);\n    g.resize(len);\n\
    \    fft(f);\n    fft(g);\n    for (int i = 0; i < len; ++i) f[i] *= g[i];\n \
    \   inv_fft(f);\n    f.erase(f.begin(), f.begin() + (n - 1));\n    f.resize(m\
    \ - n + 1);\n    return f;\n}\n#line 2 \"poly_basic.hpp\"\n\n#line 2 \"binomial.hpp\"\
    \n\n#line 5 \"binomial.hpp\"\n\ntemplate <typename Tp>\nclass Binomial {\n   \
    \ std::vector<Tp> factorial_, invfactorial_;\n\n    Binomial() : factorial_{Tp(1)},\
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
    \ }\n};\n#line 2 \"fps_basic.hpp\"\n\n#line 2 \"semi_relaxed_conv.hpp\"\n\n#line\
    \ 5 \"semi_relaxed_conv.hpp\"\n#include <type_traits>\n#include <utility>\n#line\
    \ 8 \"semi_relaxed_conv.hpp\"\n\ntemplate <typename Tp, typename Closure>\ninline\
    \ std::enable_if_t<std::is_invocable_r_v<Tp, Closure, int, const std::vector<Tp>\
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
    \ blocksize, 0);\n                fft(dftB[lv][j - 1]);\n\n                //\
    \ middle product\n                std::vector<Tp> mp(blocksize * 2);\n       \
    \         for (int k = 0; k < std::min<int>(j, dftA[lv].size()); ++k)\n      \
    \              for (int l = 0; l < blocksize * 2; ++l)\n                     \
    \   mp[l] += dftA[lv][k][l] * dftB[lv][j - 1 - k][l];\n                inv_fft(mp);\n\
    \n                for (int k = 0; k < blocksize && i + k < n; ++k) AB[i + k] +=\
    \ mp[k + blocksize];\n            }\n        }\n\n        // basecase contribution\n\
    \        for (int j = std::max(i - s, i - (int)A.size() + 1); j < i; ++j) AB[i]\
    \ += A[i - j] * B[j];\n        B[i] = gen(i, AB);\n        if (!A.empty()) AB[i]\
    \ += A[0] * B[i];\n    }\n\n    return B;\n}\n#line 7 \"fps_basic.hpp\"\n\ntemplate\
    \ <typename Tp>\ninline int order(const std::vector<Tp> &a) {\n    for (int i\
    \ = 0; i < (int)a.size(); ++i)\n        if (a[i] != 0) return i;\n    return -1;\n\
    }\n\ntemplate <typename Tp>\ninline std::vector<Tp> inv(const std::vector<Tp>\
    \ &a, int n) {\n    assert(!a.empty());\n    if (n <= 0) return {};\n    return\
    \ semi_relaxed_convolution(\n        a, [v = a[0].inv()](int n, auto &&c) { return\
    \ n == 0 ? v : -c[n] * v; }, n);\n}\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ div(const std::vector<Tp> &a, const std::vector<Tp> &b, int n) {\n    assert(!b.empty());\n\
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
    \ Q.end());\n    return Q;\n}\n#line 8 \"czt.hpp\"\n\n// returns F(a),F(ac),F(ac^2),...,F(ac^(n-1))\n\
    // Use        ij = binom(i,2)   + binom(-j,2) - binom(i-j,2)\n// instead of ij\
    \ = binom(i+j,2) - binom(i,2)  - binom(j,2)\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ czt(std::vector<Tp> F, Tp c, int n, Tp a = 1) {\n    if (n <= 0) return {};\n\
    \    const int degF = degree(F);\n    shrink(F);\n    if (degF < 0) return std::vector<Tp>(n);\n\
    \    if (degF == 0 || a == 0) return std::vector<Tp>(n, F[0]);\n    if (a != 1)\
    \ {\n        // F(x) <- F(ax)\n        Tp aa = 1;\n        for (int i = 0; i <=\
    \ degF; ++i) F[i] *= aa, aa *= a;\n    }\n    if (c == 0) {\n        std::vector<Tp>\
    \ res(n, F[0]);\n        for (int i = 1; i <= degF; ++i) res[0] += F[i];\n   \
    \     return res;\n    }\n\n    std::vector<Tp> H(std::max(degF + 1, n - 1));\n\
    \    Tp cc = H[0] = 1;\n    for (int i = 1; i < (int)H.size(); ++i) H[i] = H[i\
    \ - 1] * (cc *= c);\n    std::vector<Tp> G(degF + n); // G[i+degF]=c^(-binom(i,2))\n\
    \    auto GG     = G.begin() + degF;\n    const Tp ic = c.inv();\n    cc = GG[0]\
    \ = 1;\n    for (int i = 1; i < n; ++i) GG[i] = GG[i - 1] * cc, cc *= ic;\n  \
    \  cc = 1;\n    for (int i = -1; i >= -degF; --i) GG[i] = GG[i + 1] * (cc *= ic);\n\
    \n    // F[i] <- c^(binom(i+1,2))*F[i]\n    for (int i = 0; i <= degF; ++i) F[i]\
    \ *= H[i];\n\n    F = middle_product(G, F);\n\n    // F[i] <- c^(binom(i,2))*F[i]\n\
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
    \              = 1;\n    // M[i]=qbinom(n,i)*q^(binom(i,2))*(-1)^i\n    for (int\
    \ i = 1; i < n; ++i) M[n - i] = Sn * invS[i] * invS[n - i] * (qq *= -Q[i - 1]);\n\
    \    M[0] = qq * -Q[n - 1]; // in case of q^n=1\n    // D[i]=S[i]*S[n-i-1]*q^(binom(i,2)+i(n-i-1))*(-1)^i\n\
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
    \    }\n\n    std::vector<Tp> H(std::max(degF + 1, n - 1));\n    Tp cc = H[0]\
    \ = 1;\n    for (int i = 1; i < (int)H.size(); ++i) H[i] = H[i - 1] * (cc *= c);\n\
    \    std::vector<Tp> G(degF + n); // G[i+degF]=c^(-binom(i,2))\n    auto GG  \
    \   = G.begin() + degF;\n    const Tp ic = c.inv();\n    cc = GG[0] = 1;\n   \
    \ for (int i = 1; i < n; ++i) GG[i] = GG[i - 1] * cc, cc *= ic;\n    cc = 1;\n\
    \    for (int i = -1; i >= -degF; --i) GG[i] = GG[i + 1] * (cc *= ic);\n\n   \
    \ // F[i] <- c^(binom(i+1,2))*F[i]\n    for (int i = 0; i <= degF; ++i) F[i] *=\
    \ H[i];\n\n    F = middle_product(G, F);\n\n    // F[i] <- c^(binom(i,2))*F[i]\n\
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
    \              = 1;\n    // M[i]=qbinom(n,i)*q^(binom(i,2))*(-1)^i\n    for (int\
    \ i = 1; i < n; ++i) M[n - i] = Sn * invS[i] * invS[n - i] * (qq *= -Q[i - 1]);\n\
    \    M[0] = qq * -Q[n - 1]; // in case of q^n=1\n    // D[i]=S[i]*S[n-i-1]*q^(binom(i,2)+i(n-i-1))*(-1)^i\n\
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
  timestamp: '2024-11-20 23:45:47+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/formal_power_series/multipoint_evaluation_on_geometric_sequence.0.test.cpp
  - test/formal_power_series/polynomial_interpolation_on_geometric_sequence.0.test.cpp
  - test/convolution/convolution_mod.1.test.cpp
documentation_of: czt.hpp
layout: document
redirect_from:
- /library/czt.hpp
- /library/czt.hpp.html
title: czt.hpp
---
