#ifndef SEMI_RELAXED_CONVOLUTION_HEADER_HPP
#define SEMI_RELAXED_CONVOLUTION_HEADER_HPP

/**
 * @brief semi-relaxed convolution
 * @docs docs/math/formal_power_series/semi_relaxed_convolution.md
 */

#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

#include "radix_2_NTT.hpp"

namespace lib {

// template <typename mod_t, typename HandleFunc>
// std::vector<mod_t> semi_relaxed_convolve(int n, const std::vector<mod_t> &A, std::vector<mod_t>
// &B,
//                                          HandleFunc &&relax) {
//   int len = get_ntt_len(n);
//   std::vector<mod_t> contribution(len << 1, mod_t(0)), A_cpy(A);
//   std::vector<std::vector<mod_t>> dft_A_cache;
//   A_cpy.resize(len, mod_t(0));

//   constexpr int THRESHOLD = 32;

//   std::function<void()> run_rec = [&](int l, int r, int lv) {
//     int len = r - l; // 计算 A[0,len) * B[l,r) 的贡献
//     if (r - l <= THRESHOLD) {
//       for (int i = 0; i < len; ++i) {
//         B[i + l] = relax(i + l, contribution);
//         for (int j = 0; j <= i; ++j) contribution[i + l] += A[j] * B[i + l - j];
//       }
//       if (lv) {
//         for (int i = 0; i < len - 1; ++i) {
//           for (int j = 0; j <= i; ++j) {}
//         }
//       }
//       return;
//     }
//     int block, block_size;
//     if (1 << 16 <= len) {
//       block = 16, block_size = len >> 4;
//     } else if (1 << 8 <= len) {
//       block = 8, block_size = len >> 3;
//     } else {
//       block = 4, block_size = len >> 2;
//     }
//     if (l == 0) { // 预处理 A 的 dft
//     }
//     for (int i = 0, block_left = 0, block_right = block_size; i < block;
//          ++i, block_left += block_size, block_right += block_size) {}
//   }(0, len, 0);
//   contribution.resize(n);
//   return contribution;
// }

} // namespace lib

#endif