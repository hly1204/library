#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "poly_998244353_portable.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using namespace hly;
    int n;
    long long m;
    std::cin >> n >> m;
    Poly A(n);
    for (int i = 0; i < n; ++i) std::cin >> A[i];
    const Poly powA = A.pow(m, n);
    for (int i = 0; i < n; ++i) std::cout << powA[i] << ' ';
    return 0;
}
