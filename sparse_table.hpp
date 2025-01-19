#pragma once

#include "monoid.hpp"
#include <cassert>
#include <vector>

template<typename Tp, typename Op> class SparseTable {
public:
    const int N;
    const Monoid<Tp, Op> M;
    std::vector<Tp> T;

    SparseTable(const std::vector<Tp> &V, const Monoid<Tp, Op> &M) : N(V.size()), M(M) {
        int LogN = 0;
        while ((1 << LogN) < N) ++LogN;
        T.resize((LogN + 1) * N);
        for (int i = 0; i < N; ++i) T[i] = V[i];
        for (int i = 1; i <= LogN; ++i) {
            auto P = T.begin() + (i - 1) * N, C = P + N;
            for (int j = 0; j < N - (1 << i) + 1; ++j) C[j] = M(P[j], P[j + (1 << (i - 1))]);
        }
    }

    // returns M(V[L],...,V[R-1])
    Tp query(int L, int R) const {
        assert(L <= R);
        if (L == R) return M.id();
        const int lv = 31 - __builtin_clz(R - L);
        return M(T[lv * N + L], T[lv * N + R - (1 << lv)]);
    }
};
