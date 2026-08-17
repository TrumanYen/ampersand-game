#pragma once

#include <utility>

enum class TuiColor { Red, Green, Blue };

struct TuiCell {
  char character;
  TuiColor color;
  std::pair<int, int> location;
};
