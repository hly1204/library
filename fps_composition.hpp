#pragma once

#include "binomial.hpp"
#include "fft.hpp"
#include <algorithm>
#include <vector>

// returns f(g) mod x^n
// see: https://arxiv.org/abs/2404.05177
// Yasunori Kinoshita, Baitian Li. Power Series Composition in Near-Linear Time.
template <typename Tp>
std::vector<Tp> composition(const std::vector<Tp> &f, const std::vector<Tp> &g, int n) {
    if (n <= 0) return {};
    if (g.empty()) return std::vector<Tp>(n);

    // [[y^(-1)]] (f(y) / (-f(x) + y)) mod x^n
    // 在 R[x]((y^(-1))) 上计算乘法逆元
    auto rec = [g0 = g[0]](auto &&rec, const std::vector<Tp> &P, const std::vector<Tp> &Q, int d,
                           int n) {
        if (n == 1) {
            std::vector<Tp> invQ(d + 1);
            auto &&bin = Binomial<Tp>::get(d * 2);
            Tp gg      = 1;
            for (int i = 0; i <= d; ++i) invQ[d - i] = bin.binom(d + i - 1, d - 1) * gg, gg *= g0;
            // invQ[i] = [y^(-2d + i)]Q
            // P[0,d-1] * invQ[-2d,-d] => [0,d-1] * [0,d]
            // 取 [-d,-1] => 取 [d,2d-1]
            auto PinvQ = convolution_fft(P, invQ);
            PinvQ.erase(PinvQ.begin(), PinvQ.begin() + d);
            PinvQ.resize(d);
            return PinvQ;
        }

        std::vector<Tp> dftQ(d * n * 4);
        for (int i = 0; i < d; ++i)
            for (int j = 0; j < n; ++j) dftQ[i * (n * 2) + j] = Q[i * n + j];
        dftQ[d * n * 2] = 1;
        fft(dftQ);
        std::vector<Tp> V(d * n * 2);
        for (int i = 0; i < d * n * 4; i += 2) V[i / 2] = dftQ[i] * dftQ[i + 1];
        inv_fft(V);
        V[0] -= 1;

        for (int i = 1; i < d * 2; ++i)
            for (int j = 0; j < n / 2; ++j) V[i * (n / 2) + j] = V[i * n + j];
        V.resize(d * n);

        const auto T = rec(rec, P, V, d * 2, n / 2);

        std::vector<Tp> dftT(d * n * 2);
        for (int i = 0; i < d * 2; ++i)
            for (int j = 0; j < n / 2; ++j) dftT[i * n + j] = T[i * (n / 2) + j];
        fft(dftT);

        std::vector<Tp> U(d * n * 4);
        for (int i = 0; i < d * n * 4; i += 2) {
            U[i]     = dftT[i / 2] * dftQ[i + 1];
            U[i + 1] = dftT[i / 2] * dftQ[i];
        }
        inv_fft(U);

        // [-2d,d-1] => [0,3d-1]
        // 取 [-d,-1] => 取 [d,2d-1]
        for (int i = 0; i < d; ++i)
            for (int j = 0; j < n; ++j) U[i * n + j] = U[(i + d) * (n * 2) + j];
        U.resize(d * n);
        return U;
    };

    int k = 1;
    while (k < std::max(n, (int)f.size())) k *= 2;
    std::vector<Tp> Q(k);
    for (int i = 0; i < std::min(k, (int)g.size()); ++i) Q[i] = -g[i];

    auto res = rec(rec, f, Q, 1, k);
    res.resize(n);
    return res;
}
