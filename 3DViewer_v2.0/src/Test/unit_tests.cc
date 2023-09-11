#include <gtest/gtest.h>

#include "../Model/Facade/facade.h"
#define cube "Test/cube.obj"
#define accuracy 1e-7

TEST(Parser, parser1) {
  s21::Facade f;
  f.Parse(cube);
  EXPECT_EQ(f.GetCountVertexes(), 8);
  EXPECT_EQ(f.GetCountEdges(), 18);
  EXPECT_EQ(f.GetCountPolygons(), 12);
  EXPECT_EQ(f.GetMaxCoordinate(), 0.5);
}

TEST(Parser, parser2) {
  s21::Facade f;
  f.Parse(cube);
  f.Clear();

  EXPECT_EQ(f.GetCountVertexes(), 0);
  EXPECT_EQ(f.GetCountEdges(), 0);
  EXPECT_EQ(f.GetCountPolygons(), 0);
}

TEST(Affine, affine_move_plus_x) {
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 2;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Move(value, s21::kPositionPlusX);
  v_orig = f.GetVertexes();
  for (size_t i = 0; i < (v_copy.size() / 3); i++) {
    v_copy.at(i * 3) += value;
  }
  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }

  EXPECT_EQ(res, true);
}

TEST(Affine, affine_move_plus_y) {
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 2;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Move(value, s21::kPositionPlusY);
  v_orig = f.GetVertexes();
  for (size_t i = 0; i < (v_copy.size() / 3); i++) {
    v_copy.at(i * 3 + 1) += value;
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_move_plus_z) {
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 2;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Move(value, s21::kPositionPlusZ);
  v_orig = f.GetVertexes();
  for (size_t i = 0; i < (v_copy.size() / 3); i++) {
    v_copy.at(i * 3 + 2) += value;
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_move_minus_x) {
  std::vector<double> v_copy;
  s21::Facade f;
  double value = -1;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Move(-value, s21::kPositionMinusX);
  v_orig = f.GetVertexes();
  for (size_t i = 0; i < (v_copy.size() / 3); i++) {
    v_copy.at(i * 3) += value;
  }
  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }

  EXPECT_EQ(res, true);
}

TEST(Affine, affine_move_minus_y) {
  std::vector<double> v_copy;
  s21::Facade f;
  double value = -2;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Move(-value, s21::kPositionMinusY);
  v_orig = f.GetVertexes();
  for (size_t i = 0; i < (v_copy.size() / 3); i++) {
    v_copy.at(i * 3 + 1) += value;
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_move_minus_z) {
  std::vector<double> v_copy;
  s21::Facade f;
  double value = -2;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Move(-value, s21::kPositionMinusZ);
  v_orig = f.GetVertexes();
  for (size_t i = 0; i < (v_copy.size() / 3); i++) {
    v_copy.at(i * 3 + 2) += value;
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_tansform_plus_x) {
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 1;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Transform(value, s21::kRotationSliderX);
  v_orig = f.GetVertexes();
  value /= 36.0;
  for (size_t i = 0; i < (v_copy.size() / 3); i++) {
    double y = v_copy.at(i * 3 + 1);
    double z = v_copy.at(i * 3 + 2);
    v_copy.at(i * 3 + 1) = cos(value) * y - sin(value) * z;
    v_copy.at(i * 3 + 2) = sin(value) * y + cos(value) * z;
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_tansform_plus_y) {
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 2;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Transform(value, s21::kRotationSliderY);
  v_orig = f.GetVertexes();
  value /= 36.0;

  for (size_t i = 0; i < (v_copy.size() / 3); i++) {
    double x = v_copy.at(i * 3);
    double z = v_copy.at(i * 3 + 2);
    v_copy.at(i * 3) = cos(value) * x + sin(value) * z;
    v_copy.at(i * 3 + 2) = (-sin(value)) * x + cos(value) * z;
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_tansform_plus_z) {
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 2;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Transform(value, s21::kRotationSliderZ);
  v_orig = f.GetVertexes();
  value /= 36.0;

  for (size_t i = 0; i < (v_copy.size() / 3); i++) {
    double x = v_copy.at(i * 3);
    double y = v_copy.at(i * 3 + 1);

    v_copy.at(i * 3) = cos(value) * x - sin(value) * y;
    v_copy.at(i * 3 + 1) = sin(value) * x + cos(value) * y;
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_tansform_minus_x) {
  std::vector<double> v_copy;
  s21::Facade f;
  double value = -2;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Transform(value, s21::kRotationSliderX);
  v_orig = f.GetVertexes();
  value /= 36.0;

  for (size_t i = 0; i < (v_copy.size() / 3); i++) {
    double y = v_copy.at(i * 3 + 1);
    double z = v_copy.at(i * 3 + 2);
    v_copy.at(i * 3 + 1) = cos(value) * y - sin(value) * z;
    v_copy.at(i * 3 + 2) = sin(value) * y + cos(value) * z;
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_tansform_minus_y) {
  std::vector<double> v_copy;
  s21::Facade f;
  double value = -2;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Transform(value, s21::kRotationSliderY);
  v_orig = f.GetVertexes();
  value /= 36.0;

  for (size_t i = 0; i < (v_copy.size() / 3); i++) {
    double x = v_copy.at(i * 3);
    double z = v_copy.at(i * 3 + 2);
    v_copy.at(i * 3) = cos(value) * x + sin(value) * z;
    v_copy.at(i * 3 + 2) = (-sin(value)) * x + cos(value) * z;
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_tansform_minus_z) {
  std::vector<double> v_copy;
  s21::Facade f;
  double value = -2;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Transform(value, s21::kRotationSliderZ);
  v_orig = f.GetVertexes();
  value /= 36.0;

  for (size_t i = 0; i < (v_copy.size() / 3); i++) {
    double x = v_copy.at(i * 3);
    double y = v_copy.at(i * 3 + 1);

    v_copy.at(i * 3) = cos(value) * x - sin(value) * y;
    v_copy.at(i * 3 + 1) = sin(value) * x + cos(value) * y;
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_scaling_mouse_all) {
  size_t coor = 3;
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 0.9;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Scale(value, s21::kScaleMouseAll);
  v_orig = f.GetVertexes();
  value = 1 + value / 940.0;
  size_t i = coor;
  if (coor == kAll) {
    i = 0;
  }
  while (i < v_orig.size()) {
    v_copy.at(i) *= value;
    if (coor == kAll) {
      i++;
    } else {
      i += 3;
    }
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_scaling_scroll_all) {
  size_t coor = 3;
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 0.9;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Scale(value, s21::kScaleScrollAll);
  v_orig = f.GetVertexes();
  value = 1 + value * -1 / 2500.0;

  size_t i = coor;
  if (coor == kAll) {
    i = 0;
  }
  while (i < v_orig.size()) {
    v_copy.at(i) *= value;
    if (coor == kAll) {
      i++;
    } else {
      i += 3;
    }
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_scaling_plus_x) {
  size_t coor = 0;
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 0.9;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Scale(value, s21::kScalePlusX);
  v_orig = f.GetVertexes();
  value = 1 + value;

  size_t i = coor;
  if (coor == kAll) {
    i = 0;
  }
  while (i < v_orig.size()) {
    v_copy.at(i) *= value;
    if (coor == kAll) {
      i++;
    } else {
      i += 3;
    }
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_scaling_plus_y) {
  size_t coor = 1;
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 0.9;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Scale(value, s21::kScalePlusY);
  v_orig = f.GetVertexes();
  value = 1 + value;

  size_t i = coor;
  if (coor == kAll) {
    i = 0;
  }
  while (i < v_orig.size()) {
    v_copy.at(i) *= value;
    if (coor == kAll) {
      i++;
    } else {
      i += 3;
    }
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_scaling_plus_z) {
  size_t coor = 2;
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 0.9;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Scale(value, s21::kScalePlusZ);
  v_orig = f.GetVertexes();
  value = 1 + value;

  size_t i = coor;
  if (coor == kAll) {
    i = 0;
  }
  while (i < v_orig.size()) {
    v_copy.at(i) *= value;
    if (coor == kAll) {
      i++;
    } else {
      i += 3;
    }
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_scaling_minus_x) {
  size_t coor = 0;
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 0.9;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Scale(value, s21::kScaleMinusX);
  v_orig = f.GetVertexes();
  value = 1 - value;

  size_t i = coor;
  if (coor == kAll) {
    i = 0;
  }
  while (i < v_orig.size()) {
    v_copy.at(i) *= value;
    if (coor == kAll) {
      i++;
    } else {
      i += 3;
    }
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_scaling_minus_y) {
  size_t coor = 1;
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 0.9;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Scale(value, s21::kScaleMinusY);
  v_orig = f.GetVertexes();
  value = 1 - value;

  size_t i = coor;
  if (coor == kAll) {
    i = 0;
  }
  while (i < v_orig.size()) {
    v_copy.at(i) *= value;
    if (coor == kAll) {
      i++;
    } else {
      i += 3;
    }
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

TEST(Affine, affine_scaling_minus_z) {
  size_t coor = 2;
  std::vector<double> v_copy;
  s21::Facade f;
  double value = 0.9;
  bool res = true;

  f.Parse(cube);
  std::vector<double> v_orig = f.GetVertexes();
  for (size_t i = 0; i < v_orig.size(); i++) {
    v_copy.push_back(v_orig.at(i));
  }
  f.Scale(value, s21::kScaleMinusZ);
  v_orig = f.GetVertexes();
  value = 1 - value;

  size_t i = coor;
  if (coor == kAll) {
    i = 0;
  }
  while (i < v_orig.size()) {
    v_copy.at(i) *= value;
    if (coor == kAll) {
      i++;
    } else {
      i += 3;
    }
  }

  for (size_t i = 0; i < v_copy.size(); i++) {
    if (fabs((v_orig.at(i) - v_copy.at(i))) > accuracy) {
      res = false;
    }
  }
  EXPECT_EQ(res, true);
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
