#pragma once

#include "middle_product.hpp"
#include "poly_basic.hpp"
#include <algorithm>
#include <vector>

// returns F(a),F(ac),F(ac^2),...,F(ac^(n-1))
// Use        ij = binom(i,2)   + binom(-j,2) - binom(i-j,2)
// instead of ij = binom(i+j,2) - binom(i,2)  - binom(j,2)
template <typename Tp>
inline std::vector<Tp> czt(std::vector<Tp> F, Tp c, int n, Tp a = 1) {
    if (n <= 0) return {};
    const int degF = degree(F);
    if (degF < 0) return std::vector<Tp>(n);
    if (degF == 0 || a == 0) return std::vector<Tp>(n, F[0]);
    if (a != 1) {
        // F(x) <- F(ax)
        Tp aa = 1;
        for (int i = 0; i <= degF; ++i) F[i] *= aa, aa *= a;
    }
    if (c == 0) {
        std::vector<Tp> res(n, F[0]);
        for (int i = 1; i <= degF; ++i) res[0] += F[i];
        return res;
    }

    std::vector<Tp> H(std::max(degF + 1, n - 1));
    Tp cc = H[0] = 1;
    for (int i = 1; i < (int)H.size(); ++i) H[i] = H[i - 1] * (cc *= c);
    std::vector<Tp> G(degF + n); // G[i+degF]=c^(-binom(i,2))
    auto GG     = G.begin() + degF;
    const Tp ic = c.inv();
    cc = GG[0] = 1;
    for (int i = 1; i < n; ++i) GG[i] = GG[i - 1] * cc, cc *= ic;
    cc = 1;
    for (int i = -1; i >= -degF; --i) GG[i] = GG[i + 1] * (cc *= ic);

    // F[i] <- c^(binom(i+1,2))*F[i]
    for (int i = 0; i <= degF; ++i) F[i] *= H[i];

    F = middle_product(G, F);

    // F[i] <- c^(binom(i,2))*F[i]
    for (int i = 1; i < n; ++i) F[i] *= H[i - 1];
    return F;
}
