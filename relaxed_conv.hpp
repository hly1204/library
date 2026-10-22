#pragma once

#include "fft.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

template<typename Tp> class RelaxedConvolution {
    std::vector<Tp> L_, R_, P_ = {Tp(0), Tp(0), Tp(0), Tp(0)};
    std::vector<std::vector<Tp>> dftL_, dftR_;
    int N_ = 0;

public:
    const std::vector<Tp> &lhs() const { return L_; }
    const std::vector<Tp> &rhs() const { return R_; }
    const std::vector<Tp> &prod() const { return P_; }
    int count() const { return N_; }
    // returns [x^n] L*R
    // call operator[](n) when count=n to get [x^n] L*R - L(0) * [x^n] R - [x^n] L * R(0)
    Tp operator[](int n) const { return P_[n]; }
    Tp peek() const { return P_[N_]; }

    // set [x^N] L = l and [x^N] R = r
    // returns [x^N] L*R
    Tp push(const Tp &l, const Tp &r) {
        L_.emplace_back(l);
        R_.emplace_back(r);
        if (__builtin_expect(N_ > 1, 1)) {
            P_.emplace_back();
            P_.emplace_back();
            P_[N_] += l * R_[0] + L_[0] * r;
            P_[N_ + 1] += L_[1] * R_[N_] + L_[N_] * R_[1];
            for (int sft = 1, os = fft_len(N_ + 1) / 2, t = N_ + 1 - os;
                 (t & 1) == 0 && 1 << sft < os; ++sft, t /= 2) {
                std::vector<Tp> P0(2 << sft), P1(2 << sft);
                std::copy_n(L_.begin() + (N_ + 1 - (1 << sft)), 1 << sft, P0.begin());
                std::copy_n(R_.begin() + (N_ + 1 - (1 << sft)), 1 << sft, P1.begin());
                fft(P0);
                fft(P1);
                for (int i = 0; i < 2 << sft; ++i)
                    P0[i] = P0[i] * dftR_[sft - 1][i] + P1[i] * dftL_[sft - 1][i];
                inv_fft(P0);
                for (int i = 0; i < (2 << sft) - 1; ++i) P_[N_ + 1 + i] += P0[i];
            }
            if (((N_ + 1) & N_) == 0) {
                auto &&LL = dftL_.emplace_back(N_ + 1);
                auto &&RR = dftR_.emplace_back(N_ + 1);
                std::copy_n(L_.begin() + (N_ + 1) / 2, (N_ + 1) / 2, LL.begin());
                std::copy_n(R_.begin() + (N_ + 1) / 2, (N_ + 1) / 2, RR.begin());
                fft(LL);
                fft(RR);
                auto PP = LL;
                for (int i = 0; i < N_ + 1; ++i) PP[i] *= RR[i];
                inv_fft(PP);
                for (int i = 0; i < N_; ++i) P_[N_ + 1 + i] += PP[i];
            }
        } else {
            if (N_ == 0) P_[0] = l * r;
            if (N_ == 1) P_[1] = l * R_[0] + L_[0] * r, P_[2] = L_[1] * R_[1];
        }
        return P_[N_++];
    }
};

template<typename Tp> class RelaxedFPSInv {
    // f * 1/f = 1
    // [x^N] f * 1/f = R.peek() + f(0) * [x^N] (1/f) + ([x^N] f) * f(0)^-1
    //               = delta(N=0)
public:
    RelaxedConvolution<Tp> R;
    Tp Inv0;

    Tp push(const Tp &c) {
        if (__builtin_expect(R.count() > 0, 1)) {
            const Tp res = -(R.peek() + c * Inv0) * Inv0;
            R.push(c, res);
            return res;
        }
        assert(c != 0);
        R.push(c, Inv0 = c.inv());
        return Inv0;
    }
};

template<typename Tp> class RelaxedFPSDiv {
    // f/g * g = f
    // [x^N] f/g * g = R.peek() + (f/g)(0) * [x^N] g + ([x^N] f/g) * g(0)
    //               = [x^N] f
public:
    RelaxedConvolution<Tp> R;
    Tp Inv0;

    Tp push(const Tp &p, const Tp &q) {
        if (__builtin_expect(R.count() > 0, 1)) {
            const Tp res = (p - R.peek() - R.lhs().front() * q) * Inv0;
            R.push(res, q);
            return res;
        }
        assert(q != 0);
        const Tp res = p * (Inv0 = q.inv());
        R.push(res, q);
        return res;
    }
};

template<typename Tp> class RelaxedFPSLog {
public:
    RelaxedFPSDiv<Tp> R;
    Tp LastCoeff = Tp(1);
    bool First   = true;

    Tp push(const Tp &c) {
        if (__builtin_expect(!First, 1)) {
            const int ind = R.R.count() + 1;
            const Tp res  = R.push(c * ind, LastCoeff) / ind;
            LastCoeff     = c;
            return res;
        }
        assert(c == 1);
        First = false;
        return Tp(0);
    }
};

template<typename Tp> class RelaxedFPSExp {
    // D(exp(f)) = exp(f) * D(f)
public:
    RelaxedConvolution<Tp> R;
    Tp LastCoeff = Tp(1);
    bool First   = true;

    Tp push(const Tp &c) {
        if (__builtin_expect(!First, 1)) {
            const int ind = R.count() + 1;
            const Tp res  = R.push(LastCoeff, c * ind) / ind;
            LastCoeff     = res;
            return res;
        }
        assert(c == 0);
        First = false;
        return Tp(1);
    }
};
