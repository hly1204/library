#pragma once

#include "fft.hpp"
#include "fps_basic.hpp"
#include "poly_basic.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

template <typename Tp>
class SubproductTree {
public:
    // LV=0   => T[0..S]  = DFT((x-X_0)..(x-X_(N-1))     mod (x^S     - 1))
    //        => T[S..2S] = (x-X_0)..(x-X_(N-1))         mod (x^S     + 1)  (* SPECIAL CASE)
    // LV=1   => T[..]    = DFT((x-X_0)..(x-X_(S/2-1))   mod (x^(S/2) - 1))
    //        => T[..]    = DFT((x-X_(S/2))..(x-X_(N-1)) mod (x^(S/2) - 1)) (* GENERAL CASE)
    // LV=2.. => ..                                                         (* GENERAL CASE)
    std::vector<Tp> T;
    int N;
    int S;

    SubproductTree(const std::vector<Tp> &X)
        : N(X.size()), S(N == 0 ? 2 : std::max(fft_len(N), 2)) {
        int LogS = 1;
        while ((1 << LogS) < S) ++LogS;
        T.assign((LogS + 1) * S * 2, 1);
        for (int i = 0; i < N; ++i) {
            T[LogS * S * 2 + i * 2]     = 1 - X[i];
            T[LogS * S * 2 + i * 2 + 1] = -1 - X[i];
        }
        for (int lv = LogS - 1, len = 2; lv >= 0; --lv, len *= 2) {
            for (int i = 0; i < (1 << lv); ++i) {
                auto C = T.begin() + (lv * S * 2 + i * len * 2);       // current
                auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child
                for (int j = 0; j < len; ++j) C[j] = C[len + j] = L[j] * L[len + j];
                inv_fft_n(C + len, len);
                if ((i + 1) * len <= N) C[len] -= 2;
                if (lv) {
                    Tp k         = 1;
                    const auto t = FftInfo<Tp>::get().root(len).at(len / 2);
                    for (int j = 0; j < len; ++j) C[len + j] *= k, k *= t;
                    fft_n(C + len, len);
                }
            }
        }
    }

    std::vector<Tp> product() const {
        std::vector res(T.begin() + S, T.begin() + S * 2);
        if (N == S) {
            res[0] += 1;
            res.emplace_back(1);
        }
        res.resize(N + 1);
        return res;
    }

    // see:
    // [1]: A. Bostan, Grégoire Lecerf, É. Schost. Tellegen's principle into practice.
    // [2]: D. Bernstein. SCALED REMAINDER TREES.
    std::vector<Tp> evaluation(const std::vector<Tp> &F) const {
        const int degF = degree(F);
        const auto P   = product();
        // find x^(-1),...,x^(-N) of F/P in R((x^(-1)))
        auto res = div(std::vector(F.rend() - (degF + 1), F.rend()),
                       std::vector(P.rbegin(), P.rend()), degF + 1);
        if (degF >= N) res.erase(res.begin(), res.begin() + (degF - N + 1));
        std::reverse(res.begin(), res.end());
        res.resize(S);
        for (int lv = 0, len = S; (1 << lv) < S; ++lv, len /= 2) {
            std::vector<Tp> LL(len), RR(len);
            for (int i = 0; i < (1 << lv); ++i) {
                auto C = res.begin() + i * len;                        // current
                auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child
                fft_n(C, len);
                for (int j = 0; j < len; ++j) {
                    LL[j] = C[j] * L[len + j];
                    RR[j] = C[j] * L[j];
                }
                inv_fft(LL);
                inv_fft(RR);
                const int degL = std::max(std::min((i * len) + len / 2, N) - i * len, 0);
                const int degR = std::max(std::min((i + 1) * len, N) - ((i * len) + len / 2), 0);
                std::copy_n(LL.begin() + degR, len / 2, C);
                std::copy_n(RR.begin() + degL, len / 2, C + len / 2);
            }
        }
        res.resize(N);
        return res;
    }

