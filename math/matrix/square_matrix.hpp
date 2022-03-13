#ifndef SQUARE_MATRIX_HEADER_HPP
#define SQUARE_MATRIX_HEADER_HPP

#include <optional>

#include "math/matrix/matrix_base.hpp"

namespace lib {

template <typename Type>
class SquareMatrix : public Matrix<Type> {
public:
  SquareMatrix(int r, const Type &v = Type()) : Matrix<Type>(r, r, v) {}
  virtual ~SquareMatrix() = default;

  // 域上的方阵逆元，使用 Gauss-Jordan 消元，有除法，所以元素需要属于域
  virtual std::optional<SquareMatrix> inv() const {
    int n = this->row();
    assert(this->col() == n);
    Matrix aug(n, n << 1, Type(0));
    SquareMatrix res(n, n); // aug 即 augmented matrix 增广矩阵
    for (int i = 0; i < n; ++i) std::copy(this->row_begin(i), this->row_end(i), aug.row_begin(i));
    for (int i = 0; i < n; ++i) aug.at(i, i + n) = Type(1);
    // [ x x x x | 1 0 0 0 ] => [ 1 0 0 0 | x x x x ]
    // [ x x x x | 0 1 0 0 ] => [ 0 1 0 0 | x x x x ]
    // [ x x x x | 0 0 1 0 ] => [ 0 0 1 0 | x x x x ]
    // [ x x x x | 0 0 0 1 ] => [ 0 0 0 1 | x x x x ]
    // 先将左边矩阵消元为上三角矩阵且主对角线为 1 再下面往上将该矩阵消为 diag(1,1,1 ...)
    {
      for (int i = 0; i < n; ++i) {    // 第一阶段
        if (aug.at(i, i) == Type(0)) { // 选主元
          int pivot = i + 1;
          for (; pivot < n; ++pivot)
            if (aug.at(pivot, i) != Type(0)) break;
          if (pivot == n) return {}; // 不存在逆矩阵
          std::swap_ranges(aug.row_begin(i) + i, aug.row_end(i),
                           aug.row_begin(pivot) + i); // 交换行
        }
        if (aug.at(i, i) != Type(1)) {
          Type iv = Type(1) / aug.at(i, i);
          std::for_each(aug.row_begin(i) + i, aug.row_end(i), [iv](Type &a) { a *= iv; });
        }
        for (int j = i + 1; j < n; ++j) {
          Type p = aug.at(j, i);
          if (p == Type(0)) continue;
          aug.at(j, i) = Type(0);
          for (int k = i + 1; k < (n << 1); ++k) aug.at(j, k) -= p * aug.at(i, k);
        }
      }
      for (int i = n - 2; i >= 0; --i) { // 第二阶段
        for (int j = i; j >= 0; --j) {
          Type p = aug.at(j, i + 1);
          if (p == Type(0)) continue;
          // 这里直接从 n 开始枚举即可，而非 i + 2 ，因为 i + 2 到 n - 1 都为零了
          for (int k = n; k < (n << 1); ++k) aug.at(j, k) -= p * aug.at(i + 1, k);
        }
      }
    }
    for (int i = 0; i < n; ++i) std::copy(aug.row_begin(i) + n, aug.row_end(i), res.row_begin(i));
    return res;
  }

  // 方阵的行列式，使用 Gauss 消元，有除法，所以元素需要属于域
  virtual Type det() const {
    int n = this->row();
    assert(this->col() == n);
    SquareMatrix m(*this);
    bool odd = false;
    // 对矩阵 m 用 Gauss 消元成上三角矩阵，其对角线元素的积即解
    Type res(1); // 0x0 矩阵的行列式也为 1
    {
      for (int i = 0; i < n; ++i) {
        if (m.at(i, i) == Type(0)) { // 选主元
          int pivot = i + 1;
          for (; pivot < n; ++pivot)
            if (m.at(pivot, i) != Type(0)) break;
          if (pivot == n) return Type(0); // 行列式为 0
          std::swap_ranges(m.row_begin(i) + i, m.row_end(i), m.row_begin(pivot) + i);
          odd = !odd;
        }
        res *= m.at(i, i);
        Type iv = Type(1) / m.at(i, i);
        for (int j = i + 1; j < n; ++j) {
          Type p     = m.at(j, i) * iv;
          m.at(j, i) = Type(0);
          for (int k = i + 1; k < n; ++k) m.at(j, k) -= p * m.at(i, k);
        }
      }
    }
    return odd ? -res : res;
  }

  // 矩阵的秩，使用 Gauss 消元，有除法，所以元素需要属于域
  virtual int rank() const {
    int n = this->row(), res = 0;
    assert(this->col() == n);
    SquareMatrix m(*this);
    {
      for (int i = 0; i < n; ++i) {
        if (m.at(i, i) == Type(0)) { // 选主元
          int pivot = i + 1;
          for (; pivot < n; ++pivot)
            if (m.at(pivot, i) != Type(0)) break;
          if (pivot == n) continue;
          std::swap_ranges(m.row_begin(i) + i, m.row_end(i), m.row_begin(pivot) + i);
        }
        ++res;
        Type iv = Type(1) / m.at(i, i);
        for (int j = i + 1; j < n; ++j) {
          Type p     = m.at(j, i) * iv;
          m.at(j, i) = Type(0);
          for (int k = i + 1; k < n; ++k) m.at(j, k) -= p * m.at(i, k);
        }
      }
    }
    return res;
  }

  // 相似变换为上 Hessenberg 方阵，使用 Gauss 消元，有除法，所以元素需要属于域
  SquareMatrix to_upper_Hessenberg() const {
    int n = this->row();
    assert(this->col() == n);
    SquareMatrix m(*this);
    for (int i = 0; i < n - 2; ++i) {
      if (m.at(i + 1, i) == Type(0)) {
        int pivot = i + 2;
        for (; pivot < n; ++pivot)
          if (m.at(pivot, i) != Type(0)) break;
        if (pivot == n) continue;
        std::swap_ranges(m.row_begin(i + 1) + i, m.row_end(i + 1), m.row_begin(pivot) + i);
        for (int j = 0; j < n; ++j) std::swap(m.at(j, i + 1), m.at(j, pivot));
      }
      Type iv = Type(1) / m.at(i + 1, i);
      for (int j = i + 2; j < n; ++j) {
        if (m.at(j, i) == Type(0)) continue;
        Type v = m.at(j, i) * iv;
        for (int k = i; k < n; ++k) m.at(j, k) -= v * m.at(i + 1, k);
        for (int k = 0; k != n; ++k) m.at(k, i + 1) += v * m.at(k, j);
      }
    }
    return m;
  }

  friend std::istream &operator>>(std::istream &is, SquareMatrix &rhs) {
    for (auto &i : rhs.mat_) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const SquareMatrix &rhs) {
    int n = rhs.col();
    for (int i = 0, e = rhs.size(), k = 0; i < e; ++i) {
      os << rhs.mat_[i];
      if (++k == n) {
        k = 0;
        std::cout << '\n';
      } else {
        std::cout << ' ';
      }
    }
    return os;
  }
};

} // namespace lib

#endif
