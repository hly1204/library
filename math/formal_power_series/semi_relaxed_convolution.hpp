#ifndef SEMI_RELAXED_CONVOLUTION_HEADER_HPP
#define SEMI_RELAXED_CONVOLUTION_HEADER_HPP

/**
 * @brief semi-relaxed convolution
 * @docs docs/math/formal_power_series/semi_relaxed_convolution.md
 */

#include <algorithm>
#include <functional>
#include <vector>

#include "radix_2_NTT.hpp"

namespace lib {

/**
 * @brief 半在线卷积计算 AB
 * @param n 计算前 n 项
 * @param A 离线给出 A 的系数
 * @param B 在线给出 B 的系数
 * @param relax 句柄函数用于获取 B 的系数，可依赖于 AB 之前已经完成计算的系数
 * @return std::vector<mod_t> AB mod x^n
 */
template <typename mod_t, typename HandleFuncType>
std::vector<mod_t> semi_relaxed_convolve(int n, const std::vector<mod_t> &A, std::vector<mod_t> &B,
                                         HandleFuncType &&relax) {
  int g_len = get_ntt_len(n);
  std::vector<mod_t> contribution(g_len, mod_t(0)), A_cpy(A);
  std::vector<std::vector<std::vector<mod_t>>> dft_A_cache;
  A_cpy.resize(g_len, mod_t(0));
  B.resize(g_len, mod_t(0));

  constexpr int THRESHOLD = 32;
  /**
   * @brief 计算 A[0,g_len) * B[l,r) 的贡献
   * @note 为了能计算幂级数倒数等，需要在获取句柄前先计算完对角线上的贡献
   */
  std::function<void(int, int, int)> run_rec = [&](int l, int r, int lv) {
    int len = r - l;
    if (r - l <= THRESHOLD) {
      for (int i = 0; i < len; ++i) {
        for (int j = 1; j <= i; ++j) contribution[i + l] += A_cpy[j] * B[i + l - j];
        if (i + l < n) contribution[i + l] += A_cpy[0] * (B[i + l] = relax(i + l, contribution));
      }
      return;
    }
    int block = 16, block_size = len >> 4;
    if (len < 1 << 16) block = 8, block_size = len >> 3;
    int block_size2 = block_size << 1;
    if (l == 0) {
      auto &dft_block = dft_A_cache.emplace_back();
      for (int i = 0; i < block - 1; ++i)
        dft(dft_block.emplace_back(A_cpy.begin() + l + i * block_size,
                                   A_cpy.begin() + l + (i + 2) * block_size));
    }
    std::vector<std::vector<mod_t>> dft_B_cache;
    for (int i = 0; i < block; ++i) {
      int rec_l = l + i * block_size, rec_r = rec_l + block_size;
      run_rec(rec_l, rec_r, lv + 1);
      if (i != block - 1) {
        dft_B_cache.emplace_back(B.begin() + rec_l, B.begin() + rec_r)
            .resize(block_size2, mod_t(0));
        dft(dft_B_cache.back());
        std::vector<mod_t> sum_temp(block_size2, mod_t(0));
        for (int j = 0; j <= i; ++j)
          for (int k = 0; k != block_size2; ++k)
            sum_temp[k] += dft_A_cache[lv][i - j][k] * dft_B_cache[j][k];
        idft(sum_temp);
        for (int j = 0; j != block_size; ++j) contribution[rec_r + j] += sum_temp[block_size + j];
      }
    }
  };
  run_rec(0, g_len, 0);
  contribution.resize(n);
  B.resize(n);
  return contribution;
}

} // namespace lib

#endif