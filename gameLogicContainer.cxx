#include <gameLogicContainer.h>

#include <simToTerminalScaler.h>
#include <simulation.h>

namespace {
// Yes I put logic in my container and nobody can stop me because this is my
// project
double getMapAspectRatioFromTerminalDimensions(int numCharsX, int numCharsY) {
  return 0.5 * static_cast<double>(numCharsX) / static_cast<double>(numCharsY);
}
} // namespace

GameLogicContainer::GameLogicContainer(int numCharsX, int numCharsY)
    : sim_(std::make_unique<Simulation>(
          getMapAspectRatioFromTerminalDimensions(numCharsX, numCharsY))),
      scaledSim_(
          std::make_unique<SimToTerminalScaler>(numCharsX, numCharsY, *sim_)) {}

GameLogicContainer::~GameLogicContainer() = default;

Simulation &GameLogicContainer::sim() { return *sim_; }

SimToTerminalScaler &GameLogicContainer::simScaler() { return *scaledSim_; }
