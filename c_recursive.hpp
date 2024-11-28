#pragma once

#include "fft.hpp"
#include "fft_doubling.hpp"
#include "fps_basic.hpp"
#include "poly_basic.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

// see:
// [1]: Alin Bostan, Ryuhei Mori.
//      A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence.
//      https://arxiv.org/abs/2008.08822

template <typename Tp>
inline void fft_high(std::vector<Tp> &a) {
    const int n = a.size();
    inv_fft_n(a.begin() + n / 2, n / 2);
    Tp k         = 1;
    const auto t = FftInfo<Tp>::get().inv_root(n / 2).at(n / 4);
    for (int i = 0; i < n / 2; ++i) a[i + n / 2] *= k, k *= t;
    fft_n(a.begin() + n / 2, n / 2);
    for (int i = 0; i < n / 2; ++i) a[i] = (a[i] - a[i + n / 2]).div_by_2();
    a.resize(n / 2);
}

// returns DFT([x^[L,L+len/2)]1/Q)
// 1/Q in R[[x]]
// requires len/2 > deg(Q), len/2 is even
template <typename Tp>
inline std::vector<Tp> bostan_mori_power_series(std::vector<Tp> dftQ, long long L) {
    const int len = dftQ.size() * 2;
    if (L <= -(len / 2LL)) return std::vector<Tp>(len / 2);
    if (L <= 0) {
        inv_fft(dftQ);
        auto invQ = inv(dftQ, L + len / 2);
        invQ.insert(invQ.begin(), -L, 0);
        fft(invQ);
        return invQ;
    }

    fft_doubling(dftQ);
    std::vector<Tp> dftV(len / 2);
    for (int i = 0; i < len; i += 2) dftV[i / 2] = dftQ[i] * dftQ[i + 1];
    const auto dftT = bostan_mori_power_series(dftV, (L - len / 2 + (L & 1)) / 2);

    std::vector<Tp> dftU(len);
    if (L & 1) {
        auto &&root = FftInfo<Tp>::get().root(len / 2);
        for (int i = 0; i < len; i += 2) {
            dftU[i]     = dftT[i / 2] * dftQ[i + 1] * root[i / 2];
            dftU[i + 1] = dftT[i / 2] * dftQ[i] * -root[i / 2];
        }
    } else {
        for (int i = 0; i < len; i += 2) {
            dftU[i]     = dftT[i / 2] * dftQ[i + 1];
            dftU[i + 1] = dftT[i / 2] * dftQ[i];
        }
    }

    fft_high(dftU);
    return dftU;
}

// returns DFT([x^[-len/2,0)]x^k/Q)
// x^k/Q in R((x^(-1)))
// requires len/2 > degQ
template <typename Tp>
inline std::vector<Tp> bostan_mori_reversed_laurent_series(std::vector<Tp> dftQ, long long k) {
    assert(k >= 0);
    const int len = dftQ.size() * 2;
    if (k < len / 2LL) {
        inv_fft(dftQ);
        const int degQ = degree(dftQ);
        dftQ.resize(degQ + 1);
        std::reverse(dftQ.begin(), dftQ.end());
        auto invQ = inv(dftQ, len / 2 - degQ + k + 1);
        std::reverse(invQ.begin(), invQ.end());
        invQ.resize(len / 2);
        fft(invQ);
        return invQ;
    }

    fft_doubling(dftQ);
    std::vector<Tp> dftV(len / 2);
    for (int i = 0; i < len; i += 2) dftV[i / 2] = dftQ[i] * dftQ[i + 1];
    const auto dftT = bostan_mori_reversed_laurent_series(dftV, k / 2);

    std::vector<Tp> dftU(len);
    if (k & 1) {
        auto &&root = FftInfo<Tp>::get().root(len / 2);
        for (int i = 0; i < len; i += 2) {
            dftU[i]     = dftT[i / 2] * dftQ[i + 1] * root[i / 2];
            dftU[i + 1] = dftT[i / 2] * dftQ[i] * -root[i / 2];
        }
    } else {
        for (int i = 0; i < len; i += 2) {
            dftU[i]     = dftT[i / 2] * dftQ[i + 1];
            dftU[i + 1] = dftT[i / 2] * dftQ[i];
        }
    }

    fft_high(dftU);
    return dftU;
}

