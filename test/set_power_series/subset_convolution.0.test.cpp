// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/subset_convolution

#include "modint.hpp"
#include "subset_conv.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    std::vector<mint> a(1 << n), b(1 << n);
    for (int i = 0; i < (1 << n); ++i) std::cin >> a[i];
    for (int i = 0; i < (1 << n); ++i) std::cin >> b[i];
    const auto ab = subset_convolution(a, b);
    for (int i = 0; i < (1 << n); ++i) std::cout << ab[i] << ' ';
    return 0;
}
