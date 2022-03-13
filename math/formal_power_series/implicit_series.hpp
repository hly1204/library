#ifndef IMPLICIT_SERIES_HEADER_HPP
#define IMPLICIT_SERIES_HEADER_HPP

#include <functional>
#include <memory>
#include <optional>
#include <utility>

#include "prime_binomial.hpp"
#include "relaxed_convolution.hpp"

namespace lib {

template <typename mod_t>
class ImplicitSeries {
public:
  using handle_type = std::function<mod_t(int)>;

  ImplicitSeries() : handle_([](int) { return mod_t(0); }) {}
  ImplicitSeries(handle_type fn)
      : handle_([f = fn, cache = std::make_shared<std::vector<mod_t>>()](int k) {
          for (int i = static_cast<int>(cache->size()); i <= k; ++i) cache->emplace_back(f(i));
          return cache->at(k);
        }) {}
  ImplicitSeries(const std::vector<mod_t> &coeff)
      : handle_([cache = std::make_shared<std::vector<mod_t>>(coeff)](int k) {
          return k < static_cast<int>(cache->size()) ? cache->at(k) : mod_t(0);
        }) {}
  ImplicitSeries(const mod_t &v) : handle_([vv = v](int k) { return k == 0 ? vv : mod_t(0); }) {}
  ~ImplicitSeries()                      = default;
  ImplicitSeries(const ImplicitSeries &) = default;
  ImplicitSeries &operator=(const ImplicitSeries &) = default;
  mod_t operator[](int k) const { return handle_(k); }
  ImplicitSeries &await(int k) const { return handle_(k - 1), *this; }
  std::vector<mod_t> take(int k) const {
    std::vector<mod_t> res;
    res.reserve(k);
    for (int i = 0; i != k; ++i) res.emplace_back(handle_(i));
    return res;
  }
  handle_type get_handle() const { return handle_; }
  ImplicitSeries scale(int k) const {
    return ImplicitSeries(
        [handle = handle_, k](int i) { return i % k == 0 ? handle(i / k) : mod_t(0); });
  }
  ImplicitSeries shift(int k) const {
    return ImplicitSeries(
        [handle = handle_, k](int i) { return i - k < 0 ? mod_t(0) : handle(i - k); });
  }
  ImplicitSeries deriv() const {
    return ImplicitSeries([handle = handle_](int i) { return handle(i + 1) * (i + 1); });
  }
  ImplicitSeries integr(mod_t c = mod_t(0)) const {
    return ImplicitSeries(
        [handle = handle_, cc = c](int i) { return i == 0 ? cc : handle(i - 1) / i; });
  }
  ImplicitSeries inv() const {
    return ImplicitSeries(
        [rc = std::make_shared<RelaxedConvolution<mod_t>>(
             [handle = handle_](int i, const auto &) { return handle(i); },
             [handle = handle_, iv = std::optional<mod_t>()](int i, const auto &c) mutable {
               if (!iv) iv.emplace(handle(0).inv());
               return i == 0 ? *iv : -(c[i] + handle(i) * *iv) * *iv;
             })](int i) { return rc->await(i + 1).get_multiplier()[i]; });
  }
  ImplicitSeries exp() const {
    return ImplicitSeries(
        [rc = std::make_shared<RelaxedConvolution<mod_t>>(
             [handle = handle_](int i, const auto &) { return handle(i + 1) * (i + 1); },
             [](int i, const auto &c) { return i == 0 ? mod_t(1U) : c[i - 1] / i; })](int i) {
          return i == 0 ? mod_t(1U) : rc->at(i - 1) / i;
        });
  }
  ImplicitSeries log() const { return (deriv() / (*this)).integr(); }
  ImplicitSeries pow(unsigned long long k) const {
    // clang-format off
    return ImplicitSeries([handle = handle_, kk = mod_t(k), k, zero_cnt = 0ULL,
                           s = std::optional<std::function<mod_t(int)>>()](int i) mutable {
      if (!s) {
        auto v = handle(i);
        if (v == 0) return ++zero_cnt, mod_t(0);
        zero_cnt *= k;
        s.emplace(
            [vk = v.pow(k),
             h1 = ImplicitSeries([h0 = ImplicitSeries([offset = i, iv = v.inv(), handle](int i) {
                                         return handle(i + offset) * iv;
                                       }).log().get_handle(), kk](int i) { return h0(i) * kk; })
                                       .exp().get_handle()](int i) { return h1(i) * vk; });
        return zero_cnt == 0 ? (*s)(i) : mod_t(0);
      }
      return i < zero_cnt ? mod_t(0) : (*s)(i - zero_cnt);
    });
    // clang-format on
  }
  ImplicitSeries sqrt(std::function<mod_t(mod_t)> f) const {
    auto t = [handle = handle_, f, i2 = std::optional<mod_t>()](int i, const auto &c) mutable {
      auto v = handle(i);
      if (i != 0) return (handle(i) - c[i]) * *i2;
      auto fv = f(v);
      i2.emplace(mod_t(f(v) * 2).inv());
      return fv;
    };
    return ImplicitSeries([rc = std::make_shared<RelaxedConvolution<mod_t>>(t, t)](int i) {
      return rc->await(i + 1).get_multiplier()[i];
    });
  }
  ImplicitSeries operator+(const ImplicitSeries &rhs) const {
    return ImplicitSeries([lhs_handle = handle_, rhs_handle = rhs.handle_](int i) {
      return lhs_handle(i) + rhs_handle(i);
    });
  }
  ImplicitSeries operator-(const ImplicitSeries &rhs) const {
    return ImplicitSeries([lhs_handle = handle_, rhs_handle = rhs.handle_](int i) {
      return lhs_handle(i) - rhs_handle(i);
    });
  }
  ImplicitSeries operator-() const {
    return ImplicitSeries([handle = handle_](int i) { return -handle(i); });
  }
  ImplicitSeries operator*(const ImplicitSeries &rhs) const {
    return ImplicitSeries([rc = std::make_shared<RelaxedConvolution<mod_t>>(
                               [handle = handle_](int i, const auto &) { return handle(i); },
                               [handle = rhs.handle_](int i, const auto &) { return handle(i); })](
                              int i) { return rc->at(i); });
  }
  ImplicitSeries operator/(const ImplicitSeries &rhs) const {
    return ImplicitSeries(
        [rc = std::make_shared<RelaxedConvolution<mod_t>>(
             [handle0 = handle_, handle1 = rhs.handle_, iv = std::optional<mod_t>(),
              t0 = std::optional<mod_t>()](int i, const auto &c) mutable {
               if (!iv) t0.emplace(handle0(0) * iv.emplace(handle1(0).inv()));
               return (i == 0 ? handle0(0) : handle0(i) - handle1(i) * *t0 - c[i]) * *iv;
             },
             [handle = rhs.handle_](int i, const auto &) { return handle(i); })](int i) {
          return rc->await(i + 1).get_multiplicand()[i];
        });
  }

