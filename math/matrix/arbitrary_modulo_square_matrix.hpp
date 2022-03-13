#ifndef ARBITRARY_MODULO_SQUARE_MATRIX_HEADER_HPP
#define ARBITRARY_MODULO_SQUARE_MATRIX_HEADER_HPP

#include "square_matrix.hpp"

namespace lib {

template <typename Type>
class ArbitraryModuloSquareMatrix : public SquareMatrix<Type> {
public:
  using SquareMatrix<Type>::SquareMatrix;

  virtual ~ArbitraryModuloSquareMatrix() = default;
  virtual int rank() const override {

    using raw_type = typename Type::value_type;

    int n = this->row(), res = 0;
    assert(this->col() == n);
    ArbitraryModuloSquareMatrix m(*this);
    std::vector<int> real_row(n);
    for (int i = 0; i < n; ++i) real_row[i] = i;
    // 对矩阵 m 用 Gauss 消元成上三角矩阵
    {
      for (int i = 0; i < n; ++i) {
        int pivot = -1;
        raw_type min_value;
        for (int j = i; j < n; ++j) { // 选主元，主元选择数值最小的非零
          int real_j = real_row[j];
          if (m.at(real_j, i) != Type(0) &&
              (pivot == -1 || static_cast<raw_type>(m.at(real_j, i)) < min_value)) {
            min_value = static_cast<raw_type>(m.at(real_j, i));
            pivot     = j;
          }
        }
        if (pivot == -1) continue;
        ++res;
        if (real_row[pivot] != real_row[i]) std::swap(real_row[i], real_row[pivot]);
        for (int j = i + 1; j < n; ++j) {
          while (m.at(real_row[j], i) != Type(0)) {
            if (static_cast<raw_type>(m.at(real_row[j], i)) <
                static_cast<raw_type>(m.at(real_row[i], i)))
              std::swap(real_row[i], real_row[j]);
            int real_i = real_row[i], real_j = real_row[j];
            Type p(static_cast<raw_type>(m.at(real_j, i)) / static_cast<raw_type>(m.at(real_i, i)));
            for (int k = i; k < n; ++k) m.at(real_j, k) -= p * m.at(real_i, k);
          }
        }
      }
    }
    return res;
  }
  virtual Type det() const override {

    using raw_type = typename Type::value_type;

    int n = this->row();
    assert(this->col() == n);
    ArbitraryModuloSquareMatrix m(*this);
    bool odd = false;
    std::vector<int> real_row(n);
    for (int i = 0; i < n; ++i) real_row[i] = i;
    // 对矩阵 m 用 Gauss 消元成上三角矩阵，其对角线元素的积即解
    Type res(1); // 0x0 矩阵的行列式也为 1
    {
      for (int i = 0; i < n; ++i) {
        int pivot = -1;
        raw_type min_value;
        for (int j = i; j < n; ++j) { // 选主元，主元选择数值最小的非零
          int real_j = real_row[j];
          if (m.at(real_j, i) != Type(0) &&
              (pivot == -1 || static_cast<raw_type>(m.at(real_j, i)) < min_value)) {
            min_value = static_cast<raw_type>(m.at(real_j, i));
            pivot     = j;
          }
        }
        if (pivot == -1) return Type(0);
        if (real_row[pivot] != real_row[i]) {
          std::swap(real_row[i], real_row[pivot]);
          odd = !odd;
        }
        for (int j = i + 1; j < n; ++j) {
          while (m.at(real_row[j], i) != Type(0)) {
            if (static_cast<raw_type>(m.at(real_row[j], i)) <
                static_cast<raw_type>(m.at(real_row[i], i))) {
              std::swap(real_row[i], real_row[j]);
              odd = !odd;
            }
            int real_i = real_row[i], real_j = real_row[j];
            Type p(static_cast<raw_type>(m.at(real_j, i)) / static_cast<raw_type>(m.at(real_i, i)));
            for (int k = i; k < n; ++k) m.at(real_j, k) -= p * m.at(real_i, k);
          }
        }
        res *= m.at(real_row[i], i);
      }
    }
    return odd ? -res : res;
  }

  virtual ArbitraryModuloSquareMatrix to_upper_Hessenberg() const {

    using raw_type = typename Type::value_type;

    int n = this->row();
    assert(this->col() == n);
    ArbitraryModuloSquareMatrix m(*this);
    for (int i = 0; i < n - 2; ++i) {
      int pivot = -1;
      raw_type min_value;
      for (int j = i + 1; j < n; ++j) { // 选主元，主元选择数值最小的非零
        if (m.at(j, i) != Type(0) &&
            (pivot == -1 || static_cast<raw_type>(m.at(j, i)) < min_value)) {
          min_value = static_cast<raw_type>(m.at(j, i));
          pivot     = j;
        }
      }
      if (pivot == -1) continue;
      if (pivot != i + 1) {
        std::swap_ranges(m.row_begin(i + 1) + i, m.row_end(i + 1), m.row_begin(pivot) + i);
        for (int j = 0; j < n; ++j) std::swap(m.at(j, i + 1), m.at(j, pivot));
      }
      for (int j = i + 2; j < n; ++j) {
        while (m.at(j, i) != Type(0)) {
          if (static_cast<raw_type>(m.at(j, i)) < static_cast<raw_type>(m.at(i + 1, i))) {
            std::swap_ranges(m.row_begin(i + 1) + i, m.row_end(i + 1), m.row_begin(j) + i);
            for (int k = 0; k < n; ++k) std::swap(m.at(k, i + 1), m.at(k, j));
          }
          Type v(static_cast<raw_type>(m.at(j, i)) / static_cast<raw_type>(m.at(i + 1, i)));
          for (int k = i; k < n; ++k) m.at(j, k) -= v * m.at(i + 1, k);
          for (int k = 0; k != n; ++k) m.at(k, i + 1) += v * m.at(k, j);
        }
      }
    }
    return m;
  }

  friend std::istream &operator>>(std::istream &is, ArbitraryModuloSquareMatrix &rhs) {
    for (auto &i : rhs.mat_) is >> i;
    return is;
  }
  friend std::ostream &operator<<(std::ostream &os, const ArbitraryModuloSquareMatrix &rhs) {
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