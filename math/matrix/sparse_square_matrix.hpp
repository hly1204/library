#ifndef SPARSE_SQUARE_MATRIX_BASE_HEADER_HPP
#define SPARSE_SQUARE_MATRIX_BASE_HEADER_HPP

/**
 * @brief sparse square matrix
 *
 */

#include "sparse_matrix_base.hpp"

namespace lib {

template <typename Type>
class SparseSquareMatrix : public SparseMatrix<Type> {
public:
  SparseSquareMatrix(int r, const Type &v = Type()) : SparseMatrix<Type>(r, r, v) {}
  virtual ~SparseSquareMatrix() = default;
};

} // namespace lib

#endif