    std::vector<Tp> interpolation(const std::vector<Tp> &Y) const {
        assert((int)Y.size() == N);
        const auto D = evaluation(deriv(product())); // denominator => P'(x_i)
        std::vector<Tp> res(S * 2);
        for (int i = 0; i < N; ++i) res[i * 2] = res[i * 2 + 1] = Y[i] / D[i];
        int LogS = 1;
        while ((1 << LogS) < S) ++LogS;
        for (int lv = LogS - 1, len = 2; lv >= 0; --lv, len *= 2) {
            for (int i = 0; i < (1 << lv); ++i) {
                auto C = res.begin() + i * len * 2;                    // current
                auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child
                for (int j = 0; j < len; ++j)
                    C[j] = C[len + j] = C[j] * L[len + j] + C[len + j] * L[j];
                inv_fft_n(C + len, len);
                if (lv) {
                    Tp k         = 1;
                    const auto t = FftInfo<Tp>::get().root(len).at(len / 2);
                    for (int j = 0; j < len; ++j) C[len + j] *= k, k *= t;
                    fft_n(C + len, len);
                }
            }
        }
        return std::vector(res.begin() + S, res.begin() + S + N);
    }

    // see:
    // [1]: A. Bostan, É. Schost. Polynomial evaluation and interpolation on special sets of points.
    // [2]: noshi91. 転置原理なしで Monomial 基底から Newton 基底への変換.
    //      https://noshi91.hatenablog.com/entry/2023/05/01/022946
    std::vector<Tp> monomial_to_newton(const std::vector<Tp> &F) const {
        const int degF = degree(F);
        assert(degF < N);
        const auto P = product();
        // find x^(-1),...,x^(-N) of F/P in R((x^(-1)))
        auto res = div(std::vector(F.rend() - (degF + 1), F.rend()),
                       std::vector(P.rbegin(), P.rend()), degF + 1);
        std::reverse(res.begin(), res.end());
        res.resize(S);
        for (int lv = 0, len = S; (1 << lv) < S; ++lv, len /= 2) {
            std::vector<Tp> RR(len / 2);
            for (int i = 0; i < (1 << lv); ++i) {
                auto C = res.begin() + i * len;                              // current
                auto R = T.begin() + ((lv + 1) * S * 2 + (i * 2 + 1) * len); // right child
                std::copy_n(C + len / 2, len / 2, RR.begin());
                fft_n(C, len);
                for (int j = 0; j < len; ++j) C[j] *= R[j];
                inv_fft_n(C, len);
                const int degR = std::max(std::min((i + 1) * len, N) - ((i * len) + len / 2), 0);
                std::rotate(C, C + degR, C + (degR + len / 2));
                std::copy_n(RR.begin(), len / 2, C + len / 2);
            }
        }
        res.resize(N);
        return res;
    }

    std::vector<Tp> newton_to_monomial(const std::vector<Tp> &F) const {
        const int degF = degree(F);
        assert(degF < N);
        std::vector<Tp> res(S * 2);
        for (int i = 0; i <= degF; ++i) res[i * 2] = res[i * 2 + 1] = F[i];
        int LogS = 1;
        while ((1 << LogS) < S) ++LogS;
        for (int lv = LogS - 1, len = 2; lv >= 0; --lv, len *= 2) {
            for (int i = 0; i < (1 << lv); ++i) {
                auto C = res.begin() + i * len * 2;                    // current
                auto L = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child
                for (int j = 0; j < len; ++j) C[j] = C[len + j] = C[j] + C[len + j] * L[j];
                inv_fft_n(C + len, len);
                if (lv) {
                    Tp k         = 1;
                    const auto t = FftInfo<Tp>::get().root(len).at(len / 2);
                    for (int j = 0; j < len; ++j) C[len + j] *= k, k *= t;
                    fft_n(C + len, len);
                }
            }
        }
        return std::vector(res.begin() + S, res.begin() + S + N);
    }
};
