#pragma once

#include <utility>

class AmpersandSimulation;
class GameState;

class SimToTerminalScaler {
public:
  SimToTerminalScaler(GameState &gameState);

  ~SimToTerminalScaler();

  std::pair<int, int> currentPositionCharsXY();
  std::pair<int, int> enemyCurrentPositionCharsXY();
  void updateTerminalDimensions(int numCharsX, int numCharsY);

private:
  std::pair<int, int>
  ampersandPositionCharsXY(const AmpersandSimulation &ampersand);

private:
  int maxXChars_;
  int maxYChars_;
  double simToTerminalScaleX_;
  double simToTerminalScaleY_;
  GameState &gameState_;
};
