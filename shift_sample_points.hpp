#pragma once

#include "batch_inv.hpp"
#include "binomial.hpp"
#include "middle_product.hpp"
#include "swag.hpp"
#include <cassert>
#include <functional>
#include <vector>

template<typename Tp>
inline std::vector<Tp> shift_sample_points(const std::vector<Tp> &f, Tp c, int m) {
    if (f.empty()) return std::vector<Tp>(m);
    assert(m > 0);
    const int n = f.size();
    auto &&bin  = Binomial<Tp>::get(n);
    std::vector<Tp> F(n), G(n + m - 1);
    for (int i = 0; i < n; ++i) {
        F[i] = f[i] * bin.inv_factorial(i) * bin.inv_factorial(n - 1 - i);
        if ((n - 1 - i) & 1) F[i] = -F[i];
    }
    for (int i = 0; i < n + m - 1; ++i) {
        const auto v = c + (i - (n - 1));
        // We don't care about G[i] when v = 0.
        // We assigned 1 for G[i] when v = 0 for calling batch_inv().
        G[i] = (v == 0) ? Tp(1) : v;
    }
    auto res = middle_product(batch_inv(G), F);
    SWAG<Tp, std::multiplies<>> P(std::multiplies<>{});
    // P = c!/(c-n)! = prod[-n < i <= 0](c + i)
    for (int i = -n + 1; i <= 0; ++i) P.push_back(c + i);
    // res[i] <- (c+i)!/(c+i-n)! * res[i]
    for (int i = 0; i < m; ++i) {
        if (i) P.pop_front(), P.push_back(c + i);
        const auto v = P.query().value();
        // 0 <= c+i < n iff (c+i)!/(c+i-n)! = 0
        res[i] = (v == 0) ? f[(c + i).val()] : v * res[i];
    }
    return res;
}
