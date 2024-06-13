#pragma once

#include "batch_inv.hpp"
#include "middle_product.hpp"
#include "poly_basic.hpp"
#include <algorithm>
#include <vector>

// returns F(a),F(ac),F(ac^2),...,F(ac^(n-1))
// Use        ij = binom(i,2)   + binom(-j,2) - binom(i-j,2)
// instead of ij = binom(i+j,2) - binom(i,2)  - binom(j,2)
template <typename Tp>
inline std::vector<Tp> czt(std::vector<Tp> F, Tp c, int n, Tp a = 1) {
    if (n <= 0) return {};
    const int degF = degree(F);
    if (degF < 0) return std::vector<Tp>(n);
    if (degF == 0 || a == 0) return std::vector<Tp>(n, F[0]);
    if (a != 1) {
        // F(x) <- F(ax)
        Tp aa = 1;
        for (int i = 0; i <= degF; ++i) F[i] *= aa, aa *= a;
    }
    if (c == 0) {
        std::vector<Tp> res(n, F[0]);
        for (int i = 1; i <= degF; ++i) res[0] += F[i];
        return res;
    }

    std::vector<Tp> H(std::max(degF + 1, n - 1));
    Tp cc = H[0] = 1;
    for (int i = 1; i < (int)H.size(); ++i) H[i] = H[i - 1] * (cc *= c);
    std::vector<Tp> G(degF + n); // G[i+degF]=c^(-binom(i,2))
    auto GG     = G.begin() + degF;
    const Tp ic = c.inv();
    cc = GG[0] = 1;
    for (int i = 1; i < n; ++i) GG[i] = GG[i - 1] * cc, cc *= ic;
    cc = 1;
    for (int i = -1; i >= -degF; --i) GG[i] = GG[i + 1] * (cc *= ic);

    // F[i] <- c^(binom(i+1,2))*F[i]
    for (int i = 0; i <= degF; ++i) F[i] *= H[i];

    F = middle_product(G, F);

    // F[i] <- c^(binom(i,2))*F[i]
    for (int i = 1; i < n; ++i) F[i] *= H[i - 1];
    return F;
}

// returns f s.t. f(aq^i)=F[i]
// aq^i != aq^j for all i != j
// see: https://noshi91.github.io/algorithm-encyclopedia/polynomial-interpolation-geometric
// noshi91. 標本点が等比数列を成す場合に補間多項式を計算するアルゴリズム.
template <typename Tp>
std::vector<Tp> iczt(const std::vector<Tp> &F, Tp q, Tp a = 1) {
    if (F.empty()) return {};
    if (a == 0) return {F[0]};
    const int n = F.size();
    std::vector<Tp> Q(n), S(n), M(n), D(n);
    Tp qq = 1;
    // Q[i]=q^i
    for (int i = 0; i < n; ++i) Q[i] = qq, qq *= q;
    // S[i]=prod_(i=1..i)(1-q^i)
    S[0] = 1;
    for (int i = 1; i < n; ++i) S[i] = S[i - 1] * (1 - Q[i]);
    const auto Sn   = S[n - 1] * (1 - qq);
    const auto invS = batch_inv(S);
    qq              = 1;
    // M[i]=qbinom(n,i)*binom(i,2)*(-1)^i
    for (int i = 1; i < n; ++i) M[n - i] = Sn * invS[i] * invS[n - i] * (qq *= -Q[i - 1]);
    M[0] = qq * -Q[n - 1]; // in case of q^n=1
    // D[i]=S[i]*S[n-i-1]*q^(binom(i,2)+i(n-i-1))*(-1)^i
    D[0] = 1;
    for (int i = 0; i < n - 1; ++i) D[i + 1] = D[i] * -Q[n - i - 2];
    for (int i = 0; i < n; ++i) D[i] *= S[i] * S[n - i - 1];
    // D[i] <- -F[i]/D[i]
    D = batch_inv(D);
    for (int i = 0; i < n; ++i) D[i] *= -F[i];
    auto res = convolution(M, czt(D, q.inv(), n, q.inv()));
    res.resize(n);
    if (a != 1) {
        const auto ia = a.inv();
        Tp aa         = 1;
        for (int i = 0; i < n; ++i) res[i] *= aa, aa *= ia;
    }
    return res;
}
