// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/find_linear_recurrence

#include <algorithm>
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

// Only returns the denominator (might not be monic)
// This is a highly simplified version.
std::vector<uint> RationalRecons(std::vector<uint> A) {
    reverse(begin(A), end(A));
    int k = size(A), degA = k - 1, degB = k;
    std::vector<uint> B(k + 1), Q0, Q1  = {1U};
    for (B[k] = 1;; swap(Q0, Q1), swap(A, B), std::swap(degA, degB)) {
        while (degA >= 0 && A[degA] == 0) --degA;
        if (degA < 0 || degA - degB < -k) return Q1;
        Q0.resize(size(Q1) + (degB - degA));
        k -= (degB - degA) * 2;
        const uint a = InvMod(A[degA]);
        for (int i = degB - degA;
             // `i >= std::max(-k, 0)` => output = Berlekamp–Massey
             // `i >= 0`               => output = Euclidean
             i >= std::max(-k, 0); --i) {
            const uint d = (ull)B[degB--] * a % MOD;
            for (int j = 0; j <= degA; ++j) B[i + j] = (B[i + j] + (ull)A[j] * (MOD - d)) % MOD;
            for (int j = 0; j < (int)size(Q1); ++j) Q0[i + j] = (Q0[i + j] + (ull)Q1[j] * d) % MOD;
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<uint> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    const auto res = RationalRecons(std::move(a));
    std::cout << size(res) - 1 << '\n';
    const auto inv_lc = MOD - InvMod(res.back());
    for (int i = (int)size(res) - 2; i >= 0; --i)
        std::cout << (uint)((ull)res[i] * inv_lc % MOD) << ' ';
    return 0;
}
