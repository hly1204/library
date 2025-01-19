---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: modint.hpp
    title: modint.hpp
  - icon: ':question:'
    path: swag.hpp
    title: swag.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/queue_operate_all_composite
    links:
    - https://judge.yosupo.jp/problem/queue_operate_all_composite
  bundledCode: "#line 1 \"test/data_structure/queue_operate_all_composite.0.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#line 2 \"modint.hpp\"\n\n#include <iostream>\n#include <type_traits>\n\n\
    // clang-format off\ntemplate<unsigned Mod> class ModInt {\n    static_assert((Mod\
    \ >> 31) == 0, \"`Mod` must less than 2^(31)\");\n    template<typename Int>\n\
    \    static std::enable_if_t<std::is_integral_v<Int>, unsigned> safe_mod(Int v)\
    \ { using D = std::common_type_t<Int, unsigned>; return (v %= (int)Mod) < 0 ?\
    \ (D)(v + (int)Mod) : (D)v; }\n    struct PrivateConstructor {} static inline\
    \ private_constructor{};\n    ModInt(PrivateConstructor, unsigned v) : v_(v) {}\n\
    \    unsigned v_;\n\npublic:\n    static unsigned mod() { return Mod; }\n    static\
    \ ModInt from_raw(unsigned v) { return ModInt(private_constructor, v); }\n   \
    \ static ModInt zero() { return from_raw(0); }\n    static ModInt one() { return\
    \ from_raw(1); }\n    bool is_zero() const { return v_ == 0; }\n    bool is_one()\
    \ const { return v_ == 1; }\n    ModInt() : v_() {}\n    template<typename Int,\
    \ typename std::enable_if_t<std::is_signed_v<Int>, int> = 0> ModInt(Int v) : v_(safe_mod(v))\
    \ {}\n    template<typename Int, typename std::enable_if_t<std::is_unsigned_v<Int>,\
    \ int> = 0> ModInt(Int v) : v_(v % Mod) {}\n    unsigned val() const { return\
    \ v_; }\n    ModInt operator-() const { return from_raw(v_ == 0 ? v_ : Mod - v_);\
    \ }\n    ModInt pow(long long e) const { if (e < 0) return inv().pow(-e); for\
    \ (ModInt x(*this), res(from_raw(1));; x *= x) { if (e & 1) res *= x; if ((e >>=\
    \ 1) == 0) return res; }}\n    ModInt inv() const { int x1 = 1, x3 = 0, a = val(),\
    \ b = Mod; while (b) { const int q = a / b, x1_old = x1, a_old = a; x1 = x3, x3\
    \ = x1_old - x3 * q, a = b, b = a_old - b * q; } return from_raw(x1 < 0 ? x1 +\
    \ (int)Mod : x1); }\n    template<bool Odd = (Mod & 1)> std::enable_if_t<Odd,\
    \ ModInt> div_by_2() const { if (v_ & 1) return from_raw((v_ + Mod) >> 1); return\
    \ from_raw(v_ >> 1); }\n    ModInt &operator+=(const ModInt &a) { if ((v_ += a.v_)\
    \ >= Mod) v_ -= Mod; return *this; }\n    ModInt &operator-=(const ModInt &a)\
    \ { if ((v_ += Mod - a.v_) >= Mod) v_ -= Mod; return *this; }\n    ModInt &operator*=(const\
    \ ModInt &a) { v_ = (unsigned long long)v_ * a.v_ % Mod; return *this; }\n   \
    \ ModInt &operator/=(const ModInt &a) { return *this *= a.inv(); }\n    ModInt\
    \ &operator++() { return *this += one(); }\n    ModInt operator++(int) { ModInt\
    \ o(*this); *this += one(); return o; }\n    ModInt &operator--() { return *this\
    \ -= one(); }\n    ModInt operator--(int) { ModInt o(*this); *this -= one(); return\
    \ o; }\n    friend ModInt operator+(const ModInt &a, const ModInt &b) { return\
    \ ModInt(a) += b; }\n    friend ModInt operator-(const ModInt &a, const ModInt\
    \ &b) { return ModInt(a) -= b; }\n    friend ModInt operator*(const ModInt &a,\
    \ const ModInt &b) { return ModInt(a) *= b; }\n    friend ModInt operator/(const\
    \ ModInt &a, const ModInt &b) { return ModInt(a) /= b; }\n    friend bool operator==(const\
    \ ModInt &a, const ModInt &b) { return a.v_ == b.v_; }\n    friend bool operator!=(const\
    \ ModInt &a, const ModInt &b) { return a.v_ != b.v_; }\n    friend std::istream\
    \ &operator>>(std::istream &a, ModInt &b) { int v; a >> v; b.v_ = safe_mod(v);\
    \ return a; }\n    friend std::ostream &operator<<(std::ostream &a, const ModInt\
    \ &b) { return a << b.val(); }\n};\n// clang-format on\n#line 2 \"swag.hpp\"\n\
    \n#include <cassert>\n#include <cstddef>\n#include <optional>\n#include <stack>\n\
    #line 8 \"swag.hpp\"\n#include <vector>\n\n// see: https://www.hirzels.com/martin/papers/debs17-tutorial.pdf\n\
    // requires: Op(Op(A,B),C) = Op(A,Op(B,C))\ntemplate<typename Tp, typename Op,\n\
    \         std::enable_if_t<std::is_invocable_r_v<Tp, Op, const Tp &, const Tp\
    \ &>, int> = 0>\nclass SWAG {\npublic:\n    Op F;\n    std::stack<Tp, std::vector<Tp>>\
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
    \       return F(Front.top(), *Agg);\n    }\n};\n#line 5 \"test/data_structure/queue_operate_all_composite.0.test.cpp\"\
    \n#include <array>\n#line 7 \"test/data_structure/queue_operate_all_composite.0.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint              = ModInt<998244353>;\n    using LinearFunction  \
    \  = std::array<mint, 2>;\n    const LinearFunction Id = {0, 1};\n    // L(R)\n\
    \    auto composition = [](const LinearFunction &L, const LinearFunction &R) {\n\
    \        return LinearFunction{L[0] + L[1] * R[0], L[1] * R[1]};\n    };\n   \
    \ // R(L)\n    auto composition2 = [&](const LinearFunction &L, const LinearFunction\
    \ &R) {\n        return composition(R, L);\n    };\n    SWAG<LinearFunction, decltype(composition2)>\
    \ swag(composition2);\n    int Q;\n    std::cin >> Q;\n    while (Q--) {\n   \
    \     int cmd;\n        std::cin >> cmd;\n        if (cmd == 0) {\n          \
    \  mint a, b;\n            std::cin >> a >> b;\n            swag.push_back({b,\
    \ a});\n        } else if (cmd == 1) {\n            swag.pop_front();\n      \
    \  } else {\n            mint x;\n            std::cin >> x;\n            std::cout\
    \ << composition(swag.query().value_or(Id), {x, 0}).at(0) << '\\n';\n        }\n\
    \    }\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/queue_operate_all_composite\"\
    \n\n#include \"modint.hpp\"\n#include \"swag.hpp\"\n#include <array>\n#include\
    \ <iostream>\n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    using mint              = ModInt<998244353>;\n    using LinearFunction  \
    \  = std::array<mint, 2>;\n    const LinearFunction Id = {0, 1};\n    // L(R)\n\
    \    auto composition = [](const LinearFunction &L, const LinearFunction &R) {\n\
    \        return LinearFunction{L[0] + L[1] * R[0], L[1] * R[1]};\n    };\n   \
    \ // R(L)\n    auto composition2 = [&](const LinearFunction &L, const LinearFunction\
    \ &R) {\n        return composition(R, L);\n    };\n    SWAG<LinearFunction, decltype(composition2)>\
    \ swag(composition2);\n    int Q;\n    std::cin >> Q;\n    while (Q--) {\n   \
    \     int cmd;\n        std::cin >> cmd;\n        if (cmd == 0) {\n          \
    \  mint a, b;\n            std::cin >> a >> b;\n            swag.push_back({b,\
    \ a});\n        } else if (cmd == 1) {\n            swag.pop_front();\n      \
    \  } else {\n            mint x;\n            std::cin >> x;\n            std::cout\
    \ << composition(swag.query().value_or(Id), {x, 0}).at(0) << '\\n';\n        }\n\
    \    }\n    return 0;\n}\n"
  dependsOn:
  - modint.hpp
  - swag.hpp
  isVerificationFile: true
  path: test/data_structure/queue_operate_all_composite.0.test.cpp
  requiredBy: []
  timestamp: '2025-01-19 15:28:01+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/data_structure/queue_operate_all_composite.0.test.cpp
layout: document
redirect_from:
- /verify/test/data_structure/queue_operate_all_composite.0.test.cpp
- /verify/test/data_structure/queue_operate_all_composite.0.test.cpp.html
title: test/data_structure/queue_operate_all_composite.0.test.cpp
---
