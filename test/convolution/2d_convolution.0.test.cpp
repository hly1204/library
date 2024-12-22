#define PROBLEM "https://judge.yosupo.jp/problem/aplusb"

#include "ks.hpp"
#include "modint.hpp"
#include "random.hpp"
#include "rng.hpp"
#include <cassert>
#include <iostream>
#include <random>
#include <vector>

bool verify0() {
    std::uniform_int_distribution<> dis(2, 50);
    xoshiro256starstar gen(std::random_device{}());
    using mint        = ModInt<998244353>;
    const int maxLenA = dis(gen);
    const int maxLenB = dis(gen);
    std::vector<std::vector<mint>> A(maxLenA);
    std::vector<std::vector<mint>> B(maxLenB);
    for (int i = 0; i < maxLenA; ++i) A[i] = random_vector<mint>(dis(gen));
    for (int i = 0; i < maxLenB; ++i) B[i] = random_vector<mint>(dis(gen));
    return convolution_2d_ks(A, B) == convolution_2d_naive(A, B);
}

bool verify1() {
    std::uniform_int_distribution<> dis(2, 50);
    xoshiro256starstar gen(std::random_device{}());
    using mint        = ModInt<998244353>;
    const int maxLenA = dis(gen);
    const int maxLenB = dis(gen);
    std::vector<std::vector<mint>> A(maxLenA);
    std::vector<std::vector<mint>> B(maxLenB);
    for (int i = 0; i < maxLenA; ++i) A[i] = random_vector<mint>(dis(gen));
    for (int i = 0; i < maxLenB; ++i) B[i] = random_vector<mint>(dis(gen));
    return convolution_2d_ks_reciprocal(A, B) == convolution_2d_naive(A, B);
}

bool verify2() {
    std::uniform_int_distribution<> dis(2, 50);
    xoshiro256starstar gen(std::random_device{}());
    using mint        = ModInt<998244353>;
    const int maxLenA = dis(gen);
    const int maxLenB = dis(gen);
    std::vector<std::vector<mint>> A(maxLenA);
    std::vector<std::vector<mint>> B(maxLenB);
    for (int i = 0; i < maxLenA; ++i) A[i] = random_vector<mint>(dis(gen));
    for (int i = 0; i < maxLenB; ++i) B[i] = random_vector<mint>(dis(gen));
    return convolution_2d_ks_negated(A, B) == convolution_2d_naive(A, B);
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    assert(verify0());
    assert(verify1());
    assert(verify2());
    long long a, b;
    std::cin >> a >> b;
    std::cout << a + b;
    return 0;
}
