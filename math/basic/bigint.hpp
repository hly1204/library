#ifndef BIGINT_HEADER_HPP
#define BIGINT_HEADER_HPP

/**
 * @brief bigint
 *
 */

#include <cstdint>
#include <string>
#include <vector>
#include <iostream>

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
    
  }
  BigInt &operator-=(const BigInt &rhs) {}
  BigInt &operator*=(const BigInt &rhs) {

  }
  BigInt &operator/=(const BigInt &rhs);

  friend BigInt operator+(const BigInt &lhs, const BigInt &rhs) { return BigInt(lhs) += rhs; }
  friend BigInt operator-(const BigInt &lhs, const BigInt &rhs) { return BigInt(lhs) -= rhs; }
  friend BigInt operator*(const BigInt &lhs, const BigInt &rhs) { return BigInt(lhs) *= rhs; }
  // friend BigInt operator/(const BigInt &lhs, const BigInt &rhs) { return BigInt(lhs) /= rhs; }

  friend BigInt operator==(const BigInt &lhs, const BigInt &rhs) {}
  friend BigInt operator!=(const BigInt &lhs, const BigInt &rhs) {}
  friend BigInt operator<(const BigInt &lhs, const BigInt &rhs) {}
  friend BigInt operator>(const BigInt &lhs, const BigInt &rhs) {}
  friend BigInt operator<=(const BigInt &lhs, const BigInt &rhs) {}
  friend BigInt operator>=(const BigInt &lhs, const BigInt &rhs) {}

  bool is_zero() const {
    return !is_neg_ && static_cast<int>(rep_.size()) == 1 && rep_.front() == 0;
  }
  bool is_negative() const { return is_neg_; }

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
  friend std::ostream &operator<<(std::ostream &os, const BigInt &rhs) { return os << rhs.to_string(); }

private:
  std::vector<u32> rep_;
  bool is_neg_;
  void shrink() {
    while (rep_.back() == 0 && static_cast<int>(rep_.size()) > 1) rep_.pop_back();
  }
};

} // namespace lib

#endif