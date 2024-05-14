#pragma once

#include <cassert>
#include <vector>

template <typename Tp>
std::vector<Tp> lagrange_interpolation_naive(const std::vector<Tp> &x, const std::vector<Tp> &y) {
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
