#pragma once

#include <memory>

class Simulation;
class SimToTerminalScaler;

class GameLogicContainer {
public:
  GameLogicContainer(int numCharsX, int numCharsY);
  ~GameLogicContainer();

  Simulation &sim();
  SimToTerminalScaler &simScaler();

private:
  std::unique_ptr<Simulation> sim_;
  std::unique_ptr<SimToTerminalScaler> scaledSim_;
};
