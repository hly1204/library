#define PROBLEM "https://judge.yosupo.jp/problem/matrix_det_mod_2"

#include "bitarray.hpp"
#include <iostream>
#include <string>
#include <vector>

using BitMatrix = std::vector<BitArray>;

bool det(BitMatrix A) {
    const int n = A.size();
    for (int i = 0; i < n; ++i) {
        int pivot = i;
        for (; pivot < n; ++pivot)
            if (A[pivot].test(i)) break;
        if (pivot == n) return false;
        if (pivot != i) A[pivot].swap(A[i]);
        for (int j = i + 1; j < n; ++j)
            if (A[j].test(i)) A[j] ^= A[i];
    }
    return true;
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
    std::cout << det(A);
    return 0;
}
