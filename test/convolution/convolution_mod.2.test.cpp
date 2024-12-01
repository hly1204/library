#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "modint.hpp"
#include "radix4_fft.hpp"
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
    const int len = fft_len(n + m - 1);
    a.resize(len);
    b.resize(len);
    radix4_fft(a);
    radix4_fft(b);
    for (int i = 0; i < len; ++i) a[i] *= b[i];
    radix4_inv_fft(a);
    for (int i = 0; i < n + m - 1; ++i) std::cout << a[i] << ' ';
    return 0;
}
