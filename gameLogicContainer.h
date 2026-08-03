#pragma once

#include <memory>

class AmpersandSimulation;
class SimToTerminalScaler;

class GameLogicContainer {
public:
  GameLogicContainer(int numCharsX, int numCharsY);
  ~GameLogicContainer();

  AmpersandSimulation &ampersand();
  SimToTerminalScaler &simScaler();

private:
  std::unique_ptr<AmpersandSimulation> ampersand_;
  std::unique_ptr<SimToTerminalScaler> simScaler_;
};
