#pragma once

#include "fft.hpp"
#include "modlong.hpp"
#include <vector>

inline std::vector<int> convolution_mod(const std::vector<int> &a, const std::vector<int> &b,
                                        int modular) {
    using mint0 = ModLong<0x3F9A000000000001>;
    using mint1 = ModLong<0x3FC6000000000001>;
    auto res0   = convolution_fft(std::vector<mint0>(a.begin(), a.end()),
                                  std::vector<mint0>(b.begin(), b.end()));
    auto res1   = convolution_fft(std::vector<mint1>(a.begin(), a.end()),
                                  std::vector<mint1>(b.begin(), b.end()));

    const int n = res0.size();
    std::vector<int> res(n);
    const mint0 im1 = mint0(mint1::mod()).inv();
    const int m1    = mint1::mod() % modular;
    for (int i = 0; i < n; ++i) {
        const mint0 k1 = (res0[i] - res1[i].val()) * im1;
        res[i]         = (k1.val() % modular * m1 + res1[i].val()) % modular;
    }
    return res;
}
