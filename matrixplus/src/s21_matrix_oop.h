#ifndef SRC_S21_MATRIX_OOP_H_
#define SRC_S21_MATRIX_OOP_H_

#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  int rows_, cols_;
  double **matrix_;
  void create_matrix();
  void remove_matrix();
  void del_rc(S21Matrix &other, int num_i, int num_j);
  void minor_matrix(S21Matrix &other);
  void check_rows_cols(int rows, int cols);
  void check_for_sum_sub(int rows1, int cols1, int rows2, int cols2);

  // Методы

 public:
  //  Базовый конструктор, инициализирующий матрицу некоторой заранее заданной размерностью
  S21Matrix();
  // Параметризированный конструктор с количеством строк и столбцов
  S21Matrix(int rows, int cols);
  // Конструктор копирования
  S21Matrix(const S21Matrix &other);
  // Конструктор переноса
  S21Matrix(S21Matrix &&other);
  // Деструктор
  ~S21Matrix();
  // Получение Rows - рядов(сторк), и Cols - столбцов
  // Установка Rows - рядов(строк), и Cols - столбцов
  int GetRows();
  int GetCols();
  void SetRows(int rows);
  void SetCols(int cols);

  // Операции над матрицами

  //Проверяет матрицы на равенство между собой 
  bool EqMatrix(const S21Matrix &other);
  // Прибавляет вторую матрицы к текущей
  void SumMatrix(const S21Matrix &other);
  // Вычитает из текущей матрицы другую
  void SubMatrix(const S21Matrix &other);
  // Умножает текущую матрицу на число
  void MulNumber(const double num);
  // Умножает текущую матрицу на вторую
  void MulMatrix(const S21Matrix &other);
  // Создает новую транспонированную матрицу из текущей и возвращает ее
  S21Matrix Transpose();
  // Вычисляет матрицу алгебраических дополнений текущей матрицы и возвращает ее
  S21Matrix CalcComplements();
  // Вычисляет и возвращает определитель текущей матрицы
  double Determinant();
  // Вычисляет и возвращает обратную матрицу
  S21Matrix InverseMatrix();

  // Перегрузка операторов 

  // Сложение двух матриц
  S21Matrix operator+(const S21Matrix &other);
  // Вычитание одной матрицы из другой
  S21Matrix operator-(const S21Matrix &other);
  // Умножение матриц и умножение матрицы на число
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double &num);
  // Проверка на равенство матриц (EqMatrix)
  bool operator==(const S21Matrix &other);
  // Присвоение матрице значений другой матрицы
  S21Matrix &operator=(const S21Matrix &other);
  // Присвоение сложения (SumMatrix)
  S21Matrix &operator+=(const S21Matrix &other);
  // Присвоение разности (SubMatrix)
  S21Matrix &operator-=(const S21Matrix &other);
  // Присвоение умножения (MulMatrix/MulNumber)
  S21Matrix &operator*=(const S21Matrix &other);
  S21Matrix &operator*=(const double &num);
  // Индексация по элементам матрицы (строка, колонка)
  double &operator()(const int row, const int col);
};

#endif  // SRC_S21_MATRIX_OOP_H_
