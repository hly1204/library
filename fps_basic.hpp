#pragma once

#include "binomial.hpp"
#include "semi_relaxed_conv.hpp"
#include <cassert>
#include <vector>

template <typename Tp>
inline int order(const std::vector<Tp> &a) {
    for (int i = 0; i < (int)a.size(); ++i)
        if (a[i] != 0) return i;
    return -1;
}

template <typename Tp>
inline std::vector<Tp> inv(const std::vector<Tp> &a, int n) {
    assert(!a.empty());
    if (n <= 0) return {};
    return semi_relaxed_convolution(
        a, [v = a[0].inv()](int n, auto &&c) { return n == 0 ? v : -c[n] * v; }, n);
}

template <typename Tp>
inline std::vector<Tp> div(const std::vector<Tp> &a, const std::vector<Tp> &b, int n) {
    assert(!b.empty());
    if (n <= 0) return {};
    return semi_relaxed_convolution(
        b,
        [&, v = b[0].inv()](int n, auto &&c) {
            if (n < (int)a.size()) return (a[n] - c[n]) * v;
            return -c[n] * v;
        },
        n);
}

template <typename Tp>
inline std::vector<Tp> deriv(const std::vector<Tp> &a) {
    const int n = (int)a.size() - 1;
    if (n <= 0) return {};
    std::vector<Tp> res(n);
    for (int i = 1; i <= n; ++i) res[i - 1] = a[i] * i;
    return res;
}

template <typename Tp>
inline std::vector<Tp> integr(const std::vector<Tp> &a, Tp c = {}) {
    const int n = a.size() + 1;
    auto &&bin  = Binomial<Tp>::get(n);
    std::vector<Tp> res(n);
    res[0] = c;
    for (int i = 1; i < n; ++i) res[i] = a[i - 1] * bin.inv(i);
    return res;
}

template <typename Tp>
inline std::vector<Tp> log(const std::vector<Tp> &a, int n) {
    return integr(div(deriv(a), a, n - 1));
}

template <typename Tp>
inline std::vector<Tp> exp(const std::vector<Tp> &a, int n) {
    if (n <= 0) return {};
    assert(!a.empty() && a[0] == 0);
    return semi_relaxed_convolution(
        deriv(a),
        [bin = Binomial<Tp>::get(n)](int n, auto &&c) {
            return n == 0 ? Tp(1) : c[n - 1] * bin.inv(n);
        },
        n);
}

template <typename Tp>
inline std::vector<Tp> pow(std::vector<Tp> a, long long e, int n) {
    if (n <= 0) return {};
    if (e == 0) {
        std::vector<Tp> res(n);
        res[0] = 1;
        return res;
    }

    const int o = order(a);
    if (o < 0 || o > n / e || (o == n / e && n % e == 0)) return std::vector<Tp>(n);
    if (o != 0) a.erase(a.begin(), a.begin() + o);

    const Tp ia0 = a[0].inv();
    const Tp a0e = a[0].pow(e);
    const Tp me  = e;

    for (int i = 0; i < (int)a.size(); ++i) a[i] *= ia0;
    a = log(a, n - o * e);
    for (int i = 0; i < (int)a.size(); ++i) a[i] *= me;
    a = exp(a, n - o * e);
    for (int i = 0; i < (int)a.size(); ++i) a[i] *= a0e;

    a.insert(a.begin(), o * e, 0);
    return a;
}
