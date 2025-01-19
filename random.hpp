#pragma once

#include "rng.hpp"
#include <random>
#include <vector>

template<typename Tp> inline std::vector<Tp> random_vector(int n) {
    std::vector<Tp> res(n);
    xoshiro256starstar rng(std::random_device{}());
    std::uniform_int_distribution<decltype(Tp::mod())> dis(0, Tp::mod() - 1);
    for (int i = 0; i < n; ++i) res[i] = dis(rng);
    return res;
}

template<typename Tp> inline std::vector<Tp> random_vector_without_zero(int n) {
    std::vector<Tp> res(n);
    xoshiro256starstar rng(std::random_device{}());
    std::uniform_int_distribution<decltype(Tp::mod())> dis(1, Tp::mod() - 1);
    for (int i = 0; i < n; ++i) res[i] = dis(rng);
    return res;
}
