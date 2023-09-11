#ifndef MODEL_H
#define MODEL_H

#include <cmath>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using std::list;
using std::string;

typedef enum {
  NUMBER = 1,
  X = 2,
  PLUS = 3,
  MINUS = 4,
  DIV = 5,
  MULT = 6,
  POW = 7,
  MOD = 8,
  COS = 11,
  SIN = 12,
  TAN = 13,
  ACOS = 14,
  ASIN = 15,
  ATAN = 16,
  SQRT = 17,
  LN = 18,
  LOG = 19,
  LEFT = 20,
  RIGHT = 21
} type_action;

typedef enum {
  HIGH_PR = 3,
  MEDIUM_PR = 2,
  LOW_PR = 1,
  NUM = 0,
  LLOW_PR = -1
} type_priority;

namespace s21 {

class ListCalc {
 public:
  ListCalc(type_action act, type_priority priority, double data)
      : prt(priority), num(data), type(act) {}
  type_priority prt;
  double num = 0;
  type_action type;
};

class Model {
 public:
  list<ListCalc> stack_calc;
  void Reset();
  double ScanLineEdit(string input, double in_x);

  Model() : data_(0), temp_num_(""), check_num_(false){};
  Model(const Model &value);

  double AnnuityCalculator(const double &sum_credit, const double &percent,
                           const int &size, double &month_sum,
                           double &month_percent, double &remains);

  double DifferentiatedCalculator(const double &sum_credit,
                                  const double &percent, const int &size,
                                  double &month_sum, double &month_percent,
                                  double &remains);

  double DepositCalculator(
      const std::vector<std::pair<std::string, double>> &add_sub_money,
      const std::string &data, const double &percent, double &month_percent,
      double &profit);

  void AllProfit(double &profit, double &percent_money);
  void ReverseStack();
  void SortStation();
  void AddTempStack(Model &temp, Model &result);
  double Calculation(list<ListCalc> &head);
  double Arithmetic(double b, int symbol);
  double Trigonometry(double a, int symbol);

 private:
  double data_;
  string temp_num_;
  bool check_num_;

  void Plus(double a);
  void Minus(double a);
  void Div(double a);
  void Mult(double a);
  void Pow(double a);
  void Mod(double a);
  void Cos(double a);
  void Sin(double a);
  void Tan(double a);
  void Acos(double a);
  void Asin(double a);
  void Atan(double a);
  void Sqrt(double a);
  void Ln(double a);
  void Log(double a);
  double GetData();
  list<ListCalc> GetStack();

  void AddTokenPlus(const string &input, size_t &x, const size_t &position);
  void AddTokenMinus(const string &input, size_t &x, const size_t &position);
  void AddTokenDiv(size_t &x);
  void AddTokenMult(size_t &x);
  void AddTokenPow(size_t &x);
  void AddTokenMod(size_t &x);
  void AddTokenCos(const std::string &input, size_t &position);
  void AddTokenSin(const std::string &input, size_t &position);
  void AddTokenTan(const std::string &input, size_t &position);
  void AddTokenAcos(const std::string &input, size_t &position);
  void AddTokenAsin(const std::string &input, size_t &position);
  void AddTokenAtan(const std::string &input, size_t &position);
  void AddTokenSqrt(const std::string &input, size_t &position);
  void AddTokenLn(const std::string &input, size_t &position);
  void AddTokenLog(const std::string &input, size_t &position);
  void AddTokenLeft();
  void AddTokenRight(size_t &x);
  void AddNumber(size_t &x);
  void ReadNumber(const std::string &input, size_t &x, const size_t &position,
                  const double &in_x);

  void PushStack(type_action act, type_priority priority, double data);
  double ReadNum();
};

}  // namespace s21

#endif
