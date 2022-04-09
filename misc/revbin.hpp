#ifndef REVBIN_HEADER_HPP
#define REVBIN_HEADER_HPP

#include <cassert>
#include <utility>

namespace lib {

class RevBinRange {
public:
  RevBinRange(int low, int up, int logB) : low_(low), up_(up), logB_(logB) {
    // [low, up)
    assert(logB > 0 && logB < 32);
    assert(low >= 0);
    assert(low < up);
    assert(up <= 1 << logB);
  }
  RevBinRange(int up, int logB) : RevBinRange(0, up, logB) {}
  ~RevBinRange() = default;

  class iterator {
  public:
    iterator(int val, int logB) : val_(val), rval_(0), logB_(logB) {
      for (int i = 0; i != logB_; ++i)
        if (1 << i & val_) rval_ |= 1 << (logB_ - 1 - i);
    }
    ~iterator()                = default;
    iterator(const iterator &) = default;
    iterator &operator=(const iterator &) = default;
    bool operator==(const iterator &rhs) { return logB_ == rhs.logB_ && val_ == rhs.val_; }
    bool operator!=(const iterator &rhs) { return logB_ != rhs.logB_ || val_ != rhs.val_; }
    iterator &operator++() {
      ++val_;
      for (int k = 1 << (logB_ - 1); (rval_ ^= k) < k; k >>= 1) {}
      return *this;
    }
    iterator operator++(int) {
      iterator old(*this);
      this->operator++();
      return old;
    }
    std::pair<int, int> operator*() { return std::make_pair(val_, rval_); }

  private:
    int val_, rval_;
    const int logB_;
  };

  iterator begin() const { return iterator(low_, logB_); }
  iterator end() const { return iterator(up_, logB_); }

private:
  const int low_, up_, logB_;
};

} // namespace lib

#endif