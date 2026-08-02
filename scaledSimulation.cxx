#include <algorithm>
#include <scaledSimulation.h>
#include <simulation.h>

namespace {
static const double MAP_WIDTH_MM = 2000.0;
static const double DELTA_VELOCITY_MPS = 0.03;
} // namespace

ScaledSimulation::ScaledSimulation(int numCharsX, int numCharsY)
    : maxXChars_(numCharsX - 1), maxYChars_(numCharsY - 1) {
  simToTerminalScaleX_ = static_cast<double>(maxXChars_) / MAP_WIDTH_MM;
  simToTerminalScaleY_ = 0.5 * simToTerminalScaleX_;
  // account for the fact that each character is twice as tall as it is wide. We
  // want this to be the ratio that the player actually sees, reflected in the
  // simulation.
  double heightToWidthAspectRatio =
      2.0 * static_cast<double>(maxYChars_) / static_cast<double>(maxXChars_);
  double mapHeightMM = heightToWidthAspectRatio * MAP_WIDTH_MM;
  sim_ = std::make_unique<Simulation>(MAP_WIDTH_MM, mapHeightMM);
}

ScaledSimulation::~ScaledSimulation() = default;
void ScaledSimulation::accelerate(Direction direction) {

  double deltaVelX;
  double deltaVelY;
  switch (direction) {
  case Direction::Up:
    deltaVelX = 0.0;
    deltaVelY = -1.0 * DELTA_VELOCITY_MPS;
    break;
  case Direction::Down:
    deltaVelX = 0.0;
    deltaVelY = 1.0 * DELTA_VELOCITY_MPS;
    break;
  case Direction::Left:
    deltaVelX = -1.0 * DELTA_VELOCITY_MPS;
    deltaVelY = 0.0;
    break;
  case Direction::Right:
    deltaVelX = 1.0 * DELTA_VELOCITY_MPS;
    deltaVelY = 0.0;
    break;
  default:
    deltaVelX = 0.0;
    deltaVelY = 0.0;
  }
  sim_->incrementVelocity(deltaVelX, deltaVelY);
}

void ScaledSimulation::incrementTimeMs(int deltaTimeMs) {
  sim_->incrementTimeMs(deltaTimeMs);
}

std::pair<int, int> ScaledSimulation::currentPositionCharsXY() {
  std::pair<double, double> currentPosMeters = sim_->currentPos();

  int posXUnbounded = currentPosMeters.first * simToTerminalScaleX_;
  int posYUnbounded = currentPosMeters.second * simToTerminalScaleY_;
  int posXBounded = std::max(0, std::min(posXUnbounded, maxXChars_));
  int posYBounded = std::max(0, std::min(posYUnbounded, maxYChars_));

  return std::pair<int, int>(posXBounded, posYBounded);
}
