#ifndef BIGINT_HEADER_HPP
#define BIGINT_HEADER_HPP

/**
 * @brief bigint
 * @docs docs/math/basic/bigint.md
 */

#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>

#include "math/formal_power_series/convolution.hpp"
#include "modint/Montgomery_modint.hpp"

namespace lib {

class BigInt {
private:
  using u32 = std::uint32_t;

public:
  BigInt() : rep_(1, 0), is_neg_(false) {}
  template <typename T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
  BigInt(T v) : rep_(), is_neg_(v < 0) {
    if (v == 0) rep_.push_back(0);
    for (; v != 0; v /= 10) {
      int k = v % 10;
      if (is_neg_) k = -k;
      rep_.push_back(k);
    }
  }
  BigInt(const std::string &s) : rep_(), is_neg_(false) {
    if (s.empty()) {
      rep_ = std::vector<u32>{0};
    } else {
      int idx = 0, n = s.size();
      if (s.front() == '-') {
        is_neg_ = true;
        ++idx;
      } else if (s.front() == '+') {
        ++idx;
      }
      rep_.reserve(n);
      for (int i = n - 1; i != idx - 1; --i) rep_.push_back(s[i] - '0');
      if (static_cast<int>(rep_.size()) == 1 && rep_.front() == 0) is_neg_ = false;
    }
  }
  BigInt(const BigInt &) = default;
  ~BigInt()              = default;

  BigInt &operator=(const BigInt &) = default;
  BigInt operator-() const {
    if (is_zero()) return BigInt();
    BigInt res(*this);
    res.is_neg_ = !res.is_neg_;
    return res;
  }
  BigInt &operator<<=(int s) {
    if (!is_zero()) rep_.insert(rep_.begin(), s, 0);
    return *this;
  }
  BigInt operator<<(int s) const { return BigInt(*this) <<= s; }
  BigInt &operator>>=(int s) {
    if (!is_zero()) {
      if (s >= count_digit()) {
        rep_    = {0};
        is_neg_ = false;
      } else {
        rep_.erase(rep_.begin(), rep_.begin() + s);
      }
    }
    return *this;
  }
  BigInt operator>>(int s) const { return BigInt(*this) >>= s; }
  BigInt &operator+=(const BigInt &rhs) {
    bool lhs_neg = is_negative(), rhs_neg = rhs.is_negative();
    auto abs_big_minus_small = [](std::vector<u32> &big, const std::vector<u32> &small) {
      bool carry = false;
      int idx    = 0;
      for (int e = small.size(); idx != e; ++idx) {
        big[idx] -= static_cast<int>(carry) + small[idx];
        carry = static_cast<int>(big[idx]) < 0;
        if (carry) big[idx] += 10;
      }
      for (; carry; ++idx) {
        if (big[idx] == 0) {
          big[idx] = 9;
        } else {
          --big[idx];
          carry = false;
        }
      }
      assert(!carry);
      while (big.back() == 0 && static_cast<int>(big.size()) > 1) big.pop_back();
    };
    if (!lhs_neg && !rhs_neg) {
      if (rhs.rep_.size() > rep_.size()) rep_.resize(rhs.rep_.size(), 0);
      bool carry = false;
      int idx    = 0;
      for (int e = rhs.rep_.size(); idx != e; ++idx) {
        rep_[idx] += static_cast<int>(carry) + rhs.rep_[idx];
        carry = rep_[idx] >= 10;
        if (carry) rep_[idx] -= 10;
      }
      for (int e = rep_.size(); idx != e; ++idx) {
        rep_[idx] += static_cast<int>(carry);
        carry = rep_[idx] >= 10;
        if (carry) rep_[idx] -= 10;
      }
      if (carry) rep_.push_back(1);
    } else if (lhs_neg && rhs_neg) {
      if (rhs.rep_.size() > rep_.size()) rep_.resize(rhs.rep_.size(), 0);
      bool carry = false;
      int idx    = 0;
      for (int e = rhs.rep_.size(); idx != e; ++idx) {
        rep_[idx] += static_cast<int>(carry) + rhs.rep_[idx];
        carry = rep_[idx] >= 10;
        if (carry) rep_[idx] -= 10;
      }
      for (int e = rep_.size(); idx != e; ++idx) {
        rep_[idx] += static_cast<int>(carry);
        carry = rep_[idx] >= 10;
        if (carry) rep_[idx] -= 10;
      }
      if (carry) rep_.push_back(1);
    } else if (!lhs_neg && rhs_neg) {
      switch (abs_cmp(*this, rhs)) {
      case -1: {
        auto tmp = rhs.rep_;
        abs_big_minus_small(tmp, rep_);
        rep_    = std::move(tmp);
        is_neg_ = true;
        break;
      }
      case 0: rep_ = {0}, is_neg_ = false; break;
      case 1: abs_big_minus_small(rep_, rhs.rep_); break;
      }
      shrink();
    } else {
      switch (abs_cmp(*this, rhs)) {
      case -1: {
        auto tmp = rhs.rep_;
        abs_big_minus_small(tmp, rep_);
        rep_    = std::move(tmp);
        is_neg_ = false;
        break;
      }
      case 0: rep_ = {0}, is_neg_ = false; break;
      case 1: abs_big_minus_small(rep_, rhs.rep_); break;
      }
      shrink();
    }
    return *this;
  }
  BigInt &operator-=(const BigInt &rhs) { return operator+=(-rhs); }
  BigInt &operator*=(const BigInt &rhs) {
    if (is_zero()) return *this;
    if (rhs.is_zero()) {
      rep_ = {0}, is_neg_ = false;
      return *this;
    }
    norm(rep_ = mul(rep_, rhs.rep_));
    is_neg_ = (is_neg_ != rhs.is_neg_);
    return *this;
  }
  BigInt &operator/=(const BigInt &rhs) {
    int m = count_digit(), n = rhs.count_digit();
    BigInt rhs_p(rhs);
    int offset;
    if (m <= n << 1) {
      offset = n << 1;
    } else {
      offset = m + n;
      rhs_p <<= m - n;
    }
    auto res       = (*this) * compute_accurate(rhs_p) >> offset;
    return operator=((*this) - res * rhs < rhs ? res : res + 1);
  }
  BigInt &operator%=(const BigInt &rhs) { return operator=((*this) - (*this) / rhs * rhs); }
  BigInt abs() const {
    BigInt res(*this);
    res.is_neg_ = false;
    return res;
  }

