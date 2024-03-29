#ifndef FORMAL_POWER_SERIES
#define FORMAL_POWER_SERIES

#include "../common.hpp"
#include "extended_gcd.hpp"
#include "radix2_ntt.hpp"
#include "relaxed_convolution.hpp"

#include <functional>
#include <limits>
#include <memory>
#include <optional>
#include <type_traits>
#include <vector>

LIB_BEGIN

namespace detail {

template <typename ModIntT, typename Closure0T, typename Closure1T>
auto make_shared_relaxed_convolution(Closure0T &&f0, Closure1T &&f1) -> std::shared_ptr<
    relaxed_convolution<ModIntT, std::decay_t<Closure0T>, std::decay_t<Closure1T>>> {
  return std::make_shared<
      relaxed_convolution<ModIntT, std::decay_t<Closure0T>, std::decay_t<Closure1T>>>(f0, f1);
}

} // namespace detail

template <typename ModIntT>
class formal_power_series {
  using F = std::function<ModIntT(int)>;
  F h_; // TODO: Fix a bug that cause a lot of copy of `h_` which is not intend to

  static typename detail::modular_inverse<ModIntT> invs;

public:
  formal_power_series() : h_([](int) { return ModIntT(); }) {}
  explicit formal_power_series(F f)
      : h_([f, cache = std::make_shared<std::vector<ModIntT>>()](int k) {
          for (int i = static_cast<int>(cache->size()); i <= k; ++i) cache->emplace_back(f(i));
          return ModIntT(cache->at(k));
        }) {}
  explicit formal_power_series(const std::vector<ModIntT> &coeff)
      : h_([cache = std::make_shared<std::vector<ModIntT>>(coeff)](int k) {
          return k < static_cast<int>(cache->size()) ? ModIntT(cache->at(k)) : ModIntT();
        }) {}
  /* explicit */ formal_power_series(ModIntT v)
      : h_([v](int k) { return k == 0 ? v : ModIntT(); }) {}
  F handle() const { return h_; }
  ModIntT operator[](int k) const { return h_(k); }
  formal_power_series scale(int k) const {
    return formal_power_series([h = h_, k](int i) { return i % k == 0 ? h(i / k) : ModIntT(); });
  }
  formal_power_series shift(int k) const {
    return formal_power_series([h = h_, k](int i) { return i - k < 0 ? ModIntT() : h(i - k); });
  }
  formal_power_series deriv() const {
    return formal_power_series([h = h_](int i) { return h(i + 1) * (i + 1); });
  }
  formal_power_series integr(ModIntT c = ModIntT()) const {
    return formal_power_series([h = h_, c](int i) { return i == 0 ? c : h(i - 1) * invs(i); });
  }
  formal_power_series inv() const {
    auto rc = detail::make_shared_relaxed_convolution<ModIntT>(
        [h = h_](int i) { return h(i); },
        [h = h_, iv = ModIntT()](int i, const auto &c) mutable {
          return i == 0 ? ModIntT(iv = h(0).inv()) : -(c[i] + h(i) * iv) * iv;
        });
    return formal_power_series([rc](int i) { return rc->next(), rc->get_multiplier()[i]; });
  }
  formal_power_series exp() const {
    auto rc = detail::make_shared_relaxed_convolution<ModIntT>(
        [h = h_](int i) { return h(i + 1) * (i + 1); },
        [](int i, const auto &c) { return i == 0 ? ModIntT(1) : c[i - 1] * invs(i); });
    return formal_power_series(
        [rc](int i) { return i == 0 ? ModIntT(1) : rc->at(i - 1) * invs(i); });
  }
  formal_power_series log() const { return (deriv() / (*this)).integr(); }
  formal_power_series pow(long long k) const {
    if (k == 0) return ModIntT(1);
    return formal_power_series([h = h_, kk = ModIntT(k), k, zero_cnt = 0ull,
                                s = std::optional<F>()](int i) mutable {
      if (s)
        return static_cast<unsigned long long>(i) < zero_cnt ? ModIntT()
                                                             : (*s)(static_cast<int>(i - zero_cnt));
      ModIntT v(h(i));
      if (v.is_zero()) return ++zero_cnt, ModIntT();
      if (zero_cnt != 0 && k > static_cast<long long>(std::numeric_limits<int>::max()))
        return zero_cnt = 0, s.emplace([](int) { return ModIntT(); })(0);
      zero_cnt *= k;
      formal_power_series t0([os = i, iv = v.inv(), h](int i) { return h(i + os) * iv; });
      formal_power_series t1([h0 = t0.log().handle(), kk](int i) { return h0(i) * kk; });
      s.emplace([vk = v.pow(k), h1 = t1.exp().handle()](int i) { return h1(i) * vk; });
      return zero_cnt == 0 ? (*s)(i) : ModIntT();
    });
  }
  template <typename SqrtFuncT,
            typename std::enable_if_t<std::is_invocable_r_v<ModIntT, SqrtFuncT, ModIntT>, int> = 0>
  formal_power_series sqrt(SqrtFuncT &&f) const {
    // `h_(0) == 0` is not allowed.
    auto t = [h = h_, ff = std::decay_t<SqrtFuncT>(std::forward<SqrtFuncT>(f)),
              i2 = ModIntT()](int i, auto const &c) mutable {
      if (i != 0) return (h(i) - c[i]) * i2;
      ModIntT fi(ff(h(i)));
      i2 = (fi + fi).inv();
      return fi;
    };
    return formal_power_series([rc = detail::make_shared_relaxed_convolution<ModIntT>(t, t)](
                                   int i) { return rc->next(), rc->get_multiplier()[i]; });
  }
  formal_power_series operator+(const formal_power_series &rhs) const {
    return formal_power_series([h0 = h_, h1 = rhs.h_](int i) { return h0(i) + h1(i); });
  }
  formal_power_series operator-(const formal_power_series &rhs) const {
    return formal_power_series([h0 = h_, h1 = rhs.h_](int i) { return h0(i) - h1(i); });
  }
  formal_power_series operator-() const {
    return formal_power_series([h = h_](int i) { return -h(i); });
  }
  formal_power_series operator*(const formal_power_series &rhs) const {
    auto rc = detail::make_shared_relaxed_convolution<ModIntT>(
        [h = h_](int i) { return h(i); }, [h = rhs.h_](int i) { return h(i); });
    return formal_power_series([rc](int) { return rc->next(); });
  }
  formal_power_series operator/(const formal_power_series &rhs) const {
    auto rc = detail::make_shared_relaxed_convolution<ModIntT>(
        [h0 = h_, h1 = rhs.h_, iv = ModIntT(), t0 = ModIntT()](int i, const auto &c) mutable {
          if (i == 0) t0 = h0(0) * (iv = h1(0).inv());
          return i == 0 ? t0 : (h0(i) - h1(i) * t0 - c[i]) * iv;
        },
        [h = rhs.h_](int i) { return h(i); });
    return formal_power_series([rc](int i) { return rc->next(), rc->get_multiplicand()[i]; });
  }
  // Pólya operator Q = SEQUENCE(SEQ)
  formal_power_series Q() const {
    // `h_(0) != 0` is not allowed.
    return formal_power_series([h = h_](int i) { return i == 0 ? ModIntT(1) : -h(i); }).inv();
  }
  // Pólya operator Exp = MULTISET(MSET)
  formal_power_series Exp() const {
    // `h_(0) != 0` is not allowed.
    formal_power_series res([h = h_, cache = std::make_shared<std::vector<ModIntT>>()](int i) {
      if (i == 0) return ModIntT();
      if ((i & (i - 1)) == 0) {
        cache->resize(i << 1);
        for (int j = 1; j < i; ++j) {
          ModIntT hj(h(j));
          for (int k = 2; j * k < i << 1; ++k)
            if (j * k >= i) cache->at(j * k) += hj * invs(k);
        }
      }
      return cache->at(i) += h(i);
    });
    return res.exp();
  }
  // Pólya operator Exp(modified) = POWERSET(PSET)
  formal_power_series Exp_m() const {
    // `h_(0) != 0` is not allowed.
    formal_power_series res([h = h_, cache = std::make_shared<std::vector<ModIntT>>()](int i) {
      if (i == 0) return ModIntT();
      if ((i & (i - 1)) == 0) {
        cache->resize(i << 1);
        for (int j = 1; j < i; ++j) {
          ModIntT hj(h(j));
          for (int k = 2; j * k < i << 1; ++k)
            if (j * k >= i) {
              if (k & 1) {
                cache->at(j * k) += hj * invs(k);
              } else {
                cache->at(j * k) -= hj * invs(k);
              }
            }
        }
      }
      return cache->at(i) += h(i);
    });
    return res.exp();
  }
};

template <typename ModIntT>
typename detail::modular_inverse<ModIntT> formal_power_series<ModIntT>::invs;

template <typename ModIntT>
using fps = formal_power_series<ModIntT>;

LIB_END

#endif
