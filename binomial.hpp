#pragma once

#include <algorithm>
#include <vector>

template<typename Tp> class Binomial {
    std::vector<Tp> factorial_, invfactorial_;

    Binomial() : factorial_{Tp(1)}, invfactorial_{Tp(1)} {}

    void preprocess(int n) {
        if (const int nn = factorial_.size(); nn < n) {
            int k = nn;
            while (k < n) k *= 2;
            k = std::min<long long>(k, Tp::mod());
            factorial_.resize(k);
            invfactorial_.resize(k);
            for (int i = nn; i < k; ++i) factorial_[i] = factorial_[i - 1] * i;
            invfactorial_.back() = factorial_.back().inv();
            for (int i = k - 2; i >= nn; --i) invfactorial_[i] = invfactorial_[i + 1] * (i + 1);
        }
    }

public:
    static const Binomial &get(int n) {
        static Binomial bin;
        bin.preprocess(n);
        return bin;
    }

    Tp binom(int n, int m) const {
        return n < m ? Tp() : factorial_[n] * invfactorial_[m] * invfactorial_[n - m];
    }
    Tp inv(int n) const { return factorial_[n - 1] * invfactorial_[n]; }
    Tp factorial(int n) const { return factorial_[n]; }
    Tp inv_factorial(int n) const { return invfactorial_[n]; }
};
