#pragma once

#include <utility>

class Simulation;

class SimToTerminalScaler {
public:
  SimToTerminalScaler(int numCharsX, int numCharsY, Simulation &sim);

  ~SimToTerminalScaler();

  std::pair<int, int> currentPositionCharsXY();

private:
  int maxXChars_;
  int maxYChars_;
  double simToTerminalScaleX_;
  double simToTerminalScaleY_;

  Simulation &sim_;
};
