#pragma once

#include <memory>

class GameState;
class SimToTerminalScaler;

class GameLogicContainer {
public:
  GameLogicContainer(int numCharsX, int numCharsY);
  ~GameLogicContainer();

  GameState &gameState();
  SimToTerminalScaler &simScaler();

private:
  std::unique_ptr<GameState> gameState_;
  std::unique_ptr<SimToTerminalScaler> simScaler_;
};
