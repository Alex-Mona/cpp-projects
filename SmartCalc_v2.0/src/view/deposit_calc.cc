#include "deposit_calc.h"

#include "ui_deposit_calc.h"

s21::DepositCalc::DepositCalc(QWidget *parent)
    : QDialog(parent), ui_(new Ui::DepositCalc), new_table_(nullptr) {
  ui_->setupUi(this);

  ui_->tableWidget->setRowCount(0);
  ui_->tableWidget->setColumnCount(2);
  ui_->tableWidget->setHorizontalHeaderLabels(QStringList()
                                              << "Дата"
                                              << "Сумма пополнения");
  ui_->tableWidget->setColumnWidth(0, 115);
  ui_->tableWidget->setColumnWidth(1, 135);

  ui_->tableWidget_2->setRowCount(0);
  ui_->tableWidget_2->setColumnCount(2);
  ui_->tableWidget_2->setHorizontalHeaderLabels(QStringList()
                                                << "Дата"
                                                << "Сумма списания");
  ui_->tableWidget_2->setColumnWidth(0, 115);
  ui_->tableWidget_2->setColumnWidth(1, 135);
}

s21::DepositCalc::~DepositCalc() {
  if (new_table_ != nullptr) {
    delete new_table_;
    new_table_ = nullptr;
  }
  delete ui_;
}

void s21::DepositCalc::on_add_money_clicked() {
  QTableWidgetItem *item =
      new QTableWidgetItem(QString::number(ui_->spinBox_add->value()));
  QTableWidgetItem *item_2 =
      new QTableWidgetItem(ui_->dateEdit_add->date().toString("MM.yyyy"));
  ui_->tableWidget->setRowCount(++rows_);
  ui_->tableWidget->setItem(this->rows_ - 1, 1, item);
  ui_->tableWidget->setItem(this->rows_ - 1, 0, item_2);
  add_sub_money_.push_back(std::pair<std::string, double>(
      ui_->dateEdit_add->date().toString("MM.yyyy").toStdString(),
      ui_->spinBox_add->value()));
}

void s21::DepositCalc::on_sub_money_clicked() {
  if (rows_ > 0) {
    ui_->tableWidget->setRowCount(--rows_);
    add_sub_money_.pop_back();
  }
}

void s21::DepositCalc::on_add_money_2_clicked() {
  double buffer = 0;
  for (auto value : add_sub_money_) {
    if (value.second < 0) buffer -= value.second;
  }
  if ((ui_->spinBox_sum->value() - buffer >= ui_->spinBox_sub->value())) {
    QTableWidgetItem *item =
        new QTableWidgetItem(QString::number(ui_->spinBox_sub->value() * (-1)));
    QTableWidgetItem *item_2 =
        new QTableWidgetItem(ui_->dateEdit_sub->date().toString("MM.yyyy"));
    ui_->tableWidget_2->setRowCount(++rows_2_);
    ui_->tableWidget_2->setItem(this->rows_2_ - 1, 1, item);
    ui_->tableWidget_2->setItem(this->rows_2_ - 1, 0, item_2);
    add_sub_money_.push_back(std::pair<std::string, double>(
        ui_->dateEdit_sub->date().toString("MM.yyyy").toStdString(),
        ui_->spinBox_sub->value() * (-1)));
  }
}

void s21::DepositCalc::on_sub_money_2_clicked() {
  if (rows_2_ > 0) {
    ui_->tableWidget_2->setRowCount(--rows_2_);
    add_sub_money_.pop_back();
  }
}

void s21::DepositCalc::on_pushButton_clicked() {
  this->Refresh();
  emit signal_all_sum(ui_->spinBox_sum->value());
  emit signal_percent(ui_->doubleSpinBox->value());
  emit signal_size((ui_->comboBox->currentIndex() + 1) * 12);
  emit signal_data(ui_->dateEdit->date());
  emit signal_check(true);
  emit signal_add_sub_money(add_sub_money_);
  new_table_->CheckCalc();
  new_table_->show();
}

void s21::DepositCalc::Refresh() {
  if (new_table_ != nullptr) {
    delete new_table_;
    new_table_ = nullptr;
  }
  new_table_ = new Table;
  connect(this, &DepositCalc::signal_all_sum, new_table_, &Table::slot_all_sum);
  connect(this, &DepositCalc::signal_percent, new_table_, &Table::slot_percent);
  connect(this, &DepositCalc::signal_size, new_table_,
          &Table::slot_size_credit);
  connect(this, &DepositCalc::signal_data, new_table_,
          &Table::slot_data_credit);
  connect(this, &DepositCalc::signal_check, new_table_,
          &Table::slot_check_deposit);
  connect(this, &DepositCalc::signal_add_sub_money, new_table_,
          &Table::slot_add_sub_money);
}
