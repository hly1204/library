#pragma once

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

template<typename Tp, typename Comp = std::less<>, typename UInt = unsigned> class RMQ {
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

    Tp build_block(typename std::vector<Tp>::const_iterator A, int N,
                   typename std::vector<UInt>::iterator D) {
        UInt stack_num = 0;
        for (int i = 0, sta[W], top = 0; i < N; ++i) {
            while (top > 0 && Cmp(A[i], A[sta[top - 1]])) stack_num ^= (UInt)1 << sta[--top];
            D[i] = (stack_num |= (UInt)1 << (sta[top++] = i));
        }
        return A[__builtin_ctzll(stack_num)];
    }

    // [L, R) in same block
    Tp block(int L, int R) const { return T[L + __builtin_ctzll(StackNum[R - 1] >> (L % W))]; }

    static constexpr int W = sizeof(UInt) * 8;

    std::vector<Tp> T;
    Comp Cmp;
    SparseTableInner ST;
    std::vector<UInt> StackNum;

public:
    explicit RMQ(const std::vector<Tp> &V, Comp comp = Comp())
        : T(V), Cmp(comp), ST(*this), StackNum(V.size()) {
        std::vector<Tp> b;
        const int B = ((int)V.size() + (W - 1)) / W;
        b.reserve(B);
        for (int i = 0; i < B; ++i)
            b.emplace_back(build_block(V.begin() + i * W,
                                       std::min<int>((i + 1) * W, V.size()) - i * W,
                                       StackNum.begin() + i * W));
        ST.build(b);
    }

    Tp query(int L, int R) const {
        assert(L < R);
        const int BL = L / W, BR = (R - 1) / W;
        if (BL == BR) return block(L, R);
        if (BL + 1 == BR) return std::min(block(L, BR * W), block(BR * W, R), Cmp);
        return std::min({block(L, (BL + 1) * W), ST.query(BL + 1, BR), block(BR * W, R)}, Cmp);
    }
};
