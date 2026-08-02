#include <algorithm>
#include <simToTerminalScaler.h>
#include <simulation.h>

SimToTerminalScaler::SimToTerminalScaler(int numCharsX, int numCharsY,
                                         Simulation &sim)
    : maxXChars_(numCharsX - 1), maxYChars_(numCharsY - 1), sim_(sim) {
  // account for the fact that each character is twice as tall as it is wide. We
  // want this to be the ratio that the player actually sees, reflected in the
  // simulation.
  std::pair<double, double> mapDimensions = sim_.mapDimensionsWidthHeight();
  simToTerminalScaleX_ = static_cast<double>(numCharsX) / mapDimensions.first;
  simToTerminalScaleY_ = 0.5 * simToTerminalScaleX_;
}

SimToTerminalScaler::~SimToTerminalScaler() = default;

std::pair<int, int> SimToTerminalScaler::currentPositionCharsXY() {
  std::pair<double, double> currentPosMeters = sim_.currentPos();

  int posXUnbounded = currentPosMeters.first * simToTerminalScaleX_;
  int posYUnbounded = currentPosMeters.second * simToTerminalScaleY_;
  int posXBounded = std::clamp(posXUnbounded, 0, maxXChars_);
  int posYBounded = std::clamp(posYUnbounded, 0, maxYChars_);

  return std::pair<int, int>(posXBounded, posYBounded);
}
