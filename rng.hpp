#pragma once

#include <cstdint>
#include <limits>

// see: https://prng.di.unimi.it/xoshiro256starstar.c
// original license CC0 1.0
class xoshiro256starstar {
    using u64 = std::uint64_t;

    static inline u64 rotl(const u64 x, int k) { return (x << k) | (x >> (64 - k)); }

    u64 s_[4];

    u64 next() {
        const u64 res = rotl(s_[1] * 5, 7) * 9;
        const u64 t   = s_[1] << 17;
        s_[2] ^= s_[0];
        s_[3] ^= s_[1];
        s_[1] ^= s_[2];
        s_[0] ^= s_[3];
        s_[2] ^= t;
        s_[3] = rotl(s_[3], 45);
        return res;
    }

public:
    // see: https://prng.di.unimi.it/splitmix64.c
    // original license CC0 1.0
    explicit xoshiro256starstar(u64 seed) {
        for (int i = 0; i < 4; ++i) {
            u64 z = (seed += 0x9e3779b97f4a7c15);
            z     = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
            z     = (z ^ (z >> 27)) * 0x94d049bb133111eb;
            s_[i] = z ^ (z >> 31);
        }
    }
    // see: https://en.cppreference.com/w/cpp/named_req/UniformRandomBitGenerator
    using result_type = u64;
    static constexpr u64 min() { return std::numeric_limits<u64>::min(); }
    static constexpr u64 max() { return std::numeric_limits<u64>::max(); }
    u64 operator()() { return next(); }
};
