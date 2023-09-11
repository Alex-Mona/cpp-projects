#include "figure.h"
namespace s21 {
Figure::Figure()
    : vertexes_(std::vector<double>()),
      facets_(std::vector<int>()),
      count_vertexes_(0),
      count_edges_(0),
      count_polygons_(0),
      max_coordinate_(0) {}

void Figure::Clear() {
  vertexes_.clear();
  facets_.clear();
  count_vertexes_ = 0;
  count_edges_ = 0;
  count_polygons_ = 0;
  max_coordinate_ = 0;
}

const std::vector<double>& Figure::GetVertexes() { return vertexes_; }
const std::vector<int>& Figure::GetFacets() { return facets_; }
int Figure::GetCountVertexes() const { return count_vertexes_; }
int Figure::GetCountEdges() const { return count_edges_; }
int Figure::GetCountPolygons() const { return count_polygons_; }
double Figure::GetMaxCoordinate() const { return max_coordinate_; }

void Figure::SetVertexes(std::vector<double>& vertexes) {
  vertexes_ = vertexes;
}
void Figure::SetFacets(std::vector<int>& facets) { facets_ = facets; }
void Figure::SetCountVertexes(int count_vertexes) {
  count_vertexes_ = count_vertexes;
}
void Figure::SetCountEdges(int count_edges) { count_edges_ = count_edges; }
void Figure::SetCountPolygons(int count_polygons) {
  count_polygons_ = count_polygons;
}
void Figure::SetMaxCoordinate(double max_coordinate) {
  max_coordinate_ = max_coordinate;
}
}  // namespace s21
