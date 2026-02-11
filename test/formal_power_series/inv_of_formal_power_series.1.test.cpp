// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/inv_of_formal_power_series

#include "fft.hpp"
#include "modint.hpp"
#include <cassert>
#include <iostream>
#include <vector>

template<typename Tp> std::vector<Tp> inv_graeffe(std::vector<Tp> Q, int n) {
    assert(!Q.empty());
    assert(Q[0] != 0);
    if (n <= 0) return {};

    auto rec = [](auto &&rec, std::vector<Tp> Q) {
        const int n = Q.size();
        if (n == 1) return std::vector{Q[0].inv()};
        const int len = fft_len(n * 2 - 1);
        // deg(Q) <= n-1, len > 2deg(Q), len/2 > deg(Q)
        Q.resize(len);
        fft(Q);
        std::vector<Tp> V(len / 2);
        for (int i = 0; i < len; i += 2) V[i / 2] = Q[i] * Q[i + 1];
        inv_fft(V);
        V.resize((n + 1) / 2);
        auto T = rec(rec, std::vector(V.begin(), V.begin() + n / 2));
        T.resize(len / 2);
        if (n & 1) {
            for (int i = 1; i <= n / 2; ++i) T[n / 2] += V[i] * T[n / 2 - i];
            T[n / 2] /= -V[0];
        }
        fft(T);
        for (int i = 0; i < len; i += 2) {
            auto u = Q[i], v = Q[i + 1];
            Q[i] = T[i / 2] * v, Q[i + 1] = T[i / 2] * u;
        }
        inv_fft(Q);
        Q.resize(n);
        return Q;
    };

    Q.resize(n);
    return rec(rec, Q);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    std::vector<mint> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    const auto inva = inv_graeffe(a, n);
    for (int i = 0; i < n; ++i) std::cout << inva[i] << ' ';
    return 0;
}
