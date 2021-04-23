//===----------------------------------------------------------------------===//
//
//                         BusTub
//
// p0_starter.h
//
// Identification: src/include/primer/p0_starter.h
//
// Copyright (c) 2015-2020, Carnegie Mellon University Database Group
//
//===----------------------------------------------------------------------===//

#pragma once

#include <memory>

namespace bustub {

/*
 * The base class defining a Matrix
 */
template <typename T>
class Matrix {
 protected:
  // TODO(P0): Add implementation
  Matrix(int r, int c):rows(r), cols(c) { linear = new T[rows * cols]; }

  // # of rows in the matrix
  int rows;
  // # of Columns in the matrix
  int cols;
  // Flattened array containing the elements of the matrix
  // TODO(P0) : Allocate the array in the constructor. Don't forget to free up
  // the array in the destructor.
  T *linear;

 public:
  // Return the # of rows in the matrix
  virtual int GetRows() = 0;

  // Return the # of columns in the matrix
  virtual int GetColumns() = 0;

  // Return the (i,j)th  matrix element
  virtual T GetElem(int i, int j) = 0;

  // Sets the (i,j)th  matrix element to val
  virtual void SetElem(int i, int j, T val) = 0;

  // Sets the matrix elements based on the array arr
  virtual void MatImport(T *arr) = 0;

  // TODO(P0): Add implementation
  virtual ~Matrix() { delete [] linear; };
};

template <typename T>
class RowMatrix : public Matrix<T> {
 public:
  // TODO(P0): Add implementation
  RowMatrix(int r, int c) : Matrix<T>(r, c) { this->data_ = new int*[this->rows]; for(int i; i < r; i++) { this->data_[i] = this->linear + i * this->cols; } }

  // TODO(P0): Add implementation
  int GetRows() override { return this->rows; }

  // TODO(P0): Add implementation
  int GetColumns() override { return this->cols; }

  // TODO(P0): Add implementation
  T GetElem(int i, int j) override { return this->data_[i][j]; }

  // TODO(P0): Add implementation
  void SetElem(int i, int j, T val) override { this->data_[i][j] = val; }

  // TODO(P0): Add implementation
  void MatImport(T *arr) override { int max = this->rows * this->cols; for(int i; i < max; i++) { this->linear[i] = arr[i]; } }

  // TODO(P0): Add implementation
  ~RowMatrix() override { delete [] data_; };

 private:
  // 2D array containing the elements of the matrix in row-major format
  // TODO(P0): Allocate the array of row pointers in the constructor. Use these pointers
  // to point to corresponding elements of the 'linear' array.
  // Don't forget to free up the array in the destructor.
  T **data_;
};

template <typename T>
class RowMatrixOperations {
 public:
  // Compute (mat1 + mat2) and return the result.
  // Return nullptr if dimensions mismatch for input matrices.
  static std::unique_ptr<RowMatrix<T>> AddMatrices(std::unique_ptr<RowMatrix<T>> mat1,
                                                   std::unique_ptr<RowMatrix<T>> mat2) {
    // TODO(P0): Add code
    if((*mat1).GetRows() == (*mat2).GetRows() && (*mat1).GetColumns() == (*mat1).GetColumns()){
      int rows((*mat1).GetRows());
      int cols((*mat1).GetColumns());
      std::unique_ptr<RowMatrix<T>> mat(new RowMatrix<T>(rows, cols));
      for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          (*mat).SetElem(i, j, (*mat1).GetElem(i, j) + (*mat2).GetElem(i, j));
        }
      }
      return mat;
    }

    return std::unique_ptr<RowMatrix<T>>(nullptr);
  }

  // Compute matrix multiplication (mat1 * mat2) and return the result.
  // Return nullptr if dimensions mismatch for input matrices.
  static std::unique_ptr<RowMatrix<T>> MultiplyMatrices(std::unique_ptr<RowMatrix<T>> mat1,
                                                        std::unique_ptr<RowMatrix<T>> mat2) {
    // TODO(P0): Add code
    if((*mat2).GetRows() == (*mat1).GetColumns()){
      int rows((*mat1).GetRows());
      int tmp((*mat2).GetRows());
      int cols((*mat2).GetColumns());
      std::unique_ptr<RowMatrix<T>> mat(new RowMatrix<T>(rows, cols));
      for(int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
          (*mat).SetElem(i, j, 0);
          for (int k = 0; k < tmp; k++) {
            (*mat).SetElem(i, j, (*mat).GetElem(i, j) + (*mat1).GetElem(i, k) * (*mat2).GetElem(k, j));
          }
        }
      }
      return mat;
    }

    return std::unique_ptr<RowMatrix<T>>(nullptr);
  }

  // Simplified GEMM (general matrix multiply) operation
  // Compute (matA * matB + matC). Return nullptr if dimensions mismatch for input matrices
  static std::unique_ptr<RowMatrix<T>> GemmMatrices(std::unique_ptr<RowMatrix<T>> matA,
                                                    std::unique_ptr<RowMatrix<T>> matB,
                                                    std::unique_ptr<RowMatrix<T>> matC) {
    // TODO(P0): Add code
    std::unique_ptr<RowMatrix<T>> mul = MultiplyMatrices(matA, matB);
    if(!mul){
      std::unique_ptr<RowMatrix<T>> res = AddMatrices(mul, matC);
      return res;
    }
    return std::unique_ptr<RowMatrix<T>>(nullptr);
  }
};
}  // namespace bustub
