#pragma once

#include "subset_conv.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

// returns F(G)
// requires deg(F)<=n, G(0)=0
// see:
// [1]: Elegia. Optimal Algorithm on Polynomial Composite Set Power Series.
//      https://codeforces.com/blog/entry/92183
template <typename Tp>
inline std::vector<Tp> sps_in_egf(const std::vector<Tp> &F, const std::vector<Tp> &G) {
    const int N = (int)F.size() - 1;
    assert((int)G.size() == (1 << N));
    assert(G[0] == 0);

    std::vector res = {F[N]};
    for (int i = 0; i < N; ++i) {
        std::vector<Tp> R(1 << (i + 1));
        R[0] = F[N - (i + 1)];
        for (int j = 0; j <= i; ++j) {
            const auto FG =
                subset_convolution(std::vector(res.begin(), res.begin() + (1 << j)),
                                   std::vector(G.begin() + (1 << j), G.begin() + (2 << j)));
            std::copy(FG.begin(), FG.end(), R.begin() + (1 << j));
        }
        // now R = F^((N-(i+1)))(G)
        R.swap(res);
    }

    return res;
}

template <typename Tp>
inline std::vector<Tp> sps_in_poly(std::vector<Tp> F, std::vector<Tp> G) {
    const int N = G.size();
    int LogN    = 0;
    while ((1 << LogN) != N) ++LogN;

    if (G[0] != 0) {
        std::vector<Tp> bin(LogN + 1), pw(F.size() + 1), FF(LogN + 1);
        pw[0] = 1;
        for (int i = 1; i < (int)pw.size(); ++i) pw[i] = pw[i - 1] * G[0];
        G[0]   = 0;
        bin[0] = 1;
        for (int i = 0; i < (int)F.size(); ++i) {
            for (int j = 0; j <= std::min(LogN, i); ++j) FF[j] += F[i] * bin[j] * pw[i - j];
            for (int j = LogN; j > 0; --j) bin[j] += bin[j - 1];
        }
        FF.swap(F);
    }

    F.resize(LogN + 1);
    Tp c = 1;                                       // factorial
    for (int i = 1; i <= LogN; ++i) F[i] *= c *= i; // to EGF
    return sps_in_egf(F, G);
}
