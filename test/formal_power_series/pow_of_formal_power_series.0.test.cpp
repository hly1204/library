// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/pow_of_formal_power_series

#include "fps_basic.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    long long m;
    std::cin >> n >> m;
    std::vector<mint> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    const auto powa = fps_pow(a, m, n);
    for (int i = 0; i < n; ++i) std::cout << powa[i] << ' ';
    return 0;
}
