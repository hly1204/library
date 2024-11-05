#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "poly_998244353_portable.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using namespace hly;
    int n, m;
    std::cin >> n >> m;
    Poly A(n), B(m);
    for (int i = 0; i < n; ++i) std::cin >> A[i];
    for (int i = 0; i < m; ++i) std::cin >> B[i];
    const Poly AB = A.mul(B).trunc(n + m - 1);
    for (int i = 0; i < n + m - 1; ++i) std::cout << AB[i] << " \n"[i == n + m - 1];
    return 0;
}
