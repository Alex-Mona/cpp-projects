#include "facade.h"

namespace s21 {
Facade::Facade() {
  strategies_ = {new RotateStrategy(figure_, affine_),
                 new MoveStrategy(figure_, affine_),
                 new ScaleStrategy(figure_, affine_)};
}
Facade::~Facade() {
  for (auto strategy : strategies_) {
    delete strategy;
  }
}

//  Parser
void Facade::Parse(const std::string& file_name) {
  parser_.Parse(file_name, figure_);
}

// Affine
void Facade::Move(double move, Operation role) {
  invoker_.Execute(new MoveCommand(strategies_[kPositionStrategy]), role, move);
}
void Facade::Transform(double angle, Operation role) {
  invoker_.Execute(new RotateCommand(strategies_[kRotationStrategy]), role, angle);
}
void Facade::Scale(double scale, Operation role) {
  invoker_.Execute(new ScaleCommand(strategies_[kScaleStrategy]), role, scale);
}

// Figure
void Facade::Clear() { figure_.Clear(); }

const std::vector<double>& Facade::GetVertexes() {
  return figure_.GetVertexes();
}
const std::vector<int>& Facade::GetFacets() { return figure_.GetFacets(); }
int Facade::GetCountVertexes() const { return figure_.GetCountVertexes(); }
int Facade::GetCountEdges() const { return figure_.GetCountEdges(); }
int Facade::GetCountPolygons() const { return figure_.GetCountPolygons(); }
double Facade::GetMaxCoordinate() const { return figure_.GetMaxCoordinate(); }

void Facade::SetVertexes(std::vector<double>& vertexes) {
  figure_.SetVertexes(vertexes);
}
void Facade::SetFacets(std::vector<int>& facets) { figure_.SetFacets(facets); }
void Facade::SetCountVertexes(int count_vertexes) {
  figure_.SetCountVertexes(count_vertexes);
}
void Facade::SetCountEdges(int count_edges) {
  figure_.SetCountEdges(count_edges);
}
void Facade::SetCountPolygons(int count_polygons) {
  figure_.SetCountPolygons(count_polygons);
}
void Facade::SetMaxCoordinate(double max_coordinate) {
  figure_.SetMaxCoordinate(max_coordinate);
}
}  // namespace s21
