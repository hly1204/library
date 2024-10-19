#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_xor_convolution"

#include "bitwise_conv.hpp"
#include "modint.hpp"
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
    const auto ab = bitwise_xor_convolution(a, b);
    for (int i = 0; i < (1 << n); ++i) std::cout << ab[i] << ' ';
    return 0;
}
