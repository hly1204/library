#pragma once

#include "fft.hpp"
#include <utility>
#include <vector>

// TODO: cache dft
template<typename Tp> inline std::vector<Tp> poly_product(std::vector<std::vector<Tp>> L) {
    if (L.empty()) return {Tp(1)};
    while (L.size() > 1) {
        std::vector<std::vector<Tp>> t;
        for (int i = 0; i + 1 < (int)L.size(); i += 2) t.push_back(convolution(L[i], L[i + 1]));
        if (L.size() & 1) t.push_back(L.back());
        L = std::move(t);
    }
    return L[0];
}
