#pragma once

#include "fft.hpp"
#include <cassert>
#include <iostream>
#include <vector>

// see:
// [1]: Elegia. Hello, multivariate multiplication.
//      https://www.luogu.com/article/wje8kchr
// [2]: rushcheyo. 集训队互测 2021 Round #1 题解.
//      https://rushcheyo.blog.uoj.ac/blog/6547
template <typename Tp>
class MDConvInfo {
    int len_;
    std::vector<int> degree_bound_;
    std::vector<int> prefix_prod_degree_bound_;
    std::vector<int> chi_;

public:
    MDConvInfo(const std::vector<int> &d) : len_(1), degree_bound_(d) {
        for (auto deg : degree_bound_) {
            assert(deg > 1);
            len_ *= deg;
        }
        chi_.resize(len_);
        auto &&pp = prefix_prod_degree_bound_ = degree_bound_;
        for (int i = 1; i < (int)pp.size(); ++i) pp[i] *= pp[i - 1];
        for (int i = 1; i < len_; ++i) {
            // chi(i) = floor(i/d[0]) + floor(i/(d[0]*d[1])) + ... + floor(i/(d[0]*...))
            for (int j = 0; j < (int)pp.size() - 1; ++j) chi_[i] += i / pp[j];
            chi_[i] %= (int)pp.size();
        }
    }

    int dim() const { return degree_bound_.size(); }
    const std::vector<int> &degree_bound() const { return degree_bound_; }
    const std::vector<int> &chi() const { return chi_; }

    std::vector<Tp> convolution(const std::vector<Tp> &a, const std::vector<Tp> &b) const {
        assert((int)a.size() == len_);
        assert((int)b.size() == len_);
        const int d = dim();
        if (d == 0) return {a[0] * b[0]};
        const int len = fft_len(len_ * 2 - 1);
        std::vector aa(d, std::vector<Tp>(len));
        std::vector bb(d, std::vector<Tp>(len));
        std::vector aabb(d, std::vector<Tp>(len));
        for (int i = 0; i < len_; ++i) {
            aa[chi_[i]][i] = a[i];
            bb[chi_[i]][i] = b[i];
        }
        for (int i = 0; i < d; ++i) {
            fft(aa[i]);
            fft(bb[i]);
        }
        for (int i = 0; i < d; ++i) {
            for (int j = 0; j < d; ++j) {
                const int k = (i + j) % d;
                for (int l = 0; l < len; ++l) aabb[k][l] += aa[i][l] * bb[j][l];
            }
        }
        for (int i = 0; i < d; ++i) inv_fft(aabb[i]);
        std::vector<Tp> ab(len_);
        for (int i = 0; i < len_; ++i) ab[i] = aabb[chi_[i]][i];
        return ab;
    }

    std::ostream &pretty_print(std::ostream &os, const std::vector<Tp> &a) const {
        assert((int)a.size() == len_);
        os << '[';
        std::vector<int> deg(dim());
        for (int i = 0; i < len_; ++i) {
            if (i) os << " + ";
            os << a[i];
            for (int j = 0; j < (int)deg.size(); ++j) os << "*x" << j << "^(" << deg[j] << ')';
            for (int j = 0; j < (int)deg.size(); ++j) {
                if (++deg[j] < degree_bound_[j]) break;
                deg[j] = 0;
            }
        }
        return os << ']';
    }
};
