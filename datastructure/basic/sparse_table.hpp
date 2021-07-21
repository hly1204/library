#ifndef SPARSE_TABLE_HEADER_HPP
#define SPARSE_TABLE_HEADER_HPP

/**
 * @brief sparse table / 稀疏表
 *
 */

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <vector>

namespace lib {

template <typename Type, typename FoldFunc>
class SparseTable {
public:
  static std::uint32_t log2_floor(std::uint32_t n) {
    n >>= 1, n |= n >> 1, n |= n >> 2, n |= n >> 4, n |= n >> 8, n |= n >> 16, ++n;
    static constexpr std::uint32_t deBruijn    = 0x4653adf;
    static constexpr std::uint32_t convert[32] = {0,  1,  2,  6,  3,  11, 7,  16, 4,  14, 12,
                                                  21, 8,  23, 17, 26, 31, 5,  10, 15, 13, 20,
                                                  22, 25, 30, 9,  19, 24, 29, 18, 28, 27};
    return convert[n * deBruijn >> 27];
  }
  template <typename Container>
  SparseTable(const Container &init_v, FoldFunc f = FoldFunc()) : N_(init_v.size()), f_(f) {
    int level = log2_floor(N_);
    table_.resize(level + 1);
    table_[0].resize(N_);
    std::copy_n(init_v.begin(), N_, table_[0].begin());
    for (int i = 0; i < level; ++i) {
      int s                       = N_ + 1 - (1 << (i + 1));
      const std::vector<Type> &ti = table_[i];
      std::vector<Type> &ti1      = table_[i + 1];
      ti1.resize(s);
      for (int j = 0, offset = 1 << i; j < s; ++j) ti1[j] = f_(ti[j], ti[j + offset]);
    }
  }
  ~SparseTable() = default;

  Type fold(int l, int r) const { // [l,r]
    assert(l <= r);
    int level = log2_floor(r + 1 - l);
    return f_(table_[level][l], table_[level][r + 1 - (1 << level)]);
  }

private:
  const int N_;
  FoldFunc f_;
  std::vector<std::vector<Type>> table_;
};

template <typename Type, typename Comp = std::less<>>
SparseTable<Type, std::function<Type(const Type &, const Type &)>>
make_rmq_sparse_table(const std::vector<Type> &init_v, Comp cmp = Comp()) {
  return SparseTable<Type, std::function<Type(const Type &, const Type &)>>(
      init_v, [&cmp](const Type &x, const Type &y) { return cmp(x, y) ? x : y; });
}

} // namespace lib

#endif