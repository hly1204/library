#pragma once

#include <numeric>
#include <vector>

class DisjointSet {
    mutable std::vector<int> P;
    std::vector<int> S;

public:
    DisjointSet() = default;
    explicit DisjointSet(int N) : P(N), S(N) { std::iota(P.begin(), P.end(), 0); }
    void make_set(int N) {
        P.resize(N);
        S.assign(N, 1);
        std::iota(P.begin(), P.end(), 0);
    }
    int root(int u) const {
        // path halving
        while (P[u] != P[P[u]]) u = P[u] = P[P[u]];
        return P[u];
    }
    bool is_same(int u, int v) const { return root(u) == root(v); }
    int unite(int u, int v) {
        u = root(u), v = root(v);
        if (u == v) return u;
        if (S[u] < S[v]) return S[v] += S[u], P[u] = v;
        return S[u] += S[v], P[v] = u;
    }
    int component_size(int u) const { return S[root(u)]; }
};
