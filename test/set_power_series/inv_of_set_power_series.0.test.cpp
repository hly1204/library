#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_set_power_series"

#include "modint.hpp"
#include "sps_basic.hpp"
#include <iostream>
#include <vector>

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    using mint = ModInt<998244353>;
    int n;
    std::cin >> n;
    std::vector<mint> a(1 << n);
    for (int i = 0; i < (1 << n); ++i) std::cin >> a[i];
    const auto expa = sps_exp(a);
    assert(sps_inv(sps_inv(expa)) == expa);
    for (int i = 0; i < (1 << n); ++i) std::cout << expa[i] << ' ';
    return 0;
}
