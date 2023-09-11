#include "controller.h"

double s21::Controller::InputCalc(const std::string &input_str, double in_x) {
  return model.ScanLineEdit(input_str, in_x);
}

double s21::Controller::AnnuityCalculator(const double &sum_credit,
                                          const double &percent,
                                          const int &size, double &month_sum,
                                          double &month_percent,
                                          double &remains) {
  return model.AnnuityCalculator(sum_credit, percent, size, month_sum,
                                 month_percent, remains);
}

double s21::Controller::DifferentiatedCalculator(
    const double &sum_credit, const double &percent, const int &size,
    double &month_sum, double &month_percent, double &remains) {
  return model.DifferentiatedCalculator(sum_credit, percent, size, month_sum,
                                        month_percent, remains);
}

double s21::Controller::DepositCalculator(
    const std::vector<std::pair<std::string, double>> &add_sub_money,
    const std::string &data, const double &percent, double &month_percent,
    double &profit) {
  return model.DepositCalculator(add_sub_money, data, percent, month_percent,
                                 profit);
}

void s21::Controller::AllProfit(double &profit, double &percent_money) {
  return model.AllProfit(profit, percent_money);
}

void s21::Controller::Reset() { model.Reset(); }
