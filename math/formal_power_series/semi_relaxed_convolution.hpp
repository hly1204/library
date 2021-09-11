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

template <typename mod_t>
class SemiRelaxedConvolution {
public:
  /**
   * @param A 离线给出 A 的系数，取拷贝
   * @param B 在线给出 B 的系数，取引用
   */
  SemiRelaxedConvolution(const std::vector<mod_t> &A, std::vector<mod_t> &B,
                         const std::function<mod_t(int, const std::vector<mod_t> &)> &handle)
      : fixed_A_(A), contribution_(1024, mod_t(0)), B_(B), n_(0), handle_(handle) {
    B_.clear();
    B_.reserve(1024);
  }
  ~SemiRelaxedConvolution() = default;

  mod_t next() {
    static constexpr int BASECASE_SIZE = 32;
    static constexpr int LOG_BLOCK     = 4;
    static constexpr int BLOCK         = 1 << LOG_BLOCK;
    static constexpr int MASK          = BLOCK - 1;

    int len = get_ntt_len(n_ << 1 | 1);

    if (static_cast<int>(contribution_.size()) < len) contribution_.resize(len, mod_t(0));
    if (static_cast<int>(fixed_A_.size()) < len) fixed_A_.resize(len, mod_t(0));

    if ((n_ & (BASECASE_SIZE - 1)) == 0)
      for (int t = n_ / BASECASE_SIZE, block_size = BASECASE_SIZE, lv = 0; t != 0;
           t >>= LOG_BLOCK, block_size <<= LOG_BLOCK, ++lv)
        if (int i = t & MASK, block_size2 = block_size << 1, l = n_ - block_size; i != 0) {
          if (n_ - block_size * i == 0) {
            if (static_cast<int>(dft_A_cache_.size()) == lv) {
              dft_A_cache_.emplace_back();
              dft_B_cache_.emplace_back(BLOCK - 1);
            }
            dft(dft_A_cache_[lv].emplace_back(fixed_A_.begin() + (i - 1) * block_size,
                                              fixed_A_.begin() + (i + 1) * block_size));
          }
          auto &B_cache = dft_B_cache_[lv];
          B_cache[i - 1].resize(block_size2);
          std::fill_n(std::copy_n(B_.begin() + l, block_size, B_cache[i - 1].begin()), block_size,
                      mod_t(0));
          dft(B_cache[i - 1]);
          std::vector<mod_t> temp_sum(block_size2, mod_t(0));
          for (int j = 0; j < i; ++j)
            for (int k = 0; k != block_size2; ++k)
              temp_sum[k] += dft_A_cache_[lv][i - 1 - j][k] * B_cache[j][k];
          idft(temp_sum);
          for (int j = block_size; j != block_size2; ++j)
            contribution_[j + n_ - block_size] += temp_sum[j];
          break;
        }

    for (int i = 0, l = n_ / BASECASE_SIZE * BASECASE_SIZE; i < n_ - l; ++i)
      contribution_[n_] += fixed_A_[n_ - l - i] * B_[l + i];
    return contribution_[n_] += fixed_A_[0] * B_.emplace_back(handle_(n_, contribution_)),
           contribution_[n_++];
  }

private:
  std::vector<mod_t> fixed_A_, contribution_;
  std::vector<mod_t> &B_;
  std::vector<std::vector<std::vector<mod_t>>> dft_A_cache_, dft_B_cache_;
  int n_;
  std::function<mod_t(int, const std::vector<mod_t> &)> handle_;
};

} // namespace lib

#endif