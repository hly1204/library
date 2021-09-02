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
 * @warning 目前效率较低，可能是因为没有使用 middle product 的方法但我还不知道如何优化！！！
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
  std::vector<mod_t> contribution(g_len << 1, mod_t(0)), A_cpy(A);
  std::vector<std::vector<std::vector<mod_t>>> dft_A_cache, level_dft_sum_cache;
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
      if (r != g_len)
        for (int i = len; i < (len << 1) - 1; ++i)
          for (int j = i + 1 - len; j < len; ++j) contribution[i + l] += A_cpy[j] * B[i + l - j];
      return;
    }
    const int block = 16, block_size = len >> 4;
    if (l == 0) {
      auto &dft_block = dft_A_cache.emplace_back();
      for (int i = 1; i < block; ++i) {
        dft_block.emplace_back(A_cpy.begin() + i * block_size, A_cpy.begin() + (i + 1) * block_size)
            .resize(block_size << 1, mod_t(0));
        dft(dft_block.back());
      }
      level_dft_sum_cache.emplace_back(
          std::vector<std::vector<mod_t>>(block, std::vector<mod_t>(block_size << 1, mod_t(0))));
    } else {
      idft(level_dft_sum_cache[lv][0]);
      for (int i = 0; i != (block_size << 1) - 1; ++i)
        contribution[l + i] += level_dft_sum_cache[lv][0][i];
      std::fill_n(level_dft_sum_cache[lv].back().begin(), block_size << 1, mod_t(0));
    }
    std::vector<std::vector<mod_t>> dft_B_cache;
    for (int i = 0; i < block; ++i) {
      run_rec(l + i * block_size, l + (i + 1) * block_size, lv + 1);
      if (r == g_len && i == block - 1) return;
      dft_B_cache.emplace_back(B.begin() + l + i * block_size, B.begin() + l + (i + 1) * block_size)
          .resize(block_size << 1, mod_t(0));
      dft(dft_B_cache.back());
      if (i != block - 1) {
        std::vector<mod_t> &sum_temp = level_dft_sum_cache[lv][i + 1];
        for (int j = 0; j <= i; ++j)
          for (int k = 0; k != block_size << 1; ++k)
            sum_temp[k] += dft_A_cache[lv][i - j][k] * dft_B_cache[j][k];
        idft(sum_temp);
        for (int j = 0, offset = l + (i + 1) * block_size; j != (block_size << 1) - 1; ++j)
          contribution[offset + j] += sum_temp[j];
      }
    }
    for (int i = block; i < (block << 1) - 1; ++i) {
      std::vector<mod_t> &sum_temp = level_dft_sum_cache[lv][i - block];
      std::fill_n(sum_temp.begin(), block_size << 1, mod_t(0));
      for (int j = i + 1 - block; j < block; ++j)
        for (int k = 0; k != block_size << 1; ++k)
          sum_temp[k] += dft_A_cache[lv][i - 1 - j][k] * dft_B_cache[j][k];
    }
  };
  run_rec(0, g_len, 0);
  contribution.resize(n);
  B.resize(n);
  return contribution;
}

} // namespace lib

#endif