#pragma once

#include "binomial.hpp"
#include "fps_basic.hpp"
#include <cassert>
#include <vector>

// returns SEQ(A)=1/(1-a)
template <typename Tp>
inline std::vector<Tp> polya_q(std::vector<Tp> a, int n) {
    if (n <= 0) return {};
    a.resize(n);
    assert(a[0] == 0);
    for (int i = 1; i < n; ++i) a[i] = -a[i];
    return inv(a, n);
}

// returns MSET(A)=exp(a(x)+a(x^2)/2+a(x^3)/3+...)
template <typename Tp>
inline std::vector<Tp> polya_exp(std::vector<Tp> a, int n) {
    if (n <= 0) return {};
    a.resize(n);
    assert(a[0] == 0);
    auto &&bin = Binomial<Tp>::get(n);
    for (int i = n - 1; i > 0; --i)
        for (int j = 2; i * j < n; ++j) a[i * j] += a[i] * bin.inv(j);
    return exp(a, n);
}

// returns PSET(A)=exp(a(x)-a(x^2)/2+a(x^3)/3-...)
template <typename Tp>
inline std::vector<Tp> polya_exp_m(std::vector<Tp> a, int n) {
    if (n <= 0) return {};
    a.resize(n);
    assert(a[0] == 0);
    auto &&bin = Binomial<Tp>::get(n);
    for (int i = n - 1; i > 0; --i)
        for (int j = 2; i * j < n; ++j)
            if (j & 1) {
                a[i * j] += a[i] * bin.inv(j);
            } else {
                a[i * j] -= a[i] * bin.inv(j);
            }
    return exp(a, n);
}
