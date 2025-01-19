---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: batch_inv.hpp
    title: batch_inv.hpp
  - icon: ':question:'
    path: binomial.hpp
    title: binomial.hpp
  - icon: ':question:'
    path: fft.hpp
    title: FFT
  - icon: ':heavy_check_mark:'
    path: middle_product.hpp
    title: Middle Product
  - icon: ':heavy_check_mark:'
    path: swag.hpp
    title: swag.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/enumerative_combinatorics/factorial.0.test.cpp
    title: test/enumerative_combinatorics/factorial.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/shift_of_sampling_points_of_polynomial.1.test.cpp
    title: test/formal_power_series/shift_of_sampling_points_of_polynomial.1.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"shift_sample_points.hpp\"\n\n#line 2 \"batch_inv.hpp\"\n\
    \n#include <cassert>\n#include <vector>\n\ntemplate<typename Tp> inline std::vector<Tp>\
    \ batch_inv(const std::vector<Tp> &a) {\n    if (a.empty()) return {};\n    const\
    \ int n = a.size();\n    std::vector<Tp> b(n);\n    Tp v = 1;\n    for (int i\
    \ = 0; i < n; ++i) b[i] = v, v *= a[i];\n    assert(v != 0);\n    v = v.inv();\n\
    \    for (int i = n - 1; i >= 0; --i) b[i] *= v, v *= a[i];\n    return b;\n}\n\
    #line 2 \"binomial.hpp\"\n\n#include <algorithm>\n#line 5 \"binomial.hpp\"\n\n\
    template<typename Tp> class Binomial {\n    std::vector<Tp> factorial_, invfactorial_;\n\
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
    \ invfactorial_[n]; }\n};\n#line 2 \"middle_product.hpp\"\n\n#line 2 \"fft.hpp\"\
    \n\n#line 5 \"fft.hpp\"\n#include <iterator>\n#include <memory>\n#line 8 \"fft.hpp\"\
    \n\ntemplate<typename Tp> class FftInfo {\n    static Tp least_quadratic_nonresidue()\
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
    \  return (n | n >> 16) + 1;\n}\n\nnamespace detail {\n\ntemplate<typename Iterator>\
    \ inline void\nbutterfly_n(Iterator a, int n,\n            const std::vector<typename\
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
    \          }\n        }\n    }\n}\n\ntemplate<typename Iterator> inline void\n\
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
    \ A(x) |-> bit-reversed order of [A(1), A(zeta_n), ..., A(zeta_n^(n-1))]\ntemplate<typename\
    \ Iterator> inline void fft_n(Iterator a, int n) {\n    using Tp = typename std::iterator_traits<Iterator>::value_type;\n\
    \    detail::butterfly_n(a, n, FftInfo<Tp>::get().root(n / 2));\n}\n\ntemplate<typename\
    \ Tp> inline void fft(std::vector<Tp> &a) { fft_n(a.begin(), a.size()); }\n\n\
    // IFFT_n: bit-reversed order of [A(1), A(zeta_n), ..., A(zeta_n^(n-1))] |-> A(x)\n\
    template<typename Iterator> inline void inv_fft_n(Iterator a, int n) {\n    using\
    \ Tp = typename std::iterator_traits<Iterator>::value_type;\n    detail::inv_butterfly_n(a,\
    \ n, FftInfo<Tp>::get().inv_root(n / 2));\n    const Tp iv = Tp::mod() - (Tp::mod()\
    \ - 1) / n;\n    for (int i = 0; i < n; ++i) a[i] *= iv;\n}\n\ntemplate<typename\
    \ Tp> inline void inv_fft(std::vector<Tp> &a) { inv_fft_n(a.begin(), a.size());\
    \ }\n\n// IFFT_n^T: A(x) |-> 1/n FFT_n((x^n A(x^(-1))) mod (x^n - 1))\ntemplate<typename\
    \ Iterator> inline void transposed_inv_fft_n(Iterator a, int n) {\n    using Tp\
    \    = typename std::iterator_traits<Iterator>::value_type;\n    const Tp iv =\
    \ Tp::mod() - (Tp::mod() - 1) / n;\n    for (int i = 0; i < n; ++i) a[i] *= iv;\n\
    \    detail::butterfly_n(a, n, FftInfo<Tp>::get().inv_root(n / 2));\n}\n\ntemplate<typename\
    \ Tp> inline void transposed_inv_fft(std::vector<Tp> &a) {\n    transposed_inv_fft_n(a.begin(),\
    \ a.size());\n}\n\n// FFT_n^T : FFT_n((x^n A(x^(-1))) mod (x^n - 1)) |-> n A(x)\n\
    template<typename Iterator> inline void transposed_fft_n(Iterator a, int n) {\n\
    \    using Tp = typename std::iterator_traits<Iterator>::value_type;\n    detail::inv_butterfly_n(a,\
    \ n, FftInfo<Tp>::get().root(n / 2));\n}\n\ntemplate<typename Tp> inline void\
    \ transposed_fft(std::vector<Tp> &a) {\n    transposed_fft_n(a.begin(), a.size());\n\
    }\n\ntemplate<typename Tp> inline std::vector<Tp> convolution_fft(std::vector<Tp>\
    \ a, std::vector<Tp> b) {\n    if (a.empty() || b.empty()) return {};\n    const\
    \ int n   = a.size();\n    const int m   = b.size();\n    const int len = fft_len(n\
    \ + m - 1);\n    a.resize(len);\n    b.resize(len);\n    fft(a);\n    fft(b);\n\
    \    for (int i = 0; i < len; ++i) a[i] *= b[i];\n    inv_fft(a);\n    a.resize(n\
    \ + m - 1);\n    return a;\n}\n\ntemplate<typename Tp> inline std::vector<Tp>\
    \ square_fft(std::vector<Tp> a) {\n    if (a.empty()) return {};\n    const int\
    \ n   = a.size();\n    const int len = fft_len(n * 2 - 1);\n    a.resize(len);\n\
    \    fft(a);\n    for (int i = 0; i < len; ++i) a[i] *= a[i];\n    inv_fft(a);\n\
    \    a.resize(n * 2 - 1);\n    return a;\n}\n\ntemplate<typename Tp>\ninline std::vector<Tp>\
    \ convolution_naive(const std::vector<Tp> &a, const std::vector<Tp> &b) {\n  \
    \  if (a.empty() || b.empty()) return {};\n    const int n = a.size();\n    const\
    \ int m = b.size();\n    std::vector<Tp> res(n + m - 1);\n    for (int i = 0;\
    \ i < n; ++i)\n        for (int j = 0; j < m; ++j) res[i + j] += a[i] * b[j];\n\
    \    return res;\n}\n\ntemplate<typename Tp>\ninline std::vector<Tp> convolution(const\
    \ std::vector<Tp> &a, const std::vector<Tp> &b) {\n    if (std::min(a.size(),\
    \ b.size()) < 60) return convolution_naive(a, b);\n    if (std::addressof(a) ==\
    \ std::addressof(b)) return square_fft(a);\n    return convolution_fft(a, b);\n\
    }\n#line 7 \"middle_product.hpp\"\n\n// see:\n// [1]: Guillaume Hanrot, Michel\
    \ Quercia, Paul Zimmermann. The Middle Product Algorithm I.\n// [2]: Alin Bostan,\
    \ Gr\xE9goire Lecerf, \xC9ric Schost. Tellegen's principle into practice.\n\n\
    template<typename Tp>\ninline std::vector<Tp> middle_product_naive(const std::vector<Tp>\
    \ &f, const std::vector<Tp> &g) {\n    const int m = f.size();\n    const int\
    \ n = g.size();\n    assert(m >= n);\n    std::vector<Tp> res(m - n + 1);\n  \
    \  for (int i = n - 1; i < m; ++i)\n        for (int j = i - (n - 1); j <= i;\
    \ ++j) res[i - (n - 1)] += f[j] * g[i - j];\n    return res;\n}\n\ntemplate<typename\
    \ Tp>\ninline std::vector<Tp> middle_product_fft(std::vector<Tp> f, std::vector<Tp>\
    \ g) {\n    const int m = f.size();\n    const int n = g.size();\n    assert(m\
    \ >= n);\n    std::reverse(g.begin(), g.end());\n    const int len = fft_len(m);\n\
    \    f.resize(len);\n    g.resize(len);\n    transposed_inv_fft(f);\n    fft(g);\n\
    \    for (int i = 0; i < len; ++i) f[i] *= g[i];\n    transposed_fft(f);\n   \
    \ f.resize(m - n + 1);\n    return f;\n}\n\n// returns (fg)_(n-1),...,(fg)_(m-1)\n\
    // f: f_0 + ... + f_(m-1)x^(m-1)\n// g: g_0 + ... + g_(n-1)x^(n-1)\n// requires\
    \ m >= n\ntemplate<typename Tp>\ninline std::vector<Tp> middle_product(const std::vector<Tp>\
    \ &f, const std::vector<Tp> &g) {\n    assert(f.size() >= g.size());\n    if (f.size()\
    \ < 60) return middle_product_naive(f, g);\n    return middle_product_fft(f, g);\n\
    }\n#line 2 \"swag.hpp\"\n\n#line 4 \"swag.hpp\"\n#include <cstddef>\n#include\
    \ <optional>\n#include <stack>\n#include <type_traits>\n#line 9 \"swag.hpp\"\n\
    \n// see: https://www.hirzels.com/martin/papers/debs17-tutorial.pdf\n// requires:\
    \ Op(Op(A,B),C) = Op(A,Op(B,C))\ntemplate<typename Tp, typename Op,\n        \
    \ std::enable_if_t<std::is_invocable_r_v<Tp, Op, const Tp &, const Tp &>, int>\
    \ = 0>\nclass SWAG {\npublic:\n    Op F;\n    std::stack<Tp, std::vector<Tp>>\
    \ Front, Back;\n    std::optional<Tp> Agg;\n\n    explicit SWAG(Op F) : F(F) {}\n\
    \    bool empty() const { return Front.empty() && Back.empty(); }\n    std::size_t\
    \ size() const { return Front.size() + Back.size(); }\n    void push_back(const\
    \ Tp &v) {\n        Back.push(v);\n        Agg.emplace(Agg ? F(*Agg, v) : v);\n\
    \    }\n    void pop_front() {\n        assert(!empty());\n        if (Front.empty())\
    \ {\n            Front.push(Back.top());\n            Back.pop();\n          \
    \  while (!Back.empty()) {\n                Front.push(F(Back.top(), Front.top()));\n\
    \                Back.pop();\n            }\n            Agg.reset();\n      \
    \  }\n        Front.pop();\n    }\n\n    // returns F(...F(F(Q[0],Q[1]),Q[2]),...,Q[N-1])\n\
    \    std::optional<Tp> query() const {\n        if (empty()) return {};\n    \
    \    if (Front.empty()) return Agg;\n        if (!Agg) return Front.top();\n \
    \       return F(Front.top(), *Agg);\n    }\n};\n#line 8 \"shift_sample_points.hpp\"\
    \n#include <functional>\n#line 10 \"shift_sample_points.hpp\"\n\ntemplate<typename\
    \ Tp>\ninline std::vector<Tp> shift_sample_points(const std::vector<Tp> &f, Tp\
    \ c, int m) {\n    if (f.empty()) return std::vector<Tp>(m);\n    assert(m > 0);\n\
    \    const int n = f.size();\n    auto &&bin  = Binomial<Tp>::get(n);\n    std::vector<Tp>\
    \ F(n), G(n + m - 1);\n    for (int i = 0; i < n; ++i) {\n        F[i] = f[i]\
    \ * bin.inv_factorial(i) * bin.inv_factorial(n - 1 - i);\n        if ((n - 1 -\
    \ i) & 1) F[i] = -F[i];\n    }\n    for (int i = 0; i < n + m - 1; ++i) {\n  \
    \      const auto v = c + (i - (n - 1));\n        // We don't care about G[i]\
    \ when v = 0.\n        // We assigned 1 for G[i] when v = 0 for calling batch_inv().\n\
    \        G[i] = (v == 0) ? Tp(1) : v;\n    }\n    auto res = middle_product(batch_inv(G),\
    \ F);\n    SWAG<Tp, std::multiplies<>> P(std::multiplies<>{});\n    // P = c!/(c-n)!\
    \ = prod[-n < i <= 0](c + i)\n    for (int i = -n + 1; i <= 0; ++i) P.push_back(c\
    \ + i);\n    // res[i] <- (c+i)!/(c+i-n)! * res[i]\n    for (int i = 0; i < m;\
    \ ++i) {\n        if (i) P.pop_front(), P.push_back(c + i);\n        const auto\
    \ v = P.query().value();\n        // 0 <= c+i < n iff (c+i)!/(c+i-n)! = 0\n  \
    \      res[i] = (v == 0) ? f[(c + i).val()] : v * res[i];\n    }\n    return res;\n\
    }\n"
  code: "#pragma once\n\n#include \"batch_inv.hpp\"\n#include \"binomial.hpp\"\n#include\
    \ \"middle_product.hpp\"\n#include \"swag.hpp\"\n#include <cassert>\n#include\
    \ <functional>\n#include <vector>\n\ntemplate<typename Tp>\ninline std::vector<Tp>\
    \ shift_sample_points(const std::vector<Tp> &f, Tp c, int m) {\n    if (f.empty())\
    \ return std::vector<Tp>(m);\n    assert(m > 0);\n    const int n = f.size();\n\
    \    auto &&bin  = Binomial<Tp>::get(n);\n    std::vector<Tp> F(n), G(n + m -\
    \ 1);\n    for (int i = 0; i < n; ++i) {\n        F[i] = f[i] * bin.inv_factorial(i)\
    \ * bin.inv_factorial(n - 1 - i);\n        if ((n - 1 - i) & 1) F[i] = -F[i];\n\
    \    }\n    for (int i = 0; i < n + m - 1; ++i) {\n        const auto v = c +\
    \ (i - (n - 1));\n        // We don't care about G[i] when v = 0.\n        //\
    \ We assigned 1 for G[i] when v = 0 for calling batch_inv().\n        G[i] = (v\
    \ == 0) ? Tp(1) : v;\n    }\n    auto res = middle_product(batch_inv(G), F);\n\
    \    SWAG<Tp, std::multiplies<>> P(std::multiplies<>{});\n    // P = c!/(c-n)!\
    \ = prod[-n < i <= 0](c + i)\n    for (int i = -n + 1; i <= 0; ++i) P.push_back(c\
    \ + i);\n    // res[i] <- (c+i)!/(c+i-n)! * res[i]\n    for (int i = 0; i < m;\
    \ ++i) {\n        if (i) P.pop_front(), P.push_back(c + i);\n        const auto\
    \ v = P.query().value();\n        // 0 <= c+i < n iff (c+i)!/(c+i-n)! = 0\n  \
    \      res[i] = (v == 0) ? f[(c + i).val()] : v * res[i];\n    }\n    return res;\n\
    }\n"
  dependsOn:
  - batch_inv.hpp
  - binomial.hpp
  - middle_product.hpp
  - fft.hpp
  - swag.hpp
  isVerificationFile: false
  path: shift_sample_points.hpp
  requiredBy: []
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/enumerative_combinatorics/factorial.0.test.cpp
  - test/formal_power_series/shift_of_sampling_points_of_polynomial.1.test.cpp
