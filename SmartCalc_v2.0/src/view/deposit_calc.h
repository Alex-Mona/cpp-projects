#ifndef DEPOSITCALC_H
#define DEPOSITCALC_H

#include <qvector.h>

#include <QDialog>
#include <QStandardItemModel>

#include "table.h"

namespace Ui {
class DepositCalc;
}

namespace s21 {

class DepositCalc : public QDialog {
  Q_OBJECT

 public:
  explicit DepositCalc(QWidget *parent = nullptr);
  ~DepositCalc();

 private slots:
  void on_add_money_clicked();
  void on_sub_money_clicked();
  void on_add_money_2_clicked();
  void on_sub_money_2_clicked();
  void on_pushButton_clicked();

 private:
  Ui::DepositCalc *ui_;
  Table *new_table_;
  int rows_ = 0;
  int rows_2_ = 0;
  std::vector<std::pair<std::string, double>> add_sub_money_;
  s21::Controller control_deposit_;

  void Refresh();

 signals:
  void signal_all_sum(double);
  void signal_percent(double);
  void signal_size(int);
  void signal_data(QDate);
  void signal_check(bool);
  void signal_add_sub_money(std::vector<std::pair<std::string, double>>);
};

}  // namespace s21

#endif  // DEPOSITCALC_H
