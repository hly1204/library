#pragma once

#include "fft.hpp"
#include "fps_basic.hpp"
#include "poly_basic.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

// returns [x^k]P/Q
// see: https://arxiv.org/abs/2008.08822
// Alin Bostan, Ryuhei Mori.
// A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence
template <typename Tp>
inline Tp div_at(const std::vector<Tp> &P, std::vector<Tp> Q, long long k) {
    auto iszero       = [](const std::vector<Tp> &a) { return order(a) == -1; };
    auto fft_doubling = [](std::vector<Tp> &a) {
        const int n = a.size();
        a.resize(n * 2);
        std::copy_n(a.begin(), n, a.begin() + n);
        inv_fft_n(a.begin() + n, n);
        Tp k         = 1;
        const auto t = FftInfo<Tp>::get().root(n).at(n / 2);
        for (int i = 0; i < n; ++i) a[i + n] *= k, k *= t;
        fft_n(a.begin() + n, n);
    };

    assert(!iszero(Q));
    if (P.empty()) return 0;
    if (const int ordQ = order(Q)) {
        Q.erase(Q.begin(), Q.begin() + ordQ);
        k += ordQ;
    }

    assert(k >= 0);
    if (k < (int)P.size()) return div(P, Q, k + 1).at(k);

    const int len = fft_len(std::max(P.size() + Q.size(), Q.size() * 2) - 1);
    std::vector<Tp> dftP(P), dftQ(Q);
    dftP.resize(len);
    dftQ.resize(len);
    fft(dftP);
    fft(dftQ);

    for (;;) {
        if (k & 1) {
            auto &&root = FftInfo<Tp>::get().inv_root(len / 2);
            for (int i = 0; i < len; i += 2)
                dftP[i / 2] =
                    (dftP[i] * dftQ[i + 1] - dftP[i + 1] * dftQ[i]).div_by_2() * root[i / 2];
        } else {
            for (int i = 0; i < len; i += 2)
                dftP[i / 2] = (dftP[i] * dftQ[i + 1] + dftP[i + 1] * dftQ[i]).div_by_2();
        }
        dftP.resize(len / 2);
        for (int i = 0; i < len; i += 2) dftQ[i / 2] = dftQ[i] * dftQ[i + 1];
        dftQ.resize(len / 2);

        k /= 2;
        if (k < (int)P.size()) {
            inv_fft(dftP);
            inv_fft(dftQ);
            return div(dftP, dftQ, k + 1).at(k);
        }

        fft_doubling(dftP);
        fft_doubling(dftQ);
    }
}

