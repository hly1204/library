#pragma once

#include "fft.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

// returns max[0 <= j < a.size()]{a[j].size()}
template<typename Tp> inline int max_len_x_ks(const std::vector<std::vector<Tp>> &a) {
    int len = -1;
    for (int i = 0; i < (int)a.size(); ++i) len = std::max<int>(len, a[i].size());
    return len;
}

// returns a(x, x^N) where a(x,y) in R[x][y]
template<typename Tp>
inline std::vector<Tp> pack_2d_ks(const std::vector<std::vector<Tp>> &a, int N) {
    assert(N > 0);
    // y |-> x^N
    std::vector<Tp> b(N * a.size());
    for (int i = 0; i < (int)a.size(); ++i)
        for (int j = 0; j < (int)a[i].size(); ++j) b[i * N + j] += a[i][j]; // if N < a[i].size()
    return b;
}

template<typename Tp>
inline std::vector<std::vector<Tp>> unpack_2d_ks(const std::vector<Tp> &a, int N) {
    assert(N > 0);
    // x^N |-> y
    std::vector<std::vector<Tp>> b((a.size() + (N - 1)) / N, std::vector<Tp>(N));
    for (int i = 0; i < (int)((a.size() + N - 1) / N); ++i)
        for (int j = 0; j < N && i * N + j < (int)a.size(); ++j) b[i][j] = a[i * N + j];
    return b;
}

template<typename Tp> inline std::vector<std::vector<Tp>>
convolution_2d_naive(const std::vector<std::vector<Tp>> &a, const std::vector<std::vector<Tp>> &b) {
    if (a.empty() || b.empty()) return {};
    const int lenA = max_len_x_ks(a);
    const int lenB = max_len_x_ks(b);
    if (lenA == 0 || lenB == 0) return std::vector<std::vector<Tp>>(a.size() + b.size() - 1);
    const int N = lenA + lenB - 1;
    std::vector<std::vector<Tp>> ab(a.size() + b.size() - 1, std::vector<Tp>(N));
    for (int i = 0; i < (int)a.size(); ++i)
        for (int j = 0; j < (int)b.size(); ++j) {
            const auto aibj = convolution(a[i], b[j]);
            for (int k = 0; k < (int)aibj.size(); ++k) ab[i + j][k] += aibj[k];
        }
    return ab;
}

// standard Kronecker substitution
template<typename Tp> inline std::vector<std::vector<Tp>>
convolution_2d_ks(const std::vector<std::vector<Tp>> &a, const std::vector<std::vector<Tp>> &b) {
    if (a.empty() || b.empty()) return {};
    const int lenA = max_len_x_ks(a);
    const int lenB = max_len_x_ks(b);
    if (lenA == 0 || lenB == 0) return std::vector<std::vector<Tp>>(a.size() + b.size() - 1);
    const int N = lenA + lenB - 1;
    auto ab     = convolution(pack_2d_ks(a, N), pack_2d_ks(b, N));
    ab.resize((a.size() + b.size() - 1) * N);
    return unpack_2d_ks(ab, N);
}

// see:
// [1]: David Harvey. Faster polynomial multiplication via multipoint Kronecker substitution.
//      https://doi.org/10.1016/j.jsc.2009.05.004
template<typename Tp> inline std::vector<std::vector<Tp>>
convolution_2d_ks_reciprocal(const std::vector<std::vector<Tp>> &a,
                             const std::vector<std::vector<Tp>> &b) {
    if (a.empty() || b.empty()) return {};
    const int lenA = max_len_x_ks(a);
    const int lenB = max_len_x_ks(b);
    if (lenA == 0 || lenB == 0) return std::vector<std::vector<Tp>>(a.size() + b.size() - 1);
    const int N = std::max(lenA, lenB);
    // original version: compute a(x, x^(-N)) b(x, x^(-N))
    // modified version (this version): compute x^(2N-2) a(x^(-1), x^N) b(x^(-1), x^N)
    // ab0 = a(x, x^N) b(x, x^N)
    auto ab0 = convolution(pack_2d_ks(a, N), pack_2d_ks(b, N));

    // returns x^(N-1) a(x^(-1), y)
    auto make_reciprocal = [](const std::vector<std::vector<Tp>> &a, int N) {
        std::vector<std::vector<Tp>> b(a.size());
        for (int i = 0; i < (int)a.size(); ++i) {
            b[i] = a[i];
            b[i].resize(N);
            std::reverse(b[i].begin(), b[i].end());
        }
        return b;
    };

    // ab1 = x^(2N-2) a(x^(-1), x^N) b(x^(-1), x^N)
    auto ab1 =
        convolution(pack_2d_ks(make_reciprocal(a, N), N), pack_2d_ks(make_reciprocal(b, N), N));
    std::vector<std::vector<Tp>> ab(a.size() + b.size() - 1, std::vector<Tp>(N * 2 - 1));

    /*
        example:
                 let pack: a(x,y) |-> a(x,x^3)
                      rec: a(x,y) |-> x^2 a(x^(-1),y)

                 a = 1 + 2*x + 4*x^2 + (3 + 4*x)*y
                 b = 2 + 4*x + 5*x^2 + (5 + 8*x)*y
           pack(a) = 1 + 2*x + 4*x^2 + 3*x^3 + 4*x^4
           pack(b) = 2 + 4*x + 5*x^2 + 5*x^3 + 8*x^4
      pack(rec(a)) = 4 + 2*x +   x^2 + (0 + 4*x + 3*x^2)*y
      pack(rec(b)) = 5 + 4*x + 2*x^2 + (0 + 8*x + 5*x^2)*y
                ab = 2 + 8*x + 21*x^2 + 26*x^3 + 20*x^4 +
                                       (11     + 38*x   + 67*x^2 +  52*x^3)*y +
                                                                 + (15        + 44*x   + 32*x^2)*y^2
    pack(a)pack(b) = 2 + 8*x + 21*x^2 + 37*x^3 + 58*x^4 + 67*x^5 +  67*x^6    + 44*x^7 + 32*x^8
    pack(rec(a))pack(rec(b))
                   = 20 + 26*x + 21*x^2 + 8*x^3 + 2*x^4 +
                                        + ... (overlap)
    */

    // restore ab[0]
    for (int i = 0; i < N; ++i) ab[0][i] = ab0[i];
    // ab1[0] = [x^0](x^(2N - 2) a(x^(-1), x^N) b(x^(-1), x^N))
    for (int i = 0; i < N; ++i) ab[0][(N - 1) * 2 - i] = ab1[i];
    // restore ab[1..] by subtracting the overlaped coefficients
    for (int i = 1; i < (int)(a.size() + b.size() - 1); ++i) {
        // TODO: remove redundant assignment/subtraction
        for (int j = 0; j < N * 2 - 1; ++j) {
            ab0[(i - 1) * N + j] -= ab[i - 1][j];
            ab1[(i - 1) * N + j] -= ab[i - 1][(N - 1) * 2 - j];
        }
        for (int j = 0; j < N; ++j) ab[i][j] = ab0[i * N + j];
        for (int j = 0; j < N; ++j) ab[i][(N - 1) * 2 - j] = ab1[i * N + j];
    }
    for (int i = 0; i < (int)(a.size() + b.size() - 1); ++i) ab[i].resize(lenA + lenB - 1);
    return ab;
}

