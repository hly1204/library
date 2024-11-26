#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "fft.hpp"
#include "modint.hpp"
#include <cassert>
#include <iostream>
#include <vector>

template <typename Tp>
std::vector<Tp> inv_graeffe(const std::vector<Tp> &Q, int n) {
    assert(!Q.empty());
    assert(Q[0] != 0);
    if (n <= 0) return {};

    // 12 E(n)
    auto rec = [](auto &&rec, std::vector<Tp> Q) {
        const int n = Q.size();
        if (n == 1) return std::vector{Q[0].inv()};
        Q.resize(n * 2);
        fft(Q); // 2 E(n)
        std::vector<Tp> V(n);
        for (int i = 0; i < n * 2; i += 2) V[i / 2] = Q[i] * Q[i + 1];
        inv_fft(V); // 1 E(n)
        V.resize(n / 2);
        auto T = rec(rec, V);
        T.resize(n);
        fft(T); // 1 E(n)
        for (int i = 0; i < n * 2; i += 2) {
            auto u = Q[i], v = Q[i + 1];
            Q[i] = T[i / 2] * v, Q[i + 1] = T[i / 2] * u;
        }
        inv_fft(Q); // 2 E(n)
        Q.resize(n);
        return Q;
    };

    auto QQ = Q;
    QQ.resize(fft_len(n));
    auto res = rec(rec, QQ);
    res.resize(n);
    return res;
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
