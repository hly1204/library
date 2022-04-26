#ifndef SEMI_RELAXED_CONVOLUTION_HPP
#define SEMI_RELAXED_CONVOLUTION_HPP

#include "../common.hpp"
#include "radix2_ntt.hpp"

#include <algorithm>
#include <type_traits>
#include <utility>
#include <vector>

LIB_BEGIN

template <typename ModIntT, typename FnT>
class semi_relaxed_convolution {
  std::vector<ModIntT> fixed_A_{}, B_{}, c_{};
  std::vector<std::vector<std::vector<ModIntT>>> dft_A_cache_{}, dft_B_cache_{};
  int n_{};
  FnT handle_;

  enum : int { BASE_CASE_SIZE = 32, LOG_BLOCK = 4, BLOCK = 1 << LOG_BLOCK, MASK = BLOCK - 1 };

  static_assert((BASE_CASE_SIZE & (BASE_CASE_SIZE - 1)) == 0);
  static_assert(std::is_invocable_r_v<ModIntT, FnT, int, const std::vector<ModIntT> &> ||
                std::is_invocable_r_v<ModIntT, FnT, int>);

public:
  semi_relaxed_convolution(const std::vector<ModIntT> &A, FnT &&handle)
      : fixed_A_(A), c_(1024), handle_(std::forward<FnT>(handle)) {}
  const std::vector<ModIntT> &get_multiplier() const { return B_; }
  const std::vector<ModIntT> &get_multiplicand() const { return fixed_A_; }
  semi_relaxed_convolution &await(int k) {
    while (n_ < k) next();
    return *this;
  }
  ModIntT at(int k) {
    while (n_ <= k) next();
    return c_[k];
  }
  ModIntT operator[](int k) { return at(k); }
  ModIntT next();
};

template <typename ModIntT, typename FnT>
ModIntT semi_relaxed_convolution<ModIntT, FnT>::next() {
  {
    // enlarge space
    int len = ntt_len(n_ << 1 | 1);
    if (static_cast<int>(c_.size()) < len) c_.resize(len);
    if (static_cast<int>(fixed_A_.size()) < len) fixed_A_.resize(len);
  }
  if ((n_ & (BASE_CASE_SIZE - 1)) == 0)
    for (int t = n_ / BASE_CASE_SIZE, block_size = BASE_CASE_SIZE, lv = 0; t != 0;
         t >>= LOG_BLOCK, block_size <<= LOG_BLOCK, ++lv)
      if (int i = t & MASK, block_size2 = block_size << 1, l = n_ - block_size; i != 0) {
        if (block_size * i == n_) {
          if (static_cast<int>(dft_A_cache_.size()) == lv) {
            dft_A_cache_.emplace_back();
            dft_B_cache_.emplace_back(BLOCK - 1);
          }
          dft(dft_A_cache_[lv].emplace_back(fixed_A_.cbegin() + (i - 1) * block_size,
                                            fixed_A_.cbegin() + (i + 1) * block_size));
        }
        auto &B_cache = dft_B_cache_[lv];
        B_cache[i - 1].resize(block_size2);
        std::fill_n(std::copy_n(B_.cbegin() + l, block_size, B_cache[i - 1].begin()), block_size,
                    ModIntT());
        dft(B_cache[i - 1]);
        std::vector<ModIntT> temp_sum(block_size2);
        for (int j = 0; j != i; ++j)
          for (int k = 0; k != block_size2; ++k)
            temp_sum[k] += dft_A_cache_[lv][i - 1 - j][k] * B_cache[j][k];
        idft(temp_sum);
        for (int j = block_size; j != block_size2; ++j) c_[j + n_ - block_size] += temp_sum[j];
        break;
      }
  for (int i = 0, l = n_ & ~(BASE_CASE_SIZE - 1); i < n_ - l; ++i)
    c_[n_] += fixed_A_[n_ - l - i] * B_[l + i];
  // clang-format off
  if constexpr (std::is_invocable_r_v<ModIntT, FnT, int, const std::vector<ModIntT> &>)
    c_[n_] += fixed_A_.front() * B_.emplace_back(handle_(n_, c_));
  else
    c_[n_] += fixed_A_.front() * B_.emplace_back(handle_(n_));
  // clang-format on
  return c_[n_++];
}

LIB_END

#endif