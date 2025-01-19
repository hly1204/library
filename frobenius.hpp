#pragma once

#include "basis.hpp"
#include "mat_basic.hpp"
#include "poly.hpp"
#include "random.hpp"
#include <cassert>
#include <functional>
#include <numeric>
#include <optional>
#include <vector>

// Compute the Frobenius form (rational canonical form) of a square matrix,
// but the result is not always true.
template<typename Tp> class Frobenius {
public:
    // F_A = T^(-1)AT = diag(C_(p_0),...,C_(p_(k-1)))
    // where C_(p_j) is the companion matrix of monic polynomial P[j]
    // *        minimal polynomial of A = p_0
    // * characteristic polynomial of A = prod_(j=0)^(k-1) p_j
    int N;
    Matrix<Tp> InvT;
    std::vector<Poly<Tp>> P;
    Matrix<Tp> T;
    mutable std::optional<Poly<Tp>> CharPoly;

    // see:
    // [1]: Elegia. A (Somehow) Simple (Randomized) Algorithm for Frobenius Form of a Matrix.
    //      https://codeforces.com/blog/entry/124815
    // [2]: Arne Storjohann. Algorithms for Matrix Canonical Forms.
    //      https://cs.uwaterloo.ca/~astorjoh/diss2up.pdf
    explicit Frobenius(const Matrix<Tp> &A) : N(height(A)) {
        assert(is_square_matrix(A));
    retry: // retry is not guaranteed to give the right result
        Basis<Tp> B(N);
        Matrix<Tp> A_B(N, std::vector<Tp>(N)); // linear transform respect to basis B
        std::vector<std::vector<Tp>> V;        // vectors for new basis
        P.clear();
        while (B.size() < N) {
            int deg = 0;
            for (auto R = random_vector<Tp>(N);; R = mat_apply(A, R), ++deg)
                if (const auto c = B.insert(R)) {
                    if (deg == 0) break;
                    if (!P.empty() && deg > P.back().deg()) goto retry;
                    P.emplace_back(c->begin() + (B.size() - deg), c->begin() + B.size())
                        .emplace_back(1);
                    const Poly<Tp> b(c->begin(), c->begin() + (B.size() - deg));
                    const auto [q, r] = b.divmod(P.back());
                    if (r.deg() >= 0) goto retry;
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
            for (int k = P[i].deg(); --k; ++j)
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
        auto pow_mod = [](auto &&pow_mod, long long e, const Poly<Tp> &p) {
            if (e == 0) return Poly<Tp>{Tp(1)};
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

    Poly<Tp> charpoly() const {
        if (!CharPoly)
            CharPoly.emplace(
                std::accumulate(P.begin(), P.end(), Poly<Tp>{Tp(1)}, std::multiplies<>()));
        return *CharPoly;
    }

    // returns F(F_A)
    Matrix<Tp> eval(Poly<Tp> F) const {
        F %= this->charpoly();
        Matrix<Tp> res(N, std::vector<Tp>(N));
        if (F.deg() < 0) return res;
        for (int i = 0, s = 0; i < (int)P.size(); s += P[i++].deg()) {
            std::vector<Poly<Tp>> pow_table(F.deg() + P[i].deg() + 1);
            pow_table[0] = Poly<Tp>{Tp(1)};
            for (int j = 1; j <= F.deg() + P[i].deg(); ++j)
                pow_table[j] = (pow_table[j - 1] << 1) % P[i];
            std::vector<Poly<Tp>> row(P[i].deg());
            for (int j = 0; j <= F.deg(); ++j)
                for (int k = 0; k < P[i].deg(); ++k) row[k] += Poly<Tp>{F[j]} * pow_table[j + k];
            for (int j = 0; j < P[i].deg(); ++j)
                for (int k = 0; k <= row[j].deg(); ++k) res[k + s][s + j] = row[j][k];
        }
        return res;
    }
};
