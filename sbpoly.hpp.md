---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: frobenius.hpp
    title: frobenius.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/formal_power_series/find_linear_recurrence.0.test.cpp
    title: test/formal_power_series/find_linear_recurrence.0.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/characteristic_polynomial.1.test.cpp
    title: test/matrix/characteristic_polynomial.1.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/matrix/pow_of_matrix.0.test.cpp
    title: test/matrix/pow_of_matrix.0.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"sbpoly.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <iostream>\n#include <tuple>\n#include <utility>\n#include <vector>\n\
    \n// Schoolbook Polynomial\ntemplate <typename Tp>\nclass SBPoly : public std::vector<Tp>\
    \ {\n    using Base = std::vector<Tp>;\n\npublic:\n    using Base::Base;\n\n \
    \   int deg() const {\n        for (int i = (int)Base::size() - 1; i >= 0; --i)\n\
    \            if (Base::operator[](i) != 0) return i;\n        return -1;\n   \
    \ }\n\n    int ord() const {\n        for (int i = 0; i < (int)Base::size(); ++i)\n\
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
    \ degR;\n        assert(degR >= 0);\n        if (degQ < 0) {\n            Base::clear();\n\
    \            return *this;\n        }\n        SBPoly quo(degQ + 1);\n       \
    \ const auto inv = R.lc().inv();\n        for (int i = 0; i <= degQ; ++i) {\n\
    \            for (int j = 1; j <= std::min(i, degR); ++j)\n                quo[degQ\
    \ - i] += R[degR - j] * quo[degQ - i + j];\n            quo[degQ - i] = (Base::operator[](degL\
    \ - i) - quo[degQ - i]) * inv;\n        }\n        Base::swap(quo);\n        return\
    \ *this;\n    }\n    SBPoly &operator%=(const SBPoly &R) {\n        const int\
    \ degL = deg(), degR = R.deg(), degQ = degL - degR;\n        assert(degR >= 0);\n\
    \        const auto inv = R.lc().inv();\n        for (int i = degQ, n = degL;\
    \ i >= 0; --i)\n            if (const Tp res = Base::operator[](n--) * inv; res\
    \ != 0)\n                for (int j = 0; j <= degR; ++j) Base::operator[](i +\
    \ j) -= res * R[j];\n        return shrink();\n    }\n    SBPoly &operator<<=(int\
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
    \        auto [Q, R]  = A.divmod(B);\n        auto x11_old = x11, x12_old = x12;\n\
    \        x11 = x21, x21 = x11_old - x21 * Q;\n        x12 = x22, x22 = x12_old\
    \ - x22 * Q;\n        A = B, B = R;\n    }\n    return std::make_tuple(x11, x12,\
    \ A);\n}\n\ntemplate <typename Tp>\ninline std::pair<SBPoly<Tp>, SBPoly<Tp>> inv_gcd(SBPoly<Tp>\
    \ A, SBPoly<Tp> B) {\n    SBPoly<Tp> x11 = {Tp(1)}, x21 = {};\n    while (B.deg()\
    \ >= 0) {\n        auto [Q, R]  = A.divmod(B);\n        auto x11_old = x11;\n\
    \        x11 = x21, x21 = x11_old - x21 * Q;\n        A = B, B = R;\n    }\n \
    \   return std::make_pair(x11, A);\n}\n\n// returns P,Q s.t. P/Q=A[0]x^(-1)+A[1]x^(-2)+...\
    \ in F((x^(-1)))\n// where P,Q in F[x], deg(Q) is minimized\n// both time & space\
    \ complexity is O(n^2) where n=A.size()\n// (*) this function is only for explaining\
    \ how this algorithm works.\ntemplate <typename Tp>\ninline std::pair<SBPoly<Tp>,\
    \ SBPoly<Tp>>\nrational_function_reconstruction_slow(const std::vector<Tp> &A)\
    \ {\n    // returns C,D s.t. [x^([-k,-1])]A/B=[x^([-k,-1])]C/D and deg(D) is minimized\n\
    \    auto rec = [](auto &&rec, const SBPoly<Tp> &A, const SBPoly<Tp> &B,\n   \
    \               int k) -> std::pair<SBPoly<Tp>, SBPoly<Tp>> {\n        if (A.deg()\
    \ < 0) return std::make_pair(SBPoly<Tp>(), SBPoly<Tp>{Tp(1)});\n        const\
    \ auto [Q, R] = B.divmod(A);\n        // A/B = ...+?x^(-k)+...+?x^(-deg(Q))\n\
    \        //     = 1/(B/A)\n        //     = 1/(C+D)\n        // note that C,D\
    \ in F((x^(-1))) and we define deg(C)=deg(Q) > deg(D)\n        // (A/B)*C + (A/B)*D\
    \ = 1\n        // we must have [x^([-k,-deg(Q)])]1/C = [x^([-k,-deg(Q)])]A/B\n\
    \        //           => (A/B)*C + (A/B)*D = 1\n        //           => (A/B)\
    \ + (A/B)*D/C = 1/C\n        //           => deg(A/B) + deg(D) - deg(C) < -k\n\
    \        //           => deg(D) < -k + 2deg(C)\n        // (1) If we set C<-Q\
    \ and deg(D) < -k + 2deg(Q), we could just drop D.\n        if (R.deg() - A.deg()\
    \ < -k + Q.deg() * 2) return std::make_pair(SBPoly<Tp>{Tp(1)}, Q);\n        //\
    \ (2) Otherwise we set C<-Q+E/F and minimize deg(F)\n        const auto [E, F]\
    \ = rec(rec, R, A, k - Q.deg() * 2);\n        // now we have 1/(Q+E/F)=F/(QF+E)\n\
    \        return std::make_pair(F, Q * F + E);\n    };\n    // (A[n-1]+A[n-2]x+...+A[0]x^(n-1))\
    \ / x^n = A[0]x^(-1)+A[1]x^(-2)+...\n    return rec(rec, SBPoly<Tp>(A.rbegin(),\
    \ A.rend()), SBPoly<Tp>{Tp(1)} << A.size(), A.size());\n}\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <iostream>\n\
    #include <tuple>\n#include <utility>\n#include <vector>\n\n// Schoolbook Polynomial\n\
    template <typename Tp>\nclass SBPoly : public std::vector<Tp> {\n    using Base\
    \ = std::vector<Tp>;\n\npublic:\n    using Base::Base;\n\n    int deg() const\
    \ {\n        for (int i = (int)Base::size() - 1; i >= 0; --i)\n            if\
    \ (Base::operator[](i) != 0) return i;\n        return -1;\n    }\n\n    int ord()\
    \ const {\n        for (int i = 0; i < (int)Base::size(); ++i)\n            if\
    \ (Base::operator[](i) != 0) return i;\n        return -1;\n    }\n\n    SBPoly\
    \ rev() const {\n        const int d = deg();\n        SBPoly res(d + 1);\n  \
    \      for (int i = d; i >= 0; --i) res[i] = Base::operator[](d - i);\n      \
    \  return res;\n    }\n\n    SBPoly slice(int L, int R) const {\n        SBPoly\
    \ res(R - L);\n        for (int i = L; i < std::min(R, (int)Base::size()); ++i)\
    \ res[i - L] = Base::operator[](i);\n        return res;\n    }\n\n    SBPoly\
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
    \ degR;\n        assert(degR >= 0);\n        if (degQ < 0) {\n            Base::clear();\n\
    \            return *this;\n        }\n        SBPoly quo(degQ + 1);\n       \
    \ const auto inv = R.lc().inv();\n        for (int i = 0; i <= degQ; ++i) {\n\
    \            for (int j = 1; j <= std::min(i, degR); ++j)\n                quo[degQ\
    \ - i] += R[degR - j] * quo[degQ - i + j];\n            quo[degQ - i] = (Base::operator[](degL\
    \ - i) - quo[degQ - i]) * inv;\n        }\n        Base::swap(quo);\n        return\
    \ *this;\n    }\n    SBPoly &operator%=(const SBPoly &R) {\n        const int\
    \ degL = deg(), degR = R.deg(), degQ = degL - degR;\n        assert(degR >= 0);\n\
    \        const auto inv = R.lc().inv();\n        for (int i = degQ, n = degL;\
    \ i >= 0; --i)\n            if (const Tp res = Base::operator[](n--) * inv; res\
    \ != 0)\n                for (int j = 0; j <= degR; ++j) Base::operator[](i +\
    \ j) -= res * R[j];\n        return shrink();\n    }\n    SBPoly &operator<<=(int\
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
    \        auto [Q, R]  = A.divmod(B);\n        auto x11_old = x11, x12_old = x12;\n\
    \        x11 = x21, x21 = x11_old - x21 * Q;\n        x12 = x22, x22 = x12_old\
    \ - x22 * Q;\n        A = B, B = R;\n    }\n    return std::make_tuple(x11, x12,\
    \ A);\n}\n\ntemplate <typename Tp>\ninline std::pair<SBPoly<Tp>, SBPoly<Tp>> inv_gcd(SBPoly<Tp>\
    \ A, SBPoly<Tp> B) {\n    SBPoly<Tp> x11 = {Tp(1)}, x21 = {};\n    while (B.deg()\
    \ >= 0) {\n        auto [Q, R]  = A.divmod(B);\n        auto x11_old = x11;\n\
    \        x11 = x21, x21 = x11_old - x21 * Q;\n        A = B, B = R;\n    }\n \
    \   return std::make_pair(x11, A);\n}\n\n// returns P,Q s.t. P/Q=A[0]x^(-1)+A[1]x^(-2)+...\
    \ in F((x^(-1)))\n// where P,Q in F[x], deg(Q) is minimized\n// both time & space\
    \ complexity is O(n^2) where n=A.size()\n// (*) this function is only for explaining\
    \ how this algorithm works.\ntemplate <typename Tp>\ninline std::pair<SBPoly<Tp>,\
    \ SBPoly<Tp>>\nrational_function_reconstruction_slow(const std::vector<Tp> &A)\
    \ {\n    // returns C,D s.t. [x^([-k,-1])]A/B=[x^([-k,-1])]C/D and deg(D) is minimized\n\
    \    auto rec = [](auto &&rec, const SBPoly<Tp> &A, const SBPoly<Tp> &B,\n   \
    \               int k) -> std::pair<SBPoly<Tp>, SBPoly<Tp>> {\n        if (A.deg()\
    \ < 0) return std::make_pair(SBPoly<Tp>(), SBPoly<Tp>{Tp(1)});\n        const\
    \ auto [Q, R] = B.divmod(A);\n        // A/B = ...+?x^(-k)+...+?x^(-deg(Q))\n\
    \        //     = 1/(B/A)\n        //     = 1/(C+D)\n        // note that C,D\
    \ in F((x^(-1))) and we define deg(C)=deg(Q) > deg(D)\n        // (A/B)*C + (A/B)*D\
    \ = 1\n        // we must have [x^([-k,-deg(Q)])]1/C = [x^([-k,-deg(Q)])]A/B\n\
    \        //           => (A/B)*C + (A/B)*D = 1\n        //           => (A/B)\
    \ + (A/B)*D/C = 1/C\n        //           => deg(A/B) + deg(D) - deg(C) < -k\n\
    \        //           => deg(D) < -k + 2deg(C)\n        // (1) If we set C<-Q\
    \ and deg(D) < -k + 2deg(Q), we could just drop D.\n        if (R.deg() - A.deg()\
    \ < -k + Q.deg() * 2) return std::make_pair(SBPoly<Tp>{Tp(1)}, Q);\n        //\
    \ (2) Otherwise we set C<-Q+E/F and minimize deg(F)\n        const auto [E, F]\
    \ = rec(rec, R, A, k - Q.deg() * 2);\n        // now we have 1/(Q+E/F)=F/(QF+E)\n\
    \        return std::make_pair(F, Q * F + E);\n    };\n    // (A[n-1]+A[n-2]x+...+A[0]x^(n-1))\
    \ / x^n = A[0]x^(-1)+A[1]x^(-2)+...\n    return rec(rec, SBPoly<Tp>(A.rbegin(),\
    \ A.rend()), SBPoly<Tp>{Tp(1)} << A.size(), A.size());\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: sbpoly.hpp
  requiredBy:
  - frobenius.hpp
  timestamp: '2024-07-21 22:42:15+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/formal_power_series/find_linear_recurrence.0.test.cpp
  - test/matrix/pow_of_matrix.0.test.cpp
  - test/matrix/characteristic_polynomial.1.test.cpp
documentation_of: sbpoly.hpp
layout: document
redirect_from:
- /library/sbpoly.hpp
- /library/sbpoly.hpp.html
title: sbpoly.hpp
---
