#pragma once

#include "binomial.hpp"
#include "fft.hpp"
#include <algorithm>
#include <vector>

template<typename Tp> inline std::vector<Tp> sample_points_to_ffp(const std::vector<Tp> &F) {
    const int n = F.size();
    auto &&bin  = Binomial<Tp>::get(n);
    std::vector<Tp> egfF(F), ee(n);
    for (int i = 0; i < n; ++i) {
        egfF[i] *= bin.inv_factorial(i);
        ee[i] = bin.inv_factorial(i);
        if (i & 1) ee[i] = -ee[i];
    }
    auto ffp = convolution(egfF, ee);
    ffp.resize(n);
    return ffp;
}

template<typename Tp>
inline std::vector<Tp> ffp_to_sample_points(const std::vector<Tp> &ffp, int n) {
    auto &&bin = Binomial<Tp>::get(n);
    std::vector<Tp> ee(n);
    for (int i = 0; i < n; ++i) ee[i] = bin.inv_factorial(i);
    auto F = convolution(std::vector(ffp.begin(), ffp.begin() + std::min<int>(n, ffp.size())), ee);
    F.resize(n);
    for (int i = 0; i < n; ++i) F[i] *= bin.factorial(i);
    return F;
}

template<typename Tp> inline std::vector<Tp> shift_ffp(std::vector<Tp> ffp, Tp c) {
    const int n = ffp.size();
    auto &&bin  = Binomial<Tp>::get(n);
    std::vector<Tp> C(n);
    Tp cc = 1;
    for (int i = 0; i < n; ++i) {
        ffp[i] *= bin.factorial(i);
        C[i] = cc * bin.inv_factorial(i);
        cc *= c - i;
    }
    std::reverse(ffp.begin(), ffp.end());
    auto res = convolution(ffp, C);
    res.resize(n);
    std::reverse(res.begin(), res.end());
    for (int i = 0; i < n; ++i) res[i] *= bin.inv_factorial(i);
    return res;
}
