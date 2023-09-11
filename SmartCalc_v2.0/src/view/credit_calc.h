#ifndef CREDITCALC_H
#define CREDITCALC_H

#include <QDialog>

#include "table.h"

namespace Ui {
class CreditCalc;
}

namespace s21 {

class CreditCalc : public QDialog {
  Q_OBJECT

 public:
  explicit CreditCalc(QWidget *parent = nullptr);
  ~CreditCalc();

 private slots:
  void on_pushButton_clicked();
  void on_differentiated_calc_clicked(bool check);
  void on_annuity_calc_clicked(bool check);

 private:
  Ui::CreditCalc *ui_;
  Table *new_table_;
  void Refresh();
  bool this_annuity_;
  void сalculation_credit_(bool check);

 signals:
  void signal_all_sum(double);
  void signal_percent(double);
  void signal_size_credit(int);
  void signal_data_credit(QDate);
  void signal_check(bool);
};

}  // namespace s21

#endif  // CREDITCALC_H
