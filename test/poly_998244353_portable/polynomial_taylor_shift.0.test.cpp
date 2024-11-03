#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"

#include "poly_998244353_portable.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using namespace hly;
    int n;
    MInt c;
    std::cin >> n >> c;
    Poly A(n);
    for (int i = 0; i < n; ++i) std::cin >> A[i];
    const Poly B = A.taylor_shift(c);
    for (int i = 0; i < n; ++i) std::cout << B[i] << ' ';
    return 0;
}
