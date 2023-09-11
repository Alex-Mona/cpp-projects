#include "credit_calc.h"

#include "ui_credit_calc.h"

s21::CreditCalc::CreditCalc(QWidget *parent)
    : QDialog(parent), ui_(new Ui::CreditCalc), new_table_(nullptr) {
  ui_->setupUi(this);
}

s21::CreditCalc::~CreditCalc() {
  if (new_table_ != nullptr) {
    delete new_table_;
    new_table_ = nullptr;
  }
  delete ui_;
}

void s21::CreditCalc::on_pushButton_clicked() {
  this->Refresh();
  emit signal_all_sum(ui_->spinBox->value());
  emit signal_percent(ui_->doubleSpinBox->value());
  emit signal_size_credit((ui_->comboBox->currentIndex() + 1) * 12);
  emit signal_data_credit(ui_->dateEdit->date());
  emit signal_check(this_annuity_);
  new_table_->CheckCalc();
  new_table_->show();
}

void s21::CreditCalc::on_differentiated_calc_clicked(bool check) {
  if (check) this->this_annuity_ = false;
  this->Refresh();
}

void s21::CreditCalc::on_annuity_calc_clicked(bool check) {
  if (check) this->this_annuity_ = true;
  this->Refresh();
}

void s21::CreditCalc::Refresh() {
  if (new_table_ != nullptr) {
    delete new_table_;
    new_table_ = nullptr;
  }
  new_table_ = new Table;
  connect(this, &CreditCalc::signal_all_sum, new_table_, &Table::slot_all_sum);
  connect(this, &CreditCalc::signal_percent, new_table_, &Table::slot_percent);
  connect(this, &CreditCalc::signal_size_credit, new_table_,
          &Table::slot_size_credit);
  connect(this, &CreditCalc::signal_data_credit, new_table_,
          &Table::slot_data_credit);
  connect(this, &CreditCalc::signal_check, new_table_, &Table::slot_check);
}