documentation_of: shift_sample_points.hpp
layout: document
title: Shift Sample Points
---

## Shift via Lagrange Interpolation

Given sample points $f(0), f(1), \dots ,f(n - 1)$ of polynomial $f \in \mathbb{C}\left\lbrack x\right\rbrack$ with $\deg f \lt n$, we want to compute $f(c), f(c + 1), \dots, f(c + m - 1)$ for $c \in \mathbb{Z}, m \in \mathbb{N}$.

Recall the Lagrange interpolation formula,

$$
\begin{aligned}
f(x) &= \sum _ {0 \leq i \lt n}\left(f(i) \prod _ {0 \leq j \lt n \atop j \neq i} \frac{x - j}{i - j}\right) \\
&= \sum _ {0 \leq i \lt n}\left(f(i)\frac{\prod _ {0 \leq j \lt n \atop j \neq i}\left(x - j\right)}{\prod _ {0 \leq j \lt n \atop j \neq i}\left(i - j\right)}\right) \\
&= \sum _ {0 \leq i \lt n}\left(f(i)\frac{x!}{(x - n)!(x - i)}\frac{(-1)^{n - 1 - i}}{i!(n - 1 - i)!}\right) \\
&= \frac{x!}{(x - n)!}\sum _ {0 \leq i \lt n}\left(f(i)\frac{1}{x - i}\frac{(-1)^{n - 1 - i}}{i!(n - 1 - i)!}\right)
\end{aligned}
$$

