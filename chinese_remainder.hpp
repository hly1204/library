#pragma once

#include "xgcd.hpp"
#include <cassert>
#include <optional>
#include <vector>

template <typename Int>
struct ChineseRemainderResult {
    Int rem, mod; // remainder, modular
};

template <typename Int>
inline std::optional<ChineseRemainderResult<Int>> chinese_remainder2(Int a0, Int m0, Int a1,
                                                                     Int m1) {
    if (m0 < m1) return chinese_remainder2(a1, m1, a0, m0);
    const auto [x, d]  = inv_gcd(m0, m1);
    const auto a1_a0   = a1 - a0; // assume `a0` < `m0` and `a1` < `m1`
    const auto a1_a0_d = a1_a0 / d;
    if (a1_a0 != a1_a0_d * d) return {};
    const auto m1_d = m1 / d;
    auto k0         = x % m1_d * (a1_a0_d % m1_d) % m1_d;
    if (k0 < 0) k0 += m1_d;
    return ChineseRemainderResult<Int>{a0 + k0 * m0, m0 * m1_d};
}

template <typename Int>
inline std::optional<ChineseRemainderResult<Int>> chinese_remainder(const std::vector<Int> &rem,
                                                                    const std::vector<Int> &mod) {
    assert(rem.size() == mod.size());
    auto safe_mod = [](Int r, Int m) { return r %= m, (r < 0 ? r + m : r); };
    Int R = 0, M = 1;
    for (int i = 0; i < (int)rem.size(); ++i)
        if (const auto t = chinese_remainder2(safe_mod(rem[i], mod[i]), mod[i], R, M))
            R = t->rem, M = t->mod;
        else
            return {};
    return ChineseRemainderResult<Int>{R, M};
}
