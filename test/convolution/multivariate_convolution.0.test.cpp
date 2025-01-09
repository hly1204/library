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
    for (int i = 0; i < dim; ++i) std::cin >> db[i];
    MDConvInfo<mint> conv(db);
    const int len = conv.len();
    std::vector<mint> a(len), b(len);
    for (int i = 0; i < len; ++i) std::cin >> a[i];
    for (int i = 0; i < len; ++i) std::cin >> b[i];
    const auto ab = conv.convolution(a, b);
    for (int i = 0; i < len; ++i) std::cout << ab[i] << ' ';
    return 0;
}
