#pragma once

#include <utility>

class AmpersandSimulation;
class SimulationDomain;

class SimToTerminalScaler {
public:
  SimToTerminalScaler(SimulationDomain &simulationDomain);

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
  SimulationDomain &simulationDomain_;
};
