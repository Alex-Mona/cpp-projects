#include "mainwindow.h"
// Доделать GStyle - переименовать методы
namespace s21 {
MainWindow::MainWindow(QWidget* parent)
    : QOpenGLWidget(parent), ui_(new Ui::MainWindow) {
  value_ = 0.0;
  x_rotation_ = y_rotation_ = z_rotation_ = 0.0;
  last_position_x_ = last_position_y_ = 0.0;
  number_fps_ = 0;

  ui_->setupUi(this);
  settings_ = new QSettings(this);
  LoadSettings();
  gif_timer_ = new QTimer(0);
  connect(gif_timer_, SIGNAL(timeout()), this, SLOT(GifCreator()));
}

MainWindow::~MainWindow() {
  delete gif_timer_;
  controller_.Remove();
  delete settings_;
  delete ui_;
}

void MainWindow::initializeGL() {
  SetupPerspective();
  glEnable(GL_DEPTH_TEST);
}

void MainWindow::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);

  float aspect = (float)w / (float)h;
  glOrtho(-aspect, aspect, -1, 1, -1, 1);
  glMatrixMode(GL_MODELVIEW);

  glLoadIdentity();
}

void MainWindow::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  SetupPerspective();
  glRotatef(x_rotation_, 1, 0, 0);
  glRotatef(y_rotation_, 0, 1, 0);
  Draw();
}

void MainWindow::on_pushButton_select_name_clicked() {
  file_ =
      QFileDialog::getOpenFileName(this, "Select File", "", QString("*.obj"));
  if (file_ != "") {
    this->setWindowTitle(file_);
    InitFile(file_.toStdString());
    update();
  }
}

void MainWindow::InitFile(std::string path) {
  controller_.Parse(path);
  max_coordinate_ = controller_.getMaxCoordinate() * 1.5;
  ui_->label_info_v->setNum(static_cast<int>(controller_.getCountVertexes()));
  ui_->label_info_e->setNum(static_cast<int>(controller_.getCountEdges()));
  ui_->label_info_p->setNum(static_cast<int>(controller_.getCountPolygons()));
  update();
}

void MainWindow::on_pushButton_reset_clicked() {
  controller_.Remove();
  x_rotation_ = 0;
  y_rotation_ = 0;
  InitFile(file_.toStdString());
  update();
}

void MainWindow::mousePressEvent(QMouseEvent* mo) {
  last_position_x_ = mo->pos().x();
  last_position_y_ = mo->pos().y();
}

void MainWindow::mouseMoveEvent(QMouseEvent* mo) {
  if (mo->pos().x() > last_position_x_) {
    y_rotation_ += 2;
  } else if (mo->pos().x() < last_position_x_) {
    y_rotation_ -= 2;
  }
  if (mo->pos().y() > last_position_y_) {
    x_rotation_ += 2;
  } else if (mo->pos().y() < last_position_y_) {
    x_rotation_ -= 2;
  }
  last_position_x_ = mo->pos().x();
  last_position_y_ = mo->pos().y();
  update();
}

void MainWindow::SetupPerspective() {
  GLdouble zNear = 0.001;
  GLdouble zFar = (max_coordinate_ + 5) * 5;

  if (ui_->projection_type->currentIndex() == 1) {
    GLdouble fovY = 90;
    GLdouble fH = tan(fovY / 360 * M_PI) * zNear;
    GLdouble fW = fH;

    glFrustum(-fW, fW, -fH, fH, zNear, zFar);
    glTranslatef(0, 0, -max_coordinate_);
  } else {
    glOrtho(-max_coordinate_, max_coordinate_, -max_coordinate_,
            max_coordinate_, -max_coordinate_, zFar);
    glTranslated(0, 0, -3);
  }
}

