#pragma once

#include "binomial.hpp"
#include "fft.hpp"
#include "fps_basic.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

// returns g s.t. g(n) = sum[0 <= j < n] f(j)
template<typename Tp> inline std::vector<Tp> poly_prefix_sum(std::vector<Tp> f) {
    if (f.empty()) return {};
    const int n = f.size();
    auto &&bin  = Binomial<Tp>::get(n + 1);
    for (int i = 0; i < n; ++i) f[i] *= bin.factorial(i);
    std::vector<Tp> B(n);
    for (int i = 0; i < n; ++i) B[i] = bin.inv_factorial(i + 1);
    B = fps_inv(B, n); // B[j] = B_j/j! where B_j is the j-th Bernoulli number
    std::reverse(B.begin(), B.end());
    auto g = convolution(f, B);
    g.erase(g.begin(), g.begin() + (n - 1));
    g.insert(g.begin(), Tp(0));
    for (int i = 0; i <= n; ++i) g[i] *= bin.inv_factorial(i);
    // if we want g(n) = sum[0 <= j <= n] f(j), return g(n) + f(n)
    return g;
}
