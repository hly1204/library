---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':heavy_check_mark:'
    path: sbpoly.hpp
    title: sbpoly.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/find_linear_recurrence
    links:
    - https://judge.yosupo.jp/problem/find_linear_recurrence
  bundledCode: "#line 1 \"test/formal_power_series/find_linear_recurrence.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\n\
    \n#line 2 \"modint.hpp\"\n\n#include <iostream>\n#include <type_traits>\n\ntemplate\
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
    #line 2 \"sbpoly.hpp\"\n\n#include <algorithm>\n#include <cassert>\n#line 6 \"\
    sbpoly.hpp\"\n#include <tuple>\n#include <utility>\n#include <vector>\n\n// Schoolbook\
    \ Polynomial\ntemplate <typename Tp>\nclass SBPoly : public std::vector<Tp> {\n\
    \    using Base = std::vector<Tp>;\n\npublic:\n    using Base::Base;\n\n    int\
    \ deg() const {\n        for (int i = (int)Base::size() - 1; i >= 0; --i)\n  \
    \          if (Base::operator[](i) != 0) return i;\n        return -1;\n    }\n\
    \n    int ord() const {\n        for (int i = 0; i < (int)Base::size(); ++i)\n\
    \            if (Base::operator[](i) != 0) return i;\n        return -1;\n   \
    \ }\n\n    SBPoly rev() const {\n        const int d = deg();\n        SBPoly\
    \ res(d + 1);\n        for (int i = d; i >= 0; --i) res[i] = Base::operator[](d\
    \ - i);\n        return res;\n    }\n\n    SBPoly slice(int L, int R) const {\n\
    \        SBPoly res(R - L);\n        for (int i = L; i < std::min(R, (int)Base::size());\
    \ ++i) res[i - L] = Base::operator[](i);\n        return res;\n    }\n\n    SBPoly\
    \ trunc(int D) const {\n        SBPoly res(D);\n        for (int i = 0; i < std::min(D,\
    \ (int)Base::size()); ++i) res[i] = Base::operator[](i);\n        return res;\n\
    \    }\n\n    SBPoly &shrink() {\n        Base::resize(deg() + 1);\n        return\
    \ *this;\n    }\n\n    Tp lc() const {\n        const int d = deg();\n       \
    \ return d == -1 ? Tp() : Base::operator[](d);\n    }\n\n    SBPoly operator-()\
    \ const {\n        const int d = deg();\n        SBPoly res(d + 1);\n        for\
    \ (int i = 0; i <= d; ++i) res[i] = -Base::operator[](i);\n        res.shrink();\n\
    \        return res;\n    }\n\n    // O(deg(Q)deg(R))\n    std::pair<SBPoly, SBPoly>\
    \ divmod(const SBPoly &R) const {\n        const int degL = deg(), degR = R.deg(),\
    \ degQ = degL - degR;\n        assert(degR >= 0);\n        if (degQ < 0) return\
    \ std::make_pair(SBPoly(), *this);\n        SBPoly quo(degQ + 1), rem(*this);\n\
    \        if (degQ >= 0) {\n            const auto inv = R.lc().inv();\n      \
    \      for (int i = degQ, n = degL; i >= 0; --i)\n                if ((quo[i]\
    \ = rem[n--] * inv) != 0)\n                    for (int j = 0; j <= degR; ++j)\
    \ rem[i + j] -= quo[i] * R[j];\n        }\n        rem.shrink();\n        return\
    \ std::make_pair(quo, rem);\n    }\n    SBPoly &operator+=(const SBPoly &R) {\n\
    \        if (Base::size() < R.size()) Base::resize(R.size());\n        for (int\
    \ i = 0; i < (int)R.size(); ++i) Base::operator[](i) += R[i];\n        return\
    \ shrink();\n    }\n    SBPoly &operator-=(const SBPoly &R) {\n        if (Base::size()\
    \ < R.size()) Base::resize(R.size());\n        for (int i = 0; i < (int)R.size();\
    \ ++i) Base::operator[](i) -= R[i];\n        return shrink();\n    }\n    SBPoly\
    \ &operator*=(const SBPoly &R) {\n        const int degL = deg(), degR = R.deg();\n\
    \        if (degL < 0 || degR < 0) {\n            Base::clear();\n           \
    \ return *this;\n        }\n        SBPoly res(degL + degR + 1);\n        for\
    \ (int i = 0; i <= degL; ++i)\n            for (int j = 0; j <= degR; ++j) res[i\
    \ + j] += Base::operator[](i) * R[j];\n        Base::swap(res);\n        return\
    \ *this;\n    }\n    // O(min(deg(Q)^2,deg(Q)deg(R)))\n    SBPoly &operator/=(const\
    \ SBPoly &R) {\n        const int degL = deg(), degR = R.deg(), degQ = degL -\
    \ degR;\n        assert(degR >= 0);\n        SBPoly quo(std::max(0, degQ + 1));\n\
    \        const auto inv = R.lc().inv();\n        for (int i = 0; i <= degQ; ++i)\
    \ {\n            for (int j = 1; j <= std::min(i, degR); ++j)\n              \
    \  quo[degQ - i] += R[degR - j] * quo[degQ - i + j];\n            quo[degQ - i]\
    \ = (Base::operator[](degL - i) - quo[degQ - i]) * inv;\n        }\n        Base::swap(quo);\n\
    \        return *this;\n    }\n    SBPoly &operator%=(const SBPoly &R) {\n   \
    \     const int degL = deg(), degR = R.deg(), degQ = degL - degR;\n        assert(degR\
    \ >= 0);\n        const auto inv = R.lc().inv();\n        for (int i = degQ, n\
    \ = degL; i >= 0; --i)\n            if (const Tp res = Base::operator[](n--) *\
    \ inv; res != 0)\n                for (int j = 0; j <= degR; ++j) Base::operator[](i\
    \ + j) -= res * R[j];\n        return shrink();\n    }\n    SBPoly &operator<<=(int\
    \ D) {\n        if (D > 0) {\n            Base::insert(Base::begin(), D, Tp());\n\
    \        } else if (D < 0) {\n            if (-D < (int)Base::size()) {\n    \
    \            Base::erase(Base::begin(), Base::begin() + (-D));\n            }\
    \ else {\n                Base::clear();\n            }\n        }\n        return\
    \ shrink();\n    }\n    SBPoly &operator>>=(int D) { return operator<<=(-D); }\n\
    \n    friend SBPoly operator+(const SBPoly &L, const SBPoly &R) { return SBPoly(L)\
    \ += R; }\n    friend SBPoly operator-(const SBPoly &L, const SBPoly &R) { return\
    \ SBPoly(L) -= R; }\n    friend SBPoly operator*(const SBPoly &L, const SBPoly\
    \ &R) { return SBPoly(L) *= R; }\n    friend SBPoly operator/(const SBPoly &L,\
    \ const SBPoly &R) { return SBPoly(L) /= R; }\n    friend SBPoly operator%(const\
    \ SBPoly &L, const SBPoly &R) { return SBPoly(L) %= R; }\n    friend SBPoly operator<<(const\
    \ SBPoly &L, int D) { return SBPoly(L) <<= D; }\n    friend SBPoly operator>>(const\
    \ SBPoly &L, int D) { return SBPoly(L) >>= D; }\n\n    friend std::ostream &operator<<(std::ostream\
    \ &L, const SBPoly &R) {\n        L << '[';\n        const int d = R.deg();\n\
    \        if (d < 0) {\n            L << '0';\n        } else {\n            for\
    \ (int i = 0; i <= d; ++i) {\n                L << R[i];\n                if (i\
    \ == 1) L << \"*x\";\n                if (i > 1) L << \"*x^\" << i;\n        \
    \        if (i != d) L << \" + \";\n            }\n        }\n        return L\
    \ << ']';\n    }\n};\n\ntemplate <typename Tp>\ninline std::tuple<SBPoly<Tp>,\
    \ SBPoly<Tp>, SBPoly<Tp>> xgcd(SBPoly<Tp> A, SBPoly<Tp> B) {\n    SBPoly<Tp> x11\
    \ = {Tp(1)}, x12 = {}, x21 = {}, x22 = {Tp(1)};\n    while (B.deg() >= 0) {\n\
    \        const auto [Q, R]  = A.divmod(B);\n        const auto x11_old = x11,\
    \ x12_old = x12;\n        x11 = x21, x21 = x11_old - x21 * Q;\n        x12 = x22,\
    \ x22 = x12_old - x22 * Q;\n        A = B, B = R;\n    }\n    return std::make_tuple(x11,\
    \ x12, A);\n}\n\ntemplate <typename Tp>\ninline std::pair<SBPoly<Tp>, SBPoly<Tp>>\
    \ inv_gcd(SBPoly<Tp> A, SBPoly<Tp> B) {\n    SBPoly<Tp> x11 = {Tp(1)}, x21 = {};\n\
    \    while (B.deg() >= 0) {\n        const auto [Q, R]  = A.divmod(B);\n     \
    \   const auto x11_old = x11;\n        x11 = x21, x21 = x11_old - x21 * Q;\n \
    \       A = B, B = R;\n    }\n    return std::make_pair(x11, A);\n}\n\n// returns\
    \ P,Q s.t. [x^([-k,-1])]P/Q=[x^([-k,-1])]A/B\n// where P,Q in F[x], deg(Q) is\
    \ minimized\n// requires deg(A)<deg(B)\ntemplate <typename Tp>\ninline std::pair<SBPoly<Tp>,\
    \ SBPoly<Tp>> rational_function_approximation(SBPoly<Tp> A, SBPoly<Tp> B,\n  \
    \                                                                       int k)\
    \ {\n    if (A.deg() < 0 || A.deg() - B.deg() < -k)\n        return std::make_pair(SBPoly<Tp>(),\
    \ SBPoly<Tp>{Tp(1)});\n    SBPoly<Tp> P0 = {Tp(1)}, P1 = {}, Q0 = {}, Q1 = {Tp(1)};\n\
    \    for (;;) {\n        const auto [Q, R]              = B.divmod(A);\n     \
    \   std::tie(P0, P1, Q0, Q1, A, B) = std::make_tuple(P1, Q * P1 + P0, Q1, Q *\
    \ Q1 + Q0, R, A);\n        if (A.deg() < 0 || A.deg() - B.deg() < -(k -= Q.deg()\
    \ * 2)) return std::make_pair(P1, Q1);\n    }\n}\n\n// returns [x^([-k,-1])]A/B\n\
    // requires deg(A)<deg(B)\ntemplate <typename Tp>\ninline std::vector<Tp> rational_function_to_series(SBPoly<Tp>\
    \ A, SBPoly<Tp> B, int k) {\n    return (((A << k) / B).rev() << (B.deg() - A.deg()\
    \ - 1)).slice(0, k);\n}\n#line 7 \"test/formal_power_series/find_linear_recurrence.0.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = ModInt<998244353>;\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ A(n);\n    for (int i = 0; i < n; ++i) std::cin >> A[i];\n    const auto [P,\
    \ Q] = rational_function_approximation(\n        SBPoly<mint>(A.rbegin(), A.rend()),\
    \ SBPoly<mint>{mint(1)} << A.size(), A.size());\n    const auto res = Q / SBPoly<mint>{Q.lc()};\n\
    \    std::cout << res.deg() << '\\n';\n    for (int i = res.deg() - 1; i >= 0;\
    \ --i) std::cout << -res[i] << ' ';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\
    \n\n#include \"modint.hpp\"\n#include \"sbpoly.hpp\"\n#include <iostream>\n#include\
    \ <vector>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint = ModInt<998244353>;\n    int n;\n    std::cin >> n;\n    std::vector<mint>\
    \ A(n);\n    for (int i = 0; i < n; ++i) std::cin >> A[i];\n    const auto [P,\
    \ Q] = rational_function_approximation(\n        SBPoly<mint>(A.rbegin(), A.rend()),\
    \ SBPoly<mint>{mint(1)} << A.size(), A.size());\n    const auto res = Q / SBPoly<mint>{Q.lc()};\n\
    \    std::cout << res.deg() << '\\n';\n    for (int i = res.deg() - 1; i >= 0;\
    \ --i) std::cout << -res[i] << ' ';\n    return 0;\n}\n"
  dependsOn:
  - modint.hpp
  - sbpoly.hpp
  isVerificationFile: true
  path: test/formal_power_series/find_linear_recurrence.0.test.cpp
  requiredBy: []
  timestamp: '2024-07-26 22:54:35+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/formal_power_series/find_linear_recurrence.0.test.cpp
layout: document
redirect_from:
- /verify/test/formal_power_series/find_linear_recurrence.0.test.cpp
- /verify/test/formal_power_series/find_linear_recurrence.0.test.cpp.html
title: test/formal_power_series/find_linear_recurrence.0.test.cpp
---
