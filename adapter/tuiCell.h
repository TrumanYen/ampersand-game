#pragma once

#include <domain/vector2d.h>

enum class TuiColor { Red, Green, Blue, WhiteOnRed, Transparent };

struct TuiCell {
  char character;
  TuiColor color;
  Vector2D<int> location;
};
