#pragma once

#include <utility>

class Simulation;

class SimToTerminalScaler {
public:
  SimToTerminalScaler(int numCharsX, int numCharsY, Simulation &sim);

  ~SimToTerminalScaler();

  std::pair<int, int> currentPositionCharsXY();
  void updateTerminalDimensions(int numCharsX, int numCharsY);

private:
  Simulation &sim_;
  int maxXChars_;
  int maxYChars_;
  double simToTerminalScaleX_;
  double simToTerminalScaleY_;
};
