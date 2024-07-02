#pragma once

#include <algorithm>
#include <cassert>
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>

// Schoolbook Polynomial
template <typename Tp>
class SBPoly : public std::vector<Tp> {
    using Base = std::vector<Tp>;

public:
    using Base::Base;

    int deg() const {
        for (int i = (int)Base::size() - 1; i >= 0; --i)
            if (Base::operator[](i) != 0) return i;
        return -1;
    }

    int ord() const {
        for (int i = 0; i < (int)Base::size(); ++i)
            if (Base::operator[](i) != 0) return i;
        return -1;
    }

    SBPoly rev() const {
        const int d = deg();
        SBPoly res(d + 1);
        for (int i = d; i >= 0; --i) res[i] = Base::operator[](d - i);
        return res;
    }

    SBPoly slice(int L, int R) const {
        SBPoly res(R - L);
        for (int i = L; i < std::min(R, (int)Base::size()); ++i) res[i - L] = Base::operator[](i);
        return res;
    }

    SBPoly trunc(int D) const {
        SBPoly res(D);
        for (int i = 0; i < std::min(D, (int)Base::size()); ++i) res[i] = Base::operator[](i);
        return res;
    }

    SBPoly &shrink() {
        Base::resize(deg() + 1);
        return *this;
    }

    Tp lc() const {
        const int d = deg();
        return d == -1 ? Tp() : Base::operator[](d);
    }

    SBPoly operator-() const {
        const int d = deg();
        SBPoly res(d + 1);
        for (int i = 0; i <= d; ++i) res[i] = -Base::operator[](i);
        res.shrink();
        return res;
    }

    // O(deg(Q)deg(R))
    std::pair<SBPoly, SBPoly> divmod(const SBPoly &R) const {
        const int degL = deg(), degR = R.deg(), degQ = degL - degR;
        assert(degR >= 0);
        SBPoly quo(degQ + 1), rem(*this);
        if (degQ >= 0) {
            const auto inv = R.lc().inv();
            for (int i = degQ, n = degL; i >= 0; --i)
                if ((quo[i] = rem[n--] * inv) != 0)
                    for (int j = 0; j <= degR; ++j) rem[i + j] -= quo[i] * R[j];
        }
        rem.shrink();
        return std::make_pair(quo, rem);
    }
    SBPoly &operator+=(const SBPoly &R) {
        if (Base::size() < R.size()) Base::resize(R.size());
        for (int i = 0; i < (int)R.size(); ++i) Base::operator[](i) += R[i];
        return shrink();
    }
    SBPoly &operator-=(const SBPoly &R) {
        if (Base::size() < R.size()) Base::resize(R.size());
        for (int i = 0; i < (int)R.size(); ++i) Base::operator[](i) -= R[i];
        return shrink();
    }
    SBPoly &operator*=(const SBPoly &R) {
        const int degL = deg(), degR = R.deg();
        if (degL < 0 || degR < 0) {
            Base::clear();
            return *this;
        }
        SBPoly res(degL + degR + 1);
        for (int i = 0; i <= degL; ++i)
            for (int j = 0; j <= degR; ++j) res[i + j] += Base::operator[](i) * R[j];
        Base::swap(res);
        return *this;
    }
    // O(min(deg(Q)^2,deg(Q)deg(R)))
    SBPoly &operator/=(const SBPoly &R) {
        const int degL = deg(), degR = R.deg(), degQ = degL - degR;
        assert(degR >= 0);
        if (degQ < 0) {
            Base::clear();
            return *this;
        }
        SBPoly quo(degQ + 1);
        const auto inv = R.lc().inv();
        for (int i = 0; i <= degQ; ++i) {
            for (int j = 1; j <= std::min(i, degR); ++j)
                quo[degQ - i] += R[degR - j] * quo[degQ - i + j];
            quo[degQ - i] = (Base::operator[](degL - i) - quo[degQ - i]) * inv;
        }
        Base::swap(quo);
        return *this;
    }
    SBPoly &operator%=(const SBPoly &R) {
        const int degL = deg(), degR = R.deg(), degQ = degL - degR;
        assert(degR >= 0);
        const auto inv = R.lc().inv();
        for (int i = degQ, n = degL; i >= 0; --i)
            if (const Tp res = Base::operator[](n--) * inv; res != 0)
                for (int j = 0; j <= degR; ++j) Base::operator[](i + j) -= res * R[j];
        return shrink();
    }
    SBPoly &operator<<=(int D) {
        if (D > 0) {
            Base::insert(Base::begin(), D, Tp());
        } else if (D < 0) {
            if (-D < Base::size()) {
                Base::erase(Base::begin(), Base::begin() + (-D));
            } else {
                Base::clear();
            }
        }
        return shrink();
    }
    SBPoly &operator>>=(int D) { return operator<<=(-D); }

    friend SBPoly operator+(const SBPoly &L, const SBPoly &R) { return SBPoly(L) += R; }
    friend SBPoly operator-(const SBPoly &L, const SBPoly &R) { return SBPoly(L) -= R; }
    friend SBPoly operator*(const SBPoly &L, const SBPoly &R) { return SBPoly(L) *= R; }
    friend SBPoly operator/(const SBPoly &L, const SBPoly &R) { return SBPoly(L) /= R; }
    friend SBPoly operator%(const SBPoly &L, const SBPoly &R) { return SBPoly(L) %= R; }
    friend SBPoly operator<<(const SBPoly &L, int D) { return SBPoly(L) <<= D; }
    friend SBPoly operator>>(const SBPoly &L, int D) { return SBPoly(L) >>= D; }

    friend std::ostream &operator<<(std::ostream &L, const SBPoly &R) {
        L << '[';
        const int d = R.deg();
        if (d < 0) {
            L << '0';
        } else {
            for (int i = 0; i <= d; ++i) {
                L << R[i];
                if (i == 1) L << "*X";
                if (i > 1) L << "*X^" << i;
                if (i != d) L << " + ";
            }
        }
        return L << ']';
    }
};

template <typename Tp>
inline std::tuple<SBPoly<Tp>, SBPoly<Tp>, SBPoly<Tp>> xgcd(SBPoly<Tp> A, SBPoly<Tp> B) {
    SBPoly<Tp> x11 = {1}, x12 = {}, x21 = {}, x22 = {1};
    while (B.deg() >= 0) {
        auto [Q, R]  = A.divmod(B);
        auto x11_old = x11, x12_old = x12;
        x11 = x21, x21 = x11_old - x21 * Q;
        x12 = x22, x22 = x12_old - x22 * Q;
        A = B, B = R;
    }
    return std::make_tuple(x11, x12, A);
}

template <typename Tp>
inline std::pair<SBPoly<Tp>, SBPoly<Tp>> inv_gcd(SBPoly<Tp> A, SBPoly<Tp> B) {
    SBPoly<Tp> x11 = {1}, x21 = {};
    while (B.deg() >= 0) {
        auto [Q, R]  = A.divmod(B);
        auto x11_old = x11;
        x11 = x21, x21 = x11_old - x21 * Q;
        A = B, B = R;
    }
    return std::make_pair(x11, A);
}
