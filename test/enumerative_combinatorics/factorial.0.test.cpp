#define PROBLEM "https://judge.yosupo.jp/problem/factorial"

#include "modint.hpp"
#include "poly_interpolation.hpp"
#include "shift_sample_points.hpp"
#include "sqrt_int.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>

template <typename Tp>
Tp factorial(int N) {
    if (N >= (int)Tp::mod()) return 0;
    if (N == 0) return 1;
    const int v = sqrt_int(N);
    // Let g_d(x) = prod[1 <= i <= d](x + i)
    // g_1(x) = x + 1, g[i] = g_1(i * v)
    std::vector<Tp> g{Tp(1), Tp(v + 1)};
    int mask = 1 << 30;
    while ((mask & v) == 0) mask >>= 1;
    for (int d = 1; d != v;) {
        const auto g0 = shift_sample_points(g, Tp(d + 1), d);
        const auto g1 = shift_sample_points(g, Tp(d) / v, d << 1 | 1);
        std::copy(g0.begin(), g0.end(), std::back_inserter(g));
        d <<= 1;
        // g_(2d)(x) = g_d(x)g_d(x + d)
        for (int i = 0; i <= d; ++i) g[i] *= g1[i];
        if ((mask >>= 1) & v) {
            d |= 1;
            g.push_back(lagrange_interpolation_iota(g, Tp(d)));
            // g_(d + 1)(x) = (x + d + 1)g_d(x)
            for (int i = 0; i <= d; ++i) g[i] *= i * v + d;
        }
    }
    Tp res = 1;
    // g[0] = g_v(0), g[1] = g_v(v), ...
    for (int i = 0; i < v; ++i) res *= g[i];
    for (int i = v * v + 1; i <= N; ++i) res *= i;
    return res;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int T;
    std::cin >> T;
    while (T--) {
        int N;
        std::cin >> N;
        std::cout << factorial<mint>(N) << '\n';
    }
    return 0;
}
