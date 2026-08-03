#include <algorithm>
#include <simToTerminalScaler.h>
#include <simulation.h>

SimToTerminalScaler::SimToTerminalScaler(int numCharsX, int numCharsY,
                                         Simulation &sim)
    : sim_(sim) {
  updateTerminalDimensions(numCharsX, numCharsY);
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

void SimToTerminalScaler::updateTerminalDimensions(int numCharsX,
                                                   int numCharsY) {
  maxXChars_ = numCharsX - 1;
  maxYChars_ = numCharsY - 1;
  double widthToHeightAspectRatio =
      0.5 * static_cast<double>(numCharsX) / static_cast<double>(numCharsY);
  sim_.setNewAspectRatio(widthToHeightAspectRatio);
  std::pair<double, double> mapDimensions = sim_.mapDimensionsWidthHeight();
  simToTerminalScaleX_ = static_cast<double>(numCharsX) / mapDimensions.first;
  simToTerminalScaleY_ = 0.5 * simToTerminalScaleX_;
}
