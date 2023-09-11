#ifndef CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_PARSER_H_
#define CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_PARSER_H_

#include <string.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../Figure/figure.h"

typedef std::pair<int, int> Pairs;

namespace s21 {
class Parser {
 public:
  Parser();
  void Parse(const std::string& file_name, Figure& figure);

 private:
  std::vector<double> vertexes_;
  std::vector<int> facets_;
  int count_vertexes_;
  int count_polygons_;
  double max_coordinate_;

  void SetFigure(Figure& figure);

  bool ParseConditions(std::string& file_line, char type);
  void ParseVertexes(std::string& file_line);
  void ParseFacets(std::string& file_line);
  int ParseEdges();
  std::vector<double> ParseLine(std::string& file_line);
  void DelSpace(std::string& file_line);
  void Clear();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_MODEL_PARSER_PARSER_H_
