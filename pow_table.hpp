#pragma once

#include <vector>

// returns 0^e, 1^e, ..., (n-1)^e
template <typename Tp>
inline std::vector<Tp> pow_table(int e, int n) {
    if (n <= 0) return {};
    std::vector<bool> is_comp(n);
    std::vector<int> p;
    std::vector<Tp> res(n);
    res[0] = (e == 0 ? Tp(1) : Tp(0)); // 0^0=1
    if (n >= 2) res[1] = Tp(1);
    for (int i = 2; i < n; ++i) {
        if (!is_comp[i]) res[i] = Tp(p.emplace_back(i)).pow(e);
        for (int j = 0; j < (int)p.size() && i * p[j] < n; ++j) {
            is_comp[i * p[j]] = true;
            res[i * p[j]]     = res[i] * res[p[j]];
            if (i % p[j] == 0) break;
        }
    }
    return res;
}
