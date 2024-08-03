---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: chinese_remainder.hpp
    title: chinese_remainder.hpp
  - icon: ':heavy_check_mark:'
    path: xgcd.hpp
    title: xgcd.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/448
    links:
    - https://yukicoder.me/problems/448
  bundledCode: "#line 1 \"test/number_theory/yukicoder187.0.test.cpp\"\n#define PROBLEM\
    \ \"https://yukicoder.me/problems/448\"\n\n#line 2 \"chinese_remainder.hpp\"\n\
    \n#line 2 \"xgcd.hpp\"\n\n#include <type_traits>\n\ntemplate <typename Int>\n\
    struct XGcdResult {\n    Int x, y, gcd;\n};\n\ntemplate <typename Int>\ninline\
    \ std::enable_if_t<std::is_signed_v<Int>, XGcdResult<Int>> xgcd(Int a, Int b)\
    \ {\n    Int x11 = 1, x12 = 0, x21 = 0, x22 = 1;\n    while (b) {\n        Int\
    \ q = a / b, x11_old = x11, x12_old = x12, a_old = a;\n        x11 = x21, x21\
    \ = x11_old - x21 * q;\n        x12 = x22, x22 = x12_old - x22 * q;\n        a\
    \ = b, b = a_old - b * q;\n    }\n    return XGcdResult<Int>{x11, x12, a};\n}\n\
    \ntemplate <typename Int>\nstruct InvGcdResult {\n    Int inv, gcd;\n};\n\ntemplate\
    \ <typename Int>\ninline std::enable_if_t<std::is_signed_v<Int>, InvGcdResult<Int>>\
    \ inv_gcd(Int a, Int b) {\n    Int x11 = 1, x21 = 0;\n    while (b) {\n      \
    \  Int q = a / b, x11_old = x11, a_old = a;\n        x11 = x21, x21 = x11_old\
    \ - x21 * q;\n        a = b, b = a_old - b * q;\n    }\n    return InvGcdResult<Int>{x11,\
    \ a};\n}\n#line 4 \"chinese_remainder.hpp\"\n#include <cassert>\n#include <numeric>\n\
    #include <optional>\n#include <vector>\n\ntemplate <typename Int>\nstruct ChineseRemainderResult\
    \ {\n    Int rem, mod; // remainder, modular\n};\n\ntemplate <typename Int>\n\
    inline std::optional<ChineseRemainderResult<Int>> chinese_remainder2(Int a0, Int\
    \ m0, Int a1,\n                                                              \
    \       Int m1) {\n    if (m0 < m1) return chinese_remainder2(a1, m1, a0, m0);\n\
    \    const auto [x, d]  = inv_gcd(m0, m1);\n    const auto a1_a0   = a1 - a0;\
    \ // assume `a0` < `m0` and `a1` < `m1`\n    const auto a1_a0_d = a1_a0 / d;\n\
    \    if (a1_a0 != a1_a0_d * d) return {};\n    const auto m1_d = m1 / d;\n   \
    \ auto k0         = x % m1_d * (a1_a0_d % m1_d) % m1_d;\n    if (k0 < 0) k0 +=\
    \ m1_d;\n    return ChineseRemainderResult<Int>{a0 + k0 * m0, m0 * m1_d};\n}\n\
    \ntemplate <typename Int>\ninline std::optional<ChineseRemainderResult<Int>> chinese_remainder(const\
    \ std::vector<Int> &rem,\n                                                   \
    \                 const std::vector<Int> &mod) {\n    assert(rem.size() == mod.size());\n\
    \    auto safe_mod = [](Int r, Int m) { return r %= m, (r < 0 ? r + m : r); };\n\
    \    Int R = 0, M = 1;\n    for (int i = 0; i < (int)rem.size(); ++i)\n      \
    \  if (const auto t = chinese_remainder2(safe_mod(rem[i], mod[i]), mod[i], R,\
    \ M))\n            R = t->rem, M = t->mod;\n        else\n            return {};\n\
    \    return ChineseRemainderResult<Int>{R, M};\n}\n\nstruct ChineseRemainderModResult\
    \ {\n    int rem, mod; // remainder mod x, modular mod x\n};\n\ninline std::optional<ChineseRemainderModResult>\
    \ chinese_remainder_mod(std::vector<int> rem,\n                              \
    \                                        std::vector<int> mod, int x) {\n    using\
    \ LL = long long;\n\n    assert(rem.size() == mod.size());\n    auto safe_mod\
    \ = [](int r, int m) { return r %= m, (r < 0 ? r + m : r); };\n    const int n\
    \   = rem.size();\n    // check conflicts and make coprime\n    for (int i = 0;\
    \ i < n; ++i)\n        for (int j = 0; j < i; ++j) {\n            auto d = std::gcd(mod[i],\
    \ mod[j]);\n            if (d == 1) continue;\n            if (safe_mod(rem[i],\
    \ d) != safe_mod(rem[j], d)) return {};\n            mod[i] /= d, mod[j] /= d;\n\
    \            if (const auto k = std::gcd(mod[i], d); k != 1)\n               \
    \ while (d % k == 0) mod[i] *= k, d /= k;\n            mod[j] *= d;\n        }\n\
    \    // Garner's algorithm\n    // see: https://math314.hateblo.jp/entry/2015/05/07/014908\n\
    \    // math314. \u4EFB\u610Fmod\u3067\u306E\u7573\u307F\u8FBC\u307F\u6F14\u7B97\
    \u3092O(n log(n))\u3067.\n    mod.push_back(x);\n    std::vector<int> pp(n + 1,\
    \ 1), res(n + 1);\n    for (int i = 0; i < n; ++i) {\n        auto u = (LL)(safe_mod(rem[i],\
    \ mod[i]) - res[i]) * inv_gcd(pp[i], mod[i]).inv % mod[i];\n        if (u < 0)\
    \ u += mod[i];\n        for (int j = i + 1; j <= n; ++j)\n            res[j] =\
    \ (res[j] + u * pp[j]) % mod[j], pp[j] = (LL)pp[j] * mod[i] % mod[j];\n    }\n\
    \    return ChineseRemainderModResult{res[n], pp[n]};\n}\n#line 4 \"test/number_theory/yukicoder187.0.test.cpp\"\
    \n#include <algorithm>\n#include <iostream>\n#line 7 \"test/number_theory/yukicoder187.0.test.cpp\"\
    \n\nint main() {\n    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n\
    \    int n;\n    std::cin >> n;\n    std::vector<int> rem(n), mod(n);\n    for\
    \ (int i = 0; i < n; ++i) std::cin >> rem[i] >> mod[i];\n    if (const auto res\
    \ = chinese_remainder_mod(rem, mod, 1000000007)) {\n        if (std::all_of(rem.begin(),\
    \ rem.end(), [](int n) { return n == 0; })) {\n            std::cout << res->mod\
    \ << '\\n';\n        } else {\n            std::cout << res->rem << '\\n';\n \
    \       }\n    } else {\n        std::cout << \"-1\\n\";\n    }\n    return 0;\n\
    }\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/448\"\n\n#include \"chinese_remainder.hpp\"\
    \n#include <algorithm>\n#include <iostream>\n#include <vector>\n\nint main() {\n\
    \    std::ios::sync_with_stdio(false);\n    std::cin.tie(nullptr);\n    int n;\n\
    \    std::cin >> n;\n    std::vector<int> rem(n), mod(n);\n    for (int i = 0;\
    \ i < n; ++i) std::cin >> rem[i] >> mod[i];\n    if (const auto res = chinese_remainder_mod(rem,\
    \ mod, 1000000007)) {\n        if (std::all_of(rem.begin(), rem.end(), [](int\
    \ n) { return n == 0; })) {\n            std::cout << res->mod << '\\n';\n   \
    \     } else {\n            std::cout << res->rem << '\\n';\n        }\n    }\
    \ else {\n        std::cout << \"-1\\n\";\n    }\n    return 0;\n}\n"
  dependsOn:
  - chinese_remainder.hpp
  - xgcd.hpp
  isVerificationFile: true
  path: test/number_theory/yukicoder187.0.test.cpp
  requiredBy: []
  timestamp: '2024-07-20 11:57:39+08:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/number_theory/yukicoder187.0.test.cpp
layout: document
redirect_from:
- /verify/test/number_theory/yukicoder187.0.test.cpp
- /verify/test/number_theory/yukicoder187.0.test.cpp.html
title: test/number_theory/yukicoder187.0.test.cpp
---