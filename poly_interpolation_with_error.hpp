#pragma once

#include "poly.hpp"
#include "subproduct_tree.hpp"
#include <vector>

// returns F s.t. n=X.size(), deg(F)<n-2t with at most t Y[i] corrupted for F(X[i])=Y[i]
template<typename Tp> inline std::vector<Tp>
interpolation_with_error(const std::vector<Tp> &X, const std::vector<Tp> &Y, int t) {
    assert(X.size() == Y.size());
    const SubproductTree<Tp> T(X);
    const auto prod   = T.product();
    const auto B      = T.interpolation(Y);
    const auto [P, Q] = rational_approximation(Poly<Tp>(B.begin(), B.end()),
                                               Poly<Tp>(prod.begin(), prod.end()), t * 2);
    return Poly<Tp>(B.begin(), B.end()) - (P * Poly<Tp>(prod.begin(), prod.end())) / Q;
}
