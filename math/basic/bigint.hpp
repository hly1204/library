#ifndef BIGINT_HEADER_HPP
#define BIGINT_HEADER_HPP

/**
 * @brief bigint
 *
 */

#include <cstdint>
#include <string>
#include <vector>

namespace lib {

enum class Radix : std::uint32_t { Binary = 2, Decimal = 10, Hexadecimal = 16 };

template <Radix radix>
class BigInt;

template <>
class BigInt<Radix::Decimal> {
private:
  using u32 = std::uint32_t;

public:
  BigInt() : rep_(1, 0), is_minus_(false) {}
  BigInt(const std::string &s) : rep_(), is_minus_(false) {
    if (s.empty()) {
      rep_ = std::vector<u32>{0};
    } else {
      int idx = 0, n = s.size();
      if (s.front() == '-') {
        is_minus_ = true;
        ++idx;
      } else if (s.front() == '+') {
        ++idx;
      }
      rep_.reserve(n);
      for (int i = n - 1; i != idx - 1; --i) rep_.push_back(s[i] - '0');
      if (static_cast<int>(rep_.size()) == 1 && rep_.front() == 0) is_minus_ = false;
    }
  }
  ~BigInt() = default;

  BigInt &operator=(const BigInt &) = default;
  BigInt operator-() const {
    if (is_zero()) return BigInt();
    BigInt res(*this);
    res.is_minus_ = !res.is_minus_;
    return res;
  }
  BigInt &operator+=(const BigInt &rhs) {}
  BigInt &operator-=(const BigInt &rhs) {}
  BigInt &operator*=(const BigInt &rhs) {}
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
    return !is_minus_ && static_cast<int>(rep_.size()) == 1 && rep_.front() == 0;
  }
  bool is_minus() const { return is_minus_; }

  std::string to_string() const {}

private:
  std::vector<u32> rep_;
  bool is_minus_;
  void shrink() {
    while (rep_.back() == 0 && static_cast<int>(rep_.size()) > 1) rep_.pop_back();
  }
};

} // namespace lib

#endif