#pragma once

#include "binomial.hpp"
#include "fft.hpp"
#include <vector>

// returns f(g) mod x^n
// see: https://noshi91.hatenablog.com/entry/2024/03/16/224034
template <typename Tp>
std::vector<Tp> composition(const std::vector<Tp> &f, const std::vector<Tp> &g, int n) {
    if (n <= 0) return {};
    if (g.empty()) return std::vector<Tp>(n);

    struct composition_rec {
        composition_rec(const std::vector<Tp> &f, Tp g0) : f_(f), g0_(g0) {}
        std::vector<Tp> run(const std::vector<Tp> &Q, int d, int n) const {
            if (n == 0) {
                std::vector<Tp> P(d), invQ(d);
                for (int i = d - 1, j = 0; j < (int)f_.size() && i >= 0;) P[i--] = f_[j++];
                auto &&bin = Binomial<Tp>::get(d * 2);
                Tp gg(1);
                for (int i = 0; i < d; ++i) invQ[i] = bin.binom(d + i - 1, i) * gg, gg *= g0_;
                auto PinvQ = convolution_fft(P, invQ);
                PinvQ.resize(d);
                return PinvQ;
            }

            const int len = fft_len((d * 2 + 1) * (n * 2 + 2) - 1);
            std::vector<Tp> dftQ(len);
            for (int i = 0; i <= d; ++i)
                for (int j = 0; j <= n; ++j) dftQ[i * (n * 2 + 2) + j] = Q[i * (n + 1) + j];
            fft(dftQ);
            std::vector<Tp> VV(len / 2);
            for (int i = 0; i < len; i += 2) VV[i / 2] = dftQ[i] * dftQ[i + 1];
            inv_fft(VV);
            std::vector<Tp> V((d * 2 + 1) * (n / 2 + 1));
            for (int i = 0; i <= d * 2; ++i)
                for (int j = 0; j <= n / 2; ++j) V[i * (n / 2 + 1) + j] = VV[i * (n + 1) + j];

            const auto T = run(V, d * 2, n / 2);

            std::vector<Tp> dftT(len / 2);
            for (int i = 0; i < d * 2; ++i)
                for (int j = 0; j <= n / 2; ++j) dftT[i * (n + 1) + j] = T[i * (n / 2 + 1) + j];
            fft(dftT);
            std::vector<Tp> UU(len);
            for (int i = 0; i < len; i += 2)
                UU[i] = dftT[i / 2] * dftQ[i + 1], UU[i + 1] = dftT[i / 2] * dftQ[i];
            inv_fft(UU);
            std::vector<Tp> U(d * (n + 1));
            for (int i = 0; i < d; ++i)
                for (int j = 0; j <= n; ++j) U[i * (n + 1) + j] = UU[(i + d) * (n * 2 + 2) + j];
            return U;
        }

    private:
        const std::vector<Tp> &f_;
        const Tp g0_;
    } a(f, g[0]);

    std::vector<Tp> Q(n * 2); // [0,n)=1, [n,2n)=-g
    Q[0] = 1;
    for (int i = n, j = 0; j < (int)g.size() && i < n * 2;) Q[i++] = -g[j++];
    auto res = a.run(Q, 1, std::max(n - 1, (int)f.size() - 1));
    res.resize(n);
    return res;
}
