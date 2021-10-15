#ifndef BIGINT_HEADER_HPP
#define BIGINT_HEADER_HPP

/**
 * @brief bigint
 *
 */

#include <cassert>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

namespace lib {

enum class Radix : std::uint32_t { Binary = 2, Decimal = 10, Hexadecimal = 16 };

template <Radix radix = Radix::Decimal>
class BigInt;

template <>
class BigInt<Radix::Decimal> {
private:
  using u32 = std::uint32_t;

public:
  BigInt() : rep_(1, 0), is_neg_(false) {}
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
  // BigInt &operator*=(const BigInt &rhs) {}
  // BigInt &operator/=(const BigInt &rhs);
  BigInt abs() const {
    BigInt res(*this);
    res.is_neg_ = false;
    return res;
  }

  friend BigInt operator+(const BigInt &lhs, const BigInt &rhs) { return BigInt(lhs) += rhs; }
  friend BigInt operator-(const BigInt &lhs, const BigInt &rhs) { return BigInt(lhs) -= rhs; }
  // friend BigInt operator*(const BigInt &lhs, const BigInt &rhs) { return BigInt(lhs) *= rhs; }
  // friend BigInt operator/(const BigInt &lhs, const BigInt &rhs) { return BigInt(lhs) /= rhs; }

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
  u32 at_digit(int d) const { return rep_[d]; }

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
  }
};

} // namespace lib

#endif