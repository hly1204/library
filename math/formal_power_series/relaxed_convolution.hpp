#ifndef RELAXED_CONVOLUTION_HEADER_HPP
#define RELAXED_CONVOLUTION_HEADER_HPP

/**
 * @brief relaxed convolution
 * @docs docs/math/formal_power_series/relaxed_convolution.md
 */

#include <algorithm>
#include <vector>

#include "radix_2_NTT.hpp"

namespace lib {

template <typename mod_t>
class RelaxedConvolution {
public:
  RelaxedConvolution(const std::vector<mod_t> &A, const std::vector<mod_t> &B)
      : A_(A), B_(B), contribution_(4), n_(0) {
    contribution_.reserve(1024);
  }
  ~RelaxedConvolution() = default;

  template <int THRESHOLD = 32>
  mod_t next() {
    int sz = contribution_.size(), len = get_ntt_len(n_ << 1 | 1);
    if (sz < len) contribution_.resize(len, mod_t(0));
    switch (n_) {
    case 0: contribution_[0] = A_[0] * B_[0]; break;
    case 1:
      contribution_[1] = A_[1] * B_[0] + A_[0] * B_[1], contribution_[2] = A_[1] * B_[1];
      break;
    case 2:
      contribution_[2] += A_[0] * B_[2] + A_[2] * B_[0],
          contribution_[3] += A_[1] * B_[2] + A_[2] * B_[1];
      break;
    default:
      if ((n_ & n_ - 1) == 0) {
        int t0 = n_ >> 1, t1 = n_;
        auto &c0 = dft_cache0_.emplace_back(A_.begin() + t0, A_.begin() + t1);
        auto &c1 = dft_cache1_.emplace_back(B_.begin() + t0, B_.begin() + t1);
        c0.resize(t1, mod_t(0));
        c1.resize(t1, mod_t(0));
        dft(t1, c0.data()), dft(t1, c1.data());
        std::vector<mod_t> res(t1);
        for (int i = 0; i < t1; ++i) res[i] = c0[i] * c1[i];
        idft(t1, res.data());
        for (int i = 0; i < t1 - 1; ++i) contribution_[t1 + i] += res[i];
      }
      contribution_[n_] += A_[0] * B_[n_] + A_[n_] * B_[0];
      contribution_[n_ + 1] += A_[1] * B_[n_] + A_[n_] * B_[1];
      for (int sft = 1, offset = get_ntt_len(n_ + 1) >> 1, t = n_ + 1 - offset;
           (t & 1) == 0 && 1 << sft < offset; ++sft, t >>= 1) {
        if (1 << sft <= THRESHOLD) {
          int m = n_ + 1 - (1 << sft);
          for (int i = 0; i != 1 << sft; ++i)
            for (int j = 0; j != 1 << sft; ++j)
              contribution_[n_ + 1 + i + j] +=
                  A_[m + i] * B_[j + (1 << sft)] + A_[j + (1 << sft)] * B_[m + i];
        } else {
          std::vector<mod_t> c0(A_.begin() + n_ + 1 - (1 << sft), A_.begin() + n_ + 1);
          std::vector<mod_t> c1(B_.begin() + n_ + 1 - (1 << sft), B_.begin() + n_ + 1);
          c0.resize(2 << sft, mod_t(0));
          c1.resize(2 << sft, mod_t(0));
          dft(2 << sft, c0.data()), dft(2 << sft, c1.data());
          for (int i = 0; i != 2 << sft; ++i)
            c0[i] = c0[i] * dft_cache1_[sft - 1][i] + c1[i] * dft_cache0_[sft - 1][i];
          idft(2 << sft, c0.data());
          for (int i = 0; i != (2 << sft) - 1; ++i) contribution_[n_ + 1 + i] += c0[i];
        }
      }
    }
    return contribution_[n_++];
  }

private:
  const std::vector<mod_t> &A_, &B_;
  std::vector<mod_t> contribution_;
  int n_;
  std::vector<std::vector<mod_t>> dft_cache0_, dft_cache1_;
};

} // namespace lib

#endif