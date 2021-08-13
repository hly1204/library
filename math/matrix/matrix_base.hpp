#ifndef MATRIX_BASE_HEADER_HPP
#define MATRIX_BASE_HEADER_HPP

/**
 * @brief matrix base
 *
 */

#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

namespace lib {

template <typename Type>
class Matrix {
public:
  using value_type = Type;

  /**
   * @brief Matrix 类
   *
   * @param r 行
   * @param c 列
   * @param v 初值
   */
  Matrix(int r, int c, const Type &v = Type()) : row_(r), col_(c), mat_(row_ * col_, v) {}
  virtual ~Matrix()      = default;
  Matrix(const Matrix &) = default;

  virtual Matrix &operator=(const Matrix &) = default;

  int row() const { return row_; }
  int col() const { return col_; }
  int size() const { return row_ * col_; }
  bool is_empty() const { return size() == 0; }

  decltype(auto) row_begin(int r) { return mat_.begin() + r * col_; }
  decltype(auto) row_cbegin(int r) const { return mat_.cbegin() + r * col_; }
  decltype(auto) row_begin(int r) const { return row_cbegin(r); }
  decltype(auto) row_end(int r) { return mat_.begin() + (r + 1) * col_; }
  decltype(auto) row_cend(int r) const { return mat_.cbegin() + (r + 1) * col_; }
  decltype(auto) row_end(int r) const { return row_cend(r); }

#ifdef LOCAL
  Type &at(int r, int c) { return mat_.at(r * col_ + c); }
  const Type &at(int r, int c) const { return mat_.at(r * col_ + c); }
#else
  Type &at(int r, int c) { return mat_[r * col_ + c]; }
  const Type &at(int r, int c) const { return mat_[r * col_ + c]; }
#endif

  virtual Matrix &operator+=(const Matrix &rhs) {
    assert(row() == rhs.row());
    assert(col() == rhs.col());
    for (int i = 0, n = size(); i < n; ++i) mat_[i] -= rhs.mat_[i];
    return *this;
  }

  virtual Matrix &operator-=(const Matrix &rhs) {
    assert(row() == rhs.row());
    assert(col() == rhs.col());
    for (int i = 0, n = size(); i < n; ++i) mat_[i] -= rhs.mat_[i];
    return *this;
  }

  virtual Matrix transpose() const {
    int n = row(), m = col();
    Matrix res(m, n, Type(0));
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j) res.at(j, i) = at(i, j);
    return res;
  }

  /**
   * @brief 返回矩阵和列向量 x 的积
   * @param x 列向量 x 满足 x 的行数等于矩阵的列数
   * @return std::vector<Type>
   */
  virtual std::vector<Type> apply(const std::vector<Type> &x) const {
    assert(col() == x.size());
    int n = row();
    std::vector<Type> res(n);
    for (int i = 0; i < n; ++i)
      res[i] = std::inner_product(row_begin(i), row_end(i), x.begin(), Type(0));
    return res;
  }

  /**
   * @brief 矩阵乘法
   * @param rhs 右乘的矩阵
   * @return Matrix&
   */
  virtual Matrix &operator*=(const Matrix &rhs) {
    int n = row(), m = rhs.col(), l = col();
    assert(l == rhs.row());
    // n*l 的矩阵右乘一个 l*m 的矩阵
    Matrix res(n, m), trhs(rhs.transpose());
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < m; ++j)
        res.at(i, j) = std::inner_product(row_begin(i), row_end(i), trhs.row_begin(j), Type(0));
    return this->operator=(res);
  }

  virtual Matrix operator+(const Matrix &rhs) { return Matrix(*this) += rhs; }
  virtual Matrix operator-(const Matrix &rhs) { return Matrix(*this) -= rhs; }
  virtual Matrix operator*(const Matrix &rhs) { return Matrix(*this) *= rhs; }

  friend std::istream &operator>>(std::istream &is, Matrix &rhs) {
    for (auto &i : rhs.mat_) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const Matrix &rhs) {
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

protected:
  int row_, col_;
  std::vector<Type> mat_;
};

} // namespace lib

#endif