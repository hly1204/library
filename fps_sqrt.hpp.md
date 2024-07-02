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
    path: rng.hpp
    title: rng.hpp
  - icon: ':heavy_check_mark:'
    path: semi_relaxed_conv.hpp
    title: semi_relaxed_conv.hpp
  - icon: ':heavy_check_mark:'
    path: sqrt_mod.hpp
    title: sqrt_mod.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
    title: test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"fps_sqrt.hpp\"\n\n#line 2 \"fps_basic.hpp\"\n\n#line 2 \"\
    binomial.hpp\"\n\n#include <algorithm>\n#include <vector>\n\ntemplate <typename\
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
    \ invfactorial_[n]; }\n};\n#line 2 \"semi_relaxed_conv.hpp\"\n\n#line 2 \"fft.hpp\"\
    \n\n#line 4 \"fft.hpp\"\n#include <cassert>\n#include <iterator>\n#include <memory>\n\
    #line 8 \"fft.hpp\"\n\ntemplate <typename Tp>\nclass FftInfo {\n    static Tp\
    \ least_quadratic_nonresidue() {\n        for (int i = 2;; ++i)\n            if\
    \ (Tp(i).pow((Tp::mod() - 1) / 2) == -1) return Tp(i);\n    }\n\n    const int\
    \ ordlog2_;\n    const Tp zeta_;\n    const Tp invzeta_;\n    const Tp imag_;\n\
    \    const Tp invimag_;\n\n    mutable std::vector<Tp> root_;\n    mutable std::vector<Tp>\
    \ invroot_;\n\n    FftInfo()\n        : ordlog2_(__builtin_ctzll(Tp::mod() - 1)),\n\
    \          zeta_(least_quadratic_nonresidue().pow((Tp::mod() - 1) >> ordlog2_)),\n\
    \          invzeta_(zeta_.inv()), imag_(zeta_.pow(1LL << (ordlog2_ - 2))), invimag_(-imag_),\n\
    \          root_{Tp(1), imag_}, invroot_{Tp(1), invimag_} {}\n\npublic:\n    static\
    \ const FftInfo &get() {\n        static FftInfo info;\n        return info;\n\
    \    }\n\n    Tp imag() const { return imag_; }\n    Tp inv_imag() const { return\
    \ invimag_; }\n    Tp zeta() const { return zeta_; }\n    Tp inv_zeta() const\
    \ { return invzeta_; }\n    const std::vector<Tp> &root(int n) const {\n     \
    \   // [0, n)\n        assert((n & (n - 1)) == 0);\n        if (const int s =\
    \ root_.size(); s < n) {\n            root_.resize(n);\n            for (int i\
    \ = __builtin_ctz(s); (1 << i) < n; ++i) {\n                const int j = 1 <<\
    \ i;\n                root_[j]    = zeta_.pow(1LL << (ordlog2_ - i - 2));\n  \
    \              for (int k = j + 1; k < j * 2; ++k) root_[k] = root_[k - j] * root_[j];\n\
    \            }\n        }\n        return root_;\n    }\n    const std::vector<Tp>\
    \ &inv_root(int n) const {\n        // [0, n)\n        assert((n & (n - 1)) ==\
    \ 0);\n        if (const int s = invroot_.size(); s < n) {\n            invroot_.resize(n);\n\
    \            for (int i = __builtin_ctz(s); (1 << i) < n; ++i) {\n           \
    \     const int j = 1 << i;\n                invroot_[j] = invzeta_.pow(1LL <<\
    \ (ordlog2_ - i - 2));\n                for (int k = j + 1; k < j * 2; ++k) invroot_[k]\
    \ = invroot_[k - j] * invroot_[j];\n            }\n        }\n        return invroot_;\n\
    \    }\n};\n\ninline int fft_len(int n) {\n    --n;\n    n |= n >> 1, n |= n >>\
    \ 2, n |= n >> 4, n |= n >> 8;\n    return (n | n >> 16) + 1;\n}\n\ntemplate <typename\
    \ Iterator>\ninline void fft_n(Iterator a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
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
    \    return convolution_fft(a, b);\n}\n#line 5 \"semi_relaxed_conv.hpp\"\n#include\
    \ <type_traits>\n#include <utility>\n#line 8 \"semi_relaxed_conv.hpp\"\n\n// returns\
    \ coefficients generated by closure\n// closure: gen(index, current_product)\n\
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
    \ o * e, 0);\n    return a;\n}\n#line 2 \"sqrt_mod.hpp\"\n\n#line 2 \"rng.hpp\"\
    \n\n#include <cstdint>\n#include <limits>\n\n// see: https://prng.di.unimi.it/xoshiro256starstar.c\n\
    // original license CC0 1.0\nclass xoshiro256starstar {\n    using u64 = std::uint64_t;\n\
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
    \ }\n    u64 operator()() { return next(); }\n};\n#line 4 \"sqrt_mod.hpp\"\n#include\
    \ <random>\n#line 6 \"sqrt_mod.hpp\"\n\ntemplate <typename Tp>\ninline std::vector<Tp>\
    \ sqrt_mod_prime(Tp a) {\n    // Bostan--Mori's algorithm\n    const auto p =\
    \ Tp::mod();\n    if (p == 2 || a == 0) return {a};\n    if (a.pow(p / 2) == -1)\
    \ return {};\n    if ((p & 3) == 3) {\n        const auto b = a.pow((p + 1) /\
    \ 4);\n        return {b, -b};\n    }\n    xoshiro256starstar rng(std::random_device{}());\n\
    \    std::uniform_int_distribution<std::decay_t<decltype(p)>> dis(2, p - 1);\n\
    \    Tp t;\n    do { t = dis(rng); } while ((t * t - a * 4).pow(p / 2) != -1);\n\
    \    Tp k0 = 1, k1, k2 = -t, k3 = a;\n    for (auto e = (p + 1) >> 1;;) {\n  \
    \      if (e & 1) {\n            k0 = k1 - k0 * k2, k1 *= k3;\n        } else\
    \ {\n            k1 = k0 * k3 - k1 * k2;\n        }\n        if ((e >>= 1) ==\
    \ 0) return {k0, -k0};\n        k2 = k3 + k3 - k2 * k2, k3 *= k3;\n    }\n}\n\
    #line 5 \"fps_sqrt.hpp\"\n#include <optional>\n#line 7 \"fps_sqrt.hpp\"\n\ntemplate\
    \ <typename Tp>\ninline std::optional<std::vector<Tp>> sqrt(const std::vector<Tp>\
    \ &a, int n) {\n    const int o = order(a);\n    if (o < 0) return std::vector<Tp>(n);\n\
    \    const auto cv = sqrt_mod_prime(a[o]);\n    if (cv.empty()) return {};\n \
    \   return sqrt_hint(a, n, cv[0]);\n}\n\ntemplate <typename Tp>\ninline std::optional<std::vector<Tp>>\
    \ sqrt_hint(const std::vector<Tp> &a, int n, Tp c) {\n    const int o = order(a);\n\
    \    if (o < 0) return std::vector<Tp>(n);\n    if ((o & 1) || c * c != a[o])\
    \ return {};\n    std::vector sqrta(a.begin() + o, a.end());\n    const auto iv\
    \ = sqrta[0].inv();\n    for (int i = 0; i < (int)sqrta.size(); ++i) sqrta[i]\
    \ *= iv;\n    sqrta = pow(sqrta, Tp(1).div_by_2().val(), n - o / 2);\n    for\
    \ (int i = 0; i < (int)sqrta.size(); ++i) sqrta[i] *= c;\n    sqrta.insert(sqrta.begin(),\
    \ o / 2, 0);\n    return sqrta;\n}\n"
  code: "#pragma once\n\n#include \"fps_basic.hpp\"\n#include \"sqrt_mod.hpp\"\n#include\
    \ <optional>\n#include <vector>\n\ntemplate <typename Tp>\ninline std::optional<std::vector<Tp>>\
    \ sqrt(const std::vector<Tp> &a, int n) {\n    const int o = order(a);\n    if\
    \ (o < 0) return std::vector<Tp>(n);\n    const auto cv = sqrt_mod_prime(a[o]);\n\
    \    if (cv.empty()) return {};\n    return sqrt_hint(a, n, cv[0]);\n}\n\ntemplate\
    \ <typename Tp>\ninline std::optional<std::vector<Tp>> sqrt_hint(const std::vector<Tp>\
    \ &a, int n, Tp c) {\n    const int o = order(a);\n    if (o < 0) return std::vector<Tp>(n);\n\
    \    if ((o & 1) || c * c != a[o]) return {};\n    std::vector sqrta(a.begin()\
    \ + o, a.end());\n    const auto iv = sqrta[0].inv();\n    for (int i = 0; i <\
    \ (int)sqrta.size(); ++i) sqrta[i] *= iv;\n    sqrta = pow(sqrta, Tp(1).div_by_2().val(),\
    \ n - o / 2);\n    for (int i = 0; i < (int)sqrta.size(); ++i) sqrta[i] *= c;\n\
    \    sqrta.insert(sqrta.begin(), o / 2, 0);\n    return sqrta;\n}\n"
  dependsOn:
  - fps_basic.hpp
  - binomial.hpp
  - semi_relaxed_conv.hpp
  - fft.hpp
  - sqrt_mod.hpp
  - rng.hpp
  isVerificationFile: false
  path: fps_sqrt.hpp
  requiredBy: []
  timestamp: '2024-06-02 13:23:25+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/formal_power_series/sqrt_of_formal_power_series.0.test.cpp
documentation_of: fps_sqrt.hpp
layout: document
redirect_from:
- /library/fps_sqrt.hpp
- /library/fps_sqrt.hpp.html
title: fps_sqrt.hpp
---