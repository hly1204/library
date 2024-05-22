#pragma once

#include "fft.hpp"
#include "fps_basic.hpp"
#include "poly_basic.hpp"
#include <cassert>
#include <vector>

template <typename Tp>
class SubproductTree {
public:
    std::vector<Tp> T;
    int N;
    int S;

    SubproductTree(const std::vector<Tp> &A) : N(A.size()), S(std::max(fft_len(N), 2)) {
        assert(N > 0);
        int LogS = 1;
        while ((1 << LogS) < S) ++LogS;
        T.assign((LogS + 1) * S * 2, 1);
        for (int i = 0; i < N; ++i) {
            T[LogS * S * 2 + i * 2]     = 1 - A[i];
            T[LogS * S * 2 + i * 2 + 1] = -1 - A[i];
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
                auto FF = res.begin() + i * len;
                auto L  = T.begin() + ((lv + 1) * S * 2 + i * len * 2); // left child
                fft_n(FF, len);
                for (int j = 0; j < len; ++j) {
                    LL[j] = FF[j] * L[len + j];
                    RR[j] = FF[j] * L[j];
                }
                inv_fft(LL);
                inv_fft(RR);
                const int degL = std::max(std::min((i * len) + len / 2, N) - i * len, 0);
                const int degR = std::max(std::min((i + 1) * len, N) - ((i * len) + len / 2), 0);
                std::copy_n(LL.begin() + degR, len / 2, FF);
                std::copy_n(RR.begin() + degL, len / 2, FF + len / 2);
            }
        }
        res.resize(N);
        return res;
    }
};
