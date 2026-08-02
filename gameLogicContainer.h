#pragma once

#include <memory>

class Simulation;
class ScaledSimulation;

class GameLogicContainer {
public:
  GameLogicContainer(int numCharsX, int numCharsY);
  ~GameLogicContainer();

  Simulation &sim();
  ScaledSimulation &scaledSim();

private:
  std::unique_ptr<Simulation> sim_;
  std::unique_ptr<ScaledSimulation> scaledSim_;
};
