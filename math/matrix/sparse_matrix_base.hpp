#ifndef SPARSE_MATRIX_BASE_HEADER_HPP
#define SPARSE_MATRIX_BASE_HEADER_HPP

/**
 * @brief sparse matrix base
 *
 */

#include <cassert>
#include <utility>
#include <vector>

namespace lib {

template <typename Type>
class SparseMatrix {
public:
  using value_type = Type;

  SparseMatrix(int r, int c, const Type &v = Type()) : row_(r), col_(c), default_val_(v), mat_(r) {}
  virtual ~SparseMatrix()            = default;
  SparseMatrix(const SparseMatrix &) = default;

  virtual SparseMatrix &operator=(const SparseMatrix &) = default;

  int row() const { return row_; }
  int col() const { return col_; }
  int size() const { return row_ * col_; }
  bool is_empty() const { return size() == 0; }

  Type &at(int r, int c) {
    for (auto &[pos, v] : mat_[r])
      if (pos == c) return v;
    return mat_[r].emplace_back(c, default_val_).second;
  }
  Type at(int r, int c) const {
    for (auto &[pos, v] : mat_[r])
      if (pos == c) return v;
    return default_val_;
  }

  virtual std::vector<Type> apply(const std::vector<Type> &x) const {
    int r = row(), c = col();
    assert(c == x.size());
    assert(default_val_ == Type(0)); // 若默认值不为零则需要修改此函数
    std::vector<Type> res(r, Type(0));
    for (int i = 0; i < r; ++i) {
      for (auto &[pos, v] : mat_[i]) res[i] += v * x[pos];
    }
    return res;
  }

protected:
  int row_, col_;
  const Type default_val_;
  std::vector<std::vector<std::pair<int, Type>>> mat_;
};

} // namespace lib

#endif