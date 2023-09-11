#include "s21_matrix_oop.h"

// Хранить только приватные поля matrix_, rows_ и cols_

// Конструкторы

// Базовый конструктор, инициализирующий матрицу некоторой заранее заданной размерностью

S21Matrix::S21Matrix() {
  rows_ = cols_ = 0;
  matrix_ = nullptr;
}

// Параметризированный конструктор с количеством строк и столбцов

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  create_matrix();
}

// Конструктор копирования

S21Matrix::S21Matrix(const S21Matrix &other)
    : rows_(other.rows_), cols_(other.cols_) {
  create_matrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      this->matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

// Конструктор переноса

S21Matrix::S21Matrix(S21Matrix &&other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.matrix_ = nullptr;
  other.rows_ = other.cols_ = 0;
}

// Деструктор

S21Matrix::~S21Matrix() { remove_matrix(); }

// Получение Rows - рядов(сторк), и Cols - столбцов
// Установка Rows - рядов(строк), и Cols - столбцов

int S21Matrix::GetRows() { return rows_; }

int S21Matrix::GetCols() { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows_ != rows) {
    S21Matrix tmp(rows, cols_);
    int tmp_rows = 0;
    if (rows < rows_)
      tmp_rows = rows;
    else
      tmp_rows = rows_;
    for (int i = 0; i < tmp_rows; i++) {
      for (int j = 0; j < cols_; j++) {
        tmp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = tmp;
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols_ != cols) {
    S21Matrix tmp(rows_, cols);
    int tmp_cols = 0;
    if (cols < cols_)
      tmp_cols = cols;
    else
      tmp_cols = cols_;
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < tmp_cols; j++) {
        tmp.matrix_[i][j] = matrix_[i][j];
      }
    }
    *this = tmp;
  }
}

// Операции над матрицами

// Сравнение матриц

bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool flag = true;
  if (rows_ == other.rows_ && cols_ == other.cols_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; (j < cols_) && flag; j++) {
        if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 1e-7) {
          flag = false;
          break;
        }
      }
    }
  } else {
    flag = false;
  }
  return flag;
}

// Сложение матриц

void S21Matrix::SumMatrix(const S21Matrix &other) {
  check_for_sum_sub(rows_, cols_, other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

// Вычитание матриц

void S21Matrix::SubMatrix(const S21Matrix &other) {
  check_for_sum_sub(rows_, cols_, other.rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

// Умножение матрицы на число

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

// Умножение двух матриц

void S21Matrix::MulMatrix(const S21Matrix &other) {
  check_rows_cols(cols_, other.rows_);
  S21Matrix tmp(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < other.rows_; k++) {
        tmp.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = tmp;
}

// Транспонирование матрицы

S21Matrix S21Matrix::Transpose() {
  S21Matrix tmp(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      tmp.matrix_[j][i] = matrix_[i][j];
    }
  }
  return tmp;
}
// Минор матрицы и матрица алгебраических дополнений

S21Matrix S21Matrix::CalcComplements() {
  check_rows_cols(rows_, cols_);
  S21Matrix result(rows_, cols_);
  if (rows_ == 1) {
    result.matrix_[0][0] = matrix_[0][0];
  } else {
    this->minor_matrix(result);
    for (int i = 0; i < result.rows_; i++) {
      for (int j = 0; j < result.cols_; j++) {
        result.matrix_[i][j] *= pow(-1, i + j);
      }
    }
  }
  return result;
}

// Определитель матрицы

double S21Matrix::Determinant() {
  check_rows_cols(rows_, cols_);
  double determinant = 0;
  double multiplier = 1;
  if (rows_ == 1) {
    determinant = matrix_[0][0];
  } else if (rows_ == 2) {
    determinant = (matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0]);
  } else {
    S21Matrix tmp((rows_ - 1), (cols_ - 1));
    for (int i = 0; i < rows_; i++) {
      this->del_rc(tmp, 0, i);
      determinant += multiplier * matrix_[0][i] * tmp.Determinant();
      multiplier *= -1;
    }
  }
  return determinant;
}

// Обратная матрица

S21Matrix S21Matrix::InverseMatrix() {
  check_rows_cols(rows_, cols_);
  double determinant = 0;
  determinant = this->Determinant();
  if (!determinant) throw std::out_of_range("The determinant must not be zero");
  S21Matrix matrix1(rows_, cols_);
  if (fabs(determinant) > 1e-7) {
    matrix1 = this->CalcComplements();
    matrix1 = matrix1.Transpose();
    matrix1.MulNumber((double)1.0 / determinant);
  }
  return matrix1;
}

// Операторы перегрузки

S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(other.rows_, other.cols_);
  result.SumMatrix(*this);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(*this);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(*this);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double &num) {
  S21Matrix result(*this);
  result.MulNumber(num);
  return result;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this->rows_ != other.rows_ || this->cols_ != other.cols_) {
    remove_matrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    create_matrix();
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator+=(const S21Matrix &other) {
  this->SumMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator-=(const S21Matrix &other) {
  this->SubMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const S21Matrix &other) {
  this->MulMatrix(other);
  return *this;
}

S21Matrix &S21Matrix::operator*=(const double &num) {
  this->MulNumber(num);
  return *this;
}

double &S21Matrix::operator()(const int row, const int col) {
  if (rows_ <= row || cols_ <= col || row < 0 || col < 0) {
    throw std::out_of_range("Invalid index");
  }
  return matrix_[row][col];
}
