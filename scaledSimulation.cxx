#include <algorithm>
#include <scaledSimulation.h>

namespace {
static const double MAP_WIDTH_M = 10.0;
} // namespace

ScaledSimulation::ScaledSimulation(int numCharsX, int numCharsY)
    : maxXChars_(numCharsX - 1), maxYChars_(numCharsY - 1) {
  simToTerminalScaleX_ = static_cast<double>(maxXChars_) / MAP_WIDTH_M;
  simToTerminalScaleY_ = 0.5 * simToTerminalScaleX_;
  // account for the fact that each character is twice as tall as it is wide. We
  // want this to be the ratio that the player actually sees, reflected in the
  // simulation.
  double heightToWidthAspectRatio =
      2.0 * static_cast<double>(maxYChars_) / static_cast<double>(maxXChars_);
  double mapHeightM = heightToWidthAspectRatio * MAP_WIDTH_M;
  sim_ = std::make_unique<Simulation>(MAP_WIDTH_M, mapHeightM);
}

ScaledSimulation::~ScaledSimulation() = default;

Simulation &ScaledSimulation::sim() { return *sim_; }

std::pair<int, int> ScaledSimulation::currentPositionCharsXY() {
  std::pair<double, double> currentPosMeters = sim_->currentPos();

  int posXUnbounded = currentPosMeters.first * simToTerminalScaleX_;
  int posYUnbounded = currentPosMeters.second * simToTerminalScaleY_;
  int posXBounded = std::clamp(posXUnbounded, 0, maxXChars_);
  int posYBounded = std::clamp(posYUnbounded, 0, maxYChars_);

  return std::pair<int, int>(posXBounded, posYBounded);
}
