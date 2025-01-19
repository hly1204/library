#pragma once

#include "fft.hpp"
#include <cassert>
#include <functional>
#include <numeric>
#include <vector>

class MDConvInfo {
    int len_;
    std::vector<int> degree_bound_;

public:
    explicit MDConvInfo(const std::vector<int> &d)
        : len_(std::accumulate(d.begin(), d.end(), 1, std::multiplies<>())), degree_bound_(d) {}

    int len() const { return len_; }
    int dim() const { return degree_bound_.size(); }
    std::vector<int> degree_bound() const { return degree_bound_; }

    // see:
    // [1]: Elegia. Hello, multivariate multiplication.
    //      https://www.luogu.com/article/wje8kchr
    std::vector<int> chi() const {
        auto pp = degree_bound_;
        for (int i = 1; i < (int)pp.size(); ++i) pp[i] *= pp[i - 1];
        std::vector<int> diff(pp.size());
        // O(max(dim^2, len))
        for (int i = 1; i < (int)diff.size(); ++i) {
            for (int j = 0; j < i; ++j) diff[i] += pp[i - 1] / pp[j];
            diff[i] %= dim();
        }
        std::vector<int> c(len());
        for (int i = 1; i < (int)pp.size(); ++i)
            for (int j = pp[i - 1]; j < pp[i]; ++j)
                if ((c[j] = c[j - pp[i - 1]] + diff[i]) >= dim()) c[j] -= dim();
        return c;
    }
};

namespace detail {

template<typename Tp>
inline std::vector<std::vector<Tp>> multidimensional_hadamard(const std::vector<std::vector<Tp>> &a,
                                                              const std::vector<std::vector<Tp>> &b,
                                                              int dim, int len) {
    std::vector c(dim, std::vector<Tp>(len));
    for (int i = 0; i < dim; ++i)
        for (int j = 0; j < dim; ++j) {
            const int k = (i + j) % dim;
            for (int l = 0; l < len; ++l) c[k][l] += a[i][l] * b[j][l];
        }
    return c;
}

} // namespace detail

template<typename Tp>
inline std::vector<Tp> multidimensional_convolution(const MDConvInfo &info,
                                                    const std::vector<Tp> &a,
                                                    const std::vector<Tp> &b) {
    assert((int)a.size() == info.len());
    assert((int)b.size() == info.len());
    if (info.dim() == 0) return {a[0] * b[0]};
    const int len = fft_len(info.len() * 2 - 1);
    std::vector aa(info.dim(), std::vector<Tp>(len));
    std::vector bb(info.dim(), std::vector<Tp>(len));
    const auto chi = info.chi();
    for (int i = 0; i < info.len(); ++i) aa[chi[i]][i] = a[i], bb[chi[i]][i] = b[i];
    for (int i = 0; i < info.dim(); ++i) fft(aa[i]), fft(bb[i]);
    auto cc = detail::multidimensional_hadamard(aa, bb, info.dim(), len);
    for (int i = 0; i < info.dim(); ++i) inv_fft(cc[i]);
    std::vector<Tp> c(info.len());
    for (int i = 0; i < info.len(); ++i) c[i] = cc[chi[i]][i];
    return c;
}
