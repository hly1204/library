#pragma once

#include "xgcd.hpp"
#include <array>
#include <cassert>
#include <numeric>
#include <optional>
#include <vector>

// returns [remainder, modular] if is solvable
template <typename Int>
inline std::optional<std::array<Int, 2>> chinese_remainder2(Int a0, Int m0, Int a1, Int m1) {
    if (m0 < m1) return chinese_remainder2(a1, m1, a0, m0);
    const auto [x, d]  = inv_gcd(m0, m1);
    const auto a1_a0   = a1 - a0; // assume `a0` < `m0` and `a1` < `m1`
    const auto a1_a0_d = a1_a0 / d;
    if (a1_a0 != a1_a0_d * d) return std::nullopt;
    const auto m1_d = m1 / d;
    auto k0         = x % m1_d * (a1_a0_d % m1_d) % m1_d;
    if (k0 < 0) k0 += m1_d;
    return std::array<Int, 2>{a0 + k0 * m0, m0 * m1_d};
}

// returns [remainder, modular] if is solvable
template <typename Int>
inline std::optional<std::array<Int, 2>> chinese_remainder(const std::vector<Int> &rem,
                                                           const std::vector<Int> &mod) {
    assert(rem.size() == mod.size());
    auto safe_mod = [](Int r, Int m) { return r %= m, (r < 0 ? r + m : r); };
    Int R = 0, M = 1;
    for (int i = 0; i < (int)rem.size(); ++i) {
        if (const auto t = chinese_remainder2(safe_mod(rem[i], mod[i]), mod[i], R, M)) {
            R = t->rem, M = t->mod;
        } else {
            return std::nullopt;
        }
    }
    return std::array<Int, 2>{R, M};
}

// Garner's algorithm
// see:
// [1]: math314. 任意modでの畳み込み演算をO(n log(n))で.
//      https://math314.hateblo.jp/entry/2015/05/07/014908
// returns [remainder mod x, modular mod x] if is solvable
inline std::optional<std::array<int, 2>> chinese_remainder_mod(std::vector<int> rem,
                                                               std::vector<int> mod, int x) {
    using LL = long long;

    assert(rem.size() == mod.size());
    auto safe_mod = [](int r, int m) { return r %= m, (r < 0 ? r + m : r); };
    const int n   = rem.size();
    // check conflicts and make coprime
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            auto d = std::gcd(mod[i], mod[j]);
            if (d == 1) continue;
            if (safe_mod(rem[i], d) != safe_mod(rem[j], d)) return std::nullopt;
            mod[i] /= d, mod[j] /= d;
            if (const auto k = std::gcd(mod[i], d); k != 1)
                while (d % k == 0) mod[i] *= k, d /= k;
            mod[j] *= d;
        }
    }
    mod.push_back(x);
    std::vector<int> pp(n + 1, 1), res(n + 1);
    for (int i = 0; i < n; ++i) {
        auto u =
            (LL)(safe_mod(rem[i], mod[i]) - res[i]) * std::get<0>(inv_gcd(pp[i], mod[i])) % mod[i];
        if (u < 0) u += mod[i];
        for (int j = i + 1; j <= n; ++j) {
            res[j] = (res[j] + u * pp[j]) % mod[j];
            pp[j]  = (LL)pp[j] * mod[i] % mod[j];
        }
    }
    return std::array<int, 2>{res[n], pp[n]};
}
