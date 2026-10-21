// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/convolution_mod

#include "modint.hpp"
#include "relaxed_conv.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n, m;
    std::cin >> n >> m;
    std::vector<mint> a(n), b(m);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < m; ++i) std::cin >> b[i];
    RelaxedConvolution<mint> ab;
    for (int i = 0; i < n + m - 1; ++i) {
        if (i) std::cout << ' ';
        std::cout << ab.push(i < n ? a[i] : mint(0), i < m ? b[i] : mint(0));
    }
    return 0;
}
