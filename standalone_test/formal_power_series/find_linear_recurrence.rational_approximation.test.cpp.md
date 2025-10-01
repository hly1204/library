---
data:
  _extendedDependsOn: []
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
  bundledCode: "#line 1 \"standalone_test/formal_power_series/find_linear_recurrence.rational_approximation.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\n\
    \n#include <array>\n#include <cassert>\n#include <iostream>\n#include <tuple>\n\
    #include <vector>\n\nusing uint         = unsigned;\nusing ull          = unsigned\
    \ long long;\nconstexpr uint MOD = 998244353;\n\nconstexpr uint PowMod(uint a,\
    \ ull e) {\n    for (uint res = 1;; a = (ull)a * a % MOD) {\n        if (e & 1)\
    \ res = (ull)res * a % MOD;\n        if ((e /= 2) == 0) return res;\n    }\n}\n\
    \nconstexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }\n\nint Degree(const\
    \ std::vector<uint> &a) {\n    for (int i = (int)size(a) - 1; i >= 0; --i)\n \
    \       if (a[i]) return i;\n    return -1;\n}\n\nvoid Shrink(std::vector<uint>\
    \ &a) { a.resize(Degree(a) + 1); }\n\nuint LeadCoeff(const std::vector<uint> &a)\
    \ {\n    const int degA = Degree(a);\n    return degA >= 0 ? a[degA] : 0u;\n}\n\
    \nstd::vector<uint> Monic(std::vector<uint> a) {\n    const int ia = InvMod(LeadCoeff(a));\n\
    \    for (int i = 0; i < (int)size(a); ++i) a[i] = (ull)a[i] * ia % MOD;\n   \
    \ return a;\n}\n\nstd::array<std::vector<uint>, 2> QuoRem(std::vector<uint> A,\
    \ const std::vector<uint> &B) {\n    const int degA = Degree(A);\n    const int\
    \ degB = Degree(B);\n    assert(degB >= 0);\n    const int degQ = degA - degB;\n\
    \    if (degQ < 0) return {std::vector<uint>{}, A};\n    std::vector<uint> Q(degQ\
    \ + 1);\n    const uint ib = InvMod(LeadCoeff(B));\n    for (int i = degQ, n =\
    \ degA; i >= 0; --i) {\n        if ((Q[i] = (ull)A[n--] * ib % MOD) != 0) {\n\
    \            for (int j = 0; j <= degB; ++j) {\n                A[i + j] = A[i\
    \ + j] + MOD - ((ull)B[j] * Q[i] % MOD);\n                if (A[i + j] >= MOD)\
    \ A[i + j] -= MOD;\n            }\n        }\n    }\n    Shrink(A);\n    return\
    \ {Q, A};\n}\n\nstd::vector<uint> MultiplyAdd(const std::vector<uint> &x, const\
    \ std::vector<uint> &y,\n                              const std::vector<uint>\
    \ &z) {\n    std::vector<uint> xy(size(x) + size(y) - 1);\n    for (int i = 0;\
    \ i < (int)size(x); ++i)\n        for (int j = 0; j < (int)size(y); ++j) xy[i\
    \ + j] = (xy[i + j] + (ull)x[i] * y[j]) % MOD;\n    for (int i = 0; i < (int)size(z);\
    \ ++i)\n        if ((xy[i] += z[i]) >= MOD) xy[i] -= MOD;\n    Shrink(xy);\n \
    \   return xy;\n}\n\n// returns P, Q  such that [x^[-k, 0)] P/Q = [x^[-k, 0)]\
    \ A/B\n// and deg(Q) is minimized\n// requires deg(A) < deg(B)\nstd::array<std::vector<uint>,\
    \ 2> RationalApprox(std::vector<uint> A, std::vector<uint> B, int k) {\n    if\
    \ (Degree(A) < 0 || Degree(A) - Degree(B) < -k)\n        return {std::vector<uint>{},\
    \ std::vector<uint>{1u}};\n    std::vector<uint> P0 = {1u}, P1, Q0, Q1 = {1u};\n\
    \    for (;;) {\n        const auto [Q, R] = QuoRem(B, A);\n        std::tie(P0,\
    \ P1, Q0, Q1, A, B) =\n            std::make_tuple(P1, MultiplyAdd(Q, P1, P0),\
    \ Q1, MultiplyAdd(Q, Q1, Q0), R, A);\n        if (Degree(A) < 0 || Degree(A) -\
    \ Degree(B) < -(k -= Degree(Q) * 2)) return {P1, Q1};\n    }\n}\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n;\n    std::cin >> n;\n    std::vector<uint> a(n);\n    for (int i = 0; i <\
    \ n; ++i) std::cin >> a[i];\n    const auto res = Monic(std::get<1>(RationalApprox(\n\
    \        std::vector(a.rbegin(), a.rend()),\n        [](int n) {\n           \
    \ std::vector<uint> a(n + 1);\n            a[n] = 1;\n            return a;\n\
    \        }(n),\n        n)));\n    std::cout << Degree(res) << '\\n';\n    for\
    \ (int i = Degree(res) - 1; i >= 0; --i) std::cout << (res[i] ? MOD - res[i] :\
    \ 0u) << ' ';\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/find_linear_recurrence\"\
    \n\n#include <array>\n#include <cassert>\n#include <iostream>\n#include <tuple>\n\
    #include <vector>\n\nusing uint         = unsigned;\nusing ull          = unsigned\
    \ long long;\nconstexpr uint MOD = 998244353;\n\nconstexpr uint PowMod(uint a,\
    \ ull e) {\n    for (uint res = 1;; a = (ull)a * a % MOD) {\n        if (e & 1)\
    \ res = (ull)res * a % MOD;\n        if ((e /= 2) == 0) return res;\n    }\n}\n\
    \nconstexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }\n\nint Degree(const\
    \ std::vector<uint> &a) {\n    for (int i = (int)size(a) - 1; i >= 0; --i)\n \
    \       if (a[i]) return i;\n    return -1;\n}\n\nvoid Shrink(std::vector<uint>\
    \ &a) { a.resize(Degree(a) + 1); }\n\nuint LeadCoeff(const std::vector<uint> &a)\
    \ {\n    const int degA = Degree(a);\n    return degA >= 0 ? a[degA] : 0u;\n}\n\
    \nstd::vector<uint> Monic(std::vector<uint> a) {\n    const int ia = InvMod(LeadCoeff(a));\n\
    \    for (int i = 0; i < (int)size(a); ++i) a[i] = (ull)a[i] * ia % MOD;\n   \
    \ return a;\n}\n\nstd::array<std::vector<uint>, 2> QuoRem(std::vector<uint> A,\
    \ const std::vector<uint> &B) {\n    const int degA = Degree(A);\n    const int\
    \ degB = Degree(B);\n    assert(degB >= 0);\n    const int degQ = degA - degB;\n\
    \    if (degQ < 0) return {std::vector<uint>{}, A};\n    std::vector<uint> Q(degQ\
    \ + 1);\n    const uint ib = InvMod(LeadCoeff(B));\n    for (int i = degQ, n =\
    \ degA; i >= 0; --i) {\n        if ((Q[i] = (ull)A[n--] * ib % MOD) != 0) {\n\
    \            for (int j = 0; j <= degB; ++j) {\n                A[i + j] = A[i\
    \ + j] + MOD - ((ull)B[j] * Q[i] % MOD);\n                if (A[i + j] >= MOD)\
    \ A[i + j] -= MOD;\n            }\n        }\n    }\n    Shrink(A);\n    return\
    \ {Q, A};\n}\n\nstd::vector<uint> MultiplyAdd(const std::vector<uint> &x, const\
    \ std::vector<uint> &y,\n                              const std::vector<uint>\
    \ &z) {\n    std::vector<uint> xy(size(x) + size(y) - 1);\n    for (int i = 0;\
    \ i < (int)size(x); ++i)\n        for (int j = 0; j < (int)size(y); ++j) xy[i\
    \ + j] = (xy[i + j] + (ull)x[i] * y[j]) % MOD;\n    for (int i = 0; i < (int)size(z);\
    \ ++i)\n        if ((xy[i] += z[i]) >= MOD) xy[i] -= MOD;\n    Shrink(xy);\n \
    \   return xy;\n}\n\n// returns P, Q  such that [x^[-k, 0)] P/Q = [x^[-k, 0)]\
    \ A/B\n// and deg(Q) is minimized\n// requires deg(A) < deg(B)\nstd::array<std::vector<uint>,\
    \ 2> RationalApprox(std::vector<uint> A, std::vector<uint> B, int k) {\n    if\
    \ (Degree(A) < 0 || Degree(A) - Degree(B) < -k)\n        return {std::vector<uint>{},\
    \ std::vector<uint>{1u}};\n    std::vector<uint> P0 = {1u}, P1, Q0, Q1 = {1u};\n\
    \    for (;;) {\n        const auto [Q, R] = QuoRem(B, A);\n        std::tie(P0,\
    \ P1, Q0, Q1, A, B) =\n            std::make_tuple(P1, MultiplyAdd(Q, P1, P0),\
    \ Q1, MultiplyAdd(Q, Q1, Q0), R, A);\n        if (Degree(A) < 0 || Degree(A) -\
    \ Degree(B) < -(k -= Degree(Q) * 2)) return {P1, Q1};\n    }\n}\n\nint main()\
    \ {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int\
    \ n;\n    std::cin >> n;\n    std::vector<uint> a(n);\n    for (int i = 0; i <\
    \ n; ++i) std::cin >> a[i];\n    const auto res = Monic(std::get<1>(RationalApprox(\n\
    \        std::vector(a.rbegin(), a.rend()),\n        [](int n) {\n           \
    \ std::vector<uint> a(n + 1);\n            a[n] = 1;\n            return a;\n\
    \        }(n),\n        n)));\n    std::cout << Degree(res) << '\\n';\n    for\
    \ (int i = Degree(res) - 1; i >= 0; --i) std::cout << (res[i] ? MOD - res[i] :\
    \ 0u) << ' ';\n    return 0;\n}"
  dependsOn: []
  isVerificationFile: true
  path: standalone_test/formal_power_series/find_linear_recurrence.rational_approximation.test.cpp
  requiredBy: []
  timestamp: '2025-10-01 19:02:33+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: standalone_test/formal_power_series/find_linear_recurrence.rational_approximation.test.cpp
layout: document
redirect_from:
- /verify/standalone_test/formal_power_series/find_linear_recurrence.rational_approximation.test.cpp
- /verify/standalone_test/formal_power_series/find_linear_recurrence.rational_approximation.test.cpp.html
title: standalone_test/formal_power_series/find_linear_recurrence.rational_approximation.test.cpp
---
