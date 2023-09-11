#include "s21_matrix_oop.h"

// Создание матрицы

void S21Matrix::CreateMatrix() {
  if (rows_ < 1 || cols_ < 1) {
    throw std::out_of_range("Wrong matrix size");
  }
  int counter = 0;
  matrix_ = new double *[rows_];
  for (int i = 0; i < rows_; i++) {
    try {
      matrix_[i] = new double[cols_]();
      counter++;
    } catch (...) {
      for (int i = 0; i < counter; i++) {
        delete[] matrix_[i];
      }
      delete[] matrix_;
      matrix_ = nullptr;
      throw;
    }
  }
}

// Стирание матрицы

void S21Matrix::RemoveMatrix() {
  if (matrix_ != nullptr) {
    for (int i = 0; i < rows_; i++) {
      delete[] matrix_[i];
    }
    delete[] matrix_;
    matrix_ = nullptr;
    rows_ = cols_ = 0;
  }
}

void S21Matrix::DelRc(S21Matrix &other, int num_i, int num_j) {
  int i_row = 0;
  int i_col = 0;
  for (int i = 0; i < other.rows_; i++) {
    if (i == num_i) i_row = 1;
    for (int j = 0; j < other.cols_; j++) {
      if (j == num_j) i_col = 1;
      other.matrix_[i][j] = matrix_[i + i_row][j + i_col];
    }
    i_col = 0;
  }
}

void S21Matrix::MinorMatrix(S21Matrix &other) {
  S21Matrix result(rows_, cols_);
  S21Matrix minor(rows_ - 1, cols_ - 1);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      double determinant = 0;
      this->DelRc(minor, i, j);
      determinant = minor.Determinant();
      other.matrix_[i][j] = determinant;
    }
  }
}

void S21Matrix::CheckRowsCols(int rows, int cols) {
  if (rows != cols) {
    throw std::out_of_range("Rows and columns are not equal");
  }
}

void S21Matrix::CheckForSumSub(int rows1, int cols1, int rows2, int cols2) {
  if (rows1 != rows2 || cols1 != cols2) {
    throw std::out_of_range(
        "Invalid input, matrices must have the same size");
  }
}