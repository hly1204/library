#ifndef BINOMIAL_CONVOLUTION_HPP
#define BINOMIAL_CONVOLUTION_HPP

#include "../common.hpp"
#include "../modint/long_montgomery_modint.hpp"
#include "convolution.hpp"
#include "extended_gcd.hpp"

#include <type_traits>
#include <vector>

LIB_BEGIN

// helper class for binomial convolution
class binomial_convolution {
  using i32 = std::int32_t;
  using u32 = std::uint32_t;
  using i64 = std::int64_t;
  using u64 = std::uint64_t;

  using mint0 = mm63<0x3F9A000000000001>;
  using mint1 = mm63<0x3FC6000000000001>;

  struct factor_info {
    const u32 p_, e_, pe_; // `p_`^`e_` = `pe_`, `p_` prime
    mutable std::vector<mint0> pp0_, ipp0_;
    mutable std::vector<mint1> pp1_, ipp1_;
    mutable std::vector<u32> nu_{0}, fact_{1}, ifact_{1}; // `fact_[i]` = `i`! / `p_`^(`nu_[i]`)
    factor_info(u32 p, u32 e, u32 pe)
        : p_(p), e_(e), pe_(pe), pp0_{mint0(1), mint0(p)}, ipp0_{mint0(1), mint0(p).inv()},
          pp1_{mint1(1), mint1(p)}, ipp1_{mint1(1), mint1(p).inv()} {}
    void preprocess(int n) const {
      int os = static_cast<int>(nu_.size());
      if (os >= n) return;
      nu_.resize(n);
      fact_.resize(n);
      ifact_.resize(n);
      for (int i = os; i != n; ++i) {
        auto j = static_cast<u32>(i);
        auto v = nu_[i - 1];
        for (; j % p_ == 0; j /= p_) ++v;
        nu_[i]    = v;
        fact_[i]  = static_cast<u64>(fact_[i - 1]) * j % pe_;
        ifact_[i] = static_cast<u64>(fact_[i]) * ifact_[i - 1] % pe_;
      }
      {
        auto iv = [](u32 a, u32 b) -> u64 {
          auto v = inv_gcd(a, b).first /* % b */;
          return v < 0 ? v + b : v;
        }(ifact_.back(), pe_);
        for (int i = n - 1; i >= os; --i)
          ifact_[i] = ifact_[i - 1] * iv % pe_, iv = iv * fact_[i] % pe_;
      }
      if (int maxnu = static_cast<int>(nu_.back()), pos = static_cast<int>(pp0_.size());
          pos <= maxnu) {
        pp0_.resize(maxnu + 1);
        ipp0_.resize(maxnu + 1);
        pp1_.resize(maxnu + 1);
        ipp1_.resize(maxnu + 1);
        mint0 p0(pp0_[1]), ip0(ipp0_[1]);
        mint1 p1(pp1_[1]), ip1(ipp1_[1]);
        for (int i = pos; i <= maxnu; ++i) {
          pp0_[i]  = pp0_[i - 1] * p0;
          ipp0_[i] = ipp0_[i - 1] * ip0;
          pp1_[i]  = pp1_[i - 1] * p1;
          ipp1_[i] = ipp1_[i - 1] * ip1;
        }
      }
    }
  };

  std::vector<u32> convolution(const std::vector<u32> &a, const std::vector<u32> &b,
                               const factor_info &info) const;

  const u32 modular_;
  std::vector<factor_info> info_;

public:
  explicit binomial_convolution(u32 modular) : modular_(modular) {
    for (u32 i = 2; static_cast<u64>(i) * i <= modular; ++i)
      if (modular % i == 0) {
        int e        = 0;
        const u32 mm = modular;
        do { modular /= i, ++e; } while (modular % i == 0);
        info_.emplace_back(i, e, mm / modular);
      }
    if (modular != 1) info_.emplace_back(modular, 1, modular);
  }
  u32 mod() const { return modular_; }
  template <typename IntT>
  std::enable_if_t<std::is_integral_v<IntT>, std::vector<IntT>>
  operator()(const std::vector<IntT> &a, const std::vector<IntT> &b) const;
};

std::vector<typename binomial_convolution::u32>
binomial_convolution::convolution(const std::vector<u32> &a, const std::vector<u32> &b,
                                  const factor_info &info) const {
  const int n = static_cast<int>(a.size()), m = static_cast<int>(b.size()), len = n + m - 1;
  info.preprocess(len);
  std::vector<mint0> a0(len), b0(len);
  std::vector<mint1> a1(len), b1(len);
  const auto pe = info.pe_;
  for (int i = 0; i != n; ++i) {
    u64 a_hat = static_cast<u64>(a[i]) * info.ifact_[i] % pe;
    auto j    = info.nu_[i];
    a0[i] = a_hat * info.ipp0_[j], a1[i] = a_hat * info.ipp1_[j];
  }
  for (int i = 0; i != m; ++i) {
    u64 b_hat = static_cast<u64>(b[i]) * info.ifact_[i] % pe;
    auto j    = info.nu_[i];
    b0[i] = b_hat * info.ipp0_[j], b1[i] = b_hat * info.ipp1_[j];
  }
  tft(a0), tft(b0), tft(a1), tft(b1);
  for (int i = 0; i != len; ++i) a0[i] *= b0[i], a1[i] *= b1[i];
  itft(a0), itft(a1);
  // Chinese remainder algorithm
  auto cra = [pe, ip1 = mint0(mint1::mod()).inv(), p1_mod_pe = mint1::mod() % pe](mint0 a,
                                                                                  mint1 b) -> u64 {
    auto bv = b.val();
    return (static_cast<u64>((a - bv) * ip1) % pe * p1_mod_pe + bv) % pe;
  };
  std::vector<u32> res(len);
  for (int i = 0; i != len; ++i) {
    int j  = info.nu_[i];
    res[i] = cra(a0[i] * info.pp0_[j], a1[i] * info.pp1_[j]) * info.fact_[i] % pe;
  }
  return res;
}

template <typename IntT>
std::enable_if_t<std::is_integral_v<IntT>, std::vector<IntT>>
binomial_convolution::operator()(const std::vector<IntT> &a, const std::vector<IntT> &b) const {
  const int n = static_cast<int>(a.size()), m = static_cast<int>(b.size()), len = n + m - 1;
  std::vector<u32> a_cpy(n), b_cpy(m);
  for (int i = 0; i != n; ++i) a_cpy[i] = static_cast<u32>(a[i]);
  for (int i = 0; i != m; ++i) b_cpy[i] = static_cast<u32>(b[i]);
  u32 modular = 1;
  std::vector<u32> res(len);
  {
    auto cra = [len](std::vector<u32> &a, u32 &m, const std::vector<u32> &b, u32 m0) {
      auto im_mod_m0 = [](u32 a, u32 b) -> i64 {
        auto v = inv_gcd(a, b).first /* % b */;
        return v < 0 ? v + b : v;
      }(m, m0);
      for (int i = 0; i != len; ++i) {
        auto v = static_cast<i32>((static_cast<i64>(b[i]) - a[i]) * im_mod_m0 % m0);
        a[i] += (v < 0 ? v + m0 : v) * m;
      }
      m *= m0;
    };
    for (auto &&i : info_) cra(res, modular, convolution(a_cpy, b_cpy, i), i.pe_);
  }
  return std::vector<IntT>(res.cbegin(), res.cend());
}

using bin_conv = binomial_convolution;

LIB_END

#endif