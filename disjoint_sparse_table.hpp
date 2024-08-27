#pragma once

#include "monoid.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

template <typename Tp, typename Op>
class DisjointSparseTable {
public:
    int S;
    const Monoid<Tp, Op> M;
    std::vector<Tp> T;

    DisjointSparseTable(const std::vector<Tp> &V, const Monoid<Tp, Op> &M) : M(M) {
        const int N = V.size();
        int LogN    = 0;
        while ((1 << LogN) < N) ++LogN;
        S = (1 << LogN);
        T.resize(std::max(LogN, 1) * S);
        for (int i = 0; i < N; ++i) T[i] = V[i];
        for (int i = N; i < S; ++i) T[i] = this->M.id();
        for (int i = 2; i <= LogN; ++i) {
            auto C = T.begin() + (i - 1) * S;
            for (int j = 0; j < S; j += (1 << i)) {
                const int mid = j + (1 << (i - 1));
                C[mid - 1]    = T[mid - 1];
                for (int k = mid - 2; k >= j; --k) C[k] = M(T[k], C[k + 1]);
                C[mid] = T[mid];
                for (int k = mid + 1; k < j + (1 << i); ++k) C[k] = M(C[k - 1], T[k]);
            }
        }
    }

    // returns M(V[L],...,V[R-1])
    Tp query(int L, int R) const {
        assert(L <= R);
        if (L == R) return M.id();
        if (R - L == 1) return T[L];
        const int lv = 31 - __builtin_clz(L ^ (R - 1));
        return M(T[lv * S + L], T[lv * S + (R - 1)]);
    }
};
