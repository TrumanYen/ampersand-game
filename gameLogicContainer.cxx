#include <gameLogicContainer.h>

#include <simToTerminalScaler.h>
#include <ampersandSimulation.h>

GameLogicContainer::GameLogicContainer(int numCharsX, int numCharsY)
    : ampersand_(std::make_unique<AmpersandSimulation>()),
      simScaler_(std::make_unique<SimToTerminalScaler>(numCharsX, numCharsY,
                                                       *ampersand_)) {}

GameLogicContainer::~GameLogicContainer() = default;

AmpersandSimulation &GameLogicContainer::ampersand() { return *ampersand_; }

SimToTerminalScaler &GameLogicContainer::simScaler() { return *simScaler_; }