// returns [x^[L,R)]P/Q
// P: polynomial
// Q: non-zero polynomial
// deg(P) < deg(Q)
template <typename Tp>
inline std::vector<Tp> slice_coeff_rationalA(std::vector<Tp> P, std::vector<Tp> Q, long long L,
                                             long long R) {
    if (R <= L) return {};

    if (const int ordQ = order(Q)) {
        Q.erase(Q.begin(), Q.begin() + ordQ);
        L += ordQ;
        R += ordQ;
    }

    assert(L >= 0);
    if (L == 0) return div(P, Q, R - L);

    const int degP = degree(P);
    const int degQ = degree(Q);
    if (degP < 0) std::vector<Tp> res(R - L);
    assert(degP < degQ);
    if (degQ == 0) {
        std::vector<Tp> res(R - L);
        const auto iQ0 = Q[0].inv();
        for (long long i = L; i < R && i < (long long)P.size(); ++i) res[i - L] = P[i] * iQ0;
        return res;
    }

    auto fft_doubling = [](std::vector<Tp> &a) {
        const int n = a.size();
        a.resize(n * 2);
        std::copy_n(a.begin(), n, a.begin() + n);
        inv_fft_n(a.begin() + n, n);
        Tp k         = 1;
        const auto t = FftInfo<Tp>::get().root(n).at(n / 2);
        for (int i = 0; i < n; ++i) a[i + n] *= k, k *= t;
        fft_n(a.begin() + n, n);
    };

    auto fft_doubling2 = [](std::vector<Tp> &a) {
        const int n = a.size();
        a.resize(n * 2);
        std::copy_n(a.begin(), n, a.begin() + n);
        inv_fft_n(a.begin() + n, n);
        const std::vector b(a.begin() + n, a.end());
        Tp k         = 1;
        const auto t = FftInfo<Tp>::get().root(n).at(n / 2);
        for (int i = 0; i < n; ++i) a[i + n] *= k, k *= t;
        fft_n(a.begin() + n, n);
        return b;
    };

    auto fft_high = [](std::vector<Tp> &a) {
        const int n = a.size();
        inv_fft_n(a.begin() + n / 2, n / 2);
        Tp k         = 1;
        const auto t = FftInfo<Tp>::get().inv_root(n / 2).at(n / 4);
        for (int i = 0; i < n / 2; ++i) a[i + n / 2] *= k, k *= t;
        fft_n(a.begin() + n / 2, n / 2);
        for (int i = 0; i < n / 2; ++i) a[i] = (a[i] - a[i + n / 2]).div_by_2();
        a.resize(n / 2);
    };

    const int len = fft_len(degQ * 2 + 1);

    // returns DFT([x^[L,L+len/2)]1/Q)
    // len/2 > degQ, len/2 is even
    auto rec = [len, &fft_doubling, &fft_high](auto &&rec, std::vector<Tp> dftQ, long long L) {
        if (L <= 0) {
            inv_fft(dftQ);
            auto invQ = inv(dftQ, L + len / 2);
            invQ.insert(invQ.begin(), -L, 0);
            fft(invQ);
            return invQ;
        }

        if ((int)dftQ.size() < len) fft_doubling(dftQ);
        std::vector<Tp> dftV(len / 2);
        for (int i = 0; i < len; i += 2) dftV[i / 2] = dftQ[i] * dftQ[i + 1];
        const auto dftT = rec(rec, dftV, (L - len / 2 + (L & 1)) / 2);

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
    };

    auto dftQ = Q;
    dftQ.resize(len);
    fft(dftQ);
    auto dftinvQ    = rec(rec, dftQ, L - degP);
    const auto invQ = fft_doubling2(dftinvQ); // [x^[L-degP,L-degP+(len/2))]1/Q
    std::vector<Tp> U(len);
    for (int i = 0; i < len; ++i) U[i] = dftQ[i] * dftinvQ[i];
    inv_fft(U);
    U.resize(degQ);
    // U/Q = invQ[L-degP..]
    std::vector xinvQ(invQ.begin(), invQ.begin() + degP);
    const int convlen = fft_len(degP + degQ);
    xinvQ.resize(convlen);
    fft(xinvQ);
    for (int i = 0; i < convlen; ++i) xinvQ[i] *= dftQ[i];
    inv_fft(xinvQ);
    for (int i = degP; i < degQ; ++i) xinvQ[i] = U[i] - xinvQ[i];
    for (int i = degQ; i < degP + degQ; ++i) xinvQ[i] = -xinvQ[i];
    xinvQ.erase(xinvQ.begin(), xinvQ.begin() + degP);
    xinvQ = div(xinvQ, Q, degQ); // [x^[L,L+degQ)]1/Q
    xinvQ.insert(xinvQ.begin(), invQ.begin(), invQ.begin() + degP);

    xinvQ.resize(convlen);
    P.resize(convlen);
    fft(xinvQ);
    fft(P);
    for (int i = 0; i < convlen; ++i) P[i] *= xinvQ[i];
    inv_fft(P);
    P.erase(P.begin(), P.begin() + degP);
    P.resize(degQ);

    const int aconvlen = fft_len(degQ * 2);
    P.resize(aconvlen);
    fft(P);
    for (int i = 0; i < aconvlen; ++i) P[i] *= dftQ[i];
    inv_fft(P);
    P.resize(degQ);
    return div(P, Q, R - L);
}

// returns [x^[L,R)]P/Q
// P: polynomial
// Q: non-zero polynomial
template <typename Tp>
inline std::vector<Tp> slice_coeff_rational(const std::vector<Tp> &P, const std::vector<Tp> &Q,
                                            long long L, long long R) {
    auto [q, r] = euclidean_div(P, Q);
    auto res    = slice_coeff_rationalA(r, Q, L, R);
    for (long long i = L; i < std::min<long long>(R, q.size()); ++i) res[i - L] += q[i];
    return res;
}
