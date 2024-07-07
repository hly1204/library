#pragma once

#include "fft.hpp"
#include <vector>

template <typename Tp>
inline std::vector<Tp> poly_product(std::vector<std::vector<Tp>> L) {
    if (L.empty()) return {Tp(1)};
    std::vector<std::vector<Tp>> res;
    while (L.size() > 1) {
        for (int i = 0; i + 1 < (int)L.size(); i += 2) res.push_back(convolution(L[i], L[i + 1]));
        if (L.size() & 1) res.push_back(L.back());
        L.swap(res);
        res.clear();
    }
    return res[0];
}
