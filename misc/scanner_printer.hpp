#ifndef SCANNER_PRINTER_HEADER_HPP
#define SCANNER_PRINTER_HEADER_HPP

/**
 * @brief scanner and printer
 *
 */

#include <cctype>
#include <cstdio>
#include <type_traits>

namespace lib {

class Scanner {
public:
  /**
   * @brief 构造函数
   * @note 必须保证 buffer_size 足够容纳所有内容
   * @param f
   * @param enough_buffer_size
   */
  Scanner(std::FILE *f = stdin, std::size_t enough_buffer_size = 1 << 25)
      : f_(f), buffer_(new char[enough_buffer_size + 32]), buffer_head_(buffer_),
        buffer_tail_(buffer_ + std::fread(buffer_, sizeof(char), enough_buffer_size + 32, f_)) {}
  ~Scanner() { delete[] buffer_; }

  template <typename T>
  std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T, char> && std::is_signed_v<T>, bool>
  scan(T &x) {
    x = static_cast<T>(0);
    while (buffer_tail_ != buffer_head_ && *buffer_head_ != '-' && !std::isdigit(*buffer_head_))
      ++buffer_head_;
    bool is_minus         = *buffer_head_ == '-' && ++buffer_head_;
    char *old_buffer_head = buffer_head_;
    if (is_minus)
      while (buffer_tail_ != buffer_head_ && std::isdigit(*buffer_head_))
        x = x * static_cast<T>(10) - (*buffer_head_++ - '0');
    else
      while (buffer_tail_ != buffer_head_ && std::isdigit(*buffer_head_))
        x = x * static_cast<T>(10) + (*buffer_head_++ - '0');
    return buffer_head_ != old_buffer_head;
  }

  template <typename T>
  std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T, char> && std::is_unsigned_v<T>, bool>
  scan(T &x) {
    x = static_cast<T>(0);
    while (buffer_tail_ != buffer_head_ && *buffer_head_ != '-' && !std::isdigit(*buffer_head_))
      ++buffer_head_;
    char *old_buffer_head = buffer_head_;
    while (buffer_tail_ != buffer_head_ && std::isdigit(*buffer_head_))
      x = x * static_cast<T>(10) + (*buffer_head_++ - '0');
    return buffer_head_ != old_buffer_head;
  }

  template <typename T, typename... Rest>
  bool scan(T &x, Rest &...y) {
    return scan(x) && scan(y...);
  }

private:
  std::FILE *f_;
  char *buffer_, *buffer_head_, *buffer_tail_;
};

class Printer {
public:
  Printer(std::FILE *f = stdout, std::size_t buffer_size = 100000)
      : f_(f), buffer_(new char[buffer_size + 32]), buffer_head_(buffer_),
        buffer_end_(buffer_ + buffer_size + 32), stk_(new char[32]), top_(stk_) {}
  ~Printer() {
    flush();
    delete[] stk_;
    delete[] buffer_;
  }

  void flush() {
    std::fwrite(buffer_, buffer_head_ - buffer_, sizeof(char), f_);
    buffer_head_ = buffer_;
  }

  void putchar(char x) {
    if (buffer_end_ == buffer_head_) flush();
    *buffer_head_++ = x;
  }

  template <typename T>
  std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T, char> && std::is_signed_v<T>, void>
  print(T x) {
    if (x == static_cast<T>(0)) return putchar('0');
    if (x < 0) {
      putchar('-');
      while (x != static_cast<T>(0)) {
        T y     = x / static_cast<T>(10);
        *top_++ = y * static_cast<T>(10) - x + '0';
        x       = y;
      }
    } else {
      while (x != static_cast<T>(0)) {
        T y     = x / static_cast<T>(10);
        *top_++ = x - y * static_cast<T>(10) + '0';
        x       = y;
      }
    }
    if (buffer_end_ - buffer_head_ < top_ - stk_) flush();
    while (top_ != stk_) *buffer_head_++ = *--top_;
  }

  void print(char x) { return this->putchar(x); }

  template <typename T>
  std::enable_if_t<std::is_integral_v<T> && !std::is_same_v<T, char> && std::is_unsigned_v<T>, void>
  print(T x) {
    while (x != static_cast<T>(0)) {
      T y     = x / static_cast<T>(10);
      *top_++ = x - y * static_cast<T>(10) + '0';
      x       = y;
    }
    if (buffer_end_ - buffer_head_ < top_ - stk_) flush();
    while (top_ != stk_) *buffer_head_++ = *--top_;
  }

  template <typename T, typename... Rest>
  void print(T x, Rest... y) {
    return print(x), print(y...);
  }

private:
  std::FILE *f_;
  char *buffer_, *buffer_head_, *buffer_end_, *stk_, *top_;
};

} // namespace lib

#endif