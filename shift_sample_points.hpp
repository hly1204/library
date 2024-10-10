#pragma once

#include "falling_factorial_poly.hpp"
#include <vector>

template <typename Tp>
inline std::vector<Tp> shift_sample_points(const std::vector<Tp> &F, Tp c, int m) {
    return ffp_to_sample_points(shift_ffp(sample_points_to_ffp(F), c), m);
}
