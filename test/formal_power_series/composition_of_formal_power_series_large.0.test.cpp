#define PROBLEM "https://judge.yosupo.jp/problem/composition_of_formal_power_series_large"

#include "fps_composition.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    std::vector<mint> f(n), g(n);
    for (int i = 0; i < n; ++i) std::cin >> f[i];
    for (int i = 0; i < n; ++i) std::cin >> g[i];
    const auto fg = composition(f, g, n);
    for (int i = 0; i < n; ++i) std::cout << fg[i] << ' ';
    return 0;
}
