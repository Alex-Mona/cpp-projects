#include "table.h"

#include "ui_table.h"

s21::Table::Table(QWidget *parent)
    : QDialog(parent), ui_(new Ui::Table), count_(1) {
  ui_->setupUi(this);
  ui_->tableWidget->setRowCount(count_);
  ui_->tableWidget->setColumnCount(5);
  ui_->tableWidget->setHorizontalHeaderLabels(QStringList()
                                              << "Месяц"
                                              << "Сумма платежа, руб."
                                              << "Платеж по основному, руб."
                                              << "Платеж по процентам, руб."
                                              << "Остаток, руб.");
  ui_->tableWidget->setColumnWidth(1, 175);
  ui_->tableWidget->setColumnWidth(2, 195);
  ui_->tableWidget->setColumnWidth(3, 175);
  ui_->tableWidget->setColumnWidth(4, 155);
}

s21::Table::~Table() { delete ui_; }

void s21::Table::CheckCalc() {
  if (check_ && !check_deposit_)
    this->AnnuityCalculator();
  else if (!check_ && !check_deposit_)
    this->DifferentiatedCalculator();
  else
    this->DepositCalculator();
}

void s21::Table::AnnuityCalculator() {
  double result = 0, month_percent = 0, month_sum = 0, remains = sum_credit_;
  for (int i = 0; i < size_; i++, count_++) {
    ui_->tableWidget->setRowCount(count_);
    result = this->control_table_.AnnuityCalculator(
        sum_credit_, percent_, size_, month_sum, month_percent, remains);
    this->AddTable(result, month_sum, month_percent, remains);
  }
  this->Result();
}

void s21::Table::DifferentiatedCalculator() {
  double result = 0, month_percent = 0, month_sum = 0, remains = sum_credit_;
  for (int i = 0; i < size_; i++, count_++) {
    ui_->tableWidget->setRowCount(count_);
    result = this->control_table_.DifferentiatedCalculator(
        sum_credit_, percent_, size_, month_sum, month_percent, remains);
    this->AddTable(result, month_sum, month_percent, remains);
  }
  this->Result();
}

void s21::Table::Result() {
  double all_percent = 0;
  for (int i = 0; i < count_ - 1; i++) {
    all_percent += ui_->tableWidget->item(i, 3)->text().toDouble();
  }
  ui_->tableWidget->setRowCount(++count_);
  item_ = new QTableWidgetItem("ИТОГО:");
  item_1_ = new QTableWidgetItem(QString::number(all_percent));
  item_2_ = new QTableWidgetItem(QString::number(all_percent + sum_credit_));
  ui_->tableWidget->setItem(count_ - 1, 2, item_);
  ui_->tableWidget->setItem(count_ - 1, 3, item_1_);
  ui_->tableWidget->setItem(count_ - 1, 4, item_2_);
}

void s21::Table::DepositCalculator() {
  double result = 0, month_percent = 0, profit = sum_credit_;
  for (int i = 0; i < size_; i++, count_++) {
    ui_->tableWidget->setRowCount(count_);
    string date = data_time_.toString("MM.yyyy").toStdString();
    result = this->control_table_.DepositCalculator(
        add_sub_money_, date, percent_, month_percent, profit);
    this->AddTable(result, profit - month_percent, month_percent, profit);
    this->control_table_.AllProfit(profit, result);
  }
  this->Result();
}

void s21::Table::slot_all_sum(double all_sum) { this->sum_credit_ = all_sum; }
void s21::Table::slot_percent(double percent) { this->percent_ = percent; }
void s21::Table::slot_size_credit(int size_credit) {
  this->size_ = size_credit;
}
void s21::Table::slot_data_credit(QDate data) { this->data_time_ = data; }
void s21::Table::slot_check(bool check) { this->check_ = check; }
void s21::Table::slot_check_deposit(bool check) {
  this->check_deposit_ = check;
}
void s21::Table::slot_add_sub_money(
    std::vector<std::pair<std::string, double>> money) {
  this->add_sub_money_ = money;
}

void s21::Table::AddTable(double result, double month_sum, double month_percent,
                          double remains) {
  item_ = new QTableWidgetItem(data_time_.toString("MM.yyyy"));
  item_1_ = new QTableWidgetItem(QString::number(result));
  item_2_ = new QTableWidgetItem(QString::number(month_sum));
  item_3_ = new QTableWidgetItem(QString::number(month_percent));
  item_4_ = new QTableWidgetItem(QString::number(remains > 1 ? remains : 0));

  ui_->tableWidget->setItem(count_ - 1, 0, item_);
  ui_->tableWidget->setItem(count_ - 1, 1, item_1_);
  ui_->tableWidget->setItem(count_ - 1, 2, item_2_);
  ui_->tableWidget->setItem(count_ - 1, 3, item_3_);
  ui_->tableWidget->setItem(count_ - 1, 4, item_4_);
  data_time_ = data_time_.addMonths(1);
}

std::vector<std::pair<std::string, double>> s21::Table::to_std_vector_(
    QVector<std::pair<QDate, double>> &add_sub_money) {
  std::vector<std::pair<std::string, double>> result;
  for (auto &&i : add_sub_money) {
    result.push_back(std::pair<std::string, double>(
        i.first.toString("MM.yyyy").toStdString(), i.second));
  }
  return result;
}
