#ifndef DEBRUIJN_HEADER_HPP
#define DEBRUIJN_HEADER_HPP

/**
 * @brief de Bruijn sequence / de Bruijn 序列
 *
 */

#include <cstdint>

namespace lib {

int deBruijn_log2(std::uint64_t n) {
  static constexpr std::uint64_t deBruijn = 0x022fdd63cc95386d;
  static constexpr int convert[64]        = {
      0,  1,  2,  53, 3,  7,  54, 27, 4,  38, 41, 8,  34, 55, 48, 28, 62, 5,  39, 46, 44, 42,
      22, 9,  24, 35, 59, 56, 49, 18, 29, 11, 63, 52, 6,  26, 37, 40, 33, 47, 61, 45, 43, 21,
      23, 58, 17, 10, 51, 25, 36, 32, 60, 20, 57, 16, 50, 31, 19, 15, 30, 14, 13, 12};
  return convert[n * deBruijn >> 58];
}

int deBruijn_log2(std::uint32_t n) {
  static constexpr std::uint32_t deBruijn = 0x4653adf;
  static constexpr int convert[32]        = {0,  1,  2,  6,  3,  11, 7,  16, 4,  14, 12,
                                      21, 8,  23, 17, 26, 31, 5,  10, 15, 13, 20,
                                      22, 25, 30, 9,  19, 24, 29, 18, 28, 27};
  return convert[n * deBruijn >> 27];
}

} // namespace lib

#endif
