#pragma once

#include <memory>

class SimulationDomain;
class SimToTerminalScaler;

class GameLogicContainer {
public:
  GameLogicContainer();
  ~GameLogicContainer();

  SimulationDomain &simulationDomain();
  SimToTerminalScaler &simScaler();

private:
  std::unique_ptr<SimulationDomain> simulationDomain_;
  std::unique_ptr<SimToTerminalScaler> simScaler_;
};
