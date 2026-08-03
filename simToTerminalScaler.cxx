#include <algorithm>
#include <ampersandSimulation.h>
#include <gameState.h>
#include <mapState.h>
#include <simToTerminalScaler.h>

SimToTerminalScaler::SimToTerminalScaler(int numCharsX, int numCharsY,
                                         GameState &gameState)
    : gameState_(gameState) {
  updateTerminalDimensions(numCharsX, numCharsY);
}

SimToTerminalScaler::~SimToTerminalScaler() = default;

std::pair<int, int> SimToTerminalScaler::currentPositionCharsXY() {
  return ampersandPositionCharsXY(gameState_.ampersandSim());
}
std::pair<int, int> SimToTerminalScaler::enemyCurrentPositionCharsXY() {
  return ampersandPositionCharsXY(gameState_.enemyAmpersandSim());
}

void SimToTerminalScaler::updateTerminalDimensions(int numCharsX,
                                                   int numCharsY) {
  maxXChars_ = numCharsX - 1;
  maxYChars_ = numCharsY - 1;
  double heightToWidthAspectRatio =
      2.0 * static_cast<double>(numCharsY) / static_cast<double>(numCharsX);
  gameState_.mapState().setNewAspectRatio(heightToWidthAspectRatio);
  simToTerminalScaleX_ =
      static_cast<double>(numCharsX) / gameState_.mapState().mapWidthMeters();
  simToTerminalScaleY_ = 0.5 * simToTerminalScaleX_;
}

std::pair<int, int> SimToTerminalScaler::ampersandPositionCharsXY(
    const AmpersandSimulation &ampersand) {

  std::pair<double, double> currentPosMeters = ampersand.currentPos();

  int posXUnbounded = currentPosMeters.first * simToTerminalScaleX_;
  int posYUnbounded = currentPosMeters.second * simToTerminalScaleY_;
  int posXBounded = std::clamp(posXUnbounded, 0, maxXChars_);
  int posYBounded = std::clamp(posYUnbounded, 0, maxYChars_);

  return std::pair<int, int>(posXBounded, posYBounded);
}