void MainWindow::Draw() {
  glVertexPointer(3, GL_DOUBLE, 0, controller_.getVertexes().data());
  glEnableClientState(GL_VERTEX_ARRAY);
  glClearColor(background_color_r_, background_color_g_, background_color_b_,
               0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Draw edges
  glLineWidth(0.1);
  glColor3f(edge_color_r_, edge_color_g_, edge_color_b_);
  if (ui_->radioButton_line->isChecked()) {
    glDisable(GL_LINE_STIPPLE);
  } else if (ui_->radioButton_stipple->isChecked()) {
    glLineStipple(10, 0x3333);
    glEnable(GL_LINE_STIPPLE);
  }
  glLineWidth(ui_->spinBox_edges_size->value());
  glDrawElements(GL_LINES, static_cast<int>(controller_.getFacets().size()),
                 GL_UNSIGNED_INT, controller_.getFacets().data());
  glDisableClientState(GL_VERTEX_ARRAY);

  // Draw vertexes
  glLineWidth(0.1);
  if (ui_->radioButton_norm->isChecked()) {
  } else {
    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(vertex_color_r_, vertex_color_g_, vertex_color_b_);

    if (ui_->radioButton_circles->isChecked()) {
      glEnable(GL_POINT_SMOOTH);
      glDrawArrays(GL_POINTS, 0, controller_.getCountVertexes());
      glDisable(GL_POINT_SMOOTH);
    } else if (ui_->radioButton_quads->isChecked()) {
      glDrawArrays(GL_POINTS, 0, controller_.getCountVertexes());
    }

    glDisable(GL_POINT_SMOOTH);

    glPointSize(ui_->spinBox_vertexes_size->value());

    glDisableClientState(GL_VERTEX_ARRAY);
  }
  update();
}

void MainWindow::on_projection_type_activated() { update(); }

void MainWindow::on_spinBox_vertexes_size_valueChanged() { update(); }

void MainWindow::on_spinBox_edges_size_valueChanged() { update(); }

void MainWindow::on_pushButton_save_settings_clicked() { SaveSettings(); }

void MainWindow::wheelEvent(QWheelEvent* event) {
  controller_.Scale(event->angleDelta().y(), kScaleMouseAll);
  update();
}

void MainWindow::on_horizontalScrollBar_valueChanged(int value) {
  value_ = value;
}

void MainWindow::on_horizontalScrollBar_sliderReleased() {
  controller_.Scale(value_, kScaleScrollAll);
  ui_->horizontalScrollBar->setValue(0);
  update();
}

// Color
void MainWindow::SetColor(double value, void (MainWindow::*setFunc)(double),
                          QSpinBox* spinBox) {
  (this->*setFunc)(value / 100.0);
  spinBox->setValue(value);
  update();
}
void MainWindow::on_horizontalScrollBar_bgr_R_valueChanged(int value) {
  SetColor(value, &MainWindow::SetBackgroundColorR, ui_->spinBox_bgr_R);
}
void MainWindow::on_horizontalScrollBar_bgr_G_valueChanged(int value) {
  SetColor(value, &MainWindow::SetBackgroundColorG, ui_->spinBox_bgr_G);
}
void MainWindow::on_horizontalScrollBar_bgr_B_valueChanged(int value) {
  SetColor(value, &MainWindow::SetBackgroundColorB, ui_->spinBox_bgr_B);
}
void MainWindow::on_horizontalScrollBar_edges_R_valueChanged(int value) {
  SetColor(value, &MainWindow::SetEdgeColorR, ui_->spinBox_edges_R);
}
void MainWindow::on_horizontalScrollBar_edges_G_valueChanged(int value) {
  SetColor(value, &MainWindow::SetEdgeColorG, ui_->spinBox_edges_G);
}
void MainWindow::on_horizontalScrollBar_edges_B_valueChanged(int value) {
  SetColor(value, &MainWindow::SetEdgeColorB, ui_->spinBox_edges_B);
}
void MainWindow::on_horizontalScrollBar_vertexes_R_valueChanged(int value) {
  SetColor(value, &MainWindow::SetVertexColorR, ui_->spinBox_vertexes_R);
}
void MainWindow::on_horizontalScrollBar_vertexes_G_valueChanged(int value) {
  SetColor(value, &MainWindow::SetVertexColorG, ui_->spinBox_vertexes_G);
}
void MainWindow::on_horizontalScrollBar_vertexes_B_valueChanged(int value) {
  SetColor(value, &MainWindow::SetVertexColorB, ui_->spinBox_vertexes_B);
}

// Scale
void MainWindow::on_pushButton_sc_x_plus_clicked() {
  controller_.Scale(ui_->doubleSpinBox_sc_value->value(), kScalePlusX);
  update();
}
void MainWindow::on_pushButton_sc_y_plus_clicked() {
  controller_.Scale(ui_->doubleSpinBox_sc_value->value(), kScalePlusY);
  update();
}
void MainWindow::on_pushButton_sc_z_plus_clicked() {
  controller_.Scale(ui_->doubleSpinBox_sc_value->value(), kScalePlusZ);
  update();
}
void MainWindow::on_pushButton_sc_x_minus_clicked() {
  controller_.Scale(ui_->doubleSpinBox_sc_value->value(), kScaleMinusX);
  update();
}
void MainWindow::on_pushButton_sc_y_minus_clicked() {
  controller_.Scale(ui_->doubleSpinBox_sc_value->value(), kScaleMinusY);
  update();
}
void MainWindow::on_pushButton_sc_z_minus_clicked() {
  controller_.Scale(ui_->doubleSpinBox_sc_value->value(), kScaleMinusZ);
  update();
}

// Rotate
void MainWindow::on_horizontalScrollBar_rot_x_valueChanged(int value) {
  value_ = value;
}
void MainWindow::on_horizontalScrollBar_rot_x_sliderReleased() {
  controller_.Transform(value_, kRotationSliderX);
  ui_->horizontalScrollBar_rot_x->setValue(0);
  update();
}
void MainWindow::on_horizontalScrollBar_rot_y_valueChanged(int value) {
  value_ = value;
}
void MainWindow::on_horizontalScrollBar_rot_y_sliderReleased() {
  controller_.Transform(value_, kRotationSliderY);
  ui_->horizontalScrollBar_rot_y->setValue(0);
  update();
}
void MainWindow::on_horizontalScrollBar_rot_z_valueChanged(int value) {
  value_ = value;
}
void MainWindow::on_horizontalScrollBar_rot_z_sliderReleased() {
  controller_.Transform(value_, kRotationSliderZ);
  ui_->horizontalScrollBar_rot_z->setValue(0);
  update();
}

// Move
void MainWindow::on_pushButton_mv_x_plus_clicked() {
  controller_.Move(ui_->doubleSpinBox_mv_value->value(), kPositionPlusX);
  update();
}
void MainWindow::on_pushButton_mv_x_minus_clicked() {
  controller_.Move(ui_->doubleSpinBox_mv_value->value(), kPositionMinusX);
  update();
}
void MainWindow::on_pushButton_mv_y_plus_clicked() {
  controller_.Move(ui_->doubleSpinBox_mv_value->value(), kPositionPlusY);
  update();
}
void MainWindow::on_pushButton_mv_y_minus_clicked() {
  controller_.Move(ui_->doubleSpinBox_mv_value->value(), kPositionMinusY);
  update();
}
void MainWindow::on_pushButton_mv_z_plus_clicked() {
  controller_.Move(ui_->doubleSpinBox_mv_value->value(), kPositionPlusZ);
  update();
}
void MainWindow::on_pushButton_mv_z_minus_clicked() {
  controller_.Move(ui_->doubleSpinBox_mv_value->value(), kPositionMinusZ);
  update();
}

void MainWindow::on_pushButton_screenshot_clicked() {
  QFileDialog file_dialog_img(this);
  QString f_name = file_dialog_img.getSaveFileName(
      this, tr("Save a screenshot"), ".jpeg", tr("image (*.bmp *.jpeg)"));
  QImage img = grabFramebuffer();
  img.save(f_name);
}

void MainWindow::on_pushButton_gif_clicked() {
  gif_file_name_ = QFileDialog::getSaveFileName(this, tr("Save GIF"), ".gif",
                                                tr("Gif Files (*.gif)"));
  if (gif_file_name_ != "") {
    ui_->pushButton_gif->setDisabled(true);
    gif_image_ = new QGifImage;
    gif_image_->setDefaultDelay(10);
    GifTimer();
  } else {
    ShowMessage("Че делаешь, а? А ну вырубай!");
  }
}

void MainWindow::GifTimer() {
  gif_timer_->setInterval(100);
  gif_timer_->start();
}

void MainWindow::ShowMessage(QString message) {
  QMessageBox messageBox;
  messageBox.setFixedSize(500, 200);
  messageBox.information(0, "Info", message);
}

void MainWindow::GifCreator() {
  QImage image_ = grabFramebuffer();
  gif_image_->addFrame(image_);
  if (number_fps_ == 50) {
    gif_timer_->stop();
    gif_image_->save(gif_file_name_);
    number_fps_ = 0;
    ShowMessage("Gif saved.");
    delete gif_image_;
    ui_->pushButton_gif->setText("Gif");
    ui_->pushButton_gif->setEnabled(true);
  }
  ++number_fps_;
  if (!ui_->pushButton_gif->isEnabled()) {
    ui_->pushButton_gif->setText(QString::number(number_fps_ / 10));
  }
}

void MainWindow::SaveSettings() {
  settings_->setValue("projection_type", ui_->projection_type->currentIndex());
  settings_->setValue("edges_type_line", ui_->radioButton_line->isChecked());
  settings_->setValue("edges_type_stipple",
                      ui_->radioButton_stipple->isChecked());

  settings_->setValue("radioButton_norm", ui_->radioButton_norm->isChecked());
  settings_->setValue("radioButton_circles",
                      ui_->radioButton_circles->isChecked());
  settings_->setValue("radioButton_quads", ui_->radioButton_quads->isChecked());

  settings_->setValue("edges_size", ui_->spinBox_edges_size->value());
  settings_->setValue("vertexes_size", ui_->spinBox_vertexes_size->value());

  settings_->setValue("horizontalScrollBar_bgr_R",
                      ui_->horizontalScrollBar_bgr_R->value());
  settings_->setValue("horizontalScrollBar_bgr_G",
                      ui_->horizontalScrollBar_bgr_G->value());
  settings_->setValue("horizontalScrollBar_bgr_B",
                      ui_->horizontalScrollBar_bgr_B->value());

  settings_->setValue("horizontalScrollBar_edges_R",
                      ui_->horizontalScrollBar_edges_R->value());
  settings_->setValue("horizontalScrollBar_edges_G",
                      ui_->horizontalScrollBar_edges_G->value());
  settings_->setValue("horizontalScrollBar_edges_B",
                      ui_->horizontalScrollBar_edges_B->value());

  settings_->setValue("horizontalScrollBar_vertexes_R",
                      ui_->horizontalScrollBar_vertexes_R->value());
  settings_->setValue("horizontalScrollBar_vertexes_G",
                      ui_->horizontalScrollBar_vertexes_G->value());
  settings_->setValue("horizontalScrollBar_vertexes_B",
                      ui_->horizontalScrollBar_vertexes_B->value());
}

void MainWindow::LoadSettings() {
  ui_->projection_type->setCurrentIndex(
      settings_->value("projection_type", "0").toInt());
  ui_->radioButton_line->setChecked(
      settings_->value("edges_type_line", true).toBool());
  ui_->radioButton_stipple->setChecked(
      settings_->value("edges_type_stipple", true).toBool());

  ui_->radioButton_norm->setChecked(
      settings_->value("radioButton_norm", true).toBool());
  ui_->radioButton_circles->setChecked(
      settings_->value("radioButton_circles", true).toBool());
  ui_->radioButton_quads->setChecked(
      settings_->value("radioButton_quads", true).toBool());

  ui_->spinBox_edges_size->setValue(
      settings_->value("edges_size", "1").toInt());
  ui_->spinBox_vertexes_size->setValue(
      settings_->value("vertexes_size", "10").toInt());

  // back color
  ui_->horizontalScrollBar_bgr_R->setValue(
      settings_->value("horizontalScrollBar_bgr_R").toInt());
  ui_->horizontalScrollBar_bgr_G->setValue(
      settings_->value("horizontalScrollBar_bgr_G").toInt());
  ui_->horizontalScrollBar_bgr_B->setValue(
      settings_->value("horizontalScrollBar_bgr_B").toInt());

  ui_->horizontalScrollBar_edges_R->setValue(
      settings_->value("horizontalScrollBar_edges_R").toInt());
  ui_->horizontalScrollBar_edges_G->setValue(
      settings_->value("horizontalScrollBar_edges_G").toInt());
  ui_->horizontalScrollBar_edges_B->setValue(
      settings_->value("horizontalScrollBar_edges_B").toInt());

  ui_->horizontalScrollBar_vertexes_R->setValue(
      settings_->value("horizontalScrollBar_vertexes_R").toInt());
  ui_->horizontalScrollBar_vertexes_G->setValue(
      settings_->value("horizontalScrollBar_vertexes_G").toInt());
  ui_->horizontalScrollBar_vertexes_B->setValue(
      settings_->value("horizontalScrollBar_vertexes_B").toInt());
}

void MainWindow::SetBackgroundColorR(double background_color_r) {
  background_color_r_ = background_color_r;
}
void MainWindow::SetBackgroundColorG(double background_color_g) {
  background_color_g_ = background_color_g;
}
void MainWindow::SetBackgroundColorB(double background_color_b) {
  background_color_b_ = background_color_b;
}

void MainWindow::SetEdgeColorR(double edge_color_r) { edge_color_r_ = edge_color_r; }
void MainWindow::SetEdgeColorG(double edge_color_g) { edge_color_g_ = edge_color_g; }
void MainWindow::SetEdgeColorB(double edge_color_b) { edge_color_b_ = edge_color_b; }

void MainWindow::SetVertexColorR(double vertex_color_r) {
  vertex_color_r_ = vertex_color_r;
}
void MainWindow::SetVertexColorG(double vertex_color_g) {
  vertex_color_g_ = vertex_color_g;
}
void MainWindow::SetVertexColorB(double vertex_color_b) {
  vertex_color_b_ = vertex_color_b;
}
}  // namespace s21
