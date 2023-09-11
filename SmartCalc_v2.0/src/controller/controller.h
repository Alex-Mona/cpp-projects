#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../model/model.h"

namespace s21 {

class Controller {
 private:
  s21::Model model;

 public:
  double InputCalc(const std::string &input_str, double in_x);
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

  void Reset();
};

}  //  namespace s21

#endif
