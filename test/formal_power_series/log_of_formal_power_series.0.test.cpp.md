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
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':question:'
    path: semi_relaxed_conv.hpp
    title: semi_relaxed_conv.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/log_of_formal_power_series
    links:
    - https://judge.yosupo.jp/problem/log_of_formal_power_series
  bundledCode: "#line 1 \"test/formal_power_series/log_of_formal_power_series.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/log_of_formal_power_series\"\
    \n\n#line 2 \"fps_basic.hpp\"\n\n#line 2 \"binomial.hpp\"\n\n#include <algorithm>\n\
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
    \    assert((n & (n - 1)) == 0);\n    auto &&root = FftInfo<Tp>::get().root(n\
    \ / 2);\n    for (int i = n; i >= 2; i /= 2) {\n        for (int k = 0; k < i\
    \ / 2; ++k) {\n            const auto u = a[k], v = a[k + i / 2];\n          \
    \  a[k] = u + v, a[k + i / 2] = u - v;\n        }\n        for (int j = i, m =\
    \ 1; j < n; j += i, ++m)\n            for (int k = j; k < j + i / 2; ++k) {\n\
    \                const auto u = a[k], v = a[k + i / 2] * root[m];\n          \
    \      a[k] = u + v, a[k + i / 2] = u - v;\n            }\n    }\n}\n\ntemplate\
    \ <typename Tp>\ninline void fft(std::vector<Tp> &a) {\n    fft_n(a.begin(), a.size());\n\
    }\n\ntemplate <typename Iterator>\ninline void inv_fft_n(Iterator a, int n) {\n\
    \    using Tp = typename std::iterator_traits<Iterator>::value_type;\n    assert((n\
    \ & (n - 1)) == 0);\n    auto &&root = FftInfo<Tp>::get().inv_root(n / 2);\n \
    \   for (int i = 2; i <= n; i *= 2) {\n        for (int j = 0; j < i / 2; ++j)\
    \ {\n            const auto u = a[j], v = a[j + i / 2];\n            a[j] = u\
    \ + v, a[j + i / 2] = u - v;\n        }\n        for (int j = i, m = 1; j < n;\
    \ j += i, ++m)\n            for (int k = j; k < j + i / 2; ++k) {\n          \
    \      const auto u = a[k], v = a[k + i / 2];\n                a[k] = u + v, a[k\
    \ + i / 2] = (u - v) * root[m];\n            }\n    }\n    const Tp iv = Tp::mod()\
    \ - (Tp::mod() - 1) / n;\n    for (int i = 0; i < n; ++i) a[i] *= iv;\n}\n\ntemplate\
    \ <typename Tp>\ninline void inv_fft(std::vector<Tp> &a) {\n    inv_fft_n(a.begin(),\
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
    }\n#line 5 \"semi_relaxed_conv.hpp\"\n#include <type_traits>\n#include <utility>\n\
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
    #line 2 \"modint.hpp\"\n\n#include <iostream>\n#line 5 \"modint.hpp\"\n\ntemplate\
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
    #line 7 \"test/formal_power_series/log_of_formal_power_series.0.test.cpp\"\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = ModInt<998244353>;\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ a(n);\n    for (int i = 0; i < n; ++i) std::cin >> a[i];\n    const auto loga\
    \ = log(a, n);\n    for (int i = 0; i < n; ++i) std::cout << loga[i] << ' ';\n\
    \    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/log_of_formal_power_series\"\
    \n\n#include \"fps_basic.hpp\"\n#include \"modint.hpp\"\n#include <iostream>\n\
    #include <vector>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n   \
    \ std::cin.tie(nullptr);\n    using mint = ModInt<998244353>;\n    int n;\n  \
    \  std::cin >> n;\n    std::vector<mint> a(n);\n    for (int i = 0; i < n; ++i)\
    \ std::cin >> a[i];\n    const auto loga = log(a, n);\n    for (int i = 0; i <\
    \ n; ++i) std::cout << loga[i] << ' ';\n    return 0;\n}\n"
  dependsOn:
  - fps_basic.hpp
  - binomial.hpp
  - semi_relaxed_conv.hpp
  - fft.hpp
  - modint.hpp
  isVerificationFile: true
  path: test/formal_power_series/log_of_formal_power_series.0.test.cpp
  requiredBy: []
  timestamp: '2024-12-01 23:46:11+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/formal_power_series/log_of_formal_power_series.0.test.cpp
layout: document
redirect_from:
- /verify/test/formal_power_series/log_of_formal_power_series.0.test.cpp
- /verify/test/formal_power_series/log_of_formal_power_series.0.test.cpp.html
title: test/formal_power_series/log_of_formal_power_series.0.test.cpp
---
