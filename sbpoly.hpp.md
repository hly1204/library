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
    \ * 2)) return std::make_pair(P1, Q1);\n    }\n}\n"
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
    \ * 2)) return std::make_pair(P1, Q1);\n    }\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: sbpoly.hpp
  requiredBy:
  - frobenius.hpp
  timestamp: '2024-07-24 22:44:12+08:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/matrix/pow_of_matrix.0.test.cpp
  - test/matrix/characteristic_polynomial.1.test.cpp
  - test/formal_power_series/find_linear_recurrence.0.test.cpp
documentation_of: sbpoly.hpp
layout: document
redirect_from:
- /library/sbpoly.hpp
- /library/sbpoly.hpp.html
title: sbpoly.hpp
---
