// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/polynomial_taylor_shift

#include "modint.hpp"
#include "poly_basic.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    mint c;
    std::cin >> n >> c;
    std::vector<mint> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    const auto ac = taylor_shift(a, c);
    for (int i = 0; i < n; ++i) std::cout << ac[i] << ' ';
    return 0;
}