Let

$$
\begin{aligned}
F(x) &:= \sum _ {0 \leq i \lt n}\frac{f(i)(-1)^{n - 1 - i}}{i!(n - 1 - i)!}x^i, \\
G(x) &:= \sum _ {i \geq 0}\frac{1}{c - (n - 1) + i}x^i
\end{aligned}
$$

now we have

$$
\begin{aligned}
\left\lbrack x^{n - 1 + t}\right\rbrack\left(F(x)G(x)\right) &= \sum _ {i = 0}^{n - 1 + t}\left(\left(\left\lbrack x^i\right\rbrack F(x)\right)\left(\left\lbrack x^{n - 1 + t - i}\right\rbrack G(x)\right)\right) \\
&= \sum _ {i = 0}^{n - 1}\left(\frac{f(i)(-1)^{n - 1 - i}}{i!(n - 1 - i)!}\frac{1}{c + t - i}\right) \\
&= \frac{(c + t - n)!}{(c + t)!} f(c + t)
\end{aligned}
$$

for $t = 0, 1, \dots, m - 1$. We should handle the case that $c - (n - 1) + i = 0$ for a certain $i$.

## Shift via O.g.f.

Let

$$
F(x) := \sum _ {i \geq 0}f(i)x^i \in \mathbb{C}\left\lbrack\left\lbrack x\right\rbrack\right\rbrack
$$

We have $F(x) = \frac{P(x)}{(1 - x)^n}$ where $P(x) \in \mathbb{C}\left\lbrack x\right\rbrack _ {\lt n}$.

And the negative binomial coefficients are

$$
\begin{aligned}
\frac{1}{(1 - x)^n} &= (1 - x)^{-n} \\
&= \sum _ {k \geq 0}\binom{-n}{k}x^k \\
&= \sum _ {k \geq 0}\frac{(-n)(-n - 1)\cdots (-n - (k - 1))}{k!}x^k \\
&= \sum _ {k \geq 0}(-1)^k\frac{(n + k - 1)!}{(n - 1)!k!}x^k \\
&= \sum _ {k \geq 0}(-1)^k\binom{n + k - 1}{k}x^k
\end{aligned}
$$

But we are not able to compute $(-n)(-n - 1)\cdots (-n - (k - 1))$ and $k!$ fast if $k$ is large.

## Shift via Falling Factorial Polynomial

Might in another document.
