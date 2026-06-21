// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/2883

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using uint         = unsigned;
using ull          = unsigned long long;
constexpr uint MOD = 998244353;

constexpr uint PowMod(uint a, ull e) {
    for (uint res = 1;; a = (ull)a * a % MOD) {
        if (e & 1) res = (ull)res * a % MOD;
        if ((e /= 2) == 0) return res;
    }
}

constexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }

// returns */Q in F((x^-1)) such that */Q = A[0]*x^-1 + A[1]*x^-2 + ...
// with deg(Q) minimized and Q monic.
std::vector<uint> BerlekampMassey(std::vector<uint> A) {
    reverse(begin(A), end(A));
    int k = size(A), degA = k - 1, degB = k;
    std::vector<uint> B(k + 1), Q0, Q1  = {1U};
    for (B[k] = 1;; swap(Q0, Q1), swap(A, B), std::swap(degA, degB)) {
        while (degA >= 0 && A[degA] == 0) --degA;
        if (degA < 0 || degA - degB < -k) {
            const uint c = InvMod(Q1.back());
            for (auto &&e : Q1) e = (ull)e * c % MOD;
            return Q1;
        }
        Q0.resize(size(Q1) + (degB - degA));
        k -= (degB - degA) * 2;
        const uint a = InvMod(A[degA]);
        for (int i = degB - degA; i >= std::max(-k, 0); --i) {
            const uint d = (ull)B[degB--] * a % MOD;
            for (int j = 0; j <= degA; ++j) B[i + j] = (B[i + j] + (ull)A[j] * (MOD - d)) % MOD;
            for (int j = 0; j < (int)size(Q1); ++j) Q0[i + j] = (Q0[i + j] + (ull)Q1[j] * d) % MOD;
        }
    }
}

// returns [x^[-deg(Q), 0)] x^k/Q, x^k/Q in F((x^-1))
std::vector<uint> BostanMoriT(const std::vector<uint> &Q, long long k) {
    assert(k >= 0);
    assert(Q.back() == 1);
    const int degQ = size(Q) - 1;
    std::vector<uint> U(degQ);
    if (k == 0) return U[0] = 1, U;
    std::vector<uint> V(size(Q));
    for (int i = 0; i < (int)size(Q); ++i)
        for (int j = i % 2; j < (int)size(Q); j += 2)
            V[(i + j) / 2] = (V[(i + j) / 2] + (ull)Q[i] * (i % 2 == 0 ? Q[j] : MOD - Q[j])) % MOD;
    const auto T = BostanMoriT(V, k / 2);
    for (int i = 0; i < (int)size(T); ++i)
        for (int j = 0; j < (int)size(Q); ++j) {
            const int l = i * 2 + (int)(k % 2) + j;
            if (l >= degQ && l < degQ * 2)
                U[l - degQ] = (U[l - degQ] + (ull)T[i] * (j % 2 == 0 ? Q[j] : MOD - Q[j])) % MOD;
        }
    return U;
}

// returns x^k mod Q
std::vector<uint> MonomialModMonicPoly(long long k, const std::vector<uint> &Q) {
    const auto invQ = BostanMoriT(Q, k);
    std::vector<uint> R(size(Q) - 1);
    for (int i = 0; i < (int)size(invQ); ++i)
        for (int j = 0; j < (int)size(Q); ++j)
            if (i + j >= (int)size(invQ))
                R[i + j - (int)size(invQ)] =
                    (R[i + j - (int)size(invQ)] + (ull)invQ[i] * Q[j]) % MOD;
    return R;
}

uint BMBM(const std::vector<uint> &A, long long k) {
    const auto c = MonomialModMonicPoly(k, BerlekampMassey(A));
    uint res     = 0;
    for (int i = 0; i < (int)size(c); ++i) res = (res + (ull)c[i] * A[i]) % MOD;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    long long N;
    int K;
    std::cin >> N >> K;
    // K = 100, deg(Q) = 102
    std::vector<uint> F(204);
    F[0] = 1;
    F[1] = 1;
    for (int i = 2; i < (int)size(F); ++i) F[i] = (F[i - 1] + F[i - 2]) % MOD;
    for (int i = 0; i < (int)size(F); ++i) F[i] = PowMod(F[i], K);
    for (int i = 1; i < (int)size(F); ++i) F[i] = (F[i] + F[i - 1]) % MOD;
    std::cout << BMBM(F, N - 1) << '\n';
    return 0;
}
