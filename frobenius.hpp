#pragma once

#include "basis.hpp"
#include "mat_basic.hpp"
#include "random.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <vector>

// Compute the Frobenius form (rational canonical form) of a square matrix,
// but the result is not always correct.
template<typename Tp> class Frobenius {
    struct Poly {
        static int degree(const std::vector<Tp> &a) {
            int n = (int)a.size() - 1;
            while (n >= 0 && a[n] == 0) --n;
            return n;
        }

        static std::array<std::vector<Tp>, 2> divmod(const std::vector<Tp> &A,
                                                     const std::vector<Tp> &B) {
            const int degA = degree(A);
            const int degB = degree(B);
            assert(degB >= 0);
            const int degQ = degA - degB;
            if (degQ < 0) {
                auto R = A;
                R.resize(degB);
                return {std::vector<Tp>{Tp(0)}, std::move(R)};
            }
            std::vector<Tp> Q(degQ + 1), R = A;
            const auto inv = B[degB].inv();
            for (int i = degQ, n = degA; i >= 0; --i)
                if ((Q[i] = R[n--] * inv) != 0)
                    for (int j = 0; j <= degB; ++j) R[i + j] -= Q[i] * B[j];
            R.resize(degB);
            return {std::move(Q), std::move(R)};
        }

        // returns [x^[-deg(Q), 0)] x^k/Q, x^k/Q in F((x^-1))
        static std::vector<Tp> bostan_mori(const std::vector<Tp> &Q, long long k) {
            assert(k >= 0);
            const int degQ = Q.size() - 1;
            std::vector<Tp> U(degQ);
            if (k < degQ || k == 0) {
                if (degQ > 0) U[k] = Q[degQ].inv();
                for (int i = (int)k - 1; i >= 0; --i) {
                    for (int j = (int)k - i; j > 0; --j) U[i] -= Q[degQ - j] * U[i + j];
                    U[i] *= U[k];
                }
                return U;
            }
            std::vector<Tp> V(Q.size());
            for (int i = 0; i < (int)Q.size(); ++i)
                for (int j = i % 2; j < (int)Q.size(); j += 2)
                    V[(i + j) / 2] += Q[i] * (i % 2 == 0 ? Q[j] : -Q[j]);
            const auto T = bostan_mori(V, k / 2);
            for (int i = 0; i < (int)T.size(); ++i)
                for (int j = 0; j < (int)Q.size(); ++j) {
                    const int l = i * 2 + (int)(k % 2) + j;
                    if (l >= degQ && l < degQ * 2)
                        U[l - degQ] += T[i] * (j % 2 == 0 ? Q[j] : -Q[j]);
                }
            return U;
        }

        // returns x^k mod Q
        static std::vector<Tp> xk_mod(long long k, const std::vector<Tp> &Q) {
            const auto invQ = bostan_mori(Q, k);
            std::vector<Tp> R(Q.size() - 1);
            for (int i = 0; i < (int)invQ.size(); ++i)
                for (int j = 0; j < (int)Q.size(); ++j)
                    if (i + j >= (int)invQ.size()) R[i + j - (int)invQ.size()] += invQ[i] * Q[j];
            return R;
        }
    };

public:
    // F_A = T^(-1)AT = diag(C_(p_0),...,C_(p_(k-1)))
    // where C_(p_j) is the companion matrix of monic polynomial P[j]
    // *        minimal polynomial of A = p_0
    // * characteristic polynomial of A = prod_(j=0)^(k-1) p_j
    const int N;
    Matrix<Tp> InvT;
    std::vector<std::vector<Tp>> P; // invariant factors
    Matrix<Tp> T;

    // see:
    // [1]: Elegia. A (Somehow) Simple (Randomized) Algorithm for Frobenius Form of a Matrix.
    //      https://codeforces.com/blog/entry/124815
    // [2]: Arne Storjohann. Algorithms for Matrix Canonical Forms.
    //      https://cs.uwaterloo.ca/~astorjoh/diss2up.pdf
    explicit Frobenius(const Matrix<Tp> &A) : N(A.height()) {
        assert(A.is_square());
        if (A.empty()) {
            P.emplace_back().emplace_back(1);
            return;
        }
    retry: // retry is not guaranteed to give the correct result
        Basis<Tp> B(N);
        Matrix<Tp> A_B(N, std::vector<Tp>(N)); // linear transform respect to basis B
        std::vector<std::vector<Tp>> V;        // vectors for new basis
        P.clear();
        while (B.size() < N) {
            int deg = 0;
            for (auto R = random_vector<Tp>(N);; R = A.apply(R), ++deg)
                if (const auto c = B.insert(R)) {
                    if (deg == 0) break;
                    if (!P.empty() && deg > Poly::degree(P.back())) goto retry;
                    P.emplace_back(c->begin() + (B.size() - deg), c->begin() + B.size())
                        .emplace_back(1);
                    const auto [q, r] = Poly::divmod(
                        std::vector(c->begin(), c->begin() + (B.size() - deg)), P.back());
                    if (Poly::degree(r) >= 0) goto retry;
                    V.emplace_back(q).resize(N), V.back().at(B.size() - deg) = 1;
                    for (int i = B.size() - deg; i < B.size() - 1; ++i) A_B[i + 1][i] = 1;
                    for (int i = 0; i < B.size(); ++i) A_B[i][B.size() - 1] = -c->at(i);
                    break;
                }
        }
        T = B.transition_matrix(), InvT = B.inv_transition_matrix();
        if (P.size() <= 1) return;
        auto C = Matrix<Tp>(N, std::vector<Tp>(N));
        for (int i = 0, j = 0; i < (int)V.size(); ++i) {
            C[j++] = V[i];
            for (int k = (int)P[i].size() - 1; --k; ++j)
                for (int l = 0; l < j; ++l)
                    for (int m = 0; m < j; ++m) C[j][l] += A_B[l][m] * C[j - 1][m];
        }
        for (int i = N - 1; i > 0; --i)
            for (int j = i - 1; j >= 0; --j)
                if (C[i][j] != 0)
                    for (int k = 0; k < N; ++k)
                        T[k][i] += C[i][j] * T[k][j], InvT[j][k] -= C[i][j] * InvT[i][k];
    }

    Matrix<Tp> transition_matrix() const { return T; }
    Matrix<Tp> inv_transition_matrix() const { return InvT; }

    Matrix<Tp> frobenius_form() const {
        Matrix<Tp> res(N, std::vector<Tp>(N));
        for (int i = 0, s = 0; i < (int)P.size(); ++i) {
            const int deg = (int)P[i].size() - 1;
            for (int j = s; j < s + deg - 1; ++j) res[j + 1][j] = 1;
            for (int j = s; j < s + deg; ++j) res[j][s + deg - 1] = -P[i][j - s];
            s += deg;
        }
        return res;
    }

    std::vector<Tp> minpoly() const { return P[0]; }
    std::vector<Tp> charpoly() const {
        std::vector<Tp> p = P[0];
        for (int i = 1; i < (int)P.size(); ++i) {
            p = [](const std::vector<Tp> &A, const std::vector<Tp> &B) {
                std::vector<Tp> AB(A.size() + B.size() - 1);
                for (int i = 0; i < (int)A.size(); ++i)
                    for (int j = 0; j < (int)B.size(); ++j) AB[i + j] += A[i] * B[j];
                return AB;
            }(p, P[i]);
        }
        return p;
    }

    // returns (F_A)^e
    Matrix<Tp> pow(long long e) const {
        assert(e >= 0);
        return eval(Poly::xk_mod(e, P[0]));
    }

    // returns f(F_A)
    Matrix<Tp> eval(std::vector<Tp> f) const {
        Matrix<Tp> res(N, std::vector<Tp>(N));
        for (int i = 0, s = 0; i < (int)P.size(); ++i) {
            const int deg = (int)P[i].size() - 1;
            f             = std::get<1>(Poly::divmod(f, P[i]));
            auto c        = f;
            for (int j = 0; j < deg; ++j) {
                if (j) {
                    std::rotate(c.begin(), c.end() - 1, c.end());
                    const auto c0 = c[0];
                    c[0]          = 0;
                    for (int k = 0; k < deg; ++k) c[k] -= c0 * P[i][k];
                }
                for (int k = 0; k < deg; ++k) res[s + k][s + j] = c[k];
            }
            s += deg;
        }
        return res;
    }
};
