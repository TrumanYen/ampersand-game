#include <simulationDomain.h>

#include <ampersandSimulation.h>
#include <mapState.h>

SimulationDomain::SimulationDomain()
    : mapState_(std::make_unique<MapState>()),
      ampersandSim_(std::make_unique<AmpersandSimulation>(
          *mapState_, mapState_->topLeft())),
      enemyAmpersandSim_(std::make_unique<AmpersandSimulation>(
          *mapState_, mapState_->topRight())) {}

SimulationDomain::~SimulationDomain() {}

void SimulationDomain::incrementTimeMs(double timeDeltaMs) {
  double timeDeltaSeconds = 1e-3 * timeDeltaMs;
  mapState_->incrementTime(timeDeltaSeconds);
  ampersandSim_->incrementTime(timeDeltaSeconds);
  enemyAmpersandSim_->incrementTime(timeDeltaSeconds);
}

MapState &SimulationDomain::mapState() { return *mapState_; }

AmpersandSimulation &SimulationDomain::ampersandSim() { return *ampersandSim_; }

AmpersandSimulation &SimulationDomain::enemyAmpersandSim() {
  return *enemyAmpersandSim_;
}
