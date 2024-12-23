---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: chinese_remainder.hpp
    title: chinese_remainder.hpp
  - icon: ':question:'
    path: xgcd.hpp
    title: xgcd.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/448
    links:
    - https://yukicoder.me/problems/448
  bundledCode: "#line 1 \"test/number_theory/yukicoder187.0.test.cpp\"\n#define PROBLEM\
    \ \"https://yukicoder.me/problems/448\"\n\n#line 2 \"chinese_remainder.hpp\"\n\
    \n#line 2 \"xgcd.hpp\"\n\n#include <array>\n#include <type_traits>\n#include <utility>\n\
    \n// returns [x, y, gcd(a, b)] s.t. ax+by = gcd(a, b)\ntemplate <typename Int>\n\
    inline std::enable_if_t<std::is_signed_v<Int>, std::array<Int, 3>> xgcd(Int a,\
    \ Int b) {\n    Int x11 = 1, x12 = 0, x21 = 0, x22 = 1;\n    while (b) {\n   \
    \     std::add_const_t<Int> q = a / b;\n        x11                     = std::exchange(x21,\
    \ x11 - x21 * q);\n        x12                     = std::exchange(x22, x12 -\
    \ x22 * q);\n        a                       = std::exchange(b, a - b * q);\n\
    \    }\n    return {x11, x12, a};\n}\n\n// returns [a^(-1) mod b, gcd(a, b)]\n\
    template <typename Int>\ninline std::enable_if_t<std::is_signed_v<Int>, std::array<Int,\
    \ 2>> inv_gcd(Int a, Int b) {\n    Int x11 = 1, x21 = 0;\n    while (b) {\n  \
    \      std::add_const_t<Int> q = a / b;\n        x11                     = std::exchange(x21,\
    \ x11 - x21 * q);\n        a                       = std::exchange(b, a - b *\
    \ q);\n    }\n    return {x11, a}; // check x11 < 0, check a = 1\n}\n#line 5 \"\
    chinese_remainder.hpp\"\n#include <cassert>\n#include <numeric>\n#include <optional>\n\
    #include <vector>\n\n// returns [remainder, modular] if is solvable\ntemplate\
    \ <typename Int>\ninline std::optional<std::array<Int, 2>> chinese_remainder2(Int\
    \ a0, Int m0, Int a1, Int m1) {\n    if (m0 < m1) return chinese_remainder2(a1,\
    \ m1, a0, m0);\n    const auto [x, d]  = inv_gcd(m0, m1);\n    const auto a1_a0\
    \   = a1 - a0; // assume `a0` < `m0` and `a1` < `m1`\n    const auto a1_a0_d =\
    \ a1_a0 / d;\n    if (a1_a0 != a1_a0_d * d) return std::nullopt;\n    const auto\
    \ m1_d = m1 / d;\n    auto k0         = x % m1_d * (a1_a0_d % m1_d) % m1_d;\n\
    \    if (k0 < 0) k0 += m1_d;\n    return std::array<Int, 2>{a0 + k0 * m0, m0 *\
    \ m1_d};\n}\n\n// returns [remainder, modular] if is solvable\ntemplate <typename\
    \ Int>\ninline std::optional<std::array<Int, 2>> chinese_remainder(const std::vector<Int>\
    \ &rem,\n                                                           const std::vector<Int>\
    \ &mod) {\n    assert(rem.size() == mod.size());\n    auto safe_mod = [](Int r,\
    \ Int m) { return r %= m, (r < 0 ? r + m : r); };\n    Int R = 0, M = 1;\n   \
    \ for (int i = 0; i < (int)rem.size(); ++i) {\n        if (const auto t = chinese_remainder2(safe_mod(rem[i],\
    \ mod[i]), mod[i], R, M)) {\n            R = t->rem, M = t->mod;\n        } else\
    \ {\n            return std::nullopt;\n        }\n    }\n    return std::array<Int,\
    \ 2>{R, M};\n}\n\n// Garner's algorithm\n// see:\n// [1]: math314. \u4EFB\u610F\
    mod\u3067\u306E\u7573\u307F\u8FBC\u307F\u6F14\u7B97\u3092O(n log(n))\u3067.\n\
    //      https://math314.hateblo.jp/entry/2015/05/07/014908\n// returns [remainder\
    \ mod x, modular mod x] if is solvable\ninline std::optional<std::array<int, 2>>\
    \ chinese_remainder_mod(std::vector<int> rem,\n                              \
    \                                 std::vector<int> mod, int x) {\n    using LL\
    \ = long long;\n\n    assert(rem.size() == mod.size());\n    auto safe_mod = [](int\
    \ r, int m) { return r %= m, (r < 0 ? r + m : r); };\n    const int n   = rem.size();\n\
    \    // check conflicts and make coprime\n    for (int i = 0; i < n; ++i) {\n\
    \        for (int j = 0; j < i; ++j) {\n            auto d = std::gcd(mod[i],\
    \ mod[j]);\n            if (d == 1) continue;\n            if (safe_mod(rem[i],\
    \ d) != safe_mod(rem[j], d)) return std::nullopt;\n            mod[i] /= d, mod[j]\
    \ /= d;\n            if (const auto k = std::gcd(mod[i], d); k != 1)\n       \
    \         while (d % k == 0) mod[i] *= k, d /= k;\n            mod[j] *= d;\n\
    \        }\n    }\n    mod.push_back(x);\n    std::vector<int> pp(n + 1, 1), res(n\
    \ + 1);\n    for (int i = 0; i < n; ++i) {\n        auto u =\n            (LL)(safe_mod(rem[i],\
    \ mod[i]) - res[i]) * std::get<0>(inv_gcd(pp[i], mod[i])) % mod[i];\n        if\
    \ (u < 0) u += mod[i];\n        for (int j = i + 1; j <= n; ++j) {\n         \
    \   res[j] = (res[j] + u * pp[j]) % mod[j];\n            pp[j]  = (LL)pp[j] *\
    \ mod[i] % mod[j];\n        }\n    }\n    return std::array<int, 2>{res[n], pp[n]};\n\
    }\n#line 4 \"test/number_theory/yukicoder187.0.test.cpp\"\n#include <algorithm>\n\
    #include <iostream>\n#line 7 \"test/number_theory/yukicoder187.0.test.cpp\"\n\n\
    int main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n;\n    std::cin >> n;\n    std::vector<int> rem(n), mod(n);\n    for\
    \ (int i = 0; i < n; ++i) std::cin >> rem[i] >> mod[i];\n    if (const auto res\
    \ = chinese_remainder_mod(rem, mod, 1000000007)) {\n        if (std::all_of(rem.begin(),\
    \ rem.end(), [](int n) { return n == 0; })) {\n            std::cout << std::get<1>(*res)\
    \ << '\\n';\n        } else {\n            std::cout << std::get<0>(*res) << '\\\
    n';\n        }\n    } else {\n        std::cout << \"-1\\n\";\n    }\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/448\"\n\n#include \"chinese_remainder.hpp\"\
    \n#include <algorithm>\n#include <iostream>\n#include <vector>\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int n;\n\
    \    std::cin >> n;\n    std::vector<int> rem(n), mod(n);\n    for (int i = 0;\
    \ i < n; ++i) std::cin >> rem[i] >> mod[i];\n    if (const auto res = chinese_remainder_mod(rem,\
    \ mod, 1000000007)) {\n        if (std::all_of(rem.begin(), rem.end(), [](int\
    \ n) { return n == 0; })) {\n            std::cout << std::get<1>(*res) << '\\\
    n';\n        } else {\n            std::cout << std::get<0>(*res) << '\\n';\n\
    \        }\n    } else {\n        std::cout << \"-1\\n\";\n    }\n    return 0;\n\
    }\n"
  dependsOn:
  - chinese_remainder.hpp
  - xgcd.hpp
  isVerificationFile: true
  path: test/number_theory/yukicoder187.0.test.cpp
  requiredBy: []
  timestamp: '2024-12-23 21:08:20+08:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: test/number_theory/yukicoder187.0.test.cpp
layout: document
redirect_from:
- /verify/test/number_theory/yukicoder187.0.test.cpp
- /verify/test/number_theory/yukicoder187.0.test.cpp.html
title: test/number_theory/yukicoder187.0.test.cpp
---
