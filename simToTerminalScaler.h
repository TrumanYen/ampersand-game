#pragma once

#include <utility>

class AmpersandSimulation;
class GameState;

class SimToTerminalScaler {
public:
  SimToTerminalScaler(int numCharsX, int numCharsY, GameState &gameState);

  ~SimToTerminalScaler();

  std::pair<int, int> currentPositionCharsXY();
  std::pair<int, int> enemyCurrentPositionCharsXY();
  void updateTerminalDimensions(int numCharsX, int numCharsY);

private:
  std::pair<int, int>
  ampersandPositionCharsXY(const AmpersandSimulation &ampersand);

private:
  GameState &gameState_;
  int maxXChars_;
  int maxYChars_;
  double simToTerminalScaleX_;
  double simToTerminalScaleY_;
};
