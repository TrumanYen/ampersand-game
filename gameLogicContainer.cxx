#include <gameLogicContainer.h>

#include <gameState.h>
#include <simToTerminalScaler.h>

GameLogicContainer::GameLogicContainer()
    : gameState_(std::make_unique<GameState>()),
      simScaler_(std::make_unique<SimToTerminalScaler>(*gameState_)) {}

GameLogicContainer::~GameLogicContainer() = default;

GameState &GameLogicContainer::gameState() { return *gameState_; }

SimToTerminalScaler &GameLogicContainer::simScaler() { return *simScaler_; }
