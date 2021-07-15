#ifndef BIT_OPERATION_HEADER_HPP
#define BIT_OPERATION_HEADER_HPP

/**
 * @brief bit operations / 位运算
 *
 */

#include <cassert>
#include <cstdint>

#include "deBruijn_sequence.hpp"

namespace lib {

/**
 * @brief 在二进制最高的 1 后面填充满 1
 * @param x
 * @return std::uint32_t
 */
std::uint32_t fill_one_after_msb(std::uint32_t x) {
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  return x | x >> 16;
}

std::uint64_t fill_one_after_msb(std::uint64_t x) {
  x |= x >> 1;
  x |= x >> 2;
  x |= x >> 4;
  x |= x >> 8;
  x |= x >> 16;
  return x | x >> 32;
}

/**
 * @brief 计算 x 的二进制表示中 least significant 1-bit 的索引加一
 * @param x
 * @return int 若 x=0 则返回 0 。
 */
int ffs(std::uint32_t x) { return x == 0 ? 0 : deBruijn_log2(x & ~(x - 1)) + 1; }

int ffs(std::uint64_t x) { return x == 0 ? 0 : deBruijn_log2(x & ~(x - 1)) + 1; }

/**
 * @brief 计算 x 的二进制表示中从 most significant bit 位置开始有多少个 0
 * @param x
 * @return int 若 x=0 则未定义。
 *
 */
int clz(std::uint32_t x) {
  assert(x != 0);
  return 31 - deBruijn_log2(fill_one_after_msb(x >> 1) + 1);
}

int clz(std::uint64_t x) {
  assert(x != 0);
  return 63 - deBruijn_log2(fill_one_after_msb(x >> 1) + 1);
}

/**
 * @brief 计算 x 的二进制表示中从 least significant bit 位置开始有多少个 0
 * @param x
 * @return int 若 x=0 则返回未定义
 */
int ctz(std::uint32_t x) {
  assert(x != 0);
  return deBruijn_log2(x & ~(x - 1));
}

int ctz(std::uint64_t x) {
  assert(x != 0);
  return deBruijn_log2(x & ~(x - 1));
}

/**
 * @brief 计算 x 的二进制表示中 1 的个数
 * @param x
 * @return int
 */
int popcount(std::uint32_t x) {
  int cnt = 0;
  while (x) ++cnt, x &= x - 1;
  return cnt;
}

int popcount(std::uint64_t x) {
  int cnt = 0;
  while (x) ++cnt, x &= x - 1;
  return cnt;
}

} // namespace lib

#endif