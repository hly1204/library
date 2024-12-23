#pragma once

#include "binomial.hpp"
#include "fft.hpp"
#include "fps_basic.hpp"
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

// returns f(g) mod x^n
// see: https://arxiv.org/abs/2404.05177
// Yasunori Kinoshita, Baitian Li. Power Series Composition in Near-Linear Time.
template <typename Tp>
inline std::vector<Tp> composition(const std::vector<Tp> &f, const std::vector<Tp> &g, int n) {
    if (n <= 0) return {};
    if (g.empty()) {
        std::vector<Tp> res(n);
        if (!f.empty()) res[0] = f[0];
        return res;
    }

    // [y^(-1)] (f(y) / (-g(x) + y)) mod x^n
    // R[x]((y^(-1)))
    auto rec = [g0 = g[0]](auto &&rec, const std::vector<Tp> &P, const std::vector<Tp> &Q, int d,
                           int n) {
        if (n == 1) {
            std::vector<Tp> invQ(d + 1);
            auto &&bin = Binomial<Tp>::get(d * 2);
            Tp gg      = 1;
            for (int i = 0; i <= d; ++i) invQ[d - i] = bin.binom(d + i - 1, d - 1) * gg, gg *= g0;
            // invQ[i] = [y^(-2d + i)]Q^(-1)
            // P[0,d-1] * invQ[-2d,-d] => [0,d-1] * [0,d]
            // take [-d,-1] => take [d,2d-1]
            auto PinvQ = convolution(P, invQ);
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

        const auto T = rec(rec, P, std::move(V), d * 2, n / 2);

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
        // take [-d,-1] => take [d,2d-1]
        for (int i = 0; i < d; ++i)
            for (int j = 0; j < n; ++j) U[i * n + j] = U[(i + d) * (n * 2) + j];
        U.resize(d * n);
        return U;
    };

    const int k = fft_len(std::max<int>(n, f.size()));
    std::vector<Tp> Q(k);
    for (int i = 0; i < std::min<int>(k, g.size()); ++i) Q[i] = -g[i];

    auto res = rec(rec, f, Q, 1, k);
    res.resize(n);
    return res;
}

// returns [x^k]gf^0, [x^k]gf, ..., [x^k]gf^(n-1)
// see: https://noshi91.hatenablog.com/entry/2024/03/16/224034
// noshi91. FPS の合成と逆関数、冪乗の係数列挙 Θ(n (log(n))^2)
template <typename Tp>
inline std::vector<Tp> enum_kth_term_of_power(const std::vector<Tp> &f, const std::vector<Tp> &g,
                                              int k, int n) {
    if (k < 0 || n <= 0) return {};
    if (f.empty()) {
        std::vector<Tp> res(n);
        if (k < (int)g.size()) res[0] = g[k];
        return res;
    }

    // [x^k] (g(x) / (-f(x) + y))
    // R[x]((y^(-1)))
    std::vector<Tp> P(g), Q(k + 1);
    P.resize(k + 1);
    for (int i = 0; i < std::min<int>(k + 1, f.size()); ++i) Q[i] = -f[i];

    int d = 1;
    for (; k; d *= 2, k /= 2) {
        const int len = fft_len((d * 2) * ((k + 1) * 2) - 1);
        std::vector<Tp> dftP(len), dftQ(len);
        for (int i = 0; i < d; ++i)
            for (int j = 0; j <= k; ++j) {
                dftP[i * ((k + 1) * 2) + j] = P[i * (k + 1) + j];
                dftQ[i * ((k + 1) * 2) + j] = Q[i * (k + 1) + j];
            }
        dftQ[d * (k + 1) * 2] = 1;
        fft(dftP);
        fft(dftQ);

        P.resize(len / 2);
        Q.resize(len / 2);
        if (k & 1) {
            auto &&root = FftInfo<Tp>::get().inv_root(len / 2);
            for (int i = 0; i < len; i += 2) {
                P[i / 2] = (dftP[i] * dftQ[i + 1] - dftP[i + 1] * dftQ[i]).div_by_2() * root[i / 2];
                Q[i / 2] = dftQ[i] * dftQ[i + 1];
            }
        } else {
            for (int i = 0; i < len; i += 2) {
                P[i / 2] = (dftP[i] * dftQ[i + 1] + dftP[i + 1] * dftQ[i]).div_by_2();
                Q[i / 2] = dftQ[i] * dftQ[i + 1];
            }
        }
        inv_fft(P);
        inv_fft(Q);
        if (d * (k + 1) * 4 >= len) Q[(d * (k + 1) * 4) % len] -= 1;

        for (int i = 1; i < d * 2; ++i)
            for (int j = 0; j <= k / 2; ++j) {
                P[i * (k / 2 + 1) + j] = P[i * (k + 1) + j];
                Q[i * (k / 2 + 1) + j] = Q[i * (k + 1) + j];
            }
        P.resize(d * 2 * (k / 2 + 1));
        Q.resize(d * 2 * (k / 2 + 1));
    }

    std::vector<Tp> invQ(n + 1);
    auto &&bin = Binomial<Tp>::get(d + n);
    Tp ff      = 1;
    for (int i = 0; i <= n; ++i) invQ[n - i] = bin.binom(d + i - 1, d - 1) * ff, ff *= f[0];
    // invQ[i] = [y^(-2d + i)]Q^(-1)
    // P[0,d-1] * invQ[-(d+n),-d] => [0,d-1] * [0,n]
    auto PinvQ = convolution(P, invQ);
    // take [-n,-1] => take [d,d+n-1]
    PinvQ.erase(PinvQ.begin(), PinvQ.begin() + d);
    PinvQ.resize(n);
    // output => [-1,-n] reverse
    // before I just reverse it and mistaken something.
    std::reverse(PinvQ.begin(), PinvQ.end());
    return PinvQ;
}

// returns g s.t. f(g) = g(f) = x mod x^n
template <typename Tp>
inline std::vector<Tp> reversion(std::vector<Tp> f, int n) {
    if (n <= 0 || f.size() < 2) return {};
    assert(order(f) == 1);
    const auto if1 = f[1].inv();
    if (n == 1) return {Tp(0)};
    f.resize(n);
    Tp ff = 1;
    for (int i = 1; i < n; ++i) f[i] *= ff *= if1;
    auto a     = enum_kth_term_of_power(f, {Tp(1)}, n - 1, n);
    auto &&bin = Binomial<Tp>::get(n);
    for (int i = 1; i < n; ++i) a[i] *= (n - 1) * bin.inv(i);
    auto b = fps_pow(std::vector(a.rbegin(), a.rend() - 1), Tp(1 - n).inv().val(), n - 1);
    for (int i = 0; i < n - 1; ++i) b[i] *= if1;
    b.insert(b.begin(), Tp(0));
    return b;
}