  friend BigInt operator+(const BigInt &lhs, const BigInt &rhs) { return BigInt(lhs) += rhs; }
  friend BigInt operator-(const BigInt &lhs, const BigInt &rhs) { return BigInt(lhs) -= rhs; }
  friend BigInt operator*(const BigInt &lhs, const BigInt &rhs) { return BigInt(lhs) *= rhs; }
  friend BigInt operator/(const BigInt &lhs, const BigInt &rhs) { return BigInt(lhs) /= rhs; }
  friend BigInt operator%(const BigInt &lhs, const BigInt &rhs) { return BigInt(lhs) %= rhs; }

  friend int abs_cmp(const BigInt &lhs, const BigInt &rhs) {
    // lhs < rhs => -1, lhs == rhs => 0, lhs > rhs => 1
    if (lhs.rep_.size() > rhs.rep_.size()) return 1;
    if (lhs.rep_.size() < rhs.rep_.size()) return -1;
    for (int i = static_cast<int>(lhs.rep_.size()) - 1; i >= 0; --i) {
      if (lhs.rep_[i] > rhs.rep_[i]) return 1;
      if (lhs.rep_[i] < rhs.rep_[i]) return -1;
    }
    return 0;
  }
  friend bool operator==(const BigInt &lhs, const BigInt &rhs) {
    return lhs.is_negative() == rhs.is_negative() && lhs.rep_ == rhs.rep_;
  }
  friend bool operator!=(const BigInt &lhs, const BigInt &rhs) { return !(lhs == rhs); }
  friend bool operator<(const BigInt &lhs, const BigInt &rhs) {
    if (lhs.is_negative()) {
      if (!rhs.is_negative()) return true;
      return abs_cmp(lhs, rhs) == 1;
    } else {
      if (rhs.is_negative()) return false;
      return abs_cmp(lhs, rhs) == -1;
    }
  }
  friend bool operator>(const BigInt &lhs, const BigInt &rhs) {
    if (lhs.is_negative()) {
      if (!rhs.is_negative()) return false;
      return abs_cmp(lhs, rhs) == -1;
    } else {
      if (rhs.is_negative()) return true;
      return abs_cmp(lhs, rhs) == 1;
    }
  }
  friend bool operator<=(const BigInt &lhs, const BigInt &rhs) {
    if (lhs.is_negative()) {
      if (!rhs.is_negative()) return true;
      return abs_cmp(lhs, rhs) >= 0;
    } else {
      if (rhs.is_negative()) return false;
      return abs_cmp(lhs, rhs) <= 0;
    }
  }
  friend bool operator>=(const BigInt &lhs, const BigInt &rhs) {
    if (lhs.is_negative()) {
      if (!rhs.is_negative()) return false;
      return abs_cmp(lhs, rhs) <= 0;
    } else {
      if (rhs.is_negative()) return true;
      return abs_cmp(lhs, rhs) >= 0;
    }
  }

