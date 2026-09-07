#pragma once

#include <toolkit/vector2d.h>

enum class TuiColor { Red, Green, Blue, White };

struct TuiCell {
  char character;
  TuiColor color;
  Vector2D<int> location;
};
