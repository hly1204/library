// competitive-verifier: PROBLEM https://judge.yosupo.jp/problem/aplusb

#include "modint.hpp"
#include "mps_basic.hpp"
#include "random.hpp"
#include "rng.hpp"
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

bool verify_inv(int dim) {
    assert(dim > 0);
    std::uniform_int_distribution<> dis(2, 10);
    xoshiro256starstar gen(std::random_device{}());
    using mint = ModInt<998244353>;
    std::vector<int> degree_bound(dim);
    for (int i = 0; i < dim; ++i) degree_bound[i] = dis(gen);
    const MDConvInfo info(degree_bound);
    auto a         = random_vector<mint>(info.len());
    a[0]           = dis(gen);
    const auto res = multidimensional_convolution(info, a, mps_inv(info, a));
    std::vector<mint> correct(info.len());
    correct[0] = 1;
    return res == correct;
}

bool verify_log_exp(int dim) {
    assert(dim > 0);
    std::uniform_int_distribution<> dis(2, 10);
    xoshiro256starstar gen(std::random_device{}());
    using mint = ModInt<998244353>;
    std::vector<int> degree_bound(dim);
    for (int i = 0; i < dim; ++i) degree_bound[i] = dis(gen);
    const MDConvInfo info(degree_bound);
    auto a          = random_vector<mint>(info.len());
    a[0]            = 1;
    const auto loga = mps_log(info, a);
    return mps_exp(info, loga) == a;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    for (int i = 0; i < 5; ++i) {
        const bool ok = verify_inv(i + 1);
        if (!ok) return 1;
    }
    for (int i = 0; i < 5; ++i) {
        const bool ok = verify_log_exp(i + 1);
        if (!ok) return 1;
    }
    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b;
    return 0;
}
