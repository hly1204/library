#ifndef RELAXED_CONVOLUTION_HPP
#define RELAXED_CONVOLUTION_HPP

#include "../common.hpp"
#include "radix2_ntt.hpp"

#include <functional>
#include <type_traits>
#include <vector>

LIB_BEGIN

template <typename ModIntT>
class relaxed_convolution {                       // O(n log^2 n) impl
  std::vector<ModIntT> a_{}, b_{}, c_{};          // `a_ * b_` = `c_`
  std::vector<std::vector<ModIntT>> ac_{}, bc_{}; // cached DFTs
  std::function<ModIntT()> ha_{}, hb_{};          // handle for `a` and `b`
  int n_{};                                       // counter

  template <typename FnT>
  static auto wrap(FnT &&f, int &n, const std::vector<ModIntT> &c, std::vector<ModIntT> &e) {
    if constexpr (std::is_invocable_r_v<ModIntT, FnT, int, const std::vector<ModIntT> &>) {
      return std::bind(
          [f](int n, const std::vector<ModIntT> &c, std::vector<ModIntT> &e) mutable {
            return ModIntT(e.emplace_back(f(n, c)));
          },
          std::cref(n), std::cref(c), std::ref(e));
    } else if constexpr (std::is_invocable_r_v<ModIntT, FnT, int>) {
      return std::bind(
          [f](int n, std::vector<ModIntT> &e) mutable { return ModIntT(e.emplace_back(f(n))); },
          std::cref(n), std::ref(e));
    } else if constexpr (std::is_invocable_r_v<ModIntT, FnT>) {
      return std::bind(
          [f](std::vector<ModIntT> &e) mutable { return ModIntT(e.emplace_back(f())); },
          std::ref(e));
    } else {
      throw;
    }
  }

  enum : int { BASE_CASE_SIZE = 32 };

  static_assert((BASE_CASE_SIZE & (BASE_CASE_SIZE - 1)) == 0);

public:
  // `h0` multiplicand, `h1` multiplier
  template <typename Fn0T, typename Fn1T>
  relaxed_convolution(Fn0T &&h0, Fn1T &&h1)
      : c_(4), ha_(wrap(h0, n_, c_, a_)), hb_(wrap(h1, n_, c_, b_)) {}
  const std::vector<ModIntT> &get_multiplier() const { return b_; }
  const std::vector<ModIntT> &get_multiplicand() const { return a_; }
  relaxed_convolution &await(int k) {
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

template <typename ModIntT>
ModIntT relaxed_convolution<ModIntT>::next() {
  {
    // enlarge space
    int len = ntt_len(n_ << 1 | 1);
    if (static_cast<int>(c_.size()) < len) c_.resize(len);
  }
  switch (n_) {
  case 0: c_[0] = ha_() * hb_(); break;
  case 1:
    c_[1] = ha_() * b_.front() + a_.front() * hb_();
    c_[2] = a_[1] * b_[1];
    break;
  case 2:
    c_[2] += ha_() * b_.front() + a_.front() * hb_();
    c_[3] = a_[2] * b_[1] + a_[1] * b_[2];
    break;
  default:
    if ((n_ & (n_ - 1)) == 0) {
      auto &&c0 = ac_.emplace_back(n_);
      auto &&c1 = bc_.emplace_back(n_);
      std::copy_n(a_.cbegin() + (n_ >> 1), n_ >> 1, c0.begin());
      std::copy_n(b_.cbegin() + (n_ >> 1), n_ >> 1, c1.begin());
      dft(c0), dft(c1);
      std::vector c0_cpy(c0);
      for (int i = 0; i != n_; ++i) c0_cpy[i] *= c1[i];
      idft(c0_cpy);
      for (int i = 0; i != n_ - 1; ++i) c_[n_ + i] += c0_cpy[i];
    }
    c_[n_] += ha_() * b_.front() + a_.front() * hb_();
    c_[n_ + 1] += a_[1] * b_.back() + a_.back() * b_[1];
    for (int sft = 1, offset = ntt_len(n_ + 1) >> 1, t = n_ + 1 - offset;
         (t & 1) == 0 && 1 << sft < offset; ++sft, t >>= 1)
      if (1 << sft <= BASE_CASE_SIZE) {
        for (int i = 0, m = n_ + 1 - (1 << sft); i != 1 << sft; ++i)
          for (int j = 0; j != 1 << sft; ++j)
            c_[n_ + 1 + i + j] += a_[m + i] * b_[j + (1 << sft)] + a_[j + (1 << sft)] * b_[m + i];
      } else {
        std::vector<ModIntT> c0(2 << sft), c1(2 << sft);
        std::copy_n(a_.cbegin() + n_ + 1 - (1 << sft), 1 << sft, c0.begin());
        std::copy_n(b_.cbegin() + n_ + 1 - (1 << sft), 1 << sft, c1.begin());
        dft(c0), dft(c1);
        for (int i = 0; i != 2 << sft; ++i)
          c0[i] = c0[i] * bc_[sft - 1][i] + c1[i] * ac_[sft - 1][i];
        idft(c0);
        for (int i = 0; i != (2 << sft) - 1; ++i) c_[n_ + 1 + i] += c0[i];
      }
  }
  return c_[n_++];
}

LIB_END

#endif