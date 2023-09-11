#ifndef TABLE_H
#define TABLE_H

#include <QDate>
#include <QDialog>
#include <QTableWidgetItem>
#include <cmath>

#include "../controller/controller.h"

namespace Ui {
class Table;
}

namespace s21 {

class Table : public QDialog {
  Q_OBJECT

 public:
  explicit Table(QWidget *parent = nullptr);
  ~Table();
  void CheckCalc();
  void AnnuityCalculator();
  void DepositCalculator();
  void DifferentiatedCalculator();
  void Result();
  void AddTable(double result, double month_sum, double month_percent,
                double remains);

 private:
  Ui::Table *ui_;
  QString data_;
  QTableWidgetItem *item_, *item_1_, *item_2_, *item_3_, *item_4_;
  std::vector<std::pair<std::string, double>> add_sub_money_;
  QDate data_time_;
  s21::Controller control_table_;
  double sum_credit_, percent_;
  int size_, count_;
  bool check_, check_deposit_;
  std::vector<std::pair<std::string, double>> to_std_vector_(
      QVector<std::pair<QDate, double>> &add_sub_money_);

 public slots:
  void slot_all_sum(double all_sum);
  void slot_percent(double percent);
  void slot_size_credit(int size_credit);
  void slot_data_credit(QDate data);
  void slot_check(bool check);
  void slot_check_deposit(bool check);
  void slot_add_sub_money(std::vector<std::pair<std::string, double>> money);
};

}  // namespace s21

#endif  // TABLE_H
