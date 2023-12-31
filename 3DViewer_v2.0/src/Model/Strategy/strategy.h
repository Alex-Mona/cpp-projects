#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_STRATEGY_STRATEGY_H_
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_STRATEGY_STRATEGY_H_

#include "../Affine/affine.h"

namespace s21 {
enum Strategies { kRotationStrategy, kPositionStrategy, kScaleStrategy };
enum Operation {
  kRotationSliderX,
  kRotationSliderY,
  kRotationSliderZ,
  kPositionPlusX,
  kPositionMinusX,
  kPositionPlusY,
  kPositionMinusY,
  kPositionPlusZ,
  kPositionMinusZ,
  kScalePlusX,
  kScaleMinusX,
  kScalePlusY,
  kScaleMinusY,
  kScalePlusZ,
  kScaleMinusZ,
  kScaleMouseAll,
  kScaleScrollAll
};

class Strategy {
 public:
  virtual ~Strategy() = default;
  virtual void Execute(Operation role, double value) = 0;
};

class RotateStrategy : public Strategy {
 public:
  RotateStrategy(Figure& figure, Affine& affine);
  void Execute(Operation role, double value) override;

 private:
  double value_;
  Figure& figure_;
  Affine& affine_;
  void RotateXSlider();
  void RotateYSlider();
  void RotateZSlider();
};

class MoveStrategy : public Strategy {
 public:
  MoveStrategy(Figure& figure, Affine& affine);
  void Execute(Operation role, double value) override;

 private:
  double value_;
  Figure& figure_;
  Affine& affine_;
  void MoveXPlus();
  void MoveXMinus();
  void MoveYPlus();
  void MoveYMinus();
  void MoveZPlus();
  void MoveZMinus();
};

class ScaleStrategy : public Strategy {
 public:
  ScaleStrategy(Figure& figure, Affine& affine);
  void Execute(Operation role, double value) override;

 private:
  double value_;
  Figure& figure_;
  Affine& affine_;
  void ScalePlusX();
  void ScaleMinusX();
  void ScalePlusY();
  void ScaleMinusY();
  void ScalePlusZ();
  void ScaleMinusZ();
  void ScaleMouseAll();
  void ScaleScrollAll();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_STRATEGY_STRATEGY_H_
