#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix_mod_2"

#include "bitarray.hpp"
#include <iostream>
#include <optional>
#include <string>
#include <vector>

using BitMatrix = std::vector<BitArray>;

std::optional<BitMatrix> mat_inv(BitMatrix A) {
    const int n = A.size();
    for (int i = 0; i < n; ++i) {
        A[i].resize(n * 2);
        A[i].set(n + i);
    }
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (; pivot < n; ++pivot)
            if (A[pivot].test(i)) break;
        if (pivot == n) return {};
        if (pivot != i) A[pivot].swap(A[i]);
        for (int j = i + 1; j < n; ++j)
            if (A[j].test(i)) A[j] ^= A[i];
    }
    for (int i = n - 1; i > 0; --i)
        for (int j = i - 1; j >= 0; --j)
            if (A[j].test(i)) A[j] ^= A[i];
    for (int i = 0; i < n; ++i) A[i] = BitArray(A[i].to_string().substr(n));
    return A;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin >> n;
    BitMatrix A(n);
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        A[i] = BitArray(s);
    }
    if (const auto invA = mat_inv(A)) {
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) std::cout << invA->at(i).at(j) << " \n"[j == n - 1];
    } else {
        std::cout << "-1";
    }
    return 0;
}