  ImplicitSeries Q() const { // Pólya 算子，对应集合的 Sequence 构造
    return ImplicitSeries([handle = handle_](int i) { return i == 0 ? mod_t(1) : -handle(i); })
        .inv();
  }
  ImplicitSeries Exp() const { // Pólya 算子，对应集合的 Multiset 构造
    return ImplicitSeries(
               [handle = handle_, cache = std::make_shared<std::vector<mod_t>>()](int i) {
                 if (i == 0) return mod_t(0);
                 if ((i & (i - 1)) == 0) {
                   PrimeBinomial<mod_t> bi(i << 1);
                   cache->resize(i << 1, mod_t(0));
                   for (int j = 1; j < i; ++j) {
                     mod_t hj = handle(j);
                     for (int k = 2; j * k < i << 1; ++k)
                       if (j * k >= i) cache->at(j * k) += hj * bi.inv_unsafe(k);
                   }
                 }
                 return cache->at(i) += handle(i);
               })
        .exp();
  }
  ImplicitSeries Exp_m() const { // Pólya 算子，对应集合的 Powerset 构造
    return ImplicitSeries(
               [handle = handle_, cache = std::make_shared<std::vector<mod_t>>()](int i) {
                 if (i == 0) return mod_t(0);
                 if ((i & (i - 1)) == 0) {
                   PrimeBinomial<mod_t> bi(i << 1);
                   cache->resize(i << 1, mod_t(0));
                   for (int j = 1; j < i; ++j) {
                     mod_t hj = handle(j);
                     for (int k = 2; j * k < i << 1; ++k)
                       if (j * k >= i) {
                         if (k & 1) {
                           cache->at(j * k) += hj * bi.inv_unsafe(k);
                         } else {
                           cache->at(j * k) -= hj * bi.inv_unsafe(k);
                         }
                       }
                   }
                 }
                 return cache->at(i) += handle(i);
               })
        .exp();
  }

  friend ImplicitSeries operator*(mod_t c, const ImplicitSeries &rhs) {
    return ImplicitSeries([handle = rhs.get_handle(), c](int i) { return handle(i) * c; });
  }
  friend ImplicitSeries operator*(const ImplicitSeries &lhs, mod_t c) {
    return ImplicitSeries([handle = lhs.get_handle(), c](int i) { return handle(i) * c; });
  }
  friend ImplicitSeries operator/(const ImplicitSeries &lhs, mod_t c) {
    return ImplicitSeries(
        [handle = lhs.get_handle(), ic = c.inv()](int i) { return handle(i) * ic; });
  }

private:
  handle_type setHandle(handle_type handle) {
    handle_type old_handle(handle_);
    handle_ = handle;
    return old_handle;
  }

  handle_type handle_;
};

} // namespace lib

#endif