// returns x^k mod Q
template <typename Tp>
inline std::vector<Tp> xk_mod(long long k, const std::vector<Tp> &Q) {
    assert(k >= 0);
    const int degQ = degree(Q);
    assert(degQ >= 0);
    if (degQ == 0) return {};
    if (k < degQ) {
        std::vector<Tp> res(degQ);
        res[k] = 1;
        return res;
    }

    const int len = fft_len(degQ * 2 + 1);
    if (k < len / 2LL) {
        auto invQ = inv(std::vector(Q.rend() - (degQ + 1), Q.rend()), k + 1);
        std::reverse(invQ.begin(), invQ.end());
        invQ.resize(degQ);
        auto res = convolution(invQ, Q);
        res.erase(res.begin(), res.begin() + degQ);
        res.resize(degQ);
        return res;
    }

    // x^k/Q = ... + a_0x^(-1) + ... + a_(deg(Q)-1)x^(-deg(Q)) + ... in R((x^(-1)))
    // x^(-k)/Q(x^(-1)) = ... + a_0x + ... + a_(deg(Q)-1)x^(deg(Q)) + ... in R((x))
    // 1/Q(x^(-1)) = ... + a_0x^(k+1) + ... + a_(deg(Q)-1)x^(deg(Q)+k+1) + ... in R((x))
    // 1/(x^(deg(Q))Q(x^(-1))) = ... + a_0x^(k+1-deg(Q)) + ... in R[[x]]

    auto dftQ = std::vector(Q.rend() - (degQ + 1), Q.rend());
    dftQ.resize(len);
    fft(dftQ);
    std::vector<Tp> dftV(len / 2);
    for (int i = 0; i < len; i += 2) dftV[i / 2] = dftQ[i] * dftQ[i + 1];
    const long long L = k + 1 - degQ;
    const auto dftT   = bostan_mori_power_series(dftV, (L - len / 2 + (L & 1)) / 2);
    std::vector<Tp> dftU(len);
    if (L & 1) {
        auto &&root = FftInfo<Tp>::get().root(len / 2);
        for (int i = 0; i < len; i += 2) {
            dftU[i]     = dftT[i / 2] * dftQ[i + 1] * root[i / 2];
            dftU[i + 1] = dftT[i / 2] * dftQ[i] * -root[i / 2];
        }
    } else {
        for (int i = 0; i < len; i += 2) {
            dftU[i]     = dftT[i / 2] * dftQ[i + 1];
            dftU[i + 1] = dftT[i / 2] * dftQ[i];
        }
    }
    inv_fft(dftU);
    dftU.erase(dftU.begin(), dftU.begin() + len / 2);
    dftU.resize(degQ);
    dftU.resize(len);
    fft(dftU);
    for (int i = 0; i < len; ++i) dftU[i] *= dftQ[i];
    inv_fft(dftU);
    dftU.resize(degQ);
    std::reverse(dftU.begin(), dftU.end());
    return dftU;
}

// returns [x^[L,R)]P/Q
// P: polynomial
// Q: non-zero polynomial, ord(Q)=0
template <typename Tp>
inline std::vector<Tp> slice_coeff_rational(const std::vector<Tp> &P, const std::vector<Tp> &Q,
                                            long long L, long long R) {
    assert(L >= 0);
    assert(order(Q) == 0);
    const int degP = degree(P);
    if (degP < 0) return std::vector<Tp>(R - L);
    const int degQ = degree(Q);
    const int N    = std::max(degP + 1, degQ);
    // for single k>=0:
    // [x^(-k)]P(x^(-1))/Q(x^(-1))
    // [x^0](x^k P(x^(-1)))/Q(x^(-1))
    // P0 := x^(N-1) P((x^(-1))), Q0 := x^N Q(x^(-1))
    // [x^(-1)](x^k P0)/(Q0) = [x^(-1)](x^k P0 mod Q0)/Q0
    auto P0 = P, Q0 = Q;
    P0.resize(N);
    std::reverse(P0.begin(), P0.end());
    Q0.resize(N + 1);
    std::reverse(Q0.begin(), Q0.end());
    auto [q, r] = euclidean_div(convolution(xk_mod(L, Q0), P0), Q0);
    r.resize(N);
    std::reverse(r.begin(), r.end());
    return div(r, Q, R - L);
}

// returns [x^k]P/Q
template <typename Tp>
inline Tp div_at(const std::vector<Tp> &P, const std::vector<Tp> &Q, long long k) {
    return slice_coeff_rational(P, Q, k, k + 1).at(0);
}
