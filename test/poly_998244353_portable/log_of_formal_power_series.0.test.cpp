#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"

#include "poly_998244353_portable.hpp"
#include <iostream>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using namespace hly;
    int n;
    std::cin >> n;
    Poly A(n);
    for (int i = 0; i < n; ++i) std::cin >> A[i];
    const Poly logA = A.log(n);
    for (int i = 0; i < n; ++i) std::cout << logA[i] << ' ';
    return 0;
}
