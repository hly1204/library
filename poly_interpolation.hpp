#pragma once

#include "binomial.hpp"
#include <cassert>
#include <vector>

// returns f
// x: x_0,...
// y: f(x_0),...
template <typename Tp>
inline std::vector<Tp> lagrange_interpolation_naive(const std::vector<Tp> &x,
                                                    const std::vector<Tp> &y) {
    assert(x.size() == y.size());
    const int n = x.size();
    std::vector<Tp> M(n + 1), xx(n), f(n);
    M[0] = 1;
    for (int i = 0; i < n; ++i)
        for (int j = i; j >= 0; --j) M[j + 1] += M[j], M[j] *= -x[i];
    for (int i = n - 1; i >= 0; --i)
        for (int j = 0; j < n; ++j) xx[j] = xx[j] * x[j] + M[i + 1] * (i + 1);
    for (int i = 0; i < n; ++i) {
        Tp t = y[i] / xx[i], k = M[n];
        for (int j = n - 1; j >= 0; --j) f[j] += k * t, k = M[j] + k * x[i];
    }
    return f;
}

// returns f(c)
// f: polynomial f -> f[0]=f(0),...
template <typename Tp>
inline Tp lagrange_interpolation_iota(const std::vector<Tp> &f, Tp c) {
    if (f.empty()) return 0;
    const int n = f.size();
    auto &&bin  = Binomial<Tp>::get(n);
    std::vector<Tp> k(n);
    k[0] = f[0];
    Tp v = 1;
    for (int i = 1; i < n; ++i) k[i] = f[i] * (v *= (c - (i - 1)) * bin.inv(i));
    Tp res = k[n - 1];
    v      = 1;
    for (int i = n - 2; i >= 0; --i) res += k[i] * (v *= -(c - (i + 1)) * bin.inv(n - 1 - i));
    return res;
}
