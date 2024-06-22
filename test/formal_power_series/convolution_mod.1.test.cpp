#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "czt.hpp"
#include "modint.hpp"
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
    a = czt(a, mint(3), n + m - 1);
    b = czt(b, mint(3), n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) a[i] *= b[i];
    a = inv_czt(a, mint(3));
    for (int i = 0; i < n + m - 1; ++i) std::cout << a[i] << ' ';
    return 0;
}
