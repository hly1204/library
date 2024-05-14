#define PROBLEM "https://judge.yosupo.jp/problem/inv_of_formal_power_series"

#include "fps_basic.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    std::vector<mint> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    const auto inva = inv(a, n);
    for (int i = 0; i < n; ++i) std::cout << inva[i] << ' ';
    return 0;
}
