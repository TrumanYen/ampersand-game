#include <gameLogicContainer.h>

#include <gameState.h>
#include <simToTerminalScaler.h>

GameLogicContainer::GameLogicContainer(int numCharsX, int numCharsY)
    : gameState_(std::make_unique<GameState>()),
      simScaler_(std::make_unique<SimToTerminalScaler>(numCharsX, numCharsY,
                                                       *gameState_)) {}

GameLogicContainer::~GameLogicContainer() = default;

GameState &GameLogicContainer::gameState() { return *gameState_; }

SimToTerminalScaler &GameLogicContainer::simScaler() { return *simScaler_; }
