#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"

#include <algorithm>
#include <array>
#include <cassert>
#include <iostream>
#include <tuple>
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

int Degree(const std::vector<uint> &a) {
    for (int i = (int)size(a) - 1; i >= 0; --i)
        if (a[i]) return i;
    return -1;
}

void Shrink(std::vector<uint> &a) { a.resize(Degree(a) + 1); }

uint LeadCoeff(const std::vector<uint> &a) {
    const int degA = Degree(a);
    return degA >= 0 ? a[degA] : 0u;
}

std::vector<uint> Monic(std::vector<uint> a) {
    const uint ia = InvMod(LeadCoeff(a));
    for (int i = 0; i < (int)size(a); ++i) a[i] = (ull)a[i] * ia % MOD;
    return a;
}

std::array<std::vector<uint>, 2> QuoRem(std::vector<uint> A, const std::vector<uint> &B) {
    const int degA = Degree(A);
    const int degB = Degree(B);
    assert(degB >= 0);
    const int degQ = degA - degB;
    if (degQ < 0) return {std::vector<uint>{}, A};
    std::vector<uint> Q(degQ + 1);
    const uint ib = InvMod(LeadCoeff(B));
    for (int i = degQ, n = degA; i >= 0; --i)
        if ((Q[i] = (ull)A[n--] * ib % MOD) != 0)
            for (int j = 0; j <= degB; ++j)
                if ((A[i + j] = A[i + j] + MOD - ((ull)B[j] * Q[i] % MOD)) >= MOD) A[i + j] -= MOD;
    Shrink(A);
    return {Q, A};
}

std::vector<uint> MultiplyAdd(const std::vector<uint> &x, const std::vector<uint> &y,
                              std::vector<uint> z) {
    assert(!(empty(x) && empty(y)));
    if (size(z) < size(x) + size(y) - 1) z.resize(size(x) + size(y) - 1);
    for (int i = 0; i < (int)size(x); ++i)
        for (int j = 0; j < (int)size(y); ++j) z[i + j] = (z[i + j] + (ull)x[i] * y[j]) % MOD;
    Shrink(z);
    return z;
}

// returns P, Q such that [x^[-k, 0)] P/Q = [x^[-k, 0)] A/B
// and deg(Q) is minimized
// requires deg(A) < deg(B)
std::array<std::vector<uint>, 2> RationalApprox(std::vector<uint> A, std::vector<uint> B, int k) {
    if (Degree(A) < 0 || Degree(A) - Degree(B) < -k)
        return {std::vector<uint>{}, std::vector<uint>{1u}};
    std::vector<uint> P0 = {1u}, P1, Q0, Q1 = {1u};
    for (;;) {
        const auto [Q, R] = QuoRem(B, A);
        std::tie(P0, P1, Q0, Q1, A, B) =
            std::make_tuple(P1, MultiplyAdd(Q, P1, P0), Q1, MultiplyAdd(Q, Q1, Q0), R, A);
        if (Degree(A) < 0 || Degree(A) - Degree(B) < -(k -= Degree(Q) * 2)) return {P1, Q1};
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<uint> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    const auto res = Monic(std::get<1>(RationalApprox(
        std::vector(rbegin(a), rend(a)),
        [](int n) {
            std::vector<uint> a(n + 1);
            a[n] = 1;
            return a;
        }(n),
        n)));
    std::cout << Degree(res) << '\n';
    for (int i = Degree(res) - 1; i >= 0; --i) std::cout << (res[i] ? MOD - res[i] : 0u) << ' ';
    return 0;
}
