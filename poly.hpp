#pragma once

#include "poly_basic.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

template<typename Tp> class Poly : public std::vector<Tp> {
    using Base = std::vector<Tp>;

public:
    using Base::Base;

    static Poly from_vector(std::vector<Tp> v) {
        Poly res;
        static_cast<std::vector<Tp> &>(res) = std::move(v);
        return res;
    }

    static Poly zero() { return Poly(); }
    static Poly one() { return Poly{Tp::one()}; }

    bool is_zero() const { return deg() < 0; }
    bool is_one() const { return deg() == 0 && lc() == Tp::one(); }

    int deg() const { return degree(*this); }
    int ord() const { return order(*this); }

    Poly rev() const {
        const int d = deg();
        Poly res(d + 1);
        for (int i = d; i >= 0; --i) res[i] = Base::operator[](d - i);
        return res;
    }

    Poly slice(int L, int R) const {
        Poly res(R - L);
        for (int i = L; i < std::min<int>(R, Base::size()); ++i) res[i - L] = Base::operator[](i);
        return res;
    }

    Poly trunc(int D) const {
        Poly res(D);
        for (int i = 0; i < std::min<int>(D, Base::size()); ++i) res[i] = Base::operator[](i);
        return res;
    }

    Poly &shrink() {
        Base::resize(deg() + 1);
        return *this;
    }

    Tp lc() const {
        const int d = deg();
        return d == -1 ? Tp() : Base::operator[](d);
    }

    Poly monic() const {
        const int d = deg();
        assert(d >= 0);
        const auto iv = Base::operator[](d).inv();
        Poly res(*this);
        for (int i = 0; i <= d; ++i) res[i] *= iv;
        return res;
    }

    Poly taylor_shift(Tp c) const { return from_vector(::taylor_shift(*this, c)).shrink(); }

    Poly operator-() const {
        const int d = deg();
        Poly res(d + 1);
        for (int i = 0; i <= d; ++i) res[i] = -Base::operator[](i);
        res.shrink();
        return res;
    }

    std::array<Poly, 2> divmod(const Poly &R) const {
        auto [q, r] = euclidean_div(*this, R);
        return {from_vector(std::move(q)), from_vector(std::move(r))};
    }
    Poly &operator+=(const Poly &R) {
        if (Base::size() < R.size()) Base::resize(R.size());
        for (int i = 0; i < (int)R.size(); ++i) Base::operator[](i) += R[i];
        return shrink();
    }
    Poly &operator-=(const Poly &R) {
        if (Base::size() < R.size()) Base::resize(R.size());
        for (int i = 0; i < (int)R.size(); ++i) Base::operator[](i) -= R[i];
        return shrink();
    }
    Poly &operator*=(const Poly &R) {
        Base::operator=(convolution(*this, R));
        return shrink();
    }
    Poly &operator/=(const Poly &R) {
        Base::operator=(euclidean_div_quotient(*this, R));
        return shrink();
    }
    Poly &operator%=(const Poly &R) {
        Base::operator=(std::get<1>(divmod(R)));
        return shrink();
    }
    Poly &operator<<=(int D) {
        if (D > 0) {
            Base::insert(Base::begin(), D, Tp(0));
        } else if (D < 0) {
            if (-D < (int)Base::size()) {
                Base::erase(Base::begin(), Base::begin() + (-D));
            } else {
                Base::clear();
            }
        }
        return shrink();
    }
    Poly &operator>>=(int D) { return operator<<=(-D); }

    friend Poly operator+(const Poly &L, const Poly &R) { return Poly(L) += R; }
    friend Poly operator-(const Poly &L, const Poly &R) { return Poly(L) -= R; }
    friend Poly operator*(const Poly &L, const Poly &R) { return Poly(L) *= R; }
    friend Poly operator/(const Poly &L, const Poly &R) { return Poly(L) /= R; }
    friend Poly operator%(const Poly &L, const Poly &R) { return Poly(L) %= R; }
    friend Poly operator<<(const Poly &L, int D) { return Poly(L) <<= D; }
    friend Poly operator>>(const Poly &L, int D) { return Poly(L) >>= D; }

    friend std::ostream &operator<<(std::ostream &L, const Poly &R) {
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

// 2x2 matrix for Euclidean algorithm
template<typename Tp> class GCDMatrix : public std::array<std::array<Tp, 2>, 2> {
public:
    GCDMatrix(const Tp &x00, const Tp &x01, const Tp &x10, const Tp &x11)
        : std::array<std::array<Tp, 2>, 2>{std::array{x00, x01}, std::array{x10, x11}} {}

    GCDMatrix operator*(const GCDMatrix &R) const {
        return {(*this)[0][0] * R[0][0] + (*this)[0][1] * R[1][0],
                (*this)[0][0] * R[0][1] + (*this)[0][1] * R[1][1],
                (*this)[1][0] * R[0][0] + (*this)[1][1] * R[1][0],
                (*this)[1][0] * R[0][1] + (*this)[1][1] * R[1][1]};
    }

    std::array<Tp, 2> operator*(const std::array<Tp, 2> &R) const {
        return {(*this)[0][0] * R[0] + (*this)[0][1] * R[1],
                (*this)[1][0] * R[0] + (*this)[1][1] * R[1]};
    }

    Tp det() const { return (*this)[0][0] * (*this)[1][1] - (*this)[0][1] * (*this)[1][0]; }
    GCDMatrix adj() const { return {(*this)[1][1], -(*this)[0][1], -(*this)[1][0], (*this)[0][0]}; }
};

// returns M s.t. deg(M) <= d and deg(M21*A+M22*B) < max(deg(A),deg(B)) - d
//                det(M) in {-1, 1}
// see:
// [1]: Daniel J. Bernstein. Fast multiplication and its applications.
template<typename Tp> inline GCDMatrix<Poly<Tp>> hgcd(const Poly<Tp> &A, const Poly<Tp> &B, int d) {
    using Mat = GCDMatrix<Poly<Tp>>;
    assert(!(A.deg() < 0 && B.deg() < 0));
    if (A.deg() < B.deg()) return hgcd(B, A, d) * Mat({}, {Tp(1)}, {Tp(1)}, {});
    if (A.deg() < d) return hgcd(A, B, A.deg());
    if (B.deg() < A.deg() - d) return Mat({Tp(1)}, {}, {}, {Tp(1)});
    if (int dd = A.deg() - d * 2; dd > 0) return hgcd(A >> dd, B >> dd, d);
    if (d == 0) return Mat({}, {Tp(1)}, {Tp(1)}, -(A / B));
    const auto M = hgcd(A, B, d / 2);
    const auto D = M[1][0] * A + M[1][1] * B;
    if (D.deg() < A.deg() - d) return M;
    const auto C      = M[0][0] * A + M[0][1] * B;
    const auto [Q, R] = C.divmod(D);
    return hgcd(D, R, D.deg() - (A.deg() - d)) * Mat({}, {Tp(1)}, {Tp(1)}, -Q) * M;
}

template<typename Tp> inline std::array<Poly<Tp>, 3> xgcd(const Poly<Tp> &A, const Poly<Tp> &B) {
    const auto M = hgcd(A, B, std::max(A.deg(), B.deg()));
    return {M[0][0], M[0][1], M[0][0] * A + M[0][1] * B};
}

template<typename Tp> inline std::array<Poly<Tp>, 2> inv_gcd(const Poly<Tp> &A, const Poly<Tp> &B) {
    const auto M = hgcd(A, B, std::max(A.deg(), B.deg()));
    return {M[0][0], M[0][0] * A + M[0][1] * B};
}

// returns P, Q s.t. [x^[-k, 0)] P/Q = [x^[-k, 0)] A/B
// where P, Q in F[x], deg(Q) is minimized
// requires deg(A) < deg(B)
template<typename Tp>
inline std::array<Poly<Tp>, 2> rational_approximation(const Poly<Tp> &A, const Poly<Tp> &B, int k) {
    auto M            = hgcd(B, A, k / 2);
    const auto [C, D] = M * std::array{B, A};
    if (D.deg() >= 0 && D.deg() - C.deg() >= -(k - (B.deg() - C.deg()) * 2))
        M = GCDMatrix<Poly<Tp>>({}, {Tp(1)}, {Tp(1)}, -(C / D)) * M;
    return {M.adj()[1][0], M.adj()[0][0]};
}

template<typename Tp>
inline std::array<Poly<Tp>, 2> rational_reconstruction(const std::vector<Tp> &A) {
    return rational_approximation(Poly<Tp>(A.rbegin(), A.rend()), Poly<Tp>{Tp(1)} << A.size(),
                                  A.size());
}

// returns [x^[-k, 0)] A/B
// requires deg(A) < deg(B)
template<typename Tp>
inline std::vector<Tp> fraction_to_series(const Poly<Tp> &A, const Poly<Tp> &B, int k) {
    return (((A << k) / B).rev() << (B.deg() - A.deg() - 1)).slice(0, k);
}
