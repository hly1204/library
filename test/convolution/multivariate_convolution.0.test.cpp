#define PROBLEM "https://judge.yosupo.jp/problem/multivariate_convolution"

#include "md_conv.hpp"
#include "modint.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int dim;
    std::cin >> dim;
    std::vector<int> db(dim);
    int deg = 1; // deg(x0^ax1^bx2^c...) = a+b+c+...
    for (int i = 0; i < dim; ++i) std::cin >> db[i], deg *= db[i];
    std::vector<mint> a(deg), b(deg);
    for (int i = 0; i < deg; ++i) std::cin >> a[i];
    for (int i = 0; i < deg; ++i) std::cin >> b[i];
    MDConvInfo<mint> conv(db);
    const auto ab = conv.convolution(a, b);
    for (int i = 0; i < deg; ++i) std::cout << ab[i] << ' ';
    return 0;
}
