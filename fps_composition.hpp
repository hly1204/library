#pragma once

#include "binomial.hpp"
#include "fft.hpp"
#include "fps_basic.hpp"
#include "poly_basic.hpp"
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

// returns f(g) mod x^n
// see:
// [1]: Yasunori Kinoshita, Baitian Li. Power Series Composition in Near-Linear Time.
//      https://arxiv.org/abs/2404.05177
template<typename Tp>
inline std::vector<Tp> composition(std::vector<Tp> f, std::vector<Tp> g, int n) {
    if (n <= 0) return {};
    if (g.empty()) {
        std::vector<Tp> res(n);
        if (!f.empty()) res[0] = f[0];
        return res;
    }
    if (g[0] != 0) {
        const auto c = g[0];
        g[0]         = 0;
        return composition(taylor_shift(std::move(f), c), std::move(g), n);
    }

    // [y^(-1)] (f(y) / (-g(x) + y)) mod x^n in R[x]((y^(-1)))
    auto kinoshita_li = [](auto &&kinoshita_li, std::vector<Tp> &P, std::vector<Tp> Q, int d,
                           int n) {
        if (n == 1) return;
        Q.resize(d * n * 4);
        Q[d * n * 2] = 1;
        fft(Q);
        if (n > 2) {
            std::vector<Tp> V(d * n * 2);
            for (int i = 0; i < d * n * 4; i += 2) V[i / 2] = Q[i] * Q[i + 1];
            inv_fft(V);
            assert(V[0] == 1);
            V[0] = 0;
            for (int i = 0; i < d * 2; ++i) std::fill_n(V.begin() + (i * n + n / 2), n / 2, Tp(0));
            kinoshita_li(kinoshita_li, P, std::move(V), d * 2, n / 2);
        }
        fft(P);
        for (int i = 0; i < d * n * 4; i += 2) std::swap(Q[i] *= P[i / 2], Q[i + 1] *= P[i / 2]);
        inv_fft(Q);
        for (int i = 0; i < d; ++i)
            std::fill_n(std::copy_n(Q.begin() + (i + d) * n * 2, n, P.begin() + i * n * 2), n,
                        Tp(0));
    };

    const int N = fft_len(n);
    f.resize(N * 2);
    g.resize(N * 2);
    for (int i = N - 1; i >= 0; --i) f[i * 2] = f[i], f[i * 2 + 1] = 0;
    for (int i = 0; i < N; ++i) g[i] = (g[i] != 0 ? -g[i] : 0);
    std::fill_n(g.begin() + N, N, Tp(0));
    kinoshita_li(kinoshita_li, f, std::move(g), 1, N);
    f.resize(n);
    return f;
}

// returns [x^(n-1)] (fg^i) for i=0,..,n-1
// see:
// [1]: noshi91. FPS の合成と逆関数、冪乗の係数列挙 Θ(n (log(n))^2)
//      https://noshi91.hatenablog.com/entry/2024/03/16/224034
template<typename Tp>
inline std::vector<Tp> power_projection(std::vector<Tp> f, std::vector<Tp> g, int n) {
    if (n <= 0) return {};
    if (g.empty()) {
        std::vector<Tp> res(n);
        if ((int)f.size() >= n) res[0] = f[n - 1];
        return res;
    }

    const auto c = g[0];
    g[0]         = 0;

    // [x^(n-1)] (f(x) / (-g(x) + y)) in R[x]((y^(-1)))
    auto kinoshita_li = [&](std::vector<Tp> &P, std::vector<Tp> &Q, int d, int n) {
        P.insert(P.begin(), d * n * 2, Tp(0));
        auto nP = P.begin() + d * n * 2;
        Q.resize(d * n * 4);
        for (; n > 2; d *= 2, n /= 2) {
            Q[d * n * 2] = 1;
            transposed_inv_fft(P);
            fft(Q);
            for (int i = d * n * 4 - 2; i >= 0; i -= 2)
                nP[i / 2] = P[i] * Q[i + 1] + P[i + 1] * Q[i];
            for (int i = 0; i < d * n * 4; i += 2) Q[i / 2] = Q[i] * Q[i + 1];
            transposed_fft_n(nP, d * n * 2);
            inv_fft_n(Q.begin(), d * n * 2);
            assert(Q[0] == 1);
            Q[0] = 0;
            for (int i = 0; i < d * 2; ++i) {
                std::fill_n(nP + i * n, n / 2, Tp(0));
                std::fill_n(Q.begin() + (i * n + n / 2), n / 2, Tp(0));
            }
            std::fill_n(P.begin(), d * n * 2, Tp(0));
            std::fill_n(Q.begin() + d * n * 2, d * n * 2, Tp(0));
        }
        if (n > 1) {
            Q[d * n * 2] = 1;
            transposed_inv_fft(P);
            fft(Q);
            for (int i = d * n * 4 - 2; i >= 0; i -= 2)
                nP[i / 2] = P[i] * Q[i + 1] + P[i + 1] * Q[i];
            transposed_fft_n(nP, d * n * 2);
        }
        P.erase(P.begin(), P.begin() + d * n * 2);
    };

    const int N = fft_len(n);
    f.insert(f.begin(), N - n, Tp(0));
    f.reserve(N);
    std::reverse(f.begin(), f.end());
    f.insert(f.begin(), N, Tp(0));
    g.resize(N * 2);
    for (int i = 0; i < N; ++i) g[i] = (g[i] != 0 ? -g[i] : 0);
    std::fill_n(g.begin() + N, N, Tp(0));
    kinoshita_li(f, g, 1, N);
    for (int i = 0; i < N; ++i) f[i] = f[i * 2 + 1];
    f.resize(n);

    if (c != 0) {
        // binomial convolution
        auto &&bin = Binomial<Tp>::get(n);
        std::vector<Tp> C(n);
        Tp cc = 1;
        for (int i = 0; i < n; ++i) {
            f[i] *= bin.inv_factorial(i);
            C[i] = cc * bin.inv_factorial(i);
            cc *= c;
        }
        f = convolution_trunc(f, C, n);
        for (int i = 0; i < n; ++i) f[i] *= bin.factorial(i);
    }
    return f;
}

// returns g s.t. f(g) = g(f) = x mod x^n
template<typename Tp> inline std::vector<Tp> reversion(std::vector<Tp> f, int n) {
    if (n <= 0 || f.size() < 2) return {};
    assert(order(f) == 1);
    const auto if1 = f[1].inv();
    if (n == 1) return {Tp(0)};
    f.resize(n);
    Tp ff = 1;
    for (int i = 1; i < n; ++i) f[i] *= ff *= if1;
    auto a     = power_projection({Tp(1)}, f, n);
    auto &&bin = Binomial<Tp>::get(n);
    for (int i = 1; i < n; ++i) a[i] *= (n - 1) * bin.inv(i);
    auto b = fps_pow(std::vector(a.rbegin(), a.rend() - 1), Tp(1 - n).inv().val(), n - 1);
    for (int i = 0; i < n - 1; ++i) b[i] *= if1;
    b.insert(b.begin(), Tp(0));
    return b;
}
