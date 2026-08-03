#include <gameLogicContainer.h>

#include <simToTerminalScaler.h>
#include <simulation.h>

GameLogicContainer::GameLogicContainer(int numCharsX, int numCharsY)
    : sim_(std::make_unique<Simulation>()),
      scaledSim_(
          std::make_unique<SimToTerminalScaler>(numCharsX, numCharsY, *sim_)) {}

GameLogicContainer::~GameLogicContainer() = default;

Simulation &GameLogicContainer::sim() { return *sim_; }

SimToTerminalScaler &GameLogicContainer::simScaler() { return *scaledSim_; }
