#pragma once

#include <vector>

template <typename Tp>
inline std::vector<Tp> batch_inv(const std::vector<Tp> &a) {
    if (a.empty()) return {};
    const int n = a.size();
    std::vector<Tp> b(n);
    Tp v = 1;
    for (int i = 0; i < n; ++i) b[i] = v, v *= a[i];
    v = v.inv();
    for (int i = n - 1; i >= 0; --i) b[i] *= v, v *= a[i];
    return b;
}
