#include <domain/simulationDomain.h>

#include <domain/ampersandSimulation.h>
#include <domain/mapState.h>

namespace {
const double AMPERSAND_RADIUS = 0.01;
const double DOUBLE_AMPERSAND_RADIUS = 2.0 * AMPERSAND_RADIUS;
const double DOUBLE_AMPERSAND_RADIUS_SQRD =
    DOUBLE_AMPERSAND_RADIUS * DOUBLE_AMPERSAND_RADIUS;

// TODO: deduplicate these overloads by just using our own coordinate class
// (currently duplicated in EnemyPilot)
std::pair<double, double> operator-(std::pair<double, double> a,
                                    std::pair<double, double> b) {
  return std::pair<double, double>(a.first - b.first, a.second - b.second);
}
} // namespace

SimulationDomain::SimulationDomain()
    : mapState_(std::make_unique<MapState>()),
      ampersandSim_(std::make_unique<AmpersandSimulation>(
          *mapState_, mapState_->topLeft())),
      enemyAmpersandSim_(std::make_unique<AmpersandSimulation>(
          *mapState_, mapState_->topRight())) {}

SimulationDomain::~SimulationDomain() {}

bool SimulationDomain::ampersandsHaveCollided() const {
  std::pair<double, double> displacementBetweenAmpersands =
      ampersandSim_->currentPos() - enemyAmpersandSim_->currentPos();
  double distanceSquaredMagnitude = (displacementBetweenAmpersands.first *
                                     displacementBetweenAmpersands.first) +
                                    (displacementBetweenAmpersands.second *
                                     displacementBetweenAmpersands.second);
  if (distanceSquaredMagnitude <= DOUBLE_AMPERSAND_RADIUS_SQRD) {
    return true;
  }
  return false;
}

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
