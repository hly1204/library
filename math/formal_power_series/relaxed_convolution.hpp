#ifndef RELAXED_CONVOLUTION_HEADER_HPP
#define RELAXED_CONVOLUTION_HEADER_HPP

#include <algorithm>
#include <functional>
#include <utility>
#include <vector>

#include "radix_2_NTT.hpp"

namespace lib {

template <typename mod_t>
class RelaxedConvolution {
public:
  using handle_type = std::function<mod_t(int, const std::vector<mod_t> &)>;

  template <typename Fn1, typename Fn2>
  RelaxedConvolution(Fn1 &&handle_A, Fn2 &&handle_B)
      : contribution_(4, mod_t(0U)), n_(0), handle_A_(std::forward<Fn1>(handle_A)),
        handle_B_(std::forward<Fn2>(handle_B)) {}
  ~RelaxedConvolution()                          = default;
  RelaxedConvolution(const RelaxedConvolution &) = delete;
  RelaxedConvolution &operator=(const RelaxedConvolution &) = delete;
  const std::vector<mod_t> &get_multiplier() const { return B_; }
  const std::vector<mod_t> &get_multiplicand() const { return A_; }
  RelaxedConvolution &await(int k) {
    while (n_ < k) next();
    return *this;
  }
  mod_t at(int k) { return operator[](k); }
  mod_t operator[](int k) {
    while (n_ <= k) next();
    return contribution_[k];
  }
  mod_t next() {
    static constexpr int BASE_CASE_SIZE = 32;
    {
      int len = get_ntt_len(n_ << 1 | 1);
      if (static_cast<int>(contribution_.size()) < len) contribution_.resize(len, mod_t(0U));
    }
    switch (n_) {
    case 0:
      contribution_[0] = A_.emplace_back(handle_A_(0, contribution_)) *
                         B_.emplace_back(handle_B_(0, contribution_));
      break;
    case 1:
      contribution_[1] = A_.emplace_back(handle_A_(1, contribution_)) * B_.front() +
                         A_.front() * B_.emplace_back(handle_B_(1, contribution_));
      contribution_[2] = A_.back() * B_.back();
      break;
    case 2:
      contribution_[2] += A_.emplace_back(handle_A_(2, contribution_)) * B_.front() +
                          A_.front() * B_.emplace_back(handle_B_(2, contribution_));
      contribution_[3] = A_.back() * B_[1] + A_[1] * B_.back();
      break;
    default:
      if ((n_ & (n_ - 1)) == 0) {
        int t0 = n_ >> 1, t1 = n_;
        auto &c0 = dft_A_cache_.emplace_back(A_.begin() + t0, A_.begin() + t1);
        auto &c1 = dft_B_cache_.emplace_back(B_.begin() + t0, B_.begin() + t1);
        c0.resize(t1, mod_t(0U));
        c1.resize(t1, mod_t(0U));
        dft(c0), dft(c1);
        std::vector res(c0);
        for (int i = 0; i < t1; ++i) res[i] *= c1[i];
        idft(res);
        for (int i = 0; i < t1 - 1; ++i) contribution_[t1 + i] += res[i];
      }
      contribution_[n_] += A_.emplace_back(handle_A_(n_, contribution_)) * B_.front() +
                           A_.front() * B_.emplace_back(handle_B_(n_, contribution_));
      contribution_[n_ + 1] += A_[1] * B_.back() + A_.back() * B_[1];
      for (int sft = 1, offset = get_ntt_len(n_ + 1) >> 1, t = n_ + 1 - offset;
           (t & 1) == 0 && 1 << sft < offset; ++sft, t >>= 1)
        if (1 << sft <= BASE_CASE_SIZE) {
          for (int i = 0, m = n_ + 1 - (1 << sft); i != 1 << sft; ++i)
            for (int j = 0; j != 1 << sft; ++j)
              contribution_[n_ + 1 + i + j] +=
                  A_[m + i] * B_[j + (1 << sft)] + A_[j + (1 << sft)] * B_[m + i];
        } else {
          std::vector c0(A_.begin() + n_ + 1 - (1 << sft), A_.begin() + n_ + 1);
          std::vector c1(B_.begin() + n_ + 1 - (1 << sft), B_.begin() + n_ + 1);
          c0.resize(2 << sft, mod_t(0U));
          c1.resize(2 << sft, mod_t(0U));
          dft(c0), dft(c1);
          for (int i = 0; i != 2 << sft; ++i)
            c0[i] = c0[i] * dft_B_cache_[sft - 1][i] + c1[i] * dft_A_cache_[sft - 1][i];
          idft(c0);
          for (int i = 0; i != (2 << sft) - 1; ++i) contribution_[n_ + 1 + i] += c0[i];
        }
    }
    return contribution_[n_++];
  }

private:
  std::vector<mod_t> A_, B_, contribution_;
  std::vector<std::vector<mod_t>> dft_A_cache_, dft_B_cache_;
  int n_;
  handle_type handle_A_, handle_B_;
};

} // namespace lib

#endif