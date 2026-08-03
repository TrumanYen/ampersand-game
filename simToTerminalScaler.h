#pragma once

#include <utility>

class AmpersandSimulation;

class SimToTerminalScaler {
public:
  SimToTerminalScaler(int numCharsX, int numCharsY,
                      AmpersandSimulation &ampersand);

  ~SimToTerminalScaler();

  std::pair<int, int> currentPositionCharsXY();
  void updateTerminalDimensions(int numCharsX, int numCharsY);

private:
  AmpersandSimulation &ampersand_;
  int maxXChars_;
  int maxYChars_;
  double simToTerminalScaleX_;
  double simToTerminalScaleY_;
};
