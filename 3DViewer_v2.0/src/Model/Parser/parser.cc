#include "parser.h"

namespace s21 {
Parser::Parser() : count_vertexes_(0), count_polygons_(0), max_coordinate_(0) {}

void Parser::Parse(const std::string& file_name, Figure& figure) {
  std::ifstream file(file_name);
  Clear();
  size_t last_dot = file_name.find_last_of('.');
  if (file.is_open() && file_name.substr(last_dot) == ".obj") {
    std::string file_line;
    while (std::getline(file, file_line)) {
      if (ParseConditions(file_line, 'v')) {
        ParseVertexes(file_line);
      } else if (ParseConditions(file_line, 'f')) {
        ParseFacets(file_line);
      }
    }
  }
  SetFigure(figure);
}

bool Parser::ParseConditions(std::string& file_line, char type) {
  bool success = false;
  while (!file_line.empty() && isspace(file_line.front())) {
    file_line.erase(file_line.begin());
  }
  if (!file_line.empty() && file_line.front() == type && \
      isspace(file_line.at(1))) {
    file_line.erase(file_line.begin());
    success = true;
  }
  return success;
}

void Parser::ParseVertexes(std::string& file_line) {
  std::vector<double> vec = ParseLine(file_line);
  for (size_t i = 0; i < 3; ++i) {
    vertexes_.push_back(vec.at(i));
    double mc = fabs(vec.at(i));
    if (mc > max_coordinate_) {
      max_coordinate_ = mc;
    }
  }
  count_vertexes_++;
}

void Parser::ParseFacets(std::string& file_line) {
  int plus = 0;
  std::vector<double> vec = ParseLine(file_line);
  vec.at(0) >= 0 ? plus = -1 : plus = count_vertexes_;
  facets_.push_back(vec.at(0) + plus);
  for (size_t i = 1; i < vec.size(); i++) {
    facets_.push_back(vec.at(i) + plus);
    facets_.push_back(vec.at(i) + plus);
  }
  facets_.push_back(vec.at(0) + plus);
  count_polygons_++;
}

int Parser::ParseEdges() {
  std::set<Pairs> edges;
  for (size_t i = 1; i < facets_.size(); i++) {
    if ((i + 1) % 2 == 0) {
      Pairs edge = std::make_pair(facets_.at(i - 1), facets_.at(i));
      edges.insert(edge);
      Pairs edge_mirror = std::make_pair(facets_.at(i), facets_.at(i - 1));
      edges.erase(edge_mirror);
    }
  }
  return edges.size();
}

std::vector<double> Parser::ParseLine(std::string& file_line) {
  std::vector<double> res;
  while (!file_line.empty()) {
    DelSpace(file_line);
    std::string num;
    num = file_line.substr(0, file_line.find_first_of(' '));
    if (!num.empty())
      res.push_back(std::stod(num));
    file_line.erase(0, num.size());
  }
  return res;
}

void Parser::DelSpace(std::string& file_line) {
  while (!file_line.empty() && isspace(file_line.at(0))) {
    file_line.erase(file_line.begin());
  }
}

void Parser::SetFigure(Figure& figure) {
  figure.SetFacets(facets_);
  figure.SetVertexes(vertexes_);
  figure.SetCountEdges(ParseEdges());
  figure.SetCountPolygons(count_polygons_);
  figure.SetCountVertexes(count_vertexes_);
  figure.SetMaxCoordinate(max_coordinate_);
}

void Parser::Clear() {
  vertexes_.clear();
  facets_.clear();
  count_vertexes_ = 0;
  count_polygons_ = 0;
  max_coordinate_ = 0;
}

}  // namespace s21
