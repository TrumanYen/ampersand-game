#include <domain/simulationDomain.h>

#include <domain/ampersandSimulation.h>
#include <domain/mapState.h>

SimulationDomain::SimulationDomain()
    : mapState_(std::make_unique<MapState>()),
      ampersandSim_(std::make_unique<AmpersandSimulation>(
          *mapState_, mapState_->topLeft())),
      enemyAmpersandSim_(std::make_unique<AmpersandSimulation>(
          *mapState_, mapState_->topRight())) {}

SimulationDomain::~SimulationDomain() {}

void SimulationDomain::incrementTime(double timeDeltaSeconds) {
  mapState_->incrementTime(timeDeltaSeconds);
  ampersandSim_->incrementTime(timeDeltaSeconds);
  enemyAmpersandSim_->incrementTime(timeDeltaSeconds);
}

MapState &SimulationDomain::mapState() { return *mapState_; }

AmpersandSimulation &SimulationDomain::ampersandSim() { return *ampersandSim_; }

AmpersandSimulation &SimulationDomain::enemyAmpersandSim() {
  return *enemyAmpersandSim_;
}
