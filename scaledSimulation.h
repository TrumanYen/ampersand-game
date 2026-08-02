#pragma once

#include <utility>

class Simulation;

class ScaledSimulation {
public:
  ScaledSimulation(int numCharsX, int numCharsY, Simulation &sim);

  ~ScaledSimulation();

  // Can hide behind an interface in the future if we only want some funtions
  // accessible:
  Simulation &sim(); // deprecate
  std::pair<int, int> currentPositionCharsXY();

private:
  int maxXChars_;
  int maxYChars_;
  double simToTerminalScaleX_;
  double simToTerminalScaleY_;

  Simulation &sim_;
};
