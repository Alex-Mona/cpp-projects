#include "view.h"

#include "graph.h"
#include "ui_view.h"

s21::View::View(QWidget *parent) : QMainWindow(parent), ui_(new Ui::View) {
  ui_->setupUi(this);
  graph_function_ = new s21::Graph;
  connect(ui_->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui_->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui_->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui_->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui_->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui_->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui_->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui_->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui_->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui_->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(this, &View::signal_text, graph_function_, &s21::Graph::slot_text);
  connect(this, &View::signal_x, graph_function_, &s21::Graph::slot_x);
}

s21::View::~View() {
  if (graph_function_ != nullptr) {
    delete graph_function_;
    graph_function_ = nullptr;
  }
  delete ui_;
}

void s21::View::digits_numbers() {
  clean_result();
  QPushButton *button = (QPushButton *)sender();
  ui_->lineEdit->setText(ui_->lineEdit->text() + button->text());
}

void s21::View::digits_operations() {
  QPushButton *button = (QPushButton *)sender();
  ui_->lineEdit->setText(button->text());
}

void s21::View::on_pushButton_L_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + "(");
}

void s21::View::on_pushButton_R_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + ")");
}

void s21::View::on_pushButton_acos_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + "acos(");
}

void s21::View::on_pushButton_asin_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + "asin(");
}

void s21::View::on_pushButton_atan_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + "atan(");
}

void s21::View::on_pushButton_cos_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + "cos(");
}

void s21::View::on_pushButton_div_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + "/");
}

void s21::View::on_pushButton_ln_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + "ln(");
}

void s21::View::on_pushButton_log_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + "log(");
}

void s21::View::on_pushButton_mod_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + "mod");
}

void s21::View::on_pushButton_mult_clicked() {
  ui_->lineEdit->setText(ui_->lineEdit->text() + "*");
}

void s21::View::on_pushButton_plus_clicked() {
  ui_->lineEdit->setText(ui_->lineEdit->text() + "+");
}

void s21::View::on_pushButton_pow_clicked() {
  ui_->lineEdit->setText(ui_->lineEdit->text() + "^");
}

void s21::View::on_pushButton_result_clicked() {
  double x = 0;
  clean_view_ = true;
  if (ui_->lineEdit_2->text() != "") {
    x = (ui_->lineEdit_2->text().toDouble());
  }
  ui_->lineEdit->setText(QString::number(
      control_result_.InputCalc(ui_->lineEdit->text().toStdString(), x), 'g',
      15));
}

void s21::View::on_pushButton_sin_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + "sin(");
}

void s21::View::on_pushButton_sin_2_clicked() {
  clean_result();
  ui_->lineEdit->setText("");
}

void s21::View::on_pushButton_sqrt_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + "sqrt(");
}

void s21::View::on_pushButton_sub_clicked() {
  ui_->lineEdit->setText(ui_->lineEdit->text() + "-");
}

void s21::View::on_pushButton_tan_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + "tan(");
}

void s21::View::on_pushButton_dot_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + ".");
}

void s21::View::on_pushButton_x_clicked() {
  clean_result();
  ui_->lineEdit->setText(ui_->lineEdit->text() + "x");
}

void s21::View::clean_result() {
  if (clean_view_) {
    ui_->lineEdit->setText("");
    clean_view_ = false;
  }
}

void s21::View::on_pushButton_graph_clicked() {
  emit signal_text(ui_->lineEdit->text());
  emit signal_x(ui_->lineEdit_2->text());
  graph_function_->PrintGraph();
  graph_function_->show();
}

void s21::View::on_pushButton_credit_calc_clicked() {
  calc_dialog_ = new s21::CreditCalc;
  calc_dialog_->show();
}

void s21::View::on_pushButton_deposit_calc_clicked() {
  deposit_dialog_ = new s21::DepositCalc;
  deposit_dialog_->show();
}
