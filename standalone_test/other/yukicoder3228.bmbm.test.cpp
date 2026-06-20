// competitive-verifier: PROBLEM https://yukicoder.me/problems/no/3228

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <utility>
#include <vector>

using uint         = unsigned;
using ull          = unsigned long long;
constexpr uint MOD = 1000000007;

constexpr uint PowMod(uint a, ull e) {
    for (uint res = 1;; a = (ull)a * a % MOD) {
        if (e & 1) res = (ull)res * a % MOD;
        if ((e /= 2) == 0) return res;
    }
}

constexpr uint InvMod(uint a) { return PowMod(a, MOD - 2); }

// returns P/Q in F[[x]] such that P/Q = A[0] + A[1]*x + ...
// with max(deg(P) + 1, deg(Q)) minimized and Q(0) = 1.
std::array<std::vector<uint>, 2> RationalRecons(std::vector<uint> A) {
    reverse(begin(A), end(A));
    int k = size(A), degA = k - 1, degB = k;
    std::vector<uint> B(k + 1), P0 = {1U}, P1, Q0, Q1 = {1U};
    for (B[k] = 1;; swap(P0, P1), swap(Q0, Q1), swap(A, B), std::swap(degA, degB)) {
        while (degA >= 0 && A[degA] == 0) --degA;
        if (degA < 0 || degA - degB < -k) {
            reverse(begin(P1), end(P1)), reverse(begin(Q1), end(Q1));
            const uint c = InvMod(Q1[0]);
            for (auto &&e : P1) e = (ull)e * c % MOD;
            for (auto &&e : Q1) e = (ull)e * c % MOD;
            return {P1, Q1};
        }
        P0.resize(size(Q1) + (degB - degA - 1));
        Q0.resize(size(Q1) + (degB - degA));
        k -= (degB - degA) * 2;
        const uint a = InvMod(A[degA]);
        for (int i = degB - degA; i >= std::max(-k, 0); --i) {
            const uint d = (ull)B[degB--] * a % MOD;
            for (int j = 0; j <= degA; ++j) B[i + j] = (B[i + j] + (ull)A[j] * (MOD - d)) % MOD;
            for (int j = 0; j < (int)size(P1); ++j) P0[i + j] = (P0[i + j] + (ull)P1[j] * d) % MOD;
            for (int j = 0; j < (int)size(Q1); ++j) Q0[i + j] = (Q0[i + j] + (ull)Q1[j] * d) % MOD;
        }
    }
}

// returns [x^k] P/Q
uint BostanMori(std::vector<uint> P, std::vector<uint> Q, long long k) {
    assert(Q.at(0) == 1);
    if (empty(P)) return 0;
    for (; k > 0; k /= 2) {
        auto nQ = Q;
        for (int i = 1; i < (int)size(nQ); i += 2) nQ[i] = (nQ[i] != 0 ? MOD - nQ[i] : 0);
        std::vector<uint> PP(size(P) + size(nQ) - 1), QQ(size(Q) + size(nQ) - 1);
        for (int j = 0; j < (int)size(nQ); ++j) {
            for (int i = 0; i < (int)size(P); ++i)
                PP[i + j] = (PP[i + j] + (ull)P[i] * nQ[j]) % MOD;
            for (int i = 0; i < (int)size(Q); ++i)
                QQ[i + j] = (QQ[i + j] + (ull)Q[i] * nQ[j]) % MOD;
        }
        P.clear();
        for (int i = (int)(k & 1); i < (int)size(PP); i += 2) P.push_back(PP[i]);
        Q.clear();
        for (int i = 0; i < (int)size(QQ); i += 2) Q.push_back(QQ[i]);
    }
    return P[0];
}

uint BMBM(std::vector<uint> A, long long k) {
    auto [P, Q] = RationalRecons(std::move(A));
    return BostanMori(std::move(P), std::move(Q), k);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int a, b, c, d, e;
    long long N;
    std::cin >> a >> b >> c >> d >> e >> N;
    auto adjust = [](int &a) {
        if ((a %= (int)MOD) < 0) a += (int)MOD;
    };
    adjust(a);
    adjust(b);
    adjust(c);
    adjust(d);
    adjust(e);
    std::vector<uint> F(8);
    F[0] = a;
    F[1] = b;
    for (int i = 2; i < (int)size(F); ++i) F[i] = ((ull)c * F[i - 1] + (ull)d * F[i - 2] + e) % MOD;
    for (int i = 1; i < (int)size(F); ++i) F[i] = (F[i] + F[i - 1]) % MOD;
    std::cout << BMBM(std::move(F), N) << '\n';
    return 0;
}