// see:
// [1]: David Harvey. Faster polynomial multiplication via multipoint Kronecker substitution.
//      https://doi.org/10.1016/j.jsc.2009.05.004
template<typename Tp> inline std::vector<std::vector<Tp>>
convolution_2d_ks_negated(const std::vector<std::vector<Tp>> &a,
                          const std::vector<std::vector<Tp>> &b) {
    if (a.empty() || b.empty()) return {};
    const int lenA = max_len_x_ks(a);
    const int lenB = max_len_x_ks(b);
    if (lenA == 0 || lenB == 0) return std::vector<std::vector<Tp>>(a.size() + b.size() - 1);
    const int N = std::max(lenA, lenB);
    // ab0 = a(x, x^N) b(x, x^N)
    const auto ab0 = convolution(pack_2d_ks(a, N), pack_2d_ks(b, N));

    // returns a(x, -y)
    auto make_negated = [](const std::vector<std::vector<Tp>> &a) {
        auto b = a;
        for (int i = 1; i < (int)b.size(); i += 2)
            for (int j = 0; j < (int)b[i].size(); ++j) b[i][j] = -b[i][j];
        return b;
    };

    // ab1 = a(x, -x^N) b(x, -x^N)
    const auto ab1 = convolution(pack_2d_ks(make_negated(a), N), pack_2d_ks(make_negated(b), N));

    /*
        example:
                 let pack: a(x,y) |-> a(x,x^3)

                 a = 1 + 2*x + 4*x^2 + (3 + 4*x)*y
                 b = 2 + 4*x + 5*x^2 + (5 + 8*x)*y
           pack(a) = 1 + 2*x + 4*x^2 + 3*x^3 + 4*x^4
           pack(b) = 2 + 4*x + 5*x^2 + 5*x^3 + 8*x^4
     pack(a(x,-y)) = 1 + 2*x + 4*x^2 + -(3*x^3 + 4*x^4)
     pack(b(x,-y)) = 2 + 4*x + 5*x^2 + -(5*x^3 + 8*x^4)
                ab = 2 + 8*x + 21*x^2 + 26*x^3 + 20*x^4 +
                                       (11     + 38*x   + 67*x^2 +  52*x^3)*y +
                                                                 + (15        + 44*x   + 32*x^2)*y^2
    pack(a)pack(b) = 2 + 8*x + 21*x^2 + 37*x^3 + 58*x^4 + 67*x^5 +  67*x^6    + 44*x^7 + 32*x^8
                                       (26+11)   (20+38) ...
    pack(a(x,-y))pack(b(x,-y))
                   = 2 + 8*x + 21*x^2 + 15*x^3 + -18*x^4 + ...
                                       (26-11)   (20-38) ...
    */

    std::vector<std::vector<Tp>> ab(a.size() + b.size() - 1, std::vector<Tp>(lenA + lenB - 1));
    for (int i = 0; i < (int)(a.size() + b.size() - 1); ++i) {
        if (i & 1) {
            for (int j = 0; j < lenA + lenB - 1; ++j)
                ab[i][j] = (ab0[i * N + j] - ab1[i * N + j]).div_by_2();
        } else {
            for (int j = 0; j < lenA + lenB - 1; ++j)
                ab[i][j] = (ab0[i * N + j] + ab1[i * N + j]).div_by_2();
        }
    }
    return ab;
}
