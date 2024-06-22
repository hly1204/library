#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod_1000000007"

#include "conv_mod.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    std::vector<int> f(n), g(m);
    for (int i = 0; i < n; ++i) std::cin >> f[i];
    for (int i = 0; i < m; ++i) std::cin >> g[i];
    const auto fg = convolution_mod(f, g, 1000000007);
    for (int i = 0; i < (int)fg.size(); ++i) std::cout << fg[i] << ' ';
    return 0;
}