  bool is_zero() const {
    return !is_neg_ && static_cast<int>(rep_.size()) == 1 && rep_.front() == 0;
  }
  bool is_negative() const { return is_neg_; }
  int count_digit() const { return static_cast<int>(rep_.size()); }
  u32 at_digit(int d) const { return d < static_cast<int>(rep_.size()) ? rep_[d] : 0; }
  void set_digit(int d, int v) {
    if (v != 0 && d < static_cast<int>(rep_.size())) rep_.resize(d + 1, 0);
    if ((rep_[d] = v) == 0) shrink();
  }
  u32 operator[](int d) const { return at_digit(d); }

  std::string to_string() const {
    std::string res;
    if (is_neg_) res += '-';
    for (int i = static_cast<int>(rep_.size()) - 1; i >= 0; --i)
      res += static_cast<char>(rep_[i] + '0');
    return res;
  }

  friend std::istream &operator>>(std::istream &is, BigInt &rhs) {
    std::string x;
    is >> x;
    rhs = BigInt(x);
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const BigInt &rhs) {
    return os << rhs.to_string();
  }

private:
  std::vector<u32> rep_;
  bool is_neg_;
  void shrink() {
    while (rep_.back() == 0 && static_cast<int>(rep_.size()) > 1) rep_.pop_back();
    if (static_cast<int>(rep_.size()) == 1 && rep_.back() == 0) is_neg_ = false;
  }
  static BigInt compute_accurate(const BigInt &a) {
    std::vector<BigInt> t(7);
    t[0] = a;
    for (int i = 1; i != 7; ++i) t[i] = t[i - 1] + t[i - 1];
    auto res  = compute(a);
    int n     = a.count_digit();
    auto diff = (BigInt(1) << n * 2) - a * res;
    for (int i = 6; i >= 0; --i)
      if (diff >= t[i]) {
        diff -= t[i];
        res += 1 << i;
      }
    return res;
  }
  static BigInt compute(const BigInt &a) {
    int n = a.count_digit();
    if (n == 1) return BigInt(100 / a.at_digit(0));
    if (n == 2) return BigInt(10000 / (a.at_digit(0) + a.at_digit(1) * 10));
    int n_p = (n >> 1) + 1;
    auto q  = compute(a >> (n - n_p)) << (n - n_p);
    return q * ((BigInt(2) << n * 2) - q * a) >> n * 2; // 可展开 DFT 来优化
  }
  static void norm(std::vector<u32> &v) {
    u32 carry = 0;
    for (int i = 0, ie = v.size(); i != ie; ++i) {
      v[i] = (carry += v[i]) % 10;
      carry /= 10;
    }
    while (carry != 0) {
      u32 c = carry / 10;
      v.push_back(carry - c * 10);
      carry = c;
    }
  }
  static std::vector<u32> mul(const std::vector<u32> &lhs, const std::vector<u32> &rhs) {
    using mint = MontModInt<998244353>;
    if (&lhs == &rhs) {
      std::vector<mint> lhs_cpy;
      lhs_cpy.reserve(lhs.size());
      for (auto i : lhs) lhs_cpy.emplace_back(i);
      auto res_m = convolve(lhs_cpy, lhs_cpy);
      std::vector<u32> res;
      res.reserve(res_m.size());
      for (auto i : res_m) res.push_back(static_cast<u32>(i));
      return res;
    }
    std::vector<mint> lhs_cpy, rhs_cpy;
    lhs_cpy.reserve(lhs.size());
    for (auto i : lhs) lhs_cpy.emplace_back(i);
    rhs_cpy.reserve(rhs.size());
    for (auto i : rhs) rhs_cpy.emplace_back(i);
    auto res_m = convolve(lhs_cpy, rhs_cpy);
    std::vector<u32> res;
    res.reserve(res_m.size());
    for (auto i : res_m) res.push_back(static_cast<u32>(i));
    return res;
  }
};

} // namespace lib

#endif