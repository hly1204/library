#pragma once

#include "basis.hpp"
#include "mat_basic.hpp"
#include "random.hpp"
#include "sbpoly.hpp"
#include <cassert>
#include <vector>

template <typename Tp>
class Frobenius {
public:
    // F_A = T^(-1)AT = diag(C_(p_0),...,C_(p_(k-1)))
    // where C_(p_j) is the companion matrix of monic polynomial P[j]
    // *        minimal polynomial of A = p_0
    // * characteristic polynomial of A = prod_(j=0)^(k-1) p_j
    int N;
    Matrix<Tp> InvT;
    std::vector<SBPoly<Tp>> P;
    Matrix<Tp> T;

    // see:
    // [1]: Elegia. A (Somehow) Simple (Randomized) Algorithm for Frobenius Form of a Matrix.
    //      https://codeforces.com/blog/entry/124815
    // [2]: Arne Storjohann. Algorithms for Matrix Canonical Forms.
    //      https://cs.uwaterloo.ca/~astorjoh/diss2up.pdf
    explicit Frobenius(const Matrix<Tp> &A) : N(height(A)) {
        assert(N != 0);
        assert(is_square_matrix(A));
    retry:
        Basis<Tp> B(N);
        Matrix<Tp> A_B(N, std::vector<Tp>(N)); // linear transform respect to basis B
        std::vector<std::vector<Tp>> V;        // vectors for new basis
        P.clear();
        while (B.size() < N) {
            int deg = 0;
            for (auto R = random_vector<Tp>(N);; R = mat_apply(A, R), ++deg)
                if (const auto c = B.insert(R)) {
                    if (!P.empty() && deg > P.back().deg()) goto retry;
                    P.emplace_back(c->begin() + (B.size() - deg), c->begin() + B.size())
                        .emplace_back(1);
                    V.emplace_back(SBPoly<Tp>(c->begin(), c->begin() + (B.size() - deg)) / P.back())
                        .resize(B.size());
                    for (int i = B.size() - deg; i < B.size() - 1; ++i) A_B[i + 1][i] = 1;
                    for (int i = 0; i < B.size(); ++i) A_B[i][B.size() - 1] = -c->at(i);
                    break;
                }
        }
        auto TT = T = transpose(B.transition_matrix()), InvTT = InvT = B.inv_transition_matrix();
        for (int i = 1, n = P[0].deg(); i < (int)V.size(); ++i)
            for (int j = P[i].deg(); j--; ++n) {
                std::vector<Tp> Vi(n);
                for (int k = 0; k < n; ++k) {
                    if (V[i][k] != 0)
                        for (int l = 0; l < N; ++l)
                            TT[n][l] += V[i][k] * T[k][l], InvTT[k][l] -= V[i][k] * InvT[n][l];
                    for (int l = 0; l < n; ++l) Vi[k] += A_B[k][l] * V[i][l];
                }
                V[i] = Vi;
            }
        T = transpose(TT), InvT = InvTT;
    }

    Matrix<Tp> transition_matrix() const { return T; }
    Matrix<Tp> inv_transition_matrix() const { return InvT; }

    Matrix<Tp> frobenius_form() const {
        Matrix<Tp> res(N, std::vector<Tp>(N));
        for (int i = 0, s = 0; i < (int)P.size(); s += P[i++].deg()) {
            for (int j = s; j < s + P[i].deg() - 1; ++j) res[j + 1][j] = 1;
            for (int j = s; j < s + P[i].deg(); ++j) res[j][s + P[i].deg() - 1] = -P[i][j - s];
        }
        return res;
    }

    // returns (F_A)^e
    Matrix<Tp> pow(long long e) const {
        assert(e >= 0);
        // returns x^e mod p
        auto pow_mod = [](auto &&pow_mod, long long e, const SBPoly<Tp> &p) {
            if (e == 0) return SBPoly<Tp>{Tp(1)};
            const auto half = pow_mod(pow_mod, e / 2, p);
            return ((half * half) << (e & 1)) % p;
        };
        Matrix<Tp> res(N, std::vector<Tp>(N));
        for (int i = 0, s = 0; i < (int)P.size(); s += P[i++].deg()) {
            auto c = pow_mod(pow_mod, e, P[i]);
            for (int j = 0; j < P[i].deg(); c = (c << 1) % P[i], ++j)
                for (int k = 0; k <= c.deg(); ++k) res[k + s][s + j] = c[k];
        }
        return res;
    }
};
