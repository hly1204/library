#define PROBLEM "https://judge.yosupo.jp/problem/composition_of_formal_power_series_large"

#include "poly_998244353_portable.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using namespace hly;
    int n;
    std::cin >> n;
    Poly F(n), G(n);
    for (int i = 0; i < n; ++i) std::cin >> F[i];
    for (int i = 0; i < n; ++i) std::cin >> G[i];
    const Poly GinF = composition(F, G, n);
    for (int i = 0; i < n; ++i) std::cout << GinF[i] << ' ';
    return 0;
}
