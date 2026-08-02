#include <gameLogicContainer.h>

#include <scaledSimulation.h>
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
          std::make_unique<ScaledSimulation>(numCharsX, numCharsY, *sim_)) {}

GameLogicContainer::~GameLogicContainer() = default;

Simulation &GameLogicContainer::sim() { return *sim_; }

ScaledSimulation &GameLogicContainer::scaledSim() { return *scaledSim_; }
