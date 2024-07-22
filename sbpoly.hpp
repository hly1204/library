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
        if (degQ < 0) return std::make_pair(SBPoly(), *this);
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
            if (-D < (int)Base::size()) {
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
                if (i == 1) L << "*x";
                if (i > 1) L << "*x^" << i;
                if (i != d) L << " + ";
            }
        }
        return L << ']';
    }
};

template <typename Tp>
inline std::tuple<SBPoly<Tp>, SBPoly<Tp>, SBPoly<Tp>> xgcd(SBPoly<Tp> A, SBPoly<Tp> B) {
    SBPoly<Tp> x11 = {Tp(1)}, x12 = {}, x21 = {}, x22 = {Tp(1)};
    while (B.deg() >= 0) {
        const auto [Q, R]  = A.divmod(B);
        const auto x11_old = x11, x12_old = x12;
        x11 = x21, x21 = x11_old - x21 * Q;
        x12 = x22, x22 = x12_old - x22 * Q;
        A = B, B = R;
    }
    return std::make_tuple(x11, x12, A);
}

template <typename Tp>
inline std::pair<SBPoly<Tp>, SBPoly<Tp>> inv_gcd(SBPoly<Tp> A, SBPoly<Tp> B) {
    SBPoly<Tp> x11 = {Tp(1)}, x21 = {};
    while (B.deg() >= 0) {
        const auto [Q, R]  = A.divmod(B);
        const auto x11_old = x11;
        x11 = x21, x21 = x11_old - x21 * Q;
        A = B, B = R;
    }
    return std::make_pair(x11, A);
}

// returns P,Q s.t. P/Q=A[0]x^(-1)+A[1]x^(-2)+... in F((x^(-1)))
// where P,Q in F[x], deg(Q) is minimized
// both time & space complexity is O(n^2) where n=A.size()
// (*) this function is only for explaining how this algorithm works.
template <typename Tp>
inline std::pair<SBPoly<Tp>, SBPoly<Tp>>
rational_function_reconstruction_slow(const std::vector<Tp> &A) {
    // returns C,D s.t. [x^([-k,-1])]A/B=[x^([-k,-1])]C/D and deg(D) is minimized
    auto rec = [](auto &&rec, const SBPoly<Tp> &A, const SBPoly<Tp> &B,
                  int k) -> std::pair<SBPoly<Tp>, SBPoly<Tp>> {
        if (A.deg() < 0) return std::make_pair(SBPoly<Tp>(), SBPoly<Tp>{Tp(1)});
        const auto [Q, R] = B.divmod(A);
        // A/B = ...+?x^(-k)+...+?x^(-deg(Q))
        //     = 1/(B/A)
        //     = 1/(C+D)
        // note that C,D in F((x^(-1))) and we define deg(C)=deg(Q) > deg(D)
        // (A/B)*C + (A/B)*D = 1
        // we must have [x^([-k,-deg(Q)])]1/C = [x^([-k,-deg(Q)])]A/B
        //           => (A/B)*C + (A/B)*D = 1
        //           => (A/B) + (A/B)*D/C = 1/C
        //           => deg(A/B) + deg(D) - deg(C) < -k
        //           => deg(D) < -k + 2deg(C)
        // (1) If we set C<-Q and deg(D) < -k + 2deg(Q), we could just drop D.
        if (R.deg() - A.deg() < -k + Q.deg() * 2) return std::make_pair(SBPoly<Tp>{Tp(1)}, Q);
        // (2) Otherwise we set C<-Q+E/F and minimize deg(F)
        const auto [E, F] = rec(rec, R, A, k - Q.deg() * 2);
        // now we have 1/(Q+E/F)=F/(QF+E)
        return std::make_pair(F, Q * F + E);
    };
    // (A[n-1]+A[n-2]x+...+A[0]x^(n-1)) / x^n = A[0]x^(-1)+A[1]x^(-2)+...
    return rec(rec, SBPoly<Tp>(A.rbegin(), A.rend()), SBPoly<Tp>{Tp(1)} << A.size(), A.size());
}

// same as the function above
template <typename Tp>
inline std::pair<SBPoly<Tp>, SBPoly<Tp>>
rational_function_reconstruction(const std::vector<Tp> &F) {
    SBPoly<Tp> A = SBPoly<Tp>(F.rbegin(), F.rend()), B = SBPoly<Tp>{Tp(1)} << F.size();
    if (A.deg() < 0) return std::make_pair(SBPoly<Tp>(), SBPoly<Tp>{Tp(1)});
    SBPoly<Tp> P{Tp(1)}, PP, Q, QQ{Tp(1)};
    for (;;) {
        const auto [C, D]            = B.divmod(A);
        std::tie(P, PP, Q, QQ, A, B) = std::make_tuple(PP, C * PP + P, QQ, C * QQ + Q, D, A);
        if (A.deg() < QQ.deg()) return std::make_pair(PP, QQ);
    }
}
