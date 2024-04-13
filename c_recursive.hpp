#pragma once

#include "fft.hpp"
#include "fps_basic.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

// returns [x^k]P/Q
// see: https://arxiv.org/abs/2008.08822
// Alin Bostan, Ryuhei Mori.
// A Simple and Fast Algorithm for Computing the N-th Term of a Linearly Recurrent Sequence
template <typename Tp>
inline Tp div_at(const std::vector<Tp> &P, std::vector<Tp> Q, long long k) {
    auto ord = [](const std::vector<Tp> &a) {
        for (int i = 0; i < (int)a.size(); ++i)
            if (a[i] != 0) return i;
        return -1;
    };
    auto iszero       = [&](const std::vector<Tp> &a) { return ord(a) == -1; };
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
    if (P.empty()) return Tp();
    if (int ordQ = ord(Q)) {
        Q.erase(Q.begin(), Q.begin() + ordQ);
        k += ordQ;
    }

    assert(k >= 0);
    if (k < P.size()) return div(P, Q, k + 1).at(k);

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
        if (k < P.size()) {
            inv_fft(dftP);
            inv_fft(dftQ);
            return div(P, Q, k + 1).at(k);
        }

        fft_doubling(dftP);
        fft_doubling(dftQ);
    }
}
