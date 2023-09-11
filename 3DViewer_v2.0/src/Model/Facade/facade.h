#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H_
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H_
#include <string.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../Command/command.h"
#include "../Parser/parser.h"

namespace s21 {
class Facade {
 public:
  Facade();
  ~Facade();

  void Parse(const std::string& file_name);
  void Move(double move, Operation role);
  void Transform(double angle, Operation role);
  void Scale(double scale, Operation role);
  void Clear();

  const std::vector<double>& GetVertexes();
  const std::vector<int>& GetFacets();
  int GetCountVertexes() const;
  int GetCountEdges() const;
  int GetCountPolygons() const;
  double GetMaxCoordinate() const;

  void SetVertexes(std::vector<double>& vertexes);
  void SetFacets(std::vector<int>& facets);
  void SetCountVertexes(int count_vertexes);
  void SetCountEdges(int count_edges);
  void SetCountPolygons(int count_polygons);
  void SetMaxCoordinate(double max_coordinate);

 private:
  Parser parser_;
  Affine affine_;
  Figure figure_;
  Invoker invoker_;
  std::vector<Strategy*> strategies_;
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_MODEL_H_
