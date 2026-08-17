#pragma once

#include <domain/vector2d.h>

enum class TuiColor { Red, Green, Blue };

struct TuiCell {
  char character;
  TuiColor color;
  Vector2D<int> location;
};
