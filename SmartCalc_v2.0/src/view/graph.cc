#include "graph.h"

#include "ui_graph.h"

s21::Graph::Graph(QWidget *parent)
    : QDialog(parent), ui_(new Ui::Graph), xBegin(0), xEnd(0), h(0.1) {
  ui_->setupUi(this);
}

s21::Graph::~Graph() { delete ui_; }

void s21::Graph::slot_text(QString text_calc) {
  this->text_ = text_calc.toStdString();
}

void s21::Graph::slot_x(QString text_x) { this->view_x_ = text_x; }

void s21::Graph::PrintGraph() {
  ui_->widget->clearGraphs();
  xBegin = xEnd = 0;
  ui_->widget->xAxis->setRange(15, 15);
  ui_->widget->yAxis->setRange(15, 15);

  if (view_x_ == "") {
    xBegin = ui_->spin_x_begin->text().toInt();
    xEnd = ui_->spin_x_end->text().toInt();
  } else {
    xBegin = view_x_.toDouble() * (-1);
    xEnd = view_x_.toDouble();
  }
  ui_->widget->xAxis->setRange(xBegin, xEnd);
  ui_->widget->yAxis->setRange(xBegin, xEnd);
  ui_->spin_x_begin->setValue(xBegin);
  ui_->spin_x_end->setValue(xEnd);
  auto coordinates = this->add_coordinates_(xBegin, xEnd);
  ui_->widget->addGraph();
  ui_->widget->graph(0)->addData(coordinates.first, coordinates.second);
  ui_->widget->replot();
}

std::pair<QVector<double>, QVector<double>> s21::Graph::add_coordinates_(
    const double &xBegin, const double &xEnd) {
  QVector<double> x, y;
  for (double i = xBegin; i <= xEnd; i += 0.1) {
    x.push_back(i);
    y.push_back(control_result_.InputCalc(text_, i));
  }
  return std::pair<QVector<double>, QVector<double>>(x, y);
}

void s21::Graph::on_spin_x_begin_valueChanged() { this->PrintGraph(); }

void s21::Graph::on_spin_x_end_valueChanged() { this->PrintGraph(); }
