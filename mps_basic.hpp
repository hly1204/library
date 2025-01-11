#pragma once

#include "binomial.hpp"
#include "fft.hpp"
#include "md_conv.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

template <typename Tp>
inline std::vector<Tp> mps_inv(const MDConvInfo &info, const std::vector<Tp> &a) {
    assert((int)a.size() == info.len());
    assert(a[0] != 0);
    const auto bound = info.degree_bound();
    std::vector<Tp> res(info.len());
    res[0] = a[0].inv();
    std::vector<int> d(info.dim());
    for (int i = 0, pp = 1; i < (int)bound.size(); pp *= bound[i++]) {
        for (d[i] = 1; d[i] < bound[i]; d[i] = std::min(d[i] * 2, bound[i])) {
            auto nextd     = std::vector(d.begin(), d.begin() + (i + 1));
            nextd[i]       = std::min(d[i] * 2, bound[i]);
            const int len  = fft_len(pp * nextd[i]);
            const auto chi = MDConvInfo(nextd).chi();
            std::vector shopA(i + 1, std::vector<Tp>(len));
            std::vector shopB(i + 1, std::vector<Tp>(len));
            for (int j = 0; j < pp * nextd[i]; ++j) shopA[chi[j]][j] = a[j];
            for (int j = 0; j < pp * d[i]; ++j) shopB[chi[j]][j] = res[j];
            for (int j = 0; j <= i; ++j) fft(shopA[j]), fft(shopB[j]);
            shopA = detail::multidimensional_hadamard(shopA, shopB, i + 1, len);
            for (int j = 0; j <= i; ++j) inv_fft(shopA[j]);
            {
                std::vector<Tp> shopC(pp * (nextd[i] - d[i]));
                for (int j = pp * d[i]; j < pp * nextd[i]; ++j)
                    shopC[j - pp * d[i]] = shopA[chi[j]][j];
                for (int j = 0; j <= i; ++j) std::fill(shopA[j].begin(), shopA[j].end(), Tp(0));
                for (int j = pp * d[i]; j < pp * nextd[i]; ++j)
                    shopA[chi[j]][j] = shopC[j - pp * d[i]];
            }
            for (int j = 0; j <= i; ++j) fft(shopA[j]);
            shopA = detail::multidimensional_hadamard(shopA, shopB, i + 1, len);
            for (int j = 0; j <= i; ++j) inv_fft(shopA[j]);
            for (int j = pp * d[i]; j < pp * nextd[i]; ++j) res[j] = -shopA[chi[j]][j];
        }
    }
    return res;
}

// see:
// [1]: Elegia. Hello, multivariate multiplication.
//      https://www.luogu.com/article/wje8kchr
template <typename Tp>
inline std::vector<Tp> mps_deriv(std::vector<Tp> a) {
    for (int i = 0; i < (int)a.size(); ++i) a[i] *= i;
    return a;
}

template <typename Tp>
inline std::vector<Tp> mps_integr(std::vector<Tp> a, Tp c = {}) {
    auto &&bin = Binomial<Tp>::get(a.size());
    a[0]       = c;
    for (int i = 1; i < (int)a.size(); ++i) a[i] *= bin.inv(i);
    return a;
}

template <typename Tp>
inline std::vector<Tp> mps_log(const MDConvInfo &info, const std::vector<Tp> &a) {
    assert((int)a.size() == info.len());
    assert(a[0] == 1);
    return mps_integr(multidimensional_convolution(info, mps_deriv(a), mps_inv(info, a)));
}

template <typename Tp>
inline std::vector<Tp> mps_exp(const MDConvInfo &info, const std::vector<Tp> &a) {
    assert((int)a.size() == info.len());
    assert(a[0] == 0);
    const auto bound = info.degree_bound();
    std::vector<Tp> res(info.len());
    res[0] = 1;
    std::vector<int> d(info.dim());
    for (int i = 0, pp = 1; i < (int)bound.size(); pp *= bound[i++]) {
        for (d[i] = 1; d[i] < bound[i]; d[i] = std::min(d[i] * 2, bound[i])) {
            auto nextd = std::vector(d.begin(), d.begin() + (i + 1));
            nextd[i]   = std::min(d[i] * 2, bound[i]);
            const MDConvInfo ainfo(nextd);
            auto shopA = mps_log(ainfo, std::vector(res.begin(), res.begin() + pp * nextd[i]));
            std::fill_n(shopA.begin(), pp * d[i], Tp(0));
            for (int j = pp * d[i]; j < pp * nextd[i]; ++j) shopA[j] -= a[j];
            shopA = multidimensional_convolution(
                ainfo, std::vector(res.begin(), res.begin() + pp * nextd[i]), shopA);
            for (int j = pp * d[i]; j < pp * nextd[i]; ++j) res[j] = -shopA[j];
        }
    }
    return res;
}
