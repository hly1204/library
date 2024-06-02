#pragma once

#include "fps_basic.hpp"
#include "sqrt_mod.hpp"
#include <optional>
#include <vector>

template <typename Tp>
inline std::optional<std::vector<Tp>> sqrt(const std::vector<Tp> &a, int n) {
    const int o = order(a);
    if (o < 0) return std::vector<Tp>(n);
    const auto cv = sqrt_mod_prime(a[o]);
    if (cv.empty()) return {};
    return sqrt_hint(a, n, cv[0]);
}

template <typename Tp>
inline std::optional<std::vector<Tp>> sqrt_hint(const std::vector<Tp> &a, int n, Tp c) {
    const int o = order(a);
    if (o < 0) return std::vector<Tp>(n);
    if ((o & 1) || c * c != a[o]) return {};
    std::vector sqrta(a.begin() + o, a.end());
    const auto iv = sqrta[0].inv();
    for (int i = 0; i < (int)sqrta.size(); ++i) sqrta[i] *= iv;
    sqrta = pow(sqrta, Tp(1).div_by_2().val(), n - o / 2);
    for (int i = 0; i < (int)sqrta.size(); ++i) sqrta[i] *= c;
    sqrta.insert(sqrta.begin(), o / 2, 0);
    return sqrta;
}
