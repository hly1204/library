#pragma once

#include "binomial.hpp"
#include "fft.hpp"
#include <algorithm>
#include <vector>

// apply FPS as linear operator
// F(t): FPS in t where t = d/dx
// p(x): polynomial in x
template<typename Tp> inline std::vector<Tp> apply_egf(std::vector<Tp> F, std::vector<Tp> p) {
    // kinda transposed algorithm of binomial convolution.
    const int n = p.size();
    auto &&bin  = Binomial<Tp>::get(n);
    F.resize(n);
    for (int i = 0; i < n; ++i) {
        F[i] *= bin.inv_factorial(i);
        p[i] *= bin.factorial(i);
    }
    std::reverse(p.begin(), p.end());
    auto res = convolution(F, p);
    res.resize(n);
    std::reverse(res.begin(), res.end());
    for (int i = 0; i < n; ++i) res[i] *= bin.inv_factorial(i);
    return res;
}

template<typename Tp>
inline std::vector<Tp> apply_fps(std::vector<Tp> F, const std::vector<Tp> &p) {
    const int n = p.size();
    auto &&bin  = Binomial<Tp>::get(n);
    F.resize(n);
    for (int i = 0; i < n; ++i) F[i] *= bin.factorial(i);
    return apply_egf(F, p);
}
