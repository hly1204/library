#pragma once

#include <algorithm>
#include <string>
#include <vector>

inline std::vector<int> suffix_array(const std::string &s) {
    if (s.empty()) return {};
    auto radix_pass = [](auto &&a, auto &&b, auto &&r, int n, int K) {
        std::vector<int> c(K + 1);
        for (int i = 0; i < n; ++i) ++c[r[a[i]]];
        for (int i = 1; i <= K; ++i) c[i] += c[i - 1];
        for (int i = n - 1; i >= 0; --i) b[--c[r[a[i]]]] = a[i];
    };
    const int n = s.size();
    int K       = *std::max_element(s.begin(), s.end());
    std::vector<int> rank0(n), rank1(n), t(n), sa(n);
    for (int i = 0; i < n; ++i) rank0[sa[i] = i] = s[i];
    for (int i = 1;; i *= 2) {
        for (int j = 0; j < n; ++j) rank1[j] = (i + j < n) ? rank0[i + j] : 0;
        radix_pass(sa, t, rank1, n, K);
        radix_pass(t, sa, rank0, n, K);
        t[sa[0]] = K = 1;
        for (int j = 1; j < n; ++j)
            t[sa[j]] =
                (rank0[sa[j]] == rank0[sa[j - 1]] && rank1[sa[j]] == rank1[sa[j - 1]]) ? K : ++K;
        if (K == n) return sa;
        rank0.swap(t);
    }
}
