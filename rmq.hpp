#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

template <typename Tp, typename Comp = std::less<>>
class RMQ {
public:
    class SparseTableInner {
        const RMQ &Rmq;
        int N;
        std::vector<Tp> T;

    public:
        explicit SparseTableInner(const RMQ &R) : Rmq(R), N() {}

        void build(const std::vector<Tp> &V) {
            N        = V.size();
            int LogN = 0;
            while ((1 << LogN) < N) ++LogN;
            T.resize((LogN + 1) * N);
            for (int i = 0; i < N; ++i) T[i] = V[i];
            for (int i = 1; i <= LogN; ++i) {
                auto P = T.begin() + (i - 1) * N, C = P + N;
                for (int j = 0; j < N - (1 << i) + 1; ++j)
                    C[j] = std::min(P[j], P[j + (1 << (i - 1))], Rmq.Cmp);
            }
        }

        // returns M(V[L],...,V[R-1])
        Tp query(int L, int R) const {
            assert(L < R);
            const int lv = 31 - __builtin_clz(R - L);
            return std::min(T[lv * N + L], T[lv * N + R - (1 << lv)], Rmq.Cmp);
        }
    };

    std::vector<Tp> T;
    Comp Cmp;
    SparseTableInner ST;
    std::vector<unsigned> StackNum;

    explicit RMQ(const std::vector<Tp> &V, Comp comp = Comp())
        : T(V), Cmp(comp), ST(*this), StackNum(V.size()) {
        if (V.empty()) return;
        std::vector<Tp> b;
        const int B = ((int)V.size() - 1) / 32 + 1;
        b.reserve(B);
        for (int i = 0; i < B; ++i)
            b.emplace_back(build_block(V.begin() + i * 32,
                                       std::min<int>((i + 1) * 32, V.size()) - i * 32,
                                       StackNum.begin() + i * 32));
        ST.build(b);
    }

    Tp build_block(typename std::vector<Tp>::const_iterator A, int N,
                   typename std::vector<unsigned>::iterator D) {
        unsigned stack_num = 0;
        for (int i = 0, sta[32], top = 0; i < N; ++i) {
            while (top > 0 && Cmp(A[i], A[sta[top - 1]])) stack_num ^= 1U << sta[--top];
            D[i] = (stack_num |= 1U << (sta[top++] = i));
        }
        return A[__builtin_ctz(stack_num)];
    }

    // [L, R) in same block
    Tp query_block(int L, int R) { return T[L + __builtin_ctz(StackNum[R - 1] >> (L % 32))]; }

    Tp query(int L, int R) {
        assert(L < R);
        const int BL = L / 32, BR = (R - 1) / 32;
        if (BL == BR) return query_block(L, R);
        if (BL + 1 == BR) return std::min(query_block(L, BR * 32), query_block(BR * 32, R), Cmp);
        return std::min(
            {query_block(L, (BL + 1) * 32), ST.query(BL + 1, BR), query_block(BR * 32, R)}, Cmp);
    }
};
