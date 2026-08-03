#pragma once

#include <utility>

class GameState;

class SimToTerminalScaler {
public:
  SimToTerminalScaler(int numCharsX, int numCharsY, GameState &gameState);

  ~SimToTerminalScaler();

  std::pair<int, int> currentPositionCharsXY();
  void updateTerminalDimensions(int numCharsX, int numCharsY);

private:
  GameState &gameState_;
  int maxXChars_;
  int maxYChars_;
  double simToTerminalScaleX_;
  double simToTerminalScaleY_;
};
