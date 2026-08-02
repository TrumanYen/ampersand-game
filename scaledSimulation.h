#pragma once

#include <memory>
#include <simulation.h>
#include <utility>

class ScaledSimulation {
public:
  ScaledSimulation(int numCharsX, int numCharsY);

  ~ScaledSimulation();

  // Can hide behind an interface in the future if we only want some funtions
  // accessible:
  Simulation &sim();
  std::pair<int, int> currentPositionCharsXY();

private:
  int maxXChars_;
  int maxYChars_;
  double simToTerminalScaleX_;
  double simToTerminalScaleY_;

  std::unique_ptr<Simulation> sim_;
};
