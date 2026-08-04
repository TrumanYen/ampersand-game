#pragma once

#include <utility>

class AmpersandSimulation;
class SimulationDomain;

class ViewModel {
public:
  ViewModel(SimulationDomain &simulationDomain);

  ~ViewModel();

  std::pair<int, int> currentPositionCharsXY() const;
  std::pair<int, int> enemyCurrentPositionCharsXY() const;

  void updateTerminalDimensions(int numCharsX, int numCharsY);

private:
  std::pair<int, int>
  ampersandPositionCharsXY(const AmpersandSimulation &ampersand) const;

private:
  int maxXChars_;
  int maxYChars_;
  double simToTerminalScaleX_;
  double simToTerminalScaleY_;
  SimulationDomain &simulationDomain_;
};
