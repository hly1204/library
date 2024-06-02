#pragma once

#include "rng.hpp"
#include <random>
#include <vector>

template <typename Tp>
std::vector<Tp> sqrt_mod_prime(Tp a) {
    // Bostan--Mori's algorithm
    const auto p = Tp::mod();
    if (p == 2 || a == 0) return {a};
    if (a.pow(p / 2) == -1) return {};
    if ((p & 3) == 3) {
        const auto b = a.pow((p + 1) / 4);
        return {b, -b};
    }
    xoshiro256starstar rng(std::random_device{}());
    std::uniform_int_distribution<std::decay_t<decltype(p)>> dis(2, p - 1);
    Tp t;
    do { t = dis(rng); } while ((t * t - a * 4).pow(p / 2) != -1);
    Tp k0 = 1, k1, k2 = -t, k3 = a;
    for (auto e = (p + 1) >> 1;;) {
        if (e & 1) {
            k0 = k1 - k0 * k2, k1 *= k3;
        } else {
            k1 = k0 * k3 - k1 * k2;
        }
        if ((e >>= 1) == 0) return {k0, -k0};
        k2 = k3 + k3 - k2 * k2, k3 *= k3;
    }
}
